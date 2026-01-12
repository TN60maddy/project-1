/*
 *
 * HwFuelGaugeConfig.h
 *
 */

#ifndef TARGETSPECIFIC_HWFUELGAUGECONFIG_H_
#define TARGETSPECIFIC_HWFUELGAUGECONFIG_H_




/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Definition for Fuel Gauge Alert GPIO  */
#define HW_FUELGAUGE_ALERT_GPIO_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define HW_FUELGAUGE_ALERT_GPIO_CLK_DISABLE __HAL_RCC_GPIOC_CLK_DISABLE

#define HW_FUELGAUGE_ALERT_PIN  		GPIO_PIN_0
#define HW_FUELGAUGE_ALERT_PORT 		GPIOC



#endif /* TARGETSPECIFIC_HWFUELGAUGECONFIG_H_ */
