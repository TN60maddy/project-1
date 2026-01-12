/*
 *  HwFuelGauge.h
 */

#ifndef HW_FUEL_GAUGE_H
#define HW_FUEL_GAUGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

// Fuel Gauge Status Enumeration
typedef enum {
    FUEL_GAUGE_OK = 0,
    FUEL_GAUGE_ERROR,
    FUEL_GAUGE_NOT_FOUND,
    FUEL_GAUGE_I2C_ERROR
} FuelGaugeStatus_t;

// Battery Status Enumeration (from Fuel Gauge IC)
typedef enum {
    FG_BATT_STATUS_UNKNOWN = 0,
    FG_BATT_STATUS_NOT_CONNECTED,
    FG_BATT_STATUS_CHARGING,
    FG_BATT_STATUS_DISCHARGING,
    FG_BATT_STATUS_FULL
} FGBatteryStatus_t;

// Battery Information Structure
typedef struct {
    uint16_t voltage_mV;       // Battery voltage in millivolts
    int8_t temperature_C;      // Battery temperature in degrees Celsius
    uint8_t charge_level;      // Battery charge percentage (0-100%)
    uint16_t time_to_empty_min; // Estimated time to empty in minutes
    uint16_t time_to_full_min;  // Estimated time to full charge in minutes
    int16_t current_mA;        // Instantaneous current in mA (positive for charging, negative for discharge)
    uint16_t capacity_mAh;     // Full charge capacity in mAh
    FGBatteryStatus_t status;  // Current battery status
} FGBatteryInfo_t;

/**
 * @brief Initialize the MAX1726x fuel gauge module with battery-specific parameters.
 * @param designCapacity_mAh   Design Capacity Register Data (in mAh).
 * @param terminationCurrent_mA Termination Current Register Data (in mA).
 * @param emptyVoltage_mV      Empty Voltage Register Data (in mV).
 * @return FuelGaugeStatus_t indicating the initialization status.
 */
FuelGaugeStatus_t HwFuelGauge_Init(uint16_t designCapacity_mAh, uint16_t terminationCurrent_mA, uint16_t emptyVoltage_mV);

/**
 * @brief Check if the fuel gauge is responding.
 * @return true if the fuel gauge is detected, false otherwise.
 */
bool HwFuelGauge_IsPresent(void);

/**
 * @brief Get battery voltage in millivolts from the fuel gauge.
 * @return Battery voltage in mV.
 */
uint16_t HwFuelGauge_GetBatteryVoltage(void);

/**
 * @brief Get battery temperature in degrees Celsius.
 * @return Battery temperature.
 */
uint8_t HwFuelGauge_GetBatteryTemperature(void);

/**
 * @brief Get battery charge level in percentage.
 * @return Charge level (0-100%).
 */
uint8_t HwFuelGauge_GetBatteryChargeLevel(void);

/**
 * @brief Get estimated time to battery empty (in minutes).
 * @return Estimated time in minutes until battery is empty.
 */
uint16_t HwFuelGauge_GetTimeToEmpty(void);

/**
 * @brief Get estimated time to full charge (in minutes).
 * @return Estimated time in minutes until battery is fully charged.
 */
uint16_t HwFuelGauge_GetTimeToFull(void);

/**
 * @brief Get real-time battery current in milliamps (mA).
 * @return Battery current (positive for charging, negative for discharging).
 */
int16_t HwFuelGauge_GetBatteryCurrent(void);

/**
 * @brief Get the full charge capacity of the battery in mAh.
 * @return Battery capacity in mAh.
 */
uint16_t HwFuelGauge_GetBatteryCapacity(void);

/**
 * @brief Get the current battery status (Charging, Discharging, Full, etc.).
 * @return FGBatteryStatus_t indicating battery status.
 */
FGBatteryStatus_t HwFuelGauge_GetBatteryStatus(void);

/**
 * @brief Retrieve complete battery information from the fuel gauge.
 * @param[out] info Pointer to FGBatteryInfo_t structure to be filled.
 */
void HwFuelGauge_GetBatteryInfo(FGBatteryInfo_t *info);

/**
 * @brief Perform a soft reset of the fuel gauge.
 * @return FuelGaugeStatus_t indicating success or failure.
 */
FuelGaugeStatus_t HwFuelGauge_SoftReset(void);

#ifdef __cplusplus
}
#endif

#endif // HW_FUEL_GAUGE_H
