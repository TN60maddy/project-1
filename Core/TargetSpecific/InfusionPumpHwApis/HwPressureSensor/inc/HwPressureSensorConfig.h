/*******************************************************************************
 * @file    HwPressureSensorConfig.h
 * @brief   Configuration file for Pressure Sensor in Infusion Pump
 * @author  Radhakrishnan Rajaram
 * @company Aria Innovations Private Limited
 * @version 1.0
 * @date    25/03/2025
 *
 * Copyright (c) 2025 Aria Innovations Private Limited.
 * All rights reserved.
 *
 * This file contains the configuration settings for the pressure sensors used
 * in the infusion pump system. It defines GPIO pins, clock settings, I2C
 * settings, and sensor-specific parameters.
 *
 *******************************************************************************/

#ifndef TARGETSPECIFIC_HWPRESSURESENSORCONFIG_H_
#define TARGETSPECIFIC_HWPRESSURESENSORCONFIG_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @brief Enable clock for Pressure Sensor 1 I2C Peripheral */
#define HW_PRESSURE1_CLK_ENABLE() __HAL_RCC_I2C1_CLK_ENABLE();
/** @brief Enable clock for Pressure Sensor GPIO */
#define HW_PRESSURE_SENSOR_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE();

/* Definition for Pressure Sensor 1 */
#define HW_PRESSURE1_I2C I2C2
#define HW_PRESSURE1_SDA_PORT GPIOB
#define HW_PRESSURE1_SDA_PIN GPIO_PIN_11
#define HW_PRESSURE1_SCL_PORT GPIOB
#define HW_PRESSURE1_SCL_PIN GPIO_PIN_10
#define HW_PRESSURE1_PER_CLOCK RCC_PERIPHCLK_I2C2
#define HW_PRESSURE1_PER_CLOCK_SRC RCC_I2C123CLKSOURCE_D2PCLK1
#define HW_PRESSURE1_GPIO_ALT_FUN GPIO_AF4_I2C2
#define HW_PRESSURE1_TIMING_PARAMETER 0x00707CBB
#define HW_PRESSURE1_ADDRESS_MODE I2C_ADDRESSINGMODE_7BIT

/** @brief Enable clock for Pressure Sensor 2 I2C Peripheral */
#define HW_PRESSURE2_CLK_ENABLE() __HAL_RCC_I2C4_CLK_ENABLE();

/* Definition for Pressure Sensor 2 */
#define HW_PRESSURE2_I2C I2C4
#define HW_PRESSURE2_SDA_PORT GPIOB
#define HW_PRESSURE2_SDA_PIN GPIO_PIN_9
#define HW_PRESSURE2_SCL_PORT GPIOB
#define HW_PRESSURE2_SCL_PIN GPIO_PIN_8
#define HW_PRESSURE2_PER_CLOCK RCC_PERIPHCLK_I2C4
#define HW_PRESSURE2_PER_CLOCK_SEL RCC_I2C4CLKSOURCE_D3PCLK1
#define HW_PRESSURE2_GPIO_ALT_FUN GPIO_AF6_I2C4
#define HW_PRESSURE2_TIMING_PARAMETER 0x00707CBB
#define HW_PRESSURE2_ADDRESS_MODE I2C_ADDRESSINGMODE_7BIT

/** @brief I2C Address of Pressure Sensor */
#define PRESSURE_SENSOR_ADDRESS (0x28 << 1)

/* Pressure Sensor Parameters (Honeywell MicroForce FMA digital output, I2C) */
/* FMAMSDXX015WC2C3 full-scale is 15 N (compression). */
#define HW_PRESSURE_RANGE 15 /**< Full-scale force in Newtons */
/*
 * Transfer function per Honeywell I2C comms note:
 * - 10% output = 1638 counts
 * - 90% output = 14745 counts
 * Span = 13107 counts
 */
#define HW_PRESSURE_DOUT_MIN_RANGE 3277.0f
#define HW_PRESSURE_DOUT_MAX_RANGE 13107.0f

/* Temperature Sensor Parameters */
#define HW_TEMPERATURE_SCALE 200       /**< Temperature scale factor */
#define HW_TEMPERATURE_OFFSET 50       /**< Temperature offset */
#define HW_TEMPERATURE_RESOLUTION 2047 /**< 12-bit ADC resolution */

/* I2C Multiplexer Addresses */
#define HW_PRESSURE1_MUX_ADDR (0x71 << 1)
#define HW_PRESSURE2_MUX_ADDR (0x72 << 1)

#endif /* TARGETSPECIFIC_HWPRESSURESENSORCONFIG_H_ */
