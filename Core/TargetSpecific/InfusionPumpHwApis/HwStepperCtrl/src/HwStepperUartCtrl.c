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
*   This file implements a generic HW Interface Stepper Motors UART Control used in Infusion Pump
*
********************************************************************************/

/* Stepper Motor Register Address Details*/

#include <stdio.h>
#include <stdint.h>
#include "HwStepperCtrl.h"
#include "stm32h7xx_hal.h"
#include "HwStepperConfig.h"


#define IRUN_DEFAULT        		31


#define ADDRESS_IHOLD_IRUN 			0x10
#define CURRENT_SETTING_MIN 		0
#define ADDRESS_GCONF 				0x00
#define CURRENT_SETTING_MIN 		0
#define ADDRESS_IHOLD_IRUN 			0x10
#define SEIMIN_LOWER_SETTING       	0
#define SEIMIN_UPPER_SETTING       	1



#define WRITE_READ_REPLY_DATAGRAM_SIZE 	8
#define DATA_SIZE                      	4
#define SEIMIN_UPPER_CURRENT_LIMIT 		20
#define ADDRESS_COOLCONF           		0x42


#define SYNC                      0b101
#define RW_READ                   0
#define RW_WRITE                  1

#define BYTE_MAX_VALUE 			0xFF
#define BITS_PER_BYTE  			8

extern UART_HandleTypeDef HwStepper1UartHandle_;
extern UART_HandleTypeDef HwStepper2UartHandle_;

#define READ_REQUEST_DATAGRAM_SIZE 4
uint32_t StepperUART_read(UART_HandleTypeDef *HwStpUartHand,uint8_t register_address);


static void StepperUART_write(UART_HandleTypeDef *HwStpUartHand, uint8_t register_address, uint32_t data );

typedef enum
{
  SERIAL_ADDRESS_0 = 0,
  SERIAL_ADDRESS_1 = 1,
  SERIAL_ADDRESS_2 = 2,
  SERIAL_ADDRESS_3 = 3,
} tmc2300_serial_address_t;


typedef union
{
  struct
  {
    uint32_t semin : 4;
    uint32_t reserved_0 : 1;
    uint32_t seup : 2;
    uint32_t reserved_1 : 1;
    uint32_t semax : 4;
    uint32_t reserved_2 : 1;
    uint32_t sedn : 2;
    uint32_t seimin : 1;
    uint32_t reserved_3 : 16;
  };
  uint32_t bytes;
}cool_step_config_t;

typedef union
{
  struct
  {
    uint32_t ihold : 5;
    uint32_t reserved_0 : 3;
    uint32_t irun : 5;
    uint32_t reserved_1 : 3;
    uint32_t iholddelay : 4;
    uint32_t reserved_2 : 12;
  };
  uint32_t bytes;
}driver_current_t;

typedef union
{
  struct
  {
    uint32_t enabledrv : 1;//toff : 4;
    uint32_t reserved_0 : 14;
    uint32_t tbl : 2;
    uint32_t reserved_1 : 7;
    uint32_t mres : 4;
    uint32_t interpolation : 1;
    uint32_t double_edge : 1;
    uint32_t diss2g : 1;
    uint32_t diss2vs : 1;
  };
  uint32_t bytes;
} chopper_config_t;


typedef union
{
  struct
  {
    uint64_t sync : 4;
    uint64_t reserved : 4;
    uint64_t serial_address : 8;
    uint64_t register_address : 7;
    uint64_t rw : 1;
    uint64_t data : 32;
    uint64_t crc : 8;
  };
  uint64_t bytes;
} write_read_reply_datagram_t;


typedef union
{
  struct
  {
    uint32_t sync : 4;
    uint32_t reserved : 4;
    uint32_t serial_address : 8;
    uint32_t register_address : 7;
    uint32_t rw : 1;
    uint32_t crc : 8;
  };
  uint32_t bytes;
} read_request_datagram_t;

/**
  * @brief Reverses the byte order of a 32-bit data value.
  *
  * This function swaps the byte order of a 32-bit integer, which is
  * useful when dealing with communication protocols that require
  * little-endian to big-endian conversion.
  *
  * @param data The 32-bit data to be reversed.
  *
  * @retval uint32_t The reversed 32-bit data.
  */

