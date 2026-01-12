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

#ifndef _DeviceWifiNetworksProviderClass_H
#define _DeviceWifiNetworksProviderClass_H

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

#include "_DeviceDataProvider.h"

/* Forward declaration of the class Device::WifiNetworksProviderClass */
#ifndef _DeviceWifiNetworksProviderClass_
  EW_DECLARE_CLASS( DeviceWifiNetworksProviderClass )
#define _DeviceWifiNetworksProviderClass_
#endif


/* Deklaration of class : 'Device::WifiNetworksProviderClass' */
EW_DEFINE_FIELDS( DeviceWifiNetworksProviderClass, DeviceDataProvider )
EW_END_OF_FIELDS( DeviceWifiNetworksProviderClass )

/* Virtual Method Table (VMT) for the class : 'Device::WifiNetworksProviderClass' */
EW_DEFINE_METHODS( DeviceWifiNetworksProviderClass, DeviceDataProvider )
  EW_METHOD( GetInt32Data,      XInt32 )( DeviceWifiNetworksProviderClass _this, 
    XInt32 aRow, XInt32 aColumn )
  EW_METHOD( GetStringData,     XString )( DeviceWifiNetworksProviderClass _this, 
    XInt32 aRow, XInt32 aColumn )
  EW_METHOD( GetNoOfData,       XInt32 )( DeviceWifiNetworksProviderClass _this )
EW_END_OF_METHODS( DeviceWifiNetworksProviderClass )

/* 'C' function for method : 'Device::WifiNetworksProviderClass.GetInt32Data()' */
XInt32 DeviceWifiNetworksProviderClass_GetInt32Data( DeviceWifiNetworksProviderClass _this, 
  XInt32 aRow, XInt32 aColumn );

/* 'C' function for method : 'Device::WifiNetworksProviderClass.GetStringData()' */
XString DeviceWifiNetworksProviderClass_GetStringData( DeviceWifiNetworksProviderClass _this, 
  XInt32 aRow, XInt32 aColumn );

/* 'C' function for method : 'Device::WifiNetworksProviderClass.GetNoOfData()' */
XInt32 DeviceWifiNetworksProviderClass_GetNoOfData( DeviceWifiNetworksProviderClass _this );

#ifdef __cplusplus
  }
#endif

#endif /* _DeviceWifiNetworksProviderClass_H */

/* Embedded Wizard */
