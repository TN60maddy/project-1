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
#include "_ComponentsBaseTile.h"
#include "_ComponentsBaseTileTime.h"
#include "_ComponentsBattery.h"
#include "_ComponentsDataList.h"
#include "_ComponentsDateTimeSettingItem.h"
#include "_ComponentsEditTile.h"
#include "_ComponentsEditTileNumValue.h"
#include "_ComponentsEditTileTime.h"
#include "_ComponentsEnumSettingItem.h"
#include "_ComponentsHeader.h"
#include "_ComponentsInfoTip.h"
#include "_ComponentsIntSettingItem.h"
#include "_ComponentsIntValueDisplay.h"
#include "_ComponentsKeyboardPopupButton.h"
#include "_ComponentsLogo.h"
#include "_ComponentsMenuButton.h"
#include "_ComponentsNotificationButton.h"
#include "_ComponentsNumKeyboard.h"
#include "_ComponentsPressureSettingButton.h"
#include "_ComponentsPressureTile.h"
#include "_ComponentsProgressBar.h"
#include "_ComponentsQRCode.h"
#include "_ComponentsRoundIconButton.h"
#include "_ComponentsSettingsButton.h"
#include "_ComponentsSettingsOpenButton.h"
#include "_ComponentsStringSettingItem.h"
#include "_ComponentsStringValueDisplay.h"
#include "_ComponentsTextButton.h"
#include "_ComponentsTile.h"
#include "_ComponentsTileInRunning.h"
#include "_ComponentsTileTime.h"
#include "_ComponentsTileTimeInRunning.h"
#include "_ComponentsTimePicker.h"
#include "_ComponentsToggleButton.h"
#include "_ComponentsVertScrollbar.h"
#include "_CoreGroup.h"
#include "_CoreOutline.h"
#include "_CoreSimpleTouchHandler.h"
#include "_CoreSlideTouchHandler.h"
#include "_CoreSystemEventHandler.h"
#include "_CoreTime.h"
#include "_CoreTimer.h"
#include "_CoreView.h"
#include "_DeviceDataProvider.h"
#include "_DeviceDeviceClass.h"
#include "_DeviceEnumClass.h"
#include "_DeviceWifiConnectionStatusEnumClass.h"
#include "_DeviceWifiNetworksProviderClass.h"
#include "_DeviceWifiSignalEnumClass.h"
#include "_EffectsColorEffect.h"
#include "_EffectsInt32Effect.h"
#include "_EffectsRectEffect.h"
#include "_EffectsSlideTransition.h"
#include "_EffectsTransition.h"
#include "_GraphicsAttrSet.h"
#include "_NavigationContainer.h"
#include "_NavigationNavigatorClass.h"
#include "_NavigationPage.h"
#include "_ResourcesBitmap.h"
#include "_ResourcesFont.h"
#include "_ToolsHelperCollection.h"
#include "_ViewsAttrText.h"
#include "_ViewsImage.h"
#include "_ViewsRectangle.h"
#include "_ViewsText.h"
#include "_WidgetSetHorizontalSlider.h"
#include "_WidgetSetHorizontalSliderConfig.h"
#include "Application.h"
#include "Core.h"
#include "Device.h"
#include "Effects.h"
#include "Fonts.h"
#include "Navigation.h"
#include "Res.h"
#include "Resources.h"
#include "Strings.h"
#include "Tools.h"
#include "Views.h"

/* Compressed strings for the language 'Default'. */
EW_CONST_STRING_PRAGMA static const unsigned int _StringsDefault0[] =
{
  0x000002B0, /* ratio 51.74 % */
  0xB8003B00, 0x0008A452, 0x3C010729, 0x0003A849, 0x00550008, 0x068001B8, 0x00891840,
  0x036000C8, 0x87464CA0, 0x0458E000, 0x4823A670, 0x84F2003A, 0x00000934, 0x13058189,
  0xB0885C22, 0x2629C3E1, 0x834CA251, 0x901CE4B1, 0xF4964650, 0x1BE270F8, 0x8E1F2800,
  0xE4C72001, 0x351E9445, 0x00096886, 0x0012CC01, 0x88680090, 0x025509B5, 0x857C7D30,
  0x412C60A9, 0xC017541E, 0x678003DC, 0x6000921B, 0xF203E800, 0x04B04B61, 0x5BC002ED,
  0x02CB61A4, 0x35526D30, 0xC220D301, 0x06410C99, 0xE476E8C1, 0x2747004E, 0x98F9FC3E,
  0x3C87C723, 0x7A6CAF25, 0x8F5364B4, 0x6D4E7F3F, 0x15260079, 0x52907893, 0xA6585165,
  0x830FC4C2, 0xC00A1C5E, 0x6D3B48C9, 0xCC853EE1, 0xA1502B74, 0xE6E21F26, 0x480EF1E9,
  0x028B3F9E, 0xF9B1B3A8, 0x6600D1C3, 0xBAFC3EB4, 0x26D9EFE6, 0xAE1C5F6D, 0xA6D1F55B,
  0xF5C36582, 0x44F78438, 0x9B331794, 0x40198A6C, 0x93478C72, 0x1209CFBA, 0x09E98C7A,
  0x0D8EFA69, 0x0076A3DC, 0xDBB495DC, 0xC6D5FB77, 0xA56F43DB, 0x2243D187, 0x47D44761,
  0xD1C4ADC8, 0x55452A45, 0x21F86ADF, 0x0E7F1D66, 0x6E5DB81A, 0x9BD77A02, 0x47891760,
  0x15B9159B, 0xCA7CDC77, 0x85D96731, 0x10155154, 0x00000000
};

/* Constant values used in this 'C' module only. */
static const XRect _Const0000 = {{ 0, 0 }, { 960, 480 }};
static const XRect _Const0001 = {{ 0, 60 }, { 0, 60 }};
static const XRect _Const0002 = {{ 0, 60 }, { 960, 92 }};
static const XPoint _Const0003 = { 960, 480 };
static const XStringRes _Const0004 = { _StringsDefault0, 0x0002 };
static const XRect _Const0005 = {{ 116, 76 }, { 336, 236 }};
static const XRect _Const0006 = {{ 370, 76 }, { 590, 236 }};
static const XRect _Const0007 = {{ 622, 76 }, { 842, 236 }};
static const XRect _Const0008 = {{ 738, 280 }, { 938, 340 }};
static const XRect _Const0009 = {{ 0, 0 }, { 960, 360 }};
static const XRect _Const000A = {{ 0, 0 }, { 960, 64 }};
static const XRect _Const000B = {{ 65, 95 }, { 323, 157 }};
static const XRect _Const000C = {{ 351, 95 }, { 609, 157 }};
static const XRect _Const000D = {{ 637, 95 }, { 895, 157 }};
static const XRect _Const000E = {{ 65, 190 }, { 323, 252 }};
static const XRect _Const000F = {{ 351, 190 }, { 609, 252 }};
static const XRect _Const0010 = {{ 637, 190 }, { 895, 252 }};
static const XRect _Const0011 = {{ 400, 107 }, { 564, 241 }};
static const XRect _Const0012 = {{ 361, 280 }, { 601, 288 }};
static const XRect _Const0013 = {{ 542, 0 }, { 960, 360 }};
static const XRect _Const0014 = {{ 590, 36 }, { 814, 340 }};
static const XRect _Const0015 = {{ 452, 0 }, { 960, 360 }};
static const XRect _Const0016 = {{ 452, 0 }, { 864, 360 }};
static const XRect _Const0017 = {{ 868, 36 }, { 932, 100 }};
static const XRect _Const0018 = {{ 868, 116 }, { 932, 180 }};
static const XRect _Const0019 = {{ 817, 281 }, { 937, 341 }};
static const XRect _Const001A = {{ 118, 72 }, { 338, 232 }};
static const XRect _Const001B = {{ 370, 72 }, { 590, 232 }};
static const XRect _Const001C = {{ 622, 72 }, { 842, 232 }};
static const XRect _Const001D = {{ 24, 260 }, { 345, 341 }};
static const XRect _Const001E = {{ 370, 260 }, { 588, 341 }};
static const XPoint _Const001F = { 0, 0 };
static const XPoint _Const0020 = { 960, 0 };
static const XPoint _Const0021 = { 960, 30 };
static const XPoint _Const0022 = { 0, 30 };
static const XRect _Const0023 = {{ 380, 13 }, { 580, 17 }};
static const XStringRes _Const0024 = { _StringsDefault0, 0x001F };
static const XRect _Const0025 = {{ 0, 0 }, { 960, 32 }};
static const XRect _Const0026 = {{ 24, 0 }, { 380, 32 }};
static const XRect _Const0027 = {{ 884, 0 }, { 936, 32 }};
static const XRect _Const0028 = {{ 780, 0 }, { 884, 32 }};
static const XRect _Const0029 = {{ 852, 0 }, { 884, 32 }};
static const XPoint _Const002A = { 0, 2 };
static const XRect _Const002B = {{ 814, 0 }, { 838, 32 }};
static const XStringRes _Const002C = { _StringsDefault0, 0x0043 };
static const XRect _Const002D = {{ 202, 82 }, { 759, 294 }};
static const XRect _Const002E = {{ 0, 32 }, { 960, 64 }};
static const XRect _Const002F = {{ 24, 280 }, { 144, 340 }};
static const XRect _Const0030 = {{ 24, 134 }, { 936, 260 }};
static const XRect _Const0031 = {{ 24, 88 }, { 224, 118 }};
static const XRect _Const0032 = {{ 60, 161 }, { 132, 233 }};
static const XRect _Const0033 = {{ 156, 161 }, { 228, 233 }};
static const XRect _Const0034 = {{ 252, 161 }, { 324, 233 }};
static const XRect _Const0035 = {{ 348, 161 }, { 420, 233 }};
static const XRect _Const0036 = {{ 444, 161 }, { 516, 233 }};
static const XRect _Const0037 = {{ 540, 161 }, { 612, 233 }};
static const XRect _Const0038 = {{ 636, 161 }, { 708, 233 }};
static const XRect _Const0039 = {{ 732, 161 }, { 804, 233 }};
static const XRect _Const003A = {{ 828, 161 }, { 900, 233 }};
static const XRect _Const003B = {{ 777, 280 }, { 936, 340 }};
static const XRect _Const003C = {{ 226, 112 }, { 735, 188 }};
static const XRect _Const003D = {{ 226, 200 }, { 735, 276 }};
static const XRect _Const003E = {{ 93, 129 }, { 866, 255 }};
static const XRect _Const003F = {{ 93, 88 }, { 293, 118 }};
static const XRect _Const0040 = {{ 178, 168 }, { 778, 216 }};
static const XRect _Const0041 = {{ 134, 168 }, { 158, 216 }};
static const XRect _Const0042 = {{ 798, 168 }, { 822, 216 }};
static const XPoint _Const0043 = { 48, 48 };
static const XPoint _Const0044 = { 36, 36 };
static const XRect _Const0045 = {{ 343, 118 }, { 619, 280 }};
static const XRect _Const0046 = {{ 377, 118 }, { 528, 280 }};
static const XRect _Const0047 = {{ 528, 118 }, { 619, 280 }};
static const XRect _Const0048 = {{ 270, 78 }, { 689, 156 }};
static const XRect _Const0049 = {{ 609, 107 }, { 649, 127 }};
static const XRect _Const004A = {{ 289, 78 }, { 599, 156 }};
static const XRect _Const004B = {{ 270, 170 }, { 689, 340 }};
static const XRect _Const004C = {{ 290, 186 }, { 669, 216 }};
static const XRect _Const004D = {{ 289, 231 }, { 689, 340 }};
static const XStringRes _Const004E = { _StringsDefault0, 0x004B };
static const XStringRes _Const004F = { _StringsDefault0, 0x004F };
static const XStringRes _Const0050 = { _StringsDefault0, 0x0053 };
static const XStringRes _Const0051 = { _StringsDefault0, 0x0057 };
static const XStringRes _Const0052 = { _StringsDefault0, 0x0062 };
static const XStringRes _Const0053 = { _StringsDefault0, 0x0066 };
static const XStringRes _Const0054 = { _StringsDefault0, 0x006A };
static const XRect _Const0055 = {{ 936, 100 }, { 944, 350 }};
static const XRect _Const0056 = {{ 216, 100 }, { 960, 360 }};
static const XRect _Const0057 = {{ 216, 100 }, { 745, 360 }};
static const XRect _Const0058 = {{ 216, 100 }, { 745, 168 }};
static const XRect _Const0059 = {{ 216, 188 }, { 745, 256 }};
static const XRect _Const005A = {{ 216, 276 }, { 745, 344 }};
static const XRect _Const005B = {{ 216, 364 }, { 745, 432 }};
static const XRect _Const005C = {{ 216, 452 }, { 745, 520 }};
static const XRect _Const005D = {{ 216, 540 }, { 745, 608 }};
static const XRect _Const005E = {{ 216, 628 }, { 745, 696 }};
static const XRect _Const005F = {{ 0, 0 }, { 690, 304 }};
static const XRect _Const0060 = {{ 24, 24 }, { 666, 60 }};
static const XRect _Const0061 = {{ 24, 224 }, { 160, 284 }};
static const XStringRes _Const0062 = { _StringsDefault0, 0x006F };
static const XRect _Const0063 = {{ 24, 83 }, { 210, 193 }};
static const XRect _Const0064 = {{ 235, 83 }, { 421, 193 }};
static const XRect _Const0065 = {{ 446, 83 }, { 632, 193 }};
static const XRect _Const0066 = {{ 0, 0 }, { 210, 162 }};
static const XRect _Const0067 = {{ 11, 19 }, { 199, 73 }};
static const XRect _Const0068 = {{ 11, 89 }, { 199, 143 }};
static const XPoint _Const0069 = { 210, 0 };
static const XPoint _Const006A = { 210, 162 };
static const XPoint _Const006B = { 0, 162 };
static const XRect _Const006C = {{ 290, 107 }, { 670, 243 }};
static const XRect _Const006D = {{ 512, 253 }, { 670, 313 }};
static const XRect _Const006E = {{ 290, 253 }, { 448, 313 }};
static const XRect _Const006F = {{ 290, 136 }, { 406, 224 }};
static const XRect _Const0070 = {{ 422, 136 }, { 538, 224 }};
static const XRect _Const0071 = {{ 554, 136 }, { 670, 224 }};
static const XRect _Const0072 = {{ 70, 60 }, { 415, 300 }};
static const XRect _Const0073 = {{ 111, 60 }, { 456, 300 }};
static const XRect _Const0074 = {{ 205, 55 }, { 755, 305 }};
static const XRect _Const0075 = {{ 250, 73 }, { 282, 109 }};
static const XRect _Const0076 = {{ 292, 75 }, { 720, 135 }};
static const XStringRes _Const0077 = { _StringsDefault0, 0x0095 };
static const XRect _Const0078 = {{ 205, 107 }, { 363, 265 }};
static const XRect _Const0079 = {{ 250, 107 }, { 710, 265 }};
static const XRect _Const007A = {{ 251, 107 }, { 643, 265 }};
static const XRect _Const007B = {{ 251, 257 }, { 721, 287 }};
static const XRect _Const007C = {{ 653, 207 }, { 733, 287 }};
static const XRect _Const007D = {{ 373, 107 }, { 643, 265 }};
static const XRect _Const007E = {{ 250, 75 }, { 720, 115 }};
static const XRect _Const007F = {{ 250, 115 }, { 710, 265 }};
static const XRect _Const0080 = {{ 703, 67 }, { 735, 99 }};
static const XRect _Const0081 = {{ 246, 27 }, { 714, 333 }};
static const XRect _Const0082 = {{ 256, 47 }, { 704, 107 }};
static const XRect _Const0083 = {{ 256, 107 }, { 704, 257 }};
static const XStringRes _Const0084 = { _StringsDefault0, 0x009C };
static const XStringRes _Const0085 = { _StringsDefault0, 0x00C8 };
static const XStringRes _Const0086 = { _StringsDefault0, 0x00FB };
static const XStringRes _Const0087 = { _StringsDefault0, 0x012C };
static const XPoint _Const0088 = { 960, 360 };
static const XPoint _Const0089 = { 0, 360 };
static const XRect _Const008A = {{ 200, 100 }, { 760, 334 }};
static const XRect _Const008B = {{ 159, 93 }, { 800, 340 }};
static const XRect _Const008C = {{ 240, 113 }, { 280, 133 }};
static const XRect _Const008D = {{ 183, 104 }, { 240, 138 }};
static const XRect _Const008E = {{ 183, 140 }, { 409, 194 }};
static const XRect _Const008F = {{ 265, 204 }, { 384, 323 }};
static const XRect _Const0090 = {{ 274, 213 }, { 374, 313 }};
static const XRect _Const0091 = {{ 452, 104 }, { 764, 138 }};
static const XRect _Const0092 = {{ 452, 153 }, { 774, 323 }};
static const XRect _Const0093 = {{ 580, 126 }, { 735, 176 }};
static const XRect _Const0094 = {{ 224, 124 }, { 278, 178 }};
static const XRect _Const0095 = {{ 298, 125 }, { 560, 152 }};
static const XRect _Const0096 = {{ 298, 154 }, { 560, 178 }};
static const XRect _Const0097 = {{ 224, 202 }, { 735, 310 }};
static const XRect _Const0098 = {{ 220, 100 }, { 740, 360 }};
static const XRect _Const0099 = {{ 220, 100 }, { 740, 457 }};
static const XRect _Const009A = {{ 220, 100 }, { 960, 360 }};
static const XRect _Const009B = {{ 255, 124 }, { 702, 162 }};
static const XRect _Const009C = {{ 255, 178 }, { 702, 216 }};
static const XRect _Const009D = {{ 255, 232 }, { 702, 270 }};
static const XRect _Const009E = {{ 255, 286 }, { 702, 324 }};
static const XRect _Const009F = {{ 255, 340 }, { 702, 378 }};
static const XRect _Const00A0 = {{ 255, 394 }, { 702, 432 }};
static const XRect _Const00A1 = {{ 0, 0 }, { 312, 44 }};
static const XRect _Const00A2 = {{ 32, 0 }, { 248, 44 }};
static const XRect _Const00A3 = {{ 0, -1 }, { 24, 43 }};
static const XRect _Const00A4 = {{ 248, 0 }, { 272, 44 }};
static const XRect _Const00A5 = {{ 288, 0 }, { 312, 44 }};
static const XPoint _Const00A6 = { 0, 44 };
static const XPoint _Const00A7 = { 312, 44 };
static const XPoint _Const00A8 = { 312, 0 };
static const XRect _Const00A9 = {{ 498, 0 }, { 960, 360 }};
static const XRect _Const00AA = {{ 518, 20 }, { 564, 66 }};
static const XRect _Const00AB = {{ 498, 20 }, { 960, 66 }};
static const XRect _Const00AC = {{ 948, 76 }, { 952, 350 }};
static const XRect _Const00AD = {{ 518, 76 }, { 960, 360 }};
static const XRect _Const00AE = {{ 518, 76 }, { 940, 360 }};
static const XRect _Const00AF = {{ 518, 114 }, { 940, 152 }};
static const XRect _Const00B0 = {{ 518, 168 }, { 940, 206 }};
static const XRect _Const00B1 = {{ 518, 222 }, { 940, 260 }};
static const XRect _Const00B2 = {{ 518, 276 }, { 940, 314 }};
static const XRect _Const00B3 = {{ 518, 330 }, { 940, 368 }};
static const XRect _Const00B4 = {{ 518, 384 }, { 940, 422 }};

/* Initializer for the class 'Application::Application' */
void ApplicationApplication__Init( ApplicationApplication _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreRoot__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationApplication );

  /* ... then construct all embedded objects */
  ViewsRectangle__Init( &_this->Background, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->ContentBackground, &_this->_.XObject, 0 );
  NavigationContainer__Init( &_this->PageContainer, &_this->_.XObject, 0 );
  ApplicationSettingsContainer__Init( &_this->SettingsContainer, &_this->_.XObject, 0 );
  NavigationContainer__Init( &_this->SettingsPageContainer, &_this->_.XObject, 0 );
  ApplicationStatusBar__Init( &_this->StatusBar, &_this->_.XObject, 0 );
  ApplicationPopupContainer__Init( &_this->PopupContainer, &_this->_.XObject, 0 );
  ApplicationPopupContainer__Init( &_this->NotificationContainer, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationApplication );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0000 );
  ViewsRectangle_OnSetColor( &_this->Background, ResBlack );
  CoreRectView__OnSetBounds( &_this->ContentBackground, _Const0001 );
  ViewsRectangle_OnSetColor( &_this->ContentBackground, ResPrimaryContainer );
  CoreRectView__OnSetBounds( &_this->PageContainer, _Const0001 );
  CoreRectView__OnSetBounds( &_this->SettingsContainer, _Const0001 );
  CoreRectView__OnSetBounds( &_this->SettingsPageContainer, _Const0001 );
  CoreRectView__OnSetBounds( &_this->StatusBar, _Const0002 );
  CoreRectView__OnSetBounds( &_this->PopupContainer, _Const0001 );
  CoreRectView__OnSetBounds( &_this->NotificationContainer, _Const0001 );
  ApplicationPopupContainer_OnSetScrimColor( &_this->NotificationContainer, ResOverlay );
  CoreGroup__Add( _this, ((CoreView)&_this->Background ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ContentBackground ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->PageContainer ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->SettingsContainer ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->SettingsPageContainer ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->StatusBar ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->PopupContainer ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->NotificationContainer ), 0 );
  _this->Device = EwGetAutoObject( &DeviceDevice, DeviceDeviceClass );
  _this->Helper = EwGetAutoObject( &ToolsHelper, ToolsHelperCollection );
  _this->PageNavigator = EwGetAutoObject( &NavigationPageNavigator, NavigationNavigatorClass );
  _this->SettingsNavigator = EwGetAutoObject( &ApplicationSettingsNavigator, ApplicationSettingsNavigatorClass );
  _this->PopupNavigator = ((NavigationNavigatorClass)EwGetAutoObject( &ApplicationPopupNavigator, 
  ApplicationPopupNavigatorClass ));
  _this->NotificationNavigator = EwGetAutoObject( &ApplicationNotificationNavigator, 
  ApplicationPopupNavigatorClass );

  /* Call the user defined constructor */
  ApplicationApplication_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::Application' */
void ApplicationApplication__ReInit( ApplicationApplication _this )
{
  /* At first re-initialize the super class ... */
  CoreRoot__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsRectangle__ReInit( &_this->Background );
  ViewsRectangle__ReInit( &_this->ContentBackground );
  NavigationContainer__ReInit( &_this->PageContainer );
  ApplicationSettingsContainer__ReInit( &_this->SettingsContainer );
  NavigationContainer__ReInit( &_this->SettingsPageContainer );
  ApplicationStatusBar__ReInit( &_this->StatusBar );
  ApplicationPopupContainer__ReInit( &_this->PopupContainer );
  ApplicationPopupContainer__ReInit( &_this->NotificationContainer );
}

/* Finalizer method for the class 'Application::Application' */
void ApplicationApplication__Done( ApplicationApplication _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreRoot );

  /* Finalize all embedded objects */
  ViewsRectangle__Done( &_this->Background );
  ViewsRectangle__Done( &_this->ContentBackground );
  NavigationContainer__Done( &_this->PageContainer );
  ApplicationSettingsContainer__Done( &_this->SettingsContainer );
  NavigationContainer__Done( &_this->SettingsPageContainer );
  ApplicationStatusBar__Done( &_this->StatusBar );
  ApplicationPopupContainer__Done( &_this->PopupContainer );
  ApplicationPopupContainer__Done( &_this->NotificationContainer );

  /* Don't forget to deinitialize the super class ... */
  CoreRoot__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationApplication_Init( ApplicationApplication _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  CoreRectView__OnSetBounds( &_this->Background, EwSetRectSize( _this->Background.Super1.Bounds, 
  _Const0003 ));
  CoreRectView__OnSetBounds( &_this->ContentBackground, EwSetRectSize( _this->ContentBackground.Super1.Bounds, 
  NavigationPageSize ));
  CoreRectView__OnSetBounds( &_this->PageContainer, EwSetRectSize( _this->PageContainer.Super2.Bounds, 
  NavigationPageSize ));
  CoreRectView__OnSetBounds( &_this->SettingsContainer, EwSetRectSize( _this->SettingsContainer.Super3.Bounds, 
  NavigationPageSize ));
  CoreRectView__OnSetBounds( &_this->SettingsPageContainer, EwSetRectSize( _this->SettingsPageContainer.Super2.Bounds, 
  NavigationPageSize ));
  CoreRectView__OnSetBounds( &_this->PopupContainer, EwSetRectSize( _this->PopupContainer.Super3.Bounds, 
  NavigationPageSize ));
  CoreRectView__OnSetBounds( &_this->NotificationContainer, EwSetRectSize( _this->NotificationContainer.Super3.Bounds, 
  NavigationPageSize ));
  _this->PageNavigator->Container = &_this->PageContainer;
  _this->SettingsNavigator->Super1.Container = &_this->SettingsPageContainer;
  _this->PopupNavigator->Container = ((NavigationContainer)&_this->PopupContainer );
  _this->NotificationNavigator->Super1.Container = ((NavigationContainer)&_this->NotificationContainer );
  EwAttachRefObserver( EwNewSlot( _this, ApplicationApplication_updatePage ), EwNewRef( 
    EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetCurrentPage, 
    DeviceDeviceClass_OnSetCurrentPage ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationApplication_updatePage ), ((XObject)_this ));
  EwAttachRefObserver( EwNewSlot( _this, ApplicationApplication_updateSettings ), 
    EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetCurrentSettings, 
    DeviceDeviceClass_OnSetCurrentSettings ), 0 );
  EwAttachRefObserver( EwNewSlot( _this, ApplicationApplication_updateSettings ), 
    EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetCurrentSubSettings, 
    DeviceDeviceClass_OnSetCurrentSubSettings ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationApplication_updateSettings ), ((XObject)_this ));
  EwAttachRefObserver( EwNewSlot( _this, ApplicationApplication_onInfusionState ), 
    EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetInfusionState, 
    DeviceDeviceClass_OnSetInfusionState ), 0 );
  EwAttachRefObserver( EwNewSlot( _this, ApplicationApplication_onInfusionState ), 
    EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetInStopping, 
    DeviceDeviceClass_OnSetInStopping ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationApplication_onInfusionState ), ((XObject)_this ));
  EwAttachRefObserver( EwNewSlot( _this, ApplicationApplication_onNotification ), 
    EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetNotificationId, 
    DeviceDeviceClass_OnSetNotificationId ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationApplication_onNotification ), ((XObject)_this ));
}

/* 'C' function for method : 'Application::Application.updatePage()' */
void ApplicationApplication_updatePage( ApplicationApplication _this, XObject sender )
{
  XClass pageClass;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  pageClass = ApplicationApplication_getPageClass( _this, (XEnum)EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass )->CurrentPage );

  if ( pageClass == 0 )
    return;

  NavigationNavigatorClass_OpenPage( _this->PageNavigator, EwCastObject( EwNewObjectIndirect( 
  pageClass, 0 ), NavigationPage ));
  CoreGroup_OnSetVisible((CoreGroup)&_this->StatusBar, (XBool)( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass )->CurrentPage != 1 ));
}

/* 'C' function for method : 'Application::Application.getPageClass()' */
XClass ApplicationApplication_getPageClass( ApplicationApplication _this, XEnum 
  aPageType )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  switch ( aPageType )
  {
    case DevicePageTypeBoot :
      return EW_CLASS( ApplicationBoot );

    case DevicePageTypeHome :
      return EW_CLASS( ApplicationHome );

    case DevicePageTypeInfusionRunning :
      return EW_CLASS( ApplicationInfusionRunning );

    default : 
    {
      EwTrace( "%s%e", EwLoadString( &_Const0004 ), aPageType );
      return 0;
    }
  }
}

/* 'C' function for method : 'Application::Application.updateSettings()' */
void ApplicationApplication_updateSettings( ApplicationApplication _this, XObject 
  sender )
{
  XClass pageClass;
  XClass subPageClass;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if (( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->CurrentSettings == 
      0 ) || ( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->CurrentSettings 
      == 1 ))
  {
    if ( ApplicationSettingsNavigatorClass_GetCurrentSubPage( _this->SettingsNavigator ) 
        != 0 )
    {
      NavigationNavigatorClass__CloseCurrentPageWithTransition( _this->SettingsNavigator, 
      ((EffectsTransition)EwGetAutoObject( &ApplicationSlideRight, EffectsSlideTransition )), 
      0 );
      DeviceDeviceClass_OnSetCurrentSubSettings( EwGetAutoObject( &DeviceDevice, 
      DeviceDeviceClass ), 0 );
    }

    NavigationNavigatorClass__CloseCurrentPageWithTransition( _this->SettingsNavigator, 
    ((EffectsTransition)EwGetAutoObject( &ApplicationSlideRight, EffectsSlideTransition )), 
    0 );
    return;
  }

  pageClass = ApplicationApplication_getSettingsClass( _this, (XEnum)EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass )->CurrentSettings );

  if ( pageClass == 0 )
    return;

  subPageClass = 0;

  if ( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->CurrentSubSettings != 
      0 )
    subPageClass = ApplicationApplication_getSettingsClass( _this, (XEnum)EwGetAutoObject( 
    &DeviceDevice, DeviceDeviceClass )->CurrentSubSettings );

  if ( EwClassOf(((XObject)NavigationNavigatorClass_GetCurrentPage((NavigationNavigatorClass)_this->SettingsNavigator ))) 
      == pageClass )
  {
    if ( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->CurrentSubSettings 
        != 0 )
      ApplicationSettingsNavigatorClass_OpenSubPage( _this->SettingsNavigator, EwCastObject( 
      EwNewObjectIndirect( subPageClass, 0 ), NavigationPage ));
    else
      ApplicationSettingsNavigatorClass_CloseCurrentSubPage( _this->SettingsNavigator );
  }
  else
  {
    NavigationNavigatorClass_OpenPageWithTransition((NavigationNavigatorClass)_this->SettingsNavigator, 
    EwCastObject( EwNewObjectIndirect( pageClass, 0 ), NavigationPage ), 0, ((EffectsTransition)EwGetAutoObject( 
    &ApplicationSlideLeft, EffectsSlideTransition )), 0 );

    if ( subPageClass != 0 )
      ApplicationSettingsNavigatorClass_OpenSubPage( _this->SettingsNavigator, EwCastObject( 
      EwNewObjectIndirect( subPageClass, 0 ), NavigationPage ));
  }
}

/* 'C' function for method : 'Application::Application.getSettingsClass()' */
XClass ApplicationApplication_getSettingsClass( ApplicationApplication _this, XEnum 
  aSettingsPage )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  switch ( aSettingsPage )
  {
    case DeviceSettingsPageSettings :
      return EW_CLASS( ApplicationSettings );

    case DeviceSettingsPagePressure :
      return EW_CLASS( ApplicationPressureSettings );

    case DeviceSettingsPageAirBubbleDetector :
      return EW_CLASS( ApplicationAirBubbleDetector );

    case DeviceSettingsPageDisplay :
      return EW_CLASS( ApplicationDisplayAndBrightness );

    case DeviceSettingsPageBolusRate :
      return EW_CLASS( ApplicationBolusRateSettings );

    case DeviceSettingsPageKVO :
      return EW_CLASS( ApplicationKVOSettings );

    case DeviceSettingsPageGeneral :
      return EW_CLASS( ApplicationGeneralSettings );

    case DeviceSettingsPageWifi :
      return EW_CLASS( ApplicationWifiSettings );

    case DeviceSettingsPageAudioVolumeControl :
      return EW_CLASS( ApplicationAudioVolumeControl );

    case DeviceSettingsPageDateAndTime :
      return EW_CLASS( ApplicationDataAndTime );

    case DeviceSettingsPageLanguage :
      return EW_CLASS( ApplicationLanguage );

    case DeviceSettingsPageSoftwareUpdate :
      return EW_CLASS( ApplicationSoftwareUpdate );

    case DeviceSettingsPageAbout :
      return EW_CLASS( ApplicationAbout );

    case DeviceSettingsPageMaintenanceAndCalibration :
      return EW_CLASS( ApplicationMaintenanceAndCalibration );

    default : 
    {
      EwTrace( "%s%e", EwLoadString( &_Const0004 ), aSettingsPage );
      return 0;
    }
  }
}

/* 'C' function for method : 'Application::Application.onInfusionState()' */
void ApplicationApplication_onInfusionState( ApplicationApplication _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( sender );

  if ( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->BootProgress < 100 )
    return;

  if (( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->InfusionState == 5 ) 
      || (( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->InfusionState == 
      6 ) && EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->InStopping ))
    DeviceDeviceClass_OnSetCurrentPage( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
    4 );
  else
    DeviceDeviceClass_OnSetCurrentPage( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
    2 );
}

/* 'C' function for method : 'Application::Application.onNotification()' */
void ApplicationApplication_onNotification( ApplicationApplication _this, XObject 
  sender )
{
  XInt32 id;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  id = EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->NotificationId;

  if ( id != 0 )
  {
    ApplicationNotificationPopup popup = EwCastObject( ApplicationPopupNavigatorClass_GetCurrentPopup( 
      _this->NotificationNavigator ), ApplicationNotificationPopup );
    XEnum popupType = ApplicationApplication_getPopupType( _this, id );

    if (( popup == 0 ) || ( popup->Super1.Type != popupType ))
      popup = EwCastObject( ApplicationPopupNavigatorClass_OpenPopupByType( _this->NotificationNavigator, 
      ApplicationApplication_getPopupType( _this, id ), 0 ), ApplicationNotificationPopup );

    if ( popup != 0 )
      ApplicationNotificationPopup__OnSetNotificationId( popup, EwGetAutoObject( 
      &DeviceDevice, DeviceDeviceClass )->NotificationId );
  }
  else
    NavigationNavigatorClass_CloseCurrentPage((NavigationNavigatorClass)_this->NotificationNavigator );
}

/* 'C' function for method : 'Application::Application.getPopupType()' */
XEnum ApplicationApplication_getPopupType( ApplicationApplication _this, XInt32 
  aId )
{
  XEnum type;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  type = DeviceDeviceClass_GetNotificationType( EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass ), aId );

  if ( type == DeviceNotificationTypeError )
    return DevicePopupTypeError;

  return DevicePopupTypeInfo;
}

/* Variants derived from the class : 'Application::Application' */
EW_DEFINE_CLASS_VARIANTS( ApplicationApplication )
EW_END_OF_CLASS_VARIANTS( ApplicationApplication )

/* Virtual Method Table (VMT) for the class : 'Application::Application' */
EW_DEFINE_CLASS( ApplicationApplication, CoreRoot, Background, Device, _.VMT, _.VMT, 
                 _.VMT, _.VMT, "Application::Application" )
  CoreRectView_initLayoutContext,
  CoreRoot_GetRoot,
  CoreRoot_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreRoot_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreRoot_OnSetFocus,
  CoreRoot_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreRoot_DispatchEvent,
  CoreRoot_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreRoot_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ApplicationApplication )

