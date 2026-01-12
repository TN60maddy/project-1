/*
 * HwBattCtrl.h
 */

#ifndef HWAPIS_HWBATTCTRL_INC_HWBATTCTRL_H_
#define HWAPIS_HWBATTCTRL_INC_HWBATTCTRL_H_


#ifndef HW_BATT_CTRL_H
#define HW_BATT_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "stm32h7xx_hal.h"

// Battery Status Enumeration
typedef enum {
    BATT_STATUS_UNKNOWN = 0,
    BATT_STATUS_NOT_CONNECTED,
    BATT_STATUS_CHARGING,
    BATT_STATUS_DISCHARGING,
    BATT_STATUS_FULL
} BatteryStatus_t;

// Power Source Enumeration
typedef enum {
    POWER_SOURCE_UNKNOWN = 0,
    POWER_SOURCE_SMPS_12V,
    POWER_SOURCE_USB_12V,
    POWER_SOURCE_BATTERY
} PowerSource_t;

// Battery Information Structure
typedef struct {
    uint16_t voltage_mV;    // Battery voltage in millivolts
    int8_t temperature_C;   // Battery temperature in degrees Celsius
    uint8_t charge_level;   // Battery charge percentage (0-100%)
    uint16_t time_to_empty_min;  // Estimated time to empty in minutes
    uint16_t time_to_full_min;   // Estimated time to full charge in minutes
    BatteryStatus_t status; // Current battery status
} BatteryInfo_t;

/**
 * @brief Initialize battery control module.
 */
uint8_t HwBattCtrl_Init(void);

/**
 * @brief Check if the battery is connected.
 * @return true if battery is connected, false otherwise.
 */
bool HwBattCtrl_IsBatteryConnected(void);

/**
 * @brief Get current battery status.
 * @return BatteryStatus_t indicating current status.
 */
BatteryStatus_t HwBattCtrl_GetBatteryStatus(void);

/**
 * @brief Get battery voltage in millivolts.
 * @return Battery voltage in mV.
 */
uint16_t HwBattCtrl_GetBatteryVoltage(void);

/**
 * @brief Get battery temperature in degrees Celsius.
 * @return Battery temperature.
 */
int8_t HwBattCtrl_GetBatteryTemperature(void);

/**
 * @brief Get battery charge level in percentage.
 * @return Charge level (0-100%).
 */
uint8_t HwBattCtrl_GetBatteryChargeLevel(void);

/**
 * @brief Get the current power source (SMPS, USB, or Battery).
 * @return PowerSource_t indicating the active power source.
 */
PowerSource_t HwBattCtrl_GetPowerSource(void);

/**
 * @brief Retrieve complete battery information.
 * @param[out] info Pointer to BatteryInfo_t structure to be filled.
 */
void HwBattCtrl_GetBatteryInfo(BatteryInfo_t *info);

/**
 * @brief Enable or disable battery charging.
 * @param enable true to enable charging, false to disable.
 */
void HwBattCtrl_SetCharging(bool enable);

/**
 * @brief Check if charging is enabled.
 * @return true if charging is enabled, false otherwise.
 */
bool HwBattCtrl_IsChargingEnabled(void);

/**
 * @brief Get estimated time to battery empty (in minutes).
 * @return Estimated time in minutes until battery is empty.
 */
uint16_t HwBattCtrl_GetTimeToEmpty(void);

/**
 * @brief Get estimated time to full charge (in minutes).
 * @return Estimated time in minutes until battery is fully charged.
 */
uint16_t HwBattCtrl_GetTimeToFull(void);

#ifdef __cplusplus
}
#endif

#endif // HW_BATT_CTRL_H




#endif /* HWAPIS_HWBATTCTRL_INC_HWBATTCTRL_H_ */
