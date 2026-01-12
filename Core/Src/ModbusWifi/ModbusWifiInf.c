/**
 * @file    ModbusWifiInf.c
 * @brief   Modbus WiFi Infusion interface (macro-clean; no magic numbers).
 *
 * Exposes a Modbus holding-register map for device/system info, infusion
 * parameters, device numeric parameters, and Wi‑Fi network settings.
 *
 * Addressing & sizes are expressed via macros; CHAR fields are encoded as
 * two ASCII characters per 16‑bit register (big‑endian within the register:
 * high byte = first char, low byte = second char). If your stack expects the
 * opposite word order on the wire, flip @ref MBW_WORD_ORDER_HIGH_FIRST.
 *
 * Mapping highlights (register addresses):
 *   System:   0  (Serial#), 20 (Name RW), 40 (Mfr), 60 (Mfg DT),
 *             80 (Model), 100 (FW Ver)
 *   Infusion: 300 (State), 301 (Flow), 303 (VTBI), 305 (Vol Inf),
 *             307 (Time s), 309 (Remain s), 400 (Bolus), 402 (KVO),
 *             404 (MaxFlow), 406 (AirLineSens, U16), 408 (OcclPress),
 *             410 (CompletionAlarm RW)
 *   Device:   500 (Brightness), 501 (LockingTime s)
 *   Network:  40000 (Sel SSID RW), 40020 (Password RW), 40040 (Conn SSID RW),
 *             40060 (IP RW), 40070 (Mask RW), 40080 (Gateway RW),
 *             40090 (Conn Status RW)
 *
 * @author  Radhakrishnan Rajaram
 * @version 1.5
 * @date    2025-08-19
 * @copyright
 *   (c) 2025 Aria Innovations Pvt Ltd. All rights reserved.
 */

#include "ModbusWifiInf.h"
#include "InfDevice.h"
#include "DeviceParam.h"
#include "InfusionSet.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* ===============================
 * General constants & macros
 * =============================== */

/** Return codes */
#define MBW_OK                          (0)
#define MBW_ERR_PTR                     (-1)
#define MBW_ERR_ADDR                    (-2)
#define MBW_ERR_LEN                     (-3)
#define MBW_ERR_RO                      (-4)
#define MBW_ERR_TYPE                    (-5)

/** Modbus exception codes (to place in response.errorCode) */
#define MBW_EX_ILLEGAL_FUNCTION         (0x01u)
#define MBW_EX_ILLEGAL_DATA_ADDRESS     (0x02u)
#define MBW_EX_ILLEGAL_DATA_VALUE       (0x03u)
#define MBW_EX_SLAVE_DEVICE_FAILURE     (0x04u)

/** Per‑register byte size and ASCII packing policy */
#define MBW_BYTES_PER_REG               (2u)
#define MBW_CHARS_PER_REG               (2u)  /* pack 2 ASCII chars per 16‑bit register */

/** Word order of a 32‑bit quantity serialized to two 16‑bit registers */
#define MBW_WORD_ORDER_HIGH_FIRST       (1)   /* set 0 for low‑word first */

#if MBW_WORD_ORDER_HIGH_FIRST
  #define MBW_REG_WORD0(v32)            (uint16_t)(((uint32_t)(v32) >> 16) & 0xFFFFu)
  #define MBW_REG_WORD1(v32)            (uint16_t)((uint32_t)(v32) & 0xFFFFu)
#else
  #define MBW_REG_WORD0(v32)            (uint16_t)((uint32_t)(v32) & 0xFFFFu)
  #define MBW_REG_WORD1(v32)            (uint16_t)(((uint32_t)(v32) >> 16) & 0xFFFFu)
#endif

/** Utility: number of 16‑bit registers required for N ASCII chars */
#define MBW_REGS_FOR_CHARS(N)           (uint16_t)(((N) + (MBW_CHARS_PER_REG) - 1) / (MBW_CHARS_PER_REG))

/** Modbus channel used by this Wi‑Fi interface */
#define MBW_MODBUS_CHANNEL              (MODBUS_CHANNEL_UART4)

/* -------------------------------
 * Address map (symbolic)
 * ------------------------------- */
