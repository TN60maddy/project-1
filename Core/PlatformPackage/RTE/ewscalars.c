/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This software and related documentation ("Software") are intellectual
* property owned by TARA Systems and are copyright of TARA Systems.
* Any modification, copying, reproduction or redistribution of the Software in
* whole or in part by any means not in accordance with the End-User License
* Agreement for Embedded Wizard is expressly prohibited. The removal of this
* preamble is expressly prohibited.
*
********************************************************************************
*
* DESCRIPTION:
*   This module is a part of the Embedded Wizard Runtime Environment EWRTE.
*   This environment consists of functions, type definitions and 'C' macros
*   used inside the automatic generated 'C' code.
*
*   The module 'ewscalar.c' contains a set of EWRTE functions purpose-built for
*   operations with the Choras datatypes 'int8', 'int16' .. 'uint32', 'bool',
*   'float', 'enum' and 'set'.
*
* SUBROUTINES:
*   EwSetContains
*   EwGetVariantOfInt8
*   EwGetVariantOfInt16
*   EwGetVariantOfInt32
*   EwGetVariantOfInt64
*   EwGetVariantOfUInt8
*   EwGetVariantOfUInt16
*   EwGetVariantOfUInt32
*   EwGetVariantOfUInt64
*   EwGetVariantOfBool
*   EwGetVariantOfFloat
*   EwGetVariantOfEnum
*   EwGetVariantOfSet
*   EwGetInt32Abs
*   EwGetInt64Abs
*   EwGetFloatAbs
*   EwGetPointAbs
*   EwGetRectAbs
*   EwGetInt32UAbs
*   EwGetInt64UAbs
*   EwNewFloatNaN
*   EwNewFloatInfP
*   EwNewFloatInfN
*   EwIsFloatNaN
*   EwIsFloatInf
*   EwIsFloatInfP
*   EwIsFloatInfN
*   EwGetInt32Min
*   EwGetUInt32Min
*   EwGetInt64Min
*   EwGetUInt64Min
*   EwGetFloatMin
*   EwGetColorMin
*   EwGetPointMin
*   EwGetRectMin
*   EwGetInt32Max
*   EwGetUInt32Max
*   EwGetInt64Max
*   EwGetUInt64Max
*   EwGetFloatMax
*   EwGetColorMax
*   EwGetPointMax
*   EwGetRectMax
*   EwMathMixInt32
*   EwMathMixUInt32
*   EwMathMixInt64
*   EwMathMixUInt64
*   EwMathMixFloat
*   EwMathMixPoint
*   EwMathMixRect
*   EwMathMixColor
*   EwMathLength
*   EwMathLengthPoint
*   EwMathTrunc
*   EwMathFract
*
*******************************************************************************/

#include "ewrte.h"
#include "ewextrte.h"


/* EwLangId contains the ID of the currently selected language. LangId will be
   used to find out the correct variant of a constant in the following functions
   EwGetVariantOfXXX() */
extern int EwLangId;


