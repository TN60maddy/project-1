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
#include "_CoreGroup.h"
#include "_CoreSimpleTouchHandler.h"
#include "_CoreView.h"
#include "_NavigationContainer.h"
#include "_NavigationNavigatorClass.h"
#include "_NavigationPage.h"
#include "Navigation.h"

/* Compressed strings for the language 'Default'. */
EW_CONST_STRING_PRAGMA static const unsigned int _StringsDefault0[] =
{
  0x0000011A, /* ratio 60.99 % */
  0xB8005900, 0x0008A452, 0x3C010729, 0x0003A849, 0x00500008, 0x06700184, 0x4E001940,
  0x03B00224, 0x8D450D20, 0x01BC0074, 0xC3400720, 0x56271187, 0xA390F8BC, 0x1C778BC7,
  0x47300476, 0x75001BA6, 0x29D1B000, 0x9F800433, 0x4C160633, 0xC2217088, 0xAE351093,
  0xE5D1A8C4, 0x472189C7, 0xF29A4496, 0x2221C5E3, 0x390CDC01, 0x8BCDE3D1, 0xAC7A1F25,
  0xC8E6F0F9, 0x5E6B0F90, 0xE7C00B44, 0x0D04814F, 0x50CA2C22, 0x19A5D566, 0x08AD3A27,
  0x9954EB35, 0x045AEF13, 0x4C266560, 0xE26D6399, 0xA1F3B9E4, 0x03909FDB, 0x00000002,
  0x00000000
};

/* Constant values used in this 'C' module only. */
static const XStringRes _Const0000 = { _StringsDefault0, 0x0002 };
static const XStringRes _Const0001 = { _StringsDefault0, 0x002E };
static const XStringRes _Const0002 = { _StringsDefault0, 0x0061 };
static const XPoint _Const0003 = { 0, 0 };

/* Forward declaration of the class Effects::Transition */
#ifndef _EffectsTransition_
  EW_DECLARE_CLASS( EffectsTransition )
#define _EffectsTransition_
#endif

/* Initializer for the class 'Navigation::NavigatorClass' */
void NavigationNavigatorClass__Init( NavigationNavigatorClass _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  XObject__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( NavigationNavigatorClass );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( NavigationNavigatorClass );
}

/* Re-Initializer for the class 'Navigation::NavigatorClass' */
void NavigationNavigatorClass__ReInit( NavigationNavigatorClass _this )
{
  /* At first re-initialize the super class ... */
  XObject__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Navigation::NavigatorClass' */
void NavigationNavigatorClass__Done( NavigationNavigatorClass _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( XObject );

  /* Don't forget to deinitialize the super class ... */
  XObject__Done( &_this->_.Super );
}

/* This method opens the page provides as parameter in aPageView. The page is opened 
   and closed with the transations configured in the page view. */
XBool NavigationNavigatorClass_OpenPage( NavigationNavigatorClass _this, NavigationPage 
  aPageView )
{
  if ( aPageView == 0 )
  {
    EwTrace( "%s", EwLoadString( &_Const0000 ));
    return 0;
  }

  return NavigationNavigatorClass_openPage( _this, aPageView, 0, 0, 0 );
}

/* 'C' function for method : 'Navigation::NavigatorClass.CloseCurrentPageWithTransition()' */
XBool NavigationNavigatorClass_CloseCurrentPageWithTransition( NavigationNavigatorClass _this, 
  EffectsTransition aCloseTransition, XBool aCombine )
{
  EffectsTransition closeTransition;

  if ( _this->Container == 0 )
  {
    EwTrace( "%s", EwLoadString( &_Const0001 ));
    return 0;
  }

  if ( _this->currentPage == 0 )
    return 0;

  closeTransition = aCloseTransition;

  if ( closeTransition == 0 )
    closeTransition = 0;

  CoreGroup__DismissDialog( _this->Container, ((CoreGroup)_this->currentPage ), 
  closeTransition, 0, 0, EwNewSlot( _this->currentPage, NavigationPage__onClose ), 
  EwNullSlot, aCombine );
  NavigationContainer_OnSetIsModal( _this->Container, 0 );
  _this->currentPage = 0;
  EwNotifyObjObservers((XObject)_this, 0 );
  return 1;
}

/* Wrapper function for the virtual method : 'Navigation::NavigatorClass.CloseCurrentPageWithTransition()' */
XBool NavigationNavigatorClass__CloseCurrentPageWithTransition( void* _this, EffectsTransition 
  aCloseTransition, XBool aCombine )
{
  return ((NavigationNavigatorClass)_this)->_.VMT->CloseCurrentPageWithTransition((NavigationNavigatorClass)_this
  , aCloseTransition, aCombine );
}

/* This methos return the current page. */
NavigationPage NavigationNavigatorClass_GetCurrentPage( NavigationNavigatorClass _this )
{
  return _this->currentPage;
}

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
  aOpenTransition, XBool aCombineTransitions )
{
  return NavigationNavigatorClass_openPage( _this, aPageView, aClosePrevPageTransition, 
    aOpenTransition, aCombineTransitions );
}