uint32_t HW_StepperData_Reverse(uint32_t data)
{
	  uint32_t reversed_data = 0;
	  uint8_t  right_shift;
	  uint8_t  left_shift;
	  for (uint8_t i = 0; i < DATA_SIZE; ++i)
	  {
	    right_shift = (DATA_SIZE - i - 1) * BITS_PER_BYTE;
	    left_shift  = i * BITS_PER_BYTE;
	    reversed_data |= ((data >> right_shift) & BYTE_MAX_VALUE) << left_shift;
	  }
	  return reversed_data;
}

/**
  * @brief Computes the CRC checksum for a write datagram.
  *
  * This function calculates the cyclic redundancy check (CRC)
  * for a write-read datagram to ensure data integrity.
  *
  * @param datagram Pointer to the write-read reply datagram structure.
  * @param datagram_size Size of the datagram in bytes.
  *
  * @retval uint8_t Computed CRC value.
  */

uint8_t Hw_Stepper_Write_CRC(write_read_reply_datagram_t *datagram, uint8_t datagram_size)
{
  uint8_t crc = 0;
  uint8_t byte;
  uint8_t datagram_bytes[7];

  for (int i = 0; i < datagram_size - 1; i++)
  {
    datagram_bytes[i] = (datagram->bytes >> (i * BITS_PER_BYTE)) & BYTE_MAX_VALUE;
  }
  for (uint8_t i = 0; i < (datagram_size - 1); ++i)
  {
    byte = datagram_bytes[i];
    for (uint8_t j = 0; j < BITS_PER_BYTE; ++j)
    {
      if ((crc >> 7) ^ (byte & 0x01))
      {
        crc = (crc << 1) ^ 0x07;
      }
      else
      {
        crc = crc << 1;
      }
      byte = byte >> 1;
    }
  }
  return crc;
}

/**
  * @brief Computes the CRC checksum for a read request datagram.
  *
  * This function calculates the cyclic redundancy check (CRC)
  * for a read request datagram.
  *
  * @param datagram Pointer to the read request datagram structure.
  * @param datagram_size Size of the datagram in bytes.
  *
  * @retval uint8_t Computed CRC value.
  */

uint8_t Hw_Stepper_read_CRC(read_request_datagram_t *datagram, uint8_t datagram_size)
{
  uint8_t crc = 0;
  uint8_t byte;
  uint8_t datagram_bytes[4];
  for (int i = 0; i < (datagram_size - 1); i++)
  {
    datagram_bytes[i] = (datagram->bytes >> (i * BITS_PER_BYTE)) & BYTE_MAX_VALUE;
  }
  for (uint8_t i = 0; i < (datagram_size - 1); ++i)
  {
    byte = datagram_bytes[i];
    for (uint8_t j = 0; j < BITS_PER_BYTE; ++j)
    {
      if ((crc >> 7) ^ (byte & 0x01))
      {
        crc = (crc << 1) ^ 0x07;
      }
      else
      {
        crc = crc << 1;
      }
      byte = byte >> 1;
    }
  }
  return crc;
}
/**
* @brief Configures the current control settings for the stepper motor.
*
* This function sets various motor control parameters such as
* current, chopper configuration, and cool-step configuration.
*
* @param HwStpUartHand Pointer to the UART handle used for communication.
*/

void Hw_StepperMtr_CurCtrl(UART_HandleTypeDef *HwStpUartHand)
{
	driver_current_t stepper_current;
	cool_step_config_t cool_step;
	chopper_config_t chopper_config;
  /* Configure the Global Configuration */
	StepperUART_write(HwStpUartHand,ADDRESS_GCONF,0x0);

	chopper_config.enabledrv = 0x1;
	chopper_config.reserved_0 = 0x0000;
	chopper_config.tbl = 0x1;
	chopper_config.reserved_1 = 0x00;
	chopper_config.mres = 0x8;
	chopper_config.interpolation = 0x1;
	chopper_config.double_edge = 0x0;
	chopper_config.diss2g = 0x0;
	chopper_config.diss2vs = 0x0;

	StepperUART_write(HwStpUartHand,ADDRESS_CHOPCONF, chopper_config.bytes);

  /* Control Motor Current */
	stepper_current.irun = IRUN_DEFAULT;
//	stepper_current.irun = Current;
	stepper_current.ihold = CURRENT_SETTING_MIN;


	StepperUART_write(HwStpUartHand,ADDRESS_IHOLD_IRUN,stepper_current.bytes);                          //stepper_current.bytes
	if (stepper_current.irun >= SEIMIN_UPPER_CURRENT_LIMIT)
	  {
		cool_step.seimin = SEIMIN_UPPER_SETTING;
	  }
	  else
	  {
		  cool_step.seimin = SEIMIN_LOWER_SETTING;
	  }

	StepperUART_write(HwStpUartHand,ADDRESS_COOLCONF, cool_step.bytes);

	StepperUART_read(HwStpUartHand,0x6C);


}

