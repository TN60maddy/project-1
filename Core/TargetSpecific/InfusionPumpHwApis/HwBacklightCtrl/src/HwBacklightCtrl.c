/*******************************************************************************
*
*    INFUSION PUMP PROJECT
*
*                                    Copyright (c) Aria Innovations
*
*
********************************************************************************
*
* DESCRIPTION:
*   This file implements a generic HW Interface LCD Back Light used in Infusion Pump
*
********************************************************************************/
#include "stm32h7xx_hal.h"
#include "HwBacklightConfig.h"
#include "HwBacklightCtrl.h"

#define HW_BACKLIGHT_TIM_CLOCK (100UL)
#define HW_BACKLIGHT_CRTL_DEFAULT_PRESCALE  (((( unsigned long ) SystemCoreClock/ 1000000 ) ) - 1)
#define HW_BACKLIGHT_CRTL_DEFAULT_PULSE_VALUE ( 0 )
#define HW_BACKLIGHT_CRTL_DEFAULT_PERIOD_VALUE (100)
#define HW_BACKLIGHT_FIXED_DUTY_CYCLE_USEC (10)

/**
* Private Data
*/

static TIM_HandleTypeDef    HwBacklightCrtlTimHandle_;
static TIM_OC_InitTypeDef   HwBacklightCrtlTimConfig_;


/**
  * @brief
  *         Initializes the LCD backlight control pin as a Timer PWM (Pulse Width Modulation) channel.
  * @param void.
  *
  *
  * @retval   0  = Success
  *          -1  = Failure
  */
int HwBacklightCtrlInit(void)
{
	int retStatus = 0;
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* Enable Stepper 1 GPIO Clock & TIM Clock */
	HW_BACKLIGHT_TIM_CHANNEL_GPIO_CLK_ENABLE();
	HW_BACKLIGHT_TIM_CLK_ENABLE();
	/*
	 * Initialize Timer and PWM channel for Stepper Motor 1
	 */
	HwBacklightCrtlTimHandle_.Instance  = HW_BACKLIGHT_TIM;

	HwBacklightCrtlTimHandle_.Init.Prescaler         = HW_BACKLIGHT_CRTL_DEFAULT_PRESCALE;
	HwBacklightCrtlTimHandle_.Init.Period            = HW_BACKLIGHT_CRTL_DEFAULT_PERIOD_VALUE;
	HwBacklightCrtlTimHandle_.Init.ClockDivision     = 0;
	HwBacklightCrtlTimHandle_.Init.CounterMode       = TIM_COUNTERMODE_UP;
	HwBacklightCrtlTimHandle_.Init.RepetitionCounter = 0;

	if (HAL_TIM_PWM_Init(&HwBacklightCrtlTimHandle_) != HAL_OK )
	{
		/* Initialization Error */
		retStatus = -1;
	}
	else
	{
		HwBacklightCrtlTimConfig_.OCMode       = TIM_OCMODE_PWM1;
		HwBacklightCrtlTimConfig_.OCPolarity   = TIM_OCPOLARITY_HIGH;
		HwBacklightCrtlTimConfig_.OCFastMode   = TIM_OCFAST_DISABLE;
		HwBacklightCrtlTimConfig_.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
		HwBacklightCrtlTimConfig_.OCNIdleState = TIM_OCNIDLESTATE_RESET;

		HwBacklightCrtlTimConfig_.OCIdleState  = TIM_OCIDLESTATE_RESET;

		/* Set the pulse value for channel */
		HwBacklightCrtlTimConfig_.Pulse = HW_BACKLIGHT_CRTL_DEFAULT_PULSE_VALUE;
		if ( HAL_TIM_PWM_ConfigChannel(&HwBacklightCrtlTimHandle_,
				&HwBacklightCrtlTimConfig_, HW_BACKLIGHT_PWM_CHANNEL) != HAL_OK )
		{
			/* Configuration Error */
			retStatus = -1;
		}
		else
		{
			/*
			 *  Configure Output Pin for PWM
			 */
			GPIO_InitStruct.Pin = HW_BACKLIGHT_TIM_GPIO_PIN_CHANNEL1;
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			GPIO_InitStruct.Alternate = HW_BACKLIGHT_TIM_GPIO_AF_CHANNEL1;
			HAL_GPIO_Init( HW_BACKLIGHT_TIM_GPIO_PORT_CHANNEL1, &GPIO_InitStruct);
		}
	}
	return retStatus;
}

/**
  * @brief
  *       This function turns ON the LCD backlight by controlling the backlight control pin.
  *       It sets the appropriate hardware signal to enable the backlight.
  * @param void.
  *
  *
  * @retval  0  = Success
  *         -1  = Failure
  */

int HwBacklightCtrlON(void)
{
	int retStatus = 0;
	if (HAL_TIM_PWM_Start(&HwBacklightCrtlTimHandle_,HW_BACKLIGHT_PWM_CHANNEL ) != HAL_OK )
	{
		/* PWM Start Error */
		retStatus = -1;
	}
	return retStatus;
}
/**
  * @brief
  *       This function turns OFF the LCD backlight by controlling the backlight control pin.
  *       It sets the appropriate hardware signal to disable the backlight.
  * @param void.
  *
  *
  * @retval  0  = Success
  *         -1  = Failure
  */

int HwBacklightCtrlOFF(void)
{
	int retStatus = 0;

	if ( HAL_TIM_PWM_Stop(&HwBacklightCrtlTimHandle_,
			HW_BACKLIGHT_PWM_CHANNEL ) != HAL_OK)
	{
		/* PWM Stop Error */
		retStatus = -1;
	}
	return retStatus;
}
/**
  * @brief
  *        This function configures the hardware to generate a PWM signal, which is used to control
  *        the brightness of the LCD backlight. The PWM duty cycle can be adjusted to vary the
  *        backlight intensity.
  *
  * @param enum HwBLIntensityLevel_t
  *
  *  @retval  0  = Success
  *          -1  = Failure
  *
  */

int HwBacklightCtrlSetIntensity(HwBLIntensityLevel_t Level)
{
	int retStatus = 0;
	uint8_t Intensity;

/*  To set the Configured dutyctycle  */
	if(Level < HW_BL_INTENSITY_MAX )
	{
		Intensity = (Level * 10);
		HW_BACKLIGHT_TIM_SET_DUTYCYCLE( Intensity );
	}
	else
	{
		retStatus = -1;
	}
	return retStatus;
}
