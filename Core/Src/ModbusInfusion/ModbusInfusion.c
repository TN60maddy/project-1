/**
 * @file ModbusInfusion.c
 * @brief Modbus Infusion Interface Implementation (macro-clean, no magic numbers).
 *
 * This module exposes a Modbus holding-register interface to an infusion device.
 * It defines a register table, processes read/write requests, and bridges to
 * the underlying InfDevice API.
 *
 * @author Radhakrishnan Rajaram
 * @version 1.1
 * @date 2025-08-19
 * @copyright (c) 2025 Aria Innovations Pvt Ltd
 */

#include "ModbusInfusion.h"
#include "InfDevice.h"  /* InfDevice API declarations */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <ewrte.h>

/* ==============================
 * General constants & macros
 * ============================== */

/** @def MB_OK */
#define MB_OK                         (0)
/** @def MB_ERR_INVALID_POINTER */
#define MB_ERR_INVALID_POINTER        (-1)
/** @def MB_ERR_INVALID_ADDRESS */
#define MB_ERR_INVALID_ADDRESS        (-2)
/** @def MB_ERR_INVALID_LENGTH */
#define MB_ERR_INVALID_LENGTH         (-3)
/** @def MB_ERR_READ_ONLY */
#define MB_ERR_READ_ONLY              (-4)
/** @def MB_ERR_INVALID_TYPE */
#define MB_ERR_INVALID_TYPE           (-5)

/** @name Modbus exception codes */
/**@{*/
#define MB_EX_ILLEGAL_FUNCTION        (0x01u)
#define MB_EX_ILLEGAL_DATA_ADDRESS    (0x02u)
#define MB_EX_ILLEGAL_DATA_VALUE      (0x03u)
#define MB_EX_SLAVE_DEVICE_FAILURE    (0x04u)
/**@}*/

/** @name Register sizes (in 16-bit words) */
/**@{*/
#define MB_REGS_U16                   (1u)
#define MB_REGS_U32                   (2u)
/**@}*/

/** Bytes per Modbus 16-bit register */
#define MB_BYTES_PER_REG              (2u)

/**
 * @brief Word order for packing 32-bit values into two 16-bit registers.
 * @note If your wire format requires high-word first, swap the indices below.
 */
#define MB_REG_IDX_LOW_WORD           (0u)
#define MB_REG_IDX_HIGH_WORD          (1u)

/** Scaling factor used for x100 fixed-point values. */
#define MB_SCALE_X100                 (100u)

/** @name Control command signatures (MB_ADDR_CONTROL_CMD)
 *  \anchor control_cmd_signatures */
/**@{*/
#define MB_CMD_START_SIGNATURE        (0x55AAu)
#define MB_CMD_STOP_SIGNATURE         (0xAA55u)
/**@}*/

/** @name Alarm simulation values (MB_ADDR_ALARM_SIM) */
/**@{*/
#define MB_ALARM_USER                 (1u)
#define MB_ALARM_UPSTREAM             (2u)
#define MB_ALARM_DOWNSTREAM           (3u)
#define MB_ALARM_AIRBUBBLE            (4u)
/**@}*/

/** @name Modbus holding register addresses */
/**@{*/
#define MB_ADDR_FLOW_RATE             (100u)  /* UINT32: ml/h * 100 */
#define MB_ADDR_VTBI                  (102u)  /* UINT32: ml * 100 */
#define MB_ADDR_INFUSION_TIME         (104u)  /* UINT32: seconds */
#define MB_ADDR_CONTROL_CMD           (106u)  /* UINT16: start/stop signatures */
#define MB_ADDR_BOLUS_CMD             (108u)  /* UINT16: ml (interpretation per device) */
#define MB_ADDR_INFUSION_STATE        (110u)  /* UINT16: 0..11 */
#define MB_ADDR_ALARM_SIM             (200u)  /* UINT16: 1..4 */
#define MB_ADDR_VOLUME_INFUSED        (202u)  /* UINT32: ml * 100 */
#define MB_ADDR_REMAINING_TIME        (204u)  /* UINT32: seconds */
/**@}*/