/**
  * @brief Writes data to a specific register of the stepper motor driver over UART.
  *
  * @param HwStpUartHand Pointer to the UART handle.
  * @param register_address The register address to write to.
  * @param data The 32-bit data to write.
  */

static void StepperUART_write(UART_HandleTypeDef *HwStpUartHand, uint8_t register_address, uint32_t data )
 {
   write_read_reply_datagram_t write_datagram;
   write_datagram.bytes            = 0;
   write_datagram.sync             = SYNC;
   write_datagram.serial_address   = SERIAL_ADDRESS_0;
   write_datagram.register_address = register_address;
   write_datagram.rw               = RW_WRITE;
   write_datagram.data             = HW_StepperData_Reverse(data);
   write_datagram.crc              = Hw_Stepper_Write_CRC(&write_datagram, WRITE_READ_REPLY_DATAGRAM_SIZE);

   uint8_t datagram_bytes[8];
   for (int i = 0; i < 8; i++)
   {
     datagram_bytes[i] = (write_datagram.bytes >> (i * BITS_PER_BYTE)) & BYTE_MAX_VALUE;
   }
    HAL_HalfDuplex_EnableTransmitter(HwStpUartHand);
    HAL_UART_Transmit(HwStpUartHand, datagram_bytes, WRITE_READ_REPLY_DATAGRAM_SIZE, 0XFFFF);

 }

/**
  * @brief Reads data from a specific register of the stepper motor driver over UART.
  *
  * @param HwStpUartHand Pointer to the UART handle.
  * @param register_address The register address to read from.
  *
  * @retval uint32_t The read data.
  */

uint32_t StepperUART_read(UART_HandleTypeDef *HwStpUartHand,uint8_t register_address)
 {
   read_request_datagram_t read_request_datagram;
   read_request_datagram.bytes            = 0;
   read_request_datagram.sync             = SYNC;
   read_request_datagram.serial_address   = SERIAL_ADDRESS_0;
   read_request_datagram.register_address = register_address;
   read_request_datagram.rw               = RW_READ;
   read_request_datagram.crc              = Hw_Stepper_read_CRC(&read_request_datagram, READ_REQUEST_DATAGRAM_SIZE);

   uint8_t datagram_bytes[WRITE_READ_REPLY_DATAGRAM_SIZE];

   for (int i = 0; i < READ_REQUEST_DATAGRAM_SIZE; ++i)
   {
     datagram_bytes[i] = (read_request_datagram.bytes >> (i * BITS_PER_BYTE)) & BYTE_MAX_VALUE;
   }

   HAL_HalfDuplex_EnableTransmitter(HwStpUartHand);
   HAL_UART_Transmit(HwStpUartHand, datagram_bytes, READ_REQUEST_DATAGRAM_SIZE, 0XFFFF);

   uint8_t                     byte       = 0;
   uint8_t                     byte_count = 0;
   write_read_reply_datagram_t read_reply_datagram;
   read_reply_datagram.bytes = 0;

   HAL_HalfDuplex_EnableReceiver(HwStpUartHand);

   for (uint8_t i = 0; i < WRITE_READ_REPLY_DATAGRAM_SIZE; ++i)
   {
     HAL_UART_Receive(HwStpUartHand, (uint8_t *)&byte, 1, 100);
     datagram_bytes[i] = byte;
   }

   for (uint8_t i = 0; i < WRITE_READ_REPLY_DATAGRAM_SIZE; ++i)
   {
     read_reply_datagram.bytes |= ((uint64_t)datagram_bytes[i] << (byte_count++ * BITS_PER_BYTE));
   }
   uint32_t reversed_data = HW_StepperData_Reverse(read_reply_datagram.data);
   uint8_t  crc           = Hw_Stepper_Write_CRC(&read_reply_datagram, WRITE_READ_REPLY_DATAGRAM_SIZE);

   if (crc != read_reply_datagram.crc)
   {
   }
   return reversed_data;
 }




