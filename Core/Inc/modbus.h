/**
  ******************************************************************************
  * @file    modbus.h
  * @brief   Public header for the Modbus RTU slave multi-channel implementation.
  * @details This header declares the public types and functions used for the 
  *          multi-channel Modbus slave. Supported channels include:
  *             - USB CDC (MODBUS_CHANNEL_USB)
  *             - USART1  (MODBUS_CHANNEL_USART1)
  *             - UART4   (MODBUS_CHANNEL_UART4)
  *             - UART7   (MODBUS_CHANNEL_UART7)
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
  *  - v1.2: Added error return values, a function pointer typedef, removed internal
  *          channel structure (now internal to Modbus.c), added xProcessFunc, 
  *          Modbus_SetProcessFunction, Modbus_UnsetProcessFunction, and modified frame processing.
  *  - v1.3: Added isInitialized and taskHandle to internal state, added Modbus_Deinit,
  *          and updated Modbus_Init to return an error if already initialized.
  ******************************************************************************
  */

#ifndef MODBUS_H
#define MODBUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"
#include "FreeRTOS.h"
#include "timers.h"


/** @defgroup MODBUS_Defines Modbus Definitions
  * @{
  */

#define MODBUS_MAX_FRAME_LENGTH      256         /**< Maximum frame length */
#define MODBUS_CRC_LENGTH            2           /**< CRC length */
#define MODBUS_MIN_FRAME_LENGTH_FC03 8           /**< Minimum frame length for FC03 */
#define MODBUS_MIN_FRAME_LENGTH_FC10 9           /**< Minimum frame length for FC10 */
#define MODBUS_WRITE_MULTIPLE_HEADER_LENGTH 7    /**< Header length for FC10 */
#define MODBUS_INTERCHAR_TIMEOUT     pdMS_TO_TICKS(5) /**< Inter-character timeout (ticks) */
#define MODBUS_MAX_QUANTITY          125         /**< Maximum quantity of registers */
#define MODBUS_SLAVE_ID              1           /**< Slave ID */
#define MODBUS_FUNC_READ_HOLDING     0x03        /**< Function code: Read Holding Registers */
#define MODBUS_FUNC_WRITE_MULTIPLE   0x10        /**< Function code: Write Multiple Registers */
/** @} */

/**
 * @brief Function pointer type for processing a Modbus request.
 *
 * The function should fill in the output response. Return 0 on success;
 * nonzero indicates an error.
 */


/** @brief Enumeration for Modbus channel identifiers. */
typedef enum {
    MODBUS_CHANNEL_USB = 0,     /**< USB channel */
    MODBUS_CHANNEL_USART1,      /**< USART1 channel */
    MODBUS_CHANNEL_UART4,       /**< UART4 channel */
    MODBUS_CHANNEL_UART7        /**< UART7 channel */
} ModbusChannelId_t;

/** @brief Structure for Modbus request data. */
typedef struct ModbusRequest_t {
    uint8_t slaveId;
    uint8_t functionCode;
    union {
        struct {
            uint16_t startAddress;
            uint16_t quantity;
        } readHolding;
        struct {
            uint16_t startAddress;
            uint16_t quantity;
            uint16_t registers[MODBUS_MAX_QUANTITY];
        } writeMultiple;
    } data;
} ModbusRequest_t;

/** @brief Structure for Modbus response data. */
typedef struct ModbusResponse_t {
    uint8_t slaveId;
    uint8_t functionCode;
    uint8_t errorCode;
    union {
        struct {
            uint8_t byteCount;
            uint16_t registers[MODBUS_MAX_QUANTITY];
        } readHolding;
        struct {
            uint16_t startAddress;
            uint16_t quantity;
        } writeMultiple;
    } data;
} ModbusResponse_t;

typedef int16_t (*ModbusFunctionPtr)(struct ModbusRequest_t *input, struct ModbusResponse_t *output);

/* Public function prototypes */

/**
 * @brief Initializes the specified Modbus channel.
 * 
 * This function initializes a Modbus channel by setting up its buffers,
 * inter-character timer, and (for UART channels) starting interrupt-based reception.
 * Based on the channel identifier, the proper UART handle is automatically assigned.
 * If the channel is already initialized, an error is returned.
 *
 * @param channelId The channel identifier (MODBUS_CHANNEL_USB, etc.).
 * @return int16_t 0 on success, -1 on error (invalid channel, resource creation failure, or already initialized).
 */
int16_t Modbus_Init(ModbusChannelId_t channelId);

/**
 * @brief Deinitializes the specified Modbus channel.
 * 
 * This function deletes the timer and the task associated with the channel,
 * resets the internal state (including isInitialized and xProcessFunc).
 *
 * @param channelId The channel identifier.
 * @return int16_t 0 on success, -1 on error (invalid channel or channel not initialized).
 */
int16_t Modbus_Deinit(ModbusChannelId_t channelId);

/**
 * @brief Sets the process function for the specified channel.
 * 
 * This function registers a Modbus processing function which will be called when a valid frame is received.
 *
 * @param channelId The channel identifier.
 * @param func Pointer to the processing function.
 * @return int16_t 0 on success, -1 on error (invalid channel or func is NULL).
 */
int16_t Modbus_SetProcessFunction(ModbusChannelId_t channelId, ModbusFunctionPtr func);

/**
 * @brief Unsets the process function for the specified channel.
 * 
 * This function clears the registered Modbus processing function (sets it to NULL).
 *
 * @param channelId The channel identifier.
 * @return int16_t 0 on success, -1 on error (invalid channel).
 */
int16_t Modbus_UnsetProcessFunction(ModbusChannelId_t channelId);

/**
 * @brief USB CDC reception callback.
 * 
 * This function should be called from the USB CDC receive callback.
 * It processes received data on the USB channel.
 * 
 * @param data Pointer to the received data buffer.
 * @param length Length of the received data.
 */
void Modbus_USB_RxCpltCallback(uint8_t *data, uint16_t length);

/**
 * @brief UART reception callback.
 * 
 * This function should be called from HAL_UART_RxCpltCallback for UART channels.
 * 
 * @param channelId The UART channel identifier (MODBUS_CHANNEL_USART1, MODBUS_CHANNEL_UART4, or MODBUS_CHANNEL_UART7).
 * @param byte The received byte.
 */
void Modbus_UART_RxCpltCallback(ModbusChannelId_t channelId, uint8_t byte);

/**
 * @brief Initiates UART reception in interrupt mode for the specified channel.
 * 
 * @param channelId The UART channel identifier.
 */
void Modbus_UART_Receive_IT(ModbusChannelId_t channelId);

/**
 * @brief FreeRTOS task for processing Modbus frames.
 * 
 * This task continuously checks for complete frames and processes them.
 * 
 * @param pvParameters Pointer to the internal channel state.
 */
void Modbus_Task(void *pvParameters);

/**
 * @brief IRQ handler for USART1.
 */
void USART1_IRQHandler(void);

/**
 * @brief IRQ handler for UART4.
 */
void UART4_IRQHandler(void);

/**
 * @brief IRQ handler for UART7.
 */
void UART7_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif // MODBUS_H
