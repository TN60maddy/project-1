/**
 * @file DeviceParam.h
 * @brief Interface for Device Parameter Module.
 *
 * This header defines the interface for accessing and modifying device parameters.
 * The module supports string parameters:
 *  - Device Serial Number
 *  - Device Name
 *  - Manufacturer
 *  - Manufacturing DateTime
 *  - Model Number
 *  - Firmware Version
 *
 * and numeric parameters:
 *  - Brightness (uint16_t)
 *  - LockInPeriodInSecs (uint16_t)
 *
 * For string parameters the buffer must be at least DEVICE_PARAM_SIZE characters long,
 * and for numeric parameters, the pointer should be of type uint16_t*.
 *
 * @author
 *   Radhakrishnan Rajaram
 * @company
 *   Aria Innovations Pvt Ltd
 * @version
 *   1.0
 * @copyright
 *   © 2025 Aria Innovations Pvt Ltd. All rights reserved.
 */

#ifndef DEVICE_PARAM_H
#define DEVICE_PARAM_H

#include <stdint.h>

#define DEVICE_PARAM_SIZE 40

/**
 * @brief Enum for accessing device parameters.
 *
 * Provides identifiers for each supported parameter.
 */
typedef enum {
    DEVICE_PARAM_SERIAL_NUMBER = 0,     /**< Device Serial Number (char[40]) */
    DEVICE_PARAM_NAME,                  /**< Device Name (char[40]) */
    DEVICE_PARAM_MANUFACTURER,          /**< Manufacturer (char[40]) */
    DEVICE_PARAM_MANUFACTURING_DATETIME,/**< Manufacturing DateTime (char[40]) */
    DEVICE_PARAM_MODEL_NUMBER,          /**< Model Number (char[40]) */
    DEVICE_PARAM_FIRMWARE_VERSION,      /**< Firmware Version (char[40]) */
    DEVICE_PARAM_BRIGHTNESS,            /**< Brightness (uint16_t) */
    DEVICE_PARAM_LOCKIN_PERIOD,         /**< LockInPeriodInSecs (uint16_t) */
    DEVICE_PARAM_MAX                    /**< Total number of parameters */
} DeviceParam_ID;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the device parameters with default values.
 *
 * Default parameters:
 * - Device Serial Number: "Aria IP - 20250401000"
 * - Device Name: "AriaFusion VP"
 * - Manufacturer: "Aria Innovations Pvt Limited"
 * - Manufacturing DateTime: "2025-Apr-10 12:00:00"
 * - Model Number: "AriaFusion VP 1.00"
 * - Firmware Version: "00.02.R2"
 * - Brightness: 100
 * - LockInPeriodInSecs: 60
 *
 * @return int16_t 0 on success.
 */
int16_t DeviceParam_Init(void);

/**
 * @brief Reads the specified device parameter.
 *
 * This function copies the current value of the parameter identified by @c param
 * into the provided buffer pointed to by @c value.
 * For string parameters, @c value must be a character array with at least DEVICE_PARAM_SIZE bytes.
 * For numeric parameters, @c value must point to a uint16_t.
 *
 * @param param Enum value indicating which parameter to read.
 * @param value Pointer to the buffer for returning the parameter value.
 * @return int16_t 0 on success, or -1 if the parameter is invalid or the pointer is NULL.
 */
int16_t DeviceParam_Read(DeviceParam_ID param, void *value);

/**
 * @brief Writes a new value to the specified device parameter.
 *
 * This function updates the device parameter identified by @c param with the new value provided.
 * For string parameters, the new value is copied from a buffer that must hold at least DEVICE_PARAM_SIZE bytes.
 * For numeric parameters, @c value must point to a uint16_t.
 *
 * @param param Enum value indicating which parameter to update.
 * @param value Pointer to the buffer containing the new parameter value.
 * @return int16_t 0 on success, or -1 if the parameter is invalid or the pointer is NULL.
 */
int16_t DeviceParam_Write(DeviceParam_ID param, const void *value);

#ifdef __cplusplus
}
#endif

#endif /* DEVICE_PARAM_H */
