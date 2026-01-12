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
#include "_ApplicationInfoTipPopup.h"
#include "_ApplicationPopup.h"
#include "_ApplicationPopupNavigatorClass.h"
#include "_ComponentsBaseButton.h"
#include "_ComponentsBaseTile.h"
#include "_ComponentsBaseTileTime.h"
#include "_ComponentsBattery.h"
#include "_ComponentsDataList.h"
#include "_ComponentsDateTimeDisplay.h"
#include "_ComponentsDateTimeSettingItem.h"
#include "_ComponentsEditTile.h"
#include "_ComponentsEditTileNumValue.h"
#include "_ComponentsEditTileTime.h"
#include "_ComponentsEnumSettingItem.h"
#include "_ComponentsEnumValueDisplay.h"
#include "_ComponentsGauge.h"
#include "_ComponentsGaugeBase.h"
#include "_ComponentsGaugeExt.h"
#include "_ComponentsHeader.h"
#include "_ComponentsHorzValueBar.h"
#include "_ComponentsIconTextButton.h"
#include "_ComponentsInfoTip.h"
#include "_ComponentsIntSettingItem.h"
#include "_ComponentsIntValueDisplay.h"
#include "_ComponentsKeyButton.h"
#include "_ComponentsKeyboardPopupButton.h"
#include "_ComponentsListItem.h"
#include "_ComponentsLogo.h"
#include "_ComponentsMenuButton.h"
#include "_ComponentsNotificationButton.h"
#include "_ComponentsNumKeyboard.h"
#include "_ComponentsPressureSettingButton.h"
#include "_ComponentsPressureTile.h"
#include "_ComponentsProgressBar.h"
#include "_ComponentsQRCode.h"
#include "_ComponentsRoundButton.h"
#include "_ComponentsRoundIconButton.h"
#include "_ComponentsRoundRadioButton.h"
#include "_ComponentsRoundTextButton.h"
#include "_ComponentsSettingItem.h"
#include "_ComponentsSettingsButton.h"
#include "_ComponentsSettingsOpenButton.h"
#include "_ComponentsSpecialKeyButton.h"
#include "_ComponentsStringSettingItem.h"
#include "_ComponentsStringValueDisplay.h"
#include "_ComponentsTextButton.h"
#include "_ComponentsTextEditor.h"
#include "_ComponentsTile.h"
#include "_ComponentsTileInRunning.h"
#include "_ComponentsTileTime.h"
#include "_ComponentsTileTimeInRunning.h"
#include "_ComponentsTimePicker.h"
#include "_ComponentsToggleButton.h"
#include "_ComponentsValueDisplay.h"
#include "_ComponentsValueRangeDisplay.h"
#include "_ComponentsVertScrollbar.h"
#include "_CoreKeyPressHandler.h"
#include "_CoreQuadView.h"
#include "_CoreRoot.h"
#include "_CoreSimpleTouchHandler.h"
#include "_CoreSlideTouchHandler.h"
#include "_CoreTime.h"
#include "_CoreTimer.h"
#include "_CoreVerticalList.h"
#include "_CoreView.h"
#include "_DeviceDataProvider.h"
#include "_DeviceDeviceClass.h"
#include "_DeviceEnumClass.h"
#include "_EffectsBoolEffect.h"
#include "_ResourcesBitmap.h"
#include "_ResourcesFont.h"
#include "_ToolsHelperCollection.h"
#include "_ViewsImage.h"
#include "_ViewsLine.h"
#include "_ViewsRectangle.h"
#include "_ViewsText.h"
#include "_ViewsWarpImage.h"
#include "Application.h"
#include "Components.h"
#include "Core.h"
#include "Device.h"
#include "Fonts.h"
#include "Res.h"
#include "Resources.h"
#include "Strings.h"
#include "Tools.h"
#include "Views.h"

/* Compressed strings for the language 'Default'. */
EW_CONST_STRING_PRAGMA static const unsigned int _StringsDefault0[] =
{
  0x00000076, /* ratio 71.19 % */
  0xB8000F00, 0x800A8452, 0x00F00032, 0x21A003A0, 0x0F058182, 0x40085C26, 0x04004341,
  0x986C5A20, 0x8C46E091, 0x345C4B10, 0x80041100, 0x724C0016, 0x4291792C, 0x4E590048,
  0x44D91002, 0x293248A6, 0x02400267, 0x9ACE8740, 0xB94E453E, 0x00203448, 0x00000000
};

/* Constant values used in this 'C' module only. */
static const XRect _Const0000 = {{ 0, 0 }, { 150, 60 }};
static const XPoint _Const0001 = { 0, 60 };
static const XPoint _Const0002 = { 150, 60 };
static const XPoint _Const0003 = { 150, 0 };
static const XPoint _Const0004 = { 0, 0 };
static const XRect _Const0005 = {{ 0, 0 }, { 960, 64 }};
static const XStringRes _Const0006 = { _StringsDefault0, 0x0002 };
static const XColor _Const0007 = { 0xFF, 0xFF, 0xFF, 0xFF };
static const XRect _Const0008 = {{ 0, 0 }, { 32, 32 }};
static const XRect _Const0009 = {{ 0, 0 }, { 185, 12 }};
static const XRect _Const000A = {{ 0, 0 }, { 92, 12 }};
static const XRect _Const000B = {{ 0, 0 }, { 185, 8 }};
static const XRect _Const000C = {{ 0, 0 }, { 164, 134 }};
static const XRect _Const000D = {{ 77, 0 }, { 117, 48 }};
static const XColor _Const000E = { 0xFD, 0x9A, 0x7D, 0xFF };
static const XColor _Const000F = { 0xFF, 0x7C, 0xBA, 0xFF };
static const XRect _Const0010 = {{ 77, 75 }, { 116, 134 }};
static const XColor _Const0011 = { 0xDA, 0x4F, 0xFF, 0xFF };
static const XColor _Const0012 = { 0xFA, 0x5A, 0xF2, 0xFF };
static const XRect _Const0013 = {{ 0, 47 }, { 39, 134 }};
static const XColor _Const0014 = { 0xC5, 0x4C, 0xFF, 0xFF };
static const XColor _Const0015 = { 0x90, 0x47, 0xFE, 0xFF };
static const XRect _Const0016 = {{ 0, 0 }, { 77, 27 }};
static const XColor _Const0017 = { 0xFF, 0xDE, 0x04, 0xFF };
static const XRect _Const0018 = {{ 39, 48 }, { 132, 75 }};
static const XColor _Const0019 = { 0x9B, 0x48, 0xFE, 0xFF };
static const XColor _Const001A = { 0x69, 0x44, 0xFD, 0xFF };
static const XRect _Const001B = {{ 39, 106 }, { 77, 133 }};
static const XColor _Const001C = { 0xBB, 0x4B, 0xFE, 0xFF };
static const XColor _Const001D = { 0xE3, 0x52, 0xFB, 0xFF };
static const XRect _Const001E = {{ 136, 47 }, { 164, 75 }};
static const XRect _Const001F = {{ 0, 0 }, { 116, 88 }};
static const XRect _Const0020 = {{ 0, 6 }, { 116, 30 }};
static const XRect _Const0021 = {{ 0, 30 }, { 116, 62 }};
static const XRect _Const0022 = {{ 0, 60 }, { 116, 88 }};
static const XRect _Const0023 = {{ 0, 0 }, { 345, 240 }};
static const XRect _Const0024 = {{ 16, 16 }, { 52, 79 }};
static const XRect _Const0025 = {{ 60, 20 }, { 338, 68 }};
static const XRect _Const0026 = {{ 40, 156 }, { 338, 192 }};
static const XRect _Const0027 = {{ 28, 64 }, { 338, 156 }};
static const XRect _Const0028 = {{ 0, 0 }, { 220, 160 }};
static const XRect _Const0029 = {{ 48, 16 }, { 204, 46 }};
static const XRect _Const002A = {{ 16, 21 }, { 40, 45 }};
static const XRect _Const002B = {{ 16, 116 }, { 204, 146 }};
static const XRect _Const002C = {{ 16, 48 }, { 204, 114 }};
static const XRect _Const002D = {{ 0, 0 }, { 64, 64 }};
static const XRect _Const002E = {{ 0, 0 }, { 224, 304 }};
static const XRect _Const002F = {{ 0, 160 }, { 64, 224 }};
static const XRect _Const0030 = {{ 80, 160 }, { 144, 224 }};
static const XRect _Const0031 = {{ 160, 160 }, { 224, 224 }};
static const XRect _Const0032 = {{ 0, 80 }, { 64, 144 }};
static const XRect _Const0033 = {{ 80, 80 }, { 144, 144 }};
static const XRect _Const0034 = {{ 160, 80 }, { 224, 144 }};
static const XRect _Const0035 = {{ 80, 0 }, { 144, 64 }};
static const XRect _Const0036 = {{ 160, 0 }, { 224, 64 }};
static const XRect _Const0037 = {{ 0, 240 }, { 64, 304 }};
static const XRect _Const0038 = {{ 80, 240 }, { 144, 304 }};
static const XRect _Const0039 = {{ 160, 240 }, { 224, 304 }};
static const XRect _Const003A = {{ 0, 0 }, { 160, 120 }};
static const XStringRes _Const003B = { _StringsDefault0, 0x0009 };
static const XColor _Const003C = { 0x00, 0x00, 0x00, 0xFF };
static const XPoint _Const003D = { 50, 70 };
static const XPoint _Const003E = { 50, 50 };
static const XStringRes _Const003F = { _StringsDefault0, 0x0011 };
static const XStringRes _Const0040 = { _StringsDefault0, 0x0015 };
static const XStringRes _Const0041 = { _StringsDefault0, 0x0019 };
static const XRect _Const0042 = {{ 0, 0 }, { 412, 360 }};
static const XRect _Const0043 = {{ 258, 0 }, { 362, 360 }};
static const XPoint _Const0044 = { 0, 50 };
static const XRect _Const0045 = {{ 144, 0 }, { 249, 360 }};
static const XRect _Const0046 = {{ 26, 0 }, { 140, 360 }};
static const XRect _Const0047 = {{ 258, 0 }, { 304, 360 }};
static const XRect _Const0048 = {{ 144, 0 }, { 190, 360 }};
static const XRect _Const0049 = {{ 26, 0 }, { 72, 360 }};
static const XRect _Const004A = {{ 26, 130 }, { 386, 190 }};
static const XRect _Const004B = {{ 258, 130 }, { 304, 190 }};
static const XRect _Const004C = {{ 144, 130 }, { 190, 190 }};
static const XRect _Const004D = {{ 26, 130 }, { 72, 190 }};
static const XRect _Const004E = {{ 78, 130 }, { 142, 190 }};
static const XRect _Const004F = {{ 200, 130 }, { 250, 190 }};
static const XRect _Const0050 = {{ 314, 130 }, { 363, 190 }};
static const XRect _Const0051 = {{ 26, 0 }, { 363, 50 }};
static const XRect _Const0052 = {{ 26, 310 }, { 363, 360 }};
static const XRect _Const0053 = {{ 6, 12 }, { 24, 19 }};
static const XRect _Const0054 = {{ 0, 0 }, { 258, 62 }};
static const XRect _Const0055 = {{ 16, 0 }, { 52, 62 }};
static const XRect _Const0056 = {{ 44, 16 }, { 216, 46 }};
static const XRect _Const0057 = {{ 161, 90 }, { 194, 156 }};
static const XRect _Const0058 = {{ 16, 90 }, { 157, 156 }};
static const XRect _Const0059 = {{ 16, 39 }, { 157, 105 }};
static const XRect _Const005A = {{ 161, 39 }, { 194, 105 }};
static const XRect _Const005B = {{ 171, 39 }, { 216, 156 }};
static const XRect _Const005C = {{ 16, 124 }, { 201, 136 }};
static const XRect _Const005D = {{ 0, 0 }, { 321, 81 }};
static const XRect _Const005E = {{ 59, 14 }, { 219, 44 }};
static const XRect _Const005F = {{ 219, 53 }, { 295, 77 }};
static const XRect _Const0060 = {{ 219, 30 }, { 295, 60 }};
static const XRect _Const0061 = {{ 59, 38 }, { 219, 68 }};
static const XRect _Const0062 = {{ 16, 25 }, { 48, 57 }};
static const XRect _Const0063 = {{ 219, 10 }, { 295, 86 }};
static const XRect _Const0064 = {{ 0, 0 }, { 76, 76 }};
static const XPoint _Const0065 = { 6, 38 };
static const XPoint _Const0066 = { 2, 11 };
static const XRect _Const0067 = {{ 0, 0 }, { 186, 110 }};
static const XRect _Const0068 = {{ 0, 65 }, { 186, 95 }};
static const XRect _Const0069 = {{ 0, 18 }, { 186, 66 }};
static const XRect _Const006A = {{ 0, 0 }, { 186, 24 }};
static const XRect _Const006B = {{ 0, 0 }, { 80, 80 }};
static const XRect _Const006C = {{ 0, 42 }, { 80, 63 }};
static const XRect _Const006D = {{ 0, 18 }, { 80, 42 }};
static const XRect _Const006E = {{ 0, 0 }, { 200, 30 }};
static const XRect _Const006F = {{ 0, 0 }, { 166, 30 }};
static const XRect _Const0070 = {{ 176, 0 }, { 200, 30 }};
static const XPoint _Const0071 = { 200, 0 };
static const XPoint _Const0072 = { 200, 30 };
static const XPoint _Const0073 = { 0, 30 };
static const XRect _Const0074 = {{ 0, 0 }, { 72, 72 }};
static const XStringRes _Const0075 = { _StringsDefault0, 0x001D };
static const XStringRes _Const0076 = { _StringsDefault0, 0x0023 };
static const XRect _Const0077 = {{ 0, 0 }, { 447, 38 }};
static const XRect _Const0078 = {{ 0, 0 }, { 186, 38 }};
static const XRect _Const0079 = {{ 186, 0 }, { 447, 38 }};
static const XRect _Const007A = {{ 0, 0 }, { 509, 76 }};
static const XRect _Const007B = {{ 0, 0 }, { 387, 76 }};
static const XRect _Const007C = {{ 387, 0 }, { 509, 48 }};
static const XRect _Const007D = {{ 387, 48 }, { 509, 76 }};
static const XRect _Const007E = {{ 0, 0 }, { 8, 200 }};
static const XRect _Const007F = {{ 0, 0 }, { 8, 30 }};
static const XRect _Const0080 = {{ 0, 0 }, { 529, 68 }};
static const XRect _Const0081 = {{ 16, 15 }, { 54, 53 }};
static const XRect _Const0082 = {{ 16, 0 }, { 54, 68 }};
static const XRect _Const0083 = {{ 468, 0 }, { 492, 68 }};
static const XRect _Const0084 = {{ 0, 0 }, { 40, 20 }};
static const XRect _Const0085 = {{ 0, 1 }, { 18, 19 }};
static const XColor _Const0086 = { 0xFF, 0x00, 0x00, 0xFF };
static const XPoint _Const0087 = { 0, 20 };
static const XPoint _Const0088 = { 40, 20 };
static const XPoint _Const0089 = { 40, 0 };
static const XRect _Const008A = {{ 0, 0 }, { 300, 160 }};
static const XRect _Const008B = {{ 0, 0 }, { 282, 160 }};
static const XRect _Const008C = {{ 290, 0 }, { 296, 160 }};
static const XRect _Const008D = {{ 0, 0 }, { 286, 30 }};
static const XRect _Const008E = {{ 0, 130 }, { 286, 160 }};
static const XRect _Const008F = {{ 0, 0 }, { 300, 40 }};
static const XStringRes _Const0090 = { _StringsDefault0, 0x0027 };

/* Initializer for the class 'Components::BaseButton' */
void ComponentsBaseButton__Init( ComponentsBaseButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  TemplatesPushButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsBaseButton );

  /* ... then construct all embedded objects */
  CoreTimer__Init( &_this->FlashTimer, &_this->_.XObject, 0 );
  CoreKeyPressHandler__Init( &_this->KeyHandler, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->Background, &_this->_.XObject, 0 );
  CoreSimpleTouchHandler__Init( &_this->TouchHandler, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsBaseButton );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0000 );
  CoreTimer_OnSetPeriod( &_this->FlashTimer, 0 );
  CoreTimer_OnSetBegin( &_this->FlashTimer, 50 );
  _this->KeyHandler.Filter = CoreKeyCodeEnter;
  CoreView_OnSetLayout((CoreView)&_this->Background, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->Background, _Const0000 );
  ViewsRectangle_OnSetRadius( &_this->Background, 30 );
  CoreView_OnSetLayout((CoreView)&_this->TouchHandler, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToLeft | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz 
  | CoreLayoutResizeVert );
  CoreQuadView__OnSetPoint4( &_this->TouchHandler, _Const0001 );
  CoreQuadView__OnSetPoint3( &_this->TouchHandler, _Const0002 );
  CoreQuadView__OnSetPoint2( &_this->TouchHandler, _Const0003 );
  CoreQuadView__OnSetPoint1( &_this->TouchHandler, _Const0004 );
  _this->TouchHandler.RetargetCondition = CoreRetargetReasonWipeDown | CoreRetargetReasonWipeLeft 
  | CoreRetargetReasonWipeRight | CoreRetargetReasonWipeUp;
  CoreSimpleTouchHandler_OnSetMaxStrikeCount( &_this->TouchHandler, 100 );
  _this->BgColor = ResPrimaryContainer;
  _this->BgColorPressed = ResPrimary;
  _this->BgColorDisabled = ResSurface3;
  CoreGroup__Add( _this, ((CoreView)&_this->Background ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->TouchHandler ), 0 );
  _this->FlashTimer.OnTrigger = EwNewSlot( _this, ComponentsBaseButton_onFlashTimer );
  _this->KeyHandler.OnPress = EwNewSlot( _this, ComponentsBaseButton_onPressKey );
  _this->TouchHandler.OnLeave = EwNewSlot( _this, ComponentsBaseButton_onEnterLeaveTouch );
  _this->TouchHandler.OnEnter = EwNewSlot( _this, ComponentsBaseButton_onEnterLeaveTouch );
  _this->TouchHandler.OnRelease = EwNewSlot( _this, ComponentsBaseButton_onReleaseTouch );
  _this->TouchHandler.OnPress = EwNewSlot( _this, ComponentsBaseButton_onPressTouch );
}

/* Re-Initializer for the class 'Components::BaseButton' */
void ComponentsBaseButton__ReInit( ComponentsBaseButton _this )
{
  /* At first re-initialize the super class ... */
  TemplatesPushButton__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreTimer__ReInit( &_this->FlashTimer );
  CoreKeyPressHandler__ReInit( &_this->KeyHandler );
  ViewsRectangle__ReInit( &_this->Background );
  CoreSimpleTouchHandler__ReInit( &_this->TouchHandler );
}

/* Finalizer method for the class 'Components::BaseButton' */
void ComponentsBaseButton__Done( ComponentsBaseButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( TemplatesPushButton );

  /* Finalize all embedded objects */
  CoreTimer__Done( &_this->FlashTimer );
  CoreKeyPressHandler__Done( &_this->KeyHandler );
  ViewsRectangle__Done( &_this->Background );
  CoreSimpleTouchHandler__Done( &_this->TouchHandler );

  /* Don't forget to deinitialize the super class ... */
  TemplatesPushButton__Done( &_this->_.Super );
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
void ComponentsBaseButton_UpdateViewState( ComponentsBaseButton _this, XSet aState )
{
  XBool isEnabled;
  XBool isPressed;

  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  isEnabled = (( aState & CoreViewStateEnabled ) == CoreViewStateEnabled );
  isPressed = (XBool)(( _this->TouchHandler.Down && _this->TouchHandler.Inside ) 
  || _this->FlashTimer.Enabled );

  if ( !isEnabled )
    ViewsRectangle_OnSetColor( &_this->Background, _this->BgColorDisabled );
  else
    if ( isPressed )
      ViewsRectangle_OnSetColor( &_this->Background, _this->BgColorPressed );
    else
      ViewsRectangle_OnSetColor( &_this->Background, _this->BgColor );
}

/* This internal slot method is called when the '@FlashTimer' is expired. It ends 
   the short flash feedback effect. */
void ComponentsBaseButton_onFlashTimer( ComponentsBaseButton _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_InvalidateViewState((CoreGroup)_this );
  EwPostSignal( EwNewSlot( _this, ComponentsBaseButton__onActivate ), ((XObject)_this ));
}

/* This internal slot method is called when the '@KeyHandler' is activated (when 
   the user has pressed the key specified in the property 'Filter' of the key handler). */
void ComponentsBaseButton_onPressKey( ComponentsBaseButton _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->TouchHandler.Down )
    return;

  if ( _this->KeyHandler.Repetition )
    return;

  CoreGroup_InvalidateViewState((CoreGroup)_this );

  if ( _this->FlashTimer.Enabled )
  {
    EwPostSignal( EwNewSlot( _this, ComponentsBaseButton__onActivate ), ((XObject)_this ));
    CoreTimer_OnSetEnabled( &_this->FlashTimer, 0 );
  }

  CoreTimer_OnSetEnabled( &_this->FlashTimer, 1 );
}

/* This internal slot method is called when the user drags the finger while pressing 
   the button. This only updates the button to appear pressed or released. */
void ComponentsBaseButton_onEnterLeaveTouch( ComponentsBaseButton _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* This internal slot method is called when the user releases the touch screen after 
   touching the button's area. This activates the button. */
void ComponentsBaseButton_onReleaseTouch( ComponentsBaseButton _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( !_this->TouchHandler.Inside )
    return;

  if ( _this->TouchHandler.AutoDeflected )
    return;

  if ( _this->TouchHandler.HoldPeriod >= _this->FlashTimer.Begin )
    EwPostSignal( EwNewSlot( _this, ComponentsBaseButton__onActivate ), ((XObject)_this ));
  else
    CoreTimer_OnSetEnabled( &_this->FlashTimer, 1 );
}

/* This internal slot method is called when the user touches the button's area. */
void ComponentsBaseButton_onPressTouch( ComponentsBaseButton _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->FlashTimer.Enabled )
  {
    EwPostSignal( EwNewSlot( _this, ComponentsBaseButton__onActivate ), ((XObject)_this ));
    CoreTimer_OnSetEnabled( &_this->FlashTimer, 0 );
  }
}

/* 'C' function for method : 'Components::BaseButton.onActivate()' */
void ComponentsBaseButton_onActivate( ComponentsBaseButton _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  EwPostSignal( _this->OnActivate, ((XObject)_this ));
}

/* Wrapper function for the virtual method : 'Components::BaseButton.onActivate()' */
void ComponentsBaseButton__onActivate( void* _this, XObject sender )
{
  ((ComponentsBaseButton)_this)->_.VMT->onActivate((ComponentsBaseButton)_this, 
  sender );
}

/* 'C' function for method : 'Components::BaseButton.OnSetBgColor()' */
void ComponentsBaseButton_OnSetBgColor( ComponentsBaseButton _this, XColor value )
{
  if ( !EwCompColor( _this->BgColor, value ))
    return;

  _this->BgColor = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'Components::BaseButton.OnSetBgColorPressed()' */
void ComponentsBaseButton_OnSetBgColorPressed( ComponentsBaseButton _this, XColor 
  value )
{
  if ( !EwCompColor( _this->BgColorPressed, value ))
    return;

  _this->BgColorPressed = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* Variants derived from the class : 'Components::BaseButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsBaseButton )
EW_END_OF_CLASS_VARIANTS( ComponentsBaseButton )

/* Virtual Method Table (VMT) for the class : 'Components::BaseButton' */
EW_DEFINE_CLASS( ComponentsBaseButton, TemplatesPushButton, FlashTimer, OnActivate, 
                 OnActivate, BgColor, BgColor, BgColor, "Components::BaseButton" )
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
  ComponentsBaseButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
EW_END_OF_CLASS( ComponentsBaseButton )

/* Initializer for the class 'Components::Header' */
void ComponentsHeader__Init( ComponentsHeader _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsHeader );

  /* ... then construct all embedded objects */
  ViewsText__Init( &_this->CaptionText, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->IconImage, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsHeader );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0005 );
  CoreView_OnSetLayout((CoreView)&_this->CaptionText, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToLeft | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz 
  | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->CaptionText, _Const0005 );
  ViewsText_OnSetOverflowWarning( &_this->CaptionText, 1 );
  ViewsText_OnSetRowDistance( &_this->CaptionText, 32 );
  ViewsText__OnSetString( &_this->CaptionText, EwLoadString( &_Const0006 ));
  _this->Color = _Const0007;
  CoreRectView__OnSetBounds( &_this->IconImage, _Const0008 );
  CoreGroup__Add( _this, ((CoreView)&_this->CaptionText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->IconImage ), 0 );
  ViewsText__OnSetFont( &_this->CaptionText, EwLoadResource( &FontsHeading2, ResourcesFont ));

  /* Call the user defined constructor */
  ComponentsHeader_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::Header' */
void ComponentsHeader__ReInit( ComponentsHeader _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsText__ReInit( &_this->CaptionText );
  ViewsImage__ReInit( &_this->IconImage );
}

/* Finalizer method for the class 'Components::Header' */
void ComponentsHeader__Done( ComponentsHeader _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Finalize all embedded objects */
  ViewsText__Done( &_this->CaptionText );
  ViewsImage__Done( &_this->IconImage );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsHeader_Init( ComponentsHeader _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsHeader_UpdateLayout( ComponentsHeader _this, XPoint aSize )
{
  CoreGroup_UpdateLayout((CoreGroup)_this, aSize );
  CoreRectView__OnSetBounds( &_this->CaptionText, EwGetRectORect( _this->Super2.Bounds ));
  CoreRectView__OnSetBounds( &_this->IconImage, EwSetRectH( _this->IconImage.Super1.Bounds, 
  aSize.Y ));

  if (( _this->Icon != 0 ) && ( _this->CaptionText.Font != 0 ))
  {
    XInt32 captionWidth = ResourcesFont_GetTextAdvance( _this->CaptionText.Font, 
      _this->Caption, 0, -1 );
    XInt32 w = ( captionWidth + 8 ) + EwGetRectW( _this->IconImage.Super1.Bounds );
    CoreRectView__OnSetBounds( &_this->IconImage, EwSetRectX( _this->IconImage.Super1.Bounds, 
    ( aSize.X - w ) / 2 ));
    CoreRectView__OnSetBounds( &_this->CaptionText, EwSetRectX1( _this->CaptionText.Super1.Bounds, 
    _this->IconImage.Super1.Bounds.Point2.X + 8 ));
    CoreRectView__OnSetBounds( &_this->CaptionText, EwSetRectW( _this->CaptionText.Super1.Bounds, 
    captionWidth ));
  }
}

/* 'C' function for method : 'Components::Header.OnSetCaption()' */
void ComponentsHeader_OnSetCaption( ComponentsHeader _this, XString value )
{
  if ( !EwCompString( _this->Caption, value ))
    return;

  _this->Caption = EwShareString( value );
  ViewsText__OnSetString( &_this->CaptionText, value );
  CoreGroup_InvalidateLayout((CoreGroup)_this );
}

/* 'C' function for method : 'Components::Header.OnSetIcon()' */
void ComponentsHeader_OnSetIcon( ComponentsHeader _this, ResourcesBitmap value )
{
  if ( _this->Icon == value )
    return;

  _this->Icon = value;
  ViewsImage_OnSetBitmap( &_this->IconImage, value );
  CoreGroup_InvalidateLayout((CoreGroup)_this );
}

/* 'C' function for method : 'Components::Header.OnSetColor()' */
void ComponentsHeader_OnSetColor( ComponentsHeader _this, XColor value )
{
  if ( !EwCompColor( _this->Color, value ))
    return;

  _this->Color = value;
  ViewsText_OnSetColor( &_this->CaptionText, value );
  ViewsImage_OnSetColor( &_this->IconImage, value );
}

/* Variants derived from the class : 'Components::Header' */
EW_DEFINE_CLASS_VARIANTS( ComponentsHeader )
EW_END_OF_CLASS_VARIANTS( ComponentsHeader )

/* Virtual Method Table (VMT) for the class : 'Components::Header' */
EW_DEFINE_CLASS( ComponentsHeader, CoreGroup, CaptionText, Icon, Caption, Caption, 
                 Caption, Color, "Components::Header" )
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
  ComponentsHeader_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsHeader )

/* Initializer for the class 'Components::HorzValueBar' */
void ComponentsHorzValueBar__Init( ComponentsHorzValueBar _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  TemplatesHorizontalValueBar__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsHorzValueBar );

  /* ... then construct all embedded objects */
  ViewsRectangle__Init( &_this->Background, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->Track, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsHorzValueBar );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0009 );
  CoreView_OnSetLayout((CoreView)&_this->Background, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->Background, _Const0009 );
  ViewsRectangle_OnSetRadius( &_this->Background, 10 );
  CoreView_OnSetLayout((CoreView)&_this->Track, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToTop | CoreLayoutResizeHorz | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->Track, _Const000A );
  ViewsRectangle_OnSetRadius( &_this->Track, 10 );
  _this->CurrentValue = 50;
  _this->BarColor = _Const0007;
  _this->BgColor = ResBorder;
  CoreGroup__Add( _this, ((CoreView)&_this->Background ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Track ), 0 );
}

/* Re-Initializer for the class 'Components::HorzValueBar' */
void ComponentsHorzValueBar__ReInit( ComponentsHorzValueBar _this )
{
  /* At first re-initialize the super class ... */
  TemplatesHorizontalValueBar__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsRectangle__ReInit( &_this->Background );
  ViewsRectangle__ReInit( &_this->Track );
}

/* Finalizer method for the class 'Components::HorzValueBar' */
void ComponentsHorzValueBar__Done( ComponentsHorzValueBar _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( TemplatesHorizontalValueBar );

  /* Finalize all embedded objects */
  ViewsRectangle__Done( &_this->Background );
  ViewsRectangle__Done( &_this->Track );

  /* Don't forget to deinitialize the super class ... */
  TemplatesHorizontalValueBar__Done( &_this->_.Super );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsHorzValueBar_UpdateLayout( ComponentsHorzValueBar _this, XPoint aSize )
{
  CoreGroup_UpdateLayout((CoreGroup)_this, aSize );
  CoreRectView__OnSetBounds( &_this->Background, EwSetRectSize( _this->Background.Super1.Bounds, 
  aSize ));
  CoreRectView__OnSetBounds( &_this->Track, EwSetRectH( _this->Track.Super1.Bounds, 
  aSize.Y ));
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
void ComponentsHorzValueBar_UpdateViewState( ComponentsHorzValueBar _this, XSet 
  aState )
{
  XInt32 maxPos;
  XInt32 oldPos;
  XInt32 newPos;

  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ViewsRectangle_OnSetColor( &_this->Background, _this->BgColor );
  ViewsRectangle_OnSetColor( &_this->Track, _this->BarColor );
  maxPos = EwGetRectW( _this->Super3.Bounds );
  oldPos = _this->Track.Super1.Bounds.Point2.X;
  newPos = ( ComponentsHorzValueBar_OnGetCurrentValue( _this ) * maxPos ) / 100;

  if ( newPos != oldPos )
    CoreRectView__OnSetBounds( &_this->Track, EwSetRectX2( _this->Track.Super1.Bounds, 
    newPos ));
}

/* This slot method will receive a signal, if the value of the property assigned 
   to @Outlet has been changed by another widget or by the application logic. In 
   response to this notification, the widget will update itself. */
void ComponentsHorzValueBar_onOutlet( ComponentsHorzValueBar _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Outlet.Object != 0 )
    ComponentsHorzValueBar_OnSetCurrentValue( _this, EwOnGetInt32( _this->Outlet ));
}

/* 'C' function for method : 'Components::HorzValueBar.OnSetOutlet()' */
void ComponentsHorzValueBar_OnSetOutlet( ComponentsHorzValueBar _this, XRef value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  if ( _this->Outlet.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsHorzValueBar_onOutlet ), _this->Outlet, 
      0 );

  _this->Outlet = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsHorzValueBar_onOutlet ), value, 
      0 );

  if ( value.Object != 0 )
    EwPostSignal( EwNewSlot( _this, ComponentsHorzValueBar_onOutlet ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::HorzValueBar.OnGetCurrentValue()' */
XInt32 ComponentsHorzValueBar_OnGetCurrentValue( ComponentsHorzValueBar _this )
{
  XInt32 value = _this->CurrentValue;

  if ( value < 0 )
    value = 0;

  if ( value > 100 )
    value = 100;

  return value;
}

/* 'C' function for method : 'Components::HorzValueBar.OnSetCurrentValue()' */
void ComponentsHorzValueBar_OnSetCurrentValue( ComponentsHorzValueBar _this, XInt32 
  value )
{
  if ( _this->CurrentValue == value )
    return;

  _this->CurrentValue = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'Components::HorzValueBar.OnSetBarColor()' */
void ComponentsHorzValueBar_OnSetBarColor( ComponentsHorzValueBar _this, XColor 
  value )
{
  if ( !EwCompColor( _this->BarColor, value ))
    return;

  _this->BarColor = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* Variants derived from the class : 'Components::HorzValueBar' */
EW_DEFINE_CLASS_VARIANTS( ComponentsHorzValueBar )
EW_END_OF_CLASS_VARIANTS( ComponentsHorzValueBar )

/* Virtual Method Table (VMT) for the class : 'Components::HorzValueBar' */
EW_DEFINE_CLASS( ComponentsHorzValueBar, TemplatesHorizontalValueBar, Background, 
                 Outlet, Outlet, Outlet, CurrentValue, CurrentValue, "Components::HorzValueBar" )
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
  ComponentsHorzValueBar_UpdateLayout,
  ComponentsHorzValueBar_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsHorzValueBar )

/* Initializer for the class 'Components::ProgressBar' */
void ComponentsProgressBar__Init( ComponentsProgressBar _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsHorzValueBar__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsProgressBar );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsProgressBar );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const000B );
  ComponentsHorzValueBar_OnSetBarColor((ComponentsHorzValueBar)_this, ResPrimary );
}

/* Re-Initializer for the class 'Components::ProgressBar' */
void ComponentsProgressBar__ReInit( ComponentsProgressBar _this )
{
  /* At first re-initialize the super class ... */
  ComponentsHorzValueBar__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::ProgressBar' */
void ComponentsProgressBar__Done( ComponentsProgressBar _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsHorzValueBar );

  /* Don't forget to deinitialize the super class ... */
  ComponentsHorzValueBar__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Components::ProgressBar' */
EW_DEFINE_CLASS_VARIANTS( ComponentsProgressBar )
EW_END_OF_CLASS_VARIANTS( ComponentsProgressBar )

/* Virtual Method Table (VMT) for the class : 'Components::ProgressBar' */
EW_DEFINE_CLASS( ComponentsProgressBar, ComponentsHorzValueBar, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, _.VMT, "Components::ProgressBar" )
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
  ComponentsHorzValueBar_UpdateLayout,
  ComponentsHorzValueBar_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsProgressBar )

