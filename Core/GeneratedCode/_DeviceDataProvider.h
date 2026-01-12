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

#ifndef _DeviceDataProvider_H
#define _DeviceDataProvider_H

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

/* Forward declaration of the class Device::DataProvider */
#ifndef _DeviceDataProvider_
  EW_DECLARE_CLASS( DeviceDataProvider )
#define _DeviceDataProvider_
#endif


/* Deklaration of class : 'Device::DataProvider' */
EW_DEFINE_FIELDS( DeviceDataProvider, XObject )
EW_END_OF_FIELDS( DeviceDataProvider )

/* Virtual Method Table (VMT) for the class : 'Device::DataProvider' */
EW_DEFINE_METHODS( DeviceDataProvider, XObject )
  EW_METHOD( GetInt32Data,      XInt32 )( DeviceDataProvider _this, XInt32 aRow, 
    XInt32 aColumn )
  EW_METHOD( GetStringData,     XString )( DeviceDataProvider _this, XInt32 aRow, 
    XInt32 aColumn )
  EW_METHOD( GetNoOfData,       XInt32 )( DeviceDataProvider _this )
EW_END_OF_METHODS( DeviceDataProvider )

/* 'C' function for method : 'Device::DataProvider.GetInt32Data()' */
XInt32 DeviceDataProvider_GetInt32Data( DeviceDataProvider _this, XInt32 aRow, XInt32 
  aColumn );

/* Wrapper function for the virtual method : 'Device::DataProvider.GetInt32Data()' */
XInt32 DeviceDataProvider__GetInt32Data( void* _this, XInt32 aRow, XInt32 aColumn );

/* 'C' function for method : 'Device::DataProvider.GetStringData()' */
XString DeviceDataProvider_GetStringData( DeviceDataProvider _this, XInt32 aRow, 
  XInt32 aColumn );

/* Wrapper function for the virtual method : 'Device::DataProvider.GetStringData()' */
XString DeviceDataProvider__GetStringData( void* _this, XInt32 aRow, XInt32 aColumn );

/* 'C' function for method : 'Device::DataProvider.GetNoOfData()' */
XInt32 DeviceDataProvider_GetNoOfData( DeviceDataProvider _this );

/* Wrapper function for the virtual method : 'Device::DataProvider.GetNoOfData()' */
XInt32 DeviceDataProvider__GetNoOfData( void* _this );

/* 'C' function for method : 'Device::DataProvider.NotifyChange()' */
void DeviceDataProvider_NotifyChange( DeviceDataProvider _this );

/* Wrapper function for the non virtual method : 'Device::DataProvider.NotifyChange()' */
void DeviceDataProvider__NotifyChange( void* _this );

/* The following define announces the presence of the method Device::DataProvider.NotifyChange(). */
#define _DeviceDataProvider__NotifyChange_

#ifdef __cplusplus
  }
#endif

#endif /* _DeviceDataProvider_H */

/* Embedded Wizard */
