/*
 * HwBacklightConfig.h
 */

#ifndef SRC_HWBACKLIGHTCTRL_INC_HWBACKLIGHTCONFIG_H_
#define SRC_HWBACKLIGHTCTRL_INC_HWBACKLIGHTCONFIG_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#define HW_BACKLIGHT_TIM_GPIO_AF_CHANNEL1               GPIO_AF2_TIM3
/* PWM Pin for Back Light */
#define HW_BACKLIGHT_TIM_GPIO_PORT_CHANNEL1              GPIOB
#define HW_BACKLIGHT_TIM_GPIO_CLK_ENABLE()                   __HAL_RCC_GPIOB_CLK_ENABLE()
#define HW_BACKLIGHT_TIM_GPIO_CLK_DISABLE()                  __HAL_RCC_GPIOB_CLK_DISABLE()
#define HW_BACKLIGHT_TIM_GPIO_PIN_CHANNEL1               GPIO_PIN_0

#define HW_BACKLIGHT_TIM_CHANNEL_GPIO_CLK_ENABLE()     HW_BACKLIGHT_TIM_GPIO_CLK_ENABLE();



/* Back Light Instance & Channel */
#define HW_BACKLIGHT_TIM                 			              TIM3
#define HW_BACKLIGHT_PWM_CHANNEL                      TIM_CHANNEL_3

#define HW_BACKLIGHT_TIM_CLK_ENABLE()   				 __HAL_RCC_TIM3_CLK_ENABLE()

#define HW_BACKLIGHT_TIM_SET_DUTYCYCLE(x)             ( ( HW_BACKLIGHT_TIM->CCR3 ) = (x))
#define HW_BACKLIGHT_TIM_SET_PERIOD(x)                ( ( HW_BACKLIGHT_TIM->ARR ) = (x))

/*********************************************************************************************************************************************/


#endif /* SRC_HWBACKLIGHTCTRL_INC_HWBACKLIGHTCONFIG_H_ */
