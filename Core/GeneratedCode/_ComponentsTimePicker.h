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

#ifndef _ComponentsTimePicker_H
#define _ComponentsTimePicker_H

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

#include "_CoreSlideTouchHandler.h"
#include "_CoreVerticalList.h"
#include "_TemplatesPickerControl.h"
#include "_ViewsRectangle.h"
#include "_ViewsText.h"

/* Forward declaration of the class Components::TimePicker */
#ifndef _ComponentsTimePicker_
  EW_DECLARE_CLASS( ComponentsTimePicker )
#define _ComponentsTimePicker_
#endif

/* Forward declaration of the class Core::DialogContext */
#ifndef _CoreDialogContext_
  EW_DECLARE_CLASS( CoreDialogContext )
#define _CoreDialogContext_
#endif

/* Forward declaration of the class Core::Group */
#ifndef _CoreGroup_
  EW_DECLARE_CLASS( CoreGroup )
#define _CoreGroup_
#endif

/* Forward declaration of the class Core::KeyPressHandler */
#ifndef _CoreKeyPressHandler_
  EW_DECLARE_CLASS( CoreKeyPressHandler )
#define _CoreKeyPressHandler_
#endif

/* Forward declaration of the class Core::LayoutContext */
#ifndef _CoreLayoutContext_
  EW_DECLARE_CLASS( CoreLayoutContext )
#define _CoreLayoutContext_
#endif

/* Forward declaration of the class Core::TaskQueue */
#ifndef _CoreTaskQueue_
  EW_DECLARE_CLASS( CoreTaskQueue )
#define _CoreTaskQueue_
#endif

/* Forward declaration of the class Core::View */
#ifndef _CoreView_
  EW_DECLARE_CLASS( CoreView )
#define _CoreView_
#endif

/* Forward declaration of the class Effects::Fader */
#ifndef _EffectsFader_
  EW_DECLARE_CLASS( EffectsFader )
#define _EffectsFader_
#endif


/* This is a GUI component. */
EW_DEFINE_FIELDS( ComponentsTimePicker, TemplatesPickerControl )
  EW_OBJECT  ( TouchHandlerSecond, CoreSlideTouchHandler )
  EW_OBJECT  ( TouchHandlerMinute, CoreSlideTouchHandler )
  EW_OBJECT  ( TouchHandlerHour, CoreSlideTouchHandler )
  EW_OBJECT  ( ListSecond,      CoreVerticalList )
  EW_OBJECT  ( ListMinute,      CoreVerticalList )
  EW_OBJECT  ( ListHour,        CoreVerticalList )
  EW_OBJECT  ( BackgroundCurrent, ViewsRectangle )
  EW_OBJECT  ( ListCurrentSec,  CoreVerticalList )
  EW_OBJECT  ( ListCurrentMin,  CoreVerticalList )
  EW_OBJECT  ( ListCurrentHour, CoreVerticalList )
  EW_OBJECT  ( UnitHour,        ViewsText )
  EW_OBJECT  ( UnitMin,         ViewsText )
  EW_OBJECT  ( UnitSec,         ViewsText )
  EW_OBJECT  ( FadeTop,         ViewsRectangle )
  EW_OBJECT  ( FadeBottom,      ViewsRectangle )
  EW_PROPERTY( Outlet,          XRef )
  EW_PROPERTY( BgColor,         XColor )
  EW_PROPERTY( Time,            XInt32 )
EW_END_OF_FIELDS( ComponentsTimePicker )

