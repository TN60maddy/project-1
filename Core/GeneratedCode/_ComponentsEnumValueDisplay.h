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

#ifndef _ComponentsEnumValueDisplay_H
#define _ComponentsEnumValueDisplay_H

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

#include "_ComponentsIntValueDisplay.h"

/* Forward declaration of the class Components::EnumValueDisplay */
#ifndef _ComponentsEnumValueDisplay_
  EW_DECLARE_CLASS( ComponentsEnumValueDisplay )
#define _ComponentsEnumValueDisplay_
#endif

/* Forward declaration of the class Core::Group */
#ifndef _CoreGroup_
  EW_DECLARE_CLASS( CoreGroup )
#define _CoreGroup_
#endif

/* Forward declaration of the class Core::LayoutContext */
#ifndef _CoreLayoutContext_
  EW_DECLARE_CLASS( CoreLayoutContext )
#define _CoreLayoutContext_
#endif

/* Forward declaration of the class Core::View */
#ifndef _CoreView_
  EW_DECLARE_CLASS( CoreView )
#define _CoreView_
#endif

/* Forward declaration of the class Device::EnumClass */
#ifndef _DeviceEnumClass_
  EW_DECLARE_CLASS( DeviceEnumClass )
#define _DeviceEnumClass_
#endif

/* Forward declaration of the class Resources::Font */
#ifndef _ResourcesFont_
  EW_DECLARE_CLASS( ResourcesFont )
#define _ResourcesFont_
#endif


/* Deklaration of class : 'Components::EnumValueDisplay' */
EW_DEFINE_FIELDS( ComponentsEnumValueDisplay, ComponentsIntValueDisplay )
  EW_PROPERTY( Enum,            DeviceEnumClass )
EW_END_OF_FIELDS( ComponentsEnumValueDisplay )

/* Virtual Method Table (VMT) for the class : 'Components::EnumValueDisplay' */
EW_DEFINE_METHODS( ComponentsEnumValueDisplay, ComponentsIntValueDisplay )
  EW_METHOD( initLayoutContext, void )( CoreRectView _this, XRect aBounds, CoreOutline 
    aOutline )
  EW_METHOD( GetRoot,           CoreRoot )( CoreView _this )
  EW_METHOD( Draw,              void )( ViewsText _this, GraphicsCanvas aCanvas, 
    XRect aClip, XPoint aOffset, XInt32 aOpacity, XBool aBlend )
  EW_METHOD( GetClipping,       XRect )( CoreView _this )
  EW_METHOD( HandleEvent,       XObject )( CoreView _this, CoreEvent aEvent )
  EW_METHOD( CursorHitTest,     CoreCursorHit )( CoreView _this, XRect aArea, XInt32 
    aFinger, XInt32 aStrikeCount, CoreView aDedicatedView, CoreView aStartView, 
    XSet aRetargetReason )
  EW_METHOD( AdjustDrawingArea, XRect )( CoreView _this, XRect aArea )
  EW_METHOD( ArrangeView,       XPoint )( CoreRectView _this, XRect aBounds, XEnum 
    aFormation )
  EW_METHOD( MoveView,          void )( CoreRectView _this, XPoint aOffset, XBool 
    aFastMove )
  EW_METHOD( GetExtent,         XRect )( CoreRectView _this )
  EW_METHOD( ChangeViewState,   void )( CoreView _this, XSet aSetState, XSet aClearState )
  EW_METHOD( OnSetBounds,       void )( ComponentsValueDisplay _this, XRect value )
  EW_METHOD( OnSetString,       void )( ComponentsValueDisplay _this, XString value )
  EW_METHOD( OnSetFont,         void )( ComponentsValueDisplay _this, ResourcesFont 
    value )
  EW_METHOD( formatValue,       void )( ComponentsEnumValueDisplay _this, XObject 
    sender )
EW_END_OF_METHODS( ComponentsEnumValueDisplay )

/* 'C' function for method : 'Components::EnumValueDisplay.formatValue()' */
void ComponentsEnumValueDisplay_formatValue( ComponentsEnumValueDisplay _this, XObject 
  sender );

/* 'C' function for method : 'Components::EnumValueDisplay.OnSetEnum()' */
void ComponentsEnumValueDisplay_OnSetEnum( ComponentsEnumValueDisplay _this, DeviceEnumClass 
  value );

#ifdef __cplusplus
  }
#endif

#endif /* _ComponentsEnumValueDisplay_H */

/* Embedded Wizard */
