/*******************************************************************************
*
*    INFUSION PUMP PROJECT
*
*                                    Copyright (c) Aria Innovations
*
*
*
********************************************************************************
*
* DESCRIPTION:
*   This file implements a generic HW Interface of TCA9546 MUX used in Infusion Pump
*
********************************************************************************/

#include "HwFuelGauge.h"
#include "string.h"
#include "../inc/HwI2CMux.h"
#include "../inc/HwI2CMuxConfig.h"

I2C_HandleTypeDef HwI2CMux_Handler;

/* Function Declaration */
static int I2C_MUX_Init();

#define HWTCA9546_MUX_ADDR (0x70 << 1)

static int IsMuxInitialized = 0;


/**
  * @brief
  *        Initializes the Mux if not Initialized.
  * @param void
  * @retval int
  *         0 = Success (I2C MUX initialized successfully).
  *         -1 = Failure (Initialization failed due to an error).
  */

uint8_t HwI2CMux_Init()
{
	if(!IsMuxInitialized)
	{
		if(I2C_MUX_Init()!=0)
			return -1;
		else
		    IsMuxInitialized = 1;
    }
	return 0;
}


/**
  * @brief
  *        Initializes the I2C device connected to the multiplexer (MUX).
  *        This function configures the I2C peripheral and sets up the communication channel for the I2C multiplexer.
  * @param void
  * @retval int
  *         0 = Success (I2C MUX initialized successfully).
  *         -1 = Failure (Initialization failed due to an error).
  */



static int I2C_MUX_Init()
{
	int retStatus = 0;
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

	/* Initialize the Peripheral Clocks */
	PeriphClkInitStruct.PeriphClockSelection = HwI2CMux_PER_CLOCK;
	PeriphClkInitStruct.I2c123ClockSelection = HwI2CMux_PER_CLOCK_SRC;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
	retStatus = -1;
	}
	else{

	/* Enable GPIO Clock for I2C2 */

	HwI2CMux_SCL_CLK_ENABLE();
	//HwI2CMux_SDA_CLK_ENABLE();

	GPIO_InitStruct.Pin = HwI2CMux_SDA_PIN | HwI2CMux_SCL_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(HwI2CMux_SDA_PORT, &GPIO_InitStruct);

	/* Peripheral Clock Enable */
	HwI2CMux_CLK_ENABLE();

	/*
	* Initialize I2C for Pressure Sensor 1
	*/
	HwI2CMux_Handler.Instance = HwI2CMux_I2C;
	HwI2CMux_Handler.Init.Timing = HwI2CMux_TIMING_PARAMETER;
	HwI2CMux_Handler.Init.OwnAddress1 = 0;
	HwI2CMux_Handler.Init.AddressingMode = HwI2CMux_ADDRESS_MODE;
	HwI2CMux_Handler.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	HwI2CMux_Handler.Init.OwnAddress2 = 0;
	HwI2CMux_Handler.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	HwI2CMux_Handler.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	HwI2CMux_Handler.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&HwI2CMux_Handler) != HAL_OK)
	{
	retStatus = -1;
	}

	/** Configure Analogue filter
	*/
	if (HAL_I2CEx_ConfigAnalogFilter(&HwI2CMux_Handler, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
	retStatus = -1;
	}

	/** Configure Digital filter
	*/
	if (HAL_I2CEx_ConfigDigitalFilter(&HwI2CMux_Handler, 0) != HAL_OK)
	{
	retStatus = -1;
	}

	}
	return retStatus;
}

/**
  * @brief
  *        Selects the channel on the I2C multiplexer (MUX) for communication.
  *        This function configures the I2C MUX to route the I2C signals to the specified channel.
  *  @param Channel
  *        The channel number to select on the I2C MUX.
  *  @retval uint8_t
  *         0 = Success (Channel selected successfully).
  *         1 = Failure (Channel selection failed).
  */

uint8_t HwI2CMux_CHSEL(int Channel)
{
	uint8_t channel = 1 << Channel;
	if(HAL_I2C_Master_Transmit(&HwI2CMux_Handler,0x70 << 1,&channel,sizeof(channel),HAL_MAX_DELAY) != HAL_OK)
	{
		return -1;
	}
	return 0;
}

/**
  * @brief
  *        Wrapper function for receiving data from an I2C device connected through the TCA9546 multiplexer.
  *  @param Slaveaddr
  *        The I2C slave address of the target device from which data will be received.
  *         rdata
  *        A pointer to the buffer where the received data will be stored.
  *         length
  *        The number of bytes to receive from the I2C device.
  *
  * @retval uint8_t
  *         0 = Success (Data received successfully and stored in `rdata`).
  *         1 = Failure (Data reception failed due to an error, such as invalid parameters or I2C communication failure).
  */


uint8_t Hw_TCA9546_Mux_I2C_Receive(uint8_t Slaveaddr, uint8_t *rdata, uint16_t length)
{
	return HAL_I2C_Master_Receive(&HwI2CMux_Handler,Slaveaddr, rdata, length, 100);
}

/**
  * @brief
  *        Wrapper function for transmitting data to an I2C device connected through the TCA9546 multiplexer.
  *  @param Slaveaddr
  *        		The I2C slave address of the target device from which data will be received.
  *         tdata
  *         	A pointer to the buffer containing the data to be transmitted.
  *         length
  *          	The number of bytes to transmit to the I2C device.
  *   @retval uint8_t
  *         0 = Success (Data transmitted successfully).
  *         1 = Failure (Data transmission failed due to an error, such as invalid parameters or I2C communication failure).
  */

uint8_t Hw_TCA9546_Mux_I2C_Transmit(uint8_t Slaveaddr, uint8_t *tdata,uint16_t length)
{
		return HAL_I2C_Master_Transmit(&HwI2CMux_Handler,Slaveaddr, tdata,length, 100);
}
