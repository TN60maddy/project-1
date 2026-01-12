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
*   This file implements a generic HW Interface of Battery used in Infusion Pump
*
********************************************************************************/

#include "HwBattCtrl.h"
#include "HwBattCtrlConfig.h"
#include "HwFuelGauge.h"
#include "HwFuelGaugeConfig.h"

/* Privte Data */
/*  ADC Handlers */
/* ADC Handlers */
static ADC_HandleTypeDef HwVIN_Sense_adc_Handler;
static ADC_HandleTypeDef HwVIN_Sense12v_adc_Handler;

/* Private Declarations */
#define VOLTAGE_OFFSET 1.5
#define ADC_RESOLUTION 65535
#define ADC_REF_VOL 3.3

#define BATTERY_CAPACITY    2600
/** Charge termination current in mA */
#define BATTERY_CRG_TERM_I    49
#define BATTERY_V_EMPTY      (3000 / 10)
#define POWER_CHG_VOLTAGE    4200

/* Private function Declarations */
static uint8_t Hw_ReadPwrSrc_Adc(uint16_t *adcData);

/**
  * @brief
  *        Initializes the Battery Control Module.
  *        This function sets up the necessary hardware and configurations required for monitoring and controlling
  *        the battery.
  * @param void
  * @retval uint8_t
  *         0 = Success (Battery Control Module initialized successfully)
  *         1 = Failure (Initialization of the Battery Control Module failed)
  *
  */
