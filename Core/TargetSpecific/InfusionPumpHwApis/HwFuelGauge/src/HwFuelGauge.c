


#include "HwFuelGauge.h"
#include "HwFuelGaugeConfig.h"
#include "stdbool.h"
#include "../../HwI2CMux/inc/HwI2CMux.h"
#include "max17261.h"

/* I2C Handler */
extern I2C_HandleTypeDef HwI2CMux_Handler;

/*Private data */
struct max17261_conf hmax17261;

/* Private Definitions */
#define FUELGAUGE_I2C_ADDR (0x36 << 1)
#define FUELGAUGE_DEV_NAME 0x4033

#define BATTERY_V_RECOVERY (6100/40)
#define POWER_CHG_VOLTAGE 4200


/*Private Function declaration*/
static uint8_t HwFuelGaugeWriteReg(uint8_t *wrbuff, uint8_t length);
static uint8_t HwFuelGaugeReadReg(uint8_t RegAddr, uint16_t *data);
static uint8_t HwFuelGauge_WriteParam(uint8_t RegAddr, uint16_t data);
static uint8_t HwFuelGauge_Delayms(uint32_t period);

/**
  * @brief
  *        Initializes the fuel gauge with the specified parameters.
  *        This function configures the fuel gauge IC with the provided battery parameters, such as design capacity,
  *        termination current, and empty voltage.
  * * @param designCapacity_mAh
  *        The design capacity of the battery in milliampere-hours (mAh).
  *   @param terminationCurrent_mA
  *        The termination current of the battery in milliamperes (mA).
  *   @param emptyVoltage_mV
  *        The empty voltage of the battery in millivolts (mV).
  *   * @retval FuelGaugeStatus_t
  *         The status of the initialization process, which can be one of the following:
  *         - FUEL_GAUGE_OK: Fuel gauge initialized successfully.
  *         - FUEL_GAUGE_I2C_ERROR: Initialization failed.
  */



FuelGaugeStatus_t HwFuelGauge_Init(uint16_t designCapacity_mAh, uint16_t terminationCurrent_mA, uint16_t emptyVoltage_mV)
{
	
	hmax17261.read 			= HwFuelGaugeReadReg;
	hmax17261.write 		= HwFuelGauge_WriteParam;
	hmax17261.delay_ms 		= HwFuelGauge_Delayms;

	hmax17261.DesignCap 	= designCapacity_mAh;
	hmax17261.IchgTerm 		= terminationCurrent_mA;
	hmax17261.VEmpty 		= (emptyVoltage_mV << 7) | (BATTERY_V_RECOVERY & 0x7F);
	hmax17261.R100 			= 0;
	hmax17261.ChrgVoltage 	= POWER_CHG_VOLTAGE;

	uint8_t retStatus = FUEL_GAUGE_ERROR;
	if(HwI2CMux_Init() != 0)
	   retStatus = FUEL_GAUGE_I2C_ERROR;
	else
	{
		if(HwI2CMux_CHSEL(HwI2CMux_FUELGAUGE_CHN) !=0)
			retStatus = FUEL_GAUGE_I2C_ERROR;
		else{
			retStatus  = max17261_init(&hmax17261);
			}

	}
	return retStatus;
}

/**
  * @brief
  *        Checks if the fuel gauge device is present and responsive.
  *        This function verifies the presence of the fuel gauge by checking its device name.
  * @param void
  * @retval bool
  *         - 0: Fuel gauge is present and responsive.
  *         - 1: Fuel gauge is not detected or communication failed.
  */

bool HwFuelGauge_IsPresent(void)
{
	int retStatus = 0;
	uint16_t read_data = 0;
	uint8_t reg_addr;
	reg_addr = MAX17261_DeviceName;
	HwFuelGaugeReadReg(reg_addr,&read_data);

	if(FUELGAUGE_DEV_NAME != read_data)
	{
		retStatus = 0;                          // Fuel Gauge Not Present
	}
	else{
		retStatus = 1;                          // Fuel Gauge Present
	}

	return retStatus;
}

/**
  * @brief
  *        Retrieves the current voltage level of the battery.
  * @param void
  * @retval uint16_t
  *         The current battery voltage in millivolts (mV).
  */


