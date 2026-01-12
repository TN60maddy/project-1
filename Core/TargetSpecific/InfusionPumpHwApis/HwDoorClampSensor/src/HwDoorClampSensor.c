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
*   This file implements a generic HW Interface of Door Clamp Sensor used in Infusion Pump
*
********************************************************************************/

#include "HwDoorClampSensor.h"
#include "HwDoorClampSensorConfig.h"
#include "stm32h7xx_hal.h"



/*
 * @brief
 * This function configures the GPIO pins connected to the door clamp sensor as input pins.
 * @param void
 * @retvalue 0  = Success
 *           -1 = Failure
 * */

int HwDoorClampSensorInit( void )
{
	int retStatus = 0;
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Enable Clock for GPIO Pin */

	HW_DOOR_SENSOR_CLAMP_CLK_ENABLE();

	/*Configure the GPIO Pin used for Door Clamp Sensor   */
	GPIO_InitStruct.Pin = HW_DOORCLAMP_SENSOR_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(HW_DOORCLAMP_SENSOR_PORT, &GPIO_InitStruct);
	return retStatus;
}


/**
  * @brief
  *        Reads the current status of the door clamp sensor.
  *        This function reads the GPIO pins configured for the door clamp sensor and determines
  *        whether the door is open or closed.
  @param pStatus
  *        A pointer to a variable of type `HwDoorClampStatus_t` where the door clamp status will be stored.
  *        The possible values are:
  *        - HW_DOORCLAMP_OPEN: The door clamp is open.
  *        - HW_DOORCLAMP_CLOSED: The door clamp is closed.
  *
  *
  * @retval int
  *         0 = Success (Door clamp status read successfully and stored in `pStatus`).
  *         1 = Failure (Failed to read the door clamp status or invalid pointer provided).
  */

int HwDoorClampSensorReadStatus( HwDoorClampStatus_t *pStatus )
{
	/*Read the status of the Door Clamp */
	int retStatus = 0;
	if (pStatus == NULL)
	{
		return -1;                          // Error: Null pointer
	}
	// Read the Dorr Clamp direction
	uint8_t gpio_level;
	gpio_level = HAL_GPIO_ReadPin(HW_DOORCLAMP_SENSOR_PORT, HW_DOORCLAMP_SENSOR_PIN);
	if (gpio_level == 0)
	{
		*pStatus = HW_DOORCLAMP_OPEN;
	}
	else if (gpio_level == 1 )
	{
		*pStatus = HW_DOORCLAMP_CLOSED;
	}
 	 return retStatus;
}