/** @name Variable indices (avoid magic array indices) */
/**@{*/
#define VAR_IDX_FLOW_RATE             (0u)
#define VAR_IDX_VTBI                  (1u)
#define VAR_IDX_INFUSION_TIME         (2u)
#define VAR_IDX_CONTROL_CMD           (3u)
#define VAR_IDX_BOLUS_CMD             (4u)
#define VAR_IDX_INFUSION_STATE        (5u)
#define VAR_IDX_ALARM_SIM             (6u)
#define VAR_IDX_VOLUME_INFUSED        (7u)
#define VAR_IDX_REMAINING_TIME        (8u)
/**@}*/

/**
 * @brief Select the Modbus channel used by this interface (unified for init/deinit).
 */
#define MB_MODBUS_CHANNEL             (MODBUS_CHANNEL_USB)

/** Optional buffer size for character variables (not used in this table). */
#define MB_CHAR_BUFFER_SIZE           (41u)

/* ==============================
 * Types & helpers
 * ============================== */

/**
 * @union Pack32_t
 * @brief Utility union to pack/unpack 32-bit values into two 16-bit Modbus registers.
 */
typedef union {
    float    f;   /**< 32-bit IEEE-754 float view */
    uint32_t u32; /**< 32-bit unsigned integer view */
    uint16_t r[2];/**< Two 16-bit register view */
} Pack32_t;

/**
 * @union MB_Value_u
 * @brief Holds the current value for a Modbus variable according to its type.
 */
typedef union {
    char         str[MB_CHAR_BUFFER_SIZE]; /**< For MB_INF_TYPE_CHAR (unused here) */
    float        f;                        /**< For MB_INF_TYPE_FLOAT */
    uint32_t     u32;                      /**< For MB_INF_TYPE_UINT (32-bit) */
    uint16_t     u16;                      /**< For MB_INF_TYPE_UINT16 */
    ModbusTime_t time;                     /**< For MB_INF_TYPE_TIME */
} MB_Value_u;

/**
 * @struct MB_Variable_t
 * @brief Describes one Modbus holding-register mapped variable.
 */
typedef struct {
    uint16_t            modbusAddress;  /**< Starting Modbus address */
    const char         *name;           /**< Variable name */
    uint8_t             size;           /**< Size in 16-bit registers (words) */
    MB_INF_DataType_t   dataType;       /**< Data type */
    MB_INF_Access_t     access;         /**< Access mode (R/W) */
    MB_Value_u          value;          /**< Current value cache */
} MB_Variable_t;

/* ==============================
 * Register table
 * ============================== */
/**
 * @brief Register table mapping for the infusion device.
 * @note Flow Rate, VTBI, and Volume Infused are fixed-point x100 (UINT32).
 */
static MB_Variable_t modbusVars[MB_INF_TOTAL_VARIABLES] = {
    { MB_ADDR_FLOW_RATE,       "Flow Rate",        MB_REGS_U32, MB_INF_TYPE_UINT,   MB_INF_ACCESS_RW, .value.u32 = 0u },
    { MB_ADDR_VTBI,            "VTBI",             MB_REGS_U32, MB_INF_TYPE_UINT,   MB_INF_ACCESS_RW, .value.u32 = 0u },
    { MB_ADDR_INFUSION_TIME,   "Infusion Time",    MB_REGS_U32, MB_INF_TYPE_UINT,   MB_INF_ACCESS_RW, .value.u32 = 0u },
    { MB_ADDR_CONTROL_CMD,     "Control Command",  MB_REGS_U16, MB_INF_TYPE_UINT16, MB_INF_ACCESS_RW, .value.u16 = 0u },
    { MB_ADDR_BOLUS_CMD,       "Bolus Command",    MB_REGS_U16, MB_INF_TYPE_UINT16, MB_INF_ACCESS_RW, .value.u16 = 0u },
    { MB_ADDR_INFUSION_STATE,  "Infusion State",   MB_REGS_U16, MB_INF_TYPE_UINT16, MB_INF_ACCESS_R,  .value.u16 = 0u },
    { MB_ADDR_ALARM_SIM,       "Alarm Simulation", MB_REGS_U16, MB_INF_TYPE_UINT16, MB_INF_ACCESS_RW, .value.u16 = 0u },
    { MB_ADDR_VOLUME_INFUSED,  "Volume Infused",   MB_REGS_U32, MB_INF_TYPE_UINT,   MB_INF_ACCESS_R,  .value.u32 = 0u },
    { MB_ADDR_REMAINING_TIME,  "Remaining Time",   MB_REGS_U32, MB_INF_TYPE_UINT,   MB_INF_ACCESS_R,  .value.u32 = 0u }
};