/* Initializer for the class 'Application::Home' */
void ApplicationHome__Init( ApplicationHome _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationInfusionBasePage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationHome );

  /* ... then construct all embedded objects */
  ComponentsTile__Init( &_this->TileFlowRate, &_this->_.XObject, 0 );
  ComponentsTile__Init( &_this->TileVolume, &_this->_.XObject, 0 );
  ComponentsTileTime__Init( &_this->TileTime, &_this->_.XObject, 0 );
  ComponentsTextButton__Init( &_this->StartButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationHome );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( &_this->TileFlowRate, _Const0005 );
  ComponentsBaseTile_OnSetCaption((ComponentsBaseTile)&_this->TileFlowRate, EwLoadString( 
  &StringsFlowRate ));
  ComponentsBaseTile__OnSetUnit( &_this->TileFlowRate, EwLoadString( &StringsUnit_mLPerhour ));
  ComponentsBaseTile__OnSetResolution( &_this->TileFlowRate, -2 );
  ComponentsBaseTile_OnSetPrecision((ComponentsBaseTile)&_this->TileFlowRate, 2 );
  _this->TileFlowRate.MinValue = 0;
  _this->TileFlowRate.MaxValue = 120000;
  CoreRectView__OnSetBounds( &_this->TileVolume, _Const0006 );
  ComponentsBaseTile_OnSetCaption((ComponentsBaseTile)&_this->TileVolume, EwLoadString( 
  &StringsInfusionVolume ));
  ComponentsBaseTile__OnSetUnit( &_this->TileVolume, EwLoadString( &StringsUnit_mL ));
  ComponentsBaseTile__OnSetResolution( &_this->TileVolume, -2 );
  ComponentsBaseTile_OnSetPrecision((ComponentsBaseTile)&_this->TileVolume, 2 );
  _this->TileVolume.MinValue = 1;
  _this->TileVolume.MaxValue = 999900;
  CoreRectView__OnSetBounds( &_this->TileTime, _Const0007 );
  ComponentsBaseTile_OnSetCaption((ComponentsBaseTile)&_this->TileTime, EwLoadString( 
  &StringsInfusionTime ));
  CoreRectView__OnSetBounds( &_this->StartButton, _Const0008 );
  ComponentsTextButton__OnSetCaption( &_this->StartButton, EwLoadString( &StringsSTARTINFUSION ));
  CoreGroup__Add( _this, ((CoreView)&_this->TileFlowRate ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->TileVolume ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->TileTime ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->StartButton ), 0 );
  _this->TileFlowRate.Super2.OnActivate = EwNewSlot( _this, ApplicationInfusionBasePage_onEdit );
  ComponentsBaseTile__OnSetOutlet( &_this->TileFlowRate, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetFlowRate, DeviceDeviceClass_OnSetFlowRate ));
  ComponentsTile_OnSetIcon( &_this->TileFlowRate, EwLoadResource( &Rescircle_arrow_left, 
  ResourcesBitmap ));
  _this->TileFlowRate.EditIcon = EwLoadResource( &Rescircle_arrow_left_36px, ResourcesBitmap );
  _this->TileVolume.Super2.OnActivate = EwNewSlot( _this, ApplicationInfusionBasePage_onEdit );
  ComponentsBaseTile__OnSetOutlet( &_this->TileVolume, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetInfusionVolume, DeviceDeviceClass_OnSetInfusionVolume ));
  ComponentsTile_OnSetIcon( &_this->TileVolume, EwLoadResource( &Resdroplets, ResourcesBitmap ));
  _this->TileVolume.EditIcon = EwLoadResource( &Resdroplets_36px, ResourcesBitmap );
  _this->TileTime.Super3.OnActivate = EwNewSlot( _this, ApplicationInfusionBasePage_onEdit );
  ComponentsBaseTile__OnSetOutlet( &_this->TileTime, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetInfusionTime, DeviceDeviceClass_OnSetInfusionTime ));
  ComponentsTile_OnSetIcon((ComponentsTile)&_this->TileTime, EwLoadResource( &Restimer, 
  ResourcesBitmap ));
  _this->TileTime.Super1.EditIcon = EwLoadResource( &Restimer_36px, ResourcesBitmap );
  _this->StartButton.Super1.OnActivate = EwNewSlot( _this, ApplicationHome_startInfusion );

  /* Call the user defined constructor */
  ApplicationHome_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::Home' */
void ApplicationHome__ReInit( ApplicationHome _this )
{
  /* At first re-initialize the super class ... */
  ApplicationInfusionBasePage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsTile__ReInit( &_this->TileFlowRate );
  ComponentsTile__ReInit( &_this->TileVolume );
  ComponentsTileTime__ReInit( &_this->TileTime );
  ComponentsTextButton__ReInit( &_this->StartButton );
}

/* Finalizer method for the class 'Application::Home' */
void ApplicationHome__Done( ApplicationHome _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationInfusionBasePage );

  /* Finalize all embedded objects */
  ComponentsTile__Done( &_this->TileFlowRate );
  ComponentsTile__Done( &_this->TileVolume );
  ComponentsTileTime__Done( &_this->TileTime );
  ComponentsTextButton__Done( &_this->StartButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationInfusionBasePage__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationHome_Init( ApplicationHome _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  EwAttachRefObserver( EwNewSlot( _this, ApplicationHome_onInfusionTime ), EwNewRef( 
    EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetInfusionTime, 
    DeviceDeviceClass_OnSetInfusionTime ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationHome_onInfusionTime ), ((XObject)_this ));
}

/* 'C' function for method : 'Application::Home.OnSetopacity()' */
void ApplicationHome_OnSetopacity( ApplicationHome _this, XInt32 value )
{
  ApplicationInfusionBasePage_OnSetopacity((ApplicationInfusionBasePage)_this, value );

  if ( _this->Super1.editTile == 0 )
    return;

  if ( &_this->TileFlowRate != _this->Super1.editTile->ViewTile )
    CoreGroup__OnSetOpacity( &_this->TileFlowRate, value );

  if ( &_this->TileVolume != _this->Super1.editTile->ViewTile )
    CoreGroup__OnSetOpacity( &_this->TileVolume, value );

  if (((ComponentsTile)&_this->TileTime ) != _this->Super1.editTile->ViewTile )
    CoreGroup__OnSetOpacity( &_this->TileTime, value );
}

/* 'C' function for method : 'Application::Home.startInfusion()' */
void ApplicationHome_startInfusion( ApplicationHome _this, XObject sender )
{
  ApplicationStartInfusionConfirmPopup confirmPopup;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  confirmPopup = EwNewObject( ApplicationStartInfusionConfirmPopup, 0 );

  if ( confirmPopup == 0 )
    return;

  confirmPopup->Super1.OnConfirm = EwNewSlot( _this, ApplicationHome_doStartInfusion );
  ApplicationPopupNavigatorClass_OpenPopup( EwGetAutoObject( &ApplicationPopupNavigator, 
  ApplicationPopupNavigatorClass ), ((ApplicationPopup)confirmPopup ), 0 );
}

/* 'C' function for method : 'Application::Home.onInfusionTime()' */
void ApplicationHome_onInfusionTime( ApplicationHome _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_OnSetEnabled((CoreGroup)&_this->StartButton, (XBool)( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass )->InfusionTime > 0 ));
}

/* 'C' function for method : 'Application::Home.doStartInfusion()' */
void ApplicationHome_doStartInfusion( ApplicationHome _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( sender );

  DeviceDeviceClass_StartInfusion( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ));
}

/* Variants derived from the class : 'Application::Home' */
EW_DEFINE_CLASS_VARIANTS( ApplicationHome )
EW_END_OF_CLASS_VARIANTS( ApplicationHome )

/* Virtual Method Table (VMT) for the class : 'Application::Home' */
EW_DEFINE_CLASS( ApplicationHome, ApplicationInfusionBasePage, TileFlowRate, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Application::Home" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationHome_OnSetopacity,
EW_END_OF_CLASS( ApplicationHome )

/* Initializer for the class 'Application::Settings' */
void ApplicationSettings__Init( ApplicationSettings _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  NavigationPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationSettings );

  /* ... then construct all embedded objects */
  ViewsRectangle__Init( &_this->Scrim, &_this->_.XObject, 0 );
  ComponentsHeader__Init( &_this->Header, &_this->_.XObject, 0 );
  ComponentsSettingsButton__Init( &_this->PressureButton, &_this->_.XObject, 0 );
  ComponentsSettingsButton__Init( &_this->AirBubbleDetectorButton, &_this->_.XObject, 0 );
  ComponentsSettingsButton__Init( &_this->DisplayButton, &_this->_.XObject, 0 );
  ComponentsSettingsButton__Init( &_this->BolusRateButton, &_this->_.XObject, 0 );
  ComponentsSettingsButton__Init( &_this->KVOButton, &_this->_.XObject, 0 );
  ComponentsSettingsButton__Init( &_this->GeneralButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationSettings );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsSettings ));
  CoreRectView__OnSetBounds( &_this->Scrim, _Const0009 );
  ViewsRectangle_OnSetColor( &_this->Scrim, ResOverlayOpaque );
  CoreRectView__OnSetBounds( &_this->Header, _Const000A );
  ComponentsHeader_OnSetCaption( &_this->Header, EwLoadString( &StringsSettings ));
  ComponentsHeader_OnSetColor( &_this->Header, ResOnSecondary );
  CoreRectView__OnSetBounds( &_this->PressureButton, _Const000B );
  ComponentsTextButton__OnSetCaption( &_this->PressureButton, EwLoadString( &StringsPressure ));
  _this->PressureButton.SettingsPage = DeviceSettingsPagePressure;
  CoreRectView__OnSetBounds( &_this->AirBubbleDetectorButton, _Const000C );
  ComponentsTextButton__OnSetCaption( &_this->AirBubbleDetectorButton, EwLoadString( 
  &StringsAirBubbleDetector ));
  _this->AirBubbleDetectorButton.SettingsPage = DeviceSettingsPageAirBubbleDetector;
  CoreRectView__OnSetBounds( &_this->DisplayButton, _Const000D );
  ComponentsTextButton__OnSetCaption( &_this->DisplayButton, EwLoadString( &StringsDisplayAndBrightness ));
  _this->DisplayButton.SettingsPage = DeviceSettingsPageDisplay;
  CoreRectView__OnSetBounds( &_this->BolusRateButton, _Const000E );
  ComponentsTextButton__OnSetCaption( &_this->BolusRateButton, EwLoadString( &StringsBolusSettings ));
  _this->BolusRateButton.SettingsPage = DeviceSettingsPageBolusRate;
  CoreRectView__OnSetBounds( &_this->KVOButton, _Const000F );
  ComponentsTextButton__OnSetCaption( &_this->KVOButton, EwLoadString( &StringsKVOSettings ));
  _this->KVOButton.SettingsPage = DeviceSettingsPageKVO;
  CoreRectView__OnSetBounds( &_this->GeneralButton, _Const0010 );
  ComponentsTextButton__OnSetCaption( &_this->GeneralButton, EwLoadString( &StringsGeneral ));
  _this->GeneralButton.SettingsPage = DeviceSettingsPageGeneral;
  CoreGroup__Add( _this, ((CoreView)&_this->Scrim ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Header ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->PressureButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->AirBubbleDetectorButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->DisplayButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->BolusRateButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KVOButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->GeneralButton ), 0 );
  ComponentsHeader_OnSetIcon( &_this->Header, EwLoadResource( &Ressettings_32px, 
  ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->PressureButton, 
  EwLoadResource( &Resgauge_32px, ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->AirBubbleDetectorButton, 
  EwLoadResource( &Resbubbles_32px, ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->DisplayButton, 
  EwLoadResource( &Ressun_32px, ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->BolusRateButton, 
  EwLoadResource( &Reschevrons_left_32px, ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->KVOButton, 
  EwLoadResource( &Resspline_32px, ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->GeneralButton, 
  EwLoadResource( &Ressettings_32px, ResourcesBitmap ));
}

/* Re-Initializer for the class 'Application::Settings' */
void ApplicationSettings__ReInit( ApplicationSettings _this )
{
  /* At first re-initialize the super class ... */
  NavigationPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsRectangle__ReInit( &_this->Scrim );
  ComponentsHeader__ReInit( &_this->Header );
  ComponentsSettingsButton__ReInit( &_this->PressureButton );
  ComponentsSettingsButton__ReInit( &_this->AirBubbleDetectorButton );
  ComponentsSettingsButton__ReInit( &_this->DisplayButton );
  ComponentsSettingsButton__ReInit( &_this->BolusRateButton );
  ComponentsSettingsButton__ReInit( &_this->KVOButton );
  ComponentsSettingsButton__ReInit( &_this->GeneralButton );
}

/* Finalizer method for the class 'Application::Settings' */
void ApplicationSettings__Done( ApplicationSettings _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( NavigationPage );

  /* Finalize all embedded objects */
  ViewsRectangle__Done( &_this->Scrim );
  ComponentsHeader__Done( &_this->Header );
  ComponentsSettingsButton__Done( &_this->PressureButton );
  ComponentsSettingsButton__Done( &_this->AirBubbleDetectorButton );
  ComponentsSettingsButton__Done( &_this->DisplayButton );
  ComponentsSettingsButton__Done( &_this->BolusRateButton );
  ComponentsSettingsButton__Done( &_this->KVOButton );
  ComponentsSettingsButton__Done( &_this->GeneralButton );

  /* Don't forget to deinitialize the super class ... */
  NavigationPage__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Application::Settings' */
EW_DEFINE_CLASS_VARIANTS( ApplicationSettings )
EW_END_OF_CLASS_VARIANTS( ApplicationSettings )

/* Virtual Method Table (VMT) for the class : 'Application::Settings' */
EW_DEFINE_CLASS( ApplicationSettings, NavigationPage, Scrim, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, "Application::Settings" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
EW_END_OF_CLASS( ApplicationSettings )

/* Initializer for the class 'Application::Boot' */
void ApplicationBoot__Init( ApplicationBoot _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  NavigationPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationBoot );

  /* ... then construct all embedded objects */
  CoreTimer__Init( &_this->Timer, &_this->_.XObject, 0 );
  ComponentsLogo__Init( &_this->LogoImage, &_this->_.XObject, 0 );
  ComponentsProgressBar__Init( &_this->ProgressBar, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationBoot );

  /* ... and initialize objects, variables, properties, etc. */
  CoreTimer_OnSetPeriod( &_this->Timer, 0 );
  CoreTimer_OnSetBegin( &_this->Timer, 1000 );
  CoreTimer_OnSetEnabled( &_this->Timer, 0 );
  CoreRectView__OnSetBounds( &_this->LogoImage, _Const0011 );
  CoreRectView__OnSetBounds( &_this->ProgressBar, _Const0012 );
  CoreGroup__Add( _this, ((CoreView)&_this->LogoImage ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ProgressBar ), 0 );
  _this->Timer.OnTrigger = EwNewSlot( _this, ApplicationBoot_close );
  ComponentsHorzValueBar_OnSetOutlet((ComponentsHorzValueBar)&_this->ProgressBar, 
  EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetBootProgress, 
  DeviceDeviceClass_OnSetBootProgress ));

  /* Call the user defined constructor */
  ApplicationBoot_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::Boot' */
void ApplicationBoot__ReInit( ApplicationBoot _this )
{
  /* At first re-initialize the super class ... */
  NavigationPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreTimer__ReInit( &_this->Timer );
  ComponentsLogo__ReInit( &_this->LogoImage );
  ComponentsProgressBar__ReInit( &_this->ProgressBar );
}

/* Finalizer method for the class 'Application::Boot' */
void ApplicationBoot__Done( ApplicationBoot _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( NavigationPage );

  /* Finalize all embedded objects */
  CoreTimer__Done( &_this->Timer );
  ComponentsLogo__Done( &_this->LogoImage );
  ComponentsProgressBar__Done( &_this->ProgressBar );

  /* Don't forget to deinitialize the super class ... */
  NavigationPage__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationBoot_Init( ApplicationBoot _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  EwAttachRefObserver( EwNewSlot( _this, ApplicationBoot_onBootProgress ), EwNewRef( 
    EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetBootProgress, 
    DeviceDeviceClass_OnSetBootProgress ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationBoot_onBootProgress ), ((XObject)_this ));
}

/* 'C' function for method : 'Application::Boot.close()' */
void ApplicationBoot_close( ApplicationBoot _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  DeviceDeviceClass_OnSetCurrentPage( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  2 );
  CoreTimer_OnSetEnabled( &_this->Timer, 0 );
}

/* 'C' function for method : 'Application::Boot.onBootProgress()' */
void ApplicationBoot_onBootProgress( ApplicationBoot _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->BootProgress == 100 )
    EwPostSignal( EwNewSlot( _this, ApplicationBoot_close ), ((XObject)_this ));
}

/* Variants derived from the class : 'Application::Boot' */
EW_DEFINE_CLASS_VARIANTS( ApplicationBoot )
EW_END_OF_CLASS_VARIANTS( ApplicationBoot )

/* Virtual Method Table (VMT) for the class : 'Application::Boot' */
EW_DEFINE_CLASS( ApplicationBoot, NavigationPage, Timer, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "Application::Boot" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
EW_END_OF_CLASS( ApplicationBoot )

/* User defined auto object: 'Application::SlideLeft' */
EW_DEFINE_AUTOOBJECT( ApplicationSlideLeft, EffectsSlideTransition )

/* Initializer for the auto object 'Application::SlideLeft' */
void ApplicationSlideLeft__Init( EffectsSlideTransition _this )
{
  _this->Alignment = EffectsDialogAlignmentAlignHorzLeft | EffectsDialogAlignmentAlignVertCenter;
  _this->Direction = CoreDirectionLeft;
}

/* Re-Initializer for the auto object 'Application::SlideLeft' */
void ApplicationSlideLeft__ReInit( EffectsSlideTransition _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Application::SlideLeft' */
EW_DEFINE_AUTOOBJECT_VARIANTS( ApplicationSlideLeft )
EW_END_OF_AUTOOBJECT_VARIANTS( ApplicationSlideLeft )

/* Initializer for the class 'Application::Popup' */
void ApplicationPopup__Init( ApplicationPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  NavigationPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationPopup );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationPopup );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Type = DevicePopupTypeNone;
  _this->ScrimColor = ResOverlayOpaque;
}

/* Re-Initializer for the class 'Application::Popup' */
void ApplicationPopup__ReInit( ApplicationPopup _this )
{
  /* At first re-initialize the super class ... */
  NavigationPage__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Application::Popup' */
void ApplicationPopup__Done( ApplicationPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( NavigationPage );

  /* Don't forget to deinitialize the super class ... */
  NavigationPage__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Application::Popup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationPopup )

/* Virtual Method Table (VMT) for the class : 'Application::Popup' */
EW_DEFINE_CLASS( ApplicationPopup, NavigationPage, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "Application::Popup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
EW_END_OF_CLASS( ApplicationPopup )

/* Initializer for the class 'Application::NumKeyboardPopup' */
void ApplicationNumKeyboardPopup__Init( ApplicationNumKeyboardPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationInputPopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationNumKeyboardPopup );

  /* ... then construct all embedded objects */
  ComponentsNumKeyboard__Init( &_this->NumKeyboard, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationNumKeyboardPopup );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Super2.Type = DevicePopupTypeKeyboard;
  CoreRectView__OnSetBounds( &_this->Super1.Background, _Const0013 );
  CoreRectView__OnSetBounds( &_this->NumKeyboard, _Const0014 );
  CoreGroup__Add( _this, ((CoreView)&_this->NumKeyboard ), 0 );
}

/* Re-Initializer for the class 'Application::NumKeyboardPopup' */
void ApplicationNumKeyboardPopup__ReInit( ApplicationNumKeyboardPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationInputPopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsNumKeyboard__ReInit( &_this->NumKeyboard );
}

/* Finalizer method for the class 'Application::NumKeyboardPopup' */
void ApplicationNumKeyboardPopup__Done( ApplicationNumKeyboardPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationInputPopup );

  /* Finalize all embedded objects */
  ComponentsNumKeyboard__Done( &_this->NumKeyboard );

  /* Don't forget to deinitialize the super class ... */
  ApplicationInputPopup__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Application::NumKeyboardPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationNumKeyboardPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationNumKeyboardPopup )

/* Virtual Method Table (VMT) for the class : 'Application::NumKeyboardPopup' */
EW_DEFINE_CLASS( ApplicationNumKeyboardPopup, ApplicationInputPopup, NumKeyboard, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::NumKeyboardPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  ApplicationInputPopup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationInputPopup_OnSetOutlet,
EW_END_OF_CLASS( ApplicationNumKeyboardPopup )

/* User defined auto object: 'Application::SlideRight' */
EW_DEFINE_AUTOOBJECT( ApplicationSlideRight, EffectsSlideTransition )

/* Initializer for the auto object 'Application::SlideRight' */
void ApplicationSlideRight__Init( EffectsSlideTransition _this )
{
  _this->Alignment = EffectsDialogAlignmentAlignHorzRight | EffectsDialogAlignmentAlignVertCenter;
  _this->Direction = CoreDirectionRight;
}

/* Re-Initializer for the auto object 'Application::SlideRight' */
void ApplicationSlideRight__ReInit( EffectsSlideTransition _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Application::SlideRight' */
EW_DEFINE_AUTOOBJECT_VARIANTS( ApplicationSlideRight )
EW_END_OF_AUTOOBJECT_VARIANTS( ApplicationSlideRight )

/* Initializer for the class 'Application::TimerPickerPopup' */
void ApplicationTimerPickerPopup__Init( ApplicationTimerPickerPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationInputPopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationTimerPickerPopup );

  /* ... then construct all embedded objects */
  ComponentsTimePicker__Init( &_this->TimePicker, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationTimerPickerPopup );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Super2.Type = DevicePopupTypeValuePicker;
  CoreRectView__OnSetBounds( &_this->Super1.Background, _Const0015 );
  CoreRectView__OnSetBounds( &_this->TimePicker, _Const0016 );
  CoreGroup__Add( _this, ((CoreView)&_this->TimePicker ), 0 );
}

/* Re-Initializer for the class 'Application::TimerPickerPopup' */
void ApplicationTimerPickerPopup__ReInit( ApplicationTimerPickerPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationInputPopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsTimePicker__ReInit( &_this->TimePicker );
}

/* Finalizer method for the class 'Application::TimerPickerPopup' */
void ApplicationTimerPickerPopup__Done( ApplicationTimerPickerPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationInputPopup );

  /* Finalize all embedded objects */
  ComponentsTimePicker__Done( &_this->TimePicker );

  /* Don't forget to deinitialize the super class ... */
  ApplicationInputPopup__Done( &_this->_.Super );
}

/* The method UpdateViewState() is invoked automatically after the state of the 
   component has been changed. This method can be overridden and filled with logic 
   to ensure the visual aspect of the component does reflect its current state. 
   For example, the 'enabled' state of the component can affect its colors (disabled 
   components may appear pale). In this case the logic of the method should modify 
   the respective color properties accordingly to the current 'enabled' state. 
   The current state of the component is passed as a set in the parameter aState. 
   It reflects the very basic component state like its visibility or the ability 
   to react to user inputs. Beside this common state, the method can also involve 
   any other variables used in the component as long as they reflect its current 
   state. For example, the toggle switch component can take in account its toggle 
   state 'on' or 'off' and change accordingly the location of the slider, etc.
   Usually, this method will be invoked automatically by the framework. Optionally 
   you can request its invocation by using the method @InvalidateViewState(). */
void ApplicationTimerPickerPopup_UpdateViewState( ApplicationTimerPickerPopup _this, 
  XSet aState )
{
  ApplicationInputPopup_UpdateViewState((ApplicationInputPopup)_this, aState );
  ComponentsTimePicker_OnSetBgColor( &_this->TimePicker, _this->Super1.Background.Color );
}

/* 'C' function for method : 'Application::TimerPickerPopup.OnSetOutlet()' */
void ApplicationTimerPickerPopup_OnSetOutlet( ApplicationTimerPickerPopup _this, 
  XRef value )
{
  ApplicationInputPopup_OnSetOutlet((ApplicationInputPopup)_this, value );
  ComponentsTimePicker_OnSetOutlet( &_this->TimePicker, value );
}

/* Variants derived from the class : 'Application::TimerPickerPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationTimerPickerPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationTimerPickerPopup )

/* Virtual Method Table (VMT) for the class : 'Application::TimerPickerPopup' */
EW_DEFINE_CLASS( ApplicationTimerPickerPopup, ApplicationInputPopup, TimePicker, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::TimerPickerPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  ApplicationTimerPickerPopup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationTimerPickerPopup_OnSetOutlet,
EW_END_OF_CLASS( ApplicationTimerPickerPopup )

/* Initializer for the class 'Application::InputPopup' */
void ApplicationInputPopup__Init( ApplicationInputPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationPopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationInputPopup );

  /* ... then construct all embedded objects */
  ViewsRectangle__Init( &_this->Background, &_this->_.XObject, 0 );
  ComponentsKeyboardPopupButton__Init( &_this->OKButton, &_this->_.XObject, 0 );
  ComponentsKeyboardPopupButton__Init( &_this->CancelButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationInputPopup );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( &_this->Background, _Const0013 );
  ViewsRectangle_OnSetRadiusBL( &_this->Background, 20 );
  ViewsRectangle_OnSetRadiusTL( &_this->Background, 20 );
  CoreRectView__OnSetBounds( &_this->OKButton, _Const0017 );
  CoreRectView__OnSetBounds( &_this->CancelButton, _Const0018 );
  CoreGroup__Add( _this, ((CoreView)&_this->Background ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->OKButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->CancelButton ), 0 );
  _this->OKButton.Super3.OnActivate = EwNewSlot( _this, ApplicationInputPopup_onOK );
  ComponentsSpecialKeyButton_OnSetIcon((ComponentsSpecialKeyButton)&_this->OKButton, 
  EwLoadResource( &Rescheck_40px, ResourcesBitmap ));
  _this->CancelButton.Super3.OnActivate = EwNewSlot( _this, ApplicationInputPopup_onCancel );
  ComponentsSpecialKeyButton_OnSetIcon((ComponentsSpecialKeyButton)&_this->CancelButton, 
  EwLoadResource( &Resx_40px, ResourcesBitmap ));
}

/* Re-Initializer for the class 'Application::InputPopup' */
void ApplicationInputPopup__ReInit( ApplicationInputPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationPopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsRectangle__ReInit( &_this->Background );
  ComponentsKeyboardPopupButton__ReInit( &_this->OKButton );
  ComponentsKeyboardPopupButton__ReInit( &_this->CancelButton );
}

/* Finalizer method for the class 'Application::InputPopup' */
void ApplicationInputPopup__Done( ApplicationInputPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationPopup );

  /* Finalize all embedded objects */
  ViewsRectangle__Done( &_this->Background );
  ComponentsKeyboardPopupButton__Done( &_this->OKButton );
  ComponentsKeyboardPopupButton__Done( &_this->CancelButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationPopup__Done( &_this->_.Super );
}

/* The method UpdateViewState() is invoked automatically after the state of the 
   component has been changed. This method can be overridden and filled with logic 
   to ensure the visual aspect of the component does reflect its current state. 
   For example, the 'enabled' state of the component can affect its colors (disabled 
   components may appear pale). In this case the logic of the method should modify 
   the respective color properties accordingly to the current 'enabled' state. 
   The current state of the component is passed as a set in the parameter aState. 
   It reflects the very basic component state like its visibility or the ability 
   to react to user inputs. Beside this common state, the method can also involve 
   any other variables used in the component as long as they reflect its current 
   state. For example, the toggle switch component can take in account its toggle 
   state 'on' or 'off' and change accordingly the location of the slider, etc.
   Usually, this method will be invoked automatically by the framework. Optionally 
   you can request its invocation by using the method @InvalidateViewState(). */
void ApplicationInputPopup_UpdateViewState( ApplicationInputPopup _this, XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ViewsRectangle_OnSetColor( &_this->Background, ResSurface2 );
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)&_this->OKButton, ResSuccess );
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)&_this->CancelButton, 
  ResError );
}

/* 'C' function for method : 'Application::InputPopup.onOK()' */
void ApplicationInputPopup_onOK( ApplicationInputPopup _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  EwPostSignal( _this->OnOK, ((XObject)_this ));
}

/* 'C' function for method : 'Application::InputPopup.onCancel()' */
void ApplicationInputPopup_onCancel( ApplicationInputPopup _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  EwPostSignal( _this->OnCancel, ((XObject)_this ));
}

/* 'C' function for method : 'Application::InputPopup.OnSetOutlet()' */
void ApplicationInputPopup_OnSetOutlet( ApplicationInputPopup _this, XRef value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  _this->Outlet = value;
}

/* Wrapper function for the virtual method : 'Application::InputPopup.OnSetOutlet()' */
void ApplicationInputPopup__OnSetOutlet( void* _this, XRef value )
{
  ((ApplicationInputPopup)_this)->_.VMT->OnSetOutlet((ApplicationInputPopup)_this
  , value );
}

/* Variants derived from the class : 'Application::InputPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationInputPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationInputPopup )

/* Virtual Method Table (VMT) for the class : 'Application::InputPopup' */
EW_DEFINE_CLASS( ApplicationInputPopup, ApplicationPopup, Background, OnOK, OnOK, 
                 Outlet, _.VMT, _.VMT, "Application::InputPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  ApplicationInputPopup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationInputPopup_OnSetOutlet,
EW_END_OF_CLASS( ApplicationInputPopup )

/* Initializer for the class 'Application::InfusionRunning' */
void ApplicationInfusionRunning__Init( ApplicationInfusionRunning _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationInfusionBasePage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationInfusionRunning );

  /* ... then construct all embedded objects */
  ComponentsTextButton__Init( &_this->StopButton, &_this->_.XObject, 0 );
  ComponentsTile__Init( &_this->TileFlowRate, &_this->_.XObject, 0 );
  ComponentsTileInRunning__Init( &_this->RemainingVolumeTile, &_this->_.XObject, 0 );
  ComponentsTileTimeInRunning__Init( &_this->RemainingTimeTile, &_this->_.XObject, 0 );
  ComponentsPressureTile__Init( &_this->PressureTile, &_this->_.XObject, 0 );
  ComponentsSettingsButton__Init( &_this->BolusRateButton, &_this->_.XObject, 0 );
  CoreSystemEventHandler__Init( &_this->StopEventHandler, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationInfusionRunning );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( &_this->StopButton, _Const0019 );
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)&_this->StopButton, ResError );
  ComponentsBaseButton_OnSetBgColorPressed((ComponentsBaseButton)&_this->StopButton, 
  ResError );
  ComponentsTextButton__OnSetCaption( &_this->StopButton, EwLoadString( &StringsSTOP ));
  ComponentsTextButton_OnSetCaptionColor( &_this->StopButton, ResOnPrimary );
  CoreRectView__OnSetBounds( &_this->TileFlowRate, _Const001A );
  ComponentsBaseTile_OnSetCaption((ComponentsBaseTile)&_this->TileFlowRate, EwLoadString( 
  &StringsFlowRate ));
  ComponentsBaseTile__OnSetUnit( &_this->TileFlowRate, EwLoadString( &StringsUnit_mLPerhour ));
  ComponentsBaseTile__OnSetResolution( &_this->TileFlowRate, -2 );
  ComponentsBaseTile_OnSetPrecision((ComponentsBaseTile)&_this->TileFlowRate, 2 );
  _this->TileFlowRate.MinValue = 0;
  _this->TileFlowRate.MaxValue = 120000;
  CoreRectView__OnSetBounds( &_this->RemainingVolumeTile, _Const001B );
  ComponentsBaseTile_OnSetCaption((ComponentsBaseTile)&_this->RemainingVolumeTile, 
  EwLoadString( &StringsRemainingVolume ));
  ComponentsBaseTile__OnSetUnit( &_this->RemainingVolumeTile, EwLoadString( &StringsUnit_mL ));
  ComponentsBaseTile__OnSetResolution( &_this->RemainingVolumeTile, -2 );
  ComponentsBaseTile_OnSetPrecision((ComponentsBaseTile)&_this->RemainingVolumeTile, 
  2 );
  CoreRectView__OnSetBounds( &_this->RemainingTimeTile, _Const001C );
  ComponentsBaseTile_OnSetCaption((ComponentsBaseTile)&_this->RemainingTimeTile, 
  EwLoadString( &StringsRemainingTime ));
  CoreRectView__OnSetBounds( &_this->PressureTile, _Const001D );
  ComponentsBaseTile__OnSetUnit( &_this->PressureTile, EwLoadString( &StringsUnit_mmHg ));
  CoreRectView__OnSetBounds( &_this->BolusRateButton, _Const001E );
  ComponentsTextButton__OnSetCaption( &_this->BolusRateButton, EwLoadString( &StringsBOLUS ));
  ComponentsIconTextButton_OnSetIconColor((ComponentsIconTextButton)&_this->BolusRateButton, 
  ResWarning );
  CoreGroup__Add( _this, ((CoreView)&_this->StopButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->TileFlowRate ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->RemainingVolumeTile ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->RemainingTimeTile ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->PressureTile ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->BolusRateButton ), 0 );
  _this->StopButton.Super1.OnActivate = EwNewSlot( _this, ApplicationInfusionRunning_onStop );
  _this->TileFlowRate.Super2.OnActivate = EwNewSlot( _this, ApplicationInfusionBasePage_onEdit );
  ComponentsBaseTile__OnSetOutlet( &_this->TileFlowRate, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetFlowRate, DeviceDeviceClass_OnSetFlowRate ));
  ComponentsTile_OnSetIcon( &_this->TileFlowRate, EwLoadResource( &Rescircle_arrow_left, 
  ResourcesBitmap ));
  ComponentsBaseTile__OnSetOutlet( &_this->RemainingVolumeTile, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetInfusionVolume, DeviceDeviceClass_OnSetInfusionVolume ));
  ComponentsTile_OnSetIcon((ComponentsTile)&_this->RemainingVolumeTile, EwLoadResource( 
  &Resdroplets, ResourcesBitmap ));
  ComponentsTileInRunning_OnSetCurrentValueOutlet( &_this->RemainingVolumeTile, 
  EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetVolumeInfused, 
  DeviceDeviceClass_OnSetVolumeInfused ));
  ComponentsBaseTile__OnSetOutlet( &_this->RemainingTimeTile, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetInfusionTime, DeviceDeviceClass_OnSetInfusionTime ));
  ComponentsTile_OnSetIcon((ComponentsTile)&_this->RemainingTimeTile, EwLoadResource( 
  &Restimer, ResourcesBitmap ));
  ComponentsTileTimeInRunning_OnSetRemainingOutlet( &_this->RemainingTimeTile, EwNewRef( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetRemainingTime, 
  DeviceDeviceClass_OnSetRemainingTime ));
  ComponentsBaseTile__OnSetOutlet( &_this->PressureTile, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetPressureOnTube, DeviceDeviceClass_OnSetPressureOnTube ));
  ComponentsPressureTile_OnSetStageOutlet( &_this->PressureTile, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetPressureSetting, DeviceDeviceClass_OnSetPressureSetting ));
  _this->BolusRateButton.Super3.OnActivate = EwNewSlot( _this, ApplicationInfusionRunning_onBolus );
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->BolusRateButton, 
  EwLoadResource( &Reschevrons_left_32px, ResourcesBitmap ));
  _this->StopEventHandler.OnEvent = EwNewSlot( _this, ApplicationInfusionRunning_onStop );
  CoreSystemEventHandler_OnSetEvent( &_this->StopEventHandler, &EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass )->StopEvent );
}

/* Re-Initializer for the class 'Application::InfusionRunning' */
void ApplicationInfusionRunning__ReInit( ApplicationInfusionRunning _this )
{
  /* At first re-initialize the super class ... */
  ApplicationInfusionBasePage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsTextButton__ReInit( &_this->StopButton );
  ComponentsTile__ReInit( &_this->TileFlowRate );
  ComponentsTileInRunning__ReInit( &_this->RemainingVolumeTile );
  ComponentsTileTimeInRunning__ReInit( &_this->RemainingTimeTile );
  ComponentsPressureTile__ReInit( &_this->PressureTile );
  ComponentsSettingsButton__ReInit( &_this->BolusRateButton );
  CoreSystemEventHandler__ReInit( &_this->StopEventHandler );
}

/* Finalizer method for the class 'Application::InfusionRunning' */
void ApplicationInfusionRunning__Done( ApplicationInfusionRunning _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationInfusionBasePage );

  /* Finalize all embedded objects */
  ComponentsTextButton__Done( &_this->StopButton );
  ComponentsTile__Done( &_this->TileFlowRate );
  ComponentsTileInRunning__Done( &_this->RemainingVolumeTile );
  ComponentsTileTimeInRunning__Done( &_this->RemainingTimeTile );
  ComponentsPressureTile__Done( &_this->PressureTile );
  ComponentsSettingsButton__Done( &_this->BolusRateButton );
  CoreSystemEventHandler__Done( &_this->StopEventHandler );

  /* Don't forget to deinitialize the super class ... */
  ApplicationInfusionBasePage__Done( &_this->_.Super );
}

/* 'C' function for method : 'Application::InfusionRunning.OnSetopacity()' */
void ApplicationInfusionRunning_OnSetopacity( ApplicationInfusionRunning _this, 
  XInt32 value )
{
  ApplicationInfusionBasePage_OnSetopacity((ApplicationInfusionBasePage)_this, value );

  if ( _this->Super1.editTile == 0 )
    return;

  if ( &_this->TileFlowRate != _this->Super1.editTile->ViewTile )
    CoreGroup__OnSetOpacity( &_this->TileFlowRate, value );

  CoreGroup__OnSetOpacity( &_this->RemainingVolumeTile, value );
  CoreGroup__OnSetOpacity( &_this->RemainingTimeTile, value );
  CoreGroup__OnSetOpacity( &_this->PressureTile, value );
  CoreGroup__OnSetOpacity( &_this->BolusRateButton, value );
}

/* 'C' function for method : 'Application::InfusionRunning.onStop()' */
void ApplicationInfusionRunning_onStop( ApplicationInfusionRunning _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->InfusionState != 5 )
    return;

  DeviceDeviceClass_StopInfusion( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ));

  if ( ApplicationPopupNavigatorClass_GetCurrentPopupType( EwGetAutoObject( &ApplicationPopupNavigator, 
      ApplicationPopupNavigatorClass )) != DevicePopupTypeInfusionStop )
    ApplicationPopupNavigatorClass_OpenPopupWithEffectByType( EwGetAutoObject( &ApplicationPopupNavigator, 
    ApplicationPopupNavigatorClass ), DevicePopupTypeInfusionStop, _this->StopButton.Super4.Bounds, 
    ApplicationPopupAlignStartAreaBottomRight );
}

