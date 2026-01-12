/*
 *  @file:  max17261.c
 *  @brief: MAX17261 Driver
 *
 */

#include <stdint.h>

#include "MAX17261.h"

extern struct max17261_conf hmax17261;
typedef struct {
    float voltage;
    int soc;
}HwVolSoc_t;

HwVolSoc_t Vol_SOC_tbl[] = {
    {6.00, 0},   {6.02, 1},   {6.04, 2},   {6.06, 3},   {6.08, 4},
    {6.10, 5},   {6.12, 6},   {6.14, 7},   {6.16, 8},   {6.18, 9},
    {6.20, 10},  {6.22, 11},  {6.24, 12},  {6.26, 13},  {6.28, 14},
    {6.30, 15},  {6.32, 16},  {6.34, 17},  {6.36, 18},  {6.38, 19},
    {6.40, 20},  {6.42, 21},  {6.44, 22},  {6.46, 23},  {6.48, 24},
    {6.50, 25},  {6.52, 26},  {6.54, 27},  {6.56, 28},  {6.58, 29},
    {6.60, 30},  {6.62, 31},  {6.64, 32},  {6.66, 33},  {6.68, 34},
    {6.70, 35},  {6.72, 36},  {6.74, 37},  {6.76, 38},  {6.78, 39},
    {6.80, 40},  {6.82, 41},  {6.84, 42},  {6.86, 43},  {6.88, 44},
    {6.90, 45},  {6.92, 46},  {6.94, 47},  {6.96, 48},  {6.98, 49},
    {7.00, 50},  {7.02, 51},  {7.04, 52},  {7.06, 53},  {7.08, 54},
    {7.10, 55},  {7.12, 56},  {7.14, 57},  {7.16, 58},  {7.18, 59},
    {7.20, 60},  {7.22, 61},  {7.24, 62},  {7.26, 63},  {7.28, 64},
    {7.30, 65},  {7.32, 66},  {7.34, 67},  {7.36, 68},  {7.38, 69},
    {7.40, 70},  {7.42, 71},  {7.44, 72},  {7.46, 73},  {7.48, 74},
    {7.50, 75},  {7.52, 76},  {7.54, 77},  {7.56, 78},  {7.58, 79},
    {7.60, 80},  {7.62, 81},  {7.64, 82},  {7.66, 83},  {7.68, 84},
    {7.70, 85},  {7.72, 86},  {7.74, 87},  {7.76, 88},  {7.78, 89},
    {7.80, 90},  {7.82, 91},  {7.84, 92},  {7.86, 93},  {7.88, 94},
    {7.90, 95},  {7.92, 96},  {7.94, 97},  {7.96, 98},  {7.98, 99},
    {8.00, 100}, {8.02, 100}, {8.04, 100}, {8.06, 100}, {8.08, 100}
};

static int getSocFromVoltage(float voltage) {
    int tableSize = sizeof(Vol_SOC_tbl) / sizeof(Vol_SOC_tbl[0]);

    // Handle out-of-range voltages
    if (voltage < Vol_SOC_tbl[0].voltage) {
        return 0;                                                          // Below minimum voltage, return 0%
    }
    if (voltage >= Vol_SOC_tbl[tableSize - 1].voltage) {
        return 100;                                                        // Above maximum voltage, return 100%
    }

    // Find the closest match in the lookup table
    for (int i = 0; i < tableSize - 1; i++) {
        if (voltage >= Vol_SOC_tbl[i].voltage && voltage < Vol_SOC_tbl[i + 1].voltage) {
            return Vol_SOC_tbl[i].soc;
        }
    }

    return -1; // Should not reach here
}