/* ==============================
 * Local function prototypes
 * ============================== */
static int      findVariableByAddress(uint16_t address);
static int16_t  ModbusInfusion_Read(ModbusRequest_t* pRequest, ModbusResponse_t *pResponse);
static int16_t  ModbusInfusion_Write(ModbusRequest_t* pRequest, ModbusResponse_t *pResponse);
static int16_t  ModbusInfusion_Process(ModbusRequest_t *pRequest, ModbusResponse_t *pResponse);
static void     updateInfDeviceStatus(void);
static int      requiresLiveUpdate(uint16_t addr);

/* ==============================
 * Device status update
 * ============================== */
/**
 * @brief Refreshes cached live-read variables from the underlying device.
 *
 * This function calls ::InfDevice_GetStatus and updates the cached values for
 * Flow Rate (x100), VTBI (x100), Infusion Time (s), Volume Infused (x100), and
 * Remaining Time (s).
 *
 * @retval void
 * @note Thread-safety: Intended to be called in the Modbus processing context.
 */
static void updateInfDeviceStatus(void)
{
    InfusionStatus_t status;
    if (InfDevice_GetStatus(&status) == 0) {
        modbusVars[VAR_IDX_FLOW_RATE].value.u32      = status.FlowRatex100;
        modbusVars[VAR_IDX_VTBI].value.u32           = status.VTBIx100;
        modbusVars[VAR_IDX_INFUSION_TIME].value.u32  = status.InfusionTimeInSecs;
        modbusVars[VAR_IDX_VOLUME_INFUSED].value.u32 = status.VolumeInfusedx100;
        modbusVars[VAR_IDX_REMAINING_TIME].value.u32 = status.RemainingTimeInSecs;
    }
}

/**
 * @brief Determines if the given address should be live-updated before read.
 * @param addr Starting Modbus address.
 * @retval 1  If a live update is required.
 * @retval 0  Otherwise.
 */
static int requiresLiveUpdate(uint16_t addr)
{
    return (addr == MB_ADDR_FLOW_RATE)      ||
           (addr == MB_ADDR_VTBI)           ||
           (addr == MB_ADDR_INFUSION_TIME)  ||
           (addr == MB_ADDR_VOLUME_INFUSED) ||
           (addr == MB_ADDR_REMAINING_TIME);
}

/* ==============================
 * Lookup
 * ============================== */
/**
 * @brief Finds the variable table index for a starting Modbus address.
 * @param address Starting Modbus holding register address.
 * @return Index into ::modbusVars if found; -1 otherwise.
 */
static int findVariableByAddress(uint16_t address)
{
    for (int i = 0; i < MB_INF_TOTAL_VARIABLES; i++) {
        if (modbusVars[i].modbusAddress == address) {
            return i;
        }
    }
    return -1;
}

/* ==============================
 * Process
 * ============================== */
/**
 * @brief Top-level Modbus request dispatcher for the infusion map.
 *
 * Routes supported function codes to the appropriate handlers.
 *
 * @param pRequest  Pointer to the Modbus request.
 * @param pResponse Pointer to the Modbus response to fill.
 * @retval MB_OK on success.
 * @retval MB_ERR_INVALID_POINTER if any pointer is NULL.
 * @retval MB_ERR_INVALID_TYPE for unsupported function code.
 *
 * @note Supported function codes: ::MODBUS_FUNC_READ_HOLDING, ::MODBUS_FUNC_WRITE_MULTIPLE
 */
