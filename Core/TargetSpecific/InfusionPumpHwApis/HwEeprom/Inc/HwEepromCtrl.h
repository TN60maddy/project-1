/*
 *HwEepromCtrl.h
 */

#ifndef HW_EEPROM_CTRL_H
#define HW_EEPROM_CTRL_H

#include <stdint.h>
#include <stddef.h>
#include "stm32h7xx_hal.h"
#ifdef __cplusplus
extern "C" {
#endif

// EEPROM Middleware API Status
typedef enum {
    HwEepromCtrl_OK = 0,
    HwEepromCtrl_ERROR,
    HwEepromCtrl_INVALID_PARAM,
    HwEepromCtrl_FULL
} HwEepromCtrl_Status_t;



HwEepromCtrl_Status_t HwEepromCtrl_Init(void);

// Store structured data in EEPROM
HwEepromCtrl_Status_t HwEepromCtrl_StoreData(uint32_t address, uint8_t *data, size_t length);

// Retrieve structured data from EEPROM
HwEepromCtrl_Status_t HwEepromCtrl_RetrieveData(uint32_t address, uint8_t *data, size_t length);

// Erase specific EEPROM section
HwEepromCtrl_Status_t HwEepromCtrl_Erase(uint32_t address, size_t length);

HwEepromCtrl_Status_t HwEepromCtrl_Format(void);

#ifdef __cplusplus
}
#endif

#endif /* HW_EEPROM_CTRL_H */
