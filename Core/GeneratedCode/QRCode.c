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
#include "_GraphicsCanvas.h"
#include "_QRCodeQRCode.h"
#include "Core.h"
#include "QRCode.h"

/* Compressed strings for the language 'Default'. */
EW_CONST_STRING_PRAGMA static const unsigned int _StringsDefault0[] =
{
  0x000001A0, /* ratio 57.69 % */
  0xB8002100, 0x80090452, 0x24D80032, 0x0006F004, 0x0620000B, 0x67200432, 0x21001921,
  0x48346800, 0x8FC508B0, 0x80EA2B0D, 0x8009A008, 0x9CDC0034, 0x4006D004, 0xED24961D,
  0x6738FC1C, 0x11954365, 0x030800D1, 0x3A4466A0, 0x998A2313, 0x4B66B119, 0x22150A9E,
  0x243118AC, 0x5C718449, 0x33F85CEE, 0x789E4C28, 0xD97CB656, 0xA5CCA232, 0xC4A66D3D,
  0x8A8011A8, 0x563C4581, 0x6474E8AC, 0x79632AC4, 0x124A550E, 0x0888C368, 0x78998E55,
  0x9D556111, 0x599C017E, 0x446C75F9, 0x02B3332A, 0x0711A8CD, 0x3F20B55A, 0x570005BA,
  0x8185DCA5, 0x58BC92ED, 0xBA9DE791, 0x8C930000, 0xDEC014CA, 0x7E497D86, 0x27540946,
  0x61539C4A, 0x9088ACF3, 0x66005367, 0x4B28F248, 0x8D43ED00, 0x20FA0902, 0x56656709,
  0xAE8B0A84, 0x719333D4, 0x01018D59, 0x00000000
};

/* Constant values used in this 'C' module only. */
static const XRect _Const0000 = {{ 0, 0 }, { 200, 200 }};
static const XStringRes _Const0001 = { _StringsDefault0, 0x0002 };
static const XPoint _Const0002 = { 0, 0 };
static const XColor _Const0003 = { 0x00, 0x00, 0x00, 0xFF };
static const XStringRes _Const0004 = { _StringsDefault0, 0x0012 };
static const XStringRes _Const0005 = { _StringsDefault0, 0x005A };
static const XStringRes _Const0006 = { _StringsDefault0, 0x0084 };
static const XStringRes _Const0007 = { _StringsDefault0, 0x00BC };
static const XStringRes _Const0008 = { _StringsDefault0, 0x00C0 };

/* Include the native sources which are used by the QRCode component. */
#include "QRCodeBinding.h"


/* Initializer for the class 'QRCode::QRCode' */
void QRCodeQRCode__Init( QRCodeQRCode _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreGroup__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( QRCodeQRCode );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( QRCodeQRCode );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0000 );
  _this->Text = EwShareString( EwLoadString( &_Const0001 ));

  /* Call the user defined constructor */
  QRCodeQRCode_Init( _this, aArg );
}

/* Re-Initializer for the class 'QRCode::QRCode' */
void QRCodeQRCode__ReInit( QRCodeQRCode _this )
{
  /* At first re-initialize the super class ... */
  CoreGroup__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'QRCode::QRCode' */
void QRCodeQRCode__Done( QRCodeQRCode _this )
{
  /* Call the user defined destructor of the class */
  QRCodeQRCode_Done( _this );

  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreGroup );

  /* Don't forget to deinitialize the super class ... */
  CoreGroup__Done( &_this->_.Super );
}

/* The method Done() is invoked automatically after the component has been destroyed 
   by the garbage-collector. */
