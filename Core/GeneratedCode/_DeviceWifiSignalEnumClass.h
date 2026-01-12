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

#ifndef _DeviceWifiSignalEnumClass_H
#define _DeviceWifiSignalEnumClass_H

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

#include "_DeviceEnumClass.h"

/* Forward declaration of the class Device::WifiSignalEnumClass */
#ifndef _DeviceWifiSignalEnumClass_
  EW_DECLARE_CLASS( DeviceWifiSignalEnumClass )
#define _DeviceWifiSignalEnumClass_
#endif

/* Forward declaration of the class Resources::Bitmap */
#ifndef _ResourcesBitmap_
  EW_DECLARE_CLASS( ResourcesBitmap )
#define _ResourcesBitmap_
#endif


/* Deklaration of class : 'Device::WifiSignalEnumClass' */
EW_DEFINE_FIELDS( DeviceWifiSignalEnumClass, DeviceEnumClass )
EW_END_OF_FIELDS( DeviceWifiSignalEnumClass )

/* Virtual Method Table (VMT) for the class : 'Device::WifiSignalEnumClass' */
EW_DEFINE_METHODS( DeviceWifiSignalEnumClass, DeviceEnumClass )
  EW_METHOD( GetString,         XString )( DeviceWifiSignalEnumClass _this, XInt32 
    aItem )
  EW_METHOD( GetIcon,           ResourcesBitmap )( DeviceWifiSignalEnumClass _this, 
    XInt32 aItem )
EW_END_OF_METHODS( DeviceWifiSignalEnumClass )

/* 'C' function for method : 'Device::WifiSignalEnumClass.GetString()' */
XString DeviceWifiSignalEnumClass_GetString( DeviceWifiSignalEnumClass _this, XInt32 
  aItem );

/* 'C' function for method : 'Device::WifiSignalEnumClass.GetIcon()' */
ResourcesBitmap DeviceWifiSignalEnumClass_GetIcon( DeviceWifiSignalEnumClass _this, 
  XInt32 aItem );

#ifdef __cplusplus
  }
#endif

#endif /* _DeviceWifiSignalEnumClass_H */

/* Embedded Wizard */
