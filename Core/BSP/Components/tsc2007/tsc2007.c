/**
  ******************************************************************************
  * @file    tsc2007.c
  * @author  MCD Application Team
  * @brief   This file provides a set of functions needed to manage the TSC2007
  *          IO Expander devices.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tsc2007.h"
#include "ew_bsp_console.h"
#include "ewconfig.h"
#include "ew_bsp_inout.h"

/* Global Variables */



#define RAW_X_MIN   82
#define RAW_X_MAX   4035
#define RAW_Y_MIN   253
#define RAW_Y_MAX   3850
/** @addtogroup BSP
  * @{
  */

/** @addtogroup Component
  * @{
  */

static int32_t TSC2007_DetectTouch(TSC2007_Object_t *pObj, uint8_t *pData, uint32_t Length);
static int32_t ReadRegWrap(void *handle, uint8_t Reg, uint8_t* Data, uint16_t Length);
static int32_t WriteRegWrap(void *handle, uint8_t Reg, uint8_t* Data, uint16_t Length);

/** @defgroup TSC2007
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/** @defgroup TSC2007_Exported_Variables TSC2007 Exported Variables
  * @{
  */

/* Touch screen driver structure initialization */
TSC2007_TS_Drv_t TSC2007_TS_Driver =
{
  TSC2007_Init,
  TSC2007_DeInit,
  TSC2007_GestureConfig,
  TSC2007_ReadID,
  TSC2007_GetState,
  TSC2007_GetMultiTouchState,
  TSC2007_GetGesture,
  TSC2007_GetCapabilities,
  TSC2007_EnableIT,
  TSC2007_DisableIT,
  TSC2007_ClearIT,
  TSC2007_ITStatus
};
/**
  * @}
  */

/** @defgroup EXC7200_Private_Function_Prototypes EXC7200 Private Function Prototypes
  * @{
  */
//static int32_t EXC7200_DetectTouch(EXC7200_Object_t *pObj, uint8_t *pData, uint32_t Length);
static int32_t ReadRegWrap(void *handle, uint8_t Reg, uint8_t* Data, uint16_t Length);
static int32_t WriteRegWrap(void *handle, uint8_t Reg, uint8_t* Data, uint16_t Length);

/**
  * @}
  */

/** @defgroup TSC7200_Exported_Functions EXC7200 Exported Functions
  * @{
  */

/**
  * @brief  Register IO bus to component object
  * @param  Component object pointer
  * @retval error status
  */
int32_t TSC2007_RegisterBusIO (TSC2007_Object_t *pObj, TSC2007_IO_t *pIO)
{
  int32_t ret;

  if (pObj == NULL)
  {
    ret = TSC2007_ERROR;
  }
  else
  {
    pObj->IO.Init         =  pIO->Init;
    pObj->IO.DeInit      =  pIO->DeInit;
    pObj->IO.Address   =  pIO->Address;
    pObj->IO.WriteReg  =  pIO->WriteReg;
    pObj->IO.ReadReg   =  pIO->ReadReg;
    pObj->IO.GetTick    =  pIO->GetTick;
    pObj->IO.DevRed    = pIO->DevRed;

    pObj->Ctx.ReadReg  = ReadRegWrap;
    pObj->Ctx.WriteReg = WriteRegWrap;
    pObj->Ctx.handle   = pObj;

    if(pObj->IO.Init != NULL)
    {
      ret = pObj->IO.Init();
    }
    else
    {
      ret = TSC2007_ERROR;
    }
  }

  return ret;
}

/**
  * @brief  Get EXC7200 sensor capabilities
  * @param  pObj Component object pointer
  * @param  Capabilities pointer to EXC7200 sensor capabilities
  * @retval Component status
  */
int32_t TSC2007_GetCapabilities(TSC2007_Object_t *pObj, TSC2007_Capabilities_t *Capabilities)
{
  /* Prevent unused argument(s) compilation warning */
  (void)(pObj);

  /* Store component's capabilities */
  Capabilities->MultiTouch = 0;
  Capabilities->Gesture    = 0;
  Capabilities->MaxTouch   = TSC2007_MAX_NB_TOUCH;
  Capabilities->MaxXl      = TSC2007_MAX_X_LENGTH;
  Capabilities->MaxYl      = TSC2007_MAX_Y_LENGTH;

  return TSC2007_OK;
}

/**
  * @brief  Initialize the EXC7200 communication bus
  *         from MCU to EXC7200 : ie I2C channel initialization (if required).
  * @param  pObj Component object pointer
  * @retval Component status
  */
int32_t TSC2007_Init(TSC2007_Object_t *pObj)
{
  int32_t ret = TSC2007_OK;

  if(pObj->IsInitialized == 0U)
  {
    /* Initialize IO BUS layer */
    if(pObj->IO.Init() != TSC2007_OK)
    {
      ret = TSC2007_ERROR;
    }
    else
    {
      pObj->IsInitialized = 1;
    }
  }

  return ret;
}

