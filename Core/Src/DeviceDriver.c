/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This software is delivered "as is" and shows the usage of other software
* components. It is provided as an example software which is intended to be
* modified and extended according to particular requirements.
*
* TARA Systems hereby disclaims all warranties and conditions with regard to the
* software, including all implied warranties and conditions of merchantability
* and non-infringement of any third party IPR or other rights which may result
* from the use or the inability to use the software.
*
********************************************************************************
*
* DESCRIPTION:
*   This file implements an interface between an Embedded Wizard generated UI
*   application and a certain device. Please consider this file only as template
*   that is intended to show the binding between an UI application and the
*   underlying system (e.g. middleware, BSP, hardware driver, protocol, ...).
*
*   This device driver is the counterpart to a device class implemented within
*   your Embedded Wizard project.
*
*   Feel free to adapt this file according your needs!
*
*   This file assumes to be the counterpart of the device class 'DeviceClass'
*   within the unit 'Device'.
*
*******************************************************************************/

/*
   Include all necessary files to access the real device and/or to get access
   to the required operating system calls.
*/
#include "ewrte.h"
#include "ew_bsp_os.h"
#include "infDevice.h"

/*
   Include the generated header file to access the device class, for example to
   access the class 'DeviceClass' from the unit 'Device' include the
   generated file 'Device.h'.
*/
#include "Device.h"

/* Reference to the GUI Device Autoobject  */
static DeviceDeviceClass DeviceObject = 0;


/*******************************************************************************
* FUNCTION:
*   DeviceDriver_Initialize
*
* DESCRIPTION:
*   The function DeviceDriver_Initialize() initializes the module and prepares all
*   necessary things to access or communicate with the real device.
*   The function has to be called from your main module, before the initialization
*   of your GUI application.
*
*   IMPORTANT NOTE: This global initialization function exists for compatibility
*   reasons. The initialization of dedicated hardware drivers or middleware APIs
*   should be done in separate functions called by the Init constructor of the
*   device class.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void DeviceDriver_Initialize( void )
{
  /*
     You can implement here the necessary code to initialize your particular
     hardware, to open needed devices, to open communication channels, etc.
  */

  /*   
  Get access to the counterpart of this device driver: get access to the
  device class that is created as autoobject within your Embedded Wizard
  project. For this purpose you can call the function EwGetAutoObject().
  This function contains two paramters: The pointer to the autoobject and
  the class of the autoobject.
  */   
  DeviceObject = EwGetAutoObject( &DeviceDevice, DeviceDeviceClass );

  /*
  Once you have the access to the autoobject, lock it as long as you need
  the access (typically, until your device driver is closed). By locking 
  the autoobject, you can ensure that the object of the device class will 
  be kept within the memory and not freed by the Garbage Collector.
  Once the device class is locked, you can easily store it within a static 
  variable to access the driver class during the runtime.
  */     
  EwLockObject( DeviceObject );  
}


/*******************************************************************************
* FUNCTION:
*   DeviceDriver_Deinitialize
*
* DESCRIPTION:
*   The function DeviceDriver_Deinitialize() deinitializes the module and
*   finalizes the access or communication with the real device.
*   The function has to be called from your main module, after the GUI
*   application will be deinitialized.
*
*   IMPORTANT NOTE: This global de-initialization function exists for
*   compatibility reasons. It is recommend to use the Done destructor of the
*   device class.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void DeviceDriver_Deinitialize( void )
{
  /*
     You can implement here the necessary code to deinitialize your particular
     hardware, to close used devices, to close communication channels, etc.
  */

  // Release Device object
  if ( DeviceObject )
  {
    EwUnlockObject( DeviceObject );
    DeviceObject = 0;
  }  
}


