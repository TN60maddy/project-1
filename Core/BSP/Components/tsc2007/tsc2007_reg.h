/**
 ******************************************************************************
 * @file    tsc2007_reg.h
 * @author  MCD Application Team
 * @brief   Header of tsc2007_regs.c
 *
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TSC2007_REG_H
#define TSC2007_REG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
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

/** @defgroup TSC2007_Exported_Constants Exported Constants
  * @{
  */

/*  */
#define TSC2007_READ_XREG                             0xC0U
#define TSC2007_READ_YREG                             0xD0U


/**
  * @}
  */

/** @defgroup EXC7200_Exported_Types EXC7200 Exported Types
 * @{
 */
typedef int32_t (*TSC2007_Write_Func)(void *, uint8_t, uint8_t*, uint16_t);
typedef int32_t (*TSC2007_Read_Func) (void *, uint8_t, uint8_t*, uint16_t);

typedef struct
{
  TSC2007_Write_Func   WriteReg;
  TSC2007_Read_Func    ReadReg;
  void                *handle;
} tsc2007_ctx_t;
/**
 * @}
 */

/** @addtogroup EXC7200_Exported_Functions
 * @{
 */
int32_t tsc2007_write_reg(tsc2007_ctx_t *ctx, uint8_t reg, uint8_t *pbuf, uint16_t length);
int32_t tsc2007_read_reg(tsc2007_ctx_t *ctx, uint8_t reg, uint8_t *pbuf, uint16_t length);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif
#endif /* TSC2007_REG_H */

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
