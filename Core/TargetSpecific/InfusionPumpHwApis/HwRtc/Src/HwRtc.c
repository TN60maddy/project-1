/*******************************************************************************
*
*    INFUSION PUMP PROJECT
*
*                                    Copyright (c) Aria Innovations
*
*
*
********************************************************************************
*
* DESCRIPTION:
*   This file implements a generic HW Interface of internal RTC used in Infusion Pump
*
********************************************************************************/
#include "../../HwRtc/Inc/HwRtc.h"

#include "../../HwRtc/Inc/HwRtcConfig.h"

RTC_HandleTypeDef HwRtc_handler;


/**
  * @brief
  *        Initializes the Real-Time Clock (RTC) in backup power mode.
  *        This function configures the RTC peripheral to operate in backup power mode, ensuring that it
  *        continues to function even when the main power supply is disconnected.
  * @param void
  * @retval void
  */


void HwRtc_Init(void) {
    HwRtc_handler.Instance = HW_RTC_INSTANCE;
    HwRtc_handler.Init.HourFormat = HW_RTC_HOUR_FORMAT;
    HwRtc_handler.Init.AsynchPrediv = HW_RTC_ASYNC_PRESCALER;
    HwRtc_handler.Init.SynchPrediv = HW_RTC_SYNC_PRESCALER;
    HwRtc_handler.Init.OutPut = RTC_OUTPUT_DISABLE;
    HwRtc_handler.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
    HwRtc_handler.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    HwRtc_handler.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

    HAL_RCCEx_PeriphCLKConfig(&(RCC_PeriphCLKInitTypeDef){
        .PeriphClockSelection = RCC_PERIPHCLK_RTC,
        .RTCClockSelection = RCC_RTCCLKSOURCE_LSE
    });

    HW_RTC_CLK_ENABLE();
    HAL_RTC_Init(&HwRtc_handler);
    HW_RTC_PWR_EN_BKUP_CLK_ENABLE();
}

/**
  * @brief
  *        Sets the current time in the Real-Time Clock (RTC).
  *        This function configures the RTC to set the current time using the provided hours, minutes, and seconds.
  *  @param hours
  *        		The hour value to set (0 to 23 in 24-hour format).
  *        minutes
  *        		The minute value to set (0 to 59).
  *        seconds
  *        		The second value to set (0 to 59).
  *        @retval int
  *         0 = Success (Time set successfully).
  *         -1 = Failure (RTC write failure).
  */

int HwRtc_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    RTC_TimeTypeDef sTime = {0};
    sTime.Hours = hours;
    sTime.Minutes = minutes;
    sTime.Seconds = seconds;
    sTime.TimeFormat = RTC_HOURFORMAT12_AM;

    if (HAL_RTC_SetTime(&HwRtc_handler, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
        return -1;
    }
    return 0;
}

/**
  * @brief
  *        Retrieves the current time from the Real-Time Clock (RTC).
  *        This function reads the current time (hours, minutes, and seconds) from the RTC and stores the values
  *        in the provided variables.
  *   @param hours
  *        		A pointer to a variable where the current hour value (0 to 23 in 24-hour format) will be stored.
  *         minutes
  *        		A pointer to a variable where the current minute value (0 to 59) will be stored.
  *        seconds
  *        		A pointer to a variable where the current second value (0 to 59) will be stored.
  *    0 = Success (Time read successfully and stored in the provided variables).
  *         -1 = Failure to read.
  */

int HwRtc_GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds) {
    if (!hours || !minutes || !seconds) return -1;
    RTC_TimeTypeDef sTime = {0};

    if (HAL_RTC_GetTime(&HwRtc_handler, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
        return -1;
    }

    *hours = sTime.Hours;
    *minutes = sTime.Minutes;
    *seconds = sTime.Seconds;
    return 0;
}

/**
  * @brief
  *        Sets the current date in the Real-Time Clock (RTC).
  *        This function configures the RTC to set the current date using the provided year, month, and day.
  *  @param year
  *        		The year value to set (e.g., 2023).
  *         month
  *        		The month value to set (1 to 12).
  *        	param day
  *        		The day value to set (1 to 31, depending on the month).
  *  0 = Success (Date set successfully).
  *  -1 = Failure.
  */


int HwRtc_SetDate(uint16_t year, uint8_t month, uint8_t day) {
    RTC_DateTypeDef sDate = {0};
    sDate.Year = year - 2000; // RTC stores year as offset from 2000
    sDate.Month = month;
    sDate.Date = day;
    sDate.WeekDay = RTC_WEEKDAY_MONDAY; // Default value, should be determined properly

    if (HAL_RTC_SetDate(&HwRtc_handler, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
        return -1;
    }
    return 0;
}
/**
  * @brief
  *        Retrieves the current date from the Real-Time Clock (RTC).
  *        This function reads the current date (year, month, and day) from the RTC and stores the values
  *        in the provided variables.
  *
  * @param year
  *        A pointer to a variable where the current year value will be stored (e.g., 2023).
  *         month
  *        A pointer to a variable where the current month value (1 to 12) will be stored.
  *        day
  *        A pointer to a variable where the current day value (1 to 31, depending on the month).
  *        @retval int
  *         0 = Success (Date read successfully and stored in the provided variables).
  *         1 = Failure
  */

int HwRtc_GetDate(uint16_t *year, uint8_t *month, uint8_t *day) {
    if (!year || !month || !day) return -1;
    RTC_DateTypeDef sDate = {0};

    if (HAL_RTC_GetDate(&HwRtc_handler, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
        return -1;
    }

    *year = sDate.Year + 2000;
    *month = sDate.Month;
    *day = sDate.Date;
    return 0;
}
/**
  * @brief
  *        Sets an alarm in the Real-Time Clock (RTC) at the specified time.
  *        This function configures the RTC to trigger an alarm at the provided hours, minutes, and seconds.
  * @param hours
  *        		The hour value to set (0 to 23 in 24-hour format).
  *        minutes
  *        		The minute value to set (0 to 59).
  *        seconds
  *        		The second value to set (0 to 59)
  *  @retval int
  *         0 = Success (Alarm set successfully).
  *         1 = Failure (RTC write failure).
  */


int HwRtc_SetAlarm(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    RTC_AlarmTypeDef sAlarm = {0};
    sAlarm.AlarmTime.Hours = hours;
    sAlarm.AlarmTime.Minutes = minutes;
    sAlarm.AlarmTime.Seconds = seconds;
    sAlarm.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
    sAlarm.Alarm = RTC_ALARM_A;

    if (HAL_RTC_SetAlarm_IT(&HwRtc_handler, &sAlarm, RTC_FORMAT_BIN) != HAL_OK) {
        return -1;
    }
    return 0;
}

/**
  * @brief
  *        Disables the alaram.
  * @param void
  *  @retval void
  *
  */

void HwRtc_DisableAlarm(void) {
    HAL_RTC_DeactivateAlarm(&HwRtc_handler, RTC_ALARM_A);
}
