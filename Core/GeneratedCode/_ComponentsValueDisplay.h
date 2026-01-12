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

#ifndef _ComponentsValueDisplay_H
#define _ComponentsValueDisplay_H

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

#include "_ViewsText.h"

/* Forward declaration of the class Components::ValueDisplay */
#ifndef _ComponentsValueDisplay_
  EW_DECLARE_CLASS( ComponentsValueDisplay )
#define _ComponentsValueDisplay_
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


/* Deklaration of class : 'Components::ValueDisplay' */
EW_DEFINE_FIELDS( ComponentsValueDisplay, ViewsText )
  EW_PROPERTY( Font1,           ResourcesFont )
  EW_VARIABLE( defaultFont,     ResourcesFont )
  EW_PROPERTY( OnAdjustFont,    XSlot )
  EW_VARIABLE( inUpdateFont,    XBool )
EW_END_OF_FIELDS( ComponentsValueDisplay )

/* Virtual Method Table (VMT) for the class : 'Components::ValueDisplay' */
EW_DEFINE_METHODS( ComponentsValueDisplay, ViewsText )
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
EW_END_OF_METHODS( ComponentsValueDisplay )

/* 'C' function for method : 'Components::ValueDisplay.OnSetBounds()' */
void ComponentsValueDisplay_OnSetBounds( ComponentsValueDisplay _this, XRect value );

/* 'C' function for method : 'Components::ValueDisplay.OnSetString()' */
void ComponentsValueDisplay_OnSetString( ComponentsValueDisplay _this, XString value );

/* 'C' function for method : 'Components::ValueDisplay.OnSetFont()' */
void ComponentsValueDisplay_OnSetFont( ComponentsValueDisplay _this, ResourcesFont 
  value );

/* 'C' function for method : 'Components::ValueDisplay.OnSetFont1()' */
void ComponentsValueDisplay_OnSetFont1( ComponentsValueDisplay _this, ResourcesFont 
  value );

/* 'C' function for method : 'Components::ValueDisplay.updateFont()' */
void ComponentsValueDisplay_updateFont( ComponentsValueDisplay _this, XObject sender );

#ifdef __cplusplus
  }
#endif

#endif /* _ComponentsValueDisplay_H */

/* Embedded Wizard */