max17261_err_t
max17261_init(struct max17261_conf *conf)
{
	max17261_err_t ret;
	uint16_t value, model_cfg = 0x8000;

	// check for power on reset
	ret = max17261_read_word(conf, MAX17261_Status, &value);
	if (((value & 0x0002) || (conf->force_init)) && ret == 0) {
		// Delay until FSTAT.DNR bit == 0
		// TODO: Do we need a safety timeout here?
		do {
			ret = max17261_read_word(conf, MAX17261_FStat, &value);
		} while (ret || (value & 1));

		// Initialize Configuration
		ret = max17261_read_word(conf, MAX17261_HibCfg,
					 &conf->HibCFG); //Store original HibCFG value
		if (!ret)
			ret = max17261_write_word(conf, MAX17261_SoftWakeup,
						  0x90); // Exit Hibernate Mode step 1
		if (!ret)
			ret = max17261_write_word(conf, MAX17261_HibCfg,
						  0x0); // Exit Hibernate Mode step 2
		if (!ret)
			ret = max17261_write_word(conf, MAX17261_SoftWakeup,
						  0x0); // Exit Hibernate Mode step 3

		if (!ret)
			ret = max17261_write_word(conf, MAX17261_DesignCap, conf->DesignCap * 2);
		if (!ret)
			ret = max17261_write_word(conf, MAX17261_IChgTerm, conf->IchgTerm * 6.4);
		if (!ret)
			ret = max17261_write_word(conf, MAX17261_VEmpty, conf->VEmpty);

		if (ret)
			return ret;

		model_cfg |= (conf->ChrgVoltage > 4.275) << 10;
		model_cfg |= (conf->R100 & 1) << 13;

		// Write ModelCFG
		ret = max17261_write_word(conf, MAX17261_ModelCFG, model_cfg);
		if (ret)
			return ret;

		// Poll ModelCFG.Refresh(highest bit),
		// TODO: Do we need a safety timeout here?
		do {
			ret = max17261_read_word(conf, MAX17261_ModelCFG, &value);
			// do not continue until ModelCFG.Refresh==0
		} while (ret || (value & 0x8000));

		ret = max17261_write_word(conf, MAX17261_Config, 0xA210);
		// Init option 2
		if (conf->init_option == 2) {
			if (!ret)
				ret = max17261_write_verify(conf, MAX17261_RComp0,
							    conf->lparams.RCOMP0);
			if (!ret)
				ret = max17261_write_verify(conf, MAX17261_TempCo,
							    conf->lparams.TempCo);
			if (!ret)
				ret = max17261_write_verify(conf, MAX17261_QRTable00,
							    conf->lparams.QRTable[0]);
			if (!ret)
				ret = max17261_write_verify(conf, MAX17261_QRTable10,
							    conf->lparams.QRTable[1]);
			if (!ret)
				ret = max17261_write_verify(conf, MAX17261_QRTable20,
							    conf->lparams.QRTable[2]);
			if (!ret)
				ret = max17261_write_verify(conf, MAX17261_QRTable30,
							    conf->lparams.QRTable[3]);
		}

		// Restore Original HibCFG value
		if (!ret)
			ret = max17261_write_word(conf, MAX17261_HibCfg, conf->HibCFG);
		// Initialization complete
		if (!ret)
			ret = max17261_read_word(conf, MAX17261_Status, &value); // Read Status
		// Write and Verify Status with POR bit Cleared
		if (!ret)
			ret = max17261_write_verify(conf, MAX17261_Status, value
						    && 0xFFFD);
	}

	return ret;
}

uint8_t
max17261_get_SOC(struct max17261_conf *conf)
{
	float voltage = max17261_get_voltage(&hmax17261);
	voltage = voltage * 2;
	voltage = voltage/1000;
	float soc = getSocFromVoltage(voltage);
	return soc;
}

max17261_err_t
max17261_set_reported_capacity(struct max17261_conf *conf, uint16_t capacity)
{
	return max17261_write_word(conf, MAX17261_RepCAP, capacity / CAPACITY_MULTIPLIER);
}

uint16_t
max17261_get_reported_capacity(struct max17261_conf *conf)
{
	uint16_t value;
	max17261_read_word(conf, MAX17261_RepCAP, &value);
	return value * CAPACITY_MULTIPLIER;
}

max17261_err_t
max17261_set_full_reported_capacity(struct max17261_conf *conf,
                                    uint16_t capacity)
{
	return max17261_write_word(conf, MAX17261_FullRepCAP, capacity / CAPACITY_MULTIPLIER);
}

uint16_t
max17261_get_full_reported_capacity(struct max17261_conf *conf)
{
	uint16_t value;
	max17261_read_word(conf, MAX17261_FullRepCAP, &value);
	return value * CAPACITY_MULTIPLIER;
}

max17261_err_t
max17261_set_design_capacity(struct max17261_conf *conf, uint16_t capacity)
{
	return max17261_write_word(conf, MAX17261_DesignCap, capacity / CAPACITY_MULTIPLIER);
}

uint16_t
max17261_get_design_capacity(struct max17261_conf *conf)
{
	uint16_t value;
	max17261_read_word(conf, MAX17261_DesignCap, &value);
	return value * CAPACITY_MULTIPLIER;
}