/* Initializer for the class 'Components::Logo' */
void ComponentsLogo__Init( ComponentsLogo _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsLogo );

  /* ... then construct all embedded objects */
  ViewsImage__Init( &_this->LogoTR, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->LogoBR, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->LogoBL, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->RectangleT, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->RectangleM, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->RectangleB, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->Circle, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsLogo );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const000C );
  CoreRectView__OnSetBounds( &_this->LogoTR, _Const000D );
  ViewsImage_OnSetColorBL( &_this->LogoTR, _Const000E );
  ViewsImage_OnSetColorBR( &_this->LogoTR, _Const000F );
  ViewsImage_OnSetColorTR( &_this->LogoTR, _Const000E );
  ViewsImage_OnSetColorTL( &_this->LogoTR, _Const000E );
  CoreRectView__OnSetBounds( &_this->LogoBR, _Const0010 );
  ViewsImage_OnSetColorBL( &_this->LogoBR, _Const0011 );
  ViewsImage_OnSetColorBR( &_this->LogoBR, _Const0011 );
  ViewsImage_OnSetColorTR( &_this->LogoBR, _Const0012 );
  ViewsImage_OnSetColorTL( &_this->LogoBR, _Const0012 );
  CoreRectView__OnSetBounds( &_this->LogoBL, _Const0013 );
  ViewsImage_OnSetColorBL( &_this->LogoBL, _Const0014 );
  ViewsImage_OnSetColorBR( &_this->LogoBL, _Const0014 );
  ViewsImage_OnSetColorTR( &_this->LogoBL, _Const0015 );
  ViewsImage_OnSetColorTL( &_this->LogoBL, _Const0015 );
  CoreRectView__OnSetBounds( &_this->RectangleT, _Const0016 );
  ViewsRectangle_OnSetRadiusBL( &_this->RectangleT, 14 );
  ViewsRectangle_OnSetRadiusTL( &_this->RectangleT, 14 );
  ViewsRectangle_OnSetColorBL( &_this->RectangleT, _Const0017 );
  ViewsRectangle_OnSetColorBR( &_this->RectangleT, _Const000E );
  ViewsRectangle_OnSetColorTR( &_this->RectangleT, _Const000E );
  ViewsRectangle_OnSetColorTL( &_this->RectangleT, _Const0017 );
  CoreRectView__OnSetBounds( &_this->RectangleM, _Const0018 );
  ViewsRectangle_OnSetRadiusBR( &_this->RectangleM, 14 );
  ViewsRectangle_OnSetRadiusTR( &_this->RectangleM, 14 );
  ViewsRectangle_OnSetColorBL( &_this->RectangleM, _Const0019 );
  ViewsRectangle_OnSetColorBR( &_this->RectangleM, _Const001A );
  ViewsRectangle_OnSetColorTR( &_this->RectangleM, _Const001A );
  ViewsRectangle_OnSetColorTL( &_this->RectangleM, _Const0019 );
  CoreRectView__OnSetBounds( &_this->RectangleB, _Const001B );
  ViewsRectangle_OnSetColorBL( &_this->RectangleB, _Const001C );
  ViewsRectangle_OnSetColorBR( &_this->RectangleB, _Const001D );
  ViewsRectangle_OnSetColorTR( &_this->RectangleB, _Const001D );
  ViewsRectangle_OnSetColorTL( &_this->RectangleB, _Const001C );
  CoreRectView__OnSetBounds( &_this->Circle, _Const001E );
  ViewsRectangle_OnSetRadius( &_this->Circle, 14 );
  ViewsRectangle_OnSetColor( &_this->Circle, _Const001A );
  CoreGroup__Add( _this, ((CoreView)&_this->LogoTR ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->LogoBR ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->LogoBL ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->RectangleT ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->RectangleM ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->RectangleB ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Circle ), 0 );
  ViewsImage_OnSetBitmap( &_this->LogoTR, EwLoadResource( &ReslogoTR, ResourcesBitmap ));
  ViewsImage_OnSetBitmap( &_this->LogoBR, EwLoadResource( &ReslogoBR, ResourcesBitmap ));
  ViewsImage_OnSetBitmap( &_this->LogoBL, EwLoadResource( &ReslogoBL, ResourcesBitmap ));
}

/* Re-Initializer for the class 'Components::Logo' */
void ComponentsLogo__ReInit( ComponentsLogo _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsImage__ReInit( &_this->LogoTR );
  ViewsImage__ReInit( &_this->LogoBR );
  ViewsImage__ReInit( &_this->LogoBL );
  ViewsRectangle__ReInit( &_this->RectangleT );
  ViewsRectangle__ReInit( &_this->RectangleM );
  ViewsRectangle__ReInit( &_this->RectangleB );
  ViewsRectangle__ReInit( &_this->Circle );
}

/* Finalizer method for the class 'Components::Logo' */
void ComponentsLogo__Done( ComponentsLogo _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Finalize all embedded objects */
  ViewsImage__Done( &_this->LogoTR );
  ViewsImage__Done( &_this->LogoBR );
  ViewsImage__Done( &_this->LogoBL );
  ViewsRectangle__Done( &_this->RectangleT );
  ViewsRectangle__Done( &_this->RectangleM );
  ViewsRectangle__Done( &_this->RectangleB );
  ViewsRectangle__Done( &_this->Circle );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Components::Logo' */
EW_DEFINE_CLASS_VARIANTS( ComponentsLogo )
EW_END_OF_CLASS_VARIANTS( ComponentsLogo )

/* Virtual Method Table (VMT) for the class : 'Components::Logo' */
EW_DEFINE_CLASS( ComponentsLogo, CoreGroup, LogoTR, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "Components::Logo" )
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
EW_END_OF_CLASS( ComponentsLogo )

/* Initializer for the class 'Components::BaseTile' */
void ComponentsBaseTile__Init( ComponentsBaseTile _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsBaseButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsBaseTile );

  /* ... then construct all embedded objects */
  ViewsText__Init( &_this->CaptionText, &_this->_.XObject, 0 );
  ComponentsIntValueDisplay__Init( &_this->ValueDisplay, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->UnitText, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsBaseTile );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const001F );
  CoreRectView__OnSetBounds( &_this->Super1.Background, _Const001F );
  ViewsRectangle_OnSetRadius( &_this->Super1.Background, 10 );
  CoreRectView__OnSetBounds( &_this->CaptionText, _Const0020 );
  ViewsText_OnSetOverflowWarning( &_this->CaptionText, 1 );
  ViewsText_OnSetAlignment( &_this->CaptionText, ViewsTextAlignmentAlignHorzCenter 
  | ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->CaptionText, EwLoadString( &_Const0006 ));
  CoreRectView__OnSetBounds( &_this->ValueDisplay, _Const0021 );
  ViewsText_OnSetOverflowWarning((ViewsText)&_this->ValueDisplay, 1 );
  ViewsText_OnSetAlignment((ViewsText)&_this->ValueDisplay, ViewsTextAlignmentAlignHorzCenter 
  | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->UnitText, _Const0022 );
  ViewsText_OnSetOverflowWarning( &_this->UnitText, 1 );
  ViewsText_OnSetAlignment( &_this->UnitText, ViewsTextAlignmentAlignHorzCenter 
  | ViewsTextAlignmentAlignVertCenter );
  _this->Precision = -1;
  CoreGroup__Add( _this, ((CoreView)&_this->CaptionText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ValueDisplay ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->UnitText ), 0 );
  ViewsText__OnSetFont( &_this->CaptionText, EwLoadResource( &FontsBody14, ResourcesFont ));
  ViewsText__OnSetFont( &_this->ValueDisplay, EwLoadResource( &FontsHeading2, ResourcesFont ));
  ViewsText__OnSetFont( &_this->UnitText, EwLoadResource( &FontsBody12, ResourcesFont ));
  _this->ValueFont = EwLoadResource( &FontsHeading2, ResourcesFont );

  /* Call the user defined constructor */
  ComponentsBaseTile_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::BaseTile' */
void ComponentsBaseTile__ReInit( ComponentsBaseTile _this )
{
  /* At first re-initialize the super class ... */
  ComponentsBaseButton__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsText__ReInit( &_this->CaptionText );
  ComponentsIntValueDisplay__ReInit( &_this->ValueDisplay );
  ViewsText__ReInit( &_this->UnitText );
}

/* Finalizer method for the class 'Components::BaseTile' */
void ComponentsBaseTile__Done( ComponentsBaseTile _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsBaseButton );

  /* Finalize all embedded objects */
  ViewsText__Done( &_this->CaptionText );
  ComponentsIntValueDisplay__Done( &_this->ValueDisplay );
  ViewsText__Done( &_this->UnitText );

  /* Don't forget to deinitialize the super class ... */
  ComponentsBaseButton__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsBaseTile_Init( ComponentsBaseTile _this, XHandle aArg )
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
void ComponentsBaseTile_UpdateViewState( ComponentsBaseTile _this, XSet aState )
{
  ComponentsBaseButton_UpdateViewState((ComponentsBaseButton)_this, aState );
  ViewsRectangle_OnSetColor( &_this->Super1.Background, ResSurface3 );
  ViewsText_OnSetColor( &_this->CaptionText, ResOnPrimary );
  ViewsText_OnSetColor((ViewsText)&_this->ValueDisplay, ResOnPrimary );
  ViewsText_OnSetColor( &_this->UnitText, ResOnPrimary );
}

/* 'C' function for method : 'Components::BaseTile.OnSetCaption()' */
void ComponentsBaseTile_OnSetCaption( ComponentsBaseTile _this, XString value )
{
  if ( !EwCompString( _this->Caption, value ))
    return;

  _this->Caption = EwShareString( value );
  ViewsText__OnSetString( &_this->CaptionText, value );
}

/* 'C' function for method : 'Components::BaseTile.OnSetUnit()' */
void ComponentsBaseTile_OnSetUnit( ComponentsBaseTile _this, XString value )
{
  if ( !EwCompString( _this->Unit, value ))
    return;

  _this->Unit = EwShareString( value );
  ViewsText__OnSetString( &_this->UnitText, value );
}

/* Wrapper function for the virtual method : 'Components::BaseTile.OnSetUnit()' */
void ComponentsBaseTile__OnSetUnit( void* _this, XString value )
{
  ((ComponentsBaseTile)_this)->_.VMT->OnSetUnit((ComponentsBaseTile)_this, value );
}

/* 'C' function for method : 'Components::BaseTile.OnSetValue()' */
void ComponentsBaseTile_OnSetValue( ComponentsBaseTile _this, XInt32 value )
{
  if ( _this->Value == value )
    return;

  _this->Value = value;
  ComponentsIntValueDisplay_OnSetValue( &_this->ValueDisplay, value );
}

/* Wrapper function for the virtual method : 'Components::BaseTile.OnSetValue()' */
void ComponentsBaseTile__OnSetValue( void* _this, XInt32 value )
{
  ((ComponentsBaseTile)_this)->_.VMT->OnSetValue((ComponentsBaseTile)_this, value );
}

/* 'C' function for method : 'Components::BaseTile.OnSetResolution()' */
void ComponentsBaseTile_OnSetResolution( ComponentsBaseTile _this, XInt32 value )
{
  if ( _this->Resolution == value )
    return;

  _this->Resolution = value;
  ComponentsIntValueDisplay_OnSetResolution( &_this->ValueDisplay, value );
}

/* Wrapper function for the virtual method : 'Components::BaseTile.OnSetResolution()' */
void ComponentsBaseTile__OnSetResolution( void* _this, XInt32 value )
{
  ((ComponentsBaseTile)_this)->_.VMT->OnSetResolution((ComponentsBaseTile)_this, 
  value );
}

/* 'C' function for method : 'Components::BaseTile.OnSetOutlet()' */
void ComponentsBaseTile_OnSetOutlet( ComponentsBaseTile _this, XRef value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  if ( _this->Outlet.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsBaseTile_onOutlet ), _this->Outlet, 
      0 );

  _this->Outlet = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsBaseTile_onOutlet ), _this->Outlet, 
      0 );

  EwPostSignal( EwNewSlot( _this, ComponentsBaseTile_onOutlet ), ((XObject)_this ));
}

/* Wrapper function for the virtual method : 'Components::BaseTile.OnSetOutlet()' */
void ComponentsBaseTile__OnSetOutlet( void* _this, XRef value )
{
  ((ComponentsBaseTile)_this)->_.VMT->OnSetOutlet((ComponentsBaseTile)_this, value );
}

/* 'C' function for method : 'Components::BaseTile.onOutlet()' */
void ComponentsBaseTile_onOutlet( ComponentsBaseTile _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Outlet.Object != 0 )
    ComponentsBaseTile__OnSetValue( _this, EwOnGetInt32( _this->Outlet ));
}

/* 'C' function for method : 'Components::BaseTile.OnSetValueFont()' */
void ComponentsBaseTile_OnSetValueFont( ComponentsBaseTile _this, ResourcesFont 
  value )
{
  if ( _this->ValueFont == value )
    return;

  _this->ValueFont = value;
  ViewsText__OnSetFont( &_this->ValueDisplay, value );
}

/* 'C' function for method : 'Components::BaseTile.OnSetValueFont1()' */
void ComponentsBaseTile_OnSetValueFont1( ComponentsBaseTile _this, ResourcesFont 
  value )
{
  if ( _this->ValueFont1 == value )
    return;

  _this->ValueFont1 = value;
  ComponentsValueDisplay_OnSetFont1((ComponentsValueDisplay)&_this->ValueDisplay, 
  value );
}

/* 'C' function for method : 'Components::BaseTile.OnSetPrecision()' */
void ComponentsBaseTile_OnSetPrecision( ComponentsBaseTile _this, XInt32 value )
{
  if ( _this->Precision == value )
    return;

  _this->Precision = value;
  ComponentsIntValueDisplay_OnSetPrecision( &_this->ValueDisplay, value );
}

/* Default onget method for the property 'Value' */
XInt32 ComponentsBaseTile_OnGetValue( ComponentsBaseTile _this )
{
  return _this->Value;
}

/* Variants derived from the class : 'Components::BaseTile' */
EW_DEFINE_CLASS_VARIANTS( ComponentsBaseTile )
EW_END_OF_CLASS_VARIANTS( ComponentsBaseTile )

/* Virtual Method Table (VMT) for the class : 'Components::BaseTile' */
EW_DEFINE_CLASS( ComponentsBaseTile, ComponentsBaseButton, CaptionText, ValueFont, 
                 Outlet, Outlet, Caption, Value, "Components::BaseTile" )
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
  ComponentsBaseTile_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsBaseTile_OnSetUnit,
  ComponentsBaseTile_OnSetValue,
  ComponentsBaseTile_OnSetResolution,
  ComponentsBaseTile_OnSetOutlet,
EW_END_OF_CLASS( ComponentsBaseTile )

/* Initializer for the class 'Components::TileTime' */
void ComponentsTileTime__Init( ComponentsTileTime _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsTile__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsTileTime );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsTileTime );

  /* ... and initialize objects, variables, properties, etc. */
  ViewsText__OnSetString( &_this->Super2.UnitText, EwLoadString( &StringsUnit_hour ));
  ComponentsIntValueDisplay_OnSetIsTime( &_this->Super2.ValueDisplay, 1 );

  /* Call the user defined constructor */
  ComponentsTileTime_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::TileTime' */
void ComponentsTileTime__ReInit( ComponentsTileTime _this )
{
  /* At first re-initialize the super class ... */
  ComponentsTile__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::TileTime' */
void ComponentsTileTime__Done( ComponentsTileTime _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsTile );

  /* Don't forget to deinitialize the super class ... */
  ComponentsTile__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsTileTime_Init( ComponentsTileTime _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  ComponentsBaseTile__OnSetUnit( _this, ToolsHelperCollection_GetTimeUnitString( 
  EwGetAutoObject( &ToolsHelper, ToolsHelperCollection ), _this->Super2.ValueDisplay.Super2.Font, 
  _this->Super2.UnitText.Font ));
}

/* Variants derived from the class : 'Components::TileTime' */
EW_DEFINE_CLASS_VARIANTS( ComponentsTileTime )
EW_END_OF_CLASS_VARIANTS( ComponentsTileTime )

/* Virtual Method Table (VMT) for the class : 'Components::TileTime' */
EW_DEFINE_CLASS( ComponentsTileTime, ComponentsTile, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, "Components::TileTime" )
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
  ComponentsTile_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsBaseTile_OnSetUnit,
  ComponentsBaseTile_OnSetValue,
  ComponentsBaseTile_OnSetResolution,
  ComponentsBaseTile_OnSetOutlet,
EW_END_OF_CLASS( ComponentsTileTime )

/* Initializer for the class 'Components::EditTile' */
void ComponentsEditTile__Init( ComponentsEditTile _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsTile__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsEditTile );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsEditTile );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0023 );
  CoreRectView__OnSetBounds( &_this->Super1.IconImage, _Const0024 );
  CoreRectView__OnSetBounds( &_this->Super2.CaptionText, _Const0025 );
  CoreRectView__OnSetBounds( &_this->Super2.UnitText, _Const0026 );
  CoreRectView__OnSetBounds( &_this->Super2.ValueDisplay, _Const0027 );
  ViewsText__OnSetFont( &_this->Super2.CaptionText, EwLoadResource( &FontsSmall, 
  ResourcesFont ));
  ViewsText__OnSetFont( &_this->Super2.UnitText, EwLoadResource( &FontsHeading2, 
  ResourcesFont ));
  ViewsText__OnSetFont( &_this->Super2.ValueDisplay, EwLoadResource( &FontsLarge, 
  ResourcesFont ));

  /* Call the user defined constructor */
  ComponentsEditTile_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::EditTile' */
void ComponentsEditTile__ReInit( ComponentsEditTile _this )
{
  /* At first re-initialize the super class ... */
  ComponentsTile__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::EditTile' */
void ComponentsEditTile__Done( ComponentsEditTile _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsTile );

  /* Don't forget to deinitialize the super class ... */
  ComponentsTile__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsEditTile_Init( ComponentsEditTile _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* 'C' function for method : 'Components::EditTile.OnSetValue()' */
void ComponentsEditTile_OnSetValue( ComponentsEditTile _this, XInt32 value )
{
  ComponentsBaseTile_OnSetValue((ComponentsBaseTile)_this, value );

  if ( _this->Super2.Outlet.Object != 0 )
    EwOnSetInt32( _this->Super2.Outlet, value );
}

/* 'C' function for method : 'Components::EditTile.Initialize()' */
void ComponentsEditTile_Initialize( ComponentsEditTile _this, ComponentsTile aTile )
{
  _this->ViewTile = aTile;

  if ( aTile == 0 )
    return;

  ComponentsBaseTile_OnSetCaption((ComponentsBaseTile)_this, aTile->Super1.Caption );
  ComponentsTile_OnSetIcon((ComponentsTile)_this, aTile->EditIcon );
  ComponentsBaseTile__OnSetValue( _this, aTile->Super1.Value );
  ComponentsBaseTile__OnSetResolution( _this, aTile->Super1.Resolution );
  ComponentsBaseTile__OnSetUnit( _this, aTile->Super1.Unit );
  _this->Super1.MinValue = aTile->MinValue;
  _this->Super1.MaxValue = aTile->MaxValue;
}

/* 'C' function for method : 'Components::EditTile.Save()' */
void ComponentsEditTile_Save( ComponentsEditTile _this )
{
  if ( _this->ViewTile != 0 )
  {
    ComponentsBaseTile__OnSetValue( _this->ViewTile, _this->Super2.Value );

    if ( _this->ViewTile->Super1.Outlet.Object != 0 )
      EwOnSetInt32( _this->ViewTile->Super1.Outlet, _this->Super2.Value );
  }
}

/* Wrapper function for the virtual method : 'Components::EditTile.Save()' */
void ComponentsEditTile__Save( void* _this )
{
  ((ComponentsEditTile)_this)->_.VMT->Save((ComponentsEditTile)_this );
}

/* 'C' function for method : 'Components::EditTile.Cancel()' */
void ComponentsEditTile_Cancel( ComponentsEditTile _this )
{
  if ( _this->ViewTile != 0 )
    ComponentsBaseTile__OnSetValue( _this, _this->ViewTile->Super1.Value );
}

/* Variants derived from the class : 'Components::EditTile' */
EW_DEFINE_CLASS_VARIANTS( ComponentsEditTile )
EW_END_OF_CLASS_VARIANTS( ComponentsEditTile )

/* Virtual Method Table (VMT) for the class : 'Components::EditTile' */
EW_DEFINE_CLASS( ComponentsEditTile, ComponentsTile, ViewTile, ViewTile, _.VMT, 
                 _.VMT, _.VMT, _.VMT, "Components::EditTile" )
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
  ComponentsTile_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsBaseTile_OnSetUnit,
  ComponentsEditTile_OnSetValue,
  ComponentsBaseTile_OnSetResolution,
  ComponentsBaseTile_OnSetOutlet,
  ComponentsEditTile_Save,
EW_END_OF_CLASS( ComponentsEditTile )

/* Initializer for the class 'Components::Tile' */
void ComponentsTile__Init( ComponentsTile _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsBaseTile__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsTile );

  /* ... then construct all embedded objects */
  ViewsImage__Init( &_this->IconImage, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsTile );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0028 );
  CoreRectView__OnSetBounds( &_this->Super2.Background, _Const0028 );
  ViewsRectangle_OnSetRadius( &_this->Super2.Background, 30 );
  CoreRectView__OnSetBounds( &_this->Super1.CaptionText, _Const0029 );
  ViewsText_OnSetAlignment( &_this->Super1.CaptionText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->IconImage, _Const002A );
  CoreRectView__OnSetBounds( &_this->Super1.UnitText, _Const002B );
  ViewsText_OnSetAlignment( &_this->Super1.UnitText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->Super1.ValueDisplay, _Const002C );
  ViewsText_OnSetAlignment((ViewsText)&_this->Super1.ValueDisplay, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  _this->MaxValue = 100;
  CoreGroup__Add( _this, ((CoreView)&_this->IconImage ), -2 );
  CoreGroup__Restack( _this, ((CoreView)&_this->Super1.UnitText ), -1 );
  ViewsText__OnSetFont( &_this->Super1.CaptionText, EwLoadResource( &FontsHeading3, 
  ResourcesFont ));
  ViewsText__OnSetFont( &_this->Super1.UnitText, EwLoadResource( &FontsHeading3, 
  ResourcesFont ));
  ViewsText__OnSetFont( &_this->Super1.ValueDisplay, EwLoadResource( &FontsMedium, 
  ResourcesFont ));
  ComponentsBaseTile_OnSetValueFont((ComponentsBaseTile)_this, EwLoadResource( &FontsMedium, 
  ResourcesFont ));

  /* Call the user defined constructor */
  ComponentsTile_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::Tile' */
void ComponentsTile__ReInit( ComponentsTile _this )
{
  /* At first re-initialize the super class ... */
  ComponentsBaseTile__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsImage__ReInit( &_this->IconImage );
}

/* Finalizer method for the class 'Components::Tile' */
void ComponentsTile__Done( ComponentsTile _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsBaseTile );

  /* Finalize all embedded objects */
  ViewsImage__Done( &_this->IconImage );

  /* Don't forget to deinitialize the super class ... */
  ComponentsBaseTile__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsTile_Init( ComponentsTile _this, XHandle aArg )
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
void ComponentsTile_UpdateViewState( ComponentsTile _this, XSet aState )
{
  ComponentsBaseTile_UpdateViewState((ComponentsBaseTile)_this, aState );
  ViewsRectangle_OnSetColor( &_this->Super2.Background, ResSurface1 );
  ViewsImage_OnSetColor( &_this->IconImage, ResOnSecondary );
  ViewsText_OnSetColor( &_this->Super1.CaptionText, ResOnSecondary );
  ViewsText_OnSetColor((ViewsText)&_this->Super1.ValueDisplay, ResOnPrimary );
  ViewsText_OnSetColor( &_this->Super1.UnitText, ResOnSecondary );
}

/* 'C' function for method : 'Components::Tile.OnSetIcon()' */
void ComponentsTile_OnSetIcon( ComponentsTile _this, ResourcesBitmap value )
{
  if ( _this->Icon == value )
    return;

  _this->Icon = value;
  ViewsImage_OnSetBitmap( &_this->IconImage, value );
}

/* Variants derived from the class : 'Components::Tile' */
EW_DEFINE_CLASS_VARIANTS( ComponentsTile )
EW_END_OF_CLASS_VARIANTS( ComponentsTile )

/* Virtual Method Table (VMT) for the class : 'Components::Tile' */
EW_DEFINE_CLASS( ComponentsTile, ComponentsBaseTile, IconImage, Icon, MinValue, 
                 MinValue, MinValue, MinValue, "Components::Tile" )
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
  ComponentsTile_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsBaseTile_OnSetUnit,
  ComponentsBaseTile_OnSetValue,
  ComponentsBaseTile_OnSetResolution,
  ComponentsBaseTile_OnSetOutlet,
EW_END_OF_CLASS( ComponentsTile )

/* Initializer for the class 'Components::BaseTileTime' */
void ComponentsBaseTileTime__Init( ComponentsBaseTileTime _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsBaseTile__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsBaseTileTime );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsBaseTileTime );

  /* ... and initialize objects, variables, properties, etc. */
  ComponentsIntValueDisplay_OnSetIsTime( &_this->Super1.ValueDisplay, 1 );

  /* Call the user defined constructor */
  ComponentsBaseTileTime_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::BaseTileTime' */
void ComponentsBaseTileTime__ReInit( ComponentsBaseTileTime _this )
{
  /* At first re-initialize the super class ... */
  ComponentsBaseTile__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::BaseTileTime' */
void ComponentsBaseTileTime__Done( ComponentsBaseTileTime _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsBaseTile );

  /* Don't forget to deinitialize the super class ... */
  ComponentsBaseTile__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsBaseTileTime_Init( ComponentsBaseTileTime _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  ComponentsBaseTile__OnSetUnit( _this, ToolsHelperCollection_GetTimeUnitString( 
  EwGetAutoObject( &ToolsHelper, ToolsHelperCollection ), _this->Super1.ValueDisplay.Super2.Font, 
  _this->Super1.UnitText.Font ));
}

/* Variants derived from the class : 'Components::BaseTileTime' */
EW_DEFINE_CLASS_VARIANTS( ComponentsBaseTileTime )
EW_END_OF_CLASS_VARIANTS( ComponentsBaseTileTime )

/* Virtual Method Table (VMT) for the class : 'Components::BaseTileTime' */
EW_DEFINE_CLASS( ComponentsBaseTileTime, ComponentsBaseTile, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, _.VMT, "Components::BaseTileTime" )
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
  ComponentsBaseTile_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsBaseTile_OnSetUnit,
  ComponentsBaseTile_OnSetValue,
  ComponentsBaseTile_OnSetResolution,
  ComponentsBaseTile_OnSetOutlet,
EW_END_OF_CLASS( ComponentsBaseTileTime )

/* Initializer for the class 'Components::EditTileTime' */
void ComponentsEditTileTime__Init( ComponentsEditTileTime _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsEditTile__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsEditTileTime );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsEditTileTime );

  /* ... and initialize objects, variables, properties, etc. */
  ComponentsIntValueDisplay_OnSetIsTime( &_this->Super3.ValueDisplay, 1 );

  /* Call the user defined constructor */
  ComponentsEditTileTime_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::EditTileTime' */
void ComponentsEditTileTime__ReInit( ComponentsEditTileTime _this )
{
  /* At first re-initialize the super class ... */
  ComponentsEditTile__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::EditTileTime' */
void ComponentsEditTileTime__Done( ComponentsEditTileTime _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsEditTile );

  /* Don't forget to deinitialize the super class ... */
  ComponentsEditTile__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsEditTileTime_Init( ComponentsEditTileTime _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  ComponentsBaseTile__OnSetUnit( _this, ToolsHelperCollection_GetTimeUnitString( 
  EwGetAutoObject( &ToolsHelper, ToolsHelperCollection ), _this->Super3.ValueDisplay.Super2.Font, 
  _this->Super3.UnitText.Font ));
}

/* Variants derived from the class : 'Components::EditTileTime' */
EW_DEFINE_CLASS_VARIANTS( ComponentsEditTileTime )
EW_END_OF_CLASS_VARIANTS( ComponentsEditTileTime )

/* Virtual Method Table (VMT) for the class : 'Components::EditTileTime' */
EW_DEFINE_CLASS( ComponentsEditTileTime, ComponentsEditTile, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, _.VMT, "Components::EditTileTime" )
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
  ComponentsTile_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsBaseTile_OnSetUnit,
  ComponentsEditTile_OnSetValue,
  ComponentsBaseTile_OnSetResolution,
  ComponentsBaseTile_OnSetOutlet,
  ComponentsEditTile_Save,
EW_END_OF_CLASS( ComponentsEditTileTime )

/* Initializer for the class 'Components::KeyButton' */
void ComponentsKeyButton__Init( ComponentsKeyButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsBaseButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsKeyButton );

  /* ... then construct all embedded objects */
  ViewsText__Init( &_this->KeyText, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsKeyButton );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const002D );
  CoreRectView__OnSetBounds( &_this->Super1.Background, _Const002D );
  ViewsRectangle_OnSetRadius( &_this->Super1.Background, 5 );
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)_this, ResOnSecondary );
  ComponentsBaseButton_OnSetBgColorPressed((ComponentsBaseButton)_this, ResOnPrimary );
  CoreRectView__OnSetBounds( &_this->KeyText, _Const002D );
  ViewsText_OnSetOverflowWarning( &_this->KeyText, 1 );
  CoreGroup__Add( _this, ((CoreView)&_this->KeyText ), 0 );
  ViewsText__OnSetFont( &_this->KeyText, EwLoadResource( &FontsMedium, ResourcesFont ));

  /* Call the user defined constructor */
  ComponentsKeyButton_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::KeyButton' */
void ComponentsKeyButton__ReInit( ComponentsKeyButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsBaseButton__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsText__ReInit( &_this->KeyText );
}

/* Finalizer method for the class 'Components::KeyButton' */
void ComponentsKeyButton__Done( ComponentsKeyButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsBaseButton );

  /* Finalize all embedded objects */
  ViewsText__Done( &_this->KeyText );

  /* Don't forget to deinitialize the super class ... */
  ComponentsBaseButton__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsKeyButton_Init( ComponentsKeyButton _this, XHandle aArg )
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
void ComponentsKeyButton_UpdateViewState( ComponentsKeyButton _this, XSet aState )
{
  XBool isPressed;

  ComponentsBaseButton_UpdateViewState((ComponentsBaseButton)_this, aState );
  isPressed = (XBool)(( _this->Super1.TouchHandler.Down && _this->Super1.TouchHandler.Inside ) 
  || _this->Super1.FlashTimer.Enabled );

  if ( isPressed )
  {
    ViewsRectangle_OnSetColor( &_this->Super1.Background, ResOnPrimary );
    ViewsText_OnSetColor( &_this->KeyText, ResPrimaryContainer );
  }
  else
  {
    ViewsRectangle_OnSetColor( &_this->Super1.Background, ResOnSecondary );
    ViewsText_OnSetColor( &_this->KeyText, ResPrimaryContainer );
  }
}

/* 'C' function for method : 'Components::KeyButton.OnSetKey()' */
void ComponentsKeyButton_OnSetKey( ComponentsKeyButton _this, XChar value )
{
  if ( _this->Key == value )
    return;

  _this->Key = value;
  ViewsText__OnSetString( &_this->KeyText, EwNewStringChar( value, 1 ));
}

/* Variants derived from the class : 'Components::KeyButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsKeyButton )
EW_END_OF_CLASS_VARIANTS( ComponentsKeyButton )

/* Virtual Method Table (VMT) for the class : 'Components::KeyButton' */
EW_DEFINE_CLASS( ComponentsKeyButton, ComponentsBaseButton, KeyText, Key, Key, Key, 
                 Key, Key, "Components::KeyButton" )
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
  ComponentsKeyButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
EW_END_OF_CLASS( ComponentsKeyButton )

/* Initializer for the class 'Components::SpecialKeyButton' */
void ComponentsSpecialKeyButton__Init( ComponentsSpecialKeyButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsKeyButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsSpecialKeyButton );

  /* ... then construct all embedded objects */
  ViewsImage__Init( &_this->Image, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsSpecialKeyButton );

  /* ... and initialize objects, variables, properties, etc. */
  ViewsText__OnSetString( &_this->Super1.KeyText, 0 );
  CoreView_OnSetLayout((CoreView)&_this->Image, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->Image, _Const002D );
  CoreGroup__Add( _this, ((CoreView)&_this->Image ), 0 );

  /* Call the user defined constructor */
  ComponentsSpecialKeyButton_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::SpecialKeyButton' */
void ComponentsSpecialKeyButton__ReInit( ComponentsSpecialKeyButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsKeyButton__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsImage__ReInit( &_this->Image );
}

/* Finalizer method for the class 'Components::SpecialKeyButton' */
void ComponentsSpecialKeyButton__Done( ComponentsSpecialKeyButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsKeyButton );

  /* Finalize all embedded objects */
  ViewsImage__Done( &_this->Image );

  /* Don't forget to deinitialize the super class ... */
  ComponentsKeyButton__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsSpecialKeyButton_Init( ComponentsSpecialKeyButton _this, XHandle 
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
void ComponentsSpecialKeyButton_UpdateViewState( ComponentsSpecialKeyButton _this, 
  XSet aState )
{
  ComponentsKeyButton_UpdateViewState((ComponentsKeyButton)_this, aState );
  ViewsImage_OnSetColor( &_this->Image, _this->Super1.KeyText.Color );
}

/* 'C' function for method : 'Components::SpecialKeyButton.OnSetIcon()' */
void ComponentsSpecialKeyButton_OnSetIcon( ComponentsSpecialKeyButton _this, ResourcesBitmap 
  value )
{
  if ( _this->Icon == value )
    return;

  _this->Icon = value;
  ViewsImage_OnSetBitmap( &_this->Image, value );
}

/* Variants derived from the class : 'Components::SpecialKeyButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsSpecialKeyButton )
EW_END_OF_CLASS_VARIANTS( ComponentsSpecialKeyButton )

/* Virtual Method Table (VMT) for the class : 'Components::SpecialKeyButton' */
EW_DEFINE_CLASS( ComponentsSpecialKeyButton, ComponentsKeyButton, Image, Icon, _.VMT, 
                 _.VMT, _.VMT, _.VMT, "Components::SpecialKeyButton" )
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
  ComponentsSpecialKeyButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
EW_END_OF_CLASS( ComponentsSpecialKeyButton )

/* Initializer for the class 'Components::NumKeyboard' */
void ComponentsNumKeyboard__Init( ComponentsNumKeyboard _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  TemplatesNumKeyboard__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsNumKeyboard );

  /* ... then construct all embedded objects */
  ComponentsKeyButton__Init( &_this->KeyButton1, &_this->_.XObject, 0 );
  ComponentsKeyButton__Init( &_this->KeyButton2, &_this->_.XObject, 0 );
  ComponentsKeyButton__Init( &_this->KeyButton3, &_this->_.XObject, 0 );
  ComponentsKeyButton__Init( &_this->KeyButton4, &_this->_.XObject, 0 );
  ComponentsKeyButton__Init( &_this->KeyButton5, &_this->_.XObject, 0 );
  ComponentsKeyButton__Init( &_this->KeyButton6, &_this->_.XObject, 0 );
  ComponentsKeyButton__Init( &_this->KeyButton7, &_this->_.XObject, 0 );
  ComponentsKeyButton__Init( &_this->KeyButton8, &_this->_.XObject, 0 );
  ComponentsKeyButton__Init( &_this->KeyButton9, &_this->_.XObject, 0 );
  ComponentsKeyButton__Init( &_this->KeyButton0, &_this->_.XObject, 0 );
  ComponentsKeyButton__Init( &_this->KeyButtonPoint, &_this->_.XObject, 0 );
  ComponentsSpecialKeyButton__Init( &_this->KeyBackspace, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsNumKeyboard );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const002E );
  CoreRectView__OnSetBounds( &_this->KeyButton1, _Const002F );
  ComponentsKeyButton_OnSetKey( &_this->KeyButton1, '1' );
  CoreRectView__OnSetBounds( &_this->KeyButton2, _Const0030 );
  ComponentsKeyButton_OnSetKey( &_this->KeyButton2, '2' );
  CoreRectView__OnSetBounds( &_this->KeyButton3, _Const0031 );
  ComponentsKeyButton_OnSetKey( &_this->KeyButton3, '3' );
  CoreRectView__OnSetBounds( &_this->KeyButton4, _Const0032 );
  ComponentsKeyButton_OnSetKey( &_this->KeyButton4, '4' );
  CoreRectView__OnSetBounds( &_this->KeyButton5, _Const0033 );
  ComponentsKeyButton_OnSetKey( &_this->KeyButton5, '5' );
  CoreRectView__OnSetBounds( &_this->KeyButton6, _Const0034 );
  ComponentsKeyButton_OnSetKey( &_this->KeyButton6, '6' );
  CoreRectView__OnSetBounds( &_this->KeyButton7, _Const002D );
  ComponentsKeyButton_OnSetKey( &_this->KeyButton7, '7' );
  CoreRectView__OnSetBounds( &_this->KeyButton8, _Const0035 );
  ComponentsKeyButton_OnSetKey( &_this->KeyButton8, '8' );
  CoreRectView__OnSetBounds( &_this->KeyButton9, _Const0036 );
  ComponentsKeyButton_OnSetKey( &_this->KeyButton9, '9' );
  CoreRectView__OnSetBounds( &_this->KeyButton0, _Const0037 );
  ComponentsKeyButton_OnSetKey( &_this->KeyButton0, '0' );
  CoreRectView__OnSetBounds( &_this->KeyButtonPoint, _Const0038 );
  ComponentsKeyButton_OnSetKey( &_this->KeyButtonPoint, '.' );
  CoreRectView__OnSetBounds( &_this->KeyBackspace, _Const0039 );
  CoreGroup__Add( _this, ((CoreView)&_this->KeyButton1 ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KeyButton2 ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KeyButton3 ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KeyButton4 ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KeyButton5 ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KeyButton6 ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KeyButton7 ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KeyButton8 ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KeyButton9 ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KeyButton0 ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KeyButtonPoint ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->KeyBackspace ), 0 );
  _this->KeyButton1.Super1.OnActivate = EwNewSlot( _this, ComponentsNumKeyboard_onActivateKey );
  _this->KeyButton2.Super1.OnActivate = EwNewSlot( _this, ComponentsNumKeyboard_onActivateKey );
  _this->KeyButton3.Super1.OnActivate = EwNewSlot( _this, ComponentsNumKeyboard_onActivateKey );
  _this->KeyButton4.Super1.OnActivate = EwNewSlot( _this, ComponentsNumKeyboard_onActivateKey );
  _this->KeyButton5.Super1.OnActivate = EwNewSlot( _this, ComponentsNumKeyboard_onActivateKey );
  _this->KeyButton6.Super1.OnActivate = EwNewSlot( _this, ComponentsNumKeyboard_onActivateKey );
  _this->KeyButton7.Super1.OnActivate = EwNewSlot( _this, ComponentsNumKeyboard_onActivateKey );
  _this->KeyButton8.Super1.OnActivate = EwNewSlot( _this, ComponentsNumKeyboard_onActivateKey );
  _this->KeyButton9.Super1.OnActivate = EwNewSlot( _this, ComponentsNumKeyboard_onActivateKey );
  _this->KeyButton0.Super1.OnActivate = EwNewSlot( _this, ComponentsNumKeyboard_onActivateKey );
  _this->KeyButtonPoint.Super1.OnActivate = EwNewSlot( _this, ComponentsNumKeyboard_onActivateKey );
  _this->KeyBackspace.Super2.OnActivate = EwNewSlot( _this, ComponentsNumKeyboard_onActivateKey );
  ComponentsSpecialKeyButton_OnSetIcon( &_this->KeyBackspace, EwLoadResource( &Resarrow_left_40px, 
  ResourcesBitmap ));
}