static int16_t ModbusInfusion_Process(ModbusRequest_t *pRequest, ModbusResponse_t *pResponse)
{
    if ((pRequest == NULL) || (pResponse == NULL)) {
        return MB_ERR_INVALID_POINTER;
    }

    if (pRequest->functionCode == MODBUS_FUNC_READ_HOLDING) {
        return ModbusInfusion_Read(pRequest, pResponse);
    } else if (pRequest->functionCode == MODBUS_FUNC_WRITE_MULTIPLE) {
        return ModbusInfusion_Write(pRequest, pResponse);
    } else {
        pResponse->slaveId      = pRequest->slaveId;
        pResponse->functionCode = pRequest->functionCode;
        pResponse->errorCode    = MB_EX_ILLEGAL_FUNCTION;
        return MB_ERR_INVALID_TYPE;
    }
}

/* ==============================
 * Read handler
 * ============================== */
/**
 * @brief Handles Modbus Read Holding Registers for the infusion map.
 *
 * Validates address/length, updates live values if required, and packs the
 * requested variable into the response.
 *
 * @param pRequest  Pointer to the Modbus request (Read Holding).
 * @param pResponse Pointer to the Modbus response to fill.
 * @retval MB_OK on success.
 * @retval MB_ERR_INVALID_POINTER if any pointer is NULL.
 * @retval MB_ERR_INVALID_ADDRESS if address is not mapped.
 * @retval MB_ERR_INVALID_LENGTH  if requested length mismatches variable size.
 * @retval MB_ERR_INVALID_TYPE    if the variable type is unsupported.
 */
static int16_t ModbusInfusion_Read(ModbusRequest_t* pRequest, ModbusResponse_t *pResponse)
{
    if ((pRequest == NULL) || (pResponse == NULL)) {
        return MB_ERR_INVALID_POINTER;
    }

    const uint16_t startAddress = pRequest->data.readHolding.startAddress;
    const uint16_t quantity     = pRequest->data.readHolding.quantity;

    const int varIndex = findVariableByAddress(startAddress);
    if (varIndex < 0) {
        pResponse->errorCode = MB_EX_ILLEGAL_DATA_ADDRESS;
        return MB_ERR_INVALID_ADDRESS;
    }

    if (quantity != modbusVars[varIndex].size) {
        pResponse->errorCode = MB_EX_ILLEGAL_DATA_VALUE;
        return MB_ERR_INVALID_LENGTH;
    }

    /* Live-update where applicable */
    if (requiresLiveUpdate(modbusVars[varIndex].modbusAddress)) {
        updateInfDeviceStatus();
    } else if (modbusVars[varIndex].modbusAddress == MB_ADDR_INFUSION_STATE) {
        modbusVars[varIndex].value.u16 = InfDevice_getState();
    }

    /* Build response */
    pResponse->slaveId                    = pRequest->slaveId;
    pResponse->functionCode               = pRequest->functionCode;
    pResponse->errorCode                  = 0u;
    pResponse->data.readHolding.byteCount = (uint8_t)(quantity * MB_BYTES_PER_REG);

    switch (modbusVars[varIndex].dataType) {
        case MB_INF_TYPE_FLOAT: {
            Pack32_t pack;
            pack.f = modbusVars[varIndex].value.f;
            pResponse->data.readHolding.registers[MB_REG_IDX_LOW_WORD]  = pack.r[MB_REG_IDX_LOW_WORD];
            pResponse->data.readHolding.registers[MB_REG_IDX_HIGH_WORD] = pack.r[MB_REG_IDX_HIGH_WORD];
            break;
        }
        case MB_INF_TYPE_UINT: {
            Pack32_t pack;
            pack.u32 = modbusVars[varIndex].value.u32;
            pResponse->data.readHolding.registers[MB_REG_IDX_LOW_WORD]  = pack.r[MB_REG_IDX_LOW_WORD];
            pResponse->data.readHolding.registers[MB_REG_IDX_HIGH_WORD] = pack.r[MB_REG_IDX_HIGH_WORD];
            break;
        }
        case MB_INF_TYPE_UINT16: {
            pResponse->data.readHolding.registers[MB_REG_IDX_LOW_WORD] = modbusVars[varIndex].value.u16;
            break;
        }
        default:
            pResponse->errorCode = MB_EX_SLAVE_DEVICE_FAILURE;
            return MB_ERR_INVALID_TYPE;
    }

    return MB_OK;
}

