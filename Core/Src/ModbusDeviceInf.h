/**
 * @file ModbusDeviceInf.h
 * @brief Modbus Device Information Interface Header.
 *
 * This file contains definitions, data types, and function prototypes for the
 * Modbus Device Information Interface.
 *
 * Author: Radhakrishnan Rajaram
 * Company: Aria Innovations Pvt Ltd
 * Version: 1.0
 * Copyright: (c) 2025 Aria Innovations Pvt Ltd. All rights reserved.
 */

#ifndef MODBUSDEVICEINF_H
#define MODBUSDEVICEINF_H

#include <stdint.h>
#include "Modbus.h"  /* Use definitions from the attached Modbus.h */

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================
                           DATA TYPE DEFINITIONS
  ===========================================================================*/

/**
 * @brief Data types for Modbus variables.
 */
typedef enum {
    MB_INF_TYPE_CHAR,    /**< Character string */
    MB_INF_TYPE_FLOAT,   /**< Floating point number */
    MB_INF_TYPE_TIME,    /**< Time in format "HH:MM:SS" (reserved byte set to 0) */
    MB_INF_TYPE_UINT16,  /**< 16-bit unsigned integer */
    MB_INF_TYPE_UINT     /**< 32-bit unsigned integer (occupies 2 registers) */
} MB_INF_DataType_t;

/**
 * @brief Access types for Modbus variables.
 */
typedef enum {
    MB_INF_ACCESS_RW,    /**< Read/Write */
    MB_INF_ACCESS_R      /**< Read Only */
} MB_INF_Access_t;

/**
 * @brief Enumeration for all device variables.
 */
typedef enum {
    MB_INF_DEVICE_SERIAL_NUMBER = 0,
    MB_INF_DEVICE_NAME,
    MB_INF_MANUFACTURER,
    MB_INF_MANUFACTURING_DATETIME,
    MB_INF_MODEL_NUMBER,
    MB_INF_FIRMWARE_VERSION,
    MB_INF_FLOW_RATE,
    MB_INF_VTBI,
    MB_INF_INFUSION_TIME,
    MB_INF_VOLUME_INFUSED,
    MB_INF_REMAINING_TIME,
    MB_INF_BOLUS_RATE,
    MB_INF_KVO_RATE,
    MB_INF_MAX_FLOW_RATE,
    MB_INF_OCCLUSION_PRESSURE,
    MB_INF_AIR_LINE_SENSITIVITY,
    MB_INF_INFUSION_COMPLETION_ALARM,
    MB_INF_BRIGHTNESS,
    MB_INF_LOCKING_TIME,
    MB_INF_SELECTED_SSID,
    MB_INF_PASSWORD_FOR_SELECTED_SSID,
    MB_INF_ASSIGNED_IP,
    MB_INF_SUBNET_MASK,
    MB_INF_GATEWAY,
	MB_INF_SIGNATURE,
    MB_INF_TOTAL_VARIABLES
} ModbusDeviceInf_Variable_t;

/**
 * @brief Structure representing a time value.
 */
typedef struct {
    uint8_t hour;      /**< Hours */
    uint8_t minute;    /**< Minutes */
    uint8_t second;    /**< Seconds */
    uint8_t reserved;  /**< Reserved */
} ModbusTime_t;

/*===========================================================================
                           FUNCTION PROTOTYPES
  ===========================================================================*/

/**
 * @brief Initialize the Modbus Device Information interface.
 *
 * This function initializes the variable table with default values, initializes
 * the Modbus channel (MODBUS_CHANNEL_USB), and registers the process function.
 *
 * @return int16_t 0 on success, negative value on error.
 */
int16_t ModbusDeviceInf_Init(void);

/**
 * @brief Deinitialize the Modbus Device Information interface.
 *
 * This function unregisters the process function and deinitializes the Modbus channel.
 *
 * @return int16_t 0 on success, negative value on error.
 */
int16_t ModbusDeviceInf_Deinit(void);

/**
 * @brief Set the value of a Modbus variable.
 *
 * For MB_INF_TYPE_CHAR variables the provided string (excluding the null terminator)
 * must have a length exactly equal to (size * 2) bytes, where size is the number
 * of registers allocated for that variable. For numeric types, the string is
 * converted to the appropriate type. For MB_INF_TYPE_TIME, the expected format is "HH:MM:SS".
 *
 * @param var The Modbus variable identifier.
 * @param value The new value as a string.
 * @return int16_t 0 on success, negative value on error.
 */
int16_t ModbusDeviceInf_SetVariable(ModbusDeviceInf_Variable_t var, const char *value);

/**
 * @brief Get the value of a Modbus variable as a string.
 *
 * This function writes the variable's current value into the provided buffer as
 * a null-terminated string. For MB_INF_TYPE_CHAR the value is copied directly.
 * For MB_INF_TYPE_FLOAT, MB_INF_TYPE_UINT16, and MB_INF_TYPE_UINT the value is converted to
 * its string representation, and for MB_INF_TYPE_TIME the value is formatted as "HH:MM:SS".
 *
 * @param var The Modbus variable identifier.
 * @param buffer The output buffer.
 * @param bufSize The size of the output buffer.
 * @return int16_t 0 on success, negative value on error.
 */
int16_t ModbusDeviceInf_GetVariable(ModbusDeviceInf_Variable_t var, char *buffer, size_t bufSize);

#ifdef __cplusplus
}
#endif

#endif /* MODBUSDEVICEINF_H */
