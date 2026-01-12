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
#include "_CoreQuadView.h"
#include "_ResourcesFont.h"
#include "_ToolsHelperCollection.h"
#include "Strings.h"
#include "Tools.h"

/* Compressed strings for the language 'Default'. */
EW_CONST_STRING_PRAGMA static const unsigned int _StringsDefault0[] =
{
  0x0000003E, /* ratio 70.97 % */
  0xB8000900, 0x8004A452, 0xC2090283, 0x61200838, 0x1D0C1711, 0xB03888B6, 0x05860E88,
  0x885C2E2A, 0x860822B0, 0x00020320, 0x00000000
};

/* Constant values used in this 'C' module only. */
static const XStringRes _Const0000 = { _StringsDefault0, 0x0002 };
static const XStringRes _Const0001 = { _StringsDefault0, 0x0006 };
static const XStringRes _Const0002 = { _StringsDefault0, 0x000A };
static const XStringRes _Const0003 = { _StringsDefault0, 0x000E };
static const XStringRes _Const0004 = { _StringsDefault0, 0x0012 };
static const XStringRes _Const0005 = { _StringsDefault0, 0x0016 };
static const XStringRes _Const0006 = { _StringsDefault0, 0x001B };

/* Initializer for the class 'Tools::HelperCollection' */
void ToolsHelperCollection__Init( ToolsHelperCollection _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  XObject__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ToolsHelperCollection );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ToolsHelperCollection );
}

/* Re-Initializer for the class 'Tools::HelperCollection' */
void ToolsHelperCollection__ReInit( ToolsHelperCollection _this )
{
  /* At first re-initialize the super class ... */
  XObject__ReInit( &_this->_.Super );
}

/* Finalizer method for the class 'Tools::HelperCollection' */
void ToolsHelperCollection__Done( ToolsHelperCollection _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( XObject );

  /* Don't forget to deinitialize the super class ... */
  XObject__Done( &_this->_.Super );
}

/* 'C' function for method : 'Tools::HelperCollection.StringReplace()' */
XString ToolsHelperCollection_StringReplace( ToolsHelperCollection _this, XString 
  aString, XString aOld, XString aNew )
{
  XString result;
  XBool ready;
  XInt32 index;
  XInt32 aOldLen;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  result = 0;
  ready = 0;
  index = 0;
  aOldLen = EwGetStringLength( aOld );

  while ( !ready )
  {
    XInt32 position = EwStringFind( aString, aOld, index );

    if ( position != -1 )
    {
      result = EwConcatString( EwConcatString( result, EwStringMiddle( aString, 
      index, position - index )), aNew );
      index = position + aOldLen;
    }
    else
    {
      XInt32 aStringLen = EwGetStringLength( aString );

      if ( index < aStringLen )
        result = EwConcatString( result, EwStringRight( aString, aStringLen - index ));

      ready = 1;
    }
  }

  return result;
}

/* 'C' function for method : 'Tools::HelperCollection.StringParamReplace()' */
XString ToolsHelperCollection_StringParamReplace( ToolsHelperCollection _this, XString 
  aString, XInt32 aParamNr, XString aParam )
{
  return ToolsHelperCollection_StringReplace( _this, aString, EwConcatString( EwLoadString( 
    &_Const0000 ), EwNewStringInt( aParamNr, 0, 10 )), aParam );
}