/* Re-Initializer for the class 'Components::NumKeyboard' */
void ComponentsNumKeyboard__ReInit( ComponentsNumKeyboard _this )
{
  /* At first re-initialize the super class ... */
  TemplatesNumKeyboard__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsKeyButton__ReInit( &_this->KeyButton1 );
  ComponentsKeyButton__ReInit( &_this->KeyButton2 );
  ComponentsKeyButton__ReInit( &_this->KeyButton3 );
  ComponentsKeyButton__ReInit( &_this->KeyButton4 );
  ComponentsKeyButton__ReInit( &_this->KeyButton5 );
  ComponentsKeyButton__ReInit( &_this->KeyButton6 );
  ComponentsKeyButton__ReInit( &_this->KeyButton7 );
  ComponentsKeyButton__ReInit( &_this->KeyButton8 );
  ComponentsKeyButton__ReInit( &_this->KeyButton9 );
  ComponentsKeyButton__ReInit( &_this->KeyButton0 );
  ComponentsKeyButton__ReInit( &_this->KeyButtonPoint );
  ComponentsSpecialKeyButton__ReInit( &_this->KeyBackspace );
}

/* Finalizer method for the class 'Components::NumKeyboard' */
void ComponentsNumKeyboard__Done( ComponentsNumKeyboard _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( TemplatesNumKeyboard );

  /* Finalize all embedded objects */
  ComponentsKeyButton__Done( &_this->KeyButton1 );
  ComponentsKeyButton__Done( &_this->KeyButton2 );
  ComponentsKeyButton__Done( &_this->KeyButton3 );
  ComponentsKeyButton__Done( &_this->KeyButton4 );
  ComponentsKeyButton__Done( &_this->KeyButton5 );
  ComponentsKeyButton__Done( &_this->KeyButton6 );
  ComponentsKeyButton__Done( &_this->KeyButton7 );
  ComponentsKeyButton__Done( &_this->KeyButton8 );
  ComponentsKeyButton__Done( &_this->KeyButton9 );
  ComponentsKeyButton__Done( &_this->KeyButton0 );
  ComponentsKeyButton__Done( &_this->KeyButtonPoint );
  ComponentsSpecialKeyButton__Done( &_this->KeyBackspace );

  /* Don't forget to deinitialize the super class ... */
  TemplatesNumKeyboard__Done( &_this->_.Super );
}

/* 'C' function for method : 'Components::NumKeyboard.onActivateKey()' */
void ComponentsNumKeyboard_onActivateKey( ComponentsNumKeyboard _this, XObject sender )
{
  ComponentsKeyButton keyBtn = EwCastObject( sender, ComponentsKeyButton );
  XChar charCode;
  XEnum keyCode;

  if ( keyBtn == 0 )
    return;

  charCode = 0x0000;
  keyCode = CoreKeyCodeNoKey;

  if ( sender == ((XObject)&_this->KeyBackspace ))
    keyCode = CoreKeyCodeBackspace;
  else
    if ( keyBtn != 0 )
      charCode = keyBtn->Key;

  if ( charCode != 0x0000 )
  {
    CoreRoot_DriveKeyboardHitting( CoreView__GetRoot( _this ), CoreKeyCodeNoKey, 
    charCode, 1 );
    CoreRoot_DriveKeyboardHitting( CoreView__GetRoot( _this ), CoreKeyCodeNoKey, 
    charCode, 0 );
  }

  if ( keyCode != CoreKeyCodeNoKey )
  {
    CoreRoot_DriveKeyboardHitting( CoreView__GetRoot( _this ), keyCode, 0x0000, 
    1 );
    CoreRoot_DriveKeyboardHitting( CoreView__GetRoot( _this ), keyCode, 0x0000, 
    0 );
  }
}

/* Variants derived from the class : 'Components::NumKeyboard' */
EW_DEFINE_CLASS_VARIANTS( ComponentsNumKeyboard )
EW_END_OF_CLASS_VARIANTS( ComponentsNumKeyboard )

/* Virtual Method Table (VMT) for the class : 'Components::NumKeyboard' */
EW_DEFINE_CLASS( ComponentsNumKeyboard, TemplatesNumKeyboard, KeyButton1, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Components::NumKeyboard" )
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
EW_END_OF_CLASS( ComponentsNumKeyboard )

/* Initializer for the class 'Components::KeyboardPopupButton' */
void ComponentsKeyboardPopupButton__Init( ComponentsKeyboardPopupButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsSpecialKeyButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsKeyboardPopupButton );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsKeyboardPopupButton );

  /* Call the user defined constructor */
  ComponentsKeyboardPopupButton_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::KeyboardPopupButton' */
void ComponentsKeyboardPopupButton__ReInit( ComponentsKeyboardPopupButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsSpecialKeyButton__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::KeyboardPopupButton' */
void ComponentsKeyboardPopupButton__Done( ComponentsKeyboardPopupButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsSpecialKeyButton );

  /* Don't forget to deinitialize the super class ... */
  ComponentsSpecialKeyButton__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsKeyboardPopupButton_Init( ComponentsKeyboardPopupButton _this, XHandle 
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
void ComponentsKeyboardPopupButton_UpdateViewState( ComponentsKeyboardPopupButton _this, 
  XSet aState )
{
  ComponentsSpecialKeyButton_UpdateViewState((ComponentsSpecialKeyButton)_this, 
  aState );
  ViewsRectangle_OnSetColor( &_this->Super3.Background, _this->Super3.BgColor );
  ViewsImage_OnSetColor( &_this->Super1.Image, ResOnPrimary );
}

/* Variants derived from the class : 'Components::KeyboardPopupButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsKeyboardPopupButton )
EW_END_OF_CLASS_VARIANTS( ComponentsKeyboardPopupButton )

/* Virtual Method Table (VMT) for the class : 'Components::KeyboardPopupButton' */
EW_DEFINE_CLASS( ComponentsKeyboardPopupButton, ComponentsSpecialKeyButton, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Components::KeyboardPopupButton" )
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
  ComponentsKeyboardPopupButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
EW_END_OF_CLASS( ComponentsKeyboardPopupButton )

/* Initializer for the class 'Components::TextEditor' */
void ComponentsTextEditor__Init( ComponentsTextEditor _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  TemplatesTextEditor__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsTextEditor );

  /* ... then construct all embedded objects */
  EffectsBoolEffect__Init( &_this->blinkEffect, &_this->_.XObject, 0 );
  CoreKeyPressHandler__Init( &_this->CursorKeyHandler, &_this->_.XObject, 0 );
  CoreKeyPressHandler__Init( &_this->BackspaceKeyHandler, &_this->_.XObject, 0 );
  CoreKeyPressHandler__Init( &_this->DeleteKeyHandler, &_this->_.XObject, 0 );
  CoreKeyPressHandler__Init( &_this->NewlineKeyHandler, &_this->_.XObject, 0 );
  CoreKeyPressHandler__Init( &_this->CharacterKeyHandler, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->Text, &_this->_.XObject, 0 );
  ViewsLine__Init( &_this->Caret, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsTextEditor );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const003A );
  _this->blinkEffect.Value2 = 0;
  _this->blinkEffect.Value1 = 1;
  EffectsBoolEffect_OnSetCycleDuration( &_this->blinkEffect, 500 );
  EffectsBoolEffect_OnSetInterCycleDelay( &_this->blinkEffect, 500 );
  _this->CursorKeyHandler.Filter = CoreKeyCodeCursorKeys;
  _this->CursorKeyHandler.Enabled = 0;
  _this->BackspaceKeyHandler.Filter = CoreKeyCodeBackspace;
  _this->DeleteKeyHandler.Filter = CoreKeyCodeDelete;
  _this->NewlineKeyHandler.Filter = CoreKeyCodeEnter;
  _this->NewlineKeyHandler.Enabled = 0;
  _this->CharacterKeyHandler.Filter = CoreKeyCodeCharacterKeys;
  CoreView_OnSetLayout((CoreView)&_this->Text, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->Text, _Const003A );
  ViewsText_OnSetAlignment( &_this->Text, ViewsTextAlignmentAlignHorzLeft | ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->Text, EwLoadString( &_Const003B ));
  ViewsText_OnSetColor( &_this->Text, _Const003C );
  CoreLineView_OnSetPoint2((CoreLineView)&_this->Caret, _Const003D );
  CoreLineView_OnSetPoint1((CoreLineView)&_this->Caret, _Const003E );
  ViewsLine_OnSetWidth2( &_this->Caret, 2 );
  ViewsLine_OnSetWidth1( &_this->Caret, 2 );
  ViewsLine_OnSetColor( &_this->Caret, _Const003C );
  ViewsLine_OnSetVisible( &_this->Caret, 0 );
  _this->Color = _Const003C;
  CoreGroup__Add( _this, ((CoreView)&_this->Text ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Caret ), 0 );
  _this->blinkEffect.Outlet = EwNewRef( &_this->Caret, ViewsLine_OnGetVisible, ViewsLine_OnSetVisible );
  _this->CursorKeyHandler.OnPress = EwNewSlot( _this, ComponentsTextEditor_onCursorKey );
  _this->CursorKeyHandler.OnHold = EwNewSlot( _this, ComponentsTextEditor_onCursorKey );
  _this->BackspaceKeyHandler.OnPress = EwNewSlot( _this, ComponentsTextEditor_onBackspaceKey );
  _this->BackspaceKeyHandler.OnHold = EwNewSlot( _this, ComponentsTextEditor_onBackspaceKey );
  _this->DeleteKeyHandler.OnPress = EwNewSlot( _this, ComponentsTextEditor_onDeleteKey );
  _this->DeleteKeyHandler.OnHold = EwNewSlot( _this, ComponentsTextEditor_onDeleteKey );
  _this->NewlineKeyHandler.OnPress = EwNewSlot( _this, ComponentsTextEditor_onNewlineKey );
  _this->NewlineKeyHandler.OnHold = EwNewSlot( _this, ComponentsTextEditor_onNewlineKey );
  _this->CharacterKeyHandler.OnPress = EwNewSlot( _this, ComponentsTextEditor_onCharacterKey );
  _this->CharacterKeyHandler.OnHold = EwNewSlot( _this, ComponentsTextEditor_onCharacterKey );
  ViewsText_OnSetOnUpdate( &_this->Text, EwNewSlot( _this, ComponentsTextEditor_updateCaret ));
  ViewsText__OnSetFont( &_this->Text, EwLoadResource( &ResourcesFontMedium, ResourcesFont ));
  _this->Font = EwLoadResource( &ResourcesFontMedium, ResourcesFont );
}

/* Re-Initializer for the class 'Components::TextEditor' */
void ComponentsTextEditor__ReInit( ComponentsTextEditor _this )
{
  /* At first re-initialize the super class ... */
  TemplatesTextEditor__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  EffectsBoolEffect__ReInit( &_this->blinkEffect );
  CoreKeyPressHandler__ReInit( &_this->CursorKeyHandler );
  CoreKeyPressHandler__ReInit( &_this->BackspaceKeyHandler );
  CoreKeyPressHandler__ReInit( &_this->DeleteKeyHandler );
  CoreKeyPressHandler__ReInit( &_this->NewlineKeyHandler );
  CoreKeyPressHandler__ReInit( &_this->CharacterKeyHandler );
  ViewsText__ReInit( &_this->Text );
  ViewsLine__ReInit( &_this->Caret );
}

/* Finalizer method for the class 'Components::TextEditor' */
void ComponentsTextEditor__Done( ComponentsTextEditor _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( TemplatesTextEditor );

  /* Finalize all embedded objects */
  EffectsBoolEffect__Done( &_this->blinkEffect );
  CoreKeyPressHandler__Done( &_this->CursorKeyHandler );
  CoreKeyPressHandler__Done( &_this->BackspaceKeyHandler );
  CoreKeyPressHandler__Done( &_this->DeleteKeyHandler );
  CoreKeyPressHandler__Done( &_this->NewlineKeyHandler );
  CoreKeyPressHandler__Done( &_this->CharacterKeyHandler );
  ViewsText__Done( &_this->Text );
  ViewsLine__Done( &_this->Caret );

  /* Don't forget to deinitialize the super class ... */
  TemplatesTextEditor__Done( &_this->_.Super );
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
void ComponentsTextEditor_UpdateViewState( ComponentsTextEditor _this, XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ViewsLine_OnSetVisible( &_this->Caret, 0 );
  EffectsBoolEffect_OnSetEnabled( &_this->blinkEffect, 0 );
}

/* This slot method is attached to the Text view. Each time the Text view has rearranged 
   the text, this method is called. Its job is to adjust the caret to the evtl. 
   new position. */
void ComponentsTextEditor_updateCaret( ComponentsTextEditor _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( sender );

  return;
}

/* This method is called from the corresponding keyboard handler. Its job is to 
   move the caret up/down/left or right in the editor text. */
void ComponentsTextEditor_onCursorKey( ComponentsTextEditor _this, XObject sender )
{
  XPoint rc;
  XInt32 newCaretIndex;
  XChar ch;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Font == 0 )
    return;

  rc = ViewsText_StringIndex2RowCol( &_this->Text, _this->caretIndex );

  if ( _this->CursorKeyHandler.Code == CoreKeyCodeLeft )
  {
    rc.X = ( rc.X - 1 );

    if ( ViewsText_RowCol2StringIndex( &_this->Text, rc ) == _this->caretIndex )
    {
      rc.Y = ( rc.Y - 1 );
      rc.X = EwGetStringLength( ViewsText_GetRowString( &_this->Text, rc.Y ));
    }
  }

  if ( _this->CursorKeyHandler.Code == CoreKeyCodeRight )
  {
    rc.X = ( rc.X + 1 );

    if ( ViewsText_RowCol2StringIndex( &_this->Text, rc ) == _this->caretIndex )
    {
      rc.Y = ( rc.Y + 1 );
      rc.X = 0;
    }
  }

  if ( _this->CursorKeyHandler.Code == CoreKeyCodeUp )
  {
    XPoint pos = ViewsText_RowCol2Position( &_this->Text, rc );
    XInt32 rowHeight = ( _this->Font->Ascent + _this->Font->Descent ) + _this->Font->Leading;
    rc = ViewsText_Position2RowCol( &_this->Text, EwMovePointNeg( pos, EwNewPoint( 
    0, rowHeight )));
  }

  if ( _this->CursorKeyHandler.Code == CoreKeyCodeDown )
  {
    XPoint pos = ViewsText_RowCol2Position( &_this->Text, rc );
    XInt32 rowHeight = ( _this->Font->Ascent + _this->Font->Descent ) + _this->Font->Leading;
    rc = ViewsText_Position2RowCol( &_this->Text, EwMovePointPos( pos, EwNewPoint( 
    0, rowHeight )));
  }

  newCaretIndex = ViewsText_RowCol2StringIndex( &_this->Text, rc );
  ch = EwGetStringChar( _this->Text.String, newCaretIndex );

  if ((( ch == '^' ) || ( ch == '~' )) || ( ch == '%' ))
    newCaretIndex = newCaretIndex - 1;

  if ( newCaretIndex != _this->caretIndex )
  {
    _this->caretIndex = newCaretIndex;
    EwPostSignal( EwNewSlot( _this, ComponentsTextEditor_updateCaret ), ((XObject)_this ));
    _this->autoScroll = 1;
  }
}

/* This method is called from the corresponding keyboard handler. Its job is to 
   delete the sign preceding the current caret position and to move the caret accordingly. */
void ComponentsTextEditor_onBackspaceKey( ComponentsTextEditor _this, XObject sender )
{
  XChar ch;
  XInt32 count;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->caretIndex == 0 )
    return;

  ch = EwGetStringChar( _this->Text.String, _this->caretIndex - 1 );
  count = 1;

  if ((( ch == '^' ) || ( ch == '~' )) || ( ch == '%' ))
    count = 2;

  ViewsText__OnSetString( &_this->Text, EwStringRemove( _this->Text.String, _this->caretIndex 
  - count, count ));
  _this->caretIndex = _this->caretIndex - count;
  _this->autoScroll = 1;
  _this->changed = 1;
}

/* This method is called from the corresponding keyboard handler. Its job is to 
   delete the sign at the current caret position. */
void ComponentsTextEditor_onDeleteKey( ComponentsTextEditor _this, XObject sender )
{
  XChar ch;
  XInt32 count;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->caretIndex >= ( EwGetStringLength( _this->Text.String ) - 1 ))
    return;

  ch = EwGetStringChar( _this->Text.String, _this->caretIndex );
  count = 1;

  if ( ch == '%' )
    count = 2;

  ViewsText__OnSetString( &_this->Text, EwStringRemove( _this->Text.String, _this->caretIndex, 
  count ));
  _this->autoScroll = 1;
  _this->changed = 1;
}

/* This method is called from the corresponding keyboard handler. Its job is to 
   insert at the current caret position the <new line> sign and to move the caret 
   to the next row. */
void ComponentsTextEditor_onNewlineKey( ComponentsTextEditor _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if (( _this->MaxChars > 0 ) && ( EwGetStringLength( ComponentsTextEditor_OnGetString( 
      _this )) >= _this->MaxChars ))
    return;

  ViewsText__OnSetString( &_this->Text, EwStringInsert( _this->Text.String, EwLoadString( 
  &_Const003F ), _this->caretIndex ));
  _this->caretIndex = _this->caretIndex + 1;
  _this->autoScroll = 1;
}

/* This method is called from the corresponding keyboard handler. Its job is to 
   insert at the current caret position the sign which has been input by the user 
   and to move the caret to the next column. */
void ComponentsTextEditor_onCharacterKey( ComponentsTextEditor _this, XObject sender )
{
  XChar ch;
  XString str;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( !_this->changed )
  {
    ViewsText__OnSetString( &_this->Text, EwLoadString( &_Const0040 ));
    _this->caretIndex = 0;
    _this->changed = 1;
  }

  if (( _this->MaxChars > 0 ) && ( EwGetStringLength( ComponentsTextEditor_OnGetString( 
      _this )) > _this->MaxChars ))
    return;

  ch = _this->CharacterKeyHandler.CharCode;
  str = EwNewStringChar( ch, 1 );

  if ( _this->Numeric )
  {
    if ((( ch < '0' ) || ( ch > '9' )) && ( ch != '.' ))
      return;

    if (( ch == '.' ) && (( _this->caretIndex == 0 ) || ComponentsTextEditor_hasDecimalPoint( 
        _this )))
      return;
  }

  if (((( ch == '^' ) || ( ch == '~' )) || ( ch == 0x00AD )) || ( ch == '%' ))
    str = EwConcatStringChar( EwLoadString( &_Const0041 ), ch );

  ViewsText__OnSetString( &_this->Text, EwStringInsert( _this->Text.String, str, 
  _this->caretIndex ));
  _this->caretIndex = _this->caretIndex + EwGetStringLength( str );
  _this->autoScroll = 1;
}

/* 'C' function for method : 'Components::TextEditor.OnGetString()' */
XString ComponentsTextEditor_OnGetString( ComponentsTextEditor _this )
{
  XString str = _this->Text.String;
  XInt32 inx = EwStringFindChar( str, '%', 0 );

  while ( inx >= 0 )
  {
    str = EwStringRemove( str, inx, 1 );
    inx = EwStringFindChar( str, '%', inx + 1 );
  }

  return EwStringLeft( str, EwGetStringLength( str ) - 1 );
}

/* 'C' function for method : 'Components::TextEditor.OnSetString()' */
void ComponentsTextEditor_OnSetString( ComponentsTextEditor _this, XString value )
{
  XString str = value;
  XInt32 inx = EwStringFindChar( str, '%', 0 );

  while ( inx >= 0 )
  {
    str = EwStringInsert( str, EwLoadString( &_Const0041 ), inx );
    inx = EwStringFindChar( str, '%', inx + 2 );
  }

  inx = EwStringFindChar( str, '^', 0 );

  while ( inx >= 0 )
  {
    str = EwStringInsert( str, EwLoadString( &_Const0041 ), inx );
    inx = EwStringFindChar( str, '^', inx + 2 );
  }

  inx = EwStringFindChar( str, '~', 0 );

  while ( inx >= 0 )
  {
    str = EwStringInsert( str, EwLoadString( &_Const0041 ), inx );
    inx = EwStringFindChar( str, '~', inx + 2 );
  }

  inx = EwStringFindChar( str, 0x00AD, 0 );

  while ( inx >= 0 )
  {
    str = EwStringInsert( str, EwLoadString( &_Const0041 ), inx );
    inx = EwStringFindChar( str, 0x00AD, inx + 2 );
  }

  _this->caretIndex = EwGetStringLength( str );
  ViewsText__OnSetString( &_this->Text, EwConcatString( str, EwLoadString( &_Const0040 )));
  _this->autoScroll = 1;
  ViewsText_OnSetScrollOffset( &_this->Text, _Const0004 );
  _this->changed = 0;
}

/* 'C' function for method : 'Components::TextEditor.OnSetColor()' */
void ComponentsTextEditor_OnSetColor( ComponentsTextEditor _this, XColor value )
{
  if ( !EwCompColor( _this->Color, value ))
    return;

  _this->Color = value;
  ViewsText_OnSetColor( &_this->Text, value );
  ViewsLine_OnSetColor( &_this->Caret, value );
}

/* 'C' function for method : 'Components::TextEditor.OnSetFont()' */
void ComponentsTextEditor_OnSetFont( ComponentsTextEditor _this, ResourcesFont value )
{
  if ( _this->Font == value )
    return;

  _this->Font = value;
  ViewsText__OnSetFont( &_this->Text, value );
  _this->autoScroll = 1;
  ViewsText_OnSetScrollOffset( &_this->Text, _Const0004 );
}

/* 'C' function for method : 'Components::TextEditor.hasDecimalPoint()' */
XBool ComponentsTextEditor_hasDecimalPoint( ComponentsTextEditor _this )
{
  return (XBool)( EwStringFindChar( _this->Text.String, '.', 0 ) >= 0 );
}

/* Variants derived from the class : 'Components::TextEditor' */
EW_DEFINE_CLASS_VARIANTS( ComponentsTextEditor )
EW_END_OF_CLASS_VARIANTS( ComponentsTextEditor )

/* Virtual Method Table (VMT) for the class : 'Components::TextEditor' */
EW_DEFINE_CLASS( ComponentsTextEditor, TemplatesTextEditor, blinkEffect, Font, caretIndex, 
                 caretIndex, caretIndex, caretIndex, "Components::TextEditor" )
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
  ComponentsTextEditor_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsTextEditor )

/* Initializer for the class 'Components::EditTileNumValue' */
void ComponentsEditTileNumValue__Init( ComponentsEditTileNumValue _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsEditTile__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsEditTileNumValue );

  /* ... then construct all embedded objects */
  ComponentsTextEditor__Init( &_this->TextEditor, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsEditTileNumValue );

  /* ... and initialize objects, variables, properties, etc. */
  ViewsText_OnSetVisible((ViewsText)&_this->Super3.ValueDisplay, 0 );
  CoreRectView__OnSetBounds( &_this->TextEditor, _Const0027 );
  ComponentsTextEditor_OnSetString( &_this->TextEditor, 0 );
  _this->TextEditor.MaxChars = 9;
  _this->TextEditor.Numeric = 1;
  CoreGroup__Add( _this, ((CoreView)&_this->TextEditor ), 0 );
  CoreGroup__OnSetFocus( _this, ((CoreView)&_this->TextEditor ));
  ViewsText_OnSetOnUpdate((ViewsText)&_this->Super3.ValueDisplay, EwNewSlot( _this, 
  ComponentsEditTileNumValue_onUpdate ));
  ComponentsTextEditor_OnSetFont( &_this->TextEditor, EwLoadResource( &FontsLarge, 
  ResourcesFont ));
}

/* Re-Initializer for the class 'Components::EditTileNumValue' */
void ComponentsEditTileNumValue__ReInit( ComponentsEditTileNumValue _this )
{
  /* At first re-initialize the super class ... */
  ComponentsEditTile__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsTextEditor__ReInit( &_this->TextEditor );
}

/* Finalizer method for the class 'Components::EditTileNumValue' */
void ComponentsEditTileNumValue__Done( ComponentsEditTileNumValue _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsEditTile );

  /* Finalize all embedded objects */
  ComponentsTextEditor__Done( &_this->TextEditor );

  /* Don't forget to deinitialize the super class ... */
  ComponentsEditTile__Done( &_this->_.Super );
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
void ComponentsEditTileNumValue_UpdateViewState( ComponentsEditTileNumValue _this, 
  XSet aState )
{
  ComponentsTile_UpdateViewState((ComponentsTile)_this, aState );
  ComponentsTextEditor_OnSetColor( &_this->TextEditor, ResOnPrimary );
}

/* 'C' function for method : 'Components::EditTileNumValue.Save()' */
void ComponentsEditTileNumValue_Save( ComponentsEditTileNumValue _this )
{
  XInt32 val = ToolsHelperCollection_ParseInt32Value( EwGetAutoObject( &ToolsHelper, 
    ToolsHelperCollection ), ComponentsTextEditor_OnGetString( &_this->TextEditor ), 
    _this->Super3.Resolution );

  if ( val < _this->Super2.MinValue )
    val = _this->Super2.MinValue;
  else
    if ( val > _this->Super2.MaxValue )
      val = _this->Super2.MaxValue;

  ComponentsBaseTile__OnSetValue( _this, val );
  ComponentsEditTile_Save((ComponentsEditTile)_this );
}

/* 'C' function for method : 'Components::EditTileNumValue.onUpdate()' */
void ComponentsEditTileNumValue_onUpdate( ComponentsEditTileNumValue _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ComponentsTextEditor_OnSetString( &_this->TextEditor, _this->Super3.ValueDisplay.Super2.String );
}

/* Variants derived from the class : 'Components::EditTileNumValue' */
EW_DEFINE_CLASS_VARIANTS( ComponentsEditTileNumValue )
EW_END_OF_CLASS_VARIANTS( ComponentsEditTileNumValue )

/* Virtual Method Table (VMT) for the class : 'Components::EditTileNumValue' */
EW_DEFINE_CLASS( ComponentsEditTileNumValue, ComponentsEditTile, TextEditor, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Components::EditTileNumValue" )
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
  ComponentsEditTileNumValue_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsBaseTile_OnSetUnit,
  ComponentsEditTile_OnSetValue,
  ComponentsBaseTile_OnSetResolution,
  ComponentsBaseTile_OnSetOutlet,
  ComponentsEditTileNumValue_Save,
EW_END_OF_CLASS( ComponentsEditTileNumValue )

/* Initializer for the class 'Components::TimePicker' */
void ComponentsTimePicker__Init( ComponentsTimePicker _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  TemplatesPickerControl__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsTimePicker );

  /* ... then construct all embedded objects */
  CoreSlideTouchHandler__Init( &_this->TouchHandlerSecond, &_this->_.XObject, 0 );
  CoreSlideTouchHandler__Init( &_this->TouchHandlerMinute, &_this->_.XObject, 0 );
  CoreSlideTouchHandler__Init( &_this->TouchHandlerHour, &_this->_.XObject, 0 );
  CoreVerticalList__Init( &_this->ListSecond, &_this->_.XObject, 0 );
  CoreVerticalList__Init( &_this->ListMinute, &_this->_.XObject, 0 );
  CoreVerticalList__Init( &_this->ListHour, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->BackgroundCurrent, &_this->_.XObject, 0 );
  CoreVerticalList__Init( &_this->ListCurrentSec, &_this->_.XObject, 0 );
  CoreVerticalList__Init( &_this->ListCurrentMin, &_this->_.XObject, 0 );
  CoreVerticalList__Init( &_this->ListCurrentHour, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->UnitHour, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->UnitMin, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->UnitSec, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->FadeTop, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->FadeBottom, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsTimePicker );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0042 );
  CoreRectView__OnSetBounds( &_this->TouchHandlerSecond, _Const0043 );
  CoreSlideTouchHandler_OnSetSnapNext( &_this->TouchHandlerSecond, _Const0044 );
  CoreSlideTouchHandler_OnSetFriction( &_this->TouchHandlerSecond, 0.2f );
  CoreRectView__OnSetBounds( &_this->TouchHandlerMinute, _Const0045 );
  CoreSlideTouchHandler_OnSetSnapNext( &_this->TouchHandlerMinute, _Const0044 );
  CoreSlideTouchHandler_OnSetFriction( &_this->TouchHandlerMinute, 0.2f );
  CoreRectView__OnSetBounds( &_this->TouchHandlerHour, _Const0046 );
  CoreSlideTouchHandler_OnSetSnapNext( &_this->TouchHandlerHour, _Const0044 );
  CoreSlideTouchHandler_OnSetFriction( &_this->TouchHandlerHour, 0.2f );
  CoreRectView__OnSetBounds( &_this->ListSecond, _Const0047 );
  CoreVerticalList_OnSetPaddingBottom( &_this->ListSecond, 180 );
  CoreVerticalList_OnSetPaddingTop( &_this->ListSecond, 130 );
  CoreVerticalList_OnSetItemHeight( &_this->ListSecond, 50 );
  CoreVerticalList_OnSetNoOfItems( &_this->ListSecond, 60 );
  CoreRectView__OnSetBounds( &_this->ListMinute, _Const0048 );
  CoreVerticalList_OnSetPaddingBottom( &_this->ListMinute, 180 );
  CoreVerticalList_OnSetPaddingTop( &_this->ListMinute, 130 );
  CoreVerticalList_OnSetItemHeight( &_this->ListMinute, 50 );
  CoreVerticalList_OnSetNoOfItems( &_this->ListMinute, 60 );
  CoreRectView__OnSetBounds( &_this->ListHour, _Const0049 );
  CoreVerticalList_OnSetPaddingBottom( &_this->ListHour, 180 );
  CoreVerticalList_OnSetPaddingTop( &_this->ListHour, 130 );
  CoreVerticalList_OnSetItemHeight( &_this->ListHour, 50 );
  CoreVerticalList_OnSetNoOfItems( &_this->ListHour, 24 );
  CoreRectView__OnSetBounds( &_this->BackgroundCurrent, _Const004A );
  ViewsRectangle_OnSetRadius( &_this->BackgroundCurrent, 10 );
  CoreRectView__OnSetBounds( &_this->ListCurrentSec, _Const004B );
  CoreVerticalList_OnSetScrollOffset( &_this->ListCurrentSec, 4 );
  CoreVerticalList_OnSetItemHeight( &_this->ListCurrentSec, 50 );
  CoreVerticalList_OnSetNoOfItems( &_this->ListCurrentSec, 60 );
  CoreRectView__OnSetBounds( &_this->ListCurrentMin, _Const004C );
  CoreVerticalList_OnSetScrollOffset( &_this->ListCurrentMin, 4 );
  CoreVerticalList_OnSetItemHeight( &_this->ListCurrentMin, 50 );
  CoreVerticalList_OnSetNoOfItems( &_this->ListCurrentMin, 60 );
  CoreRectView__OnSetBounds( &_this->ListCurrentHour, _Const004D );
  CoreVerticalList_OnSetScrollOffset( &_this->ListCurrentHour, 4 );
  CoreVerticalList_OnSetItemHeight( &_this->ListCurrentHour, 50 );
  CoreVerticalList_OnSetNoOfItems( &_this->ListCurrentHour, 24 );
  CoreRectView__OnSetBounds( &_this->UnitHour, _Const004E );
  ViewsText_OnSetOverflowWarning( &_this->UnitHour, 1 );
  ViewsText_OnSetAlignment( &_this->UnitHour, ViewsTextAlignmentAlignHorzLeft | 
  ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->UnitHour, EwLoadString( &StringsUnit_hours ));
  CoreRectView__OnSetBounds( &_this->UnitMin, _Const004F );
  ViewsText_OnSetOverflowWarning( &_this->UnitMin, 1 );
  ViewsText_OnSetAlignment( &_this->UnitMin, ViewsTextAlignmentAlignHorzLeft | ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->UnitMin, EwLoadString( &StringsUnit_min ));
  CoreRectView__OnSetBounds( &_this->UnitSec, _Const0050 );
  ViewsText_OnSetOverflowWarning( &_this->UnitSec, 1 );
  ViewsText_OnSetAlignment( &_this->UnitSec, ViewsTextAlignmentAlignHorzLeft | ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->UnitSec, EwLoadString( &StringsUnit_sec ));
  CoreRectView__OnSetBounds( &_this->FadeTop, _Const0051 );
  ViewsRectangle_OnSetColorBL( &_this->FadeTop, ResTRANSPARENT );
  ViewsRectangle_OnSetColorBR( &_this->FadeTop, ResTRANSPARENT );
  CoreRectView__OnSetBounds( &_this->FadeBottom, _Const0052 );
  ViewsRectangle_OnSetColorTR( &_this->FadeBottom, ResTRANSPARENT );
  ViewsRectangle_OnSetColorTL( &_this->FadeBottom, ResTRANSPARENT );
  _this->BgColor = _Const0007;
  CoreGroup__Add( _this, ((CoreView)&_this->TouchHandlerSecond ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->TouchHandlerMinute ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->TouchHandlerHour ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ListSecond ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ListMinute ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ListHour ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->BackgroundCurrent ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ListCurrentSec ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ListCurrentMin ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ListCurrentHour ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->UnitHour ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->UnitMin ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->UnitSec ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->FadeTop ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->FadeBottom ), 0 );
  _this->TouchHandlerSecond.OnSlide = EwNewSlot( _this, ComponentsTimePicker_onSlide );
  _this->TouchHandlerSecond.OnEnd = EwNewSlot( _this, ComponentsTimePicker_onEndSlide );
  _this->TouchHandlerSecond.OnStart = EwNewSlot( _this, ComponentsTimePicker_onStartSlide );
  _this->TouchHandlerMinute.OnSlide = EwNewSlot( _this, ComponentsTimePicker_onSlide );
  _this->TouchHandlerMinute.OnEnd = EwNewSlot( _this, ComponentsTimePicker_onEndSlide );
  _this->TouchHandlerMinute.OnStart = EwNewSlot( _this, ComponentsTimePicker_onStartSlide );
  _this->TouchHandlerHour.OnSlide = EwNewSlot( _this, ComponentsTimePicker_onSlide );
  _this->TouchHandlerHour.OnEnd = EwNewSlot( _this, ComponentsTimePicker_onEndSlide );
  _this->TouchHandlerHour.OnStart = EwNewSlot( _this, ComponentsTimePicker_onStartSlide );
  _this->ListSecond.OnUpdate = EwNewSlot( _this, ComponentsTimePicker_onSecUpdate );
  _this->ListSecond.OnLoadItem = EwNewSlot( _this, ComponentsTimePicker_OnLoadSecondItem );
  CoreVerticalList_OnSetSlideHandler( &_this->ListSecond, &_this->TouchHandlerSecond );
  _this->ListMinute.OnUpdate = EwNewSlot( _this, ComponentsTimePicker_onMinUpdate );
  _this->ListMinute.OnLoadItem = EwNewSlot( _this, ComponentsTimePicker_OnLoadMinuteItem );
  CoreVerticalList_OnSetSlideHandler( &_this->ListMinute, &_this->TouchHandlerMinute );
  _this->ListHour.OnUpdate = EwNewSlot( _this, ComponentsTimePicker_onHourUpdate );
  _this->ListHour.OnLoadItem = EwNewSlot( _this, ComponentsTimePicker_OnLoadHourItem );
  CoreVerticalList_OnSetSlideHandler( &_this->ListHour, &_this->TouchHandlerHour );
  _this->ListCurrentSec.OnLoadItem = EwNewSlot( _this, ComponentsTimePicker_OnLoadCurrentSecItem );
  _this->ListCurrentMin.OnLoadItem = EwNewSlot( _this, ComponentsTimePicker_OnLoadCurrentMinItem );
  _this->ListCurrentHour.OnLoadItem = EwNewSlot( _this, ComponentsTimePicker_OnLoadCurrentHourItem );
  ViewsText__OnSetFont( &_this->UnitHour, EwLoadResource( &FontsHeading2, ResourcesFont ));
  ViewsText__OnSetFont( &_this->UnitMin, EwLoadResource( &FontsHeading2, ResourcesFont ));
  ViewsText__OnSetFont( &_this->UnitSec, EwLoadResource( &FontsHeading2, ResourcesFont ));
}

