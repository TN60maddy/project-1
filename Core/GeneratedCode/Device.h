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

#ifndef Device_H
#define Device_H

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
#include "_DeviceDeviceClass.h"
#include "_DeviceEnumClass.h"
#include "_DeviceWifiConnectionStatusEnumClass.h"
#include "_DeviceWifiNetworksProviderClass.h"
#include "_DeviceWifiSignalEnumClass.h"

/* User defined enumeration: 'Device::PageType' */
typedef XEnum DevicePageType;

#define DevicePageTypeNone                                  0
#define DevicePageTypeBoot                                  1
#define DevicePageTypeHome                                  2
#define DevicePageTypeLAST                                  3
#define DevicePageTypeInfusionRunning                       4

/* User defined auto object: 'Device::Device' */
EW_DECLARE_AUTOOBJECT( DeviceDevice, DeviceDeviceClass )

/* User defined enumeration: 'Device::SettingsPage' */
typedef XEnum DeviceSettingsPage;

#define DeviceSettingsPageNone                              0
#define DeviceSettingsPageSettings                          1
#define DeviceSettingsPagePressure                          2
#define DeviceSettingsPageAirBubbleDetector                 3
#define DeviceSettingsPageDisplay                           4
#define DeviceSettingsPageBolusRate                         5
#define DeviceSettingsPageKVO                               6
#define DeviceSettingsPageGeneral                           7
#define DeviceSettingsPageWifi                              8
#define DeviceSettingsPageAudioVolumeControl                9
#define DeviceSettingsPageDateAndTime                       10
#define DeviceSettingsPageLanguage                          11
#define DeviceSettingsPageSoftwareUpdate                    12
#define DeviceSettingsPageAbout                             13
#define DeviceSettingsPageMaintenanceAndCalibration         14
#define DeviceSettingsPageLAST                              15

/* User defined enumeration: 'Device::WiFiSignal' */
typedef XEnum DeviceWiFiSignal;

#define DeviceWiFiSignalNoSignal                            0
#define DeviceWiFiSignalVeryWeak                            1
#define DeviceWiFiSignalWeak                                2
#define DeviceWiFiSignalOk                                  3
#define DeviceWiFiSignalGood                                4
#define DeviceWiFiSignalExcellent                           5
#define DeviceWiFiSignalLAST                                6

/* User defined enumeration: 'Device::BatteryChargeStatus' */
typedef XEnum DeviceBatteryChargeStatus;

#define DeviceBatteryChargeStatusNotConnected               0
#define DeviceBatteryChargeStatusChargingUSB                1
#define DeviceBatteryChargeStatusChargingPower              2
#define DeviceBatteryChargeStatusNotChargingOnBattery       3
#define DeviceBatteryChargeStatusLAST                       4

/* User defined enumeration: 'Device::InfusionState' */
typedef XEnum DeviceInfusionState;

#define DeviceInfusionStateInit                             0
#define DeviceInfusionStateSelftTestInProgress              1
#define DeviceInfusionStateSelfTestFailed                   2
#define DeviceInfusionStateIdle                             3
#define DeviceInfusionStateCfgSet                           4
#define DeviceInfusionStateInfusing                         5
#define DeviceInfusionStatePausedByUser                     6
#define DeviceInfusionStatePausedUpstreamPressLow           7
#define DeviceInfusionStatePausedDownstreamPressLow         8
#define DeviceInfusionStatePausedUpstreamPressHigh          9
#define DeviceInfusionStatePausedDownstreamPressHigh        10
#define DeviceInfusionStatePausedAirBubble                  11
#define DeviceInfusionStateLAST                             12

/* User defined enumeration: 'Device::WifiStatus' */
typedef XEnum DeviceWifiStatus;

#define DeviceWifiStatusOff                                 0
#define DeviceWifiStatusOn                                  1

/* User defined enumeration: 'Device::PopupType' */
typedef XEnum DevicePopupType;

#define DevicePopupTypeNone                                 0
#define DevicePopupTypeKeyboard                             1
#define DevicePopupTypeValuePicker                          2
#define DevicePopupTypeBolusMenu                            3
#define DevicePopupTypeInfusionStartConfirm                 4
#define DevicePopupTypeInfusionStop                         5
#define DevicePopupTypeConfirmation                         6
#define DevicePopupTypeInfoTip                              7
#define DevicePopupTypeInfo                                 8
#define DevicePopupTypeError                                9
#define DevicePopupTypeLAST                                 10

/* User defined auto object: 'Device::WifiSignalEnum' */
EW_DECLARE_AUTOOBJECT( DeviceWifiSignalEnum, DeviceWifiSignalEnumClass )

/* User defined enumeration: 'Device::NotificationId' */
typedef XEnum DeviceNotificationId;

#define DeviceNotificationIdNone                            0
#define DeviceNotificationIdOpenRollerClamp                 1
#define DeviceNotificationIdCloseRollerClamp                2
#define DeviceNotificationIdAirBubbleAlarm                  3
#define DeviceNotificationIdUpstreamOcclusion               4
#define DeviceNotificationIdDeviceAlarmOnBoot               5
#define DeviceNotificationIdDeviceAlarm                     6
#define DeviceNotificationIdLAST                            7

/* User defined enumeration: 'Device::NotificationType' */
typedef XEnum DeviceNotificationType;

#define DeviceNotificationTypeUndefined                     0
#define DeviceNotificationTypeInfo                          1
#define DeviceNotificationTypeWarning                       2
#define DeviceNotificationTypeError                         3

/* User defined auto object: 'Device::WifiNetworksProvider' */
EW_DECLARE_AUTOOBJECT( DeviceWifiNetworksProvider, DeviceWifiNetworksProviderClass )

/* User defined enumeration: 'Device::WifiNetworkData' */
typedef XEnum DeviceWifiNetworkData;

#define DeviceWifiNetworkDataSSID                           0
#define DeviceWifiNetworkDataSignalStrength                 1
#define DeviceWifiNetworkDataConnectionStatus               2
#define DeviceWifiNetworkDataSecurity                       3
#define DeviceWifiNetworkDataIPAddress                      4
#define DeviceWifiNetworkDataGateway                        5
#define DeviceWifiNetworkDataSubnetMask                     6

/* User defined enumeration: 'Device::WifiConnectionStatus' */
typedef XEnum DeviceWifiConnectionStatus;

#define DeviceWifiConnectionStatusNotConnected              0
#define DeviceWifiConnectionStatusConnected                 1
#define DeviceWifiConnectionStatusLAST                      2

/* User defined auto object: 'Device::WifiConnectionStatusEnum' */
EW_DECLARE_AUTOOBJECT( DeviceWifiConnectionStatusEnum, DeviceWifiConnectionStatusEnumClass )

#ifdef __cplusplus
  }
#endif

#endif /* Device_H */

/* Embedded Wizard */
