/*
 *HwEeprom.h
 */


#ifndef HW_EEPROM_H
#define HW_EEPROM_H

#include <stdint.h>
#include <stddef.h>
#include "stm32h7xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

// EEPROM Hardware Configuration
#define EEPROM_I2C_ADDRESS  0xA0
#define EEPROM_PAGE_SIZE    256                // EEPROM Page Size
#define EEPROM_TOTAL_SIZE   262143           // Total EEPROM Size in Bytes


typedef enum {
    EEPROM_OK = 0,
    EEPROM_ERROR,
    EEPROM_BUSY,
    EEPROM_TIMEOUT
} HwEepromStatus_t;

// Initialize EEPROM hardware (I2C)
HwEepromStatus_t HwEepromInit(void);

// Write a single byte to EEPROM
HwEepromStatus_t HwEepromWriteByte(uint32_t address, uint8_t data);

// Write multiple bytes to EEPROM
HwEepromStatus_t HwEepromWrite(uint32_t address, uint8_t *data, size_t length);

// Read a single byte from EEPROM
HwEepromStatus_t HwEepromReadByte(uint32_t address, uint8_t *data);

// Read multiple bytes from EEPROM
HwEepromStatus_t HwEepromRead(uint32_t address, uint8_t *data, size_t length);

// Wait for EEPROM Write Cycle to complete
HwEepromStatus_t HwEepromWaitForReady(void);

#ifdef __cplusplus
}
#endif

#endif /* HW_EEPROM_H */
