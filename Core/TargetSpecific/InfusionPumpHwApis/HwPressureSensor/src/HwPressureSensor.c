/*******************************************************************************
 * @file    HwPressureSensor.c
 * @brief   Hardware Interface for Pressure Sensor in Infusion Pump
 * @author  Radhakrishnan Rajaram
 * @company Aria Innovations Private Limited
 * @version 1.0
 * @date    25/03/2025
 *
 * Copyright (c) 2025 Aria Innovations Private Limited.
 * All rights reserved.
 *
 * This file provides the implementation for the pressure sensor interface used
 * in the infusion pump system. It includes initialization, data extraction,
 * and calculations for pressure and temperature values.
 *
 *******************************************************************************/

#include "HwPressureSensor.h"
#include "HwPressureSensorConfig.h"
#include "infusion_platform.h"
#include "infusion_safety.h"
#include "stm32h7xx_hal.h"

// Define macros for each operation
#define EXTRACT_STATUS(data0) (((data0) & 0xC0) >> 6)
#define EXTRACT_PRESSURE(data0, data1) ((((data0) & 0x3F) << 8) | (data1))
/* 11-bit temperature: 8 bits from data2, 3 bits from top of data3 (bits 7,6,5)
 */
#define EXTRACT_TEMPERATURE(data2, data3)                                      \
  ((((data2) & 0xFF) << 3) | (((data3) & 0xE0) >> 5))

/*Private data */

#define NUM_OF_BYTES 4

typedef struct {
  uint8_t Status;
  uint16_t RawPressureData;
  uint16_t RawTemperatureData;
} HwPressureSensorDatabitfield_s;

/*Private Function declaration*/
static HwPressureSensorDatabitfield_s HwPressureDataExtract(uint8_t Data[4]);
static float HwPressureCal(uint16_t PressureCount);
static float HwTemparatureCal(uint8_t TemperatureCount);
static int HwPressureStatusToErr(uint8_t status);

/*
 * I2C Handlers Definition
 * */
static I2C_HandleTypeDef HwPressureSensor1_handler;
static I2C_HandleTypeDef HwPressureSensor2_handler;

/* Private Definition */
#define PRESSURE_SENSOR1_CHN 1
#define PRESSURE_SENSOR2_CHN 1

/**
 * @brief
 *        Initializes the I2C peripheral for the specified pressure sensor.
 *        This function configures the I2C communication interface for the
 * selected pressure sensor, ensuring that it is ready for data read/write
 * operations.
 *   * @param hwPressure
 *        The pressure sensor to initialize, specified as a value of type
 * `HwPressureSensorNum_t`. Valid values are:
 *        - HW_PRESSURE_NUM_1: Initialize pressure sensor 1.
 *        - HW_PRESSURE_NUM_2: Initialize pressure sensor 2.
 *   * @retval int
 *         0 = Success (Pressure sensor I2C peripheral initialized
 * successfully). 1 = Failure (Initialization failed due to an error or invalid
 * sensor number).
 */