uint8_t HwBattCtrl_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	int retStatus = 0;

	/* Initialize Fuel Gauge */
	ADC_ChannelConfTypeDef sConfig = {0};
	ADC_MultiModeTypeDef multimode = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	PeriphClkInitStruct.PLL2.PLL2M = 4;
	PeriphClkInitStruct.PLL2.PLL2N = 9;
	PeriphClkInitStruct.PLL2.PLL2P = 2;
	PeriphClkInitStruct.PLL2.PLL2Q = 2;
	PeriphClkInitStruct.PLL2.PLL2R = 2;
	PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
	PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOMEDIUM;
	PeriphClkInitStruct.PLL2.PLL2FRACN = 3072.0;
	PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
		retStatus = -1;
	}

	/* ADC3_Init 1 */

	HW_VIN_SENSE_ADC_OUT_CLK_ENABLE();
	HW_VIN_SENSE_ADC_OUT_GPIO_CLK_ENABLE();
	HW_VIN_SENSE_ADC_12V_OUT_CLK_ENABLE();
	HW_VIN_SENSE_ADC_12V_OUT_GPIO_CLK_ENABLE();

	/* ADC1_Init 1 */
	HwVIN_Sense_adc_Handler.Instance = HW_VIN_SENSE_ADC_OUT_ADC;
	HwVIN_Sense_adc_Handler.Init.ClockPrescaler = HW_VIN_SENSE_ADC_OUT_ADC_DIVIDER;
	HwVIN_Sense_adc_Handler.Init.Resolution = HW_VIN_SENSE_ADC_OUT_RESOLUTION;
	HwVIN_Sense_adc_Handler.Init.ScanConvMode = HW_VIN_SENSE_ADC_OUT_ADC_ENDIS;
	HwVIN_Sense_adc_Handler.Init.EOCSelection = HW_VIN_SENSE_ADC_OUT_CONV;
	HwVIN_Sense_adc_Handler.Init.LowPowerAutoWait = DISABLE;
	HwVIN_Sense_adc_Handler.Init.ContinuousConvMode = DISABLE;
	HwVIN_Sense_adc_Handler.Init.NbrOfConversion = 1;
	HwVIN_Sense_adc_Handler.Init.DiscontinuousConvMode = DISABLE;
	HwVIN_Sense_adc_Handler.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	HwVIN_Sense_adc_Handler.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	HwVIN_Sense_adc_Handler.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
	HwVIN_Sense_adc_Handler.Init.Overrun = ADC_OVR_DATA_PRESERVED;
	HwVIN_Sense_adc_Handler.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
	HwVIN_Sense_adc_Handler.Init.OversamplingMode = DISABLE;
	if (HAL_ADC_Init(&HwVIN_Sense_adc_Handler) != HAL_OK)
	{
		retStatus = -1;
	}

	/** Configure the ADC multi-mode
	*/
	multimode.Mode = ADC_MODE_INDEPENDENT;
	if (HAL_ADCEx_MultiModeConfigChannel(&HwVIN_Sense_adc_Handler, &multimode) != HAL_OK)
	{
		retStatus = -1;
	}

	/** Configure Regular Channel
	*/
	sConfig.Channel = HW_VIN_SENSE_ADC_OUT_ADC_CHANNEL;
	sConfig.Rank = HW_VIN_SENSE_ADC_OUT_REG_RANK;
	sConfig.SamplingTime = HW_VIN_SENSE_ADC_OUT_SAMPLE_TIME;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.OffsetNumber = HW_VIN_SENSE_ADC_OUT_OFFSET;
	sConfig.Offset = 0;
	sConfig.OffsetSignedSaturation = DISABLE;
	if (HAL_ADC_ConfigChannel(&HwVIN_Sense_adc_Handler, &sConfig) != HAL_OK)
	{
		retStatus = -1;
	}

	HwVIN_Sense12v_adc_Handler.Instance = HW_VIN_SENSE_ADC_12V_OUT_ADC;
	HwVIN_Sense12v_adc_Handler.Init.ClockPrescaler = HW_VIN_SENSE_ADC_12V_OUT_ADC_DIVIDER;
	HwVIN_Sense12v_adc_Handler.Init.Resolution = HW_VIN_SENSE_ADC_12V_OUT_RESOLUTION;
	HwVIN_Sense12v_adc_Handler.Init.ScanConvMode = HW_VIN_SENSE_ADC_12V_OUT_ADC_ENDIS;
	HwVIN_Sense12v_adc_Handler.Init.EOCSelection = HW_VIN_SENSE_ADC_12V_OUT_CONV;
	HwVIN_Sense12v_adc_Handler.Init.LowPowerAutoWait = DISABLE;
	HwVIN_Sense12v_adc_Handler.Init.ContinuousConvMode = DISABLE;
	HwVIN_Sense12v_adc_Handler.Init.NbrOfConversion = 1;
	HwVIN_Sense12v_adc_Handler.Init.DiscontinuousConvMode = DISABLE;
	HwVIN_Sense12v_adc_Handler.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	HwVIN_Sense12v_adc_Handler.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	HwVIN_Sense12v_adc_Handler.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
	HwVIN_Sense12v_adc_Handler.Init.Overrun = ADC_OVR_DATA_PRESERVED;
	HwVIN_Sense12v_adc_Handler.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
	HwVIN_Sense12v_adc_Handler.Init.OversamplingMode = DISABLE;
	if (HAL_ADC_Init(&HwVIN_Sense12v_adc_Handler) != HAL_OK)
	{
		retStatus = -1;
	}

	/** Configure Regular Channel
	*/
	sConfig.Channel 	 = HW_VIN_SENSE_ADC_12V_OUT_ADC_CHANNEL;
	sConfig.Rank 		 = HW_VIN_SENSE_ADC_12V_OUT_REG_RANK;
	sConfig.SamplingTime = HW_VIN_SENSE_ADC_12V_OUT_SAMPLE_TIME;
	sConfig.SingleDiff   = ADC_SINGLE_ENDED;
	sConfig.OffsetNumber = HW_VIN_SENSE_ADC_12V_OUT_OFFSET;
	sConfig.Offset       = 0;
	sConfig.OffsetSignedSaturation = DISABLE;
	if (HAL_ADC_ConfigChannel(&HwVIN_Sense12v_adc_Handler, &sConfig) != HAL_OK)
	{
		retStatus = -1;
	}


	/**ADC1 GPIO Configuration
	*/
	HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PA1, SYSCFG_SWITCH_PA1_OPEN);


	/**ADC3 GPIO Configuration
	*/
	HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PC2, SYSCFG_SWITCH_PC2_OPEN);


   /* Battery Status Pin */
	GPIO_InitStruct.Pin = HW_BATTERY_STS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(HW_BATTERY_STS_PORT, &GPIO_InitStruct);

	/* Power Source Indicator GPIO */
	GPIO_InitStruct.Pin = HW_PWR_SRC_IND_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(HW_PWR_SRC_IND_PORT, &GPIO_InitStruct);
	retStatus = HwFuelGauge_Init(BATTERY_CAPACITY,BATTERY_CRG_TERM_I,BATTERY_V_EMPTY);
	return retStatus;
}