uint16_t
max17261_get_voltage(struct max17261_conf *conf)
{
	uint16_t value;
	max17261_read_word(conf, MAX17261_VCell, &value);
	value *= VOLTAGE_MULTIPLIER_V;
	return value;
}

uint16_t
max17261_get_average_voltage(struct max17261_conf *conf)
{
	uint16_t value;
	max17261_read_word(conf, MAX17261_AvgVCell, &value);
	value *= VOLTAGE_MULTIPLIER_V;
	return value;
}

max17261_err_t
max17261_reset_minmax_voltage(struct max17261_conf *conf)
{
	return max17261_write_word(conf, MAX17261_MaxMinVolt, 0x00FF);
}

max17261_err_t
max17261_get_minmax_voltage(struct max17261_conf *conf, uint16_t *min,
                            uint16_t *max)
{
	uint16_t value;
	max17261_err_t ret = max17261_read_word(conf, MAX17261_MaxMinVolt, &value);

	if (!ret) {
		*min = (value & 0xFF) * 20;
		*max = ((value >> 8) & 0xFF) * 20;
	}

	return ret;
}

int16_t
max17261_get_current(struct max17261_conf *conf)
{
	int16_t value;
	max17261_read_word(conf, MAX17261_Current, (uint16_t *) &value);
	value = value * CURRENT_MULTIPLIER;
	return value;
}

int16_t
max17261_get_average_current(struct max17261_conf *conf)
{
	int16_t value;
	max17261_read_word(conf, MAX17261_AvgCurrent, (uint16_t *) &value);
	value = value * CURRENT_MULTIPLIER;
	return value;
}

max17261_err_t
max17261_reset_minmax_current(struct max17261_conf *conf)
{
	return max17261_write_word(conf, MAX17261_MaxMinCurr, 0x00FF);
}

max17261_err_t
max17261_get_minmax_current(struct max17261_conf *conf, int16_t *min,
                            int16_t *max)
{
	uint16_t value;
	max17261_err_t ret = max17261_read_word(conf, MAX17261_MaxMinCurr, &value);

	if (!ret) {
		*min = ((int8_t)(value & 0xFF)) * CURRENT_MULTIPLIER_MINMAX;
		*max = ((int8_t)(value >> 8)) * CURRENT_MULTIPLIER_MINMAX;
	}

	return ret;
}

max17261_err_t
max17261_get_die_temperature(struct max17261_conf *conf)
{
	uint16_t value;
	max17261_err_t ret = max17261_read_word(conf, MAX17261_DieTemp, &value);

	if (ret)
		return ret;

	return value >> 8;
}

max17261_err_t
max17261_get_temperature(struct max17261_conf *conf)
{
	uint16_t value;
	max17261_err_t ret = max17261_read_word(conf, MAX17261_Temp, &value);

	if (ret)
		return ret;

	return value >> 8;
}

max17261_err_t
max17261_get_average_temperature(struct max17261_conf *conf)
{
	uint16_t value;
	max17261_err_t ret = max17261_read_word(conf, MAX17261_AvgTA, &value);

	if (ret)
		return ret;

	return value >> 8;
}

max17261_err_t
max17261_get_minmax_temperature(struct max17261_conf *conf, int8_t *min,
                                int8_t *max)
{
	uint16_t value;
	max17261_err_t ret = max17261_read_word(conf, MAX17261_MaxMinTemp, &value);
	if (!ret) {
		*min = value & 0xFF;
		*max = (value >> 8) & 0xFF;
	}

	return ret;
}

max17261_err_t
max17261_reset_minmax_temperature(struct max17261_conf *conf)
{
	return max17261_write_word(conf, MAX17261_MaxMinTemp,  0x807F);
}

uint16_t
max17261_get_TTE(struct max17261_conf *conf)
{
	uint16_t value;
	uint8_t ret = max17261_read_word(conf, MAX17261_TTE, &value);
	return ret ? 0 : value * TIME_MULTIPLIER_MIN;
}

uint16_t
max17261_get_TTF(struct max17261_conf *conf)
{
	uint16_t value;
	uint8_t ret = max17261_read_word(conf, MAX17261_TTF, &value);
	return ret ? 0 : value * TIME_MULTIPLIER_MIN;
}

