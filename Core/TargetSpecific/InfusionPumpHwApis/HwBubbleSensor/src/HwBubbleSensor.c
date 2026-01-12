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
*   This file implements a generic HW Interface of Air Bubble Sensor used in Infusion Pump
*
********************************************************************************/

#include "HwBubbleSensorConfig.h"
#include "HwBubbleSensor.h"
#include <stdio.h>
#include <string.h>


/**
 * @brief  Initializes the GPIO pins for Air Bubble Sensor and Self-Test.
 * @param void
 * @retval
 * HW_BUBBLE_SENSOR_OK if successful,
 * HW_BUBBLE_SENSOR_ERROR otherwise.
 */

int HwBubbleSensorInit(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIO clocks (adjust to match actual port)
    __HAL_RCC_GPIOC_CLK_ENABLE();  // Assuming GPIOA is used for the sensor pins

    // Configure GPIO for sensor signal pin
    GPIO_InitStruct.Pin 			= 	HW_BUBBLE_SENSOR_SIG_PIN;
    GPIO_InitStruct.Mode 		    = 	HW_BUBBLE_SENSOR_SIG_PIN_MODE;
    GPIO_InitStruct.Pull 			= 	HW_BUBBLE_SENSOR_SIG_PIN_PULLUP;
    GPIO_InitStruct.Speed 		    = 	HW_BUBBLE_SENSOR_SIG_PIN_SPEED;

    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);


    HAL_GPIO_Init(HW_BUBBLE_SENSOR_SIG_PORT, &GPIO_InitStruct);

    // Configure GPIO for Self-Test pin
    GPIO_InitStruct.Pin 			= 		HW_BUBBLE_SENSOR_SELFTEST_PIN;
    GPIO_InitStruct.Mode 		    = 		HW_BUBBLE_SENSOR_SELFTEST_PIN_MODE;         // Push-pull output mode
    GPIO_InitStruct.Pull 			= 		HW_BUBBLE_SENSOR_SELFTEST_PIN_PULLUP;       // No pull-up or pull-down
    GPIO_InitStruct.Speed 		    = 		HW_BUBBLE_SENSOR_SELFTEST_PIN_SPEED;

    HAL_GPIO_Init(HW_BUBBLE_SENSOR_SELFTEST_PORT, &GPIO_InitStruct);


    return HW_BUBBLE_SENSOR_OK;
}

/**
 * @brief  IRQ Handler for the Bubble Sensor Status GPIO.
 * @param  void
 * @retval void
 */


void EXTI15_10_IRQHandler(void)
{
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != RESET)
    {
    	HwBubbleSensorRead();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13); // Clear interrupt flag
    }
}

/**
 * @brief  Reads the status of the Air Bubble Sensor (Wet or Dry).
 * @retval 1  if Wet (High CMOS level),
 *         0  if Dry (Low CMOS level),
 *        -1  in case of failure.
 */
int HwBubbleSensorRead(void) {
    // Read the GPIO pin connected to the sensor
    if (HAL_GPIO_ReadPin(HW_BUBBLE_SENSOR_SIG_PORT, HW_BUBBLE_SENSOR_SIG_PIN) == GPIO_PIN_SET) {
        return 0;                // Wet
    }
    else if (HAL_GPIO_ReadPin(HW_BUBBLE_SENSOR_SIG_PORT, HW_BUBBLE_SENSOR_SIG_PIN) == GPIO_PIN_RESET) {
        return 1;               // Dry
    }
    return HW_BUBBLE_SENSOR_ERROR;  					// Error in reading the sensor
}

/**
 * @brief  Starts or stops the self-test of the Air Bubble Sensor.
 * @param  action: 1 to start self-test,
 *                 0 to stop self-test(Normal Operation)
 * @retval HW_BUBBLE_SENSOR_OK if successful,
 *         HW_BUBBLE_SENSOR_SELFTEST_ERROR    if error occurs.
 */
int HwBubbleSensor_Selftest(int action) {
    if (action == BUBBLE_SENSOR_SELFTEST_START) {

    	// Set self-test pin to start the self-test (assuming active-high to start)
        HAL_GPIO_WritePin(HW_BUBBLE_SENSOR_SELFTEST_PORT, HW_BUBBLE_SENSOR_SELFTEST_PIN, GPIO_PIN_SET);
        if (HAL_GPIO_ReadPin(HW_BUBBLE_SENSOR_SELFTEST_PORT, HW_BUBBLE_SENSOR_SELFTEST_PIN) != GPIO_PIN_SET) {
                    return HW_BUBBLE_SENSOR_SELFTEST_ERROR;  			// Error in setting self-test pin
                }


    } else if (action == BUBBLE_SENSOR_SELFTEST_STOP) {
        // Set self-test pin to stop the self-test (assuming active-low to stop)
    	 HAL_GPIO_WritePin(HW_BUBBLE_SENSOR_SELFTEST_PORT, HW_BUBBLE_SENSOR_SELFTEST_PIN, GPIO_PIN_RESET);
    	 if (HAL_GPIO_ReadPin(HW_BUBBLE_SENSOR_SELFTEST_PORT, HW_BUBBLE_SENSOR_SELFTEST_PIN) != GPIO_PIN_RESET) {
    	             return HW_BUBBLE_SENSOR_SELFTEST_ERROR;  			// Error in setting self-test pin
    	        }
    } else {
        return HW_BUBBLE_SENSOR_SELFTEST_ERROR;  				// Invalid action
    }

    return HW_BUBBLE_SENSOR_OK;  							   // Success
}

