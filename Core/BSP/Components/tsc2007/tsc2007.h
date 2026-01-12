/**
 ******************************************************************************
 * @file    tsc2007.h
 * @author  Aria Innovation
 * @brief   This file contains all the functions prototypes for the
 *          tsc2007.c Touch Screen driver.
 ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2014 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TSC2007_H
#define TSC2007_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "tsc2007_reg.h"
#include <stddef.h>
#include "stdint.h"
#include "stdbool.h"
#include "tsc2007_reg.h"
//#include "tsc2007_conf.h"

/* Macros --------------------------------------------------------------------*/

/** @addtogroup BSP
 * @{
 */

/** @addtogroup Component
 * @{
 */

/** @addtogroup TSC2007
 * @{
 */

/** @addtogroup TSC2007_Exported_Constants
 * @{
 */
#define TSC2007_OK                      (0)
#define TSC2007_ERROR                   (-1)

/* Max detectable simultaneous touches */
#define TSC2007_MAX_NB_TOUCH      1U

/* Touch TSC2007 IDs */
#define TSC2007_ID                       0x90U

#define TSC2007_READ_CMD                 0x81U
#define TSC2007_WRITE_CMD                0x08U

#define TSC2007_MAX_X_LENGTH                  4096U
#define TSC2007_MAX_Y_LENGTH                  4096U







/* do not edit */
#define TSC2007_ADDR_GND_VAL 0
#define TSC2007_ADDR_VDD_VAL 1

/**
 * @brief Configuration of the A1 and A0 pins
 */
#define TSC2007_A1_HW_CONF TSC2007_ADDR_GND_VAL
#define TSC2007_A0_HW_CONF TSC2007_ADDR_GND_VAL

/* do not edit */
#define TSC2007_ADDR_HW_CONF_VAL ((TSC2007_A1_HW_CONF <<1)|(TSC2007_A0_HW_CONF))
                                                         // 0 << 1 | 0 ;
#define TSC2007_ADDR_HW_CONF_VAL_OFFSET 1
#define TSC2007_ADDR_HW_CONF_VAL_MASK 0x6


/*******************************************************************************
* Defines
*******************************************************************************/
/* Addres Byte defines */
#define TSC2007_D7_D4 0x12 /* 0b1 0010 */
#define TSC2007_D7_D4_OFFSET 3
#define TSC2007_D7_D4_MASK 0xF8 /* */
#define TSC2007_I2C_ADDR_READ_WRITE_OFFSET 0
#define TSC2007_I2C_ADDR_READ_WRITE_MASK 0x1
#define TSC2007_I2C_ADDR_READ_VAL 1                    /* I2C master read from TSC (I2C read addressing) */
#define TSC2007_I2C_ADDR_WRITE_VAL 0                  /* I2C master write to TSC (I2C write addressing) */
#define TSC2007_I2C_ADDR (((TSC2007_D7_D4<<TSC2007_D7_D4_OFFSET)&TSC2007_D7_D4_MASK) | ((TSC2007_ADDR_HW_CONF_VAL << TSC2007_ADDR_HW_CONF_VAL_OFFSET) & TSC2007_ADDR_HW_CONF_VAL_MASK))

                                        //    ((0x12 << 3) & 0xF8) | 0 << 1 & 0x06


/* Converter Function Select as in Table 3 from TSC2007 datasheet */
#define TC_FUNCTION_MEASURE_TEMP_0 0
#define TC_FUNCTION_MEASURE_AUX 2
#define TC_FUNCTION_MEASURE_TEMP_1 4
#define TC_FUNCTION_ACTIVATE_X_DRIVERS 8
#define TC_FUNCTION_ACTIVATE_Y_DRIVERS 9
#define TC_FUNCTION_ACTIVATE_Yp_Xn_DRIVERS 10
#define TC_FUNCTION_SETUP_COMMAND 11
#define TC_FUNCTION_MEASURE_X_POSITION 12
#define TC_FUNCTION_MEASURE_Y_POSITION 13
#define TC_FUNCTION_MEASURE_Z1_POSITION 14
#define TC_FUNCTION_MEASURE_Z2_POSITION 15

