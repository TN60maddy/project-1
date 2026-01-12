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
*   This file implements a generic HW Interface of Buzzer used in Infusion Pump
*
********************************************************************************/
#include "stm32h7xx_hal.h"
#include "HwBuzzerConfig.h"
#include "HwBuzzerCtrl.h"

#define HW_BUZZER_TIM_CLOCK (100UL)
#define HW_BUZZER_CRTL_DEFAULT_PRESCALE  (((( unsigned long ) SystemCoreClock/ 1000000 ) ) - 1)
#define HW_BUZZER_CRTL_DEFAULT_PULSE_VALUE ( 0 )
#define HW_BUZZER_CRTL_DEFAULT_PERIOD_VALUE (500-1)
#define HW_BUZZER_FIXED_DUTY_CYCLE_USEC (10)

/**
* Private Data
*/

static TIM_HandleTypeDef    HwBuzzerCrtlTimHandle_;
static TIM_OC_InitTypeDef   HwBuzzerCrtlTimConfig_;

/**
  * @brief
  *        Initializes the Buzzer control pin as a Timer PWM (Pulse Width Modulation) channel.
  *        This function configures the buzzer control pin to generate a PWM signal with a frequency of 2 kHz
  *        and a duty cycle of 50%.
  * @param void
  * @retval int
  *         0  = Success (Buzzer control pin initialized successfully as a PWM channel).
  *         -1 = Failure (Failed to initialize the buzzer control pin as a PWM channel).
  */

int HwBuzzerCtrlInit(void)
{
	int retStatus = 0;
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* Enable Stepper 1 GPIO Clock & TIM Clock */
	HW_BUZZER_TIM_CHANNEL_GPIO_CLK_ENABLE();
	HW_BUZZER_TIM_CLK_ENABLE();
	/*
	 * Initialize Timer and PWM channel for Stepper Motor 1
	 */
	HwBuzzerCrtlTimHandle_.Instance  = HW_BUZZER_TIM;
	HwBuzzerCrtlTimHandle_.Init.Prescaler = HW_BUZZER_CRTL_DEFAULT_PRESCALE;
	HwBuzzerCrtlTimHandle_.Init.Period            = HW_BUZZER_CRTL_DEFAULT_PERIOD_VALUE;
	HwBuzzerCrtlTimHandle_.Init.ClockDivision     = 0;
	HwBuzzerCrtlTimHandle_.Init.CounterMode       = TIM_COUNTERMODE_UP;
	HwBuzzerCrtlTimHandle_.Init.RepetitionCounter = 0;

	if (HAL_TIM_PWM_Init(&HwBuzzerCrtlTimHandle_) != HAL_OK )
	{
		/* Initialization Error */
		retStatus = -1;
	}
	else
	{
		HwBuzzerCrtlTimConfig_.OCMode       = TIM_OCMODE_PWM1;
		HwBuzzerCrtlTimConfig_.OCPolarity   = TIM_OCPOLARITY_HIGH;
		HwBuzzerCrtlTimConfig_.OCFastMode   = TIM_OCFAST_DISABLE;
		HwBuzzerCrtlTimConfig_.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
		HwBuzzerCrtlTimConfig_.OCNIdleState = TIM_OCNIDLESTATE_RESET;

		HwBuzzerCrtlTimConfig_.OCIdleState  = TIM_OCIDLESTATE_RESET;

		/* Set the pulse value for channel */
		HwBuzzerCrtlTimConfig_.Pulse = HW_BUZZER_CRTL_DEFAULT_PULSE_VALUE;
		if ( HAL_TIM_PWM_ConfigChannel(&HwBuzzerCrtlTimHandle_,
				&HwBuzzerCrtlTimConfig_, HW_BUZZER_PWM_CHANNEL) != HAL_OK )
		{
			/* Configuration Error */
			retStatus = -1;
		}
		else
		{
			/*
			 *  Configure Output Pin for PWM
			 */
			GPIO_InitStruct.Pin = HW_BUZZER_TIM_GPIO_PIN_CHANNEL1;
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			GPIO_InitStruct.Alternate = HW_BUZZER_TIM_GPIO_AF_CHANNEL1;
			HAL_GPIO_Init( HW_BUZZER_TIM_GPIO_PORT_CHANNEL1, &GPIO_InitStruct);
		}
	}
	return retStatus;
}

/**
  * @brief
  *       This function turns ON the Buzzer by Enabling the PWM Channel.
  * @param void.
  * @retval  0  = Success
  *         -1  = Failure
  */


int HwBuzzerCtrlON(HWBuzz_Vol_Ctrl val)
{
	int retStatus = 0;
	TIM3->CCR1 = val;
	if (HAL_TIM_PWM_Start(&HwBuzzerCrtlTimHandle_,HW_BUZZER_PWM_CHANNEL ) != HAL_OK )
	{
		/* PWM Start Error */
		retStatus = -1;
	}
	return retStatus;
}

/**
  * @brief
  *       This function turns OFF the Buzzer by Enabling the PWM Channel.
  * @param void.
  * @retval  0  = Success
  *         -1  = Failure
  */

int HwBuzzerCtrlOFF(void)
{
	int retStatus = 0;

	if ( HAL_TIM_PWM_Stop(&HwBuzzerCrtlTimHandle_,
			HW_BUZZER_PWM_CHANNEL ) != HAL_OK)
	{
		/* PWM Stop Error */
		retStatus = -1;
	}
	return retStatus;
}
