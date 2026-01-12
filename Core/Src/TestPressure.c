/**
 * @file TestPressure.c
 * @brief Implementation of the upstream pressure sensor test module.
 *
 * Initializes the hardware pressure sensor and launches a FreeRTOS task
 * to read and print the upstream pressure value every second.
 *
 * @author Radhakrishnan Rajaram
 * @date 2025-04-23
 * @version 1.0
 * @company Aria Innovations
 * @copyright Copyright (c) 2025 Aria Innovations. All rights reserved.
 */

#include <TestPressure.h>
#include "HwPressureSensor.h"
#include "ewrte.h"        /**< Runtime engine print function */
#include "FreeRTOS.h"
#include "task.h"

/**
 * @brief FreeRTOS task that reads and prints the upstream pressure value.
 *
 * This task reads from sensor HW_PRESSURE_NUM_2 once per second and outputs
 * the pressure value or an error message via the runtime engine.
 *
 * @param pvParameters Unused.
 */
static void vTestPressureTask(void *pvParameters)
{
    (void)pvParameters;
    HwPressureSensorValues_s sValues;

    for (;;)
    {
    	vTaskDelay(pdMS_TO_TICKS(500));
    	EwPrint("\r\n##########################################################################\r\n");
        if (HwPressureSensorRead(HW_PRESSURE_NUM_2, &sValues) == 0)
        {
            EwPrint("Up Stream Pressure Value = %f\r\n", sValues.PressureValue);
        }
        else
        {
        	EwPrint("Failed to read upstream pressure sensor\r\n");
        }
        vTaskDelay(pdMS_TO_TICKS(500));
		if (HwPressureSensorRead(HW_PRESSURE_NUM_1, &sValues) == 0)
		{
			EwPrint("Down Stream Pressure Value = %f\r\n", sValues.PressureValue);
		}
		else
		{
			EwPrint("Failed to Down upstream pressure sensor\r\n");
		}
		EwPrint("\r\n##########################################################################\r\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void TestPressure_Init(void)
{
    /* Initialize the pressure sensor HW_PRESSURE_NUM_2 */
  //  HwPressureSensorInit(HW_PRESSURE_NUM_2);
    /* Initialize the pressure sensor HW_PRESSURE_NUM_1 */
  //  HwPressureSensorInit(HW_PRESSURE_NUM_1);
    /* Create a FreeRTOS task for upstream pressure monitoring */
    xTaskCreate(vTestPressureTask,
                "TestUpPressure",
                configMINIMAL_STACK_SIZE*4,
                NULL,
                3,
                NULL);
}