int HwPressureSensorInit(HwPressureSensorNum_t hwPressure) {
  int retStatus = 0;
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  uint8_t PS_Channel;

  /*
   * Initialize the HW modules for each Stepper Motor interface like PWM output,
   */
  switch (hwPressure) {
  case HW_PRESSURE_NUM_1:
    PS_Channel = PRESSURE_SENSOR1_CHN;

    /* Initialize the Peripheral Clocks */
    PeriphClkInitStruct.PeriphClockSelection = HW_PRESSURE1_PER_CLOCK;
    PeriphClkInitStruct.I2c123ClockSelection = HW_PRESSURE1_PER_CLOCK_SRC;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
      retStatus = -1;
      return retStatus;
    } else {

      /* Enable GPIO Clock for I2C2 */

      /* Enable GPIO Clock for I2C2 */
      /* NOTE: This enables GPIOB, which is used by BOTH sensors.
       * Ideally this should be called once for the system or checked in both
       * cases. Moving it here is fine if Sensor 1 is always init first, but for
       * safety we should ensure it.
       */
      HW_PRESSURE_SENSOR_GPIO_CLK_ENABLE();

      GPIO_InitStruct.Pin = HW_PRESSURE1_SCL_PIN | HW_PRESSURE1_SDA_PIN;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate = HW_PRESSURE1_GPIO_ALT_FUN;
      HAL_GPIO_Init(HW_PRESSURE1_SDA_PORT, &GPIO_InitStruct);

      /* Peripheral Clock Enable */
      __HAL_RCC_I2C2_CLK_ENABLE();

      /*
       * Initialize I2C for Pressure Sensor 1
       */
      HwPressureSensor1_handler.Instance = HW_PRESSURE1_I2C;
      HwPressureSensor1_handler.Init.Timing = HW_PRESSURE1_TIMING_PARAMETER;
      HwPressureSensor1_handler.Init.OwnAddress1 = 0;
      HwPressureSensor1_handler.Init.AddressingMode = HW_PRESSURE1_ADDRESS_MODE;
      HwPressureSensor1_handler.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
      HwPressureSensor1_handler.Init.OwnAddress2 = 0;
      HwPressureSensor1_handler.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
      HwPressureSensor1_handler.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
      HwPressureSensor1_handler.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
      if (HAL_I2C_Init(&HwPressureSensor1_handler) != HAL_OK) {
        retStatus = -1;
      }

      /** Configure Analogue filter
       */
      if (HAL_I2CEx_ConfigAnalogFilter(&HwPressureSensor1_handler,
                                       I2C_ANALOGFILTER_ENABLE) != HAL_OK) {
        retStatus = -1;
      }

      /** Configure Digital filter
       */
      if (HAL_I2CEx_ConfigDigitalFilter(&HwPressureSensor1_handler, 0) !=
          HAL_OK) {
        retStatus = -1;
      }
    }
    /* Enable the mux channel with a bounded timeout (no HAL_MAX_DELAY in safety
     * code). */
    if (HAL_I2C_Master_Transmit(
            &HwPressureSensor1_handler, HW_PRESSURE1_MUX_ADDR, &PS_Channel,
            sizeof(PS_Channel), INF_I2C_TIMEOUT_MS_INIT) != HAL_OK) {
      retStatus = -1;
    }

    break;
  case HW_PRESSURE_NUM_2:
    PS_Channel = PRESSURE_SENSOR2_CHN;
    /** Initializes the peripheral clock for Pressure Sensor 2
     */
    PeriphClkInitStruct.PeriphClockSelection = HW_PRESSURE2_PER_CLOCK;
    PeriphClkInitStruct.I2c4ClockSelection = HW_PRESSURE2_PER_CLOCK_SEL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
      retStatus = -1;
    }

    /*Enable GPIO Clock for Pressure Sensor 2 */
    else {
      /* Ensure GPIO Clock is enabled (shared with Sensor 1) */
      HW_PRESSURE_SENSOR_GPIO_CLK_ENABLE();

      GPIO_InitStruct.Pin = HW_PRESSURE2_SDA_PIN | HW_PRESSURE2_SCL_PIN;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate = HW_PRESSURE2_GPIO_ALT_FUN;
      HAL_GPIO_Init(HW_PRESSURE2_SDA_PORT, &GPIO_InitStruct);

      HW_PRESSURE2_CLK_ENABLE();

      /*
       * Initialize I2C for Pressure Sensor 1
       */
      HwPressureSensor2_handler.Instance = HW_PRESSURE2_I2C;
      HwPressureSensor2_handler.Init.Timing = HW_PRESSURE2_TIMING_PARAMETER;
      HwPressureSensor2_handler.Init.OwnAddress1 = 0;
      HwPressureSensor2_handler.Init.AddressingMode = HW_PRESSURE2_ADDRESS_MODE;
      HwPressureSensor2_handler.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
      HwPressureSensor2_handler.Init.OwnAddress2 = 0;
      HwPressureSensor2_handler.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
      HwPressureSensor2_handler.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
      HwPressureSensor2_handler.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
      if (HAL_I2C_Init(&HwPressureSensor2_handler) != HAL_OK) {
        retStatus = -1;
      }

      /** Configure Analogue filter
       */
      if (HAL_I2CEx_ConfigAnalogFilter(&HwPressureSensor2_handler,
                                       I2C_ANALOGFILTER_ENABLE) != HAL_OK) {
        retStatus = -1;
      }

      /** Configure Digital filter
       */
      if (HAL_I2CEx_ConfigDigitalFilter(&HwPressureSensor2_handler, 0) !=
          HAL_OK) {
        retStatus = -1;
      }
      /* Enable the mux channel with a bounded timeout (no HAL_MAX_DELAY in
       * safety code). */
      if (HAL_I2C_Master_Transmit(
              &HwPressureSensor2_handler, HW_PRESSURE2_MUX_ADDR, &PS_Channel,
              sizeof(PS_Channel), INF_I2C_TIMEOUT_MS_INIT) != HAL_OK) {
        retStatus = -1;
      }
    }

    break;
  default:
    retStatus = -1;
    break;
  }

  return retStatus;
}