max17261_err_t
max17261_get_learned_params(struct max17261_conf *conf)
{
	max17261_err_t ret;

	ret = max17261_read_word(conf, MAX17261_FullCapNom, &conf->lparams.FullCapNom);
	if (!ret)
		ret = max17261_read_word(conf, MAX17261_FullRepCAP, &conf->lparams.FullCapRep);
	if (!ret)
		ret = max17261_read_word(conf, MAX17261_RComp0, &conf->lparams.RCOMP0);
	if (!ret)
		ret = max17261_read_word(conf, MAX17261_TempCo, &conf->lparams.TempCo);
	if (!ret)
		ret = max17261_read_word(conf, MAX17261_Cycles, &conf->lparams.cycles);

	return ret;
}

max17261_err_t
max17261_restore_learned_params(struct max17261_conf *conf)
{
	max17261_err_t ret;

	ret = max17261_write_verify(conf, MAX17261_RComp0, conf->lparams.RCOMP0);
	if (!ret)
		ret = max17261_write_verify(conf, MAX17261_TempCo, conf->lparams.TempCo);
	if (!ret)
		ret = max17261_write_verify(conf, MAX17261_FullRepCAP,
					    conf->lparams.FullCapRep);
	if (!ret)
		ret = max17261_write_verify(conf, MAX17261_FullCapNom,
					    conf->lparams.FullCapNom);
	if (!ret)
		ret = max17261_write_verify(conf, MAX17261_dPAcc, 0x0C80);
	if (!ret)
		ret = max17261_write_verify(conf, MAX17261_dQAcc,
					    conf->lparams.FullCapNom * 2);
	if (!ret)
		ret = max17261_write_verify(conf, MAX17261_Cycles, conf->lparams.cycles);

	return ret;
}

uint8_t
max17261_get_qrtable_values(struct max17261_conf *conf)
{
	max17261_err_t ret;

	ret = max17261_read_word(conf, MAX17261_QRTable00, &conf->lparams.QRTable[0]);
	if (!ret)
		ret = max17261_read_word(conf, MAX17261_QRTable10, &conf->lparams.QRTable[1]);
	if (!ret)
		ret = max17261_read_word(conf, MAX17261_QRTable20, &conf->lparams.QRTable[2]);
	if (!ret)
		ret = max17261_read_word(conf, MAX17261_QRTable30, &conf->lparams.QRTable[3]);

	return ret;
}
/**
 * @brief I2C Read function wrapper
 * Reads 16bit data from device
 * @param conf
 * @param reg Register to read from
 * @param value Pointer to write value
 * @return 0 on success error code otherwise
 */
__attribute__((weak)) max17261_err_t
max17261_read_word(struct max17261_conf *conf, uint8_t reg, uint16_t *value)
{
#ifndef MAX17261_USE_WEAK
	return conf->read(reg, value);
#else
	return 0;
#endif
}

/**
 * @brief I2C Write function wrapper
 * Writes 16bit data to device
 * @param conf
 * @param reg Register to write to
 * @param value Value to write
 * @return 0 on success error code otherwise
 */
__attribute__((weak)) max17261_err_t
max17261_write_word(struct max17261_conf *conf, uint8_t reg, uint16_t value)
{
#ifndef MAX17261_USE_WEAK
	return conf->write(reg, value);
#else
	return 0;
#endif
}

/**
 * @brief I2C Write with verify function
 * Writes 16bit data to device and verifies content
 * @param conf
 * @param reg Register to write to
 * @param value Value to write
 * @return 0 on success error code otherwise
 */
max17261_err_t
max17261_write_verify(struct max17261_conf *conf, uint8_t reg, uint16_t value)
{
	uint8_t wcount = 0, ret;
	uint16_t readback;
	do {
		if ((ret = max17261_write_word(conf, reg, value)) != 0)
			return ret;
#ifdef MAX17261_USE_WEAK
		max17261_delay_ms(conf, 1);
#else
		conf->delay_ms(1);
#endif
		if ((ret = max17261_read_word(conf, reg, &readback)) != 0)
			return ret;
	} while (readback != value && ++wcount < MAX17261_RB_THRESHOLD);
	return ((readback == value) ? 0 : 0x04);
}

/**
 * @brief Delay function
 * @param conf
 * @param period
 * @return
 */
__attribute__((weak)) max17261_err_t
max17261_delay_ms(struct max17261_conf *conf, uint32_t period)
{
#ifndef MAX17261_USE_WEAK
	return conf->delay_ms(period);
#else
	return 0;
#endif
}