/* Virtual Method Table (VMT) for the class : 'Components::TimePicker' */
EW_DEFINE_METHODS( ComponentsTimePicker, TemplatesPickerControl )
  EW_METHOD( initLayoutContext, void )( CoreRectView _this, XRect aBounds, CoreOutline 
    aOutline )
  EW_METHOD( GetRoot,           CoreRoot )( CoreView _this )
  EW_METHOD( Draw,              void )( CoreGroup _this, GraphicsCanvas aCanvas, 
    XRect aClip, XPoint aOffset, XInt32 aOpacity, XBool aBlend )
  EW_METHOD( GetClipping,       XRect )( CoreGroup _this )
  EW_METHOD( HandleEvent,       XObject )( CoreView _this, CoreEvent aEvent )
  EW_METHOD( CursorHitTest,     CoreCursorHit )( CoreGroup _this, XRect aArea, XInt32 
    aFinger, XInt32 aStrikeCount, CoreView aDedicatedView, CoreView aStartView, 
    XSet aRetargetReason )
  EW_METHOD( AdjustDrawingArea, XRect )( CoreGroup _this, XRect aArea )
  EW_METHOD( ArrangeView,       XPoint )( CoreRectView _this, XRect aBounds, XEnum 
    aFormation )
  EW_METHOD( MoveView,          void )( CoreRectView _this, XPoint aOffset, XBool 
    aFastMove )
  EW_METHOD( GetExtent,         XRect )( CoreRectView _this )
  EW_METHOD( ChangeViewState,   void )( CoreGroup _this, XSet aSetState, XSet aClearState )
  EW_METHOD( OnSetBounds,       void )( CoreGroup _this, XRect value )
  EW_METHOD( drawContent,       void )( CoreGroup _this, GraphicsCanvas aCanvas, 
    XRect aClip, XPoint aOffset, XInt32 aOpacity, XBool aBlend )
  EW_METHOD( OnSetFocus,        void )( CoreGroup _this, CoreView value )
  EW_METHOD( OnSetOpacity,      void )( CoreGroup _this, XInt32 value )
  EW_METHOD( ExtendClipping,    void )( CoreGroup _this, XInt32 aExtClipLeft, XInt32 
    aExtClipRight, XInt32 aExtClipTop, XInt32 aExtClipBottom )
  EW_METHOD( SwitchToDialog,    void )( CoreGroup _this, CoreGroup aDialogGroup, 
    EffectsTransition aPresentTransition, EffectsTransition aDismissTransition, 
    EffectsTransition aOverlayTransition, EffectsTransition aRestoreTransition, 
    EffectsTransition aOverrideDismissTransition, EffectsTransition aOverrideOverlayTransition, 
    EffectsTransition aOverrideRestoreTransition, XSlot aComplete, XSlot aCancel, 
    XBool aCombine )
  EW_METHOD( DismissDialog,     void )( CoreGroup _this, CoreGroup aDialogGroup, 
    EffectsTransition aOverrideDismissTransition, EffectsTransition aOverrideOverlayTransition, 
    EffectsTransition aOverrideRestoreTransition, XSlot aComplete, XSlot aCancel, 
    XBool aCombine )
  EW_METHOD( PresentDialog,     void )( CoreGroup _this, CoreGroup aDialogGroup, 
    EffectsTransition aPresentTransition, EffectsTransition aDismissTransition, 
    EffectsTransition aOverlayTransition, EffectsTransition aRestoreTransition, 
    EffectsTransition aOverrideOverlayTransition, EffectsTransition aOverrideRestoreTransition, 
    XSlot aComplete, XSlot aCancel, XBool aCombine )
  EW_METHOD( DispatchEvent,     XObject )( CoreGroup _this, CoreEvent aEvent )
  EW_METHOD( BroadcastEvent,    XObject )( CoreGroup _this, CoreEvent aEvent, XSet 
    aFilter )
  EW_METHOD( UpdateLayout,      void )( CoreGroup _this, XPoint aSize )
  EW_METHOD( UpdateViewState,   void )( ComponentsTimePicker _this, XSet aState )
  EW_METHOD( InvalidateArea,    void )( CoreGroup _this, XRect aArea )
  EW_METHOD( FindSiblingView,   CoreView )( CoreGroup _this, CoreView aView, XSet 
    aFilter )
  EW_METHOD( FadeGroup,         void )( CoreGroup _this, CoreGroup aGroup, EffectsFader 
    aFader, XSlot aComplete, XSlot aCancel, XBool aCombine )
  EW_METHOD( RestackTop,        void )( CoreGroup _this, CoreView aView )
  EW_METHOD( Restack,           void )( CoreGroup _this, CoreView aView, XInt32 
    aOrder )
  EW_METHOD( Remove,            void )( CoreGroup _this, CoreView aView )
  EW_METHOD( AddBehind,         void )( CoreGroup _this, CoreView aView, CoreView 
    aSibling )
  EW_METHOD( Add,               void )( CoreGroup _this, CoreView aView, XInt32 
    aOrder )
EW_END_OF_METHODS( ComponentsTimePicker )

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
void ComponentsTimePicker_UpdateViewState( ComponentsTimePicker _this, XSet aState );

