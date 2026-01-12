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

#ifndef Application_H
#define Application_H

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

#include "_ApplicationAbout.h"
#include "_ApplicationAirBubbleDetector.h"
#include "_ApplicationApplication.h"
#include "_ApplicationAudioVolumeControl.h"
#include "_ApplicationBaseMenuPopup.h"
#include "_ApplicationBolusMenuPopup.h"
#include "_ApplicationBolusRateSettings.h"
#include "_ApplicationBoot.h"
#include "_ApplicationConfirmationPopup.h"
#include "_ApplicationDataAndTime.h"
#include "_ApplicationDisplayAndBrightness.h"
#include "_ApplicationErrorPopup.h"
#include "_ApplicationGeneralSettings.h"
#include "_ApplicationHome.h"
#include "_ApplicationInfoPopup.h"
#include "_ApplicationInfoTipPopup.h"
#include "_ApplicationInfusionBasePage.h"
#include "_ApplicationInfusionRunning.h"
#include "_ApplicationInfusionStopPopup.h"
#include "_ApplicationInputPopup.h"
#include "_ApplicationKVOSettings.h"
#include "_ApplicationLanguage.h"
#include "_ApplicationMaintenanceAndCalibration.h"
#include "_ApplicationMenuPopup.h"
#include "_ApplicationMessagePopup.h"
#include "_ApplicationNotificationPopup.h"
#include "_ApplicationNumKeyboardPopup.h"
#include "_ApplicationPopup.h"
#include "_ApplicationPopupContainer.h"
#include "_ApplicationPopupNavigatorClass.h"
#include "_ApplicationPressureSettings.h"
#include "_ApplicationSettings.h"
#include "_ApplicationSettingsContainer.h"
#include "_ApplicationSettingsNavigatorClass.h"
#include "_ApplicationSettingsPage.h"
#include "_ApplicationSettingsSubPage.h"
#include "_ApplicationSoftwareUpdate.h"
#include "_ApplicationStartInfusionConfirmPopup.h"
#include "_ApplicationStatusBar.h"
#include "_ApplicationTimerPickerPopup.h"
#include "_ApplicationWifiConfigPopup.h"
#include "_ApplicationWifiNetworkListItem.h"
#include "_ApplicationWifiSettings.h"

/* Forward declaration of the class Effects::SlideTransition */
#ifndef _EffectsSlideTransition_
  EW_DECLARE_CLASS( EffectsSlideTransition )
#define _EffectsSlideTransition_
#endif

/* User defined auto object: 'Application::SlideLeft' */
EW_DECLARE_AUTOOBJECT( ApplicationSlideLeft, EffectsSlideTransition )

/* User defined auto object: 'Application::SlideRight' */
EW_DECLARE_AUTOOBJECT( ApplicationSlideRight, EffectsSlideTransition )

/* Popup Navigator autobject. */
EW_DECLARE_AUTOOBJECT( ApplicationPopupNavigator, ApplicationPopupNavigatorClass )

/* Page Navigator autobject. */
EW_DECLARE_AUTOOBJECT( ApplicationSettingsNavigator, ApplicationSettingsNavigatorClass )

/* User defined enumeration: 'Application::PopupAlign' */
typedef XEnum ApplicationPopupAlign;

#define ApplicationPopupAlignCentered                       0
#define ApplicationPopupAlignStartAreaBottomRight           1

/* Notification Navigator autobject. */
EW_DECLARE_AUTOOBJECT( ApplicationNotificationNavigator, ApplicationPopupNavigatorClass )

#ifdef __cplusplus
  }
#endif

#endif /* Application_H */

/* Embedded Wizard */
