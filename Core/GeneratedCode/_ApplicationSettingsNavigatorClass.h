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

#ifndef _ApplicationSettingsNavigatorClass_H
#define _ApplicationSettingsNavigatorClass_H

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

/* Forward declaration of the class Application::SettingsNavigatorClass */
#ifndef _ApplicationSettingsNavigatorClass_
  EW_DECLARE_CLASS( ApplicationSettingsNavigatorClass )
#define _ApplicationSettingsNavigatorClass_
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


/* Deklaration of class : 'Application::SettingsNavigatorClass' */
EW_DEFINE_FIELDS( ApplicationSettingsNavigatorClass, NavigationNavigatorClass )
  EW_VARIABLE( currentSubPage,  NavigationPage )
EW_END_OF_FIELDS( ApplicationSettingsNavigatorClass )

/* Virtual Method Table (VMT) for the class : 'Application::SettingsNavigatorClass' */
EW_DEFINE_METHODS( ApplicationSettingsNavigatorClass, NavigationNavigatorClass )
  EW_METHOD( CloseCurrentPageWithTransition, XBool )( NavigationNavigatorClass _this, 
    EffectsTransition aCloseTransition, XBool aCombine )
EW_END_OF_METHODS( ApplicationSettingsNavigatorClass )

/* This method opens the page provides as parameter in aPageView. The page is opened 
   and closed with the transations configured in the page view. */
XBool ApplicationSettingsNavigatorClass_OpenSubPage( ApplicationSettingsNavigatorClass _this, 
  NavigationPage aPageView );

/* 'C' function for method : 'Application::SettingsNavigatorClass.CloseCurrentSubPageWithTransition()' */
XBool ApplicationSettingsNavigatorClass_CloseCurrentSubPageWithTransition( ApplicationSettingsNavigatorClass _this, 
  EffectsTransition aCloseTransition, XBool aCombine );

/* This methos return the current page. */
NavigationPage ApplicationSettingsNavigatorClass_GetCurrentSubPage( ApplicationSettingsNavigatorClass _this );

/* 'C' function for method : 'Application::SettingsNavigatorClass.CloseCurrentSubPage()' */
XBool ApplicationSettingsNavigatorClass_CloseCurrentSubPage( ApplicationSettingsNavigatorClass _this );

/* 'C' function for method : 'Application::SettingsNavigatorClass.openSubPage()' */
XBool ApplicationSettingsNavigatorClass_openSubPage( ApplicationSettingsNavigatorClass _this, 
  NavigationPage aPageView, EffectsTransition aClosePrevPageTransition, EffectsTransition 
  aOpenTransition, XBool aCombineTransitions );

#ifdef __cplusplus
  }
#endif

#endif /* _ApplicationSettingsNavigatorClass_H */

/* Embedded Wizard */