/* 'C' function for method : 'Navigation::NavigatorClass.openPage()' */
XBool NavigationNavigatorClass_openPage( NavigationNavigatorClass _this, NavigationPage 
  aPageView, EffectsTransition aClosePrevPageTransition, EffectsTransition aOpenTransition, 
  XBool aCombineTransitions )
{
  EffectsTransition openTransition;

  if ( _this->Container == 0 )
  {
    EwTrace( "%s", EwLoadString( &_Const0001 ));
    return 0;
  }

  if ( aPageView == 0 )
  {
    EwTrace( "%s", EwLoadString( &_Const0002 ));
    return 0;
  }

  if ( _this->currentPage != 0 )
    NavigationNavigatorClass__CloseCurrentPageWithTransition( _this, aClosePrevPageTransition, 
    aCombineTransitions );

  openTransition = aOpenTransition;

  if ( openTransition == 0 )
    openTransition = 0;

  CoreGroup__PresentDialog( _this->Container, ((CoreGroup)aPageView ), openTransition, 
  0, 0, 0, 0, 0, EwNewSlot( aPageView, NavigationPage_onOpen ), EwNullSlot, aCombineTransitions );
  NavigationContainer_OnSetIsModal( _this->Container, 1 );
  _this->currentPage = aPageView;
  EwNotifyObjObservers((XObject)_this, 0 );
  return 1;
}

/* 'C' function for method : 'Navigation::NavigatorClass.CloseCurrentPage()' */
XBool NavigationNavigatorClass_CloseCurrentPage( NavigationNavigatorClass _this )
{
  return NavigationNavigatorClass__CloseCurrentPageWithTransition( _this, 0, 0 );
}

/* Variants derived from the class : 'Navigation::NavigatorClass' */
EW_DEFINE_CLASS_VARIANTS( NavigationNavigatorClass )
EW_END_OF_CLASS_VARIANTS( NavigationNavigatorClass )

/* Virtual Method Table (VMT) for the class : 'Navigation::NavigatorClass' */
EW_DEFINE_CLASS( NavigationNavigatorClass, XObject, Container, Container, _.VMT, 
                 _.VMT, _.VMT, _.VMT, "Navigation::NavigatorClass" )
  NavigationNavigatorClass_CloseCurrentPageWithTransition,
EW_END_OF_CLASS( NavigationNavigatorClass )

/* Initializer for the class 'Navigation::Page' */
void NavigationPage__Init( NavigationPage _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( NavigationPage );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( NavigationPage );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, EwNewRect( 0, 0, NavigationPageSize.X, NavigationPageSize.Y ));
}