/*******************************************************************************
* FUNCTION:
*   DeviceDriver_ProcessData
*
* DESCRIPTION:
*   The function DeviceDriver_ProcessData() is called from the main UI loop, in
*   order to process data and events from your particular device.
*   This function is responsible to update properties within the device class
*   if the corresponding state or value of the real device has changed.
*   This function is also responsible to trigger system events if necessary.
*
*   IMPORTANT NOTE: This data processing function can be used to process data
*   periodically in the context of the main GUI thread/task or in case there
*   is no operating system at all (bare metal).
*   In case you want to feed the GUI application with data and events from a
*   foreign thread/task or an interrupt service routine it will be much easier
*   to use the functions EwInvoke() and EwInvokeCopy().
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   The function returns a non-zero value if a property has changed or if a
*   system event was triggered. If nothing happens, the function returns 0.
*
*******************************************************************************/
int DeviceDriver_ProcessData( void )
{
  int needUpdate = 0;
  static int bootProgress = 0;

	  bootProgress++;

	  DeviceDeviceClass_UpdateBootProgress( DeviceObject, bootProgress );
	  needUpdate = 1;


  /*
     Get the data you want to provide to the GUI application.
     Please note, that this function is called within the context of the main
     GUI thread/task.
  */

 /*
  * TODO 1: 
  *   - when in booting, please update the DeviceObject BootProgress property:
  *     DeviceDeviceClass_UpdateBootProgress( DeviceObject, bootProgress );
  *     needUpdate = 1;
  */

 /*
  * TODO 2: 
  *   - when the infusion state is changed, please update the DeviceObject InfusionState property:
  *     DeviceDeviceClass_UpdateInfusionState( DeviceObject, DeviceInfusionStateInfusing );
  *     needUpdate = 1;
  *    
  */

  /*
     Return a value != 0 if there is at least one property changed or if a
     system event was triggered. The return value is used by the main loop, to
     decide whether the GUI application has changed or not.
  */
  return needUpdate;
}


/*******************************************************************************
* FUNCTION:
*   DeviceDriver_SetFlowRate
*
* DESCRIPTION:
*   The function DeviceDriver_SetFlowRate() is called by the GUI to set a
*   new flow rate value.
*
* ARGUMENTS:
*   aValue - Flow Rate value. Range 0 - 120000
             Resolution -2 hardcoded in GUI ( 0.00 - 1200.00 )
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_SetFlowRate( XInt32 aValue )
{
    float value_f =0.0;
	EwPrint( "SetFlowRate - %d\n", aValue );

  
  /* TODO:
  *  set / store the new Flow Rate 
  */
	value_f = 	aValue/100.0;
  InfDevice_SetFlowRate( value_f );
}


/*******************************************************************************
* FUNCTION:
*   DeviceDriver_SetInfusionVolume
*
* DESCRIPTION:
*   The function DeviceDriver_SetInfusionVolume() is called by the GUI to set a
*   new infusion volume value.
*
* ARGUMENTS:
*   aValue - Infusion Volume value. Range 1 - 999900
*            Resolution -2 hardcoded in GUI ( 0.01 - 9999.00 )
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_SetInfusionVolume( XInt32 aValue )
{

  EwPrint( "SetInfusionVolume - %d\n", aValue );

  /* TODO:
  *  set / store the new Infusion Volume
  */

  InfDevice_SetVTBI( (float)(aValue)/100.0 );

}


/*******************************************************************************
* FUNCTION:
*   DeviceDriver_SetInfusionTime
*
* DESCRIPTION:
*   The function DeviceDriver_SetInfusionTime() is called by the GUI to set a
*   new infusion time.
*
* ARGUMENTS:
*   aValue - Infusion Time in seconds
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_SetInfusionTime( XInt32 aValue )
{
  EwPrint( "SetInfusionTime - %d\n", aValue );

  /* TODO:
  *  set / store the new Infusion Time
  */
  InfDevice_SetInfusionTime( aValue );

}


/*******************************************************************************
* FUNCTION:
*   DeviceDriver_StartInfusion
*
* DESCRIPTION:
*   The function DeviceDriver_StartInfusion() is called by the GUI to start the
*   infusion process.
* 
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_StartInfusion()
{
  EwPrint( "START INFUSION\n" );

  /* TODO 1:
  *  start infusion process
  */
  InfDevice_EvStart( );

 /*
  * TODO 2: 
  *   - if infusion started successfully set the InfusionState to Infusing:*/
  DeviceDeviceClass_UpdateInfusionState( DeviceObject, DeviceInfusionStateInfusing );

}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_StopInfusion
*
* DESCRIPTION:
*   The function DeviceDriver_StopInfusion() is called by the GUI when the
*   user chooses to stop the infusion.
* 
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_StopInfusion()
{
  EwPrint( "STOP INFUSION\n" );

  /* TODO 1:
  *  stop infusion process
  */
  InfDevice_EvPauseByUser( );
 /*
  * TODO 2: 
  *   - if infusion stopped successfully set the InfusionState to PausedByUser:*/
   DeviceDeviceClass_UpdateInfusionState( DeviceObject, DeviceInfusionStatePausedByUser );


}


