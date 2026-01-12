/*
 * @file    poweron.h
 * @brief   Power On/Off control module for STM32H753 with debounce and FreeRTOS support
 * @company Aria Innovations Pvt Ltd
 * @author  Radhakrishnan Rajaram
 * @version 1.2
 * @date    2025-06-27
 * @copyright © 2025 Aria Innovations Pvt Ltd. All rights reserved.
 */
#ifndef POWERON_H
#define POWERON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "stm32h7xx_hal.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

/**
 * @def    SYS_PWR_ON_OFF_PORT
 * @brief  GPIO port for the power on/off push button.
 */
#define SYS_PWR_ON_OFF_PORT    GPIOG
/**
 * @def    SYS_PWR_ON_OFF_PIN
 * @brief  GPIO pin for the power on/off push button (PG7).
 */
#define SYS_PWR_ON_OFF_PIN     GPIO_PIN_7
/**
 * @def    SYS_PWR_GPIO_PORT
 * @brief  GPIO port controlling the system power latch.
 */
#define SYS_PWR_GPIO_PORT      GPIOH
/**
 * @def    SYS_PWR_GPIO_PIN
 * @brief  GPIO pin driving the system power latch (PH4).
 */
#define SYS_PWR_GPIO_PIN       GPIO_PIN_4
/**
 * @def    BUTTON_DEBOUNCE_MS
 * @brief  Debounce time in milliseconds after interrupt before action.
 */
#define BUTTON_DEBOUNCE_MS     2000U  /* 2 seconds debounce */

/**
 * @brief Create and start the FreeRTOS task and semaphore for power button.
 * @note  Call after HAL initialization and before scheduler start.
 */
void PowerOn_Start(void);

/**
 * @brief  Initialize GPIOs for power on/off control and EXTI interrupt.
 * @note   Call this early in your system initialization.
 */
void PowerOn_Init(void);


void PowerOn_handleIntr( void );

#ifdef __cplusplus
}
#endif

#endif /* POWERON_H */