/*******************************************************************************
* FUNCTION:
*   EwSetContains
*
* DESCRIPTION:
*   The function EwSetContains() implements the Chora instant method
*   'set.contains()'.
*
* ARGUMENTS:
*   aSet1 - The first set to verify its content.
*   aSet2 - The second set.
*
* RETURN VALUE:
*   The function returns != 0, if the second set aSet2 is contained in the
*   given aSet1.
*
*******************************************************************************/
XBool EwSetContains( XSet aSet1, XSet aSet2 )
{
  return aSet2 && (( aSet1 & aSet2 ) == aSet2 );
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfInt8
*
* DESCRIPTION:
*   The function EwGetVariantOfInt8() will be called to determinate a value
*   of a multilingual/multivariant constant depending on the currently selected
*   language and the styles set.
*
*   If the currently selected language could not be found in the multilingual
*   constant, the function returns the value corresponding to the default
*   language (LangId == 0). In case of a multivariant constant, the function
*   evaluates the variants in order to find one, which fits the styles currently
*   active in the styles set.
*
* ARGUMENTS:
*   aVariants - A pointer to the constant containing multiple int8 values.
*
* RETURN VALUE:
*   Returns the determinated int8 value.
*
*******************************************************************************/
XInt8 EwGetVariantOfInt8( const XVariant* aConstant )
{
  const XVariantOfInt8* data = EwGetVariantOf( aConstant, XVariantOfInt8 );

  /* The content of the constant is available directly in the binary. */
  if ( data->LangId != EW_BLOB_LANG_ID )
    return data->Value;

  /* The constant should be available in a BLOB file. */
  else
  {
    const XInt8* v = (const XInt8*)EwGetBlobConstant((const XBlobLink*)data,
                                                      EW_BLOB_TYPE_INT8 );

    /* Return the content of the constant if it was found or its zero value
       if it was not found. */
    return v? *v : 0;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfInt16
*
* DESCRIPTION:
*   The function EwGetVariantOfInt16() will be called to determinate a value
*   of a multilingual/multivariant constant depending on the currently selected
*   language and the styles set.
*
*   If the currently selected language could not be found in the multilingual
*   constant, the function returns the value corresponding to the default
*   language (LangId == 0). In case of a multivariant constant, the function
*   evaluates the variants in order to find one, which fits the styles currently
*   active in the styles set.
*
* ARGUMENTS:
*   aVariants - A pointer to the constant containing multiple int16 values.
*
* RETURN VALUE:
*   Returns the determinated int16 value.
*
*******************************************************************************/
XInt16 EwGetVariantOfInt16( const XVariant* aConstant )
{
  const XVariantOfInt16* data = EwGetVariantOf( aConstant, XVariantOfInt16 );

  /* The content of the constant is available directly in the binary. */
  if ( data->LangId != EW_BLOB_LANG_ID )
    return data->Value;

  /* The constant should be available in a BLOB file. */
  else
  {
    const XInt16* v = (const XInt16*)EwGetBlobConstant((const XBlobLink*)data,
                                                        EW_BLOB_TYPE_INT16 );

    /* Return the content of the constant if it was found or its zero value
       if it was not found. */
    return v? *v : 0;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfInt32
*
* DESCRIPTION:
*   The function EwGetVariantOfInt32() will be called to determinate a value
*   of a multilingual/multivariant constant depending on the currently selected
*   language and the styles set.
*
*   If the currently selected language could not be found in the multilingual
*   constant, the function returns the value corresponding to the default
*   language (LangId == 0). In case of a multivariant constant, the function
*   evaluates the variants in order to find one, which fits the styles currently
*   active in the styles set.
*
* ARGUMENTS:
*   aVariants - A pointer to the constant containing multiple int32 values.
*
* RETURN VALUE:
*   Returns the determinated int32 value.
*
*******************************************************************************/
XInt32 EwGetVariantOfInt32( const XVariant* aConstant )
{
  const XVariantOfInt32* data = EwGetVariantOf( aConstant, XVariantOfInt32 );

  /* The content of the constant is available directly in the binary. */
  if ( data->LangId != EW_BLOB_LANG_ID )
    return data->Value;

  /* The constant should be available in a BLOB file. */
  else
  {
    const XInt32* v = (const XInt32*)EwGetBlobConstant((const XBlobLink*)data,
                                                        EW_BLOB_TYPE_INT32 );

    /* Return the content of the constant if it was found or its zero value
       if it was not found. */
    return v? *v : 0;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfInt64
*
* DESCRIPTION:
*   The function EwGetVariantOfInt64() will be called to determinate a value
*   of a multilingual/multivariant constant depending on the currently selected
*   language and the styles set.
*
*   If the currently selected language could not be found in the multilingual
*   constant, the function returns the value corresponding to the default
*   language (LangId == 0). In case of a multivariant constant, the function
*   evaluates the variants in order to find one, which fits the styles currently
*   active in the styles set.
*
* ARGUMENTS:
*   aVariants - A pointer to the constant containing multiple int64 values.
*
* RETURN VALUE:
*   Returns the determinated int64 value.
*
*******************************************************************************/
XInt64 EwGetVariantOfInt64( const XVariant* aConstant )
{
  const XVariantOfInt64* data = EwGetVariantOf( aConstant, XVariantOfInt64 );

  /* The content of the constant is available directly in the binary. */
  if ( data->LangId != EW_BLOB_LANG_ID )
    return data->Value;

  /* The constant should be available in a BLOB file. */
  else
  {
    const XInt64* v = (const XInt64*)EwGetBlobConstant((const XBlobLink*)data,
                                                        EW_BLOB_TYPE_INT64 );

    /* Return the content of the constant if it was found or its zero value
       if it was not found. */
    return v? *v : 0;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfUInt8
*
* DESCRIPTION:
*   The function EwGetVariantOfUInt8() will be called to determinate a value
*   of a multilingual/multivariant constant depending on the currently selected
*   language and the styles set.
*
*   If the currently selected language could not be found in the multilingual
*   constant, the function returns the value corresponding to the default
*   language (LangId == 0). In case of a multivariant constant, the function
*   evaluates the variants in order to find one, which fits the styles currently
*   active in the styles set.
*
* ARGUMENTS:
*   aVariants - A pointer to the constant containing multiple uint8 values.
*
* RETURN VALUE:
*   Returns the determinated uint8 value.
*
*******************************************************************************/
XUInt8 EwGetVariantOfUInt8( const XVariant* aConstant )
{
  const XVariantOfUInt8* data = EwGetVariantOf( aConstant, XVariantOfUInt8 );

  /* The content of the constant is available directly in the binary. */
  if ( data->LangId != EW_BLOB_LANG_ID )
    return data->Value;

  /* The constant should be available in a BLOB file. */
  else
  {
    const XUInt8* v = (const XUInt8*)EwGetBlobConstant((const XBlobLink*)data,
                                                        EW_BLOB_TYPE_UINT8 );

    /* Return the content of the constant if it was found or its zero value
       if it was not found. */
    return v? *v : 0;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfUInt16
*
* DESCRIPTION:
*   The function EwGetVariantOfUInt16() will be called to determinate a value
*   of a multilingual/multivariant constant depending on the currently selected
*   language and the styles set.
*
*   If the currently selected language could not be found in the multilingual
*   constant, the function returns the value corresponding to the default
*   language (LangId == 0). In case of a multivariant constant, the function
*   evaluates the variants in order to find one, which fits the styles currently
*   active in the styles set.
*
* ARGUMENTS:
*   aVariants - A pointer to the constant containing multiple uint16 values.
*
* RETURN VALUE:
*   Returns the determinated uint16 value.
*
*******************************************************************************/
XUInt16 EwGetVariantOfUInt16( const XVariant* aConstant )
{
  const XVariantOfUInt16* data = EwGetVariantOf( aConstant, XVariantOfUInt16 );

  /* The content of the constant is available directly in the binary. */
  if ( data->LangId != EW_BLOB_LANG_ID )
    return data->Value;

  /* The constant should be available in a BLOB file. */
  else
  {
    const XUInt16* v = (const XUInt16*)EwGetBlobConstant((const XBlobLink*)data,
                                                        EW_BLOB_TYPE_UINT16 );

    /* Return the content of the constant if it was found or its zero value
       if it was not found. */
    return v? *v : 0;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfUInt32
*
* DESCRIPTION:
*   The function EwGetVariantOfUInt32() will be called to determinate a value
*   of a multilingual/multivariant constant depending on the currently selected
*   language and the styles set.
*
*   If the currently selected language could not be found in the multilingual
*   constant, the function returns the value corresponding to the default
*   language (LangId == 0). In case of a multivariant constant, the function
*   evaluates the variants in order to find one, which fits the styles currently
*   active in the styles set.
*
* ARGUMENTS:
*   aVariants - A pointer to the constant containing multiple uint32 values.
*
* RETURN VALUE:
*   Returns the determinated uint32 value.
*
*******************************************************************************/
XUInt32 EwGetVariantOfUInt32( const XVariant* aConstant )
{
  const XVariantOfUInt32* data = EwGetVariantOf( aConstant, XVariantOfUInt32 );

  /* The content of the constant is available directly in the binary. */
  if ( data->LangId != EW_BLOB_LANG_ID )
    return data->Value;

  /* The constant should be available in a BLOB file. */
  else
  {
    const XUInt32* v = (const XUInt32*)EwGetBlobConstant((const XBlobLink*)data,
                                                          EW_BLOB_TYPE_UINT32 );

    /* Return the content of the constant if it was found or its zero value
       if it was not found. */
    return v? *v : 0;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfUInt64
*
* DESCRIPTION:
*   The function EwGetVariantOfUInt64() will be called to determinate a value
*   of a multilingual/multivariant constant depending on the currently selected
*   language and the styles set.
*
*   If the currently selected language could not be found in the multilingual
*   constant, the function returns the value corresponding to the default
*   language (LangId == 0). In case of a multivariant constant, the function
*   evaluates the variants in order to find one, which fits the styles currently
*   active in the styles set.
*
* ARGUMENTS:
*   aVariants - A pointer to the constant containing multiple uint64 values.
*
* RETURN VALUE:
*   Returns the determinated uint64 value.
*
*******************************************************************************/
XUInt64 EwGetVariantOfUInt64( const XVariant* aConstant )
{
  const XVariantOfUInt64* data = EwGetVariantOf( aConstant, XVariantOfUInt64 );

  /* The content of the constant is available directly in the binary. */
  if ( data->LangId != EW_BLOB_LANG_ID )
    return data->Value;

  /* The constant should be available in a BLOB file. */
  else
  {
    const XUInt64* v = (const XUInt64*)EwGetBlobConstant((const XBlobLink*)data,
                                                          EW_BLOB_TYPE_UINT64 );

    /* Return the content of the constant if it was found or its zero value
       if it was not found. */
    return v? *v : 0;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfBool
*
* DESCRIPTION:
*   The function EwGetVariantOfBool() will be called to determinate a value
*   of a multilingual/multivariant constant depending on the currently selected
*   language and the styles set.
*
*   If the currently selected language could not be found in the multilingual
*   constant, the function returns the value corresponding to the default
*   language (LangId == 0). In case of a multivariant constant, the function
*   evaluates the variants in order to find one, which fits the styles currently
*   active in the styles set.
*
* ARGUMENTS:
*   aVariants - A pointer to the constant containing multiple bool values.
*
* RETURN VALUE:
*   Returns the determinated bool value.
*
*******************************************************************************/
XBool EwGetVariantOfBool( const XVariant* aConstant )
{
  const XVariantOfBool* data = EwGetVariantOf( aConstant, XVariantOfBool );

  /* The content of the constant is available directly in the binary. */
  if ( data->LangId != EW_BLOB_LANG_ID )
    return data->Value;

  /* The constant should be available in a BLOB file. */
  else
  {
    const XBool* v = (const XBool*)EwGetBlobConstant((const XBlobLink*)data,
                                                      EW_BLOB_TYPE_BOOL );

    /* Return the content of the constant if it was found or its zero value
       if it was not found. */
    return v? *v : 0;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfFloat
*
* DESCRIPTION:
*   The function EwGetVariantOfFloat() will be called to determinate a value
*   of a multilingual/multivariant constant depending on the currently selected
*   language and the styles set.
*
*   If the currently selected language could not be found in the multilingual
*   constant, the function returns the value corresponding to the default
*   language (LangId == 0). In case of a multivariant constant, the function
*   evaluates the variants in order to find one, which fits the styles currently
*   active in the styles set.
*
* ARGUMENTS:
*   aVariants - A pointer to the constant containing multiple float values.
*
* RETURN VALUE:
*   Returns the determinated float value.
*
*******************************************************************************/
XFloat EwGetVariantOfFloat( const XVariant* aConstant )
{
  const XVariantOfFloat* data = EwGetVariantOf( aConstant, XVariantOfFloat );

  /* The content of the constant is available directly in the binary. */
  if ( data->LangId != EW_BLOB_LANG_ID )
    return data->Value;

  /* The constant should be available in a BLOB file. */
  else
  {
    const XFloat* v = (const XFloat*)EwGetBlobConstant((const XBlobLink*)data,
                                                        EW_BLOB_TYPE_FLOAT );

    /* Return the content of the constant if it was found or its zero value
       if it was not found. */
    return v? *v : 0;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfEnum
*
* DESCRIPTION:
*   The function EwGetVariantOfEnum() will be called to determinate a value
*   of a multilingual/multivariant constant depending on the currently selected
*   language and the styles set.
*
*   If the currently selected language could not be found in the multilingual
*   constant, the function returns the value corresponding to the default
*   language (LangId == 0). In case of a multivariant constant, the function
*   evaluates the variants in order to find one, which fits the styles currently
*   active in the styles set.
*
* ARGUMENTS:
*   aVariants - A pointer to the constant containing multiple enum values.
*
* RETURN VALUE:
*   Returns the determinated enum value.
*
*******************************************************************************/
XEnum EwGetVariantOfEnum( const XVariant* aConstant )
{
  const XVariantOfEnum* data = EwGetVariantOf( aConstant, XVariantOfEnum );

  /* The content of the constant is available directly in the binary. */
  if ( data->LangId != EW_BLOB_LANG_ID )
    return data->Value;

  /* The constant should be available in a BLOB file. */
  else
  {
    const XEnum* v = (const XEnum*)EwGetBlobConstant((const XBlobLink*)data,
                                                      EW_BLOB_TYPE_ENUM );

    /* Return the content of the constant if it was found or its zero value
       if it was not found. */
    return v? *v : 0;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfSet
*
* DESCRIPTION:
*   The function EwGetVariantOfSet() will be called to determinate a value
*   of a multilingual/multivariant constant depending on the currently selected
*   language and the styles set.
*
*   If the currently selected language could not be found in the multilingual
*   constant, the function returns the value corresponding to the default
*   language (LangId == 0). In case of a multivariant constant, the function
*   evaluates the variants in order to find one, which fits the styles currently
*   active in the styles set.
*
* ARGUMENTS:
*   aVariants - A pointer to the constant containing multiple set values.
*
* RETURN VALUE:
*   Returns the determinated set value.
*
*******************************************************************************/
XSet EwGetVariantOfSet( const XVariant* aConstant )
{
  const XVariantOfSet* data = EwGetVariantOf( aConstant, XVariantOfSet );

  /* The content of the constant is available directly in the binary. */
  if ( data->LangId != EW_BLOB_LANG_ID )
    return data->Value;

  /* The constant should be available in a BLOB file. */
  else
  {
    const XSet* v = (const XSet*)EwGetBlobConstant((const XBlobLink*)data,
                                                    EW_BLOB_TYPE_SET );

    /* Return the content of the constant if it was found or its zero value
       if it was not found. */
    return v? *v : 0;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwGetInt32Abs
*
* DESCRIPTION:
*   The function EwGetInt32Abs() implements the Chora int8.abs, int16.abs,
*   int32.abs instant properties.
*
* ARGUMENTS:
*   aValue - A value to calculate its absolute value.
*
* RETURN VALUE:
*   Returns the absolute value of aValue.
*
*******************************************************************************/
XInt32 EwGetInt32Abs( XInt32 aValue )
{
  return ( aValue < 0 )? -aValue : aValue;
}


/*******************************************************************************
* FUNCTION:
*   EwGetInt64Abs
*
* DESCRIPTION:
*   The function EwGetInt64Abs() implements the Chora int8.abs, int16.abs,
*   int64.abs instant properties.
*
* ARGUMENTS:
*   aValue - A value to calculate its absolute value.
*
* RETURN VALUE:
*   Returns the absolute value of aValue.
*
*******************************************************************************/
XInt64 EwGetInt64Abs( XInt64 aValue )
{
  return ( aValue < 0 )? -aValue : aValue;
}


/*******************************************************************************
* FUNCTION:
*   EwGetFloatAbs
*
* DESCRIPTION:
*   The function EwGetFloatAbs() implements the Chora float.abs instant property.
*
* ARGUMENTS:
*   aValue - A value to calculate its absolute value.
*
* RETURN VALUE:
*   Returns the absolute value of aValue.
*
*******************************************************************************/
XFloat EwGetFloatAbs( XFloat aValue )
{
  return ( aValue < 0.0f )? -aValue : aValue;
}


/*******************************************************************************
* FUNCTION:
*   EwGetPointAbs
*
* DESCRIPTION:
*   The function EwGetPointAbs() implements the Chora point.abs instant
*   property.
*
* ARGUMENTS:
*   aValue - A value to calculate its absolute value.
*
* RETURN VALUE:
*   Returns the absolute value of aValue.
*
*******************************************************************************/
XPoint EwGetPointAbs( XPoint aValue )
{
  if ( aValue.X < 0 ) aValue.X = -aValue.X;
  if ( aValue.Y < 0 ) aValue.Y = -aValue.Y;

  return aValue;
}


/*******************************************************************************
* FUNCTION:
*   EwGetRectAbs
*
* DESCRIPTION:
*   The function EwGetRectAbs() implements the Chora rect.abs instant
*   property.
*
* ARGUMENTS:
*   aValue - A value to calculate its absolute value.
*
* RETURN VALUE:
*   Returns the absolute value of aValue.
*
*******************************************************************************/
XRect EwGetRectAbs( XRect aValue )
{
  if ( aValue.Point1.X < 0 ) aValue.Point1.X = -aValue.Point1.X;
  if ( aValue.Point1.Y < 0 ) aValue.Point1.Y = -aValue.Point1.Y;
  if ( aValue.Point2.X < 0 ) aValue.Point2.X = -aValue.Point2.X;
  if ( aValue.Point2.Y < 0 ) aValue.Point2.Y = -aValue.Point2.Y;

  return aValue;
}


/*******************************************************************************
* FUNCTION:
*   EwGetInt32UAbs
*
* DESCRIPTION:
*   The function EwGetInt32UAbs() implements the Chora int8.uabs, int16.uabs,
*   int32.uabs instant properties.
*
* ARGUMENTS:
*   aValue - A value to calculate its absolute value.
*
* RETURN VALUE:
*   Returns the absolute value of aValue.
*
*******************************************************************************/
XUInt32 EwGetInt32UAbs( XInt32 aValue )
{
  return ( aValue < 0 )? (XUInt32)-aValue : (XUInt32)aValue;
}


/*******************************************************************************
* FUNCTION:
*   EwGetInt64UAbs
*
* DESCRIPTION:
*   The function EwGetInt64UAbs() implements the Chora int8.uabs, int16.uabs,
*   int64.uabs instant properties.
*
* ARGUMENTS:
*   aValue - A value to calculate its absolute value.
*
* RETURN VALUE:
*   Returns the absolute value of aValue.
*
*******************************************************************************/
XUInt64 EwGetInt64UAbs( XInt64 aValue )
{
  return ( aValue < 0 )? (XUInt64)-aValue : (XUInt64)aValue;
}


/*******************************************************************************
* FUNCTION:
*   EwNewFloatNaN
*
* DESCRIPTION:
*   The function EwNewFloatNaN() return the value corresponding to float NAN.
*
*   EwNewFloatNaN() implements the Chora instant constructor:
*   'float_nan()'.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   Returns the initialized float value.
*
*******************************************************************************/
XFloat EwNewFloatNaN( void )
{
  static const unsigned int valNAN = 0x7F800001;
  const void* ptr = &valNAN;
  return *((float*)ptr);
}


/*******************************************************************************
* FUNCTION:
*   EwNewFloatInfP
*
* DESCRIPTION:
*   The function EwNewFloatInfP() return the value corresponding to float +INF.
*
*   EwNewFloatInfP() implements the Chora instant constructor:
*   'float_infp()'.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   Returns the initialized float value.
*
*******************************************************************************/
XFloat EwNewFloatInfP( void )
{
  static const unsigned int valINFP = 0x7F800000;
  const void* ptr = &valINFP;
  return *((float*)ptr);
}


/*******************************************************************************
* FUNCTION:
*   EwNewFloatInfN
*
* DESCRIPTION:
*   The function EwNewFloatInfN() return the value corresponding to float -INF.
*
*   EwNewFloatInfN() implements the Chora instant constructor:
*   'float_infn()'.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   Returns the initialized float value.
*
*******************************************************************************/
XFloat EwNewFloatInfN( void )
{
  static const unsigned int valINFN = 0xFF800000;
  const void* ptr = &valINFN;
  return *((float*)ptr);
}


/*******************************************************************************
* FUNCTION:
*   EwIsFloatNaN
*
* DESCRIPTION:
*   The function EwIsFloatNaN() implements the Chora float.isnan instant
*   property.
*
* ARGUMENTS:
*   aValue - A value to test whether it is 'not a number'.
*
* RETURN VALUE:
*   Returns != 0 if the given value is not a number.
*
*******************************************************************************/
XBool EwIsFloatNaN( XFloat aValue )
{
  void* ptr = &aValue;
  unsigned int l = *((unsigned int*)ptr );

  if (( l > 0x7F800000 ) && ( l <= 0x7FFFFFFF )) return 1;
  if ( l > 0xFF800000 ) return 1;

  return 0;
}


/*******************************************************************************
* FUNCTION:
*   EwIsFloatInf
*
* DESCRIPTION:
*   The function EwIsFloatInf() implements the Chora float.isinf instant
*   property.
*
* ARGUMENTS:
*   aValue - A value to test whether it is a positive/negative infinite value.
*
* RETURN VALUE:
*   Returns != 0 if the given value is +/- infinite.
*
*******************************************************************************/
XBool EwIsFloatInf( XFloat aValue )
{
  void* ptr = &aValue;
  unsigned int l = *((unsigned int*)ptr );

  if ( l == 0x7F800000 ) return 1;
  if ( l == 0xFF800000 ) return 1;

  return 0;
}


/*******************************************************************************
* FUNCTION:
*   EwIsFloatInfP
*
* DESCRIPTION:
*   The function EwIsFloatInfP() implements the Chora float.isinfp instant
*   property.
*
* ARGUMENTS:
*   aValue - A value to test whether it is a positive infinite value.
*
* RETURN VALUE:
*   Returns != 0 if the given value is + infinite.
*
*******************************************************************************/
XBool EwIsFloatInfP( XFloat aValue )
{
  void* ptr = &aValue;
  unsigned int l = *((unsigned int*)ptr );

  return l == 0x7F800000;
}


/*******************************************************************************
* FUNCTION:
*   EwIsFloatInfN
*
* DESCRIPTION:
*   The function EwIsFloatInfN() implements the Chora float.isinfn instant
*   property.
*
* ARGUMENTS:
*   aValue - A value to test whether it is a negative infinite value.
*
* RETURN VALUE:
*   Returns != 0 if the given value is - infinite.
*
*******************************************************************************/
XBool EwIsFloatInfN( XFloat aValue )
{
  void* ptr = &aValue;
  unsigned int l = *((unsigned int*)ptr );

  return l == 0xFF800000;
}


/*******************************************************************************
* FUNCTION:
*   EwGetInt32Min
*
* DESCRIPTION:
*   The function EwGetInt32Min() implements the Chora math_min() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the minimum.
*
* RETURN VALUE:
*   Returns the minimum of the given aCount XInt32 values.
*
*******************************************************************************/
XInt32 EwGetInt32Min( int aCount, ... )
{
  va_list marker;
  XInt32  value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XInt32 );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XInt32 tmp = va_arg( marker, XInt32 );

    if ( tmp < value )
      value = tmp;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetUInt32Min
*
* DESCRIPTION:
*   The function EwGetUInt32Min() implements the Chora math_min() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the minimum.
*
* RETURN VALUE:
*   Returns the minimum of the given aCount XUInt32 values.
*
*******************************************************************************/
XUInt32 EwGetUInt32Min( int aCount, ... )
{
  va_list marker;
  XUInt32 value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XUInt32 );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XUInt32 tmp = va_arg( marker, XUInt32 );

    if ( tmp < value )
      value = tmp;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetInt64Min
*
* DESCRIPTION:
*   The function EwGetInt64Min() implements the Chora math_min() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the minimum.
*
* RETURN VALUE:
*   Returns the minimum of the given aCount XInt64 values.
*
*******************************************************************************/
XInt64 EwGetInt64Min( int aCount, ... )
{
  va_list marker;
  XInt64  value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XInt64 );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XInt64 tmp = va_arg( marker, XInt64 );

    if ( tmp < value )
      value = tmp;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetUInt64Min
*
* DESCRIPTION:
*   The function EwGetUInt64Min() implements the Chora math_min() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the minimum.
*
* RETURN VALUE:
*   Returns the minimum of the given aCount XUInt64 values.
*
*******************************************************************************/
XUInt64 EwGetUInt64Min( int aCount, ... )
{
  va_list marker;
  XUInt64 value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XUInt64 );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XUInt64 tmp = va_arg( marker, XUInt64 );

    if ( tmp < value )
      value = tmp;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetFloatMin
*
* DESCRIPTION:
*   The function EwGetFloatMin() implements the Chora math_min() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the minimum.
*
* RETURN VALUE:
*   Returns the minimum of the given aCount XFloat values.
*
*******************************************************************************/
XFloat EwGetFloatMin( int aCount, ... )
{
  va_list marker;
  XFloat  value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = (XFloat)va_arg( marker, double );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XFloat tmp = (XFloat)va_arg( marker, double );

    if ( tmp < value )
      value = tmp;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetColorMin
*
* DESCRIPTION:
*   The function EwGetColorMin() implements the Chora math_min() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the minimum.
*
* RETURN VALUE:
*   Returns the minimum of the given aCount XColor values.
*
*******************************************************************************/
XColor EwGetColorMin( int aCount, ... )
{
  va_list marker;
  XColor  value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XColor );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XColor tmp = va_arg( marker, XColor );

    if ( tmp.Red   < value.Red   ) value.Red   = tmp.Red;
    if ( tmp.Green < value.Green ) value.Green = tmp.Green;
    if ( tmp.Blue  < value.Blue  ) value.Blue  = tmp.Blue;
    if ( tmp.Alpha < value.Alpha ) value.Alpha = tmp.Alpha;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetPointMin
*
* DESCRIPTION:
*   The function EwGetPointMin() implements the Chora math_min() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the minimum.
*
* RETURN VALUE:
*   Returns the minimum of the given aCount XPoint values.
*
*******************************************************************************/
XPoint EwGetPointMin( int aCount, ... )
{
  va_list marker;
  XPoint  value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XPoint );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XPoint tmp = va_arg( marker, XPoint );

    if ( tmp.X < value.X ) value.X = tmp.X;
    if ( tmp.Y < value.Y ) value.Y = tmp.Y;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetRectMin
*
* DESCRIPTION:
*   The function EwGetRectMin() implements the Chora math_min() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the minimum.
*
* RETURN VALUE:
*   Returns the minimum of the given aCount XRect values.
*
*******************************************************************************/
XRect EwGetRectMin( int aCount, ... )
{
  va_list marker;
  XRect   value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XRect );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XRect tmp = va_arg( marker, XRect );

    if ( tmp.Point1.X < value.Point1.X ) value.Point1.X = tmp.Point1.X;
    if ( tmp.Point1.Y < value.Point1.Y ) value.Point1.Y = tmp.Point1.Y;
    if ( tmp.Point2.X < value.Point2.X ) value.Point2.X = tmp.Point2.X;
    if ( tmp.Point2.Y < value.Point2.Y ) value.Point2.Y = tmp.Point2.Y;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetInt32Max
*
* DESCRIPTION:
*   The function EwGetInt32Max() implements the Chora math_min() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the minimum.
*
* RETURN VALUE:
*   Returns the minimum of the given aCount XInt32 values.
*
*******************************************************************************/
XInt32 EwGetInt32Max( int aCount, ... )
{
  va_list marker;
  XInt32  value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XInt32 );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XInt32 tmp = va_arg( marker, XInt32 );

    if ( tmp > value )
      value = tmp;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetUInt32Max
*
* DESCRIPTION:
*   The function EwGetUInt32Max() implements the Chora math_min() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the minimum.
*
* RETURN VALUE:
*   Returns the minimum of the given aCount XUInt32 values.
*
*******************************************************************************/
XUInt32 EwGetUInt32Max( int aCount, ... )
{
  va_list marker;
  XUInt32 value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XUInt32 );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XUInt32 tmp = va_arg( marker, XUInt32 );

    if ( tmp > value )
      value = tmp;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetInt64Max
*
* DESCRIPTION:
*   The function EwGetInt64Max() implements the Chora math_min() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the minimum.
*
* RETURN VALUE:
*   Returns the minimum of the given aCount XInt64 values.
*
*******************************************************************************/
XInt64 EwGetInt64Max( int aCount, ... )
{
  va_list marker;
  XInt64  value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XInt64 );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XInt64 tmp = va_arg( marker, XInt64 );

    if ( tmp > value )
      value = tmp;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetUInt64Max
*
* DESCRIPTION:
*   The function EwGetUInt64Max() implements the Chora math_min() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the minimum.
*
* RETURN VALUE:
*   Returns the minimum of the given aCount XUInt64 values.
*
*******************************************************************************/
XUInt64 EwGetUInt64Max( int aCount, ... )
{
  va_list marker;
  XUInt64 value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XUInt64 );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XUInt64 tmp = va_arg( marker, XUInt64 );

    if ( tmp > value )
      value = tmp;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetFloatMax
*
* DESCRIPTION:
*   The function EwGetFloatMax() implements the Chora math_min() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the minimum.
*
* RETURN VALUE:
*   Returns the minimum of the given aCount XFloat values.
*
*******************************************************************************/
XFloat EwGetFloatMax( int aCount, ... )
{
  va_list marker;
  XFloat  value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = (XFloat)va_arg( marker, double );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XFloat tmp = (XFloat)va_arg( marker, double );

    if ( tmp > value )
      value = tmp;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetColorMax
*
* DESCRIPTION:
*   The function EwGetColorMax() implements the Chora math_max() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the maximum.
*
* RETURN VALUE:
*   Returns the maximum of the given aCount XColor values.
*
*******************************************************************************/
XColor EwGetColorMax( int aCount, ... )
{
  va_list marker;
  XColor  value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XColor );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XColor tmp = va_arg( marker, XColor );

    if ( tmp.Red   > value.Red   ) value.Red   = tmp.Red;
    if ( tmp.Green > value.Green ) value.Green = tmp.Green;
    if ( tmp.Blue  > value.Blue  ) value.Blue  = tmp.Blue;
    if ( tmp.Alpha > value.Alpha ) value.Alpha = tmp.Alpha;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetPointMax
*
* DESCRIPTION:
*   The function EwGetPointMax() implements the Chora math_max() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the maximum.
*
* RETURN VALUE:
*   Returns the maximum of the given aCount XPoint values.
*
*******************************************************************************/
XPoint EwGetPointMax( int aCount, ... )
{
  va_list marker;
  XPoint  value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XPoint );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XPoint tmp = va_arg( marker, XPoint );

    if ( tmp.X > value.X ) value.X = tmp.X;
    if ( tmp.Y > value.Y ) value.Y = tmp.Y;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetRectMax
*
* DESCRIPTION:
*   The function EwGetRectMax() implements the Chora math_max() function.
*
* ARGUMENTS:
*   aCount - Number of values to estimate the maximum.
*
* RETURN VALUE:
*   Returns the maximum of the given aCount XRect values.
*
*******************************************************************************/
XRect EwGetRectMax( int aCount, ... )
{
  va_list marker;
  XRect   value;
  int     i;

  /* Init arguments. */
  va_start( marker, aCount );
  value = va_arg( marker, XRect );

  /* Iterate over all available arguments */
  for ( i = 1; i < aCount; i++ )
  {
    XRect tmp = va_arg( marker, XRect );

    if ( tmp.Point1.X > value.Point1.X ) value.Point1.X = tmp.Point1.X;
    if ( tmp.Point1.Y > value.Point1.Y ) value.Point1.Y = tmp.Point1.Y;
    if ( tmp.Point2.X > value.Point2.X ) value.Point2.X = tmp.Point2.X;
    if ( tmp.Point2.Y > value.Point2.Y ) value.Point2.Y = tmp.Point2.Y;
  }

  /* Complete */
  va_end( marker );
  return value;
}


/*******************************************************************************
* FUNCTION:
*   EwMathMixInt32
*
* DESCRIPTION:
*   The function EwMathMixInt32() implements the Chora math_mix() function
*   intended to interpolate an int32 value within a given range.
*
* ARGUMENTS:
*   aValue1 - The start value of the range.
*   aValue2 - The end value of the range.
*   aFactor - Factor controlling the interpolation.
*
* RETURN VALUE:
*   Returns a value lying between aValue1 and aValue2 according to the parameter
*   aFactor. If aFactor <= 0.0, the function returns aValue1. If aFactor >= 1.0,
*   the function returns aValue2.
*
*******************************************************************************/
XInt32 EwMathMixInt32( XInt32 aValue1, XInt32 aValue2, XFloat aFactor )
{
  unsigned int fi;
  XInt32       r;
  signed int   s;

  if ( aFactor < 0.0f ) aFactor = 0.0f;
  if ( aFactor > 1.0f ) aFactor = 1.0f;

  fi = (unsigned int)( 65536.0f * aFactor );
  r  = aValue2 - aValue1;
  s  = ( r < 0 )? -1 : 1;
  r *= s;
  r  = (( fi * (( r >>  0 ) & 0xFFFF )) >> 16 ) +
       (( fi * (( r >> 16 ) & 0xFFFF )) >>  0 );
  r *= s;

  return aValue1 + r;
}


/*******************************************************************************
* FUNCTION:
*   EwMathMixUInt32
*
* DESCRIPTION:
*   The function EwMathMixUInt32() implements the Chora math_mix() function
*   intended to interpolate an uint32 value within a given range.
*
* ARGUMENTS:
*   aValue1 - The start value of the range.
*   aValue2 - The end value of the range.
*   aFactor - Factor controlling the interpolation.
*
* RETURN VALUE:
*   Returns a value lying between aValue1 and aValue2 according to the parameter
*   aFactor. If aFactor <= 0.0, the function returns aValue1. If aFactor >= 1.0,
*   the function returns aValue2.
*
*******************************************************************************/
XUInt32 EwMathMixUInt32( XUInt32 aValue1, XUInt32 aValue2, XFloat aFactor )
{
  unsigned int f1, f2;
  XUInt32      r;

  if ( aFactor < 0.0f ) aFactor = 0.0f;
  if ( aFactor > 1.0f ) aFactor = 1.0f;

  f2 = (unsigned int)( 65536.0f * aFactor );
  f1 = 65536 - f2;

  r  = (( f1 * (( aValue1 >>  0 ) & 0xFFFF )) +
        ( f2 * (( aValue2 >>  0 ) & 0xFFFF ))) >> 16;
  r += (( f1 * (( aValue1 >> 16 ) & 0xFFFF )) +
        ( f2 * (( aValue2 >> 16 ) & 0xFFFF ))) >>  0;

  return r;
}


/*******************************************************************************
* FUNCTION:
*   EwMathMixInt64
*
* DESCRIPTION:
*   The function EwMathMixInt64() implements the Chora math_mix() function
*   intended to interpolate an int64 value within a given range.
*
* ARGUMENTS:
*   aValue1 - The start value of the range.
*   aValue2 - The end value of the range.
*   aFactor - Factor controlling the interpolation.
*
* RETURN VALUE:
*   Returns a value lying between aValue1 and aValue2 according to the parameter
*   aFactor. If aFactor <= 0.0, the function returns aValue1. If aFactor >= 1.0,
*   the function returns aValue2.
*
*******************************************************************************/
XInt64 EwMathMixInt64( XInt64 aValue1, XInt64 aValue2, XFloat aFactor )
{
  unsigned int fi;
  XInt64       r;
  signed int   s;

  if ( aFactor < 0.0f ) aFactor = 0.0f;
  if ( aFactor > 1.0f ) aFactor = 1.0f;

  fi = (unsigned int)( 65536.0f * aFactor );
  r  = aValue2 - aValue1;
  s  = ( r < 0 )? -1 : 1;
  r *= s;
  r  = (( fi * (( r >>  0 ) & 0xFFFF )) >> 16 ) +
       (( fi * (( r >> 16 ) & 0xFFFF )) >>  0 ) +
       (( fi * (( r >> 32 ) & 0xFFFF )) << 16 ) +
       (( fi * (( r >> 48 ) & 0xFFFF )) << 32 );
  r *= s;

  return aValue1 + r;
}


/*******************************************************************************
* FUNCTION:
*   EwMathMixUInt64
*
* DESCRIPTION:
*   The function EwMathMixUInt64() implements the Chora math_mix() function
*   intended to interpolate an uint64 value within a given range.
*
* ARGUMENTS:
*   aValue1 - The start value of the range.
*   aValue2 - The end value of the range.
*   aFactor - Factor controlling the interpolation.
*
* RETURN VALUE:
*   Returns a value lying between aValue1 and aValue2 according to the parameter
*   aFactor. If aFactor <= 0.0, the function returns aValue1. If aFactor >= 1.0,
*   the function returns aValue2.
*
*******************************************************************************/
XUInt64 EwMathMixUInt64( XUInt64 aValue1, XUInt64 aValue2, XFloat aFactor )
{
  unsigned int f1, f2;
  XUInt64      r;

  if ( aFactor < 0.0f ) aFactor = 0.0f;
  if ( aFactor > 1.0f ) aFactor = 1.0f;

  f2 = (unsigned int)( 65536.0f * aFactor );
  f1 = 65536 - f2;

  r  = (( f1 * (( aValue1 >>  0 ) & 0xFFFF )) +
        ( f2 * (( aValue2 >>  0 ) & 0xFFFF ))) >> 16;
  r += (( f1 * (( aValue1 >> 16 ) & 0xFFFF )) +
        ( f2 * (( aValue2 >> 16 ) & 0xFFFF ))) >>  0;
  r += (( f1 * (( aValue1 >> 32 ) & 0xFFFF )) +
        ( f2 * (( aValue2 >> 32 ) & 0xFFFF ))) << 16;
  r += (( f1 * (( aValue1 >> 48 ) & 0xFFFF )) +
        ( f2 * (( aValue2 >> 48 ) & 0xFFFF ))) << 32;

  return r;
}


/*******************************************************************************
* FUNCTION:
*   EwMathMixFloat
*
* DESCRIPTION:
*   The function EwMathMixFloat() implements the Chora math_mix() function
*   intended to interpolate a float value within a given range.
*
* ARGUMENTS:
*   aValue1 - The start value of the range.
*   aValue2 - The end value of the range.
*   aFactor - Factor controlling the interpolation.
*
* RETURN VALUE:
*   Returns a value lying between aValue1 and aValue2 according to the parameter
*   aFactor. If aFactor <= 0.0, the function returns aValue1. If aFactor >= 1.0,
*   the function returns aValue2.
*
*******************************************************************************/
XFloat EwMathMixFloat( XFloat aValue1, XFloat aValue2, XFloat aFactor )
{
  if ( aFactor < 0.0f ) aFactor = 0.0f;
  if ( aFactor > 1.0f ) aFactor = 1.0f;

  return (( 1.0f - aFactor ) * aValue1 ) + ( aFactor * aValue2 );
}


/*******************************************************************************
* FUNCTION:
*   EwMathMixPoint
*
* DESCRIPTION:
*   The function EwMathMixPoint() implements the Chora math_mix() function
*   intended to interpolate an point value within a given range.
*
* ARGUMENTS:
*   aValue1 - The start value of the range.
*   aValue2 - The end value of the range.
*   aFactor - Factor controlling the interpolation.
*
* RETURN VALUE:
*   Returns a value lying between aValue1 and aValue2 according to the parameter
*   aFactor. If aFactor <= 0.0, the function returns aValue1. If aFactor >= 1.0,
*   the function returns aValue2.
*
*******************************************************************************/
XPoint EwMathMixPoint( XPoint aValue1, XPoint aValue2, XFloat aFactor )
{
  unsigned int fi;
  XInt32       x, y;
  signed int   sx, sy;

  if ( aFactor < 0.0f ) aFactor = 0.0f;
  if ( aFactor > 1.0f ) aFactor = 1.0f;

  fi = (unsigned int)( 65536.0f * aFactor );
  x  = aValue2.X - aValue1.X;
  y  = aValue2.Y - aValue1.Y;
  sx = ( x < 0 )? -1 : 1;
  sy = ( y < 0 )? -1 : 1;
  x *= sx;
  y *= sy;
  x  = (( fi * (( x >>  0 ) & 0xFFFF )) >> 16 ) +
       (( fi * (( x >> 16 ) & 0xFFFF )) >>  0 );
  y  = (( fi * (( y >>  0 ) & 0xFFFF )) >> 16 ) +
       (( fi * (( y >> 16 ) & 0xFFFF )) >>  0 );
  x *= sx;
  y *= sy;

  aValue1.X += x;
  aValue1.Y += y;

  return aValue1;
}


/*******************************************************************************
* FUNCTION:
*   EwMathMixRect
*
* DESCRIPTION:
*   The function EwMathMixRect() implements the Chora math_mix() function
*   intended to interpolate a rect value within a given range.
*
* ARGUMENTS:
*   aValue1 - The start value of the range.
*   aValue2 - The end value of the range.
*   aFactor - Factor controlling the interpolation.
*
* RETURN VALUE:
*   Returns a value lying between aValue1 and aValue2 according to the parameter
*   aFactor. If aFactor <= 0.0, the function returns aValue1. If aFactor >= 1.0,
*   the function returns aValue2.
*
*******************************************************************************/
XRect EwMathMixRect( XRect aValue1, XRect aValue2, XFloat aFactor )
{
  unsigned int fi;
  XInt32       x1, y1, x2, y2;
  signed int   sx1, sy1, sx2, sy2;

  if ( aFactor < 0.0f ) aFactor = 0.0f;
  if ( aFactor > 1.0f ) aFactor = 1.0f;

  fi = (unsigned int)( 65536.0f * aFactor );
  x1  = aValue2.Point1.X - aValue1.Point1.X;
  y1  = aValue2.Point1.Y - aValue1.Point1.Y;
  x2  = aValue2.Point2.X - aValue1.Point2.X;
  y2  = aValue2.Point2.Y - aValue1.Point2.Y;
  sx1 = ( x1 < 0 )? -1 : 1;
  sy1 = ( y1 < 0 )? -1 : 1;
  sx2 = ( x2 < 0 )? -1 : 1;
  sy2 = ( y2 < 0 )? -1 : 1;
  x1 *= sx1;
  y1 *= sy1;
  x2 *= sx2;
  y2 *= sy2;
  x1  = (( fi * (( x1 >>  0 ) & 0xFFFF )) >> 16 ) +
        (( fi * (( x1 >> 16 ) & 0xFFFF )) >>  0 );
  y1  = (( fi * (( y1 >>  0 ) & 0xFFFF )) >> 16 ) +
        (( fi * (( y1 >> 16 ) & 0xFFFF )) >>  0 );
  x2  = (( fi * (( x2 >>  0 ) & 0xFFFF )) >> 16 ) +
        (( fi * (( x2 >> 16 ) & 0xFFFF )) >>  0 );
  y2  = (( fi * (( y2 >>  0 ) & 0xFFFF )) >> 16 ) +
        (( fi * (( y2 >> 16 ) & 0xFFFF )) >>  0 );
  x1 *= sx1;
  y1 *= sy1;
  x2 *= sx2;
  y2 *= sy2;

  aValue1.Point1.X += x1;
  aValue1.Point1.Y += y1;
  aValue1.Point2.X += x2;
  aValue1.Point2.Y += y2;

  return aValue1;
}


/*******************************************************************************
* FUNCTION:
*   EwMathMixColor
*
* DESCRIPTION:
*   The function EwMathMixColor() implements the Chora math_mix() function
*   intended to interpolate a color value within a given range.
*
* ARGUMENTS:
*   aValue1 - The start value of the range.
*   aValue2 - The end value of the range.
*   aFactor - Factor controlling the interpolation.
*
* RETURN VALUE:
*   Returns a value lying between aValue1 and aValue2 according to the parameter
*   aFactor. If aFactor <= 0.0, the function returns aValue1. If aFactor >= 1.0,
*   the function returns aValue2.
*
*******************************************************************************/
XColor EwMathMixColor( XColor aValue1, XColor aValue2, XFloat aFactor )
{
  unsigned int f1, f2;
  XColor       r;

  if ( aFactor < 0.0f ) aFactor = 0.0f;
  if ( aFactor > 1.0f ) aFactor = 1.0f;

  f2 = (unsigned int)( 256.0f * aFactor );
  f1 = 256 - f2;

  r.Red   = (( f1 * aValue1.Red   ) + ( f2 * aValue2.Red   )) >> 8;
  r.Green = (( f1 * aValue1.Green ) + ( f2 * aValue2.Green )) >> 8;
  r.Blue  = (( f1 * aValue1.Blue  ) + ( f2 * aValue2.Blue  )) >> 8;
  r.Alpha = (( f1 * aValue1.Alpha ) + ( f2 * aValue2.Alpha )) >> 8;

  return r;
}


/*******************************************************************************
* FUNCTION:
*   EwMathLength
*
* DESCRIPTION:
*   The function EwMathLength() implements the Chora math_length() built-in
*   function intended to calculate the length of a given vector.
*
* ARGUMENTS:
*   aX, aY : The size of the vector in X and Y direction.
*
* RETURN VALUE:
*   Returns the length of the vector.
*
*******************************************************************************/
XFloat EwMathLength( XFloat aX, XFloat aY )
{
  return EwMathSqrt(( aX * aX ) + ( aY * aY ));
}


/*******************************************************************************
* FUNCTION:
*   EwMathLengthPoint
*
* DESCRIPTION:
*   The function EwMathLengthPoint() implements the Chora math_length() built-
*   in function intended to calculate the length of a given vector.
*
* ARGUMENTS:
*   aPoint : The size of the vector in X and Y direction.
*
* RETURN VALUE:
*   Returns the length of the vector.
*
*******************************************************************************/
XFloat EwMathLengthPoint( XPoint aPoint )
{
  XFloat x = (XFloat)aPoint.X;
  XFloat y = (XFloat)aPoint.Y;

  return EwMathSqrt(( x * x ) + ( y * y ));
}


/*******************************************************************************
* FUNCTION:
*   EwMathTrunc
*
* DESCRIPTION:
*   The function EwMathTrunc() implements the Chora math_trunc() built-in
*   function intended to calculate the integer part of a given number by
*   removing the fractional digits.
*
* ARGUMENTS:
*   aValue : The value to calculate the integer part.
*
* RETURN VALUE:
*   Returns the integer part of the number.
*
*******************************************************************************/
XFloat EwMathTrunc( XFloat aValue )
{
  if ( aValue < 0.0f ) return EwMathCeil ( aValue );
  else                 return EwMathFloor( aValue );
}


/*******************************************************************************
* FUNCTION:
*   EwMathFract
*
* DESCRIPTION:
*   The function EwMathFract() implements the Chora math_fract() built-in
*   function intended to calculate the fractional part of the given number.
*
* ARGUMENTS:
*   aValue : The value to calculate the fractional part.
*
* RETURN VALUE:
*   Returns the fractional part of the number.
*
*******************************************************************************/
XFloat EwMathFract( XFloat aValue )
{
  if ( aValue < 0.0f ) return aValue - EwMathCeil ( aValue );
  else                 return aValue - EwMathFloor( aValue );
}


/* pba, msy */
