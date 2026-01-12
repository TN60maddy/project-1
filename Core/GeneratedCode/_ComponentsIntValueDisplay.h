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

#ifndef _ComponentsIntValueDisplay_H
#define _ComponentsIntValueDisplay_H

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

#include "_ComponentsValueDisplay.h"

/* Forward declaration of the class Components::IntValueDisplay */
#ifndef _ComponentsIntValueDisplay_
  EW_DECLARE_CLASS( ComponentsIntValueDisplay )
#define _ComponentsIntValueDisplay_
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

/* Forward declaration of the class Resources::Font */
#ifndef _ResourcesFont_
  EW_DECLARE_CLASS( ResourcesFont )
#define _ResourcesFont_
#endif


/* Deklaration of class : 'Components::IntValueDisplay' */
EW_DEFINE_FIELDS( ComponentsIntValueDisplay, ComponentsValueDisplay )
  EW_PROPERTY( Outlet,          XRef )
  EW_PROPERTY( Value,           XInt32 )
  EW_PROPERTY( Resolution,      XInt32 )
  EW_PROPERTY( Precision,       XInt32 )
  EW_PROPERTY( IsTime,          XBool )
EW_END_OF_FIELDS( ComponentsIntValueDisplay )

/* Virtual Method Table (VMT) for the class : 'Components::IntValueDisplay' */
EW_DEFINE_METHODS( ComponentsIntValueDisplay, ComponentsValueDisplay )
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
  EW_METHOD( formatValue,       void )( ComponentsIntValueDisplay _this, XObject 
    sender )
EW_END_OF_METHODS( ComponentsIntValueDisplay )

/* 'C' function for method : 'Components::IntValueDisplay.Init()' */
void ComponentsIntValueDisplay_Init( ComponentsIntValueDisplay _this, XHandle aArg );

/* 'C' function for method : 'Components::IntValueDisplay.OnSetValue()' */
void ComponentsIntValueDisplay_OnSetValue( ComponentsIntValueDisplay _this, XInt32 
  value );

/* 'C' function for method : 'Components::IntValueDisplay.formatValue()' */
void ComponentsIntValueDisplay_formatValue( ComponentsIntValueDisplay _this, XObject 
  sender );

/* Wrapper function for the virtual method : 'Components::IntValueDisplay.formatValue()' */
void ComponentsIntValueDisplay__formatValue( void* _this, XObject sender );

/* 'C' function for method : 'Components::IntValueDisplay.OnSetOutlet()' */
void ComponentsIntValueDisplay_OnSetOutlet( ComponentsIntValueDisplay _this, XRef 
  value );

/* This slot method will receive a signal, if the value of the property assigned 
   to @Outlet has been changed by another widget or by the application logic. In 
   response to this notification, the widget will update itself. */
void ComponentsIntValueDisplay_onOutlet( ComponentsIntValueDisplay _this, XObject 
  sender );

/* 'C' function for method : 'Components::IntValueDisplay.OnSetResolution()' */
void ComponentsIntValueDisplay_OnSetResolution( ComponentsIntValueDisplay _this, 
  XInt32 value );

/* 'C' function for method : 'Components::IntValueDisplay.OnSetIsTime()' */
void ComponentsIntValueDisplay_OnSetIsTime( ComponentsIntValueDisplay _this, XBool 
  value );

/* 'C' function for method : 'Components::IntValueDisplay.OnSetPrecision()' */
void ComponentsIntValueDisplay_OnSetPrecision( ComponentsIntValueDisplay _this, 
  XInt32 value );

#ifdef __cplusplus
  }
#endif

#endif /* _ComponentsIntValueDisplay_H */

/* Embedded Wizard */
