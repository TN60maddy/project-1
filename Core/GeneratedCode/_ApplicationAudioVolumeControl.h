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

#ifndef _ApplicationAudioVolumeControl_H
#define _ApplicationAudioVolumeControl_H

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

#include "_ApplicationSettingsSubPage.h"
#include "_ComponentsPressureSettingButton.h"
#include "_ComponentsTextButton.h"
#include "_CoreSimpleTouchHandler.h"
#include "_ViewsRectangle.h"
#include "_ViewsText.h"

/* Forward declaration of the class Application::AudioVolumeControl */
#ifndef _ApplicationAudioVolumeControl_
  EW_DECLARE_CLASS( ApplicationAudioVolumeControl )
#define _ApplicationAudioVolumeControl_
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


/* Deklaration of class : 'Application::AudioVolumeControl' */
EW_DEFINE_FIELDS( ApplicationAudioVolumeControl, ApplicationSettingsSubPage )
  EW_OBJECT  ( Setting1Button,  ComponentsPressureSettingButton )
  EW_OBJECT  ( Setting2Button,  ComponentsPressureSettingButton )
  EW_OBJECT  ( Setting3Button,  ComponentsPressureSettingButton )
  EW_OBJECT  ( Setting4Button,  ComponentsPressureSettingButton )
  EW_OBJECT  ( Setting5Button,  ComponentsPressureSettingButton )
  EW_OBJECT  ( Setting6Button,  ComponentsPressureSettingButton )
  EW_OBJECT  ( Setting7Button,  ComponentsPressureSettingButton )
  EW_OBJECT  ( Setting8Button,  ComponentsPressureSettingButton )
  EW_OBJECT  ( Setting9Button,  ComponentsPressureSettingButton )
  EW_OBJECT  ( ConfirmButton,   ComponentsTextButton )
  EW_PROPERTY( AudioVolume,     XInt32 )
EW_END_OF_FIELDS( ApplicationAudioVolumeControl )

/* Virtual Method Table (VMT) for the class : 'Application::AudioVolumeControl' */
EW_DEFINE_METHODS( ApplicationAudioVolumeControl, ApplicationSettingsSubPage )
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
  EW_METHOD( OnSetCaption,      void )( ApplicationSettingsPage _this, XString value )
  EW_METHOD( onClose,           void )( NavigationPage _this, XObject sender )
  EW_METHOD( onBack,            void )( ApplicationSettingsSubPage _this, XObject 
    sender )
EW_END_OF_METHODS( ApplicationAudioVolumeControl )

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationAudioVolumeControl_Init( ApplicationAudioVolumeControl _this, XHandle 
  aArg );

/* 'C' function for method : 'Application::AudioVolumeControl.onConfirm()' */
void ApplicationAudioVolumeControl_onConfirm( ApplicationAudioVolumeControl _this, 
  XObject sender );

/* 'C' function for method : 'Application::AudioVolumeControl.doConfirm()' */
void ApplicationAudioVolumeControl_doConfirm( ApplicationAudioVolumeControl _this, 
  XObject sender );

/* 'C' function for method : 'Application::AudioVolumeControl.onCancel()' */
void ApplicationAudioVolumeControl_onCancel( ApplicationAudioVolumeControl _this, 
  XObject sender );

/* 'C' function for method : 'Application::AudioVolumeControl.OnSetAudioVolume()' */
void ApplicationAudioVolumeControl_OnSetAudioVolume( ApplicationAudioVolumeControl _this, 
  XInt32 value );

/* 'C' function for method : 'Application::AudioVolumeControl.onAudioVolume()' */
void ApplicationAudioVolumeControl_onAudioVolume( ApplicationAudioVolumeControl _this, 
  XObject sender );

/* Default onget method for the property 'AudioVolume' */
XInt32 ApplicationAudioVolumeControl_OnGetAudioVolume( ApplicationAudioVolumeControl _this );

#ifdef __cplusplus
  }
#endif

#endif /* _ApplicationAudioVolumeControl_H */

/* Embedded Wizard */