/**
  * @brief
  *        Checks whether the battery is connected to the system.
  *        This function reads the status of the battery connection by checking the appropriate hardware signal
  *        or GPIO pin that indicates the presence of a battery.
  *
  * @param void
  *        This function does not take any parameters.
  *
  * @retval bool
  *         0  = Battery is connected.
  *         1  = Battery is not connected.
  */


bool HwBattCtrl_IsBatteryConnected(void)
{
	return 0;
}

/**
  * @brief
  *        Retrieves the current status of the battery.
  *        This function reads the battery status from the hardware and returns it as a value of type `BatteryStatus_t`.
  *        It can be used to determine whether the battery is charging, discharging, fully charged, not connected, or in an unknown state.
  * @param void
  *
  * @retval BatteryStatus_t
  *         The current status of the battery, which can be one of the following:
  *         - BATT_STATUS_CHARGING:        Battery is currently charging.
  *         - BATT_STATUS_FULL:            Battery is fully charged.
  *
  */

BatteryStatus_t HwBattCtrl_GetBatteryStatus(void)
{
	BatteryStatus_t BtSts;
	BtSts = HAL_GPIO_ReadPin(HW_BATTERY_STS_PORT,HW_BATTERY_STS_PIN);
	if(BtSts == 0)
		BtSts = BATT_STATUS_CHARGING;
	else{
		BtSts = BATT_STATUS_FULL;
	    }
	return BtSts;
}

/**
  * @brief
  *        Retrieves the current voltage level of the battery.
  * @param void
  * @retval uint16_t
  *         The current battery voltage in millivolts (mV).
  */

uint16_t HwBattCtrl_GetBatteryVoltage(void)
{
	return HwFuelGauge_GetBatteryVoltage();
}

/**
  * @brief
  *        Retrieves the current temperature of the battery.
  *
  * @param   void
  *  @retval int8_t
  *         The current battery temperature in degrees Celsius (°C).
  *
  */

int8_t HwBattCtrl_GetBatteryTemperature(void)
{
	return HwFuelGauge_GetBatteryTemperature();
}

/**
  * @brief
  *        Retrieves the State of Charge (SOC) of the battery.
  *        This function reads the battery's State of Charge, which represents the remaining capacity of the battery.
  * @param void
  * @retval uint8_t
  *         The current battery charge level as a percentage (0% to 100%).
  *
  */

uint8_t HwBattCtrl_GetBatteryChargeLevel(void)
{
	return HwFuelGauge_GetBatteryChargeLevel();
}

/**
  * @brief
  *        Reads the Power Source Detection ADC channel to determine the current power source.
  * @param adcData = A pointer to a uint16_t variable where the raw ADC value will be stored.
  * @retval uint8_t
  *         0 = Success (ADC value read successfully and stored in `adcData`).
  *         1 = Failure (ADC read operation failed or invalid pointer provided).
  *
  */


static uint8_t Hw_ReadPwrSrc_Adc(uint16_t *adcData)
{
	int retStatus;
	if(HAL_ADC_Start(&HwVIN_Sense_adc_Handler) != HAL_OK)         // VIN_SENSE_ADC_12V_OUT
	{
		return HAL_ERROR;
	}
	if (HAL_ADC_Start(&HwVIN_Sense_adc_Handler) != HAL_OK)
	{
		retStatus =  -1;         // ADC start error
	}

	// Poll for end of conversion
	if (HAL_ADC_PollForConversion(&HwVIN_Sense_adc_Handler, 100) != HAL_OK)
	{
		retStatus = -1; // ADC conversion error
	}

	// Get the ADC value
	*adcData = HAL_ADC_GetValue(&HwVIN_Sense_adc_Handler);

	return retStatus;
}

