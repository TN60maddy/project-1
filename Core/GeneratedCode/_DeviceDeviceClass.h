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

#ifndef _DeviceDeviceClass_H
#define _DeviceDeviceClass_H

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

#include "_CoreSystemEvent.h"
#include "_TemplatesDeviceClass.h"

/* Forward declaration of the class Device::DeviceClass */
#ifndef _DeviceDeviceClass_
  EW_DECLARE_CLASS( DeviceDeviceClass )
#define _DeviceDeviceClass_
#endif

/* Forward declaration of the class Resources::Bitmap */
#ifndef _ResourcesBitmap_
  EW_DECLARE_CLASS( ResourcesBitmap )
#define _ResourcesBitmap_
#endif


/* This class implements the interface between the GUI application and the device. */
EW_DEFINE_FIELDS( DeviceDeviceClass, TemplatesDeviceClass )
  EW_PROPERTY( MfgDateTime,     XInt64 )
  EW_OBJECT  ( PowerSwitchEvent, CoreSystemEvent )
  EW_OBJECT  ( StopEvent,       CoreSystemEvent )
  EW_OBJECT  ( DoorOpenEvent,   CoreSystemEvent )
  EW_PROPERTY( SerialNumber,    XString )
  EW_PROPERTY( Name,            XString )
  EW_PROPERTY( Manufacturer,    XString )
  EW_PROPERTY( ModelNumber,     XString )
  EW_PROPERTY( FirmwareVersion, XString )
  EW_PROPERTY( AppQRCode,       XString )
  EW_PROPERTY( NewFirmwareVersion, XString )
  EW_PROPERTY( NewFirmwareVersionDesc, XString )
  EW_PROPERTY( Brightness,      XInt32 )
  EW_PROPERTY( CurrentPage,     XInt32 )
  EW_PROPERTY( CurrentSettings, XInt32 )
  EW_VARIABLE( previousPage,    XInt32 )
  EW_VARIABLE( previousSettings, XInt32 )
  EW_PROPERTY( WifiSignal,      XInt32 )
  EW_PROPERTY( BatteryLevel,    XInt32 )
  EW_PROPERTY( BatteryChargeStatus, XInt32 )
  EW_PROPERTY( FlowRate,        XInt32 )
  EW_PROPERTY( InfusionVolume,  XInt32 )
  EW_PROPERTY( InfusionTime,    XInt32 )
  EW_PROPERTY( InfusionState,   XInt32 )
  EW_PROPERTY( RemainingTime,   XInt32 )
  EW_PROPERTY( VolumeInfused,   XInt32 )
  EW_PROPERTY( PressureOnTube,  XInt32 )
  EW_PROPERTY( BolusVolumeSet,  XInt32 )
  EW_PROPERTY( VolumeInfusedInBolus, XInt32 )
  EW_PROPERTY( PressureSetting, XInt32 )
  EW_PROPERTY( SingleBubbleThreshold, XInt32 )
  EW_PROPERTY( CumulativeBubbleThreshold, XInt32 )
  EW_PROPERTY( BootProgress,    XInt32 )
  EW_PROPERTY( CurrentPopup,    XInt32 )
  EW_ARRAY   ( PressureNormalMax, XInt32, [9])
  EW_ARRAY   ( PressureWarningMax, XInt32, [9])
  EW_ARRAY   ( PressureErrorMax, XInt32, [9])
  EW_PROPERTY( NotificationId,  XInt32 )
  EW_PROPERTY( CurrentSubSettings, XInt32 )
  EW_PROPERTY( AudioVolume,     XInt32 )
  EW_PROPERTY( BolusRate,       XInt32 )
  EW_PROPERTY( KVORateHighFlowRate, XInt32 )
  EW_PROPERTY( KVORateMediumFlowRate, XInt32 )
  EW_PROPERTY( KVORateLowFlowRate, XInt32 )
  EW_PROPERTY( FlowRateMedium,  XInt32 )
  EW_PROPERTY( FlowRateLow,     XInt32 )
  EW_PROPERTY( WifiStatus,      XBool )
  EW_PROPERTY( SoftwareUpdate,  XBool )
  EW_PROPERTY( InStopping,      XBool )
  EW_PROPERTY( KVOMode,         XBool )
EW_END_OF_FIELDS( DeviceDeviceClass )

