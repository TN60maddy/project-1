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

#include "ewlocale.h"
#include "_CoreSystemEvent.h"
#include "_DeviceDataProvider.h"
#include "_DeviceDeviceClass.h"
#include "_DeviceEnumClass.h"
#include "_DeviceWifiConnectionStatusEnumClass.h"
#include "_DeviceWifiNetworksProviderClass.h"
#include "_DeviceWifiSignalEnumClass.h"
#include "_ResourcesBitmap.h"
#include "Device.h"
#include "Res.h"
#include "Strings.h"

/* Compressed strings for the language 'Default'. */
EW_CONST_STRING_PRAGMA static const unsigned int _StringsDefault0[] =
{
  0x000000E6, /* ratio 67.83 % */
  0xB8000F00, 0x00088452, 0x60010718, 0x2050C001, 0x11088341, 0xC00860D6, 0x09279161,
  0x386C2463, 0x844262F0, 0xE87E2839, 0x14800458, 0x9E300093, 0x040001D4, 0xDC002A80,
  0x20034000, 0x64004C4C, 0x5001B000, 0x9E4B6706, 0x6800EB37, 0x4D4ED3F3, 0xF684009D,
  0x4190C974, 0xDE002747, 0x20029CFC, 0x3733800D, 0xDA6CEE6D, 0x39500AD1, 0xBCFCF200,
  0x1AE6D402, 0xF6C9168A, 0x40B14B34, 0xD04B8C47, 0xB5123C76, 0x0B864E6E, 0x03C00248,
  0x9DD00C60, 0xA1D2653D, 0x00203848, 0x00000000
};

/* Constant values used in this 'C' module only. */
static const XStringRes _Const0000 = { _StringsDefault0, 0x0002 };
static const XStringRes _Const0001 = { _StringsDefault0, 0x0009 };
static const XStringRes _Const0002 = { _StringsDefault0, 0x0010 };
static const XStringRes _Const0003 = { _StringsDefault0, 0x0017 };
static const XStringRes _Const0004 = { _StringsDefault0, 0x001E };
static const XStringRes _Const0005 = { _StringsDefault0, 0x003D };
static const XStringRes _Const0006 = { _StringsDefault0, 0x0049 };
static const XStringRes _Const0007 = { _StringsDefault0, 0x0055 };
static const XStringRes _Const0008 = { _StringsDefault0, 0x005C };
static const XStringRes _Const0009 = { _StringsDefault0, 0x0061 };
static const XStringRes _Const000A = { _StringsDefault0, 0x0068 };

#ifndef EW_DONT_CHECK_INDEX
  /* This function is used to check the indices when accessing an array.
     If you don't want this verification add the define EW_DONT_CHECK_INDEX
     to your Makefile or project settings. */
  static int EwCheckIndex( int aIndex, int aRange, const char* aFile, int aLine )
  {
    if (( aIndex < 0 ) || ( aIndex >= aRange ))
    {
      EwPrint( "[FATAL ERROR in %s:%d] Array index %d out of bounds %d",
                aFile, aLine, aIndex, aRange );
      EwPanic();
      return 0;
    }
    return aIndex;
  }

  #define EwCheckIndex( aIndex, aRange ) \
    EwCheckIndex( aIndex, aRange, __FILE__, __LINE__ )
#else
  #define EwCheckIndex( aIndex, aRange ) aIndex
#endif

/* User defined inline code: 'Device::Inline' */
#include "DeviceDriver.h"


