/**
 * @file ModbusInfusion.h
 * @brief Modbus Infusion Interface Header.
 *
 * This file contains definitions, data types, and function prototypes for the
 * Modbus Infusion Interface.
 *
 * Author: Radhakrishnan Rajaram
 * Company: Aria Innovations Pvt Ltd
 * Version: 1.0
 * Copyright: (c) 2025 Aria Innovations Pvt Ltd. All rights reserved.
 */

#ifndef MODBUSINFUSION_H
#define MODBUSINFUSION_H

#include <stdint.h>
#include "Modbus.h"  /* Assumes definitions from Modbus.h are available */

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
    MB_INF_TYPE_TIME,    /**< Time in format "HH:MM:SS" (stored in 4 bytes) */
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
 * @brief Enumeration for all infusion device variables.
 *
 * The new Modbus register table maps as follows:
 *
 *  - Flow Rate:        Register 100–101, 2 registers, Write, MB_INF_TYPE_FLOAT
 *  - VTBI:             Register 102–103, 2 registers, Write, MB_INF_TYPE_FLOAT
 *  - Infusion Time:    Register 104–105, 2 registers, Write, MB_INF_TYPE_UINT
 *  - Control Command:  Register 106,     1 register,  Write, MB_INF_TYPE_UINT16
 *  - Bolus Command:    Register 108,     1 register,  Write, MB_INF_TYPE_UINT16
 *  - Infusion State:   Register 110,     1 register,  Read,  MB_INF_TYPE_UINT16
 *  - Alarm Simulation: Register 200,     1 register,  Write, MB_INF_TYPE_UINT16
 *  - Volume Infused:   Register 202–203, 2 registers, Read,  MB_INF_TYPE_FLOAT
 *  - Remaining Time:   Register 204–205, 2 registers, Read,  MB_INF_TYPE_TIME
 */
typedef enum {
    MB_INF_FLOW_RATE = 0,        /**< Flow Rate */
    MB_INF_VTBI,                 /**< VTBI */
    MB_INF_INFUSION_TIME,        /**< Infusion Time */
    MB_INF_CONTROL_COMMAND,      /**< Control Command */
    MB_INF_BOLUS_COMMAND,        /**< Bolus Command */
    MB_INF_INFUSION_STATE,       /**< Infusion State */
    MB_INF_ALARM_SIMULATION,     /**< Alarm Simulation */
    MB_INF_VOLUME_INFUSED,       /**< Volume Infused */
    MB_INF_REMAINING_TIME,       /**< Remaining Time */
    MB_INF_TOTAL_VARIABLES
} ModbusInfusion_Variable_t;

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
 * @brief Initialize the Modbus Infusion interface.
 *
 * Initializes the variable table with default values, sets up the Modbus
 * channel, and registers the process function.
 *
 * @return int16_t 0 on success, negative value on error.
 */
int16_t ModbusInfusion_Init(void);

/**
 * @brief Deinitialize the Modbus Infusion interface.
 *
 * Unregisters the process function and deinitializes the Modbus channel.
 *
 * @return int16_t 0 on success, negative value on error.
 */
int16_t ModbusInfusion_Deinit(void);

/**
 * @brief Set the value of a Modbus variable.
 *
 * For numeric types, the provided string is converted to the appropriate type.
 * For MB_INF_TYPE_TIME, the expected format is "HH:MM:SS".
 *
 * @param var The Modbus variable identifier.
 * @param value The new value as a string.
 * @return int16_t 0 on success, negative value on error.
 */
int16_t ModbusInfusion_SetVariable(ModbusInfusion_Variable_t var, const char *value);

/**
 * @brief Get the value of a Modbus variable as a string.
 *
 * Converts the variable’s current value into a null-terminated string.
 *
 * @param var The Modbus variable identifier.
 * @param buffer The output buffer.
 * @param bufSize The size of the output buffer.
 * @return int16_t 0 on success, negative value on error.
 */
int16_t ModbusInfusion_GetVariable(ModbusInfusion_Variable_t var, char *buffer, size_t bufSize);

#ifdef __cplusplus
}
#endif

#endif /* MODBUSINFUSION_H */