/* 'C' function for method : 'Application::InfusionRunning.onBolus()' */
void ApplicationInfusionRunning_onBolus( ApplicationInfusionRunning _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ApplicationPopupNavigatorClass_OpenPopupWithEffectByType( EwGetAutoObject( &ApplicationPopupNavigator, 
  ApplicationPopupNavigatorClass ), DevicePopupTypeBolusMenu, _this->BolusRateButton.Super6.Bounds, 
  ApplicationPopupAlignCentered );
}

/* Variants derived from the class : 'Application::InfusionRunning' */
EW_DEFINE_CLASS_VARIANTS( ApplicationInfusionRunning )
EW_END_OF_CLASS_VARIANTS( ApplicationInfusionRunning )

/* Virtual Method Table (VMT) for the class : 'Application::InfusionRunning' */
EW_DEFINE_CLASS( ApplicationInfusionRunning, ApplicationInfusionBasePage, StopButton, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::InfusionRunning" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationInfusionRunning_OnSetopacity,
EW_END_OF_CLASS( ApplicationInfusionRunning )

/* Initializer for the class 'Application::SettingsContainer' */
void ApplicationSettingsContainer__Init( ApplicationSettingsContainer _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  NavigationContainer__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationSettingsContainer );

  /* ... then construct all embedded objects */
  CoreSimpleTouchHandler__Init( &_this->TouchHandler, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->HandlerBar, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationSettingsContainer );

  /* ... and initialize objects, variables, properties, etc. */
  CoreQuadView__OnSetPoint4( &_this->TouchHandler, _Const001F );
  CoreQuadView__OnSetPoint3( &_this->TouchHandler, _Const0020 );
  CoreQuadView__OnSetPoint2( &_this->TouchHandler, _Const0021 );
  CoreQuadView__OnSetPoint1( &_this->TouchHandler, _Const0022 );
  CoreSimpleTouchHandler_OnSetMaxStrikeCount( &_this->TouchHandler, 9999 );
  CoreSimpleTouchHandler_OnSetEnabled( &_this->TouchHandler, 0 );
  CoreRectView__OnSetBounds( &_this->HandlerBar, _Const0023 );
  ViewsRectangle_OnSetRadius( &_this->HandlerBar, 10 );
  ViewsRectangle_OnSetVisible( &_this->HandlerBar, 0 );
  _this->direction = CoreDirectionNone;
  CoreGroup__Add( _this, ((CoreView)&_this->TouchHandler ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->HandlerBar ), 0 );
  _this->TouchHandler.OnDrag = EwNewSlot( _this, ApplicationSettingsContainer_onTouchDrag );
  _this->TouchHandler.OnRelease = EwNewSlot( _this, ApplicationSettingsContainer_onTouchRelease );
  _this->TouchHandler.OnPress = EwNewSlot( _this, ApplicationSettingsContainer_onTouchPress );

  /* Call the user defined constructor */
  ApplicationSettingsContainer_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::SettingsContainer' */
void ApplicationSettingsContainer__ReInit( ApplicationSettingsContainer _this )
{
  /* At first re-initialize the super class ... */
  NavigationContainer__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreSimpleTouchHandler__ReInit( &_this->TouchHandler );
  ViewsRectangle__ReInit( &_this->HandlerBar );
}

/* Finalizer method for the class 'Application::SettingsContainer' */
void ApplicationSettingsContainer__Done( ApplicationSettingsContainer _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( NavigationContainer );

  /* Finalize all embedded objects */
  CoreSimpleTouchHandler__Done( &_this->TouchHandler );
  ViewsRectangle__Done( &_this->HandlerBar );

  /* Don't forget to deinitialize the super class ... */
  NavigationContainer__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationSettingsContainer_Init( ApplicationSettingsContainer _this, XHandle 
  aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  _this->handlerInitPos = _this->HandlerBar.Super1.Bounds.Point1.Y;
  _this->handlerPos = _this->handlerInitPos;
  _this->handlerTouchHeight = EwGetRectH( CoreView__GetExtent( &_this->TouchHandler ));
  EwAttachRefObserver( EwNewSlot( _this, ApplicationSettingsContainer_onPageChange ), 
    EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetCurrentPage, 
    DeviceDeviceClass_OnSetCurrentPage ), 0 );
  EwAttachRefObserver( EwNewSlot( _this, ApplicationSettingsContainer_onPageChange ), 
    EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetCurrentSettings, 
    DeviceDeviceClass_OnSetCurrentSettings ), 0 );
  EwAttachRefObserver( EwNewSlot( _this, ApplicationSettingsContainer_onPageChange ), 
    EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetCurrentPopup, 
    DeviceDeviceClass_OnSetCurrentPopup ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationSettingsContainer_onPageChange ), ((XObject)_this ));
}

/* The method UpdateViewState() is invoked automatically after the state of the 
   component has been changed. This method can be overridden and filled with logic 
   to ensure the visual aspect of the component does reflect its current state. 
   For example, the 'enabled' state of the component can affect its colors (disabled 
   components may appear pale). In this case the logic of the method should modify 
   the respective color properties accordingly to the current 'enabled' state. 
   The current state of the component is passed as a set in the parameter aState. 
   It reflects the very basic component state like its visibility or the ability 
   to react to user inputs. Beside this common state, the method can also involve 
   any other variables used in the component as long as they reflect its current 
   state. For example, the toggle switch component can take in account its toggle 
   state 'on' or 'off' and change accordingly the location of the slider, etc.
   Usually, this method will be invoked automatically by the framework. Optionally 
   you can request its invocation by using the method @InvalidateViewState(). */
void ApplicationSettingsContainer_UpdateViewState( ApplicationSettingsContainer _this, 
  XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ViewsRectangle_OnSetColor( &_this->HandlerBar, ResOnPrimary );
}

/* 'C' function for method : 'Application::SettingsContainer.onTouchDrag()' */
void ApplicationSettingsContainer_onTouchDrag( ApplicationSettingsContainer _this, 
  XObject sender )
{
  XInt32 yDrag;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  yDrag = _this->TouchHandler.CurrentPos.Y - _this->TouchHandler.HittingPos.Y;
  _this->direction = CoreDirectionNone;

  if ( EwGetInt32Abs( yDrag ) >= 8 )
  {
    if (( _this->TouchHandler.CurrentPos.Y - _this->currentY ) > 0 )
      _this->direction = CoreDirectionBottom;
    else
      _this->direction = CoreDirectionTop;
  }

  if ( !_this->inDragging )
  {
    if ( _this->direction != CoreDirectionNone )
    {
      ApplicationSettingsContainer_createSettingsPage( _this );
      _this->startY = _this->HandlerBar.Super1.Bounds.Point1.Y;
      ApplicationSettingsContainer_OnSethandlerPos( _this, _this->startY + yDrag );
      _this->inDragging = 1;
    }
  }
  else
    ApplicationSettingsContainer_OnSethandlerPos( _this, _this->startY + yDrag );

  _this->currentY = _this->TouchHandler.CurrentPos.Y;
}

/* 'C' function for method : 'Application::SettingsContainer.onTouchPress()' */
void ApplicationSettingsContainer_onTouchPress( ApplicationSettingsContainer _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  _this->inDragging = 0;
  _this->currentY = _this->TouchHandler.HittingPos.Y;
}

/* 'C' function for method : 'Application::SettingsContainer.onTouchRelease()' */
void ApplicationSettingsContainer_onTouchRelease( ApplicationSettingsContainer _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->direction == CoreDirectionTop )
    ApplicationSettingsContainer_startReleaseEffect( _this, 0 );
  else
    if ( _this->direction == CoreDirectionBottom )
      ApplicationSettingsContainer_startReleaseEffect( _this, 1 );
    else
    {
      XRect handlerArea = CoreView__GetExtent( &_this->HandlerBar );
      XInt32 delta = ( _this->handlerTouchHeight - EwGetRectH( handlerArea )) / 
        2;
      handlerArea.Point1.Y = ( handlerArea.Point1.Y - delta );
      handlerArea.Point2.Y = ( handlerArea.Point2.Y + delta );

      if ( EwIsPointInRect( handlerArea, _this->TouchHandler.HittingPos ))
      {
        if ( handlerArea.Point1.Y == 0 )
          ApplicationSettingsContainer_startReleaseEffect( _this, 1 );
        else
          if ( handlerArea.Point2.Y == EwGetRectH( _this->Super3.Bounds ))
            ApplicationSettingsContainer_startReleaseEffect( _this, 0 );
      }
    }

  _this->inDragging = 0;
  _this->direction = CoreDirectionNone;
}

/* 'C' function for method : 'Application::SettingsContainer.startReleaseEffect()' */
void ApplicationSettingsContainer_startReleaseEffect( ApplicationSettingsContainer _this, 
  XBool aOpen )
{
  XInt32 startPos = _this->HandlerBar.Super1.Bounds.Point1.Y;
  XInt32 endPos;

  if ( aOpen )
  {
    ApplicationSettingsContainer_createSettingsPage( _this );
    endPos = ( EwGetRectH( _this->Super3.Bounds ) - _this->handlerInitPos ) - EwGetRectH( 
    _this->HandlerBar.Super1.Bounds );
  }
  else
    endPos = _this->handlerInitPos;

  if ( EwGetInt32Abs( endPos - startPos ) < 8 )
  {
    ApplicationSettingsContainer_OnSethandlerPos( _this, endPos );

    if ( aOpen )
      EwPostSignal( EwNewSlot( _this, ApplicationSettingsContainer_onOpen ), ((XObject)_this ));
    else
      EwPostSignal( EwNewSlot( _this, ApplicationSettingsContainer_onClose ), ((XObject)_this ));

    return;
  }

  if ( _this->releaseEffect == 0 )
    _this->releaseEffect = EwNewObject( EffectsInt32Effect, 0 );

  if ( _this->releaseEffect == 0 )
    return;

  EffectsEffect_OnSetEnabled((EffectsEffect)_this->releaseEffect, 0 );
  EffectsEffect_OnSetCycleDuration((EffectsEffect)_this->releaseEffect, 200 );
  EffectsEffect_OnSetNoOfCycles((EffectsEffect)_this->releaseEffect, 1 );
  _this->releaseEffect->Value1 = startPos;
  _this->releaseEffect->Value2 = endPos;
  _this->releaseEffect->Outlet = EwNewRef( _this, ApplicationSettingsContainer_OnGethandlerPos, 
  ApplicationSettingsContainer_OnSethandlerPos );
  EffectsEffect_OnSetEnabled((EffectsEffect)_this->releaseEffect, 1 );

  if ( aOpen )
    _this->releaseEffect->Super1.OnFinished = EwNewSlot( _this, ApplicationSettingsContainer_onOpen );
  else
    _this->releaseEffect->Super1.OnFinished = EwNewSlot( _this, ApplicationSettingsContainer_onClose );
}

/* 'C' function for method : 'Application::SettingsContainer.onOpen()' */
void ApplicationSettingsContainer_onOpen( ApplicationSettingsContainer _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ApplicationSettingsContainer_OnSethandlerPos( _this, ( EwGetRectH( _this->Super3.Bounds ) 
  - _this->handlerInitPos ) - EwGetRectH( _this->HandlerBar.Super1.Bounds ));

  if ( _this->SettingsPage != 0 )
  {
    NavigationContainer_OnSetIsModal((NavigationContainer)_this, 1 );

    if ( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->CurrentSettings == 
        0 )
      DeviceDeviceClass_OnSetCurrentSettings( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
      1 );
  }
}

/* 'C' function for method : 'Application::SettingsContainer.OnSethandlerPos()' */
void ApplicationSettingsContainer_OnSethandlerPos( ApplicationSettingsContainer _this, 
  XInt32 value )
{
  if ( value < _this->handlerInitPos )
    value = _this->handlerInitPos;
  else
    if ( value > (( EwGetRectH( _this->Super3.Bounds ) - _this->handlerInitPos ) 
        - EwGetRectH( _this->HandlerBar.Super1.Bounds )))
      value = ( EwGetRectH( _this->Super3.Bounds ) - _this->handlerInitPos ) - EwGetRectH( 
      _this->HandlerBar.Super1.Bounds );

  if ( _this->handlerPos == value )
    return;

  _this->handlerPos = value;
  CoreRectView__OnSetBounds( &_this->HandlerBar, EwSetRectY( _this->HandlerBar.Super1.Bounds, 
  value ));
  CoreQuadView__OnSetPoint1( &_this->TouchHandler, EwSetPointY( _this->TouchHandler.Super1.Point1, 
  ( value + _this->handlerTouchHeight ) - _this->handlerInitPos ));
  CoreQuadView__OnSetPoint2( &_this->TouchHandler, EwSetPointY( _this->TouchHandler.Super1.Point2, 
  _this->TouchHandler.Super1.Point1.Y ));

  if ( _this->SettingsPage == 0 )
  {
    EwTrace( "%s", EwLoadString( &_Const0024 ));
    return;
  }

  CoreRectView__OnSetBounds( _this->SettingsPage, EwSetRectY( _this->SettingsPage->Super2.Bounds, 
  _this->TouchHandler.Super1.Point1.Y - EwGetRectH( _this->SettingsPage->Super2.Bounds )));
}

/* 'C' function for method : 'Application::SettingsContainer.onClose()' */
void ApplicationSettingsContainer_onClose( ApplicationSettingsContainer _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ApplicationSettingsContainer_OnSethandlerPos( _this, _this->handlerInitPos );

  if ( _this->SettingsPage != 0 )
  {
    if ( _this->SettingsPage->Super3.Owner == (CoreGroup)_this )
      CoreGroup__Remove( _this, ((CoreView)_this->SettingsPage ));

    _this->SettingsPage = 0;
    DeviceDeviceClass_OnSetCurrentSettings( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
    0 );
  }

  NavigationContainer_OnSetIsModal((NavigationContainer)_this, 0 );
}

/* 'C' function for method : 'Application::SettingsContainer.onPageChange()' */
void ApplicationSettingsContainer_onPageChange( ApplicationSettingsContainer _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ApplicationSettingsContainer_OnSetShowHandlerBar( _this, (XBool)(((( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass )->CurrentPage != 1 ) && ( EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass )->CurrentPage != 4 )) && (( EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass )->CurrentSettings == 0 ) || ( EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass )->CurrentSettings == 1 ))) && ( EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass )->CurrentPopup == 0 )));
}

/* 'C' function for method : 'Application::SettingsContainer.OnSetShowHandlerBar()' */
void ApplicationSettingsContainer_OnSetShowHandlerBar( ApplicationSettingsContainer _this, 
  XBool value )
{
  if ( _this->ShowHandlerBar == value )
    return;

  _this->ShowHandlerBar = value;
  ViewsRectangle_OnSetVisible( &_this->HandlerBar, value );
  CoreSimpleTouchHandler_OnSetEnabled( &_this->TouchHandler, value );
}

/* 'C' function for method : 'Application::SettingsContainer.createSettingsPage()' */
void ApplicationSettingsContainer_createSettingsPage( ApplicationSettingsContainer _this )
{
  if ( _this->SettingsPage == 0 )
    _this->SettingsPage = ((NavigationPage)EwNewObject( ApplicationSettings, 0 ));

  if ( _this->SettingsPage->Super3.Owner == 0 )
    CoreGroup__AddBehind( _this, ((CoreView)_this->SettingsPage ), ((CoreView)&_this->HandlerBar ));
}

/* Default onget method for the property 'handlerPos' */
XInt32 ApplicationSettingsContainer_OnGethandlerPos( ApplicationSettingsContainer _this )
{
  return _this->handlerPos;
}

/* Variants derived from the class : 'Application::SettingsContainer' */
EW_DEFINE_CLASS_VARIANTS( ApplicationSettingsContainer )
EW_END_OF_CLASS_VARIANTS( ApplicationSettingsContainer )

/* Virtual Method Table (VMT) for the class : 'Application::SettingsContainer' */
EW_DEFINE_CLASS( ApplicationSettingsContainer, NavigationContainer, TouchHandler, 
                 SettingsPage, startY, startY, startY, startY, "Application::SettingsContainer" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  NavigationContainer_UpdateLayout,
  ApplicationSettingsContainer_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ApplicationSettingsContainer )

/* Initializer for the class 'Application::StatusBar' */
void ApplicationStatusBar__Init( ApplicationStatusBar _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationStatusBar );

  /* ... then construct all embedded objects */
  ViewsText__Init( &_this->InfusionStateText, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->TimeText, &_this->_.XObject, 0 );
  CoreOutline__Init( &_this->Outline, &_this->_.XObject, 0 );
  ComponentsBattery__Init( &_this->Battery, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->WifiIcon, &_this->_.XObject, 0 );
  CoreTimer__Init( &_this->Timer, &_this->_.XObject, 0 );
  CoreTime__Init( &_this->time, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationStatusBar );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0025 );
  CoreRectView__OnSetBounds( &_this->InfusionStateText, _Const0026 );
  ViewsText_OnSetOverflowWarning( &_this->InfusionStateText, 1 );
  ViewsText_OnSetRowDistance( &_this->InfusionStateText, 30 );
  ViewsText_OnSetAlignment( &_this->InfusionStateText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->TimeText, _Const0027 );
  ViewsText_OnSetOverflowWarning( &_this->TimeText, 1 );
  ViewsText_OnSetAlignment( &_this->TimeText, ViewsTextAlignmentAlignHorzRight | 
  ViewsTextAlignmentAlignVertCenter );
  ViewsText_OnSetColor( &_this->TimeText, ResOnSecondary );
  CoreRectView__OnSetBounds( &_this->Outline, _Const0028 );
  CoreOutline_OnSetSpaceHorz( &_this->Outline, 10 );
  CoreOutline_OnSetFormation( &_this->Outline, CoreFormationRightToLeft );
  CoreRectView__OnSetBounds( &_this->Battery, _Const0029 );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->Battery, 1 );
  ComponentsBattery_OnSetColor( &_this->Battery, ResOnSecondary );
  ComponentsBattery_OnSetScrollOffset( &_this->Battery, _Const002A );
  CoreRectView__OnSetBounds( &_this->WifiIcon, _Const002B );
  ViewsImage_OnSetColor( &_this->WifiIcon, ResOnSecondary );
  ViewsImage_OnSetEmbedded( &_this->WifiIcon, 1 );
  CoreGroup__Add( _this, ((CoreView)&_this->InfusionStateText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->TimeText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Outline ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Battery ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->WifiIcon ), 0 );
  ViewsText__OnSetFont( &_this->InfusionStateText, EwLoadResource( &FontsHeading3, 
  ResourcesFont ));
  ViewsText__OnSetFont( &_this->TimeText, EwLoadResource( &FontsBody18, ResourcesFont ));
  ComponentsBattery_OnSetOutletLevel( &_this->Battery, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetBatteryLevel, DeviceDeviceClass_OnSetBatteryLevel ));
  ComponentsBattery_OnSetOutletStatus( &_this->Battery, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetBatteryChargeStatus, 
  DeviceDeviceClass_OnSetBatteryChargeStatus ));
  _this->Timer.OnTrigger = EwNewSlot( _this, ApplicationStatusBar_onTimeUpdate );

  /* Call the user defined constructor */
  ApplicationStatusBar_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::StatusBar' */
void ApplicationStatusBar__ReInit( ApplicationStatusBar _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsText__ReInit( &_this->InfusionStateText );
  ViewsText__ReInit( &_this->TimeText );
  CoreOutline__ReInit( &_this->Outline );
  ComponentsBattery__ReInit( &_this->Battery );
  ViewsImage__ReInit( &_this->WifiIcon );
  CoreTimer__ReInit( &_this->Timer );
  CoreTime__ReInit( &_this->time );
}

/* Finalizer method for the class 'Application::StatusBar' */
void ApplicationStatusBar__Done( ApplicationStatusBar _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Finalize all embedded objects */
  ViewsText__Done( &_this->InfusionStateText );
  ViewsText__Done( &_this->TimeText );
  CoreOutline__Done( &_this->Outline );
  ComponentsBattery__Done( &_this->Battery );
  ViewsImage__Done( &_this->WifiIcon );
  CoreTimer__Done( &_this->Timer );
  CoreTime__Done( &_this->time );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationStatusBar_Init( ApplicationStatusBar _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  CoreTimer_OnSetEnabled( &_this->Timer, 1 );
  EwPostSignal( EwNewSlot( _this, ApplicationStatusBar_onTimeUpdate ), ((XObject)_this ));
  EwAttachRefObserver( EwNewSlot( _this, ApplicationStatusBar_onInfusionState ), 
    EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetInfusionState, 
    DeviceDeviceClass_OnSetInfusionState ), 0 );
  EwAttachRefObserver( EwNewSlot( _this, ApplicationStatusBar_onWifiSignal ), EwNewRef( 
    EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetWifiSignal, 
    DeviceDeviceClass_OnSetWifiSignal ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationStatusBar_onTimeUpdate ), ((XObject)_this ));
  EwPostSignal( EwNewSlot( _this, ApplicationStatusBar_onInfusionState ), ((XObject)_this ));
  EwPostSignal( EwNewSlot( _this, ApplicationStatusBar_onWifiSignal ), ((XObject)_this ));
}

/* 'C' function for method : 'Application::StatusBar.onInfusionState()' */
void ApplicationStatusBar_onInfusionState( ApplicationStatusBar _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  switch ( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->InfusionState )
  {
    case 5 :
    {
      ViewsText__OnSetString( &_this->InfusionStateText, EwLoadString( &StringsInfusionRunning ));
      ViewsText_OnSetColor( &_this->InfusionStateText, ResSuccess );
    }
    break;

    case 6 :
    {
      ViewsText__OnSetString( &_this->InfusionStateText, EwLoadString( &StringsInfusionStopped ));
      ViewsText_OnSetColor( &_this->InfusionStateText, ResError );
    }
    break;

    default : 
      ViewsText__OnSetString( &_this->InfusionStateText, 0 );
  }
}

/* 'C' function for method : 'Application::StatusBar.onWifiSignal()' */
void ApplicationStatusBar_onWifiSignal( ApplicationStatusBar _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ViewsImage_OnSetBitmap( &_this->WifiIcon, DeviceEnumClass__GetIcon( EwGetAutoObject( 
  &DeviceWifiSignalEnum, DeviceWifiSignalEnumClass ), EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass )->WifiSignal ));
}

/* 'C' function for method : 'Application::StatusBar.onTimeUpdate()' */
void ApplicationStatusBar_onTimeUpdate( ApplicationStatusBar _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ViewsText__OnSetString( &_this->TimeText, CoreTime_Format( CoreTime_Initialize( 
  &_this->time, CoreTime_OnGetTime( CoreTime_OnGetCurrentTime( &_this->time ))), 
  EwLoadString( &_Const002C )));
}

/* Variants derived from the class : 'Application::StatusBar' */
EW_DEFINE_CLASS_VARIANTS( ApplicationStatusBar )
EW_END_OF_CLASS_VARIANTS( ApplicationStatusBar )

/* Virtual Method Table (VMT) for the class : 'Application::StatusBar' */
EW_DEFINE_CLASS( ApplicationStatusBar, CoreGroup, InfusionStateText, _.VMT, _.VMT, 
                 _.VMT, _.VMT, _.VMT, "Application::StatusBar" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ApplicationStatusBar )

/* Initializer for the class 'Application::SettingsPage' */
void ApplicationSettingsPage__Init( ApplicationSettingsPage _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  NavigationPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationSettingsPage );

  /* ... then construct all embedded objects */
  ViewsRectangle__Init( &_this->Scrim, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->ContentBackground, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->CaptionText, &_this->_.XObject, 0 );
  ComponentsTextButton__Init( &_this->BackButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationSettingsPage );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( &_this->Scrim, _Const0009 );
  ViewsRectangle_OnSetColor( &_this->Scrim, ResOverlayOpaque );
  CoreRectView__OnSetBounds( &_this->ContentBackground, _Const002D );
  ViewsRectangle_OnSetRadius( &_this->ContentBackground, 30 );
  ViewsRectangle_OnSetColor( &_this->ContentBackground, ResSurface2 );
  CoreRectView__OnSetBounds( &_this->CaptionText, _Const002E );
  ViewsText_OnSetOverflowWarning( &_this->CaptionText, 1 );
  ViewsText_OnSetColor( &_this->CaptionText, ResOnSecondary );
  CoreRectView__OnSetBounds( &_this->BackButton, _Const002F );
  ComponentsTextButton__OnSetCaption( &_this->BackButton, EwLoadString( &StringsBACK ));
  CoreGroup__Add( _this, ((CoreView)&_this->Scrim ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ContentBackground ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->CaptionText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->BackButton ), 0 );
  ViewsText__OnSetFont( &_this->CaptionText, EwLoadResource( &FontsHeading2, ResourcesFont ));
  _this->BackButton.Super1.OnActivate = EwNewSlot( _this, ApplicationSettingsPage__onBack );

  /* Call the user defined constructor */
  ApplicationSettingsPage_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::SettingsPage' */
void ApplicationSettingsPage__ReInit( ApplicationSettingsPage _this )
{
  /* At first re-initialize the super class ... */
  NavigationPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsRectangle__ReInit( &_this->Scrim );
  ViewsRectangle__ReInit( &_this->ContentBackground );
  ViewsText__ReInit( &_this->CaptionText );
  ComponentsTextButton__ReInit( &_this->BackButton );
}

/* Finalizer method for the class 'Application::SettingsPage' */
void ApplicationSettingsPage__Done( ApplicationSettingsPage _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( NavigationPage );

  /* Finalize all embedded objects */
  ViewsRectangle__Done( &_this->Scrim );
  ViewsRectangle__Done( &_this->ContentBackground );
  ViewsText__Done( &_this->CaptionText );
  ComponentsTextButton__Done( &_this->BackButton );

  /* Don't forget to deinitialize the super class ... */
  NavigationPage__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationSettingsPage_Init( ApplicationSettingsPage _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* 'C' function for method : 'Application::SettingsPage.OnSetCaption()' */
void ApplicationSettingsPage_OnSetCaption( ApplicationSettingsPage _this, XString 
  value )
{
  NavigationPage_OnSetCaption((NavigationPage)_this, value );
  ViewsText__OnSetString( &_this->CaptionText, value );
}

/* 'C' function for method : 'Application::SettingsPage.onBack()' */
void ApplicationSettingsPage_onBack( ApplicationSettingsPage _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( sender );

  DeviceDeviceClass_OnSetCurrentSettings( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  1 );
}

/* Wrapper function for the virtual method : 'Application::SettingsPage.onBack()' */
void ApplicationSettingsPage__onBack( void* _this, XObject sender )
{
  ((ApplicationSettingsPage)_this)->_.VMT->onBack((ApplicationSettingsPage)_this
  , sender );
}

/* Variants derived from the class : 'Application::SettingsPage' */
EW_DEFINE_CLASS_VARIANTS( ApplicationSettingsPage )
EW_END_OF_CLASS_VARIANTS( ApplicationSettingsPage )

/* Virtual Method Table (VMT) for the class : 'Application::SettingsPage' */
EW_DEFINE_CLASS( ApplicationSettingsPage, NavigationPage, Scrim, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, "Application::SettingsPage" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsPage_onBack,
EW_END_OF_CLASS( ApplicationSettingsPage )

/* Initializer for the class 'Application::PressureSettings' */
void ApplicationPressureSettings__Init( ApplicationPressureSettings _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationPressureSettings );

  /* ... then construct all embedded objects */
  ComponentsInfoTip__Init( &_this->InfoTip, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting1Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting2Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting3Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting4Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting5Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting6Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting7Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting8Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting9Button, &_this->_.XObject, 0 );
  ComponentsTextButton__Init( &_this->ConfirmButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationPressureSettings );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsPressureSettings ));
  CoreRectView__OnSetBounds( &_this->Super1.ContentBackground, _Const0030 );
  CoreRectView__OnSetBounds( &_this->InfoTip, _Const0031 );
  ComponentsInfoTip_OnSetTipString( &_this->InfoTip, EwLoadString( &StringsPressureAlarmLimit ));
  _this->InfoTip.InfoCaption = EwShareString( EwLoadString( &StringsPressureSettingInfoCaption ));
  _this->InfoTip.InfoMessage = EwShareString( EwLoadString( &StringsPressureSettingInfoText ));
  CoreRectView__OnSetBounds( &_this->Setting1Button, _Const0032 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting1Button, 1 );
  CoreRectView__OnSetBounds( &_this->Setting2Button, _Const0033 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting2Button, 2 );
  CoreRectView__OnSetBounds( &_this->Setting3Button, _Const0034 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting3Button, 3 );
  CoreRectView__OnSetBounds( &_this->Setting4Button, _Const0035 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting4Button, 4 );
  CoreRectView__OnSetBounds( &_this->Setting5Button, _Const0036 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting5Button, 5 );
  CoreRectView__OnSetBounds( &_this->Setting6Button, _Const0037 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting6Button, 6 );
  CoreRectView__OnSetBounds( &_this->Setting7Button, _Const0038 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting7Button, 7 );
  CoreRectView__OnSetBounds( &_this->Setting8Button, _Const0039 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting8Button, 8 );
  CoreRectView__OnSetBounds( &_this->Setting9Button, _Const003A );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting9Button, 9 );
  CoreRectView__OnSetBounds( &_this->ConfirmButton, _Const003B );
  CoreGroup_OnSetEnabled((CoreGroup)&_this->ConfirmButton, 0 );
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)&_this->ConfirmButton, 
  ResSuccess );
  ComponentsBaseButton_OnSetBgColorPressed((ComponentsBaseButton)&_this->ConfirmButton, 
  ResSuccess );
  ComponentsTextButton__OnSetCaption( &_this->ConfirmButton, EwLoadString( &StringsCONFIRM ));
  ComponentsTextButton_OnSetCaptionColor( &_this->ConfirmButton, ResOnPrimary );
  CoreGroup__Add( _this, ((CoreView)&_this->InfoTip ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting1Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting2Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting3Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting4Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting5Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting6Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting7Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting8Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting9Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ConfirmButton ), 0 );
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting1Button, 
  EwNewRef( _this, ApplicationPressureSettings_OnGetPressureSetting, ApplicationPressureSettings_OnSetPressureSetting ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting2Button, 
  EwNewRef( _this, ApplicationPressureSettings_OnGetPressureSetting, ApplicationPressureSettings_OnSetPressureSetting ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting3Button, 
  EwNewRef( _this, ApplicationPressureSettings_OnGetPressureSetting, ApplicationPressureSettings_OnSetPressureSetting ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting4Button, 
  EwNewRef( _this, ApplicationPressureSettings_OnGetPressureSetting, ApplicationPressureSettings_OnSetPressureSetting ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting5Button, 
  EwNewRef( _this, ApplicationPressureSettings_OnGetPressureSetting, ApplicationPressureSettings_OnSetPressureSetting ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting6Button, 
  EwNewRef( _this, ApplicationPressureSettings_OnGetPressureSetting, ApplicationPressureSettings_OnSetPressureSetting ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting7Button, 
  EwNewRef( _this, ApplicationPressureSettings_OnGetPressureSetting, ApplicationPressureSettings_OnSetPressureSetting ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting8Button, 
  EwNewRef( _this, ApplicationPressureSettings_OnGetPressureSetting, ApplicationPressureSettings_OnSetPressureSetting ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting9Button, 
  EwNewRef( _this, ApplicationPressureSettings_OnGetPressureSetting, ApplicationPressureSettings_OnSetPressureSetting ));
  _this->ConfirmButton.Super1.OnActivate = EwNewSlot( _this, ApplicationPressureSettings_onConfirm );

  /* Call the user defined constructor */
  ApplicationPressureSettings_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::PressureSettings' */
void ApplicationPressureSettings__ReInit( ApplicationPressureSettings _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsInfoTip__ReInit( &_this->InfoTip );
  ComponentsPressureSettingButton__ReInit( &_this->Setting1Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting2Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting3Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting4Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting5Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting6Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting7Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting8Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting9Button );
  ComponentsTextButton__ReInit( &_this->ConfirmButton );
}

/* Finalizer method for the class 'Application::PressureSettings' */
void ApplicationPressureSettings__Done( ApplicationPressureSettings _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsPage );

  /* Finalize all embedded objects */
  ComponentsInfoTip__Done( &_this->InfoTip );
  ComponentsPressureSettingButton__Done( &_this->Setting1Button );
  ComponentsPressureSettingButton__Done( &_this->Setting2Button );
  ComponentsPressureSettingButton__Done( &_this->Setting3Button );
  ComponentsPressureSettingButton__Done( &_this->Setting4Button );
  ComponentsPressureSettingButton__Done( &_this->Setting5Button );
  ComponentsPressureSettingButton__Done( &_this->Setting6Button );
  ComponentsPressureSettingButton__Done( &_this->Setting7Button );
  ComponentsPressureSettingButton__Done( &_this->Setting8Button );
  ComponentsPressureSettingButton__Done( &_this->Setting9Button );
  ComponentsTextButton__Done( &_this->ConfirmButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsPage__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationPressureSettings_Init( ApplicationPressureSettings _this, XHandle 
  aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  EwAttachRefObserver( EwNewSlot( _this, ApplicationPressureSettings_onPressureSetting ), 
    EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetPressureSetting, 
    DeviceDeviceClass_OnSetPressureSetting ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationPressureSettings_onPressureSetting ), 
    ((XObject)_this ));
}

/* 'C' function for method : 'Application::PressureSettings.OnSetPressureSetting()' */
void ApplicationPressureSettings_OnSetPressureSetting( ApplicationPressureSettings _this, 
  XInt32 value )
{
  if ( _this->PressureSetting == value )
    return;

  _this->PressureSetting = value;
  CoreGroup_OnSetEnabled((CoreGroup)&_this->ConfirmButton, (XBool)( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass )->PressureSetting != value ));
  EwNotifyRefObservers( EwNewRef( _this, ApplicationPressureSettings_OnGetPressureSetting, 
    ApplicationPressureSettings_OnSetPressureSetting ), 0 );
}

/* 'C' function for method : 'Application::PressureSettings.onPressureSetting()' */
void ApplicationPressureSettings_onPressureSetting( ApplicationPressureSettings _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ApplicationPressureSettings_OnSetPressureSetting( _this, EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass )->PressureSetting );
}

/* 'C' function for method : 'Application::PressureSettings.onConfirm()' */
void ApplicationPressureSettings_onConfirm( ApplicationPressureSettings _this, XObject 
  sender )
{
  ApplicationConfirmationPopup popup;
  XString message;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  popup = EwNewObject( ApplicationConfirmationPopup, 0 );

  if ( popup == 0 )
    return;

  message = EwLoadString( &StringsConfirmPressureChangeText );
  message = ToolsHelperCollection_StringParamReplace( EwGetAutoObject( &ToolsHelper, 
  ToolsHelperCollection ), message, 1, EwNewStringInt( EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass )->PressureSetting, 0, 10 ));
  message = ToolsHelperCollection_StringParamReplace( EwGetAutoObject( &ToolsHelper, 
  ToolsHelperCollection ), message, 2, EwNewStringInt( _this->PressureSetting, 0, 
  10 ));
  NavigationPage__OnSetCaption( popup, EwLoadString( &StringsConfirmPressureChangeCaption ));
  ApplicationMessagePopup_OnSetMessage((ApplicationMessagePopup)popup, message );
  popup->OnConfirm = EwNewSlot( _this, ApplicationPressureSettings_doConfirm );
  popup->OnCancel = EwNewSlot( _this, ApplicationPressureSettings_onCancel );
  ApplicationPopupNavigatorClass_OpenPopup( EwGetAutoObject( &ApplicationPopupNavigator, 
  ApplicationPopupNavigatorClass ), ((ApplicationPopup)popup ), 0 );
}

/* 'C' function for method : 'Application::PressureSettings.doConfirm()' */
void ApplicationPressureSettings_doConfirm( ApplicationPressureSettings _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  DeviceDeviceClass_OnSetPressureSetting( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  _this->PressureSetting );
  DeviceDeviceClass_OnSetCurrentSettings( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  1 );
}

/* 'C' function for method : 'Application::PressureSettings.onCancel()' */
void ApplicationPressureSettings_onCancel( ApplicationPressureSettings _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ApplicationPressureSettings_OnSetPressureSetting( _this, EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass )->PressureSetting );
}

/* Default onget method for the property 'PressureSetting' */
XInt32 ApplicationPressureSettings_OnGetPressureSetting( ApplicationPressureSettings _this )
{
  return _this->PressureSetting;
}

/* Variants derived from the class : 'Application::PressureSettings' */
EW_DEFINE_CLASS_VARIANTS( ApplicationPressureSettings )
EW_END_OF_CLASS_VARIANTS( ApplicationPressureSettings )

/* Virtual Method Table (VMT) for the class : 'Application::PressureSettings' */
EW_DEFINE_CLASS( ApplicationPressureSettings, ApplicationSettingsPage, InfoTip, 
                 PressureSetting, PressureSetting, PressureSetting, PressureSetting, 
                 PressureSetting, "Application::PressureSettings" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsPage_onBack,
EW_END_OF_CLASS( ApplicationPressureSettings )

/* Initializer for the class 'Application::AirBubbleDetector' */
void ApplicationAirBubbleDetector__Init( ApplicationAirBubbleDetector _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationAirBubbleDetector );

  /* ... then construct all embedded objects */
  ComponentsIntSettingItem__Init( &_this->SingleBubbleThresholdItem, &_this->_.XObject, 0 );
  ComponentsIntSettingItem__Init( &_this->CumulativeBubbleThresholdItem, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationAirBubbleDetector );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsAirBubbleDetectorSettings ));
  CoreRectView__OnSetBounds( &_this->SingleBubbleThresholdItem, _Const003C );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->SingleBubbleThresholdItem, 
  EwLoadString( &StringsSingleBubbleThreshold ));
  ComponentsIntSettingItem_OnSetResolution( &_this->SingleBubbleThresholdItem, -1 );
  ComponentsIntSettingItem_OnSetMinValue( &_this->SingleBubbleThresholdItem, 2 );
  ComponentsIntSettingItem_OnSetMaxValue( &_this->SingleBubbleThresholdItem, 3 );
  ComponentsIntSettingItem_OnSetUnit( &_this->SingleBubbleThresholdItem, EwLoadString( 
  &StringsUnit_mL ));
  ComponentsIntSettingItem_OnSetPrecision( &_this->SingleBubbleThresholdItem, 1 );
  CoreRectView__OnSetBounds( &_this->CumulativeBubbleThresholdItem, _Const003D );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->CumulativeBubbleThresholdItem, 
  EwLoadString( &StringsCumulativeBubbleThreshold ));
  ComponentsIntSettingItem_OnSetResolution( &_this->CumulativeBubbleThresholdItem, 
  -1 );
  ComponentsIntSettingItem_OnSetMinValue( &_this->CumulativeBubbleThresholdItem, 
  30 );
  ComponentsIntSettingItem_OnSetMaxValue( &_this->CumulativeBubbleThresholdItem, 
  40 );
  ComponentsIntSettingItem_OnSetUnit( &_this->CumulativeBubbleThresholdItem, EwLoadString( 
  &StringsUnit_mL ));
  ComponentsIntSettingItem_OnSetPrecision( &_this->CumulativeBubbleThresholdItem, 
  1 );
  CoreGroup__Add( _this, ((CoreView)&_this->SingleBubbleThresholdItem ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->CumulativeBubbleThresholdItem ), 0 );
  ComponentsIntSettingItem_OnSetOutlet( &_this->SingleBubbleThresholdItem, EwNewRef( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetSingleBubbleThreshold, 
  DeviceDeviceClass_OnSetSingleBubbleThreshold ));
  ComponentsIntSettingItem_OnSetOutlet( &_this->CumulativeBubbleThresholdItem, EwNewRef( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetCumulativeBubbleThreshold, 
  DeviceDeviceClass_OnSetCumulativeBubbleThreshold ));
}