/* Re-Initializer for the class 'Components::TimePicker' */
void ComponentsTimePicker__ReInit( ComponentsTimePicker _this )
{
  /* At first re-initialize the super class ... */
  TemplatesPickerControl__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreSlideTouchHandler__ReInit( &_this->TouchHandlerSecond );
  CoreSlideTouchHandler__ReInit( &_this->TouchHandlerMinute );
  CoreSlideTouchHandler__ReInit( &_this->TouchHandlerHour );
  CoreVerticalList__ReInit( &_this->ListSecond );
  CoreVerticalList__ReInit( &_this->ListMinute );
  CoreVerticalList__ReInit( &_this->ListHour );
  ViewsRectangle__ReInit( &_this->BackgroundCurrent );
  CoreVerticalList__ReInit( &_this->ListCurrentSec );
  CoreVerticalList__ReInit( &_this->ListCurrentMin );
  CoreVerticalList__ReInit( &_this->ListCurrentHour );
  ViewsText__ReInit( &_this->UnitHour );
  ViewsText__ReInit( &_this->UnitMin );
  ViewsText__ReInit( &_this->UnitSec );
  ViewsRectangle__ReInit( &_this->FadeTop );
  ViewsRectangle__ReInit( &_this->FadeBottom );
}

/* Finalizer method for the class 'Components::TimePicker' */
void ComponentsTimePicker__Done( ComponentsTimePicker _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( TemplatesPickerControl );

  /* Finalize all embedded objects */
  CoreSlideTouchHandler__Done( &_this->TouchHandlerSecond );
  CoreSlideTouchHandler__Done( &_this->TouchHandlerMinute );
  CoreSlideTouchHandler__Done( &_this->TouchHandlerHour );
  CoreVerticalList__Done( &_this->ListSecond );
  CoreVerticalList__Done( &_this->ListMinute );
  CoreVerticalList__Done( &_this->ListHour );
  ViewsRectangle__Done( &_this->BackgroundCurrent );
  CoreVerticalList__Done( &_this->ListCurrentSec );
  CoreVerticalList__Done( &_this->ListCurrentMin );
  CoreVerticalList__Done( &_this->ListCurrentHour );
  ViewsText__Done( &_this->UnitHour );
  ViewsText__Done( &_this->UnitMin );
  ViewsText__Done( &_this->UnitSec );
  ViewsRectangle__Done( &_this->FadeTop );
  ViewsRectangle__Done( &_this->FadeBottom );

  /* Don't forget to deinitialize the super class ... */
  TemplatesPickerControl__Done( &_this->_.Super );
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
void ComponentsTimePicker_UpdateViewState( ComponentsTimePicker _this, XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ViewsRectangle_OnSetColor( &_this->BackgroundCurrent, ResSurface3 );
  ViewsText_OnSetColor( &_this->UnitHour, ResOnPrimary );
  ViewsRectangle_OnSetColorTL( &_this->FadeTop, _this->BgColor );
  ViewsRectangle_OnSetColorTR( &_this->FadeTop, _this->BgColor );
  ViewsRectangle_OnSetColorBL( &_this->FadeBottom, _this->BgColor );
  ViewsRectangle_OnSetColorBR( &_this->FadeBottom, _this->BgColor );
}

/* This method is called when one of the Slide Touch Handler (TouchHandlerHour, 
   TouchHandlerMinute or TouchHandlerSecond) has finished the slide animation. Thereupon 
   the owner of the time picker is notified, that the time has been changed. */
void ComponentsTimePicker_onEndSlide( ComponentsTimePicker _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_InvalidateViewState((CoreGroup)_this );

  if ( _this->Outlet.Object != 0 )
    EwOnSetInt32( _this->Outlet, ComponentsTimePicker_OnGetTime( _this ));
}

/* This method is called when one of the Slide Touch Handler (TouchHandlerHour, 
   TouchHandlerMinute or TouchHandlerSecond) has begun the slide animation. */
void ComponentsTimePicker_onStartSlide( ComponentsTimePicker _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* This method is called by 'ListSecond' vertical list every time the list loads 
   or updates an item. */
void ComponentsTimePicker_OnLoadSecondItem( ComponentsTimePicker _this, XObject 
  sender )
{
  XInt32 itemNo;
  ViewsText itemView;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  itemNo = _this->ListSecond.Item;
  itemView = EwCastObject( _this->ListSecond.View, ViewsText );

  if ( itemView == 0 )
    return;

  ViewsText__OnSetString( itemView, EwNewStringInt( itemNo, 2, 10 ));
  ViewsText__OnSetFont( itemView, EwLoadResource( &FontsHeading1, ResourcesFont ));
  ViewsText_OnSetColor( itemView, ResSurface3 );
  ViewsText_OnSetAlignment( itemView, ViewsTextAlignmentAlignHorzRight | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( itemView, EwSetRectSize( itemView->Super1.Bounds, _this->ListSecond.ViewSize ));
}

/* This method is called by 'ListMinute' vertical list every time the list loads 
   or updates an item. */
void ComponentsTimePicker_OnLoadMinuteItem( ComponentsTimePicker _this, XObject 
  sender )
{
  XInt32 itemNo;
  ViewsText itemView;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  itemNo = _this->ListMinute.Item;
  itemView = EwCastObject( _this->ListMinute.View, ViewsText );

  if ( itemView == 0 )
    return;

  ViewsText__OnSetString( itemView, EwNewStringInt( itemNo, 2, 10 ));
  ViewsText__OnSetFont( itemView, EwLoadResource( &FontsHeading1, ResourcesFont ));
  ViewsText_OnSetColor( itemView, ResSurface3 );
  ViewsText_OnSetAlignment( itemView, ViewsTextAlignmentAlignHorzRight | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( itemView, EwSetRectSize( itemView->Super1.Bounds, _this->ListMinute.ViewSize ));
}

/* This method is called by 'ListHour' vertical list every time the list loads or 
   updates an item. */
void ComponentsTimePicker_OnLoadHourItem( ComponentsTimePicker _this, XObject sender )
{
  XInt32 itemNo;
  ViewsText itemView;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  itemNo = _this->ListHour.Item;
  itemView = EwCastObject( _this->ListHour.View, ViewsText );

  if ( itemView == 0 )
    return;

  ViewsText__OnSetString( itemView, EwNewStringInt( itemNo, 2, 10 ));
  ViewsText__OnSetFont( itemView, EwLoadResource( &FontsHeading1, ResourcesFont ));
  ViewsText_OnSetColor( itemView, ResSurface3 );
  ViewsText_OnSetAlignment( itemView, ViewsTextAlignmentAlignHorzRight | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( itemView, EwSetRectSize( itemView->Super1.Bounds, _this->ListHour.ViewSize ));
}

/* 'C' function for method : 'Components::TimePicker.OnGetSecond()' */
XInt32 ComponentsTimePicker_OnGetSecond( ComponentsTimePicker _this )
{
  return ( -_this->ListSecond.ScrollOffset / _this->ListSecond.ItemHeight ) % 60;
}

/* 'C' function for method : 'Components::TimePicker.OnSetSecond()' */
void ComponentsTimePicker_OnSetSecond( ComponentsTimePicker _this, XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( value > 59 )
    value = 59;

  CoreVerticalList_OnSetScrollOffset( &_this->ListSecond, value * -_this->ListSecond.ItemHeight );
}

/* 'C' function for method : 'Components::TimePicker.OnGetMinute()' */
XInt32 ComponentsTimePicker_OnGetMinute( ComponentsTimePicker _this )
{
  return ( -_this->ListMinute.ScrollOffset / _this->ListMinute.ItemHeight ) % 60;
}

/* 'C' function for method : 'Components::TimePicker.OnSetMinute()' */
void ComponentsTimePicker_OnSetMinute( ComponentsTimePicker _this, XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( value > 59 )
    value = 59;

  CoreVerticalList_OnSetScrollOffset( &_this->ListMinute, value * -_this->ListMinute.ItemHeight );
}

/* 'C' function for method : 'Components::TimePicker.OnGetHour()' */
XInt32 ComponentsTimePicker_OnGetHour( ComponentsTimePicker _this )
{
  return ( -_this->ListHour.ScrollOffset / _this->ListHour.ItemHeight ) % 24;
}

/* 'C' function for method : 'Components::TimePicker.OnSetHour()' */
void ComponentsTimePicker_OnSetHour( ComponentsTimePicker _this, XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( value > 23 )
    value = 23;

  CoreVerticalList_OnSetScrollOffset( &_this->ListHour, value * -_this->ListHour.ItemHeight );
}

/* This method is called by 'ListHour' vertical list every time the list loads or 
   updates an item. */
void ComponentsTimePicker_OnLoadCurrentHourItem( ComponentsTimePicker _this, XObject 
  sender )
{
  XInt32 itemNo;
  ViewsText itemView;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  itemNo = _this->ListCurrentHour.Item;
  itemView = EwCastObject( _this->ListCurrentHour.View, ViewsText );

  if ( itemView == 0 )
    return;

  ViewsText__OnSetString( itemView, EwNewStringInt( itemNo, 2, 10 ));
  ViewsText__OnSetFont( itemView, EwLoadResource( &FontsHeading1, ResourcesFont ));
  ViewsText_OnSetColor( itemView, ResOnPrimary );
  ViewsText_OnSetAlignment( itemView, ViewsTextAlignmentAlignHorzRight | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( itemView, EwSetRectSize( itemView->Super1.Bounds, _this->ListCurrentHour.ViewSize ));
}

/* 'C' function for method : 'Components::TimePicker.onHourUpdate()' */
void ComponentsTimePicker_onHourUpdate( ComponentsTimePicker _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreVerticalList_OnSetScrollOffset( &_this->ListCurrentHour, _this->ListHour.ScrollOffset 
  + 4 );
}

/* This method is called by 'ListHour' vertical list every time the list loads or 
   updates an item. */
void ComponentsTimePicker_OnLoadCurrentMinItem( ComponentsTimePicker _this, XObject 
  sender )
{
  XInt32 itemNo;
  ViewsText itemView;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  itemNo = _this->ListCurrentMin.Item;
  itemView = EwCastObject( _this->ListCurrentMin.View, ViewsText );

  if ( itemView == 0 )
    return;

  ViewsText__OnSetString( itemView, EwNewStringInt( itemNo, 2, 10 ));
  ViewsText__OnSetFont( itemView, EwLoadResource( &FontsHeading1, ResourcesFont ));
  ViewsText_OnSetColor( itemView, ResOnPrimary );
  ViewsText_OnSetAlignment( itemView, ViewsTextAlignmentAlignHorzRight | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( itemView, EwSetRectSize( itemView->Super1.Bounds, _this->ListCurrentMin.ViewSize ));
}

/* This method is called by 'ListSecond' vertical list every time the list loads 
   or updates an item. */
void ComponentsTimePicker_OnLoadCurrentSecItem( ComponentsTimePicker _this, XObject 
  sender )
{
  XInt32 itemNo;
  ViewsText itemView;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  itemNo = _this->ListCurrentSec.Item;
  itemView = EwCastObject( _this->ListCurrentSec.View, ViewsText );

  if ( itemView == 0 )
    return;

  ViewsText__OnSetString( itemView, EwNewStringInt( itemNo, 2, 10 ));
  ViewsText__OnSetFont( itemView, EwLoadResource( &FontsHeading1, ResourcesFont ));
  ViewsText_OnSetColor( itemView, ResOnPrimary );
  ViewsText_OnSetAlignment( itemView, ViewsTextAlignmentAlignHorzRight | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( itemView, EwSetRectSize( itemView->Super1.Bounds, _this->ListCurrentSec.ViewSize ));
}

/* 'C' function for method : 'Components::TimePicker.onMinUpdate()' */
void ComponentsTimePicker_onMinUpdate( ComponentsTimePicker _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreVerticalList_OnSetScrollOffset( &_this->ListCurrentMin, _this->ListMinute.ScrollOffset 
  + 4 );
}

/* 'C' function for method : 'Components::TimePicker.onSecUpdate()' */
void ComponentsTimePicker_onSecUpdate( ComponentsTimePicker _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreVerticalList_OnSetScrollOffset( &_this->ListCurrentSec, _this->ListSecond.ScrollOffset 
  + 4 );
}

/* 'C' function for method : 'Components::TimePicker.OnSetBgColor()' */
void ComponentsTimePicker_OnSetBgColor( ComponentsTimePicker _this, XColor value )
{
  if ( !EwCompColor( _this->BgColor, value ))
    return;

  _this->BgColor = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'Components::TimePicker.OnSetTime()' */
void ComponentsTimePicker_OnSetTime( ComponentsTimePicker _this, XInt32 value )
{
  XInt32 hour;
  XInt32 min;
  XInt32 sec;

  if ( _this->Time == value )
    return;

  _this->Time = value;
  hour = value / 3600;
  min = ( value - ( hour * 3600 )) / 60;
  sec = ( value - ( hour * 3600 )) - ( min * 60 );
  ComponentsTimePicker_OnSetHour( _this, hour );
  ComponentsTimePicker_OnSetMinute( _this, min );
  ComponentsTimePicker_OnSetSecond( _this, sec );
}

/* 'C' function for method : 'Components::TimePicker.OnGetTime()' */
XInt32 ComponentsTimePicker_OnGetTime( ComponentsTimePicker _this )
{
  return (( ComponentsTimePicker_OnGetHour( _this ) * 3600 ) + ( ComponentsTimePicker_OnGetMinute( 
    _this ) * 60 )) + ComponentsTimePicker_OnGetSecond( _this );
}

/* 'C' function for method : 'Components::TimePicker.OnSetOutlet()' */
void ComponentsTimePicker_OnSetOutlet( ComponentsTimePicker _this, XRef value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  _this->Outlet = value;

  if ( value.Object != 0 )
    ComponentsTimePicker_OnSetTime( _this, EwOnGetInt32( value ));
}

/* 'C' function for method : 'Components::TimePicker.onSlide()' */
void ComponentsTimePicker_onSlide( ComponentsTimePicker _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Outlet.Object != 0 )
    EwOnSetInt32( _this->Outlet, ComponentsTimePicker_OnGetTime( _this ));
}

/* Variants derived from the class : 'Components::TimePicker' */
EW_DEFINE_CLASS_VARIANTS( ComponentsTimePicker )
EW_END_OF_CLASS_VARIANTS( ComponentsTimePicker )

/* Virtual Method Table (VMT) for the class : 'Components::TimePicker' */
EW_DEFINE_CLASS( ComponentsTimePicker, TemplatesPickerControl, TouchHandlerSecond, 
                 Outlet, Outlet, Outlet, BgColor, BgColor, "Components::TimePicker" )
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
  ComponentsTimePicker_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsTimePicker )

/* Initializer for the class 'Components::TextButton' */
void ComponentsTextButton__Init( ComponentsTextButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsBaseButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsTextButton );

  /* ... then construct all embedded objects */
  ViewsText__Init( &_this->CaptionText, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsTextButton );

  /* ... and initialize objects, variables, properties, etc. */
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)_this, ResOnPrimary );
  ComponentsBaseButton_OnSetBgColorPressed((ComponentsBaseButton)_this, ResOnPrimary );
  CoreView_OnSetLayout((CoreView)&_this->CaptionText, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToLeft | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz 
  | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->CaptionText, _Const0000 );
  ViewsText_OnSetOverflowWarning( &_this->CaptionText, 1 );
  ViewsText__OnSetString( &_this->CaptionText, EwLoadString( &_Const0006 ));
  _this->CaptionColor = ResPrimaryContainer;
  _this->CaptionColorDisabled = ResPrimaryContainer;
  CoreGroup__Add( _this, ((CoreView)&_this->CaptionText ), 0 );
  ViewsText__OnSetFont( &_this->CaptionText, EwLoadResource( &FontsHeading3, ResourcesFont ));
  _this->Font = EwLoadResource( &FontsHeading3, ResourcesFont );

  /* Call the user defined constructor */
  ComponentsTextButton_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::TextButton' */
void ComponentsTextButton__ReInit( ComponentsTextButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsBaseButton__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsText__ReInit( &_this->CaptionText );
}

/* Finalizer method for the class 'Components::TextButton' */
void ComponentsTextButton__Done( ComponentsTextButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsBaseButton );

  /* Finalize all embedded objects */
  ViewsText__Done( &_this->CaptionText );

  /* Don't forget to deinitialize the super class ... */
  ComponentsBaseButton__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsTextButton_Init( ComponentsTextButton _this, XHandle aArg )
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
void ComponentsTextButton_UpdateViewState( ComponentsTextButton _this, XSet aState )
{
  XBool isEnabled;

  ComponentsBaseButton_UpdateViewState((ComponentsBaseButton)_this, aState );
  isEnabled = (( aState & CoreViewStateEnabled ) == CoreViewStateEnabled );

  if ( isEnabled )
    ViewsText_OnSetColor( &_this->CaptionText, _this->CaptionColor );
  else
    ViewsText_OnSetColor( &_this->CaptionText, _this->CaptionColorDisabled );
}

/* 'C' function for method : 'Components::TextButton.OnSetCaption()' */
void ComponentsTextButton_OnSetCaption( ComponentsTextButton _this, XString value )
{
  if ( !EwCompString( _this->Caption, value ))
    return;

  _this->Caption = EwShareString( value );
  ViewsText__OnSetString( &_this->CaptionText, value );
}

/* Wrapper function for the virtual method : 'Components::TextButton.OnSetCaption()' */
void ComponentsTextButton__OnSetCaption( void* _this, XString value )
{
  ((ComponentsTextButton)_this)->_.VMT->OnSetCaption((ComponentsTextButton)_this
  , value );
}

/* 'C' function for method : 'Components::TextButton.OnSetCaptionColor()' */
void ComponentsTextButton_OnSetCaptionColor( ComponentsTextButton _this, XColor 
  value )
{
  if ( !EwCompColor( _this->CaptionColor, value ))
    return;

  _this->CaptionColor = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'Components::TextButton.OnSetFont()' */
void ComponentsTextButton_OnSetFont( ComponentsTextButton _this, ResourcesFont value )
{
  if ( _this->Font == value )
    return;

  _this->Font = value;
  ViewsText__OnSetFont( &_this->CaptionText, value );
}

/* Variants derived from the class : 'Components::TextButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsTextButton )
EW_END_OF_CLASS_VARIANTS( ComponentsTextButton )

/* Virtual Method Table (VMT) for the class : 'Components::TextButton' */
EW_DEFINE_CLASS( ComponentsTextButton, ComponentsBaseButton, CaptionText, Font, 
                 Caption, Caption, Caption, CaptionColor, "Components::TextButton" )
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
  ComponentsTextButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsTextButton_OnSetCaption,
EW_END_OF_CLASS( ComponentsTextButton )

/* Initializer for the class 'Components::Battery' */
void ComponentsBattery__Init( ComponentsBattery _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsBattery );

  /* ... then construct all embedded objects */
  ViewsImage__Init( &_this->BatteryIcon, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->LevelRectangle, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->ChargingIcon, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsBattery );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0008 );
  CoreRectView__OnSetBounds( &_this->BatteryIcon, _Const0008 );
  CoreRectView__OnSetBounds( &_this->LevelRectangle, _Const0053 );
  ViewsRectangle_OnSetRadius( &_this->LevelRectangle, 2 );
  CoreRectView__OnSetBounds( &_this->ChargingIcon, _Const0008 );
  _this->Color = _Const0007;
  CoreGroup__Add( _this, ((CoreView)&_this->BatteryIcon ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->LevelRectangle ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ChargingIcon ), 0 );
  ViewsImage_OnSetBitmap( &_this->BatteryIcon, EwLoadResource( &Resbattery, ResourcesBitmap ));
}

/* Re-Initializer for the class 'Components::Battery' */
void ComponentsBattery__ReInit( ComponentsBattery _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsImage__ReInit( &_this->BatteryIcon );
  ViewsRectangle__ReInit( &_this->LevelRectangle );
  ViewsImage__ReInit( &_this->ChargingIcon );
}

/* Finalizer method for the class 'Components::Battery' */
void ComponentsBattery__Done( ComponentsBattery _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Finalize all embedded objects */
  ViewsImage__Done( &_this->BatteryIcon );
  ViewsRectangle__Done( &_this->LevelRectangle );
  ViewsImage__Done( &_this->ChargingIcon );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
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
void ComponentsBattery_UpdateViewState( ComponentsBattery _this, XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  CoreRectView__OnSetBounds( &_this->LevelRectangle, EwSetRectW( _this->LevelRectangle.Super1.Bounds, 
  ( _this->Level * 18 ) / 100 ));
  ViewsImage_OnSetColor( &_this->BatteryIcon, _this->Color );
  CoreGroup_OnSetVisible((CoreGroup)_this, 1 );

  switch ( _this->Status )
  {
    case 0 :
      CoreGroup_OnSetVisible((CoreGroup)_this, 0 );
    break;

    case 1 :
    case 2 :
    {
      ViewsImage_OnSetBitmap( &_this->ChargingIcon, EwLoadResource( &Resbattery_charging, 
      ResourcesBitmap ));
      ViewsImage_OnSetColor( &_this->ChargingIcon, ResOnPrimary );
      ViewsRectangle_OnSetColor( &_this->LevelRectangle, ResSuccess );
    }
    break;

    default : 
    {
      ViewsImage_OnSetBitmap( &_this->ChargingIcon, 0 );
      ViewsRectangle_OnSetColor( &_this->LevelRectangle, _this->Color );
    }
  }
}

/* 'C' function for method : 'Components::Battery.OnSetColor()' */
void ComponentsBattery_OnSetColor( ComponentsBattery _this, XColor value )
{
  if ( !EwCompColor( _this->Color, value ))
    return;

  _this->Color = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'Components::Battery.OnSetLevel()' */
void ComponentsBattery_OnSetLevel( ComponentsBattery _this, XInt32 value )
{
  if ( _this->Level == value )
    return;

  _this->Level = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'Components::Battery.OnSetStatus()' */
void ComponentsBattery_OnSetStatus( ComponentsBattery _this, XInt32 value )
{
  if ( _this->Status == value )
    return;

  _this->Status = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* This slot method will receive a signal, if the value of the property assigned 
   to @Outlet has been changed by another widget or by the application logic. In 
   response to this notification, the widget will update itself. */
void ComponentsBattery_onOutletLevel( ComponentsBattery _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->OutletLevel.Object != 0 )
    ComponentsBattery_OnSetLevel( _this, EwOnGetInt32( _this->OutletLevel ));
}

/* 'C' function for method : 'Components::Battery.OnSetOutletLevel()' */
void ComponentsBattery_OnSetOutletLevel( ComponentsBattery _this, XRef value )
{
  if ( !EwCompRef( _this->OutletLevel, value ))
    return;

  if ( _this->OutletLevel.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsBattery_onOutletLevel ), _this->OutletLevel, 
      0 );

  _this->OutletLevel = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsBattery_onOutletLevel ), value, 
      0 );

  if ( value.Object != 0 )
    EwPostSignal( EwNewSlot( _this, ComponentsBattery_onOutletLevel ), ((XObject)_this ));
}

/* This slot method will receive a signal, if the value of the property assigned 
   to @Outlet has been changed by another widget or by the application logic. In 
   response to this notification, the widget will update itself. */
void ComponentsBattery_onOutletStatus( ComponentsBattery _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->OutletStatus.Object != 0 )
    ComponentsBattery_OnSetStatus( _this, EwOnGetInt32( _this->OutletStatus ));
}

/* 'C' function for method : 'Components::Battery.OnSetOutletStatus()' */
void ComponentsBattery_OnSetOutletStatus( ComponentsBattery _this, XRef value )
{
  if ( !EwCompRef( _this->OutletStatus, value ))
    return;

  if ( _this->OutletStatus.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsBattery_onOutletStatus ), _this->OutletStatus, 
      0 );

  _this->OutletStatus = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsBattery_onOutletStatus ), value, 
      0 );

  if ( value.Object != 0 )
    EwPostSignal( EwNewSlot( _this, ComponentsBattery_onOutletStatus ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::Battery.OnSetScrollOffset()' */
void ComponentsBattery_OnSetScrollOffset( ComponentsBattery _this, XPoint value )
{
  /* List of temporarily used variables */
  XRect _tmpK0;
  if ( !EwCompPoint( _this->ScrollOffset, value ))
    return;

  _this->ScrollOffset = value;
  ViewsImage_OnSetScrollOffset( &_this->BatteryIcon, value );
  ViewsImage_OnSetScrollOffset( &_this->ChargingIcon, value );
  ((void)( _tmpK0 = _this->LevelRectangle.Super1.Bounds ), CoreRectView__OnSetBounds( 
  &_this->LevelRectangle, EwSetRectOrigin( _tmpK0, EwMovePointPos( _tmpK0.Point1, 
  value ))));
}

/* Variants derived from the class : 'Components::Battery' */
EW_DEFINE_CLASS_VARIANTS( ComponentsBattery )
EW_END_OF_CLASS_VARIANTS( ComponentsBattery )

/* Virtual Method Table (VMT) for the class : 'Components::Battery' */
EW_DEFINE_CLASS( ComponentsBattery, CoreGroup, BatteryIcon, OutletLevel, OutletLevel, 
                 OutletLevel, Color, Color, "Components::Battery" )
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
  ComponentsBattery_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsBattery )

/* Initializer for the class 'Components::IntValueDisplay' */
void ComponentsIntValueDisplay__Init( ComponentsIntValueDisplay _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsValueDisplay__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsIntValueDisplay );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsIntValueDisplay );

  /* ... and initialize objects, variables, properties, etc. */
  _this->Precision = -1;

  /* Call the user defined constructor */
  ComponentsIntValueDisplay_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::IntValueDisplay' */
void ComponentsIntValueDisplay__ReInit( ComponentsIntValueDisplay _this )
{
  /* At first re-initialize the super class ... */
  ComponentsValueDisplay__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::IntValueDisplay' */
void ComponentsIntValueDisplay__Done( ComponentsIntValueDisplay _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsValueDisplay );

  /* Don't forget to deinitialize the super class ... */
  ComponentsValueDisplay__Done( &_this->_.Super );
}

/* 'C' function for method : 'Components::IntValueDisplay.Init()' */
void ComponentsIntValueDisplay_Init( ComponentsIntValueDisplay _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* 'C' function for method : 'Components::IntValueDisplay.OnSetValue()' */
void ComponentsIntValueDisplay_OnSetValue( ComponentsIntValueDisplay _this, XInt32 
  value )
{
  if ( _this->Value == value )
    return;

  _this->Value = value;
  EwPostSignal( EwNewSlot( _this, ComponentsIntValueDisplay__formatValue ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::IntValueDisplay.formatValue()' */
void ComponentsIntValueDisplay_formatValue( ComponentsIntValueDisplay _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->IsTime )
    ViewsText__OnSetString( _this, ToolsHelperCollection_FormatTime( EwGetAutoObject( 
    &ToolsHelper, ToolsHelperCollection ), _this->Value ));
  else
    ViewsText__OnSetString( _this, ToolsHelperCollection_FormatInt32Value( EwGetAutoObject( 
    &ToolsHelper, ToolsHelperCollection ), _this->Value, _this->Resolution, _this->Precision ));
}

/* Wrapper function for the virtual method : 'Components::IntValueDisplay.formatValue()' */
void ComponentsIntValueDisplay__formatValue( void* _this, XObject sender )
{
  ((ComponentsIntValueDisplay)_this)->_.VMT->formatValue((ComponentsIntValueDisplay)_this
  , sender );
}

/* 'C' function for method : 'Components::IntValueDisplay.OnSetOutlet()' */
void ComponentsIntValueDisplay_OnSetOutlet( ComponentsIntValueDisplay _this, XRef 
  value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  if ( _this->Outlet.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsIntValueDisplay_onOutlet ), 
      _this->Outlet, 0 );

  _this->Outlet = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsIntValueDisplay_onOutlet ), 
      value, 0 );

  if ( value.Object != 0 )
    EwPostSignal( EwNewSlot( _this, ComponentsIntValueDisplay_onOutlet ), ((XObject)_this ));
}

/* This slot method will receive a signal, if the value of the property assigned 
   to @Outlet has been changed by another widget or by the application logic. In 
   response to this notification, the widget will update itself. */
void ComponentsIntValueDisplay_onOutlet( ComponentsIntValueDisplay _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Outlet.Object != 0 )
    ComponentsIntValueDisplay_OnSetValue( _this, EwOnGetInt32( _this->Outlet ));
}

