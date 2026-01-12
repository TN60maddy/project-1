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
*   This file implements a generic Hardware Level API's of EEPROM used in Infusion Pump
*
********************************************************************************/

#include "../../HwEeprom/Inc/HwEepromCtrl.h"

#include <string.h>
#include <stdio.h>
#include "../../HwEeprom/Inc/HwEeprom.h"
#include "stm32h7xx_hal.h"

extern I2C_HandleTypeDef HwI2CMux_Handler;
#define EEPROM_SIGNATURE_VALUE 0xDEADBEEF
#define EEPROM_SIGNATURE_ADDRESS (EEPROM_TOTAL_SIZE - 4)


/**
  * @brief
  *        Initializes the EEPROM peripheral and ensures its accessibility.
  *        This function performs the following tasks:
  *        1. Initializes the EEPROM peripheral (e.g., I2C or SPI interface).
  *        2. Checks if the EEPROM is accessible and responsive.
  *        3. Verifies if the EEPROM contains valid data (e.g., by checking a predefined signature or checksum).
  *        4. Formats the EEPROM if it is not already formatted or contains invalid data.
  *
  * @param void
  @retval HwEepromCtrl_Status_t
  *         The status of the initialization process, which can be one of the following:
  *         - HwEepromCtrl_OK: EEPROM initialized and ready for use.
  *         - HwEepromCtrl_ERROR: Initialization & accessibility failed.
  */

HwEepromCtrl_Status_t HwEepromCtrl_Init(void)
{
    if (HwEepromInit() != EEPROM_OK)
    {
        return HwEepromCtrl_ERROR;
    }
    // Check EEPROM accessibility
    uint8_t testByte = 0x55;
    uint8_t readByte = 0x00;
    if (HwEepromWriteByte(0, testByte) != EEPROM_OK || HwEepromReadByte(0, &readByte) != EEPROM_OK)
    {
        return HwEepromCtrl_ERROR;
    }

    if (readByte != testByte)
    {
        return HwEepromCtrl_ERROR;
    }


    /* Check for a valid data structure (Optional) */
    uint8_t magic[4] = {0};
    HwEepromRead(0, magic, sizeof(magic));

	if (magic[0] != 'E' || magic[1] != 'E' || magic[2] != 'P' || magic[3] != 'R') {
	// If not formatted, format EEPROM
	return HwEepromCtrl_Format();
	}

	return HwEepromCtrl_OK;
}

/**
  * @brief
  *        Stores data in the EEPROM at the specified address.
  *        This function writes a block of data to the EEPROM starting from the given address.
  * @param address -  The starting address in the EEPROM where the data will be stored.
  *        data    -  A pointer to the data buffer that will be written to the EEPROM.
  *        length  -  The number of bytes to write from the data buffer.
  * * @retval HwEepromCtrl_Status_t
  *         The status of the store operation, which can be one of the following:
  *         - HwEepromCtrl_OK: Data stored successfully.
  *         - HwEepromCtrl_ERROR: Operation failed.
  *         - HwEepromCtrl_INVALID_PARAM: Invalid address, data pointer, or length provided.
  */

HwEepromCtrl_Status_t HwEepromCtrl_StoreData(uint32_t address, uint8_t *data, size_t length) {
    if (data == NULL || length == 0) {
        return HwEepromCtrl_INVALID_PARAM;
    }

    if (HwEepromWrite(address, data, length) != EEPROM_OK) {
        return HwEepromCtrl_ERROR;
    }
    return HwEepromCtrl_OK;
}