/* ==============================
 * Write handler
 * ============================== */
/**
 * @brief Handles Modbus Write Multiple Registers for the infusion map.
 *
 * Validates address/length and access mode, then decodes and forwards the write
 * to the underlying device where applicable (e.g., Flow Rate, VTBI, Time,
 * Control, Alarm). For generic RW UINT16 variables, the value is cached.
 *
 * @param pRequest  Pointer to the Modbus request (Write Multiple).
 * @param pResponse Pointer to the Modbus response to fill.
 * @retval MB_OK on success.
 * @retval MB_ERR_INVALID_POINTER if any pointer is NULL.
 * @retval MB_ERR_INVALID_ADDRESS if address is not mapped.
 * @retval MB_ERR_INVALID_LENGTH  if requested length mismatches variable size.
 * @retval MB_ERR_READ_ONLY       if attempting to write a read-only variable.
 * @retval MB_ERR_INVALID_TYPE    if value/type is invalid for the target register.
 */
static int16_t ModbusInfusion_Write(ModbusRequest_t* pRequest, ModbusResponse_t *pResponse)
{
    if ((pRequest == NULL) || (pResponse == NULL)) {
        return MB_ERR_INVALID_POINTER;
    }

    const uint16_t startAddress = pRequest->data.writeMultiple.startAddress;
    const uint16_t quantity     = pRequest->data.writeMultiple.quantity;

    const int varIndex = findVariableByAddress(startAddress);
    if (varIndex < 0) {
        pResponse->errorCode = MB_EX_ILLEGAL_DATA_ADDRESS;
        return MB_ERR_INVALID_ADDRESS;
    }

    if (quantity != modbusVars[varIndex].size) {
        pResponse->errorCode = MB_EX_ILLEGAL_DATA_VALUE;
        return MB_ERR_INVALID_LENGTH;
    }

    if (modbusVars[varIndex].access != MB_INF_ACCESS_RW) {
        pResponse->errorCode = MB_EX_ILLEGAL_FUNCTION; /* write not allowed */
        return MB_ERR_READ_ONLY;
    }

    switch (modbusVars[varIndex].modbusAddress) {
        case MB_ADDR_FLOW_RATE: {  /* UINT32 (x100) -> float ml/h */
            Pack32_t pack;
            pack.r[MB_REG_IDX_LOW_WORD]  = pRequest->data.writeMultiple.registers[MB_REG_IDX_LOW_WORD];
            pack.r[MB_REG_IDX_HIGH_WORD] = pRequest->data.writeMultiple.registers[MB_REG_IDX_HIGH_WORD];
            const float flow_mlh = ((float)pack.u32) / (float)MB_SCALE_X100;
            InfDevice_SetFlowRate(flow_mlh);
            break;
        }
        case MB_ADDR_VTBI: {       /* UINT32 (x100) -> float ml */
            Pack32_t pack;
            pack.r[MB_REG_IDX_LOW_WORD]  = pRequest->data.writeMultiple.registers[MB_REG_IDX_LOW_WORD];
            pack.r[MB_REG_IDX_HIGH_WORD] = pRequest->data.writeMultiple.registers[MB_REG_IDX_HIGH_WORD];
            const float vtbi_ml = ((float)pack.u32) / (float)MB_SCALE_X100;
            InfDevice_SetVTBI(vtbi_ml);
            break;
        }
        case MB_ADDR_INFUSION_TIME: { /* UINT32 seconds */
            Pack32_t pack;
            pack.r[MB_REG_IDX_LOW_WORD]  = pRequest->data.writeMultiple.registers[MB_REG_IDX_LOW_WORD];
            pack.r[MB_REG_IDX_HIGH_WORD] = pRequest->data.writeMultiple.registers[MB_REG_IDX_HIGH_WORD];
            const uint32_t secs = pack.u32;
            InfDevice_SetInfusionTime(secs);
            break;
        }
        case MB_ADDR_CONTROL_CMD: { /* UINT16 signature */
            const uint16_t command = pRequest->data.writeMultiple.registers[MB_REG_IDX_LOW_WORD];
            if (command == MB_CMD_START_SIGNATURE) {
                InfDevice_EvStart();
            } else if (command == MB_CMD_STOP_SIGNATURE) {
                InfDevice_EvStop();
            } else {
                pResponse->errorCode = MB_EX_ILLEGAL_DATA_VALUE;
                return MB_ERR_INVALID_TYPE;
            }
            break;
        }
        case MB_ADDR_ALARM_SIM: {  /* UINT16 */
            const uint16_t alarmVal = pRequest->data.writeMultiple.registers[MB_REG_IDX_LOW_WORD];
            if (alarmVal == MB_ALARM_USER) {
                InfDevice_EvPauseByUser();
            } else if (alarmVal == MB_ALARM_UPSTREAM) {
                InfDevice_EvPauseUpstream();
            } else if (alarmVal == MB_ALARM_DOWNSTREAM) {
                InfDevice_EvPauseDownstream();
            } else if (alarmVal == MB_ALARM_AIRBUBBLE) {
                InfDevice_EvPauseAirbubble();
            } else {
                pResponse->errorCode = MB_EX_ILLEGAL_DATA_VALUE;
                return MB_ERR_INVALID_TYPE;
            }
            break;
        }
        case MB_ADDR_BOLUS_CMD: {  /* Cache value; device may pull later */
            modbusVars[varIndex].value.u16 = pRequest->data.writeMultiple.registers[MB_REG_IDX_LOW_WORD];
            break;
        }
        default: {
            /* Generic pass-through for other RW UINT16 registers */
            if (modbusVars[varIndex].dataType == MB_INF_TYPE_UINT16) {
                modbusVars[varIndex].value.u16 = pRequest->data.writeMultiple.registers[MB_REG_IDX_LOW_WORD];
            } else {
                pResponse->errorCode = MB_EX_SLAVE_DEVICE_FAILURE;
                return MB_ERR_INVALID_TYPE;
            }
            break;
        }
    }

    /* Acknowledge write */
    pResponse->slaveId                         = pRequest->slaveId;
    pResponse->functionCode                    = pRequest->functionCode;
    pResponse->errorCode                       = 0u;
    pResponse->data.writeMultiple.startAddress = startAddress;
    pResponse->data.writeMultiple.quantity     = quantity;

    return MB_OK;
}

