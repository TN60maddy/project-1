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
*   This file is the interface for the implementation of Quadrature Encoder used
*   to detect the position, direction, and speed of rotation of a shaft connected
*   to the peristaltic mechanism of Infusion Pump
*
********************************************************************************/

#include "stm32h7xx_hal.h"
#include "HwQuadEncoder.h"
#include "HwQuadEncoderConfig.h"
#include "stm32h7xx_hal_tim.h"
#include "stdio.h"

/**
*  Private Defines
*/
#define HW_QUAD_ENC_TIM_CLOCK ( 1000000UL )
#define HW_QUAD_ENC_DEFAULT_PRESCALE ( ( unsigned long ) SystemCoreClock/ HW_QUAD_ENC_TIM_CLOCK  - 1UL )
#define HW_QUAD_ENC_DEFAULT_PERIOD_VALUE  ( 1000-1)

/**
* Private Data
*/
static TIM_HandleTypeDef HwQuadTimHandle_;

static volatile uint32_t pulseCount = 0;            // Count pulses in 1 sec
static volatile uint32_t ppsValue   = 0;            // Store PPS value
static uint8_t lastStateA = 0;
static uint8_t lastStateB = 0;

/**
*  Private Methods/Functions
*/

static uint8_t HwQuadEncoder_ReadChannelA(void);
static uint8_t HwQuadEncoder_ReadChannelB(void);

/**
  * @brief Quadrature Encoder HW Interface Initialization
  *        This function is to initialize the underlying HAL
  *        to configure peripherals like GPIO,Timer/Encoder
  * @param None
  *
  * @retval int 0 if Successful else error code in negative sign
  */