/* Re-Initializer for the class 'Application::AirBubbleDetector' */
void ApplicationAirBubbleDetector__ReInit( ApplicationAirBubbleDetector _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsIntSettingItem__ReInit( &_this->SingleBubbleThresholdItem );
  ComponentsIntSettingItem__ReInit( &_this->CumulativeBubbleThresholdItem );
}

/* Finalizer method for the class 'Application::AirBubbleDetector' */
void ApplicationAirBubbleDetector__Done( ApplicationAirBubbleDetector _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsPage );

  /* Finalize all embedded objects */
  ComponentsIntSettingItem__Done( &_this->SingleBubbleThresholdItem );
  ComponentsIntSettingItem__Done( &_this->CumulativeBubbleThresholdItem );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsPage__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Application::AirBubbleDetector' */
EW_DEFINE_CLASS_VARIANTS( ApplicationAirBubbleDetector )
EW_END_OF_CLASS_VARIANTS( ApplicationAirBubbleDetector )

/* Virtual Method Table (VMT) for the class : 'Application::AirBubbleDetector' */
EW_DEFINE_CLASS( ApplicationAirBubbleDetector, ApplicationSettingsPage, SingleBubbleThresholdItem, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::AirBubbleDetector" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsPage_onBack,
EW_END_OF_CLASS( ApplicationAirBubbleDetector )

/* Initializer for the class 'Application::DisplayAndBrightness' */
void ApplicationDisplayAndBrightness__Init( ApplicationDisplayAndBrightness _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationDisplayAndBrightness );

  /* ... then construct all embedded objects */
  ComponentsInfoTip__Init( &_this->InfoTip, &_this->_.XObject, 0 );
  WidgetSetHorizontalSlider__Init( &_this->HorzSlider, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->MinImage, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->MaxImage, &_this->_.XObject, 0 );
  WidgetSetHorizontalSliderConfig__Init( &_this->HorizontalSliderConfig, &_this->_.XObject, 0 );
  ComponentsTextButton__Init( &_this->ConfirmButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationDisplayAndBrightness );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsDisplayAndBrightness ));
  CoreRectView__OnSetBounds( &_this->Super1.ContentBackground, _Const003E );
  CoreRectView__OnSetBounds( &_this->InfoTip, _Const003F );
  ComponentsInfoTip_OnSetTipString( &_this->InfoTip, EwLoadString( &StringsBRIGHTNESS ));
  CoreRectView__OnSetBounds( &_this->HorzSlider, _Const0040 );
  CoreRectView__OnSetBounds( &_this->MinImage, _Const0041 );
  CoreRectView__OnSetBounds( &_this->MaxImage, _Const0042 );
  WidgetSetHorizontalSliderConfig_OnSetStateTransitionDuration( &_this->HorizontalSliderConfig, 
  50 );
  WidgetSetHorizontalSliderConfig_OnSetKeyRepeatPeriod( &_this->HorizontalSliderConfig, 
  30 );
  WidgetSetHorizontalSliderConfig_OnSetKeyRepeatDelay( &_this->HorizontalSliderConfig, 
  500 );
  WidgetSetHorizontalSliderConfig_OnSetAccentColorActive( &_this->HorizontalSliderConfig, 
  ResOnPrimary );
  WidgetSetHorizontalSliderConfig_OnSetAccentColorFocused( &_this->HorizontalSliderConfig, 
  ResTRANSPARENT );
  WidgetSetHorizontalSliderConfig_OnSetAccentColorDisabled( &_this->HorizontalSliderConfig, 
  ResTRANSPARENT );
  WidgetSetHorizontalSliderConfig_OnSetAccentColorDefault( &_this->HorizontalSliderConfig, 
  ResTRANSPARENT );
  WidgetSetHorizontalSliderConfig_OnSetAccentCornerRadiusActive( &_this->HorizontalSliderConfig, 
  24 );
  WidgetSetHorizontalSliderConfig_OnSetAccentCornerRadiusFocused( &_this->HorizontalSliderConfig, 
  24 );
  WidgetSetHorizontalSliderConfig_OnSetAccentCornerRadiusDisabled( &_this->HorizontalSliderConfig, 
  24 );
  WidgetSetHorizontalSliderConfig_OnSetAccentCornerRadiusDefault( &_this->HorizontalSliderConfig, 
  24 );
  WidgetSetHorizontalSliderConfig_OnSetAccentSizeActive( &_this->HorizontalSliderConfig, 
  _Const0043 );
  WidgetSetHorizontalSliderConfig_OnSetAccentSizeFocused( &_this->HorizontalSliderConfig, 
  _Const0043 );
  WidgetSetHorizontalSliderConfig_OnSetAccentSizeDisabled( &_this->HorizontalSliderConfig, 
  _Const0043 );
  WidgetSetHorizontalSliderConfig_OnSetAccentSizeDefault( &_this->HorizontalSliderConfig, 
  _Const0043 );
  WidgetSetHorizontalSliderConfig_OnSetThumbColorActive( &_this->HorizontalSliderConfig, 
  ResOnPrimary );
  WidgetSetHorizontalSliderConfig_OnSetThumbColorFocused( &_this->HorizontalSliderConfig, 
  ResOnPrimary );
  WidgetSetHorizontalSliderConfig_OnSetThumbColorDisabled( &_this->HorizontalSliderConfig, 
  ResOnSecondary );
  WidgetSetHorizontalSliderConfig_OnSetThumbColorDefault( &_this->HorizontalSliderConfig, 
  ResOnPrimary );
  WidgetSetHorizontalSliderConfig_OnSetThumbCornerRadiusActive( &_this->HorizontalSliderConfig, 
  18 );
  WidgetSetHorizontalSliderConfig_OnSetThumbCornerRadiusFocused( &_this->HorizontalSliderConfig, 
  18 );
  WidgetSetHorizontalSliderConfig_OnSetThumbCornerRadiusDisabled( &_this->HorizontalSliderConfig, 
  18 );
  WidgetSetHorizontalSliderConfig_OnSetThumbCornerRadiusDefault( &_this->HorizontalSliderConfig, 
  18 );
  WidgetSetHorizontalSliderConfig_OnSetThumbSizeActive( &_this->HorizontalSliderConfig, 
  _Const0044 );
  WidgetSetHorizontalSliderConfig_OnSetThumbSizeFocused( &_this->HorizontalSliderConfig, 
  _Const0044 );
  WidgetSetHorizontalSliderConfig_OnSetThumbSizeDisabled( &_this->HorizontalSliderConfig, 
  _Const0044 );
  WidgetSetHorizontalSliderConfig_OnSetThumbSizeDefault( &_this->HorizontalSliderConfig, 
  _Const0044 );
  WidgetSetHorizontalSliderConfig_OnSetThumbMarginRight( &_this->HorizontalSliderConfig, 
  18 );
  WidgetSetHorizontalSliderConfig_OnSetThumbMarginLeft( &_this->HorizontalSliderConfig, 
  18 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightColorActive( &_this->HorizontalSliderConfig, 
  ResSurface1 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightColorFocused( &_this->HorizontalSliderConfig, 
  ResSurface1 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightColorDefault( &_this->HorizontalSliderConfig, 
  ResSurface1 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightCornerRadiusActive( &_this->HorizontalSliderConfig, 
  10 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightCornerRadiusFocused( &_this->HorizontalSliderConfig, 
  10 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightCornerRadiusDisabled( &_this->HorizontalSliderConfig, 
  10 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightCornerRadiusDefault( &_this->HorizontalSliderConfig, 
  10 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightThicknessActive( &_this->HorizontalSliderConfig, 
  20 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightThicknessFocused( &_this->HorizontalSliderConfig, 
  20 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightThicknessDisabled( &_this->HorizontalSliderConfig, 
  20 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightThicknessDefault( &_this->HorizontalSliderConfig, 
  20 );
  WidgetSetHorizontalSliderConfig_OnSetTrackRightFlattened( &_this->HorizontalSliderConfig, 
  1 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftColorActive( &_this->HorizontalSliderConfig, 
  ResPrimary );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftColorFocused( &_this->HorizontalSliderConfig, 
  ResPrimary );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftColorDisabled( &_this->HorizontalSliderConfig, 
  ResOnSecondary );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftColorDefault( &_this->HorizontalSliderConfig, 
  ResPrimary );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftCornerRadiusActive( &_this->HorizontalSliderConfig, 
  10 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftCornerRadiusFocused( &_this->HorizontalSliderConfig, 
  10 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftCornerRadiusDisabled( &_this->HorizontalSliderConfig, 
  10 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftCornerRadiusDefault( &_this->HorizontalSliderConfig, 
  10 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftThicknessActive( &_this->HorizontalSliderConfig, 
  20 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftThicknessFocused( &_this->HorizontalSliderConfig, 
  20 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftThicknessDisabled( &_this->HorizontalSliderConfig, 
  20 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftThicknessDefault( &_this->HorizontalSliderConfig, 
  20 );
  WidgetSetHorizontalSliderConfig_OnSetTrackLeftFlattened( &_this->HorizontalSliderConfig, 
  1 );
  WidgetSetHorizontalSliderConfig_OnSetWidgetMinSize( &_this->HorizontalSliderConfig, 
  _Const0043 );
  CoreRectView__OnSetBounds( &_this->ConfirmButton, _Const003B );
  CoreGroup_OnSetEnabled((CoreGroup)&_this->ConfirmButton, 0 );
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)&_this->ConfirmButton, 
  ResSuccess );
  ComponentsBaseButton_OnSetBgColorPressed((ComponentsBaseButton)&_this->ConfirmButton, 
  ResSuccess );
  ComponentsTextButton__OnSetCaption( &_this->ConfirmButton, EwLoadString( &StringsCONFIRM ));
  ComponentsTextButton_OnSetCaptionColor( &_this->ConfirmButton, ResOnPrimary );
  CoreGroup__Add( _this, ((CoreView)&_this->InfoTip ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->HorzSlider ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->MinImage ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->MaxImage ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ConfirmButton ), 0 );
  _this->HorzSlider.OnChange = EwNewSlot( _this, ApplicationDisplayAndBrightness_onChange );
  WidgetSetHorizontalSlider_OnSetOutlet( &_this->HorzSlider, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetBrightness, DeviceDeviceClass_OnSetBrightness ));
  WidgetSetHorizontalSlider_OnSetAppearance( &_this->HorzSlider, &_this->HorizontalSliderConfig );
  ViewsImage_OnSetBitmap( &_this->MinImage, EwLoadResource( &Resmoon, ResourcesBitmap ));
  ViewsImage_OnSetBitmap( &_this->MaxImage, EwLoadResource( &Ressun, ResourcesBitmap ));
  _this->ConfirmButton.Super1.OnActivate = EwNewSlot( _this, ApplicationDisplayAndBrightness_onConfirm );

  /* Call the user defined constructor */
  ApplicationDisplayAndBrightness_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::DisplayAndBrightness' */
void ApplicationDisplayAndBrightness__ReInit( ApplicationDisplayAndBrightness _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsInfoTip__ReInit( &_this->InfoTip );
  WidgetSetHorizontalSlider__ReInit( &_this->HorzSlider );
  ViewsImage__ReInit( &_this->MinImage );
  ViewsImage__ReInit( &_this->MaxImage );
  WidgetSetHorizontalSliderConfig__ReInit( &_this->HorizontalSliderConfig );
  ComponentsTextButton__ReInit( &_this->ConfirmButton );
}

/* Finalizer method for the class 'Application::DisplayAndBrightness' */
void ApplicationDisplayAndBrightness__Done( ApplicationDisplayAndBrightness _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsPage );

  /* Finalize all embedded objects */
  ComponentsInfoTip__Done( &_this->InfoTip );
  WidgetSetHorizontalSlider__Done( &_this->HorzSlider );
  ViewsImage__Done( &_this->MinImage );
  ViewsImage__Done( &_this->MaxImage );
  WidgetSetHorizontalSliderConfig__Done( &_this->HorizontalSliderConfig );
  ComponentsTextButton__Done( &_this->ConfirmButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsPage__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationDisplayAndBrightness_Init( ApplicationDisplayAndBrightness _this, 
  XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  _this->initialBrightness = EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->Brightness;
  EwTrace( "%i", _this->initialBrightness );
}

/* 'C' function for method : 'Application::DisplayAndBrightness.onBack()' */
void ApplicationDisplayAndBrightness_onBack( ApplicationDisplayAndBrightness _this, 
  XObject sender )
{
  DeviceDeviceClass_OnSetBrightness( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  _this->initialBrightness );
  ApplicationSettingsPage_onBack((ApplicationSettingsPage)_this, sender );
}

/* 'C' function for method : 'Application::DisplayAndBrightness.onChange()' */
void ApplicationDisplayAndBrightness_onChange( ApplicationDisplayAndBrightness _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_OnSetEnabled((CoreGroup)&_this->ConfirmButton, 1 );
}

/* 'C' function for method : 'Application::DisplayAndBrightness.onConfirm()' */
void ApplicationDisplayAndBrightness_onConfirm( ApplicationDisplayAndBrightness _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( sender );

  DeviceDeviceClass_OnSetCurrentSettings( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  1 );
}

/* Variants derived from the class : 'Application::DisplayAndBrightness' */
EW_DEFINE_CLASS_VARIANTS( ApplicationDisplayAndBrightness )
EW_END_OF_CLASS_VARIANTS( ApplicationDisplayAndBrightness )

/* Virtual Method Table (VMT) for the class : 'Application::DisplayAndBrightness' */
EW_DEFINE_CLASS( ApplicationDisplayAndBrightness, ApplicationSettingsPage, InfoTip, 
                 initialBrightness, initialBrightness, initialBrightness, initialBrightness, 
                 initialBrightness, "Application::DisplayAndBrightness" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationDisplayAndBrightness_onBack,
EW_END_OF_CLASS( ApplicationDisplayAndBrightness )

/* Initializer for the class 'Application::BolusRateSettings' */
void ApplicationBolusRateSettings__Init( ApplicationBolusRateSettings _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationBolusRateSettings );

  /* ... then construct all embedded objects */
  ComponentsInfoTip__Init( &_this->InfoTip, &_this->_.XObject, 0 );
  ComponentsIntValueDisplay__Init( &_this->ValueDisplay, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->UnitText, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationBolusRateSettings );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsBolusSettings ));
  CoreRectView__OnSetBounds( &_this->Super1.ContentBackground, _Const0045 );
  CoreRectView__OnSetBounds( &_this->InfoTip, _Const0031 );
  ComponentsInfoTip_OnSetTipString( &_this->InfoTip, EwLoadString( &StringsStandardBolusRate ));
  _this->InfoTip.InfoCaption = EwShareString( EwLoadString( &StringsStandardBolusRateInfoCaption ));
  _this->InfoTip.InfoMessage = EwShareString( EwLoadString( &StringsStandardBolusRateInfoText ));
  CoreRectView__OnSetBounds( &_this->ValueDisplay, _Const0046 );
  ViewsText_OnSetAlignment((ViewsText)&_this->ValueDisplay, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->UnitText, _Const0047 );
  ViewsText_OnSetOverflowWarning( &_this->UnitText, 1 );
  ViewsText_OnSetAlignment( &_this->UnitText, ViewsTextAlignmentAlignHorzLeft | 
  ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->UnitText, EwLoadString( &StringsUnit_mLPerhour ));
  CoreGroup__Add( _this, ((CoreView)&_this->InfoTip ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ValueDisplay ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->UnitText ), 0 );
  ViewsText__OnSetFont( &_this->ValueDisplay, EwLoadResource( &FontsMedium, ResourcesFont ));
  ComponentsIntValueDisplay_OnSetOutlet( &_this->ValueDisplay, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetBolusRate, DeviceDeviceClass_OnSetBolusRate ));
  ViewsText__OnSetFont( &_this->UnitText, EwLoadResource( &FontsHeading3, ResourcesFont ));
}

/* Re-Initializer for the class 'Application::BolusRateSettings' */
void ApplicationBolusRateSettings__ReInit( ApplicationBolusRateSettings _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsInfoTip__ReInit( &_this->InfoTip );
  ComponentsIntValueDisplay__ReInit( &_this->ValueDisplay );
  ViewsText__ReInit( &_this->UnitText );
}

/* Finalizer method for the class 'Application::BolusRateSettings' */
void ApplicationBolusRateSettings__Done( ApplicationBolusRateSettings _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsPage );

  /* Finalize all embedded objects */
  ComponentsInfoTip__Done( &_this->InfoTip );
  ComponentsIntValueDisplay__Done( &_this->ValueDisplay );
  ViewsText__Done( &_this->UnitText );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsPage__Done( &_this->_.Super );
}

/* The method UpdateViewState() is invoked automatically after the state of the 
   component has been changed. This method can be overridden and filled with logic 
   to ensure the visual aspect of the component does reflect its current state. 
   For example, the 'enabled' state of the component can affect its colors (disabled 
   components may appear pale). In this case the logic of the method should modify 
   the respective color properties accordingly to the current 'enabled' state. 
   The current state of the component is passed as a set in the parameter aState. 
   It reflects the very basic component state like its visibility or the ability 
   to react to user inputs. Beside this common state, the method can also involve 
   any other variables used in the component as long as they reflect its current 
   state. For example, the toggle switch component can take in account its toggle 
   state 'on' or 'off' and change accordingly the location of the slider, etc.
   Usually, this method will be invoked automatically by the framework. Optionally 
   you can request its invocation by using the method @InvalidateViewState(). */
void ApplicationBolusRateSettings_UpdateViewState( ApplicationBolusRateSettings _this, 
  XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ViewsText_OnSetColor((ViewsText)&_this->ValueDisplay, ResOnPrimary );
  ViewsText_OnSetColor( &_this->UnitText, ResOnSecondary );
}

/* Variants derived from the class : 'Application::BolusRateSettings' */
EW_DEFINE_CLASS_VARIANTS( ApplicationBolusRateSettings )
EW_END_OF_CLASS_VARIANTS( ApplicationBolusRateSettings )

/* Virtual Method Table (VMT) for the class : 'Application::BolusRateSettings' */
EW_DEFINE_CLASS( ApplicationBolusRateSettings, ApplicationSettingsPage, InfoTip, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::BolusRateSettings" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  ApplicationBolusRateSettings_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsPage_onBack,
EW_END_OF_CLASS( ApplicationBolusRateSettings )

/* Initializer for the class 'Application::KVOSettings' */
void ApplicationKVOSettings__Init( ApplicationKVOSettings _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationKVOSettings );

  /* ... then construct all embedded objects */
  ComponentsToggleButton__Init( &_this->KVOModeToggle, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->KVOModeText, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->KVORatesBg, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->KVORatesLabel, &_this->_.XObject, 0 );
  ViewsAttrText__Init( &_this->KVORatesInfo, &_this->_.XObject, 0 );
  GraphicsAttrSet__Init( &_this->AttrSet, &_this->_.XObject, 0 );
  ComponentsTextButton__Init( &_this->ConfirmButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationKVOSettings );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsKVOSettings ));
  CoreRectView__OnSetBounds( &_this->Super1.ContentBackground, _Const0048 );
  CoreRectView__OnSetBounds( &_this->KVOModeToggle, _Const0049 );
  CoreRectView__OnSetBounds( &_this->KVOModeText, _Const004A );
  ViewsText_OnSetOverflowWarning( &_this->KVOModeText, 1 );
  ViewsText_OnSetAlignment( &_this->KVOModeText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->KVOModeText, EwLoadString( &StringsKVOMode ));
  ViewsText_OnSetColor( &_this->KVOModeText, ResOnPrimary );
  CoreRectView__OnSetBounds( &_this->KVORatesBg, _Const004B );
  ViewsRectangle_OnSetRadius( &_this->KVORatesBg, 30 );
  ViewsRectangle_OnSetColor( &_this->KVORatesBg, ResSurface2 );
  ViewsRectangle_OnSetVisible( &_this->KVORatesBg, 0 );
  CoreRectView__OnSetBounds( &_this->KVORatesLabel, _Const004C );
  ViewsText_OnSetOverflowWarning( &_this->KVORatesLabel, 1 );
  ViewsText_OnSetAlignment( &_this->KVORatesLabel, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertTop );
  ViewsText__OnSetString( &_this->KVORatesLabel, EwLoadString( &StringsKVORates ));
  ViewsText_OnSetColor( &_this->KVORatesLabel, ResOnPrimary );
  ViewsText_OnSetVisible( &_this->KVORatesLabel, 0 );
  CoreRectView__OnSetBounds( &_this->KVORatesInfo, _Const004D );
  ViewsAttrText_OnSetAlignment( &_this->KVORatesInfo, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertTop );
  ViewsAttrText_OnSetVisible( &_this->KVORatesInfo, 0 );
  GraphicsAttrSet_OnSetColor0( &_this->AttrSet, ResOnPrimary );
  CoreRectView__OnSetBounds( &_this->ConfirmButton, _Const003B );
  CoreGroup_OnSetEnabled((CoreGroup)&_this->ConfirmButton, 0 );
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)&_this->ConfirmButton, 
  ResSuccess );
  ComponentsBaseButton_OnSetBgColorPressed((ComponentsBaseButton)&_this->ConfirmButton, 
  ResSuccess );
  ComponentsTextButton__OnSetCaption( &_this->ConfirmButton, EwLoadString( &StringsCONFIRM ));
  ComponentsTextButton_OnSetCaptionColor( &_this->ConfirmButton, ResOnPrimary );
  CoreGroup__Add( _this, ((CoreView)&_this->KVOModeToggle ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KVOModeText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KVORatesBg ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KVORatesLabel ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KVORatesInfo ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ConfirmButton ), 0 );
  ComponentsToggleButton_OnSetOutlet( &_this->KVOModeToggle, EwNewRef( _this, ApplicationKVOSettings_OnGetKVOMode, 
  ApplicationKVOSettings_OnSetKVOMode ));
  ViewsText__OnSetFont( &_this->KVOModeText, EwLoadResource( &FontsHeading3, ResourcesFont ));
  ViewsText__OnSetFont( &_this->KVORatesLabel, EwLoadResource( &FontsHeading3, ResourcesFont ));
  ViewsAttrText_OnSetAttrSet( &_this->KVORatesInfo, &_this->AttrSet );
  GraphicsAttrSet_OnSetFont0( &_this->AttrSet, EwLoadResource( &FontsHeading3, ResourcesFont ));
  GraphicsAttrSet_OnSetBitmap0( &_this->AttrSet, EwLoadResource( &Resbullet_30px, 
  ResourcesBitmap ));
  _this->ConfirmButton.Super1.OnActivate = EwNewSlot( _this, ApplicationKVOSettings_onConfirm );

  /* Call the user defined constructor */
  ApplicationKVOSettings_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::KVOSettings' */
void ApplicationKVOSettings__ReInit( ApplicationKVOSettings _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsToggleButton__ReInit( &_this->KVOModeToggle );
  ViewsText__ReInit( &_this->KVOModeText );
  ViewsRectangle__ReInit( &_this->KVORatesBg );
  ViewsText__ReInit( &_this->KVORatesLabel );
  ViewsAttrText__ReInit( &_this->KVORatesInfo );
  GraphicsAttrSet__ReInit( &_this->AttrSet );
  ComponentsTextButton__ReInit( &_this->ConfirmButton );
}

/* Finalizer method for the class 'Application::KVOSettings' */
void ApplicationKVOSettings__Done( ApplicationKVOSettings _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsPage );

  /* Finalize all embedded objects */
  ComponentsToggleButton__Done( &_this->KVOModeToggle );
  ViewsText__Done( &_this->KVOModeText );
  ViewsRectangle__Done( &_this->KVORatesBg );
  ViewsText__Done( &_this->KVORatesLabel );
  ViewsAttrText__Done( &_this->KVORatesInfo );
  GraphicsAttrSet__Done( &_this->AttrSet );
  ComponentsTextButton__Done( &_this->ConfirmButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsPage__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationKVOSettings_Init( ApplicationKVOSettings _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  EwAttachRefObserver( EwNewSlot( _this, ApplicationKVOSettings_onKVOMode ), EwNewRef( 
    EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetKVOMode, 
    DeviceDeviceClass_OnSetKVOMode ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationKVOSettings_onKVOMode ), ((XObject)_this ));
  EwAttachRefObserver( EwNewSlot( _this, ApplicationKVOSettings_onKVORates ), EwNewRef( 
    EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetKVORateHighFlowRate, 
    DeviceDeviceClass_OnSetKVORateHighFlowRate ), 0 );
  EwAttachRefObserver( EwNewSlot( _this, ApplicationKVOSettings_onKVORates ), EwNewRef( 
    EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetKVORateMediumFlowRate, 
    DeviceDeviceClass_OnSetKVORateMediumFlowRate ), 0 );
  EwAttachRefObserver( EwNewSlot( _this, ApplicationKVOSettings_onKVORates ), EwNewRef( 
    EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetKVORateLowFlowRate, 
    DeviceDeviceClass_OnSetKVORateLowFlowRate ), 0 );
  EwAttachRefObserver( EwNewSlot( _this, ApplicationKVOSettings_onKVORates ), EwNewRef( 
    EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetFlowRateMedium, 
    DeviceDeviceClass_OnSetFlowRateMedium ), 0 );
  EwAttachRefObserver( EwNewSlot( _this, ApplicationKVOSettings_onKVORates ), EwNewRef( 
    EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetFlowRateLow, 
    DeviceDeviceClass_OnSetFlowRateLow ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationKVOSettings_onKVORates ), ((XObject)_this ));
}

/* 'C' function for method : 'Application::KVOSettings.onKVOMode()' */
void ApplicationKVOSettings_onKVOMode( ApplicationKVOSettings _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ApplicationKVOSettings_OnSetKVOMode( _this, EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->KVOMode );
}

/* 'C' function for method : 'Application::KVOSettings.onKVORates()' */
void ApplicationKVOSettings_onKVORates( ApplicationKVOSettings _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ViewsAttrText_OnSetString( &_this->KVORatesInfo, EwConcatString( EwConcatString( 
  EwConcatString( EwConcatString( ApplicationKVOSettings_formatKVORate( _this, EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass )->FlowRateMedium, EwLoadString( &_Const004E ), 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->KVORateHighFlowRate, 0 ), 
  EwLoadString( &_Const004F )), ApplicationKVOSettings_formatKVORate( _this, EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass )->FlowRateMedium, EwLoadString( &_Const0050 ), 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->KVORateMediumFlowRate, 0 )), 
  EwLoadString( &_Const004F )), ApplicationKVOSettings_formatKVORate( _this, EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass )->FlowRateLow, EwLoadString( &_Const0050 ), 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->KVORateLowFlowRate, 1 )));
}

/* 'C' function for method : 'Application::KVOSettings.formatKVORate()' */
XString ApplicationKVOSettings_formatKVORate( ApplicationKVOSettings _this, XInt32 
  aFlowRate, XString aOperator, XInt32 aKVORate, XInt32 aKVORatePrecision )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  return EwConcatString( EwConcatString( EwConcatString( EwConcatString( EwConcatString( 
    EwConcatString( EwConcatString( EwConcatString( EwConcatString( EwConcatString( 
    EwConcatString( EwConcatString( EwConcatString( EwConcatString( EwLoadString( 
    &_Const0051 ), EwLoadString( &StringsFlowRate )), EwLoadString( &_Const0052 )), 
    aOperator ), EwLoadString( &_Const0052 )), ToolsHelperCollection_FormatInt32Value( 
    EwGetAutoObject( &ToolsHelper, ToolsHelperCollection ), aFlowRate, -2, 0 )), 
    EwLoadString( &_Const0052 )), EwLoadString( &StringsUnit_mLPerhour )), EwLoadString( 
    &_Const0053 )), EwLoadString( &_Const0052 )), EwLoadString( &StringsKVORate )), 
    EwLoadString( &_Const0054 )), ToolsHelperCollection_FormatInt32Value( EwGetAutoObject( 
    &ToolsHelper, ToolsHelperCollection ), aKVORate, -2, aKVORatePrecision )), EwLoadString( 
    &_Const0052 )), EwLoadString( &StringsUnit_mLPerhour ));
}

/* 'C' function for method : 'Application::KVOSettings.onConfirm()' */
void ApplicationKVOSettings_onConfirm( ApplicationKVOSettings _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  DeviceDeviceClass_OnSetKVOMode( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  _this->KVOMode );
  DeviceDeviceClass_OnSetCurrentSettings( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  1 );
}

/* 'C' function for method : 'Application::KVOSettings.OnSetKVOMode()' */
void ApplicationKVOSettings_OnSetKVOMode( ApplicationKVOSettings _this, XBool value )
{
  if ( _this->KVOMode == value )
    return;

  _this->KVOMode = value;
  ViewsRectangle_OnSetVisible( &_this->KVORatesBg, value );
  ViewsText_OnSetVisible( &_this->KVORatesLabel, value );
  ViewsAttrText_OnSetVisible( &_this->KVORatesInfo, value );
  CoreGroup_OnSetEnabled((CoreGroup)&_this->ConfirmButton, (XBool)( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass )->KVOMode != value ));
  EwNotifyRefObservers( EwNewRef( _this, ApplicationKVOSettings_OnGetKVOMode, ApplicationKVOSettings_OnSetKVOMode ), 
    0 );
}

/* Default onget method for the property 'KVOMode' */
XBool ApplicationKVOSettings_OnGetKVOMode( ApplicationKVOSettings _this )
{
  return _this->KVOMode;
}

/* Variants derived from the class : 'Application::KVOSettings' */
EW_DEFINE_CLASS_VARIANTS( ApplicationKVOSettings )
EW_END_OF_CLASS_VARIANTS( ApplicationKVOSettings )

/* Virtual Method Table (VMT) for the class : 'Application::KVOSettings' */
EW_DEFINE_CLASS( ApplicationKVOSettings, ApplicationSettingsPage, KVOModeToggle, 
                 KVOMode, KVOMode, KVOMode, KVOMode, KVOMode, "Application::KVOSettings" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsPage_onBack,
EW_END_OF_CLASS( ApplicationKVOSettings )

/* Initializer for the class 'Application::GeneralSettings' */
void ApplicationGeneralSettings__Init( ApplicationGeneralSettings _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationGeneralSettings );

  /* ... then construct all embedded objects */
  ComponentsVertScrollbar__Init( &_this->VertScrollbar, &_this->_.XObject, 0 );
  CoreSlideTouchHandler__Init( &_this->SlideTouchHandler, &_this->_.XObject, 0 );
  CoreOutline__Init( &_this->Outline, &_this->_.XObject, 0 );
  ComponentsSettingsOpenButton__Init( &_this->WifiButton, &_this->_.XObject, 0 );
  ComponentsSettingsOpenButton__Init( &_this->AudioVolumeControlButton, &_this->_.XObject, 0 );
  ComponentsSettingsOpenButton__Init( &_this->DateAndTimeButton, &_this->_.XObject, 0 );
  ComponentsSettingsOpenButton__Init( &_this->LanguageButton, &_this->_.XObject, 0 );
  ComponentsSettingsOpenButton__Init( &_this->SoftwareUpdateButton, &_this->_.XObject, 0 );
  ComponentsSettingsOpenButton__Init( &_this->AboutButton, &_this->_.XObject, 0 );
  ComponentsSettingsOpenButton__Init( &_this->MaintenaceAndCalibrationButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationGeneralSettings );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsGeneral ));
  ViewsRectangle_OnSetVisible( &_this->Super1.ContentBackground, 0 );
  CoreRectView__OnSetBounds( &_this->VertScrollbar, _Const0055 );
  CoreRectView__OnSetBounds( &_this->SlideTouchHandler, _Const0056 );
  _this->SlideTouchHandler.SlideHorz = 0;
  CoreRectView__OnSetBounds( &_this->Outline, _Const0057 );
  CoreOutline_OnSetSpaceVert( &_this->Outline, 20 );
  CoreOutline_OnSetFormation( &_this->Outline, CoreFormationTopToBottom );
  CoreRectView__OnSetBounds( &_this->WifiButton, _Const0058 );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->WifiButton, 1 );
  ComponentsTextButton__OnSetCaption( &_this->WifiButton, EwLoadString( &StringsWiFiSettings ));
  _this->WifiButton.Super1.SettingsPage = DeviceSettingsPageWifi;
  CoreRectView__OnSetBounds( &_this->AudioVolumeControlButton, _Const0059 );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->AudioVolumeControlButton, 1 );
  ComponentsTextButton__OnSetCaption( &_this->AudioVolumeControlButton, EwLoadString( 
  &StringsAudioVolumeControl ));
  _this->AudioVolumeControlButton.Super1.SettingsPage = DeviceSettingsPageAudioVolumeControl;
  ComponentsSettingsOpenButton_OnSetIconBgColor( &_this->AudioVolumeControlButton, 
  ResRed );
  CoreRectView__OnSetBounds( &_this->DateAndTimeButton, _Const005A );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->DateAndTimeButton, 1 );
  ComponentsTextButton__OnSetCaption( &_this->DateAndTimeButton, EwLoadString( &StringsDateTimeSettings ));
  _this->DateAndTimeButton.Super1.SettingsPage = DeviceSettingsPageDateAndTime;
  ComponentsSettingsOpenButton_OnSetIconBgColor( &_this->DateAndTimeButton, ResIndigo );
  CoreRectView__OnSetBounds( &_this->LanguageButton, _Const005B );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->LanguageButton, 1 );
  ComponentsTextButton__OnSetCaption( &_this->LanguageButton, EwLoadString( &StringsLanguageSelection ));
  _this->LanguageButton.Super1.SettingsPage = DeviceSettingsPageLanguage;
  ComponentsSettingsOpenButton_OnSetIconBgColor( &_this->LanguageButton, ResCyan );
  CoreRectView__OnSetBounds( &_this->SoftwareUpdateButton, _Const005C );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->SoftwareUpdateButton, 1 );
  ComponentsTextButton__OnSetCaption( &_this->SoftwareUpdateButton, EwLoadString( 
  &StringsSoftwareUpdate ));
  _this->SoftwareUpdateButton.Super1.SettingsPage = DeviceSettingsPageSoftwareUpdate;
  ComponentsSettingsOpenButton_OnSetIconBgColor( &_this->SoftwareUpdateButton, ResGray2 );
  CoreRectView__OnSetBounds( &_this->AboutButton, _Const005D );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->AboutButton, 1 );
  ComponentsTextButton__OnSetCaption( &_this->AboutButton, EwLoadString( &StringsAbout ));
  _this->AboutButton.Super1.SettingsPage = DeviceSettingsPageAbout;
  ComponentsSettingsOpenButton_OnSetIconBgColor( &_this->AboutButton, ResGray );
  CoreRectView__OnSetBounds( &_this->MaintenaceAndCalibrationButton, _Const005E );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->MaintenaceAndCalibrationButton, 1 );
  ComponentsTextButton__OnSetCaption( &_this->MaintenaceAndCalibrationButton, EwLoadString( 
  &StringsMaintenanceAndCalibration ));
  _this->MaintenaceAndCalibrationButton.Super1.SettingsPage = DeviceSettingsPageMaintenanceAndCalibration;
  ComponentsSettingsOpenButton_OnSetIconBgColor( &_this->MaintenaceAndCalibrationButton, 
  ResDeepIndigo );
  CoreGroup__Add( _this, ((CoreView)&_this->VertScrollbar ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->SlideTouchHandler ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Outline ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->WifiButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->AudioVolumeControlButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->DateAndTimeButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->LanguageButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->SoftwareUpdateButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->AboutButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->MaintenaceAndCalibrationButton ), 0 );
  _this->Outline.OnUpdate = EwNewSlot( _this, ApplicationGeneralSettings_updateScrollBar );
  CoreOutline_OnSetSlideHandler( &_this->Outline, &_this->SlideTouchHandler );
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->WifiButton, 
  EwLoadResource( &Reswifi_excelent, ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->AudioVolumeControlButton, 
  EwLoadResource( &Resaudio_volume, ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->DateAndTimeButton, 
  EwLoadResource( &Rescalendar_clock, ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->LanguageButton, 
  EwLoadResource( &Resglobe, ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->SoftwareUpdateButton, 
  EwLoadResource( &Ressettings, ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->AboutButton, 
  EwLoadResource( &Resinfo, ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->MaintenaceAndCalibrationButton, 
  EwLoadResource( &Resinfo, ResourcesBitmap ));
}

/* Re-Initializer for the class 'Application::GeneralSettings' */
void ApplicationGeneralSettings__ReInit( ApplicationGeneralSettings _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsVertScrollbar__ReInit( &_this->VertScrollbar );
  CoreSlideTouchHandler__ReInit( &_this->SlideTouchHandler );
  CoreOutline__ReInit( &_this->Outline );
  ComponentsSettingsOpenButton__ReInit( &_this->WifiButton );
  ComponentsSettingsOpenButton__ReInit( &_this->AudioVolumeControlButton );
  ComponentsSettingsOpenButton__ReInit( &_this->DateAndTimeButton );
  ComponentsSettingsOpenButton__ReInit( &_this->LanguageButton );
  ComponentsSettingsOpenButton__ReInit( &_this->SoftwareUpdateButton );
  ComponentsSettingsOpenButton__ReInit( &_this->AboutButton );
  ComponentsSettingsOpenButton__ReInit( &_this->MaintenaceAndCalibrationButton );
}

/* Finalizer method for the class 'Application::GeneralSettings' */
void ApplicationGeneralSettings__Done( ApplicationGeneralSettings _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsPage );

  /* Finalize all embedded objects */
  ComponentsVertScrollbar__Done( &_this->VertScrollbar );
  CoreSlideTouchHandler__Done( &_this->SlideTouchHandler );
  CoreOutline__Done( &_this->Outline );
  ComponentsSettingsOpenButton__Done( &_this->WifiButton );
  ComponentsSettingsOpenButton__Done( &_this->AudioVolumeControlButton );
  ComponentsSettingsOpenButton__Done( &_this->DateAndTimeButton );
  ComponentsSettingsOpenButton__Done( &_this->LanguageButton );
  ComponentsSettingsOpenButton__Done( &_this->SoftwareUpdateButton );
  ComponentsSettingsOpenButton__Done( &_this->AboutButton );
  ComponentsSettingsOpenButton__Done( &_this->MaintenaceAndCalibrationButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsPage__Done( &_this->_.Super );
}

/* 'C' function for method : 'Application::GeneralSettings.updateScrollBar()' */
void ApplicationGeneralSettings_updateScrollBar( ApplicationGeneralSettings _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ComponentsVertScrollbar_OnSetContentArea( &_this->VertScrollbar, EwGetRectH( CoreOutline_GetContentArea( 
  &_this->Outline, CoreViewStateVisible )));
  ComponentsVertScrollbar_OnSetViewArea( &_this->VertScrollbar, EwGetRectH( _this->Outline.Super1.Bounds ));
  ComponentsVertScrollbar_OnSetPosition( &_this->VertScrollbar, -_this->Outline.ScrollOffset.Y );
}

/* Variants derived from the class : 'Application::GeneralSettings' */
EW_DEFINE_CLASS_VARIANTS( ApplicationGeneralSettings )
EW_END_OF_CLASS_VARIANTS( ApplicationGeneralSettings )

/* Virtual Method Table (VMT) for the class : 'Application::GeneralSettings' */
EW_DEFINE_CLASS( ApplicationGeneralSettings, ApplicationSettingsPage, VertScrollbar, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::GeneralSettings" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsPage_onBack,
EW_END_OF_CLASS( ApplicationGeneralSettings )

/* Initializer for the class 'Application::MenuPopup' */
void ApplicationMenuPopup__Init( ApplicationMenuPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationBaseMenuPopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationMenuPopup );

  /* ... then construct all embedded objects */
  ViewsText__Init( &_this->CaptionText, &_this->_.XObject, 0 );
  ComponentsTextButton__Init( &_this->CancelButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationMenuPopup );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const005F );
  _this->Super2.FadeBackground = 1;
  CoreRectView__OnSetBounds( &_this->CaptionText, _Const0060 );
  ViewsText_OnSetOverflowWarning( &_this->CaptionText, 1 );
  ViewsText_OnSetAlignment( &_this->CaptionText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertTop );
  CoreRectView__OnSetBounds( &_this->CancelButton, _Const0061 );
  ComponentsTextButton__OnSetCaption( &_this->CancelButton, EwLoadString( &StringsCANCEL ));
  CoreGroup__Add( _this, ((CoreView)&_this->CaptionText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->CancelButton ), 0 );
  ViewsText__OnSetFont( &_this->CaptionText, EwLoadResource( &FontsHeading2, ResourcesFont ));
  _this->CancelButton.Super1.OnActivate = EwNewSlot( _this, ApplicationMenuPopup_onCancel );

  /* Call the user defined constructor */
  ApplicationMenuPopup_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::MenuPopup' */
void ApplicationMenuPopup__ReInit( ApplicationMenuPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationBaseMenuPopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsText__ReInit( &_this->CaptionText );
  ComponentsTextButton__ReInit( &_this->CancelButton );
}

/* Finalizer method for the class 'Application::MenuPopup' */
void ApplicationMenuPopup__Done( ApplicationMenuPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationBaseMenuPopup );

  /* Finalize all embedded objects */
  ViewsText__Done( &_this->CaptionText );
  ComponentsTextButton__Done( &_this->CancelButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationBaseMenuPopup__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationMenuPopup_Init( ApplicationMenuPopup _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* The method UpdateViewState() is invoked automatically after the state of the 
   component has been changed. This method can be overridden and filled with logic 
   to ensure the visual aspect of the component does reflect its current state. 
   For example, the 'enabled' state of the component can affect its colors (disabled 
   components may appear pale). In this case the logic of the method should modify 
   the respective color properties accordingly to the current 'enabled' state. 
   The current state of the component is passed as a set in the parameter aState. 
   It reflects the very basic component state like its visibility or the ability 
   to react to user inputs. Beside this common state, the method can also involve 
   any other variables used in the component as long as they reflect its current 
   state. For example, the toggle switch component can take in account its toggle 
   state 'on' or 'off' and change accordingly the location of the slider, etc.
   Usually, this method will be invoked automatically by the framework. Optionally 
   you can request its invocation by using the method @InvalidateViewState(). */
void ApplicationMenuPopup_UpdateViewState( ApplicationMenuPopup _this, XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ViewsText_OnSetColor( &_this->CaptionText, ResOnPrimary );
}

/* 'C' function for method : 'Application::MenuPopup.OnSetCaption()' */
void ApplicationMenuPopup_OnSetCaption( ApplicationMenuPopup _this, XString value )
{
  NavigationPage_OnSetCaption((NavigationPage)_this, value );
  ViewsText__OnSetString( &_this->CaptionText, value );
}

/* 'C' function for method : 'Application::MenuPopup.onCancel()' */
void ApplicationMenuPopup_onCancel( ApplicationMenuPopup _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ApplicationPopupNavigatorClass_ClosePopup( EwGetAutoObject( &ApplicationPopupNavigator, 
  ApplicationPopupNavigatorClass ), ((ApplicationPopup)_this ), 0 );
}

/* Variants derived from the class : 'Application::MenuPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationMenuPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationMenuPopup )

/* Virtual Method Table (VMT) for the class : 'Application::MenuPopup' */
EW_DEFINE_CLASS( ApplicationMenuPopup, ApplicationBaseMenuPopup, CaptionText, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Application::MenuPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  ApplicationMenuPopup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationMenuPopup_OnSetCaption,
  NavigationPage_onClose,
EW_END_OF_CLASS( ApplicationMenuPopup )

/* Initializer for the class 'Application::PopupContainer' */
void ApplicationPopupContainer__Init( ApplicationPopupContainer _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  NavigationContainer__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationPopupContainer );

  /* ... then construct all embedded objects */
  ViewsRectangle__Init( &_this->Scrim, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationPopupContainer );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( &_this->Scrim, _Const0009 );
  ViewsRectangle_OnSetColor( &_this->Scrim, ResOverlayOpaque );
  ViewsRectangle_OnSetVisible( &_this->Scrim, 0 );
  _this->ScrimColor = ResOverlayOpaque;
  CoreGroup__Add( _this, ((CoreView)&_this->Scrim ), 0 );
  _this->Super1.DontTouchBehind.OnPress = EwNewSlot( _this, ApplicationPopupContainer_onTouchOutside );
}

/* Re-Initializer for the class 'Application::PopupContainer' */
void ApplicationPopupContainer__ReInit( ApplicationPopupContainer _this )
{
  /* At first re-initialize the super class ... */
  NavigationContainer__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsRectangle__ReInit( &_this->Scrim );
}

/* Finalizer method for the class 'Application::PopupContainer' */
void ApplicationPopupContainer__Done( ApplicationPopupContainer _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( NavigationContainer );

  /* Finalize all embedded objects */
  ViewsRectangle__Done( &_this->Scrim );

  /* Don't forget to deinitialize the super class ... */
  NavigationContainer__Done( &_this->_.Super );
}

/* 'C' function for method : 'Application::PopupContainer.OnSetFadeBackground()' */
void ApplicationPopupContainer_OnSetFadeBackground( ApplicationPopupContainer _this, 
  XBool value )
{
  if ( _this->FadeBackground == value )
    return;

  _this->FadeBackground = value;
  ViewsRectangle_OnSetVisible( &_this->Scrim, value );
}

/* 'C' function for method : 'Application::PopupContainer.onTouchOutside()' */
void ApplicationPopupContainer_onTouchOutside( ApplicationPopupContainer _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( sender );
}

/* 'C' function for method : 'Application::PopupContainer.OnSetScrimColor()' */
void ApplicationPopupContainer_OnSetScrimColor( ApplicationPopupContainer _this, 
  XColor value )
{
  if ( !EwCompColor( _this->ScrimColor, value ))
    return;

  _this->ScrimColor = value;
  ViewsRectangle_OnSetColor( &_this->Scrim, value );
}

/* Variants derived from the class : 'Application::PopupContainer' */
EW_DEFINE_CLASS_VARIANTS( ApplicationPopupContainer )
EW_END_OF_CLASS_VARIANTS( ApplicationPopupContainer )

/* Virtual Method Table (VMT) for the class : 'Application::PopupContainer' */
EW_DEFINE_CLASS( ApplicationPopupContainer, NavigationContainer, Scrim, ScrimColor, 
                 ScrimColor, ScrimColor, ScrimColor, ScrimColor, "Application::PopupContainer" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  NavigationContainer_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ApplicationPopupContainer )

/* Initializer for the class 'Application::PopupNavigatorClass' */
void ApplicationPopupNavigatorClass__Init( ApplicationPopupNavigatorClass _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  NavigationNavigatorClass__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationPopupNavigatorClass );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationPopupNavigatorClass );
}

/* Re-Initializer for the class 'Application::PopupNavigatorClass' */
void ApplicationPopupNavigatorClass__ReInit( ApplicationPopupNavigatorClass _this )
{
  /* At first re-initialize the super class ... */
  NavigationNavigatorClass__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Application::PopupNavigatorClass' */
void ApplicationPopupNavigatorClass__Done( ApplicationPopupNavigatorClass _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( NavigationNavigatorClass );

  /* Don't forget to deinitialize the super class ... */
  NavigationNavigatorClass__Done( &_this->_.Super );
}

/* 'C' function for method : 'Application::PopupNavigatorClass.CloseCurrentPageWithTransition()' */
XBool ApplicationPopupNavigatorClass_CloseCurrentPageWithTransition( ApplicationPopupNavigatorClass _this, 
  EffectsTransition aCloseTransition, XBool aCombine )
{
  XBool result;

  if (( aCloseTransition == 0 ) && ( _this->resizeEffect != 0 ))
  {
    if ( _this->resizeEffect->Super1.Enabled )
    {
      _this->resizeEffect->Value1 = _this->resizeEffect->Value;
      EffectsEffect_OnSetEnabled((EffectsEffect)_this->resizeEffect, 0 );
    }

    EffectsEffect_OnSetReversed((EffectsEffect)_this->resizeEffect, 1 );
    _this->resizeEffect->Super1.OnFinished = EwNewSlot( _this, ApplicationPopupNavigatorClass_onResizeFinish );
    EffectsEffect_OnSetEnabled((EffectsEffect)_this->resizeEffect, 1 );

    if ( _this->fadeEffect != 0 )
    {
      if ( _this->fadeEffect->Super1.Enabled )
      {
        _this->fadeEffect->Value1 = _this->fadeEffect->Value;
        EffectsEffect_OnSetEnabled((EffectsEffect)_this->fadeEffect, 0 );
      }

      EffectsEffect_OnSetReversed((EffectsEffect)_this->fadeEffect, 1 );
      _this->fadeEffect->Super1.OnFinished = EwNewSlot( _this, ApplicationPopupNavigatorClass_onFadeFinish );
      EffectsEffect_OnSetEnabled((EffectsEffect)_this->fadeEffect, 1 );
    }

    return 1;
  }

  result = NavigationNavigatorClass_CloseCurrentPageWithTransition((NavigationNavigatorClass)_this, 
  aCloseTransition, aCombine );
  ApplicationPopupNavigatorClass_updateContainer( _this, ApplicationPopupNavigatorClass_GetCurrentPopup( 
  _this ));
  return result;
}

/* 'C' function for method : 'Application::PopupNavigatorClass.OpenPopupWithEffectByType()' */
ApplicationPopup ApplicationPopupNavigatorClass_OpenPopupWithEffectByType( ApplicationPopupNavigatorClass _this, 
  XEnum aType, XRect aStartArea, XEnum aAlign )
{
  ApplicationPopup popup;

  if ( _this->Super1.Container == 0 )
    return 0;

  if ( ApplicationPopupNavigatorClass_checkAnimationInProgress( _this ))
    return 0;

  popup = EwCastObject( EwNewObjectIndirect( ApplicationPopupNavigatorClass_getPopupClass( 
  _this, aType ), 0 ), ApplicationPopup );

  if ( popup == 0 )
    return 0;

  return ApplicationPopupNavigatorClass_OpenPopupWithEffect( _this, popup, aStartArea, 
    aAlign );
}

/* This method opens the page provides as parameter in aPageView. If parameter aClosePrevPageTransition 
   is not null, the previous page is closed with this transation, otherwise with 
   the transation configured on the page view.
   If parameter aOpenTransition is not null, the current page is opened with this 
   transation, otherwise with the transation configured on the page view.
   If aCombineTransitions is true the transitions for closing the previous page 
   and opening the current one will be executed simultaneously, otherwise will be 
   executed one after another. */
ApplicationPopup ApplicationPopupNavigatorClass_OpenPopup( ApplicationPopupNavigatorClass _this, 
  ApplicationPopup aPopup, EffectsTransition aOpenTransition )
{
  XBool result;

  if ( aPopup == 0 )
    return 0;

  if ( ApplicationPopupNavigatorClass_checkAnimationInProgress( _this ))
    return 0;

  result = NavigationNavigatorClass_OpenPageWithTransition((NavigationNavigatorClass)_this, 
  ((NavigationPage)aPopup ), 0, aOpenTransition, 0 );

  if ( result )
    ApplicationPopupNavigatorClass_updateContainer( _this, aPopup );

  return EwCastObject( _this->Super1.currentPage, ApplicationPopup );
}

/* This method opens the page provides as parameter in aPageView. If parameter aClosePrevPageTransition 
   is not null, the previous page is closed with this transation, otherwise with 
   the transation configured on the page view.
   If parameter aOpenTransition is not null, the current page is opened with this 
   transation, otherwise with the transation configured on the page view.
   If aCombineTransitions is true the transitions for closing the previous page 
   and opening the current one will be executed simultaneously, otherwise will be 
   executed one after another. */
XBool ApplicationPopupNavigatorClass_ClosePopup( ApplicationPopupNavigatorClass _this, 
  ApplicationPopup aPopup, EffectsTransition aCloseTransition )
{
  XBool result;

  if ((NavigationPage)aPopup != _this->Super1.currentPage )
    return 0;

  result = NavigationNavigatorClass__CloseCurrentPageWithTransition( _this, aCloseTransition, 
  0 );

  if ( result )
    ApplicationPopupNavigatorClass_updateContainer( _this, 0 );

  return result;
}

/* 'C' function for method : 'Application::PopupNavigatorClass.onResizeFinish()' */
void ApplicationPopupNavigatorClass_onResizeFinish( ApplicationPopupNavigatorClass _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  _this->resizeEffect = 0;
  EwPostSignal( EwNewSlot( _this, ApplicationPopupNavigatorClass_dismissPopup ), 
    ((XObject)_this ));
}

/* 'C' function for method : 'Application::PopupNavigatorClass.onFadeFinish()' */
void ApplicationPopupNavigatorClass_onFadeFinish( ApplicationPopupNavigatorClass _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  _this->fadeEffect = 0;
  EwPostSignal( EwNewSlot( _this, ApplicationPopupNavigatorClass_dismissPopup ), 
    ((XObject)_this ));
}

/* 'C' function for method : 'Application::PopupNavigatorClass.OpenPopupWithEffect()' */
ApplicationPopup ApplicationPopupNavigatorClass_OpenPopupWithEffect( ApplicationPopupNavigatorClass _this, 
  ApplicationPopup aPopup, XRect aStartArea, XEnum aAlign )
{
  XBool result;
  ApplicationPopupContainer popupContainer;

  if (( _this->Super1.Container == 0 ) || ( aPopup == 0 ))
    return 0;

  if ( ApplicationPopupNavigatorClass_checkAnimationInProgress( _this ))
    return 0;

  _this->resizeEffect = 0;
  _this->fadeEffect = 0;
  result = NavigationNavigatorClass_OpenPage((NavigationNavigatorClass)_this, ((NavigationPage)aPopup ));

  if ( !result )
    return 0;

  ApplicationPopupNavigatorClass_updateContainer( _this, aPopup );
  _this->resizeEffect = EwNewObject( EffectsRectEffect, 0 );
  EffectsEffect_OnSetEnabled((EffectsEffect)_this->resizeEffect, 0 );
  EffectsEffect_OnSetCycleDuration((EffectsEffect)_this->resizeEffect, 300 );
  EffectsEffect_OnSetNoOfCycles((EffectsEffect)_this->resizeEffect, 1 );
  EffectsEffect_OnSetTiming((EffectsEffect)_this->resizeEffect, EffectsTimingLinear );
  _this->resizeEffect->Outlet = EwNewRef( aPopup, CoreRectView_OnGetBounds, CoreRectView__OnSetBounds );
  _this->resizeEffect->Super1.OnFinished = EwNullSlot;
  _this->resizeEffect->Value1 = aStartArea;
  _this->resizeEffect->Value2 = ApplicationPopupNavigatorClass_getEndArea( _this, 
  aPopup, aStartArea, aAlign );
  EffectsEffect_OnSetEnabled((EffectsEffect)_this->resizeEffect, 1 );
  CoreRectView__OnSetBounds( aPopup, aStartArea );

  if ( !aPopup->FadeBackground )
    return aPopup;

  popupContainer = EwCastObject( _this->Super1.Container, ApplicationPopupContainer );

  if ( popupContainer != 0 )
  {
    _this->fadeEffect = EwNewObject( EffectsColorEffect, 0 );

    if ( _this->fadeEffect == 0 )
      return aPopup;

    EffectsEffect_OnSetCycleDuration((EffectsEffect)_this->fadeEffect, 300 );
    EffectsEffect_OnSetNoOfCycles((EffectsEffect)_this->fadeEffect, 1 );
    EffectsEffect_OnSetTiming((EffectsEffect)_this->fadeEffect, EffectsTimingLinear );
    _this->fadeEffect->Value1 = ResOverlayOpaque;
    _this->fadeEffect->Value1.Alpha = 0;
    _this->fadeEffect->Value2 = ResOverlayOpaque;
    _this->fadeEffect->Outlet = EwNewRef( &popupContainer->Scrim, ViewsRectangle_OnGetColor, 
    ViewsRectangle_OnSetColor );
    _this->fadeEffect->Super1.OnFinished = EwNullSlot;
    EffectsEffect_OnSetEnabled((EffectsEffect)_this->fadeEffect, 1 );
  }

  return aPopup;
}

/* 'C' function for method : 'Application::PopupNavigatorClass.getPopupClass()' */
XClass ApplicationPopupNavigatorClass_getPopupClass( ApplicationPopupNavigatorClass _this, 
  XEnum aType )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  switch ( aType )
  {
    case DevicePopupTypeBolusMenu :
      return EW_CLASS( ApplicationBolusMenuPopup );

    case DevicePopupTypeInfusionStop :
      return EW_CLASS( ApplicationInfusionStopPopup );

    case DevicePopupTypeError :
      return EW_CLASS( ApplicationErrorPopup );

    case DevicePopupTypeInfo :
      return EW_CLASS( ApplicationInfoPopup );

    default : 
      return 0;
  }
}

/* 'C' function for method : 'Application::PopupNavigatorClass.getEndArea()' */
XRect ApplicationPopupNavigatorClass_getEndArea( ApplicationPopupNavigatorClass _this, 
  ApplicationPopup aPopup, XRect aStartArea, XEnum aAlign )
{
  XRect endArea = EwGetRectORect( aPopup->Super3.Bounds );

  switch ( aAlign )
  {
    case ApplicationPopupAlignStartAreaBottomRight :
    {
      endArea = EwSetRectX( endArea, aStartArea.Point2.X - EwGetRectW( aPopup->Super3.Bounds ));
      endArea = EwSetRectY( endArea, aStartArea.Point2.Y - EwGetRectH( aPopup->Super3.Bounds ));
    }
    break;

    default : 
    {
      endArea = EwSetRectX( endArea, ( EwGetRectW( _this->Super1.Container->Super2.Bounds ) 
      - EwGetRectW( aPopup->Super3.Bounds )) / 2 );
      endArea = EwSetRectY( endArea, ( EwGetRectH( _this->Super1.Container->Super2.Bounds ) 
      - EwGetRectH( aPopup->Super3.Bounds )) / 2 );
    }
  }

  return endArea;
}

/* 'C' function for method : 'Application::PopupNavigatorClass.dismissPopup()' */
void ApplicationPopupNavigatorClass_dismissPopup( ApplicationPopupNavigatorClass _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if (( _this->resizeEffect != 0 ) || ( _this->fadeEffect != 0 ))
    return;

  if ( _this->Super1.Container == 0 )
    return;

  CoreGroup__DismissDialog( _this->Super1.Container, ((CoreGroup)_this->Super1.currentPage ), 
  0, 0, 0, EwNewSlot( _this->Super1.currentPage, NavigationPage__onClose ), EwNullSlot, 
  0 );
  NavigationContainer_OnSetIsModal( _this->Super1.Container, 0 );
  _this->Super1.currentPage = 0;
  ApplicationPopupNavigatorClass_updateContainer( _this, 0 );
  EwNotifyObjObservers((XObject)_this, 0 );
}

/* 'C' function for method : 'Application::PopupNavigatorClass.checkAnimationInProgress()' */
XBool ApplicationPopupNavigatorClass_checkAnimationInProgress( ApplicationPopupNavigatorClass _this )
{
  if ((( _this->resizeEffect != 0 ) && _this->resizeEffect->Super1.Enabled ) || 
      (( _this->fadeEffect != 0 ) && _this->fadeEffect->Super1.Enabled ))
  {
    EwTrace( "%s", EwLoadString( &_Const0062 ));
    return 1;
  }

  return 0;
}

/* 'C' function for method : 'Application::PopupNavigatorClass.updateContainer()' */
void ApplicationPopupNavigatorClass_updateContainer( ApplicationPopupNavigatorClass _this, 
  ApplicationPopup aPopup )
{
  ApplicationPopupContainer container = EwCastObject( _this->Super1.Container, ApplicationPopupContainer );

  if ( aPopup != 0 )
  {
    DeviceDeviceClass_OnSetCurrentPopup( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
    aPopup->Type );

    if ( container != 0 )
    {
      ApplicationPopupContainer_OnSetFadeBackground( container, aPopup->FadeBackground );
      ApplicationPopupContainer_OnSetScrimColor( container, aPopup->ScrimColor );
    }
  }
  else
  {
    DeviceDeviceClass_OnSetCurrentPopup( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
    0 );

    if ( container != 0 )
      ApplicationPopupContainer_OnSetFadeBackground( container, 0 );
  }
}

/* 'C' function for method : 'Application::PopupNavigatorClass.OpenPopupByType()' */
ApplicationPopup ApplicationPopupNavigatorClass_OpenPopupByType( ApplicationPopupNavigatorClass _this, 
  XEnum aType, EffectsTransition aOpenTransition )
{
  ApplicationPopup popup;

  if ( _this->Super1.Container == 0 )
    return 0;

  if ( ApplicationPopupNavigatorClass_checkAnimationInProgress( _this ))
    return 0;

  popup = EwCastObject( EwNewObjectIndirect( ApplicationPopupNavigatorClass_getPopupClass( 
  _this, aType ), 0 ), ApplicationPopup );

  if ( popup == 0 )
    return 0;

  return ApplicationPopupNavigatorClass_OpenPopup( _this, popup, aOpenTransition );
}

/* 'C' function for method : 'Application::PopupNavigatorClass.GetCurrentPopup()' */
ApplicationPopup ApplicationPopupNavigatorClass_GetCurrentPopup( ApplicationPopupNavigatorClass _this )
{
  return EwCastObject( NavigationNavigatorClass_GetCurrentPage((NavigationNavigatorClass)_this ), 
    ApplicationPopup );
}

/* 'C' function for method : 'Application::PopupNavigatorClass.GetCurrentPopupType()' */
XEnum ApplicationPopupNavigatorClass_GetCurrentPopupType( ApplicationPopupNavigatorClass _this )
{
  ApplicationPopup currentPopup = EwCastObject( _this->Super1.currentPage, ApplicationPopup );

  if ( currentPopup != 0 )
    return currentPopup->Type;

  return DevicePopupTypeNone;
}

/* Variants derived from the class : 'Application::PopupNavigatorClass' */
EW_DEFINE_CLASS_VARIANTS( ApplicationPopupNavigatorClass )
EW_END_OF_CLASS_VARIANTS( ApplicationPopupNavigatorClass )

/* Virtual Method Table (VMT) for the class : 'Application::PopupNavigatorClass' */
EW_DEFINE_CLASS( ApplicationPopupNavigatorClass, NavigationNavigatorClass, resizeEffect, 
                 resizeEffect, _.VMT, _.VMT, _.VMT, _.VMT, "Application::PopupNavigatorClass" )
  ApplicationPopupNavigatorClass_CloseCurrentPageWithTransition,
EW_END_OF_CLASS( ApplicationPopupNavigatorClass )

/* Initializer for the class 'Application::BolusMenuPopup' */
void ApplicationBolusMenuPopup__Init( ApplicationBolusMenuPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationMenuPopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationBolusMenuPopup );

  /* ... then construct all embedded objects */
  ComponentsMenuButton__Init( &_this->ProgramButton, &_this->_.XObject, 0 );
  ComponentsMenuButton__Init( &_this->UseLastProgButton, &_this->_.XObject, 0 );
  ComponentsMenuButton__Init( &_this->ManualButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationBolusMenuPopup );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const005F );
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsBolusMenu ));
  CoreRectView__OnSetBounds( &_this->ProgramButton, _Const0063 );
  ComponentsTextButton__OnSetCaption( &_this->ProgramButton, EwLoadString( &StringsProgramBolus ));
  ComponentsMenuButton_OnSetHint( &_this->ProgramButton, 0 );
  CoreRectView__OnSetBounds( &_this->UseLastProgButton, _Const0064 );
  ComponentsTextButton__OnSetCaption( &_this->UseLastProgButton, EwLoadString( &StringsUseLastProgBolus ));
  ComponentsMenuButton_OnSetHint( &_this->UseLastProgButton, 0 );
  CoreRectView__OnSetBounds( &_this->ManualButton, _Const0065 );
  ComponentsTextButton__OnSetCaption( &_this->ManualButton, EwLoadString( &StringsManualBolus ));
  ComponentsMenuButton_OnSetHint( &_this->ManualButton, EwLoadString( &StringsPressAndHold ));
  CoreGroup__Add( _this, ((CoreView)&_this->ProgramButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->UseLastProgButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ManualButton ), 0 );
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->ProgramButton, 
  EwLoadResource( &Resedit, ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->UseLastProgButton, 
  EwLoadResource( &Resreload, ResourcesBitmap ));
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->ManualButton, 
  EwLoadResource( &Reschevrons_left_48px, ResourcesBitmap ));
}