/**
  * @brief  De-Initialize the EXC7200 communication bus
  *         from MCU to EXC7200 : ie I2C channel initialization (if required).
  * @param  pObj Component object pointer
  * @retval Component status
  */
int32_t TSC2007_DeInit(TSC2007_Object_t *pObj)
{
  int32_t ret =TSC2007_OK;

  if(pObj->IsInitialized == 1U)
  {
    if(pObj->IO.DeInit() != TSC2007_OK)
    {
      ret = TSC2007_ERROR;
    }
    else
    {
      pObj->IsInitialized = 0;
    }
  }

  return ret;
}

/**
  * @brief  Configure the TSC2007 gesture
  *         from MCU to TSC2007 : ie I2C channel initialization (if required).
  * @param  pObj  Component object pointer
  * @param  GestureInit Gesture init structure
  * @retval Component status
  */
int32_t TSC2007_GestureConfig(TSC2007_Object_t *pObj, TSC2007_Gesture_Init_t *GestureInit)
{
  /* Feature not supported */
  return TSC2007_ERROR;
}

/**
  * @brief  Read the TSC2007 device ID, pre initialize I2C in case of need to be
  *         able to read the TSC2007 device ID, and verify this is a TSC2007.
  * @param  pObj Component object pointer
  * @param  Id Pointer to component ID value
  * @retval Component status
  */
int32_t TSC2007_ReadID(TSC2007_Object_t *pObj, uint32_t *Id)
{
  int32_t ret = TSC2007_ERROR;



//  if(tsc2007_read_reg(&pObj->Ctx, TSC2007_READ_REG, &data, 1) == TSC2007_OK)
  if(pObj->IO.DevRed(0x70,100) == 0)
  {
    //*Id = TSC2007_ID;
    ret = TSC2007_OK;
  }


  return ret;
}

/**
  * @brief  Get the touch screen X and Y positions values
  * @param  pObj Component object pointer
  * @param  State Single Touch stucture pointer
  * @retval Component status.
  */
/* Raw ranges you found */


/* LCD size in pixels */
#define LCD_W       960
#define LCD_H       360
#define RAW_X_MIN   82
#define RAW_X_MAX   4035
#define RAW_Y_MIN   253
#define RAW_Y_MAX   3850

static inline uint16_t map_lin(uint16_t raw, uint16_t raw_min,
                               uint16_t raw_max, uint16_t out_max)
{
    /* Clamp first for robustness */
    if (raw < raw_min) raw = raw_min;
    if (raw > raw_max) raw = raw_max;

    /* (raw-raw_min) * (out_max-1) / (raw_max-raw_min) */
    uint32_t num   = (uint32_t)(raw - raw_min) * (out_max - 1);
    uint32_t denom = (uint32_t)(raw_max - raw_min);
    return (uint16_t)(num / denom);
}

/* Call this every time you have a new ADC reading */
void touch_raw_to_gui(uint16_t rx, uint16_t ry,
                      uint16_t *gx, uint16_t *gy)
{
    *gx = map_lin(rx, RAW_X_MIN, RAW_X_MAX, LCD_W);
    *gy = map_lin(ry, RAW_Y_MIN, RAW_Y_MAX, LCD_H) + 60;   /* flip here if Y is upside-down */
}

int32_t TSC2007_GetState(TSC2007_Object_t *pObj, TSC2007_State_t *State)
{
	uint8_t  data[10];

    State -> TouchDetected = (uint32_t)TSC2007_DetectTouch(pObj, data, (uint32_t)sizeof(data));


    uint16_t raw_x = ((uint16_t)data[2] << 4) | ((uint16_t)data[3] >> 4);
    uint16_t raw_y = ((uint16_t)data[4] << 4) | ((uint16_t)data[5] >> 4);

    State->TouchX  = map_lin(raw_x, RAW_X_MIN, RAW_X_MAX, LCD_W);
    State->TouchY = map_lin(raw_y, RAW_Y_MIN, RAW_Y_MAX, LCD_H);   /* flip here if Y is upside-down */


  /* Dummy Read to deactivate read mode */
  (void)TSC2007_DetectTouch(pObj, data, (uint32_t)sizeof(data));

  return TSC2007_OK;
}

/**
  * @brief  Get the touch screen Xn and Yn positions values in multi-touch mode
  * @param  pObj Component object pointer
  * @param  State Multi Touch stucture pointer
  * @retval Component status.
  */
int32_t TSC2007_GetMultiTouchState(TSC2007_Object_t *pObj, TSC2007_MultiTouch_State_t *State)
{
  /* Feature not supported */
  return TSC2007_ERROR;
}

/**
  * @brief  Get Gesture ID
  * @param  pObj Component object pointer
  * @param  GestureId gesture ID
  * @retval Component status.
  */