/* System (strings, 20 chars → 10 regs) */
#define MBW_ADDR_SYS_SERIAL             (0u)
#define MBW_ADDR_SYS_NAME               (20u)
#define MBW_ADDR_SYS_MANUFACTURER       (40u)
#define MBW_ADDR_SYS_MFG_DATETIME       (60u)
#define MBW_ADDR_SYS_MODEL              (80u)
#define MBW_ADDR_SYS_FW_VERSION         (100u)

/* Infusion */
#define MBW_ADDR_INF_STATE              (300u)   /* U16 */
#define MBW_ADDR_INF_FLOW               (301u)   /* float */
#define MBW_ADDR_INF_VTBI               (303u)   /* float */
#define MBW_ADDR_INF_VOL_INFUSED        (305u)   /* float */
#define MBW_ADDR_INF_TIME_S             (307u)   /* U32 seconds */
#define MBW_ADDR_INF_REMAIN_S           (309u)   /* U32 seconds */
#define MBW_ADDR_INF_BOLUS              (400u)   /* float */
#define MBW_ADDR_INF_KVO                (402u)   /* float */
#define MBW_ADDR_INF_MAX_FLOW           (404u)   /* float */
#define MBW_ADDR_INF_AIRLINE_SENS       (406u)   /* U16 */
#define MBW_ADDR_INF_OCCL_PRESS         (408u)   /* float */
#define MBW_ADDR_INF_COMPLETE_ALARM     (410u)   /* U16 RW */

/* Device numeric params */
#define MBW_ADDR_DEV_BRIGHTNESS         (500u)   /* U16 */
#define MBW_ADDR_DEV_LOCK_TIME_S        (501u)   /* U16 */

/* Network (strings) */
#define MBW_ADDR_NET_SEL_SSID           (40000u)
#define MBW_ADDR_NET_PWD_FOR_SEL        (40020u)
#define MBW_ADDR_NET_CONN_SSID          (40040u)
#define MBW_ADDR_NET_IP                 (40060u)
#define MBW_ADDR_NET_MASK               (40070u)
#define MBW_ADDR_NET_GW                 (40080u)
#define MBW_ADDR_NET_CONN_STATUS        (40090u) /* U16 */

/* -------------------------------
 * Field lengths (characters)
 * ------------------------------- */
#define MBW_LEN_CHAR20                  (20u)
#define MBW_LEN_CHAR10                  (10u)

/* Derived: #registers for the above lengths */
#define MBW_SIZE_REGS_CHAR20            MBW_REGS_FOR_CHARS(MBW_LEN_CHAR20) /* = 10 */
#define MBW_SIZE_REGS_CHAR10            MBW_REGS_FOR_CHARS(MBW_LEN_CHAR10) /* = 5 */

/* ===============================
 * Module state (Wi‑Fi/network)
 * =============================== */
static char     g_selectedSSID[MBW_LEN_CHAR20 + 1]            = "DefaultSSID";
static char     g_passwordForSelectedSSID[MBW_LEN_CHAR20 + 1] = "DefaultPassword";
static char     g_connectedSSID[MBW_LEN_CHAR20 + 1]           = "NotConnected";
static char     g_assignedIP[MBW_LEN_CHAR10 + 1]              = "192.168.1.2";
static char     g_subnetMask[MBW_LEN_CHAR20 + 1]              = "255.255.255.0";
static char     g_gateway[MBW_LEN_CHAR10 + 1]                 = "192.168.1.1";
static uint16_t g_connectionStatus                             = 0u; /* 0=disconnected, 1=connected */

/* Infusion completion alarm (RW) */
static uint16_t g_infusionCompletionAlarm                      = 1u;

/* ===============================
 * Register meta (for contiguous reads)
 * =============================== */
/**
 * @brief Row describing one register block.
 * @note size is in 16‑bit registers, not bytes, not characters.
 */
typedef struct {
    uint16_t    addr;       /**< starting Modbus address */
    const char *name;       /**< display name */
    uint8_t     size;       /**< number of 16‑bit registers */
    uint8_t     rw;         /**< 0=R, 1=RW */
} MBW_Row;

#define R   (0u)
#define RW  (1u)