/**
  * @brief
  *        Retrieves data from the EEPROM starting at the specified address.
  *        This function reads a block of data from the EEPROM starting from the given address and stores it
  *        in the provided data buffer.
  *  @param address
  *        The starting address in the EEPROM from which the data will be read.
  *        data
  *        A pointer to the buffer where the retrieved data will be stored.
  *        length
  *        The number of bytes to read from the EEPROM.
  *  @retval HwEepromCtrl_Status_t
  *         The status of the retrieve operation, which can be one of the following:
  *         - HwEepromCtrl_OK: Data retrieved successfully and stored in the buffer.
  *         - HwEepromCtrl_ERROR: Operation failed.
  *         - HwEepromCtrl_INVALID_PARAM: Invalid address, data pointer, or length provided.
  */

HwEepromCtrl_Status_t HwEepromCtrl_RetrieveData(uint32_t address, uint8_t *data, size_t length) {
    if (data == NULL || length == 0) {
        return HwEepromCtrl_INVALID_PARAM;
    }

    if (HwEepromRead(address, data, length) != EEPROM_OK) {
        return HwEepromCtrl_ERROR;
    }
    return HwEepromCtrl_OK;
}

/**
  * @brief
  *        Erases a block of data in the EEPROM starting from the specified address.
  *        This function erases a specified number of bytes from the EEPROM, starting at the given address.
  *  @param address
  *        The starting address in the EEPROM from which the erase operation will begin.
  *        length
  *        The number of bytes to erase from the EEPROM.
  *         * @retval HwEepromCtrl_Status_t
  *         The status of the erase operation, which can be one of the following:
  *         - HwEepromCtrl_OK: Data erased successfully.
  *         - HwEepromCtrl_ERROR: Operation failed.
  *         - HwEepromCtrl_INVALID_PARAM: Invalid address or length provided.
  */


HwEepromCtrl_Status_t HwEepromCtrl_Erase(uint32_t address, size_t length) {
    if (length == 0) {
        return HwEepromCtrl_INVALID_PARAM;
    }
    uint8_t eraseData[length];
    memset(eraseData, 0xFF, length);

    if (HwEepromWrite(address, eraseData, length) != EEPROM_OK) {
        return HwEepromCtrl_ERROR;
    }
    return HwEepromCtrl_OK;
}

/**
  * @brief
  *        Formats the entire EEPROM memory.
  *        This function erases all data in the EEPROM and prepares it for reuse.
  * @param void
  *  * @retval HwEepromCtrl_Status_t
  *         - HwEepromCtrl_OK: EEPROM formatted successfully.
  *         - HwEepromCtrl_ERROR: Operation failed.
  */
HwEepromCtrl_Status_t HwEepromCtrl_Format(void) {
    uint8_t emptyBuffer[EEPROM_PAGE_SIZE];  // Buffer filled with 0xFF
    memset(emptyBuffer, 0xFF, EEPROM_PAGE_SIZE);
    for (uint32_t addr = 0; addr < EEPROM_TOTAL_SIZE; addr += EEPROM_PAGE_SIZE) {
        if (HwEepromWrite(addr, emptyBuffer, EEPROM_PAGE_SIZE) != EEPROM_OK) {
            return HwEepromCtrl_ERROR;
        }
    }
    uint32_t signature = EEPROM_SIGNATURE_VALUE;
    if (HwEepromWrite(EEPROM_SIGNATURE_ADDRESS, (uint8_t*)&signature, sizeof(signature)) != EEPROM_OK) {
        return HwEepromCtrl_ERROR;
    }
    else
    {
    	  uint32_t readSignature = 0;

    	  // Read the last 4 bytes of EEPROM where the signature should be stored
    	  if (HwEepromRead(EEPROM_SIGNATURE_ADDRESS, (uint8_t*)&readSignature, sizeof(readSignature)) != EEPROM_OK) {
    	      printf("EEPROM Read Error!\r\n");
    	      return HwEepromCtrl_ERROR;
    	  }

    	  // Check if the signature is valid
    	  if (readSignature == 0xdeadbeef) {
    	      return HwEepromCtrl_OK;
    	  } else {
    	      return HwEepromCtrl_ERROR;
    	  }
    }
    return HwEepromCtrl_OK;
}