/*******************************************************************************
* FUNCTION:
*   DeviceDriver_RestartInfusion
*
* DESCRIPTION:
*   The function DeviceDriver_RestartInfusion() is called by the GUI when the
*   user chooses to restart the infusion.
* 
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_RestartInfusion()
{
  EwPrint( "RESTART INFUSION\n" );

  /* TODO:
  *  restart infusion process
  */
  InfDevice_EvResume( );
  DeviceDeviceClass_UpdateInfusionState( DeviceObject, DeviceInfusionStateInfusing );

}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_ClearSettings
*
* DESCRIPTION:
*   The function DeviceDriver_ClearSettings() is called by the GUI when the
*   user chooses to clear the infusion settings.
* 
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_ClearSettings()
{
  EwPrint( "CLEAR SETTINGS\n" );

  /* TODO:
  *  clear infusion settings
  */
  InfDevice_EvStop( );
}


/*******************************************************************************
* FUNCTION:
*   DeviceDriver_SetBolusVolumeSet
*
* DESCRIPTION:
*   The function DeviceDriver_SetBolusVolumeSet() is called by the GUI to set a
*   new Bolus Volume Set.
*
* ARGUMENTS:
*   aValue - Bolus Volume Set: 5,10,15,20,25,...100
*            Resolution TBD ( 0 for now )
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_SetBolusVolumeSet( XInt32 aValue )
{
  EwPrint( "SetBolusVolumeSet - %d\n", aValue );

  /* TODO:
  *  set / store the new Bolus Volume Set
  */

}


/*******************************************************************************
* FUNCTION:
*   DeviceDriver_SetPressureSetting
*
* DESCRIPTION:
*   The function DeviceDriver_SetPressureSetting() is called by the GUI to set a
*   new Pressure Setting.
*
* ARGUMENTS:
*   aValue - Pressure Setting. Range 1-9
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_SetPressureSetting( XInt32 aValue )
{
  EwPrint( "SetPressureSetting - %d\n", aValue );

  /* TODO:
  *  set / store the new Pressure Setting
  */

}


/*******************************************************************************
* FUNCTION:
*   DeviceDriver_SetSoftwareUpdate
*
* DESCRIPTION:
*   The function DeviceDriver_SetSoftwareUpdate() is called by the GUI to start
*   a Software Update.
*
* ARGUMENTS:
*   aValue - if true start software update
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_SetSoftwareUpdate( XBool aValue )
{
  EwPrint( "SetSoftwareUpdate - %d\n", aValue );

  /* TODO:
  *  start software update if aValue is true
  */

}