static const MBW_Row kMap[] = {
    /* System */
    { MBW_ADDR_SYS_SERIAL,       "Device Serial Number",      MBW_SIZE_REGS_CHAR20, R },
    { MBW_ADDR_SYS_NAME,         "Device Name",               MBW_SIZE_REGS_CHAR20, RW },
    { MBW_ADDR_SYS_MANUFACTURER, "Manufacturer",              MBW_SIZE_REGS_CHAR20, R },
    { MBW_ADDR_SYS_MFG_DATETIME, "Manufacturing DateTime",    MBW_SIZE_REGS_CHAR20, R },
    { MBW_ADDR_SYS_MODEL,        "Model Number",              MBW_SIZE_REGS_CHAR20, R },
    { MBW_ADDR_SYS_FW_VERSION,   "Firmware Version",          MBW_SIZE_REGS_CHAR20, R },

    /* Infusion */
    { MBW_ADDR_INF_STATE,        "InfusionState",             1, R },
    { MBW_ADDR_INF_FLOW,         "Flow Rate",                 2, R },
    { MBW_ADDR_INF_VTBI,         "VTBI",                      2, R },
    { MBW_ADDR_INF_VOL_INFUSED,  "Volume Infused in ml",      2, R },
    { MBW_ADDR_INF_TIME_S,       "Infusion Time (s)",         2, R },
    { MBW_ADDR_INF_REMAIN_S,     "Remaining Time (s)",        2, R },
    { MBW_ADDR_INF_BOLUS,        "Bolus Rate",                2, R },
    { MBW_ADDR_INF_KVO,          "KVO Rate",                  2, R },
    { MBW_ADDR_INF_MAX_FLOW,     "Max Flow Rate",             2, R },
    { MBW_ADDR_INF_AIRLINE_SENS, "Air Line Sensitivity",      1, R },
    { MBW_ADDR_INF_OCCL_PRESS,   "Occlusion Pressure",        2, R },
    { MBW_ADDR_INF_COMPLETE_ALARM,"Infusion Completion Alarm", 1, RW },

    /* Device */
    { MBW_ADDR_DEV_BRIGHTNESS,   "Brightness",                1, R },
    { MBW_ADDR_DEV_LOCK_TIME_S,  "LockingTime in Secs",       1, R },

    /* Network */
    { MBW_ADDR_NET_SEL_SSID,     "Selected SSID",             MBW_SIZE_REGS_CHAR20, RW },
    { MBW_ADDR_NET_PWD_FOR_SEL,  "PasswordForSelectedSSID",   MBW_SIZE_REGS_CHAR20, RW },
    { MBW_ADDR_NET_CONN_SSID,    "Connected SSID",            MBW_SIZE_REGS_CHAR20, RW },
    { MBW_ADDR_NET_IP,           "Assigned IP Address IPV4",  MBW_SIZE_REGS_CHAR10, RW },
    { MBW_ADDR_NET_MASK,         "Subnet Mask",               MBW_SIZE_REGS_CHAR10, RW },
    { MBW_ADDR_NET_GW,           "Gateway",                   MBW_SIZE_REGS_CHAR10, RW },
    { MBW_ADDR_NET_CONN_STATUS,  "Connection Status",         1, RW }
};

#define MBW_MAP_SIZE  ((uint16_t)(sizeof(kMap)/sizeof(kMap[0])))

/* ===============================
 * Helpers: packing / strings
 * =============================== */
/**
 * @brief Packs an IEEE‑754 float into two Modbus registers using configured word order.
 * @param f      Input float.
 * @param regs2  Output array[2] of 16‑bit registers.
 */
static inline void MBW_FloatToRegs(float f, uint16_t regs2[2])
{
    union { float f; uint32_t u32; } conv; conv.f = f;
    regs2[0] = MBW_REG_WORD0(conv.u32);
    regs2[1] = MBW_REG_WORD1(conv.u32);
}

/**
 * @brief Packs a 32‑bit unsigned integer into two Modbus registers.
 */
static inline void MBW_U32ToRegs(uint32_t v, uint16_t regs2[2])
{
    regs2[0] = MBW_REG_WORD0(v);
    regs2[1] = MBW_REG_WORD1(v);
}

/**
 * @brief Encodes an ASCII buffer into N 16‑bit registers (2 chars per register).
 * @param s        Source C‑string.
 * @param maxChars Maximum characters to encode from @p s.
 * @param outRegs  Destination register buffer.
 * @param nRegs    Number of registers to fill (must equal MBW_REGS_FOR_CHARS(maxChars)).
 */