/* Power modes */
#define POWER_CONFIG_POWER_DOWN_BETWEEN_CYCLES 0
#define POWER_CONFIG_ADC_ON_IRQ_DISABLED 1
#define POWER_CONFIG_ADC_OFF_IRQ_ENABLED 2
#define POWER_CONFIG_ADC_ON_IRQ_DISABLED2 3 /* Same as previous? Possible errata */

/* Adc resolution */
#define ADC_CONFIG_12_BITS_RESOLUTION 0
#define ADC_CONFIG_8_BITS_RESOLUTION 1
/* Filter configuration */
#define FILTER_CONTROL_USE_ONBOARD_MAV_FILTER 0
#define FILTER_CONTROL_BYPASS_ONBOARD 1
/* Pull up configuration*/
#define PULL_UP_RESISTORS_50K 0
#define PULL_UP_RESISTORS_90k 1
/* RX buffer lengths */
#define MAX_LENGTH_RX_MESSAGE 2

#define IRQ_TRIGGERED_BY_PUSH 0
#define IRQ_TRIGGERED_BY_RELEASE 1

/*******************************************************************************
* Local Types and Typedefs
*******************************************************************************/
/**
 * Union to build command bytes
 */
typedef union {
    struct {
        unsigned char dont_care :1; /**< do not care*/
        unsigned char adc_config :1; /**< 12 or 8 bits sampling */
        unsigned char power_config :2; /**< Select PENIRQ enable and poder down */
        unsigned char tc_function :4; /**< function selector*/
    } cmd_bits;
    unsigned char cmd_byte;



} TSC2007_CommandByte;

/**
 * Union to build command bytes for the Setup command special case
 */
typedef union {
    struct {
        unsigned char pull_up_resistors :1; /**< Select 50/80 Ohm filters */
        unsigned char filter_control :1; /**< Onboard vs Bypass */
        unsigned char reserved :2; /**< must write 00 */
        unsigned char tc_function :4; /**< function selector*/
    } cmd_bits;
    unsigned char cmd_byte;
} TSC2007_CommandByteSetupCommand;


typedef enum{
    TSC_IT_IDLE,
    TSC_IT_GET_X,
    TSC_IT_GET_Y,
    TSC_IT_GET_Z,
    TSC_IT_PROCESS,
} FSM_TSC2007DriverIT;



/**
 * @}
 */

/** @defgroup TSC2007_Exported_Types TS3510 Exported Types
 * @{
 */

typedef struct
{
  uint32_t  Radian;
  uint32_t  OffsetLeftRight;
  uint32_t  OffsetUpDown;
  uint32_t  DistanceLeftRight;
  uint32_t  DistanceUpDown;
  uint32_t  DistanceZoom;
}TSC2007_Gesture_Init_t;

typedef int32_t (*TSC2007_Init_Func)    (void);
typedef int32_t (*TSC2007_DeInit_Func)  (void);
typedef int32_t (*TSC2007_GetTick_Func) (void);
typedef int32_t (*TSC2007_Delay_Func)   (uint32_t);
typedef int32_t (*TS2007_WriteReg_Func)(uint16_t, uint16_t, uint8_t*, uint16_t);
typedef int32_t (*TSC2007_ReadReg_Func) (uint16_t, uint16_t, uint8_t*, uint16_t);
typedef int32_t (*TSC2007_DeviceReadyFunc) (uint16_t DevAddr, uint32_t Trials);


typedef struct
{
  TSC2007_Init_Func          Init;
  TSC2007_DeInit_Func        DeInit;
  uint16_t                   Address;
  TS2007_WriteReg_Func       WriteReg;
  TSC2007_ReadReg_Func       ReadReg;
  TSC2007_GetTick_Func       GetTick;
  TSC2007_DeviceReadyFunc DevRed;
} TSC2007_IO_t;