/* Re-Initializer for the class 'Application::BolusMenuPopup' */
void ApplicationBolusMenuPopup__ReInit( ApplicationBolusMenuPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationMenuPopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsMenuButton__ReInit( &_this->ProgramButton );
  ComponentsMenuButton__ReInit( &_this->UseLastProgButton );
  ComponentsMenuButton__ReInit( &_this->ManualButton );
}

/* Finalizer method for the class 'Application::BolusMenuPopup' */
void ApplicationBolusMenuPopup__Done( ApplicationBolusMenuPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationMenuPopup );

  /* Finalize all embedded objects */
  ComponentsMenuButton__Done( &_this->ProgramButton );
  ComponentsMenuButton__Done( &_this->UseLastProgButton );
  ComponentsMenuButton__Done( &_this->ManualButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationMenuPopup__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Application::BolusMenuPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationBolusMenuPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationBolusMenuPopup )

/* Virtual Method Table (VMT) for the class : 'Application::BolusMenuPopup' */
EW_DEFINE_CLASS( ApplicationBolusMenuPopup, ApplicationMenuPopup, ProgramButton, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::BolusMenuPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  ApplicationMenuPopup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationMenuPopup_OnSetCaption,
  NavigationPage_onClose,
EW_END_OF_CLASS( ApplicationBolusMenuPopup )

/* Popup Navigator autobject. */
EW_DEFINE_AUTOOBJECT( ApplicationPopupNavigator, ApplicationPopupNavigatorClass )

/* Initializer for the auto object 'Application::PopupNavigator' */
void ApplicationPopupNavigator__Init( ApplicationPopupNavigatorClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Re-Initializer for the auto object 'Application::PopupNavigator' */
void ApplicationPopupNavigator__ReInit( ApplicationPopupNavigatorClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Application::PopupNavigator' */
EW_DEFINE_AUTOOBJECT_VARIANTS( ApplicationPopupNavigator )
EW_END_OF_AUTOOBJECT_VARIANTS( ApplicationPopupNavigator )

/* Page Navigator autobject. */
EW_DEFINE_AUTOOBJECT( ApplicationSettingsNavigator, ApplicationSettingsNavigatorClass )

/* Initializer for the auto object 'Application::SettingsNavigator' */
void ApplicationSettingsNavigator__Init( ApplicationSettingsNavigatorClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Re-Initializer for the auto object 'Application::SettingsNavigator' */
void ApplicationSettingsNavigator__ReInit( ApplicationSettingsNavigatorClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Application::SettingsNavigator' */
EW_DEFINE_AUTOOBJECT_VARIANTS( ApplicationSettingsNavigator )
EW_END_OF_AUTOOBJECT_VARIANTS( ApplicationSettingsNavigator )

/* Initializer for the class 'Application::InfusionStopPopup' */
void ApplicationInfusionStopPopup__Init( ApplicationInfusionStopPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationBaseMenuPopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationInfusionStopPopup );

  /* ... then construct all embedded objects */
  ComponentsTextButton__Init( &_this->RestartButton, &_this->_.XObject, 0 );
  ComponentsTextButton__Init( &_this->ClearSettingsButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationInfusionStopPopup );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0066 );
  CoreRectView__OnSetBounds( &_this->RestartButton, _Const0067 );
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)&_this->RestartButton, 
  ResSuccess );
  ComponentsBaseButton_OnSetBgColorPressed((ComponentsBaseButton)&_this->RestartButton, 
  ResSuccess );
  ComponentsTextButton__OnSetCaption( &_this->RestartButton, EwLoadString( &StringsRESTARTINFUSION ));
  ComponentsTextButton_OnSetCaptionColor( &_this->RestartButton, ResOnPrimary );
  CoreRectView__OnSetBounds( &_this->ClearSettingsButton, _Const0068 );
  ComponentsTextButton__OnSetCaption( &_this->ClearSettingsButton, EwLoadString( 
  &StringsCLEARSETTINGS ));
  CoreGroup__Add( _this, ((CoreView)&_this->RestartButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ClearSettingsButton ), 0 );
  _this->RestartButton.Super1.OnActivate = EwNewSlot( _this, ApplicationInfusionStopPopup_onRestart );
  _this->ClearSettingsButton.Super1.OnActivate = EwNewSlot( _this, ApplicationInfusionStopPopup_onClearSettings );

  /* Call the user defined constructor */
  ApplicationInfusionStopPopup_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::InfusionStopPopup' */
void ApplicationInfusionStopPopup__ReInit( ApplicationInfusionStopPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationBaseMenuPopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsTextButton__ReInit( &_this->RestartButton );
  ComponentsTextButton__ReInit( &_this->ClearSettingsButton );
}

/* Finalizer method for the class 'Application::InfusionStopPopup' */
void ApplicationInfusionStopPopup__Done( ApplicationInfusionStopPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationBaseMenuPopup );

  /* Finalize all embedded objects */
  ComponentsTextButton__Done( &_this->RestartButton );
  ComponentsTextButton__Done( &_this->ClearSettingsButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationBaseMenuPopup__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationInfusionStopPopup_Init( ApplicationInfusionStopPopup _this, XHandle 
  aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );

  DeviceDeviceClass_OnSetInStopping( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  1 );
}

/* 'C' function for method : 'Application::InfusionStopPopup.onClose()' */
void ApplicationInfusionStopPopup_onClose( ApplicationInfusionStopPopup _this, XObject 
  sender )
{
  NavigationPage_onClose((NavigationPage)_this, sender );
  DeviceDeviceClass_OnSetInStopping( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  0 );
}

/* 'C' function for method : 'Application::InfusionStopPopup.onRestart()' */
void ApplicationInfusionStopPopup_onRestart( ApplicationInfusionStopPopup _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  DeviceDeviceClass_RestartInfusion( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ));
  EwPostSignal( EwNewSlot( _this, ApplicationInfusionStopPopup_close ), ((XObject)_this ));
}

/* 'C' function for method : 'Application::InfusionStopPopup.close()' */
void ApplicationInfusionStopPopup_close( ApplicationInfusionStopPopup _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ApplicationPopupNavigatorClass_ClosePopup( EwGetAutoObject( &ApplicationPopupNavigator, 
  ApplicationPopupNavigatorClass ), ((ApplicationPopup)_this ), 0 );
}

/* 'C' function for method : 'Application::InfusionStopPopup.onClearSettings()' */
void ApplicationInfusionStopPopup_onClearSettings( ApplicationInfusionStopPopup _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  DeviceDeviceClass_ClearSettings( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ));
  EwPostSignal( EwNewSlot( _this, ApplicationInfusionStopPopup_close ), ((XObject)_this ));
}

