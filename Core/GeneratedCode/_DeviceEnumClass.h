/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This file was generated automatically by Embedded Wizard Studio.
*
* Please do not make any modifications of this file! The modifications are lost
* when the file is generated again by Embedded Wizard Studio!
*
* The template of this heading text can be found in the file 'head.ewt' in the
* directory 'Platforms' of your Embedded Wizard installation directory. If you
* wish to adapt this text, please copy the template file 'head.ewt' into your
* project directory and edit the copy only. Please avoid any modifications of
* the original template file!
*
* Version  : 14.03
* Profile  : STM32
* Platform : STM.STM32.RGB565
*
*******************************************************************************/

#ifndef _DeviceEnumClass_H
#define _DeviceEnumClass_H

#ifdef __cplusplus
  extern "C"
  {
#endif

#include "ewrte.h"
#if ( EW_RTE_VERSION >> 16 ) != 14
  #error Wrong version of Embedded Wizard Runtime Environment.
#endif

#include "ewgfx.h"
#if ( EW_GFX_VERSION >> 16 ) != 14
  #error Wrong version of Embedded Wizard Graphics Engine.
#endif

/* Forward declaration of the class Device::EnumClass */
#ifndef _DeviceEnumClass_
  EW_DECLARE_CLASS( DeviceEnumClass )
#define _DeviceEnumClass_
#endif

/* Forward declaration of the class Resources::Bitmap */
#ifndef _ResourcesBitmap_
  EW_DECLARE_CLASS( ResourcesBitmap )
#define _ResourcesBitmap_
#endif


/* Deklaration of class : 'Device::EnumClass' */
EW_DEFINE_FIELDS( DeviceEnumClass, XObject )
EW_END_OF_FIELDS( DeviceEnumClass )

/* Virtual Method Table (VMT) for the class : 'Device::EnumClass' */
EW_DEFINE_METHODS( DeviceEnumClass, XObject )
  EW_METHOD( GetString,         XString )( DeviceEnumClass _this, XInt32 aItem )
  EW_METHOD( GetIcon,           ResourcesBitmap )( DeviceEnumClass _this, XInt32 
    aItem )
EW_END_OF_METHODS( DeviceEnumClass )

/* 'C' function for method : 'Device::EnumClass.GetString()' */
XString DeviceEnumClass_GetString( DeviceEnumClass _this, XInt32 aItem );

/* Wrapper function for the virtual method : 'Device::EnumClass.GetString()' */
XString DeviceEnumClass__GetString( void* _this, XInt32 aItem );

/* 'C' function for method : 'Device::EnumClass.GetIcon()' */
ResourcesBitmap DeviceEnumClass_GetIcon( DeviceEnumClass _this, XInt32 aItem );

/* Wrapper function for the virtual method : 'Device::EnumClass.GetIcon()' */
ResourcesBitmap DeviceEnumClass__GetIcon( void* _this, XInt32 aItem );

#ifdef __cplusplus
  }
#endif

#endif /* _DeviceEnumClass_H */

/* Embedded Wizard */