/* Re-Initializer for the class 'Navigation::Page' */
void NavigationPage__ReInit( NavigationPage _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Navigation::Page' */
void NavigationPage__Done( NavigationPage _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* 'C' function for method : 'Navigation::Page.OnSetCaption()' */
void NavigationPage_OnSetCaption( NavigationPage _this, XString value )
{
  if ( !EwCompString( _this->Caption, value ))
    return;

  _this->Caption = EwShareString( value );
}

/* Wrapper function for the virtual method : 'Navigation::Page.OnSetCaption()' */
void NavigationPage__OnSetCaption( void* _this, XString value )
{
  ((NavigationPage)_this)->_.VMT->OnSetCaption((NavigationPage)_this, value );
}

/* 'C' function for method : 'Navigation::Page.onClose()' */
void NavigationPage_onClose( NavigationPage _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( sender );
}

/* Wrapper function for the virtual method : 'Navigation::Page.onClose()' */
void NavigationPage__onClose( void* _this, XObject sender )
{
  ((NavigationPage)_this)->_.VMT->onClose((NavigationPage)_this, sender );
}

/* Slot trigerred when page is opened. */
void NavigationPage_onOpen( NavigationPage _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( sender );
}

/* Variants derived from the class : 'Navigation::Page' */
EW_DEFINE_CLASS_VARIANTS( NavigationPage )
EW_END_OF_CLASS_VARIANTS( NavigationPage )

/* Virtual Method Table (VMT) for the class : 'Navigation::Page' */
EW_DEFINE_CLASS( NavigationPage, CoreGroup, Caption, Caption, Caption, Caption, 
                 Caption, _.VMT, "Navigation::Page" )
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
  CoreGroup_OnSetBounds,
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
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
  NavigationPage_OnSetCaption,
  NavigationPage_onClose,
EW_END_OF_CLASS( NavigationPage )

/* Page Navigator autobject. */
EW_DEFINE_AUTOOBJECT( NavigationPageNavigator, NavigationNavigatorClass )

/* Initializer for the auto object 'Navigation::PageNavigator' */
void NavigationPageNavigator__Init( NavigationNavigatorClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Re-Initializer for the auto object 'Navigation::PageNavigator' */
void NavigationPageNavigator__ReInit( NavigationNavigatorClass _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Navigation::PageNavigator' */
EW_DEFINE_AUTOOBJECT_VARIANTS( NavigationPageNavigator )
EW_END_OF_AUTOOBJECT_VARIANTS( NavigationPageNavigator )

/* Initializer for the class 'Navigation::Container' */
void NavigationContainer__Init( NavigationContainer _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( NavigationContainer );

  /* ... then construct all embedded objects */
  CoreSimpleTouchHandler__Init( &_this->DontTouchBehind, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( NavigationContainer );

  /* ... and initialize objects, variables, properties, etc. */
  CoreSimpleTouchHandler_OnSetMaxStrikeCount( &_this->DontTouchBehind, 999 );
  CoreSimpleTouchHandler_OnSetEnabled( &_this->DontTouchBehind, 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->DontTouchBehind ), 0 );

  /* Call the user defined constructor */
  NavigationContainer_Init( _this, aArg );
}

/* Re-Initializer for the class 'Navigation::Container' */
void NavigationContainer__ReInit( NavigationContainer _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreSimpleTouchHandler__ReInit( &_this->DontTouchBehind );
}

/* Finalizer method for the class 'Navigation::Container' */
void NavigationContainer__Done( NavigationContainer _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Finalize all embedded objects */
  CoreSimpleTouchHandler__Done( &_this->DontTouchBehind );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void NavigationContainer_Init( NavigationContainer _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void NavigationContainer_UpdateLayout( NavigationContainer _this, XPoint aSize )
{
  CoreGroup_UpdateLayout((CoreGroup)_this, aSize );
  CoreQuadView__OnSetPoint1( &_this->DontTouchBehind, EwNewPoint( 0, aSize.Y ));
  CoreQuadView__OnSetPoint2( &_this->DontTouchBehind, EwNewPoint( aSize.X, aSize.Y ));
  CoreQuadView__OnSetPoint3( &_this->DontTouchBehind, EwNewPoint( aSize.X, 0 ));
  CoreQuadView__OnSetPoint4( &_this->DontTouchBehind, _Const0003 );
}

/* 'C' function for method : 'Navigation::Container.OnSetIsModal()' */
void NavigationContainer_OnSetIsModal( NavigationContainer _this, XBool value )
{
  if ( _this->IsModal == value )
    return;

  _this->IsModal = value;
  CoreSimpleTouchHandler_OnSetEnabled( &_this->DontTouchBehind, value );
}

/* Variants derived from the class : 'Navigation::Container' */
EW_DEFINE_CLASS_VARIANTS( NavigationContainer )
EW_END_OF_CLASS_VARIANTS( NavigationContainer )

/* Virtual Method Table (VMT) for the class : 'Navigation::Container' */
EW_DEFINE_CLASS( NavigationContainer, CoreGroup, DontTouchBehind, IsModal, IsModal, 
                 IsModal, IsModal, IsModal, "Navigation::Container" )
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
  CoreGroup_OnSetBounds,
  CoreGroup_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  NavigationContainer_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( NavigationContainer )

/* User defined constant: 'Navigation::PageSize' */
const XPoint NavigationPageSize = { 960, 360 };

/* Embedded Wizard */