/**
 * @brief
 *        This function extracts the Sensor Valid raw data by eliminating the
 * Don't Care bits and returns the structure .
 *
 * @param enum uint8_t Data[4]
 *
 *
 * @retval HwPressureSensorDatabitfield_s returns the structure.
 */

static HwPressureSensorDatabitfield_s HwPressureDataExtract(uint8_t Data[4]) {
  HwPressureSensorDatabitfield_s HwPressureData;
  HwPressureData.Status = EXTRACT_STATUS(Data[0]);
  HwPressureData.RawPressureData = EXTRACT_PRESSURE(Data[0], Data[1]);
  HwPressureData.RawTemperatureData = EXTRACT_TEMPERATURE(Data[2], Data[3]);
  return HwPressureData;
}

static int HwPressureStatusToErr(uint8_t status) {
  /* Honeywell digital output force sensors:
   * 00 = normal, 01 = command mode, 10 = stale, 11 = diagnostic fault.
   */
  switch ((HwPressureSensorStatus_t)status) {
  case HW_PRESSURE_NORMAL_MODE:
    return 0;
  case HW_PRESSURE_STALE_MODE:
    return -2; /* data not fresh */
  case HW_PRESSURE_COMMAND_MODE:
    return -3; /* unexpected in normal operation */
  case HW_PRESSURE_DIAGNOSTIC_MODE:
  default:
    return -4; /* sensor diagnostic fault */
  }
}

/**
 * @brief
 *        This function calculates the force of the Pressure Sensor and returns
 * the value in Newton.
 *
 * @param enum uint16_t PressureCount => Raw Pressure Count
 *
 *
 * @retval uint16_t returns the calculated force Value in Newton.
 */

static float HwPressureCal(uint16_t PressureCount) {
  /* Force Output Calculation */
  return (float)((PressureCount - HW_PRESSURE_DOUT_MIN_RANGE) *
                 HW_PRESSURE_RANGE) /
         (HW_PRESSURE_DOUT_MAX_RANGE - HW_PRESSURE_DOUT_MIN_RANGE);
}

/**
 * @brief
 *        This function calculates the Temperature and returns the
 *        value in Celcius.
 *
 * @param enum uint16_t TemperatureCount => Raw Temperature Count
 *
 *
 * @retval uint16_t returns the calculated Temperature Value in Celcius.
 */

static float HwTemparatureCal(uint8_t TemperatureCount) {
  /* Temperature Calculation */
  return ((((float)TemperatureCount / HW_TEMPERATURE_RESOLUTION) *
           HW_TEMPERATURE_SCALE) -
          HW_TEMPERATURE_OFFSET);
}