/**
  * @brief
  *        Determines the current power source of the system.
  *        This function identifies the active power source by analyzing the voltage level or other signals
  *        from the power source detection circuit.
  *  @param void
  *  @retval PowerSource_t
  *         The current power source, which can be one of the following:
  *         - POWER_SOURCE_UNKNOWN: The power source is unknown or cannot be determined.
  *         - POWER_SOURCE_SMPS_12V: The system is powered by a 12V Switched-Mode Power Supply (SMPS).
  *         - POWER_SOURCE_USB_12V: The system is powered by a 12V USB power source.
  *         - POWER_SOURCE_BATTERY: The system is powered by the battery.
  */


PowerSource_t HwBattCtrl_GetPowerSource(void)
{
	PowerSource_t Pwr_Src;
	uint16_t Pwr_SrcADCVal;
	float SrcVolt;
	/* Read the Power Source Status Pin */
	Pwr_Src = HAL_GPIO_ReadPin(HW_PWR_SRC_IND_PORT,HW_PWR_SRC_IND_PIN);
	if(Pwr_Src == 0){
		Hw_ReadPwrSrc_Adc(&Pwr_SrcADCVal);
		/* Convert the Raw Value into the Volatge */
		SrcVolt = ((float)Pwr_SrcADCVal /ADC_RESOLUTION) * ADC_REF_VOL;
		if(SrcVolt < VOLTAGE_OFFSET)
			Pwr_Src = POWER_SOURCE_BATTERY;
		else
			Pwr_Src = POWER_SOURCE_USB_12V;
	}
	else
	{
		/* Read the ADC Value to confirm the Source */
	    /*  Because on DC Power & Battery Power the Status Pin is High*/
		Hw_ReadPwrSrc_Adc(&Pwr_SrcADCVal);
		/* if the Value of the ADC is < 1.5V */
		SrcVolt = ((float)Pwr_SrcADCVal /ADC_RESOLUTION) * ADC_REF_VOL;
		if(SrcVolt < VOLTAGE_OFFSET)
			Pwr_Src = POWER_SOURCE_BATTERY;
		else
			Pwr_Src = POWER_SOURCE_SMPS_12V;
	}

	return Pwr_Src;

}

/**
  * @brief
  *        Retrieves detailed information about the battery.
  * @param info  A pointer to a `BatteryInfo_t` structure where the battery information will be stored.
  * @retval void
  *         The function does not return a value.
  */

void HwBattCtrl_GetBatteryInfo(BatteryInfo_t *info)
{
	info -> voltage_mV        = HwFuelGauge_GetBatteryVoltage();        // Battery voltage in millivolts
    info -> temperature_C     = HwFuelGauge_GetBatteryTemperature();;   // Battery temperature in degrees Celsius
    info -> charge_level      = HwFuelGauge_GetBatteryChargeLevel();    // Battery charge percentage (0-100%)
    info -> time_to_empty_min = HwFuelGauge_GetTimeToEmpty();           // Estimated time to empty in minutes
    info -> time_to_full_min  = HwFuelGauge_GetTimeToFull();            // Estimated time to full charge in minutes
   

}

void HwBattCtrl_SetCharging(bool enable)
{
	enable = 0;
}

bool HwBattCtrl_IsChargingEnabled(void)
{
	return 0;
}
/**
  * @brief
  *        Retrieves the estimated time until the battery is fully discharged (empty).
  *        This function calculates or retrieves the estimated time, in minutes, based on the current battery discharge rate
  *        and remaining capacity.
  *  @param void
  *  @retval uint16_t
  *         The estimated time until the battery is empty, in minutes.
  */

uint16_t HwBattCtrl_GetTimeToEmpty(void)
{
	return HwFuelGauge_GetTimeToEmpty();
}
/**
  * @brief
  *        Retrieves the estimated time until the battery is fully charged (FULL).
  *        This function calculates or retrieves the estimated time, in minutes, based on the current battery charge rate
  *        and remaining capacity.
  *  @param void
  *  @retval uint16_t
  *         The estimated time until the battery is FULL, in minutes.
  */

uint16_t HwBattCtrl_GetTimeToFull(void)
{
	return HwFuelGauge_GetTimeToEmpty();
}