static void MBW_StringToRegs(const char *s, uint16_t maxChars, uint16_t *outRegs, uint16_t nRegs)
{
    const size_t len = s ? strlen(s) : 0u;
    for (uint16_t reg = 0; reg < nRegs; reg++) {
        const size_t idx1 = (size_t)reg * MBW_CHARS_PER_REG + 0u;
        const size_t idx2 = idx1 + 1u;
        const uint8_t c1 = (idx1 < len && idx1 < maxChars) ? (uint8_t)s[idx1] : (uint8_t)' ';
        const uint8_t c2 = (idx2 < len && idx2 < maxChars) ? (uint8_t)s[idx2] : (uint8_t)' ';
        outRegs[reg] = (uint16_t)(((uint16_t)c1 << 8) | (uint16_t)c2);
    }
}

/**
 * @brief Decodes N 16bit registers (2 chars per reg) into a bounded C‑string.
 * @param regs     Source register buffer.
 * @param nRegs    Number of registers.
 * @param out      Destination char buffer.
 * @param outCap   Destination capacity in chars (including NUL).
 */
static void MBW_RegsToString(const uint16_t *regs, uint16_t nRegs, char *out, uint16_t outCap)
{
    const uint16_t maxChars = (uint16_t)(nRegs * MBW_CHARS_PER_REG);
    const uint16_t copyChars = (uint16_t)((outCap - 1u) < maxChars ? (outCap - 1u) : maxChars);
    uint16_t w = 0u;
    for (uint16_t i = 0; i < nRegs && (w + 1u) < outCap; i++) {
        const uint16_t r = regs[i];
        if (w < copyChars) out[w++] = (char)((r >> 8) & 0xFFu);
        if (w < copyChars) out[w++] = (char)(r & 0xFFu);
    }
    out[w] = '\0';
}

/* ===============================
 * Forward declarations
 * =============================== */
static int16_t ModbusWifiInf_Process(ModbusRequest_t* pRequest, ModbusResponse_t* pResponse);
static int16_t ModbusWifiInf_Read   (ModbusRequest_t* pRequest, ModbusResponse_t* pResponse);
static int16_t ModbusWifiInf_Write  (ModbusRequest_t* pRequest, ModbusResponse_t* pResponse);
static int      MBW_FindRowByAddr   (uint16_t addr);
static uint8_t  MBW_IsContiguous    (uint16_t startIdx, uint16_t needRegs, uint16_t *endIdxOut);

/* ===============================
 * Public API
 * =============================== */
/**
 * @brief Initializes the Modbus Wi‑Fi infusion map and registers the process hook.
 * @retval MBW_OK on success, negative error code otherwise.
 */
int16_t ModbusWifiInf_Init(void)
{
    if (Modbus_Init(MBW_MODBUS_CHANNEL) != 0) {
        return MBW_ERR_TYPE; /* generic failure */
    }
    if (Modbus_SetProcessFunction(MBW_MODBUS_CHANNEL, ModbusWifiInf_Process) != 0) {
        return MBW_ERR_TYPE;
    }
    return MBW_OK;
}

/**
 * @brief Top‑level request dispatcher for this map.
 * @param pRequest  Incoming request (must not be NULL).
 * @param pResponse Response to populate (must not be NULL).
 * @retval MBW_OK on success, negative error code otherwise.
 */
static int16_t ModbusWifiInf_Process(ModbusRequest_t* pRequest, ModbusResponse_t* pResponse)
{
    if (!pRequest || !pResponse) { return MBW_ERR_PTR; }

    switch (pRequest->functionCode) {
        case MODBUS_FUNC_READ_HOLDING:    return ModbusWifiInf_Read(pRequest, pResponse);
        case MODBUS_FUNC_WRITE_MULTIPLE:  return ModbusWifiInf_Write(pRequest, pResponse);
        default:
            pResponse->errorCode = MBW_EX_ILLEGAL_FUNCTION;
            return MBW_ERR_TYPE;
    }
}

/* ===============================
 * Core helpers
 * =============================== */
/**
 * @brief Finds the row index in @ref kMap for a given address.
 * @return index or -1 if not found.
 */
