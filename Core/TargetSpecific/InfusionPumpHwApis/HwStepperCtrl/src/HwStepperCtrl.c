/*******************************************************************************
*
*    INFUSION PUMP PROJECT
*
*                                    Copyright (c) Aria Innovations
*                                    written by RK
*
*
********************************************************************************
*
* DESCRIPTION:
*   This file implements a generic HW Interface Stepper Motors used in Infusion Pump
*
********************************************************************************/

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_tim.h"
#include "HwStepperConfig.h"
#include "HwStepperCtrl.h"



/**
*  Private Defines
*/
#define HW_STEPPER_PPS_MAX ( 100000 )
#define HW_STEPPER_CRTL_DEFAULT_PULSE_VALUE ( 0 )
#define HW_STEPPER_CRTL_DEFAULT_PERIOD_VALUE ( 100 )
#define HW_STEPPER_PPS_IS_VALID( x )( ( 0 < x ) && ( HW_STEPPER_PPS_MAX >= x ) )
#define HW_STEPPER_FIXED_DUTY_CYCLE_USEC ( 5 )

/**
* Private Data
*/
static TIM_HandleTypeDef    HwStepper1CrtlTimHandle_;
static TIM_OC_InitTypeDef   HwStepper1CrtlTimConfig_;

static TIM_HandleTypeDef    HwStepper2CrtlTimHandle_;
static TIM_OC_InitTypeDef   HwStepper2CrtlTimConfig_;
static TIM_BreakDeadTimeConfigTypeDef HwStepper2CrtlDeadTimConfig_ = {0};



UART_HandleTypeDef HwStepper1UartHandle_;
UART_HandleTypeDef HwStepper2UartHandle_;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart5;
extern void Hw_StepperMtr_CurCtrl(UART_HandleTypeDef *HwStpUartHand);


/**
  * @brief Stepper Motor 1 GPIO Pin Initialization
  *        This function is used to Initialize the Stepper 1 GPIO Pins.
  *
  * @param void
  *
  *
  * @retval void
  */

static void Stepper1_Gpio_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int HwStepperChangePps( HwStepperNum_t stpr, unsigned int pps  )
{
	int retStatus = 0;
	    unsigned long int calculatedPeriod_us = 0;
	    unsigned long int dutyCycle_us = HW_STEPPER_FIXED_DUTY_CYCLE_USEC;

		if( HW_STEPPER_PPS_IS_VALID( pps ) )
		{

				calculatedPeriod_us = ( unsigned long int ) ( ( float )( ( HW_STEPPER_TIM_CLOCK * 1.0 ) / ( ( float ) pps ) ) ) ;

				switch( stpr )
				{
				case HW_STEPPER_NUM_1:

					HW_STEPPER1_TIM_SET_DUTYCYCLE( dutyCycle_us );
	                HW_STEPPER1_TIM_SET_PERIOD( calculatedPeriod_us - 1 );
	                HW_STEPPER2_TIM_UPDATE( );

					break;
				case HW_STEPPER_NUM_2:

					HW_STEPPER2_TIM_SET_DUTYCYCLE( dutyCycle_us );
					HW_STEPPER2_TIM_SET_PERIOD( calculatedPeriod_us - 1 );
				    /*  Control Stepper Motor 2 Current */
					HW_STEPPER2_TIM_UPDATE( );
					break;
				default:
					retStatus = -1;
				}
			}

		return retStatus;

}
/**
  * @brief Stepper Motor 2 GPIO Pin Initialization
  *        This function is used to Initialize the Stepper 2 GPIO Pins.
  *
  * @param void
  *
  *
  * @retval void
  */

static void Stepper2_Gpio_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStruct = {0};

   /* Peripheral clock enable */
    __HAL_RCC_UART5_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**UART5 GPIO Configuration
    PC12     ------> UART5_TX
    PD2     ------> UART5_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  }






/**
  * @brief
  *        Initializes the stepper motor peripherals and UART for the specified stepper motor.
  *        This function configures the necessary hardware (e.g., GPIOs, timers, UART) to control
  *        the specified stepper motor.
  * @param hwStpr
  *        The stepper motor to initialize, specified as a value of type `HwStepperNum_t`.
  *        Valid values are:
  *        - HW_STEPPER_NUM_1: Initialize stepper motor 1.
  *        - HW_STEPPER_NUM_2: Initialize stepper motor 2.
  *  * @retval int
  *         0 = Success (Stepper motor initialized successfully).
  *         1 = Failure (Initialization failed).
  */