int32_t TSC2007_GetGesture(TSC2007_Object_t *pObj, uint8_t *GestureId)
{
  /* Feature not supported */
  return TSC2007_ERROR;
}

/**
  * @brief  Configure the EXC7200 device to generate IT on given INT pin
  *         connected to MCU as EXTI.
  * @param  pObj Component object pointer
  * @retval Component status.
  */
int32_t TSC2007_EnableIT(TSC2007_Object_t *pObj)
{
  /* Feature not supported */
  return TSC2007_ERROR;
}

/**
  * @brief  Configure the EXC7200 device to stop generating IT on the given INT pin
  *         connected to MCU as EXTI.
  * @param  pObj Component object pointer
  * @retval Component status.
  */
int32_t TSC2007_DisableIT(TSC2007_Object_t *pObj)
{
  /* Feature not supported */
  return TSC2007_ERROR;
}

/**
  * @brief  Get IT status from TSC2007 interrupt status registers
  *         Should be called Following an EXTI coming to the MCU to know the detailed
  *         reason of the interrupt.
  *         @note : This feature is not applicable to EXC7200.
  * @param  pObj Component object pointer
  * @retval Component status.
  */
int32_t TSC2007_ITStatus(TSC2007_Object_t *pObj)
{
  /* Feature not supported */
  return TSC2007_ERROR;
}

/**
  * @brief  Clear IT status in TSC2007 interrupt status clear registers
  *         Should be called Following an EXTI coming to the MCU.
  *         @note : This feature is not applicable to EXC7200.
  * @param  pObj Component object pointer
  * @retval Component status.
  */
int32_t TSC2007_ClearIT(TSC2007_Object_t *pObj)
{
  /* Feature not supported */
  return TSC2007_ERROR;
}
/**
  * @}
  */

/** @defgroup TSC2007_Private_Functions TSC2007 Private Functions
  * @{
  */

/**
  * @brief  Return if there is touches detected or not.
  *         Get the touch screen X and Y positions values
  * @param  pObj Component object pointer
  * @param  pData Pointer to data buffer
  * @param  Length Number of data to read
  * @retval Number of active touches detected (can be 0 or 1) or TSC2007_ERROR
  *         in case of error
  */
static int32_t TSC2007_DetectTouch(TSC2007_Object_t *pObj, uint8_t *pData, uint32_t Length)
{
  int32_t ret;
    /* Read the Touch Screen Controller Interrupt Detection  */
   /*  PC8 is connected to Touch Interrupt Pin */
   /*  Read the GPIO Pin Status */

     if( TSC2007_ReadTouchStatus() == 0 )
     {
	   	   	     /* If valid number of touch detected, set it to zero */
	            /*   Read the Touch Co-ordinates and return as Touch Detected */
	   	   	   if(tsc2007_read_reg(&pObj->Ctx, TSC2007_READ_XREG,&pData[2] , 2) != TSC2007_OK)
	   	   	   {
	   	   		   	   ret = TSC2007_ERROR;
	   	   	   }

	   	   	   else if(tsc2007_read_reg(&pObj->Ctx, TSC2007_READ_YREG, &pData[4], 2) != TSC2007_OK)
	   	   	   {
	   	   		   	   ret = TSC2007_ERROR;
	   	   	   	 }
	   	   	   	   	   /* Touch detected */
	   	   	   	   	   ret = 1;
   }

   else
   {
	   /* If invalid number of touch detected, set it to zero */
	   ret = 0;
   }

  #if 0
  else
  {
    if(pData[1] == 0x83U)
    {
      /* Touch detected */
      ret = 1;
    }
    else
    {
      /* If invalid number of touch detected, set it to zero */
      ret = 0;
    }
  }
#endif

  return ret;
}

/**
  * @brief  Wrap IO bus read function to component register red function
  * @param  handle Component object handle
  * @param  Reg The target register address to read
  * @param  pData The target register value to be read
  * @param  Length buffer size to be read
  * @retval Component status.
  */
static int32_t ReadRegWrap(void *handle, uint8_t Reg, uint8_t* pData, uint16_t Length)
{
  TSC2007_Object_t *pObj = (TSC2007_Object_t *)handle;
  return pObj->IO.ReadReg(pObj->IO.Address, Reg, pData, Length);
}

/**
  * @brief  Wrap IO bus write function to component register write function
  * @param  handle Component object handle
  * @param  Reg The target register address to write
  * @param  pData The target register value to be written
  * @param  Length buffer size to be written
  * @retval Component status.
  */
static int32_t WriteRegWrap(void *handle, uint8_t Reg, uint8_t* pData, uint16_t Length)
{
  TSC2007_Object_t *pObj = (TSC2007_Object_t *)handle;

  return pObj->IO.WriteReg(pObj->IO.Address, Reg, pData, Length);
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