static int MBW_FindRowByAddr(uint16_t addr)
{
    for (uint16_t i = 0; i < MBW_MAP_SIZE; i++) {
        if (kMap[i].addr == addr) { return (int)i; }
    }
    return -1;
}

/**
 * @brief Validates that a request of @p needRegs registers starting at row @p startIdx
 *        is contiguous in the map. Returns the end row index via @p endIdxOut.
 * @retval 1 if contiguous and size matches, 0 otherwise.
 */
static uint8_t MBW_IsContiguous(uint16_t startIdx, uint16_t needRegs, uint16_t *endIdxOut)
{
    uint16_t acc = 0u;
    uint16_t end = startIdx;
    while (end < MBW_MAP_SIZE) {
        if (end > startIdx) {
            const uint16_t prevEndAddr = (uint16_t)(kMap[end-1].addr + kMap[end-1].size);
            if (kMap[end].addr != prevEndAddr) { break; }
        }
        acc = (uint16_t)(acc + kMap[end].size);
        if (acc >= needRegs) { break; }
        end++;
    }
    if (acc != needRegs) { return 0u; }
    if (endIdxOut) { *endIdxOut = end; }
    return 1u;
}

/* ===============================
 * Read handler
 * =============================== */
/**
 * @brief Handles Read Holding Registers for this map.
 */