/* 'C' function for method : 'Components::IntValueDisplay.OnSetResolution()' */
void ComponentsIntValueDisplay_OnSetResolution( ComponentsIntValueDisplay _this, 
  XInt32 value )
{
  if ( _this->Resolution == value )
    return;

  _this->Resolution = value;
  EwPostSignal( EwNewSlot( _this, ComponentsIntValueDisplay__formatValue ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::IntValueDisplay.OnSetIsTime()' */
void ComponentsIntValueDisplay_OnSetIsTime( ComponentsIntValueDisplay _this, XBool 
  value )
{
  if ( _this->IsTime == value )
    return;

  _this->IsTime = value;
  EwPostSignal( EwNewSlot( _this, ComponentsIntValueDisplay__formatValue ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::IntValueDisplay.OnSetPrecision()' */
void ComponentsIntValueDisplay_OnSetPrecision( ComponentsIntValueDisplay _this, 
  XInt32 value )
{
  if ( _this->Precision == value )
    return;

  _this->Precision = value;
  EwPostSignal( EwNewSlot( _this, ComponentsIntValueDisplay__formatValue ), ((XObject)_this ));
}

/* Variants derived from the class : 'Components::IntValueDisplay' */
EW_DEFINE_CLASS_VARIANTS( ComponentsIntValueDisplay )
EW_END_OF_CLASS_VARIANTS( ComponentsIntValueDisplay )

/* Virtual Method Table (VMT) for the class : 'Components::IntValueDisplay' */
EW_DEFINE_CLASS( ComponentsIntValueDisplay, ComponentsValueDisplay, Outlet, Outlet, 
                 Outlet, Outlet, Value, Value, "Components::IntValueDisplay" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  ViewsText_Draw,
  CoreView_GetClipping,
  CoreView_HandleEvent,
  CoreView_CursorHitTest,
  CoreView_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreView_ChangeViewState,
  ComponentsValueDisplay_OnSetBounds,
  ComponentsValueDisplay_OnSetString,
  ComponentsValueDisplay_OnSetFont,
  ComponentsIntValueDisplay_formatValue,
EW_END_OF_CLASS( ComponentsIntValueDisplay )

/* Initializer for the class 'Components::EnumValueDisplay' */
void ComponentsEnumValueDisplay__Init( ComponentsEnumValueDisplay _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsIntValueDisplay__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsEnumValueDisplay );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsEnumValueDisplay );
}

/* Re-Initializer for the class 'Components::EnumValueDisplay' */
void ComponentsEnumValueDisplay__ReInit( ComponentsEnumValueDisplay _this )
{
  /* At first re-initialize the super class ... */
  ComponentsIntValueDisplay__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::EnumValueDisplay' */
void ComponentsEnumValueDisplay__Done( ComponentsEnumValueDisplay _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsIntValueDisplay );

  /* Don't forget to deinitialize the super class ... */
  ComponentsIntValueDisplay__Done( &_this->_.Super );
}

/* 'C' function for method : 'Components::EnumValueDisplay.formatValue()' */
void ComponentsEnumValueDisplay_formatValue( ComponentsEnumValueDisplay _this, XObject 
  sender )
{
  if ( _this->Enum == 0 )
  {
    ComponentsIntValueDisplay_formatValue((ComponentsIntValueDisplay)_this, sender );
    return;
  }

  ViewsText__OnSetString( _this, DeviceEnumClass__GetString( _this->Enum, _this->Super1.Value ));
}

/* 'C' function for method : 'Components::EnumValueDisplay.OnSetEnum()' */
void ComponentsEnumValueDisplay_OnSetEnum( ComponentsEnumValueDisplay _this, DeviceEnumClass 
  value )
{
  if ( _this->Enum == value )
    return;

  _this->Enum = value;
  EwPostSignal( EwNewSlot( _this, ComponentsIntValueDisplay__formatValue ), ((XObject)_this ));
}

/* Variants derived from the class : 'Components::EnumValueDisplay' */
EW_DEFINE_CLASS_VARIANTS( ComponentsEnumValueDisplay )
EW_END_OF_CLASS_VARIANTS( ComponentsEnumValueDisplay )

/* Virtual Method Table (VMT) for the class : 'Components::EnumValueDisplay' */
EW_DEFINE_CLASS( ComponentsEnumValueDisplay, ComponentsIntValueDisplay, Enum, Enum, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Components::EnumValueDisplay" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  ViewsText_Draw,
  CoreView_GetClipping,
  CoreView_HandleEvent,
  CoreView_CursorHitTest,
  CoreView_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreView_ChangeViewState,
  ComponentsValueDisplay_OnSetBounds,
  ComponentsValueDisplay_OnSetString,
  ComponentsValueDisplay_OnSetFont,
  ComponentsEnumValueDisplay_formatValue,
EW_END_OF_CLASS( ComponentsEnumValueDisplay )

/* Initializer for the class 'Components::IconTextButton' */
void ComponentsIconTextButton__Init( ComponentsIconTextButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsTextButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsIconTextButton );

  /* ... then construct all embedded objects */
  ViewsImage__Init( &_this->Image, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsIconTextButton );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0054 );
  CoreView_OnSetLayout((CoreView)&_this->Image, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToTop | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->Image, _Const0055 );
  ViewsImage_OnSetColor( &_this->Image, ResPrimaryContainer );
  _this->IconColor = ResPrimaryContainer;
  CoreGroup__Add( _this, ((CoreView)&_this->Image ), 0 );

  /* Call the user defined constructor */
  ComponentsIconTextButton_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::IconTextButton' */
void ComponentsIconTextButton__ReInit( ComponentsIconTextButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsTextButton__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsImage__ReInit( &_this->Image );
}

/* Finalizer method for the class 'Components::IconTextButton' */
void ComponentsIconTextButton__Done( ComponentsIconTextButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsTextButton );

  /* Finalize all embedded objects */
  ViewsImage__Done( &_this->Image );

  /* Don't forget to deinitialize the super class ... */
  ComponentsTextButton__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsIconTextButton_Init( ComponentsIconTextButton _this, XHandle aArg )
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
void ComponentsIconTextButton_UpdateViewState( ComponentsIconTextButton _this, XSet 
  aState )
{
  ComponentsTextButton_UpdateViewState((ComponentsTextButton)_this, aState );
  ViewsImage_OnSetColor( &_this->Image, _this->IconColor );
}

/* 'C' function for method : 'Components::IconTextButton.OnSetCaption()' */
void ComponentsIconTextButton_OnSetCaption( ComponentsIconTextButton _this, XString 
  value )
{
  ComponentsTextButton_OnSetCaption((ComponentsTextButton)_this, value );
  CoreGroup_InvalidateLayout((CoreGroup)_this );
}

/* 'C' function for method : 'Components::IconTextButton.OnSetIcon()' */
void ComponentsIconTextButton_OnSetIcon( ComponentsIconTextButton _this, ResourcesBitmap 
  value )
{
  if ( _this->Icon == value )
    return;

  _this->Icon = value;
  ViewsImage_OnSetBitmap( &_this->Image, value );
  CoreGroup_InvalidateLayout((CoreGroup)_this );
}

/* 'C' function for method : 'Components::IconTextButton.OnSetIconColor()' */
void ComponentsIconTextButton_OnSetIconColor( ComponentsIconTextButton _this, XColor 
  value )
{
  if ( !EwCompColor( _this->IconColor, value ))
    return;

  _this->IconColor = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* Variants derived from the class : 'Components::IconTextButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsIconTextButton )
EW_END_OF_CLASS_VARIANTS( ComponentsIconTextButton )

/* Virtual Method Table (VMT) for the class : 'Components::IconTextButton' */
EW_DEFINE_CLASS( ComponentsIconTextButton, ComponentsTextButton, Image, Icon, IconColor, 
                 IconColor, IconColor, IconColor, "Components::IconTextButton" )
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
  ComponentsIconTextButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsIconTextButton_OnSetCaption,
EW_END_OF_CLASS( ComponentsIconTextButton )

/* Initializer for the class 'Components::SettingsButton' */
void ComponentsSettingsButton__Init( ComponentsSettingsButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsIconTextButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsSettingsButton );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsSettingsButton );

  /* ... and initialize objects, variables, properties, etc. */
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)_this, ResSurface2 );
  ComponentsBaseButton_OnSetBgColorPressed((ComponentsBaseButton)_this, ResSurface2 );
  ComponentsTextButton_OnSetCaptionColor((ComponentsTextButton)_this, ResOnPrimary );
  CoreView_OnSetLayout((CoreView)&_this->Super1.Image, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToLeft | CoreLayoutAlignToTop | CoreLayoutResizeVert );
  ComponentsIconTextButton_OnSetIconColor((ComponentsIconTextButton)_this, ResOnPrimary );
  _this->SettingsPage = DeviceSettingsPageNone;

  /* Call the user defined constructor */
  ComponentsSettingsButton_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::SettingsButton' */
void ComponentsSettingsButton__ReInit( ComponentsSettingsButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsIconTextButton__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::SettingsButton' */
void ComponentsSettingsButton__Done( ComponentsSettingsButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsIconTextButton );

  /* Don't forget to deinitialize the super class ... */
  ComponentsIconTextButton__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsSettingsButton_Init( ComponentsSettingsButton _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsSettingsButton_UpdateLayout( ComponentsSettingsButton _this, XPoint 
  aSize )
{
  XInt32 captionWidth;
  XInt32 x;

  CoreGroup_UpdateLayout((CoreGroup)_this, aSize );

  if ( _this->Super1.Icon == 0 )
    return;

  captionWidth = ResourcesFont_GetTextAdvance( _this->Super2.CaptionText.Font, _this->Super2.CaptionText.String, 
  0, -1 );
  x = ( aSize.X - captionWidth ) / 2;

  if ( x < ( _this->Super1.Image.Super1.Bounds.Point2.X + 10 ))
  {
    XInt32 maxCaptionWidth;
    ViewsText_OnSetAlignment( &_this->Super2.CaptionText, ViewsTextAlignmentAlignHorzLeft 
    | ViewsTextAlignmentAlignVertCenter );
    maxCaptionWidth = aSize.X - ((( _this->Super1.Image.Super1.Bounds.Point1.X + 
    EwGetRectW( _this->Super1.Image.Super1.Bounds )) + 10 ) + 10 );
    CoreRectView__OnSetBounds( &_this->Super2.CaptionText, EwSetRectX1( _this->Super2.CaptionText.Super1.Bounds, 
    ( _this->Super1.Image.Super1.Bounds.Point2.X + 10 ) + (( maxCaptionWidth - captionWidth ) 
    / 2 )));
    CoreRectView__OnSetBounds( &_this->Super2.CaptionText, EwSetRectX2( _this->Super2.CaptionText.Super1.Bounds, 
    aSize.X ));
  }
  else
    ViewsText_OnSetAlignment( &_this->Super2.CaptionText, ViewsTextAlignmentAlignHorzCenter 
    | ViewsTextAlignmentAlignVertCenter );
}

/* 'C' function for method : 'Components::SettingsButton.onActivate()' */
void ComponentsSettingsButton_onActivate( ComponentsSettingsButton _this, XObject 
  sender )
{
  ComponentsBaseButton_onActivate((ComponentsBaseButton)_this, sender );

  if ( _this->SettingsPage != DeviceSettingsPageNone )
    DeviceDeviceClass_OnSetCurrentSettings( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
    _this->SettingsPage );
}

/* Variants derived from the class : 'Components::SettingsButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsSettingsButton )
EW_END_OF_CLASS_VARIANTS( ComponentsSettingsButton )

/* Virtual Method Table (VMT) for the class : 'Components::SettingsButton' */
EW_DEFINE_CLASS( ComponentsSettingsButton, ComponentsIconTextButton, _.VMT, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, "Components::SettingsButton" )
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
  ComponentsSettingsButton_UpdateLayout,
  ComponentsIconTextButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsSettingsButton_onActivate,
  ComponentsIconTextButton_OnSetCaption,
EW_END_OF_CLASS( ComponentsSettingsButton )

/* Initializer for the class 'Components::TileInRunning' */
void ComponentsTileInRunning__Init( ComponentsTileInRunning _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsTile__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsTileInRunning );

  /* ... then construct all embedded objects */
  ComponentsIntValueDisplay__Init( &_this->RemainingValueDisplay, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->Unit1Text, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->OfText, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsTileInRunning );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( &_this->Super2.CaptionText, _Const0056 );
  CoreRectView__OnSetBounds( &_this->Super2.UnitText, _Const0057 );
  CoreRectView__OnSetBounds( &_this->Super2.ValueDisplay, _Const0058 );
  CoreRectView__OnSetBounds( &_this->RemainingValueDisplay, _Const0059 );
  ViewsText_OnSetOverflowWarning((ViewsText)&_this->RemainingValueDisplay, 1 );
  ViewsText_OnSetAlignment((ViewsText)&_this->RemainingValueDisplay, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->RemainingValueDisplay, EwLoadString( &_Const0006 ));
  CoreRectView__OnSetBounds( &_this->Unit1Text, _Const005A );
  ViewsText_OnSetOverflowWarning( &_this->Unit1Text, 1 );
  ViewsText_OnSetAlignment( &_this->Unit1Text, ViewsTextAlignmentAlignHorzLeft | 
  ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->Unit1Text, EwLoadString( &_Const0006 ));
  CoreRectView__OnSetBounds( &_this->OfText, _Const005B );
  ViewsText_OnSetOverflowWarning( &_this->OfText, 1 );
  ViewsText_OnSetAlignment( &_this->OfText, ViewsTextAlignmentAlignHorzLeft | ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->OfText, EwLoadString( &Stringsof ));
  CoreGroup__Add( _this, ((CoreView)&_this->RemainingValueDisplay ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Unit1Text ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->OfText ), 0 );
  ComponentsValueDisplay_OnSetFont1((ComponentsValueDisplay)&_this->Super2.ValueDisplay, 
  EwLoadResource( &FontsSmall, ResourcesFont ));
  _this->Super2.ValueDisplay.Super1.OnAdjustFont = EwNewSlot( _this, ComponentsTileInRunning_onAdjustFont );
  ComponentsBaseTile_OnSetValueFont1((ComponentsBaseTile)_this, EwLoadResource( 
  &FontsSmall, ResourcesFont ));
  ViewsText__OnSetFont( &_this->RemainingValueDisplay, EwLoadResource( &FontsMedium, 
  ResourcesFont ));
  ViewsText__OnSetFont( &_this->Unit1Text, EwLoadResource( &FontsHeading3, ResourcesFont ));
  ViewsText__OnSetFont( &_this->OfText, EwLoadResource( &FontsHeading2, ResourcesFont ));

  /* Call the user defined constructor */
  ComponentsTileInRunning_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::TileInRunning' */
void ComponentsTileInRunning__ReInit( ComponentsTileInRunning _this )
{
  /* At first re-initialize the super class ... */
  ComponentsTile__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsIntValueDisplay__ReInit( &_this->RemainingValueDisplay );
  ViewsText__ReInit( &_this->Unit1Text );
  ViewsText__ReInit( &_this->OfText );
}

/* Finalizer method for the class 'Components::TileInRunning' */
void ComponentsTileInRunning__Done( ComponentsTileInRunning _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsTile );

  /* Finalize all embedded objects */
  ComponentsIntValueDisplay__Done( &_this->RemainingValueDisplay );
  ViewsText__Done( &_this->Unit1Text );
  ViewsText__Done( &_this->OfText );

  /* Don't forget to deinitialize the super class ... */
  ComponentsTile__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsTileInRunning_Init( ComponentsTileInRunning _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  EwPostSignal( EwNewSlot( _this, ComponentsTileInRunning_update ), ((XObject)_this ));
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
void ComponentsTileInRunning_UpdateViewState( ComponentsTileInRunning _this, XSet 
  aState )
{
  ComponentsTile_UpdateViewState((ComponentsTile)_this, aState );
  ViewsText_OnSetColor((ViewsText)&_this->RemainingValueDisplay, ResOnPrimary );
  ViewsText_OnSetColor( &_this->Unit1Text, ResOnSecondary );
  ViewsText_OnSetColor( &_this->OfText, ResOnPrimary );
}

/* 'C' function for method : 'Components::TileInRunning.OnSetUnit()' */
void ComponentsTileInRunning_OnSetUnit( ComponentsTileInRunning _this, XString value )
{
  ComponentsBaseTile_OnSetUnit((ComponentsBaseTile)_this, value );
  ViewsText__OnSetString( &_this->Unit1Text, value );
}

/* 'C' function for method : 'Components::TileInRunning.OnSetValue()' */
void ComponentsTileInRunning_OnSetValue( ComponentsTileInRunning _this, XInt32 value )
{
  ComponentsBaseTile_OnSetValue((ComponentsBaseTile)_this, value );
  EwPostSignal( EwNewSlot( _this, ComponentsTileInRunning_update ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::TileInRunning.OnSetResolution()' */
void ComponentsTileInRunning_OnSetResolution( ComponentsTileInRunning _this, XInt32 
  value )
{
  ComponentsBaseTile_OnSetResolution((ComponentsBaseTile)_this, value );
  ComponentsIntValueDisplay_OnSetResolution( &_this->RemainingValueDisplay, value );
}

/* 'C' function for method : 'Components::TileInRunning.OnSetCurrentValue()' */
void ComponentsTileInRunning_OnSetCurrentValue( ComponentsTileInRunning _this, XInt32 
  value )
{
  if ( _this->CurrentValue == value )
    return;

  _this->CurrentValue = value;
  EwPostSignal( EwNewSlot( _this, ComponentsTileInRunning_update ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::TileInRunning.OnSetCurrentValueOutlet()' */
void ComponentsTileInRunning_OnSetCurrentValueOutlet( ComponentsTileInRunning _this, 
  XRef value )
{
  if ( !EwCompRef( _this->CurrentValueOutlet, value ))
    return;

  if ( _this->CurrentValueOutlet.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsTileInRunning_onCurrentValueOutlet ), 
      _this->CurrentValueOutlet, 0 );

  _this->CurrentValueOutlet = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsTileInRunning_onCurrentValueOutlet ), 
      _this->CurrentValueOutlet, 0 );

  EwPostSignal( EwNewSlot( _this, ComponentsTileInRunning_onCurrentValueOutlet ), 
    ((XObject)_this ));
}

/* 'C' function for method : 'Components::TileInRunning.onCurrentValueOutlet()' */
void ComponentsTileInRunning_onCurrentValueOutlet( ComponentsTileInRunning _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->CurrentValueOutlet.Object != 0 )
    ComponentsTileInRunning_OnSetCurrentValue( _this, EwOnGetInt32( _this->CurrentValueOutlet ));
}

/* 'C' function for method : 'Components::TileInRunning.update()' */
void ComponentsTileInRunning_update( ComponentsTileInRunning _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ComponentsIntValueDisplay_OnSetValue( &_this->RemainingValueDisplay, _this->Super2.Value 
  - _this->CurrentValue );
}

/* 'C' function for method : 'Components::TileInRunning.onAdjustFont()' */
void ComponentsTileInRunning_onAdjustFont( ComponentsTileInRunning _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ViewsText__OnSetFont( &_this->RemainingValueDisplay, _this->Super2.ValueDisplay.Super2.Font );
}

/* Variants derived from the class : 'Components::TileInRunning' */
EW_DEFINE_CLASS_VARIANTS( ComponentsTileInRunning )
EW_END_OF_CLASS_VARIANTS( ComponentsTileInRunning )

/* Virtual Method Table (VMT) for the class : 'Components::TileInRunning' */
EW_DEFINE_CLASS( ComponentsTileInRunning, ComponentsTile, RemainingValueDisplay, 
                 CurrentValueOutlet, CurrentValueOutlet, CurrentValueOutlet, CurrentValue, 
                 CurrentValue, "Components::TileInRunning" )
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
  ComponentsTileInRunning_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsTileInRunning_OnSetUnit,
  ComponentsTileInRunning_OnSetValue,
  ComponentsTileInRunning_OnSetResolution,
  ComponentsBaseTile_OnSetOutlet,
EW_END_OF_CLASS( ComponentsTileInRunning )

/* Initializer for the class 'Components::TileTimeInRunning' */
void ComponentsTileTimeInRunning__Init( ComponentsTileTimeInRunning _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsTileTime__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsTileTimeInRunning );

  /* ... then construct all embedded objects */
  ComponentsProgressBar__Init( &_this->ProgressBar, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsTileTimeInRunning );

  /* ... and initialize objects, variables, properties, etc. */
  ViewsText_OnSetVisible( &_this->Super3.UnitText, 0 );
  CoreRectView__OnSetBounds( &_this->ProgressBar, _Const005C );
  ComponentsHorzValueBar_OnSetBarColor((ComponentsHorzValueBar)&_this->ProgressBar, 
  ResSuccess );
  CoreGroup__Add( _this, ((CoreView)&_this->ProgressBar ), 0 );
  ComponentsHorzValueBar_OnSetOutlet((ComponentsHorzValueBar)&_this->ProgressBar, 
  EwNewRef( _this, ComponentsTileTimeInRunning_OnGetProgress, ComponentsTileTimeInRunning_OnSetProgress ));
}

/* Re-Initializer for the class 'Components::TileTimeInRunning' */
void ComponentsTileTimeInRunning__ReInit( ComponentsTileTimeInRunning _this )
{
  /* At first re-initialize the super class ... */
  ComponentsTileTime__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsProgressBar__ReInit( &_this->ProgressBar );
}

/* Finalizer method for the class 'Components::TileTimeInRunning' */
void ComponentsTileTimeInRunning__Done( ComponentsTileTimeInRunning _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsTileTime );

  /* Finalize all embedded objects */
  ComponentsProgressBar__Done( &_this->ProgressBar );

  /* Don't forget to deinitialize the super class ... */
  ComponentsTileTime__Done( &_this->_.Super );
}

/* 'C' function for method : 'Components::TileTimeInRunning.OnSetRemainingTime()' */
void ComponentsTileTimeInRunning_OnSetRemainingTime( ComponentsTileTimeInRunning _this, 
  XInt32 value )
{
  if ( _this->RemainingTime == value )
    return;

  _this->RemainingTime = value;
  ComponentsIntValueDisplay_OnSetValue( &_this->Super3.ValueDisplay, value );

  if ( _this->Super3.Value > 0 )
    ComponentsTileTimeInRunning_OnSetProgress( _this, 100 - (( value * 100 ) / _this->Super3.Value ));
}

/* 'C' function for method : 'Components::TileTimeInRunning.OnSetRemainingOutlet()' */
void ComponentsTileTimeInRunning_OnSetRemainingOutlet( ComponentsTileTimeInRunning _this, 
  XRef value )
{
  if ( !EwCompRef( _this->RemainingOutlet, value ))
    return;

  if ( _this->RemainingOutlet.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsTileTimeInRunning_onRemainingOutlet ), 
      _this->RemainingOutlet, 0 );

  _this->RemainingOutlet = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsTileTimeInRunning_onRemainingOutlet ), 
      _this->RemainingOutlet, 0 );

  EwPostSignal( EwNewSlot( _this, ComponentsTileTimeInRunning_onRemainingOutlet ), 
    ((XObject)_this ));
}

/* 'C' function for method : 'Components::TileTimeInRunning.onRemainingOutlet()' */
void ComponentsTileTimeInRunning_onRemainingOutlet( ComponentsTileTimeInRunning _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->RemainingOutlet.Object != 0 )
    ComponentsTileTimeInRunning_OnSetRemainingTime( _this, EwOnGetInt32( _this->RemainingOutlet ));
}

/* 'C' function for method : 'Components::TileTimeInRunning.OnSetProgress()' */
void ComponentsTileTimeInRunning_OnSetProgress( ComponentsTileTimeInRunning _this, 
  XInt32 value )
{
  if ( _this->Progress == value )
    return;

  _this->Progress = value;
  EwNotifyRefObservers( EwNewRef( _this, ComponentsTileTimeInRunning_OnGetProgress, 
    ComponentsTileTimeInRunning_OnSetProgress ), 0 );
}

/* Default onget method for the property 'Progress' */
XInt32 ComponentsTileTimeInRunning_OnGetProgress( ComponentsTileTimeInRunning _this )
{
  return _this->Progress;
}

/* Variants derived from the class : 'Components::TileTimeInRunning' */
EW_DEFINE_CLASS_VARIANTS( ComponentsTileTimeInRunning )
EW_END_OF_CLASS_VARIANTS( ComponentsTileTimeInRunning )

/* Virtual Method Table (VMT) for the class : 'Components::TileTimeInRunning' */
EW_DEFINE_CLASS( ComponentsTileTimeInRunning, ComponentsTileTime, ProgressBar, RemainingOutlet, 
                 RemainingOutlet, RemainingOutlet, RemainingTime, RemainingTime, 
                 "Components::TileTimeInRunning" )
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
  ComponentsTile_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsBaseTile_OnSetUnit,
  ComponentsBaseTile_OnSetValue,
  ComponentsBaseTile_OnSetResolution,
  ComponentsBaseTile_OnSetOutlet,
EW_END_OF_CLASS( ComponentsTileTimeInRunning )

/* Initializer for the class 'Components::PressureTile' */
void ComponentsPressureTile__Init( ComponentsPressureTile _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsTile__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsPressureTile );

  /* ... then construct all embedded objects */
  ViewsText__Init( &_this->StageText, &_this->_.XObject, 0 );
  ComponentsGauge__Init( &_this->Gauge, &_this->_.XObject, 0 );
  ComponentsGaugeExt__Init( &_this->GaugeExt, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsPressureTile );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const005D );
  ComponentsBaseTile_OnSetCaption((ComponentsBaseTile)_this, EwLoadString( &StringsPressureStage ));
  ViewsImage_OnSetVisible( &_this->Super1.IconImage, 0 );
  CoreRectView__OnSetBounds( &_this->Super2.CaptionText, _Const005E );
  ViewsText_OnSetAlignment( &_this->Super2.CaptionText, ViewsTextAlignmentAlignHorzCenter 
  | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->Super2.UnitText, _Const005F );
  ViewsText_OnSetAlignment( &_this->Super2.UnitText, ViewsTextAlignmentAlignHorzCenter 
  | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->Super2.ValueDisplay, _Const0060 );
  ViewsText_OnSetAlignment((ViewsText)&_this->Super2.ValueDisplay, ViewsTextAlignmentAlignHorzCenter 
  | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->StageText, _Const0061 );
  ViewsText_OnSetOverflowWarning( &_this->StageText, 1 );
  ViewsText_OnSetAlignment( &_this->StageText, ViewsTextAlignmentAlignHorzCenter 
  | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->Gauge, _Const0062 );
  ComponentsGaugeBase_OnSetMaxValue((ComponentsGaugeBase)&_this->Gauge, 9 );
  CoreRectView__OnSetBounds( &_this->GaugeExt, _Const0063 );
  ComponentsGaugeBase_OnSetMaxValue((ComponentsGaugeBase)&_this->GaugeExt, 1000 );
  CoreGroup__Add( _this, ((CoreView)&_this->StageText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Gauge ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->GaugeExt ), 0 );
  ViewsText__OnSetFont( &_this->Super2.UnitText, EwLoadResource( &FontsBody16, ResourcesFont ));
  ViewsText__OnSetFont( &_this->Super2.ValueDisplay, EwLoadResource( &FontsHeading3, 
  ResourcesFont ));
  ViewsText__OnSetFont( &_this->StageText, EwLoadResource( &FontsHeading3, ResourcesFont ));

  /* Call the user defined constructor */
  ComponentsPressureTile_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::PressureTile' */
void ComponentsPressureTile__ReInit( ComponentsPressureTile _this )
{
  /* At first re-initialize the super class ... */
  ComponentsTile__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsText__ReInit( &_this->StageText );
  ComponentsGauge__ReInit( &_this->Gauge );
  ComponentsGaugeExt__ReInit( &_this->GaugeExt );
}

/* Finalizer method for the class 'Components::PressureTile' */
void ComponentsPressureTile__Done( ComponentsPressureTile _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsTile );

  /* Finalize all embedded objects */
  ViewsText__Done( &_this->StageText );
  ComponentsGauge__Done( &_this->Gauge );
  ComponentsGaugeExt__Done( &_this->GaugeExt );

  /* Don't forget to deinitialize the super class ... */
  ComponentsTile__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsPressureTile_Init( ComponentsPressureTile _this, XHandle aArg )
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
void ComponentsPressureTile_UpdateViewState( ComponentsPressureTile _this, XSet 
  aState )
{
  ComponentsTile_UpdateViewState((ComponentsTile)_this, aState );
  ViewsText_OnSetColor( &_this->StageText, ResOnPrimary );
  ViewsText_OnSetColor( &_this->Super2.UnitText, ResInfo );
}

/* 'C' function for method : 'Components::PressureTile.OnSetOutlet()' */
void ComponentsPressureTile_OnSetOutlet( ComponentsPressureTile _this, XRef value )
{
  ComponentsBaseTile_OnSetOutlet((ComponentsBaseTile)_this, value );
  ComponentsGaugeBase_OnSetOutlet((ComponentsGaugeBase)&_this->GaugeExt, value );
}

/* 'C' function for method : 'Components::PressureTile.OnSetStage()' */
void ComponentsPressureTile_OnSetStage( ComponentsPressureTile _this, XInt32 value )
{
  if ( _this->Stage == value )
    return;

  _this->Stage = value;
  ViewsText__OnSetString( &_this->StageText, EwNewStringInt( value, 0, 10 ));
  ComponentsGaugeBase_OnSetCurrentValue((ComponentsGaugeBase)&_this->Gauge, value );
  ComponentsGaugeExt_OnSetNormalRangeMax( &_this->GaugeExt, DeviceDeviceClass_GetPresurreNormalMax( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), value ));
  ComponentsGaugeExt_OnSetWarningRangeMax( &_this->GaugeExt, DeviceDeviceClass_GetPresurreWarningMax( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), value ));
  ComponentsGaugeExt_OnSetErrorRangeMax( &_this->GaugeExt, DeviceDeviceClass_GetPresurreErrorMax( 
  EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), value ));
}

/* 'C' function for method : 'Components::PressureTile.OnSetStageOutlet()' */
void ComponentsPressureTile_OnSetStageOutlet( ComponentsPressureTile _this, XRef 
  value )
{
  if ( !EwCompRef( _this->StageOutlet, value ))
    return;

  if ( _this->StageOutlet.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsPressureTile_onStageOutlet ), 
      _this->StageOutlet, 0 );

  _this->StageOutlet = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsPressureTile_onStageOutlet ), 
      _this->StageOutlet, 0 );

  EwPostSignal( EwNewSlot( _this, ComponentsPressureTile_onStageOutlet ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::PressureTile.onStageOutlet()' */
void ComponentsPressureTile_onStageOutlet( ComponentsPressureTile _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->StageOutlet.Object != 0 )
    ComponentsPressureTile_OnSetStage( _this, EwOnGetInt32( _this->StageOutlet ));
}

/* Variants derived from the class : 'Components::PressureTile' */
EW_DEFINE_CLASS_VARIANTS( ComponentsPressureTile )
EW_END_OF_CLASS_VARIANTS( ComponentsPressureTile )

/* Virtual Method Table (VMT) for the class : 'Components::PressureTile' */
EW_DEFINE_CLASS( ComponentsPressureTile, ComponentsTile, StageText, StageOutlet, 
                 StageOutlet, StageOutlet, Stage, Stage, "Components::PressureTile" )
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
  ComponentsPressureTile_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsBaseTile_OnSetUnit,
  ComponentsBaseTile_OnSetValue,
  ComponentsBaseTile_OnSetResolution,
  ComponentsPressureTile_OnSetOutlet,
EW_END_OF_CLASS( ComponentsPressureTile )

/* Initializer for the class 'Components::Gauge' */
void ComponentsGauge__Init( ComponentsGauge _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsGaugeBase__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsGauge );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsGauge );

  /* ... and initialize objects, variables, properties, etc. */
  ViewsImage_OnSetBitmap( &_this->Super1.Background, EwLoadResource( &Resgauge, 
  ResourcesBitmap ));
  ViewsWarpImage_OnSetBitmap( &_this->Super1.Needle, EwLoadResource( &Resneedle, 
  ResourcesBitmap ));
}

/* Re-Initializer for the class 'Components::Gauge' */
void ComponentsGauge__ReInit( ComponentsGauge _this )
{
  /* At first re-initialize the super class ... */
  ComponentsGaugeBase__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::Gauge' */
void ComponentsGauge__Done( ComponentsGauge _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsGaugeBase );

  /* Don't forget to deinitialize the super class ... */
  ComponentsGaugeBase__Done( &_this->_.Super );
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
void ComponentsGauge_UpdateViewState( ComponentsGauge _this, XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ComponentsGaugeBase_rotateNeedle((ComponentsGaugeBase)_this, 0, _this->Super1.MaxValue, 
  210.0f, -30.0f );
  ViewsImage_OnSetColor( &_this->Super1.Background, ResOnSecondary );
  ViewsWarpImage_OnSetColor( &_this->Super1.Needle, ResOnSecondary );
}

/* Variants derived from the class : 'Components::Gauge' */
EW_DEFINE_CLASS_VARIANTS( ComponentsGauge )
EW_END_OF_CLASS_VARIANTS( ComponentsGauge )

/* Virtual Method Table (VMT) for the class : 'Components::Gauge' */
EW_DEFINE_CLASS( ComponentsGauge, ComponentsGaugeBase, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, "Components::Gauge" )
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
  ComponentsGauge_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsGaugeBase_getNeedlePos,
EW_END_OF_CLASS( ComponentsGauge )

/* Initializer for the class 'Components::GaugeExt' */
void ComponentsGaugeExt__Init( ComponentsGaugeExt _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsGaugeBase__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsGaugeExt );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsGaugeExt );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0064 );
  ViewsWarpView_OnSetSourceAnchor((ViewsWarpView)&_this->Super1.Needle, _Const0065 );
  ViewsImage_OnSetBitmap( &_this->Super1.Background, EwLoadResource( &Resgauge_ranges, 
  ResourcesBitmap ));
  ViewsWarpImage_OnSetBitmap( &_this->Super1.Needle, EwLoadResource( &Resneedle_circle, 
  ResourcesBitmap ));

  /* Call the user defined constructor */
  ComponentsGaugeExt_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::GaugeExt' */
void ComponentsGaugeExt__ReInit( ComponentsGaugeExt _this )
{
  /* At first re-initialize the super class ... */
  ComponentsGaugeBase__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::GaugeExt' */
void ComponentsGaugeExt__Done( ComponentsGaugeExt _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsGaugeBase );

  /* Don't forget to deinitialize the super class ... */
  ComponentsGaugeBase__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsGaugeExt_Init( ComponentsGaugeExt _this, XHandle aArg )
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
void ComponentsGaugeExt_UpdateViewState( ComponentsGaugeExt _this, XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );

  if ( ComponentsGaugeBase_OnGetCurrentValue((ComponentsGaugeBase)_this ) <= _this->NormalRangeMax )
    ComponentsGaugeBase_rotateNeedle((ComponentsGaugeBase)_this, 0, _this->NormalRangeMax, 
    200.0f, 90.0f );
  else
    if ( ComponentsGaugeBase_OnGetCurrentValue((ComponentsGaugeBase)_this ) < _this->WarningRangeMax )
      ComponentsGaugeBase_rotateNeedle((ComponentsGaugeBase)_this, _this->NormalRangeMax, 
      _this->WarningRangeMax, 90.0f, 0.0f );
    else
      ComponentsGaugeBase_rotateNeedle((ComponentsGaugeBase)_this, _this->WarningRangeMax, 
      _this->ErrorRangeMax, 5.0f, -15.0f );
}

/* 'C' function for method : 'Components::GaugeExt.getNeedlePos()' */
XPoint ComponentsGaugeExt_getNeedlePos( ComponentsGaugeExt _this )
{
  return EwGetRectCenter( EwGetRectORect( _this->Super4.Bounds ));
}

/* 'C' function for method : 'Components::GaugeExt.OnSetNormalRangeMax()' */
void ComponentsGaugeExt_OnSetNormalRangeMax( ComponentsGaugeExt _this, XInt32 value )
{
  if ( _this->NormalRangeMax == value )
    return;

  _this->NormalRangeMax = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'Components::GaugeExt.OnSetWarningRangeMax()' */
void ComponentsGaugeExt_OnSetWarningRangeMax( ComponentsGaugeExt _this, XInt32 value )
{
  if ( _this->WarningRangeMax == value )
    return;

  _this->WarningRangeMax = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'Components::GaugeExt.OnSetErrorRangeMax()' */
void ComponentsGaugeExt_OnSetErrorRangeMax( ComponentsGaugeExt _this, XInt32 value )
{
  if ( _this->ErrorRangeMax == value )
    return;

  _this->ErrorRangeMax = value;
  ComponentsGaugeBase_OnSetMaxValue((ComponentsGaugeBase)_this, value );
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* Variants derived from the class : 'Components::GaugeExt' */
EW_DEFINE_CLASS_VARIANTS( ComponentsGaugeExt )
EW_END_OF_CLASS_VARIANTS( ComponentsGaugeExt )

/* Virtual Method Table (VMT) for the class : 'Components::GaugeExt' */
EW_DEFINE_CLASS( ComponentsGaugeExt, ComponentsGaugeBase, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, "Components::GaugeExt" )
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
  ComponentsGaugeExt_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsGaugeExt_getNeedlePos,
EW_END_OF_CLASS( ComponentsGaugeExt )

/* Initializer for the class 'Components::GaugeBase' */
void ComponentsGaugeBase__Init( ComponentsGaugeBase _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  TemplatesGauge__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsGaugeBase );

  /* ... then construct all embedded objects */
  ViewsImage__Init( &_this->Background, &_this->_.XObject, 0 );
  ViewsWarpImage__Init( &_this->Needle, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsGaugeBase );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0008 );
  CoreGroup_OnSetEnabled((CoreGroup)_this, 0 );
  CoreView_OnSetLayout((CoreView)&_this->Background, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->Background, _Const0008 );
  ViewsWarpView_OnSetSourceAnchor((ViewsWarpView)&_this->Needle, _Const0066 );
  _this->MaxValue = 100;
  CoreGroup__Add( _this, ((CoreView)&_this->Background ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Needle ), 0 );
}

/* Re-Initializer for the class 'Components::GaugeBase' */
void ComponentsGaugeBase__ReInit( ComponentsGaugeBase _this )
{
  /* At first re-initialize the super class ... */
  TemplatesGauge__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsImage__ReInit( &_this->Background );
  ViewsWarpImage__ReInit( &_this->Needle );
}

/* Finalizer method for the class 'Components::GaugeBase' */
void ComponentsGaugeBase__Done( ComponentsGaugeBase _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( TemplatesGauge );

  /* Finalize all embedded objects */
  ViewsImage__Done( &_this->Background );
  ViewsWarpImage__Done( &_this->Needle );

  /* Don't forget to deinitialize the super class ... */
  TemplatesGauge__Done( &_this->_.Super );
}

/* This slot method will receive a signal, if the value of the property assigned 
   to @Outlet has been changed by another widget or by the application logic. In 
   response to this notification, the gauge will update itself. */
void ComponentsGaugeBase_onOutlet( ComponentsGaugeBase _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Outlet.Object != 0 )
    ComponentsGaugeBase_OnSetCurrentValue( _this, EwOnGetInt32( _this->Outlet ));
}

