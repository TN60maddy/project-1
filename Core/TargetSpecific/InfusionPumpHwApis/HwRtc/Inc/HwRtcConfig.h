/*
 * HwRtcConfig.h
 *
 */

#ifndef RTC_INC_HWRTCCONFIG_H_
#define RTC_INC_HWRTCCONFIG_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_rtc.h"

/* RTC Clock Enable */
#define HW_RTC_CLK_ENABLE()           __HAL_RCC_RTC_ENABLE();
#define HW_RTC_CLK_DISABLE()          __HAL_RCC_RTC_DISABLE();

/* RTC Instance */
#define HW_RTC_INSTANCE                  RTC

#define HW_RTC_PWR_EN_BKUP_CLK_ENABLE()  HAL_PWR_EnableBkUpAccess();

/* RTC Time Format */
#define HW_RTC_HOUR_FORMAT            RTC_HOURFORMAT_24

/* RTC Asynchronous and Synchronous Prescalers */
#define HW_RTC_ASYNC_PRESCALER        127
#define HW_RTC_SYNC_PRESCALER         255

/* RTC Alarm Configuration */
#define HW_RTC_ALARM_A                RTC_ALARM_A
#define HW_RTC_ALARM_B                RTC_ALARM_B


#endif /* RTC_INC_HWRTCCONFIG_H_ */