static int16_t ModbusWifiInf_Read(ModbusRequest_t* pRequest, ModbusResponse_t* pResponse)
{
    if (!pRequest || !pResponse) { return MBW_ERR_PTR; }

    const uint16_t start  = pRequest->data.readHolding.startAddress;
    const uint16_t qty    = pRequest->data.readHolding.quantity; /* in registers */

    const int idx = MBW_FindRowByAddr(start);
    if (idx < 0) {
        pResponse->errorCode = MBW_EX_ILLEGAL_DATA_ADDRESS;
        return MBW_ERR_ADDR;
    }

    uint16_t endIdx = (uint16_t)idx;
    if (!MBW_IsContiguous((uint16_t)idx, qty, &endIdx)) {
        pResponse->errorCode = MBW_EX_ILLEGAL_DATA_VALUE;
        return MBW_ERR_LEN;
    }

    uint16_t rspI = 0u;
    uint16_t regs2[2];

    for (uint16_t i = (uint16_t)idx; i <= endIdx; i++) {
        const uint16_t a = kMap[i].addr;
        switch (a) {
            /* ---- System strings via DeviceParam_Read ---- */
            case MBW_ADDR_SYS_SERIAL:
            case MBW_ADDR_SYS_NAME:
            case MBW_ADDR_SYS_MANUFACTURER:
            case MBW_ADDR_SYS_MFG_DATETIME:
            case MBW_ADDR_SYS_MODEL:
            case MBW_ADDR_SYS_FW_VERSION:
            {
                char tmp[MBW_LEN_CHAR20 + 1] = {0};
                DeviceParam_ID dp;
                switch (a) {
                    case MBW_ADDR_SYS_SERIAL:       dp = DEVICE_PARAM_SERIAL_NUMBER;          break;
                    case MBW_ADDR_SYS_NAME:         dp = DEVICE_PARAM_NAME;                   break;
                    case MBW_ADDR_SYS_MANUFACTURER: dp = DEVICE_PARAM_MANUFACTURER;           break;
                    case MBW_ADDR_SYS_MFG_DATETIME: dp = DEVICE_PARAM_MANUFACTURING_DATETIME; break;
                    case MBW_ADDR_SYS_MODEL:        dp = DEVICE_PARAM_MODEL_NUMBER;           break;
                    default:                         dp = DEVICE_PARAM_FIRMWARE_VERSION;       break;
                }
                if (DeviceParam_Read(dp, tmp) != 0) { strcpy(tmp, "ERR"); }
                MBW_StringToRegs(tmp, MBW_LEN_CHAR20,
                                 &pResponse->data.readHolding.registers[rspI],
                                 MBW_SIZE_REGS_CHAR20);
                rspI = (uint16_t)(rspI + MBW_SIZE_REGS_CHAR20);
            } break;

            /* ---- Infusion values ---- */
            case MBW_ADDR_INF_STATE: {
                const uint16_t v = (uint16_t)InfDevice_getState();
                pResponse->data.readHolding.registers[rspI++] = v;
            } break;

            case MBW_ADDR_INF_FLOW: {
                InfusionStatus_t st; if (InfDevice_GetStatus(&st) != 0) { pResponse->errorCode = MBW_EX_ILLEGAL_DATA_VALUE; return MBW_ERR_LEN; }
                const float fv = ((float)st.FlowRatex100) / 100.0f;
                MBW_FloatToRegs(fv, regs2);
                pResponse->data.readHolding.registers[rspI++] = regs2[0];
                pResponse->data.readHolding.registers[rspI++] = regs2[1];
            } break;

            case MBW_ADDR_INF_VTBI: {
                InfusionStatus_t st; if (InfDevice_GetStatus(&st) != 0) { pResponse->errorCode = MBW_EX_ILLEGAL_DATA_VALUE; return MBW_ERR_LEN; }
                const float fv = ((float)st.VTBIx100) / 100.0f;
                MBW_FloatToRegs(fv, regs2);
                pResponse->data.readHolding.registers[rspI++] = regs2[0];
                pResponse->data.readHolding.registers[rspI++] = regs2[1];
            } break;

            case MBW_ADDR_INF_VOL_INFUSED: {
                InfusionStatus_t st; if (InfDevice_GetStatus(&st) != 0) { pResponse->errorCode = MBW_EX_ILLEGAL_DATA_VALUE; return MBW_ERR_LEN; }
                const float fv = ((float)st.VolumeInfusedx100) / 100.0f;
                MBW_FloatToRegs(fv, regs2);
                pResponse->data.readHolding.registers[rspI++] = regs2[0];
                pResponse->data.readHolding.registers[rspI++] = regs2[1];
            } break;

            case MBW_ADDR_INF_TIME_S: {
                InfusionStatus_t st; if (InfDevice_GetStatus(&st) != 0) { pResponse->errorCode = MBW_EX_ILLEGAL_DATA_VALUE; return MBW_ERR_LEN; }
                MBW_U32ToRegs(st.InfusionTimeInSecs, regs2);
                pResponse->data.readHolding.registers[rspI++] = regs2[0];
                pResponse->data.readHolding.registers[rspI++] = regs2[1];
            } break;

            case MBW_ADDR_INF_REMAIN_S: {
                InfusionStatus_t st; if (InfDevice_GetStatus(&st) != 0) { pResponse->errorCode = MBW_EX_ILLEGAL_DATA_VALUE; return MBW_ERR_LEN; }
                MBW_U32ToRegs(st.RemainingTimeInSecs, regs2);
                pResponse->data.readHolding.registers[rspI++] = regs2[0];
                pResponse->data.readHolding.registers[rspI++] = regs2[1];
            } break;

            case MBW_ADDR_INF_BOLUS: {
                const float fv = InfusionSet_GetBolusRate();
                MBW_FloatToRegs(fv, regs2);
                pResponse->data.readHolding.registers[rspI++] = regs2[0];
                pResponse->data.readHolding.registers[rspI++] = regs2[1];
            } break;

            case MBW_ADDR_INF_KVO: {
                const float fv = InfusionSet_GetKVORate();
                MBW_FloatToRegs(fv, regs2);
                pResponse->data.readHolding.registers[rspI++] = regs2[0];
                pResponse->data.readHolding.registers[rspI++] = regs2[1];
            } break;

            case MBW_ADDR_INF_MAX_FLOW: {
                const float fv = InfusionSet_GetMaxFlowRate();
                MBW_FloatToRegs(fv, regs2);
                pResponse->data.readHolding.registers[rspI++] = regs2[0];
                pResponse->data.readHolding.registers[rspI++] = regs2[1];
            } break;

            case MBW_ADDR_INF_AIRLINE_SENS: {
                const uint16_t v = InfusionSet_GetAirLineSensitivity();
                pResponse->data.readHolding.registers[rspI++] = v;
            } break;

            case MBW_ADDR_INF_OCCL_PRESS: {
                const float fv = InfusionSet_GetOcclusionPressure();
                MBW_FloatToRegs(fv, regs2);
                pResponse->data.readHolding.registers[rspI++] = regs2[0];
                pResponse->data.readHolding.registers[rspI++] = regs2[1];
            } break;

            case MBW_ADDR_INF_COMPLETE_ALARM: {
                pResponse->data.readHolding.registers[rspI++] = g_infusionCompletionAlarm;
            } break;

            /* ---- Device numeric ---- */
            case MBW_ADDR_DEV_BRIGHTNESS: {
                uint16_t v = 0u; (void)DeviceParam_Read(DEVICE_PARAM_BRIGHTNESS, &v);
                pResponse->data.readHolding.registers[rspI++] = v;
            } break;

            case MBW_ADDR_DEV_LOCK_TIME_S: {
                uint16_t v = 0u; (void)DeviceParam_Read(DEVICE_PARAM_LOCKIN_PERIOD, &v);
                pResponse->data.readHolding.registers[rspI++] = v;
            } break;

            /* ---- Network strings ---- */
            case MBW_ADDR_NET_SEL_SSID: {
                MBW_StringToRegs(g_selectedSSID, MBW_LEN_CHAR20,
                                 &pResponse->data.readHolding.registers[rspI],
                                 MBW_SIZE_REGS_CHAR20);
                rspI = (uint16_t)(rspI + MBW_SIZE_REGS_CHAR20);
            } break;
            case MBW_ADDR_NET_PWD_FOR_SEL: {
                MBW_StringToRegs(g_passwordForSelectedSSID, MBW_LEN_CHAR20,
                                 &pResponse->data.readHolding.registers[rspI],
                                 MBW_SIZE_REGS_CHAR20);
                rspI = (uint16_t)(rspI + MBW_SIZE_REGS_CHAR20);
            } break;
            case MBW_ADDR_NET_CONN_SSID: {
                MBW_StringToRegs(g_connectedSSID, MBW_LEN_CHAR20,
                                 &pResponse->data.readHolding.registers[rspI],
                                 MBW_SIZE_REGS_CHAR20);
                rspI = (uint16_t)(rspI + MBW_SIZE_REGS_CHAR20);
            } break;
            case MBW_ADDR_NET_IP: {
                MBW_StringToRegs(g_assignedIP, MBW_LEN_CHAR10,
                                 &pResponse->data.readHolding.registers[rspI],
                                 MBW_SIZE_REGS_CHAR10);
                rspI = (uint16_t)(rspI + MBW_SIZE_REGS_CHAR10);
            } break;
            case MBW_ADDR_NET_MASK: {
                MBW_StringToRegs(g_subnetMask, MBW_LEN_CHAR10,
                                 &pResponse->data.readHolding.registers[rspI],
                                 MBW_SIZE_REGS_CHAR10);
                rspI = (uint16_t)(rspI + MBW_SIZE_REGS_CHAR10);
            } break;
            case MBW_ADDR_NET_GW: {
                MBW_StringToRegs(g_gateway, MBW_LEN_CHAR10,
                                 &pResponse->data.readHolding.registers[rspI],
                                 MBW_SIZE_REGS_CHAR10);
                rspI = (uint16_t)(rspI + MBW_SIZE_REGS_CHAR10);
            } break;
            case MBW_ADDR_NET_CONN_STATUS: {
                pResponse->data.readHolding.registers[rspI++] = g_connectionStatus;
            } break;

            default: {
                /* unmapped (should not reach with validated contiguity) */
                pResponse->data.readHolding.registers[rspI++] = 0u;
            } break;
        }
    }

    pResponse->slaveId                         = pRequest->slaveId;
    pResponse->functionCode                    = pRequest->functionCode;
    pResponse->errorCode                       = 0u;
    pResponse->data.readHolding.byteCount      = (uint8_t)(qty * MBW_BYTES_PER_REG);
    return MBW_OK;
}

