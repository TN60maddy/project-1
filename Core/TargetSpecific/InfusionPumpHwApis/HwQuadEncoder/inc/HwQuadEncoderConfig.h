
/*
 * HwQuadEncoderConfig.h
 */
#ifndef SRC_HWOPTICALSENSORCONFIG_H_
#define SRC_HWOPTICALSENSORCONFIG_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_tim.h"



#define HW_QUAD_ENC_A_PIN     		GPIO_PIN_7
#define HW_QUAD_ENC_B_PIN     		GPIO_PIN_5
#define HW_QUAD_ENC_A_PORT    		GPIOA
#define HW_QUAD_ENC_B_PORT    		GPIOB
#define HW_QUAD_ENC_GPIOA_CLK_ENABLE() 	__HAL_RCC_GPIOA_CLK_ENABLE();
#define HW_QUAD_ENC_GPIOB_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE();


#define HW_QUAD_ENC_TIM_CLK_ENABLE()    __HAL_RCC_TIM1_CLK_ENABLE(); 
#define HW_QUAD_ENC_TIM  				TIM1
#define HW_QUAD_ENC_TIM_CHN             TIM_CHANNEL_5                           
#define HW_QUAD_ENC_TIM_COUNT_MODE      TIM_COUNTERMODE_UP 
     


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#endif /* SRC_HWOPTICALSENSORCONFIG_H_ */
