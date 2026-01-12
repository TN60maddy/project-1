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

#ifndef _ToolsHelperCollection_H
#define _ToolsHelperCollection_H

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

/* Forward declaration of the class Core::QuadView */
#ifndef _CoreQuadView_
  EW_DECLARE_CLASS( CoreQuadView )
#define _CoreQuadView_
#endif

/* Forward declaration of the class Resources::Font */
#ifndef _ResourcesFont_
  EW_DECLARE_CLASS( ResourcesFont )
#define _ResourcesFont_
#endif

/* Forward declaration of the class Tools::HelperCollection */
#ifndef _ToolsHelperCollection_
  EW_DECLARE_CLASS( ToolsHelperCollection )
#define _ToolsHelperCollection_
#endif


/* This is a class. */
EW_DEFINE_FIELDS( ToolsHelperCollection, XObject )
EW_END_OF_FIELDS( ToolsHelperCollection )

/* Virtual Method Table (VMT) for the class : 'Tools::HelperCollection' */
EW_DEFINE_METHODS( ToolsHelperCollection, XObject )
EW_END_OF_METHODS( ToolsHelperCollection )

/* 'C' function for method : 'Tools::HelperCollection.StringReplace()' */
XString ToolsHelperCollection_StringReplace( ToolsHelperCollection _this, XString 
  aString, XString aOld, XString aNew );

/* 'C' function for method : 'Tools::HelperCollection.StringParamReplace()' */
XString ToolsHelperCollection_StringParamReplace( ToolsHelperCollection _this, XString 
  aString, XInt32 aParamNr, XString aParam );

/* 'C' function for method : 'Tools::HelperCollection.FormatInt32Value()' */
XString ToolsHelperCollection_FormatInt32Value( ToolsHelperCollection _this, XInt32 
  aValue, XInt32 aResolution, XInt32 aPrecision );

/* 'C' function for method : 'Tools::HelperCollection.ParseInt32Value()' */
XInt32 ToolsHelperCollection_ParseInt32Value( ToolsHelperCollection _this, XString 
  aFormatValue, XInt32 aResolution );

/* 'C' function for method : 'Tools::HelperCollection.FormatTime()' */
XString ToolsHelperCollection_FormatTime( ToolsHelperCollection _this, XInt32 aTime );

/* 'C' function for method : 'Tools::HelperCollection.GetTimeUnitString()' */
XString ToolsHelperCollection_GetTimeUnitString( ToolsHelperCollection _this, ResourcesFont 
  aTimeFont, ResourcesFont aUnitFont );

/* 'C' function for method : 'Tools::HelperCollection.getCenteredUnit()' */
XString ToolsHelperCollection_getCenteredUnit( ToolsHelperCollection _this, XString 
  aUnit, ResourcesFont aUnitFont, XInt32 aTimeItemWidth, XInt32 aSpaceWidth );

/* 'C' function for method : 'Tools::HelperCollection.SetQuadViewBounds()' */
void ToolsHelperCollection_SetQuadViewBounds( ToolsHelperCollection _this, CoreQuadView 
  aView, XRect aBounds );

#ifdef __cplusplus
  }
#endif

#endif /* _ToolsHelperCollection_H */

/* Embedded Wizard */
