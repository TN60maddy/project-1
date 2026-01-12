/*******************************************************************************
 * @file    HwPressureSensor.h
 * @brief   Hardware Interface for Pressure Sensor in Infusion Pump
 * @author  Radhakrishnan Rajaram
 * @company Aria Innovations Private Limited
 * @version 1.0
 * @date    25/03/2025
 *
 * Copyright (c) 2025 Aria Innovations Private Limited.
 * All rights reserved.
 *
 * This file defines the hardware interface for the pressure sensor used
 * in the infusion pump system. It provides functions for initialization
 * and reading pressure values.
 *
 *******************************************************************************/

#ifndef TARGETSPECIFIC_HWPRESSURESENSOR_H_
#define TARGETSPECIFIC_HWPRESSURESENSOR_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

/** @enum HwPressureSensorNum_t
 *  @brief Enumeration for available pressure sensors.
 */
typedef enum
{
    HW_PRESSURE_NUM_1 = 0, /**< Pressure Sensor 1 */
    HW_PRESSURE_NUM_2,     /**< Pressure Sensor 2 */
    HW_PRESSURE_NUM_MAX    /**< Maximum number of sensors */
} HwPressureSensorNum_t;

/** @enum HwPressureSensorStatus_t
 *  @brief Enumeration for pressure sensor status.
 */
typedef enum {
    HW_PRESSURE_NORMAL_MODE,       /**< Normal operation mode */
    HW_PRESSURE_COMMAND_MODE,      /**< Command mode for sensor programming */
    HW_PRESSURE_STALE_MODE,        /**< Data polled faster than sensor update */
    HW_PRESSURE_DIAGNOSTIC_MODE    /**< Sensor fault (loss of connection, short circuit) */
} HwPressureSensorStatus_t;

/** @struct HwPressureSensorValues_s
 *  @brief Structure for storing pressure and temperature values.
 */
typedef struct
{
    float PressureValue;      /**< Pressure value in Newtons */
    float TemperatureValue;   /**< Temperature value in Celsius */
} HwPressureSensorValues_s;

/**
 * @brief  Initializes the pressure sensor hardware.
 * @param  hwPressure The pressure sensor number to initialize.
 * @retval int 0 if successful, negative error code otherwise.
 */
int HwPressureSensorInit(HwPressureSensorNum_t hwPressure);

/**
 * @brief  Reads values from the pressure sensor.
 * @param  hwPressure The pressure sensor number to read from.
 * @param  psValues Pointer to structure to store pressure and temperature values.
 * @retval int 0 if successful, negative error code otherwise.
 */
int HwPressureSensorRead(HwPressureSensorNum_t hwPressure, HwPressureSensorValues_s *psValues);

/**
 * @brief  Performs a basic sensor self-test (I2C comms + status bits + plausible output range).
 * @note   This does not apply a known force. It validates digital diagnostics and communication.
 * @param  hwPressure The pressure sensor number to test.
 * @retval int 0 if successful, negative error code otherwise.
 */
int HwPressureSensorSelfTest(HwPressureSensorNum_t hwPressure);

#endif /* TARGETSPECIFIC_HWPRESSURESENSOR_H_ */