/* Variants derived from the class : 'Application::InfusionStopPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationInfusionStopPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationInfusionStopPopup )

/* Virtual Method Table (VMT) for the class : 'Application::InfusionStopPopup' */
EW_DEFINE_CLASS( ApplicationInfusionStopPopup, ApplicationBaseMenuPopup, RestartButton, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::InfusionStopPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  ApplicationInfusionStopPopup_onClose,
EW_END_OF_CLASS( ApplicationInfusionStopPopup )

/* Initializer for the class 'Application::BaseMenuPopup' */
void ApplicationBaseMenuPopup__Init( ApplicationBaseMenuPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationPopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationBaseMenuPopup );

  /* ... then construct all embedded objects */
  CoreSimpleTouchHandler__Init( &_this->SimpleTouchHandler, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->Background, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationBaseMenuPopup );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0066 );
  CoreView_OnSetLayout((CoreView)&_this->SimpleTouchHandler, CoreLayoutAlignToBottom 
  | CoreLayoutAlignToLeft | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz 
  | CoreLayoutResizeVert );
  CoreQuadView__OnSetPoint4( &_this->SimpleTouchHandler, _Const001F );
  CoreQuadView__OnSetPoint3( &_this->SimpleTouchHandler, _Const0069 );
  CoreQuadView__OnSetPoint2( &_this->SimpleTouchHandler, _Const006A );
  CoreQuadView__OnSetPoint1( &_this->SimpleTouchHandler, _Const006B );
  CoreSimpleTouchHandler_OnSetMaxStrikeCount( &_this->SimpleTouchHandler, 999 );
  CoreView_OnSetLayout((CoreView)&_this->Background, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->Background, _Const0066 );
  ViewsRectangle_OnSetRadius( &_this->Background, 20 );
  ViewsRectangle_OnSetColor( &_this->Background, ResSurface2 );
  CoreGroup__Add( _this, ((CoreView)&_this->SimpleTouchHandler ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Background ), 0 );
}

/* Re-Initializer for the class 'Application::BaseMenuPopup' */
void ApplicationBaseMenuPopup__ReInit( ApplicationBaseMenuPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationPopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreSimpleTouchHandler__ReInit( &_this->SimpleTouchHandler );
  ViewsRectangle__ReInit( &_this->Background );
}

/* Finalizer method for the class 'Application::BaseMenuPopup' */
void ApplicationBaseMenuPopup__Done( ApplicationBaseMenuPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationPopup );

  /* Finalize all embedded objects */
  CoreSimpleTouchHandler__Done( &_this->SimpleTouchHandler );
  ViewsRectangle__Done( &_this->Background );

  /* Don't forget to deinitialize the super class ... */
  ApplicationPopup__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Application::BaseMenuPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationBaseMenuPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationBaseMenuPopup )

/* Virtual Method Table (VMT) for the class : 'Application::BaseMenuPopup' */
EW_DEFINE_CLASS( ApplicationBaseMenuPopup, ApplicationPopup, SimpleTouchHandler, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::BaseMenuPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
EW_END_OF_CLASS( ApplicationBaseMenuPopup )

/* Initializer for the class 'Application::ConfirmationPopup' */
void ApplicationConfirmationPopup__Init( ApplicationConfirmationPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationMessagePopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationConfirmationPopup );

  /* ... then construct all embedded objects */
  ComponentsTextButton__Init( &_this->ConfirmButton, &_this->_.XObject, 0 );
  ComponentsTextButton__Init( &_this->CancelButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationConfirmationPopup );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Super2.Type = DevicePopupTypeConfirmation;
  CoreRectView__OnSetBounds( &_this->Super1.MessageText, _Const006C );
  CoreRectView__OnSetBounds( &_this->ConfirmButton, _Const006D );
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)&_this->ConfirmButton, 
  ResSuccess );
  ComponentsBaseButton_OnSetBgColorPressed((ComponentsBaseButton)&_this->ConfirmButton, 
  ResSuccess );
  ComponentsTextButton__OnSetCaption( &_this->ConfirmButton, EwLoadString( &StringsCONFIRM ));
  ComponentsTextButton_OnSetCaptionColor( &_this->ConfirmButton, ResOnPrimary );
  CoreRectView__OnSetBounds( &_this->CancelButton, _Const006E );
  ComponentsTextButton__OnSetCaption( &_this->CancelButton, EwLoadString( &StringsCANCEL ));
  CoreGroup__Add( _this, ((CoreView)&_this->ConfirmButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->CancelButton ), 0 );
  _this->ConfirmButton.Super1.OnActivate = EwNewSlot( _this, ApplicationConfirmationPopup_onConfirm );
  _this->CancelButton.Super1.OnActivate = EwNewSlot( _this, ApplicationConfirmationPopup_onCancel );
}

/* Re-Initializer for the class 'Application::ConfirmationPopup' */
void ApplicationConfirmationPopup__ReInit( ApplicationConfirmationPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationMessagePopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsTextButton__ReInit( &_this->ConfirmButton );
  ComponentsTextButton__ReInit( &_this->CancelButton );
}

/* Finalizer method for the class 'Application::ConfirmationPopup' */
void ApplicationConfirmationPopup__Done( ApplicationConfirmationPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationMessagePopup );

  /* Finalize all embedded objects */
  ComponentsTextButton__Done( &_this->ConfirmButton );
  ComponentsTextButton__Done( &_this->CancelButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationMessagePopup__Done( &_this->_.Super );
}

/* 'C' function for method : 'Application::ConfirmationPopup.onConfirm()' */
void ApplicationConfirmationPopup_onConfirm( ApplicationConfirmationPopup _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  EwPostSignal( EwNewSlot( _this, ApplicationMessagePopup_close ), ((XObject)_this ));
  EwPostSignal( _this->OnConfirm, ((XObject)_this ));
}

/* 'C' function for method : 'Application::ConfirmationPopup.onCancel()' */
void ApplicationConfirmationPopup_onCancel( ApplicationConfirmationPopup _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  EwPostSignal( EwNewSlot( _this, ApplicationMessagePopup_close ), ((XObject)_this ));
  EwPostSignal( _this->OnCancel, ((XObject)_this ));
}

/* Variants derived from the class : 'Application::ConfirmationPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationConfirmationPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationConfirmationPopup )

/* Virtual Method Table (VMT) for the class : 'Application::ConfirmationPopup' */
EW_DEFINE_CLASS( ApplicationConfirmationPopup, ApplicationMessagePopup, ConfirmButton, 
                 OnConfirm, OnConfirm, _.VMT, _.VMT, _.VMT, "Application::ConfirmationPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationMessagePopup_OnSetCaption,
  NavigationPage_onClose,
EW_END_OF_CLASS( ApplicationConfirmationPopup )

/* Initializer for the class 'Application::StartInfusionConfirmPopup' */
void ApplicationStartInfusionConfirmPopup__Init( ApplicationStartInfusionConfirmPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationConfirmationPopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationStartInfusionConfirmPopup );

  /* ... then construct all embedded objects */
  ComponentsBaseTile__Init( &_this->FlowRateTile, &_this->_.XObject, 0 );
  ComponentsBaseTile__Init( &_this->InfusionVolumeTile, &_this->_.XObject, 0 );
  ComponentsBaseTileTime__Init( &_this->BaseTileTime, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationStartInfusionConfirmPopup );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsCONFIRMINFUSIONPARAMS ));
  _this->Super3.Type = DevicePopupTypeInfusionStartConfirm;
  CoreRectView__OnSetBounds( &_this->FlowRateTile, _Const006F );
  ComponentsBaseTile_OnSetCaption( &_this->FlowRateTile, EwLoadString( &StringsFlowRate ));
  ComponentsBaseTile__OnSetUnit( &_this->FlowRateTile, EwLoadString( &StringsUnit_mLPerhour ));
  ComponentsBaseTile__OnSetResolution( &_this->FlowRateTile, -2 );
  CoreRectView__OnSetBounds( &_this->InfusionVolumeTile, _Const0070 );
  ComponentsBaseTile_OnSetCaption( &_this->InfusionVolumeTile, EwLoadString( &StringsInfusionVolume ));
  ComponentsBaseTile__OnSetUnit( &_this->InfusionVolumeTile, EwLoadString( &StringsUnit_mL ));
  ComponentsBaseTile__OnSetResolution( &_this->InfusionVolumeTile, -2 );
  CoreRectView__OnSetBounds( &_this->BaseTileTime, _Const0071 );
  ComponentsBaseTile_OnSetCaption((ComponentsBaseTile)&_this->BaseTileTime, EwLoadString( 
  &StringsInfusionTime ));
  CoreGroup__Add( _this, ((CoreView)&_this->FlowRateTile ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->InfusionVolumeTile ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->BaseTileTime ), 0 );
  ComponentsBaseTile__OnSetOutlet( &_this->FlowRateTile, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetFlowRate, DeviceDeviceClass_OnSetFlowRate ));
  ComponentsBaseTile__OnSetOutlet( &_this->InfusionVolumeTile, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetInfusionVolume, DeviceDeviceClass_OnSetInfusionVolume ));
  ComponentsBaseTile__OnSetOutlet( &_this->BaseTileTime, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetInfusionTime, DeviceDeviceClass_OnSetInfusionTime ));
}

/* Re-Initializer for the class 'Application::StartInfusionConfirmPopup' */
void ApplicationStartInfusionConfirmPopup__ReInit( ApplicationStartInfusionConfirmPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationConfirmationPopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsBaseTile__ReInit( &_this->FlowRateTile );
  ComponentsBaseTile__ReInit( &_this->InfusionVolumeTile );
  ComponentsBaseTileTime__ReInit( &_this->BaseTileTime );
}

/* Finalizer method for the class 'Application::StartInfusionConfirmPopup' */
void ApplicationStartInfusionConfirmPopup__Done( ApplicationStartInfusionConfirmPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationConfirmationPopup );

  /* Finalize all embedded objects */
  ComponentsBaseTile__Done( &_this->FlowRateTile );
  ComponentsBaseTile__Done( &_this->InfusionVolumeTile );
  ComponentsBaseTileTime__Done( &_this->BaseTileTime );

  /* Don't forget to deinitialize the super class ... */
  ApplicationConfirmationPopup__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Application::StartInfusionConfirmPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationStartInfusionConfirmPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationStartInfusionConfirmPopup )

/* Virtual Method Table (VMT) for the class : 'Application::StartInfusionConfirmPopup' */
EW_DEFINE_CLASS( ApplicationStartInfusionConfirmPopup, ApplicationConfirmationPopup, 
                 FlowRateTile, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::StartInfusionConfirmPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationMessagePopup_OnSetCaption,
  NavigationPage_onClose,
EW_END_OF_CLASS( ApplicationStartInfusionConfirmPopup )

/* Initializer for the class 'Application::InfusionBasePage' */
void ApplicationInfusionBasePage__Init( ApplicationInfusionBasePage _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  NavigationPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationInfusionBasePage );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationInfusionBasePage );

  /* ... and initialize objects, variables, properties, etc. */
}

/* Re-Initializer for the class 'Application::InfusionBasePage' */
void ApplicationInfusionBasePage__ReInit( ApplicationInfusionBasePage _this )
{
  /* At first re-initialize the super class ... */
  NavigationPage__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Application::InfusionBasePage' */
void ApplicationInfusionBasePage__Done( ApplicationInfusionBasePage _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( NavigationPage );

  /* Don't forget to deinitialize the super class ... */
  NavigationPage__Done( &_this->_.Super );
}

/* 'C' function for method : 'Application::InfusionBasePage.showTile()' */
void ApplicationInfusionBasePage_showTile( ApplicationInfusionBasePage _this, ComponentsTile 
  aTile, XBool aShow )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  CoreGroup_OnSetVisible((CoreGroup)aTile, aShow );
  CoreGroup_OnSetEnabled((CoreGroup)aTile, aShow );
}

/* 'C' function for method : 'Application::InfusionBasePage.onEdit()' */
void ApplicationInfusionBasePage_onEdit( ApplicationInfusionBasePage _this, XObject 
  sender )
{
  ComponentsTile tile;

  if ( _this->editMode )
    return;

  tile = EwCastObject( sender, ComponentsTile );

  if ( tile == 0 )
    return;

  ApplicationInfusionBasePage_createEditTile( _this, tile );

  if ( _this->editTile == 0 )
    return;

  CoreRectView__OnSetBounds( _this->editTile, tile->Super5.Bounds );
  CoreGroup__Add( _this, ((CoreView)_this->editTile ), 0 );
  ApplicationInfusionBasePage_showTile( _this, tile, 0 );
  ApplicationInfusionBasePage_setupEffects( _this, tile->Super5.Bounds, 0 );
  ApplicationInfusionBasePage_showInputPopup( _this );
  _this->editMode = 1;
}

/* 'C' function for method : 'Application::InfusionBasePage.OnSetopacity()' */
void ApplicationInfusionBasePage_OnSetopacity( ApplicationInfusionBasePage _this, 
  XInt32 value )
{
  if ( _this->opacity == value )
    return;

  _this->opacity = value;
}

/* Wrapper function for the virtual method : 'Application::InfusionBasePage.OnSetopacity()' */
void ApplicationInfusionBasePage__OnSetopacity( void* _this, XInt32 value )
{
  ((ApplicationInfusionBasePage)_this)->_.VMT->OnSetopacity((ApplicationInfusionBasePage)_this
  , value );
}

/* 'C' function for method : 'Application::InfusionBasePage.onMoveFinished()' */
void ApplicationInfusionBasePage_onMoveFinished( ApplicationInfusionBasePage _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  _this->moveEffect = 0;

  if ( _this->editTile == 0 )
    return;

  if ( _this->editMode )
  {
    CoreGroup_ObtainFocus((CoreGroup)_this->editTile );
    CoreRectView__OnSetBounds( _this->editTile, ApplicationInfusionBasePage_getEditTileRect( 
    _this ));
  }
  else
  {
    ApplicationInfusionBasePage_showTile( _this, _this->editTile->ViewTile, 1 );
    CoreGroup__Remove( _this, ((CoreView)_this->editTile ));
    _this->editTile = 0;
  }
}

/* 'C' function for method : 'Application::InfusionBasePage.onFadeFinished()' */
void ApplicationInfusionBasePage_onFadeFinished( ApplicationInfusionBasePage _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->editMode )
    ApplicationInfusionBasePage__OnSetopacity( _this, 0 );
  else
    ApplicationInfusionBasePage__OnSetopacity( _this, 255 );

  _this->fadeEffect = 0;
}

/* 'C' function for method : 'Application::InfusionBasePage.onEditConfirm()' */
void ApplicationInfusionBasePage_onEditConfirm( ApplicationInfusionBasePage _this, 
  XObject sender )
{
  if ( _this->editTile != 0 )
    ComponentsEditTile__Save( _this->editTile );

  ApplicationInfusionBasePage_closeEditMode( _this, sender );
}

/* 'C' function for method : 'Application::InfusionBasePage.onEditCancel()' */
void ApplicationInfusionBasePage_onEditCancel( ApplicationInfusionBasePage _this, 
  XObject sender )
{
  if ( _this->editTile != 0 )
    ComponentsEditTile_Cancel( _this->editTile );

  ApplicationInfusionBasePage_closeEditMode( _this, sender );
}

/* 'C' function for method : 'Application::InfusionBasePage.closeEditMode()' */
void ApplicationInfusionBasePage_closeEditMode( ApplicationInfusionBasePage _this, 
  XObject aSender )
{
  XRect viewTileRect;

  if ( _this->editTile == 0 )
    return;

  viewTileRect = _this->editTile->ViewTile->Super5.Bounds;
  ApplicationInfusionBasePage_setupEffects( _this, viewTileRect, 1 );
  ApplicationPopupNavigatorClass_ClosePopup( EwGetAutoObject( &ApplicationPopupNavigator, 
  ApplicationPopupNavigatorClass ), EwCastObject( aSender, ApplicationPopup ), ((EffectsTransition)EwGetAutoObject( 
  &ApplicationSlideRight, EffectsSlideTransition )));
  _this->editMode = 0;
}

/* 'C' function for method : 'Application::InfusionBasePage.setupEffects()' */
void ApplicationInfusionBasePage_setupEffects( ApplicationInfusionBasePage _this, 
  XRect aStartRect, XBool aReversed )
{
  XRect editTileRect;

  _this->moveEffect = EwNewObject( EffectsRectEffect, 0 );

  if ( _this->moveEffect == 0 )
    return;

  editTileRect = ApplicationInfusionBasePage_getEditTileRect( _this );
  EffectsEffect_OnSetCycleDuration((EffectsEffect)_this->moveEffect, 300 );
  EffectsEffect_OnSetNoOfCycles((EffectsEffect)_this->moveEffect, 1 );
  _this->moveEffect->Outlet = EwNewRef( _this, ApplicationInfusionBasePage_OnGetmoveRect, 
  ApplicationInfusionBasePage_OnSetmoveRect );
  _this->moveEffect->Super1.OnFinished = EwNewSlot( _this, ApplicationInfusionBasePage_onMoveFinished );

  if ( aReversed )
  {
    _this->moveEffect->Value1 = editTileRect;
    _this->moveEffect->Value2 = aStartRect;
  }
  else
  {
    _this->moveEffect->Value1 = aStartRect;
    _this->moveEffect->Value2 = editTileRect;
  }

  EffectsEffect_OnSetEnabled((EffectsEffect)_this->moveEffect, 1 );
  _this->fadeEffect = EwNewObject( EffectsInt32Effect, 0 );

  if ( _this->fadeEffect == 0 )
    return;

  EffectsEffect_OnSetCycleDuration((EffectsEffect)_this->fadeEffect, 300 );
  EffectsEffect_OnSetNoOfCycles((EffectsEffect)_this->fadeEffect, 1 );

  if ( aReversed )
  {
    _this->fadeEffect->Value1 = 0;
    _this->fadeEffect->Value2 = 255;
  }
  else
  {
    _this->fadeEffect->Value1 = 255;
    _this->fadeEffect->Value2 = 0;
  }

  _this->fadeEffect->Outlet = EwNewRef( _this, ApplicationInfusionBasePage_OnGetopacity, 
  ApplicationInfusionBasePage__OnSetopacity );
  _this->fadeEffect->Super1.OnFinished = EwNewSlot( _this, ApplicationInfusionBasePage_onFadeFinished );
  EffectsEffect_OnSetEnabled((EffectsEffect)_this->fadeEffect, 1 );
}

/* 'C' function for method : 'Application::InfusionBasePage.getEditTileClass()' */
XClass ApplicationInfusionBasePage_getEditTileClass( ApplicationInfusionBasePage _this, 
  ComponentsTile aTile )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  if ( EwCastObject( aTile, ComponentsTileTime ) != 0 )
    return EW_CLASS( ComponentsEditTileTime );

  return EW_CLASS( ComponentsEditTileNumValue );
}

/* 'C' function for method : 'Application::InfusionBasePage.getEditTilePopupClass()' */
XClass ApplicationInfusionBasePage_getEditTilePopupClass( ApplicationInfusionBasePage _this )
{
  if ( _this->editTile == 0 )
    return 0;

  if ( EwCastObject( _this->editTile->ViewTile, ComponentsTileTime ) != 0 )
    return EW_CLASS( ApplicationTimerPickerPopup );

  return EW_CLASS( ApplicationNumKeyboardPopup );
}

/* 'C' function for method : 'Application::InfusionBasePage.showInputPopup()' */
void ApplicationInfusionBasePage_showInputPopup( ApplicationInfusionBasePage _this )
{
  ApplicationInputPopup popup = EwCastObject( EwNewObjectIndirect( ApplicationInfusionBasePage_getEditTilePopupClass( 
    _this ), 0 ), ApplicationInputPopup );

  if ( popup == 0 )
    return;

  ApplicationInputPopup__OnSetOutlet( popup, EwNewRef( _this->editTile, ComponentsBaseTile_OnGetValue, 
  ComponentsBaseTile__OnSetValue ));
  popup->OnOK = EwNewSlot( _this, ApplicationInfusionBasePage_onEditConfirm );
  popup->OnCancel = EwNewSlot( _this, ApplicationInfusionBasePage_onEditCancel );
  ApplicationPopupNavigatorClass_OpenPopup( EwGetAutoObject( &ApplicationPopupNavigator, 
  ApplicationPopupNavigatorClass ), ((ApplicationPopup)popup ), ((EffectsTransition)EwGetAutoObject( 
  &ApplicationSlideLeft, EffectsSlideTransition )));
}

/* 'C' function for method : 'Application::InfusionBasePage.createEditTile()' */
void ApplicationInfusionBasePage_createEditTile( ApplicationInfusionBasePage _this, 
  ComponentsTile aTile )
{
  XClass editTileClass;

  if ( aTile == 0 )
    return;

  editTileClass = ApplicationInfusionBasePage_getEditTileClass( _this, aTile );
  _this->editTile = EwCastObject( EwNewObjectIndirect( editTileClass, 0 ), ComponentsEditTile );

  if ( _this->editTile == 0 )
    return;

  ComponentsEditTile_Initialize( _this->editTile, aTile );
}

/* 'C' function for method : 'Application::InfusionBasePage.OnSetmoveRect()' */
void ApplicationInfusionBasePage_OnSetmoveRect( ApplicationInfusionBasePage _this, 
  XRect value )
{
  if ( !EwCompRect( _this->moveRect, value ))
    return;

  _this->moveRect = value;

  if ( _this->editTile != 0 )
    CoreRectView__OnSetBounds( _this->editTile, value );
}

/* 'C' function for method : 'Application::InfusionBasePage.getEditTileRect()' */
XRect ApplicationInfusionBasePage_getEditTileRect( ApplicationInfusionBasePage _this )
{
  if ( EwCastObject( _this->editTile, ComponentsEditTileTime ) != 0 )
    return _Const0072;

  return _Const0073;
}

/* Default onget method for the property 'opacity' */
XInt32 ApplicationInfusionBasePage_OnGetopacity( ApplicationInfusionBasePage _this )
{
  return _this->opacity;
}

/* Default onget method for the property 'moveRect' */
XRect ApplicationInfusionBasePage_OnGetmoveRect( ApplicationInfusionBasePage _this )
{
  return _this->moveRect;
}

/* Variants derived from the class : 'Application::InfusionBasePage' */
EW_DEFINE_CLASS_VARIANTS( ApplicationInfusionBasePage )
EW_END_OF_CLASS_VARIANTS( ApplicationInfusionBasePage )

/* Virtual Method Table (VMT) for the class : 'Application::InfusionBasePage' */
EW_DEFINE_CLASS( ApplicationInfusionBasePage, NavigationPage, editTile, editTile, 
                 opacity, opacity, opacity, opacity, "Application::InfusionBasePage" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationInfusionBasePage_OnSetopacity,
EW_END_OF_CLASS( ApplicationInfusionBasePage )

/* Initializer for the class 'Application::NotificationPopup' */
void ApplicationNotificationPopup__Init( ApplicationNotificationPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationPopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationNotificationPopup );

  /* ... then construct all embedded objects */
  ViewsRectangle__Init( &_this->Background, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->IconImage, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->CaptionText, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->Image, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->MessageText, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationNotificationPopup );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Super1.FadeBackground = 1;
  CoreView_OnSetLayout((CoreView)&_this->Background, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->Background, _Const0074 );
  ViewsRectangle_OnSetRadius( &_this->Background, 20 );
  ViewsRectangle_OnSetColor( &_this->Background, ResSurface2 );
  CoreRectView__OnSetBounds( &_this->IconImage, _Const0075 );
  ViewsImage_OnSetAlignment( &_this->IconImage, ViewsImageAlignmentAlignHorzCenter 
  | ViewsImageAlignmentAlignVertCenter );
  _this->type = DeviceNotificationTypeUndefined;
  CoreRectView__OnSetBounds( &_this->CaptionText, _Const0076 );
  ViewsText_OnSetOverflowWarning( &_this->CaptionText, 1 );
  ViewsText_OnSetWrapText( &_this->CaptionText, 1 );
  ViewsText_OnSetAlignment( &_this->CaptionText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertTop );
  ViewsText__OnSetString( &_this->CaptionText, EwLoadString( &_Const0077 ));
  CoreRectView__OnSetBounds( &_this->Image, _Const0078 );
  CoreRectView__OnSetBounds( &_this->MessageText, _Const0079 );
  ViewsText_OnSetOverflowWarning( &_this->MessageText, 1 );
  ViewsText_OnSetWrapText( &_this->MessageText, 1 );
  ViewsText_OnSetAlignment( &_this->MessageText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->MessageText, EwLoadString( &_Const0077 ));
  CoreGroup__Add( _this, ((CoreView)&_this->Background ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->IconImage ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->CaptionText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Image ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->MessageText ), 0 );
  ViewsImage_OnSetBitmap( &_this->IconImage, EwLoadResource( &ResourcesDefaultBitmap, 
  ResourcesBitmap ));
  ViewsText__OnSetFont( &_this->CaptionText, EwLoadResource( &FontsHeading2, ResourcesFont ));
  ViewsText__OnSetFont( &_this->MessageText, EwLoadResource( &FontsHeading3, ResourcesFont ));

  /* Call the user defined constructor */
  ApplicationNotificationPopup_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::NotificationPopup' */
void ApplicationNotificationPopup__ReInit( ApplicationNotificationPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationPopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsRectangle__ReInit( &_this->Background );
  ViewsImage__ReInit( &_this->IconImage );
  ViewsText__ReInit( &_this->CaptionText );
  ViewsImage__ReInit( &_this->Image );
  ViewsText__ReInit( &_this->MessageText );
}

/* Finalizer method for the class 'Application::NotificationPopup' */
void ApplicationNotificationPopup__Done( ApplicationNotificationPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationPopup );

  /* Finalize all embedded objects */
  ViewsRectangle__Done( &_this->Background );
  ViewsImage__Done( &_this->IconImage );
  ViewsText__Done( &_this->CaptionText );
  ViewsImage__Done( &_this->Image );
  ViewsText__Done( &_this->MessageText );

  /* Don't forget to deinitialize the super class ... */
  ApplicationPopup__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationNotificationPopup_Init( ApplicationNotificationPopup _this, XHandle 
  aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* The method UpdateViewState() is invoked automatically after the state of the 
   component has been changed. This method can be overridden and filled with logic 
   to ensure the visual aspect of the component does reflect its current state. 
   For example, the 'enabled' state of the component can affect its colors (disabled 
   components may appear pale). In this case the logic of the method should modify 
   the respective color properties accordingly to the current 'enabled' state. 
   The current state of the component is passed as a set in the parameter aState. 
   It reflects the very basic component state like its visibility or the ability 
   to react to user inputs. Beside this common state, the method can also involve 
   any other variables used in the component as long as they reflect its current 
   state. For example, the toggle switch component can take in account its toggle 
   state 'on' or 'off' and change accordingly the location of the slider, etc.
   Usually, this method will be invoked automatically by the framework. Optionally 
   you can request its invocation by using the method @InvalidateViewState(). */
void ApplicationNotificationPopup_UpdateViewState( ApplicationNotificationPopup _this, 
  XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );

  if ( _this->type == DeviceNotificationTypeError )
    ViewsRectangle_OnSetColor( &_this->Background, ResError );
  else
    ViewsRectangle_OnSetColor( &_this->Background, ResSurface2 );

  ViewsImage_OnSetColor( &_this->IconImage, ResOnPrimary );
  ViewsText_OnSetColor( &_this->CaptionText, ResOnPrimary );
  ViewsText_OnSetColor( &_this->MessageText, ResOnPrimary );
}

/* 'C' function for method : 'Application::NotificationPopup.OnSetNotificationId()' */
void ApplicationNotificationPopup_OnSetNotificationId( ApplicationNotificationPopup _this, 
  XInt32 value )
{
  if ( _this->NotificationId == value )
    return;

  _this->NotificationId = value;
  _this->type = DeviceDeviceClass_GetNotificationType( EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass ), value );
  ViewsImage_OnSetBitmap( &_this->IconImage, ApplicationNotificationPopup_getIcon( 
  _this ));
  ViewsImage_OnSetBitmap( &_this->Image, DeviceDeviceClass_GetNotificationImage( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), value ));
  ViewsText__OnSetString( &_this->CaptionText, DeviceDeviceClass_GetNotificationCaption( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), value ));
  ViewsText__OnSetString( &_this->MessageText, DeviceDeviceClass_GetNotificationMessage( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), value ));

  if ( _this->Image.Bitmap != 0 )
    CoreRectView__OnSetBounds( &_this->MessageText, EwSetRectX1( _this->MessageText.Super1.Bounds, 
    _this->Image.Super1.Bounds.Point2.X + 10 ));
  else
    CoreRectView__OnSetBounds( &_this->MessageText, EwSetRectX1( _this->MessageText.Super1.Bounds, 
    _this->IconImage.Super1.Bounds.Point1.X ));

  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* Wrapper function for the virtual method : 'Application::NotificationPopup.OnSetNotificationId()' */
void ApplicationNotificationPopup__OnSetNotificationId( void* _this, XInt32 value )
{
  ((ApplicationNotificationPopup)_this)->_.VMT->OnSetNotificationId((ApplicationNotificationPopup)_this
  , value );
}

/* 'C' function for method : 'Application::NotificationPopup.getIcon()' */
ResourcesBitmap ApplicationNotificationPopup_getIcon( ApplicationNotificationPopup _this )
{
  switch ( _this->type )
  {
    case DeviceNotificationTypeError :
    case DeviceNotificationTypeWarning :
      return EwLoadResource( &Restriangle_alert_32px, ResourcesBitmap );

    default : 
      return EwLoadResource( &Resinfo, ResourcesBitmap );
  }
}

/* Variants derived from the class : 'Application::NotificationPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationNotificationPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationNotificationPopup )

/* Virtual Method Table (VMT) for the class : 'Application::NotificationPopup' */
EW_DEFINE_CLASS( ApplicationNotificationPopup, ApplicationPopup, Background, NotificationId, 
                 NotificationId, NotificationId, NotificationId, NotificationId, 
                 "Application::NotificationPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  ApplicationNotificationPopup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationNotificationPopup_OnSetNotificationId,
EW_END_OF_CLASS( ApplicationNotificationPopup )

/* Initializer for the class 'Application::ErrorPopup' */
void ApplicationErrorPopup__Init( ApplicationErrorPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationNotificationPopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationErrorPopup );

  /* ... then construct all embedded objects */
  ViewsText__Init( &_this->ErrorCodeText, &_this->_.XObject, 0 );
  ComponentsNotificationButton__Init( &_this->MuteButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationErrorPopup );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Super2.Type = DevicePopupTypeError;
  CoreRectView__OnSetBounds( &_this->Super1.MessageText, _Const007A );
  CoreRectView__OnSetBounds( &_this->ErrorCodeText, _Const007B );
  ViewsText_OnSetOverflowWarning( &_this->ErrorCodeText, 1 );
  ViewsText_OnSetAlignment( &_this->ErrorCodeText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertTop );
  CoreRectView__OnSetBounds( &_this->MuteButton, _Const007C );
  ComponentsTextButton__OnSetCaption( &_this->MuteButton, EwLoadString( &StringsMUTE ));
  CoreGroup__Add( _this, ((CoreView)&_this->ErrorCodeText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->MuteButton ), 0 );
  ViewsText__OnSetFont( &_this->ErrorCodeText, EwLoadResource( &FontsHeading3, ResourcesFont ));
  _this->MuteButton.Super3.OnActivate = EwNewSlot( _this, ApplicationErrorPopup_onMute );
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->MuteButton, 
  EwLoadResource( &Resmute, ResourcesBitmap ));

  /* Call the user defined constructor */
  ApplicationErrorPopup_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::ErrorPopup' */
void ApplicationErrorPopup__ReInit( ApplicationErrorPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationNotificationPopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsText__ReInit( &_this->ErrorCodeText );
  ComponentsNotificationButton__ReInit( &_this->MuteButton );
}

/* Finalizer method for the class 'Application::ErrorPopup' */
void ApplicationErrorPopup__Done( ApplicationErrorPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationNotificationPopup );

  /* Finalize all embedded objects */
  ViewsText__Done( &_this->ErrorCodeText );
  ComponentsNotificationButton__Done( &_this->MuteButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationNotificationPopup__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationErrorPopup_Init( ApplicationErrorPopup _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* 'C' function for method : 'Application::ErrorPopup.OnSetNotificationId()' */
void ApplicationErrorPopup_OnSetNotificationId( ApplicationErrorPopup _this, XInt32 
  value )
{
  if ( _this->Super1.NotificationId == value )
    return;

  ApplicationNotificationPopup_OnSetNotificationId((ApplicationNotificationPopup)_this, 
  value );
  ViewsText__OnSetString( &_this->ErrorCodeText, EwConcatString( EwConcatString( 
  EwLoadString( &StringsErrorCode ), EwLoadString( &_Const0054 )), DeviceDeviceClass_GetErrorCode( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), value )));
  CoreGroup_OnSetVisible((CoreGroup)&_this->MuteButton, DeviceDeviceClass_IsErrorWithSound( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), value ));
  CoreGroup_OnSetEnabled((CoreGroup)&_this->MuteButton, CoreGroup_OnGetVisible((CoreGroup)&_this->MuteButton ));
}

/* 'C' function for method : 'Application::ErrorPopup.onMute()' */
void ApplicationErrorPopup_onMute( ApplicationErrorPopup _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  DeviceDeviceClass_MuteAlarm( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  _this->Super1.NotificationId );
  CoreGroup_OnSetEnabled((CoreGroup)&_this->MuteButton, 0 );
}

