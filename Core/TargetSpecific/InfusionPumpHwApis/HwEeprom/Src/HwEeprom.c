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
*   This file implements a generic Middle Level Layer of EEPROM used in Infusion Pump
*
********************************************************************************/
#include "../../HwEeprom/Inc/HwEeprom.h"
#include "../../HwEeprom/Inc/HwEepromConfig.h"
#include "../../HwEeprom/Inc/HwEepromCtrl.h"
#include "../../HwI2CMux/inc/HwI2CMux.h"
#include <math.h>
#include <string.h>

extern I2C_HandleTypeDef HwI2CMux_Handler;

#define EEPROM_I2C_TIMEOUT 100
#define EEPROM_I2C_BASE_ADDR 0x50 // Base address (A2, A1, A0 = 000)

// Get the correct I2C device address based on the upper bits of the EEPROM address
#define GET_EEPROM_I2C_ADDRESS(addr) (EEPROM_I2C_BASE_ADDR | ((addr >> 16) & 0x03))


/**
  * @brief
  *        Initializes the I2C channel connected to the EEPROM.
  *        This function configures the I2C peripheral and initializes the communication channel
  *        used to interact with the EEPROM. It ensures that the I2C interface is ready for read/write operations.
  * @param void
  *
  * @retval HwEepromStatus_t
  *         The status of the EEPROM initialization, which can be one of the following:
  *         - EEPROM_OK      : I2C channel initialized successfully.
  *         - EEPROM_ERROR   : Initialization failed due to an error.
  *
  */

HwEepromStatus_t HwEepromInit(void) {
    if (HwI2CMux_Init() == HAL_OK) {
        if (HwI2CMux_CHSEL(HwI2CMux_EEPROM_CHN) != HAL_OK) {
            return EEPROM_ERROR;
        }
    } else {
        return EEPROM_ERROR;
    }
    return EEPROM_OK;
}

/**
  * @brief
  *        Writes a single byte of data to the specified address in the EEPROM.
  *  @param address = The memory address in the EEPROM where the data byte will be written.
  *        data     = The byte of data to be written to the EEPROM.
  *  @retval HwEepromStatus_t
  *           EEPROM_OK: Data byte written successfully.
  *           EEPROM_ERROR: Write operation failed.
  */


HwEepromStatus_t HwEepromWriteByte(uint32_t address, uint8_t data) {
    return HwEepromWrite(address, &data, 1);
}

/**
  * @brief
  *        Writes no of bytes of data from the specified address in the EEPROM.
  *  @param address = The memory address in the EEPROM where the data byte will be written.
  *        data     = The bytes of data to be written to the EEPROM.
  *        length   = No.of.bytes to be written.
  *  @retval HwEepromStatus_t
  *           EEPROM_OK: Data byte written successfully.
  *           EEPROM_ERROR: Write operation failed.
  */



HwEepromStatus_t HwEepromWrite(uint32_t address, uint8_t *data, size_t length) {
    if (data == NULL || length == 0) {
        return EEPROM_ERROR; // Invalid input
    }

 //   int paddrposition = log(EEPROM_PAGE_SIZE) / log(2);
    uint32_t startPage = address / EEPROM_PAGE_SIZE;
    uint16_t offset = address % EEPROM_PAGE_SIZE;

    uint32_t endPage = startPage + ((length + offset + EEPROM_PAGE_SIZE - 1) / EEPROM_PAGE_SIZE);
    uint32_t numofpages = endPage - startPage;
    uint32_t pos = 0;

    for (uint32_t i = 0; i < numofpages; i++) {
        uint8_t eepromAddress = GET_EEPROM_I2C_ADDRESS(address);
        uint16_t memAddress = address & 0xFFFF; // Lower 16 bits of address

        uint16_t bytesToWrite = EEPROM_PAGE_SIZE - offset;
        if (bytesToWrite > (length - pos)) {
            bytesToWrite = length - pos;
        }

        if (HAL_I2C_Mem_Write(&HwI2CMux_Handler, eepromAddress << 1, memAddress,
                              I2C_MEMADD_SIZE_16BIT, &data[pos], bytesToWrite, EEPROM_I2C_TIMEOUT) != HAL_OK) {
            return EEPROM_ERROR;
        }

        HAL_Delay(7); // Ensure write cycle completion

        address += bytesToWrite; // Move to the next address
        offset = 0; // Reset offset
        pos += bytesToWrite;
    }
    return EEPROM_OK;
}

/**
  * @brief
  *        Reads a single byte of data to the specified address in the EEPROM.
  *  @param address  = The memory address in the EEPROM where the data byte will read.
  *         data     = A pointer to a variable where the read data byte will be stored.
  *  @retval HwEepromStatus_t
  *           EEPROM_OK: Data byte read successfully.
  *           EEPROM_ERROR: Read operation failed.
  */

HwEepromStatus_t HwEepromReadByte(uint32_t address, uint8_t *data) {
    return HwEepromRead(address, data, 1);
}

/**
  * @brief
  *        Reads no of bytes of data from the specified address in the EEPROM.
  *  @param address = The starting memory address in the EEPROM where the data byte will be read.
  *        data     = A pointer to a variable where the read data bytes will be stored.
  *        length   = No.of.bytes to be read.
  *  @retval HwEepromStatus_t
  *           EEPROM_OK: Data byte written successfully.
  *           EEPROM_ERROR: Write operation failed.
  */

HwEepromStatus_t HwEepromRead(uint32_t address, uint8_t *data, size_t length) {
    if (data == NULL || length == 0) {
        return EEPROM_ERROR;
    }

//    int paddrposition = log(EEPROM_PAGE_SIZE) / log(2);
    uint32_t startPage = address / EEPROM_PAGE_SIZE;
    uint16_t offset = address % EEPROM_PAGE_SIZE;

    uint32_t endPage = startPage + ((length + offset) / EEPROM_PAGE_SIZE);
    uint32_t numofpages = (endPage - startPage) + 1;
    uint32_t pos = 0;

    for (uint32_t i = 0; i < numofpages; i++) {
        uint8_t eepromAddress = GET_EEPROM_I2C_ADDRESS(address);
        uint16_t memAddress = address & 0xFFFF; // Lower 16 bits of address

        uint16_t bytesToRead = EEPROM_PAGE_SIZE - offset;
        if (bytesToRead > (length - pos)) {
            bytesToRead = length - pos;
        }

        if (HAL_I2C_Mem_Read(&HwI2CMux_Handler, eepromAddress << 1, memAddress,
                             I2C_MEMADD_SIZE_16BIT, &data[pos], bytesToRead, EEPROM_I2C_TIMEOUT) != HAL_OK) {
            return EEPROM_ERROR;
        }

        address += bytesToRead;
        offset = 0;
        pos += bytesToRead;
    }

    return EEPROM_OK;
}

/**
  * @brief
  *        Waits for the EEPROM to become ready for the next operation.
  * @param void
*   @retval HwEepromStatus_t
  *           EEPROM_OK: EEPROM is ready for next Operation.
  *           EEPROM_TIMEOUT: The function timed out while waiting for the EEPROM to become read.
  */

HwEepromStatus_t HwEepromWaitForReady(void) {
    uint32_t timeout = HAL_GetTick() + 50;
    while (HAL_I2C_IsDeviceReady(&HwI2CMux_Handler, EEPROM_I2C_BASE_ADDR << 1, 10, EEPROM_I2C_TIMEOUT) != HAL_OK) {
        if (HAL_GetTick() > timeout) {
            return EEPROM_TIMEOUT;
        }
    }
    return EEPROM_OK;
}