/* ==============================
 * Variable set/get (string API)
 * ============================== */
/**
 * @brief Sets a variable value from a string representation.
 *
 * Converts the input string to the variable's data type and stores it in the
 * cache (does not call device APIs).
 *
 * @param var   Variable identifier (index into the register table).
 * @param value Null-terminated C-string value.
 * @retval MB_OK on success.
 * @retval MB_ERR_INVALID_POINTER if @p value is NULL.
 * @retval MB_ERR_INVALID_ADDRESS if @p var is out of range.
 * @retval MB_ERR_INVALID_TYPE    if the variable's type is unsupported.
 */
int16_t ModbusInfusion_SetVariable(ModbusInfusion_Variable_t var, const char *value)
{
    if (value == NULL) { return MB_ERR_INVALID_POINTER; }
    if ((var < 0) || (var >= MB_INF_TOTAL_VARIABLES)) { return MB_ERR_INVALID_ADDRESS; }

    MB_Variable_t *pVar = &modbusVars[var];

    switch (pVar->dataType) {
        case MB_INF_TYPE_FLOAT:
            pVar->value.f = (float)atof(value);
            break;
        case MB_INF_TYPE_UINT:
            pVar->value.u32 = (uint32_t)strtoul(value, NULL, 10);
            break;
        case MB_INF_TYPE_UINT16:
            pVar->value.u16 = (uint16_t)atoi(value);
            break;
        default:
            return MB_ERR_INVALID_TYPE;
    }
    return MB_OK;
}

