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
#include "_CoreKeyPressHandler.h"
#include "_CoreOutline.h"
#include "_CoreRoot.h"
#include "_CoreSimpleTouchHandler.h"
#include "_CoreTimer.h"
#include "_CoreView.h"
#include "_EffectsFloatEffect.h"
#include "_ViewsRectangle.h"
#include "_WidgetSetHorizontalSlider.h"
#include "_WidgetSetHorizontalSliderConfig.h"
#include "_WidgetSetWidgetConfig.h"
#include "Core.h"
#include "WidgetSet.h"

/* Constant values used in this 'C' module only. */
static const XRect _Const0000 = {{ 0, 0 }, { 200, 50 }};
static const XPoint _Const0001 = { 0, 50 };
static const XPoint _Const0002 = { 200, 50 };
static const XPoint _Const0003 = { 200, 0 };
static const XPoint _Const0004 = { 0, 0 };
static const XColor _Const0005 = { 0x00, 0x00, 0x00, 0x00 };
static const XRect _Const0006 = {{ 0, 0 }, { 0, 0 }};
static const XRect _Const0007 = {{ -8, -8 }, { 9, 9 }};

/* Initializer for the class 'WidgetSet::HorizontalSliderConfig' */
void WidgetSetHorizontalSliderConfig__Init( WidgetSetHorizontalSliderConfig _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  WidgetSetWidgetConfig__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( WidgetSetHorizontalSliderConfig );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( WidgetSetHorizontalSliderConfig );

  /* ... and initialize objects, variables, properties, etc. */
}

/* Re-Initializer for the class 'WidgetSet::HorizontalSliderConfig' */
void WidgetSetHorizontalSliderConfig__ReInit( WidgetSetHorizontalSliderConfig _this )
{
  /* At first re-initialize the super class ... */
  WidgetSetWidgetConfig__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'WidgetSet::HorizontalSliderConfig' */
void WidgetSetHorizontalSliderConfig__Done( WidgetSetHorizontalSliderConfig _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( WidgetSetWidgetConfig );

  /* Don't forget to deinitialize the super class ... */
  WidgetSetWidgetConfig__Done( &_this->_.Super );
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetStateTransitionDuration()' */
void WidgetSetHorizontalSliderConfig_OnSetStateTransitionDuration( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->StateTransitionDuration == value )
    return;

  _this->StateTransitionDuration = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetKeyRepeatPeriod()' */
void WidgetSetHorizontalSliderConfig_OnSetKeyRepeatPeriod( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->KeyRepeatPeriod == value )
    return;

  _this->KeyRepeatPeriod = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetKeyRepeatDelay()' */
void WidgetSetHorizontalSliderConfig_OnSetKeyRepeatDelay( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->KeyRepeatDelay == value )
    return;

  _this->KeyRepeatDelay = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetAccentColorActive()' */
void WidgetSetHorizontalSliderConfig_OnSetAccentColorActive( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->AccentColorActive, value ))
    return;

  _this->AccentColorActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetAccentColorFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetAccentColorFocused( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->AccentColorFocused, value ))
    return;

  _this->AccentColorFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetAccentColorDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetAccentColorDisabled( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->AccentColorDisabled, value ))
    return;

  _this->AccentColorDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetAccentColorDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetAccentColorDefault( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->AccentColorDefault, value ))
    return;

  _this->AccentColorDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetAccentCornerRadiusActive()' */
void WidgetSetHorizontalSliderConfig_OnSetAccentCornerRadiusActive( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->AccentCornerRadiusActive == value )
    return;

  _this->AccentCornerRadiusActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetAccentCornerRadiusFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetAccentCornerRadiusFocused( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->AccentCornerRadiusFocused == value )
    return;

  _this->AccentCornerRadiusFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetAccentCornerRadiusDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetAccentCornerRadiusDisabled( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->AccentCornerRadiusDisabled == value )
    return;

  _this->AccentCornerRadiusDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetAccentCornerRadiusDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetAccentCornerRadiusDefault( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->AccentCornerRadiusDefault == value )
    return;

  _this->AccentCornerRadiusDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetAccentSizeActive()' */