/* 'C' function for method : 'Components::GaugeBase.OnSetOutlet()' */
void ComponentsGaugeBase_OnSetOutlet( ComponentsGaugeBase _this, XRef value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  if ( _this->Outlet.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsGaugeBase_onOutlet ), _this->Outlet, 
      0 );

  _this->Outlet = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsGaugeBase_onOutlet ), value, 
      0 );

  if ( value.Object != 0 )
    EwPostSignal( EwNewSlot( _this, ComponentsGaugeBase_onOutlet ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::GaugeBase.OnSetMaxValue()' */
void ComponentsGaugeBase_OnSetMaxValue( ComponentsGaugeBase _this, XInt32 value )
{
  if ( _this->MaxValue == value )
    return;

  _this->MaxValue = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'Components::GaugeBase.OnGetCurrentValue()' */
XInt32 ComponentsGaugeBase_OnGetCurrentValue( ComponentsGaugeBase _this )
{
  XInt32 value = _this->CurrentValue;

  if ( 0 > _this->MaxValue )
  {
    if ( value < _this->MaxValue )
      value = _this->MaxValue;

    if ( value > 0 )
      value = 0;
  }
  else
  {
    if ( value < 0 )
      value = 0;

    if ( value > _this->MaxValue )
      value = _this->MaxValue;
  }

  return value;
}

/* 'C' function for method : 'Components::GaugeBase.OnSetCurrentValue()' */
void ComponentsGaugeBase_OnSetCurrentValue( ComponentsGaugeBase _this, XInt32 value )
{
  if ( _this->CurrentValue == value )
    return;

  _this->CurrentValue = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'Components::GaugeBase.rotateNeedle()' */
void ComponentsGaugeBase_rotateNeedle( ComponentsGaugeBase _this, XInt32 aMinValue, 
  XInt32 aMaxValue, XFloat aMinAngle, XFloat aMaxAngle )
{
  XFloat newRotationAngle;
  XPoint dstPos;

  if ( _this->Needle.Bitmap == 0 )
    return;

  newRotationAngle = aMinAngle;

  if ( aMaxValue != aMinValue )
    newRotationAngle = (((XFloat)( ComponentsGaugeBase_OnGetCurrentValue( _this ) 
    - aMinValue ) * ( aMaxAngle - aMinAngle )) / (XFloat)( aMaxValue - aMinValue )) 
    + aMinAngle;

  dstPos = ComponentsGaugeBase__getNeedlePos( _this );
  ViewsWarpView_RotateAndScale((ViewsWarpView)&_this->Needle, dstPos, newRotationAngle 
  - 90.0f, 1.0f, 1.0f );
}

/* 'C' function for method : 'Components::GaugeBase.getNeedlePos()' */
XPoint ComponentsGaugeBase_getNeedlePos( ComponentsGaugeBase _this )
{
  XPoint needleSize = _this->Needle.Bitmap->FrameSize;
  XPoint needlePivot = _this->Needle.Super1.SourceAnchor;

  return EwNewPoint( EwGetRectW( _this->Super3.Bounds ) / 2, (( EwGetRectH( _this->Super3.Bounds ) 
    - needleSize.Y ) / 2 ) + needlePivot.Y );
}

/* Wrapper function for the virtual method : 'Components::GaugeBase.getNeedlePos()' */
XPoint ComponentsGaugeBase__getNeedlePos( void* _this )
{
  return ((ComponentsGaugeBase)_this)->_.VMT->getNeedlePos((ComponentsGaugeBase)_this );
}

/* Variants derived from the class : 'Components::GaugeBase' */
EW_DEFINE_CLASS_VARIANTS( ComponentsGaugeBase )
EW_END_OF_CLASS_VARIANTS( ComponentsGaugeBase )

/* Virtual Method Table (VMT) for the class : 'Components::GaugeBase' */
EW_DEFINE_CLASS( ComponentsGaugeBase, TemplatesGauge, Background, Outlet, Outlet, 
                 Outlet, MaxValue, MaxValue, "Components::GaugeBase" )
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
  ComponentsGaugeBase_getNeedlePos,
EW_END_OF_CLASS( ComponentsGaugeBase )

/* Initializer for the class 'Components::MenuButton' */
void ComponentsMenuButton__Init( ComponentsMenuButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsIconTextButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsMenuButton );

  /* ... then construct all embedded objects */
  ViewsText__Init( &_this->HintText, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsMenuButton );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0067 );
  ViewsRectangle_OnSetRadius( &_this->Super3.Background, 10 );
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)_this, ResSurface3 );
  ComponentsBaseButton_OnSetBgColorPressed((ComponentsBaseButton)_this, ResSurface3 );
  CoreRectView__OnSetBounds( &_this->Super2.CaptionText, _Const0068 );
  ComponentsTextButton_OnSetCaptionColor((ComponentsTextButton)_this, ResOnPrimary );
  CoreView_OnSetLayout((CoreView)&_this->Super1.Image, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToLeft | CoreLayoutAlignToTop | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->Super1.Image, _Const0069 );
  ComponentsIconTextButton_OnSetIconColor((ComponentsIconTextButton)_this, ResOnPrimary );
  CoreView_OnSetLayout((CoreView)&_this->HintText, CoreLayoutAlignToLeft | CoreLayoutAlignToRight 
  | CoreLayoutAlignToTop | CoreLayoutResizeHorz );
  CoreRectView__OnSetBounds( &_this->HintText, _Const006A );
  ViewsText_OnSetOverflowWarning( &_this->HintText, 1 );
  ViewsText_OnSetAlignment( &_this->HintText, ViewsTextAlignmentAlignHorzCenter 
  | ViewsTextAlignmentAlignVertBottom );
  CoreGroup__Add( _this, ((CoreView)&_this->HintText ), 0 );
  ViewsText__OnSetFont( &_this->HintText, EwLoadResource( &FontsBody16, ResourcesFont ));

  /* Call the user defined constructor */
  ComponentsMenuButton_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::MenuButton' */
void ComponentsMenuButton__ReInit( ComponentsMenuButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsIconTextButton__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsText__ReInit( &_this->HintText );
}

/* Finalizer method for the class 'Components::MenuButton' */
void ComponentsMenuButton__Done( ComponentsMenuButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsIconTextButton );

  /* Finalize all embedded objects */
  ViewsText__Done( &_this->HintText );

  /* Don't forget to deinitialize the super class ... */
  ComponentsIconTextButton__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsMenuButton_Init( ComponentsMenuButton _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsMenuButton_UpdateLayout( ComponentsMenuButton _this, XPoint aSize )
{
  CoreGroup_UpdateLayout((CoreGroup)_this, aSize );

  if ( EwCompString( _this->Hint, 0 ) != 0 )
    CoreRectView__OnSetBounds( &_this->Super1.Image, EwSetRectY( _this->Super1.Image.Super1.Bounds, 
    _this->HintText.Super1.Bounds.Point2.Y ));
  else
    CoreRectView__OnSetBounds( &_this->Super1.Image, EwSetRectY( _this->Super1.Image.Super1.Bounds, 
    _this->Super2.CaptionText.Super1.Bounds.Point1.Y - EwGetRectH( _this->Super1.Image.Super1.Bounds )));
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
void ComponentsMenuButton_UpdateViewState( ComponentsMenuButton _this, XSet aState )
{
  ComponentsIconTextButton_UpdateViewState((ComponentsIconTextButton)_this, aState );
  ViewsText_OnSetColor( &_this->HintText, _this->Super2.CaptionText.Color );
}

/* 'C' function for method : 'Components::MenuButton.OnSetHint()' */
void ComponentsMenuButton_OnSetHint( ComponentsMenuButton _this, XString value )
{
  if ( !EwCompString( _this->Hint, value ))
    return;

  _this->Hint = EwShareString( value );
  ViewsText__OnSetString( &_this->HintText, value );
}

/* Variants derived from the class : 'Components::MenuButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsMenuButton )
EW_END_OF_CLASS_VARIANTS( ComponentsMenuButton )

/* Virtual Method Table (VMT) for the class : 'Components::MenuButton' */
EW_DEFINE_CLASS( ComponentsMenuButton, ComponentsIconTextButton, HintText, Hint, 
                 Hint, Hint, Hint, _.VMT, "Components::MenuButton" )
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
  ComponentsMenuButton_UpdateLayout,
  ComponentsMenuButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsIconTextButton_OnSetCaption,
EW_END_OF_CLASS( ComponentsMenuButton )

/* Initializer for the class 'Components::NotificationButton' */
void ComponentsNotificationButton__Init( ComponentsNotificationButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsIconTextButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsNotificationButton );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsNotificationButton );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const006B );
  ViewsRectangle_OnSetRadius( &_this->Super3.Background, 22 );
  CoreView_OnSetLayout((CoreView)&_this->Super2.CaptionText, CoreLayoutAlignToLeft 
  | CoreLayoutAlignToTop );
  CoreRectView__OnSetBounds( &_this->Super2.CaptionText, _Const006C );
  ViewsText_OnSetAlignment( &_this->Super2.CaptionText, ViewsTextAlignmentAlignHorzCenter 
  | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->Super1.Image, _Const006D );
  ViewsText__OnSetFont( &_this->Super2.CaptionText, EwLoadResource( &FontsBody14, 
  ResourcesFont ));
}

/* Re-Initializer for the class 'Components::NotificationButton' */
void ComponentsNotificationButton__ReInit( ComponentsNotificationButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsIconTextButton__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::NotificationButton' */
void ComponentsNotificationButton__Done( ComponentsNotificationButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsIconTextButton );

  /* Don't forget to deinitialize the super class ... */
  ComponentsIconTextButton__Done( &_this->_.Super );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsNotificationButton_UpdateLayout( ComponentsNotificationButton _this, 
  XPoint aSize )
{
  CoreGroup_UpdateLayout((CoreGroup)_this, aSize );

  if ( _this->Super1.Image.Bitmap == 0 )
  {
    CoreRectView__OnSetBounds( &_this->Super2.CaptionText, EwGetRectORect( _this->Super6.Bounds ));
    ViewsText__OnSetFont( &_this->Super2.CaptionText, EwLoadResource( &FontsHeading3, 
    ResourcesFont ));
    ViewsText_OnSetAlignment( &_this->Super2.CaptionText, ViewsTextAlignmentAlignHorzCenter 
    | ViewsTextAlignmentAlignVertCenter );
  }
  else
  {
    CoreRectView__OnSetBounds( &_this->Super2.CaptionText, EwNewRect( 0, _this->Super1.Image.Super1.Bounds.Point2.Y, 
    EwGetRectW( _this->Super6.Bounds ), EwGetRectH( _this->Super6.Bounds )));
    ViewsText__OnSetFont( &_this->Super2.CaptionText, EwLoadResource( &FontsBody14, 
    ResourcesFont ));
    ViewsText_OnSetAlignment( &_this->Super2.CaptionText, ViewsTextAlignmentAlignHorzCenter 
    | ViewsTextAlignmentAlignVertTop );
  }
}

/* Variants derived from the class : 'Components::NotificationButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsNotificationButton )
EW_END_OF_CLASS_VARIANTS( ComponentsNotificationButton )

/* Virtual Method Table (VMT) for the class : 'Components::NotificationButton' */
EW_DEFINE_CLASS( ComponentsNotificationButton, ComponentsIconTextButton, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Components::NotificationButton" )
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
  ComponentsNotificationButton_UpdateLayout,
  ComponentsIconTextButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
  ComponentsIconTextButton_OnSetCaption,
EW_END_OF_CLASS( ComponentsNotificationButton )

/* Initializer for the class 'Components::InfoTip' */
void ComponentsInfoTip__Init( ComponentsInfoTip _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsInfoTip );

  /* ... then construct all embedded objects */
  ViewsText__Init( &_this->TipText, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->IconImage, &_this->_.XObject, 0 );
  CoreSimpleTouchHandler__Init( &_this->SimpleTouchHandler, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsInfoTip );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const006E );
  CoreRectView__OnSetBounds( &_this->TipText, _Const006F );
  ViewsText_OnSetOverflowWarning( &_this->TipText, 1 );
  ViewsText_OnSetAlignment( &_this->TipText, ViewsTextAlignmentAlignHorzLeft | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->IconImage, _Const0070 );
  CoreQuadView__OnSetPoint4( &_this->SimpleTouchHandler, _Const0004 );
  CoreQuadView__OnSetPoint3( &_this->SimpleTouchHandler, _Const0071 );
  CoreQuadView__OnSetPoint2( &_this->SimpleTouchHandler, _Const0072 );
  CoreQuadView__OnSetPoint1( &_this->SimpleTouchHandler, _Const0073 );
  CoreSimpleTouchHandler_OnSetMaxStrikeCount( &_this->SimpleTouchHandler, 100 );
  CoreGroup__Add( _this, ((CoreView)&_this->TipText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->IconImage ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->SimpleTouchHandler ), 0 );
  ViewsText__OnSetFont( &_this->TipText, EwLoadResource( &FontsHeading3, ResourcesFont ));
  ViewsImage_OnSetBitmap( &_this->IconImage, EwLoadResource( &Resinfo, ResourcesBitmap ));
  _this->SimpleTouchHandler.OnPress = EwNewSlot( _this, ComponentsInfoTip_onTouchPress );

  /* Call the user defined constructor */
  ComponentsInfoTip_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::InfoTip' */
void ComponentsInfoTip__ReInit( ComponentsInfoTip _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsText__ReInit( &_this->TipText );
  ViewsImage__ReInit( &_this->IconImage );
  CoreSimpleTouchHandler__ReInit( &_this->SimpleTouchHandler );
}

/* Finalizer method for the class 'Components::InfoTip' */
void ComponentsInfoTip__Done( ComponentsInfoTip _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Finalize all embedded objects */
  ViewsText__Done( &_this->TipText );
  ViewsImage__Done( &_this->IconImage );
  CoreSimpleTouchHandler__Done( &_this->SimpleTouchHandler );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsInfoTip_Init( ComponentsInfoTip _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  EwPostSignal( EwNewSlot( _this, ComponentsInfoTip_updateBounds ), ((XObject)_this ));
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsInfoTip_UpdateLayout( ComponentsInfoTip _this, XPoint aSize )
{
  CoreGroup_UpdateLayout((CoreGroup)_this, aSize );
  CoreRectView__OnSetBounds( &_this->TipText, EwSetRectW( _this->TipText.Super1.Bounds, 
  ( aSize.X - EwGetRectW( _this->IconImage.Super1.Bounds )) - 10 ));
  CoreRectView__OnSetBounds( &_this->TipText, EwSetRectH( _this->TipText.Super1.Bounds, 
  aSize.Y ));
  CoreRectView__OnSetBounds( &_this->IconImage, EwSetRectX( _this->IconImage.Super1.Bounds, 
  _this->TipText.Super1.Bounds.Point2.X + 10 ));
  CoreRectView__OnSetBounds( &_this->IconImage, EwSetRectH( _this->IconImage.Super1.Bounds, 
  aSize.Y ));
  ToolsHelperCollection_SetQuadViewBounds( EwGetAutoObject( &ToolsHelper, ToolsHelperCollection ), 
  ((CoreQuadView)&_this->SimpleTouchHandler ), EwGetRectORect( _this->Super2.Bounds ));
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
void ComponentsInfoTip_UpdateViewState( ComponentsInfoTip _this, XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ViewsText_OnSetColor( &_this->TipText, ResOnPrimary );
  ViewsImage_OnSetColor( &_this->IconImage, ResPrimary );
}

/* 'C' function for method : 'Components::InfoTip.OnSetTipString()' */
void ComponentsInfoTip_OnSetTipString( ComponentsInfoTip _this, XString value )
{
  if ( !EwCompString( _this->TipString, value ))
    return;

  _this->TipString = EwShareString( value );
  ViewsText__OnSetString( &_this->TipText, value );
  EwPostSignal( EwNewSlot( _this, ComponentsInfoTip_updateBounds ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::InfoTip.onTouchPress()' */
void ComponentsInfoTip_onTouchPress( ComponentsInfoTip _this, XObject sender )
{
  ApplicationInfoTipPopup popup;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( !EwCompString( _this->InfoCaption, 0 ))
    return;

  popup = EwNewObject( ApplicationInfoTipPopup, 0 );

  if ( popup == 0 )
    return;

  NavigationPage__OnSetCaption( popup, _this->InfoCaption );
  ApplicationMessagePopup_OnSetMessage((ApplicationMessagePopup)popup, _this->InfoMessage );
  ApplicationPopupNavigatorClass_OpenPopup( EwGetAutoObject( &ApplicationPopupNavigator, 
  ApplicationPopupNavigatorClass ), ((ApplicationPopup)popup ), 0 );
}

/* 'C' function for method : 'Components::InfoTip.updateBounds()' */
void ComponentsInfoTip_updateBounds( ComponentsInfoTip _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->TipText.Font == 0 )
    return;

  CoreRectView__OnSetBounds( _this, EwSetRectW( _this->Super2.Bounds, ( ResourcesFont_GetTextAdvance( 
  _this->TipText.Font, _this->TipString, 0, -1 ) + EwGetRectW( _this->IconImage.Super1.Bounds )) 
  + 10 ));
}

/* Variants derived from the class : 'Components::InfoTip' */
EW_DEFINE_CLASS_VARIANTS( ComponentsInfoTip )
EW_END_OF_CLASS_VARIANTS( ComponentsInfoTip )

/* Virtual Method Table (VMT) for the class : 'Components::InfoTip' */
EW_DEFINE_CLASS( ComponentsInfoTip, CoreGroup, TipText, TipString, TipString, TipString, 
                 TipString, _.VMT, "Components::InfoTip" )
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
  ComponentsInfoTip_UpdateLayout,
  ComponentsInfoTip_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsInfoTip )

/* Initializer for the class 'Components::RoundIconButton' */
void ComponentsRoundIconButton__Init( ComponentsRoundIconButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsRoundButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsRoundIconButton );

  /* ... then construct all embedded objects */
  ViewsImage__Init( &_this->IconImage, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsRoundIconButton );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0008 );
  _this->IconColor = ResPrimaryContainer;
  CoreView_OnSetLayout((CoreView)&_this->IconImage, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->IconImage, _Const0008 );
  CoreGroup__Add( _this, ((CoreView)&_this->IconImage ), 0 );

  /* Call the user defined constructor */
  ComponentsRoundIconButton_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::RoundIconButton' */
void ComponentsRoundIconButton__ReInit( ComponentsRoundIconButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsRoundButton__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsImage__ReInit( &_this->IconImage );
}

/* Finalizer method for the class 'Components::RoundIconButton' */
void ComponentsRoundIconButton__Done( ComponentsRoundIconButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsRoundButton );

  /* Finalize all embedded objects */
  ViewsImage__Done( &_this->IconImage );

  /* Don't forget to deinitialize the super class ... */
  ComponentsRoundButton__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsRoundIconButton_Init( ComponentsRoundIconButton _this, XHandle aArg )
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
void ComponentsRoundIconButton_UpdateViewState( ComponentsRoundIconButton _this, 
  XSet aState )
{
  ComponentsBaseButton_UpdateViewState((ComponentsBaseButton)_this, aState );
  ViewsImage_OnSetColor( &_this->IconImage, _this->IconColor );
}

/* 'C' function for method : 'Components::RoundIconButton.OnSetIcon()' */
void ComponentsRoundIconButton_OnSetIcon( ComponentsRoundIconButton _this, ResourcesBitmap 
  value )
{
  if ( _this->Icon == value )
    return;

  _this->Icon = value;
  ViewsImage_OnSetBitmap( &_this->IconImage, value );
}

/* Variants derived from the class : 'Components::RoundIconButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsRoundIconButton )
EW_END_OF_CLASS_VARIANTS( ComponentsRoundIconButton )

/* Virtual Method Table (VMT) for the class : 'Components::RoundIconButton' */
EW_DEFINE_CLASS( ComponentsRoundIconButton, ComponentsRoundButton, IconImage, Icon, 
                 IconColor, IconColor, IconColor, IconColor, "Components::RoundIconButton" )
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
  ComponentsRoundButton_UpdateLayout,
  ComponentsRoundIconButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
EW_END_OF_CLASS( ComponentsRoundIconButton )

/* Initializer for the class 'Components::RoundButton' */
void ComponentsRoundButton__Init( ComponentsRoundButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsBaseButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsRoundButton );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsRoundButton );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0074 );
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)_this, ResOnPrimary );
  ComponentsBaseButton_OnSetBgColorPressed((ComponentsBaseButton)_this, ResOnPrimary );
}

/* Re-Initializer for the class 'Components::RoundButton' */
void ComponentsRoundButton__ReInit( ComponentsRoundButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsBaseButton__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::RoundButton' */
void ComponentsRoundButton__Done( ComponentsRoundButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsBaseButton );

  /* Don't forget to deinitialize the super class ... */
  ComponentsBaseButton__Done( &_this->_.Super );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsRoundButton_UpdateLayout( ComponentsRoundButton _this, XPoint aSize )
{
  CoreGroup_UpdateLayout((CoreGroup)_this, aSize );
  ViewsRectangle_OnSetRadius( &_this->Super1.Background, aSize.X / 2 );
}

/* Variants derived from the class : 'Components::RoundButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsRoundButton )
EW_END_OF_CLASS_VARIANTS( ComponentsRoundButton )

/* Virtual Method Table (VMT) for the class : 'Components::RoundButton' */
EW_DEFINE_CLASS( ComponentsRoundButton, ComponentsBaseButton, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, _.VMT, "Components::RoundButton" )
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
  ComponentsRoundButton_UpdateLayout,
  ComponentsBaseButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
EW_END_OF_CLASS( ComponentsRoundButton )

/* Initializer for the class 'Components::RoundTextButton' */
void ComponentsRoundTextButton__Init( ComponentsRoundTextButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsRoundButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsRoundTextButton );

  /* ... then construct all embedded objects */
  ViewsText__Init( &_this->CaptionText, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsRoundTextButton );

  /* ... and initialize objects, variables, properties, etc. */
  CoreView_OnSetLayout((CoreView)&_this->CaptionText, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToLeft | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz 
  | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->CaptionText, _Const0074 );
  ViewsText_OnSetOverflowWarning( &_this->CaptionText, 1 );
  ViewsText__OnSetString( &_this->CaptionText, EwLoadString( &_Const0006 ));
  _this->CaptionColor = ResPrimaryContainer;
  CoreGroup__Add( _this, ((CoreView)&_this->CaptionText ), 0 );
  ViewsText__OnSetFont( &_this->CaptionText, EwLoadResource( &FontsHeading3, ResourcesFont ));
  _this->Font = EwLoadResource( &FontsHeading3, ResourcesFont );
}

/* Re-Initializer for the class 'Components::RoundTextButton' */
void ComponentsRoundTextButton__ReInit( ComponentsRoundTextButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsRoundButton__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsText__ReInit( &_this->CaptionText );
}

/* Finalizer method for the class 'Components::RoundTextButton' */
void ComponentsRoundTextButton__Done( ComponentsRoundTextButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsRoundButton );

  /* Finalize all embedded objects */
  ViewsText__Done( &_this->CaptionText );

  /* Don't forget to deinitialize the super class ... */
  ComponentsRoundButton__Done( &_this->_.Super );
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
void ComponentsRoundTextButton_UpdateViewState( ComponentsRoundTextButton _this, 
  XSet aState )
{
  ComponentsBaseButton_UpdateViewState((ComponentsBaseButton)_this, aState );
  ViewsText_OnSetColor( &_this->CaptionText, _this->CaptionColor );
}

/* 'C' function for method : 'Components::RoundTextButton.OnSetCaption()' */
void ComponentsRoundTextButton_OnSetCaption( ComponentsRoundTextButton _this, XString 
  value )
{
  if ( !EwCompString( _this->Caption, value ))
    return;

  _this->Caption = EwShareString( value );
  ViewsText__OnSetString( &_this->CaptionText, value );
}

/* 'C' function for method : 'Components::RoundTextButton.OnSetFont()' */
void ComponentsRoundTextButton_OnSetFont( ComponentsRoundTextButton _this, ResourcesFont 
  value )
{
  if ( _this->Font == value )
    return;

  _this->Font = value;
  ViewsText__OnSetFont( &_this->CaptionText, value );
}

/* Variants derived from the class : 'Components::RoundTextButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsRoundTextButton )
EW_END_OF_CLASS_VARIANTS( ComponentsRoundTextButton )

/* Virtual Method Table (VMT) for the class : 'Components::RoundTextButton' */
EW_DEFINE_CLASS( ComponentsRoundTextButton, ComponentsRoundButton, CaptionText, 
                 Font, Caption, Caption, Caption, CaptionColor, "Components::RoundTextButton" )
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
  ComponentsRoundButton_UpdateLayout,
  ComponentsRoundTextButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsBaseButton_onActivate,
EW_END_OF_CLASS( ComponentsRoundTextButton )

/* Initializer for the class 'Components::RoundRadioButton' */
void ComponentsRoundRadioButton__Init( ComponentsRoundRadioButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsRoundTextButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsRoundRadioButton );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsRoundRadioButton );

  /* ... and initialize objects, variables, properties, etc. */
  ComponentsBaseButton_OnSetBgColor((ComponentsBaseButton)_this, ResOnSecondary );
  ComponentsBaseButton_OnSetBgColorPressed((ComponentsBaseButton)_this, ResOnSecondary );
  _this->BgColorSelected = ResOnPrimary;
}

/* Re-Initializer for the class 'Components::RoundRadioButton' */
void ComponentsRoundRadioButton__ReInit( ComponentsRoundRadioButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsRoundTextButton__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::RoundRadioButton' */
void ComponentsRoundRadioButton__Done( ComponentsRoundRadioButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsRoundTextButton );

  /* Don't forget to deinitialize the super class ... */
  ComponentsRoundTextButton__Done( &_this->_.Super );
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
void ComponentsRoundRadioButton_UpdateViewState( ComponentsRoundRadioButton _this, 
  XSet aState )
{
  ComponentsRoundTextButton_UpdateViewState((ComponentsRoundTextButton)_this, aState );

  if ( _this->Selected )
    ViewsRectangle_OnSetColor( &_this->Super3.Background, _this->BgColorSelected );
}

/* 'C' function for method : 'Components::RoundRadioButton.onActivate()' */
void ComponentsRoundRadioButton_onActivate( ComponentsRoundRadioButton _this, XObject 
  sender )
{
  ComponentsBaseButton_onActivate((ComponentsBaseButton)_this, sender );

  if ( !_this->Selected )
  {
    ComponentsRoundRadioButton_OnSetSelected( _this, 1 );

    if ( _this->Outlet.Object != 0 )
    {
      EwOnSetInt32( _this->Outlet, _this->OutletSelector );
      EwNotifyRefObservers( _this->Outlet, 0 );
    }
  }
}

/* This slot method will receive a signal, if the value of the property assigned 
   to @Outlet has been changed by another widget or by the application logic. In 
   response to this notification, the widget will update itself. */
void ComponentsRoundRadioButton_onOutlet( ComponentsRoundRadioButton _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Outlet.Object != 0 )
    ComponentsRoundRadioButton_OnSetSelected( _this, (XBool)( EwOnGetInt32( _this->Outlet ) 
    == _this->OutletSelector ));
}

/* 'C' function for method : 'Components::RoundRadioButton.OnSetOutletSelector()' */
void ComponentsRoundRadioButton_OnSetOutletSelector( ComponentsRoundRadioButton _this, 
  XInt32 value )
{
  if ( _this->OutletSelector == value )
    return;

  _this->OutletSelector = value;

  if ( _this->Outlet.Object != 0 )
    ComponentsRoundRadioButton_OnSetSelected( _this, (XBool)( EwOnGetInt32( _this->Outlet ) 
    == _this->OutletSelector ));
}

/* Wrapper function for the virtual method : 'Components::RoundRadioButton.OnSetOutletSelector()' */
void ComponentsRoundRadioButton__OnSetOutletSelector( void* _this, XInt32 value )
{
  ((ComponentsRoundRadioButton)_this)->_.VMT->OnSetOutletSelector((ComponentsRoundRadioButton)_this
  , value );
}