/* 'C' function for method : 'Tools::HelperCollection.FormatInt32Value()' */
XString ToolsHelperCollection_FormatInt32Value( ToolsHelperCollection _this, XInt32 
  aValue, XInt32 aResolution, XInt32 aPrecision )
{
  XString valueString;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  valueString = 0;

  if ( aResolution == 0 )
    valueString = EwNewStringInt( aValue, 0, 10 );
  else
    if ( aResolution > 0 )
    {
      XInt32 res;
      valueString = EwNewStringInt( aValue, 0, 10 );
      res = aResolution;

      while ( res > 0 )
      {
        valueString = EwConcatString( valueString, EwLoadString( &_Const0001 ));
        res--;
      }
    }
    else
    {
      XInt32 noOfDigits = -aResolution + 1;
      XInt32 decimalPointPos;

      if ( aValue < 0 )
        valueString = EwNewStringInt( -aValue, noOfDigits, 10 );
      else
        valueString = EwNewStringInt( aValue, noOfDigits, 10 );

      decimalPointPos = EwGetStringLength( valueString ) + aResolution;

      if ( aPrecision >= 0 )
      {
        XInt32 length;

        if ( aPrecision > EwGetInt32Abs( aResolution ))
          aPrecision = EwGetInt32Abs( aResolution );

        length = ( decimalPointPos + aPrecision ) + 1;

        if ( aPrecision > 0 )
          valueString = EwStringInsert( valueString, EwLoadString( &_Const0002 ), 
          decimalPointPos );
        else
          length--;

        valueString = EwStringLeft( valueString, length );
      }
      else
        valueString = EwStringInsert( valueString, EwLoadString( &_Const0002 ), 
        decimalPointPos );

      if ( aValue < 0 )
        valueString = EwStringInsert( valueString, EwLoadString( &_Const0003 ), 
        0 );
    }

  return valueString;
}

/* 'C' function for method : 'Tools::HelperCollection.ParseInt32Value()' */
XInt32 ToolsHelperCollection_ParseInt32Value( ToolsHelperCollection _this, XString 
  aFormatValue, XInt32 aResolution )
{
  XString valueString;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  valueString = aFormatValue;

  if ( aResolution > 0 )
    valueString = EwStringRemove( valueString, EwGetStringLength( valueString ) 
    - aResolution, aResolution );
  else
    if ( aResolution < 0 )
    {
      XInt32 noOfZeros = -aResolution;
      XInt32 decPointPos = EwStringFindChar( valueString, '.', 0 );

      if ( decPointPos >= 0 )
      {
        valueString = EwStringRemove( valueString, decPointPos, 1 );

        while (( noOfZeros > 0 ) && ( decPointPos < EwGetStringLength( valueString )))
        {
          decPointPos++;
          noOfZeros--;
        }

        if ( decPointPos < EwGetStringLength( valueString ))
          valueString = EwStringInsert( valueString, EwLoadString( &_Const0002 ), 
          decPointPos );
        else
          while ( noOfZeros > 0 )
          {
            valueString = EwConcatString( valueString, EwLoadString( &_Const0001 ));
            noOfZeros--;
          }
      }
      else
        while ( noOfZeros > 0 )
        {
          valueString = EwConcatString( valueString, EwLoadString( &_Const0001 ));
          noOfZeros--;
        }
    }

  return EwStringParseInt32( valueString, 0, 10 );
}

/* 'C' function for method : 'Tools::HelperCollection.FormatTime()' */
XString ToolsHelperCollection_FormatTime( ToolsHelperCollection _this, XInt32 aTime )
{
  XInt32 h;
  XInt32 m;
  XInt32 s;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  h = aTime / 3600;
  m = ( aTime - ( h * 3600 )) / 60;
  s = ( aTime - ( h * 3600 )) - ( m * 60 );
  return EwConcatString( EwConcatString( EwConcatString( EwConcatString( EwNewStringInt( 
    h, 2, 10 ), EwLoadString( &_Const0004 )), EwNewStringInt( m, 2, 10 )), EwLoadString( 
    &_Const0004 )), EwNewStringInt( s, 2, 10 ));
}