typedef struct
{
  uint32_t  TouchDetected;
  uint32_t  TouchX;
  uint32_t  TouchY;
} TSC2007_State_t;

typedef struct
{
  uint32_t  TouchDetected;
  uint32_t  TouchX[TSC2007_MAX_NB_TOUCH];
  uint32_t  TouchY[TSC2007_MAX_NB_TOUCH];
  uint32_t  TouchWeight[TSC2007_MAX_NB_TOUCH];
  uint32_t  TouchEvent[TSC2007_MAX_NB_TOUCH];
  uint32_t  TouchArea[TSC2007_MAX_NB_TOUCH];
} TSC2007_MultiTouch_State_t;

typedef struct
{
  TSC2007_IO_t         IO;
  tsc2007_ctx_t        Ctx;
  uint8_t             IsInitialized;
} TSC2007_Object_t;

typedef struct
{
  uint8_t   MultiTouch;
  uint8_t   Gesture;
  uint8_t   MaxTouch;
  uint32_t  MaxXl;
  uint32_t  MaxYl;
} TSC2007_Capabilities_t;

 typedef struct
{
  int32_t ( *Init                 ) ( TSC2007_Object_t *);
  int32_t ( *DeInit               ) ( TSC2007_Object_t * );
  int32_t ( *GestureConfig        ) ( TSC2007_Object_t *, TSC2007_Gesture_Init_t* );
  int32_t ( *ReadID               ) ( TSC2007_Object_t *, uint32_t * );
  int32_t ( *GetState             ) ( TSC2007_Object_t *, TSC2007_State_t* );
  int32_t ( *GetMultiTouchState   ) ( TSC2007_Object_t *, TSC2007_MultiTouch_State_t* );
  int32_t ( *GetGesture           ) ( TSC2007_Object_t *, uint8_t* );
  int32_t ( *GetCapabilities      ) ( TSC2007_Object_t *, TSC2007_Capabilities_t * );
  int32_t ( *EnableIT             ) ( TSC2007_Object_t * );
  int32_t ( *DisableIT            ) ( TSC2007_Object_t * );
  int32_t ( *ClearIT              ) ( TSC2007_Object_t * );
  int32_t ( *ITStatus             ) ( TSC2007_Object_t * );
} TSC2007_TS_Drv_t;
/**
 * @}
 */

/** @addtogroup TSC2007_Exported_Variables
  * @{
  */

extern TSC2007_TS_Drv_t TSC2007_TS_Driver;
/**
 * @}
 */

/** @addtogroup TSC2007_Exported_Functions
 * @{
 */
int32_t TSC2007_RegisterBusIO (TSC2007_Object_t *pObj, TSC2007_IO_t *pIO);
int32_t TSC2007_Init(TSC2007_Object_t *pObj);
int32_t TSC2007_DeInit(TSC2007_Object_t *pObj);
int32_t TSC2007_GestureConfig(TSC2007_Object_t *pObj, TSC2007_Gesture_Init_t *GestureInit);
int32_t TSC2007_ReadID(TSC2007_Object_t *pObj, uint32_t *Id);
int32_t TSC2007_GetState(TSC2007_Object_t *pObj, TSC2007_State_t *State);
int32_t TSC2007_GetMultiTouchState(TSC2007_Object_t *pObj, TSC2007_MultiTouch_State_t *State);
int32_t TSC2007_GetGesture(TSC2007_Object_t *pObj, uint8_t *GestureId);
int32_t TSC2007_EnableIT(TSC2007_Object_t *pObj);
int32_t TSC2007_DisableIT(TSC2007_Object_t *pObj);
int32_t TSC2007_ITStatus(TSC2007_Object_t *pObj);
int32_t TSC2007_ClearIT(TSC2007_Object_t *pObj);
int32_t TSC2007_GetCapabilities(TSC2007_Object_t *pObj, TSC2007_Capabilities_t *Capabilities);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /* TSC2007_H */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

