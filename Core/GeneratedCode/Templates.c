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
#include "_TemplatesDeviceClass.h"
#include "_TemplatesGauge.h"
#include "_TemplatesHorizontalValueBar.h"
#include "_TemplatesNumKeyboard.h"
#include "_TemplatesPickerControl.h"
#include "_TemplatesPushButton.h"
#include "_TemplatesTextEditor.h"
#include "_TemplatesToggleButton.h"
#include "_TemplatesVerticalScrollbar.h"
#include "Templates.h"

/* Initializer for the class 'Templates::PushButton' */
void TemplatesPushButton__Init( TemplatesPushButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( TemplatesPushButton );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( TemplatesPushButton );
}

/* Re-Initializer for the class 'Templates::PushButton' */
void TemplatesPushButton__ReInit( TemplatesPushButton _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Templates::PushButton' */
void TemplatesPushButton__Done( TemplatesPushButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Templates::PushButton' */
EW_DEFINE_CLASS_VARIANTS( TemplatesPushButton )
EW_END_OF_CLASS_VARIANTS( TemplatesPushButton )

/* Virtual Method Table (VMT) for the class : 'Templates::PushButton' */
EW_DEFINE_CLASS( TemplatesPushButton, CoreGroup, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "Templates::PushButton" )
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
EW_END_OF_CLASS( TemplatesPushButton )

/* Initializer for the class 'Templates::ToggleButton' */
void TemplatesToggleButton__Init( TemplatesToggleButton _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( TemplatesToggleButton );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( TemplatesToggleButton );
}

/* Re-Initializer for the class 'Templates::ToggleButton' */
void TemplatesToggleButton__ReInit( TemplatesToggleButton _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Templates::ToggleButton' */
void TemplatesToggleButton__Done( TemplatesToggleButton _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Templates::ToggleButton' */
EW_DEFINE_CLASS_VARIANTS( TemplatesToggleButton )
EW_END_OF_CLASS_VARIANTS( TemplatesToggleButton )

/* Virtual Method Table (VMT) for the class : 'Templates::ToggleButton' */
EW_DEFINE_CLASS( TemplatesToggleButton, CoreGroup, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "Templates::ToggleButton" )
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
EW_END_OF_CLASS( TemplatesToggleButton )

/* Initializer for the class 'Templates::Gauge' */
void TemplatesGauge__Init( TemplatesGauge _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( TemplatesGauge );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( TemplatesGauge );
}

/* Re-Initializer for the class 'Templates::Gauge' */
void TemplatesGauge__ReInit( TemplatesGauge _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Templates::Gauge' */
void TemplatesGauge__Done( TemplatesGauge _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Templates::Gauge' */
EW_DEFINE_CLASS_VARIANTS( TemplatesGauge )
EW_END_OF_CLASS_VARIANTS( TemplatesGauge )

/* Virtual Method Table (VMT) for the class : 'Templates::Gauge' */
EW_DEFINE_CLASS( TemplatesGauge, CoreGroup, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 "Templates::Gauge" )
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
EW_END_OF_CLASS( TemplatesGauge )

/* Initializer for the class 'Templates::VerticalScrollbar' */
void TemplatesVerticalScrollbar__Init( TemplatesVerticalScrollbar _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( TemplatesVerticalScrollbar );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( TemplatesVerticalScrollbar );
}

/* Re-Initializer for the class 'Templates::VerticalScrollbar' */
void TemplatesVerticalScrollbar__ReInit( TemplatesVerticalScrollbar _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Templates::VerticalScrollbar' */
void TemplatesVerticalScrollbar__Done( TemplatesVerticalScrollbar _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Templates::VerticalScrollbar' */
EW_DEFINE_CLASS_VARIANTS( TemplatesVerticalScrollbar )
EW_END_OF_CLASS_VARIANTS( TemplatesVerticalScrollbar )

/* Virtual Method Table (VMT) for the class : 'Templates::VerticalScrollbar' */
EW_DEFINE_CLASS( TemplatesVerticalScrollbar, CoreGroup, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, "Templates::VerticalScrollbar" )
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
EW_END_OF_CLASS( TemplatesVerticalScrollbar )

/* Initializer for the class 'Templates::TextEditor' */
void TemplatesTextEditor__Init( TemplatesTextEditor _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( TemplatesTextEditor );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( TemplatesTextEditor );
}

/* Re-Initializer for the class 'Templates::TextEditor' */
void TemplatesTextEditor__ReInit( TemplatesTextEditor _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Templates::TextEditor' */
void TemplatesTextEditor__Done( TemplatesTextEditor _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Templates::TextEditor' */
EW_DEFINE_CLASS_VARIANTS( TemplatesTextEditor )
EW_END_OF_CLASS_VARIANTS( TemplatesTextEditor )

/* Virtual Method Table (VMT) for the class : 'Templates::TextEditor' */
EW_DEFINE_CLASS( TemplatesTextEditor, CoreGroup, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "Templates::TextEditor" )
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
EW_END_OF_CLASS( TemplatesTextEditor )

/* Initializer for the class 'Templates::NumKeyboard' */
void TemplatesNumKeyboard__Init( TemplatesNumKeyboard _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( TemplatesNumKeyboard );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( TemplatesNumKeyboard );
}

/* Re-Initializer for the class 'Templates::NumKeyboard' */
void TemplatesNumKeyboard__ReInit( TemplatesNumKeyboard _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Templates::NumKeyboard' */
void TemplatesNumKeyboard__Done( TemplatesNumKeyboard _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Templates::NumKeyboard' */
EW_DEFINE_CLASS_VARIANTS( TemplatesNumKeyboard )
EW_END_OF_CLASS_VARIANTS( TemplatesNumKeyboard )

/* Virtual Method Table (VMT) for the class : 'Templates::NumKeyboard' */
EW_DEFINE_CLASS( TemplatesNumKeyboard, CoreGroup, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "Templates::NumKeyboard" )
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
EW_END_OF_CLASS( TemplatesNumKeyboard )

/* Initializer for the class 'Templates::PickerControl' */
void TemplatesPickerControl__Init( TemplatesPickerControl _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( TemplatesPickerControl );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( TemplatesPickerControl );
}

/* Re-Initializer for the class 'Templates::PickerControl' */
void TemplatesPickerControl__ReInit( TemplatesPickerControl _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Templates::PickerControl' */
void TemplatesPickerControl__Done( TemplatesPickerControl _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Templates::PickerControl' */
EW_DEFINE_CLASS_VARIANTS( TemplatesPickerControl )
EW_END_OF_CLASS_VARIANTS( TemplatesPickerControl )

/* Virtual Method Table (VMT) for the class : 'Templates::PickerControl' */
EW_DEFINE_CLASS( TemplatesPickerControl, CoreGroup, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, "Templates::PickerControl" )
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
EW_END_OF_CLASS( TemplatesPickerControl )

/* Initializer for the class 'Templates::HorizontalValueBar' */
void TemplatesHorizontalValueBar__Init( TemplatesHorizontalValueBar _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( TemplatesHorizontalValueBar );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( TemplatesHorizontalValueBar );
}

/* Re-Initializer for the class 'Templates::HorizontalValueBar' */
void TemplatesHorizontalValueBar__ReInit( TemplatesHorizontalValueBar _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Templates::HorizontalValueBar' */
void TemplatesHorizontalValueBar__Done( TemplatesHorizontalValueBar _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Templates::HorizontalValueBar' */
EW_DEFINE_CLASS_VARIANTS( TemplatesHorizontalValueBar )
EW_END_OF_CLASS_VARIANTS( TemplatesHorizontalValueBar )

/* Virtual Method Table (VMT) for the class : 'Templates::HorizontalValueBar' */
EW_DEFINE_CLASS( TemplatesHorizontalValueBar, CoreGroup, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, _.VMT, "Templates::HorizontalValueBar" )
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
EW_END_OF_CLASS( TemplatesHorizontalValueBar )

/* Initializer for the class 'Templates::DeviceClass' */
void TemplatesDeviceClass__Init( TemplatesDeviceClass _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  XObject__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( TemplatesDeviceClass );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( TemplatesDeviceClass );
}

/* Re-Initializer for the class 'Templates::DeviceClass' */
void TemplatesDeviceClass__ReInit( TemplatesDeviceClass _this )
{
  /* At first re-initialize the super class ... */
  XObject__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Templates::DeviceClass' */
void TemplatesDeviceClass__Done( TemplatesDeviceClass _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( XObject );

  /* Don't forget to deinitialize the super class ... */
  XObject__Done( &_this->_.Super );
}

/* Variants derived from the class : 'Templates::DeviceClass' */
EW_DEFINE_CLASS_VARIANTS( TemplatesDeviceClass )
EW_END_OF_CLASS_VARIANTS( TemplatesDeviceClass )

/* Virtual Method Table (VMT) for the class : 'Templates::DeviceClass' */
EW_DEFINE_CLASS( TemplatesDeviceClass, XObject, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "Templates::DeviceClass" )
EW_END_OF_CLASS( TemplatesDeviceClass )

/* Embedded Wizard */
