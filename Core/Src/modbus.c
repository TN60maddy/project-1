/**
  ******************************************************************************
  * @file    Modbus.c
  * @brief   Modbus RTU slave implementation for multiple channels.
  * @details This file implements a multi-channel Modbus slave supporting:
  *            - USB CDC (MODBUS_CHANNEL_USB)
  *            - USART1  (MODBUS_CHANNEL_USART1)
  *            - UART4   (MODBUS_CHANNEL_UART4)
  *            - UART7   (MODBUS_CHANNEL_UART7)
  *
  *          The module provides functions to initialize and deinitialize a channel,
  *          handle RX callbacks for USB and UART, process Modbus frames, send responses,
  *          and provide IRQ handlers for UART channels.
  *
  *          The Modbus_Init function now returns an error code (-1 on error, 0 on success)
  *          and the internal channel structure now includes a function pointer (xProcessFunc)
  *          to process a received Modbus request, a flag (isInitialized), and a task handle.
  *
  * @author  
  *          Radhakrishnan Rajaram
  * @company 
  *          Aria Innovations Pvt Ltd
  * @version 
  *          1.3
  * @date    
  *          2025-03-24
  * @copyright Copyright (c) 2025 Aria Innovations Pvt Ltd.
  *            All rights reserved. Unauthorized copying, modification,
  *            or distribution of this file, via any medium, is strictly prohibited.
  *
  * Revision History:
  *  - v1.0: Initial version.
  *  - v1.1: Modified Modbus_Init to accept only one parameter.
  *  - v1.2: Added error return values, a function pointer typedef, removed queue members,
  *          added xProcessFunc, Modbus_SetProcessFunction, Modbus_UnsetProcessFunction, and modified frame processing.
  *  - v1.3: Added isInitialized and taskHandle to the internal state, added Modbus_Deinit, and updated Modbus_Init to check for reinitialization.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "modbus.h"
#include "stm32h7xx_hal.h"
#include "usbd_cdc_if.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include <string.h>
#include <stdio.h>
#include "uart.h"
#include "usb_device.h"

/* Private defines -----------------------------------------------------------*/
#define MODBUS_CHANNEL_COUNT 4

/* External UART handles (ensure these are defined in your project) */
extern UART_HandleTypeDef huart_usart1;
extern UART_HandleTypeDef huart_uart4;
extern UART_HandleTypeDef huart_uart7;

/* Internal Modbus channel state structure */
typedef struct {
    uint8_t rxBuffer[MODBUS_MAX_FRAME_LENGTH];
    uint16_t rxIndex;
    volatile uint8_t frameCompleteFlag;
    TimerHandle_t xInterCharTimer;
    uint8_t type;                   /* 0 = USB, 1 = UART */
    UART_HandleTypeDef *uartHandle; /* Valid if type==UART */
    uint8_t rxByte;                 /* For UART reception */
    ModbusFunctionPtr xProcessFunc; /* Function pointer to process the Modbus request */
    int16_t isInitialized;          /* Set to 1 when channel is initialized */
    TaskHandle_t taskHandle;        /* Handle for the FreeRTOS task */
} ModbusChannel_t;

/* Internal Modbus channel array */

static ModbusChannel_t modbusChannels[MODBUS_CHANNEL_COUNT];


/* Private function prototypes -----------------------------------------------*/
static uint16_t Modbus_CalcCRC(uint8_t *buffer, uint16_t length);
static void Modbus_InterCharTimerCallback(TimerHandle_t xTimer);
static void Modbus_SendFrame(ModbusChannel_t *channel, uint8_t *frame, uint16_t length);
static void Modbus_SendResponse(ModbusChannel_t *channel, ModbusResponse_t *response);
static void Modbus_ProcessFrame(ModbusChannel_t *channel);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief Calculates the Modbus RTU CRC-16.
  * @param buffer Pointer to the data buffer.
  * @param length Length of the data buffer.
  * @return Calculated CRC value.
  */