uint16_t HwFuelGauge_GetBatteryVoltage(void)
{
	
	return max17261_get_voltage(&hmax17261);
	
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



uint8_t HwFuelGauge_GetBatteryTemperature(void)
{
	return max17261_get_temperature(&hmax17261);
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

uint8_t HwFuelGauge_GetBatteryChargeLevel()
{
	return max17261_get_SOC(&hmax17261);
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

uint16_t HwFuelGauge_GetTimeToEmpty(void)
{
	return max17261_get_TTE(&hmax17261);
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

uint16_t HwFuelGauge_GetTimeToFull(void)
{
	return (max17261_get_TTF(&hmax17261));
}

/**
  * @brief
  *        Retrieves the  charging/Discharging current in mA of the battery.
  *
  * @param   void
  *  @retval int8_t
  *         The charging/discharging current in mA.
  *
  */

int16_t HwFuelGauge_GetBatteryCurrent(void)
{
	return max17261_get_TTE(&hmax17261);
}

/**
  * @brief
  *        Retrieves Design Capacity of the battery.
  *
  * @param   void
  *  @retval int8_t
  *         The Design Capcity of the battery in maH.
  *
  */

uint16_t HwFuelGauge_GetBatteryCapacity(void)
{
	return max17261_get_design_capacity(&hmax17261);
}



FGBatteryStatus_t HwFuelGauge_GetBatteryStatus(void)
{
	return FUEL_GAUGE_ERROR;
}

/**
  * @brief
  *        Retrieves detailed information about the battery.
  * @param info  A pointer to a `FGBatteryInfo_t` structure where the battery information will be stored.
  * @retval void
  *         The function does not return a value.
  */


void HwFuelGauge_GetBatteryInfo(FGBatteryInfo_t *info)
{
	info -> voltage_mV        = HwFuelGauge_GetBatteryVoltage();        // Battery voltage in millivolts
	info -> temperature_C     = HwFuelGauge_GetBatteryTemperature();;   // Battery temperature in degrees Celsius
	info -> charge_level      = HwFuelGauge_GetBatteryChargeLevel();    // Battery charge percentage (0-100%)
	info -> time_to_empty_min = HwFuelGauge_GetTimeToEmpty();           // Estimated time to empty in minutes
	info -> time_to_full_min  = HwFuelGauge_GetTimeToFull();            // Estimated time to full charge in minutes
	info -> time_to_full_min  = HwFuelGauge_GetTimeToFull();            // Estimated time to full charge in minutes
}

FuelGaugeStatus_t HwFuelGauge_SoftReset(void)
{
	return FUEL_GAUGE_ERROR;
}

/* Fuel Gauge I2C Wrapper function to write */

uint8_t HwFuelGauge_WriteParam(uint8_t RegAddr, uint16_t data)
{
	uint8_t wr_Data[3];
	wr_Data[0] = RegAddr;
	wr_Data[1] = (uint8_t)(data & 0xFF);
	wr_Data[2] = (uint8_t)(data >> 8);
	return HwFuelGaugeWriteReg(wr_Data,3);
}

// Fuel I2C Gauge Write API
static uint8_t HwFuelGaugeWriteReg(uint8_t *wrbuff, uint8_t length)
{
    return (Hw_TCA9546_Mux_I2C_Transmit(FUELGAUGE_I2C_ADDR, wrbuff, length));
}

/* Fuel Gauge I2C Read Function */
uint8_t HwFuelGaugeReadReg(uint8_t RegAddr, uint16_t *data)
{
	uint8_t rx_buffer[2];
	if(Hw_TCA9546_Mux_I2C_Transmit(FUELGAUGE_I2C_ADDR, &RegAddr,1)!=HAL_OK)
		return -1;
    if(Hw_TCA9546_Mux_I2C_Receive(FUELGAUGE_I2C_ADDR, rx_buffer,2)!=HAL_OK)
		return -2;
	
	*data = (uint16_t)(rx_buffer[1] << 8 | (rx_buffer[0]));

	return 0;
}

/* Wrapper function for Delay */

uint8_t HwFuelGauge_Delayms(uint32_t period)
{
	HAL_Delay(period);               // Delay in ms
	return 0;
}