void WidgetSetHorizontalSliderConfig_OnSetAccentSizeActive( WidgetSetHorizontalSliderConfig _this, 
  XPoint value )
{
  if ( value.X < 0 )
    value.X = 0;

  if ( value.Y < 0 )
    value.Y = 0;

  if ( !EwCompPoint( _this->AccentSizeActive, value ))
    return;

  _this->AccentSizeActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetAccentSizeFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetAccentSizeFocused( WidgetSetHorizontalSliderConfig _this, 
  XPoint value )
{
  if ( value.X < 0 )
    value.X = 0;

  if ( value.Y < 0 )
    value.Y = 0;

  if ( !EwCompPoint( _this->AccentSizeFocused, value ))
    return;

  _this->AccentSizeFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetAccentSizeDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetAccentSizeDisabled( WidgetSetHorizontalSliderConfig _this, 
  XPoint value )
{
  if ( value.X < 0 )
    value.X = 0;

  if ( value.Y < 0 )
    value.Y = 0;

  if ( !EwCompPoint( _this->AccentSizeDisabled, value ))
    return;

  _this->AccentSizeDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetAccentSizeDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetAccentSizeDefault( WidgetSetHorizontalSliderConfig _this, 
  XPoint value )
{
  if ( value.X < 0 )
    value.X = 0;

  if ( value.Y < 0 )
    value.Y = 0;

  if ( !EwCompPoint( _this->AccentSizeDefault, value ))
    return;

  _this->AccentSizeDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbColorActive()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbColorActive( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->ThumbColorActive, value ))
    return;

  _this->ThumbColorActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbColorFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbColorFocused( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->ThumbColorFocused, value ))
    return;

  _this->ThumbColorFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbColorDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbColorDisabled( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->ThumbColorDisabled, value ))
    return;

  _this->ThumbColorDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbColorDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbColorDefault( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->ThumbColorDefault, value ))
    return;

  _this->ThumbColorDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbCornerRadiusActive()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbCornerRadiusActive( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->ThumbCornerRadiusActive == value )
    return;

  _this->ThumbCornerRadiusActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbCornerRadiusFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbCornerRadiusFocused( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->ThumbCornerRadiusFocused == value )
    return;

  _this->ThumbCornerRadiusFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbCornerRadiusDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbCornerRadiusDisabled( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->ThumbCornerRadiusDisabled == value )
    return;

  _this->ThumbCornerRadiusDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbCornerRadiusDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbCornerRadiusDefault( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->ThumbCornerRadiusDefault == value )
    return;

  _this->ThumbCornerRadiusDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbSizeActive()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbSizeActive( WidgetSetHorizontalSliderConfig _this, 
  XPoint value )
{
  if ( value.X < 0 )
    value.X = 0;

  if ( value.Y < 0 )
    value.Y = 0;

  if ( !EwCompPoint( _this->ThumbSizeActive, value ))
    return;

  _this->ThumbSizeActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbSizeFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbSizeFocused( WidgetSetHorizontalSliderConfig _this, 
  XPoint value )
{
  if ( value.X < 0 )
    value.X = 0;

  if ( value.Y < 0 )
    value.Y = 0;

  if ( !EwCompPoint( _this->ThumbSizeFocused, value ))
    return;

  _this->ThumbSizeFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbSizeDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbSizeDisabled( WidgetSetHorizontalSliderConfig _this, 
  XPoint value )
{
  if ( value.X < 0 )
    value.X = 0;

  if ( value.Y < 0 )
    value.Y = 0;

  if ( !EwCompPoint( _this->ThumbSizeDisabled, value ))
    return;

  _this->ThumbSizeDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbSizeDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbSizeDefault( WidgetSetHorizontalSliderConfig _this, 
  XPoint value )
{
  if ( value.X < 0 )
    value.X = 0;

  if ( value.Y < 0 )
    value.Y = 0;

  if ( !EwCompPoint( _this->ThumbSizeDefault, value ))
    return;

  _this->ThumbSizeDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbMarginRight()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbMarginRight( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->ThumbMarginRight == value )
    return;

  _this->ThumbMarginRight = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetThumbMarginLeft()' */
void WidgetSetHorizontalSliderConfig_OnSetThumbMarginLeft( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( _this->ThumbMarginLeft == value )
    return;

  _this->ThumbMarginLeft = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightColorActive()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightColorActive( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->TrackRightColorActive, value ))
    return;

  _this->TrackRightColorActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightColorFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightColorFocused( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->TrackRightColorFocused, value ))
    return;

  _this->TrackRightColorFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightColorDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightColorDefault( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->TrackRightColorDefault, value ))
    return;

  _this->TrackRightColorDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightCornerRadiusActive()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightCornerRadiusActive( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackRightCornerRadiusActive == value )
    return;

  _this->TrackRightCornerRadiusActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightCornerRadiusFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightCornerRadiusFocused( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackRightCornerRadiusFocused == value )
    return;

  _this->TrackRightCornerRadiusFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightCornerRadiusDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightCornerRadiusDisabled( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackRightCornerRadiusDisabled == value )
    return;

  _this->TrackRightCornerRadiusDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightCornerRadiusDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightCornerRadiusDefault( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackRightCornerRadiusDefault == value )
    return;

  _this->TrackRightCornerRadiusDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightThicknessActive()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightThicknessActive( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackRightThicknessActive == value )
    return;

  _this->TrackRightThicknessActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightThicknessFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightThicknessFocused( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackRightThicknessFocused == value )
    return;

  _this->TrackRightThicknessFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightThicknessDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightThicknessDisabled( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackRightThicknessDisabled == value )
    return;

  _this->TrackRightThicknessDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightThicknessDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightThicknessDefault( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackRightThicknessDefault == value )
    return;

  _this->TrackRightThicknessDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackRightFlattened()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackRightFlattened( WidgetSetHorizontalSliderConfig _this, 
  XBool value )
{
  if ( _this->TrackRightFlattened == value )
    return;

  _this->TrackRightFlattened = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftColorActive()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftColorActive( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->TrackLeftColorActive, value ))
    return;

  _this->TrackLeftColorActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftColorFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftColorFocused( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->TrackLeftColorFocused, value ))
    return;

  _this->TrackLeftColorFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftColorDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftColorDisabled( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->TrackLeftColorDisabled, value ))
    return;

  _this->TrackLeftColorDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftColorDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftColorDefault( WidgetSetHorizontalSliderConfig _this, 
  XColor value )
{
  if ( !EwCompColor( _this->TrackLeftColorDefault, value ))
    return;

  _this->TrackLeftColorDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftCornerRadiusActive()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftCornerRadiusActive( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackLeftCornerRadiusActive == value )
    return;

  _this->TrackLeftCornerRadiusActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftCornerRadiusFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftCornerRadiusFocused( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackLeftCornerRadiusFocused == value )
    return;

  _this->TrackLeftCornerRadiusFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftCornerRadiusDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftCornerRadiusDisabled( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackLeftCornerRadiusDisabled == value )
    return;

  _this->TrackLeftCornerRadiusDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftCornerRadiusDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftCornerRadiusDefault( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackLeftCornerRadiusDefault == value )
    return;

  _this->TrackLeftCornerRadiusDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftThicknessActive()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftThicknessActive( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackLeftThicknessActive == value )
    return;

  _this->TrackLeftThicknessActive = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftThicknessFocused()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftThicknessFocused( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackLeftThicknessFocused == value )
    return;

  _this->TrackLeftThicknessFocused = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftThicknessDisabled()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftThicknessDisabled( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackLeftThicknessDisabled == value )
    return;

  _this->TrackLeftThicknessDisabled = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftThicknessDefault()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftThicknessDefault( WidgetSetHorizontalSliderConfig _this, 
  XInt32 value )
{
  if ( value < 0 )
    value = 0;

  if ( _this->TrackLeftThicknessDefault == value )
    return;

  _this->TrackLeftThicknessDefault = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetTrackLeftFlattened()' */
void WidgetSetHorizontalSliderConfig_OnSetTrackLeftFlattened( WidgetSetHorizontalSliderConfig _this, 
  XBool value )
{
  if ( _this->TrackLeftFlattened == value )
    return;

  _this->TrackLeftFlattened = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSliderConfig.OnSetWidgetMinSize()' */
void WidgetSetHorizontalSliderConfig_OnSetWidgetMinSize( WidgetSetHorizontalSliderConfig _this, 
  XPoint value )
{
  if ( value.X < 0 )
    value.X = 0;

  if ( value.Y < 0 )
    value.Y = 0;

  if ( !EwCompPoint( _this->WidgetMinSize, value ))
    return;

  _this->WidgetMinSize = value;
  EwPostSignal( EwNewSlot( _this, WidgetSetWidgetConfig_onInvalidate ), ((XObject)_this ));
}

/* Variants derived from the class : 'WidgetSet::HorizontalSliderConfig' */
EW_DEFINE_CLASS_VARIANTS( WidgetSetHorizontalSliderConfig )
EW_END_OF_CLASS_VARIANTS( WidgetSetHorizontalSliderConfig )

/* Virtual Method Table (VMT) for the class : 'WidgetSet::HorizontalSliderConfig' */
EW_DEFINE_CLASS( WidgetSetHorizontalSliderConfig, WidgetSetWidgetConfig, _.VMT, 
                 _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, "WidgetSet::HorizontalSliderConfig" )
EW_END_OF_CLASS( WidgetSetHorizontalSliderConfig )

/* Initializer for the class 'WidgetSet::WidgetConfig' */
void WidgetSetWidgetConfig__Init( WidgetSetWidgetConfig _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  XObject__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( WidgetSetWidgetConfig );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( WidgetSetWidgetConfig );
}

/* Re-Initializer for the class 'WidgetSet::WidgetConfig' */
void WidgetSetWidgetConfig__ReInit( WidgetSetWidgetConfig _this )
{
  /* At first re-initialize the super class ... */
  XObject__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'WidgetSet::WidgetConfig' */
void WidgetSetWidgetConfig__Done( WidgetSetWidgetConfig _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( XObject );

  /* Don't forget to deinitialize the super class ... */
  XObject__Done( &_this->_.Super );
}

/* 'C' function for method : 'WidgetSet::WidgetConfig.onInvalidate()' */
void WidgetSetWidgetConfig_onInvalidate( WidgetSetWidgetConfig _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  EwNotifyObjObservers((XObject)_this, 0 );
}

/* Variants derived from the class : 'WidgetSet::WidgetConfig' */
EW_DEFINE_CLASS_VARIANTS( WidgetSetWidgetConfig )
EW_END_OF_CLASS_VARIANTS( WidgetSetWidgetConfig )

/* Virtual Method Table (VMT) for the class : 'WidgetSet::WidgetConfig' */
EW_DEFINE_CLASS( WidgetSetWidgetConfig, XObject, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "WidgetSet::WidgetConfig" )
EW_END_OF_CLASS( WidgetSetWidgetConfig )

/* Initializer for the class 'WidgetSet::HorizontalSlider' */
void WidgetSetHorizontalSlider__Init( WidgetSetHorizontalSlider _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( WidgetSetHorizontalSlider );

  /* ... then construct all embedded objects */
  CoreTimer__Init( &_this->RepetitionTimer, &_this->_.XObject, 0 );
  CoreKeyPressHandler__Init( &_this->KeyHandlerLeft, &_this->_.XObject, 0 );
  CoreKeyPressHandler__Init( &_this->KeyHandlerRight, &_this->_.XObject, 0 );
  CoreSimpleTouchHandler__Init( &_this->TouchHandler, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( WidgetSetHorizontalSlider );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0000 );
  CoreTimer_OnSetPeriod( &_this->RepetitionTimer, 0 );
  CoreTimer_OnSetBegin( &_this->RepetitionTimer, 50 );
  _this->KeyHandlerLeft.Filter = CoreKeyCodeLeft;
  _this->KeyHandlerRight.Filter = CoreKeyCodeRight;
  CoreView_OnSetLayout((CoreView)&_this->TouchHandler, CoreLayoutAlignToBottom | 
  CoreLayoutAlignToLeft | CoreLayoutAlignToRight | CoreLayoutAlignToTop | CoreLayoutResizeHorz 
  | CoreLayoutResizeVert );
  CoreQuadView__OnSetPoint4( &_this->TouchHandler, _Const0001 );
  CoreQuadView__OnSetPoint3( &_this->TouchHandler, _Const0002 );
  CoreQuadView__OnSetPoint2( &_this->TouchHandler, _Const0003 );
  CoreQuadView__OnSetPoint1( &_this->TouchHandler, _Const0004 );
  CoreSimpleTouchHandler_OnSetRetargetOffset( &_this->TouchHandler, 16 );
  CoreSimpleTouchHandler_OnSetMaxStrikeCount( &_this->TouchHandler, 100 );
  _this->CurrentValue = 50;
  CoreGroup__Add( _this, ((CoreView)&_this->TouchHandler ), 0 );
  _this->RepetitionTimer.OnTrigger = EwNewSlot( _this, WidgetSetHorizontalSlider_onRepetitionTimer );
  _this->KeyHandlerLeft.OnRelease = EwNewSlot( _this, WidgetSetHorizontalSlider_onReleaseKey );
  _this->KeyHandlerLeft.OnPress = EwNewSlot( _this, WidgetSetHorizontalSlider_onPressKey );
  _this->KeyHandlerRight.OnRelease = EwNewSlot( _this, WidgetSetHorizontalSlider_onReleaseKey );
  _this->KeyHandlerRight.OnPress = EwNewSlot( _this, WidgetSetHorizontalSlider_onPressKey );
  _this->TouchHandler.OnDrag = EwNewSlot( _this, WidgetSetHorizontalSlider_onDragTouch );
  _this->TouchHandler.OnRelease = EwNewSlot( _this, WidgetSetHorizontalSlider_onReleaseTouch );
  _this->TouchHandler.OnPress = EwNewSlot( _this, WidgetSetHorizontalSlider_onPressTouch );
}

/* Re-Initializer for the class 'WidgetSet::HorizontalSlider' */
void WidgetSetHorizontalSlider__ReInit( WidgetSetHorizontalSlider _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreTimer__ReInit( &_this->RepetitionTimer );
  CoreKeyPressHandler__ReInit( &_this->KeyHandlerLeft );
  CoreKeyPressHandler__ReInit( &_this->KeyHandlerRight );
  CoreSimpleTouchHandler__ReInit( &_this->TouchHandler );
}

/* Finalizer method for the class 'WidgetSet::HorizontalSlider' */
void WidgetSetHorizontalSlider__Done( WidgetSetHorizontalSlider _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Finalize all embedded objects */
  CoreTimer__Done( &_this->RepetitionTimer );
  CoreKeyPressHandler__Done( &_this->KeyHandlerLeft );
  CoreKeyPressHandler__Done( &_this->KeyHandlerRight );
  CoreSimpleTouchHandler__Done( &_this->TouchHandler );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.OnSetBounds()' */
void WidgetSetHorizontalSlider_OnSetBounds( WidgetSetHorizontalSlider _this, XRect 
  value )
{
  if ( _this->Appearance != 0 )
  {
    XPoint cs = EwGetRectSize( value );
    XPoint ns = cs;
    XPoint delta;

    if ( ns.X < _this->Appearance->WidgetMinSize.X )
      ns.X = _this->Appearance->WidgetMinSize.X;

    if ( ns.Y < _this->Appearance->WidgetMinSize.Y )
      ns.Y = _this->Appearance->WidgetMinSize.Y;

    delta = EwMovePointNeg( ns, cs );

    if ( delta.X != 0 )
    {
      XBool alignToLeft = (( _this->Super3.Layout & CoreLayoutAlignToLeft ) == CoreLayoutAlignToLeft );
      XBool alignToRight = (( _this->Super3.Layout & CoreLayoutAlignToRight ) == 
        CoreLayoutAlignToRight );

      if ( alignToLeft && !alignToRight )
        value.Point2.X = ( value.Point2.X + delta.X );
      else
        if ( !alignToLeft && alignToRight )
          value.Point1.X = ( value.Point1.X - delta.X );
        else
        {
          value.Point1.X = ( value.Point1.X - ( delta.X / 2 ));
          value.Point2.X = ( value.Point1.X + ns.X );
        }
    }

    if ( delta.Y != 0 )
    {
      XBool alignToTop = (( _this->Super3.Layout & CoreLayoutAlignToTop ) == CoreLayoutAlignToTop );
      XBool alignToBottom = (( _this->Super3.Layout & CoreLayoutAlignToBottom ) 
        == CoreLayoutAlignToBottom );

      if ( alignToTop && !alignToBottom )
        value.Point2.Y = ( value.Point2.Y + delta.Y );
      else
        if ( !alignToTop && alignToBottom )
          value.Point1.Y = ( value.Point1.Y - delta.Y );
        else
        {
          value.Point1.Y = ( value.Point1.Y - ( delta.Y / 2 ));
          value.Point2.Y = ( value.Point1.Y + ns.Y );
        }
    }
  }

  CoreGroup_OnSetBounds((CoreGroup)_this, value );
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
void WidgetSetHorizontalSlider_UpdateViewState( WidgetSetHorizontalSlider _this, 
  XSet aState )
{
  XBool needsRect1;
  XBool needsRect2;
  XBool needsRect3;
  XBool needsRect4;
  XBool needsOutline1;
  XBool needsOutline2;
  XRect area;
  XInt32 trackLeftThickness;
  XInt32 trackLeftCornerRadius;
  XInt32 trackRightThickness;
  XInt32 trackRightCornerRadius;
  XPoint thumbSize;
  XInt32 thumbCornerRadius;
  XPoint accentSize;
  XInt32 accentCornerRadius;
  XChar isState;
  XBool needsAnimation;
  XBool startAnimation;
  XInt32 marginLeft;
  XInt32 marginRight;
  XInt32 minPos;
  XInt32 maxPos;
  XInt32 newThumbPos;
  XRect r;

  CoreGroup_UpdateViewState((CoreGroup)_this, aState );
  needsRect1 = (XBool)((( _this->Appearance != 0 ) && ((( !EwIsColorNull( _this->Appearance->TrackLeftColorDefault ) 
  || !EwIsColorNull( _this->Appearance->TrackLeftColorDisabled )) || !EwIsColorNull( 
  _this->Appearance->TrackLeftColorFocused )) || !EwIsColorNull( _this->Appearance->TrackLeftColorActive ))) 
  && ((( !!_this->Appearance->TrackLeftThicknessDefault || !!_this->Appearance->TrackLeftThicknessDisabled ) 
  || !!_this->Appearance->TrackLeftThicknessFocused ) || !!_this->Appearance->TrackLeftThicknessActive ));
  needsRect2 = (XBool)((( _this->Appearance != 0 ) && (( !EwIsColorNull( _this->Appearance->TrackRightColorDefault ) 
  || !EwIsColorNull( _this->Appearance->TrackRightColorFocused )) || !EwIsColorNull( 
  _this->Appearance->TrackRightColorActive ))) && ((( !!_this->Appearance->TrackRightThicknessDefault 
  || !!_this->Appearance->TrackRightThicknessDisabled ) || !!_this->Appearance->TrackRightThicknessFocused ) 
  || !!_this->Appearance->TrackRightThicknessActive ));
  needsRect3 = (XBool)((( _this->Appearance != 0 ) && ((( !EwIsColorNull( _this->Appearance->ThumbColorDefault ) 
  || !EwIsColorNull( _this->Appearance->ThumbColorDisabled )) || !EwIsColorNull( 
  _this->Appearance->ThumbColorFocused )) || !EwIsColorNull( _this->Appearance->ThumbColorActive ))) 
  && ((( !EwIsPointNull( _this->Appearance->ThumbSizeDefault ) || !EwIsPointNull( 
  _this->Appearance->ThumbSizeDisabled )) || !EwIsPointNull( _this->Appearance->ThumbSizeFocused )) 
  || !EwIsPointNull( _this->Appearance->ThumbSizeActive )));
  needsRect4 = (XBool)((( _this->Appearance != 0 ) && ((( !EwIsColorNull( _this->Appearance->AccentColorDefault ) 
  || !EwIsColorNull( _this->Appearance->AccentColorDisabled )) || !EwIsColorNull( 
  _this->Appearance->AccentColorFocused )) || !EwIsColorNull( _this->Appearance->AccentColorActive ))) 
  && ((( !EwIsPointNull( _this->Appearance->AccentSizeDefault ) || !EwIsPointNull( 
  _this->Appearance->AccentSizeDisabled )) || !EwIsPointNull( _this->Appearance->AccentSizeFocused )) 
  || !EwIsPointNull( _this->Appearance->AccentSizeActive )));
  needsOutline1 = (XBool)(( needsRect1 && ( _this->Appearance != 0 )) && ((( !!_this->Appearance->TrackLeftCornerRadiusDefault 
  || !!_this->Appearance->TrackLeftCornerRadiusDisabled ) || !!_this->Appearance->TrackLeftCornerRadiusFocused ) 
  || !!_this->Appearance->TrackLeftCornerRadiusActive ));
  needsOutline2 = (XBool)(( needsRect2 && ( _this->Appearance != 0 )) && ((( !!_this->Appearance->TrackRightCornerRadiusDefault 
  || !!_this->Appearance->TrackRightCornerRadiusDisabled ) || !!_this->Appearance->TrackRightCornerRadiusFocused ) 
  || !!_this->Appearance->TrackRightCornerRadiusActive ));
  area = EwGetRectORect( _this->Super2.Bounds );
  trackLeftThickness = 0;
  trackLeftCornerRadius = 0;
  trackRightThickness = 0;
  trackRightCornerRadius = 0;
  thumbSize = _Const0004;
  thumbCornerRadius = 0;
  accentSize = _Const0004;
  accentCornerRadius = 0;

  if ( needsRect1 && !( _this->rectView1 != 0 ))
  {
    _this->rectView1 = EwNewObject( ViewsRectangle, 0 );
    CoreGroup__Add( _this, ((CoreView)_this->rectView1 ), 0 );
  }
  else
    if ( !needsRect1 && ( _this->rectView1 != 0 ))
    {
      CoreGroup__Remove( _this, ((CoreView)_this->rectView1 ));
      _this->rectView1 = 0;
    }

  if ( needsRect2 && !( _this->rectView2 != 0 ))
  {
    _this->rectView2 = EwNewObject( ViewsRectangle, 0 );
    CoreGroup__Add( _this, ((CoreView)_this->rectView2 ), 0 );
  }
  else
    if ( !needsRect2 && ( _this->rectView2 != 0 ))
    {
      CoreGroup__Remove( _this, ((CoreView)_this->rectView2 ));
      _this->rectView2 = 0;
    }

  if ( needsRect3 && !( _this->rectView3 != 0 ))
  {
    _this->rectView3 = EwNewObject( ViewsRectangle, 0 );
    CoreGroup__Add( _this, ((CoreView)_this->rectView3 ), 0 );
  }
  else
    if ( !needsRect3 && ( _this->rectView3 != 0 ))
    {
      CoreGroup__Remove( _this, ((CoreView)_this->rectView3 ));
      _this->rectView3 = 0;
    }

  if ( needsRect4 && !( _this->rectView4 != 0 ))
  {
    _this->rectView4 = EwNewObject( ViewsRectangle, 0 );
    CoreGroup__Add( _this, ((CoreView)_this->rectView4 ), 0 );
  }
  else
    if ( !needsRect4 && ( _this->rectView4 != 0 ))
    {
      CoreGroup__Remove( _this, ((CoreView)_this->rectView4 ));
      _this->rectView4 = 0;
    }

  if ( needsOutline1 && !( _this->outline1 != 0 ))
  {
    _this->outline1 = EwNewObject( CoreOutline, 0 );
    CoreGroup__Add( _this, ((CoreView)_this->outline1 ), 0 );
  }
  else
    if ( !needsOutline1 && ( _this->outline1 != 0 ))
    {
      CoreGroup__Remove( _this, ((CoreView)_this->outline1 ));
      _this->outline1 = 0;
    }

  if ( needsOutline2 && !( _this->outline2 != 0 ))
  {
    _this->outline2 = EwNewObject( CoreOutline, 0 );
    CoreGroup__Add( _this, ((CoreView)_this->outline2 ), 0 );
  }
  else
    if ( !needsOutline2 && ( _this->outline2 != 0 ))
    {
      CoreGroup__Remove( _this, ((CoreView)_this->outline2 ));
      _this->outline2 = 0;
    }

  if ( !(( aState & CoreViewStateEnabled ) == CoreViewStateEnabled ))
    isState = 'D';
  else
    if (( _this->touchActive || _this->KeyHandlerRight.Down ) || _this->KeyHandlerLeft.Down )
      isState = 'A';
    else
      if ((( aState & CoreViewStateFocused ) == CoreViewStateFocused ))
        isState = 'F';
      else
        isState = 'E';

  needsAnimation = (XBool)(( _this->Appearance != 0 ) && !!_this->Appearance->StateTransitionDuration );
  startAnimation = (XBool)(( needsAnimation && ( _this->prevState != isState )) 
  && !!_this->prevState );

  if ((( startAnimation && ( _this->animation != 0 )) && !_this->animation->Super1.Reversed ) 
      && ( isState == _this->animStartState ))
  {
    EffectsEffect_OnSetReversed((EffectsEffect)_this->animation, 1 );
    startAnimation = 0;
  }

  if ((( startAnimation && ( _this->animation != 0 )) && _this->animation->Super1.Reversed ) 
      && ( isState == _this->animEndState ))
  {
    EffectsEffect_OnSetReversed((EffectsEffect)_this->animation, 0 );
    startAnimation = 0;
  }

  if (( _this->animation != 0 ) && (( !_this->animation->Super1.Enabled || startAnimation ) 
      || !needsAnimation ))
  {
    EffectsEffect_OnSetEnabled((EffectsEffect)_this->animation, 0 );
    _this->animation->Super1.OnAnimate = EwNullSlot;
    _this->animation->Super1.OnFinished = EwNullSlot;
    _this->animation = 0;
  }

  if ( startAnimation )
  {
    _this->animation = EwNewObject( EffectsFloatEffect, 0 );
    _this->animation->Super1.OnAnimate = EwNewSlot( _this, WidgetSetHorizontalSlider_onAnimate );
    _this->animation->Super1.OnFinished = EwNewSlot( _this, WidgetSetHorizontalSlider_onAnimate );
    EffectsEffect_OnSetCycleDuration((EffectsEffect)_this->animation, _this->Appearance->StateTransitionDuration );
    EffectsEffect_OnSetNoOfCycles((EffectsEffect)_this->animation, 1 );
    EffectsEffect_OnSetEnabled((EffectsEffect)_this->animation, 1 );
    _this->animStartState = _this->prevState;
    _this->animEndState = isState;
  }

  _this->prevState = isState;

  if ( _this->rectView1 != 0 )
  {
    switch ((( _this->animation != 0 )? _this->animEndState : isState ))
    {
      case 'D' :
      case 'A' :
      case 'F' :
      break;

      default :; 
    }

    if ( _this->animation != 0 )
      switch ( _this->animStartState )
      {
        case 'D' :
        case 'A' :
        case 'F' :
        break;

        default :; 
      }
  }

  if ( _this->rectView2 != 0 )
  {
    switch ((( _this->animation != 0 )? _this->animEndState : isState ))
    {
      case 'D' :
      case 'A' :
      case 'F' :
      break;

      default :; 
    }

    if ( _this->animation != 0 )
      switch ( _this->animStartState )
      {
        case 'D' :
        case 'A' :
        case 'F' :
        break;

        default :; 
      }
  }

  if ( _this->rectView1 != 0 )
  {
    switch ((( _this->animation != 0 )? _this->animEndState : isState ))
    {
      case 'D' :
      {
        trackLeftThickness = _this->Appearance->TrackLeftThicknessDisabled;
        trackLeftCornerRadius = _this->Appearance->TrackLeftCornerRadiusDisabled;
      }
      break;

      case 'A' :
      {
        trackLeftThickness = _this->Appearance->TrackLeftThicknessActive;
        trackLeftCornerRadius = _this->Appearance->TrackLeftCornerRadiusActive;
      }
      break;

      case 'F' :
      {
        trackLeftThickness = _this->Appearance->TrackLeftThicknessFocused;
        trackLeftCornerRadius = _this->Appearance->TrackLeftCornerRadiusFocused;
      }
      break;

      default : 
      {
        trackLeftThickness = _this->Appearance->TrackLeftThicknessDefault;
        trackLeftCornerRadius = _this->Appearance->TrackLeftCornerRadiusDefault;
      }
    }

    if ( _this->animation != 0 )
    {
      XInt32 trackLeftThicknessS;
      XInt32 trackLeftCornerRadiusS;

      switch ( _this->animStartState )
      {
        case 'D' :
        {
          trackLeftThicknessS = _this->Appearance->TrackLeftThicknessDisabled;
          trackLeftCornerRadiusS = _this->Appearance->TrackLeftCornerRadiusDisabled;
        }
        break;

        case 'A' :
        {
          trackLeftThicknessS = _this->Appearance->TrackLeftThicknessActive;
          trackLeftCornerRadiusS = _this->Appearance->TrackLeftCornerRadiusActive;
        }
        break;

        case 'F' :
        {
          trackLeftThicknessS = _this->Appearance->TrackLeftThicknessFocused;
          trackLeftCornerRadiusS = _this->Appearance->TrackLeftCornerRadiusFocused;
        }
        break;

        default : 
        {
          trackLeftThicknessS = _this->Appearance->TrackLeftThicknessDefault;
          trackLeftCornerRadiusS = _this->Appearance->TrackLeftCornerRadiusDefault;
        }
      }

      trackLeftCornerRadius = EwMathMixInt32( trackLeftCornerRadiusS, trackLeftCornerRadius, 
      _this->animation->Value );
      trackLeftThickness = EwMathMixInt32( trackLeftThicknessS, trackLeftThickness, 
      _this->animation->Value );
    }
  }

  if ( _this->rectView2 != 0 )
  {
    switch ((( _this->animation != 0 )? _this->animEndState : isState ))
    {
      case 'D' :
      {
        trackRightThickness = _this->Appearance->TrackRightThicknessDisabled;
        trackRightCornerRadius = _this->Appearance->TrackRightCornerRadiusDisabled;
      }
      break;

      case 'A' :
      {
        trackRightThickness = _this->Appearance->TrackRightThicknessActive;
        trackRightCornerRadius = _this->Appearance->TrackRightCornerRadiusActive;
      }
      break;

      case 'F' :
      {
        trackRightThickness = _this->Appearance->TrackRightThicknessFocused;
        trackRightCornerRadius = _this->Appearance->TrackRightCornerRadiusFocused;
      }
      break;

      default : 
      {
        trackRightThickness = _this->Appearance->TrackRightThicknessDefault;
        trackRightCornerRadius = _this->Appearance->TrackRightCornerRadiusDefault;
      }
    }

    if ( _this->animation != 0 )
    {
      XInt32 trackRightThicknessS;
      XInt32 trackRightCornerRadiusS;

      switch ( _this->animStartState )
      {
        case 'D' :
        {
          trackRightThicknessS = _this->Appearance->TrackRightThicknessDisabled;
          trackRightCornerRadiusS = _this->Appearance->TrackRightCornerRadiusDisabled;
        }
        break;

        case 'A' :
        {
          trackRightThicknessS = _this->Appearance->TrackRightThicknessActive;
          trackRightCornerRadiusS = _this->Appearance->TrackRightCornerRadiusActive;
        }
        break;

        case 'F' :
        {
          trackRightThicknessS = _this->Appearance->TrackRightThicknessFocused;
          trackRightCornerRadiusS = _this->Appearance->TrackRightCornerRadiusFocused;
        }
        break;

        default : 
        {
          trackRightThicknessS = _this->Appearance->TrackRightThicknessDefault;
          trackRightCornerRadiusS = _this->Appearance->TrackRightCornerRadiusDefault;
        }
      }

      trackRightCornerRadius = EwMathMixInt32( trackRightCornerRadiusS, trackRightCornerRadius, 
      _this->animation->Value );
      trackRightThickness = EwMathMixInt32( trackRightThicknessS, trackRightThickness, 
      _this->animation->Value );
    }
  }

  if ( _this->rectView3 != 0 )
  {
    switch ((( _this->animation != 0 )? _this->animEndState : isState ))
    {
      case 'D' :
      case 'A' :
      case 'F' :
      break;

      default :; 
    }

    if ( _this->animation != 0 )
      switch ( _this->animStartState )
      {
        case 'D' :
        case 'A' :
        case 'F' :
        break;

        default :; 
      }
  }

  if ( _this->rectView3 != 0 )
  {
    switch ((( _this->animation != 0 )? _this->animEndState : isState ))
    {
      case 'D' :
      {
        thumbSize = _this->Appearance->ThumbSizeDisabled;
        thumbCornerRadius = _this->Appearance->ThumbCornerRadiusDisabled;
      }
      break;

      case 'A' :
      {
        thumbSize = _this->Appearance->ThumbSizeActive;
        thumbCornerRadius = _this->Appearance->ThumbCornerRadiusActive;
      }
      break;

      case 'F' :
      {
        thumbSize = _this->Appearance->ThumbSizeFocused;
        thumbCornerRadius = _this->Appearance->ThumbCornerRadiusFocused;
      }
      break;

      default : 
      {
        thumbSize = _this->Appearance->ThumbSizeDefault;
        thumbCornerRadius = _this->Appearance->ThumbCornerRadiusDefault;
      }
    }

    if ( _this->animation != 0 )
    {
      XPoint thumbSizeS;
      XInt32 thumbCornerRadiusS;

      switch ( _this->animStartState )
      {
        case 'D' :
        {
          thumbSizeS = _this->Appearance->ThumbSizeDisabled;
          thumbCornerRadiusS = _this->Appearance->ThumbCornerRadiusDisabled;
        }
        break;

        case 'A' :
        {
          thumbSizeS = _this->Appearance->ThumbSizeActive;
          thumbCornerRadiusS = _this->Appearance->ThumbCornerRadiusActive;
        }
        break;

        case 'F' :
        {
          thumbSizeS = _this->Appearance->ThumbSizeFocused;
          thumbCornerRadiusS = _this->Appearance->ThumbCornerRadiusFocused;
        }
        break;

        default : 
        {
          thumbSizeS = _this->Appearance->ThumbSizeDefault;
          thumbCornerRadiusS = _this->Appearance->ThumbCornerRadiusDefault;
        }
      }

      thumbCornerRadius = EwMathMixInt32( thumbCornerRadiusS, thumbCornerRadius, 
      _this->animation->Value );
      thumbSize = EwMathMixPoint( thumbSizeS, thumbSize, _this->animation->Value );
    }
  }

  if ( _this->rectView4 != 0 )
  {
    switch ((( _this->animation != 0 )? _this->animEndState : isState ))
    {
      case 'D' :
      {
        accentSize = _this->Appearance->AccentSizeDisabled;
        accentCornerRadius = _this->Appearance->AccentCornerRadiusDisabled;
      }
      break;

      case 'A' :
      {
        accentSize = _this->Appearance->AccentSizeActive;
        accentCornerRadius = _this->Appearance->AccentCornerRadiusActive;
      }
      break;

      case 'F' :
      {
        accentSize = _this->Appearance->AccentSizeFocused;
        accentCornerRadius = _this->Appearance->AccentCornerRadiusFocused;
      }
      break;

      default : 
      {
        accentSize = _this->Appearance->AccentSizeDefault;
        accentCornerRadius = _this->Appearance->AccentCornerRadiusDefault;
      }
    }

    if ( _this->animation != 0 )
    {
      XPoint accentSizeS;
      XInt32 accentCornerRadiusS;

      switch ( _this->animStartState )
      {
        case 'D' :
        {
          accentSizeS = _this->Appearance->AccentSizeDisabled;
          accentCornerRadiusS = _this->Appearance->AccentCornerRadiusDisabled;
        }
        break;

        case 'A' :
        {
          accentSizeS = _this->Appearance->AccentSizeActive;
          accentCornerRadiusS = _this->Appearance->AccentCornerRadiusActive;
        }
        break;

        case 'F' :
        {
          accentSizeS = _this->Appearance->AccentSizeFocused;
          accentCornerRadiusS = _this->Appearance->AccentCornerRadiusFocused;
        }
        break;

        default : 
        {
          accentSizeS = _this->Appearance->AccentSizeDefault;
          accentCornerRadiusS = _this->Appearance->AccentCornerRadiusDefault;
        }
      }

      accentCornerRadius = EwMathMixInt32( accentCornerRadiusS, accentCornerRadius, 
      _this->animation->Value );
      accentSize = EwMathMixPoint( accentSizeS, accentSize, _this->animation->Value );
    }
  }

  if ( _this->rectView1 != 0 )
  {
    XColor clr;

    switch ((( _this->animation != 0 )? _this->animEndState : isState ))
    {
      case 'D' :
        clr = _this->Appearance->TrackLeftColorDisabled;
      break;

      case 'A' :
        clr = _this->Appearance->TrackLeftColorActive;
      break;

      case 'F' :
        clr = _this->Appearance->TrackLeftColorFocused;
      break;

      default : 
        clr = _this->Appearance->TrackLeftColorDefault;
    }

    if ( _this->animation != 0 )
    {
      XColor clrS;

      switch ( _this->animStartState )
      {
        case 'D' :
          clrS = _this->Appearance->TrackLeftColorDisabled;
        break;

        case 'A' :
          clrS = _this->Appearance->TrackLeftColorActive;
        break;

        case 'F' :
          clrS = _this->Appearance->TrackLeftColorFocused;
        break;

        default : 
          clrS = _this->Appearance->TrackLeftColorDefault;
      }

      clr = EwMathMixColor( clrS, clr, _this->animation->Value );
    }

    ViewsRectangle_OnSetRadius( _this->rectView1, trackLeftCornerRadius );
    ViewsRectangle_OnSetColor( _this->rectView1, clr );
    ViewsRectangle_OnSetEmbedded( _this->rectView1, _this->outline1 != 0 );
    CoreView_OnSetStackingPriority((CoreView)_this->rectView1, 52 );
  }

  if ( _this->rectView2 != 0 )
  {
    XColor clr;

    switch ((( _this->animation != 0 )? _this->animEndState : isState ))
    {
      case 'D' :
        clr = _Const0005;
      break;

      case 'A' :
        clr = _this->Appearance->TrackRightColorActive;
      break;

      case 'F' :
        clr = _this->Appearance->TrackRightColorFocused;
      break;

      default : 
        clr = _this->Appearance->TrackRightColorDefault;
    }

    if ( _this->animation != 0 )
    {
      XColor clrS;

      switch ( _this->animStartState )
      {
        case 'D' :
          clrS = _Const0005;
        break;

        case 'A' :
          clrS = _this->Appearance->TrackRightColorActive;
        break;

        case 'F' :
          clrS = _this->Appearance->TrackRightColorFocused;
        break;

        default : 
          clrS = _this->Appearance->TrackRightColorDefault;
      }

      clr = EwMathMixColor( clrS, clr, _this->animation->Value );
    }

    ViewsRectangle_OnSetRadius( _this->rectView2, trackRightCornerRadius );
    ViewsRectangle_OnSetColor( _this->rectView2, clr );
    ViewsRectangle_OnSetEmbedded( _this->rectView2, _this->outline2 != 0 );
    CoreView_OnSetStackingPriority((CoreView)_this->rectView2, 33 );
  }

  if ( _this->rectView3 != 0 )
  {
    XColor clr;

    switch ((( _this->animation != 0 )? _this->animEndState : isState ))
    {
      case 'D' :
        clr = _this->Appearance->ThumbColorDisabled;
      break;

      case 'A' :
        clr = _this->Appearance->ThumbColorActive;
      break;

      case 'F' :
        clr = _this->Appearance->ThumbColorFocused;
      break;

      default : 
        clr = _this->Appearance->ThumbColorDefault;
    }

    if ( _this->animation != 0 )
    {
      XColor clrS;

      switch ( _this->animStartState )
      {
        case 'D' :
          clrS = _this->Appearance->ThumbColorDisabled;
        break;

        case 'A' :
          clrS = _this->Appearance->ThumbColorActive;
        break;

        case 'F' :
          clrS = _this->Appearance->ThumbColorFocused;
        break;

        default : 
          clrS = _this->Appearance->ThumbColorDefault;
      }

      clr = EwMathMixColor( clrS, clr, _this->animation->Value );
    }

    ViewsRectangle_OnSetRadius( _this->rectView3, thumbCornerRadius );
    ViewsRectangle_OnSetColor( _this->rectView3, clr );
    CoreView_OnSetStackingPriority((CoreView)_this->rectView3, 72 );
  }

  if ( _this->rectView4 != 0 )
  {
    XColor clr;

    switch ((( _this->animation != 0 )? _this->animEndState : isState ))
    {
      case 'D' :
        clr = _this->Appearance->AccentColorDisabled;
      break;

      case 'A' :
        clr = _this->Appearance->AccentColorActive;
      break;

      case 'F' :
        clr = _this->Appearance->AccentColorFocused;
      break;

      default : 
        clr = _this->Appearance->AccentColorDefault;
    }

    if ( _this->animation != 0 )
    {
      XColor clrS;

      switch ( _this->animStartState )
      {
        case 'D' :
          clrS = _this->Appearance->AccentColorDisabled;
        break;

        case 'A' :
          clrS = _this->Appearance->AccentColorActive;
        break;

        case 'F' :
          clrS = _this->Appearance->AccentColorFocused;
        break;

        default : 
          clrS = _this->Appearance->AccentColorDefault;
      }

      clr = EwMathMixColor( clrS, clr, _this->animation->Value );
    }

    ViewsRectangle_OnSetRadius( _this->rectView4, accentCornerRadius );
    ViewsRectangle_OnSetColor( _this->rectView4, clr );
    CoreView_OnSetStackingPriority((CoreView)_this->rectView4, 93 );
  }

  marginLeft = (( _this->Appearance != 0 )? _this->Appearance->ThumbMarginLeft : 
  0 );
  marginRight = (( _this->Appearance != 0 )? _this->Appearance->ThumbMarginRight 
  : 0 );
  minPos = marginLeft;
  maxPos = EwGetRectW( area ) - marginRight;
  newThumbPos = (XInt32)(((XFloat)WidgetSetHorizontalSlider_OnGetCurrentValue( _this ) 
  * (XFloat)( maxPos - minPos )) / 100.0f ) + minPos;

  if ( newThumbPos < marginLeft )
    newThumbPos = marginLeft;

  if ( newThumbPos > ( EwGetRectW( area ) - marginRight ))
    newThumbPos = EwGetRectW( area ) - marginRight;

  if ( _this->outline1 != 0 )
  {
    XInt32 x2 = EwGetRectW( area );
    XInt32 x = newThumbPos;

    if ( x > x2 )
      x = x2;

    CoreRectView__OnSetBounds( _this->outline1, EwNewRect( 0, 0, x, EwGetRectH( 
    area )));
    CoreView_OnSetStackingPriority((CoreView)_this->outline1, 51 );
  }

  if ( _this->outline2 != 0 )
  {
    XInt32 x2 = EwGetRectW( area );
    XInt32 x = newThumbPos;

    if ( x < 0 )
      x = 0;

    CoreRectView__OnSetBounds( _this->outline2, EwNewRect( x, 0, x2, EwGetRectH( 
    area )));
    CoreView_OnSetStackingPriority((CoreView)_this->outline2, 32 );
  }

  if ( _this->rectView1 != 0 )
  {
    XInt32 h = trackLeftThickness;
    XInt32 x2 = EwGetRectW( area );
    XInt32 x = newThumbPos + ( _this->Appearance->TrackLeftFlattened? trackLeftCornerRadius 
      : 0 );
    XRect r;

    if ( x < ( 2 * trackLeftCornerRadius ))
      x = 2 * trackLeftCornerRadius;

    if ( x > x2 )
      x = x2;

    r = EwNewRect( 0, ( EwGetRectH( area ) / 2 ) - ( h / 2 ), x, (( EwGetRectH( 
    area ) / 2 ) - ( h / 2 )) + h );

    if ( _this->rectView1 != 0 )
      CoreRectView__OnSetBounds( _this->rectView1, r );
  }

  if ( _this->rectView2 != 0 )
  {
    XInt32 h = trackRightThickness;
    XInt32 x2 = EwGetRectW( area );
    XInt32 x = newThumbPos - ( _this->Appearance->TrackRightFlattened? trackRightCornerRadius 
      : 0 );
    XRect r;

    if (( x2 - x ) < ( 2 * trackRightCornerRadius ))
      x = x2 - ( 2 * trackRightCornerRadius );

    if ( x < 0 )
      x = 0;

    r = EwNewRect( x, ( EwGetRectH( area ) / 2 ) - ( h / 2 ), x2, (( EwGetRectH( 
    area ) / 2 ) - ( h / 2 )) + h );

    if ( _this->rectView2 != 0 )
      CoreRectView__OnSetBounds( _this->rectView2, r );
  }

  if ( _this->rectView3 != 0 )
  {
    XPoint o = EwNewPoint( newThumbPos - ( thumbSize.X / 2 ), ( EwGetRectH( area ) 
      / 2 ) - ( thumbSize.Y / 2 ));
    XRect r = EwMoveRectPos( EwNewRect2Point( _Const0004, thumbSize ), o );

    if ( _this->rectView3 != 0 )
      CoreRectView__OnSetBounds( _this->rectView3, r );
  }

  if ( _this->rectView4 != 0 )
  {
    XPoint o = EwNewPoint( newThumbPos - ( accentSize.X / 2 ), ( EwGetRectH( area ) 
      / 2 ) - ( accentSize.Y / 2 ));
    XRect r = EwMoveRectPos( EwNewRect2Point( _Const0004, accentSize ), o );

    if ( _this->rectView4 != 0 )
      CoreRectView__OnSetBounds( _this->rectView4, r );
  }

  r = _Const0006;

  if ( _this->rectView3 != 0 )
    r = EwUnionRect( r, _this->rectView3->Super1.Bounds );

  if ( _this->rectView4 != 0 )
    r = EwUnionRect( r, _this->rectView4->Super1.Bounds );

  CoreGroup__ExtendClipping( _this, EwGetInt32Max( 2, -r.Point1.X, 0 ), EwGetInt32Max( 
  2, r.Point2.X - area.Point2.X, 0 ), EwGetInt32Max( 2, -r.Point1.Y, 0 ), EwGetInt32Max( 
  2, r.Point2.Y - area.Point2.Y, 0 ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onAnimate()' */
void WidgetSetHorizontalSlider_onAnimate( WidgetSetHorizontalSlider _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onConfigChanged()' */
void WidgetSetHorizontalSlider_onConfigChanged( WidgetSetHorizontalSlider _this, 
  XObject sender )
{
  XEnum oldKeyCodeRight;
  XEnum oldKeyCodeLeft;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  oldKeyCodeRight = _this->KeyHandlerRight.Filter;
  oldKeyCodeLeft = _this->KeyHandlerLeft.Filter;
  _this->KeyHandlerRight.Filter = CoreKeyCodeRight;
  _this->KeyHandlerLeft.Filter = CoreKeyCodeLeft;

  if (((( oldKeyCodeRight == CoreKeyCodeNoKey ) || ( oldKeyCodeLeft == CoreKeyCodeNoKey )) 
      && ( _this->KeyHandlerRight.Filter != CoreKeyCodeNoKey )) && ( _this->KeyHandlerLeft.Filter 
      != CoreKeyCodeNoKey ))
    CoreView__ChangeViewState( _this, CoreViewStateFocusable, 0 );

  if ((( oldKeyCodeRight != CoreKeyCodeNoKey ) && ( oldKeyCodeLeft != CoreKeyCodeNoKey )) 
      && (( _this->KeyHandlerRight.Filter == CoreKeyCodeNoKey ) || ( _this->KeyHandlerLeft.Filter 
      == CoreKeyCodeNoKey )))
    CoreView__ChangeViewState( _this, 0, CoreViewStateFocusable );

  if ( _this->Appearance != 0 )
  {
    CoreTimer_OnSetBegin( &_this->RepetitionTimer, _this->Appearance->KeyRepeatDelay );
    CoreTimer_OnSetPeriod( &_this->RepetitionTimer, _this->Appearance->KeyRepeatPeriod );
  }
  else
  {
    CoreTimer_OnSetBegin( &_this->RepetitionTimer, 0 );
    CoreTimer_OnSetPeriod( &_this->RepetitionTimer, 0 );
  }

  if ( _this->Appearance != 0 )
    CoreRectView__OnSetBounds( _this, _this->Super2.Bounds );

  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onOutlet()' */
void WidgetSetHorizontalSlider_onOutlet( WidgetSetHorizontalSlider _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( _this->Outlet.Object != 0 )
    WidgetSetHorizontalSlider_OnSetCurrentValue( _this, EwOnGetInt32( _this->Outlet ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onRepetitionTimer()' */
void WidgetSetHorizontalSlider_onRepetitionTimer( WidgetSetHorizontalSlider _this, 
  XObject sender )
{
  XInt32 oldValue;
  XInt32 newValue;
  XInt32 delta;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  oldValue = WidgetSetHorizontalSlider_OnGetCurrentValue( _this );
  newValue = oldValue;
  delta = 1;

  if ( _this->KeyHandlerLeft.Down )
    delta = -1;

  if ( oldValue < 0 )
  {
    newValue = -newValue;
    delta = -delta;
  }

  if ( delta > 0 )
    newValue = ( newValue + delta ) - (( newValue + delta ) % delta );

  if ( delta < 0 )
  {
    if (( newValue % -delta ) != 0 )
      newValue = ( newValue - delta ) - ( newValue % -delta );

    newValue = newValue + delta;
  }

  if ( oldValue < 0 )
    newValue = -newValue;

  WidgetSetHorizontalSlider_OnSetCurrentValue( _this, newValue );

  if ( oldValue == WidgetSetHorizontalSlider_OnGetCurrentValue( _this ))
    return;

  EwPostSignal( _this->OnChange, ((XObject)_this ));

  if ( _this->Outlet.Object != 0 )
  {
    EwOnSetInt32( _this->Outlet, WidgetSetHorizontalSlider_OnGetCurrentValue( _this ));
    EwNotifyRefObservers( _this->Outlet, 0 );
  }
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onReleaseKey()' */
void WidgetSetHorizontalSlider_onReleaseKey( WidgetSetHorizontalSlider _this, XObject 
  sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreSimpleTouchHandler_OnSetEnabled( &_this->TouchHandler, 1 );
  CoreGroup_InvalidateViewState((CoreGroup)_this );
  CoreTimer_OnSetEnabled( &_this->RepetitionTimer, 0 );
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onPressKey()' */
void WidgetSetHorizontalSlider_onPressKey( WidgetSetHorizontalSlider _this, XObject 
  sender )
{
  XInt32 oldValue;
  XInt32 newValue;
  XInt32 delta;

  CoreSimpleTouchHandler_OnSetEnabled( &_this->TouchHandler, 0 );
  CoreGroup_InvalidateViewState((CoreGroup)_this );
  CoreTimer_OnSetEnabled( &_this->RepetitionTimer, 1 );
  oldValue = WidgetSetHorizontalSlider_OnGetCurrentValue( _this );
  newValue = oldValue;
  delta = 1;

  if ( sender == ((XObject)&_this->KeyHandlerLeft ))
    delta = -1;

  if ( oldValue < 0 )
  {
    newValue = -newValue;
    delta = -delta;
  }

  if ( delta > 0 )
    newValue = ( newValue + delta ) - (( newValue + delta ) % delta );

  if ( delta < 0 )
  {
    if (( newValue % -delta ) != 0 )
      newValue = ( newValue - delta ) - ( newValue % -delta );

    newValue = newValue + delta;
  }

  if ( oldValue < 0 )
    newValue = -newValue;

  WidgetSetHorizontalSlider_OnSetCurrentValue( _this, newValue );

  if ( oldValue == WidgetSetHorizontalSlider_OnGetCurrentValue( _this ))
    return;

  EwPostSignal( _this->OnChange, ((XObject)_this ));

  if ( _this->Outlet.Object != 0 )
  {
    EwOnSetInt32( _this->Outlet, WidgetSetHorizontalSlider_OnGetCurrentValue( _this ));
    EwNotifyRefObservers( _this->Outlet, 0 );
  }
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onDragTouch()' */
void WidgetSetHorizontalSlider_onDragTouch( WidgetSetHorizontalSlider _this, XObject 
  sender )
{
  XInt32 marginLeft;
  XInt32 marginRight;
  XPoint delta;
  XInt32 minPos;
  XInt32 maxPos;
  XInt32 oldValue;
  XInt32 newValue;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( !_this->touchActive )
    return;

  marginLeft = 0;
  marginRight = 0;

  if ( _this->Appearance != 0 )
  {
    marginLeft = _this->Appearance->ThumbMarginLeft;
    marginRight = _this->Appearance->ThumbMarginRight;
  }

  delta = EwMovePointNeg( _this->TouchHandler.CurrentPos, _this->TouchHandler.HittingPos );
  minPos = marginLeft;
  maxPos = EwGetRectW( _this->Super2.Bounds ) - marginRight;
  oldValue = WidgetSetHorizontalSlider_OnGetCurrentValue( _this );
  newValue = oldValue;

  if ( maxPos > minPos )
    newValue = (XInt32)(((XFloat)delta.X * 100.0f ) / (XFloat)( maxPos - minPos )) 
    + _this->touchStartValue;

  WidgetSetHorizontalSlider_OnSetCurrentValue( _this, newValue );

  if ( oldValue == WidgetSetHorizontalSlider_OnGetCurrentValue( _this ))
    return;

  EwPostSignal( _this->OnChange, ((XObject)_this ));

  if ( _this->Outlet.Object != 0 )
  {
    EwOnSetInt32( _this->Outlet, WidgetSetHorizontalSlider_OnGetCurrentValue( _this ));
    EwNotifyRefObservers( _this->Outlet, 0 );
  }
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onReleaseTouch()' */
void WidgetSetHorizontalSlider_onReleaseTouch( WidgetSetHorizontalSlider _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  if ( !_this->touchActive )
    return;

  _this->touchActive = 0;
  _this->KeyHandlerRight.Enabled = 1;
  _this->KeyHandlerLeft.Enabled = 1;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.onPressTouch()' */
void WidgetSetHorizontalSlider_onPressTouch( WidgetSetHorizontalSlider _this, XObject 
  sender )
{
  XRect touchArea;
  XBool hasThumb;
  XBool insideThumb;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  touchArea = EwMoveRectPos( _Const0007, _this->TouchHandler.CurrentPos );
  hasThumb = 0;
  insideThumb = 0;

  if ( _this->rectView3 != 0 )
  {
    hasThumb = 1;
    insideThumb |= !EwIsRectEmpty( EwIntersectRect( _this->rectView3->Super1.Bounds, 
    touchArea ));
  }

  if ( hasThumb && !insideThumb )
  {
    CoreRoot root = CoreView__GetRoot( _this );
    CoreSimpleTouchHandler_OnSetEnabled( &_this->TouchHandler, 0 );
    CoreRoot_RetargetCursor( root, ((CoreView)root ), 0, ((CoreView)_this ));
    CoreSimpleTouchHandler_OnSetEnabled( &_this->TouchHandler, 1 );
    return;
  }

  _this->touchActive = 1;
  _this->KeyHandlerRight.Enabled = 0;
  _this->KeyHandlerLeft.Enabled = 0;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
  _this->touchStartValue = WidgetSetHorizontalSlider_OnGetCurrentValue( _this );
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.OnSetOutlet()' */
void WidgetSetHorizontalSlider_OnSetOutlet( WidgetSetHorizontalSlider _this, XRef 
  value )
{
  if ( !EwCompRef( _this->Outlet, value ))
    return;

  if ( _this->Outlet.Object != 0 )
    EwDetachRefObserver( EwNewSlot( _this, WidgetSetHorizontalSlider_onOutlet ), 
      _this->Outlet, 0 );

  _this->Outlet = value;

  if ( value.Object != 0 )
    EwAttachRefObserver( EwNewSlot( _this, WidgetSetHorizontalSlider_onOutlet ), 
      value, 0 );

  if ( value.Object != 0 )
    EwSignal( EwNewSlot( _this, WidgetSetHorizontalSlider_onOutlet ), ((XObject)_this ));
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.OnGetCurrentValue()' */
XInt32 WidgetSetHorizontalSlider_OnGetCurrentValue( WidgetSetHorizontalSlider _this )
{
  XInt32 value = _this->CurrentValue;

  if ( value < 0 )
    value = 0;

  if ( value > 100 )
    value = 100;

  return value;
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.OnSetCurrentValue()' */
void WidgetSetHorizontalSlider_OnSetCurrentValue( WidgetSetHorizontalSlider _this, 
  XInt32 value )
{
  if ( _this->CurrentValue == value )
    return;

  _this->CurrentValue = value;
  CoreGroup_InvalidateViewState((CoreGroup)_this );
}

/* 'C' function for method : 'WidgetSet::HorizontalSlider.OnSetAppearance()' */
void WidgetSetHorizontalSlider_OnSetAppearance( WidgetSetHorizontalSlider _this, 
  WidgetSetHorizontalSliderConfig value )
{
  if ( _this->Appearance == value )
    return;

  if ( _this->Appearance != 0 )
    EwDetachObjObserver( EwNewSlot( _this, WidgetSetHorizontalSlider_onConfigChanged ), 
      (XObject)_this->Appearance, 0 );

  _this->Appearance = value;

  if ( value != 0 )
    EwAttachObjObserver( EwNewSlot( _this, WidgetSetHorizontalSlider_onConfigChanged ), 
      (XObject)value, 0 );

  EwPostSignal( EwNewSlot( _this, WidgetSetHorizontalSlider_onConfigChanged ), ((XObject)_this ));
}

/* Variants derived from the class : 'WidgetSet::HorizontalSlider' */
EW_DEFINE_CLASS_VARIANTS( WidgetSetHorizontalSlider )
EW_END_OF_CLASS_VARIANTS( WidgetSetHorizontalSlider )

/* Virtual Method Table (VMT) for the class : 'WidgetSet::HorizontalSlider' */
EW_DEFINE_CLASS( WidgetSetHorizontalSlider, CoreGroup, RepetitionTimer, animation, 
                 OnChange, Outlet, touchStartValue, touchStartValue, "WidgetSet::HorizontalSlider" )
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
  WidgetSetHorizontalSlider_OnSetBounds,
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
  WidgetSetHorizontalSlider_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( WidgetSetHorizontalSlider )

/* Embedded Wizard */
