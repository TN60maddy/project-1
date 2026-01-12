/*
 * HwRtc.h
 * */


#ifndef HW_RTC_H
#define HW_RTC_H

#include "stm32h7xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @brief Initializes the RTC hardware.
 */
void HwRtc_Init(void);

/**
 * @brief Sets the RTC time.
 * @param hours   Hours (0-23)
 * @param minutes Minutes (0-59)
 * @param seconds Seconds (0-59)
 * @return 0 if success, -1 if error
 */
int HwRtc_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds);

/**
 * @brief Gets the current RTC time.
 * @param hours   Pointer to store hours (0-23)
 * @param minutes Pointer to store minutes (0-59)
 * @param seconds Pointer to store seconds (0-59)
 * @return 0 if success, -1 if error
 */
int HwRtc_GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds);

/**
 * @brief Sets the RTC date.
 * @param year    Year (e.g., 2025)
 * @param month   Month (1-12)
 * @param day     Day (1-31)
 * @return 0 if success, -1 if error
 */
int HwRtc_SetDate(uint16_t year, uint8_t month, uint8_t day);

/**
 * @brief Gets the current RTC date.
 * @param year    Pointer to store year
 * @param month   Pointer to store month (1-12)
 * @param day     Pointer to store day (1-31)
 * @return 0 if success, -1 if error
 */
int HwRtc_GetDate(uint16_t *year, uint8_t *month, uint8_t *day);

/**
 * @brief Sets an RTC alarm.
 * @param hours   Hours (0-23)
 * @param minutes Minutes (0-59)
 * @param seconds Seconds (0-59)
 * @return 0 if success, -1 if error
 */
int HwRtc_SetAlarm(uint8_t hours, uint8_t minutes, uint8_t seconds);

/**
 * @brief Disables the RTC alarm.
 */
void HwRtc_DisableAlarm(void);

#ifdef __cplusplus
}
#endif

#endif /* HW_RTC_H */