/* Variants derived from the class : 'Application::ErrorPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationErrorPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationErrorPopup )

/* Virtual Method Table (VMT) for the class : 'Application::ErrorPopup' */
EW_DEFINE_CLASS( ApplicationErrorPopup, ApplicationNotificationPopup, ErrorCodeText, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::ErrorPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  ApplicationNotificationPopup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationErrorPopup_OnSetNotificationId,
EW_END_OF_CLASS( ApplicationErrorPopup )

/* Initializer for the class 'Application::InfoPopup' */
void ApplicationInfoPopup__Init( ApplicationInfoPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationNotificationPopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationInfoPopup );

  /* ... then construct all embedded objects */
  ComponentsNotificationButton__Init( &_this->OKButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationInfoPopup );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Super2.Type = DevicePopupTypeInfo;
  CoreRectView__OnSetBounds( &_this->Super1.MessageText, _Const007D );
  CoreRectView__OnSetBounds( &_this->OKButton, _Const007C );
  ComponentsTextButton__OnSetCaption( &_this->OKButton, EwLoadString( &StringsOK ));
  CoreGroup__Add( _this, ((CoreView)&_this->OKButton ), 0 );
  _this->OKButton.Super3.OnActivate = EwNewSlot( _this, ApplicationInfoPopup_onOK );
  ComponentsIconTextButton_OnSetIcon((ComponentsIconTextButton)&_this->OKButton, 
  0 );

  /* Call the user defined constructor */
  ApplicationInfoPopup_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::InfoPopup' */
void ApplicationInfoPopup__ReInit( ApplicationInfoPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationNotificationPopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsNotificationButton__ReInit( &_this->OKButton );
}

/* Finalizer method for the class 'Application::InfoPopup' */
void ApplicationInfoPopup__Done( ApplicationInfoPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationNotificationPopup );

  /* Finalize all embedded objects */
  ComponentsNotificationButton__Done( &_this->OKButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationNotificationPopup__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationInfoPopup_Init( ApplicationInfoPopup _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* 'C' function for method : 'Application::InfoPopup.onOK()' */
void ApplicationInfoPopup_onOK( ApplicationInfoPopup _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  DeviceDeviceClass_ConfirmNotification( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  _this->Super1.NotificationId );
  ApplicationPopupNavigatorClass_ClosePopup( EwGetAutoObject( &ApplicationNotificationNavigator, 
  ApplicationPopupNavigatorClass ), ((ApplicationPopup)_this ), 0 );
}

/* Variants derived from the class : 'Application::InfoPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationInfoPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationInfoPopup )

/* Virtual Method Table (VMT) for the class : 'Application::InfoPopup' */
EW_DEFINE_CLASS( ApplicationInfoPopup, ApplicationNotificationPopup, OKButton, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Application::InfoPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  ApplicationNotificationPopup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationNotificationPopup_OnSetNotificationId,
EW_END_OF_CLASS( ApplicationInfoPopup )

/* Notification Navigator autobject. */
EW_DEFINE_AUTOOBJECT( ApplicationNotificationNavigator, ApplicationPopupNavigatorClass )

/* Initializer for the auto object 'Application::NotificationNavigator' */
void ApplicationNotificationNavigator__Init( ApplicationPopupNavigatorClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Re-Initializer for the auto object 'Application::NotificationNavigator' */
void ApplicationNotificationNavigator__ReInit( ApplicationPopupNavigatorClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Application::NotificationNavigator' */
EW_DEFINE_AUTOOBJECT_VARIANTS( ApplicationNotificationNavigator )
EW_END_OF_AUTOOBJECT_VARIANTS( ApplicationNotificationNavigator )

/* Initializer for the class 'Application::InfoTipPopup' */
void ApplicationInfoTipPopup__Init( ApplicationInfoTipPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationMessagePopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationInfoTipPopup );

  /* ... then construct all embedded objects */
  ComponentsRoundIconButton__Init( &_this->CloseButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationInfoTipPopup );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Super2.Type = DevicePopupTypeInfoTip;
  CoreRectView__OnSetBounds( &_this->Super1.Background, _Const0074 );
  CoreRectView__OnSetBounds( &_this->Super1.CaptionText, _Const007E );
  CoreRectView__OnSetBounds( &_this->Super1.MessageText, _Const007F );
  CoreRectView__OnSetBounds( &_this->CloseButton, _Const0080 );
  CoreGroup__Add( _this, ((CoreView)&_this->CloseButton ), 0 );
  _this->CloseButton.Super2.OnActivate = EwNewSlot( _this, ApplicationMessagePopup_close );
  ComponentsRoundIconButton_OnSetIcon( &_this->CloseButton, EwLoadResource( &Resx, 
  ResourcesBitmap ));

  /* Call the user defined constructor */
  ApplicationInfoTipPopup_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::InfoTipPopup' */
void ApplicationInfoTipPopup__ReInit( ApplicationInfoTipPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationMessagePopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsRoundIconButton__ReInit( &_this->CloseButton );
}

/* Finalizer method for the class 'Application::InfoTipPopup' */
void ApplicationInfoTipPopup__Done( ApplicationInfoTipPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationMessagePopup );

  /* Finalize all embedded objects */
  ComponentsRoundIconButton__Done( &_this->CloseButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationMessagePopup__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationInfoTipPopup_Init( ApplicationInfoTipPopup _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* Variants derived from the class : 'Application::InfoTipPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationInfoTipPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationInfoTipPopup )

/* Virtual Method Table (VMT) for the class : 'Application::InfoTipPopup' */
EW_DEFINE_CLASS( ApplicationInfoTipPopup, ApplicationMessagePopup, CloseButton, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::InfoTipPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationMessagePopup_OnSetCaption,
  NavigationPage_onClose,
EW_END_OF_CLASS( ApplicationInfoTipPopup )

/* Initializer for the class 'Application::MessagePopup' */
void ApplicationMessagePopup__Init( ApplicationMessagePopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationPopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationMessagePopup );

  /* ... then construct all embedded objects */
  ViewsRectangle__Init( &_this->Background, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->CaptionText, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->MessageText, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationMessagePopup );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Super1.FadeBackground = 1;
  CoreRectView__OnSetBounds( &_this->Background, _Const0081 );
  ViewsRectangle_OnSetRadius( &_this->Background, 20 );
  ViewsRectangle_OnSetColor( &_this->Background, ResSurface2 );
  CoreRectView__OnSetBounds( &_this->CaptionText, _Const0082 );
  ViewsText_OnSetOverflowWarning( &_this->CaptionText, 1 );
  ViewsText__OnSetString( &_this->CaptionText, EwLoadString( &StringsCONFIRMINFUSIONPARAMS ));
  ViewsText_OnSetColor( &_this->CaptionText, ResOnPrimary );
  CoreRectView__OnSetBounds( &_this->MessageText, _Const0083 );
  ViewsText_OnSetOverflowWarning( &_this->MessageText, 1 );
  ViewsText_OnSetWrapText( &_this->MessageText, 1 );
  ViewsText_OnSetAlignment( &_this->MessageText, ViewsTextAlignmentAlignHorzCenter 
  | ViewsTextAlignmentAlignVertCenter );
  ViewsText_OnSetColor( &_this->MessageText, ResOnPrimary );
  CoreGroup__Add( _this, ((CoreView)&_this->Background ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->CaptionText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->MessageText ), 0 );
  ViewsText__OnSetFont( &_this->CaptionText, EwLoadResource( &FontsHeading2, ResourcesFont ));
  ViewsText__OnSetFont( &_this->MessageText, EwLoadResource( &FontsHeading3, ResourcesFont ));

  /* Call the user defined constructor */
  ApplicationMessagePopup_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::MessagePopup' */
void ApplicationMessagePopup__ReInit( ApplicationMessagePopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationPopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsRectangle__ReInit( &_this->Background );
  ViewsText__ReInit( &_this->CaptionText );
  ViewsText__ReInit( &_this->MessageText );
}

/* Finalizer method for the class 'Application::MessagePopup' */
void ApplicationMessagePopup__Done( ApplicationMessagePopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationPopup );

  /* Finalize all embedded objects */
  ViewsRectangle__Done( &_this->Background );
  ViewsText__Done( &_this->CaptionText );
  ViewsText__Done( &_this->MessageText );

  /* Don't forget to deinitialize the super class ... */
  ApplicationPopup__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationMessagePopup_Init( ApplicationMessagePopup _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* 'C' function for method : 'Application::MessagePopup.OnSetCaption()' */
void ApplicationMessagePopup_OnSetCaption( ApplicationMessagePopup _this, XString 
  value )
{
  NavigationPage_OnSetCaption((NavigationPage)_this, value );
  ViewsText__OnSetString( &_this->CaptionText, value );
}

/* 'C' function for method : 'Application::MessagePopup.close()' */
void ApplicationMessagePopup_close( ApplicationMessagePopup _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ApplicationPopupNavigatorClass_ClosePopup( EwGetAutoObject( &ApplicationPopupNavigator, 
  ApplicationPopupNavigatorClass ), ((ApplicationPopup)_this ), 0 );
}

/* 'C' function for method : 'Application::MessagePopup.OnSetMessage()' */
void ApplicationMessagePopup_OnSetMessage( ApplicationMessagePopup _this, XString 
  value )
{
  if ( !EwCompString( _this->Message, value ))
    return;

  _this->Message = EwShareString( value );
  ViewsText__OnSetString( &_this->MessageText, value );
}

/* Variants derived from the class : 'Application::MessagePopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationMessagePopup )
EW_END_OF_CLASS_VARIANTS( ApplicationMessagePopup )

/* Virtual Method Table (VMT) for the class : 'Application::MessagePopup' */
EW_DEFINE_CLASS( ApplicationMessagePopup, ApplicationPopup, Background, Message, 
                 Message, Message, Message, _.VMT, "Application::MessagePopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationMessagePopup_OnSetCaption,
  NavigationPage_onClose,
EW_END_OF_CLASS( ApplicationMessagePopup )

/* Initializer for the class 'Application::SettingsNavigatorClass' */
void ApplicationSettingsNavigatorClass__Init( ApplicationSettingsNavigatorClass _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  NavigationNavigatorClass__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationSettingsNavigatorClass );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationSettingsNavigatorClass );
}

/* Re-Initializer for the class 'Application::SettingsNavigatorClass' */
void ApplicationSettingsNavigatorClass__ReInit( ApplicationSettingsNavigatorClass _this )
{
  /* At first re-initialize the super class ... */
  NavigationNavigatorClass__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Application::SettingsNavigatorClass' */
void ApplicationSettingsNavigatorClass__Done( ApplicationSettingsNavigatorClass _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( NavigationNavigatorClass );

  /* Don't forget to deinitialize the super class ... */
  NavigationNavigatorClass__Done( &_this->_.Super );
}

/* This method opens the page provides as parameter in aPageView. The page is opened 
   and closed with the transations configured in the page view. */
XBool ApplicationSettingsNavigatorClass_OpenSubPage( ApplicationSettingsNavigatorClass _this, 
  NavigationPage aPageView )
{
  if ( aPageView == 0 )
  {
    EwTrace( "%s", EwLoadString( &_Const0084 ));
    return 0;
  }

  return ApplicationSettingsNavigatorClass_openSubPage( _this, aPageView, 0, 0, 
    0 );
}

/* 'C' function for method : 'Application::SettingsNavigatorClass.CloseCurrentSubPageWithTransition()' */
XBool ApplicationSettingsNavigatorClass_CloseCurrentSubPageWithTransition( ApplicationSettingsNavigatorClass _this, 
  EffectsTransition aCloseTransition, XBool aCombine )
{
  EffectsTransition closeTransition;

  if ( _this->Super1.Container == 0 )
  {
    EwTrace( "%s", EwLoadString( &_Const0085 ));
    return 0;
  }

  if ( _this->currentSubPage == 0 )
    return 0;

  closeTransition = aCloseTransition;

  if ( closeTransition == 0 )
    closeTransition = 0;

  CoreGroup__DismissDialog( _this->Super1.Container, ((CoreGroup)_this->currentSubPage ), 
  closeTransition, 0, 0, EwNewSlot( _this->currentSubPage, NavigationPage__onClose ), 
  EwNullSlot, aCombine );
  NavigationContainer_OnSetIsModal( _this->Super1.Container, 0 );
  _this->currentSubPage = 0;
  EwNotifyObjObservers((XObject)_this, 0 );
  return 1;
}

/* This methos return the current page. */
NavigationPage ApplicationSettingsNavigatorClass_GetCurrentSubPage( ApplicationSettingsNavigatorClass _this )
{
  return _this->currentSubPage;
}

/* 'C' function for method : 'Application::SettingsNavigatorClass.CloseCurrentSubPage()' */
XBool ApplicationSettingsNavigatorClass_CloseCurrentSubPage( ApplicationSettingsNavigatorClass _this )
{
  return ApplicationSettingsNavigatorClass_CloseCurrentSubPageWithTransition( _this, 
    0, 0 );
}

/* 'C' function for method : 'Application::SettingsNavigatorClass.openSubPage()' */
XBool ApplicationSettingsNavigatorClass_openSubPage( ApplicationSettingsNavigatorClass _this, 
  NavigationPage aPageView, EffectsTransition aClosePrevPageTransition, EffectsTransition 
  aOpenTransition, XBool aCombineTransitions )
{
  EffectsTransition openTransition;

  if ( _this->Super1.Container == 0 )
  {
    EwTrace( "%s", EwLoadString( &_Const0085 ));
    return 0;
  }

  if ( _this->Super1.currentPage == 0 )
  {
    EwTrace( "%s", EwLoadString( &_Const0086 ));
    return 0;
  }

  if ( aPageView == 0 )
  {
    EwTrace( "%s", EwLoadString( &_Const0087 ));
    return 0;
  }

  if ( _this->currentSubPage != 0 )
    NavigationNavigatorClass__CloseCurrentPageWithTransition( _this, aClosePrevPageTransition, 
    aCombineTransitions );

  openTransition = aOpenTransition;

  if ( openTransition == 0 )
    openTransition = 0;

  CoreGroup__PresentDialog( _this->Super1.Container, ((CoreGroup)aPageView ), openTransition, 
  0, 0, 0, 0, 0, EwNewSlot( aPageView, NavigationPage_onOpen ), EwNullSlot, aCombineTransitions );
  NavigationContainer_OnSetIsModal( _this->Super1.Container, 1 );
  _this->currentSubPage = aPageView;
  EwNotifyObjObservers((XObject)_this, 0 );
  return 1;
}

/* Variants derived from the class : 'Application::SettingsNavigatorClass' */
EW_DEFINE_CLASS_VARIANTS( ApplicationSettingsNavigatorClass )
EW_END_OF_CLASS_VARIANTS( ApplicationSettingsNavigatorClass )

/* Virtual Method Table (VMT) for the class : 'Application::SettingsNavigatorClass' */
EW_DEFINE_CLASS( ApplicationSettingsNavigatorClass, NavigationNavigatorClass, currentSubPage, 
                 currentSubPage, _.VMT, _.VMT, _.VMT, _.VMT, "Application::SettingsNavigatorClass" )
  NavigationNavigatorClass_CloseCurrentPageWithTransition,
EW_END_OF_CLASS( ApplicationSettingsNavigatorClass )

/* Initializer for the class 'Application::SettingsSubPage' */
void ApplicationSettingsSubPage__Init( ApplicationSettingsSubPage _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationSettingsSubPage );

  /* ... then construct all embedded objects */
  CoreSimpleTouchHandler__Init( &_this->DontTouchBehind, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationSettingsSubPage );

  /* ... and initialize objects, variables, properties, etc. */
  CoreQuadView__OnSetPoint4( &_this->DontTouchBehind, _Const001F );
  CoreQuadView__OnSetPoint3( &_this->DontTouchBehind, _Const0020 );
  CoreQuadView__OnSetPoint2( &_this->DontTouchBehind, _Const0088 );
  CoreQuadView__OnSetPoint1( &_this->DontTouchBehind, _Const0089 );
  CoreSimpleTouchHandler_OnSetMaxStrikeCount( &_this->DontTouchBehind, 999 );
  ViewsRectangle_OnSetColor( &_this->Super1.Scrim, ResOverlayOpaque );
  CoreRectView__OnSetBounds( &_this->Super1.ContentBackground, _Const008A );
  CoreGroup__Add( _this, ((CoreView)&_this->DontTouchBehind ), -4 );
}

/* Re-Initializer for the class 'Application::SettingsSubPage' */
void ApplicationSettingsSubPage__ReInit( ApplicationSettingsSubPage _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreSimpleTouchHandler__ReInit( &_this->DontTouchBehind );
}

/* Finalizer method for the class 'Application::SettingsSubPage' */
void ApplicationSettingsSubPage__Done( ApplicationSettingsSubPage _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsPage );

  /* Finalize all embedded objects */
  CoreSimpleTouchHandler__Done( &_this->DontTouchBehind );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsPage__Done( &_this->_.Super );
}

/* 'C' function for method : 'Application::SettingsSubPage.onBack()' */
void ApplicationSettingsSubPage_onBack( ApplicationSettingsSubPage _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( sender );

  DeviceDeviceClass_OnSetCurrentSubSettings( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  0 );
}

/* Variants derived from the class : 'Application::SettingsSubPage' */
EW_DEFINE_CLASS_VARIANTS( ApplicationSettingsSubPage )
EW_END_OF_CLASS_VARIANTS( ApplicationSettingsSubPage )

/* Virtual Method Table (VMT) for the class : 'Application::SettingsSubPage' */
EW_DEFINE_CLASS( ApplicationSettingsSubPage, ApplicationSettingsPage, DontTouchBehind, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::SettingsSubPage" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsSubPage_onBack,
EW_END_OF_CLASS( ApplicationSettingsSubPage )

/* Initializer for the class 'Application::WifiSettings' */
void ApplicationWifiSettings__Init( ApplicationWifiSettings _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsSubPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationWifiSettings );

  /* ... then construct all embedded objects */
  ComponentsToggleButton__Init( &_this->ToggleButton, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->WiFiText, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->ScanCodeText, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->QRCodeBg, &_this->_.XObject, 0 );
  ComponentsQRCode__Init( &_this->QRCode, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->NetworksText, &_this->_.XObject, 0 );
  ComponentsDataList__Init( &_this->NetworkList, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationWifiSettings );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsWiFiSettings ));
  CoreRectView__OnSetBounds( &_this->Super2.ContentBackground, _Const008B );
  CoreRectView__OnSetBounds( &_this->ToggleButton, _Const008C );
  CoreRectView__OnSetBounds( &_this->WiFiText, _Const008D );
  ViewsText_OnSetOverflowWarning( &_this->WiFiText, 1 );
  ViewsText_OnSetAlignment( &_this->WiFiText, ViewsTextAlignmentAlignHorzLeft | 
  ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->WiFiText, EwLoadString( &StringsWiFi ));
  ViewsText_OnSetColor( &_this->WiFiText, ResOnPrimary );
  CoreRectView__OnSetBounds( &_this->ScanCodeText, _Const008E );
  ViewsText_OnSetOverflowWarning( &_this->ScanCodeText, 1 );
  ViewsText_OnSetWrapText( &_this->ScanCodeText, 1 );
  ViewsText_OnSetAlignment( &_this->ScanCodeText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertTop );
  ViewsText__OnSetString( &_this->ScanCodeText, EwLoadString( &StringsScanCode ));
  ViewsText_OnSetColor( &_this->ScanCodeText, ResOnSecondary );
  CoreRectView__OnSetBounds( &_this->QRCodeBg, _Const008F );
  ViewsRectangle_OnSetRadius( &_this->QRCodeBg, 16 );
  CoreRectView__OnSetBounds( &_this->QRCode, _Const0090 );
  CoreRectView__OnSetBounds( &_this->NetworksText, _Const0091 );
  ViewsText_OnSetOverflowWarning( &_this->NetworksText, 1 );
  ViewsText_OnSetAlignment( &_this->NetworksText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->NetworksText, EwLoadString( &StringsMyNetworks ));
  ViewsText_OnSetColor( &_this->NetworksText, ResOnSecondary );
  CoreRectView__OnSetBounds( &_this->NetworkList, _Const0092 );
  ComponentsDataList_OnSetItemClass( &_this->NetworkList, EW_CLASS( ApplicationWifiNetworkListItem ));
  ComponentsDataList_OnSetItemHeight( &_this->NetworkList, 44 );
  CoreGroup__Add( _this, ((CoreView)&_this->ToggleButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->WiFiText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ScanCodeText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->QRCodeBg ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->QRCode ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->NetworksText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->NetworkList ), 0 );
  ComponentsToggleButton_OnSetOutlet( &_this->ToggleButton, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetWifiStatus, DeviceDeviceClass_OnSetWifiStatus ));
  ViewsText__OnSetFont( &_this->WiFiText, EwLoadResource( &FontsHeading3, ResourcesFont ));
  ViewsText__OnSetFont( &_this->ScanCodeText, EwLoadResource( &FontsBody18, ResourcesFont ));
  ComponentsQRCode_OnSetOutlet( &_this->QRCode, EwNewRef( EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass ), DeviceDeviceClass_OnGetAppQRCode, DeviceDeviceClass_OnSetAppQRCode ));
  ViewsText__OnSetFont( &_this->NetworksText, EwLoadResource( &FontsHeading3, ResourcesFont ));

  /* Call the user defined constructor */
  ApplicationWifiSettings_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::WifiSettings' */
void ApplicationWifiSettings__ReInit( ApplicationWifiSettings _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsSubPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsToggleButton__ReInit( &_this->ToggleButton );
  ViewsText__ReInit( &_this->WiFiText );
  ViewsText__ReInit( &_this->ScanCodeText );
  ViewsRectangle__ReInit( &_this->QRCodeBg );
  ComponentsQRCode__ReInit( &_this->QRCode );
  ViewsText__ReInit( &_this->NetworksText );
  ComponentsDataList__ReInit( &_this->NetworkList );
}

/* Finalizer method for the class 'Application::WifiSettings' */
void ApplicationWifiSettings__Done( ApplicationWifiSettings _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsSubPage );

  /* Finalize all embedded objects */
  ComponentsToggleButton__Done( &_this->ToggleButton );
  ViewsText__Done( &_this->WiFiText );
  ViewsText__Done( &_this->ScanCodeText );
  ViewsRectangle__Done( &_this->QRCodeBg );
  ComponentsQRCode__Done( &_this->QRCode );
  ViewsText__Done( &_this->NetworksText );
  ComponentsDataList__Done( &_this->NetworkList );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsSubPage__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationWifiSettings_Init( ApplicationWifiSettings _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  EwAttachRefObserver( EwNewSlot( _this, ApplicationWifiSettings_onWifiStatus ), 
    EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetWifiStatus, 
    DeviceDeviceClass_OnSetWifiStatus ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationWifiSettings_onWifiStatus ), ((XObject)_this ));
}

/* 'C' function for method : 'Application::WifiSettings.onWifiStatus()' */
void ApplicationWifiSettings_onWifiStatus( ApplicationWifiSettings _this, XObject 
  sender )
{
  XBool on;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  on = EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->WifiStatus;
  ViewsText_OnSetVisible( &_this->ScanCodeText, on );
  ViewsRectangle_OnSetVisible( &_this->QRCodeBg, on );
  CoreGroup_OnSetVisible((CoreGroup)&_this->QRCode, on );
  CoreGroup_OnSetVisible((CoreGroup)&_this->NetworkList, on );

  if ( on )
    ComponentsDataList_OnSetDataProvider( &_this->NetworkList, ((DeviceDataProvider)EwGetAutoObject( 
    &DeviceWifiNetworksProvider, DeviceWifiNetworksProviderClass )));
  else
    ComponentsDataList_OnSetDataProvider( &_this->NetworkList, 0 );
}

/* Variants derived from the class : 'Application::WifiSettings' */
EW_DEFINE_CLASS_VARIANTS( ApplicationWifiSettings )
EW_END_OF_CLASS_VARIANTS( ApplicationWifiSettings )

/* Virtual Method Table (VMT) for the class : 'Application::WifiSettings' */
EW_DEFINE_CLASS( ApplicationWifiSettings, ApplicationSettingsSubPage, ToggleButton, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::WifiSettings" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsSubPage_onBack,
EW_END_OF_CLASS( ApplicationWifiSettings )

/* Initializer for the class 'Application::AudioVolumeControl' */
void ApplicationAudioVolumeControl__Init( ApplicationAudioVolumeControl _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsSubPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationAudioVolumeControl );

  /* ... then construct all embedded objects */
  ComponentsPressureSettingButton__Init( &_this->Setting1Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting2Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting3Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting4Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting5Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting6Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting7Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting8Button, &_this->_.XObject, 0 );
  ComponentsPressureSettingButton__Init( &_this->Setting9Button, &_this->_.XObject, 0 );
  ComponentsTextButton__Init( &_this->ConfirmButton, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationAudioVolumeControl );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsAudioVolumeControl ));
  CoreRectView__OnSetBounds( &_this->Super2.ContentBackground, _Const0030 );
  CoreRectView__OnSetBounds( &_this->Setting1Button, _Const0032 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting1Button, 1 );
  CoreRectView__OnSetBounds( &_this->Setting2Button, _Const0033 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting2Button, 2 );
  CoreRectView__OnSetBounds( &_this->Setting3Button, _Const0034 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting3Button, 3 );
  CoreRectView__OnSetBounds( &_this->Setting4Button, _Const0035 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting4Button, 4 );
  CoreRectView__OnSetBounds( &_this->Setting5Button, _Const0036 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting5Button, 5 );
  CoreRectView__OnSetBounds( &_this->Setting6Button, _Const0037 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting6Button, 6 );
  CoreRectView__OnSetBounds( &_this->Setting7Button, _Const0038 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting7Button, 7 );
  CoreRectView__OnSetBounds( &_this->Setting8Button, _Const0039 );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting8Button, 8 );
  CoreRectView__OnSetBounds( &_this->Setting9Button, _Const003A );
  ComponentsRoundRadioButton__OnSetOutletSelector( &_this->Setting9Button, 9 );
  CoreRectView__OnSetBounds( &_this->ConfirmButton, _Const003B );
  CoreGroup_OnSetEnabled((CoreGroup)&_this->ConfirmButton, 0 );
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)&_this->ConfirmButton, 
  ResSuccess );
  ComponentsBaseButton_OnSetBgColorPressed((ComponentsBaseButton)&_this->ConfirmButton, 
  ResSuccess );
  ComponentsTextButton__OnSetCaption( &_this->ConfirmButton, EwLoadString( &StringsCONFIRM ));
  ComponentsTextButton_OnSetCaptionColor( &_this->ConfirmButton, ResOnPrimary );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting1Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting2Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting3Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting4Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting5Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting6Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting7Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting8Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Setting9Button ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ConfirmButton ), 0 );
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting1Button, 
  EwNewRef( _this, ApplicationAudioVolumeControl_OnGetAudioVolume, ApplicationAudioVolumeControl_OnSetAudioVolume ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting2Button, 
  EwNewRef( _this, ApplicationAudioVolumeControl_OnGetAudioVolume, ApplicationAudioVolumeControl_OnSetAudioVolume ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting3Button, 
  EwNewRef( _this, ApplicationAudioVolumeControl_OnGetAudioVolume, ApplicationAudioVolumeControl_OnSetAudioVolume ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting4Button, 
  EwNewRef( _this, ApplicationAudioVolumeControl_OnGetAudioVolume, ApplicationAudioVolumeControl_OnSetAudioVolume ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting5Button, 
  EwNewRef( _this, ApplicationAudioVolumeControl_OnGetAudioVolume, ApplicationAudioVolumeControl_OnSetAudioVolume ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting6Button, 
  EwNewRef( _this, ApplicationAudioVolumeControl_OnGetAudioVolume, ApplicationAudioVolumeControl_OnSetAudioVolume ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting7Button, 
  EwNewRef( _this, ApplicationAudioVolumeControl_OnGetAudioVolume, ApplicationAudioVolumeControl_OnSetAudioVolume ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting8Button, 
  EwNewRef( _this, ApplicationAudioVolumeControl_OnGetAudioVolume, ApplicationAudioVolumeControl_OnSetAudioVolume ));
  ComponentsRoundRadioButton_OnSetOutlet((ComponentsRoundRadioButton)&_this->Setting9Button, 
  EwNewRef( _this, ApplicationAudioVolumeControl_OnGetAudioVolume, ApplicationAudioVolumeControl_OnSetAudioVolume ));
  _this->ConfirmButton.Super1.OnActivate = EwNewSlot( _this, ApplicationAudioVolumeControl_onConfirm );

  /* Call the user defined constructor */
  ApplicationAudioVolumeControl_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::AudioVolumeControl' */
void ApplicationAudioVolumeControl__ReInit( ApplicationAudioVolumeControl _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsSubPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsPressureSettingButton__ReInit( &_this->Setting1Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting2Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting3Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting4Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting5Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting6Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting7Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting8Button );
  ComponentsPressureSettingButton__ReInit( &_this->Setting9Button );
  ComponentsTextButton__ReInit( &_this->ConfirmButton );
}

/* Finalizer method for the class 'Application::AudioVolumeControl' */
void ApplicationAudioVolumeControl__Done( ApplicationAudioVolumeControl _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsSubPage );

  /* Finalize all embedded objects */
  ComponentsPressureSettingButton__Done( &_this->Setting1Button );
  ComponentsPressureSettingButton__Done( &_this->Setting2Button );
  ComponentsPressureSettingButton__Done( &_this->Setting3Button );
  ComponentsPressureSettingButton__Done( &_this->Setting4Button );
  ComponentsPressureSettingButton__Done( &_this->Setting5Button );
  ComponentsPressureSettingButton__Done( &_this->Setting6Button );
  ComponentsPressureSettingButton__Done( &_this->Setting7Button );
  ComponentsPressureSettingButton__Done( &_this->Setting8Button );
  ComponentsPressureSettingButton__Done( &_this->Setting9Button );
  ComponentsTextButton__Done( &_this->ConfirmButton );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsSubPage__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationAudioVolumeControl_Init( ApplicationAudioVolumeControl _this, XHandle 
  aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  EwAttachRefObserver( EwNewSlot( _this, ApplicationAudioVolumeControl_onAudioVolume ), 
    EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetAudioVolume, 
    DeviceDeviceClass_OnSetAudioVolume ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationAudioVolumeControl_onAudioVolume ), 
    ((XObject)_this ));
}

/* 'C' function for method : 'Application::AudioVolumeControl.onConfirm()' */
void ApplicationAudioVolumeControl_onConfirm( ApplicationAudioVolumeControl _this, 
  XObject sender )
{
  ApplicationConfirmationPopup popup;
  XString message;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  popup = EwNewObject( ApplicationConfirmationPopup, 0 );

  if ( popup == 0 )
    return;

  message = EwLoadString( &StringsConfirmAudioVolumeChangeText );
  message = ToolsHelperCollection_StringParamReplace( EwGetAutoObject( &ToolsHelper, 
  ToolsHelperCollection ), message, 1, EwNewStringInt( EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass )->AudioVolume, 0, 10 ));
  message = ToolsHelperCollection_StringParamReplace( EwGetAutoObject( &ToolsHelper, 
  ToolsHelperCollection ), message, 2, EwNewStringInt( _this->AudioVolume, 0, 10 ));
  NavigationPage__OnSetCaption( popup, EwLoadString( &StringsConfirmAudioVolumeChangeCaption ));
  ApplicationMessagePopup_OnSetMessage((ApplicationMessagePopup)popup, message );
  popup->OnConfirm = EwNewSlot( _this, ApplicationAudioVolumeControl_doConfirm );
  popup->OnCancel = EwNewSlot( _this, ApplicationAudioVolumeControl_onCancel );
  ApplicationPopupNavigatorClass_OpenPopup( EwGetAutoObject( &ApplicationPopupNavigator, 
  ApplicationPopupNavigatorClass ), ((ApplicationPopup)popup ), 0 );
}

/* 'C' function for method : 'Application::AudioVolumeControl.doConfirm()' */
void ApplicationAudioVolumeControl_doConfirm( ApplicationAudioVolumeControl _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  DeviceDeviceClass_OnSetAudioVolume( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  _this->AudioVolume );
  DeviceDeviceClass_OnSetCurrentSubSettings( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  0 );
}

/* 'C' function for method : 'Application::AudioVolumeControl.onCancel()' */
void ApplicationAudioVolumeControl_onCancel( ApplicationAudioVolumeControl _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ApplicationAudioVolumeControl_OnSetAudioVolume( _this, EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass )->AudioVolume );
}

/* 'C' function for method : 'Application::AudioVolumeControl.OnSetAudioVolume()' */
void ApplicationAudioVolumeControl_OnSetAudioVolume( ApplicationAudioVolumeControl _this, 
  XInt32 value )
{
  if ( _this->AudioVolume == value )
    return;

  _this->AudioVolume = value;
  CoreGroup_OnSetEnabled((CoreGroup)&_this->ConfirmButton, (XBool)( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass )->AudioVolume != value ));
  EwNotifyRefObservers( EwNewRef( _this, ApplicationAudioVolumeControl_OnGetAudioVolume, 
    ApplicationAudioVolumeControl_OnSetAudioVolume ), 0 );
}

/* 'C' function for method : 'Application::AudioVolumeControl.onAudioVolume()' */
void ApplicationAudioVolumeControl_onAudioVolume( ApplicationAudioVolumeControl _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ApplicationAudioVolumeControl_OnSetAudioVolume( _this, EwGetAutoObject( &DeviceDevice, 
  DeviceDeviceClass )->AudioVolume );
}

/* Default onget method for the property 'AudioVolume' */
XInt32 ApplicationAudioVolumeControl_OnGetAudioVolume( ApplicationAudioVolumeControl _this )
{
  return _this->AudioVolume;
}

/* Variants derived from the class : 'Application::AudioVolumeControl' */
EW_DEFINE_CLASS_VARIANTS( ApplicationAudioVolumeControl )
EW_END_OF_CLASS_VARIANTS( ApplicationAudioVolumeControl )

/* Virtual Method Table (VMT) for the class : 'Application::AudioVolumeControl' */
EW_DEFINE_CLASS( ApplicationAudioVolumeControl, ApplicationSettingsSubPage, Setting1Button, 
                 AudioVolume, AudioVolume, AudioVolume, AudioVolume, AudioVolume, 
                 "Application::AudioVolumeControl" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsSubPage_onBack,
EW_END_OF_CLASS( ApplicationAudioVolumeControl )

/* Initializer for the class 'Application::DataAndTime' */
void ApplicationDataAndTime__Init( ApplicationDataAndTime _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsSubPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationDataAndTime );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationDataAndTime );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsDateTimeSettings ));
}

/* Re-Initializer for the class 'Application::DataAndTime' */
void ApplicationDataAndTime__ReInit( ApplicationDataAndTime _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsSubPage__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Application::DataAndTime' */
void ApplicationDataAndTime__Done( ApplicationDataAndTime _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsSubPage );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsSubPage__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Application::DataAndTime' */
EW_DEFINE_CLASS_VARIANTS( ApplicationDataAndTime )
EW_END_OF_CLASS_VARIANTS( ApplicationDataAndTime )

/* Virtual Method Table (VMT) for the class : 'Application::DataAndTime' */
EW_DEFINE_CLASS( ApplicationDataAndTime, ApplicationSettingsSubPage, _.VMT, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Application::DataAndTime" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsSubPage_onBack,
EW_END_OF_CLASS( ApplicationDataAndTime )

/* Initializer for the class 'Application::Language' */
void ApplicationLanguage__Init( ApplicationLanguage _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsSubPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationLanguage );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationLanguage );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsLanguageSelection ));
}

/* Re-Initializer for the class 'Application::Language' */
void ApplicationLanguage__ReInit( ApplicationLanguage _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsSubPage__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Application::Language' */
void ApplicationLanguage__Done( ApplicationLanguage _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsSubPage );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsSubPage__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Application::Language' */
EW_DEFINE_CLASS_VARIANTS( ApplicationLanguage )
EW_END_OF_CLASS_VARIANTS( ApplicationLanguage )

/* Virtual Method Table (VMT) for the class : 'Application::Language' */
EW_DEFINE_CLASS( ApplicationLanguage, ApplicationSettingsSubPage, _.VMT, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Application::Language" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsSubPage_onBack,
EW_END_OF_CLASS( ApplicationLanguage )

/* Initializer for the class 'Application::SoftwareUpdate' */
void ApplicationSoftwareUpdate__Init( ApplicationSoftwareUpdate _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsSubPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationSoftwareUpdate );

  /* ... then construct all embedded objects */
  ComponentsTextButton__Init( &_this->StartUpdateButton, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->IconImage, &_this->_.XObject, 0 );
  ComponentsStringValueDisplay__Init( &_this->VersionText, &_this->_.XObject, 0 );
  ComponentsStringValueDisplay__Init( &_this->VersionDescText, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->InfoText, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationSoftwareUpdate );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsSoftwareUpdate ));
  CoreRectView__OnSetBounds( &_this->StartUpdateButton, _Const0093 );
  ComponentsTextButton__OnSetCaption( &_this->StartUpdateButton, EwLoadString( &StringsStartUpdate ));
  CoreRectView__OnSetBounds( &_this->IconImage, _Const0094 );
  CoreRectView__OnSetBounds( &_this->VersionText, _Const0095 );
  ViewsText_OnSetOverflowWarning((ViewsText)&_this->VersionText, 1 );
  ViewsText_OnSetAlignment((ViewsText)&_this->VersionText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->VersionDescText, _Const0096 );
  ViewsText_OnSetOverflowWarning((ViewsText)&_this->VersionDescText, 1 );
  ViewsText_OnSetAlignment((ViewsText)&_this->VersionDescText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->InfoText, _Const0097 );
  ViewsText_OnSetOverflowWarning( &_this->InfoText, 1 );
  ViewsText_OnSetWrapText( &_this->InfoText, 1 );
  ViewsText_OnSetAlignment( &_this->InfoText, ViewsTextAlignmentAlignHorzLeft | 
  ViewsTextAlignmentAlignVertTop );
  ViewsText__OnSetString( &_this->InfoText, EwLoadString( &StringsSoftwareUpdateDesc ));
  CoreGroup__Add( _this, ((CoreView)&_this->StartUpdateButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->IconImage ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->VersionText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->VersionDescText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->InfoText ), 0 );
  _this->StartUpdateButton.Super1.OnActivate = EwNewSlot( _this, ApplicationSoftwareUpdate_onStartUpdate );
  ComponentsTextButton_OnSetFont( &_this->StartUpdateButton, EwLoadResource( &FontsBody18, 
  ResourcesFont ));
  ViewsImage_OnSetBitmap( &_this->IconImage, EwLoadResource( &Resinfo_32px, ResourcesBitmap ));
  ViewsText__OnSetFont( &_this->VersionText, EwLoadResource( &FontsBody18SemiBold, 
  ResourcesFont ));
  ComponentsStringValueDisplay_OnSetOutlet( &_this->VersionText, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetNewFirmwareVersion, 
  DeviceDeviceClass_OnSetNewFirmwareVersion ));
  ViewsText__OnSetFont( &_this->VersionDescText, EwLoadResource( &FontsBody16, ResourcesFont ));
  ComponentsStringValueDisplay_OnSetOutlet( &_this->VersionDescText, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetNewFirmwareVersionDesc, 
  DeviceDeviceClass_OnSetNewFirmwareVersionDesc ));
  ViewsText__OnSetFont( &_this->InfoText, EwLoadResource( &FontsBody18, ResourcesFont ));

  /* Call the user defined constructor */
  ApplicationSoftwareUpdate_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::SoftwareUpdate' */
void ApplicationSoftwareUpdate__ReInit( ApplicationSoftwareUpdate _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsSubPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsTextButton__ReInit( &_this->StartUpdateButton );
  ViewsImage__ReInit( &_this->IconImage );
  ComponentsStringValueDisplay__ReInit( &_this->VersionText );
  ComponentsStringValueDisplay__ReInit( &_this->VersionDescText );
  ViewsText__ReInit( &_this->InfoText );
}

/* Finalizer method for the class 'Application::SoftwareUpdate' */
void ApplicationSoftwareUpdate__Done( ApplicationSoftwareUpdate _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsSubPage );

  /* Finalize all embedded objects */
  ComponentsTextButton__Done( &_this->StartUpdateButton );
  ViewsImage__Done( &_this->IconImage );
  ComponentsStringValueDisplay__Done( &_this->VersionText );
  ComponentsStringValueDisplay__Done( &_this->VersionDescText );
  ViewsText__Done( &_this->InfoText );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsSubPage__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationSoftwareUpdate_Init( ApplicationSoftwareUpdate _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  EwAttachRefObserver( EwNewSlot( _this, ApplicationSoftwareUpdate_onNewFWVersion ), 
    EwNewRef( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetNewFirmwareVersion, 
    DeviceDeviceClass_OnSetNewFirmwareVersion ), 0 );
  EwPostSignal( EwNewSlot( _this, ApplicationSoftwareUpdate_onNewFWVersion ), ((XObject)_this ));
}