/**
 * @brief Gets a variable value as a string.
 *
 * Converts the cached value to a string and writes it into the provided buffer.
 *
 * @param var     Variable identifier (index into the register table).
 * @param buffer  Output buffer to receive the string (null-terminated on success).
 * @param bufSize Size, in bytes, of @p buffer.
 * @retval MB_OK on success.
 * @retval MB_ERR_INVALID_POINTER if @p buffer is NULL.
 * @retval MB_ERR_INVALID_ADDRESS if @p var is out of range.
 * @retval MB_ERR_INVALID_LENGTH  if the formatted value does not fit in @p buffer.
 * @retval MB_ERR_INVALID_TYPE    if the variable's type is unsupported.
 */
int16_t ModbusInfusion_GetVariable(ModbusInfusion_Variable_t var, char *buffer, size_t bufSize)
{
    if (buffer == NULL) { return MB_ERR_INVALID_POINTER; }
    if ((var < 0) || (var >= MB_INF_TOTAL_VARIABLES)) { return MB_ERR_INVALID_ADDRESS; }

    MB_Variable_t *pVar = &modbusVars[var];

    switch (pVar->dataType) {
        case MB_INF_TYPE_FLOAT:
            if (snprintf(buffer, bufSize, "%f", pVar->value.f) >= (int)bufSize) {
                return MB_ERR_INVALID_LENGTH;
            }
            break;
        case MB_INF_TYPE_UINT:
            if (snprintf(buffer, bufSize, "%" PRIu32, pVar->value.u32) >= (int)bufSize) {
                return MB_ERR_INVALID_LENGTH;
            }
            break;
        case MB_INF_TYPE_UINT16:
            if (snprintf(buffer, bufSize, "%u", (unsigned)pVar->value.u16) >= (int)bufSize) {
                return MB_ERR_INVALID_LENGTH;
            }
            break;
        default:
            return MB_ERR_INVALID_TYPE;
    }
    return MB_OK;
}

/* ==============================
 * Init / Deinit
 * ============================== */
/**
 * @brief Initializes the Modbus infusion interface.
 *
 * Clears cached values and registers the process function with the Modbus stack
 * on ::MB_MODBUS_CHANNEL.
 *
 * @retval MB_OK on success.
 * @retval MB_ERR_INVALID_TYPE if Modbus stack initialization or hook registration fails.
 */
int16_t ModbusInfusion_Init(void)
{
    for (int i = 0; i < MB_INF_TOTAL_VARIABLES; i++) {
        switch (modbusVars[i].dataType) {
            case MB_INF_TYPE_FLOAT:   modbusVars[i].value.f   = 0.0f; break;
            case MB_INF_TYPE_UINT:    modbusVars[i].value.u32 = 0u;   break;
            case MB_INF_TYPE_UINT16:  modbusVars[i].value.u16 = 0u;   break;
            default: break;
        }
    }

    if (Modbus_Init(MB_MODBUS_CHANNEL) != 0) {
        return MB_ERR_INVALID_TYPE; /* generic non-zero failure */
    }
    if (Modbus_SetProcessFunction(MB_MODBUS_CHANNEL, ModbusInfusion_Process) != 0) {
        return MB_ERR_INVALID_TYPE;
    }
    return MB_OK;
}

/**
 * @brief Deinitializes the Modbus infusion interface.
 *
 * Unregisters the process function and deinitializes the Modbus channel.
 *
 * @retval MB_OK on success.
 * @retval MB_ERR_INVALID_TYPE if any deinitialization step fails.
 */
int16_t ModbusInfusion_Deinit(void)
{
    const int16_t ret1 = Modbus_UnsetProcessFunction(MB_MODBUS_CHANNEL);
    const int16_t ret2 = Modbus_Deinit(MB_MODBUS_CHANNEL);
    if ((ret1 != 0) || (ret2 != 0)) {
        return MB_ERR_INVALID_TYPE;
    }
    return MB_OK;
}
