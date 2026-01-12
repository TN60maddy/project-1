/*
 * HwRtcCtrl.h
 * */

#ifndef HW_RTC_CTRL_H
#define HW_RTC_CTRL_H

#include "../../HwRtc/Inc/HwRtc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes and configures the RTC.
 */
void HwRtcCtrl_Init(void);

/**
 * @brief Sets the RTC time using a formatted string.
1.	How It Works Calling the low-level RTC initialization (HwRtc_Init())
    Ensures that the RTC hardware is properly configured.
2.	Checking if the RTC has valid time/date settings
	STM32 RTC retains time/date even during power loss (if backed up by a battery).
	This function should check if RTC has been reset or contains invalid values.
3.	Setting default values if RTC is not initialized properly
	If RTC is uninitialized or reset (e.g., due to power failure and no backup battery), it sets a default date/time.


 * @param timeStr Time string in "HH:MM:SS" format.
 * @return 0 if success, -1 if error
 */
int HwRtcCtrl_SetTimeStr(const char *timeStr);

/**
 * @brief Gets the RTC time as a formatted string.
 * @param buffer Buffer to store the time string (must be at least 9 bytes).
 * @return 0 if success, -1 if error
 */
int HwRtcCtrl_GetTimeStr(char *buffer);

/**
 * @brief Sets the RTC date using a formatted string.
 * @param dateStr Date string in "YYYY-MM-DD" format.
 * @return 0 if success, -1 if error
 */
int HwRtcCtrl_SetDateStr(const char *dateStr);

/**
 * @brief Gets the RTC date as a formatted string.
 * @param buffer Buffer to store the date string (must be at least 11 bytes).
 * @return 0 if success, -1 if error
 */
int HwRtcCtrl_GetDateStr(char *buffer);

/**
 * @brief Sets an RTC alarm using a formatted string.
 * @param timeStr Alarm time in "HH:MM:SS" format.
 * @return 0 if success, -1 if error
 */
int HwRtcCtrl_SetAlarmStr(const char *timeStr);

/**
 * @brief Disables the RTC alarm.
 */
void HwRtcCtrl_DisableAlarm(void);

#ifdef __cplusplus
}
#endif

#endif /* HW_RTC_CTRL_H */