/* ===============================
 * Write handler
 * =============================== */
/**
 * @brief Handles Write Multiple Registers for this map.
 */
static int16_t ModbusWifiInf_Write(ModbusRequest_t* pRequest, ModbusResponse_t* pResponse)
{
    if (!pRequest || !pResponse) { return MBW_ERR_PTR; }

    const uint16_t start = pRequest->data.writeMultiple.startAddress;
    const uint16_t qty   = pRequest->data.writeMultiple.quantity; /* in registers */

    const int idx = MBW_FindRowByAddr(start);
    if (idx < 0) { pResponse->errorCode = MBW_EX_ILLEGAL_DATA_ADDRESS; return MBW_ERR_ADDR; }

    uint16_t endIdx = (uint16_t)idx;
    if (!MBW_IsContiguous((uint16_t)idx, qty, &endIdx)) {
        pResponse->errorCode = MBW_EX_ILLEGAL_DATA_VALUE; return MBW_ERR_LEN;
    }

    uint16_t reqI = 0u;

    for (uint16_t i = (uint16_t)idx; i <= endIdx; i++) {
        if (kMap[i].rw != RW) { pResponse->errorCode = MBW_EX_ILLEGAL_FUNCTION; return MBW_ERR_RO; }

        const uint16_t a = kMap[i].addr;
        switch (a) {
            case MBW_ADDR_SYS_NAME: { /* Write Device Name (CHAR20) */
                char tmp[MBW_LEN_CHAR20 + 1];
                MBW_RegsToString(&pRequest->data.writeMultiple.registers[reqI],
                                 MBW_SIZE_REGS_CHAR20, tmp, sizeof(tmp));
                DeviceParam_Write(DEVICE_PARAM_NAME, tmp);
                reqI = (uint16_t)(reqI + MBW_SIZE_REGS_CHAR20);
            } break;

            case MBW_ADDR_INF_COMPLETE_ALARM: {
                g_infusionCompletionAlarm = pRequest->data.writeMultiple.registers[reqI++];
            } break;

            case MBW_ADDR_NET_SEL_SSID: {
                MBW_RegsToString(&pRequest->data.writeMultiple.registers[reqI],
                                 MBW_SIZE_REGS_CHAR20, g_selectedSSID, sizeof(g_selectedSSID));
                reqI = (uint16_t)(reqI + MBW_SIZE_REGS_CHAR20);
            } break;
            case MBW_ADDR_NET_PWD_FOR_SEL: {
                MBW_RegsToString(&pRequest->data.writeMultiple.registers[reqI],
                                 MBW_SIZE_REGS_CHAR20, g_passwordForSelectedSSID, sizeof(g_passwordForSelectedSSID));
                reqI = (uint16_t)(reqI + MBW_SIZE_REGS_CHAR20);
            } break;
            case MBW_ADDR_NET_CONN_SSID: {
                MBW_RegsToString(&pRequest->data.writeMultiple.registers[reqI],
                                 MBW_SIZE_REGS_CHAR20, g_connectedSSID, sizeof(g_connectedSSID));
                reqI = (uint16_t)(reqI + MBW_SIZE_REGS_CHAR20);
            } break;
            case MBW_ADDR_NET_IP: {
                MBW_RegsToString(&pRequest->data.writeMultiple.registers[reqI],
                                 MBW_SIZE_REGS_CHAR10, g_assignedIP, sizeof(g_assignedIP));
                reqI = (uint16_t)(reqI + MBW_SIZE_REGS_CHAR10);
            } break;
            case MBW_ADDR_NET_MASK: {
                MBW_RegsToString(&pRequest->data.writeMultiple.registers[reqI],
                                 MBW_SIZE_REGS_CHAR10, g_subnetMask, sizeof(g_subnetMask));
                reqI = (uint16_t)(reqI + MBW_SIZE_REGS_CHAR10);
            } break;
            case MBW_ADDR_NET_GW: {
                MBW_RegsToString(&pRequest->data.writeMultiple.registers[reqI],
                                 MBW_SIZE_REGS_CHAR10, g_gateway, sizeof(g_gateway));
                reqI = (uint16_t)(reqI + MBW_SIZE_REGS_CHAR10);
            } break;
            case MBW_ADDR_NET_CONN_STATUS: {
                g_connectionStatus = pRequest->data.writeMultiple.registers[reqI++];
            } break;

            default: {
                /* Skip over RW block we don't explicitly handle */
                reqI = (uint16_t)(reqI + kMap[i].size);
            } break;
        }
    }

    pResponse->slaveId                         = pRequest->slaveId;
    pResponse->functionCode                    = pRequest->functionCode;
    pResponse->errorCode                       = 0u;
    pResponse->data.writeMultiple.startAddress = start;
    pResponse->data.writeMultiple.quantity     = qty;
    return MBW_OK;
}