static uint16_t Modbus_CalcCRC(uint8_t *buffer, uint16_t length)
{
    uint16_t crc = 0xFFFF;
    for (uint16_t pos = 0; pos < length; pos++)
    {
        crc ^= (uint16_t)buffer[pos];
        for (int i = 0; i < 8; i++)
        {
            if (crc & 0x0001)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

/**
  * @brief Timer callback for inter-character timeout.
  * @param xTimer Timer handle.
  */
static void Modbus_InterCharTimerCallback(TimerHandle_t xTimer)
{
    ModbusChannel_t *channel = (ModbusChannel_t *)pvTimerGetTimerID(xTimer);
    if(channel != NULL)
    {
        channel->frameCompleteFlag = 1;
    }
}

/**
  * @brief Sends a frame via the specified channel.
  * @param channel Pointer to the internal Modbus channel state.
  * @param frame Pointer to the frame to be transmitted.
  * @param length Length of the frame in bytes.
  */
static void Modbus_SendFrame(ModbusChannel_t *channel, uint8_t *frame, uint16_t length)
{
    if(channel->type == 0) // USB
    {
        CDC_Transmit_FS(frame, length);
    }
    else if(channel->type == 1) // UART
    {
        HAL_UART_Transmit(channel->uartHandle, frame, length, HAL_MAX_DELAY);
    }
}

/**
  * @brief Builds and sends a Modbus response frame (with CRC) via the specified channel.
  * @param channel Pointer to the internal Modbus channel state.
  * @param response Pointer to the Modbus response data.
  */
static void Modbus_SendResponse(ModbusChannel_t *channel, ModbusResponse_t *response)
{
    uint8_t txFrame[MODBUS_MAX_FRAME_LENGTH];
    uint16_t frameLen = 0;

    if(response->errorCode != 0)
    {
        txFrame[frameLen++] = response->slaveId;
        txFrame[frameLen++] = response->functionCode | 0x80;
        txFrame[frameLen++] = response->errorCode;
    }
    else
    {
        if(response->functionCode == MODBUS_FUNC_READ_HOLDING)
        {
            txFrame[frameLen++] = response->slaveId;
            txFrame[frameLen++] = response->functionCode;
            txFrame[frameLen++] = response->data.readHolding.byteCount;
            uint8_t numRegs = response->data.readHolding.byteCount / 2U;
            for(uint8_t i = 0; i < numRegs; i++)
            {
                txFrame[frameLen++] = (response->data.readHolding.registers[i] >> 8) & 0xFF;
                txFrame[frameLen++] = response->data.readHolding.registers[i] & 0xFF;
            }
        }
        else if(response->functionCode == MODBUS_FUNC_WRITE_MULTIPLE)
        {
            txFrame[frameLen++] = response->slaveId;
            txFrame[frameLen++] = response->functionCode;
            txFrame[frameLen++] = (response->data.writeMultiple.startAddress >> 8) & 0xFF;
            txFrame[frameLen++] = response->data.writeMultiple.startAddress & 0xFF;
            txFrame[frameLen++] = (response->data.writeMultiple.quantity >> 8) & 0xFF;
            txFrame[frameLen++] = response->data.writeMultiple.quantity & 0xFF;
        }
    }
    uint16_t crc = Modbus_CalcCRC(txFrame, frameLen);
    txFrame[frameLen++] = crc & 0xFF;
    txFrame[frameLen++] = (crc >> 8) & 0xFF;
    Modbus_SendFrame(channel, txFrame, frameLen);
}


/*
 @brief Receives the request and process and update the Modbus registers.
  * @param input  => Request modbus frame.
  *        output => Response frame sent to through Modbus 
  * Upon receiving the request frame,the data is updated to the registers or read from the registers
  * If the process function is not set or returns an error,
  * an error response with an illegal access exception (error code 0x02) is sent.
 */


/**
  * @brief Processes a received Modbus frame on the specified channel.
  * @param channel Pointer to the internal Modbus channel state.
  *
  * Upon receiving a valid frame, this function parses the frame and invokes
  * the registered process function. If the process function is not set or returns an error,
  * an error response with an illegal access exception (error code 0x02) is sent.
  */
static void Modbus_ProcessFrame(ModbusChannel_t *channel)
{
    ModbusRequest_t request;
    ModbusResponse_t response;

    if(channel->rxIndex >= MODBUS_MIN_FRAME_LENGTH_FC03)
    {
        uint16_t receivedCrc = channel->rxBuffer[channel->rxIndex - MODBUS_CRC_LENGTH] |
                               (channel->rxBuffer[channel->rxIndex - MODBUS_CRC_LENGTH + 1] << 8);
        uint16_t calcCrc = Modbus_CalcCRC(channel->rxBuffer, channel->rxIndex - MODBUS_CRC_LENGTH);

        if(receivedCrc == calcCrc)
        {
            uint8_t slave = channel->rxBuffer[0];
            if((slave == MODBUS_SLAVE_ID) || (slave == 0))
            {
                uint8_t func = channel->rxBuffer[1];
                if(func == MODBUS_FUNC_READ_HOLDING)
                {
                    if(channel->rxIndex != MODBUS_MIN_FRAME_LENGTH_FC03)
                    {
                        response.slaveId = slave;
                        response.functionCode = func;
                        response.errorCode = 0x03;
                        Modbus_SendResponse(channel, &response);
                        channel->rxIndex = 0;
                        channel->frameCompleteFlag = 0;
                        return;
                    }
                    request.slaveId = slave;
                    request.functionCode = MODBUS_FUNC_READ_HOLDING;
                    request.data.readHolding.startAddress = (channel->rxBuffer[2] << 8) | channel->rxBuffer[3];
                    request.data.readHolding.quantity     = (channel->rxBuffer[4] << 8) | channel->rxBuffer[5];
                    if((request.data.readHolding.quantity == 0) ||
                       (request.data.readHolding.quantity > MODBUS_MAX_QUANTITY))
                    {
                        response.slaveId = slave;
                        response.functionCode = func;
                        response.errorCode = 0x03;
                        Modbus_SendResponse(channel, &response);
                        channel->rxIndex = 0;
                        channel->frameCompleteFlag = 0;
                        return;
                    }
                }
                else if(func == MODBUS_FUNC_WRITE_MULTIPLE)
                {
                    if(channel->rxIndex < MODBUS_MIN_FRAME_LENGTH_FC10)
                    {
                        response.slaveId = slave;
                        response.functionCode = func;
                        response.errorCode = 0x03;
                        Modbus_SendResponse(channel, &response);
                        channel->rxIndex = 0;
                        channel->frameCompleteFlag = 0;
                        return;
                    }
                    uint16_t quantity = (channel->rxBuffer[4] << 8) | channel->rxBuffer[5];
                    uint8_t byteCount = channel->rxBuffer[6];
                    if(byteCount != (quantity * 2U))
                    {
                        response.slaveId = slave;
                        response.functionCode = func;
                        response.errorCode = 0x03;
                        Modbus_SendResponse(channel, &response);
                        channel->rxIndex = 0;
                        channel->frameCompleteFlag = 0;
                        return;
                    }
                    uint16_t expectedLength = MODBUS_WRITE_MULTIPLE_HEADER_LENGTH + byteCount + MODBUS_CRC_LENGTH;
                    if(channel->rxIndex != expectedLength)
                    {
                        response.slaveId = slave;
                        response.functionCode = func;
                        response.errorCode = 0x03;
                        Modbus_SendResponse(channel, &response);
                        channel->rxIndex = 0;
                        channel->frameCompleteFlag = 0;
                        return;
                    }
                    request.slaveId = slave;
                    request.functionCode = MODBUS_FUNC_WRITE_MULTIPLE;
                    request.data.writeMultiple.startAddress = (channel->rxBuffer[2] << 8) | channel->rxBuffer[3];
                    request.data.writeMultiple.quantity = quantity;
                    if((quantity == 0) || (quantity > MODBUS_MAX_QUANTITY))
                    {
                        response.slaveId = slave;
                        response.functionCode = func;
                        response.errorCode = 0x03;
                        Modbus_SendResponse(channel, &response);
                        channel->rxIndex = 0;
                        channel->frameCompleteFlag = 0;
                        return;
                    }
                    for(uint16_t i = 0; i < quantity; i++)
                    {
                        uint16_t dataIndex = MODBUS_WRITE_MULTIPLE_HEADER_LENGTH + (i * 2U);
                        request.data.writeMultiple.registers[i] = (channel->rxBuffer[dataIndex] << 8) |
                                                                  channel->rxBuffer[dataIndex + 1];
                    }
                }
                else
                {
                    response.slaveId = slave;
                    response.functionCode = func;
                    response.errorCode = 0x01;
                    Modbus_SendResponse(channel, &response);
                    channel->rxIndex = 0;
                    channel->frameCompleteFlag = 0;
                    return;
                }
                /* Process the request using the registered function pointer.
                   If xProcessFunc is not set or returns nonzero, send an error response with illegal access exception (error code 0x02). */
                if(channel->xProcessFunc != NULL)
                {
                    if(channel->xProcessFunc(&request, &response) != 0)
                    {
                        response.slaveId = request.slaveId;
                        response.functionCode = request.functionCode;
                        response.errorCode = 0x02; /* Illegal access exception */
                        Modbus_SendResponse(channel, &response);
                    }
                    else
                    {
                        Modbus_SendResponse(channel, &response);
                    }
                }
                else
                {
                    response.slaveId = request.slaveId;
                    response.functionCode = request.functionCode;
                    response.errorCode = 0x02; /* Illegal access exception */
                    Modbus_SendResponse(channel, &response);
                }
            }
        }
        else
        {
            response.slaveId = channel->rxBuffer[0];
            response.functionCode = channel->rxBuffer[1];
            response.errorCode = 0x03;
            Modbus_SendResponse(channel, &response);
        }
    }
    channel->rxIndex = 0;
    channel->frameCompleteFlag = 0;
}

/**
  * @brief FreeRTOS task for processing Modbus frames.
  * @param pvParameters Pointer to the internal Modbus channel state.
  */
void Modbus_Task(void *pvParameters)
{
    ModbusChannel_t *channel = (ModbusChannel_t *)pvParameters;
    for(;;)
    {
        if(channel->frameCompleteFlag == 1)
        {
            if(channel->xInterCharTimer != NULL)
            {
                xTimerStop(channel->xInterCharTimer, portMAX_DELAY);
            }
            Modbus_ProcessFrame(channel);
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

/**
  * @brief Initializes the specified Modbus channel.
  * @param channelId The channel identifier (MODBUS_CHANNEL_USB, etc.).
  * @return int16_t 0 on success, -1 on error.
  *
  * Based on the channel identifier, this function automatically assigns the appropriate
  * UART handle (for USB, the handle is set to NULL). It creates the inter-character timer,
  * starts UART reception for UART channels, and creates a FreeRTOS task to process frames.
  * If the channel is already initialized, an error is returned.
  */
int16_t Modbus_Init(ModbusChannelId_t channelId)
{
    BaseType_t taskStatus;
    if(channelId >= MODBUS_CHANNEL_COUNT)
        return -1;

    ModbusChannel_t *channel = &modbusChannels[channelId];
    
    /* Check if already initialized */
    if(channel->isInitialized == 1)
        return -1;
    
    channel->rxIndex = 0;
    channel->frameCompleteFlag = 0;
    channel->xProcessFunc = NULL;
    channel->isInitialized = 0;      /* Not yet set */
    channel->taskHandle = NULL;
    
    channel->xInterCharTimer = xTimerCreate("Modbus_Timer",
                                            MODBUS_INTERCHAR_TIMEOUT,
                                            pdFALSE,
                                            (void *)channel,
                                            Modbus_InterCharTimerCallback);
    if(channel->xInterCharTimer == NULL)
    {
        return -1;
    }
    
    if(channelId == MODBUS_CHANNEL_USB)
	{
		//MX_USB_GPIO_Init();
		//MX_USB_DEVICE_Init();
	    channel->type = 0; 
        channel->uartHandle = NULL;
    }
    else if(channelId == MODBUS_CHANNEL_USART1)
    {
        channel->type = 1;
		MX_USART1_Init();
        channel->uartHandle = &huart_usart1;
        Modbus_UART_Receive_IT(channelId);
    }
    else if(channelId == MODBUS_CHANNEL_UART4)
    {
        channel->type = 1; 
		MX_UART4_Init();
        channel->uartHandle = &huart_uart4;
        Modbus_UART_Receive_IT(channelId);
    }
    else if(channelId == MODBUS_CHANNEL_UART7)
    {
        channel->type = 1; 
	    MX_UART7_Init();
        channel->uartHandle = &huart_uart7;
        Modbus_UART_Receive_IT(channelId);
    }
    {
        char taskName[16];
        snprintf(taskName, sizeof(taskName), "Modbus_Task_%d", channelId);
        taskStatus = xTaskCreate(Modbus_Task, taskName, 512, (void *)channel, tskIDLE_PRIORITY + 5, &channel->taskHandle);
        if(taskStatus != pdPASS)
        {
            return -1;
        }
    }
    channel->isInitialized = 1;
    return 0;
}


/**
  * @brief Deinitializes the specified Modbus channel.
  * @param channelId The channel identifier.
  * @return int16_t 0 on success, -1 on error.
  *
  * This function deletes the inter-character timer and the FreeRTOS task associated
  * with the channel, resets the internal state, and sets isInitialized to 0.
  */
int16_t Modbus_Deinit(ModbusChannelId_t channelId)
{
    if(channelId >= MODBUS_CHANNEL_COUNT)
        return -1;
    
    ModbusChannel_t *channel = &modbusChannels[channelId];
    
    if(channel->isInitialized != 1)
        return -1;
    
    /* Delete the timer if it exists */
    if(channel->xInterCharTimer != NULL)
    {
        xTimerDelete(channel->xInterCharTimer, 0);
        channel->xInterCharTimer = NULL;
    }
    
    /* Delete the task if it exists */
    if(channel->taskHandle != NULL)
    {
        vTaskDelete(channel->taskHandle);
        channel->taskHandle = NULL;
    }
    
    /* Reset the internal state */
    channel->rxIndex = 0;
    channel->frameCompleteFlag = 0;
    channel->xProcessFunc = NULL;
    channel->isInitialized = 0;
    
    return 0;
}

/**
  * @brief Sets the process function for the specified channel.
  * @param channelId The channel identifier.
  * @param func Pointer to the process function.
  * @return int16_t 0 on success, -1 on error.
  */
int16_t Modbus_SetProcessFunction(ModbusChannelId_t channelId, ModbusFunctionPtr func)
{
    if(channelId >= MODBUS_CHANNEL_COUNT || func == NULL)
        return -1;
    modbusChannels[channelId].xProcessFunc = func;
    return 0;
}

/**
  * @brief Unsets the process function for the specified channel.
  * @param channelId The channel identifier.
  * @return int16_t 0 on success, -1 on error.
  */
int16_t Modbus_UnsetProcessFunction(ModbusChannelId_t channelId)
{
    if(channelId >= MODBUS_CHANNEL_COUNT)
        return -1;
    modbusChannels[channelId].xProcessFunc = NULL;
    return 0;
}



/**
  * @brief USB CDC reception callback.
  * 
  * This function should be called from the USB CDC receive callback.
  * @param data Pointer to the received data.
  * @param length Length of the received data.
  */
void Modbus_USB_RxCpltCallback(uint8_t *data, uint16_t length)
{
    /* For USB, always use channel 0 */
    ModbusChannel_t *channel = &modbusChannels[MODBUS_CHANNEL_USB];
    for(uint16_t i = 0; i < length; i++)
    {
        if(channel->rxIndex < MODBUS_MAX_FRAME_LENGTH)
        {
            channel->rxBuffer[channel->rxIndex++] = data[i];
        }
        else
        {
            channel->rxIndex = 0; // Buffer overflow, reset
        }
    }
    if(channel->xInterCharTimer != NULL)
    {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xTimerResetFromISR(channel->xInterCharTimer, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

/**
  * @brief UART reception callback.
  * 
  * This function should be called from HAL_UART_RxCpltCallback for UART channels.
  * @param channelId The UART channel identifier.
  * @param byte The received byte.
  */
void Modbus_UART_RxCpltCallback(ModbusChannelId_t channelId, uint8_t byte)
{
    if(channelId >= MODBUS_CHANNEL_COUNT)
        return;
    ModbusChannel_t *channel = &modbusChannels[channelId];
    if(channel->rxIndex < MODBUS_MAX_FRAME_LENGTH)
    {
        channel->rxBuffer[channel->rxIndex++] = byte;
    }
    else
    {
        channel->rxIndex = 0; // Buffer overflow, reset
    }
    if(channel->xInterCharTimer != NULL)
    {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xTimerResetFromISR(channel->xInterCharTimer, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
    Modbus_UART_Receive_IT(channelId);
}

/**
  * @brief Initiates UART reception in interrupt mode for the specified channel.
  * @param channelId The UART channel identifier.
  */
void Modbus_UART_Receive_IT(ModbusChannelId_t channelId)
{
    if(channelId >= MODBUS_CHANNEL_COUNT)
        return;
    ModbusChannel_t *channel = &modbusChannels[channelId];
    if(channel->uartHandle != NULL)
    {
        HAL_UART_Receive_IT(channel->uartHandle, &channel->rxByte, 1);
    }
}

/**
  * @brief Overridden HAL UART Rx complete callback.
  *
  * This function integrates the HAL callback with the Modbus module.
  *
  * @param huart Pointer to the UART handle.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	ModbusChannelId_t channelId;
	 if (huart->Instance == USART1) {
	        channelId = MODBUS_CHANNEL_USART1;
	    }
	    else if (huart->Instance == UART4) {
	        channelId = MODBUS_CHANNEL_UART4;
	    }
	    else if (huart->Instance == UART7) {
	        channelId = MODBUS_CHANNEL_UART7;
	    }
	    else {
	        return;                                             // Unknown UART
	    }

	    ModbusChannel_t *channel = &modbusChannels[channelId];
	    Modbus_UART_RxCpltCallback(channelId, channel->rxByte);
}

/**
  * @brief IRQ handler for USART1.
  */
void USART1_IRQHandler(void)
{

    if(modbusChannels[MODBUS_CHANNEL_USART1].uartHandle != NULL)
    {
        HAL_UART_IRQHandler(modbusChannels[MODBUS_CHANNEL_USART1].uartHandle);
    }
}

/**
  * @brief IRQ handler for UART4.
  */
void UART4_IRQHandler(void)
{
    if(modbusChannels[MODBUS_CHANNEL_UART4].uartHandle != NULL)
    {
        HAL_UART_IRQHandler(modbusChannels[MODBUS_CHANNEL_UART4].uartHandle);
    }
}

/**
  * @brief IRQ handler for UART7.
  */
void UART7_IRQHandler(void)
{
    if(modbusChannels[MODBUS_CHANNEL_UART7].uartHandle != NULL)
    {
        HAL_UART_IRQHandler(modbusChannels[MODBUS_CHANNEL_UART7].uartHandle);
    }
}