/* Initializer for the class 'Device::DeviceClass' */
void DeviceDeviceClass__Init( DeviceDeviceClass _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  TemplatesDeviceClass__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( DeviceDeviceClass );

  /* ... then construct all embedded objects */
  CoreSystemEvent__Init( &_this->PowerSwitchEvent, &_this->_.XObject, 0 );
  CoreSystemEvent__Init( &_this->StopEvent, &_this->_.XObject, 0 );
  CoreSystemEvent__Init( &_this->DoorOpenEvent, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( DeviceDeviceClass );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Brightness = 50;
  _this->CurrentPage = 1;
  _this->PressureNormalMax[ 0 ] = 60;
  _this->PressureNormalMax[ 1 ] = 120;
  _this->PressureNormalMax[ 2 ] = 180;
  _this->PressureNormalMax[ 3 ] = 270;
  _this->PressureNormalMax[ 4 ] = 360;
  _this->PressureNormalMax[ 5 ] = 450;
  _this->PressureNormalMax[ 6 ] = 540;
  _this->PressureNormalMax[ 7 ] = 630;
  _this->PressureNormalMax[ 8 ] = 720;
  _this->PressureWarningMax[ 0 ] = 75;
  _this->PressureWarningMax[ 1 ] = 150;
  _this->PressureWarningMax[ 2 ] = 225;
  _this->PressureWarningMax[ 3 ] = 338;
  _this->PressureWarningMax[ 4 ] = 450;
  _this->PressureWarningMax[ 5 ] = 563;
  _this->PressureWarningMax[ 6 ] = 675;
  _this->PressureWarningMax[ 7 ] = 788;
  _this->PressureWarningMax[ 8 ] = 900;
  _this->PressureErrorMax[ 0 ] = 120;
  _this->PressureErrorMax[ 1 ] = 180;
  _this->PressureErrorMax[ 2 ] = 270;
  _this->PressureErrorMax[ 3 ] = 360;
  _this->PressureErrorMax[ 4 ] = 563;
  _this->PressureErrorMax[ 5 ] = 675;
  _this->PressureErrorMax[ 6 ] = 788;
  _this->PressureErrorMax[ 7 ] = 900;
  _this->PressureErrorMax[ 8 ] = 1000;
}

/* Re-Initializer for the class 'Device::DeviceClass' */
void DeviceDeviceClass__ReInit( DeviceDeviceClass _this )
{
  /* At first re-initialize the super class ... */
  TemplatesDeviceClass__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreSystemEvent__ReInit( &_this->PowerSwitchEvent );
  CoreSystemEvent__ReInit( &_this->StopEvent );
  CoreSystemEvent__ReInit( &_this->DoorOpenEvent );
}

/* Finalizer method for the class 'Device::DeviceClass' */
void DeviceDeviceClass__Done( DeviceDeviceClass _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( TemplatesDeviceClass );

  /* Finalize all embedded objects */
  CoreSystemEvent__Done( &_this->PowerSwitchEvent );
  CoreSystemEvent__Done( &_this->StopEvent );
  CoreSystemEvent__Done( &_this->DoorOpenEvent );

  /* Don't forget to deinitialize the super class ... */
  TemplatesDeviceClass__Done( &_this->_.Super );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetBrightness()' */
void DeviceDeviceClass_OnSetBrightness( DeviceDeviceClass _this, XInt32 value )
{
  if ( _this->Brightness == value )
    return;

  _this->Brightness = value;
  DeviceDriver_SetBrightness( value );
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetBrightness, DeviceDeviceClass_OnSetBrightness ), 
    0 );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateBrightness( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->Brightness )
  {
    _this->Brightness = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetBrightness, DeviceDeviceClass_OnSetBrightness ), 
      0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateBrightness()' */
void DeviceDeviceClass__UpdateBrightness( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateBrightness((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetCurrentPage()' */
void DeviceDeviceClass_OnSetCurrentPage( DeviceDeviceClass _this, XInt32 value )
{
  if ( _this->CurrentPage == value )
    return;

  _this->previousPage = _this->CurrentPage;
  _this->CurrentPage = value;
  {
    /*
       TO DO:

       You can call a function of your own device API or you simply
       modify a variable existing in your middleware to reflect the
       new value:

       YourDevice_SetSomeValue( value );

       or

       YourDevice_SomeVariable = value;
    */
  }
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetCurrentPage, DeviceDeviceClass_OnSetCurrentPage ), 
    0 );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateCurrentPage( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ((XEnum)aNewValue != _this->CurrentPage )
  {
    _this->previousPage = _this->CurrentPage;
    _this->CurrentPage = (XEnum)aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetCurrentPage, DeviceDeviceClass_OnSetCurrentPage ), 
      0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateCurrentPage()' */
void DeviceDeviceClass__UpdateCurrentPage( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateCurrentPage((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetCurrentSettings()' */
void DeviceDeviceClass_OnSetCurrentSettings( DeviceDeviceClass _this, XInt32 value )
{
  if ( _this->CurrentSettings == value )
    return;

  _this->previousSettings = _this->CurrentSettings;
  _this->CurrentSettings = value;
  {
    /*
       TO DO:

       You can call a function of your own device API or you simply
       modify a variable existing in your middleware to reflect the
       new value:

       YourDevice_SetSomeValue( value );

       or

       YourDevice_SomeVariable = value;
    */
  }
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetCurrentSettings, 
    DeviceDeviceClass_OnSetCurrentSettings ), 0 );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateCurrentSettings( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ((XEnum)aNewValue != _this->CurrentSettings )
  {
    _this->previousSettings = _this->CurrentSettings;
    _this->CurrentSettings = (XEnum)aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetCurrentSettings, 
      DeviceDeviceClass_OnSetCurrentSettings ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateCurrentSettings()' */
void DeviceDeviceClass__UpdateCurrentSettings( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateCurrentSettings((DeviceDeviceClass)_this, aNewValue );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_GoToPreviousPage( DeviceDeviceClass _this )
{
  if ( _this->previousPage != 0 )
    DeviceDeviceClass_OnSetCurrentPage( _this, _this->previousPage );
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.GoToPreviousPage()' */
void DeviceDeviceClass__GoToPreviousPage( void* _this )
{
  DeviceDeviceClass_GoToPreviousPage((DeviceDeviceClass)_this );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_GoToPreviousSettings( DeviceDeviceClass _this )
{
  if ( _this->previousSettings != 0 )
    DeviceDeviceClass_OnSetCurrentSettings( _this, _this->previousSettings );
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.GoToPreviousSettings()' */
void DeviceDeviceClass__GoToPreviousSettings( void* _this )
{
  DeviceDeviceClass_GoToPreviousSettings((DeviceDeviceClass)_this );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetWifiSignal()' */
void DeviceDeviceClass_OnSetWifiSignal( DeviceDeviceClass _this, XInt32 value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateWifiSignal( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->WifiSignal )
  {
    _this->WifiSignal = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetWifiSignal, DeviceDeviceClass_OnSetWifiSignal ), 
      0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateWifiSignal()' */
void DeviceDeviceClass__UpdateWifiSignal( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateWifiSignal((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetBatteryLevel()' */
void DeviceDeviceClass_OnSetBatteryLevel( DeviceDeviceClass _this, XInt32 value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateBatteryLevel( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->BatteryLevel )
  {
    _this->BatteryLevel = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetBatteryLevel, 
      DeviceDeviceClass_OnSetBatteryLevel ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateBatteryLevel()' */
void DeviceDeviceClass__UpdateBatteryLevel( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateBatteryLevel((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetBatteryChargeStatus()' */
void DeviceDeviceClass_OnSetBatteryChargeStatus( DeviceDeviceClass _this, XInt32 
  value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateBatteryChargeStatus( DeviceDeviceClass _this, XInt32 
  aNewValue )
{
  if ( aNewValue != _this->BatteryChargeStatus )
  {
    _this->BatteryChargeStatus = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetBatteryChargeStatus, 
      DeviceDeviceClass_OnSetBatteryChargeStatus ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateBatteryChargeStatus()' */
void DeviceDeviceClass__UpdateBatteryChargeStatus( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateBatteryChargeStatus((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetFlowRate()' */
void DeviceDeviceClass_OnSetFlowRate( DeviceDeviceClass _this, XInt32 value )
{
  if ( _this->FlowRate == value )
    return;

  _this->FlowRate = value;
  DeviceDriver_SetFlowRate( value );
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetFlowRate, DeviceDeviceClass_OnSetFlowRate ), 
    0 );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateFlowRate( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->FlowRate )
  {
    _this->FlowRate = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetFlowRate, DeviceDeviceClass_OnSetFlowRate ), 
      0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateFlowRate()' */
void DeviceDeviceClass__UpdateFlowRate( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateFlowRate((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetInfusionVolume()' */
void DeviceDeviceClass_OnSetInfusionVolume( DeviceDeviceClass _this, XInt32 value )
{
  if ( _this->InfusionVolume == value )
    return;

  _this->InfusionVolume = value;
  DeviceDriver_SetInfusionVolume( value );
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetInfusionVolume, 
    DeviceDeviceClass_OnSetInfusionVolume ), 0 );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateInfusionVolume( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->InfusionVolume )
  {
    _this->InfusionVolume = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetInfusionVolume, 
      DeviceDeviceClass_OnSetInfusionVolume ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateInfusionVolume()' */
void DeviceDeviceClass__UpdateInfusionVolume( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateInfusionVolume((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetInfusionTime()' */
void DeviceDeviceClass_OnSetInfusionTime( DeviceDeviceClass _this, XInt32 value )
{
  if ( _this->InfusionTime == value )
    return;

  _this->InfusionTime = value;
  DeviceDriver_SetInfusionTime( value );
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetInfusionTime, DeviceDeviceClass_OnSetInfusionTime ), 
    0 );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateInfusionTime( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->InfusionTime )
  {
    _this->InfusionTime = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetInfusionTime, 
      DeviceDeviceClass_OnSetInfusionTime ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateInfusionTime()' */
void DeviceDeviceClass__UpdateInfusionTime( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateInfusionTime((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetInfusionState()' */
void DeviceDeviceClass_OnSetInfusionState( DeviceDeviceClass _this, XInt32 value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateInfusionState( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->InfusionState )
  {
    _this->InfusionState = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetInfusionState, 
      DeviceDeviceClass_OnSetInfusionState ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateInfusionState()' */
void DeviceDeviceClass__UpdateInfusionState( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateInfusionState((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetRemainingTime()' */
void DeviceDeviceClass_OnSetRemainingTime( DeviceDeviceClass _this, XInt32 value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateRemainingTime( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->RemainingTime )
  {
    _this->RemainingTime = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetRemainingTime, 
      DeviceDeviceClass_OnSetRemainingTime ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateRemainingTime()' */
void DeviceDeviceClass__UpdateRemainingTime( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateRemainingTime((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetVolumeInfused()' */
void DeviceDeviceClass_OnSetVolumeInfused( DeviceDeviceClass _this, XInt32 value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateVolumeInfused( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->VolumeInfused )
  {
    _this->VolumeInfused = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetVolumeInfused, 
      DeviceDeviceClass_OnSetVolumeInfused ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateVolumeInfused()' */
void DeviceDeviceClass__UpdateVolumeInfused( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateVolumeInfused((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetPressureOnTube()' */
void DeviceDeviceClass_OnSetPressureOnTube( DeviceDeviceClass _this, XInt32 value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdatePressureOnTube( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->PressureOnTube )
  {
    _this->PressureOnTube = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetPressureOnTube, 
      DeviceDeviceClass_OnSetPressureOnTube ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdatePressureOnTube()' */
void DeviceDeviceClass__UpdatePressureOnTube( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdatePressureOnTube((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetBolusVolumeSet()' */
void DeviceDeviceClass_OnSetBolusVolumeSet( DeviceDeviceClass _this, XInt32 value )
{
  if ( _this->BolusVolumeSet == value )
    return;

  _this->BolusVolumeSet = value;
  DeviceDriver_SetBolusVolumeSet( value );
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetBolusVolumeSet, 
    DeviceDeviceClass_OnSetBolusVolumeSet ), 0 );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateBolusVolumeSet( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->BolusVolumeSet )
  {
    _this->BolusVolumeSet = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetBolusVolumeSet, 
      DeviceDeviceClass_OnSetBolusVolumeSet ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateBolusVolumeSet()' */
void DeviceDeviceClass__UpdateBolusVolumeSet( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateBolusVolumeSet((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetVolumeInfusedInBolus()' */
void DeviceDeviceClass_OnSetVolumeInfusedInBolus( DeviceDeviceClass _this, XInt32 
  value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateVolumeInfusedInBolus( DeviceDeviceClass _this, XInt32 
  aNewValue )
{
  if ( aNewValue != _this->VolumeInfusedInBolus )
  {
    _this->VolumeInfusedInBolus = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetVolumeInfusedInBolus, 
      DeviceDeviceClass_OnSetVolumeInfusedInBolus ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateVolumeInfusedInBolus()' */
void DeviceDeviceClass__UpdateVolumeInfusedInBolus( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateVolumeInfusedInBolus((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetPressureSetting()' */
void DeviceDeviceClass_OnSetPressureSetting( DeviceDeviceClass _this, XInt32 value )
{
  if ( _this->PressureSetting == value )
    return;

  _this->PressureSetting = value;
  DeviceDriver_SetPressureSetting( value );
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetPressureSetting, 
    DeviceDeviceClass_OnSetPressureSetting ), 0 );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdatePressureSetting( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->PressureSetting )
  {
    _this->PressureSetting = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetPressureSetting, 
      DeviceDeviceClass_OnSetPressureSetting ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdatePressureSetting()' */
void DeviceDeviceClass__UpdatePressureSetting( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdatePressureSetting((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetSingleBubbleThreshold()' */
void DeviceDeviceClass_OnSetSingleBubbleThreshold( DeviceDeviceClass _this, XInt32 
  value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateSingleBubbleThreshold( DeviceDeviceClass _this, XInt32 
  aNewValue )
{
  if ( aNewValue != _this->SingleBubbleThreshold )
  {
    _this->SingleBubbleThreshold = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetSingleBubbleThreshold, 
      DeviceDeviceClass_OnSetSingleBubbleThreshold ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateSingleBubbleThreshold()' */
void DeviceDeviceClass__UpdateSingleBubbleThreshold( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateSingleBubbleThreshold((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetCumulativeBubbleThreshold()' */
void DeviceDeviceClass_OnSetCumulativeBubbleThreshold( DeviceDeviceClass _this, 
  XInt32 value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateCumulativeBubbleThreshold( DeviceDeviceClass _this, 
  XInt32 aNewValue )
{
  if ( aNewValue != _this->CumulativeBubbleThreshold )
  {
    _this->CumulativeBubbleThreshold = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetCumulativeBubbleThreshold, 
      DeviceDeviceClass_OnSetCumulativeBubbleThreshold ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateCumulativeBubbleThreshold()' */
void DeviceDeviceClass__UpdateCumulativeBubbleThreshold( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateCumulativeBubbleThreshold((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetSerialNumber()' */
void DeviceDeviceClass_OnSetSerialNumber( DeviceDeviceClass _this, XString value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateSerialNumber( DeviceDeviceClass _this, XString aNewValue )
{
  if ( EwCompString( aNewValue, _this->SerialNumber ) != 0 )
  {
    _this->SerialNumber = EwShareString( aNewValue );
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetSerialNumber, 
      DeviceDeviceClass_OnSetSerialNumber ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateSerialNumber()' */
void DeviceDeviceClass__UpdateSerialNumber( void* _this, XString aNewValue )
{
  DeviceDeviceClass_UpdateSerialNumber((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetName()' */
void DeviceDeviceClass_OnSetName( DeviceDeviceClass _this, XString value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateName( DeviceDeviceClass _this, XString aNewValue )
{
  if ( EwCompString( aNewValue, _this->Name ) != 0 )
  {
    _this->Name = EwShareString( aNewValue );
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetName, DeviceDeviceClass_OnSetName ), 
      0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateName()' */
void DeviceDeviceClass__UpdateName( void* _this, XString aNewValue )
{
  DeviceDeviceClass_UpdateName((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetManufacturer()' */
void DeviceDeviceClass_OnSetManufacturer( DeviceDeviceClass _this, XString value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateManufacturer( DeviceDeviceClass _this, XString aNewValue )
{
  if ( EwCompString( aNewValue, _this->Manufacturer ) != 0 )
  {
    _this->Manufacturer = EwShareString( aNewValue );
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetManufacturer, 
      DeviceDeviceClass_OnSetManufacturer ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateManufacturer()' */
void DeviceDeviceClass__UpdateManufacturer( void* _this, XString aNewValue )
{
  DeviceDeviceClass_UpdateManufacturer((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetMfgDateTime()' */
void DeviceDeviceClass_OnSetMfgDateTime( DeviceDeviceClass _this, XInt64 value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateMfgDateTime( DeviceDeviceClass _this, XInt64 aNewValue )
{
  if ( aNewValue != _this->MfgDateTime )
  {
    _this->MfgDateTime = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetMfgDateTime, DeviceDeviceClass_OnSetMfgDateTime ), 
      0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateMfgDateTime()' */
void DeviceDeviceClass__UpdateMfgDateTime( void* _this, XInt64 aNewValue )
{
  DeviceDeviceClass_UpdateMfgDateTime((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetModelNumber()' */
void DeviceDeviceClass_OnSetModelNumber( DeviceDeviceClass _this, XString value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateModelNumber( DeviceDeviceClass _this, XString aNewValue )
{
  if ( EwCompString( aNewValue, _this->ModelNumber ) != 0 )
  {
    _this->ModelNumber = EwShareString( aNewValue );
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetModelNumber, DeviceDeviceClass_OnSetModelNumber ), 
      0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateModelNumber()' */
void DeviceDeviceClass__UpdateModelNumber( void* _this, XString aNewValue )
{
  DeviceDeviceClass_UpdateModelNumber((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetFirmwareVersion()' */
void DeviceDeviceClass_OnSetFirmwareVersion( DeviceDeviceClass _this, XString value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateFirmwareVersion( DeviceDeviceClass _this, XString aNewValue )
{
  if ( EwCompString( aNewValue, _this->FirmwareVersion ) != 0 )
  {
    _this->FirmwareVersion = EwShareString( aNewValue );
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetFirmwareVersion, 
      DeviceDeviceClass_OnSetFirmwareVersion ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateFirmwareVersion()' */
void DeviceDeviceClass__UpdateFirmwareVersion( void* _this, XString aNewValue )
{
  DeviceDeviceClass_UpdateFirmwareVersion((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetWifiStatus()' */
void DeviceDeviceClass_OnSetWifiStatus( DeviceDeviceClass _this, XBool value )
{
  if ( _this->WifiStatus == value )
    return;

  _this->WifiStatus = value;
  DeviceDriver_SetWifiStatus( value );
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetWifiStatus, DeviceDeviceClass_OnSetWifiStatus ), 
    0 );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateWifiStatus( DeviceDeviceClass _this, XBool aNewValue )
{
  if ( aNewValue != _this->WifiStatus )
  {
    _this->WifiStatus = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetWifiStatus, DeviceDeviceClass_OnSetWifiStatus ), 
      0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateWifiStatus()' */
void DeviceDeviceClass__UpdateWifiStatus( void* _this, XBool aNewValue )
{
  DeviceDeviceClass_UpdateWifiStatus((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetSoftwareUpdate()' */
void DeviceDeviceClass_OnSetSoftwareUpdate( DeviceDeviceClass _this, XBool value )
{
  _this->SoftwareUpdate = value;
  DeviceDriver_SetSoftwareUpdate( value );
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetSoftwareUpdate, 
    DeviceDeviceClass_OnSetSoftwareUpdate ), 0 );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetBootProgress()' */
void DeviceDeviceClass_OnSetBootProgress( DeviceDeviceClass _this, XInt32 value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateBootProgress( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->BootProgress )
  {
    _this->BootProgress = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetBootProgress, 
      DeviceDeviceClass_OnSetBootProgress ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateBootProgress()' */
void DeviceDeviceClass__UpdateBootProgress( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateBootProgress((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.StartInfusion()' */
void DeviceDeviceClass_StartInfusion( DeviceDeviceClass _this )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  DeviceDriver_StartInfusion();
}

/* 'C' function for method : 'Device::DeviceClass.RestartInfusion()' */
void DeviceDeviceClass_RestartInfusion( DeviceDeviceClass _this )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  DeviceDriver_RestartInfusion();
}

/* 'C' function for method : 'Device::DeviceClass.ClearSettings()' */
void DeviceDeviceClass_ClearSettings( DeviceDeviceClass _this )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  DeviceDriver_ClearSettings();
}

/* 'C' function for method : 'Device::DeviceClass.OnSetCurrentPopup()' */
void DeviceDeviceClass_OnSetCurrentPopup( DeviceDeviceClass _this, XInt32 value )
{
  if ( _this->CurrentPopup == value )
    return;

  _this->CurrentPopup = value;
  {
    /*
       TO DO:

       You can call a function of your own device API or you simply
       modify a variable existing in your middleware to reflect the
       new value:

       YourDevice_SetSomeValue( value );

       or

       YourDevice_SomeVariable = value;
    */
  }
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetCurrentPopup, DeviceDeviceClass_OnSetCurrentPopup ), 
    0 );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateCurrentPopup( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ((XEnum)aNewValue != _this->CurrentPopup )
  {
    _this->previousPage = _this->CurrentPopup;
    _this->CurrentPopup = (XEnum)aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetCurrentPopup, 
      DeviceDeviceClass_OnSetCurrentPopup ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateCurrentPopup()' */
void DeviceDeviceClass__UpdateCurrentPopup( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateCurrentPopup((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.StopInfusion()' */
void DeviceDeviceClass_StopInfusion( DeviceDeviceClass _this )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  DeviceDriver_StopInfusion();
}

/* 'C' function for method : 'Device::DeviceClass.GetPresurreNormalMax()' */
XInt32 DeviceDeviceClass_GetPresurreNormalMax( DeviceDeviceClass _this, XInt32 aStage )
{
  XInt32 index = aStage - 1;

  if (( index >= 0 ) && ( index < 9 ))
    return _this->PressureNormalMax[ EwCheckIndex( index, 9 )];

  return 0;
}

/* 'C' function for method : 'Device::DeviceClass.GetPresurreWarningMax()' */
XInt32 DeviceDeviceClass_GetPresurreWarningMax( DeviceDeviceClass _this, XInt32 
  aStage )
{
  XInt32 index = aStage - 1;

  if (( index >= 0 ) && ( index < 9 ))
    return _this->PressureWarningMax[ EwCheckIndex( index, 9 )];

  return 0;
}

/* 'C' function for method : 'Device::DeviceClass.GetPresurreErrorMax()' */
XInt32 DeviceDeviceClass_GetPresurreErrorMax( DeviceDeviceClass _this, XInt32 aStage )
{
  XInt32 index = aStage - 1;

  if (( index >= 0 ) && ( index < 9 ))
    return _this->PressureErrorMax[ EwCheckIndex( index, 9 )];

  return 0;
}

/* 'C' function for method : 'Device::DeviceClass.OnSetInStopping()' */
void DeviceDeviceClass_OnSetInStopping( DeviceDeviceClass _this, XBool value )
{
  if ( _this->InStopping == value )
    return;

  _this->InStopping = value;
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetInStopping, DeviceDeviceClass_OnSetInStopping ), 
    0 );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetNotificationId()' */
void DeviceDeviceClass_OnSetNotificationId( DeviceDeviceClass _this, XInt32 value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateNotificationId( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->NotificationId )
  {
    _this->NotificationId = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetNotificationId, 
      DeviceDeviceClass_OnSetNotificationId ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateNotificationId()' */
void DeviceDeviceClass__UpdateNotificationId( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateNotificationId((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.GetNotificationType()' */
XEnum DeviceDeviceClass_GetNotificationType( DeviceDeviceClass _this, XInt32 aId )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  switch ( aId )
  {
    case 6 :
    case 5 :
    case 3 :
    case 4 :
      return DeviceNotificationTypeError;

    case 1 :
    case 2 :
      return DeviceNotificationTypeWarning;

    default : 
      return DeviceNotificationTypeUndefined;
  }
}

/* 'C' function for method : 'Device::DeviceClass.GetNotificationCaption()' */
XString DeviceDeviceClass_GetNotificationCaption( DeviceDeviceClass _this, XInt32 
  aId )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  switch ( aId )
  {
    case 6 :
    case 5 :
      return EwLoadString( &StringsDeviceAlarm );

    case 3 :
      return EwLoadString( &StringsAirBubbleAlarm );

    case 4 :
      return EwLoadString( &StringsUpstreamOcclusionAlarm );

    case 1 :
      return EwLoadString( &StringsOpenRollerClamp );

    case 2 :
      return EwLoadString( &StringsCloseRollerClamp );

    default : 
      return 0;
  }
}

/* 'C' function for method : 'Device::DeviceClass.GetNotificationMessage()' */
XString DeviceDeviceClass_GetNotificationMessage( DeviceDeviceClass _this, XInt32 
  aId )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  switch ( aId )
  {
    case 6 :
      return EwLoadString( &StringsDeviceAlarmMsg );

    case 5 :
      return EwLoadString( &StringsDeviceAlarmOnBootMsg );

    case 3 :
      return EwLoadString( &StringsAirBubbleAlarmMsg );

    case 4 :
      return EwLoadString( &StringsUpstreamOcclusionAlarmMsg );

    case 1 :
      return EwLoadString( &StringsOpenRollerClampMsg );

    case 2 :
      return EwLoadString( &StringsCloseRollerClampMsg );

    default : 
      return 0;
  }
}

/* 'C' function for method : 'Device::DeviceClass.GetErrorCode()' */
XString DeviceDeviceClass_GetErrorCode( DeviceDeviceClass _this, XInt32 aErrorId )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  switch ( aErrorId )
  {
    case 6 :
      return EwLoadString( &_Const0000 );

    case 5 :
      return EwLoadString( &_Const0001 );

    case 3 :
      return EwLoadString( &_Const0002 );

    case 4 :
      return EwLoadString( &_Const0003 );

    default : 
      return 0;
  }
}

/* 'C' function for method : 'Device::DeviceClass.IsErrorWithSound()' */
XBool DeviceDeviceClass_IsErrorWithSound( DeviceDeviceClass _this, XInt32 aErrorId )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  if ( aErrorId == 5 )
    return 0;

  return 1;
}

/* 'C' function for method : 'Device::DeviceClass.GetNotificationImage()' */
ResourcesBitmap DeviceDeviceClass_GetNotificationImage( DeviceDeviceClass _this, 
  XInt32 aId )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  switch ( aId )
  {
    case 1 :
    case 2 :
      return EwLoadResource( &ResrollerClamp, ResourcesBitmap );

    default : 
      return 0;
  }
}

/* 'C' function for method : 'Device::DeviceClass.MuteAlarm()' */
void DeviceDeviceClass_MuteAlarm( DeviceDeviceClass _this, XInt32 aId )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  DeviceDriver_MuteAlarm( aId );
}

/* 'C' function for method : 'Device::DeviceClass.ConfirmNotification()' */
void DeviceDeviceClass_ConfirmNotification( DeviceDeviceClass _this, XInt32 aId )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  DeviceDriver_ConfirmNotification( aId );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetCurrentSubSettings()' */
void DeviceDeviceClass_OnSetCurrentSubSettings( DeviceDeviceClass _this, XInt32 
  value )
{
  if ( _this->CurrentSubSettings == value )
    return;

  _this->CurrentSubSettings = value;
  {
    /*
       TO DO:

       You can call a function of your own device API or you simply
       modify a variable existing in your middleware to reflect the
       new value:

       YourDevice_SetSomeValue( value );

       or

       YourDevice_SomeVariable = value;
    */
  }
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetCurrentSubSettings, 
    DeviceDeviceClass_OnSetCurrentSubSettings ), 0 );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateCurrentSubSettings( DeviceDeviceClass _this, XInt32 
  aNewValue )
{
  if ((XEnum)aNewValue != _this->CurrentSubSettings )
  {
    _this->CurrentSubSettings = (XEnum)aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetCurrentSubSettings, 
      DeviceDeviceClass_OnSetCurrentSubSettings ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateCurrentSubSettings()' */
void DeviceDeviceClass__UpdateCurrentSubSettings( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateCurrentSubSettings((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetAppQRCode()' */
void DeviceDeviceClass_OnSetAppQRCode( DeviceDeviceClass _this, XString value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateAppQRCode( DeviceDeviceClass _this, XString aNewValue )
{
  if ( EwCompString( aNewValue, _this->AppQRCode ) != 0 )
  {
    _this->AppQRCode = EwShareString( aNewValue );
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetAppQRCode, DeviceDeviceClass_OnSetAppQRCode ), 
      0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateAppQRCode()' */
void DeviceDeviceClass__UpdateAppQRCode( void* _this, XString aNewValue )
{
  DeviceDeviceClass_UpdateAppQRCode((DeviceDeviceClass)_this, aNewValue );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateWifiNetworkList( DeviceDeviceClass _this )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  DeviceDataProvider_NotifyChange((DeviceDataProvider)EwGetAutoObject( &DeviceWifiNetworksProvider, 
  DeviceWifiNetworksProviderClass ));
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateWifiNetworkList()' */
void DeviceDeviceClass__UpdateWifiNetworkList( void* _this )
{
  DeviceDeviceClass_UpdateWifiNetworkList((DeviceDeviceClass)_this );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetAudioVolume()' */
void DeviceDeviceClass_OnSetAudioVolume( DeviceDeviceClass _this, XInt32 value )
{
  if ( _this->AudioVolume == value )
    return;

  _this->AudioVolume = value;
  DeviceDriver_SetAudioVolume( value );
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetAudioVolume, DeviceDeviceClass_OnSetAudioVolume ), 
    0 );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateAudioVolume( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->AudioVolume )
  {
    _this->AudioVolume = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetAudioVolume, DeviceDeviceClass_OnSetAudioVolume ), 
      0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateAudioVolume()' */
void DeviceDeviceClass__UpdateAudioVolume( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateAudioVolume((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetNewFirmwareVersion()' */
void DeviceDeviceClass_OnSetNewFirmwareVersion( DeviceDeviceClass _this, XString 
  value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateNewFirmwareVersion( DeviceDeviceClass _this, XString 
  aNewValue )
{
  if ( EwCompString( aNewValue, _this->NewFirmwareVersion ) != 0 )
  {
    _this->NewFirmwareVersion = EwShareString( aNewValue );
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetNewFirmwareVersion, 
      DeviceDeviceClass_OnSetNewFirmwareVersion ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateNewFirmwareVersion()' */
void DeviceDeviceClass__UpdateNewFirmwareVersion( void* _this, XString aNewValue )
{
  DeviceDeviceClass_UpdateNewFirmwareVersion((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetNewFirmwareVersionDesc()' */
void DeviceDeviceClass_OnSetNewFirmwareVersionDesc( DeviceDeviceClass _this, XString 
  value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateNewFirmwareVersionDesc( DeviceDeviceClass _this, XString 
  aNewValue )
{
  if ( EwCompString( aNewValue, _this->NewFirmwareVersionDesc ) != 0 )
  {
    _this->NewFirmwareVersionDesc = EwShareString( aNewValue );
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetNewFirmwareVersionDesc, 
      DeviceDeviceClass_OnSetNewFirmwareVersionDesc ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateNewFirmwareVersionDesc()' */
void DeviceDeviceClass__UpdateNewFirmwareVersionDesc( void* _this, XString aNewValue )
{
  DeviceDeviceClass_UpdateNewFirmwareVersionDesc((DeviceDeviceClass)_this, aNewValue );
}

/* This method is intended to be called by the device to notify the GUI application 
   about a particular system event. */
void DeviceDeviceClass_TriggerPowerSwitchEvent( DeviceDeviceClass _this )
{
  CoreSystemEvent_Trigger( &_this->PowerSwitchEvent, 0, 0 );
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.TriggerPowerSwitchEvent()' */
void DeviceDeviceClass__TriggerPowerSwitchEvent( void* _this )
{
  DeviceDeviceClass_TriggerPowerSwitchEvent((DeviceDeviceClass)_this );
}

/* This method is intended to be called by the device to notify the GUI application 
   about a particular system event. */
void DeviceDeviceClass_TriggerStopEvent( DeviceDeviceClass _this )
{
  CoreSystemEvent_Trigger( &_this->StopEvent, 0, 0 );
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.TriggerStopEvent()' */
void DeviceDeviceClass__TriggerStopEvent( void* _this )
{
  DeviceDeviceClass_TriggerStopEvent((DeviceDeviceClass)_this );
}

/* This method is intended to be called by the device to notify the GUI application 
   about a particular system event. */
void DeviceDeviceClass_TriggerDoorOpenEvent( DeviceDeviceClass _this )
{
  CoreSystemEvent_Trigger( &_this->DoorOpenEvent, 0, 0 );
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.TriggerDoorOpenEvent()' */
void DeviceDeviceClass__TriggerDoorOpenEvent( void* _this )
{
  DeviceDeviceClass_TriggerDoorOpenEvent((DeviceDeviceClass)_this );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetBolusRate()' */
void DeviceDeviceClass_OnSetBolusRate( DeviceDeviceClass _this, XInt32 value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateBolusRate( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->BolusRate )
  {
    _this->BolusRate = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetBolusRate, DeviceDeviceClass_OnSetBolusRate ), 
      0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateBolusRate()' */
void DeviceDeviceClass__UpdateBolusRate( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateBolusRate((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetKVOMode()' */
void DeviceDeviceClass_OnSetKVOMode( DeviceDeviceClass _this, XBool value )
{
  if ( _this->KVOMode == value )
    return;

  _this->KVOMode = value;
  DeviceDriver_SetKVOMode( value );
  EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetKVOMode, DeviceDeviceClass_OnSetKVOMode ), 
    0 );
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateKVOMode( DeviceDeviceClass _this, XBool aNewValue )
{
  if ( aNewValue != _this->KVOMode )
  {
    _this->KVOMode = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetKVOMode, DeviceDeviceClass_OnSetKVOMode ), 
      0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateKVOMode()' */
void DeviceDeviceClass__UpdateKVOMode( void* _this, XBool aNewValue )
{
  DeviceDeviceClass_UpdateKVOMode((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetKVORateHighFlowRate()' */
void DeviceDeviceClass_OnSetKVORateHighFlowRate( DeviceDeviceClass _this, XInt32 
  value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateKVORateHighFlowRate( DeviceDeviceClass _this, XInt32 
  aNewValue )
{
  if ( aNewValue != _this->KVORateHighFlowRate )
  {
    _this->KVORateHighFlowRate = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetKVORateHighFlowRate, 
      DeviceDeviceClass_OnSetKVORateHighFlowRate ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateKVORateHighFlowRate()' */
void DeviceDeviceClass__UpdateKVORateHighFlowRate( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateKVORateHighFlowRate((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetKVORateMediumFlowRate()' */
void DeviceDeviceClass_OnSetKVORateMediumFlowRate( DeviceDeviceClass _this, XInt32 
  value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateKVORateMediumFlowRate( DeviceDeviceClass _this, XInt32 
  aNewValue )
{
  if ( aNewValue != _this->KVORateMediumFlowRate )
  {
    _this->KVORateMediumFlowRate = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetKVORateMediumFlowRate, 
      DeviceDeviceClass_OnSetKVORateMediumFlowRate ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateKVORateMediumFlowRate()' */
void DeviceDeviceClass__UpdateKVORateMediumFlowRate( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateKVORateMediumFlowRate((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetKVORateLowFlowRate()' */
void DeviceDeviceClass_OnSetKVORateLowFlowRate( DeviceDeviceClass _this, XInt32 
  value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateKVORateLowFlowRate( DeviceDeviceClass _this, XInt32 
  aNewValue )
{
  if ( aNewValue != _this->KVORateLowFlowRate )
  {
    _this->KVORateLowFlowRate = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetKVORateLowFlowRate, 
      DeviceDeviceClass_OnSetKVORateLowFlowRate ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateKVORateLowFlowRate()' */
void DeviceDeviceClass__UpdateKVORateLowFlowRate( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateKVORateLowFlowRate((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetFlowRateMedium()' */
void DeviceDeviceClass_OnSetFlowRateMedium( DeviceDeviceClass _this, XInt32 value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateFlowRateMedium( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->FlowRateMedium )
  {
    _this->FlowRateMedium = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetFlowRateMedium, 
      DeviceDeviceClass_OnSetFlowRateMedium ), 0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateFlowRateMedium()' */
void DeviceDeviceClass__UpdateFlowRateMedium( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateFlowRateMedium((DeviceDeviceClass)_this, aNewValue );
}

/* 'C' function for method : 'Device::DeviceClass.OnSetFlowRateLow()' */
void DeviceDeviceClass_OnSetFlowRateLow( DeviceDeviceClass _this, XInt32 value )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( value );

  EwTrace( "%s", EwLoadString( &ResErrorReadOnly ));
}

/* This method is intended to be called by the device to notify the GUI application 
   about an alternation of its setting or state value. */
void DeviceDeviceClass_UpdateFlowRateLow( DeviceDeviceClass _this, XInt32 aNewValue )
{
  if ( aNewValue != _this->FlowRateLow )
  {
    _this->FlowRateLow = aNewValue;
    EwNotifyRefObservers( EwNewRef( _this, DeviceDeviceClass_OnGetFlowRateLow, DeviceDeviceClass_OnSetFlowRateLow ), 
      0 );
  }
}

/* Wrapper function for the non virtual method : 'Device::DeviceClass.UpdateFlowRateLow()' */
void DeviceDeviceClass__UpdateFlowRateLow( void* _this, XInt32 aNewValue )
{
  DeviceDeviceClass_UpdateFlowRateLow((DeviceDeviceClass)_this, aNewValue );
}

/* Default onget method for the property 'Brightness' */
XInt32 DeviceDeviceClass_OnGetBrightness( DeviceDeviceClass _this )
{
  return _this->Brightness;
}

/* Default onget method for the property 'CurrentPage' */
XInt32 DeviceDeviceClass_OnGetCurrentPage( DeviceDeviceClass _this )
{
  return _this->CurrentPage;
}

/* Default onget method for the property 'CurrentSettings' */
XInt32 DeviceDeviceClass_OnGetCurrentSettings( DeviceDeviceClass _this )
{
  return _this->CurrentSettings;
}

/* Default onget method for the property 'WifiSignal' */
XInt32 DeviceDeviceClass_OnGetWifiSignal( DeviceDeviceClass _this )
{
  return _this->WifiSignal;
}

/* Default onget method for the property 'BatteryLevel' */
XInt32 DeviceDeviceClass_OnGetBatteryLevel( DeviceDeviceClass _this )
{
  return _this->BatteryLevel;
}

/* Default onget method for the property 'BatteryChargeStatus' */
XInt32 DeviceDeviceClass_OnGetBatteryChargeStatus( DeviceDeviceClass _this )
{
  return _this->BatteryChargeStatus;
}

/* Default onget method for the property 'FlowRate' */
XInt32 DeviceDeviceClass_OnGetFlowRate( DeviceDeviceClass _this )
{
  return _this->FlowRate;
}

/* Default onget method for the property 'InfusionVolume' */
XInt32 DeviceDeviceClass_OnGetInfusionVolume( DeviceDeviceClass _this )
{
  return _this->InfusionVolume;
}

/* Default onget method for the property 'InfusionTime' */
XInt32 DeviceDeviceClass_OnGetInfusionTime( DeviceDeviceClass _this )
{
  return _this->InfusionTime;
}

/* Default onget method for the property 'InfusionState' */
XInt32 DeviceDeviceClass_OnGetInfusionState( DeviceDeviceClass _this )
{
  return _this->InfusionState;
}

/* Default onget method for the property 'RemainingTime' */
XInt32 DeviceDeviceClass_OnGetRemainingTime( DeviceDeviceClass _this )
{
  return _this->RemainingTime;
}

/* Default onget method for the property 'VolumeInfused' */
XInt32 DeviceDeviceClass_OnGetVolumeInfused( DeviceDeviceClass _this )
{
  return _this->VolumeInfused;
}

/* Default onget method for the property 'PressureOnTube' */
XInt32 DeviceDeviceClass_OnGetPressureOnTube( DeviceDeviceClass _this )
{
  return _this->PressureOnTube;
}

/* Default onget method for the property 'BolusVolumeSet' */
XInt32 DeviceDeviceClass_OnGetBolusVolumeSet( DeviceDeviceClass _this )
{
  return _this->BolusVolumeSet;
}

/* Default onget method for the property 'VolumeInfusedInBolus' */
XInt32 DeviceDeviceClass_OnGetVolumeInfusedInBolus( DeviceDeviceClass _this )
{
  return _this->VolumeInfusedInBolus;
}

/* Default onget method for the property 'PressureSetting' */
XInt32 DeviceDeviceClass_OnGetPressureSetting( DeviceDeviceClass _this )
{
  return _this->PressureSetting;
}

/* Default onget method for the property 'SingleBubbleThreshold' */
XInt32 DeviceDeviceClass_OnGetSingleBubbleThreshold( DeviceDeviceClass _this )
{
  return _this->SingleBubbleThreshold;
}

/* Default onget method for the property 'CumulativeBubbleThreshold' */
XInt32 DeviceDeviceClass_OnGetCumulativeBubbleThreshold( DeviceDeviceClass _this )
{
  return _this->CumulativeBubbleThreshold;
}

/* Default onget method for the property 'SerialNumber' */
XString DeviceDeviceClass_OnGetSerialNumber( DeviceDeviceClass _this )
{
  return _this->SerialNumber;
}

/* Default onget method for the property 'Name' */
XString DeviceDeviceClass_OnGetName( DeviceDeviceClass _this )
{
  return _this->Name;
}

/* Default onget method for the property 'Manufacturer' */
XString DeviceDeviceClass_OnGetManufacturer( DeviceDeviceClass _this )
{
  return _this->Manufacturer;
}

/* Default onget method for the property 'MfgDateTime' */
XInt64 DeviceDeviceClass_OnGetMfgDateTime( DeviceDeviceClass _this )
{
  return _this->MfgDateTime;
}

/* Default onget method for the property 'ModelNumber' */
XString DeviceDeviceClass_OnGetModelNumber( DeviceDeviceClass _this )
{
  return _this->ModelNumber;
}

/* Default onget method for the property 'FirmwareVersion' */
XString DeviceDeviceClass_OnGetFirmwareVersion( DeviceDeviceClass _this )
{
  return _this->FirmwareVersion;
}

/* Default onget method for the property 'WifiStatus' */
XBool DeviceDeviceClass_OnGetWifiStatus( DeviceDeviceClass _this )
{
  return _this->WifiStatus;
}

/* Default onget method for the property 'SoftwareUpdate' */
XBool DeviceDeviceClass_OnGetSoftwareUpdate( DeviceDeviceClass _this )
{
  return _this->SoftwareUpdate;
}

/* Default onget method for the property 'BootProgress' */
XInt32 DeviceDeviceClass_OnGetBootProgress( DeviceDeviceClass _this )
{
  return _this->BootProgress;
}

/* Default onget method for the property 'CurrentPopup' */
XInt32 DeviceDeviceClass_OnGetCurrentPopup( DeviceDeviceClass _this )
{
  return _this->CurrentPopup;
}

/* Default onget method for the property 'InStopping' */
XBool DeviceDeviceClass_OnGetInStopping( DeviceDeviceClass _this )
{
  return _this->InStopping;
}

/* Default onget method for the property 'NotificationId' */
XInt32 DeviceDeviceClass_OnGetNotificationId( DeviceDeviceClass _this )
{
  return _this->NotificationId;
}

/* Default onget method for the property 'CurrentSubSettings' */
XInt32 DeviceDeviceClass_OnGetCurrentSubSettings( DeviceDeviceClass _this )
{
  return _this->CurrentSubSettings;
}

/* Default onget method for the property 'AppQRCode' */
XString DeviceDeviceClass_OnGetAppQRCode( DeviceDeviceClass _this )
{
  return _this->AppQRCode;
}

/* Default onget method for the property 'AudioVolume' */
XInt32 DeviceDeviceClass_OnGetAudioVolume( DeviceDeviceClass _this )
{
  return _this->AudioVolume;
}

/* Default onget method for the property 'NewFirmwareVersion' */
XString DeviceDeviceClass_OnGetNewFirmwareVersion( DeviceDeviceClass _this )
{
  return _this->NewFirmwareVersion;
}

/* Default onget method for the property 'NewFirmwareVersionDesc' */
XString DeviceDeviceClass_OnGetNewFirmwareVersionDesc( DeviceDeviceClass _this )
{
  return _this->NewFirmwareVersionDesc;
}

/* Default onget method for the property 'BolusRate' */
XInt32 DeviceDeviceClass_OnGetBolusRate( DeviceDeviceClass _this )
{
  return _this->BolusRate;
}

/* Default onget method for the property 'KVOMode' */
XBool DeviceDeviceClass_OnGetKVOMode( DeviceDeviceClass _this )
{
  return _this->KVOMode;
}

/* Default onget method for the property 'KVORateHighFlowRate' */
XInt32 DeviceDeviceClass_OnGetKVORateHighFlowRate( DeviceDeviceClass _this )
{
  return _this->KVORateHighFlowRate;
}

/* Default onget method for the property 'KVORateMediumFlowRate' */
XInt32 DeviceDeviceClass_OnGetKVORateMediumFlowRate( DeviceDeviceClass _this )
{
  return _this->KVORateMediumFlowRate;
}

/* Default onget method for the property 'KVORateLowFlowRate' */
XInt32 DeviceDeviceClass_OnGetKVORateLowFlowRate( DeviceDeviceClass _this )
{
  return _this->KVORateLowFlowRate;
}

/* Default onget method for the property 'FlowRateMedium' */
XInt32 DeviceDeviceClass_OnGetFlowRateMedium( DeviceDeviceClass _this )
{
  return _this->FlowRateMedium;
}

/* Default onget method for the property 'FlowRateLow' */
XInt32 DeviceDeviceClass_OnGetFlowRateLow( DeviceDeviceClass _this )
{
  return _this->FlowRateLow;
}

/* Variants derived from the class : 'Device::DeviceClass' */
EW_DEFINE_CLASS_VARIANTS( DeviceDeviceClass )
EW_END_OF_CLASS_VARIANTS( DeviceDeviceClass )

/* Virtual Method Table (VMT) for the class : 'Device::DeviceClass' */
EW_DEFINE_CLASS( DeviceDeviceClass, TemplatesDeviceClass, PowerSwitchEvent, SerialNumber, 
                 SerialNumber, SerialNumber, SerialNumber, Brightness, "Device::DeviceClass" )
EW_END_OF_CLASS( DeviceDeviceClass )

/* User defined auto object: 'Device::Device' */
EW_DEFINE_AUTOOBJECT( DeviceDevice, DeviceDeviceClass )

/* Initializer for the auto object 'Device::Device' */
void DeviceDevice__Init( DeviceDeviceClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Re-Initializer for the auto object 'Device::Device' */
void DeviceDevice__ReInit( DeviceDeviceClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Device::Device' */
EW_DEFINE_AUTOOBJECT_VARIANTS( DeviceDevice )
EW_END_OF_AUTOOBJECT_VARIANTS( DeviceDevice )

/* Initializer for the class 'Device::EnumClass' */
void DeviceEnumClass__Init( DeviceEnumClass _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  XObject__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( DeviceEnumClass );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( DeviceEnumClass );
}

/* Re-Initializer for the class 'Device::EnumClass' */
void DeviceEnumClass__ReInit( DeviceEnumClass _this )
{
  /* At first re-initialize the super class ... */
  XObject__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Device::EnumClass' */
void DeviceEnumClass__Done( DeviceEnumClass _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( XObject );

  /* Don't forget to deinitialize the super class ... */
  XObject__Done( &_this->_.Super );
}

/* 'C' function for method : 'Device::EnumClass.GetString()' */
XString DeviceEnumClass_GetString( DeviceEnumClass _this, XInt32 aItem )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  EwTrace( "%s", EwConcatString( EwLoadString( &_Const0004 ), EwNewStringInt( aItem, 
    0, 10 )));
  return 0;
}

/* Wrapper function for the virtual method : 'Device::EnumClass.GetString()' */
XString DeviceEnumClass__GetString( void* _this, XInt32 aItem )
{
  return ((DeviceEnumClass)_this)->_.VMT->GetString((DeviceEnumClass)_this, aItem );
}

/* 'C' function for method : 'Device::EnumClass.GetIcon()' */
ResourcesBitmap DeviceEnumClass_GetIcon( DeviceEnumClass _this, XInt32 aItem )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aItem );

  return 0;
}

/* Wrapper function for the virtual method : 'Device::EnumClass.GetIcon()' */
ResourcesBitmap DeviceEnumClass__GetIcon( void* _this, XInt32 aItem )
{
  return ((DeviceEnumClass)_this)->_.VMT->GetIcon((DeviceEnumClass)_this, aItem );
}

/* Variants derived from the class : 'Device::EnumClass' */
EW_DEFINE_CLASS_VARIANTS( DeviceEnumClass )
EW_END_OF_CLASS_VARIANTS( DeviceEnumClass )

/* Virtual Method Table (VMT) for the class : 'Device::EnumClass' */
EW_DEFINE_CLASS( DeviceEnumClass, XObject, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 "Device::EnumClass" )
  DeviceEnumClass_GetString,
  DeviceEnumClass_GetIcon,
EW_END_OF_CLASS( DeviceEnumClass )

/* Initializer for the class 'Device::WifiSignalEnumClass' */
void DeviceWifiSignalEnumClass__Init( DeviceWifiSignalEnumClass _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  DeviceEnumClass__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( DeviceWifiSignalEnumClass );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( DeviceWifiSignalEnumClass );
}

/* Re-Initializer for the class 'Device::WifiSignalEnumClass' */
void DeviceWifiSignalEnumClass__ReInit( DeviceWifiSignalEnumClass _this )
{
  /* At first re-initialize the super class ... */
  DeviceEnumClass__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Device::WifiSignalEnumClass' */
void DeviceWifiSignalEnumClass__Done( DeviceWifiSignalEnumClass _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( DeviceEnumClass );

  /* Don't forget to deinitialize the super class ... */
  DeviceEnumClass__Done( &_this->_.Super );
}

/* 'C' function for method : 'Device::WifiSignalEnumClass.GetString()' */
XString DeviceWifiSignalEnumClass_GetString( DeviceWifiSignalEnumClass _this, XInt32 
  aItem )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  switch ( aItem )
  {
    case 0 :
      return EwLoadString( &_Const0005 );

    case 1 :
      return EwLoadString( &_Const0006 );

    case 2 :
      return EwLoadString( &_Const0007 );

    case 3 :
      return EwLoadString( &_Const0008 );

    case 4 :
      return EwLoadString( &_Const0009 );

    case 5 :
      return EwLoadString( &_Const000A );

    default : 
      return 0;
  }
}

/* 'C' function for method : 'Device::WifiSignalEnumClass.GetIcon()' */
ResourcesBitmap DeviceWifiSignalEnumClass_GetIcon( DeviceWifiSignalEnumClass _this, 
  XInt32 aItem )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  switch ( aItem )
  {
    case 1 :
      return EwLoadResource( &Reswifi_veryweak, ResourcesBitmap );

    case 2 :
      return EwLoadResource( &Reswifi_weak, ResourcesBitmap );

    case 3 :
      return EwLoadResource( &Reswifi_ok, ResourcesBitmap );

    case 4 :
      return EwLoadResource( &Reswifi_good, ResourcesBitmap );

    case 5 :
      return EwLoadResource( &Reswifi_excelent, ResourcesBitmap );

    default : 
      return 0;
  }
}

/* Variants derived from the class : 'Device::WifiSignalEnumClass' */
EW_DEFINE_CLASS_VARIANTS( DeviceWifiSignalEnumClass )
EW_END_OF_CLASS_VARIANTS( DeviceWifiSignalEnumClass )

/* Virtual Method Table (VMT) for the class : 'Device::WifiSignalEnumClass' */
EW_DEFINE_CLASS( DeviceWifiSignalEnumClass, DeviceEnumClass, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, _.VMT, "Device::WifiSignalEnumClass" )
  DeviceWifiSignalEnumClass_GetString,
  DeviceWifiSignalEnumClass_GetIcon,
EW_END_OF_CLASS( DeviceWifiSignalEnumClass )

/* User defined auto object: 'Device::WifiSignalEnum' */
EW_DEFINE_AUTOOBJECT( DeviceWifiSignalEnum, DeviceWifiSignalEnumClass )

/* Initializer for the auto object 'Device::WifiSignalEnum' */
void DeviceWifiSignalEnum__Init( DeviceWifiSignalEnumClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Re-Initializer for the auto object 'Device::WifiSignalEnum' */
void DeviceWifiSignalEnum__ReInit( DeviceWifiSignalEnumClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Device::WifiSignalEnum' */
EW_DEFINE_AUTOOBJECT_VARIANTS( DeviceWifiSignalEnum )
EW_END_OF_AUTOOBJECT_VARIANTS( DeviceWifiSignalEnum )

/* Initializer for the class 'Device::DataProvider' */
void DeviceDataProvider__Init( DeviceDataProvider _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  XObject__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( DeviceDataProvider );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( DeviceDataProvider );
}

/* Re-Initializer for the class 'Device::DataProvider' */
void DeviceDataProvider__ReInit( DeviceDataProvider _this )
{
  /* At first re-initialize the super class ... */
  XObject__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Device::DataProvider' */
void DeviceDataProvider__Done( DeviceDataProvider _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( XObject );

  /* Don't forget to deinitialize the super class ... */
  XObject__Done( &_this->_.Super );
}

/* 'C' function for method : 'Device::DataProvider.GetInt32Data()' */
XInt32 DeviceDataProvider_GetInt32Data( DeviceDataProvider _this, XInt32 aRow, XInt32 
  aColumn )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aColumn );
  EW_UNUSED_ARG( aRow );

  return 0;
}

/* Wrapper function for the virtual method : 'Device::DataProvider.GetInt32Data()' */
XInt32 DeviceDataProvider__GetInt32Data( void* _this, XInt32 aRow, XInt32 aColumn )
{
  return ((DeviceDataProvider)_this)->_.VMT->GetInt32Data((DeviceDataProvider)_this
  , aRow, aColumn );
}

/* 'C' function for method : 'Device::DataProvider.GetStringData()' */
XString DeviceDataProvider_GetStringData( DeviceDataProvider _this, XInt32 aRow, 
  XInt32 aColumn )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aColumn );
  EW_UNUSED_ARG( aRow );

  return 0;
}

/* Wrapper function for the virtual method : 'Device::DataProvider.GetStringData()' */
XString DeviceDataProvider__GetStringData( void* _this, XInt32 aRow, XInt32 aColumn )
{
  return ((DeviceDataProvider)_this)->_.VMT->GetStringData((DeviceDataProvider)_this
  , aRow, aColumn );
}

/* 'C' function for method : 'Device::DataProvider.GetNoOfData()' */
XInt32 DeviceDataProvider_GetNoOfData( DeviceDataProvider _this )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  return 0;
}

/* Wrapper function for the virtual method : 'Device::DataProvider.GetNoOfData()' */
XInt32 DeviceDataProvider__GetNoOfData( void* _this )
{
  return ((DeviceDataProvider)_this)->_.VMT->GetNoOfData((DeviceDataProvider)_this );
}

/* 'C' function for method : 'Device::DataProvider.NotifyChange()' */
void DeviceDataProvider_NotifyChange( DeviceDataProvider _this )
{
  EwNotifyObjObservers((XObject)_this, 0 );
}

/* Wrapper function for the non virtual method : 'Device::DataProvider.NotifyChange()' */
void DeviceDataProvider__NotifyChange( void* _this )
{
  DeviceDataProvider_NotifyChange((DeviceDataProvider)_this );
}

/* Variants derived from the class : 'Device::DataProvider' */
EW_DEFINE_CLASS_VARIANTS( DeviceDataProvider )
EW_END_OF_CLASS_VARIANTS( DeviceDataProvider )

/* Virtual Method Table (VMT) for the class : 'Device::DataProvider' */
EW_DEFINE_CLASS( DeviceDataProvider, XObject, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "Device::DataProvider" )
  DeviceDataProvider_GetInt32Data,
  DeviceDataProvider_GetStringData,
  DeviceDataProvider_GetNoOfData,
EW_END_OF_CLASS( DeviceDataProvider )

/* Initializer for the class 'Device::WifiNetworksProviderClass' */
void DeviceWifiNetworksProviderClass__Init( DeviceWifiNetworksProviderClass _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  DeviceDataProvider__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( DeviceWifiNetworksProviderClass );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( DeviceWifiNetworksProviderClass );
}

/* Re-Initializer for the class 'Device::WifiNetworksProviderClass' */
void DeviceWifiNetworksProviderClass__ReInit( DeviceWifiNetworksProviderClass _this )
{
  /* At first re-initialize the super class ... */
  DeviceDataProvider__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Device::WifiNetworksProviderClass' */
void DeviceWifiNetworksProviderClass__Done( DeviceWifiNetworksProviderClass _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( DeviceDataProvider );

  /* Don't forget to deinitialize the super class ... */
  DeviceDataProvider__Done( &_this->_.Super );
}

/* 'C' function for method : 'Device::WifiNetworksProviderClass.GetInt32Data()' */
XInt32 DeviceWifiNetworksProviderClass_GetInt32Data( DeviceWifiNetworksProviderClass _this, 
  XInt32 aRow, XInt32 aColumn )
{
  XInt32 data;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  data = 0;

  switch ( aColumn )
  {
    case 1 :
      data = DeviceDriver_GetWifiNetworkSignalStrength( aRow );
    break;

    case 2 :
      data = DeviceDriver_GetWifiNetworkConnectionStatus( aRow );
    break;

    default :; 
  }

  return data;
}

/* 'C' function for method : 'Device::WifiNetworksProviderClass.GetStringData()' */
XString DeviceWifiNetworksProviderClass_GetStringData( DeviceWifiNetworksProviderClass _this, 
  XInt32 aRow, XInt32 aColumn )
{
  XString data;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  data = 0;

  switch ( aColumn )
  {
    case 0 :
      data = DeviceDriver_GetWifiNetworkSSID( aRow );
    break;

    case 3 :
      data = DeviceDriver_GetWifiNetworkSecurity( aRow );
    break;

    case 4 :
      data = DeviceDriver_GetWifiNetworkIPAddress( aRow );
    break;

    case 5 :
      data = DeviceDriver_GetWifiNetworkGateway( aRow );
    break;

    case 6 :
      data = DeviceDriver_GetWifiNetworkSubnetMask( aRow );
    break;

    default :; 
  }

  return data;
}

/* 'C' function for method : 'Device::WifiNetworksProviderClass.GetNoOfData()' */
XInt32 DeviceWifiNetworksProviderClass_GetNoOfData( DeviceWifiNetworksProviderClass _this )
{
  XInt32 noOfData;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  noOfData = 0;
  noOfData = DeviceDriver_GetWifiNetworkCount();
  return noOfData;
}

/* Variants derived from the class : 'Device::WifiNetworksProviderClass' */
EW_DEFINE_CLASS_VARIANTS( DeviceWifiNetworksProviderClass )
EW_END_OF_CLASS_VARIANTS( DeviceWifiNetworksProviderClass )

/* Virtual Method Table (VMT) for the class : 'Device::WifiNetworksProviderClass' */
EW_DEFINE_CLASS( DeviceWifiNetworksProviderClass, DeviceDataProvider, _.VMT, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Device::WifiNetworksProviderClass" )
  DeviceWifiNetworksProviderClass_GetInt32Data,
  DeviceWifiNetworksProviderClass_GetStringData,
  DeviceWifiNetworksProviderClass_GetNoOfData,
EW_END_OF_CLASS( DeviceWifiNetworksProviderClass )

/* User defined auto object: 'Device::WifiNetworksProvider' */
EW_DEFINE_AUTOOBJECT( DeviceWifiNetworksProvider, DeviceWifiNetworksProviderClass )

/* Initializer for the auto object 'Device::WifiNetworksProvider' */
void DeviceWifiNetworksProvider__Init( DeviceWifiNetworksProviderClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Re-Initializer for the auto object 'Device::WifiNetworksProvider' */
void DeviceWifiNetworksProvider__ReInit( DeviceWifiNetworksProviderClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Device::WifiNetworksProvider' */
EW_DEFINE_AUTOOBJECT_VARIANTS( DeviceWifiNetworksProvider )
EW_END_OF_AUTOOBJECT_VARIANTS( DeviceWifiNetworksProvider )

/* Initializer for the class 'Device::WifiConnectionStatusEnumClass' */
void DeviceWifiConnectionStatusEnumClass__Init( DeviceWifiConnectionStatusEnumClass _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  DeviceEnumClass__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( DeviceWifiConnectionStatusEnumClass );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( DeviceWifiConnectionStatusEnumClass );
}

/* Re-Initializer for the class 'Device::WifiConnectionStatusEnumClass' */
void DeviceWifiConnectionStatusEnumClass__ReInit( DeviceWifiConnectionStatusEnumClass _this )
{
  /* At first re-initialize the super class ... */
  DeviceEnumClass__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Device::WifiConnectionStatusEnumClass' */
void DeviceWifiConnectionStatusEnumClass__Done( DeviceWifiConnectionStatusEnumClass _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( DeviceEnumClass );

  /* Don't forget to deinitialize the super class ... */
  DeviceEnumClass__Done( &_this->_.Super );
}

/* 'C' function for method : 'Device::WifiConnectionStatusEnumClass.GetString()' */
XString DeviceWifiConnectionStatusEnumClass_GetString( DeviceWifiConnectionStatusEnumClass _this, 
  XInt32 aItem )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  switch ( aItem )
  {
    case 0 :
      return EwLoadString( &StringsWiFiNotConnected );

    case 1 :
      return EwLoadString( &StringsWiFiConnected );

    default : 
      return 0;
  }
}

/* Variants derived from the class : 'Device::WifiConnectionStatusEnumClass' */
EW_DEFINE_CLASS_VARIANTS( DeviceWifiConnectionStatusEnumClass )
EW_END_OF_CLASS_VARIANTS( DeviceWifiConnectionStatusEnumClass )

/* Virtual Method Table (VMT) for the class : 'Device::WifiConnectionStatusEnumClass' */
EW_DEFINE_CLASS( DeviceWifiConnectionStatusEnumClass, DeviceEnumClass, _.VMT, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Device::WifiConnectionStatusEnumClass" )
  DeviceWifiConnectionStatusEnumClass_GetString,
  DeviceEnumClass_GetIcon,
EW_END_OF_CLASS( DeviceWifiConnectionStatusEnumClass )

/* User defined auto object: 'Device::WifiConnectionStatusEnum' */
EW_DEFINE_AUTOOBJECT( DeviceWifiConnectionStatusEnum, DeviceWifiConnectionStatusEnumClass )

/* Initializer for the auto object 'Device::WifiConnectionStatusEnum' */
void DeviceWifiConnectionStatusEnum__Init( DeviceWifiConnectionStatusEnumClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Re-Initializer for the auto object 'Device::WifiConnectionStatusEnum' */
void DeviceWifiConnectionStatusEnum__ReInit( DeviceWifiConnectionStatusEnumClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Device::WifiConnectionStatusEnum' */
EW_DEFINE_AUTOOBJECT_VARIANTS( DeviceWifiConnectionStatusEnum )
EW_END_OF_AUTOOBJECT_VARIANTS( DeviceWifiConnectionStatusEnum )

/* Embedded Wizard */
