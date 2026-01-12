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
*   This file implements a generic HW Interface of Door Position Sensor used in Infusion Pump
*
********************************************************************************/


#include "HwDoorPositionSensor.h"
#include "HwDoorPositionSensorConfig.h"
#include "stm32h7xx_hal.h"



/* Private variables ---------------------------------------------------------*/

#define ADC_MAX_VALUE 4095
#define ADC_MIN_VALUE 0
#define ADC_REF_VOLTAGE 3.3

ADC_HandleTypeDef HwDoorPositionSensorADCHandle_;

/*
 * @brief
 *  This function configures the GPIO pin connected to the door position sensor as an ADC input channel.
 * @param void
 * @retval int
 *         0  = Success (Door position sensor pin initialized successfully as an ADC channel).
 *         -1 = Failure (Failed to initialize the door position sensor pin as an ADC channel).
 * */

int HwDoorPositionSensorInit( void )
{
	  int retStatus = 0;

	  ADC_ChannelConfTypeDef HwDoorPositionSensorConfig_ = {0};
	  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
	  /*
	   * Initialize the HW modules for ADC like Door Position Sensor
	   */
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

	    /* Peripheral clock enable */
	  HW_DOOR_POSITION_SENSOR_ADC_CLK_ENABLE();
	  HW_DOOR_POSITION_SENSOR_ADC_GPIO_CLK_ENABLE();
	  HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PC3, SYSCFG_SWITCH_PC3_OPEN);

	  HwDoorPositionSensorADCHandle_.Instance = HW_DOOR_POSITION_SENSOR_ADC;
	  HwDoorPositionSensorADCHandle_.Init.ClockPrescaler = HWDOOR_POSITION_SENSOR_ADC_DIVIDER;
	  HwDoorPositionSensorADCHandle_.Init.Resolution = HWDOOR_POSITION_SENSOR_ADC_RESOLUTION;
	  HwDoorPositionSensorADCHandle_.Init.ScanConvMode = HWDOOR_POSITION_SENSOR_ADC_ENDIS;
	  HwDoorPositionSensorADCHandle_.Init.EOCSelection = HWDOOR_POSITION_SENSOR_ADC_CONV;
	  HwDoorPositionSensorADCHandle_.Init.LowPowerAutoWait = DISABLE;
	  HwDoorPositionSensorADCHandle_.Init.ContinuousConvMode = HWDOOR_POSITION_SENSOR_ADC_CONTINEOUS_CONV;
	  HwDoorPositionSensorADCHandle_.Init.NbrOfConversion = 1;
	  HwDoorPositionSensorADCHandle_.Init.DiscontinuousConvMode = DISABLE;
	  HwDoorPositionSensorADCHandle_.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	  HwDoorPositionSensorADCHandle_.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	  HwDoorPositionSensorADCHandle_.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
	  HwDoorPositionSensorADCHandle_.Init.Overrun = ADC_OVR_DATA_PRESERVED;
	  HwDoorPositionSensorADCHandle_.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
	  HwDoorPositionSensorADCHandle_.Init.OversamplingMode = DISABLE;
	  if (HAL_ADC_Init(&HwDoorPositionSensorADCHandle_) != HAL_OK)
	  {
		  retStatus = -1;
	  }
	  /** Configure Regular Channel
	  */
	  HwDoorPositionSensorConfig_.Channel = HW_DOOR_POSITION_SENSOR_ACD_CHANNEL;
	  HwDoorPositionSensorConfig_.Rank = HWDOOR_POSITION_SENSOR_ADC_REG_RANK;
	  HwDoorPositionSensorConfig_.SamplingTime = HWDOOR_POSITION_SENSOR_ADC_SAMPLE_TIME;
	  HwDoorPositionSensorConfig_.SingleDiff = ADC_SINGLE_ENDED;
	  HwDoorPositionSensorConfig_.OffsetNumber = HWDOOR_POSITION_SENSOR_ADC_OFFSET;
	  HwDoorPositionSensorConfig_.Offset = 0;
	  HwDoorPositionSensorConfig_.OffsetSignedSaturation = DISABLE;
	  if (HAL_ADC_ConfigChannel(&HwDoorPositionSensorADCHandle_, &HwDoorPositionSensorConfig_) != HAL_OK)
	  {
		  retStatus = -1;
	  }
	  return retStatus;
}


/**
  * @brief
   *        This function reads the analog voltage level from the ADC channel configured for the door position sensor
  *        and stores the raw ADC value in the provided variable. The ADC value corresponds to the door's position.
  * @param pStatus
  *        A pointer to a variable of type `HwDoorPosition_t` where the raw ADC value will be stored.
 * @retval int
  *         0 = Success (ADC value read successfully and stored in `pStatus`).
  *         -1 = Failure (Failed to read the ADC value or invalid pointer provided).
  */

int HwDoorPositionSensorReadStatus( HwDoorPosition_t *pStatus )
{
	int retStatus = 0;
	if (pStatus == NULL)
	{
		return -1;                                                                                                       // Error: Null pointer
	}
	HwDoorPosition_t adcValue = 0;
	
	// Start ADC conversion
	if (HAL_ADC_Start(&HwDoorPositionSensorADCHandle_) != HAL_OK)
	{
		retStatus =  -1;                                                                                                 // ADC start error
	}

	// Poll for end of conversion
	if (HAL_ADC_PollForConversion(&HwDoorPositionSensorADCHandle_, 100) != HAL_OK)
	{
		retStatus = -1; // ADC conversion error
	}

    // Get the ADC value
	 adcValue = HAL_ADC_GetValue(&HwDoorPositionSensorADCHandle_);
	
	 

	 // Stop ADC conversion
	 if (HAL_ADC_Stop(&HwDoorPositionSensorADCHandle_) != HAL_OK)
	 {
        retStatus = -1;                                                                                                  // ADC stop error
	 }
    
     if( 0 == retStatus )
     {
       *pStatus = adcValue;
     }
	
	return retStatus;
}




