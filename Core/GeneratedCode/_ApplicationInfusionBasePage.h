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

#ifndef _ApplicationInfusionBasePage_H
#define _ApplicationInfusionBasePage_H

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

#include "_NavigationPage.h"

/* Forward declaration of the class Application::InfusionBasePage */
#ifndef _ApplicationInfusionBasePage_
  EW_DECLARE_CLASS( ApplicationInfusionBasePage )
#define _ApplicationInfusionBasePage_
#endif

/* Forward declaration of the class Components::EditTile */
#ifndef _ComponentsEditTile_
  EW_DECLARE_CLASS( ComponentsEditTile )
#define _ComponentsEditTile_
#endif

/* Forward declaration of the class Components::Tile */
#ifndef _ComponentsTile_
  EW_DECLARE_CLASS( ComponentsTile )
#define _ComponentsTile_
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

/* Forward declaration of the class Effects::Int32Effect */
#ifndef _EffectsInt32Effect_
  EW_DECLARE_CLASS( EffectsInt32Effect )
#define _EffectsInt32Effect_
#endif

/* Forward declaration of the class Effects::RectEffect */
#ifndef _EffectsRectEffect_
  EW_DECLARE_CLASS( EffectsRectEffect )
#define _EffectsRectEffect_
#endif


/* Deklaration of class : 'Application::InfusionBasePage' */
EW_DEFINE_FIELDS( ApplicationInfusionBasePage, NavigationPage )
  EW_VARIABLE( editTile,        ComponentsEditTile )
  EW_VARIABLE( moveEffect,      EffectsRectEffect )
  EW_VARIABLE( fadeEffect,      EffectsInt32Effect )
  EW_PROPERTY( opacity,         XInt32 )
  EW_PROPERTY( moveRect,        XRect )
  EW_VARIABLE( editMode,        XBool )
EW_END_OF_FIELDS( ApplicationInfusionBasePage )

/* Virtual Method Table (VMT) for the class : 'Application::InfusionBasePage' */
EW_DEFINE_METHODS( ApplicationInfusionBasePage, NavigationPage )
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
  EW_METHOD( UpdateViewState,   void )( CoreGroup _this, XSet aState )
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
  EW_METHOD( OnSetCaption,      void )( NavigationPage _this, XString value )
  EW_METHOD( onClose,           void )( NavigationPage _this, XObject sender )
  EW_METHOD( OnSetopacity,      void )( ApplicationInfusionBasePage _this, XInt32 
    value )
EW_END_OF_METHODS( ApplicationInfusionBasePage )

/* 'C' function for method : 'Application::InfusionBasePage.showTile()' */
void ApplicationInfusionBasePage_showTile( ApplicationInfusionBasePage _this, ComponentsTile 
  aTile, XBool aShow );

/* 'C' function for method : 'Application::InfusionBasePage.onEdit()' */
void ApplicationInfusionBasePage_onEdit( ApplicationInfusionBasePage _this, XObject 
  sender );

/* 'C' function for method : 'Application::InfusionBasePage.OnSetopacity()' */
void ApplicationInfusionBasePage_OnSetopacity( ApplicationInfusionBasePage _this, 
  XInt32 value );

/* Wrapper function for the virtual method : 'Application::InfusionBasePage.OnSetopacity()' */
void ApplicationInfusionBasePage__OnSetopacity( void* _this, XInt32 value );

/* 'C' function for method : 'Application::InfusionBasePage.onMoveFinished()' */
void ApplicationInfusionBasePage_onMoveFinished( ApplicationInfusionBasePage _this, 
  XObject sender );

/* 'C' function for method : 'Application::InfusionBasePage.onFadeFinished()' */
void ApplicationInfusionBasePage_onFadeFinished( ApplicationInfusionBasePage _this, 
  XObject sender );

/* 'C' function for method : 'Application::InfusionBasePage.onEditConfirm()' */
void ApplicationInfusionBasePage_onEditConfirm( ApplicationInfusionBasePage _this, 
  XObject sender );

/* 'C' function for method : 'Application::InfusionBasePage.onEditCancel()' */
void ApplicationInfusionBasePage_onEditCancel( ApplicationInfusionBasePage _this, 
  XObject sender );

/* 'C' function for method : 'Application::InfusionBasePage.closeEditMode()' */
void ApplicationInfusionBasePage_closeEditMode( ApplicationInfusionBasePage _this, 
  XObject aSender );

/* 'C' function for method : 'Application::InfusionBasePage.setupEffects()' */
void ApplicationInfusionBasePage_setupEffects( ApplicationInfusionBasePage _this, 
  XRect aStartRect, XBool aReversed );

/* 'C' function for method : 'Application::InfusionBasePage.getEditTileClass()' */
XClass ApplicationInfusionBasePage_getEditTileClass( ApplicationInfusionBasePage _this, 
  ComponentsTile aTile );

/* 'C' function for method : 'Application::InfusionBasePage.getEditTilePopupClass()' */
XClass ApplicationInfusionBasePage_getEditTilePopupClass( ApplicationInfusionBasePage _this );

/* 'C' function for method : 'Application::InfusionBasePage.showInputPopup()' */
void ApplicationInfusionBasePage_showInputPopup( ApplicationInfusionBasePage _this );

/* 'C' function for method : 'Application::InfusionBasePage.createEditTile()' */
void ApplicationInfusionBasePage_createEditTile( ApplicationInfusionBasePage _this, 
  ComponentsTile aTile );

/* 'C' function for method : 'Application::InfusionBasePage.OnSetmoveRect()' */
void ApplicationInfusionBasePage_OnSetmoveRect( ApplicationInfusionBasePage _this, 
  XRect value );

/* 'C' function for method : 'Application::InfusionBasePage.getEditTileRect()' */
XRect ApplicationInfusionBasePage_getEditTileRect( ApplicationInfusionBasePage _this );

/* Default onget method for the property 'opacity' */
XInt32 ApplicationInfusionBasePage_OnGetopacity( ApplicationInfusionBasePage _this );

/* Default onget method for the property 'moveRect' */
XRect ApplicationInfusionBasePage_OnGetmoveRect( ApplicationInfusionBasePage _this );

#ifdef __cplusplus
  }
#endif

#endif /* _ApplicationInfusionBasePage_H */

/* Embedded Wizard */