/* 'C' function for method : 'Components::RoundRadioButton.OnSetOutlet()' */
void ComponentsRoundRadioButton_OnSetOutlet( ComponentsRoundRadioButton _this, XRef 
  value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  if ( _this->Outlet.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsRoundRadioButton_onOutlet ), 
      _this->Outlet, 0 );

  _this->Outlet = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsRoundRadioButton_onOutlet ), 
      value, 0 );

  if ( value.Object != 0 )
    EwPostSignal( EwNewSlot( _this, ComponentsRoundRadioButton_onOutlet ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::RoundRadioButton.OnSetSelected()' */
void ComponentsRoundRadioButton_OnSetSelected( ComponentsRoundRadioButton _this, 
  XBool value )
{
  if ( _this->Selected == value )
    return;

  _this->Selected = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* Variants derived from the class : 'Components::RoundRadioButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsRoundRadioButton )
EW_END_OF_CLASS_VARIANTS( ComponentsRoundRadioButton )

/* Virtual Method Table (VMT) for the class : 'Components::RoundRadioButton' */
EW_DEFINE_CLASS( ComponentsRoundRadioButton, ComponentsRoundTextButton, Outlet, 
                 Outlet, Outlet, Outlet, OutletSelector, OutletSelector, "Components::RoundRadioButton" )
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
  ComponentsRoundButton_UpdateLayout,
  ComponentsRoundRadioButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsRoundRadioButton_onActivate,
  ComponentsRoundRadioButton_OnSetOutletSelector,
EW_END_OF_CLASS( ComponentsRoundRadioButton )

/* Initializer for the class 'Components::PressureSettingButton' */
void ComponentsPressureSettingButton__Init( ComponentsPressureSettingButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsRoundRadioButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsPressureSettingButton );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsPressureSettingButton );

  /* ... and initialize objects, variables, properties, etc. */
  ComponentsRoundTextButton_OnSetFont((ComponentsRoundTextButton)_this, EwLoadResource( 
  &FontsMediumLarge, ResourcesFont ));

  /* Call the user defined constructor */
  ComponentsPressureSettingButton_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::PressureSettingButton' */
void ComponentsPressureSettingButton__ReInit( ComponentsPressureSettingButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsRoundRadioButton__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::PressureSettingButton' */
void ComponentsPressureSettingButton__Done( ComponentsPressureSettingButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsRoundRadioButton );

  /* Don't forget to deinitialize the super class ... */
  ComponentsRoundRadioButton__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ComponentsPressureSettingButton_Init( ComponentsPressureSettingButton _this, 
  XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* 'C' function for method : 'Components::PressureSettingButton.OnSetOutletSelector()' */
void ComponentsPressureSettingButton_OnSetOutletSelector( ComponentsPressureSettingButton _this, 
  XInt32 value )
{
  ComponentsRoundRadioButton_OnSetOutletSelector((ComponentsRoundRadioButton)_this, 
  value );
  ComponentsRoundTextButton_OnSetCaption((ComponentsRoundTextButton)_this, EwNewStringInt( 
  value, 0, 10 ));
}

/* Variants derived from the class : 'Components::PressureSettingButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsPressureSettingButton )
EW_END_OF_CLASS_VARIANTS( ComponentsPressureSettingButton )

/* Virtual Method Table (VMT) for the class : 'Components::PressureSettingButton' */
EW_DEFINE_CLASS( ComponentsPressureSettingButton, ComponentsRoundRadioButton, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "Components::PressureSettingButton" )
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
  ComponentsRoundButton_UpdateLayout,
  ComponentsRoundRadioButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsRoundRadioButton_onActivate,
  ComponentsPressureSettingButton_OnSetOutletSelector,
EW_END_OF_CLASS( ComponentsPressureSettingButton )

/* Initializer for the class 'Components::ValueRangeDisplay' */
void ComponentsValueRangeDisplay__Init( ComponentsValueRangeDisplay _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsValueDisplay__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsValueRangeDisplay );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsValueRangeDisplay );

  /* ... and initialize objects, variables, properties, etc. */
  _this->MaxValue = 100;
  _this->Precision = -1;

  /* Call the user defined constructor */
  ComponentsValueRangeDisplay_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::ValueRangeDisplay' */
void ComponentsValueRangeDisplay__ReInit( ComponentsValueRangeDisplay _this )
{
  /* At first re-initialize the super class ... */
  ComponentsValueDisplay__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::ValueRangeDisplay' */
void ComponentsValueRangeDisplay__Done( ComponentsValueRangeDisplay _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsValueDisplay );

  /* Don't forget to deinitialize the super class ... */
  ComponentsValueDisplay__Done( &_this->_.Super );
}

/* 'C' function for method : 'Components::ValueRangeDisplay.Init()' */
void ComponentsValueRangeDisplay_Init( ComponentsValueRangeDisplay _this, XHandle 
  aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  EwPostSignal( EwNewSlot( _this, ComponentsValueRangeDisplay_formatRange ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::ValueRangeDisplay.OnSetMinValue()' */
void ComponentsValueRangeDisplay_OnSetMinValue( ComponentsValueRangeDisplay _this, 
  XInt32 value )
{
  if ( _this->MinValue == value )
    return;

  _this->MinValue = value;
  EwPostSignal( EwNewSlot( _this, ComponentsValueRangeDisplay_formatRange ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::ValueRangeDisplay.formatRange()' */
void ComponentsValueRangeDisplay_formatRange( ComponentsValueRangeDisplay _this, 
  XObject sender )
{
  XString str;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  str = EwConcatString( EwConcatString( ToolsHelperCollection_FormatInt32Value( 
  EwGetAutoObject( &ToolsHelper, ToolsHelperCollection ), _this->MinValue, _this->Resolution, 
  _this->Precision ), EwLoadString( &_Const0075 )), ToolsHelperCollection_FormatInt32Value( 
  EwGetAutoObject( &ToolsHelper, ToolsHelperCollection ), _this->MaxValue, _this->Resolution, 
  _this->Precision ));

  if ( EwCompString( _this->Unit, 0 ) != 0 )
    str = EwConcatString( str, EwConcatString( EwLoadString( &_Const0076 ), _this->Unit ));

  ViewsText__OnSetString( _this, str );
}

/* 'C' function for method : 'Components::ValueRangeDisplay.OnSetResolution()' */
void ComponentsValueRangeDisplay_OnSetResolution( ComponentsValueRangeDisplay _this, 
  XInt32 value )
{
  if ( _this->Resolution == value )
    return;

  _this->Resolution = value;
  EwPostSignal( EwNewSlot( _this, ComponentsValueRangeDisplay_formatRange ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::ValueRangeDisplay.OnSetMaxValue()' */
void ComponentsValueRangeDisplay_OnSetMaxValue( ComponentsValueRangeDisplay _this, 
  XInt32 value )
{
  if ( _this->MaxValue == value )
    return;

  _this->MaxValue = value;
  EwPostSignal( EwNewSlot( _this, ComponentsValueRangeDisplay_formatRange ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::ValueRangeDisplay.OnSetUnit()' */
void ComponentsValueRangeDisplay_OnSetUnit( ComponentsValueRangeDisplay _this, XString 
  value )
{
  if ( !EwCompString( _this->Unit, value ))
    return;

  _this->Unit = EwShareString( value );
  EwPostSignal( EwNewSlot( _this, ComponentsValueRangeDisplay_formatRange ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::ValueRangeDisplay.OnSetPrecision()' */
void ComponentsValueRangeDisplay_OnSetPrecision( ComponentsValueRangeDisplay _this, 
  XInt32 value )
{
  if ( _this->Precision == value )
    return;

  _this->Precision = value;
  EwPostSignal( EwNewSlot( _this, ComponentsValueRangeDisplay_formatRange ), ((XObject)_this ));
}

/* Variants derived from the class : 'Components::ValueRangeDisplay' */
EW_DEFINE_CLASS_VARIANTS( ComponentsValueRangeDisplay )
EW_END_OF_CLASS_VARIANTS( ComponentsValueRangeDisplay )

/* Virtual Method Table (VMT) for the class : 'Components::ValueRangeDisplay' */
EW_DEFINE_CLASS( ComponentsValueRangeDisplay, ComponentsValueDisplay, Unit, Unit, 
                 Unit, Unit, Unit, MinValue, "Components::ValueRangeDisplay" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  ViewsText_Draw,
  CoreView_GetClipping,
  CoreView_HandleEvent,
  CoreView_CursorHitTest,
  CoreView_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreView_ChangeViewState,
  ComponentsValueDisplay_OnSetBounds,
  ComponentsValueDisplay_OnSetString,
  ComponentsValueDisplay_OnSetFont,
EW_END_OF_CLASS( ComponentsValueRangeDisplay )

/* Initializer for the class 'Components::SettingItem' */
void ComponentsSettingItem__Init( ComponentsSettingItem _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsSettingItem );

  /* ... then construct all embedded objects */
  ViewsText__Init( &_this->CaptionText, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->ValueBg, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsSettingItem );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0077 );
  CoreRectView__OnSetBounds( &_this->CaptionText, _Const0078 );
  ViewsText_OnSetOverflowWarning( &_this->CaptionText, 1 );
  ViewsText_OnSetAlignment( &_this->CaptionText, ViewsTextAlignmentAlignHorzRight 
  | ViewsTextAlignmentAlignVertCenter );
  ViewsText__OnSetString( &_this->CaptionText, EwLoadString( &_Const0006 ));
  CoreRectView__OnSetBounds( &_this->ValueBg, _Const0079 );
  ViewsRectangle_OnSetRadius( &_this->ValueBg, 16 );
  ViewsRectangle_OnSetColor( &_this->ValueBg, ResSurface1 );
  _this->ValueAreaWith = 261;
  _this->ValuePadding = 24;
  _this->CaptionValueSpace = 45;
  CoreGroup__Add( _this, ((CoreView)&_this->CaptionText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ValueBg ), 0 );
  ViewsText__OnSetFont( &_this->CaptionText, EwLoadResource( &FontsBody18, ResourcesFont ));
}

/* Re-Initializer for the class 'Components::SettingItem' */
void ComponentsSettingItem__ReInit( ComponentsSettingItem _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsText__ReInit( &_this->CaptionText );
  ViewsRectangle__ReInit( &_this->ValueBg );
}

/* Finalizer method for the class 'Components::SettingItem' */
void ComponentsSettingItem__Done( ComponentsSettingItem _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Finalize all embedded objects */
  ViewsText__Done( &_this->CaptionText );
  ViewsRectangle__Done( &_this->ValueBg );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsSettingItem_UpdateLayout( ComponentsSettingItem _this, XPoint aSize )
{
  CoreGroup_UpdateLayout((CoreGroup)_this, aSize );
  CoreRectView__OnSetBounds( &_this->ValueBg, EwSetRectX( _this->ValueBg.Super1.Bounds, 
  aSize.X - _this->ValueAreaWith ));
  CoreRectView__OnSetBounds( &_this->ValueBg, EwSetRectW( _this->ValueBg.Super1.Bounds, 
  _this->ValueAreaWith ));
  CoreRectView__OnSetBounds( &_this->ValueBg, EwSetRectH( _this->ValueBg.Super1.Bounds, 
  aSize.Y ));
  CoreRectView__OnSetBounds( &_this->CaptionText, EwSetRectX2( _this->CaptionText.Super1.Bounds, 
  _this->ValueBg.Super1.Bounds.Point1.X - _this->CaptionValueSpace ));
  CoreRectView__OnSetBounds( &_this->CaptionText, EwSetRectH( _this->CaptionText.Super1.Bounds, 
  aSize.Y ));
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
void ComponentsSettingItem_UpdateViewState( ComponentsSettingItem _this, XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ViewsText_OnSetColor( &_this->CaptionText, ResOnPrimary );
  ViewsRectangle_OnSetColor( &_this->ValueBg, ResSurface1 );
}

/* 'C' function for method : 'Components::SettingItem.OnSetCaption()' */
void ComponentsSettingItem_OnSetCaption( ComponentsSettingItem _this, XString value )
{
  if ( !EwCompString( _this->Caption, value ))
    return;

  _this->Caption = EwShareString( value );
  ViewsText__OnSetString( &_this->CaptionText, value );
}

/* 'C' function for method : 'Components::SettingItem.OnSetValueAreaWith()' */
void ComponentsSettingItem_OnSetValueAreaWith( ComponentsSettingItem _this, XInt32 
  value )
{
  if ( _this->ValueAreaWith == value )
    return;

  _this->ValueAreaWith = value;
  CoreGroup_InvalidateLayout((CoreGroup)_this );
}

/* 'C' function for method : 'Components::SettingItem.OnSetValuePadding()' */
void ComponentsSettingItem_OnSetValuePadding( ComponentsSettingItem _this, XInt32 
  value )
{
  if ( _this->ValuePadding == value )
    return;

  _this->ValuePadding = value;
  CoreGroup_InvalidateLayout((CoreGroup)_this );
}

/* 'C' function for method : 'Components::SettingItem.updateValueDisplay()' */
void ComponentsSettingItem_updateValueDisplay( ComponentsSettingItem _this, ComponentsValueDisplay 
  aValueDisplay )
{
  /* List of temporarily used variables */
  XRect _tmpK0;
  if ( aValueDisplay == 0 )
    return;

  CoreRectView__OnSetBounds( aValueDisplay, _this->ValueBg.Super1.Bounds );
  ((void)( _tmpK0 = aValueDisplay->Super2.Bounds ), CoreRectView__OnSetBounds( aValueDisplay, 
  EwSetRectX1( _tmpK0, _tmpK0.Point1.X + _this->ValuePadding )));
  ((void)( _tmpK0 = aValueDisplay->Super2.Bounds ), CoreRectView__OnSetBounds( aValueDisplay, 
  EwSetRectX2( _tmpK0, _tmpK0.Point2.X - _this->ValuePadding )));
}

/* 'C' function for method : 'Components::SettingItem.OnSetCaptionValueSpace()' */
void ComponentsSettingItem_OnSetCaptionValueSpace( ComponentsSettingItem _this, 
  XInt32 value )
{
  if ( _this->CaptionValueSpace == value )
    return;

  _this->CaptionValueSpace = value;
  CoreGroup_InvalidateLayout((CoreGroup)_this );
}

/* Variants derived from the class : 'Components::SettingItem' */
EW_DEFINE_CLASS_VARIANTS( ComponentsSettingItem )
EW_END_OF_CLASS_VARIANTS( ComponentsSettingItem )

/* Virtual Method Table (VMT) for the class : 'Components::SettingItem' */
EW_DEFINE_CLASS( ComponentsSettingItem, CoreGroup, CaptionText, Caption, Caption, 
                 Caption, Caption, ValueAreaWith, "Components::SettingItem" )
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
  ComponentsSettingItem_UpdateLayout,
  ComponentsSettingItem_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsSettingItem )

/* Initializer for the class 'Components::IntSettingItem' */
void ComponentsIntSettingItem__Init( ComponentsIntSettingItem _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsSettingItem__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsIntSettingItem );

  /* ... then construct all embedded objects */
  ComponentsIntValueDisplay__Init( &_this->ValueDisplay, &_this->_.XObject, 0 );
  ComponentsValueRangeDisplay__Init( &_this->ValueRangeDisplay, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsIntSettingItem );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const007A );
  CoreRectView__OnSetBounds( &_this->Super1.CaptionText, _Const007B );
  ComponentsSettingItem_OnSetValueAreaWith((ComponentsSettingItem)_this, 122 );
  CoreView_OnSetLayout((CoreView)&_this->ValueDisplay, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToRight | CoreLayoutAlignToTop );
  CoreRectView__OnSetBounds( &_this->ValueDisplay, _Const007C );
  CoreView_OnSetLayout((CoreView)&_this->ValueRangeDisplay, CoreLayoutAlignToBottom 
  | CoreLayoutAlignToRight | CoreLayoutAlignToTop );
  CoreRectView__OnSetBounds( &_this->ValueRangeDisplay, _Const007D );
  ViewsText_OnSetAlignment((ViewsText)&_this->ValueRangeDisplay, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  _this->MaxValue = 100;
  _this->Precision = -1;
  CoreGroup__Add( _this, ((CoreView)&_this->ValueDisplay ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ValueRangeDisplay ), 0 );
  ViewsText__OnSetFont( &_this->Super1.CaptionText, EwLoadResource( &FontsHeading3, 
  ResourcesFont ));
  ViewsText__OnSetFont( &_this->ValueDisplay, EwLoadResource( &FontsHeading2, ResourcesFont ));
  ViewsText__OnSetFont( &_this->ValueRangeDisplay, EwLoadResource( &FontsBody16, 
  ResourcesFont ));
}

/* Re-Initializer for the class 'Components::IntSettingItem' */
void ComponentsIntSettingItem__ReInit( ComponentsIntSettingItem _this )
{
  /* At first re-initialize the super class ... */
  ComponentsSettingItem__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsIntValueDisplay__ReInit( &_this->ValueDisplay );
  ComponentsValueRangeDisplay__ReInit( &_this->ValueRangeDisplay );
}

/* Finalizer method for the class 'Components::IntSettingItem' */
void ComponentsIntSettingItem__Done( ComponentsIntSettingItem _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsSettingItem );

  /* Finalize all embedded objects */
  ComponentsIntValueDisplay__Done( &_this->ValueDisplay );
  ComponentsValueRangeDisplay__Done( &_this->ValueRangeDisplay );

  /* Don't forget to deinitialize the super class ... */
  ComponentsSettingItem__Done( &_this->_.Super );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsIntSettingItem_UpdateLayout( ComponentsIntSettingItem _this, XPoint 
  aSize )
{
  ComponentsSettingItem_UpdateLayout((ComponentsSettingItem)_this, aSize );
  CoreRectView__OnSetBounds( &_this->Super1.ValueBg, EwSetRectY2( _this->Super1.ValueBg.Super1.Bounds, 
  aSize.Y - EwGetRectH( _this->ValueRangeDisplay.Super3.Bounds )));
  ComponentsSettingItem_updateValueDisplay((ComponentsSettingItem)_this, ((ComponentsValueDisplay)&_this->ValueDisplay ));
  CoreRectView__OnSetBounds( &_this->ValueRangeDisplay, EwSetRectY( _this->ValueRangeDisplay.Super3.Bounds, 
  _this->Super1.ValueBg.Super1.Bounds.Point2.Y ));
  CoreRectView__OnSetBounds( &_this->ValueRangeDisplay, EwSetRectX1( _this->ValueRangeDisplay.Super3.Bounds, 
  _this->Super1.ValueBg.Super1.Bounds.Point1.X ));
  CoreRectView__OnSetBounds( &_this->ValueRangeDisplay, EwSetRectX2( _this->ValueRangeDisplay.Super3.Bounds, 
  _this->Super1.ValueBg.Super1.Bounds.Point2.X ));
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
void ComponentsIntSettingItem_UpdateViewState( ComponentsIntSettingItem _this, XSet 
  aState )
{
  ComponentsSettingItem_UpdateViewState((ComponentsSettingItem)_this, aState );
  ViewsText_OnSetColor((ViewsText)&_this->ValueDisplay, ResOnPrimary );
  ViewsText_OnSetColor((ViewsText)&_this->ValueRangeDisplay, ResOnPrimary );
}

/* 'C' function for method : 'Components::IntSettingItem.OnSetOutlet()' */
void ComponentsIntSettingItem_OnSetOutlet( ComponentsIntSettingItem _this, XRef 
  value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  _this->Outlet = value;
  ComponentsIntValueDisplay_OnSetOutlet( &_this->ValueDisplay, value );
}

/* 'C' function for method : 'Components::IntSettingItem.OnSetResolution()' */
void ComponentsIntSettingItem_OnSetResolution( ComponentsIntSettingItem _this, XInt32 
  value )
{
  if ( _this->Resolution == value )
    return;

  _this->Resolution = value;
  ComponentsIntValueDisplay_OnSetResolution( &_this->ValueDisplay, value );
  ComponentsValueRangeDisplay_OnSetResolution( &_this->ValueRangeDisplay, value );
}

/* 'C' function for method : 'Components::IntSettingItem.OnSetMinValue()' */
void ComponentsIntSettingItem_OnSetMinValue( ComponentsIntSettingItem _this, XInt32 
  value )
{
  if ( _this->MinValue == value )
    return;

  _this->MinValue = value;
  ComponentsValueRangeDisplay_OnSetMinValue( &_this->ValueRangeDisplay, value );
}

/* 'C' function for method : 'Components::IntSettingItem.OnSetMaxValue()' */
void ComponentsIntSettingItem_OnSetMaxValue( ComponentsIntSettingItem _this, XInt32 
  value )
{
  if ( _this->MaxValue == value )
    return;

  _this->MaxValue = value;
  ComponentsValueRangeDisplay_OnSetMaxValue( &_this->ValueRangeDisplay, value );
}

/* 'C' function for method : 'Components::IntSettingItem.OnSetUnit()' */
void ComponentsIntSettingItem_OnSetUnit( ComponentsIntSettingItem _this, XString 
  value )
{
  if ( !EwCompString( _this->Unit, value ))
    return;

  _this->Unit = EwShareString( value );
  ComponentsValueRangeDisplay_OnSetUnit( &_this->ValueRangeDisplay, value );
}

/* 'C' function for method : 'Components::IntSettingItem.OnSetPrecision()' */
void ComponentsIntSettingItem_OnSetPrecision( ComponentsIntSettingItem _this, XInt32 
  value )
{
  if ( _this->Precision == value )
    return;

  _this->Precision = value;
  ComponentsIntValueDisplay_OnSetPrecision( &_this->ValueDisplay, value );
  ComponentsValueRangeDisplay_OnSetPrecision( &_this->ValueRangeDisplay, value );
}

/* Variants derived from the class : 'Components::IntSettingItem' */
EW_DEFINE_CLASS_VARIANTS( ComponentsIntSettingItem )
EW_END_OF_CLASS_VARIANTS( ComponentsIntSettingItem )

/* Virtual Method Table (VMT) for the class : 'Components::IntSettingItem' */
EW_DEFINE_CLASS( ComponentsIntSettingItem, ComponentsSettingItem, ValueDisplay, 
                 Outlet, Outlet, Outlet, Unit, Resolution, "Components::IntSettingItem" )
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
  ComponentsIntSettingItem_UpdateLayout,
  ComponentsIntSettingItem_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsIntSettingItem )

/* Initializer for the class 'Components::VertScrollbar' */
void ComponentsVertScrollbar__Init( ComponentsVertScrollbar _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  TemplatesVerticalScrollbar__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsVertScrollbar );

  /* ... then construct all embedded objects */
  CoreTimer__Init( &_this->ActiveTimer, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->Track, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->Thumb, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsVertScrollbar );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const007E );
  CoreGroup_OnSetEnabled((CoreGroup)_this, 0 );
  CoreTimer_OnSetPeriod( &_this->ActiveTimer, 0 );
  CoreTimer_OnSetBegin( &_this->ActiveTimer, 500 );
  CoreView_OnSetLayout((CoreView)&_this->Track, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->Track, _Const007E );
  ViewsRectangle_OnSetRadius( &_this->Track, 4 );
  CoreView_OnSetLayout((CoreView)&_this->Thumb, 0 );
  CoreRectView__OnSetBounds( &_this->Thumb, _Const007F );
  ViewsRectangle_OnSetRadius( &_this->Thumb, 4 );
  _this->ViewArea = 10;
  _this->ContentArea = 100;
  CoreGroup__Add( _this, ((CoreView)&_this->Track ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Thumb ), 0 );
  _this->ActiveTimer.OnTrigger = EwNewSlot( _this, ComponentsVertScrollbar_onActiveTimer );
}

/* Re-Initializer for the class 'Components::VertScrollbar' */
void ComponentsVertScrollbar__ReInit( ComponentsVertScrollbar _this )
{
  /* At first re-initialize the super class ... */
  TemplatesVerticalScrollbar__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreTimer__ReInit( &_this->ActiveTimer );
  ViewsRectangle__ReInit( &_this->Track );
  ViewsRectangle__ReInit( &_this->Thumb );
}

/* Finalizer method for the class 'Components::VertScrollbar' */
void ComponentsVertScrollbar__Done( ComponentsVertScrollbar _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( TemplatesVerticalScrollbar );

  /* Finalize all embedded objects */
  CoreTimer__Done( &_this->ActiveTimer );
  ViewsRectangle__Done( &_this->Track );
  ViewsRectangle__Done( &_this->Thumb );

  /* Don't forget to deinitialize the super class ... */
  TemplatesVerticalScrollbar__Done( &_this->_.Super );
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
void ComponentsVertScrollbar_UpdateViewState( ComponentsVertScrollbar _this, XSet 
  aState )
{
  XBool isActive;
  XInt32 bottomEdge;
  XInt32 minThumbSize;
  XInt32 thumbSize;
  XInt32 thumbPos;

  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ViewsRectangle_OnSetColor( &_this->Track, ResSurface1 );
  ViewsRectangle_OnSetColor( &_this->Thumb, ResSurface3 );
  isActive = _this->ActiveTimer.Enabled;
  bottomEdge = EwGetRectH( _this->Super3.Bounds );
  minThumbSize = 8;
  thumbSize = bottomEdge;
  thumbPos = 0;

  if ( 8 > bottomEdge )
    minThumbSize = bottomEdge;

  if ( _this->ViewArea < _this->ContentArea )
    thumbSize = ( thumbSize * _this->ViewArea ) / _this->ContentArea;

  if ( thumbSize < minThumbSize )
    thumbSize = minThumbSize;

  if ( _this->ViewArea < _this->ContentArea )
    thumbPos = ( ComponentsVertScrollbar_OnGetPosition( _this ) * ( bottomEdge - 
    thumbSize )) / ( _this->ContentArea - _this->ViewArea );

  CoreRectView__OnSetBounds( &_this->Thumb, EwSetRectY1( _this->Thumb.Super1.Bounds, 
  thumbPos ));
  CoreRectView__OnSetBounds( &_this->Thumb, EwSetRectY2( _this->Thumb.Super1.Bounds, 
  thumbPos + thumbSize ));
  ViewsRectangle_OnSetVisible( &_this->Track, isActive );
  ViewsRectangle_OnSetVisible( &_this->Thumb, isActive );
  _this->active = isActive;
}

/* This internal slot method is called when the '@ActiveTimer' is expired. It forces 
   the scrollbar to disappear again. */
void ComponentsVertScrollbar_onActiveTimer( ComponentsVertScrollbar _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'Components::VertScrollbar.OnGetPosition()' */
XInt32 ComponentsVertScrollbar_OnGetPosition( ComponentsVertScrollbar _this )
{
  XInt32 value = _this->Position;
  XInt32 range = _this->ContentArea - _this->ViewArea;

  if (( range > 0 ) && ( value > range ))
    value = range;

  if ( range <= 0 )
    value = 0;

  return value;
}

/* 'C' function for method : 'Components::VertScrollbar.OnSetPosition()' */
void ComponentsVertScrollbar_OnSetPosition( ComponentsVertScrollbar _this, XInt32 
  value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->Position == value )
    return;

  _this->Position = value;
  CoreTimer_OnSetEnabled( &_this->ActiveTimer, 0 );
  CoreTimer_OnSetEnabled( &_this->ActiveTimer, (XBool)( _this->ContentArea > _this->ViewArea ));
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'Components::VertScrollbar.OnSetViewArea()' */
void ComponentsVertScrollbar_OnSetViewArea( ComponentsVertScrollbar _this, XInt32 
  value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->ViewArea == value )
    return;

  _this->ViewArea = value;
  CoreTimer_OnSetEnabled( &_this->ActiveTimer, 0 );
  CoreTimer_OnSetEnabled( &_this->ActiveTimer, (XBool)( _this->ContentArea > _this->ViewArea ));
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'Components::VertScrollbar.OnSetContentArea()' */
void ComponentsVertScrollbar_OnSetContentArea( ComponentsVertScrollbar _this, XInt32 
  value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->ContentArea == value )
    return;

  _this->ContentArea = value;
  CoreTimer_OnSetEnabled( &_this->ActiveTimer, 0 );
  CoreTimer_OnSetEnabled( &_this->ActiveTimer, (XBool)( _this->ContentArea > _this->ViewArea ));
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* Variants derived from the class : 'Components::VertScrollbar' */
EW_DEFINE_CLASS_VARIANTS( ComponentsVertScrollbar )
EW_END_OF_CLASS_VARIANTS( ComponentsVertScrollbar )

/* Virtual Method Table (VMT) for the class : 'Components::VertScrollbar' */
EW_DEFINE_CLASS( ComponentsVertScrollbar, TemplatesVerticalScrollbar, ActiveTimer, 
                 Position, Position, Position, Position, Position, "Components::VertScrollbar" )
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
  ComponentsVertScrollbar_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsVertScrollbar )

/* Initializer for the class 'Components::SettingsOpenButton' */
void ComponentsSettingsOpenButton__Init( ComponentsSettingsOpenButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsSettingsButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsSettingsOpenButton );

  /* ... then construct all embedded objects */
  ViewsRectangle__Init( &_this->IconBackground, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->OpenImage, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsSettingsOpenButton );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0080 );
  CoreView_OnSetLayout((CoreView)&_this->IconBackground, CoreLayoutAlignToBottom 
  | CoreLayoutAlignToLeft | CoreLayoutAlignToTop | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->IconBackground, _Const0081 );
  ViewsRectangle_OnSetRadius( &_this->IconBackground, 8 );
  ViewsRectangle_OnSetColor( &_this->IconBackground, ResBlue );
  ViewsRectangle_OnSetVisible( &_this->IconBackground, 0 );
  CoreRectView__OnSetBounds( &_this->Super2.Image, _Const0082 );
  CoreRectView__OnSetBounds( &_this->OpenImage, _Const0083 );
  _this->IconBgColor = ResBlue;
  CoreGroup__Add( _this, ((CoreView)&_this->IconBackground ), -1 );
  CoreGroup__Add( _this, ((CoreView)&_this->OpenImage ), 0 );
  ViewsImage_OnSetBitmap( &_this->OpenImage, EwLoadResource( &Reschevron_right, 
  ResourcesBitmap ));
}

/* Re-Initializer for the class 'Components::SettingsOpenButton' */
void ComponentsSettingsOpenButton__ReInit( ComponentsSettingsOpenButton _this )
{
  /* At first re-initialize the super class ... */
  ComponentsSettingsButton__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsRectangle__ReInit( &_this->IconBackground );
  ViewsImage__ReInit( &_this->OpenImage );
}

/* Finalizer method for the class 'Components::SettingsOpenButton' */
void ComponentsSettingsOpenButton__Done( ComponentsSettingsOpenButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsSettingsButton );

  /* Finalize all embedded objects */
  ViewsRectangle__Done( &_this->IconBackground );
  ViewsImage__Done( &_this->OpenImage );

  /* Don't forget to deinitialize the super class ... */
  ComponentsSettingsButton__Done( &_this->_.Super );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsSettingsOpenButton_UpdateLayout( ComponentsSettingsOpenButton _this, 
  XPoint aSize )
{
  ComponentsSettingsButton_UpdateLayout((ComponentsSettingsButton)_this, aSize );
  ViewsText_OnSetAlignment( &_this->Super3.CaptionText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  CoreRectView__OnSetBounds( &_this->Super3.CaptionText, EwSetRectX1( _this->Super3.CaptionText.Super1.Bounds, 
  _this->IconBackground.Super1.Bounds.Point2.X + 16 ));
  CoreRectView__OnSetBounds( &_this->Super3.CaptionText, EwSetRectX2( _this->Super3.CaptionText.Super1.Bounds, 
  aSize.X - 16 ));
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
void ComponentsSettingsOpenButton_UpdateViewState( ComponentsSettingsOpenButton _this, 
  XSet aState )
{
  ComponentsIconTextButton_UpdateViewState((ComponentsIconTextButton)_this, aState );
  ViewsImage_OnSetColor( &_this->OpenImage, _this->Super3.CaptionText.Color );
  ViewsRectangle_OnSetColor( &_this->IconBackground, _this->IconBgColor );
}

/* 'C' function for method : 'Components::SettingsOpenButton.onActivate()' */
void ComponentsSettingsOpenButton_onActivate( ComponentsSettingsOpenButton _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Super1.SettingsPage != DeviceSettingsPageNone )
    DeviceDeviceClass_OnSetCurrentSubSettings( EwGetAutoObject( &DeviceDevice, DeviceDeviceClass ), 
    _this->Super1.SettingsPage );

  EwPostSignal( _this->Super4.OnActivate, ((XObject)_this ));
}

/* 'C' function for method : 'Components::SettingsOpenButton.OnSetIconBgColor()' */
void ComponentsSettingsOpenButton_OnSetIconBgColor( ComponentsSettingsOpenButton _this, 
  XColor value )
{
  if ( !EwCompColor( _this->IconBgColor, value ))
    return;

  _this->IconBgColor = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* Variants derived from the class : 'Components::SettingsOpenButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsSettingsOpenButton )
EW_END_OF_CLASS_VARIANTS( ComponentsSettingsOpenButton )

/* Virtual Method Table (VMT) for the class : 'Components::SettingsOpenButton' */
EW_DEFINE_CLASS( ComponentsSettingsOpenButton, ComponentsSettingsButton, IconBackground, 
                 IconBgColor, IconBgColor, IconBgColor, IconBgColor, IconBgColor, 
                 "Components::SettingsOpenButton" )
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
  ComponentsSettingsOpenButton_UpdateLayout,
  ComponentsSettingsOpenButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  ComponentsSettingsOpenButton_onActivate,
  ComponentsIconTextButton_OnSetCaption,
EW_END_OF_CLASS( ComponentsSettingsOpenButton )

/* Initializer for the class 'Components::ToggleButton' */
void ComponentsToggleButton__Init( ComponentsToggleButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  TemplatesToggleButton__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsToggleButton );

  /* ... then construct all embedded objects */
  CoreTimer__Init( &_this->FlashTimer, &_this->_.XObject, 0 );
  CoreKeyPressHandler__Init( &_this->KeyHandler, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->Background, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->Knob, &_this->_.XObject, 0 );
  CoreSimpleTouchHandler__Init( &_this->TouchHandler, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsToggleButton );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0084 );
  CoreTimer_OnSetPeriod( &_this->FlashTimer, 0 );
  CoreTimer_OnSetBegin( &_this->FlashTimer, 50 );
  _this->KeyHandler.Filter = CoreKeyCodeEnter;
  CoreView_OnSetLayout((CoreView)&_this->Background, CoreLayoutAlignToBottom | CoreLayoutAlignToLeft 
  | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->Background, _Const0084 );
  ViewsRectangle_OnSetRadius( &_this->Background, 10 );
  CoreView_OnSetLayout((CoreView)&_this->Knob, CoreLayoutAlignToBottom | CoreLayoutAlignToTop 
  | CoreLayoutResizeHorz | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->Knob, _Const0085 );
  ViewsRectangle_OnSetColor( &_this->Knob, _Const0086 );
  CoreView_OnSetLayout((CoreView)&_this->TouchHandler, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToLeft | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz 
  | CoreLayoutResizeVert );
  CoreQuadView__OnSetPoint4( &_this->TouchHandler, _Const0087 );
  CoreQuadView__OnSetPoint3( &_this->TouchHandler, _Const0088 );
  CoreQuadView__OnSetPoint2( &_this->TouchHandler, _Const0089 );
  CoreQuadView__OnSetPoint1( &_this->TouchHandler, _Const0004 );
  _this->TouchHandler.RetargetCondition = CoreRetargetReasonWipeDown | CoreRetargetReasonWipeLeft 
  | CoreRetargetReasonWipeRight | CoreRetargetReasonWipeUp;
  CoreSimpleTouchHandler_OnSetMaxStrikeCount( &_this->TouchHandler, 100 );
  CoreGroup__Add( _this, ((CoreView)&_this->Background ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Knob ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->TouchHandler ), 0 );
  _this->FlashTimer.OnTrigger = EwNewSlot( _this, ComponentsToggleButton_onFlashTimer );
  _this->KeyHandler.OnPress = EwNewSlot( _this, ComponentsToggleButton_onPressKey );
  _this->TouchHandler.OnLeave = EwNewSlot( _this, ComponentsToggleButton_onEnterLeaveTouch );
  _this->TouchHandler.OnEnter = EwNewSlot( _this, ComponentsToggleButton_onEnterLeaveTouch );
  _this->TouchHandler.OnRelease = EwNewSlot( _this, ComponentsToggleButton_onReleaseTouch );
  _this->TouchHandler.OnPress = EwNewSlot( _this, ComponentsToggleButton_onPressTouch );
}

/* Re-Initializer for the class 'Components::ToggleButton' */
void ComponentsToggleButton__ReInit( ComponentsToggleButton _this )
{
  /* At first re-initialize the super class ... */
  TemplatesToggleButton__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreTimer__ReInit( &_this->FlashTimer );
  CoreKeyPressHandler__ReInit( &_this->KeyHandler );
  ViewsRectangle__ReInit( &_this->Background );
  ViewsRectangle__ReInit( &_this->Knob );
  CoreSimpleTouchHandler__ReInit( &_this->TouchHandler );
}

/* Finalizer method for the class 'Components::ToggleButton' */
void ComponentsToggleButton__Done( ComponentsToggleButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( TemplatesToggleButton );

  /* Finalize all embedded objects */
  CoreTimer__Done( &_this->FlashTimer );
  CoreKeyPressHandler__Done( &_this->KeyHandler );
  ViewsRectangle__Done( &_this->Background );
  ViewsRectangle__Done( &_this->Knob );
  CoreSimpleTouchHandler__Done( &_this->TouchHandler );

  /* Don't forget to deinitialize the super class ... */
  TemplatesToggleButton__Done( &_this->_.Super );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsToggleButton_UpdateLayout( ComponentsToggleButton _this, XPoint aSize )
{
  CoreGroup_UpdateLayout((CoreGroup)_this, aSize );
  ViewsRectangle_OnSetRadius( &_this->Knob, EwGetRectW( _this->Knob.Super1.Bounds ) 
  / 2 );
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
void ComponentsToggleButton_UpdateViewState( ComponentsToggleButton _this, XSet 
  aState )
{
  XBool isEnabled;
  XBool isPressed;
  XBool isChecked;

  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  isEnabled = (( aState & CoreViewStateEnabled ) == CoreViewStateEnabled );
  isPressed = (XBool)(( _this->TouchHandler.Down && _this->TouchHandler.Inside ) 
  || _this->FlashTimer.Enabled );
  isChecked = _this->Active;

  if ( !isEnabled )
  {
    ViewsRectangle_OnSetColor( &_this->Background, ResSurface3 );
    ViewsRectangle_OnSetColor( &_this->Knob, ResOnSecondary );
  }
  else
    if ( isPressed || isChecked )
    {
      ViewsRectangle_OnSetColor( &_this->Background, ResSuccess );
      ViewsRectangle_OnSetColor( &_this->Knob, ResOnPrimary );
    }
    else
    {
      ViewsRectangle_OnSetColor( &_this->Background, ResOnPrimary );
      ViewsRectangle_OnSetColor( &_this->Knob, ResOnPrimary );
    }

  if ( isPressed )
    CoreRectView__OnSetBounds( &_this->Knob, EwSetRectX( _this->Knob.Super1.Bounds, 
    ( EwGetRectW( _this->Super3.Bounds ) - EwGetRectW( _this->Knob.Super1.Bounds )) 
    / 2 ));
  else
    if ( isChecked )
      CoreRectView__OnSetBounds( &_this->Knob, EwSetRectX( _this->Knob.Super1.Bounds, 
      ( EwGetRectW( _this->Super3.Bounds ) - EwGetRectW( _this->Knob.Super1.Bounds )) 
      - 1 ));
    else
      CoreRectView__OnSetBounds( &_this->Knob, EwSetRectX( _this->Knob.Super1.Bounds, 
      1 ));
}

/* This slot method will receive a signal, if the value of the property assigned 
   to @Outlet has been changed by another widget or by the application logic. In 
   response to this notification, the widget will update itself. */
void ComponentsToggleButton_onOutlet( ComponentsToggleButton _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Outlet.Object != 0 )
    ComponentsToggleButton_OnSetActive( _this, EwOnGetBool( _this->Outlet ));
}

/* This internal slot method is called when the '@FlashTimer' is expired. It ends 
   the short flash feedback effect. */
void ComponentsToggleButton_onFlashTimer( ComponentsToggleButton _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_InvalidateViewState((CoreGroup)_this );
  ComponentsToggleButton_OnSetActive( _this, (XBool)!_this->Active );

  if ( _this->Outlet.Object != 0 )
  {
    EwOnSetBool( _this->Outlet, _this->Active );
    EwNotifyRefObservers( _this->Outlet, 0 );
  }
}

/* This internal slot method is called when the '@KeyHandler' is activated (when 
   the user has pressed the key specified in the property 'Filter' of the key handler). */
void ComponentsToggleButton_onPressKey( ComponentsToggleButton _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->TouchHandler.Down )
    return;

  if ( _this->KeyHandler.Repetition )
    return;

  CoreGroup_InvalidateViewState((CoreGroup)_this );

  if ( _this->FlashTimer.Enabled )
  {
    CoreTimer_OnSetEnabled( &_this->FlashTimer, 0 );
    ComponentsToggleButton_OnSetActive( _this, (XBool)!_this->Active );

    if ( _this->Outlet.Object != 0 )
    {
      EwOnSetBool( _this->Outlet, _this->Active );
      EwNotifyRefObservers( _this->Outlet, 0 );
    }
  }

  CoreTimer_OnSetEnabled( &_this->FlashTimer, 1 );
}

/* This internal slot method is called when the user drags the finger while pressing 
   the button. This only updates the button to appear pressed or released. */
void ComponentsToggleButton_onEnterLeaveTouch( ComponentsToggleButton _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* This internal slot method is called when the user releases the touch screen after 
   touching the button's area. This activates the button. */
void ComponentsToggleButton_onReleaseTouch( ComponentsToggleButton _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( !_this->TouchHandler.Inside )
    return;

  if ( _this->TouchHandler.AutoDeflected )
    return;

  if ( _this->TouchHandler.HoldPeriod >= _this->FlashTimer.Begin )
  {
    ComponentsToggleButton_OnSetActive( _this, (XBool)!_this->Active );

    if ( _this->Outlet.Object != 0 )
    {
      EwOnSetBool( _this->Outlet, _this->Active );
      EwNotifyRefObservers( _this->Outlet, 0 );
    }
  }
  else
    CoreTimer_OnSetEnabled( &_this->FlashTimer, 1 );
}

/* This internal slot method is called when the user touches the button's area. */
void ComponentsToggleButton_onPressTouch( ComponentsToggleButton _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->FlashTimer.Enabled )
  {
    CoreTimer_OnSetEnabled( &_this->FlashTimer, 0 );
    ComponentsToggleButton_OnSetActive( _this, (XBool)!_this->Active );

    if ( _this->Outlet.Object != 0 )
    {
      EwOnSetBool( _this->Outlet, _this->Active );
      EwNotifyRefObservers( _this->Outlet, 0 );
    }
  }
}

/* 'C' function for method : 'Components::ToggleButton.OnSetOutlet()' */
void ComponentsToggleButton_OnSetOutlet( ComponentsToggleButton _this, XRef value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  if ( _this->Outlet.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsToggleButton_onOutlet ), _this->Outlet, 
      0 );

  _this->Outlet = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsToggleButton_onOutlet ), value, 
      0 );

  if ( value.Object != 0 )
    EwPostSignal( EwNewSlot( _this, ComponentsToggleButton_onOutlet ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::ToggleButton.OnSetActive()' */
void ComponentsToggleButton_OnSetActive( ComponentsToggleButton _this, XBool value )
{
  if ( _this->Active == value )
    return;

  _this->Active = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* Variants derived from the class : 'Components::ToggleButton' */
EW_DEFINE_CLASS_VARIANTS( ComponentsToggleButton )
EW_END_OF_CLASS_VARIANTS( ComponentsToggleButton )

/* Virtual Method Table (VMT) for the class : 'Components::ToggleButton' */
EW_DEFINE_CLASS( ComponentsToggleButton, TemplatesToggleButton, FlashTimer, Outlet, 
                 Outlet, Outlet, Active, Active, "Components::ToggleButton" )
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
  ComponentsToggleButton_UpdateLayout,
  ComponentsToggleButton_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsToggleButton )

/* Initializer for the class 'Components::QRCode' */
void ComponentsQRCode__Init( ComponentsQRCode _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  QRCodeQRCode__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsQRCode );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsQRCode );
}

/* Re-Initializer for the class 'Components::QRCode' */
void ComponentsQRCode__ReInit( ComponentsQRCode _this )
{
  /* At first re-initialize the super class ... */
  QRCodeQRCode__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::QRCode' */
void ComponentsQRCode__Done( ComponentsQRCode _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( QRCodeQRCode );

  /* Don't forget to deinitialize the super class ... */
  QRCodeQRCode__Done( &_this->_.Super );
}

/* This slot method will receive a signal, if the value of the property assigned 
   to @Outlet has been changed by another widget or by the application logic. In 
   response to this notification, the widget will update itself. */
void ComponentsQRCode_onOutlet( ComponentsQRCode _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Outlet.Object != 0 )
    QRCodeQRCode_OnSetText((QRCodeQRCode)_this, EwOnGetString( _this->Outlet ));
}

/* 'C' function for method : 'Components::QRCode.OnSetOutlet()' */
void ComponentsQRCode_OnSetOutlet( ComponentsQRCode _this, XRef value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  if ( _this->Outlet.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsQRCode_onOutlet ), _this->Outlet, 
      0 );

  _this->Outlet = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsQRCode_onOutlet ), value, 0 );

  if ( value.Object != 0 )
    EwPostSignal( EwNewSlot( _this, ComponentsQRCode_onOutlet ), ((XObject)_this ));
}

/* Variants derived from the class : 'Components::QRCode' */
EW_DEFINE_CLASS_VARIANTS( ComponentsQRCode )
EW_END_OF_CLASS_VARIANTS( ComponentsQRCode )

/* Virtual Method Table (VMT) for the class : 'Components::QRCode' */
EW_DEFINE_CLASS( ComponentsQRCode, QRCodeQRCode, Outlet, Outlet, Outlet, Outlet, 
                 _.VMT, _.VMT, "Components::QRCode" )
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
  QRCodeQRCode_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  QRCodeQRCode_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsQRCode )

/* Initializer for the class 'Components::DataList' */
void ComponentsDataList__Init( ComponentsDataList _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsDataList );

  /* ... then construct all embedded objects */
  CoreSlideTouchHandler__Init( &_this->SlideTouchHandler, &_this->_.XObject, 0 );
  CoreVerticalList__Init( &_this->List, &_this->_.XObject, 0 );
  ComponentsVertScrollbar__Init( &_this->Scrollbar, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->FadeTop, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->FadeBottom, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsDataList );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const008A );
  CoreView_OnSetLayout((CoreView)&_this->SlideTouchHandler, CoreLayoutAlignToBottom 
  | CoreLayoutAlignToLeft | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz 
  | CoreLayoutResizeVert );
  CoreRectView__OnSetBounds( &_this->SlideTouchHandler, _Const008A );
  _this->SlideTouchHandler.SlideHorz = 0;
  _this->SlideTouchHandler.RubberBandScrolling = 0;
  CoreRectView__OnSetBounds( &_this->List, _Const008B );
  CoreVerticalList_OnSetItemClass( &_this->List, EW_CLASS( ComponentsListItem ));
  CoreRectView__OnSetBounds( &_this->Scrollbar, _Const008C );
  _this->ItemClass = EW_CLASS( ComponentsListItem );
  _this->ItemHeight = 24;
  _this->Item = -1;
  CoreRectView__OnSetBounds( &_this->FadeTop, _Const008D );
  ViewsRectangle_OnSetVisible( &_this->FadeTop, 0 );
  CoreRectView__OnSetBounds( &_this->FadeBottom, _Const008E );
  ViewsRectangle_OnSetVisible( &_this->FadeBottom, 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->SlideTouchHandler ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->List ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->Scrollbar ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->FadeTop ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->FadeBottom ), 0 );
  _this->List.OnUpdate = EwNewSlot( _this, ComponentsDataList_onListUpdate );
  _this->List.OnLoadItem = EwNewSlot( _this, ComponentsDataList_onLoadItem );
  CoreVerticalList_OnSetSlideHandler( &_this->List, &_this->SlideTouchHandler );
}

/* Re-Initializer for the class 'Components::DataList' */
void ComponentsDataList__ReInit( ComponentsDataList _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreSlideTouchHandler__ReInit( &_this->SlideTouchHandler );
  CoreVerticalList__ReInit( &_this->List );
  ComponentsVertScrollbar__ReInit( &_this->Scrollbar );
  ViewsRectangle__ReInit( &_this->FadeTop );
  ViewsRectangle__ReInit( &_this->FadeBottom );
}

/* Finalizer method for the class 'Components::DataList' */
void ComponentsDataList__Done( ComponentsDataList _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Finalize all embedded objects */
  CoreSlideTouchHandler__Done( &_this->SlideTouchHandler );
  CoreVerticalList__Done( &_this->List );
  ComponentsVertScrollbar__Done( &_this->Scrollbar );
  ViewsRectangle__Done( &_this->FadeTop );
  ViewsRectangle__Done( &_this->FadeBottom );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsDataList_UpdateLayout( ComponentsDataList _this, XPoint aSize )
{
  CoreGroup_UpdateLayout((CoreGroup)_this, aSize );
  CoreRectView__OnSetBounds( &_this->Scrollbar, EwSetRectX( _this->Scrollbar.Super3.Bounds, 
  aSize.X - EwGetRectW( _this->Scrollbar.Super3.Bounds )));
  CoreRectView__OnSetBounds( &_this->List, EwSetRectX2( _this->List.Super2.Bounds, 
  _this->Scrollbar.Super3.Bounds.Point1.X - 4 ));
  CoreRectView__OnSetBounds( &_this->List, EwSetRectY2( _this->List.Super2.Bounds, 
  aSize.Y ));
  CoreRectView__OnSetBounds( &_this->Scrollbar, EwSetRectY1( _this->Scrollbar.Super3.Bounds, 
  _this->List.Super2.Bounds.Point1.Y ));
  CoreRectView__OnSetBounds( &_this->Scrollbar, EwSetRectY2( _this->Scrollbar.Super3.Bounds, 
  _this->List.Super2.Bounds.Point2.Y ));
  CoreRectView__OnSetBounds( &_this->FadeTop, EwNewRect( _this->List.Super2.Bounds.Point1.X, 
  _this->List.Super2.Bounds.Point1.Y, _this->List.Super2.Bounds.Point2.X, _this->List.Super2.Bounds.Point1.Y 
  + 50 ));
  CoreRectView__OnSetBounds( &_this->FadeBottom, EwNewRect( _this->List.Super2.Bounds.Point1.X, 
  _this->List.Super2.Bounds.Point2.Y - 50, _this->List.Super2.Bounds.Point2.X, _this->List.Super2.Bounds.Point2.Y ));
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
void ComponentsDataList_UpdateViewState( ComponentsDataList _this, XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  ViewsRectangle_OnSetColorTL( &_this->FadeTop, _Const003C );
  ViewsRectangle_OnSetColorTR( &_this->FadeTop, _Const003C );
  ViewsRectangle_OnSetColorBL( &_this->FadeTop, ResTRANSPARENT );
  ViewsRectangle_OnSetColorBR( &_this->FadeTop, ResTRANSPARENT );
  ViewsRectangle_OnSetColorTL( &_this->FadeBottom, ResTRANSPARENT );
  ViewsRectangle_OnSetColorTR( &_this->FadeBottom, ResTRANSPARENT );
  ViewsRectangle_OnSetColorBL( &_this->FadeBottom, _Const003C );
  ViewsRectangle_OnSetColorBR( &_this->FadeBottom, _Const003C );
}

/* This method is called by 'VerticalList' every time the list loads or updates 
   an item. */
void ComponentsDataList_onLoadItem( ComponentsDataList _this, XObject sender )
{
  XInt32 itemNo;
  ComponentsListItem itemView;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  itemNo = _this->List.Item;
  itemView = EwCastObject( _this->List.View, ComponentsListItem );

  if ( itemView == 0 )
    return;

  itemView->DataProvider = _this->DataProvider;
  ComponentsListItem__UpdateData( itemView, itemNo );
  CoreRectView__OnSetBounds( itemView, EwSetRectSize( itemView->Super2.Bounds, _this->List.ViewSize ));
  _this->Item = _this->List.Item;
  _this->View = _this->List.View;
  _this->Item = -1;
  _this->View = 0;
}

/* 'C' function for method : 'Components::DataList.OnSetDataProvider()' */
void ComponentsDataList_OnSetDataProvider( ComponentsDataList _this, DeviceDataProvider 
  value )
{
  if ( _this->DataProvider == value )
    return;

  if ( _this->DataProvider != 0 )
    EwDetachObjObserver( EwNewSlot( _this, ComponentsDataList_onDataChanged ), (XObject)_this->DataProvider, 
      0 );

  _this->DataProvider = value;

  if ( value != 0 )
    EwAttachObjObserver( EwNewSlot( _this, ComponentsDataList_onDataChanged ), (XObject)value, 
      0 );

  EwPostSignal( EwNewSlot( _this, ComponentsDataList_onDataChanged ), ((XObject)_this ));
}

/* Wrapper function for the non virtual method : 'Components::DataList.OnSetDataProvider()' */
void ComponentsDataList__OnSetDataProvider( void* _this, DeviceDataProvider value )
{
  ComponentsDataList_OnSetDataProvider((ComponentsDataList)_this, value );
}

/* 'C' function for method : 'Components::DataList.onDataChanged()' */
void ComponentsDataList_onDataChanged( ComponentsDataList _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->DataProvider != 0 )
  {
    CoreVerticalList_OnSetNoOfItems( &_this->List, DeviceDataProvider__GetNoOfData( 
    _this->DataProvider ));
    CoreVerticalList_InvalidateItems( &_this->List, 0, _this->List.NoOfItems - 1 );
    CoreVerticalList_AdjustList( &_this->List, 0, EwNullSlot );
  }
  else
    CoreVerticalList_OnSetNoOfItems( &_this->List, 0 );
}

/* 'C' function for method : 'Components::DataList.onListUpdate()' */
void ComponentsDataList_onListUpdate( ComponentsDataList _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ComponentsVertScrollbar_OnSetViewArea( &_this->Scrollbar, EwGetRectH( _this->List.Super2.Bounds ));
  ComponentsVertScrollbar_OnSetContentArea( &_this->Scrollbar, EwGetRectH( CoreVerticalList_GetItemsArea( 
  &_this->List, 0, _this->List.NoOfItems - 1 )));
  ComponentsVertScrollbar_OnSetPosition( &_this->Scrollbar, -_this->List.ScrollOffset );
  ViewsRectangle_OnSetVisible( &_this->FadeTop, (XBool)(( _this->Scrollbar.ViewArea 
  < _this->Scrollbar.ContentArea ) && ( _this->List.ScrollOffset != 0 )));
  ViewsRectangle_OnSetVisible( &_this->FadeBottom, (XBool)(( _this->Scrollbar.ViewArea 
  < _this->Scrollbar.ContentArea ) && ( _this->List.ScrollOffset != ( _this->Scrollbar.ViewArea 
  - _this->Scrollbar.ContentArea ))));
}

/* 'C' function for method : 'Components::DataList.OnSetItemClass()' */
void ComponentsDataList_OnSetItemClass( ComponentsDataList _this, XClass value )
{
  if ( _this->ItemClass == value )
    return;

  _this->ItemClass = value;
  CoreVerticalList_OnSetItemClass( &_this->List, value );
}

/* 'C' function for method : 'Components::DataList.OnSetItemHeight()' */
void ComponentsDataList_OnSetItemHeight( ComponentsDataList _this, XInt32 value )
{
  if ( _this->ItemHeight == value )
    return;

  _this->ItemHeight = value;
  CoreVerticalList_OnSetItemHeight( &_this->List, value );
  CoreSlideTouchHandler_OnSetSnapNext( &_this->SlideTouchHandler, EwSetPointY( _this->SlideTouchHandler.SnapNext, 
  value ));
}

/* Variants derived from the class : 'Components::DataList' */
EW_DEFINE_CLASS_VARIANTS( ComponentsDataList )
EW_END_OF_CLASS_VARIANTS( ComponentsDataList )

/* Virtual Method Table (VMT) for the class : 'Components::DataList' */
EW_DEFINE_CLASS( ComponentsDataList, CoreGroup, SlideTouchHandler, DataProvider, 
                 ItemClass, ItemClass, ItemClass, ItemClass, "Components::DataList" )
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
  ComponentsDataList_UpdateLayout,
  ComponentsDataList_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsDataList )

/* Initializer for the class 'Components::ListItem' */
void ComponentsListItem__Init( ComponentsListItem _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsListItem );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsListItem );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const008F );
}

/* Re-Initializer for the class 'Components::ListItem' */
void ComponentsListItem__ReInit( ComponentsListItem _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::ListItem' */
void ComponentsListItem__Done( ComponentsListItem _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* 'C' function for method : 'Components::ListItem.UpdateData()' */
void ComponentsListItem_UpdateData( ComponentsListItem _this, XInt32 aItemIndex )
{
  _this->Index = aItemIndex;
}

/* Wrapper function for the virtual method : 'Components::ListItem.UpdateData()' */
void ComponentsListItem__UpdateData( void* _this, XInt32 aItemIndex )
{
  ((ComponentsListItem)_this)->_.VMT->UpdateData((ComponentsListItem)_this, aItemIndex );
}

/* Variants derived from the class : 'Components::ListItem' */
EW_DEFINE_CLASS_VARIANTS( ComponentsListItem )
EW_END_OF_CLASS_VARIANTS( ComponentsListItem )

/* Virtual Method Table (VMT) for the class : 'Components::ListItem' */
EW_DEFINE_CLASS( ComponentsListItem, CoreGroup, DataProvider, DataProvider, Index, 
                 Index, Index, Index, "Components::ListItem" )
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
  ComponentsListItem_UpdateData,
EW_END_OF_CLASS( ComponentsListItem )

/* Initializer for the class 'Components::StringValueDisplay' */
void ComponentsStringValueDisplay__Init( ComponentsStringValueDisplay _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsValueDisplay__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsStringValueDisplay );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsStringValueDisplay );

  /* Call the user defined constructor */
  ComponentsStringValueDisplay_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::StringValueDisplay' */
void ComponentsStringValueDisplay__ReInit( ComponentsStringValueDisplay _this )
{
  /* At first re-initialize the super class ... */
  ComponentsValueDisplay__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::StringValueDisplay' */
void ComponentsStringValueDisplay__Done( ComponentsStringValueDisplay _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsValueDisplay );

  /* Don't forget to deinitialize the super class ... */
  ComponentsValueDisplay__Done( &_this->_.Super );
}

/* 'C' function for method : 'Components::StringValueDisplay.Init()' */
void ComponentsStringValueDisplay_Init( ComponentsStringValueDisplay _this, XHandle 
  aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* 'C' function for method : 'Components::StringValueDisplay.OnSetValue()' */
void ComponentsStringValueDisplay_OnSetValue( ComponentsStringValueDisplay _this, 
  XString value )
{
  if ( !EwCompString( _this->Value, value ))
    return;

  _this->Value = EwShareString( value );
  ViewsText__OnSetString( _this, value );
}

/* 'C' function for method : 'Components::StringValueDisplay.OnSetOutlet()' */
void ComponentsStringValueDisplay_OnSetOutlet( ComponentsStringValueDisplay _this, 
  XRef value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  if ( _this->Outlet.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsStringValueDisplay_onOutlet ), 
      _this->Outlet, 0 );

  _this->Outlet = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsStringValueDisplay_onOutlet ), 
      value, 0 );

  if ( value.Object != 0 )
    EwPostSignal( EwNewSlot( _this, ComponentsStringValueDisplay_onOutlet ), ((XObject)_this ));
}

/* This slot method will receive a signal, if the value of the property assigned 
   to @Outlet has been changed by another widget or by the application logic. In 
   response to this notification, the widget will update itself. */
void ComponentsStringValueDisplay_onOutlet( ComponentsStringValueDisplay _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Outlet.Object != 0 )
    ComponentsStringValueDisplay_OnSetValue( _this, EwOnGetString( _this->Outlet ));
}