/* Virtual Method Table (VMT) for the class : 'Device::DeviceClass' */
EW_DEFINE_METHODS( DeviceDeviceClass, TemplatesDeviceClass )
EW_END_OF_METHODS( DeviceDeviceClass )

/* 'C' function for method : 'Device::DeviceClass.OnSetBrightness()' */
void DeviceDeviceClass_OnSetBrightness( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateBrightness( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateBrightness()' */
void DeviceDeviceClass__UpdateBrightness( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateBrightness(). */
#define _DeviceDeviceClass__UpdateBrightness_

/* 'C' function for method : 'Device::DeviceClass.OnSetCurrentPage()' */
void DeviceDeviceClass_OnSetCurrentPage( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateCurrentPage( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateCurrentPage()' */
void DeviceDeviceClass__UpdateCurrentPage( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateCurrentPage(). */
#define _DeviceDeviceClass__UpdateCurrentPage_

/* 'C' function for method : 'Device::DeviceClass.OnSetCurrentSettings()' */
void DeviceDeviceClass_OnSetCurrentSettings( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateCurrentSettings( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateCurrentSettings()' */
void DeviceDeviceClass__UpdateCurrentSettings( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateCurrentSettings(). */
#define _DeviceDeviceClass__UpdateCurrentSettings_

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_GoToPreviousPage( DeviceDeviceClass _this );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.GoToPreviousPage()' */
void DeviceDeviceClass__GoToPreviousPage( void* _this );

/* The following define announces the presence of the method Device::DeviceClass.GoToPreviousPage(). */
#define _DeviceDeviceClass__GoToPreviousPage_

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_GoToPreviousSettings( DeviceDeviceClass _this );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.GoToPreviousSettings()' */
void DeviceDeviceClass__GoToPreviousSettings( void* _this );

/* The following define announces the presence of the method Device::DeviceClass.GoToPreviousSettings(). */
#define _DeviceDeviceClass__GoToPreviousSettings_

/* 'C' function for method : 'Device::DeviceClass.OnSetWifiSignal()' */
void DeviceDeviceClass_OnSetWifiSignal( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateWifiSignal( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateWifiSignal()' */
void DeviceDeviceClass__UpdateWifiSignal( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateWifiSignal(). */
#define _DeviceDeviceClass__UpdateWifiSignal_

/* 'C' function for method : 'Device::DeviceClass.OnSetBatteryLevel()' */
void DeviceDeviceClass_OnSetBatteryLevel( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateBatteryLevel( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateBatteryLevel()' */
void DeviceDeviceClass__UpdateBatteryLevel( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateBatteryLevel(). */
#define _DeviceDeviceClass__UpdateBatteryLevel_

/* 'C' function for method : 'Device::DeviceClass.OnSetBatteryChargeStatus()' */
void DeviceDeviceClass_OnSetBatteryChargeStatus( DeviceDeviceClass _this, XInt32 
  value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateBatteryChargeStatus( DeviceDeviceClass _this, XInt32 
  aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateBatteryChargeStatus()' */
void DeviceDeviceClass__UpdateBatteryChargeStatus( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateBatteryChargeStatus(). */
#define _DeviceDeviceClass__UpdateBatteryChargeStatus_

/* 'C' function for method : 'Device::DeviceClass.OnSetFlowRate()' */
void DeviceDeviceClass_OnSetFlowRate( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateFlowRate( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateFlowRate()' */
void DeviceDeviceClass__UpdateFlowRate( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateFlowRate(). */
#define _DeviceDeviceClass__UpdateFlowRate_

/* 'C' function for method : 'Device::DeviceClass.OnSetInfusionVolume()' */
void DeviceDeviceClass_OnSetInfusionVolume( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateInfusionVolume( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateInfusionVolume()' */
void DeviceDeviceClass__UpdateInfusionVolume( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateInfusionVolume(). */
#define _DeviceDeviceClass__UpdateInfusionVolume_

/* 'C' function for method : 'Device::DeviceClass.OnSetInfusionTime()' */
void DeviceDeviceClass_OnSetInfusionTime( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateInfusionTime( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateInfusionTime()' */
void DeviceDeviceClass__UpdateInfusionTime( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateInfusionTime(). */
#define _DeviceDeviceClass__UpdateInfusionTime_

/* 'C' function for method : 'Device::DeviceClass.OnSetInfusionState()' */
void DeviceDeviceClass_OnSetInfusionState( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateInfusionState( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateInfusionState()' */
void DeviceDeviceClass__UpdateInfusionState( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateInfusionState(). */
#define _DeviceDeviceClass__UpdateInfusionState_

/* 'C' function for method : 'Device::DeviceClass.OnSetRemainingTime()' */
void DeviceDeviceClass_OnSetRemainingTime( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateRemainingTime( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateRemainingTime()' */
void DeviceDeviceClass__UpdateRemainingTime( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateRemainingTime(). */
#define _DeviceDeviceClass__UpdateRemainingTime_

/* 'C' function for method : 'Device::DeviceClass.OnSetVolumeInfused()' */
void DeviceDeviceClass_OnSetVolumeInfused( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateVolumeInfused( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateVolumeInfused()' */
void DeviceDeviceClass__UpdateVolumeInfused( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateVolumeInfused(). */
#define _DeviceDeviceClass__UpdateVolumeInfused_

/* 'C' function for method : 'Device::DeviceClass.OnSetPressureOnTube()' */
void DeviceDeviceClass_OnSetPressureOnTube( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdatePressureOnTube( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdatePressureOnTube()' */
void DeviceDeviceClass__UpdatePressureOnTube( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdatePressureOnTube(). */
#define _DeviceDeviceClass__UpdatePressureOnTube_

/* 'C' function for method : 'Device::DeviceClass.OnSetBolusVolumeSet()' */
void DeviceDeviceClass_OnSetBolusVolumeSet( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateBolusVolumeSet( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateBolusVolumeSet()' */
void DeviceDeviceClass__UpdateBolusVolumeSet( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateBolusVolumeSet(). */
#define _DeviceDeviceClass__UpdateBolusVolumeSet_

/* 'C' function for method : 'Device::DeviceClass.OnSetVolumeInfusedInBolus()' */
void DeviceDeviceClass_OnSetVolumeInfusedInBolus( DeviceDeviceClass _this, XInt32 
  value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateVolumeInfusedInBolus( DeviceDeviceClass _this, XInt32 
  aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateVolumeInfusedInBolus()' */
void DeviceDeviceClass__UpdateVolumeInfusedInBolus( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateVolumeInfusedInBolus(). */
#define _DeviceDeviceClass__UpdateVolumeInfusedInBolus_

/* 'C' function for method : 'Device::DeviceClass.OnSetPressureSetting()' */
void DeviceDeviceClass_OnSetPressureSetting( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdatePressureSetting( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdatePressureSetting()' */
void DeviceDeviceClass__UpdatePressureSetting( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdatePressureSetting(). */
#define _DeviceDeviceClass__UpdatePressureSetting_

/* 'C' function for method : 'Device::DeviceClass.OnSetSingleBubbleThreshold()' */
void DeviceDeviceClass_OnSetSingleBubbleThreshold( DeviceDeviceClass _this, XInt32 
  value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateSingleBubbleThreshold( DeviceDeviceClass _this, XInt32 
  aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateSingleBubbleThreshold()' */
void DeviceDeviceClass__UpdateSingleBubbleThreshold( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateSingleBubbleThreshold(). */
#define _DeviceDeviceClass__UpdateSingleBubbleThreshold_

/* 'C' function for method : 'Device::DeviceClass.OnSetCumulativeBubbleThreshold()' */
void DeviceDeviceClass_OnSetCumulativeBubbleThreshold( DeviceDeviceClass _this, 
  XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateCumulativeBubbleThreshold( DeviceDeviceClass _this, 
  XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateCumulativeBubbleThreshold()' */
void DeviceDeviceClass__UpdateCumulativeBubbleThreshold( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateCumulativeBubbleThreshold(). */
#define _DeviceDeviceClass__UpdateCumulativeBubbleThreshold_

/* 'C' function for method : 'Device::DeviceClass.OnSetSerialNumber()' */
void DeviceDeviceClass_OnSetSerialNumber( DeviceDeviceClass _this, XString value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateSerialNumber( DeviceDeviceClass _this, XString aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateSerialNumber()' */
void DeviceDeviceClass__UpdateSerialNumber( void* _this, XString aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateSerialNumber(). */
#define _DeviceDeviceClass__UpdateSerialNumber_

/* 'C' function for method : 'Device::DeviceClass.OnSetName()' */
void DeviceDeviceClass_OnSetName( DeviceDeviceClass _this, XString value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateName( DeviceDeviceClass _this, XString aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateName()' */
void DeviceDeviceClass__UpdateName( void* _this, XString aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateName(). */
#define _DeviceDeviceClass__UpdateName_

/* 'C' function for method : 'Device::DeviceClass.OnSetManufacturer()' */
void DeviceDeviceClass_OnSetManufacturer( DeviceDeviceClass _this, XString value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateManufacturer( DeviceDeviceClass _this, XString aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateManufacturer()' */
void DeviceDeviceClass__UpdateManufacturer( void* _this, XString aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateManufacturer(). */
#define _DeviceDeviceClass__UpdateManufacturer_

/* 'C' function for method : 'Device::DeviceClass.OnSetMfgDateTime()' */
void DeviceDeviceClass_OnSetMfgDateTime( DeviceDeviceClass _this, XInt64 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateMfgDateTime( DeviceDeviceClass _this, XInt64 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateMfgDateTime()' */
void DeviceDeviceClass__UpdateMfgDateTime( void* _this, XInt64 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateMfgDateTime(). */
#define _DeviceDeviceClass__UpdateMfgDateTime_

/* 'C' function for method : 'Device::DeviceClass.OnSetModelNumber()' */
void DeviceDeviceClass_OnSetModelNumber( DeviceDeviceClass _this, XString value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateModelNumber( DeviceDeviceClass _this, XString aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateModelNumber()' */
void DeviceDeviceClass__UpdateModelNumber( void* _this, XString aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateModelNumber(). */
#define _DeviceDeviceClass__UpdateModelNumber_

/* 'C' function for method : 'Device::DeviceClass.OnSetFirmwareVersion()' */
void DeviceDeviceClass_OnSetFirmwareVersion( DeviceDeviceClass _this, XString value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateFirmwareVersion( DeviceDeviceClass _this, XString aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateFirmwareVersion()' */
void DeviceDeviceClass__UpdateFirmwareVersion( void* _this, XString aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateFirmwareVersion(). */
#define _DeviceDeviceClass__UpdateFirmwareVersion_

/* 'C' function for method : 'Device::DeviceClass.OnSetWifiStatus()' */
void DeviceDeviceClass_OnSetWifiStatus( DeviceDeviceClass _this, XBool value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateWifiStatus( DeviceDeviceClass _this, XBool aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateWifiStatus()' */
void DeviceDeviceClass__UpdateWifiStatus( void* _this, XBool aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateWifiStatus(). */
#define _DeviceDeviceClass__UpdateWifiStatus_

/* 'C' function for method : 'Device::DeviceClass.OnSetSoftwareUpdate()' */
void DeviceDeviceClass_OnSetSoftwareUpdate( DeviceDeviceClass _this, XBool value );

/* 'C' function for method : 'Device::DeviceClass.OnSetBootProgress()' */
void DeviceDeviceClass_OnSetBootProgress( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateBootProgress( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateBootProgress()' */
void DeviceDeviceClass__UpdateBootProgress( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateBootProgress(). */
#define _DeviceDeviceClass__UpdateBootProgress_

/* 'C' function for method : 'Device::DeviceClass.StartInfusion()' */
void DeviceDeviceClass_StartInfusion( DeviceDeviceClass _this );

/* 'C' function for method : 'Device::DeviceClass.RestartInfusion()' */
void DeviceDeviceClass_RestartInfusion( DeviceDeviceClass _this );

/* 'C' function for method : 'Device::DeviceClass.ClearSettings()' */
void DeviceDeviceClass_ClearSettings( DeviceDeviceClass _this );

/* 'C' function for method : 'Device::DeviceClass.OnSetCurrentPopup()' */
void DeviceDeviceClass_OnSetCurrentPopup( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateCurrentPopup( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateCurrentPopup()' */
void DeviceDeviceClass__UpdateCurrentPopup( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateCurrentPopup(). */
#define _DeviceDeviceClass__UpdateCurrentPopup_

/* 'C' function for method : 'Device::DeviceClass.StopInfusion()' */
void DeviceDeviceClass_StopInfusion( DeviceDeviceClass _this );

/* 'C' function for method : 'Device::DeviceClass.GetPresurreNormalMax()' */
XInt32 DeviceDeviceClass_GetPresurreNormalMax( DeviceDeviceClass _this, XInt32 aStage );

/* 'C' function for method : 'Device::DeviceClass.GetPresurreWarningMax()' */
XInt32 DeviceDeviceClass_GetPresurreWarningMax( DeviceDeviceClass _this, XInt32 
  aStage );

/* 'C' function for method : 'Device::DeviceClass.GetPresurreErrorMax()' */
XInt32 DeviceDeviceClass_GetPresurreErrorMax( DeviceDeviceClass _this, XInt32 aStage );

/* 'C' function for method : 'Device::DeviceClass.OnSetInStopping()' */
void DeviceDeviceClass_OnSetInStopping( DeviceDeviceClass _this, XBool value );

/* 'C' function for method : 'Device::DeviceClass.OnSetNotificationId()' */
void DeviceDeviceClass_OnSetNotificationId( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateNotificationId( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateNotificationId()' */
void DeviceDeviceClass__UpdateNotificationId( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateNotificationId(). */
#define _DeviceDeviceClass__UpdateNotificationId_

/* 'C' function for method : 'Device::DeviceClass.GetNotificationType()' */
XEnum DeviceDeviceClass_GetNotificationType( DeviceDeviceClass _this, XInt32 aId );

/* 'C' function for method : 'Device::DeviceClass.GetNotificationCaption()' */
XString DeviceDeviceClass_GetNotificationCaption( DeviceDeviceClass _this, XInt32 
  aId );

/* 'C' function for method : 'Device::DeviceClass.GetNotificationMessage()' */
XString DeviceDeviceClass_GetNotificationMessage( DeviceDeviceClass _this, XInt32 
  aId );

/* 'C' function for method : 'Device::DeviceClass.GetErrorCode()' */
XString DeviceDeviceClass_GetErrorCode( DeviceDeviceClass _this, XInt32 aErrorId );

/* 'C' function for method : 'Device::DeviceClass.IsErrorWithSound()' */
XBool DeviceDeviceClass_IsErrorWithSound( DeviceDeviceClass _this, XInt32 aErrorId );

/* 'C' function for method : 'Device::DeviceClass.GetNotificationImage()' */
ResourcesBitmap DeviceDeviceClass_GetNotificationImage( DeviceDeviceClass _this, 
  XInt32 aId );

/* 'C' function for method : 'Device::DeviceClass.MuteAlarm()' */
void DeviceDeviceClass_MuteAlarm( DeviceDeviceClass _this, XInt32 aId );

/* 'C' function for method : 'Device::DeviceClass.ConfirmNotification()' */
void DeviceDeviceClass_ConfirmNotification( DeviceDeviceClass _this, XInt32 aId );

/* 'C' function for method : 'Device::DeviceClass.OnSetCurrentSubSettings()' */
void DeviceDeviceClass_OnSetCurrentSubSettings( DeviceDeviceClass _this, XInt32 
  value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateCurrentSubSettings( DeviceDeviceClass _this, XInt32 
  aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateCurrentSubSettings()' */
void DeviceDeviceClass__UpdateCurrentSubSettings( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateCurrentSubSettings(). */
#define _DeviceDeviceClass__UpdateCurrentSubSettings_

/* 'C' function for method : 'Device::DeviceClass.OnSetAppQRCode()' */
void DeviceDeviceClass_OnSetAppQRCode( DeviceDeviceClass _this, XString value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateAppQRCode( DeviceDeviceClass _this, XString aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateAppQRCode()' */
void DeviceDeviceClass__UpdateAppQRCode( void* _this, XString aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateAppQRCode(). */
#define _DeviceDeviceClass__UpdateAppQRCode_

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateWifiNetworkList( DeviceDeviceClass _this );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateWifiNetworkList()' */
void DeviceDeviceClass__UpdateWifiNetworkList( void* _this );

/* The following define announces the presence of the method Device::DeviceClass.UpdateWifiNetworkList(). */
#define _DeviceDeviceClass__UpdateWifiNetworkList_

/* 'C' function for method : 'Device::DeviceClass.OnSetAudioVolume()' */
void DeviceDeviceClass_OnSetAudioVolume( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateAudioVolume( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateAudioVolume()' */
void DeviceDeviceClass__UpdateAudioVolume( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateAudioVolume(). */
#define _DeviceDeviceClass__UpdateAudioVolume_

/* 'C' function for method : 'Device::DeviceClass.OnSetNewFirmwareVersion()' */
void DeviceDeviceClass_OnSetNewFirmwareVersion( DeviceDeviceClass _this, XString 
  value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateNewFirmwareVersion( DeviceDeviceClass _this, XString 
  aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateNewFirmwareVersion()' */
void DeviceDeviceClass__UpdateNewFirmwareVersion( void* _this, XString aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateNewFirmwareVersion(). */
#define _DeviceDeviceClass__UpdateNewFirmwareVersion_

/* 'C' function for method : 'Device::DeviceClass.OnSetNewFirmwareVersionDesc()' */
void DeviceDeviceClass_OnSetNewFirmwareVersionDesc( DeviceDeviceClass _this, XString 
  value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateNewFirmwareVersionDesc( DeviceDeviceClass _this, XString 
  aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateNewFirmwareVersionDesc()' */
void DeviceDeviceClass__UpdateNewFirmwareVersionDesc( void* _this, XString aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateNewFirmwareVersionDesc(). */
#define _DeviceDeviceClass__UpdateNewFirmwareVersionDesc_

/* This method is intended to be called by the device to notify the GUI application 
   about a particular system event. */
void DeviceDeviceClass_TriggerPowerSwitchEvent( DeviceDeviceClass _this );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.TriggerPowerSwitchEvent()' */
void DeviceDeviceClass__TriggerPowerSwitchEvent( void* _this );

/* The following define announces the presence of the method Device::DeviceClass.TriggerPowerSwitchEvent(). */
#define _DeviceDeviceClass__TriggerPowerSwitchEvent_

/* This method is intended to be called by the device to notify the GUI application 
   about a particular system event. */
void DeviceDeviceClass_TriggerStopEvent( DeviceDeviceClass _this );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.TriggerStopEvent()' */
void DeviceDeviceClass__TriggerStopEvent( void* _this );

/* The following define announces the presence of the method Device::DeviceClass.TriggerStopEvent(). */
#define _DeviceDeviceClass__TriggerStopEvent_

/* This method is intended to be called by the device to notify the GUI application 
   about a particular system event. */
void DeviceDeviceClass_TriggerDoorOpenEvent( DeviceDeviceClass _this );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.TriggerDoorOpenEvent()' */
void DeviceDeviceClass__TriggerDoorOpenEvent( void* _this );

/* The following define announces the presence of the method Device::DeviceClass.TriggerDoorOpenEvent(). */
#define _DeviceDeviceClass__TriggerDoorOpenEvent_

/* 'C' function for method : 'Device::DeviceClass.OnSetBolusRate()' */
void DeviceDeviceClass_OnSetBolusRate( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateBolusRate( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateBolusRate()' */
void DeviceDeviceClass__UpdateBolusRate( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateBolusRate(). */
#define _DeviceDeviceClass__UpdateBolusRate_

/* 'C' function for method : 'Device::DeviceClass.OnSetKVOMode()' */
void DeviceDeviceClass_OnSetKVOMode( DeviceDeviceClass _this, XBool value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateKVOMode( DeviceDeviceClass _this, XBool aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateKVOMode()' */
void DeviceDeviceClass__UpdateKVOMode( void* _this, XBool aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateKVOMode(). */
#define _DeviceDeviceClass__UpdateKVOMode_

/* 'C' function for method : 'Device::DeviceClass.OnSetKVORateHighFlowRate()' */
void DeviceDeviceClass_OnSetKVORateHighFlowRate( DeviceDeviceClass _this, XInt32 
  value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateKVORateHighFlowRate( DeviceDeviceClass _this, XInt32 
  aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateKVORateHighFlowRate()' */
void DeviceDeviceClass__UpdateKVORateHighFlowRate( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateKVORateHighFlowRate(). */
#define _DeviceDeviceClass__UpdateKVORateHighFlowRate_

/* 'C' function for method : 'Device::DeviceClass.OnSetKVORateMediumFlowRate()' */
void DeviceDeviceClass_OnSetKVORateMediumFlowRate( DeviceDeviceClass _this, XInt32 
  value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateKVORateMediumFlowRate( DeviceDeviceClass _this, XInt32 
  aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateKVORateMediumFlowRate()' */
void DeviceDeviceClass__UpdateKVORateMediumFlowRate( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateKVORateMediumFlowRate(). */
#define _DeviceDeviceClass__UpdateKVORateMediumFlowRate_

/* 'C' function for method : 'Device::DeviceClass.OnSetKVORateLowFlowRate()' */
void DeviceDeviceClass_OnSetKVORateLowFlowRate( DeviceDeviceClass _this, XInt32 
  value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateKVORateLowFlowRate( DeviceDeviceClass _this, XInt32 
  aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateKVORateLowFlowRate()' */
void DeviceDeviceClass__UpdateKVORateLowFlowRate( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateKVORateLowFlowRate(). */
#define _DeviceDeviceClass__UpdateKVORateLowFlowRate_

/* 'C' function for method : 'Device::DeviceClass.OnSetFlowRateMedium()' */
void DeviceDeviceClass_OnSetFlowRateMedium( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateFlowRateMedium( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateFlowRateMedium()' */
void DeviceDeviceClass__UpdateFlowRateMedium( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateFlowRateMedium(). */
#define _DeviceDeviceClass__UpdateFlowRateMedium_

/* 'C' function for method : 'Device::DeviceClass.OnSetFlowRateLow()' */
void DeviceDeviceClass_OnSetFlowRateLow( DeviceDeviceClass _this, XInt32 value );

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateFlowRateLow( DeviceDeviceClass _this, XInt32 aNewValue );

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateFlowRateLow()' */
void DeviceDeviceClass__UpdateFlowRateLow( void* _this, XInt32 aNewValue );

/* The following define announces the presence of the method Device::DeviceClass.UpdateFlowRateLow(). */
#define _DeviceDeviceClass__UpdateFlowRateLow_

/* Default onget method for the property 'Brightness' */
XInt32 DeviceDeviceClass_OnGetBrightness( DeviceDeviceClass _this );

/* Default onget method for the property 'CurrentPage' */
XInt32 DeviceDeviceClass_OnGetCurrentPage( DeviceDeviceClass _this );

/* Default onget method for the property 'CurrentSettings' */
XInt32 DeviceDeviceClass_OnGetCurrentSettings( DeviceDeviceClass _this );

/* Default onget method for the property 'WifiSignal' */
XInt32 DeviceDeviceClass_OnGetWifiSignal( DeviceDeviceClass _this );

/* Default onget method for the property 'BatteryLevel' */
XInt32 DeviceDeviceClass_OnGetBatteryLevel( DeviceDeviceClass _this );

/* Default onget method for the property 'BatteryChargeStatus' */
XInt32 DeviceDeviceClass_OnGetBatteryChargeStatus( DeviceDeviceClass _this );

/* Default onget method for the property 'FlowRate' */
XInt32 DeviceDeviceClass_OnGetFlowRate( DeviceDeviceClass _this );

/* Default onget method for the property 'InfusionVolume' */
XInt32 DeviceDeviceClass_OnGetInfusionVolume( DeviceDeviceClass _this );

/* Default onget method for the property 'InfusionTime' */
XInt32 DeviceDeviceClass_OnGetInfusionTime( DeviceDeviceClass _this );

/* Default onget method for the property 'InfusionState' */
XInt32 DeviceDeviceClass_OnGetInfusionState( DeviceDeviceClass _this );

/* Default onget method for the property 'RemainingTime' */
XInt32 DeviceDeviceClass_OnGetRemainingTime( DeviceDeviceClass _this );

/* Default onget method for the property 'VolumeInfused' */
XInt32 DeviceDeviceClass_OnGetVolumeInfused( DeviceDeviceClass _this );

/* Default onget method for the property 'PressureOnTube' */
XInt32 DeviceDeviceClass_OnGetPressureOnTube( DeviceDeviceClass _this );

/* Default onget method for the property 'BolusVolumeSet' */
XInt32 DeviceDeviceClass_OnGetBolusVolumeSet( DeviceDeviceClass _this );

/* Default onget method for the property 'VolumeInfusedInBolus' */
XInt32 DeviceDeviceClass_OnGetVolumeInfusedInBolus( DeviceDeviceClass _this );

/* Default onget method for the property 'PressureSetting' */
XInt32 DeviceDeviceClass_OnGetPressureSetting( DeviceDeviceClass _this );

/* Default onget method for the property 'SingleBubbleThreshold' */
XInt32 DeviceDeviceClass_OnGetSingleBubbleThreshold( DeviceDeviceClass _this );

/* Default onget method for the property 'CumulativeBubbleThreshold' */
XInt32 DeviceDeviceClass_OnGetCumulativeBubbleThreshold( DeviceDeviceClass _this );

/* Default onget method for the property 'SerialNumber' */
XString DeviceDeviceClass_OnGetSerialNumber( DeviceDeviceClass _this );

/* Default onget method for the property 'Name' */
XString DeviceDeviceClass_OnGetName( DeviceDeviceClass _this );

/* Default onget method for the property 'Manufacturer' */
XString DeviceDeviceClass_OnGetManufacturer( DeviceDeviceClass _this );

/* Default onget method for the property 'MfgDateTime' */
XInt64 DeviceDeviceClass_OnGetMfgDateTime( DeviceDeviceClass _this );

/* Default onget method for the property 'ModelNumber' */
XString DeviceDeviceClass_OnGetModelNumber( DeviceDeviceClass _this );

/* Default onget method for the property 'FirmwareVersion' */
XString DeviceDeviceClass_OnGetFirmwareVersion( DeviceDeviceClass _this );

/* Default onget method for the property 'WifiStatus' */
XBool DeviceDeviceClass_OnGetWifiStatus( DeviceDeviceClass _this );

/* Default onget method for the property 'SoftwareUpdate' */
XBool DeviceDeviceClass_OnGetSoftwareUpdate( DeviceDeviceClass _this );

/* Default onget method for the property 'BootProgress' */
XInt32 DeviceDeviceClass_OnGetBootProgress( DeviceDeviceClass _this );

/* Default onget method for the property 'CurrentPopup' */
XInt32 DeviceDeviceClass_OnGetCurrentPopup( DeviceDeviceClass _this );

/* Default onget method for the property 'InStopping' */
XBool DeviceDeviceClass_OnGetInStopping( DeviceDeviceClass _this );

/* Default onget method for the property 'NotificationId' */
XInt32 DeviceDeviceClass_OnGetNotificationId( DeviceDeviceClass _this );

/* Default onget method for the property 'CurrentSubSettings' */
XInt32 DeviceDeviceClass_OnGetCurrentSubSettings( DeviceDeviceClass _this );

/* Default onget method for the property 'AppQRCode' */
XString DeviceDeviceClass_OnGetAppQRCode( DeviceDeviceClass _this );

/* Default onget method for the property 'AudioVolume' */
XInt32 DeviceDeviceClass_OnGetAudioVolume( DeviceDeviceClass _this );

/* Default onget method for the property 'NewFirmwareVersion' */
XString DeviceDeviceClass_OnGetNewFirmwareVersion( DeviceDeviceClass _this );

/* Default onget method for the property 'NewFirmwareVersionDesc' */
XString DeviceDeviceClass_OnGetNewFirmwareVersionDesc( DeviceDeviceClass _this );

/* Default onget method for the property 'BolusRate' */
XInt32 DeviceDeviceClass_OnGetBolusRate( DeviceDeviceClass _this );

/* Default onget method for the property 'KVOMode' */
XBool DeviceDeviceClass_OnGetKVOMode( DeviceDeviceClass _this );

/* Default onget method for the property 'KVORateHighFlowRate' */
XInt32 DeviceDeviceClass_OnGetKVORateHighFlowRate( DeviceDeviceClass _this );

/* Default onget method for the property 'KVORateMediumFlowRate' */
XInt32 DeviceDeviceClass_OnGetKVORateMediumFlowRate( DeviceDeviceClass _this );

/* Default onget method for the property 'KVORateLowFlowRate' */
XInt32 DeviceDeviceClass_OnGetKVORateLowFlowRate( DeviceDeviceClass _this );

/* Default onget method for the property 'FlowRateMedium' */
XInt32 DeviceDeviceClass_OnGetFlowRateMedium( DeviceDeviceClass _this );

/* Default onget method for the property 'FlowRateLow' */
XInt32 DeviceDeviceClass_OnGetFlowRateLow( DeviceDeviceClass _this );

#ifdef __cplusplus
  }
#endif

#endif /* _DeviceDeviceClass_H */

/* Embedded Wizard */
