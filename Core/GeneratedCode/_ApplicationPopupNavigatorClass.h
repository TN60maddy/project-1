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

#ifndef _ApplicationPopupNavigatorClass_H
#define _ApplicationPopupNavigatorClass_H

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

#include "_NavigationNavigatorClass.h"

/* Forward declaration of the class Application::Popup */
#ifndef _ApplicationPopup_
  EW_DECLARE_CLASS( ApplicationPopup )
#define _ApplicationPopup_
#endif

/* Forward declaration of the class Application::PopupNavigatorClass */
#ifndef _ApplicationPopupNavigatorClass_
  EW_DECLARE_CLASS( ApplicationPopupNavigatorClass )
#define _ApplicationPopupNavigatorClass_
#endif

/* Forward declaration of the class Effects::ColorEffect */
#ifndef _EffectsColorEffect_
  EW_DECLARE_CLASS( EffectsColorEffect )
#define _EffectsColorEffect_
#endif

/* Forward declaration of the class Effects::RectEffect */
#ifndef _EffectsRectEffect_
  EW_DECLARE_CLASS( EffectsRectEffect )
#define _EffectsRectEffect_
#endif

/* Forward declaration of the class Effects::Transition */
#ifndef _EffectsTransition_
  EW_DECLARE_CLASS( EffectsTransition )
#define _EffectsTransition_
#endif

/* Forward declaration of the class Navigation::Container */
#ifndef _NavigationContainer_
  EW_DECLARE_CLASS( NavigationContainer )
#define _NavigationContainer_
#endif

/* Forward declaration of the class Navigation::Page */
#ifndef _NavigationPage_
  EW_DECLARE_CLASS( NavigationPage )
#define _NavigationPage_
#endif


/* Deklaration of class : 'Application::PopupNavigatorClass' */
EW_DEFINE_FIELDS( ApplicationPopupNavigatorClass, NavigationNavigatorClass )
  EW_VARIABLE( resizeEffect,    EffectsRectEffect )
  EW_VARIABLE( fadeEffect,      EffectsColorEffect )
EW_END_OF_FIELDS( ApplicationPopupNavigatorClass )

/* Virtual Method Table (VMT) for the class : 'Application::PopupNavigatorClass' */
EW_DEFINE_METHODS( ApplicationPopupNavigatorClass, NavigationNavigatorClass )
  EW_METHOD( CloseCurrentPageWithTransition, XBool )( ApplicationPopupNavigatorClass _this, 
    EffectsTransition aCloseTransition, XBool aCombine )
EW_END_OF_METHODS( ApplicationPopupNavigatorClass )

/* 'C' function for method : 'Application::PopupNavigatorClass.CloseCurrentPageWithTransition()' */
XBool ApplicationPopupNavigatorClass_CloseCurrentPageWithTransition( ApplicationPopupNavigatorClass _this, 
  EffectsTransition aCloseTransition, XBool aCombine );

/* 'C' function for method : 'Application::PopupNavigatorClass.OpenPopupWithEffectByType()' */
ApplicationPopup ApplicationPopupNavigatorClass_OpenPopupWithEffectByType( ApplicationPopupNavigatorClass _this, 
  XEnum aType, XRect aStartArea, XEnum aAlign );

/* This method opens the page provides as parameter in aPageView. If parameter aClosePrevPageTransition 
   is not null, the previous page is closed with this transation, otherwise with 
   the transation configured on the page view.
   If parameter aOpenTransition is not null, the current page is opened with this 
   transation, otherwise with the transation configured on the page view.
   If aCombineTransitions is true the transitions for closing the previous page 
   and opening the current one will be executed simultaneously, otherwise will be 
   executed one after another. */
ApplicationPopup ApplicationPopupNavigatorClass_OpenPopup( ApplicationPopupNavigatorClass _this, 
  ApplicationPopup aPopup, EffectsTransition aOpenTransition );

/* This method opens the page provides as parameter in aPageView. If parameter aClosePrevPageTransition 
   is not null, the previous page is closed with this transation, otherwise with 
   the transation configured on the page view.
   If parameter aOpenTransition is not null, the current page is opened with this 
   transation, otherwise with the transation configured on the page view.
   If aCombineTransitions is true the transitions for closing the previous page 
   and opening the current one will be executed simultaneously, otherwise will be 
   executed one after another. */
XBool ApplicationPopupNavigatorClass_ClosePopup( ApplicationPopupNavigatorClass _this, 
  ApplicationPopup aPopup, EffectsTransition aCloseTransition );

/* 'C' function for method : 'Application::PopupNavigatorClass.onResizeFinish()' */
void ApplicationPopupNavigatorClass_onResizeFinish( ApplicationPopupNavigatorClass _this, 
  XObject sender );

/* 'C' function for method : 'Application::PopupNavigatorClass.onFadeFinish()' */
void ApplicationPopupNavigatorClass_onFadeFinish( ApplicationPopupNavigatorClass _this, 
  XObject sender );

/* 'C' function for method : 'Application::PopupNavigatorClass.OpenPopupWithEffect()' */
ApplicationPopup ApplicationPopupNavigatorClass_OpenPopupWithEffect( ApplicationPopupNavigatorClass _this, 
  ApplicationPopup aPopup, XRect aStartArea, XEnum aAlign );

/* 'C' function for method : 'Application::PopupNavigatorClass.getPopupClass()' */
XClass ApplicationPopupNavigatorClass_getPopupClass( ApplicationPopupNavigatorClass _this, 
  XEnum aType );

/* 'C' function for method : 'Application::PopupNavigatorClass.getEndArea()' */
XRect ApplicationPopupNavigatorClass_getEndArea( ApplicationPopupNavigatorClass _this, 
  ApplicationPopup aPopup, XRect aStartArea, XEnum aAlign );

/* 'C' function for method : 'Application::PopupNavigatorClass.dismissPopup()' */
void ApplicationPopupNavigatorClass_dismissPopup( ApplicationPopupNavigatorClass _this, 
  XObject sender );

/* 'C' function for method : 'Application::PopupNavigatorClass.checkAnimationInProgress()' */
XBool ApplicationPopupNavigatorClass_checkAnimationInProgress( ApplicationPopupNavigatorClass _this );

/* 'C' function for method : 'Application::PopupNavigatorClass.updateContainer()' */
void ApplicationPopupNavigatorClass_updateContainer( ApplicationPopupNavigatorClass _this, 
  ApplicationPopup aPopup );

/* 'C' function for method : 'Application::PopupNavigatorClass.OpenPopupByType()' */
ApplicationPopup ApplicationPopupNavigatorClass_OpenPopupByType( ApplicationPopupNavigatorClass _this, 
  XEnum aType, EffectsTransition aOpenTransition );

/* 'C' function for method : 'Application::PopupNavigatorClass.GetCurrentPopup()' */
ApplicationPopup ApplicationPopupNavigatorClass_GetCurrentPopup( ApplicationPopupNavigatorClass _this );

/* 'C' function for method : 'Application::PopupNavigatorClass.GetCurrentPopupType()' */
XEnum ApplicationPopupNavigatorClass_GetCurrentPopupType( ApplicationPopupNavigatorClass _this );

#ifdef __cplusplus
  }
#endif

#endif /* _ApplicationPopupNavigatorClass_H */

/* Embedded Wizard */
