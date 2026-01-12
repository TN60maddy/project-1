/**
  ******************************************************************************
  * @file    stm32h743i_eval_bus.h
  * @author  MCD Application Team
  * @brief   This file is the header of stm32h743i_eval_bus.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H743I_EVAL_BUS_H
#define STM32H743I_EVAL_BUS_H

#ifdef __cplusplus
 extern "C" {
#endif


 /* Includes ------------------------------------------------------------------*/
#include "stm32h743i_eval_conf.h"
#include "stm32h743i_eval_errno.h"
#if defined(BSP_USE_CMSIS_OS)
#include "cmsis_os.h"
#endif
/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32H743I_EVAL
  * @{
  */

/** @addtogroup STM32H743I_EVAL_BUS
  * @{
  */
/** @defgroup STM32H743I_EVAL_BUS_Exported_Types BUS Exported Types
  * @{
  */
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
typedef struct
{
  void (* pMspInitCb)(I2C_HandleTypeDef *);
  void (* pMspDeInitCb)(I2C_HandleTypeDef *);
}BSP_I2C_Cb_t;
#endif /* (USE_HAL_I2C_REGISTER_CALLBACKS == 1) */

/**
  * @}
  */
/** @defgroup STM32H743I_EVAL_BUS_Exported_Constants BUS Exported Constants
  * @{
  */
/* Definition for I2C1 clock resources */
#define BUS_I2C1                              I2C1
#define BUS_I2C1_CLK_ENABLE()                  __HAL_RCC_I2C1_CLK_ENABLE()
#define BUS_I2C1_CLK_DISABLE()                 __HAL_RCC_I2C1_CLK_DISABLE()
#define BUS_I2C1_SCL_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define BUS_I2C1_SCL_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOB_CLK_DISABLE()
#define BUS_I2C1_SDA_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define BUS_I2C1_SDA_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOB_CLK_DISABLE()

#define BUS_I2C1_FORCE_RESET()                 __HAL_RCC_I2C1_FORCE_RESET()
#define BUS_I2C1_RELEASE_RESET()               __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2C1 Pins */
#define BUS_I2C1_SCL_PIN                       GPIO_PIN_6
#define BUS_I2C1_SDA_PIN                       GPIO_PIN_7
#define BUS_I2C1_SCL_GPIO_PORT                 GPIOB
#define BUS_I2C1_SDA_GPIO_PORT                 GPIOB
#define BUS_I2C1_SCL_AF                        GPIO_AF4_I2C1
#define BUS_I2C1_SDA_AF                        GPIO_AF4_I2C1

#ifndef BUS_I2C1_FREQUENCY
   #define BUS_I2C1_FREQUENCY  100000U /* Frequency of I2Cn = 100 KHz*/
#endif



/* I2C 4 Peripheral Definitions */

#define BUS_I2C3                                      I2C4
#define BUS_I2C3_CLK_ENABLE()                  __HAL_RCC_I2C4_CLK_ENABLE()
#define BUS_I2C3_CLK_DISABLE()                 __HAL_RCC_I2C4_CLK_DISABLE()

/* I2C GPIO Pins are PB8(SCL) and PB9(SDA) */

#define BUS_I2C3_SCL_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define BUS_I2C3_SCL_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOB_CLK_DISABLE()
#define BUS_I2C3_SDA_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define BUS_I2C3_SDA_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOB_CLK_DISABLE()

#define BUS_I2C3_FORCE_RESET()                 __HAL_RCC_I2C4_FORCE_RESET()
#define BUS_I2C3_RELEASE_RESET()               __HAL_RCC_I2C4_RELEASE_RESET()

/* Definition for I2C1 Pins */
#define BUS_I2C3_SCL_PIN                      GPIO_PIN_8
#define BUS_I2C3_SDA_PIN                      GPIO_PIN_9
#define BUS_I2C3_SCL_GPIO_PORT            GPIOB
#define BUS_I2C3_SDA_GPIO_PORT            GPIOB

#define BUS_I2C3_SCL_AF                        GPIO_AF6_I2C4
#define BUS_I2C3_SDA_AF                        GPIO_AF6_I2C4

#ifndef BUS_I2C3_FREQUENCY
   #define BUS_I2C3_FREQUENCY  100000U /* Frequency of I2Cn = 100 KHz*/
#endif



/* Configuration for I2C4 Peripheral*/


#define BUS_I2C4                              I2C4
#define BUS_I2C4_CLK_ENABLE()                  __HAL_RCC_I2C4_CLK_ENABLE()
#define BUS_I2C4_CLK_DISABLE()                 __HAL_RCC_I2C4_CLK_DISABLE()

/* I2C GPIO Pins are PB8(SCL) and PB9(SDA) */

#define BUS_I2C4_SCL_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define BUS_I2C4_SCL_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOB_CLK_DISABLE()
#define BUS_I2C4_SDA_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define BUS_I2C4_SDA_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOB_CLK_DISABLE()

#define BUS_I2C4_FORCE_RESET()                 __HAL_RCC_I2C4_FORCE_RESET()
#define BUS_I2C4_RELEASE_RESET()               __HAL_RCC_I2C4_RELEASE_RESET()

/* Definition for I2C1 Pins */
#define BUS_I2C4_SCL_PIN                      GPIO_PIN_8
#define BUS_I2C4_SDA_PIN                      GPIO_PIN_9
#define BUS_I2C4_SCL_GPIO_PORT            GPIOB
#define BUS_I2C4_SDA_GPIO_PORT            GPIOB
#define BUS_I2C4_SCL_AF                        GPIO_AF6_I2C4
#define BUS_I2C4_SDA_AF                        GPIO_AF6_I2C4

#ifndef BUS_I2C4_FREQUENCY
   #define BUS_I2C4_FREQUENCY  100000U /* Frequency of I2Cn = 100 KHz*/
#endif


/* Configuration for SPI2 Peripheral*/


#define BUS_SPI2                              SPI2

#define BUS_SPI2_CLK_ENABLE()                  __HAL_RCC_SPI2_CLK_ENABLE()
#define BUS_SPI2_CLK_DISABLE()                 __HAL_RCC_SPI2_CLK_DISABLE()

/* I2C GPIO Pins are PB8(SCL) and PB9(SDA) */

#define BUS_SPI2_MOSI_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOC_CLK_ENABLE()
#define BUS_SPI2_MOSI_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOC_CLK_DISABLE()
#define BUS_SPI2_MISO_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOC_CLK_ENABLE()
#define BUS_SPI2_MISO_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOC_CLK_DISABLE()
#define BUS_SPI2_SCK_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOD_CLK_DISABLE
#define BUS_SPI2_SCK_GPIO_CLK_DISABLE()         __HAL_RCC_GPIOD_CLK_DISABLE
#define BUS_SPI2_NSS_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOB_CLK_DISABLE
#define BUS_SPI2_NSS_GPIO_CLK_DISABLE()       __HAL_RCC_GPIOB_CLK_DISABLE

/* Definition for I2C1 Pins */
#define BUS_SPI2_MOSI_PIN                      GPIO_PIN_1
#define BUS_SPI2_MISO_PIN                      GPIO_PIN_2
#define BUS_SPI2_SCK_PIN                        GPIO_PIN_3
#define BUS_SPI2_NSS_PIN                        GPIO_PIN_5


#define BUS_SPI2_MOSI_GPIO_PORT            GPIOC
#define BUS_SPI2_MISO_GPIO_PORT            GPIOC
#define BUS_SPI2_SCK_GPIO_PORT              GPIOD
#define BUS_SPI2_NSS_GPIO_PORT              GPIOB


#define BUS_SPI2_SCK_AF                        GPIO_AF5_SPI2
#define BUS_SPI2_MOSI_AF                       GPIO_AF5_SPI2
#define BUS_SPI2_MISO_AF                       GPIO_AF5_SPI2



#ifndef BUS_I2C4_FREQUENCY
   #define BUS_I2C4_FREQUENCY  100000U /* Frequency of I2Cn = 100 KHz*/
#endif


/*  SPI related Functions */

int32_t BSP_SPI2_Init(void);
int32_t BSP_SPI2_DeInit(void);
int32_t BSP_SPI2_ReadReg(uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_SPI2_WriteReg(uint16_t Reg, uint8_t *pData, uint16_t Length);


/**
  * @}
  */

/** @addtogroup STM32H743I_EVAL_BUS_Exported_Variables
  * @{
  */
extern I2C_HandleTypeDef hbus_i2c1;
/**
  * @}
  */

/** @addtogroup STM32H743I_EVAL_BUS_Exported_Functions
  * @{
  */
int32_t BSP_I2C1_Init(void);
int32_t BSP_I2C1_DeInit(void);
int32_t BSP_I2C1_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_WriteReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_ReadReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_Recv(uint16_t DevAddr, uint16_t Reg, uint16_t MemAddSize, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_Send(uint16_t DevAddr, uint16_t Reg, uint16_t MemAddSize, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_IsReady(uint16_t DevAddr, uint32_t Trials);
int32_t BSP_GetTick(void);




int32_t BSP_I2C3_Init(void);
int32_t BSP_I2C3_DeInit(void);
int32_t BSP_I2C3_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C3_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C3_IsReady(uint16_t DevAddr, uint32_t Trials);

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
int32_t BSP_I2C1_RegisterDefaultMspCallbacks (void);
int32_t BSP_I2C1_RegisterMspCallbacks (BSP_I2C_Cb_t *Callback);
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */
__weak HAL_StatusTypeDef MX_I2C1_Init(I2C_HandleTypeDef *hI2c, uint32_t timing);
__weak HAL_StatusTypeDef MX_I2C3_Init(I2C_HandleTypeDef *hI2c, uint32_t timing);


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H743I_EVAL_BUS_H */
