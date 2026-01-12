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
*   The following code demonstrates the access to the board LED, a simulated
*   ADC value and the hardware button. Furthemore, the console interface is used
*   to print a string.
*
*   The Embedded Wizard GUI example 'DeviceIntegration' shows the usage of this
*   device driver.
*
*   This file assumes to be the counterpart of the device class 'DeviceClass'
*   within the unit 'Application'.
*
*******************************************************************************/

#ifndef DEVICEDRIVER_H
#define DEVICEDRIVER_H


#ifdef __cplusplus
  extern "C"
  {
#endif


/*******************************************************************************
* FUNCTION:
*   DeviceIntegrationExample_Init
*
* DESCRIPTION:
*   This is the initialization function used for the example 'DeviceIntegration'.
*   It initializes the hardware that should be accessed from the GUI. If the
*   GUI application is running in an operating system, a separate worker-thread
*   will be created to showcase the data processing as separate thread.
*
*******************************************************************************/
void DeviceIntegrationExample_Init( void );


/*******************************************************************************
* FUNCTION:
*   DeviceIntegrationExample_Done
*
* DESCRIPTION:
*   This is the de-initialization function of the example 'DeviceIntegration'.
*   It de-initializes the hardware that was accessed from the GUI. If the
*   GUI application is running in an operating system, the separate worker-thread
*   will be terminated.
*
*******************************************************************************/
void DeviceIntegrationExample_Done( void );


/*******************************************************************************
* FUNCTION:
*   DeviceIntegrationExample_SetLedStatus
*
* DESCRIPTION:
*   This is a sample for a function called from the device class, when a
*   property has changed. As a result, the corresponding value of the real
*   device should be changed.
*   In this implementation the LED is switched on or off.
*
*******************************************************************************/
void DeviceIntegrationExample_SetLedStatus( XInt32 aValue );


/*******************************************************************************
* FUNCTION:
*   DeviceIntegrationExample_PrintMessage
*
* DESCRIPTION:
*   This is a sample for a function that is called directly from a 'Command'
*   method of the device class. As a result, the corresponding action should
*   happen.
*   In this implementation the given message is printed via the console interface.
*
*******************************************************************************/
void DeviceIntegrationExample_PrintMessage( XString aText );


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
void DeviceDriver_Initialize( void );


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
void DeviceDriver_Deinitialize( void );


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
int DeviceDriver_ProcessData( void );


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
void DeviceDriver_SetFlowRate( XInt32 aValue );


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
void DeviceDriver_SetInfusionVolume( XInt32 aValue );


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
void DeviceDriver_SetInfusionTime( XInt32 aValue );


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
void DeviceDriver_StartInfusion();

/*******************************************************************************
* FUNCTION:
*   DeviceDriver_StopInfusion
*
* DESCRIPTION:
*   The function DeviceDriver_StopInfusion() is called by the GUI to stop the
*   infusion process.
* 
* ARGUMENTS:
*   NONE
*
* RETURN VALUE:
*   NONE
*
*******************************************************************************/
void DeviceDriver_StopInfusion();

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
void DeviceDriver_RestartInfusion();


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
void DeviceDriver_ClearSettings();


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
void DeviceDriver_SetBolusVolumeSet( XInt32 aValue );


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
void DeviceDriver_SetPressureSetting( XInt32 aValue );


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
void DeviceDriver_SetSoftwareUpdate( XBool aValue );


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
void DeviceDriver_SetWifiStatus( XBool aValue );


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
void DeviceDriver_SetBrightness( XInt32 aValue );


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
void DeviceDriver_MuteAlarm( XInt32 aId );

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
void DeviceDriver_ConfirmNotification( XInt32 aId );

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
void DeviceDriver_SetAudioVolume( XInt32 value );

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
XInt32 DeviceDriver_GetWifiNetworkSignalStrength( XInt32 aRow );

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
XInt32 DeviceDriver_GetWifiNetworkConnectionStatus( XInt32 aRow );

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
*   SSID string identifier.
*
*******************************************************************************/
XString DeviceDriver_GetWifiNetworkSSID( XInt32 aRow );

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
*   Security type XString.
*
*******************************************************************************/
XString DeviceDriver_GetWifiNetworkSecurity( XInt32 aRow );

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
XString DeviceDriver_GetWifiNetworkIPAddress( XInt32 aRow );

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
XString DeviceDriver_GetWifiNetworkGateway( XInt32 aRow );

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
XString DeviceDriver_GetWifiNetworkSubnetMask( XInt32 aRow );

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
XInt32 DeviceDriver_GetWifiNetworkCount( void );


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
void DeviceDriver_SetKVOMode( XBool Value);
#ifdef __cplusplus
  }
#endif

#endif /* DEVICEDRIVER_H */


/* msy */
