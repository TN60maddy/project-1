/*
 * HwStepperConfig.h
 *
 */

#ifndef TARGETSPECIFIC_HWSTEPPERCONFIG_H_
#define TARGETSPECIFIC_HWSTEPPERCONFIG_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"


#define HW_STEPPER_TIM_CLOCK ( 1000000UL )
#define HW_STEPPER_CRTL_DEFAULT_PRESCALE ( ( ( ( unsigned long ) SystemCoreClock/ HW_STEPPER_TIM_CLOCK ) ) - 1 )


/* Direction Pin for Stepper 1 */

#define HW_STEPPER1_TIM_GPIO_AF_CHANNEL1          GPIO_AF1_TIM2

#define HW_STEPPER1_DIR_GPIO_PORT                   GPIOC
#define HW_STEPPER1_DIR_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define HW_STEPPER1_DIR_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()
#define HW_STEPPER1_DIR_GPIO_PIN                    GPIO_PIN_4

/* Enable Pin for Stepper 1 */
#define HW_STEPPER1_EN_GPIO_PORT                GPIOG
#define HW_STEPPER1_EN_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOG_CLK_ENABLE()
#define HW_STEPPER1_EN_GPIO_CLK_DISABLE()       __HAL_RCC_GPIOG_CLK_DISABLE()
#define HW_STEPPER1_EN_GPIO_PIN                 GPIO_PIN_12


/* Step Pin for Stepper 1 */
#define HW_STEPPER1_TIM_GPIO_PORT_CHANNEL1              GPIOA
#define HW_STEPPER1_TIM_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define HW_STEPPER1_TIM_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOA_CLK_DISABLE()
#if defined( USE_STM32H743I_EVAL )
#define HW_STEPPER1_TIM_GPIO_PIN_CHANNEL1            GPIO_PIN_15
#else
#define HW_STEPPER1_TIM_GPIO_PIN_CHANNEL1            GPIO_PIN_5

#define ADDRESS_CHOPCONF       0x6C

#endif
#define HW_STEPPER1_TIM_CHANNEL_GPIO_CLK_ENABLE()     HW_STEPPER1_TIM_GPIO_CLK_ENABLE();\
													  HW_STEPPER1_DIR_GPIO_CLK_ENABLE();\
													  HW_STEPPER1_EN_GPIO_CLK_ENABLE();



/* Stepper 1 Instance & Channel */
#define HW_STEPPER1_TIM                 			 TIM2
#define HW_STEPPER1_PWM_CHANNEL                      TIM_CHANNEL_1

#define HW_STEPPER1_TIM_CLK_ENABLE()   				 __HAL_RCC_TIM2_CLK_ENABLE()

#define HW_STEPPER1_TIM_SET_DUTYCYCLE(x)             ( ( HW_STEPPER1_TIM->CCR1 ) = ( x + 1 ) )
#define HW_STEPPER1_TIM_SET_PERIOD(x)                ( ( HW_STEPPER1_TIM->ARR ) = x )
#define HW_STEPPER1_TIM_UPDATE( )                    ( ( HW_STEPPER1_TIM->EGR = TIM_EGR_UG )


#define HW_STEPPER1_UART          USART2
#define HW_STEPPER1_BAUDRATE      115200
#define HW_STEPPER1_WORDLENGTH    UART_WORDLENGTH_8B
#define HW_STEPPER1_PARITY        UART_PARITY_NONE
#define HW_STEPPER1_STOPBITS      UART_STOPBITS_1

/*********************************************************************************************************************************************/

/* Definitions for Stepper 2 */

/* Direction Pin for Stepper 2 */

#define HW_STEPPER2_TIM_GPIO_AF_CHANNEL2          GPIO_AF3_TIM8

#define HW_STEPPER2_DIR_GPIO_PORT						GPIOC
#define HW_STEPPER2_DIR_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOC_CLK_ENABLE()
#define HW_STEPPER2_DIR_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOC_CLK_DISABLE()
#define HW_STEPPER2_DIR_GPIO_PIN                     		GPIO_PIN_5

/* Enable Pin for Stepper 2 */

#define HW_STEPPER2_EN_GPIO_PORT                   GPIOB
#define HW_STEPPER2_EN_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define HW_STEPPER2_EN_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()
#define HW_STEPPER2_EN_GPIO_PIN                         GPIO_PIN_1


/* Step Pin for Stepper 2 */

#define HW_STEPPER2_TIM_GPIO_PORT_CHANNEL2             GPIOC
#define HW_STEPPER2_TIM_GPIO_CLK_ENABLE()      		__HAL_RCC_GPIOC_CLK_ENABLE();
#define HW_STEPPER2_TIM_GPIO_CLK_DISABLE()             __HAL_RCC_GPIOC_CLK_DISABLE();
#define HW_STEPPER2_TIM_GPIO_PIN_CHANNEL2             GPIO_PIN_8



#define HW_STEPPER2_TIM_CHANNEL_GPIO_CLK_ENABLE()        HW_STEPPER2_TIM_GPIO_CLK_ENABLE();\
	                                                     HW_STEPPER2_EN_GPIO_CLK_ENABLE();\
	                                                     HW_STEPPER2_DIR_GPIO_CLK_ENABLE();



#define HW_STEPPER2_TIM                              TIM8
#define HW_STEPPER2_PWM_CHANNEL                     TIM_CHANNEL_3
#define HW_STEPPER2_TIM_CLK_ENABLE()   				__HAL_RCC_TIM8_CLK_ENABLE()

#define HW_STEPPER2_TIM_SET_DUTYCYCLE(x)          ( ( HW_STEPPER2_TIM->CCR3 ) = (x))
#define HW_STEPPER2_TIM_SET_PERIOD(x)             ( ( HW_STEPPER2_TIM->ARR ) = (x))
#define HW_STEPPER2_TIM_UPDATE()                 HW_STEPPER2_TIM->EGR = TIM_EGR_UG



#define HW_STEPPER2_UART          UART5
#define HW_STEPPER2_BAUDRATE      115200
#define HW_STEPPER2_WORDLENGTH    UART_WORDLENGTH_8B
#define HW_STEPPER2_PARITY        UART_PARITY_NONE
#define HW_STEPPER2_STOPBITS      UART_STOPBITS_1

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* TARGETSPECIFIC_HWSTEPPERCONFIG_H_ */