void QRCodeQRCode_Done( QRCodeQRCode _this )
{
  QRCodeQRCode_destroyQRCode( _this );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void QRCodeQRCode_Init( QRCodeQRCode _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  _this->qrHandle = QRCodeQRCode_createQRCode( _this );
  EwSignal( EwNewSlot( _this, QRCodeQRCode_encodeTextSlot ), ((XObject)_this ));
}

/* The method drawContent() gets invoked to draw the cubes of the qr code. */
void QRCodeQRCode_drawContent( QRCodeQRCode _this, GraphicsCanvas aCanvas, XRect 
  aClip, XPoint aOffset, XInt32 aOpacity, XBool aBlend )
{
  XInt32 borderLength;
  XInt32 width;
  XInt32 x;
  XInt32 y;
  XRect destRect;
  XPoint padding;
  XColor c;

  CoreGroup_drawContent((CoreGroup)_this, aCanvas, aClip, aOffset, aOpacity, aBlend );
  borderLength = 0;
  width = QRCodeQRCode_getSize( _this );
  x = 0;
  destRect = _this->Super2.Bounds;
  padding = _Const0002;
  c = _Const0003;

  if (( width > EwGetRectW( _this->Super2.Bounds )) || ( width > EwGetRectH( _this->Super2.Bounds )))
    return;

  aBlend = (XBool)( aBlend && (( _this->Super3.viewState & CoreViewStateAlphaBlended ) 
  == CoreViewStateAlphaBlended ));
  aOpacity = aOpacity + 1;

  if ( aOpacity < 256 )
    c.Alpha = (XUInt8)(( aOpacity * 255 ) >> 8 );

  if ( width > 0 )
  {
    if ( EwGetRectW( _this->Super2.Bounds ) > EwGetRectH( _this->Super2.Bounds ))
      borderLength = EwGetRectH( _this->Super2.Bounds ) / width;
    else
      borderLength = EwGetRectW( _this->Super2.Bounds ) / width;

    padding.X = (( EwGetRectW( _this->Super2.Bounds ) - ( borderLength * width )) 
    / 2 );
    padding.Y = (( EwGetRectH( _this->Super2.Bounds ) - ( borderLength * width )) 
    / 2 );
  }

  for ( y = 0; y < width; y = y + 1 )
    for ( x = 0; x < width; x = x + 1 )
      if ( QRCodeQRCode_getData( _this, x, y ))
      {
        destRect = EwNewRect( x * borderLength, y * borderLength, ( x + 1 ) * borderLength, 
        ( y + 1 ) * borderLength );
        destRect = EwMoveRectPos( EwMoveRectPos( destRect, aOffset ), padding );
        GraphicsCanvas_FillRectangle( aCanvas, aClip, destRect, c, c, c, c, aBlend );
      }
}

/* The method UpdateLayout() is invoked automatically after the size of the component 
   has been changed. This method can be overridden and filled with logic to perform 
   a sophisticated arrangement calculation for one or more enclosed views. In this 
   case the parameter aSize can be used. It contains the current size of the component. 
   Usually, all enclosed views are arranged automatically accordingly to their @Layout 
   property. UpdateLayout() gives the derived components a chance to extend this 
   automatism by a user defined algorithm. */
void QRCodeQRCode_UpdateLayout( QRCodeQRCode _this, XPoint aSize )
{
  CoreGroup_UpdateLayout((CoreGroup)_this, aSize );
  EwPostSignal( EwNewSlot( _this, QRCodeQRCode_validate ), ((XObject)_this ));
}

/* The method getData() gets called to obtain whether a cube at a given position 
   should be drawn or not. */
XBool QRCodeQRCode_getData( QRCodeQRCode _this, XInt32 aXPos, XInt32 aYPos )
{
  XBool result = 0;
  XInt32 x = aXPos;
  XInt32 y = aYPos;
  XHandle qr = _this->qrHandle;

  result = QRCodeBindingGetModule( qr, x, y );
  return result;
}

/* 'C' function for method : 'QRCode::QRCode.OnSetText()' */
void QRCodeQRCode_OnSetText( QRCodeQRCode _this, XString value )
{
  if ( !EwCompString( _this->Text, value ))
    return;

  _this->Text = EwShareString( value );
  EwPostSignal( EwNewSlot( _this, QRCodeQRCode_encodeTextSlot ), ((XObject)_this ));
}

/* The method getSize() gets called to obtain the needed border width in number 
   of cubes to display the previous encoded 'Text'. */
XInt32 QRCodeQRCode_getSize( QRCodeQRCode _this )
{
  XHandle qr = _this->qrHandle;
  XInt32 size = 0;

  size = QRCodeBindingGetSize( qr );
  return size;
}

/* The method createQRCode() gets called once per instance of this qr code component 
   to create a native handle. */
XHandle QRCodeQRCode_createQRCode( QRCodeQRCode _this )
{
  XHandle qr;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  qr = 0;
  qr = QRCodeBindingCreate();
  return qr;
}

/* The method encodeText() gets called to encode the text which should be display 
   at the qr code component. */
XBool QRCodeQRCode_encodeText( QRCodeQRCode _this, XString aText, XInt32 aMinVersion, 
  XInt32 aMaxVersion )
{
  XBool success = 0;
  XHandle qr = _this->qrHandle;
  XString text = aText;
  XInt32 minVersion = aMinVersion;
  XInt32 maxVersion = aMaxVersion;

  if ( minVersion > maxVersion )
  {
    EwTrace( "%s", EwLoadString( &_Const0004 ));
    return 0;
  }

  success = QRCodeBindingEncodeText( qr, text, minVersion, maxVersion );

  if ( !success )
    EwTrace( "%s%s", EwLoadString( &_Const0005 ), text );

  return success;
}

/* The method destroyQRCode() gets called once per instance of this qr code component 
   to destroy and free the native allocated memory. */
void QRCodeQRCode_destroyQRCode( QRCodeQRCode _this )
{
  XHandle qr = _this->qrHandle;

  QRCodeBindingDestroy( qr );
  _this->qrHandle = 0;
}

/* 'C' function for method : 'QRCode::QRCode.encodeTextSlot()' */
void QRCodeQRCode_encodeTextSlot( QRCodeQRCode _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  QRCodeQRCode_encodeText( _this, _this->Text, 1, 40 );
  EwPostSignal( EwNewSlot( _this, QRCodeQRCode_validate ), ((XObject)_this ));
  CoreGroup__InvalidateArea( _this, EwGetRectORect( _this->Super2.Bounds ));
}

/* The slot validate() gets called to obtain whether the encoded QR code can be 
   displayed within the bounds of the QRCode view. */
void QRCodeQRCode_validate( QRCodeQRCode _this, XObject sender )
{
  XInt32 width;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  width = QRCodeQRCode_getSize( _this );

  if (( width > EwGetRectW( _this->Super2.Bounds )) || ( width > EwGetRectH( _this->Super2.Bounds )))
    EwTrace( "%s", EwConcatString( EwConcatString( EwConcatString( EwConcatString( 
      EwLoadString( &_Const0006 ), EwNewStringInt( EwGetRectW( _this->Super2.Bounds ), 
      0, 10 )), EwLoadString( &_Const0007 )), EwNewStringInt( EwGetRectH( _this->Super2.Bounds ), 
      0, 10 )), EwLoadString( &_Const0008 )));
}

/* Variants derived from the class : 'QRCode::QRCode' */
EW_DEFINE_CLASS_VARIANTS( QRCodeQRCode )
EW_END_OF_CLASS_VARIANTS( QRCodeQRCode )

/* Virtual Method Table (VMT) for the class : 'QRCode::QRCode' */
EW_DEFINE_CLASS( QRCodeQRCode, CoreGroup, Text, Text, Text, Text, Text, qrHandle, 
                 "QRCode::QRCode" )
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
  QRCodeQRCode_drawContent,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetOpacity,
  CoreGroup_ExtendClipping,
  CoreGroup_SwitchToDialog,
  CoreGroup_DismissDialog,
  CoreGroup_PresentDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  QRCodeQRCode_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_FindSiblingView,
  CoreGroup_FadeGroup,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_AddBehind,
  CoreGroup_Add,
EW_END_OF_CLASS( QRCodeQRCode )

/* Embedded Wizard */