/* Variants derived from the class : 'Components::StringValueDisplay' */
EW_DEFINE_CLASS_VARIANTS( ComponentsStringValueDisplay )
EW_END_OF_CLASS_VARIANTS( ComponentsStringValueDisplay )

/* Virtual Method Table (VMT) for the class : 'Components::StringValueDisplay' */
EW_DEFINE_CLASS( ComponentsStringValueDisplay, ComponentsValueDisplay, Outlet, Outlet, 
                 Outlet, Outlet, Value, _.VMT, "Components::StringValueDisplay" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  ViewsText_Draw,
  CoreView_GetClipping,
  CoreView_HandleEvent,
  CoreView_CursorHitTest,
  CoreView_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreView_ChangeViewState,
  ComponentsValueDisplay_OnSetBounds,
  ComponentsValueDisplay_OnSetString,
  ComponentsValueDisplay_OnSetFont,
EW_END_OF_CLASS( ComponentsStringValueDisplay )

/* Initializer for the class 'Components::StringSettingItem' */
void ComponentsStringSettingItem__Init( ComponentsStringSettingItem _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsSettingItem__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsStringSettingItem );

  /* ... then construct all embedded objects */
  ComponentsStringValueDisplay__Init( &_this->ValueDisplay, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsStringSettingItem );

  /* ... and initialize objects, variables, properties, etc. */
  CoreView_OnSetLayout((CoreView)&_this->ValueDisplay, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToRight | CoreLayoutAlignToTop );
  CoreRectView__OnSetBounds( &_this->ValueDisplay, _Const0079 );
  ViewsText_OnSetAlignment((ViewsText)&_this->ValueDisplay, ViewsTextAlignmentAlignHorzRight 
  | ViewsTextAlignmentAlignVertCenter );
  CoreGroup__Add( _this, ((CoreView)&_this->ValueDisplay ), 0 );
  ViewsText__OnSetFont( &_this->ValueDisplay, EwLoadResource( &FontsBody18SemiBold, 
  ResourcesFont ));
  ComponentsValueDisplay_OnSetFont1((ComponentsValueDisplay)&_this->ValueDisplay, 
  EwLoadResource( &FontsBody16, ResourcesFont ));
}

/* Re-Initializer for the class 'Components::StringSettingItem' */
void ComponentsStringSettingItem__ReInit( ComponentsStringSettingItem _this )
{
  /* At first re-initialize the super class ... */
  ComponentsSettingItem__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsStringValueDisplay__ReInit( &_this->ValueDisplay );
}

/* Finalizer method for the class 'Components::StringSettingItem' */
void ComponentsStringSettingItem__Done( ComponentsStringSettingItem _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsSettingItem );

  /* Finalize all embedded objects */
  ComponentsStringValueDisplay__Done( &_this->ValueDisplay );

  /* Don't forget to deinitialize the super class ... */
  ComponentsSettingItem__Done( &_this->_.Super );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsStringSettingItem_UpdateLayout( ComponentsStringSettingItem _this, 
  XPoint aSize )
{
  ComponentsSettingItem_UpdateLayout((ComponentsSettingItem)_this, aSize );
  ComponentsSettingItem_updateValueDisplay((ComponentsSettingItem)_this, ((ComponentsValueDisplay)&_this->ValueDisplay ));
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
void ComponentsStringSettingItem_UpdateViewState( ComponentsStringSettingItem _this, 
  XSet aState )
{
  ComponentsSettingItem_UpdateViewState((ComponentsSettingItem)_this, aState );
  ViewsText_OnSetColor((ViewsText)&_this->ValueDisplay, ResOnPrimary );
}

/* 'C' function for method : 'Components::StringSettingItem.OnSetValue()' */
void ComponentsStringSettingItem_OnSetValue( ComponentsStringSettingItem _this, 
  XString value )
{
  if ( !EwCompString( _this->Value, value ))
    return;

  _this->Value = EwShareString( value );
  ComponentsStringValueDisplay_OnSetValue( &_this->ValueDisplay, value );
}

/* 'C' function for method : 'Components::StringSettingItem.OnSetOutlet()' */
void ComponentsStringSettingItem_OnSetOutlet( ComponentsStringSettingItem _this, 
  XRef value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  _this->Outlet = value;
  ComponentsStringValueDisplay_OnSetOutlet( &_this->ValueDisplay, value );
}

/* Variants derived from the class : 'Components::StringSettingItem' */
EW_DEFINE_CLASS_VARIANTS( ComponentsStringSettingItem )
EW_END_OF_CLASS_VARIANTS( ComponentsStringSettingItem )

/* Virtual Method Table (VMT) for the class : 'Components::StringSettingItem' */
EW_DEFINE_CLASS( ComponentsStringSettingItem, ComponentsSettingItem, ValueDisplay, 
                 Outlet, Outlet, Outlet, Value, _.VMT, "Components::StringSettingItem" )
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
  ComponentsStringSettingItem_UpdateLayout,
  ComponentsStringSettingItem_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsStringSettingItem )

/* Initializer for the class 'Components::EnumSettingItem' */
void ComponentsEnumSettingItem__Init( ComponentsEnumSettingItem _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsSettingItem__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsEnumSettingItem );

  /* ... then construct all embedded objects */
  ComponentsEnumValueDisplay__Init( &_this->ValueDisplay, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsEnumSettingItem );

  /* ... and initialize objects, variables, properties, etc. */
  CoreView_OnSetLayout((CoreView)&_this->ValueDisplay, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToRight | CoreLayoutAlignToTop );
  CoreRectView__OnSetBounds( &_this->ValueDisplay, _Const0079 );
  ViewsText_OnSetAlignment((ViewsText)&_this->ValueDisplay, ViewsTextAlignmentAlignHorzRight 
  | ViewsTextAlignmentAlignVertCenter );
  CoreGroup__Add( _this, ((CoreView)&_this->ValueDisplay ), 0 );
  ViewsText__OnSetFont( &_this->ValueDisplay, EwLoadResource( &FontsBody18SemiBold, 
  ResourcesFont ));
}

/* Re-Initializer for the class 'Components::EnumSettingItem' */
void ComponentsEnumSettingItem__ReInit( ComponentsEnumSettingItem _this )
{
  /* At first re-initialize the super class ... */
  ComponentsSettingItem__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsEnumValueDisplay__ReInit( &_this->ValueDisplay );
}

/* Finalizer method for the class 'Components::EnumSettingItem' */
void ComponentsEnumSettingItem__Done( ComponentsEnumSettingItem _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsSettingItem );

  /* Finalize all embedded objects */
  ComponentsEnumValueDisplay__Done( &_this->ValueDisplay );

  /* Don't forget to deinitialize the super class ... */
  ComponentsSettingItem__Done( &_this->_.Super );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsEnumSettingItem_UpdateLayout( ComponentsEnumSettingItem _this, XPoint 
  aSize )
{
  ComponentsSettingItem_UpdateLayout((ComponentsSettingItem)_this, aSize );
  ComponentsSettingItem_updateValueDisplay((ComponentsSettingItem)_this, ((ComponentsValueDisplay)&_this->ValueDisplay ));
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
void ComponentsEnumSettingItem_UpdateViewState( ComponentsEnumSettingItem _this, 
  XSet aState )
{
  ComponentsSettingItem_UpdateViewState((ComponentsSettingItem)_this, aState );
  ViewsText_OnSetColor((ViewsText)&_this->ValueDisplay, ResOnPrimary );
}

/* 'C' function for method : 'Components::EnumSettingItem.OnSetValue()' */
void ComponentsEnumSettingItem_OnSetValue( ComponentsEnumSettingItem _this, XInt32 
  value )
{
  if ( _this->Value == value )
    return;

  _this->Value = value;
  ComponentsIntValueDisplay_OnSetValue((ComponentsIntValueDisplay)&_this->ValueDisplay, 
  value );
}

/* 'C' function for method : 'Components::EnumSettingItem.OnSetEnum()' */
void ComponentsEnumSettingItem_OnSetEnum( ComponentsEnumSettingItem _this, DeviceEnumClass 
  value )
{
  if ( _this->Enum == value )
    return;

  _this->Enum = value;
  ComponentsEnumValueDisplay_OnSetEnum( &_this->ValueDisplay, value );
}

/* Variants derived from the class : 'Components::EnumSettingItem' */
EW_DEFINE_CLASS_VARIANTS( ComponentsEnumSettingItem )
EW_END_OF_CLASS_VARIANTS( ComponentsEnumSettingItem )

/* Virtual Method Table (VMT) for the class : 'Components::EnumSettingItem' */
EW_DEFINE_CLASS( ComponentsEnumSettingItem, ComponentsSettingItem, ValueDisplay, 
                 Enum, Value, Value, Value, Value, "Components::EnumSettingItem" )
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
  ComponentsEnumSettingItem_UpdateLayout,
  ComponentsEnumSettingItem_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsEnumSettingItem )

/* Initializer for the class 'Components::DateTimeDisplay' */
void ComponentsDateTimeDisplay__Init( ComponentsDateTimeDisplay _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsValueDisplay__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsDateTimeDisplay );

  /* ... then construct all embedded objects */
  CoreTime__Init( &_this->time, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsDateTimeDisplay );

  /* ... and initialize objects, variables, properties, etc. */
  /* Call the user defined constructor */
  ComponentsDateTimeDisplay_Init( _this, aArg );
}

/* Re-Initializer for the class 'Components::DateTimeDisplay' */
void ComponentsDateTimeDisplay__ReInit( ComponentsDateTimeDisplay _this )
{
  /* At first re-initialize the super class ... */
  ComponentsValueDisplay__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreTime__ReInit( &_this->time );
}

/* Finalizer method for the class 'Components::DateTimeDisplay' */
void ComponentsDateTimeDisplay__Done( ComponentsDateTimeDisplay _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsValueDisplay );

  /* Finalize all embedded objects */
  CoreTime__Done( &_this->time );

  /* Don't forget to deinitialize the super class ... */
  ComponentsValueDisplay__Done( &_this->_.Super );
}

/* 'C' function for method : 'Components::DateTimeDisplay.Init()' */
void ComponentsDateTimeDisplay_Init( ComponentsDateTimeDisplay _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* 'C' function for method : 'Components::DateTimeDisplay.OnSetValue()' */
void ComponentsDateTimeDisplay_OnSetValue( ComponentsDateTimeDisplay _this, XInt64 
  value )
{
  if ( _this->Value == value )
    return;

  _this->Value = value;
  EwPostSignal( EwNewSlot( _this, ComponentsDateTimeDisplay_formatValue ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::DateTimeDisplay.OnSetOutlet()' */
void ComponentsDateTimeDisplay_OnSetOutlet( ComponentsDateTimeDisplay _this, XRef 
  value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  if ( _this->Outlet.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, ComponentsDateTimeDisplay_onOutlet ), 
      _this->Outlet, 0 );

  _this->Outlet = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, ComponentsDateTimeDisplay_onOutlet ), 
      value, 0 );

  if ( value.Object != 0 )
    EwPostSignal( EwNewSlot( _this, ComponentsDateTimeDisplay_onOutlet ), ((XObject)_this ));
}

/* This slot method will receive a signal, if the value of the property assigned 
   to @Outlet has been changed by another widget or by the application logic. In 
   response to this notification, the widget will update itself. */
void ComponentsDateTimeDisplay_onOutlet( ComponentsDateTimeDisplay _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Outlet.Object != 0 )
    ComponentsDateTimeDisplay_OnSetValue( _this, EwOnGetInt64( _this->Outlet ));
}

/* 'C' function for method : 'Components::DateTimeDisplay.formatValue()' */
void ComponentsDateTimeDisplay_formatValue( ComponentsDateTimeDisplay _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  ViewsText__OnSetString( _this, CoreTime_Format( CoreTime_Initialize( &_this->time, 
  _this->Value ), EwLoadString( &_Const0090 )));
}

/* Variants derived from the class : 'Components::DateTimeDisplay' */
EW_DEFINE_CLASS_VARIANTS( ComponentsDateTimeDisplay )
EW_END_OF_CLASS_VARIANTS( ComponentsDateTimeDisplay )

/* Virtual Method Table (VMT) for the class : 'Components::DateTimeDisplay' */
EW_DEFINE_CLASS( ComponentsDateTimeDisplay, ComponentsValueDisplay, time, Outlet, 
                 Outlet, Outlet, _.VMT, _.VMT, "Components::DateTimeDisplay" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  ViewsText_Draw,
  CoreView_GetClipping,
  CoreView_HandleEvent,
  CoreView_CursorHitTest,
  CoreView_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreView_ChangeViewState,
  ComponentsValueDisplay_OnSetBounds,
  ComponentsValueDisplay_OnSetString,
  ComponentsValueDisplay_OnSetFont,
EW_END_OF_CLASS( ComponentsDateTimeDisplay )

/* Initializer for the class 'Components::DateTimeSettingItem' */
void ComponentsDateTimeSettingItem__Init( ComponentsDateTimeSettingItem _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsSettingItem__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsDateTimeSettingItem );

  /* ... then construct all embedded objects */
  ComponentsDateTimeDisplay__Init( &_this->ValueDisplay, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsDateTimeSettingItem );

  /* ... and initialize objects, variables, properties, etc. */
  CoreView_OnSetLayout((CoreView)&_this->ValueDisplay, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToRight | CoreLayoutAlignToTop );
  CoreRectView__OnSetBounds( &_this->ValueDisplay, _Const0079 );
  ViewsText_OnSetAlignment((ViewsText)&_this->ValueDisplay, ViewsTextAlignmentAlignHorzRight 
  | ViewsTextAlignmentAlignVertCenter );
  CoreGroup__Add( _this, ((CoreView)&_this->ValueDisplay ), 0 );
  ViewsText__OnSetFont( &_this->ValueDisplay, EwLoadResource( &FontsBody18SemiBold, 
  ResourcesFont ));
}

/* Re-Initializer for the class 'Components::DateTimeSettingItem' */
void ComponentsDateTimeSettingItem__ReInit( ComponentsDateTimeSettingItem _this )
{
  /* At first re-initialize the super class ... */
  ComponentsSettingItem__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ComponentsDateTimeDisplay__ReInit( &_this->ValueDisplay );
}

/* Finalizer method for the class 'Components::DateTimeSettingItem' */
void ComponentsDateTimeSettingItem__Done( ComponentsDateTimeSettingItem _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsSettingItem );

  /* Finalize all embedded objects */
  ComponentsDateTimeDisplay__Done( &_this->ValueDisplay );

  /* Don't forget to deinitialize the super class ... */
  ComponentsSettingItem__Done( &_this->_.Super );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void ComponentsDateTimeSettingItem_UpdateLayout( ComponentsDateTimeSettingItem _this, 
  XPoint aSize )
{
  ComponentsSettingItem_UpdateLayout((ComponentsSettingItem)_this, aSize );
  ComponentsSettingItem_updateValueDisplay((ComponentsSettingItem)_this, ((ComponentsValueDisplay)&_this->ValueDisplay ));
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
void ComponentsDateTimeSettingItem_UpdateViewState( ComponentsDateTimeSettingItem _this, 
  XSet aState )
{
  ComponentsSettingItem_UpdateViewState((ComponentsSettingItem)_this, aState );
  ViewsText_OnSetColor((ViewsText)&_this->ValueDisplay, ResOnPrimary );
}

/* 'C' function for method : 'Components::DateTimeSettingItem.OnSetOutlet()' */
void ComponentsDateTimeSettingItem_OnSetOutlet( ComponentsDateTimeSettingItem _this, 
  XRef value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  _this->Outlet = value;
  ComponentsDateTimeDisplay_OnSetOutlet( &_this->ValueDisplay, value );
}

/* Variants derived from the class : 'Components::DateTimeSettingItem' */
EW_DEFINE_CLASS_VARIANTS( ComponentsDateTimeSettingItem )
EW_END_OF_CLASS_VARIANTS( ComponentsDateTimeSettingItem )

/* Virtual Method Table (VMT) for the class : 'Components::DateTimeSettingItem' */
EW_DEFINE_CLASS( ComponentsDateTimeSettingItem, ComponentsSettingItem, ValueDisplay, 
                 Outlet, Outlet, Outlet, _.VMT, _.VMT, "Components::DateTimeSettingItem" )
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
  ComponentsDateTimeSettingItem_UpdateLayout,
  ComponentsDateTimeSettingItem_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( ComponentsDateTimeSettingItem )

/* Initializer for the class 'Components::ValueDisplay' */
void ComponentsValueDisplay__Init( ComponentsValueDisplay _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ViewsText__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ComponentsValueDisplay );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ComponentsValueDisplay );
}

/* Re-Initializer for the class 'Components::ValueDisplay' */
void ComponentsValueDisplay__ReInit( ComponentsValueDisplay _this )
{
  /* At first re-initialize the super class ... */
  ViewsText__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Components::ValueDisplay' */
void ComponentsValueDisplay__Done( ComponentsValueDisplay _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ViewsText );

  /* Don't forget to deinitialize the super class ... */
  ViewsText__Done( &_this->_.Super );
}

/* 'C' function for method : 'Components::ValueDisplay.OnSetBounds()' */
void ComponentsValueDisplay_OnSetBounds( ComponentsValueDisplay _this, XRect value )
{
  if ( !EwCompRect( value, _this->Super2.Bounds ))
    return;

  ViewsText_OnSetBounds((ViewsText)_this, value );
  EwPostSignal( EwNewSlot( _this, ComponentsValueDisplay_updateFont ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::ValueDisplay.OnSetString()' */
void ComponentsValueDisplay_OnSetString( ComponentsValueDisplay _this, XString value )
{
  if ( !EwCompString( value, _this->Super1.String ))
    return;

  ViewsText_OnSetString((ViewsText)_this, value );
  EwPostSignal( EwNewSlot( _this, ComponentsValueDisplay_updateFont ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::ValueDisplay.OnSetFont()' */
void ComponentsValueDisplay_OnSetFont( ComponentsValueDisplay _this, ResourcesFont 
  value )
{
  if ( value == _this->Super1.Font )
    return;

  ViewsText_OnSetFont((ViewsText)_this, value );

  if ( !_this->inUpdateFont )
    _this->defaultFont = value;

  EwPostSignal( EwNewSlot( _this, ComponentsValueDisplay_updateFont ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::ValueDisplay.OnSetFont1()' */
void ComponentsValueDisplay_OnSetFont1( ComponentsValueDisplay _this, ResourcesFont 
  value )
{
  if ( _this->Font1 == value )
    return;

  _this->Font1 = value;
  EwPostSignal( EwNewSlot( _this, ComponentsValueDisplay_updateFont ), ((XObject)_this ));
}

/* 'C' function for method : 'Components::ValueDisplay.updateFont()' */
void ComponentsValueDisplay_updateFont( ComponentsValueDisplay _this, XObject sender )
{
  XInt32 w;
  ResourcesFont newFont;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if (( _this->Font1 == 0 ) || ( _this->defaultFont == 0 ))
    return;

  w = ResourcesFont_GetTextAdvance( _this->defaultFont, _this->Super1.String, 0, 
  -1 );

  if ( w > EwGetRectW( _this->Super2.Bounds ))
    newFont = _this->Font1;
  else
    newFont = _this->defaultFont;

  if ( newFont != _this->Super1.Font )
  {
    _this->inUpdateFont = 1;
    ViewsText__OnSetFont( _this, newFont );
    _this->inUpdateFont = 0;
    EwPostSignal( _this->OnAdjustFont, ((XObject)_this ));
  }
}

/* Variants derived from the class : 'Components::ValueDisplay' */
EW_DEFINE_CLASS_VARIANTS( ComponentsValueDisplay )
EW_END_OF_CLASS_VARIANTS( ComponentsValueDisplay )

/* Virtual Method Table (VMT) for the class : 'Components::ValueDisplay' */
EW_DEFINE_CLASS( ComponentsValueDisplay, ViewsText, Font1, Font1, OnAdjustFont, 
                 inUpdateFont, inUpdateFont, inUpdateFont, "Components::ValueDisplay" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  ViewsText_Draw,
  CoreView_GetClipping,
  CoreView_HandleEvent,
  CoreView_CursorHitTest,
  CoreView_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreView_ChangeViewState,
  ComponentsValueDisplay_OnSetBounds,
  ComponentsValueDisplay_OnSetString,
  ComponentsValueDisplay_OnSetFont,
EW_END_OF_CLASS( ComponentsValueDisplay )

/* Embedded Wizard */