/*******************************************************************************
* FUNCTION:
*   DeviceDriver_SetWifiStatus
*
* DESCRIPTION:
*   The function DeviceDriver_SetWifiStatus() is called by the GUI to turn the
*   WiFi on / off.
*
* ARGUMENTS:
*   aValue - 0 is off, 1 is on
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_SetWifiStatus( XBool aValue )
{
  EwPrint( "SetWifiStatus - %d\n", aValue );

#warning "Following is hardcoded which needs to be modified later"

  XString Value= EwNewStringAnsi("<Aria-IVF10-1220240002><IVF10-1220240002>");
  if( 1 == aValue )
  {
	  DeviceDeviceClass__UpdateAppQRCode( DeviceObject, Value);
  }

  /* TODO:
  *  if aValue is 0 turn wifi off, otherwise turn it on
  */

}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_MuteAlarm
*
* DESCRIPTION:
*   The function DeviceDriver_MuteAlarm() is called by the GUI to mute the
*   specified alarm.
*
* ARGUMENTS:
*   aId - Alarm identifier.
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_MuteAlarm( XInt32 aId )
{
    // TODO: Implement alarm mute functionality for alarm ID aId
}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_ConfirmNotification
*
* DESCRIPTION:
*   The function DeviceDriver_ConfirmNotification() is called by the GUI to
*   confirm a notification event.
*
* ARGUMENTS:
*   aId - Notification identifier.
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_ConfirmNotification( XInt32 aId )
{
    // TODO: Implement notification confirmation for ID aId
}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_SetAudioVolume
*
* DESCRIPTION:
*   The function DeviceDriver_SetAudioVolume() is called by the GUI to set the
*   audio output volume.
*
* ARGUMENTS:
*   value - Volume level. Range: 0 - 9
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_SetAudioVolume( XInt32 value )
{
    // TODO: Implement audio volume adjustment. Ensure value is within 0-9.
}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_GetWifiNetworkSignalStrength
*
* DESCRIPTION:
*   Retrieves the current Wi-Fi network signal strength.
*
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   Signal strength (RSSI) in dBm.
*
*******************************************************************************/
XInt32 DeviceDriver_GetWifiNetworkSignalStrength( XInt32 aRow )
{
    // TODO: Retrieve and return Wi-Fi signal strength
    return 0;
}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_GetWifiNetworkConnectionStatus
*
* DESCRIPTION:
*   Retrieves the current Wi-Fi network connection status.
*
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   Connection status code.
*
*******************************************************************************/
XInt32 DeviceDriver_GetWifiNetworkConnectionStatus( XInt32 aRow )
{
    // TODO: Retrieve and return connection status
    return 0;
}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_GetWifiNetworkSSID
*
* DESCRIPTION:
*   Retrieves the SSID of the connected Wi-Fi network.
*
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   SSID string identifier as XString
*
*******************************************************************************/
XString DeviceDriver_GetWifiNetworkSSID( XInt32 aRow )
{
    // TODO: Retrieve and return network SSID identifier
    return 0;
}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_GetWifiNetworkSecurity
*
* DESCRIPTION:
*   Retrieves the security type of the connected Wi-Fi network.
*
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   Security type code XString
*
*******************************************************************************/
XString DeviceDriver_GetWifiNetworkSecurity( XInt32 aRow )
{
    // TODO: Retrieve and return network security type
    return 0;
}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_GetWifiNetworkIPAddress
*
* DESCRIPTION:
*   Retrieves the IP address assigned to the device on the Wi-Fi network.
*
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   IP address as a XString
*
*******************************************************************************/
XString DeviceDriver_GetWifiNetworkIPAddress( XInt32 aRow )
{
    // TODO: Retrieve and return IP address
    return 0;
}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_GetWifiNetworkGateway
*
* DESCRIPTION:
*   Retrieves the gateway address for the connected Wi-Fi network.
*
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   Gateway address as a XString
*
*******************************************************************************/
XString DeviceDriver_GetWifiNetworkGateway( XInt32 aRow )
{
    // TODO: Retrieve and return gateway address
    return 0;
}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_GetWifiNetworkSubnetMask
*
* DESCRIPTION:
*   Retrieves the subnet mask for the connected Wi-Fi network.
*
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   Subnet mask as a XString
*
*******************************************************************************/
XString DeviceDriver_GetWifiNetworkSubnetMask( void )
{
    // TODO: Retrieve and return subnet mask
    return 0;
}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_GetWifiNetworkCount
*
* DESCRIPTION:
*   Retrieves the number of available Wi-Fi networks.
*
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   Number of detected networks.
*
*******************************************************************************/
XInt32 DeviceDriver_GetWifiNetworkCount( void )
{
    // TODO: Scan and return number of available networks
    return 0;
}


/*******************************************************************************
* FUNCTION:
*   DeviceDriver_SetBrightness
*
* DESCRIPTION:
*   The function DeviceDriver_SetBrightness() is called by the GUI to set the
*   display brightness.
*
* ARGUMENTS:
*   aValue - Brightness value. Range:  0 - 100 )
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_SetBrightness( XInt32 aValue )
{
  EwPrint( "SetWifiStatus - %d\n", aValue );

  /* TODO:
  *  if aValue is 0 turn wifi off, otherwise turn it on
  */

}

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_SetKVOMode
*
* DESCRIPTION:
*  Set the KVO Mode
*
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   Number of detected networks.
*
*******************************************************************************/
void DeviceDriver_SetKVOMode( XBool aValue)
{

	 EwPrint( "Set KVO Mode - %d\n", aValue );
	 /* TODO:
	   *  if aValue is 0 turn KVO off, otherwise turn it on
	   */
}

/* msy */