int HwQuadEncoderInit( void )
{
		int retStatus = 0;
		TIM_OC_InitTypeDef sConfigOC = {0};
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		/*
		* Initialize the HW modules for Optical Sensor interface like PWM output,
		*/
		HW_QUAD_ENC_TIM_CLK_ENABLE();

		HwQuadTimHandle_.Instance = HW_QUAD_ENC_TIM;
		HwQuadTimHandle_.Init.Prescaler = HW_QUAD_ENC_DEFAULT_PRESCALE;
		HwQuadTimHandle_.Init.CounterMode = TIM_COUNTERMODE_UP;
		HwQuadTimHandle_.Init.Period = HW_QUAD_ENC_DEFAULT_PERIOD_VALUE;
		HwQuadTimHandle_.Init.ClockDivision = 0;
		if (HAL_TIM_OC_Init(&HwQuadTimHandle_) != HAL_OK)
		{
		retStatus = -1;
		}
		sConfigOC.OCMode = TIM_OCMODE_TIMING;
		sConfigOC.Pulse = 0;
		sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
		sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
		
		
		/* TIM1 interrupt Init */
		HAL_NVIC_SetPriority(TIM1_UP_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
		__HAL_TIM_ENABLE_IT(&HwQuadTimHandle_, TIM_IT_UPDATE);
		HAL_TIM_Base_Start_IT(&HwQuadTimHandle_);

		if (HAL_TIM_OC_ConfigChannel(&HwQuadTimHandle_, &sConfigOC, HW_QUAD_ENC_TIM_CHN) != HAL_OK)
		{
			retStatus = -1;
		} 
		else
		{
		HW_QUAD_ENC_GPIOA_CLK_ENABLE();
		HW_QUAD_ENC_GPIOB_CLK_ENABLE();

		/*Configure GPIO pin : HW_QUAD_ENC_A_PIN_Pin */
		GPIO_InitStruct.Pin = HW_QUAD_ENC_A_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(HW_QUAD_ENC_A_PORT, &GPIO_InitStruct);

		/*Configure GPIO pin : HW_QUAD_ENC_B_PIN_Pin */
		GPIO_InitStruct.Pin = HW_QUAD_ENC_B_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(HW_QUAD_ENC_B_PORT, &GPIO_InitStruct);

		/* Enable & Set Priority for EXTI interrupts in NVIC */
		HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
		}
		return retStatus;
}



/**
  * @brief Read the gpio Value.
  *
  * @param void
  *
  * @retval gpio value.
  *
  */
  
 static uint8_t HwQuadEncoder_ReadChannelA(void)
{
	return HAL_GPIO_ReadPin(HW_QUAD_ENC_A_PORT, HW_QUAD_ENC_A_PIN);
} 

/**
  * @brief Read the gpio Value.
  *
  * @param void
  *
  * @retval gpio value.
  *
  */

static uint8_t HwQuadEncoder_ReadChannelB(void)
{
	return HAL_GPIO_ReadPin(HW_QUAD_ENC_B_PORT, HW_QUAD_ENC_B_PIN);
}

/**
  * @brief Starts the quadrature encoder timer with interrupt mode.
  *
  * @param void
  *
  * @retval int Returns 0 on success, or a HAL error code if the operation fails.
  */

int HwQuadEncoderStart( void )
{
	return(HAL_TIM_OC_Start_IT(&HwQuadTimHandle_, HW_QUAD_ENC_TIM_CHN));
}

/**
  * @brief Stops the quadrature encoder timer.
  *
  * @param void
  *
  * @retval int Returns 0 on success, or a HAL error code if the operation fails.
  */
int HwQuadEncoderStop( void )
{
    return (HAL_TIM_OC_Stop_IT(&HwQuadTimHandle_, HW_QUAD_ENC_TIM_CHN));
}

/**
  * @brief Reads the current position, direction, and speed of the encoder.
  *
  * @param psValues Pointer to the structure where the encoder values will be stored.
  *
  * @retval int Returns 0 on success, or -1 if the input pointer is NULL.
  */
int HwQuadEncoderRead(HwPQuadEncoderValues_s *psValues)
{
    if (psValues == NULL)
    {
        return -1; // Error: Null pointer
    }

    uint8_t channelA = HwQuadEncoder_ReadChannelA();
    uint8_t channelB = HwQuadEncoder_ReadChannelB();

    // Detect Position
    if (channelA && channelB) {
        psValues->Pos = HW_QUADENCODER_POS_1AND2;
    } else if (channelA) {
        psValues->Pos = HW_QUADENCODER_POS_1;
    } else if (channelB) {
        psValues->Pos = HW_QUADENCODER_POS_2;
    } else {
        psValues->Pos = HW_QUADENCODER_POS_NONE;
    }

    // Detect Direction
    if (lastStateA == 0 && channelA == 1 && channelB == 0) {
        psValues->Direction  = HW_QUADENCODER_DIR_FWD;
    } else if (lastStateB == 0 && channelB == 1 && channelA == 0) {
        psValues->Direction  = HW_QUADENCODER_DIR_REV;
    }

    /* Update the Pulse Per Second */
    psValues->SpeedInPulsesPerSec = ppsValue;  // Use global variable

    /* Update the last states */
    lastStateA = channelA;
    lastStateB = channelB;

    return 0;
}



/**
  * @brief This function handles TIM1 update interrupt.
  */
void TIM1_UP_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&HwQuadTimHandle_);
}

/**
  * @brief EXTI Handler for GPIO Pins.
  */

void EXTI9_5_IRQHandler(void)
{  
  HAL_GPIO_EXTI_IRQHandler(HW_QUAD_ENC_B_PIN);      // Handle Quad GPIOB
  HAL_GPIO_EXTI_IRQHandler(HW_QUAD_ENC_A_PIN);      // Handle Quad GPIOA

}

/**
  * @brief GPIO Interrupt Callback function .
  */

void HwQuadEncoder_incrementPulses(uint16_t GPIO_Pin)
{

		pulseCount++;                                               // Count pulses per second

}

/**
  * @brief TIMER 1 Callback function.
  */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)  			                        // Assuming TIM1 is used
    {
        ppsValue = pulseCount; 				                       // Store PPS value
        pulseCount = 0;        				                       // Reset for the next second
    }
}