/* The method UpdateViewState() is invoked automatically after the state of the 
   component has been changed. This method can be overridden and filled with logic 
   to ensure the visual aspect of the component does reflect its current state. 
   For example, the 'enabled' state of the component can affect its colors (disabled 
   components may appear pale). In this case the logic of the method should modify 
   the respective color properties accordingly to the current 'enabled' state. 
   The current state of the component is passed as a set in the parameter aState. 
   It reflects the very basic component state like its visibility or the ability 
   to react to user inputs. Beside this common state, the method can also involve 
   any other variables used in the component as long as they reflect its current 
   state. For example, the toggle switch component can take in account its toggle 
   state 'on' or 'off' and change accordingly the location of the slider, etc.
   Usually, this method will be invoked automatically by the framework. Optionally 
   you can request its invocation by using the method @InvalidateViewState(). */
void ApplicationSoftwareUpdate_UpdateViewState( ApplicationSoftwareUpdate _this, 
  XSet aState )
{
  XColor cl;

  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  cl = ResOnPrimary;
  ViewsImage_OnSetColor( &_this->IconImage, cl );
  ViewsText_OnSetColor((ViewsText)&_this->VersionText, cl );
  ViewsText_OnSetColor((ViewsText)&_this->VersionDescText, cl );
  ViewsText_OnSetColor( &_this->InfoText, cl );
}

/* 'C' function for method : 'Application::SoftwareUpdate.onNewFWVersion()' */
void ApplicationSoftwareUpdate_onNewFWVersion( ApplicationSoftwareUpdate _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_OnSetEnabled((CoreGroup)&_this->StartUpdateButton, (XBool)(( EwCompString( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->NewFirmwareVersion, 0 ) != 
  0 ) && ( EwCompString( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->NewFirmwareVersion, 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass )->FirmwareVersion ) != 0 )));
}

/* 'C' function for method : 'Application::SoftwareUpdate.onStartUpdate()' */
void ApplicationSoftwareUpdate_onStartUpdate( ApplicationSoftwareUpdate _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  DeviceDeviceClass_OnSetSoftwareUpdate( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
  1 );
  CoreGroup_OnSetEnabled((CoreGroup)&_this->StartUpdateButton, 0 );
}

/* Variants derived from the class : 'Application::SoftwareUpdate' */
EW_DEFINE_CLASS_VARIANTS( ApplicationSoftwareUpdate )
EW_END_OF_CLASS_VARIANTS( ApplicationSoftwareUpdate )

/* Virtual Method Table (VMT) for the class : 'Application::SoftwareUpdate' */
EW_DEFINE_CLASS( ApplicationSoftwareUpdate, ApplicationSettingsSubPage, StartUpdateButton, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::SoftwareUpdate" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  ApplicationSoftwareUpdate_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsSubPage_onBack,
EW_END_OF_CLASS( ApplicationSoftwareUpdate )

/* Initializer for the class 'Application::About' */
void ApplicationAbout__Init( ApplicationAbout _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsSubPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationAbout );

  /* ... then construct all embedded objects */
  CoreOutline__Init( &_this->OutlineBackground, &_this->_.XObject, 0 );
  ComponentsVertScrollbar__Init( &_this->VertScrollbar, &_this->_.XObject, 0 );
  CoreSlideTouchHandler__Init( &_this->SlideTouchHandler, &_this->_.XObject, 0 );
  CoreOutline__Init( &_this->Outline, &_this->_.XObject, 0 );
  ComponentsStringSettingItem__Init( &_this->SerialNumberItem, &_this->_.XObject, 0 );
  ComponentsStringSettingItem__Init( &_this->NameItem, &_this->_.XObject, 0 );
  ComponentsStringSettingItem__Init( &_this->ManufacturerItem, &_this->_.XObject, 0 );
  ComponentsDateTimeSettingItem__Init( &_this->MfgDateTimeItem, &_this->_.XObject, 0 );
  ComponentsStringSettingItem__Init( &_this->ModelNumberItem, &_this->_.XObject, 0 );
  ComponentsStringSettingItem__Init( &_this->FirmwareVersionItem, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationAbout );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsAbout ));
  CoreRectView__OnSetBounds( &_this->OutlineBackground, _Const0098 );
  CoreRectView__OnSetBounds( &_this->Super2.ContentBackground, _Const0099 );
  ViewsRectangle_OnSetEmbedded( &_this->Super2.ContentBackground, 1 );
  CoreRectView__OnSetBounds( &_this->VertScrollbar, _Const0055 );
  CoreRectView__OnSetBounds( &_this->SlideTouchHandler, _Const009A );
  _this->SlideTouchHandler.SlideHorz = 0;
  CoreRectView__OnSetBounds( &_this->Outline, _Const0098 );
  CoreOutline_OnSetPaddingBottom( &_this->Outline, 24 );
  CoreOutline_OnSetPaddingTop( &_this->Outline, 24 );
  CoreOutline_OnSetPaddingLeft( &_this->Outline, 35 );
  CoreOutline_OnSetSpaceVert( &_this->Outline, 16 );
  CoreOutline_OnSetFormation( &_this->Outline, CoreFormationTopToBottom );
  CoreRectView__OnSetBounds( &_this->SerialNumberItem, _Const009B );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->SerialNumberItem, 1 );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->SerialNumberItem, 
  EwLoadString( &StringsSerialNumber ));
  CoreRectView__OnSetBounds( &_this->NameItem, _Const009C );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->NameItem, 1 );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->NameItem, EwLoadString( 
  &StringsName ));
  CoreRectView__OnSetBounds( &_this->ManufacturerItem, _Const009D );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->ManufacturerItem, 1 );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->ManufacturerItem, 
  EwLoadString( &StringsManufacturer ));
  CoreRectView__OnSetBounds( &_this->MfgDateTimeItem, _Const009E );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->MfgDateTimeItem, 1 );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->MfgDateTimeItem, 
  EwLoadString( &StringsMfgDateTime ));
  CoreRectView__OnSetBounds( &_this->ModelNumberItem, _Const009F );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->ModelNumberItem, 1 );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->ModelNumberItem, 
  EwLoadString( &StringsModelNumber ));
  CoreRectView__OnSetBounds( &_this->FirmwareVersionItem, _Const00A0 );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->FirmwareVersionItem, 1 );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->FirmwareVersionItem, 
  EwLoadString( &StringsFirmwareVersion ));
  CoreGroup__Add( _this, ((CoreView)&_this->OutlineBackground ), -3 );
  CoreGroup__Add( _this, ((CoreView)&_this->VertScrollbar ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->SlideTouchHandler ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Outline ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->SerialNumberItem ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->NameItem ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ManufacturerItem ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->MfgDateTimeItem ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ModelNumberItem ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->FirmwareVersionItem ), 0 );
  _this->Outline.OnUpdate = EwNewSlot( _this, ApplicationAbout_onOutlineUpdate );
  CoreOutline_OnSetSlideHandler( &_this->Outline, &_this->SlideTouchHandler );
  ComponentsStringSettingItem_OnSetOutlet( &_this->SerialNumberItem, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetSerialNumber, DeviceDeviceClass_OnSetSerialNumber ));
  ComponentsStringSettingItem_OnSetOutlet( &_this->NameItem, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetName, DeviceDeviceClass_OnSetName ));
  ComponentsStringSettingItem_OnSetOutlet( &_this->ManufacturerItem, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetManufacturer, DeviceDeviceClass_OnSetManufacturer ));
  ComponentsDateTimeSettingItem_OnSetOutlet( &_this->MfgDateTimeItem, EwNewRef( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetMfgDateTime, 
  DeviceDeviceClass_OnSetMfgDateTime ));
  ComponentsStringSettingItem_OnSetOutlet( &_this->ModelNumberItem, EwNewRef( EwGetAutoObject( 
  &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetModelNumber, DeviceDeviceClass_OnSetModelNumber ));
  ComponentsStringSettingItem_OnSetOutlet( &_this->FirmwareVersionItem, EwNewRef( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), DeviceDeviceClass_OnGetFirmwareVersion, 
  DeviceDeviceClass_OnSetFirmwareVersion ));
}

/* Re-Initializer for the class 'Application::About' */
void ApplicationAbout__ReInit( ApplicationAbout _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsSubPage__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreOutline__ReInit( &_this->OutlineBackground );
  ComponentsVertScrollbar__ReInit( &_this->VertScrollbar );
  CoreSlideTouchHandler__ReInit( &_this->SlideTouchHandler );
  CoreOutline__ReInit( &_this->Outline );
  ComponentsStringSettingItem__ReInit( &_this->SerialNumberItem );
  ComponentsStringSettingItem__ReInit( &_this->NameItem );
  ComponentsStringSettingItem__ReInit( &_this->ManufacturerItem );
  ComponentsDateTimeSettingItem__ReInit( &_this->MfgDateTimeItem );
  ComponentsStringSettingItem__ReInit( &_this->ModelNumberItem );
  ComponentsStringSettingItem__ReInit( &_this->FirmwareVersionItem );
}

/* Finalizer method for the class 'Application::About' */
void ApplicationAbout__Done( ApplicationAbout _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsSubPage );

  /* Finalize all embedded objects */
  CoreOutline__Done( &_this->OutlineBackground );
  ComponentsVertScrollbar__Done( &_this->VertScrollbar );
  CoreSlideTouchHandler__Done( &_this->SlideTouchHandler );
  CoreOutline__Done( &_this->Outline );
  ComponentsStringSettingItem__Done( &_this->SerialNumberItem );
  ComponentsStringSettingItem__Done( &_this->NameItem );
  ComponentsStringSettingItem__Done( &_this->ManufacturerItem );
  ComponentsDateTimeSettingItem__Done( &_this->MfgDateTimeItem );
  ComponentsStringSettingItem__Done( &_this->ModelNumberItem );
  ComponentsStringSettingItem__Done( &_this->FirmwareVersionItem );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsSubPage__Done( &_this->_.Super );
}

/* 'C' function for method : 'Application::About.onOutlineUpdate()' */
void ApplicationAbout_onOutlineUpdate( ApplicationAbout _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ComponentsVertScrollbar_OnSetContentArea( &_this->VertScrollbar, EwGetRectH( CoreOutline_GetContentArea( 
  &_this->Outline, CoreViewStateVisible )));
  ComponentsVertScrollbar_OnSetViewArea( &_this->VertScrollbar, EwGetRectH( _this->Outline.Super1.Bounds ));
  ComponentsVertScrollbar_OnSetPosition( &_this->VertScrollbar, -_this->Outline.ScrollOffset.Y );
  CoreOutline_OnSetScrollOffset( &_this->OutlineBackground, _this->Outline.ScrollOffset );
}

/* Variants derived from the class : 'Application::About' */
EW_DEFINE_CLASS_VARIANTS( ApplicationAbout )
EW_END_OF_CLASS_VARIANTS( ApplicationAbout )

/* Virtual Method Table (VMT) for the class : 'Application::About' */
EW_DEFINE_CLASS( ApplicationAbout, ApplicationSettingsSubPage, MfgDateTimeItem, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::About" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsSubPage_onBack,
EW_END_OF_CLASS( ApplicationAbout )

/* Initializer for the class 'Application::MaintenanceAndCalibration' */
void ApplicationMaintenanceAndCalibration__Init( ApplicationMaintenanceAndCalibration _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationSettingsSubPage__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationMaintenanceAndCalibration );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationMaintenanceAndCalibration );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsMaintenanceAndCalibration ));
}

/* Re-Initializer for the class 'Application::MaintenanceAndCalibration' */
void ApplicationMaintenanceAndCalibration__ReInit( ApplicationMaintenanceAndCalibration _this )
{
  /* At first re-initialize the super class ... */
  ApplicationSettingsSubPage__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Application::MaintenanceAndCalibration' */
void ApplicationMaintenanceAndCalibration__Done( ApplicationMaintenanceAndCalibration _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationSettingsSubPage );

  /* Don't forget to deinitialize the super class ... */
  ApplicationSettingsSubPage__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Application::MaintenanceAndCalibration' */
EW_DEFINE_CLASS_VARIANTS( ApplicationMaintenanceAndCalibration )
EW_END_OF_CLASS_VARIANTS( ApplicationMaintenanceAndCalibration )

/* Virtual Method Table (VMT) for the class : 'Application::MaintenanceAndCalibration' */
EW_DEFINE_CLASS( ApplicationMaintenanceAndCalibration, ApplicationSettingsSubPage, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Application::MaintenanceAndCalibration" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationSettingsPage_OnSetCaption,
  NavigationPage_onClose,
  ApplicationSettingsSubPage_onBack,
EW_END_OF_CLASS( ApplicationMaintenanceAndCalibration )

/* Initializer for the class 'Application::WifiNetworkListItem' */
void ApplicationWifiNetworkListItem__Init( ApplicationWifiNetworkListItem _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsListItem__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationWifiNetworkListItem );

  /* ... then construct all embedded objects */
  ViewsText__Init( &_this->SSIDText, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->ConnectedIcon, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->WifiIcon, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->InfoIcon, &_this->_.XObject, 0 );
  CoreSimpleTouchHandler__Init( &_this->TouchHandler, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationWifiNetworkListItem );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const00A1 );
  CoreView_OnSetLayout((CoreView)&_this->SSIDText, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->SSIDText, _Const00A2 );
  ViewsText_OnSetAlignment( &_this->SSIDText, ViewsTextAlignmentAlignHorzLeft | 
  ViewsTextAlignmentAlignVertCenter );
  CoreView_OnSetLayout((CoreView)&_this->ConnectedIcon, CoreLayoutAlignToBottom 
  | CoreLayoutAlignToLeft | CoreLayoutAlignToTop | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->ConnectedIcon, _Const00A3 );
  ViewsImage_OnSetVisible( &_this->ConnectedIcon, 0 );
  CoreView_OnSetLayout((CoreView)&_this->WifiIcon, CoreLayoutAlignToBottom | CoreLayoutAlignToRight 
  | CoreLayoutAlignToTop | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->WifiIcon, _Const00A4 );
  CoreView_OnSetLayout((CoreView)&_this->InfoIcon, CoreLayoutAlignToBottom | CoreLayoutAlignToRight 
  | CoreLayoutAlignToTop | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->InfoIcon, _Const00A5 );
  CoreView_OnSetLayout((CoreView)&_this->TouchHandler, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToLeft | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz 
  | CoreLayoutResizeVert );
  CoreQuadView__OnSetPoint4( &_this->TouchHandler, _Const00A6 );
  CoreQuadView__OnSetPoint3( &_this->TouchHandler, _Const00A7 );
  CoreQuadView__OnSetPoint2( &_this->TouchHandler, _Const00A8 );
  CoreQuadView__OnSetPoint1( &_this->TouchHandler, _Const001F );
  _this->TouchHandler.RetargetCondition = CoreRetargetReasonWipeDown | CoreRetargetReasonWipeLeft 
  | CoreRetargetReasonWipeRight | CoreRetargetReasonWipeUp;
  CoreSimpleTouchHandler_OnSetMaxStrikeCount( &_this->TouchHandler, 100 );
  CoreGroup__Add( _this, ((CoreView)&_this->SSIDText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ConnectedIcon ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->WifiIcon ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->InfoIcon ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->TouchHandler ), 0 );
  ViewsText__OnSetFont( &_this->SSIDText, EwLoadResource( &FontsBody18, ResourcesFont ));
  ViewsImage_OnSetBitmap( &_this->ConnectedIcon, EwLoadResource( &Rescheck, ResourcesBitmap ));
  ViewsImage_OnSetBitmap( &_this->InfoIcon, EwLoadResource( &Resinfo, ResourcesBitmap ));
  _this->TouchHandler.OnPress = EwNewSlot( _this, ApplicationWifiNetworkListItem_onPressTouch );

  /* Call the user defined constructor */
  ApplicationWifiNetworkListItem_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::WifiNetworkListItem' */
void ApplicationWifiNetworkListItem__ReInit( ApplicationWifiNetworkListItem _this )
{
  /* At first re-initialize the super class ... */
  ComponentsListItem__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsText__ReInit( &_this->SSIDText );
  ViewsImage__ReInit( &_this->ConnectedIcon );
  ViewsImage__ReInit( &_this->WifiIcon );
  ViewsImage__ReInit( &_this->InfoIcon );
  CoreSimpleTouchHandler__ReInit( &_this->TouchHandler );
}

/* Finalizer method for the class 'Application::WifiNetworkListItem' */
void ApplicationWifiNetworkListItem__Done( ApplicationWifiNetworkListItem _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsListItem );

  /* Finalize all embedded objects */
  ViewsText__Done( &_this->SSIDText );
  ViewsImage__Done( &_this->ConnectedIcon );
  ViewsImage__Done( &_this->WifiIcon );
  ViewsImage__Done( &_this->InfoIcon );
  CoreSimpleTouchHandler__Done( &_this->TouchHandler );

  /* Don't forget to deinitialize the super class ... */
  ComponentsListItem__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationWifiNetworkListItem_Init( ApplicationWifiNetworkListItem _this, 
  XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* The method UpdateViewState() is invoked automatically after the state of the 
   component has been changed. This method can be overridden and filled with logic 
   to ensure the visual aspect of the component does reflect its current state. 
   For example, the 'enabled' state of the component can affect its colors (disabled 
   components may appear pale). In this case the logic of the method should modify 
   the respective color properties accordingly to the current 'enabled' state. 
   The current state of the component is passed as a set in the parameter aState. 
   It reflects the very basic component state like its visibility or the ability 
   to react to user inputs. Beside this common state, the method can also involve 
   any other variables used in the component as long as they reflect its current 
   state. For example, the toggle switch component can take in account its toggle 
   state 'on' or 'off' and change accordingly the location of the slider, etc.
   Usually, this method will be invoked automatically by the framework. Optionally 
   you can request its invocation by using the method @InvalidateViewState(). */
void ApplicationWifiNetworkListItem_UpdateViewState( ApplicationWifiNetworkListItem _this, 
  XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ViewsImage_OnSetColor( &_this->ConnectedIcon, ResOnPrimary );
  ViewsText_OnSetColor( &_this->SSIDText, ResOnPrimary );
  ViewsImage_OnSetColor( &_this->WifiIcon, ResOnPrimary );
  ViewsImage_OnSetColor( &_this->InfoIcon, ResPrimary );
}

/* 'C' function for method : 'Application::WifiNetworkListItem.UpdateData()' */
void ApplicationWifiNetworkListItem_UpdateData( ApplicationWifiNetworkListItem _this, 
  XInt32 aItemIndex )
{
  XInt32 connected;
  XInt32 signalStrength;

  ComponentsListItem_UpdateData((ComponentsListItem)_this, aItemIndex );

  if ( _this->Super1.DataProvider == 0 )
    return;

  ViewsText__OnSetString( &_this->SSIDText, DeviceDataProvider__GetStringData( _this->Super1.DataProvider, 
  _this->Super1.Index, 0 ));
  connected = DeviceDataProvider__GetInt32Data( _this->Super1.DataProvider, _this->Super1.Index, 
  2 );
  ViewsImage_OnSetVisible( &_this->ConnectedIcon, (XBool)( connected == 1 ));
  signalStrength = DeviceDataProvider__GetInt32Data( _this->Super1.DataProvider, 
  _this->Super1.Index, 1 );
  ViewsImage_OnSetBitmap( &_this->WifiIcon, DeviceEnumClass__GetIcon( EwGetAutoObject( 
  &DeviceWifiSignalEnum, DeviceWifiSignalEnumClass ), signalStrength ));
}

/* This internal slot method is called when the user touches the button's area. */
void ApplicationWifiNetworkListItem_onPressTouch( ApplicationWifiNetworkListItem _this, 
  XObject sender )
{
  ApplicationWifiConfigPopup popup;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  popup = EwCastObject( ApplicationPopupNavigatorClass_GetCurrentPopup( EwGetAutoObject( 
  &ApplicationPopupNavigator, ApplicationPopupNavigatorClass )), ApplicationWifiConfigPopup );

  if ( popup == 0 )
  {
    popup = EwNewObject( ApplicationWifiConfigPopup, 0 );

    if ( popup != 0 )
    {
      ApplicationWifiConfigPopup_OnSetNetworkIndex( popup, _this->Super1.Index );
      ApplicationPopupNavigatorClass_OpenPopup( EwGetAutoObject( &ApplicationPopupNavigator, 
      ApplicationPopupNavigatorClass ), ((ApplicationPopup)popup ), ((EffectsTransition)EwGetAutoObject( 
      &ApplicationSlideLeft, EffectsSlideTransition )));
    }
  }
  else
    ApplicationWifiConfigPopup_OnSetNetworkIndex( popup, _this->Super1.Index );
}

/* Variants derived from the class : 'Application::WifiNetworkListItem' */
EW_DEFINE_CLASS_VARIANTS( ApplicationWifiNetworkListItem )
EW_END_OF_CLASS_VARIANTS( ApplicationWifiNetworkListItem )

/* Virtual Method Table (VMT) for the class : 'Application::WifiNetworkListItem' */
EW_DEFINE_CLASS( ApplicationWifiNetworkListItem, ComponentsListItem, SSIDText, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Application::WifiNetworkListItem" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  ApplicationWifiNetworkListItem_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationWifiNetworkListItem_UpdateData,
EW_END_OF_CLASS( ApplicationWifiNetworkListItem )

/* Initializer for the class 'Application::WifiConfigPopup' */
void ApplicationWifiConfigPopup__Init( ApplicationWifiConfigPopup _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ApplicationPopup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationWifiConfigPopup );

  /* ... then construct all embedded objects */
  ViewsRectangle__Init( &_this->Background, &_this->_.XObject, 0 );
  ComponentsRoundIconButton__Init( &_this->CloseButton, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->CaptionText, &_this->_.XObject, 0 );
  ComponentsVertScrollbar__Init( &_this->VertScrollbar, &_this->_.XObject, 0 );
  CoreSlideTouchHandler__Init( &_this->SlideTouchHandler, &_this->_.XObject, 0 );
  CoreOutline__Init( &_this->Outline, &_this->_.XObject, 0 );
  ComponentsStringSettingItem__Init( &_this->SSIDItem, &_this->_.XObject, 0 );
  ComponentsEnumSettingItem__Init( &_this->ConnectionStatusItem, &_this->_.XObject, 0 );
  ComponentsStringSettingItem__Init( &_this->SecurityItem, &_this->_.XObject, 0 );
  ComponentsStringSettingItem__Init( &_this->IPAddressItem, &_this->_.XObject, 0 );
  ComponentsStringSettingItem__Init( &_this->GatewayItem, &_this->_.XObject, 0 );
  ComponentsStringSettingItem__Init( &_this->SubnetMaskItem, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationWifiConfigPopup );

  /* ... and initialize objects, variables, properties, etc. */
  NavigationPage__OnSetCaption( _this, EwLoadString( &StringsWiFiConfigurations ));
  _this->Super1.FadeBackground = 1;
  _this->Super1.ScrimColor = ResOverlayTransparent;
  CoreRectView__OnSetBounds( &_this->Background, _Const00A9 );
  ViewsRectangle_OnSetRadiusBL( &_this->Background, 30 );
  ViewsRectangle_OnSetRadiusTL( &_this->Background, 30 );
  CoreRectView__OnSetBounds( &_this->CloseButton, _Const00AA );
  CoreRectView__OnSetBounds( &_this->CaptionText, _Const00AB );
  ViewsText_OnSetOverflowWarning( &_this->CaptionText, 1 );
  CoreRectView__OnSetBounds( &_this->VertScrollbar, _Const00AC );
  CoreRectView__OnSetBounds( &_this->SlideTouchHandler, _Const00AD );
  _this->SlideTouchHandler.SlideHorz = 0;
  CoreRectView__OnSetBounds( &_this->Outline, _Const00AE );
  CoreOutline_OnSetPaddingBottom( &_this->Outline, 16 );
  CoreOutline_OnSetPaddingTop( &_this->Outline, 38 );
  CoreOutline_OnSetSpaceVert( &_this->Outline, 16 );
  CoreOutline_OnSetFormation( &_this->Outline, CoreFormationTopToBottom );
  _this->NetworkIndex = -1;
  CoreRectView__OnSetBounds( &_this->SSIDItem, _Const00AF );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->SSIDItem, 1 );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->SSIDItem, EwLoadString( 
  &StringsWiFiName ));
  ComponentsSettingItem_OnSetValueAreaWith((ComponentsSettingItem)&_this->SSIDItem, 
  230 );
  ComponentsSettingItem_OnSetValuePadding((ComponentsSettingItem)&_this->SSIDItem, 
  16 );
  ComponentsSettingItem_OnSetCaptionValueSpace((ComponentsSettingItem)&_this->SSIDItem, 
  24 );
  CoreRectView__OnSetBounds( &_this->ConnectionStatusItem, _Const00B0 );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->ConnectionStatusItem, 1 );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->ConnectionStatusItem, 
  EwLoadString( &StringsConnectionStatus ));
  ComponentsSettingItem_OnSetValueAreaWith((ComponentsSettingItem)&_this->ConnectionStatusItem, 
  230 );
  ComponentsSettingItem_OnSetValuePadding((ComponentsSettingItem)&_this->ConnectionStatusItem, 
  16 );
  ComponentsSettingItem_OnSetCaptionValueSpace((ComponentsSettingItem)&_this->ConnectionStatusItem, 
  24 );
  CoreRectView__OnSetBounds( &_this->SecurityItem, _Const00B1 );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->SecurityItem, 1 );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->SecurityItem, 
  EwLoadString( &StringsSecurity ));
  ComponentsSettingItem_OnSetValueAreaWith((ComponentsSettingItem)&_this->SecurityItem, 
  230 );
  ComponentsSettingItem_OnSetValuePadding((ComponentsSettingItem)&_this->SecurityItem, 
  16 );
  ComponentsSettingItem_OnSetCaptionValueSpace((ComponentsSettingItem)&_this->SecurityItem, 
  24 );
  CoreRectView__OnSetBounds( &_this->IPAddressItem, _Const00B2 );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->IPAddressItem, 1 );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->IPAddressItem, 
  EwLoadString( &StringsIPAddress ));
  ComponentsSettingItem_OnSetValueAreaWith((ComponentsSettingItem)&_this->IPAddressItem, 
  230 );
  ComponentsSettingItem_OnSetValuePadding((ComponentsSettingItem)&_this->IPAddressItem, 
  16 );
  ComponentsSettingItem_OnSetCaptionValueSpace((ComponentsSettingItem)&_this->IPAddressItem, 
  24 );
  CoreRectView__OnSetBounds( &_this->GatewayItem, _Const00B3 );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->GatewayItem, 1 );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->GatewayItem, 
  EwLoadString( &StringsGateway ));
  ComponentsSettingItem_OnSetValueAreaWith((ComponentsSettingItem)&_this->GatewayItem, 
  230 );
  ComponentsSettingItem_OnSetValuePadding((ComponentsSettingItem)&_this->GatewayItem, 
  16 );
  ComponentsSettingItem_OnSetCaptionValueSpace((ComponentsSettingItem)&_this->GatewayItem, 
  24 );
  CoreRectView__OnSetBounds( &_this->SubnetMaskItem, _Const00B4 );
  CoreGroup_OnSetEmbedded((CoreGroup)&_this->SubnetMaskItem, 1 );
  ComponentsSettingItem_OnSetCaption((ComponentsSettingItem)&_this->SubnetMaskItem, 
  EwLoadString( &StringsSubnetMask ));
  ComponentsSettingItem_OnSetValueAreaWith((ComponentsSettingItem)&_this->SubnetMaskItem, 
  230 );
  ComponentsSettingItem_OnSetValuePadding((ComponentsSettingItem)&_this->SubnetMaskItem, 
  16 );
  ComponentsSettingItem_OnSetCaptionValueSpace((ComponentsSettingItem)&_this->SubnetMaskItem, 
  24 );
  CoreGroup__Add( _this, ((CoreView)&_this->Background ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->CloseButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->CaptionText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->VertScrollbar ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->SlideTouchHandler ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Outline ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->SSIDItem ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ConnectionStatusItem ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->SecurityItem ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->IPAddressItem ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->GatewayItem ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->SubnetMaskItem ), 0 );
  _this->CloseButton.Super2.OnActivate = EwNewSlot( _this, ApplicationWifiConfigPopup_close );
  ComponentsRoundIconButton_OnSetIcon( &_this->CloseButton, EwLoadResource( &Resx, 
  ResourcesBitmap ));
  ViewsText__OnSetFont( &_this->CaptionText, EwLoadResource( &FontsHeading2, ResourcesFont ));
  _this->Outline.OnUpdate = EwNewSlot( _this, ApplicationWifiConfigPopup_onOutlineUpdate );
  CoreOutline_OnSetSlideHandler( &_this->Outline, &_this->SlideTouchHandler );
  ComponentsEnumSettingItem_OnSetEnum( &_this->ConnectionStatusItem, ((DeviceEnumClass)EwGetAutoObject( 
  &DeviceWifiConnectionStatusEnum, DeviceWifiConnectionStatusEnumClass )));

  /* Call the user defined constructor */
  ApplicationWifiConfigPopup_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::WifiConfigPopup' */
void ApplicationWifiConfigPopup__ReInit( ApplicationWifiConfigPopup _this )
{
  /* At first re-initialize the super class ... */
  ApplicationPopup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsRectangle__ReInit( &_this->Background );
  ComponentsRoundIconButton__ReInit( &_this->CloseButton );
  ViewsText__ReInit( &_this->CaptionText );
  ComponentsVertScrollbar__ReInit( &_this->VertScrollbar );
  CoreSlideTouchHandler__ReInit( &_this->SlideTouchHandler );
  CoreOutline__ReInit( &_this->Outline );
  ComponentsStringSettingItem__ReInit( &_this->SSIDItem );
  ComponentsEnumSettingItem__ReInit( &_this->ConnectionStatusItem );
  ComponentsStringSettingItem__ReInit( &_this->SecurityItem );
  ComponentsStringSettingItem__ReInit( &_this->IPAddressItem );
  ComponentsStringSettingItem__ReInit( &_this->GatewayItem );
  ComponentsStringSettingItem__ReInit( &_this->SubnetMaskItem );
}

/* Finalizer method for the class 'Application::WifiConfigPopup' */
void ApplicationWifiConfigPopup__Done( ApplicationWifiConfigPopup _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ApplicationPopup );

  /* Finalize all embedded objects */
  ViewsRectangle__Done( &_this->Background );
  ComponentsRoundIconButton__Done( &_this->CloseButton );
  ViewsText__Done( &_this->CaptionText );
  ComponentsVertScrollbar__Done( &_this->VertScrollbar );
  CoreSlideTouchHandler__Done( &_this->SlideTouchHandler );
  CoreOutline__Done( &_this->Outline );
  ComponentsStringSettingItem__Done( &_this->SSIDItem );
  ComponentsEnumSettingItem__Done( &_this->ConnectionStatusItem );
  ComponentsStringSettingItem__Done( &_this->SecurityItem );
  ComponentsStringSettingItem__Done( &_this->IPAddressItem );
  ComponentsStringSettingItem__Done( &_this->GatewayItem );
  ComponentsStringSettingItem__Done( &_this->SubnetMaskItem );

  /* Don't forget to deinitialize the super class ... */
  ApplicationPopup__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationWifiConfigPopup_Init( ApplicationWifiConfigPopup _this, XHandle 
  aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* The method UpdateViewState() is invoked automatically after the state of the 
   component has been changed. This method can be overridden and filled with logic 
   to ensure the visual aspect of the component does reflect its current state. 
   For example, the 'enabled' state of the component can affect its colors (disabled 
   components may appear pale). In this case the logic of the method should modify 
   the respective color properties accordingly to the current 'enabled' state. 
   The current state of the component is passed as a set in the parameter aState. 
   It reflects the very basic component state like its visibility or the ability 
   to react to user inputs. Beside this common state, the method can also involve 
   any other variables used in the component as long as they reflect its current 
   state. For example, the toggle switch component can take in account its toggle 
   state 'on' or 'off' and change accordingly the location of the slider, etc.
   Usually, this method will be invoked automatically by the framework. Optionally 
   you can request its invocation by using the method @InvalidateViewState(). */
void ApplicationWifiConfigPopup_UpdateViewState( ApplicationWifiConfigPopup _this, 
  XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ViewsRectangle_OnSetColor( &_this->Background, ResSurface2 );
  ViewsText_OnSetColor( &_this->CaptionText, ResOnPrimary );
}

/* 'C' function for method : 'Application::WifiConfigPopup.OnSetCaption()' */
void ApplicationWifiConfigPopup_OnSetCaption( ApplicationWifiConfigPopup _this, 
  XString value )
{
  NavigationPage_OnSetCaption((NavigationPage)_this, value );
  ViewsText__OnSetString( &_this->CaptionText, value );
}

/* 'C' function for method : 'Application::WifiConfigPopup.close()' */
void ApplicationWifiConfigPopup_close( ApplicationWifiConfigPopup _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ApplicationPopupNavigatorClass_ClosePopup( EwGetAutoObject( &ApplicationPopupNavigator, 
  ApplicationPopupNavigatorClass ), ((ApplicationPopup)_this ), ((EffectsTransition)EwGetAutoObject( 
  &ApplicationSlideRight, EffectsSlideTransition )));
}

/* 'C' function for method : 'Application::WifiConfigPopup.onOutlineUpdate()' */
void ApplicationWifiConfigPopup_onOutlineUpdate( ApplicationWifiConfigPopup _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ComponentsVertScrollbar_OnSetContentArea( &_this->VertScrollbar, EwGetRectH( CoreOutline_GetContentArea( 
  &_this->Outline, CoreViewStateVisible )));
  ComponentsVertScrollbar_OnSetViewArea( &_this->VertScrollbar, EwGetRectH( _this->Outline.Super1.Bounds ));
  ComponentsVertScrollbar_OnSetPosition( &_this->VertScrollbar, -_this->Outline.ScrollOffset.Y );
  CoreSlideTouchHandler_OnSetEnabled( &_this->SlideTouchHandler, (XBool)( _this->VertScrollbar.ContentArea 
  > _this->VertScrollbar.ViewArea ));
}

/* 'C' function for method : 'Application::WifiConfigPopup.OnSetNetworkIndex()' */
void ApplicationWifiConfigPopup_OnSetNetworkIndex( ApplicationWifiConfigPopup _this, 
  XInt32 value )
{
  DeviceWifiNetworksProviderClass provider;
  XBool connected;

  if ( _this->NetworkIndex == value )
    return;

  _this->NetworkIndex = value;
  provider = EwGetAutoObject( &DeviceWifiNetworksProvider, DeviceWifiNetworksProviderClass );

  if ( provider == 0 )
    return;

  ComponentsStringSettingItem_OnSetValue( &_this->SSIDItem, DeviceDataProvider__GetStringData( 
  provider, value, 0 ));
  ComponentsEnumSettingItem_OnSetValue( &_this->ConnectionStatusItem, DeviceDataProvider__GetInt32Data( 
  provider, value, 2 ));
  ComponentsStringSettingItem_OnSetValue( &_this->SecurityItem, DeviceDataProvider__GetStringData( 
  provider, value, 3 ));
  connected = (XBool)( _this->ConnectionStatusItem.Value == 1 );

  if ( connected )
  {
    ComponentsStringSettingItem_OnSetValue( &_this->IPAddressItem, DeviceDataProvider__GetStringData( 
    provider, value, 4 ));
    ComponentsStringSettingItem_OnSetValue( &_this->GatewayItem, DeviceDataProvider__GetStringData( 
    provider, value, 5 ));
    ComponentsStringSettingItem_OnSetValue( &_this->SubnetMaskItem, DeviceDataProvider__GetStringData( 
    provider, value, 6 ));
  }

  CoreGroup_OnSetVisible((CoreGroup)&_this->IPAddressItem, connected );
  CoreGroup_OnSetVisible((CoreGroup)&_this->GatewayItem, connected );
  CoreGroup_OnSetVisible((CoreGroup)&_this->SubnetMaskItem, connected );
}

/* Variants derived from the class : 'Application::WifiConfigPopup' */
EW_DEFINE_CLASS_VARIANTS( ApplicationWifiConfigPopup )
EW_END_OF_CLASS_VARIANTS( ApplicationWifiConfigPopup )

/* Virtual Method Table (VMT) for the class : 'Application::WifiConfigPopup' */
EW_DEFINE_CLASS( ApplicationWifiConfigPopup, ApplicationPopup, Background, NetworkIndex, 
                 NetworkIndex, NetworkIndex, NetworkIndex, NetworkIndex, "Application::WifiConfigPopup" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreGroup_GetClipping,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  ApplicationWifiConfigPopup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ApplicationWifiConfigPopup_OnSetCaption,
  NavigationPage_onClose,
EW_END_OF_CLASS( ApplicationWifiConfigPopup )

/* Embedded Wizard */