/**
 * @brief Pressure Sensor Interface to read the Sensor Data
 *        This function is used to read the Pressure Sensor Data
 *
 * @param enum HwPressureSensorNum_t
 *
 *
 * @retval int 0 if Successful else error code in negative sign
 */

int HwPressureSensorRead(HwPressureSensorNum_t hwPressure,
                         HwPressureSensorValues_s *psValues) {
  int retStatus = 0;
  uint8_t Data[4];
  HwPressureSensorDatabitfield_s HwPressureData = {0};

  if (psValues == NULL) {
    return -1; // Error: Null pointer
  }

  // Check if hwPressure is within valid range
  if (hwPressure >= HW_PRESSURE_NUM_MAX) {
    // Invalid pressure sensor number
    psValues->PressureValue = 0;    // Set Pressure sensor value to 0
    psValues->TemperatureValue = 0; // Set  Temperature Sensor value to 0
    return -1;                      // Return an error code
  }

  switch (hwPressure) {
  case HW_PRESSURE_NUM_1:
    if (HAL_I2C_Master_Receive(&HwPressureSensor1_handler,
                               PRESSURE_SENSOR_ADDRESS, Data, NUM_OF_BYTES,
                               100) != HAL_OK) {
      /* Pressure Sensor 1 Communication Error */
      retStatus = -1;
    } else {
      HwPressureData = HwPressureDataExtract(Data);
      int st = HwPressureStatusToErr(HwPressureData.Status);
      if (st != 0) {
        psValues->PressureValue = 0.0f;
        psValues->TemperatureValue = 0.0f;
        return st;
      }

      psValues->PressureValue = HwPressureCal(HwPressureData.RawPressureData);
      psValues->TemperatureValue =
          HwTemparatureCal(HwPressureData.RawTemperatureData);
    }
    break;

  case HW_PRESSURE_NUM_2:
    if (HAL_I2C_Master_Receive(&HwPressureSensor2_handler,
                               PRESSURE_SENSOR_ADDRESS, Data, NUM_OF_BYTES,
                               100) != HAL_OK) {
      /* Pressure Sensor 4 Communication Error */
      retStatus = -1;
    } else {
      HwPressureData = HwPressureDataExtract(Data);
      int st = HwPressureStatusToErr(HwPressureData.Status);
      if (st != 0) {
        psValues->PressureValue = 0.0f;
        psValues->TemperatureValue = 0.0f;
        return st;
      }

      psValues->PressureValue = HwPressureCal(HwPressureData.RawPressureData);
      psValues->TemperatureValue =
          HwTemparatureCal(HwPressureData.RawTemperatureData);
    }
    break;

  default:
    retStatus = -1;
  }

  return retStatus;
}

int HwPressureSensorSelfTest(HwPressureSensorNum_t hwPressure) {
  /* Basic self-test:
   * - verify we can read 4 bytes over I2C
   * - verify status != command/diagnostic
   * - tolerate STALE by retrying a few times
   * - verify raw output is within plausible 14-bit range and within transfer
   * bounds (with margin)
   */
  HwPressureSensorValues_s v = {0};
  for (int attempt = 0; attempt < 3; attempt++) {
    int ret = HwPressureSensorRead(hwPressure, &v);
    if (ret == 0) {
      /* Plausibility: should never exceed full-scale by much, and should not be
       * NaN. */
      if (!(v.PressureValue == v.PressureValue)) { /* NaN check */
        return -5;
      }
      /* Allow small negative/over-range due to tolerances/noise. */
      if (v.PressureValue < -2.0f ||
          v.PressureValue > (HW_PRESSURE_RANGE + 2.0f)) {
        return -6;
      }
      return 0;
    }
    if (ret == -2) {
      /* Stale: wait for next conversion and retry. */
      Infusion_DelayMs(2);
      continue;
    }
    return ret;
  }
  return -2;
}
