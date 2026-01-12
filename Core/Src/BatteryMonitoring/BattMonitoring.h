/**
 * @file BattMonitoring.h
 * @brief Battery Monitoring Module interface.
 *
 * This header file declares the functions and definitions for the battery monitoring module.
 * The module uses a FreeRTOS task and timer to periodically retrieve battery information from
 * the hardware battery control module.
 *
 * @author
 *   Radhakrishnan Rajaram
 * @company
 *   Aria Innovation Pvt Limited
 * @version
 *   1.0.2
 * @date
 *   2025-03-27
 *
 * @copyright
 *   Copyright (c) 2025 Aria Innovation Pvt Limited. All rights reserved.
 */

#ifndef BATTMONITORING_H
#define BATTMONITORING_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the Battery Monitoring Module.
 *
 * This function initializes the battery control hardware, creates the battery information queue,
 * starts the battery monitoring task, and creates the RTOS timer to periodically send battery info.
 *
 * @return int 0 on success, -1 on error.
 */
int BattMonitoring_Init(void);

/**
 * @brief Deinitialize the Battery Monitoring Module.
 *
 * This function stops and deletes the RTOS timer, deletes the battery information queue,
 * and deletes the battery monitoring task.
 *
 * @return int 0 on success, -1 on error.
 */
int BattMonitoring_Deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* BATTMONITORING_H */
