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
*   This file implements a generic HW Interface of Internal RTC used in Infusion Pump
*
********************************************************************************/


#include "../../HwRtc/Inc/HwRtcCtrl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
  * @brief Initializes RTC and sets default date & time.
  * @param void
  * @retvalue void
  *
  */

void HwRtcCtrl_Init(void) {
    HwRtc_Init();

    uint16_t year;
    uint8_t month, day, hours, minutes, seconds;

    if (HwRtc_GetDate(&year, &month, &day) != 0 || HwRtc_GetTime(&hours, &minutes, &seconds) != 0) {
        year = 2025;
        month = 1;
        day = 1;
        hours = 0;
        minutes = 0;
        seconds = 0;

        HwRtc_SetDate(year, month, day);
        HwRtc_SetTime(hours, minutes, seconds);
    }
}

/**
  * @brief Sets RTC time using a string (format: "HH:MM:SS").
  * @retval 0 = Success, -1 = Failure.
  */

int HwRtcCtrl_SetTimeStr(const char *timeStr) {
    if (!timeStr || strlen(timeStr) != 8) return -1;

    char tempStr[9];  // Copy input string to avoid modifying original
    strncpy(tempStr, timeStr, 9);

    char *token;
    uint8_t hours, minutes, seconds;

    token = strtok(tempStr, ":");
    if (token == NULL) return -1;
    hours = atoi(token);

    token = strtok(NULL, ":");
    if (token == NULL) return -1;
    minutes = atoi(token);

    token = strtok(NULL, ":");
    if (token == NULL) return -1;
    seconds = atoi(token);

    return HwRtc_SetTime(hours, minutes, seconds);
}



/**
  * @brief Reads RTC time and stores it in buffer (format: "HH:MM:SS").
  * @retval 0 = Success, 1 = Failure.
  */


int HwRtcCtrl_GetTimeStr(char *buffer) {
    if (!buffer) return -1;

    uint8_t hours, minutes, seconds;
    if (HwRtc_GetTime(&hours, &minutes, &seconds) != 0) return -1;
    	sprintf(buffer,"%02d:%02d:%02d\r\n",hours,minutes,seconds);
    return 0;
}

/**
  * @brief Sets RTC date using a string (format: "YYYY-MM-DD").
  * @retval 0 = Success, 1 = Failure.
  */



int HwRtcCtrl_SetDateStr(const char *dateStr) {
    if (!dateStr || strlen(dateStr) != 10) return -1;

    char tempStr[11];                   // Copy input string to avoid modifying original
    strncpy(tempStr, dateStr, 11);

    char *token;
    uint16_t year;
    uint8_t month, day;

    token = strtok(tempStr, "-");
    if (token == NULL) return -1;
    year = atoi(token);

    token = strtok(NULL, "-");
    if (token == NULL) return -1;
    month = atoi(token);

    token = strtok(NULL, "-");
    if (token == NULL) return -1;
    day = atoi(token);
    return HwRtc_SetDate(year, month, day);
}

/**
  * @brief Reads RTC date and stores it in buffer (format: "YYYY-MM-DD").
  * @retval 0 = Success, -1 = Failure.
  */





int HwRtcCtrl_GetDateStr(char *buffer) {
    if (!buffer) return -1;

    uint16_t year;
    uint8_t month, day;
    if (HwRtc_GetDate(&year, &month, &day) != 0) return -1;
    sprintf(buffer,"%04d:%02d:%02d\r\n",year,month,day);
    return 0;
}

/**
  * @brief Sets RTC alarm using a string (format: "HH:MM:SS").
  * @retval 0 = Success, -1 = Failure.
  */

int HwRtcCtrl_SetAlarmStr(const char *timeStr) {
    if (!timeStr || strlen(timeStr) != 8) return -1;

    char tempStr[9];  // Copy input string to avoid modifying the original
    strncpy(tempStr, timeStr, 9);

    char *token;
    uint8_t hours, minutes, seconds;

    token = strtok(tempStr, ":");
    if (token == NULL) return -1;
    hours = atoi(token);

    token = strtok(NULL, ":");
    if (token == NULL) return -1;
    minutes = atoi(token);

    token = strtok(NULL, ":");
    if (token == NULL) return -1;
    seconds = atoi(token);

    return HwRtc_SetAlarm(hours, minutes, seconds);
}

/**
  * @brief Disables the RTC alarm.
  */


void HwRtcCtrl_DisableAlarm(void) {
    HwRtc_DisableAlarm();
}
