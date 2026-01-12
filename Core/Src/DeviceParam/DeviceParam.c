/**
 * @file DeviceParam.c
 * @brief Implementation of the Device Parameter Module.
 *
 * This file provides the definitions for functions declared in DeviceParam.h to
 * initialize, read, and update device parameters.
 *
 * String parameters are maintained as fixed-length (DEVICE_PARAM_SIZE) character arrays,
 * while the numeric parameters (Brightness and LockInPeriodInSecs) are stored as uint16_t variables.
 *
 * Default values:
 *   - Device Serial Number: "Aria IP - 20250401000"
 *   - Device Name: "AriaFusion VP"
 *   - Manufacturer: "Aria Innovations Pvt Limited"
 *   - Manufacturing DateTime: "2025-Apr-10 12:00:00"
 *   - Model Number: "AriaFusion VP 1.00"
 *   - Firmware Version: "00.02.R2"
 *   - Brightness: 100
 *   - LockInPeriodInSecs: 60
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

#include "DeviceParam.h"
#include <string.h>

/* Internal storage for string parameters.
   Parameters 0 to 5 are stored as strings of fixed length (DEVICE_PARAM_SIZE).
*/
static char deviceParams[DEVICE_PARAM_FIRMWARE_VERSION + 1][DEVICE_PARAM_SIZE];

/* Internal storage for numeric parameters */
static uint16_t deviceBrightness = 0;
static uint16_t deviceLockInPeriod = 0;

int16_t DeviceParam_Init(void)
{
    /* Initialize string parameters with default values */
    strncpy(deviceParams[DEVICE_PARAM_SERIAL_NUMBER], "Aria IP - 20250401000", DEVICE_PARAM_SIZE - 1);
    deviceParams[DEVICE_PARAM_SERIAL_NUMBER][DEVICE_PARAM_SIZE - 1] = '\0';

    strncpy(deviceParams[DEVICE_PARAM_NAME], "AriaFusion VP", DEVICE_PARAM_SIZE - 1);
    deviceParams[DEVICE_PARAM_NAME][DEVICE_PARAM_SIZE - 1] = '\0';

    strncpy(deviceParams[DEVICE_PARAM_MANUFACTURER], "Aria Innovations Pvt Limited", DEVICE_PARAM_SIZE - 1);
    deviceParams[DEVICE_PARAM_MANUFACTURER][DEVICE_PARAM_SIZE - 1] = '\0';

    strncpy(deviceParams[DEVICE_PARAM_MANUFACTURING_DATETIME], "2025-Apr-10 12:00:00", DEVICE_PARAM_SIZE - 1);
    deviceParams[DEVICE_PARAM_MANUFACTURING_DATETIME][DEVICE_PARAM_SIZE - 1] = '\0';

    strncpy(deviceParams[DEVICE_PARAM_MODEL_NUMBER], "AriaFusion VP 1.00", DEVICE_PARAM_SIZE - 1);
    deviceParams[DEVICE_PARAM_MODEL_NUMBER][DEVICE_PARAM_SIZE - 1] = '\0';

    strncpy(deviceParams[DEVICE_PARAM_FIRMWARE_VERSION], "00.02.R2", DEVICE_PARAM_SIZE - 1);
    deviceParams[DEVICE_PARAM_FIRMWARE_VERSION][DEVICE_PARAM_SIZE - 1] = '\0';

    /* Initialize numeric parameters with default values */
    deviceBrightness = 100;       /* Default Brightness */
    deviceLockInPeriod = 60;      /* Default LockInPeriodInSecs */

    return 0;
}

int16_t DeviceParam_Read(DeviceParam_ID param, void *value)
{
    if (value == NULL || param < 0 || param >= DEVICE_PARAM_MAX) {
        return -1;
    }

    switch (param) {
        /* String parameters */
        case DEVICE_PARAM_SERIAL_NUMBER:
        case DEVICE_PARAM_NAME:
        case DEVICE_PARAM_MANUFACTURER:
        case DEVICE_PARAM_MANUFACTURING_DATETIME:
        case DEVICE_PARAM_MODEL_NUMBER:
        case DEVICE_PARAM_FIRMWARE_VERSION:
            /* Copy the string parameter value. */
            strncpy((char *)value, deviceParams[param], DEVICE_PARAM_SIZE);
            break;

        /* Numeric parameters */
        case DEVICE_PARAM_BRIGHTNESS:
            *((uint16_t *)value) = deviceBrightness;
            break;

        case DEVICE_PARAM_LOCKIN_PERIOD:
            *((uint16_t *)value) = deviceLockInPeriod;
            break;

        default:
            return -1;
    }
    return 0;
}

int16_t DeviceParam_Write(DeviceParam_ID param, const void *value)
{
    if (value == NULL || param < 0 || param >= DEVICE_PARAM_MAX) {
        return -1;
    }

    switch (param) {
        /* String parameters */
        case DEVICE_PARAM_SERIAL_NUMBER:
        case DEVICE_PARAM_NAME:
        case DEVICE_PARAM_MANUFACTURER:
        case DEVICE_PARAM_MANUFACTURING_DATETIME:
        case DEVICE_PARAM_MODEL_NUMBER:
        case DEVICE_PARAM_FIRMWARE_VERSION:
            strncpy(deviceParams[param], (const char *)value, DEVICE_PARAM_SIZE - 1);
            deviceParams[param][DEVICE_PARAM_SIZE - 1] = '\0';
            break;

        /* Numeric parameters */
        case DEVICE_PARAM_BRIGHTNESS:
            deviceBrightness = *((const uint16_t *)value);
            break;

        case DEVICE_PARAM_LOCKIN_PERIOD:
            deviceLockInPeriod = *((const uint16_t *)value);
            break;

        default:
            return -1;
    }
    return 0;
}