/* 'C' function for method : 'Tools::HelperCollection.GetTimeUnitString()' */
XString ToolsHelperCollection_GetTimeUnitString( ToolsHelperCollection _this, ResourcesFont 
  aTimeFont, ResourcesFont aUnitFont )
{
  XString unitStr = 0;
  XInt32 itemWidth = ResourcesFont_GetTextAdvance( aTimeFont, EwLoadString( &_Const0005 ), 
    0, -1 );
  XInt32 sepWidth = ResourcesFont_GetGlyphAdvance( aTimeFont, ':' );
  XInt32 spaceWidth = ResourcesFont_GetGlyphAdvance( aUnitFont, 0x0020 );

  unitStr = EwConcatString( unitStr, ToolsHelperCollection_getCenteredUnit( _this, 
  EwLoadString( &StringsUnit_hour ), aUnitFont, itemWidth, spaceWidth ));
  unitStr = EwConcatString( unitStr, ToolsHelperCollection_getCenteredUnit( _this, 
  EwLoadString( &StringsUnit_min ), aUnitFont, itemWidth + ( 2 * sepWidth ), spaceWidth ));
  unitStr = EwConcatString( unitStr, ToolsHelperCollection_getCenteredUnit( _this, 
  EwLoadString( &StringsUnit_sec ), aUnitFont, itemWidth + sepWidth, spaceWidth ));
  return unitStr;
}

/* 'C' function for method : 'Tools::HelperCollection.getCenteredUnit()' */
XString ToolsHelperCollection_getCenteredUnit( ToolsHelperCollection _this, XString 
  aUnit, ResourcesFont aUnitFont, XInt32 aTimeItemWidth, XInt32 aSpaceWidth )
{
  XString unitStr;
  XInt32 unitItemW;
  XInt32 spaceNr;
  XInt32 spaces;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  unitStr = 0;
  unitItemW = ResourcesFont_GetTextAdvance( aUnitFont, aUnit, 0, -1 );
  spaceNr = (( aTimeItemWidth - unitItemW ) / aSpaceWidth ) / 2;
  spaces = spaceNr;

  while ( spaces > 0 )
  {
    unitStr = EwConcatString( unitStr, EwLoadString( &_Const0006 ));
    spaces--;
  }

  unitStr = EwConcatString( unitStr, aUnit );
  spaces = spaceNr;

  while ( spaces > 0 )
  {
    unitStr = EwConcatString( unitStr, EwLoadString( &_Const0006 ));
    spaces--;
  }

  return unitStr;
}

/* 'C' function for method : 'Tools::HelperCollection.SetQuadViewBounds()' */
void ToolsHelperCollection_SetQuadViewBounds( ToolsHelperCollection _this, CoreQuadView 
  aView, XRect aBounds )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );

  CoreQuadView__OnSetPoint1( aView, EwNewPoint( aBounds.Point1.X, aBounds.Point1.Y ));
  CoreQuadView__OnSetPoint2( aView, EwNewPoint( aBounds.Point2.X, aBounds.Point1.Y ));
  CoreQuadView__OnSetPoint3( aView, EwNewPoint( aBounds.Point2.X, aBounds.Point2.Y ));
  CoreQuadView__OnSetPoint4( aView, EwNewPoint( aBounds.Point1.X, aBounds.Point2.Y ));
}

/* Variants derived from the class : 'Tools::HelperCollection' */
EW_DEFINE_CLASS_VARIANTS( ToolsHelperCollection )
EW_END_OF_CLASS_VARIANTS( ToolsHelperCollection )

/* Virtual Method Table (VMT) for the class : 'Tools::HelperCollection' */
EW_DEFINE_CLASS( ToolsHelperCollection, XObject, _.VMT, _.VMT, _.VMT, _.VMT, _.VMT, 
                 _.VMT, "Tools::HelperCollection" )
EW_END_OF_CLASS( ToolsHelperCollection )

/* User defined auto object: 'Tools::Helper' */
EW_DEFINE_AUTOOBJECT( ToolsHelper, ToolsHelperCollection )

/* Initializer for the auto object 'Tools::Helper' */
void ToolsHelper__Init( ToolsHelperCollection _this )
{
  EW_UNUSED_ARG( _this );
}

/* Re-Initializer for the auto object 'Tools::Helper' */
void ToolsHelper__ReInit( ToolsHelperCollection _this )
{
  EW_UNUSED_ARG( _this );
}

/* Table with links to derived variants of the auto object : 'Tools::Helper' */
EW_DEFINE_AUTOOBJECT_VARIANTS( ToolsHelper )
EW_END_OF_AUTOOBJECT_VARIANTS( ToolsHelper )

/* Embedded Wizard */
