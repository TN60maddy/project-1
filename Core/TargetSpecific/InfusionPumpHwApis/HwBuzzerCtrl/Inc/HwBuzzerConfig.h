/*
 * HwBuzzerConfig.h
 */

#ifndef HWAPIS_HWBUZZERCTRL_INC_HWBUZZERCONFIG_H_
#define HWAPIS_HWBUZZERCTRL_INC_HWBUZZERCONFIG_H_


/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#define HW_BUZZER_TIM_GPIO_AF_CHANNEL1                GPIO_AF2_TIM3
/* PWM Pin for Back Light */
#define HW_BUZZER_TIM_GPIO_PORT_CHANNEL1              GPIOA
#define HW_BUZZER_TIM_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOA_CLK_ENABLE()
#define HW_BUZZER_TIM_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOA_CLK_DISABLE()
#define HW_BUZZER_TIM_GPIO_PIN_CHANNEL1                GPIO_PIN_6

#define HW_BUZZER_TIM_CHANNEL_GPIO_CLK_ENABLE()       HW_BUZZER_TIM_GPIO_CLK_ENABLE();



/* Back Light Instance & Channel */
#define HW_BUZZER_TIM                 			   TIM3
#define HW_BUZZER_PWM_CHANNEL                      TIM_CHANNEL_1

#define HW_BUZZER_TIM_CLK_ENABLE()   				 __HAL_RCC_TIM3_CLK_ENABLE()

#define HW_BUZZER_TIM_SET_DUTYCYCLE(x)             ( ( HW_BACKLIGHT_TIM->CCR1 ) = (x))
#define HW_BUZZER_TIM_SET_PERIOD(x)                ( ( HW_BACKLIGHT_TIM->ARR ) = (x))

/*********************************************************************************************************************************************/

#endif /* HWAPIS_HWBUZZERCTRL_INC_HWBUZZERCONFIG_H_ */
