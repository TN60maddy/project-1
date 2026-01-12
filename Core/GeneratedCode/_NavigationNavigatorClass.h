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

#ifndef _NavigationNavigatorClass_H
#define _NavigationNavigatorClass_H

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

/* Forward declaration of the class Navigation::NavigatorClass */
#ifndef _NavigationNavigatorClass_
  EW_DECLARE_CLASS( NavigationNavigatorClass )
#define _NavigationNavigatorClass_
#endif

/* Forward declaration of the class Navigation::Page */
#ifndef _NavigationPage_
  EW_DECLARE_CLASS( NavigationPage )
#define _NavigationPage_
#endif


/* Navigator class containing methods for opening a page an returning the current 
   page. Please set the PageContainer property before calling any method. */
EW_DEFINE_FIELDS( NavigationNavigatorClass, XObject )
  EW_PROPERTY( Container,       NavigationContainer )
  EW_VARIABLE( currentPage,     NavigationPage )
EW_END_OF_FIELDS( NavigationNavigatorClass )

/* Virtual Method Table (VMT) for the class : 'Navigation::NavigatorClass' */
EW_DEFINE_METHODS( NavigationNavigatorClass, XObject )
  EW_METHOD( CloseCurrentPageWithTransition, XBool )( NavigationNavigatorClass _this, 
    EffectsTransition aCloseTransition, XBool aCombine )
EW_END_OF_METHODS( NavigationNavigatorClass )

/* This method opens the page provides as parameter in aPageView. The page is opened 
   and closed with the transations configured in the page view. */
XBool NavigationNavigatorClass_OpenPage( NavigationNavigatorClass _this, NavigationPage 
  aPageView );

/* 'C' function for method : 'Navigation::NavigatorClass.CloseCurrentPageWithTransition()' */
XBool NavigationNavigatorClass_CloseCurrentPageWithTransition( NavigationNavigatorClass _this, 
  EffectsTransition aCloseTransition, XBool aCombine );

/* Wrapper function for the virtual method : 'Navigation::NavigatorClass.CloseCurrentPageWithTransition()' */
XBool NavigationNavigatorClass__CloseCurrentPageWithTransition( void* _this, EffectsTransition 
  aCloseTransition, XBool aCombine );

/* This methos return the current page. */
NavigationPage NavigationNavigatorClass_GetCurrentPage( NavigationNavigatorClass _this );

/* This method opens the page provides as parameter in aPageView. If parameter aClosePrevPageTransition 
   is not null, the previous page is closed with this transation, otherwise with 
   the transation configured on the page view.
   If parameter aOpenTransition is not null, the current page is opened with this 
   transation, otherwise with the transation configured on the page view.
   If aCombineTransitions is true the transitions for closing the previous page 
   and opening the current one will be executed simultaneously, otherwise will be 
   executed one after another. */
XBool NavigationNavigatorClass_OpenPageWithTransition( NavigationNavigatorClass _this, 
  NavigationPage aPageView, EffectsTransition aClosePrevPageTransition, EffectsTransition 
  aOpenTransition, XBool aCombineTransitions );

/* 'C' function for method : 'Navigation::NavigatorClass.openPage()' */
XBool NavigationNavigatorClass_openPage( NavigationNavigatorClass _this, NavigationPage 
  aPageView, EffectsTransition aClosePrevPageTransition, EffectsTransition aOpenTransition, 
  XBool aCombineTransitions );

/* 'C' function for method : 'Navigation::NavigatorClass.CloseCurrentPage()' */
XBool NavigationNavigatorClass_CloseCurrentPage( NavigationNavigatorClass _this );

#ifdef __cplusplus
  }
#endif

#endif /* _NavigationNavigatorClass_H */

/* Embedded Wizard */