int HwStepperCtrlInit( HwStepperNum_t hwStpr )
{
	int retStatus = 0;
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
	Stepper1_Gpio_Init();

	/*
	 * Initialize the HW modules for each Stepper Motor interface like PWM output,
	 */
	switch( hwStpr )
	{
	case HW_STEPPER_NUM_1:
		//MX_USART2_UART_Init();

		/* Enable Stepper 1 GPIO Clock & TIM Clock */
		HW_STEPPER1_TIM_CHANNEL_GPIO_CLK_ENABLE();
		HW_STEPPER1_TIM_CLK_ENABLE();

		  /*
		   * Configure GPIO for Stepper1 Direction
		   */
		  GPIO_InitStruct.Pin = HW_STEPPER1_DIR_GPIO_PIN;
		  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		  HAL_GPIO_Init( HW_STEPPER1_DIR_GPIO_PORT, &GPIO_InitStruct );

		  /*
		   * Configure GPIO for Stepper1 Enable
		   */
		  GPIO_InitStruct.Pin = HW_STEPPER1_TIM_GPIO_PIN_CHANNEL1;
		  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		  HAL_GPIO_Init( HW_STEPPER1_TIM_GPIO_PORT_CHANNEL1, &GPIO_InitStruct );

		  /*
		   * Initialize Timer and PWM channel for Stepper Motor 1
		   */


		  HwStepper1CrtlTimHandle_.Instance  = HW_STEPPER1_TIM;

		  HwStepper1CrtlTimHandle_.Init.Prescaler         = HW_STEPPER_CRTL_DEFAULT_PRESCALE;
		  HwStepper1CrtlTimHandle_.Init.Period            = HW_STEPPER_CRTL_DEFAULT_PERIOD_VALUE;
		  HwStepper1CrtlTimHandle_.Init.ClockDivision     = 0;
		  HwStepper1CrtlTimHandle_.Init.CounterMode       = TIM_COUNTERMODE_UP;
		  HwStepper1CrtlTimHandle_.Init.RepetitionCounter = 0;

		  if (HAL_TIM_PWM_Init(&HwStepper1CrtlTimHandle_) != HAL_OK )
		  {
		    /* Initialization Error */
			  retStatus = -1;
		  }
		  else
		  {
			  HwStepper1CrtlTimConfig_.OCMode       = TIM_OCMODE_PWM1;
			  HwStepper1CrtlTimConfig_.OCPolarity   = TIM_OCPOLARITY_HIGH;
			  HwStepper1CrtlTimConfig_.OCFastMode   = TIM_OCFAST_DISABLE;
			  HwStepper1CrtlTimConfig_.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
			  HwStepper1CrtlTimConfig_.OCNIdleState = TIM_OCNIDLESTATE_RESET;

			  HwStepper1CrtlTimConfig_.OCIdleState  = TIM_OCIDLESTATE_RESET;

			  /* Set the pulse value for channel */
					  HwStepper1CrtlTimConfig_.Pulse = HW_STEPPER_CRTL_DEFAULT_PULSE_VALUE;
				  if ( HAL_TIM_PWM_ConfigChannel(&HwStepper1CrtlTimHandle_,
						  &HwStepper1CrtlTimConfig_, HW_STEPPER1_PWM_CHANNEL) != HAL_OK )
				  {
					/* Configuration Error */
					  retStatus = -1;
				  }
				  else
				  {
					  /*
					   * Configure Output Pin for PWM
					   */

					  GPIO_InitStruct.Pin = HW_STEPPER1_TIM_GPIO_PIN_CHANNEL1;
					  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
					  GPIO_InitStruct.Pull = GPIO_NOPULL;
					  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
					  GPIO_InitStruct.Alternate = HW_STEPPER1_TIM_GPIO_AF_CHANNEL1;
					  HAL_GPIO_Init( HW_STEPPER1_TIM_GPIO_PORT_CHANNEL1, &GPIO_InitStruct);
				  }

		  }
#if 1
		  /* UART Initialization for Stepper Motor */
		  HwStepper1UartHandle_.Instance = HW_STEPPER1_UART;
		  HwStepper1UartHandle_.Init.BaudRate = HW_STEPPER1_BAUDRATE;
		  HwStepper1UartHandle_.Init.WordLength = HW_STEPPER1_WORDLENGTH;
		  HwStepper1UartHandle_.Init.StopBits = HW_STEPPER1_STOPBITS;
		  HwStepper1UartHandle_.Init.Parity = HW_STEPPER1_PARITY;
		  HwStepper1UartHandle_.Init.Mode = UART_MODE_TX_RX;
		  HwStepper1UartHandle_.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		  HwStepper1UartHandle_.Init.OverSampling = UART_OVERSAMPLING_16;
		  HwStepper1UartHandle_.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
		  HwStepper1UartHandle_.Init.ClockPrescaler = UART_PRESCALER_DIV1;
		  HwStepper1UartHandle_.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
		  if (HAL_UART_Init(&HwStepper1UartHandle_) != HAL_OK)
		  {
			  retStatus = -1;
		  }
		  else
		  {
		  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART2;
		  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
		  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		  {
			  retStatus = -1;
		  }

		  }

		  if (HAL_UARTEx_SetTxFifoThreshold(&HwStepper1UartHandle_, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
		  {
			  retStatus = -1;
		  }
		  if (HAL_UARTEx_SetRxFifoThreshold(&HwStepper1UartHandle_, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
		  {
			  retStatus = -1;
		  }
		  if (HAL_UARTEx_DisableFifoMode(&HwStepper1UartHandle_) != HAL_OK)
		  {
			  retStatus = -1;
		  }
#endif
break;

	case HW_STEPPER_NUM_2:
		/* Enable Stepper 1 GPIO Clock & TIM Clock */
	//MX_UART5_Init();
		Stepper2_Gpio_Init();
	HW_STEPPER2_TIM_CHANNEL_GPIO_CLK_ENABLE();
	HW_STEPPER2_TIM_CLK_ENABLE();

	/*
	* Configure GPIO for Stepper1 Direction
	*/
	GPIO_InitStruct.Pin = HW_STEPPER2_DIR_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init( HW_STEPPER2_DIR_GPIO_PORT, &GPIO_InitStruct );

	/*
	* Configure GPIO for Stepper1 Enable
	*/
	GPIO_InitStruct.Pin = HW_STEPPER2_EN_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init( HW_STEPPER2_EN_GPIO_PORT, &GPIO_InitStruct );

	/*
	* Initialize Timer and PWM channel for Stepper Motor 1
	*/


	HwStepper2CrtlTimHandle_.Instance  = HW_STEPPER2_TIM;

	HwStepper2CrtlTimHandle_.Init.Prescaler         = HW_STEPPER_CRTL_DEFAULT_PRESCALE;
	HwStepper2CrtlTimHandle_.Init.Period            = HW_STEPPER_CRTL_DEFAULT_PERIOD_VALUE;
	HwStepper2CrtlTimHandle_.Init.ClockDivision     = 0;
	HwStepper2CrtlTimHandle_.Init.CounterMode       = TIM_COUNTERMODE_UP;
	HwStepper2CrtlTimHandle_.Init.RepetitionCounter = 0;
	HwStepper2CrtlTimHandle_.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
		if (HAL_TIM_PWM_Init(&HwStepper2CrtlTimHandle_) != HAL_OK )
		{
		/* Initialization Error */
		retStatus = -1;
		}
		else
		{
		HwStepper2CrtlTimConfig_.OCMode       = TIM_OCMODE_PWM1;
		HwStepper2CrtlTimConfig_.OCPolarity   = TIM_OCPOLARITY_HIGH;
		HwStepper2CrtlTimConfig_.OCFastMode   = TIM_OCFAST_DISABLE;
		HwStepper2CrtlTimConfig_.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
		HwStepper2CrtlTimConfig_.OCNIdleState = TIM_OCNIDLESTATE_RESET;

		HwStepper2CrtlTimConfig_.OCIdleState  = TIM_OCIDLESTATE_RESET;

		/* Set the pulse value for channel */
		HwStepper2CrtlTimConfig_.Pulse = HW_STEPPER_CRTL_DEFAULT_PULSE_VALUE;
			if ( HAL_TIM_PWM_ConfigChannel(&HwStepper2CrtlTimHandle_,
			&HwStepper2CrtlTimConfig_, HW_STEPPER2_PWM_CHANNEL) != HAL_OK )
			{
			/* Configuration Error */
			retStatus = -1;
			}
			else
			{
			HwStepper2CrtlDeadTimConfig_.OffStateRunMode = TIM_OSSR_DISABLE;
			HwStepper2CrtlDeadTimConfig_.OffStateIDLEMode = TIM_OSSI_DISABLE;
			HwStepper2CrtlDeadTimConfig_.LockLevel = TIM_LOCKLEVEL_OFF;
			HwStepper2CrtlDeadTimConfig_.DeadTime = 0;
			HwStepper2CrtlDeadTimConfig_.BreakState = TIM_BREAK_DISABLE;
			HwStepper2CrtlDeadTimConfig_.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
			HwStepper2CrtlDeadTimConfig_.BreakFilter = 0;
			HwStepper2CrtlDeadTimConfig_.Break2State = TIM_BREAK2_DISABLE;
			HwStepper2CrtlDeadTimConfig_.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
			HwStepper2CrtlDeadTimConfig_.Break2Filter = 0;
			HwStepper2CrtlDeadTimConfig_.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
				if (HAL_TIMEx_ConfigBreakDeadTime(&HwStepper2CrtlTimHandle_,
				&HwStepper2CrtlDeadTimConfig_) != HAL_OK)
				{
				retStatus = -1;
				}
				else
				{
				//__HAL_RCC_GPIOC_CLK_ENABLE();
				/*
				* Configure Output Pin for PWM
				*/

				GPIO_InitStruct.Pin = HW_STEPPER2_TIM_GPIO_PIN_CHANNEL2;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Pull = GPIO_NOPULL;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				GPIO_InitStruct.Alternate = HW_STEPPER2_TIM_GPIO_AF_CHANNEL2;
				HAL_GPIO_Init( HW_STEPPER2_TIM_GPIO_PORT_CHANNEL2,&GPIO_InitStruct);
				}
				}
				}



					/* UART Initialization for Stepper 2 */
					HwStepper2UartHandle_.Instance = HW_STEPPER2_UART;
					HwStepper2UartHandle_.Init.BaudRate = HW_STEPPER2_BAUDRATE;
					HwStepper2UartHandle_.Init.WordLength = HW_STEPPER2_WORDLENGTH;
					HwStepper2UartHandle_.Init.StopBits = HW_STEPPER2_STOPBITS;
					HwStepper2UartHandle_.Init.Parity = HW_STEPPER2_PARITY;
					HwStepper2UartHandle_.Init.Mode = UART_MODE_TX_RX;
					HwStepper2UartHandle_.Init.HwFlowCtl = UART_HWCONTROL_NONE;
					HwStepper2UartHandle_.Init.OverSampling = UART_OVERSAMPLING_16;
					HwStepper2UartHandle_.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
					HwStepper2UartHandle_.Init.ClockPrescaler = UART_PRESCALER_DIV1;
					HwStepper2UartHandle_.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
					if (HAL_UART_Init(&HwStepper2UartHandle_) != HAL_OK)
					{
					retStatus = -1;
					}
					else
					{
					PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART5;
					PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
					if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
					{
					retStatus = -1;
					}

		           }
					if (HAL_UARTEx_SetTxFifoThreshold(&HwStepper2UartHandle_, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
					{
					retStatus = -1;
					}
					if (HAL_UARTEx_SetRxFifoThreshold(&HwStepper2UartHandle_, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
					{
					retStatus = -1;
					}
					if (HAL_UARTEx_DisableFifoMode(&HwStepper2UartHandle_) != HAL_OK)
					{
					retStatus = -1;
					}


		break;
	default:
		retStatus = -1;
	}

	return retStatus;
}

/**
  * @brief Stepper Interface For Stop
  *        This function is used to stop the stop the specified stepper Motor
  *
  * @param enum HwStepperNum_t
  *
  *
  * @retval int 0 if Successful else error code in negative sign
  */

int HwStepperCtrlStop( HwStepperNum_t stpr )
{
	int retStatus = 0;

	switch( stpr )
	{
	case HW_STEPPER_NUM_1:
		if ( HAL_TIM_PWM_Stop(&HwStepper1CrtlTimHandle_, HW_STEPPER1_PWM_CHANNEL ) != HAL_OK)
		  {
		    /* PWM Stop Error */
			retStatus = -1;
		  }
		else
		{
			HAL_GPIO_WritePin(HW_STEPPER1_EN_GPIO_PORT, HW_STEPPER1_EN_GPIO_PIN, GPIO_PIN_RESET);
		}
		break;
	case HW_STEPPER_NUM_2:
		if ( HAL_TIM_PWM_Stop(&HwStepper2CrtlTimHandle_, HW_STEPPER2_PWM_CHANNEL ) != HAL_OK)
		  {
			/* PWM Stop Error */
			retStatus = -1;
		  }
		else
		{
			HAL_GPIO_WritePin(HW_STEPPER2_EN_GPIO_PORT, HW_STEPPER2_EN_GPIO_PIN, GPIO_PIN_RESET );
		}
		break;
	default:
		retStatus = -1;
	break;
	}
	return retStatus;
}
/**
  * @brief Stepper Interface For Configuration
  *        This function is used to stop the specified stepper Motor
  *
  * @param enum HwStepperNum_t, enum HwStepperDir_t dir, unsigned int pps
  *
  *
  * @retval int 0 if Successful else error code in negative sign
  */

int HwStepperCtrlConfigure( HwStepperNum_t stpr,HwStepperDir_t dir, unsigned int pps  )
{
	int retStatus = 0;
    unsigned long int calculatedPeriod_us = 0;
    unsigned long int dutyCycle_us = HW_STEPPER_FIXED_DUTY_CYCLE_USEC;

	if( HW_STEPPER_PPS_IS_VALID( pps ) )
	{

		if( (  HW_STEPPER_DIR_FWD == dir )|| ( HW_STEPPER_DIR_REV == dir ) )
		{
			calculatedPeriod_us = ( unsigned long int ) ( ( float )( ( HW_STEPPER_TIM_CLOCK * 1.0 ) / ( ( float ) pps ) ) ) ;

			switch( stpr )
			{
			case HW_STEPPER_NUM_1:
                                HAL_GPIO_WritePin(HW_STEPPER1_DIR_GPIO_PORT,
                                            HW_STEPPER1_DIR_GPIO_PIN,
                                            (dir == HW_STEPPER_DIR_FWD)? GPIO_PIN_RESET: GPIO_PIN_SET );
				HW_STEPPER1_TIM_SET_DUTYCYCLE( dutyCycle_us );
                                HW_STEPPER1_TIM_SET_PERIOD( calculatedPeriod_us - 1 );
                                /*  Control Stepper Motor 1 Current */
                                Hw_StepperMtr_CurCtrl(&HwStepper1UartHandle_);


				break;
			case HW_STEPPER_NUM_2:
				HAL_GPIO_WritePin(HW_STEPPER2_DIR_GPIO_PORT, HW_STEPPER2_DIR_GPIO_PIN,
                                                  (dir == HW_STEPPER_DIR_FWD)? GPIO_PIN_RESET: GPIO_PIN_SET );
				HW_STEPPER2_TIM_SET_DUTYCYCLE( dutyCycle_us );
				HW_STEPPER2_TIM_SET_PERIOD( calculatedPeriod_us - 1 );
			    /*  Control Stepper Motor 2 Current */
				Hw_StepperMtr_CurCtrl(&HwStepper2UartHandle_);
				break;
			default:
				retStatus = -1;
			}
		}
	}else
	{
		retStatus = -1;
	}
	return retStatus;
}

/**
  * @brief Stepper Interface For Start
  *        This function is used to used to start rotating particular stepper motor with
  *        already configured parameters like speed and direction.
  *
  * @param enum HwStepperNum_t
  *
  *
  * @retval int 0 if Successful else error code in negative sign
  */

int HwStepperCtrlStart( HwStepperNum_t stpr )
{
	int retStatus = 0;

	switch( stpr )
	{
	case HW_STEPPER_NUM_1:
		if (HAL_TIM_PWM_Start(&HwStepper1CrtlTimHandle_,
				HW_STEPPER1_PWM_CHANNEL ) != HAL_OK )
		{
			/* PWM Start Error */
			retStatus = -1;
		}
		else
		{
			HAL_GPIO_WritePin(HW_STEPPER1_EN_GPIO_PORT, HW_STEPPER1_EN_GPIO_PIN, GPIO_PIN_SET );

		}
		break;

	case HW_STEPPER_NUM_2:
		if (HAL_TIM_PWM_Start(&HwStepper2CrtlTimHandle_,
						HW_STEPPER2_PWM_CHANNEL ) != HAL_OK )
		{
			/* PWM Start Error */
			retStatus = -1;
		}
		else
		{
			HAL_GPIO_WritePin(HW_STEPPER2_EN_GPIO_PORT, HW_STEPPER2_EN_GPIO_PIN, GPIO_PIN_SET );
		}
		break;
	default:
		retStatus = -1;
	}
	return retStatus;
}




