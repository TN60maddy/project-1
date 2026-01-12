/*
 * HwTCA9546_Mux.h
 *
 */




#ifndef INC_HWI2CMUX_H_
#define INC_HWI2CMUX_H_

#include "stdio.h"
#include "stdint.h"
#include "stm32h7xx_hal.h"

#define HwI2CMux_EEPROM_CHN         0
#define HwI2CMux_FUELGAUGE_CHN      1
#define HwI2CMux_PWRIC_CHN          2
#define HwI2CMux_TOUCHCONTROLLER_CHN    3


uint8_t HwI2CMux_Init();
uint8_t HwI2CMux_CHSEL(int Channel);
uint8_t Hw_TCA9546_Mux_I2C_Receive(uint8_t Slaveaddr, uint8_t *rdata, uint16_t length);
uint8_t Hw_TCA9546_Mux_I2C_Transmit(uint8_t Slaveaddr, uint8_t *tdata,uint16_t length);



#endif /* INC_HWI2CMUX_H_ */