/* This method is called when one of the Slide Touch Handler (TouchHandlerHour, 
   TouchHandlerMinute or TouchHandlerSecond) has finished the slide animation. Thereupon 
   the owner of the time picker is notified, that the time has been changed. */
void ComponentsTimePicker_onEndSlide( ComponentsTimePicker _this, XObject sender );

/* This method is called when one of the Slide Touch Handler (TouchHandlerHour, 
   TouchHandlerMinute or TouchHandlerSecond) has begun the slide animation. */
void ComponentsTimePicker_onStartSlide( ComponentsTimePicker _this, XObject sender );

/* This method is called by 'ListSecond' vertical list every time the list loads 
   or updates an item. */
void ComponentsTimePicker_OnLoadSecondItem( ComponentsTimePicker _this, XObject 
  sender );

/* This method is called by 'ListMinute' vertical list every time the list loads 
   or updates an item. */
void ComponentsTimePicker_OnLoadMinuteItem( ComponentsTimePicker _this, XObject 
  sender );

/* This method is called by 'ListHour' vertical list every time the list loads or 
   updates an item. */
void ComponentsTimePicker_OnLoadHourItem( ComponentsTimePicker _this, XObject sender );

/* 'C' function for method : 'Components::TimePicker.OnGetSecond()' */
XInt32 ComponentsTimePicker_OnGetSecond( ComponentsTimePicker _this );

/* 'C' function for method : 'Components::TimePicker.OnSetSecond()' */
void ComponentsTimePicker_OnSetSecond( ComponentsTimePicker _this, XInt32 value );

/* 'C' function for method : 'Components::TimePicker.OnGetMinute()' */
XInt32 ComponentsTimePicker_OnGetMinute( ComponentsTimePicker _this );

/* 'C' function for method : 'Components::TimePicker.OnSetMinute()' */
void ComponentsTimePicker_OnSetMinute( ComponentsTimePicker _this, XInt32 value );

/* 'C' function for method : 'Components::TimePicker.OnGetHour()' */
XInt32 ComponentsTimePicker_OnGetHour( ComponentsTimePicker _this );

/* 'C' function for method : 'Components::TimePicker.OnSetHour()' */
void ComponentsTimePicker_OnSetHour( ComponentsTimePicker _this, XInt32 value );

/* This method is called by 'ListHour' vertical list every time the list loads or 
   updates an item. */
void ComponentsTimePicker_OnLoadCurrentHourItem( ComponentsTimePicker _this, XObject 
  sender );

/* 'C' function for method : 'Components::TimePicker.onHourUpdate()' */
void ComponentsTimePicker_onHourUpdate( ComponentsTimePicker _this, XObject sender );

/* This method is called by 'ListHour' vertical list every time the list loads or 
   updates an item. */
void ComponentsTimePicker_OnLoadCurrentMinItem( ComponentsTimePicker _this, XObject 
  sender );

/* This method is called by 'ListSecond' vertical list every time the list loads 
   or updates an item. */
void ComponentsTimePicker_OnLoadCurrentSecItem( ComponentsTimePicker _this, XObject 
  sender );

/* 'C' function for method : 'Components::TimePicker.onMinUpdate()' */
void ComponentsTimePicker_onMinUpdate( ComponentsTimePicker _this, XObject sender );

/* 'C' function for method : 'Components::TimePicker.onSecUpdate()' */
void ComponentsTimePicker_onSecUpdate( ComponentsTimePicker _this, XObject sender );

/* 'C' function for method : 'Components::TimePicker.OnSetBgColor()' */
void ComponentsTimePicker_OnSetBgColor( ComponentsTimePicker _this, XColor value );

/* 'C' function for method : 'Components::TimePicker.OnSetTime()' */
void ComponentsTimePicker_OnSetTime( ComponentsTimePicker _this, XInt32 value );

/* 'C' function for method : 'Components::TimePicker.OnGetTime()' */
XInt32 ComponentsTimePicker_OnGetTime( ComponentsTimePicker _this );

/* 'C' function for method : 'Components::TimePicker.OnSetOutlet()' */
void ComponentsTimePicker_OnSetOutlet( ComponentsTimePicker _this, XRef value );

/* 'C' function for method : 'Components::TimePicker.onSlide()' */
void ComponentsTimePicker_onSlide( ComponentsTimePicker _this, XObject sender );

#ifdef __cplusplus
  }
#endif

#endif /* _ComponentsTimePicker_H */

/* Embedded Wizard */
