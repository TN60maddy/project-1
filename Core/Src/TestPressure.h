/**
 * @file TestPressure.h
 * @brief Interface for the upstream pressure sensor test module.
 *
 * Initializes the hardware pressure sensor (HW_PRESSURE_NUM_2) and
 * creates a FreeRTOS task to periodically read and print the pressure value.
 *
 * @author Radhakrishnan Rajaram
 * @date 2025-04-23
 * @version 1.0
 * @company Aria Innovations
 * @copyright Copyright (c) 2025 Aria Innovations. All rights reserved.
 */

#ifndef TESTPRESSURE_H
#define TESTPRESSURE_H

#include "HwPressureSensor.h"  /**< Hardware pressure sensor interface */
#include "ewrte.h"             /**< Runtime engine print function */
#include "FreeRTOS.h"
#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the TestUpPressure module.
 *
 * Called at system startup to initialize the pressure sensor HW_PRESSURE_NUM_2
 * and start a FreeRTOS task that reads and prints the pressure value every second.
 */
void TestUpPressure_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* TESTPRESSURE_H */
