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
*   This is the main module of the Embedded Wizard Graphics Engine EWGFX. It
*   implements the top level API of the engine:
*
*   > Bitmap and font management. Creation and destroying of bitmaps, loading
*     of bitmap and font resources. The loading of resources will take place
*     through the external bitmap and font resource provider interfaces. (See
*     ewgfxres.h).
*
*   > Drawing operations. Functions to perform all kinds of drawing operations
*     like drawing lines, text, bitmaps, etc. For each operation a new task is
*     created and stored within an issue. Issues in turn belong to surfaces and
*     they remain pending as long as they have not been flushed. This kind of
*     lazy processing allows the optimization of drawing tasks. (More details
*     about tasks in ewgfxtasks.h)
*
*   > Text size calculation.
*
*   > Creation and management of path data.
*
*   > Viewport support as framebuffer abstraction.
*
* SUBROUTINES:
*   EwInitGraphicsEngine
*   EwDoneGraphicsEngine
*   EwGetGraphicsEngineInfo
*   EwEnableGfxTaskTracing
*   EwCreateBitmap
*   EwCreateBitmapWrapped
*   EwLoadBitmap
*   EwFreeBitmap
*   EwLockBitmap
*   EwUnlockBitmap
*   EwModifyBitmapPalette
*   EwFlushBitmap
*   EwGetFontResource
*   EwLoadFont
*   EwFreeFont
*   EwInitViewport
*   EwDoneViewport
*   EwConfigViewport
*   EwBeginUpdate
*   EwBeginUpdateArea
*   EwEndUpdate
*   EwFillRectangle
*   EwFillRoundedRectangle
*   EwDrawBorder
*   EwDrawRoundedBorder
*   EwDrawRoundedShadow
*   EwCreateGradient
*   EwFreeGradient
*   EwSetGradientTypeLinear
*   EwSetGradientTypeRadial
*   EwAddGradientColorStop
*   EwSetGradientColorStop
*   EwGetGradientMaxNoOfColorStops
*   EwGetGradientNoOfColorStops
*   EwCreatePath
*   EwFreePath
*   EwGetMaxNoOfSubPaths
*   EwInitSubPath
*   EwBeginSubPath
*   EwAddSubPathLine
*   EwAddSubPathBezier2
*   EwAddSubPathBezier3
*   EwAddSubPathArc
*   EwAddSubPathCopy
*   EwCloseSubPath
*   EwShiftSubPathNodes
*   EwSetSubPathNode
*   EwGetSubPathNodeX
*   EwGetSubPathNodeY
*   EwSetNoOfSubPathEdges
*   EwGetNoOfSubPathEdges
*   EwGetNoOfFreeSubPathEdges
*   EwIsSubPathClosed
*   EwGetSubPathBounds
*   EwGetPathBounds
*   EwTranslatePathMatrix
*   EwScalePathMatrix
*   EwRotatePathMatrix
*   EwPushPathMatrix
*   EwPopPathMatrix
*   EwInitPathMatrix
*   EwSetPathMatrix
*   EwFillPath
*   EwFillPathWithGradient
*   EwStrokePath
*   EwStrokePathWithGradient
*   EwGetBitmapFromFillPath
*   EwGetBitmapFromStrokePath
*   EwGetBlurredBitmapFromFillPath
*   EwGetBlurredBitmapFromStrokePath
*   EwCopyBitmap
*   EwTileBitmap
*   EwWarpBitmap
*   EwAdjustFilterBlurRadius
*   EwFilterBitmap
*   EwDrawLine
*   EwDrawText
*   EwGetTextExtent
*   EwGetTextAdvance
*   EwGetTextColumnAtPosition
*   EwGetPositionAtTextColumn
*   EwIsGlyphAvailable
*   EwGetGlyphId
*   EwGetGlyphMetrics
*   EwGetKerning
*   EwLockGlyph
*   EwUnlockGlyph
*   EwDrawBitmapFrame
*   EwIndexToColor
*   EwColorToIndex
*   EwAllocUserColor
*   EwFreeUserColor
*   EwSetUserColor
*   EwFindUserColor
*   EwGetOverlayArea
*
*******************************************************************************/

#include "ewrte.h"
#include "ewgfxdriver.h"
#include "ewgfxcore.h"
#include "ewgfxtasks.h"
#include "ewgfxres.h"
#include "ewgfx.h"


/* Helper macros for fast color conversion and evaluation */
#define IS_TRANSPARENT2( aColor1, aColor2 )                                    \
  ((( aColor1 | aColor2 ) >> 24 ) == 0 )

#define IS_OPAQUE2( aColor1, aColor2 )                                         \
  ((( aColor1 & aColor2 ) >> 24 ) == 255 )

#define IS_GRADIENT2( aColor1, aColor2 )                                       \
  ( aColor1 != aColor2 )

#define IS_TRANSPARENT4( aColor1, aColor2, aColor3, aColor4 )                  \
  ((( aColor1 | aColor2 | aColor3 | aColor4 ) >> 24 ) == 0 )

#define IS_OPAQUE4( aColor1, aColor2, aColor3, aColor4 )                       \
  ((( aColor1 & aColor2 & aColor3 & aColor4 ) >> 24 ) == 255 )

#define IS_GRADIENT4( aColor1, aColor2, aColor3, aColor4 )                     \
  (( aColor1 != aColor2 ) || ( aColor3 != aColor4 ) || ( aColor2 != aColor4 ))

#define IS_LINEAR_GRADIENT4( aColorTL, aColorTR, aColorBL, aColorBR )          \
  ((( aColorTL != aColorTR ) && ( aColorBL != aColorBR ) &&                    \
    ( aColorTL == aColorBL ) && ( aColorTR == aColorBR )) ||                   \
   (( aColorTL != aColorBL ) && ( aColorTR != aColorBR ) &&                    \
    ( aColorTL == aColorTR ) && ( aColorBL == aColorBR )))

#define PACK_COLOR( aColor, aDst )                                             \
  EwPackColor( aColor.Red, aColor.Green, aColor.Blue, aColor.Alpha,            \
               aDst? aDst->Format : EW_PIXEL_FORMAT_NATIVE )


/* Helper macros for minimum and maximum calculation */
#ifdef MIN
  #undef MIN
#endif
#define MIN( a, b ) (((a) < (b))? (a) : (b))

#ifdef MAX
  #undef MAX
#endif
#define MAX( a, b ) (((a) > (b))? (a) : (b))

#ifdef ABS
  #undef ABS
#endif
#define ABS( a ) (((a) < 0 )? -(a) : a )


/* Global tables containing index to color and color to index conversion.
   These globals are generated by Embedded Wizard and linked together with
   the project. Here the globals are 'linked' at the runtime. */
#ifdef EW_ENABLE_COLOR_TABLE
  extern unsigned int        EwGlobalClut[ 256 ];
  extern const int           EwGlobalClutCount;
  extern const unsigned char EwColorIndexTable[ 0x4000 ];
#endif


/* User defined color allocation table */
#ifdef EW_ENABLE_COLOR_TABLE
  char EwColorAllocTable[ 256 ];
#endif


/* Memory usage profiler */
extern int EwResourcesMemory;
extern int EwResourcesMemoryPeak;
extern int EwObjectsMemory;
extern int EwStringsMemory;
extern int EwMemoryPeak;


/* Surface cache optimization profiler */
int EwNoOfDiscardedSurfaces   = 0;
int EwDiscardedSurfacesMemory = 0;


/* Debugging mode */
#ifdef EW_PRINT_GFX_TASKS
  int EwPrintGfxTasks = 1;
#else
  int EwPrintGfxTasks = 0;
#endif


/* Attributes controlling the size of the glyph and surface cache */
extern int EwMaxGlyphSurfaceWidth;
extern int EwMaxGlyphSurfaceHeight;
extern int EwMaxSurfaceCacheSize;


/* This variable is used to track the usage of compressed bitmaps during
   prototyping only. The respective decompression algorithm requires
   additional memory which should be taken in account when estimating
   memory usage during prototyping. */
#ifdef EW_PROTOTYPING
  extern int EwUseDecompression;
#endif


/* From the optional graphics subsystem settings extract the mode how the
   Mosaic framework should drive the screen composition */
int EwFullScreenUpdate           = EW_PERFORM_FULLSCREEN_UPDATE;
int EwFullOffScreenBufferUpdate  = EW_PERFORM_FULLOFFSCREENBUFFER_UPDATE;
int EwPreserveFramebufferContent = EW_PRESERVE_FRAMEBUFFER_CONTENT;


/* Should map the surfaces immediately and retain them in memory? */
int EwLazyLoadBitmaps                        = EW_LAZY_LOAD_BITMAPS;
int EwLazyLoadBitmapsIfAnimatedOnly          = EW_LAZY_LOAD_BITMAPS_IF_ANIMATED_ONLY;
int EwDiscardBitmaps                         = EW_DISCARD_BITMAPS;
int EwDiscardBitmapsIfAnimatedOnly           = EW_DISCARD_BITMAPS_IF_ANIMATED_ONLY;
int EwDiscardBitmapsIfNotUsedInCurrentUpdate = EW_DISCARD_BITMAPS_IF_NOT_USED_IN_CURRENT_UPDATE;
int EwDiscardBitmapsIfNotUsedInRecentUpdates = EW_DISCARD_BITMAPS_IF_NOT_USED_IN_RECENT_UPDATES;


/* This counter is incremented with every screen update. It identifies the
   screen updates. */
int EwUpdateCycle = 0;


#ifdef EW_EVALUATION_VERSION
  #include "ewgfxeval.inc"
#else
  #define EW_EVAL_INC_1()
  #define EW_EVAL_INC_2()
  #define EW_EVAL_INC_3( aDummy )
  #define EW_EVAL_INC_4()
  #define EW_EVAL_INC_5()
  #define EW_EVAL_INC_6()
#endif


/* Helper function for minimum and maximum calculation */
static int    MIN3 ( int a, int b, int c );
static int    MAX3 ( int a, int b, int c );

#ifndef EW_DONT_USE_WARP_FUNCTIONS
  static XFloat MINF4( XFloat a, XFloat b, XFloat c, XFloat d );
  static XFloat MAXF4( XFloat a, XFloat b, XFloat c, XFloat d );
#endif


/* This helper function creates and initializes a new descriptor structure for
   a new bitmap with the given number of frames, the frame size, etc. */
static XBitmap* InitBitmap( XInt32 aFormat, XPoint aFrameSize, int aFrameDelay,
  int aNoOfFrames, int aNoOfVirtFrames, int aMaxNoOfFramesX, int aMaxNoOfFramesY,
  int aBorder, int aExtraBorder, int aFramesSurfaceBalance );


/* This helper function verifies whether the given bitmap frame is already mapped
   to a surface. If this is not the case, new surface is created and the frame is
   initialized with a reference to this surface. If the bitmap contains resource
   data, the just created surface is loaded with the respective frames. The
   function returns the given bitmap frame or 0 (zero) if the frame or bitmap
   are wrong. */
static XBitmapFrame* MapBitmapFrame( XBitmap* aBitmap, int aFrameNo );


/* The following function helps to fill the surface with a transparent color
   grid as it is necessary to separate frames within multi-frame bitmaps. */
static void DrawFrameGrid( XSurface* aSurface, int aWidth, int aHeight );


/* This helper function seeks in the cache for a glyph. If necessary, a new
   glyph will be loaded into the cache. For all new loaded glyphs there is
   no pixel information stored primarily.  */
static XGlyph* GetGlyph( XFont* aFont, unsigned int aGlyphId );


/* This helper function verifies whether the given glyph is already loaded
   into the glyph surface cache (it is mapped). If necessary, the function
   takes care of loading the glyph pixel data. If successful the function
   return != 0. */
static int MapGlyph( XFont* aFont, unsigned int aGlyphId, XGlyph* aGlyph );


/* This helper function calculates the color value in the range aColor 1 ..
   aColor2 depending on the Factor, which lies in the range 0 .. aRange. */
static XColor InterpolateColor( XColor aColor1, XColor aColor2, int aFactor,
  int aRange );


/* WcsLen() returns the number of wide-characters in the string aString
   without the zero-terminator sign */
static int WcsLen( const XChar* aString );


#ifndef EW_DONT_USE_PATH_FUNCTIONS
  /* This helper function verifies whether the path information is still valid and
     if this is not the case, updates the path. */
  static void UpdatePath( XPath* aPath );


  /* This helper function is used to copy path information so that it can be
     rasterized. The function copies the path data into the buffer aBufPath
     and returns the address within the buffer where the copied information
     ends */
  static int* PrepareForFillPath( XSubPath* aSubPath, int* aBufPath,
    int aDstX, int DstY, int aFlipY );


  /* This helper function is used to prepare and copy path information so that it
     can be rasterized. The function copies the path data into the buffer
     aBufPath and returns the address within the buffer where the copied
     information ends */
  static int* PrepareForStrokePath( XSubPath* aSubPath, int aStyleStart,
    int aStyleEnd, int aStyleJoin, float aMiterLimit, float aWidth2,
    int* aBufPath, float* aBufHelp, int aDstX, int aDstY, int aFlipY,
    int aRoundSteps, float aRoundCos, float aRoundSin, float* aMatrix );
#endif /* EW_DONT_USE_PATH_FUNCTIONS */


#if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
  /* This helper function sorts the aCount color stops according their
     offset values. */
  static void SortColorStops( XGradientStop* aStops, int aCount );
#endif /* EW_DONT_USE_GRADIENTS && EW_DONT_USE_PATH_FUNCTIONS */


#ifndef EW_DONT_USE_PATH_FUNCTIONS
  /* The following data structure describes an ALPHA8 bitmap containing the base
     shape of a rounded and eventually blurred rectangle. Such bitmaps are created
     by functions like EwFillRoundedRectangle() or EwDrawRoundedShadow(). Since
     creation of the bitmaps is CPU intensive, the Graphics Engine retains the
     once created bitmaps for reuse. The data structure describes it then so the
     bitmap can be found again. */
  typedef struct _XCachedRoundedRectangleBitmap
  {
    struct _XCachedRoundedRectangleBitmap* Next;
    struct _XCachedRoundedRectangleBitmap* Prev;
    int                                    Width;
    int                                    Height;
    int                                    BorderWidth;
    int                                    RadiusTL;
    int                                    RadiusTR;
    int                                    RadiusBR;
    int                                    RadiusBL;
    int                                    BlurRadius;
    XSurface*                              Surface;
  }
  XCachedRoundedRectangleBitmap;


  /* The start and the end of the list containing cached rounded rectangle
     bitmaps. */
  XCachedRoundedRectangleBitmap* EwRoundedRectangleBitmapCacheHead;
  XCachedRoundedRectangleBitmap* EwRoundedRectangleBitmapCacheTail;


  /* Following internal function stores the given bitmap in the 'Rounded Rectangle
     Bitmap Cache'. Thereupon the bitmap can be reused. */
  static void CacheRoundedRectangleBitmap( XBitmap* aBitmap, int aWidth, 
    int aHeight, int aBorderWidth,  int aRadiusTL, int aRadiusTR, int aRadiusBR,
    int aRadiusBL, int aBlurRadius );

  /* Following function searches in the 'Rounded Rectangle Bitmap Cache' for a
     bitmap created originally according to the specified parameters. If found,
     the bitmap is removed from the cache and returned. If not found, the function
     returns NULL. */
  static XBitmap* FindCachedRoundedRectangleBitmap( int aWidth, int aHeight,
    int aBorderWidth,  int aRadiusTL, int aRadiusTR, int aRadiusBR, int aRadiusBL,
    int aBlurRadius );
#endif /* EW_DONT_USE_PATH_FUNCTIONS */


/* Internal initialization function for the attributed text and Bidi sub-
   systems, etc. */
int EwInitAttrText( void* aArgs );
int EwInitBidi( void* aArgs );
int EwInitSVG( void* aArgs );


/* Internal initialization function for the graphics tasks module */
int EwGfxTasksInit( void* aArgs );


/* Performance counter for performance investigation and debugging only */
EW_PERF_COUNTER( EwCreateBitmap,                   Graphics_Engine_API )
EW_PERF_COUNTER( EwCreateBitmapWrapped,            Graphics_Engine_API )
EW_PERF_COUNTER( EwLoadBitmap,                     Graphics_Engine_API )
EW_PERF_COUNTER( EwFreeBitmap,                     Graphics_Engine_API )
EW_PERF_COUNTER( EwLockBitmap,                     Graphics_Engine_API )
EW_PERF_COUNTER( EwUnlockBitmap,                   Graphics_Engine_API )
EW_PERF_COUNTER( EwModifyBitmapPalette,            Graphics_Engine_API )
EW_PERF_COUNTER( EwFlushBitmap,                    Graphics_Engine_API )
EW_PERF_COUNTER( EwGetFontResource,                Graphics_Engine_API )
EW_PERF_COUNTER( EwLoadFont,                       Graphics_Engine_API )
EW_PERF_COUNTER( EwFreeFont,                       Graphics_Engine_API )
EW_PERF_COUNTER( EwInitViewport,                   Graphics_Engine_API )
EW_PERF_COUNTER( EwDoneViewport,                   Graphics_Engine_API )
EW_PERF_COUNTER( EwConfigViewport,                 Graphics_Engine_API )
EW_PERF_COUNTER( EwBeginUpdate,                    Graphics_Engine_API )
EW_PERF_COUNTER( EwBeginUpdateArea,                Graphics_Engine_API )
EW_PERF_COUNTER( EwEndUpdate,                      Graphics_Engine_API )
EW_PERF_COUNTER( EwFillRectangle,                  Graphics_Engine_API )
EW_PERF_COUNTER( EwFillRoundedRectangle,           Graphics_Engine_API )
EW_PERF_COUNTER( EwDrawBorder,                     Graphics_Engine_API )
EW_PERF_COUNTER( EwDrawRoundedBorder,              Graphics_Engine_API )
EW_PERF_COUNTER( EwDrawRoundedShadow,              Graphics_Engine_API )
EW_PERF_COUNTER( EwCreateGradient,                 Graphics_Engine_API )
EW_PERF_COUNTER( EwFreeGradient,                   Graphics_Engine_API )
EW_PERF_COUNTER( EwSetGradientTypeLinear,          Graphics_Engine_API )
EW_PERF_COUNTER( EwSetGradientTypeRadial,          Graphics_Engine_API )
EW_PERF_COUNTER( EwAddGradientColorStop,           Graphics_Engine_API )
EW_PERF_COUNTER( EwSetGradientColorStop,           Graphics_Engine_API )
EW_PERF_COUNTER( EwGetGradientMaxNoOfColorStops,   Graphics_Engine_API )
EW_PERF_COUNTER( EwGetGradientNoOfColorStops,      Graphics_Engine_API )
EW_PERF_COUNTER( EwCreatePath,                     Graphics_Engine_API )
EW_PERF_COUNTER( EwFreePath,                       Graphics_Engine_API )
EW_PERF_COUNTER( EwGetMaxNoOfSubPaths,             Graphics_Engine_API )
EW_PERF_COUNTER( EwInitSubPath,                    Graphics_Engine_API )
EW_PERF_COUNTER( EwBeginSubPath,                   Graphics_Engine_API )
EW_PERF_COUNTER( EwAddSubPathLine,                 Graphics_Engine_API )
EW_PERF_COUNTER( EwAddSubPathBezier2,              Graphics_Engine_API )
EW_PERF_COUNTER( EwAddSubPathBezier3,              Graphics_Engine_API )
EW_PERF_COUNTER( EwAddSubPathArc,                  Graphics_Engine_API )
EW_PERF_COUNTER( EwAddSubPathCopy,                 Graphics_Engine_API )
EW_PERF_COUNTER( EwCloseSubPath,                   Graphics_Engine_API )
EW_PERF_COUNTER( EwShiftSubPathNodes,              Graphics_Engine_API )
EW_PERF_COUNTER( EwSetSubPathNode,                 Graphics_Engine_API )
EW_PERF_COUNTER( EwGetSubPathNodeX,                Graphics_Engine_API )
EW_PERF_COUNTER( EwGetSubPathNodeY,                Graphics_Engine_API )
EW_PERF_COUNTER( EwSetNoOfSubPathEdges,            Graphics_Engine_API )
EW_PERF_COUNTER( EwGetNoOfSubPathEdges,            Graphics_Engine_API )
EW_PERF_COUNTER( EwGetNoOfFreeSubPathEdges,        Graphics_Engine_API )
EW_PERF_COUNTER( EwIsSubPathClosed,                Graphics_Engine_API )
EW_PERF_COUNTER( EwGetSubPathBounds,               Graphics_Engine_API )
EW_PERF_COUNTER( EwGetPathBounds,                  Graphics_Engine_API )
EW_PERF_COUNTER( EwTranslatePathMatrix,            Graphics_Engine_API )
EW_PERF_COUNTER( EwScalePathMatrix,                Graphics_Engine_API )
EW_PERF_COUNTER( EwRotatePathMatrix,               Graphics_Engine_API )
EW_PERF_COUNTER( EwPushPathMatrix,                 Graphics_Engine_API )
EW_PERF_COUNTER( EwPopPathMatrix,                  Graphics_Engine_API )
EW_PERF_COUNTER( EwInitPathMatrix,                 Graphics_Engine_API )
EW_PERF_COUNTER( EwSetPathMatrix,                  Graphics_Engine_API )
EW_PERF_COUNTER( EwFillPath,                       Graphics_Engine_API )
EW_PERF_COUNTER( EwFillPathWithGradient,           Graphics_Engine_API )
EW_PERF_COUNTER( EwStrokePath,                     Graphics_Engine_API )
EW_PERF_COUNTER( EwStrokePathWithGradient,         Graphics_Engine_API )
EW_PERF_COUNTER( EwGetBitmapFromFillPath,          Graphics_Engine_API )
EW_PERF_COUNTER( EwGetBitmapFromStrokePath,        Graphics_Engine_API )
EW_PERF_COUNTER( EwGetBlurredBitmapFromFillPath,   Graphics_Engine_API )
EW_PERF_COUNTER( EwGetBlurredBitmapFromStrokePath, Graphics_Engine_API )
EW_PERF_COUNTER( EwCopyBitmap,                     Graphics_Engine_API )
EW_PERF_COUNTER( EwTileBitmap,                     Graphics_Engine_API )
EW_PERF_COUNTER( EwWarpBitmap,                     Graphics_Engine_API )
EW_PERF_COUNTER( EwAdjustFilterBlurRadius,         Graphics_Engine_API )
EW_PERF_COUNTER( EwFilterBitmap,                   Graphics_Engine_API )
EW_PERF_COUNTER( EwDrawLine,                       Graphics_Engine_API )
EW_PERF_COUNTER( EwDrawText,                       Graphics_Engine_API )
EW_PERF_COUNTER( EwGetTextExtent,                  Graphics_Engine_API )
EW_PERF_COUNTER( EwGetTextAdvance,                 Graphics_Engine_API )
EW_PERF_COUNTER( EwGetTextColumnAtPosition,        Graphics_Engine_API )
EW_PERF_COUNTER( EwGetPositionAtTextColumn,        Graphics_Engine_API )
EW_PERF_COUNTER( EwIsGlyphAvailable,               Graphics_Engine_API )
EW_PERF_COUNTER( EwGetGlyphId,                     Graphics_Engine_API )
EW_PERF_COUNTER( EwGetGlyphMetrics,                Graphics_Engine_API )
EW_PERF_COUNTER( EwGetKerning,                     Graphics_Engine_API )
EW_PERF_COUNTER( EwLockGlyph,                      Graphics_Engine_API )
EW_PERF_COUNTER( EwUnlockGlyph,                    Graphics_Engine_API )
EW_PERF_COUNTER( EwDrawBitmapFrame,                Graphics_Engine_API )
EW_PERF_COUNTER( EwIndexToColor,                   Graphics_Engine_API )
EW_PERF_COUNTER( EwColorToIndex,                   Graphics_Engine_API )
EW_PERF_COUNTER( EwAllocUserColor,                 Graphics_Engine_API )
EW_PERF_COUNTER( EwFreeUserColor,                  Graphics_Engine_API )
EW_PERF_COUNTER( EwSetUserColor,                   Graphics_Engine_API )
EW_PERF_COUNTER( EwFindUserColor,                  Graphics_Engine_API )
EW_PERF_COUNTER( MapBitmapFrame,                   Graphics_Engine_API )
EW_PERF_COUNTER( EwGfxInitViewport,                Platform_Integration_API )
EW_PERF_COUNTER( EwGfxDoneViewport,                Platform_Integration_API )
EW_PERF_COUNTER( EwGfxConfigViewport,              Platform_Integration_API )
EW_PERF_COUNTER( EwGfxBeginUpdate,                 Platform_Integration_API )
EW_PERF_COUNTER( EwGfxBeginUpdateArea,             Platform_Integration_API )
EW_PERF_COUNTER( EwGfxEndUpdate,                   Platform_Integration_API )
EW_PERF_COUNTER( ViewportCallback,                 Platform_Integration_API )


/* Map the Graphics Engine API to the corresponding functions if no performance
   counters are active  */
#ifndef EW_PRINT_PERF_COUNTERS
  #define EwCreateBitmap_                   EwCreateBitmap
  #define EwCreateBitmapWrapped_            EwCreateBitmapWrapped
  #define EwLoadBitmap_                     EwLoadBitmap
  #define EwFreeBitmap_                     EwFreeBitmap
  #define EwLockBitmap_                     EwLockBitmap
  #define EwUnlockBitmap_                   EwUnlockBitmap
  #define EwModifyBitmapPalette_            EwModifyBitmapPalette
  #define EwFlushBitmap_                    EwFlushBitmap
  #define EwGetFontResource_                EwGetFontResource
  #define EwLoadFont_                       EwLoadFont
  #define EwFreeFont_                       EwFreeFont
  #define EwInitViewport_                   EwInitViewport
  #define EwDoneViewport_                   EwDoneViewport
  #define EwConfigViewport_                 EwConfigViewport
  #define EwBeginUpdate_                    EwBeginUpdate
  #define EwBeginUpdateArea_                EwBeginUpdateArea
  #define EwEndUpdate_                      EwEndUpdate
  #define EwFillRectangle_                  EwFillRectangle
  #define EwFillRoundedRectangle_           EwFillRoundedRectangle
  #define EwDrawBorder_                     EwDrawBorder
  #define EwDrawRoundedBorder_              EwDrawRoundedBorder
  #define EwDrawRoundedShadow_              EwDrawRoundedShadow
  #define EwCreateGradient_                 EwCreateGradient
  #define EwFreeGradient_                   EwFreeGradient
  #define EwSetGradientTypeLinear_          EwSetGradientTypeLinear
  #define EwSetGradientTypeRadial_          EwSetGradientTypeRadial
  #define EwAddGradientColorStop_           EwAddGradientColorStop
  #define EwSetGradientColorStop_           EwSetGradientColorStop
  #define EwGetGradientMaxNoOfColorStops_   EwGetGradientMaxNoOfColorStops
  #define EwGetGradientNoOfColorStops_      EwGetGradientNoOfColorStops
  #define EwCreatePath_                     EwCreatePath
  #define EwFreePath_                       EwFreePath
  #define EwGetMaxNoOfSubPaths_             EwGetMaxNoOfSubPaths
  #define EwInitSubPath_                    EwInitSubPath
  #define EwBeginSubPath_                   EwBeginSubPath
  #define EwAddSubPathLine_                 EwAddSubPathLine
  #define EwAddSubPathBezier2_              EwAddSubPathBezier2
  #define EwAddSubPathBezier3_              EwAddSubPathBezier3
  #define EwAddSubPathArc_                  EwAddSubPathArc
  #define EwAddSubPathCopy_                 EwAddSubPathCopy
  #define EwCloseSubPath_                   EwCloseSubPath
  #define EwShiftSubPathNodes_              EwShiftSubPathNodes
  #define EwSetSubPathNode_                 EwSetSubPathNode
  #define EwGetSubPathNodeX_                EwGetSubPathNodeX
  #define EwGetSubPathNodeY_                EwGetSubPathNodeY
  #define EwSetNoOfSubPathEdges_            EwSetNoOfSubPathEdges
  #define EwGetNoOfSubPathEdges_            EwGetNoOfSubPathEdges
  #define EwGetNoOfFreeSubPathEdges_        EwGetNoOfFreeSubPathEdges
  #define EwIsSubPathClosed_                EwIsSubPathClosed
  #define EwGetSubPathBounds_               EwGetSubPathBounds
  #define EwGetPathBounds_                  EwGetPathBounds
  #define EwTranslatePathMatrix_            EwTranslatePathMatrix
  #define EwScalePathMatrix_                EwScalePathMatrix
  #define EwRotatePathMatrix_               EwRotatePathMatrix
  #define EwPushPathMatrix_                 EwPushPathMatrix
  #define EwPopPathMatrix_                  EwPopPathMatrix
  #define EwInitPathMatrix_                 EwInitPathMatrix
  #define EwSetPathMatrix_                  EwSetPathMatrix
  #define EwFillPath_                       EwFillPath
  #define EwFillPathWithGradient_           EwFillPathWithGradient
  #define EwStrokePath_                     EwStrokePath
  #define EwStrokePathWithGradient_         EwStrokePathWithGradient
  #define EwGetBitmapFromFillPath_          EwGetBitmapFromFillPath
  #define EwGetBitmapFromStrokePath_        EwGetBitmapFromStrokePath
  #define EwGetBlurredBitmapFromFillPath_   EwGetBlurredBitmapFromFillPath
  #define EwGetBlurredBitmapFromStrokePath_ EwGetBlurredBitmapFromStrokePath
  #define EwCopyBitmap_                     EwCopyBitmap
  #define EwTileBitmap_                     EwTileBitmap
  #define EwWarpBitmap_                     EwWarpBitmap
  #define EwAdjustFilterBlurRadius_         EwAdjustFilterBlurRadius
  #define EwFilterBitmap_                   EwFilterBitmap
  #define EwDrawLine_                       EwDrawLine
  #define EwDrawText_                       EwDrawText
  #define EwGetTextExtent_                  EwGetTextExtent
  #define EwGetTextAdvance_                 EwGetTextAdvance
  #define EwGetTextColumnAtPosition_        EwGetTextColumnAtPosition
  #define EwGetPositionAtTextColumn_        EwGetPositionAtTextColumn
  #define EwIsGlyphAvailable_               EwIsGlyphAvailable
  #define EwGetGlyphId_                     EwGetGlyphId
  #define EwGetGlyphMetrics_                EwGetGlyphMetrics
  #define EwGetKerning_                     EwGetKerning
  #define EwLockGlyph_                      EwLockGlyph
  #define EwUnlockGlyph_                    EwUnlockGlyph
  #define EwDrawBitmapFrame_                EwDrawBitmapFrame
  #define EwIndexToColor_                   EwIndexToColor
  #define EwColorToIndex_                   EwColorToIndex
  #define EwAllocUserColor_                 EwAllocUserColor
  #define EwFreeUserColor_                  EwFreeUserColor
  #define EwSetUserColor_                   EwSetUserColor
  #define EwFindUserColor_                  EwFindUserColor
#endif


/*******************************************************************************
* FUNCTION:
*   EwInitGraphicsEngine
*
* DESCRIPTION:
*   The function EwInitGraphicsEngine() initializes the Graphics Engine.
*
* ARGUMENTS:
*   aArgs - Optional argument to pass to the init function of the underlying
*     platform specific adaptation layer.
*
* RETURN VALUE:
*   If successful, returns != 0.
*
*******************************************************************************/
int EwInitGraphicsEngine( void* aArgs )
{
  /* Prepare performance counters */
  EwAddPerfCounter( EwCreateBitmap                   );
  EwAddPerfCounter( EwCreateBitmapWrapped            );
  EwAddPerfCounter( EwLoadBitmap                     );
  EwAddPerfCounter( EwFreeBitmap                     );
  EwAddPerfCounter( EwLockBitmap                     );
  EwAddPerfCounter( EwUnlockBitmap                   );
  EwAddPerfCounter( EwModifyBitmapPalette            );
  EwAddPerfCounter( EwFlushBitmap                    );
  EwAddPerfCounter( EwGetFontResource                );
  EwAddPerfCounter( EwLoadFont                       );
  EwAddPerfCounter( EwFreeFont                       );
  EwAddPerfCounter( EwInitViewport                   );
  EwAddPerfCounter( EwDoneViewport                   );
  EwAddPerfCounter( EwConfigViewport                 );
  EwAddPerfCounter( EwBeginUpdate                    );
  EwAddPerfCounter( EwBeginUpdateArea                );
  EwAddPerfCounter( EwEndUpdate                      );
  EwAddPerfCounter( EwFillRectangle                  );
  EwAddPerfCounter( EwFillRoundedRectangle           );
  EwAddPerfCounter( EwDrawBorder                     );
  EwAddPerfCounter( EwDrawRoundedBorder              );
  EwAddPerfCounter( EwDrawRoundedShadow              );
  EwAddPerfCounter( EwCreateGradient                 );
  EwAddPerfCounter( EwFreeGradient                   );
  EwAddPerfCounter( EwSetGradientTypeLinear          );
  EwAddPerfCounter( EwSetGradientTypeRadial          );
  EwAddPerfCounter( EwAddGradientColorStop           );
  EwAddPerfCounter( EwSetGradientColorStop           );
  EwAddPerfCounter( EwGetGradientMaxNoOfColorStops   );
  EwAddPerfCounter( EwGetGradientNoOfColorStops      );
  EwAddPerfCounter( EwCreatePath                     );
  EwAddPerfCounter( EwFreePath                       );
  EwAddPerfCounter( EwGetMaxNoOfSubPaths             );
  EwAddPerfCounter( EwInitSubPath                    );
  EwAddPerfCounter( EwBeginSubPath                   );
  EwAddPerfCounter( EwAddSubPathLine                 );
  EwAddPerfCounter( EwAddSubPathBezier2              );
  EwAddPerfCounter( EwAddSubPathBezier3              );
  EwAddPerfCounter( EwAddSubPathArc                  );
  EwAddPerfCounter( EwAddSubPathCopy                 );
  EwAddPerfCounter( EwCloseSubPath                   );
  EwAddPerfCounter( EwShiftSubPathNodes              );
  EwAddPerfCounter( EwSetSubPathNode                 );
  EwAddPerfCounter( EwGetSubPathNodeX                );
  EwAddPerfCounter( EwGetSubPathNodeY                );
  EwAddPerfCounter( EwSetNoOfSubPathEdges            );
  EwAddPerfCounter( EwGetNoOfSubPathEdges            );
  EwAddPerfCounter( EwGetNoOfFreeSubPathEdges        );
  EwAddPerfCounter( EwIsSubPathClosed                );
  EwAddPerfCounter( EwGetSubPathBounds               );
  EwAddPerfCounter( EwGetPathBounds                  );
  EwAddPerfCounter( EwTranslatePathMatrix            );
  EwAddPerfCounter( EwScalePathMatrix                );
  EwAddPerfCounter( EwRotatePathMatrix               );
  EwAddPerfCounter( EwPushPathMatrix                 );
  EwAddPerfCounter( EwPopPathMatrix                  );
  EwAddPerfCounter( EwInitPathMatrix                 );
  EwAddPerfCounter( EwSetPathMatrix                  );
  EwAddPerfCounter( EwFillPath                       );
  EwAddPerfCounter( EwFillPathWithGradient           );
  EwAddPerfCounter( EwStrokePath                     );
  EwAddPerfCounter( EwStrokePathWithGradient         );
  EwAddPerfCounter( EwGetBitmapFromFillPath          );
  EwAddPerfCounter( EwGetBitmapFromStrokePath        );
  EwAddPerfCounter( EwGetBlurredBitmapFromFillPath   );
  EwAddPerfCounter( EwGetBlurredBitmapFromStrokePath );
  EwAddPerfCounter( EwCopyBitmap                     );
  EwAddPerfCounter( EwTileBitmap                     );
  EwAddPerfCounter( EwWarpBitmap                     );
  EwAddPerfCounter( EwAdjustFilterBlurRadius         );
  EwAddPerfCounter( EwFilterBitmap                   );
  EwAddPerfCounter( EwDrawLine                       );
  EwAddPerfCounter( EwDrawText                       );
  EwAddPerfCounter( EwGetTextExtent                  );
  EwAddPerfCounter( EwGetTextAdvance                 );
  EwAddPerfCounter( EwGetTextColumnAtPosition        );
  EwAddPerfCounter( EwGetPositionAtTextColumn        );
  EwAddPerfCounter( EwIsGlyphAvailable               );
  EwAddPerfCounter( EwGetGlyphId                     );
  EwAddPerfCounter( EwGetGlyphMetrics                );
  EwAddPerfCounter( EwGetKerning                     );
  EwAddPerfCounter( EwLockGlyph                      );
  EwAddPerfCounter( EwUnlockGlyph                    );
  EwAddPerfCounter( EwDrawBitmapFrame                );
  EwAddPerfCounter( EwIndexToColor                   );
  EwAddPerfCounter( EwColorToIndex                   );
  EwAddPerfCounter( EwAllocUserColor                 );
  EwAddPerfCounter( EwFreeUserColor                  );
  EwAddPerfCounter( EwSetUserColor                   );
  EwAddPerfCounter( EwFindUserColor                  );
  EwAddPerfCounter( MapBitmapFrame                   );
  EwAddPerfCounter( EwGfxInitViewport                );
  EwAddPerfCounter( EwGfxDoneViewport                );
  EwAddPerfCounter( EwGfxConfigViewport              );
  EwAddPerfCounter( EwGfxBeginUpdate                 );
  EwAddPerfCounter( EwGfxBeginUpdateArea             );
  EwAddPerfCounter( EwGfxEndUpdate                   );
  EwAddPerfCounter( ViewportCallback                 );

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Start the underlying graphics subsystem ... if any. */
  #ifdef EwGfxInit
    if ( !EwGfxInit( aArgs ))
    {
      EwError( 101 );
      return 0;
    }
  #endif

  /* On Index8 target systems load the global hardware CLUT */
  #if defined EW_ENABLE_COLOR_TABLE && defined EwGfxLoadClut
    #if defined __LP64__ || defined _LP64
      if ( !EwGfxLoadClut( EwGlobalClut, 0, EwGlobalClutCount ))
    #else
      if ( !EwGfxLoadClut((unsigned long*)EwGlobalClut, 0, EwGlobalClutCount ))
    #endif
      {
        EwError( 102 );
        return 0;
      }
  #endif

  /* First start the core functionality */
  if ( !EwInitGfxCore())
  {
    EwError( 105 );
    return 0;
  }

  /* Initialize the external bitmap resource loader */
  if ( !EwBmpInit( aArgs ))
  {
    EwDoneGfxCore();
    EwError( 106 );
    return 0;
  }

  /* Initialize the external font resource loader */
  if ( !EwFntInit( aArgs ))
  {
    EwBmpDone();
    EwDoneGfxCore();
    EwError( 107 );
    return 0;
  }

  /* Initialize the external SVG resource loader */
  if ( !EwSVGInit( aArgs ))
  {
    EwFntDone();
    EwBmpDone();
    EwDoneGfxCore();
    EwError( 500 );
    return 0;
  }

  /* Initialize the Bidi processor sub-system */
  if ( !EwInitBidi( aArgs ))
  {
    EwSVGDone();
    EwFntDone();
    EwBmpDone();
    EwDoneGfxCore();
    EwError( 108 );
    return 0;
  }

  /* Initialize the attribute text sub-system */
  if ( !EwInitAttrText( aArgs ))
  {
    EwSVGDone();
    EwFntDone();
    EwBmpDone();
    EwDoneGfxCore();
    EwError( 109 );
    return 0;
  }

  /* Initialize the SVG functionality */
  if ( !EwInitSVG( aArgs ))
  {
    EwSVGDone();
    EwFntDone();
    EwBmpDone();
    EwDoneGfxCore();
    EwError( 504 );
    return 0;
  }

  /* Initialize the attribute text sub-system */
  if ( !EwGfxTasksInit( aArgs ))
  {
    EwSVGDone();
    EwFntDone();
    EwBmpDone();
    EwDoneGfxCore();
    EwError( 110 );
    return 0;
  }

  #ifdef EW_ENABLE_COLOR_TABLE
    EwZero( EwColorAllocTable, sizeof( EwColorAllocTable ));

    /* Take in account the internally managed CLUT */
    EwResourcesMemory += EwGlobalClutCount * sizeof( int );
    EwResourcesMemory += sizeof( EwColorAllocTable );

    /* Also track the max. memory pressure */
    if ( EwResourcesMemory > EwResourcesMemoryPeak )
      EwResourcesMemoryPeak = EwResourcesMemory;

    if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
      EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;
  #endif

  EW_EVAL_INC_1();

  return 1;
}


/*******************************************************************************
* FUNCTION:
*   EwDoneGraphicsEngine
*
* DESCRIPTION:
*   The function EwDoneGraphicsEngine() deinitializes the Graphics Engine. If
*   necessary, still existing resources will be freed.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwDoneGraphicsEngine( void )
{
  EW_EVAL_INC_2();

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  EwSVGDone();
  EwFntDone();
  EwBmpDone();
  EwDoneGfxCore();

  /* At fin stop the underlying graphics subsystem ... if any. */
  #ifdef EwGfxDone
    EwGfxDone();
  #endif

  /* Take in account the internally managed CLUT */
  #ifdef EW_ENABLE_COLOR_TABLE
    EwResourcesMemory -= EwGlobalClutCount * sizeof( int );
    EwResourcesMemory -= sizeof( EwColorAllocTable );
  #endif
}


/*******************************************************************************
* FUNCTION:
*   EwGetGraphicsEngineInfo
*
* DESCRIPTION:
*   The function EwGetGraphicsEngineInfo() returns a data structure containing
*   most essential parameters of the Graphics Engine. For more details see the
*   declaration XGraphicsEngineInfo.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   Returns a pointer to a structure containing the essential parameters.
*
*******************************************************************************/
const XGraphicsEngineInfo* EwGetGraphicsEngineInfo( void )
{
  extern void EwGetColorFormatSpecificInfo( XGraphicsEngineInfo* aInfo );

  static XGraphicsEngineInfo info;

  /* The structure is aleady loaded */
  if ( info.Version )
    return &info;

  info.Version = EW_GFX_VERSION;

  #ifndef EW_DONT_USE_GRADIENTS
    info.DoesSupportGradients = 1;
  #endif

  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    info.DoesSupportPaths = 1;
  #endif

  #ifndef EW_DONT_USE_WARP_FUNCTIONS
    info.DoesSupportWarp = 1;
  #endif

  #ifndef EW_DONT_USE_BLUR_FUNCTIONS
    info.DoesSupportBlur = 1;
  #endif

  #ifndef EW_DONT_USE_MASK_FUNCTIONS
    info.DoesSupportMask = 1;
  #endif

  #ifndef EW_DONT_USE_TINT_FUNCTIONS
    info.DoesSupportTint = 1;
  #endif

  #ifndef EW_DONT_USE_BIDI_FUNCTIONS
    info.DoesSupportBIDI = 1;
  #endif

  #ifndef EW_DONT_USE_COMPRESSION
    info.DoesSupportCompression = 1;
  #endif

  #ifndef EW_DONT_USE_NATIVE_SURFACES
    info.DoesSupportNativeSurfaces = 1;
  #endif

  #ifndef EW_DONT_USE_INDEX8_SURFACES
    info.DoesSupportIndex8Surfaces = 1;
  #endif

  #ifndef EW_DONT_USE_RGB565_SURFACES
    info.DoesSupportRGB565Surfaces = 1;
  #endif

  #ifdef EW_USE_PIXEL_FORMAT_SCREEN
    info.DoesSupportScreenSurfaces = 1;
  #endif

  #ifndef EW_DONT_USE_NATIVE_SURFACES
    switch ( EwPixelDriverVariant )
    {
      case EW_DRIVER_VARIANT_RGBA8888        :
      case EW_DRIVER_VARIANT_RGB565_RGBA8888 :
      case EW_DRIVER_VARIANT_RGB888_RGBA8888 :
        info.FormatOfNativeSurfaces = EW_DRIVER_VARIANT_RGBA8888;
      break;
      case EW_DRIVER_VARIANT_RGBA4444        :
      case EW_DRIVER_VARIANT_LUMA44          :
      case EW_DRIVER_VARIANT_INDEX8          :
        info.FormatOfNativeSurfaces = EwPixelDriverVariant;
      break;
      default :;
    }
  #endif

  #ifndef EW_DONT_USE_SCREEN_SURFACES
    switch ( EwPixelDriverVariant )
    {
      case EW_DRIVER_VARIANT_RGB565_RGBA8888 :
        info.FormatOfScreenSurfaces = EW_DRIVER_VARIANT_RGB565;
      break;
      case EW_DRIVER_VARIANT_RGB888_RGBA8888 :
        info.FormatOfScreenSurfaces = EW_DRIVER_VARIANT_RGB888;
      break;
      default :;
    }
  #endif

  /* Obtain color format specific information from the pixel driver */
  EwGetColorFormatSpecificInfo( &info );

  return &info;
}


/*******************************************************************************
* FUNCTION:
*   EwEnableGfxTaskTracing
*
* DESCRIPTION:
*   The function EwEnableGfxTaskTracing() activates or deactivates the internal
*   debugging mode of the Graphics Engine. With this mode enabled, the Graphics
*   Engine prints log messages for every performed drawing operation, resource
*   loading operation, etc.
*
*   Please note, in order to use the 'task tracing' the Graphics Engine has to
*   be rebuilt with the macro EW_SUPPORT_GFX_TASK_TRACING defined.
*
* ARGUMENTS:
*   aEnable - If this parameter is != 0, the mode is activated. To deactivate
*     it again, pass 0 in this parameter.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwEnableGfxTaskTracing( int aEnable )
{
  EwPrintGfxTasks = aEnable;

  #ifndef EW_SUPPORT_GFX_TASK_TRACING
    EwError( 190 );
  #endif
}


/*******************************************************************************
* FUNCTION:
*   EwCreateBitmap
*
* DESCRIPTION:
*   The function EwCreateBitmap() creates a new bitmap with the given size and
*   color format. If no more used, the bitmap should be freed by calling the
*   function EwFreeBitmap().
*
* ARGUMENTS:
*   aFormat     - Color format of the bitmap. (See EW_PIXEL_FORMAT_XXX).
*   aFrameSize  - Size of a single bitmap frame.
*   aFrameDelay - Delay in milliseconds for animated bitmaps. If no animation
*     is specified for the bitmap, the value == 0.
*   aNoOfFrames - Number of frames to embed within the bitmap. At least one
*     frame is created.
*
* RETURN VALUE:
*   The function returns the pointer to the XBitmap structure, if the bitmap
*   was created successfully, otherwise 0.
*
*******************************************************************************/
XBitmap* EwCreateBitmap_( int aFormat, XPoint aFrameSize, XInt32 aFrameDelay,
  XInt32 aNoOfFrames )
{
  XBitmap* bitmap;
  int      maxNoOfFrames = 0;
  int      i;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Surfaces with the 'Screen' pixel format are used internally for the frame
     buffer only. It is not possible to create a 'screen' bitmap with this API. */
  if ( aFormat == EW_PIXEL_FORMAT_SCREEN )
  {
    EwError( 123 );
    return 0;
  }

  /* The support of Native bitmaps can be excluded to reduce the code size */
  #if defined EW_DONT_USE_NATIVE_SURFACES &&                                   \
      defined EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION
    if ( aFormat == EW_PIXEL_FORMAT_NATIVE )
    {
      EwError( 381 );
      return 0;
    }
  #endif

  /* The support of Index8 bitmaps can be excluded to reduce the code size */
  #ifdef EW_DONT_USE_INDEX8_SURFACES
    if ( aFormat == EW_PIXEL_FORMAT_INDEX8 )
    {
      EwError( 197 );
      return 0;
    }
  #endif

  /* The support of Index8 bitmaps can be excluded to reduce the code size */
  #ifdef EW_DONT_USE_RGB565_SURFACES
    if ( aFormat == EW_PIXEL_FORMAT_RGB565 )
    {
      EwError( 199 );
      return 0;
    }
  #endif

  /* Running on GPU not able to retain old off-screen buffer contents expects
     full update of the off-screen buffer. In such case we can't store several
     multi-frames within the same off-screen buffer. Limit one surface to one
     frame. */
  if ( EwFullOffScreenBufferUpdate && ( aFormat == EW_PIXEL_FORMAT_NATIVE ))
    maxNoOfFrames = 1;

  /* Create and initialize a bitmap descriptor structure. This call prepares
     the list of frames and assigns them the appropriate positions within the
     respective surfaces. The surfaces, however, are not created until the
     frames are accessed. */
  bitmap = InitBitmap( aFormat, aFrameSize, aFrameDelay, aNoOfFrames, aNoOfFrames,
                       maxNoOfFrames, maxNoOfFrames, 1, 0, EwLazyLoadBitmaps &&
                       !EwLazyLoadBitmapsIfAnimatedOnly );

  /* Failed due to out of memory or invalid parameter */
  if ( !bitmap )
    return 0;

  /* Ensure, the bitmaps are created immediatelly with all surfaces */
  for ( i = 0; i < bitmap->NoOfVirtFrames; i++ )
    if ( !MapBitmapFrame( bitmap, i ))
    {
      EwError( 320 );
      EwFreeBitmap( bitmap );
      return 0;
    }

  return bitmap;
}


EW_INSTRUMENT_FUNC( EwCreateBitmap, XBitmap*, ( int aFormat, XPoint aFrameSize,
  XInt32 aFrameDelay, XInt32 aNoOfFrames ), ( aFormat, aFrameSize, aFrameDelay,
  aNoOfFrames ))


/*******************************************************************************
* FUNCTION:
*   EwCreateBitmapWrapped
*
* DESCRIPTION:
*   The function EwCreateBitmapWrapped() creates a new bitmap with the given
*   size and color format. Important here is the fact that the function doesn't
*   reserve any memory to store the pixel information. Instead it, the bitmap
*   associates the image data passed in the parameter aHandle. In other words,
*   it 'wraps' the externally created image content.
*
*   The value specified in aHandle is specific for the particular target system
*   or the underlying graphics API. For example, in case of an OpenGL target it
*   will be a texture-id. This value is simply passed through to the lower-level
*   driver implementing the glue code between Embedded Wizard and the underlying
*   graphics subsystem.
*
*   Since the image content is created and owned externally, Embedded Wizard is
*   not allowed to delete the contents by itself. Instead, when the associated
*   image contents are about to be disposed, the callback function aDeleteProc
*   is called. Within the function all necessary cleanup operations can be
*   performed to free the externally created image content.
*
*   Please note, when using this function, the resulting bitmap will contain
*   one frame only. Creating multi-frame or animated bitmaps is not supported
*   with externally created image contents. In other words, one bitmap 'wraps'
*   a single image frame created externally.
*
*   If no more used, the bitmap should be freed by calling the function
*   EwFreeBitmap().
*
* ARGUMENTS:
*   aFormat     - Color format of the bitmap. (See EW_PIXEL_FORMAT_XXX).
*   aFrameSize  - Size of the bitmap to create. This must correspond to the
*     size of the image content provided in aHandle.
*   aHandle     - The externally created content of the bitmap. This value is
*     specific for the particular target system. It will be passed through to
*     the lower-level driver integrating the Graphics Engine with the target
*     system.
*   aDeleteProc - Function to be called by Graphics Engine when the image is
*     disposed. The implementation of the function can thereupon release the
*     involved image contents and perform any other cleaning operations.
*   aDeleteArg  - This parameter is passed to the callback function aDeleteProc.
*
* RETURN VALUE:
*   The function returns the pointer to the XBitmap structure, if the bitmap
*   was created successfully, otherwise 0.
*
*******************************************************************************/
XBitmap* EwCreateBitmapWrapped_( int aFormat, XPoint aFrameSize,
  void* aHandle, XDeleteSurfaceProc aDeleteProc, void* aDeleteArg )
{
  XBitmap*  bitmap;
  XSurface* surface;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Surfaces with the 'Screen' pixel format are used internally for the frame
     buffer only. It is not possible to create a 'screen' bitmap with this API. */
  if ( aFormat == EW_PIXEL_FORMAT_SCREEN )
  {
    EwError( 123 );
    return 0;
  }

  /* The support of Native bitmaps can be excluded to reduce the code size */
  #if defined EW_DONT_USE_NATIVE_SURFACES &&                                   \
      defined EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION
    if ( aFormat == EW_PIXEL_FORMAT_NATIVE )
    {
      EwError( 381 );
      return 0;
    }
  #endif

  /* The support of Index8 bitmaps can be excluded to reduce the code size */
  #ifdef EW_DONT_USE_INDEX8_SURFACES
    if ( aFormat == EW_PIXEL_FORMAT_INDEX8 )
    {
      EwError( 197 );
      return 0;
    }
  #endif

  /* The support of Index8 bitmaps can be excluded to reduce the code size */
  #ifdef EW_DONT_USE_RGB565_SURFACES
    if ( aFormat == EW_PIXEL_FORMAT_RGB565 )
    {
      EwError( 199 );
      return 0;
    }
  #endif

  /* Create and initialize a bitmap descriptor structure. This call prepares
     the list of frames and assigns them the appropriate positions within the
     respective surfaces. The surfaces, however, are not created until the
     frames are accessed. */
  bitmap = InitBitmap( aFormat, aFrameSize, 0, 1, 1, 1, 1, 0, 0, 0 );

  /* Failed due to out of memory or invalid parameter */
  if ( !bitmap )
    return 0;

  /* Ensure, the bitmaps are created immediatelly with all surfaces */
  surface = EwCreateSurfaceWrapped( aFormat, aFrameSize.X, aFrameSize.Y,
                                    bitmap, 0, 0, aHandle, aDeleteProc,
                                    aDeleteArg );

  /* Failed due to out of memory or invalid parameter */
  if ( !surface )
  {
    EwError( 401 );
    EwFreeBitmap( bitmap );
    return 0;
  }

  /* Store the surface in the bitmap */
  bitmap->Surfaces[ 0 ]         = surface;
  bitmap->Frames  [ 0 ].Surface = surface;

  /* Mark the surface as used during the actual update cycle */
  surface->Stamp = EwUpdateCycle;

  return bitmap;
}


EW_INSTRUMENT_FUNC( EwCreateBitmapWrapped, XBitmap*, ( int aFormat,
  XPoint aFrameSize, void* aHandle, XDeleteSurfaceProc aDeleteProc,
  void* aDeleteArg ), ( aFormat, aFrameSize, aHandle, aDeleteProc, aDeleteArg ))


/*******************************************************************************
* FUNCTION:
*   EwLoadBitmap
*
* DESCRIPTION:
*   The function EwLoadBitmap() creates a new bitmap and loads it with the
*   content of the passed bitmap resource.
*
* ARGUMENTS:
*   aResource - Descriptor of the bitmap resource to load. The content of this
*     descriptor depends on the particular platform system.
*
* RETURN VALUE:
*   If sucessful, the function returns a new bitmap initialized with the content
*   of the resource. If failed, the function returns null.
*
*******************************************************************************/
XBitmap* EwLoadBitmap_( const struct XBmpRes* aResource )
{
  int            lazyMapSurfaces = EwLazyLoadBitmaps;
  void*          handle;
  XBitmap*       bitmap;
  int            format;
  int            noOfFrames;
  int            noOfVirtFrames;
  int            frameWidth;
  int            frameHeight;
  XPoint         frameSize;
  int            frameDelay;
  int            maxNoOfFramesX = 0;
  int            maxNoOfFramesY = 0;
  int            directAccess;
  XSurfaceMemory memory;
  int            i;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Couldn't open the bitmap resource */
  if ( !aResource || (( handle = EwBmpOpen( aResource )) == 0 ))
  {
    EwErrorPD( 132, aResource, 0 );
    return 0;
  }

  /* Query the number of enclosed frames and other metrics of the bitmap
     resource */
  if ( !EwBmpGetMetrics( handle, &format, &noOfFrames, &noOfVirtFrames,
                         &frameWidth, &frameHeight, &frameDelay ))
  {
    EwBmpClose( handle );
    EwErrorPD( 133, aResource, 0 );
    return 0;
  }

  /* The support of Native bitmaps can be excluded to reduce the code size */
  #ifdef EW_DONT_USE_NATIVE_SURFACES
    if ( format == EW_PIXEL_FORMAT_NATIVE )
    {
      EwBmpClose( handle );
      EwError( 382 );
      return 0;
    }
  #endif

  /* The support of Index8 bitmaps can be excluded to reduce the code size */
  #ifdef EW_DONT_USE_INDEX8_SURFACES
    if ( format == EW_PIXEL_FORMAT_INDEX8 )
    {
      EwBmpClose( handle );
      EwError( 198 );
      return 0;
    }
  #endif

  /* The support of Index8 bitmaps can be excluded to reduce the code size */
  #ifdef EW_DONT_USE_RGB565_SURFACES
    if ( format == EW_PIXEL_FORMAT_RGB565 )
    {
      EwBmpClose( handle );
      EwError( 200 );
      return 0;
    }
  #endif

  /* How are the bitmap pixel information stored? Compressed or we can access
     it directly? Simply try to get a pointer to uncompressed pixel. */
  directAccess = EwBmpGetFrameMemory( handle, 0, &memory );

  /* Should limit the lazy map surfaces operation to animated bitmaps only? */
  if ( EwLazyLoadBitmapsIfAnimatedOnly )
    lazyMapSurfaces = ( noOfVirtFrames > 1 ) && ( frameDelay > 0 );

  /* When the bitmap allows its pixel data be accessed directly (without any
     decompression), then the layout of how frames are arranged within the
     bitmap associated surfaces should be limited to one row/column depending
     on the orientation of the bitmap. */
  #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
    if ( directAccess ) maxNoOfFramesY = 1;
  #else
    if ( directAccess ) maxNoOfFramesX = 1;
  #endif

  /* Create and initialize a bitmap descriptor structure. This call prepares the
     list of frames and assigns them the appropriate positions within the
     respective surfaces. The surfaces are not created until the frame is
     accessed. */
  frameSize.X = frameWidth;
  frameSize.Y = frameHeight;
  bitmap      = InitBitmap( format, frameSize, frameDelay, noOfFrames,
                            noOfVirtFrames, maxNoOfFramesX, maxNoOfFramesY,
                            1, format == EW_PIXEL_FORMAT_RGB565,
                            lazyMapSurfaces && !directAccess );

  /* Failed due to out of memory or invalid parameter */
  if ( !bitmap )
  {
    EwBmpClose( handle );
    return 0;
  }

  /* The bitmap contains frame duplicates. These 'virtual' frames need to be
     mapped to real existing franes. Load the mapping table. */
  if ( noOfVirtFrames > noOfFrames )
    EwBmpLoadMappingTable( handle, bitmap->Mapping );

  /* Query the metric information associated to the frames */
  for ( i = 0; i < noOfFrames; i++ )
  {
    /* Determine the surface number to store the frame pixel data and the size
       of the surface */
    XBitmapFrame* frame = bitmap->Frames + i;
    int           opqX, opqY;
    int           opqW, opqH;

    /* Get the metrics of the frame */
    if ( !EwBmpGetFrameMetrics( handle, i, &opqX, &opqY, &opqW, &opqH ))
    {
      EwErrorPD( 134, aResource, 0 );
      EwFreeBitmap( bitmap );
      EwBmpClose( handle );
      return 0;
    }

    frame->OpaqueRect.Point1.X = opqX;
    frame->OpaqueRect.Point1.Y = opqY;
    frame->OpaqueRect.Point2.X = opqX + opqW;
    frame->OpaqueRect.Point2.Y = opqY + opqH;
  }

  /* At fin close the bitmap resource */
  EwBmpClose( handle );

  /* The loading of pixel data is deferred. Therefore the bitmap has to know
     the original resource from where it should get the pixel data  */
  bitmap->Resource = aResource;

  /* Please note, bitmaps for direct access store their frames strictly in
     their logical order. This however is not the order in which frames are
     addressed when surfaces manages their pixel data rotated. The frame
     coordinates need an adaptation in this case. */
  #if EW_SURFACE_ROTATION != 0
    if ( directAccess )
    {
      XBitmapFrame* frameS = bitmap->Frames;
      XBitmapFrame* frameL = bitmap->Frames + noOfFrames - 1;

      /* Process all frames belonging to this bitmap. */
      while ( frameS < frameL )
      {
        XBitmapFrame* frame1 = frameS;
        XBitmapFrame* frame2 = frameS;

        /* Search for frames located within the same surface. */
        while (( frame2 < frameL ) && (( frame2->Origin.X < frame2[1].Origin.X ) ||
                                       ( frame2->Origin.Y < frame2[1].Origin.Y )))
          frame2++;

        frameS = frame2 + 1;

        /* For all frames belonging to the same surface, adjust the coordinates */
        for ( ; frame1 < frame2; frame1++, frame2-- )
        {
          XPoint tmp = frame1->Origin;

          #if ( EW_SURFACE_ROTATION == 180 ) || ( EW_SURFACE_ROTATION == 270 )
            frame1->Origin.X = frame2->Origin.X;
            frame2->Origin.X = tmp.X;
          #endif

          #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 180 )
            frame1->Origin.Y = frame2->Origin.Y;
            frame2->Origin.Y = tmp.Y;
          #endif
        }
      }
    }
  #endif

  /* Should the bitmaps be loaded immediatelly with all frames? */
  if ( !lazyMapSurfaces )
    for ( i = 0; i < bitmap->NoOfVirtFrames; i++ )
      if ( !MapBitmapFrame( bitmap, i ))
      {
        EwErrorPD( 321, aResource, 0 );
        EwFreeBitmap( bitmap );
        return 0;
      }

  return bitmap;
}


EW_INSTRUMENT_FUNC( EwLoadBitmap, XBitmap*, ( const struct XBmpRes* aResource ),
  ( aResource ))


/*******************************************************************************
* FUNCTION:
*   EwFreeBitmap
*
* DESCRIPTION:
*   The function EwFreeBitmap() frees the given bitmap. Bitmaps may be created
*   by using EwCreateBitmap() or they may be loaded from a bitmap resource by
*   calling the function EwLoadBitmap().
*
* ARGUMENTS:
*   aBitmap - Bitmap to free.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwFreeBitmap_( XBitmap* aBitmap )
{
  int i;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Ensure the given bitmap is still valid */
  if ( !aBitmap || !aBitmap->NoOfFrames || !aBitmap->NoOfSurfaces )
    return;

  /* Track the RAM usage */
  EwResourcesMemory -= sizeof( XBitmap );
  EwResourcesMemory -= sizeof( XSurface* )    * aBitmap->NoOfSurfaces;
  EwResourcesMemory -= sizeof( XBitmapFrame ) * aBitmap->NoOfFrames;

  if ( aBitmap->Mapping )
    EwResourcesMemory -= sizeof( unsigned short ) * aBitmap->NoOfVirtFrames;

  /* Free the underlying surfaces */
  for ( i = 0; i < aBitmap->NoOfSurfaces; i++ )
    if ( aBitmap->Surfaces[i])
      EwFreeSurface( aBitmap->Surfaces[i]);

  aBitmap->NoOfFrames     = 0;
  aBitmap->NoOfVirtFrames = 0;
  aBitmap->NoOfSurfaces   = 0;

  /* ... and the bitmap structure itself */
  EwFree( aBitmap );
}


EW_INSTRUMENT_VOID_FUNC( EwFreeBitmap, ( XBitmap* aBitmap ), ( aBitmap ))


/*******************************************************************************
* FUNCTION:
*   EwLockBitmap
*
* DESCRIPTION:
*   The function EwLockBitmap() provides a direct access to the pixel memory of
*   the given bitmap. The function returns a lock object containing pointers to
*   memory, where the caller can read/write the bitmap pixel values. Additional
*   pitch values also returned in the lock object allow the caller to calculate
*   the desired pixel addresses.
*
*   When finished the access cycle, the function EwUnlockBitmap() should be used
*   in order to release the lock, update the affected bitmap, flush CPU caches,
*   etc.
*
*   The memory returned by the function is not guaranteed to be the real video
*   memory of the bitmap. If necessary, the function will handle the access by
*   using a shadow memory area. Therefore to limit the effort of memory copy
*   operations, the desired bitmap area and the access mode should be specified.
*   Note the three parameters aArea, aRead and aWrite. Depending on the graphics
*   sub-system these three parameters may affect significantly the performance.
*
*   If there was not possible to lock the surface, or the desired access mode
*   is just not supported by the underlying graphics sub-system, the function
*   fails and returns zero. (e.g. OpenGL based sub-systems usually allow the
*   write access to bitmaps (textures) only. Read access may fail in this case)
*
*   Note, the pixel storage depends on the pixel format. For more details see
*   the 'ewextpxl_XXX.h' file (XXX stands for your target pixel format. e.g.
*   'ewextpxl_RGBA8888.h').
*
* ARGUMENTS:
*   aBitmap  - Bitmap to obtain the direct memory access.
*   aFrameNo - Frame within the destination bitmap affected by the access
*     operation.
*   aArea    - Area within the frame affected by the access operation (Relative
*     to the top-left corner of the bitmap frame). This is the area, the caller
*     intends to read/write the pixel data.
*   aRead    - Is != 0, if the caller intends to read the pixel information
*     from the bitmap memory. If == 0, the memory content may remain undefined
*     depending on the underlying graphics sub-system and its video-memory
*     management.
*   aWrite   - Is != 0, if the caller intends to overwrite the pixel information
*     within the bitmap memory. If == 0, any modifications within the memory may
*     remain ignored depending on the underlying graphics sub-system and its
*     video-memory management.
*
* RETURN VALUE:
*   If successful, the function returns a temporary bitmap lock object. If the
*   intended access is not possible or not supported by the underlying graphics
*   sub-system, 0 is returned.
*
*******************************************************************************/
XBitmapLock* EwLockBitmap_( XBitmap* aBitmap, XInt32 aFrameNo, XRect aArea,
  XBool aRead, XBool aWrite )
{
  XBitmapFrame*  frame   = MapBitmapFrame( aBitmap, aFrameNo );
  XBitmapLock*   bmpLock = 0;
  XSurfaceLock   srfLock;
  int            x1      = aArea.Point1.X;
  int            y1      = aArea.Point1.Y;
  int            x2      = aArea.Point2.X;
  int            y2      = aArea.Point2.Y;
  short          mode    = 0;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Invalid bitmap, frame number or the origin of the lock area lies outside
     the bitmap? */
  if ( !frame || ( x1 < 0 ) || ( y1 < 0 ))
  {
    EwErrorPD( 143, aBitmap, aFrameNo );
    return 0;
  }

  /* Limit the lock area to the frame boundary */
  x1 = MAX( x1, 0 );
  y1 = MAX( y1, 0 );
  x2 = MIN( x2, aBitmap->FrameSize.X );
  y2 = MIN( y2, aBitmap->FrameSize.Y );

  /* Nothing to lock? */
  if (( x2 <= x1 ) || ( y2 <= y1 ))
    return 0;

  /* Determine the desired lock mode */
  if ( aRead  ) mode |= EW_LOCK_PIXEL_READ;
  if ( aWrite ) mode |= EW_LOCK_PIXEL_WRITE;

  /* Try to lock the corresponding surface */
  if ( !EwLockSurface( frame->Surface, frame->Origin.X + x1,
          frame->Origin.Y + y1, x2 - x1, y2 - y1, 0, 0, mode, &srfLock ))
  {
    EwErrorPD( 137, frame->Surface, 0 );
    return 0;
  }

  /* Ok, we got the access privilege - now, prepare the temporary lock object */
  do
    bmpLock = EwAlloc( sizeof( XBitmapLock ) + sizeof( XSurfaceLock ) +
                       sizeof( XSurface* ));
  while ( !bmpLock && EwImmediateReclaimMemory( 24 ));

  /* Out of memory ... */
  if ( !bmpLock )
  {
    EwUnlockSurface( frame->Surface, &srfLock );
    EwError( 24 );
    return 0;
  }

  bmpLock->Pixel1  = srfLock.Memory.Pixel1;
  bmpLock->Pitch1X = srfLock.Memory.Pitch1X;
  bmpLock->Pitch1Y = srfLock.Memory.Pitch1Y;
  bmpLock->Pixel2  = srfLock.Memory.Pixel2;
  bmpLock->Pitch2X = srfLock.Memory.Pitch2X;
  bmpLock->Pitch2Y = srfLock.Memory.Pitch2Y;

  /* Store the internal lock information in the hidden part of the structure */
  *(XSurfaceLock*)( bmpLock + 1 ) = srfLock;
  *(XSurface**)((XSurfaceLock*)( bmpLock + 1 ) + 1 ) = frame->Surface;

  /* Track the RAM usage */
  EwResourcesMemory += sizeof( XBitmapLock ) + sizeof( XSurfaceLock ) +
                       sizeof( XSurface* );

  /* Also track the max. memory pressure */
  if ( EwResourcesMemory > EwResourcesMemoryPeak )
    EwResourcesMemoryPeak = EwResourcesMemory;

  if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
    EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

  return bmpLock;
}


EW_INSTRUMENT_FUNC( EwLockBitmap, XBitmapLock*, ( XBitmap* aBitmap,
  XInt32 aFrameNo, XRect aArea, XBool aRead, XBool aWrite ), ( aBitmap,
  aFrameNo, aArea, aRead, aWrite ))


/*******************************************************************************
* FUNCTION:
*   EwUnlockBitmap
*
* DESCRIPTION:
*   The function EwUnlockBitmap() provides a counterpart to EwLockBitmap(). When
*   called, the function releases the given lock and if necessary, transfers the
*   memory modifications back to the video memory of the bitmap and flushes the
*   CPU caches.
*
*   After calling this function, the aLock structure will become invalid.
*
* ARGUMENTS:
*   aLock - Lock object returned by the previous EwLockBitmap() call.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwUnlockBitmap_( XBitmapLock* aLock )
{
  XSurfaceLock* srfLock = (XSurfaceLock*)( aLock + 1 );
  XSurface**    surface = (XSurface**)( srfLock + 1 );

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Invalid lock object or already released? */
  if ( !aLock || !*surface )
    return;

  /* Release the lock - update the surface, video-memory, flush caches, etc. */
  EwUnlockSurface( *surface, srfLock );

  /* Mark the lock object as released and ... */
  *surface = 0;

  /* ... free the object memory */
  EwFree( aLock );

  /* Track the RAM usage */
  EwResourcesMemory -= sizeof( XBitmapLock ) + sizeof( XSurfaceLock ) +
                       sizeof( XSurface* );
}


EW_INSTRUMENT_VOID_FUNC( EwUnlockBitmap, ( XBitmapLock* aLock ), ( aLock ))


/*******************************************************************************
* FUNCTION:
*   EwModifyBitmapPalette
*
* DESCRIPTION:
*   The function EwModifyBitmapPalette() changes color values within the palette
*   of the given Index8 bitmap. If applied on a non Index8 bitmap, the function
*   will ignore the operation.
*
*   In case of a multi-frame bitmap, the modification affects all frames within
*   this bitmap.
*
* ARGUMENTS:
*   aBitmap - Index8 bitmap to modify its palette.
*   aIndex  - Number of the first palette entry affected by the modification.
*   aCount  - Number of entries to modify.
*   aColors - Array with aCount colors to store within the palette starting
*     with palette entry aIndex.
*
* RETURN VALUE:
*   None.
*
*******************************************************************************/
void EwModifyBitmapPalette_( XBitmap* aBitmap, XInt32 aIndex, XInt32 aCount,
  XColor* aColors )
{
  #ifndef EW_DONT_USE_INDEX8_SURFACES
    XSurfaceLock lock;
    int          i, j;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Is the bitmap valid? */
    if ( !aBitmap || ( aBitmap->Format != EW_PIXEL_FORMAT_INDEX8 ))
    {
      EwErrorPD( 144, aBitmap, 0 );
      return;
    }

    /* Does the parameters make sense? */
    if ( !aColors || ( aIndex < 0 ) || ( aCount <= 0 ) ||
       (( aIndex + aCount ) > 256 ))
    {
      EwErrorPD( 145, aBitmap, 0 );
      return;
    }

    /* Palette can not be modified if the bitmap does contain data loaded from
       resource. */
    if ( aBitmap->Resource )
    {
      EwErrorPD( 317, aBitmap, 0 );
      return;
    }

    /* The palette modification applies to all frames (all surfaces) of the
       bitmap. Ensure all surfaces are in memory */
    for  ( i = 0; i < aBitmap->NoOfVirtFrames; i++ )
      if ( !MapBitmapFrame( aBitmap, i ))
      {
        EwError( 319 );
        return;
      }

    /* Once the surfaces are loaded, update all enclosed surfaces */
    for ( i = 0; i < aBitmap->NoOfSurfaces; i++ )
    {
      XSurface* surface = aBitmap->Surfaces[i];

      /* Try to lock the corresponding surface */
      if ( !EwLockSurface( surface, 0, 0, 0, 0, aIndex, aCount, EW_LOCK_CLUT_WRITE,
              &lock ))
      {
        EwErrorPD( 138, surface, 0 );
        return;
      }

      /* Assign the new color values */
      for ( j = 0; j < aCount; j++ )
      {
        XColor*      c = aColors + j;
        unsigned int x = EwFindUserColor( *c );

        /* No user defined color found - try to map the color to one of the
           pre-defined clut entries */
        if ( !x )
          x = EwPackClutEntry( c->Red, c->Green, c->Blue, c->Alpha );

        lock.Memory.Clut[j] = x;
      }

      /* Unlock and update the surface */
      EwUnlockSurface( surface, &lock );
    }
  #else
    EW_UNUSED_ARG( aBitmap );
    EW_UNUSED_ARG( aIndex );
    EW_UNUSED_ARG( aCount );
    EW_UNUSED_ARG( aColors );
  #endif
}


EW_INSTRUMENT_VOID_FUNC( EwModifyBitmapPalette, ( XBitmap* aBitmap,
  XInt32 aIndex, XInt32 aCount, XColor* aColors ), ( aBitmap, aIndex, aCount,
  aColors ))


/*******************************************************************************
* FUNCTION:
*   EwFlushBitmap
*
* DESCRIPTION:
*   The function EwFlushBitmap() has the job to flush any outstanding drawing
*   Graphics Engine operations for this bitmap as destination.
*
* ARGUMENTS:
*   aBitmap - Bitmap to flush drawing operations.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwFlushBitmap_( XBitmap* aBitmap )
{
  int i;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Nothing to do */
  if ( !aBitmap )
    return;

  /* Repeat for all enclosed bitmap surfaces */
  for ( i = 0; i < aBitmap->NoOfSurfaces; i++ )
    if ( aBitmap->Surfaces[i])
      EwFlushTasks( aBitmap->Surfaces[i]);
}


EW_INSTRUMENT_VOID_FUNC( EwFlushBitmap, ( XBitmap* aBitmap ), ( aBitmap ))


/*******************************************************************************
* FUNCTION:
*   EwGetFontResource
*
* DESCRIPTION:
*   The function EwGetFontResource() has the job to find or create a resource
*   descriptor matching the attributes specified in the function parameters. The
*   returned resource can thereupon be passed to EwLoadFont() function in order
*   to use the font.
*
*   Please note: this function allows the caller to dynamically create fonts on
*   target systems supporting a TrueType font engine. In the case, you are using
*   the version WITHOUT TrueType font engine integration, all fonts are already
*   stored as prerasterized glyphs. Dynamic creation of a font with different
*   attributes is in such case not possible and the function will return null.
*
* ARGUMENTS:
*   aName        - A unique name of the TrueType font stored as zero terminated
*     widechar string (e.g. "Arial"). The function limits the evaluation to the
*     first 31 characters from the string.
*   aHeight      - The desired height of the font in pixel.
*   aBold        - This parameter determines, whether a bold or a normal style
*     of the font should be used at the runtime. A bold font will be used if
*     this parameter contains a value != 0.
*   aItalic      - This parameter determines, whether an italic or a normal
*     style of the font should be used at the runtime. An italic font is used
*     if this parameter contains a value != 0.
*   aAspectRatio - The AspectRatio parameter defines the desired aspect ratio
*     of the font in the range from 0.25 to 4.0. The default value is 1.0 - in
*     this case the aspect ratio of the font corresponds to the origin design
*     of the font.
*   aNoOfColors  - Desired quality of the font glyphs to raster. Only the
*     values 2, 4 or 16 are valid.
*   aKerning     - Determines whether kerning data should be used for this
*     font. In such case the value has to be != 0.
*   aRowDistance - The desired distance between two consecutive text rows. If
*     the value is == 0, the distance is calculated on the base of the font
*     metrics.
*   aPopularMode - If != 0, calculate the font size similarly to how other
*     application it does. If == 0, the mode compatible to older Embedded
*     Wizard version is used.
*
* RETURN VALUE:
*   Returns a pointer to a data structure representing the font resource. If
*   the target system does not support the dynamic font creation, the function
*   will return null.
*
*******************************************************************************/
const struct XFntRes* EwGetFontResource_( XString aName, XInt32 aHeight,
  XBool aBold, XBool aItalic, XFloat aAspectRatio, XInt32 aNoOfColors,
  XBool aKerning, XInt32 aRowDistance, XBool aPopularMode )
{
  char         name[32];
  unsigned int i;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Convert the desired font name in ASCII string. Character codes beyond the
     ASCII area are converted in blank sign */
  for ( i = 0; ( i < ( sizeof( name ) - 1 )) && aName && aName[i]; i++ )
    if ( aName[i] > 255 ) name[i] = ' ';
    else                  name[i] = (char)aName[i];

  /* Terminate the string with zero */
  name[i] = 0;

  return EwFntGetResource( name, aHeight, aBold, aItalic, aAspectRatio,
                           aNoOfColors, aKerning, aRowDistance, aPopularMode );
}


EW_INSTRUMENT_FUNC( EwGetFontResource, const struct XFntRes*, ( XString aName,
  XInt32 aHeight, XBool aBold, XBool aItalic, XFloat aAspectRatio,
  XInt32 aNoOfColors, XBool aKerning, XInt32 aRowDistance, XBool aPopularMode ),
  ( aName, aHeight, aBold, aItalic, aAspectRatio, aNoOfColors, aKerning,
    aRowDistance, aPopularMode ))


/*******************************************************************************
* FUNCTION:
*   EwLoadFont
*
* DESCRIPTION:
*   The function EwLoadFont() creates a new font and loads it with the content
*   of the passed font resource.
*
* ARGUMENTS:
*   aResource - Descriptor of the font resource to load. The content of this
*     descriptor depends on the particular platform system.
*
* RETURN VALUE:
*   If sucessful, the function returns a new font initialized with the content
*   of the resource. If failed, the function returns null.
*
*******************************************************************************/
XFont* EwLoadFont_( const struct XFntRes* aResource )
{
  void*         handle;
  XFont*        font;
  int           ascent;
  int           descent;
  int           leading;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Couldn't open the font resource */
  if ( !aResource || (( handle = EwFntOpen( aResource )) == 0 ))
  {
    EwErrorPD( 146, aResource, 0 );
    return 0;
  }

  /* Query the general font metrics */
  if ( !EwFntGetMetrics( handle, &ascent, &descent, &leading ))
  {
    EwFntClose( handle );
    EwErrorSD( 147, EwFntGetResourceName( handle ), 0 );
    return 0;
  }

  /* Reserve memory for the font object */
  do
    font = EwAlloc( sizeof( XFont ));
  while ( !font && EwImmediateReclaimMemory( 25 ));

  /* Couldn't create the font object due to the resource deficit - rewind */
  if ( !font )
  {
    EwFntClose( handle );
    EwError( 25 );
    return 0;
  }

  /* Complete the initialization */
  font->Ascent  = ascent;
  font->Descent = descent;
  font->Leading = leading;
  font->Tag     = (void*)EwFntGetCacheSearchTag( handle );
  font->Handle  = handle;

  /* Track the RAM usage */
  EwResourcesMemory += sizeof( XFont );

  /* Also track the max. memory pressure */
  if ( EwResourcesMemory > EwResourcesMemoryPeak )
    EwResourcesMemoryPeak = EwResourcesMemory;

  if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
    EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

  return font;
}


EW_INSTRUMENT_FUNC( EwLoadFont, XFont*, ( const struct XFntRes* aResource ),
  ( aResource ))


/*******************************************************************************
* FUNCTION:
*   EwFreeFont
*
* DESCRIPTION:
*   The function EwFreeFont() frees the given font. Fonts can be loaded from a
*   font resource by calling the function EwLoadFont().
*
* ARGUMENTS:
*   aFont - Font to free.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwFreeFont_( XFont* aFont )
{
  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  if ( !aFont )
    return;

  /* Close the original font resource */
  EwFntClose( aFont->Handle );
  aFont->Handle = 0;

  /* ... and free the font structure itself */
  EwFree( aFont );

  /* Track the RAM usage */
  EwResourcesMemory -= sizeof( XFont );
}


EW_INSTRUMENT_VOID_FUNC( EwFreeFont, ( XFont* aFont ), ( aFont ))


/*******************************************************************************
* FUNCTION:
*   EwInitViewport
*
* DESCRIPTION:
*   The function EwInitViewport() prepares a new viewport. Viewports provide a
*   kind of abstraction of the physical framebuffer or display where graphical
*   outputs are drawn. Depending on the particular target system there are two
*   mayor approaches how Graphics Engine can deal with a framebuffer:
*
*   1. The creation and the initialization of the framebuffer are perfomed by
*      the Graphics Engine in the particular platform adaptation layer. In this
*      case Graphics Engine maintains the full control and the ownership over
*      the framebuffer. The Graphics Engine can show, hide and reconfigure the
*      framebuffer every time. Therefore the viewport API provides functions
*      which allow the main software or other external software parts to change
*      the framebuffer configuration - in a platform independent way.
*
*      In this use case, the arguments passed to EwInitViewport() are used to
*      create and configure a new framebuffer and finally to arrange it on the
*      display. These configuration can be changed later by EwConfigViewport().
*
*   2. The framebuffer creation and its initialization are tasks of the main
*      software, external frameworks, the operating system, etc. This means,
*      the framebuffer control lies completely beyond the Embedded Wizard. The
*      Graphics Engine is limited to draw into this framebuffer. The ownership
*      and the framebuffer configuration are aspects of the main software or
*      the external framework only.
*
*      In this use case, EwInitViewport() receives a reference to an existing
*      framebuffer or other kind of graphical context where drawing operation
*      will take place and stores it internally. Optionally, EwInitViewport()
*      can create a private, internal off-screen surface which is used as the
*      framebuffer. When screen update is performed, Graphics Engine copies
*      the affected area from the off-screen surface into the framebuffer or
*      display passed to the EwInitViewport() function.
*
*   After a viewport has been initialized, screen updates can be performed. To
*   do this the functions EwBeginUpdate(), EwBeginUpdateArea() and EwEndUpdate()
*   are intended. These functions cover the internal aspects of the framebuffer
*   access, the double buffering, V-Sync, etc.
*
*   If unused anymore, viewports should be freed by EwDoneViewport().
*
* ARGUMENTS:
*   aSize     - Size of the viewport in pixel. This is the area where graphics
*     outputs will occur. Depending on the use case, this parameter determines
*     the size of the framebuffer to create or the size of an already existing
*     framebuffer to use.
*   aExtent   - Position and size, where the created framebuffer should be shown
*     on the screen. If the size of aExtent differs from aSize, the framebuffer
*     content should be scaled in order to fit in the aExtent area.
*     Please note: The area is already expressed in coordinates valid within the
*     target display by taking in account all particular configuration aspects
*     like the default rotation of the surface contents.
*   aOrient   - Orientation hint. The meaning of this parameter depends on the
*     target system. For example, OpenGL target uses aOrient to determine the
*     screen rotation in degrees.
*   aOpacity  - Opacity value for the created framebuffer in the range 0 .. 255.
*     0 -> fully transparent. 255 -> fully opaque.
*   aDisplay1,
*   aDisplay2,
*   aDisplay3 - Platform dependent parameter, where already existing framebuffer
*     or drawing context, etc. are passed.
*   aProc     - Optional callback function to call when viewport update has
*     been done. The callback function can then perform some particular tasks
*     to complete the screen update, etc. If 0, no callback is called.
*
* RETURN VALUE:
*   If successful, the function returns a new viewport otherwise 0 is returned.
*
*******************************************************************************/
XViewport* EwInitViewport_( XPoint aSize, XRect aExtent, XInt32 aOrient,
  XInt32 aOpacity, void* aDisplay1, void* aDisplay2, void* aDisplay3,
  XViewportProc aProc )
{
  XViewport*    port;
  void*         handle = 0;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Ensure the opacity lies in the valid range */
  if ( aOpacity < 0   ) aOpacity = 0;
  if ( aOpacity > 255 ) aOpacity = 255;

  /* Is the viewport size valid? */
  if (( aSize.X <= 0 ) || ( aSize.Y <= 0 ) ||
     (( aExtent.Point2.X - aExtent.Point1.X ) <= 0 ) ||
     (( aExtent.Point2.Y - aExtent.Point1.Y ) <= 0 ))
  {
    EwError( 149 );
    return 0;
  }

  /* Get memory for the new view port */
  if (( port = EwAlloc( sizeof( XViewport ))) == 0 )
  {
    EwError( 26 );
    return 0;
  }

  /* Pass the call to the underlying graphics subsystem where the framebuffer
     should be created or an existing framebuffer should be attached */
  #ifdef EwGfxInitViewport
    EwStartPerfCounter( EwGfxInitViewport );

    #if ( EW_SURFACE_ROTATION == 0 ) || ( EW_SURFACE_ROTATION == 180 )
      handle = EwGfxInitViewport( aSize.X, aSize.Y, aExtent.Point1.X,
                 aExtent.Point1.Y, aExtent.Point2.X - aExtent.Point1.X,
                 aExtent.Point2.Y - aExtent.Point1.Y, aOrient, aOpacity,
                 aDisplay1, aDisplay2, aDisplay3 );
    #endif

    #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
      handle = EwGfxInitViewport( aSize.Y, aSize.X, aExtent.Point1.X,
                 aExtent.Point1.Y, aExtent.Point2.X - aExtent.Point1.X,
                 aExtent.Point2.Y - aExtent.Point1.Y, aOrient, aOpacity,
                 aDisplay1, aDisplay2, aDisplay3 );
    #endif

    EwStopPerfCounter( EwGfxInitViewport );
  #endif

  /* Initialize the viewport structure */
  EwZero( port, sizeof( *port ));

  /* ... and prepare the internal bitmap and surface */
  port->Size                  = aSize;
  port->Bitmap.Frames         = &port->Frames;
  port->Bitmap.Surfaces       = &port->Surfaces;
  port->Bitmap.FrameSize.X    = 0;
  port->Bitmap.FrameSize.Y    = 0;
  port->Bitmap.NoOfFrames     = 1;
  port->Bitmap.NoOfVirtFrames = 1;
  port->Bitmap.NoOfSurfaces   = 1;
  port->Frames.Surface        = &port->Surface;
  port->Surfaces              = &port->Surface;
  #ifdef EW_USE_PIXEL_FORMAT_SCREEN
    port->Bitmap.Format       = EW_PIXEL_FORMAT_SCREEN;
    port->Surface.Format      = EW_PIXEL_FORMAT_SCREEN;
  #else
    port->Bitmap.Format       = EW_PIXEL_FORMAT_NATIVE;
    port->Surface.Format      = EW_PIXEL_FORMAT_NATIVE;
  #endif
  port->Surface.Width         = 0;
  port->Surface.Height        = 0;
  port->Surface.Owned         = 1;
  port->Surface.Used          = 1;
  port->UpdateArea.Point1.X   = 0;
  port->UpdateArea.Point1.Y   = 0;
  port->UpdateArea.Point2.X   = 0;
  port->UpdateArea.Point2.Y   = 0;
  port->Proc                  = aProc;
  port->Display1              = aDisplay1;
  port->Display2              = aDisplay2;
  port->Display3              = aDisplay3;
  port->Handle                = handle;

  /* The underlying graphics subsystem couldn't establish the framebuffer */
  if ( !handle )
  {
    EwFree( port );
    EwError( 150 );
    port = 0;
  }

  /* Track the RAM usage */
  EwResourcesMemory += sizeof( XViewport );

  /* Also track the max. memory pressure */
  if ( EwResourcesMemory > EwResourcesMemoryPeak )
    EwResourcesMemoryPeak = EwResourcesMemory;

  if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
    EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

  return port;
}


EW_INSTRUMENT_FUNC( EwInitViewport, XViewport*, ( XPoint aSize, XRect aExtent,
  XInt32 aOrient, XInt32 aOpacity, void* aDisplay1, void* aDisplay2,
  void* aDisplay3, XViewportProc aProc ), ( aSize, aExtent, aOrient,
  aOpacity, aDisplay1, aDisplay2, aDisplay3, aProc ))


/*******************************************************************************
* FUNCTION:
*   EwDoneViewport
*
* DESCRIPTION:
*   The function EwDoneViewport() deinitializes the given viewport. If necessary
*   the previously created framebuffers are hidden and video memory is released.
*
* ARGUMENTS:
*   aViewport - Viewport to deinitialize.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwDoneViewport_( XViewport* aViewport )
{
  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  if ( !aViewport )
    return;

  /* Ensure there are no pending operations for the viewport */
  if ( aViewport->Valid )
    EwEndUpdate( aViewport, EwNewRect( 0, 0, 0, 0 ));

  #ifdef EwGfxDoneViewport
    EwStartPerfCounter( EwGfxDoneViewport );
    EwGfxDoneViewport( aViewport->Handle );
    EwStopPerfCounter( EwGfxDoneViewport );
  #endif

  EwFree( aViewport );

  /* Track the RAM usage */
  EwResourcesMemory -= sizeof( XViewport );
}


EW_INSTRUMENT_VOID_FUNC( EwDoneViewport, ( XViewport* aViewport ), ( aViewport ))


/*******************************************************************************
* FUNCTION:
*   EwConfigViewport
*
* DESCRIPTION:
*   The function EwConfigViewport() changes the configuration of the viewport.
*   Generally, the function can modify the settings of framebuffers belonging
*   to the viewport.
*
* ARGUMENTS:
*   aViewport - Viewport to reconfigure its framebuffer.
*   aPos      - Position, where the framebuffer should be shown on the screen.
*     Please note: The value is already expressed in coordinates valid within
*     the target display by taking in account all particular configuration
*     aspects like the default rotation of the surface contents.
*   aOpacity  - Opacity value for the framebuffer in the range 0 .. 255.
*     0 -> fully transparent. 255 -> fully opaque.
*
* RETURN VALUE:
*   If successful, the function returns != 0. If the used framebuffer doesn't
*   belong to the viewport, or if it doesn't support the parameter modification
*   0 is returned.
*
*******************************************************************************/
int EwConfigViewport_( XViewport* aViewport, XPoint aPos, XInt32 aOpacity )
{
  int result = 0;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  #ifndef EwGfxConfigViewport
    EW_UNUSED_ARG( aOpacity );
    EW_UNUSED_ARG( aPos );
  #endif

  if ( !aViewport )
    return result;

  /* Ensure there are no pending operations for the viewport */
  if ( aViewport->Valid )
    EwEndUpdate( aViewport, EwNewRect( 0, 0, 0, 0 ));

  #ifdef EwGfxConfigViewport
    EwStartPerfCounter( EwGfxConfigViewport );
    result = EwGfxConfigViewport( aViewport->Handle, aPos.X, aPos.Y, aOpacity );
    EwStopPerfCounter( EwGfxConfigViewport );
  #endif

  return result;
}


EW_INSTRUMENT_FUNC( EwConfigViewport, int, ( XViewport* aViewport, XPoint aPos,
  XInt32 aOpacity ), ( aViewport, aPos, aOpacity ))


/*******************************************************************************
* FUNCTION:
*   EwBeginUpdate
*
* DESCRIPTION:
*   The function EwBeginUpdate() initiates the screen update cycle for the given
*   viewport and provides access to its framebuffer via the returned temporary
*   bitmap.
*
*   The returned bitmap covers the framebuffer and can serve as the destination
*   in all drawing operations until the function EwEndUpdate() is called. Due to
*   the platform specific framebuffer limitations the returned bitmap may not be
*   used as source in the drawing operations.
*
*   The bitmap remains valid until EwEndUpdate() is called. Afterwards it may
*   not be used.
*
* ARGUMENTS:
*   aViewport - Viewport to begin the drawing operations.
*
* RETURN VALUE:
*   If successful, the function returns a temporary bitmap providing the access
*   to the framebuffer of the viewport.
*
*******************************************************************************/
XBitmap* EwBeginUpdate_( XViewport* aViewport )
{
  void*         handle = 0;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Ignore if a screen update cycle is currently active */
  if ( !aViewport || aViewport->Valid )
  {
    EwErrorPD( 151, aViewport, 0 );
    return 0;
  }

  /* Get the framebuffer or display object to update */
  #ifdef EwGfxBeginUpdate
    EwStartPerfCounter( EwGfxBeginUpdate );
    handle = EwGfxBeginUpdate( aViewport->Handle );
    EwStopPerfCounter( EwGfxBeginUpdate );
  #endif

  /* Couldn't obtain the access to the framebuffer */
  if ( !handle )
  {
    EwErrorPD( 154, aViewport, 0 );
    return 0;
  }

  /* Cover the returned framebuffer within the internal bitmap object */
  aViewport->Surface.Handle      = handle;
  aViewport->Valid               = 1;
  aViewport->Bitmap.FrameSize    = aViewport->Size;
  aViewport->Surface.Width       = (short)aViewport->Size.X;
  aViewport->Surface.Height      = (short)aViewport->Size.Y;
  aViewport->UpdateArea.Point1.X = 0;
  aViewport->UpdateArea.Point1.Y = 0;
  aViewport->UpdateArea.Point2   = aViewport->Size;

  EW_EVAL_INC_3( 16 );

  return &aViewport->Bitmap;
}


EW_INSTRUMENT_FUNC( EwBeginUpdate, XBitmap*, ( XViewport* aViewport ),
  ( aViewport ))


/*******************************************************************************
* FUNCTION:
*   EwBeginUpdateArea
*
* DESCRIPTION:
*   The function EwBeginUpdateArea() initiates the screen update cycle for the
*   given viewport and provides access to the specified area of its framebuffer
*   via the returned temporary bitmap.
*
*   The returned bitmap covers the area of the framebuffer and can serve as the
*   destination in all drawing operations until the function EwEndUpdate() is
*   called. Due to the platform specific framebuffer limitations the returned
*   bitmap may not be used as source in the drawing operations.
*
*   The bitmap remains valid until EwEndUpdate() is called. Afterwards it may
*   not be used.
*
* ARGUMENTS:
*   aViewport - Viewport to begin the drawing operations.
*   aArea     - Area to update relative to the top-left corner of the viewport.
*
* RETURN VALUE:
*   If successful, the function returns a temporary bitmap providing the access
*   to the framebuffer of the viewport.
*
*******************************************************************************/
XBitmap* EwBeginUpdateArea_( XViewport* aViewport, XRect aArea )
{
  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Ignore if a screen update cycle is currently active */
  if ( !aViewport || aViewport->Valid )
  {
    EwErrorPD( 152, aViewport, 0 );
    return 0;
  }

  /* Limit the update area to the area of the viewport */
  aArea = EwIntersectRect( aArea, EwNewRect( 0, 0,
                           aViewport->Size.X, aViewport->Size.Y ));

  /* Nothing to do? */
  if ( EwIsRectEmpty( aArea ))
    return 0;

  /* Get the framebuffer or display object to update */
  #ifdef EwGfxBeginUpdateArea
  {
    void*         handle = 0;

    EwStartPerfCounter( EwGfxBeginUpdateArea );

    #if EW_SURFACE_ROTATION == 0
      handle = EwGfxBeginUpdateArea( aViewport->Handle,
        aArea.Point1.X, aArea.Point1.Y,
        aArea.Point2.X - aArea.Point1.X, aArea.Point2.Y - aArea.Point1.Y );
    #endif

    #if EW_SURFACE_ROTATION == 90
      handle = EwGfxBeginUpdateArea( aViewport->Handle,
        aViewport->Size.Y - aArea.Point2.Y, aArea.Point1.X,
        aArea.Point2.Y - aArea.Point1.Y, aArea.Point2.X - aArea.Point1.X );
    #endif

    #if EW_SURFACE_ROTATION == 180
      handle = EwGfxBeginUpdateArea( aViewport->Handle,
        aViewport->Size.X - aArea.Point2.X, aViewport->Size.Y - aArea.Point2.Y,
        aArea.Point2.X - aArea.Point1.X, aArea.Point2.Y - aArea.Point1.Y );
    #endif

    #if EW_SURFACE_ROTATION == 270
      handle = EwGfxBeginUpdateArea( aViewport->Handle,
        aArea.Point1.Y, aViewport->Size.X - aArea.Point2.X,
        aArea.Point2.Y - aArea.Point1.Y, aArea.Point2.X - aArea.Point1.X );
    #endif

    EwStopPerfCounter( EwGfxBeginUpdateArea );

    /* Couldn't obtain the access to the framebuffer */
    if ( !handle )
    {
      EwErrorPD( 155, aViewport, 0 );
      return 0;
    }

    /* Cover the returned framebuffer within the internal bitmap object */
    aViewport->Surface.Handle     = handle;
    aViewport->Valid              = 1;
    aViewport->Bitmap.FrameSize.X = aArea.Point2.X - aArea.Point1.X;
    aViewport->Bitmap.FrameSize.Y = aArea.Point2.Y - aArea.Point1.Y;
    aViewport->Surface.Width      = (short)aViewport->Bitmap.FrameSize.X;
    aViewport->Surface.Height     = (short)aViewport->Bitmap.FrameSize.Y;
    aViewport->UpdateArea         = aArea;

    EW_EVAL_INC_3( 1000 );

    return &aViewport->Bitmap;
  }
  #else
  {
    EwError( 186 );
    return 0;
  }
  #endif
}


EW_INSTRUMENT_FUNC( EwBeginUpdateArea, XBitmap*, ( XViewport* aViewport,
  XRect aArea ), ( aViewport, aArea ))


/*******************************************************************************
* FUNCTION:
*   EwEndUpdate
*
* DESCRIPTION:
*   The function EwEndUpdate() finalizes the screen update cycle for the given
*   viewport. This function flushes all outstanding drawing operations, updates
*   the framebuffer state and frees the temporary bitmap object provided by the
*   previous EwBeginUpdate() or EwBeginUpdateArea() function call.
*
*   Depending on the particular platform double buffering is used or the update
*   is synchronized with the V-Sync.
*
*   If there was a callback function specified during the initialization of the
*   viewport, the function is called at the fin of the update cycle.
*
* ARGUMENTS:
*   aViewport - Viewport to finalize the drawing operations.
*   aArea     - Area modified by the update relative to the top-left corner of
*     the viewport.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwEndUpdate_( XViewport* aViewport, XRect aArea )
{
  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Ignore if no screen update cycle is active */
  if ( !aViewport || !aViewport->Valid )
  {
    EwErrorPD( 153, aViewport, 0 );
    return;
  }

  /* Limit the update area to the viewport area */
  aArea = EwIntersectRect( aArea, aViewport->UpdateArea );

  EW_EVAL_INC_4();

  /* Flush the still outstanding drawing operations for the framebuffer */
  EwWaitForSurface( &aViewport->Surface, 0 );

  EW_EVAL_INC_5();

  #ifdef EwGfxEndUpdate
    EwStartPerfCounter( EwGfxEndUpdate );

    #if EW_SURFACE_ROTATION == 0
      EwGfxEndUpdate( aViewport->Handle,
        aArea.Point1.X, aArea.Point1.Y,
        aArea.Point2.X - aArea.Point1.X, aArea.Point2.Y - aArea.Point1.Y );
    #endif

    #if EW_SURFACE_ROTATION == 90
      EwGfxEndUpdate( aViewport->Handle,
        aViewport->Size.Y - aArea.Point2.Y, aArea.Point1.X,
        aArea.Point2.Y - aArea.Point1.Y, aArea.Point2.X - aArea.Point1.X );
    #endif

    #if EW_SURFACE_ROTATION == 180
      EwGfxEndUpdate( aViewport->Handle,
        aViewport->Size.X - aArea.Point2.X, aViewport->Size.Y - aArea.Point2.Y,
        aArea.Point2.X - aArea.Point1.X, aArea.Point2.Y - aArea.Point1.Y );
    #endif

    #if EW_SURFACE_ROTATION == 270
      EwGfxEndUpdate( aViewport->Handle,
        aArea.Point1.Y, aViewport->Size.X - aArea.Point2.X,
        aArea.Point2.Y - aArea.Point1.Y, aArea.Point2.X - aArea.Point1.X );
    #endif

    EwStopPerfCounter( EwGfxEndUpdate );
  #endif

  /* If specified inform the owner of the viewport about the performed flip */
  if ( aViewport->Proc )
  {
    EwStartPerfCounter( ViewportCallback );
    ((XViewportProc)aViewport->Proc)( aViewport, aViewport->Handle,
                     aViewport->Display1, aViewport->Display2,
                     aViewport->Display3, aArea );
    EwStopPerfCounter( ViewportCallback );
  }

  /* Discard surfaces which are not in use anymore and not intended to remain
     in the cache. */
  EwCleanSurfaceCache( 0 );

  /* Finish the framebuffer access */
  aViewport->Bitmap.FrameSize.X  = 0;
  aViewport->Bitmap.FrameSize.Y  = 0;
  aViewport->Surface.Width       = 0;
  aViewport->Surface.Height      = 0;
  aViewport->Surface.Handle      = 0;
  aViewport->UpdateArea.Point1.X = 0;
  aViewport->UpdateArea.Point1.Y = 0;
  aViewport->UpdateArea.Point2.X = 0;
  aViewport->UpdateArea.Point2.Y = 0;
  aViewport->Valid               = 0;

  /* Count the update cycles. */
  EwUpdateCycle++;
}


EW_INSTRUMENT_VOID_FUNC( EwEndUpdate, ( XViewport* aViewport, XRect aArea ),
  ( aViewport, aArea ))


/*******************************************************************************
* FUNCTION:
*   EwFillRectangle
*
* DESCRIPTION:
*   The function EwFillRectangle() fills the rectangular area aDstRect of the
*   bitmap aDst with a color gradient specified by the four color parameters
*   aColorTL .. aColorBL.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst        - Destination bitmap.
*   aDstFrameNo - Frame within the destination bitmap affected by the drawing
*     operation.
*   aClipRect   - Area to limit the drawing operation (Relative to the top-left
*     corner of the destination bitmap frame).
*   aDstRect    - Area to fill with the color gradient (Relative to the top-
*     left corner of the destination bitmap frame).
*   aColorTL,
*   aColorTR,
*   aColorBR,
*   aColorBL    - Color values corresponding to the four corners of aDstRect.
*   aBlend      - If != 0, the drawn pixel will be alpha-blended with the pixel
*     in the background.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwFillRectangle_( XBitmap* aDst, XInt32 aDstFrameNo, XRect aClipRect,
  XRect aDstRect, XColor aColorTL, XColor aColorTR, XColor aColorBR,
  XColor aColorBL, XBool aBlend )
{
  XBitmapFrame*   dst     = MapBitmapFrame( aDst, aDstFrameNo );
  XFillRectangle* data;
  XIssue*         issue;
  XTask*          task;
  int             x1, y1, x2, y2;
  unsigned int    colorTL = PACK_COLOR( aColorTL, aDst );
  unsigned int    colorTR = PACK_COLOR( aColorTR, aDst );
  unsigned int    colorBL = PACK_COLOR( aColorBL, aDst );
  unsigned int    colorBR = PACK_COLOR( aColorBR, aDst );

  /* Only screen/native surfaces are allowed as the destination */
  if ( !dst || (( dst->Surface->Format != EW_PIXEL_FORMAT_SCREEN ) &&
                ( dst->Surface->Format != EW_PIXEL_FORMAT_NATIVE )))
  {
    EwErrorPD( 156, aDst, aDstFrameNo );
    return;
  }

  /* The support for Native surface as destination is disabled. */
  #ifdef EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION
    if ( dst->Surface->Format == EW_PIXEL_FORMAT_NATIVE )
    {
      EwErrorPD( 351, aDst, aDstFrameNo );
      return;
    }
  #endif

  /* Bitmaps loaded from resources can't be modified by drawing operations */
  if ( dst->Surface->Tag1 || dst->Surface->Tag2 )
  {
    EwErrorPD( 341, aDst, aDstFrameNo );
    return;
  }

  /* The support for color gradients is disabled. */
  #ifdef EW_DONT_USE_GRADIENTS
    if ( IS_LINEAR_GRADIENT4( colorTL, colorTR, colorBL, colorBR ) ||
         IS_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
    {
      EwError( 371 );
      return;
    }
  #endif

  /* Limit the fill area to the frame boundary and to the clipping area */
  x1 = MAX3( aClipRect.Point1.X, aDstRect.Point1.X, 0 );
  y1 = MAX3( aClipRect.Point1.Y, aDstRect.Point1.Y, 0 );
  x2 = MIN3( aClipRect.Point2.X, aDstRect.Point2.X, aDst->FrameSize.X );
  y2 = MIN3( aClipRect.Point2.Y, aDstRect.Point2.Y, aDst->FrameSize.Y );

  /* Nothing to do? */
  if (( x2 <= x1 ) || ( y2 <= y1 ) ||
      ( aBlend && IS_TRANSPARENT4( colorTL, colorTR, colorBL, colorBR )))
    return;

  /* Full opaque fill operation doesn't need the alpha blending */
  if ( aBlend && IS_OPAQUE4( colorTL, colorTR, colorBL, colorBR ))
    aBlend = 0;

  /* Start the preparation of a new drawing operation */
  if (( issue = EwInitIssue( dst->Surface )) == 0 )
  {
    EwErrorPD( 124, aDst, 0 );
    return;
  }

  /* Get a storage area for the drawings parameter */
  data = EwAllocTaskData( issue, sizeof( *data ));
  data->DstX1     = (short)( aDstRect.Point1.X + dst->Origin.X );
  data->DstY1     = (short)( aDstRect.Point1.Y + dst->Origin.Y );
  data->DstX2     = (short)( aDstRect.Point2.X + dst->Origin.X );
  data->DstY2     = (short)( aDstRect.Point2.Y + dst->Origin.Y );
  data->Colors[0] = colorTL;
  data->Colors[1] = colorTR;
  data->Colors[2] = colorBR;
  data->Colors[3] = colorBL;

  /* Enqueue the drawing operation by the issue */
  task = EwAllocTask( issue, 0 );
  task->Token     = EW_TASKID_FILL_RECTANGLE;
  task->Data      = data;
  task->X1        = (short)( x1 + dst->Origin.X );
  task->Y1        = (short)( y1 + dst->Origin.Y );
  task->X2        = (short)( x2 + dst->Origin.X );
  task->Y2        = (short)( y2 + dst->Origin.Y );
  task->Flags     = (short)( EW_TASK_ENTIRE_AREA |
                           ( aBlend? EW_TASK_ALPHABLEND : 0 ));

  /* What to do with the 4 colors? */
  #ifndef EW_DONT_USE_GRADIENTS
    if ( IS_LINEAR_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
      task->Flags |= EW_TASK_LINEAR_GRADIENT;
    else if ( IS_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
      task->Flags |= EW_TASK_GRADIENT;
    else
  #endif
    task->Flags |= EW_TASK_SOLID;

  /* Close the preparation. This may flush the issue */
  EwDoneIssue( dst->Surface );
}


EW_INSTRUMENT_VOID_FUNC( EwFillRectangle, ( XBitmap* aDst, XInt32 aDstFrameNo,
  XRect aClipRect, XRect aDstRect, XColor aColorTL, XColor aColorTR,
  XColor aColorBR, XColor aColorBL, XBool aBlend ), ( aDst, aDstFrameNo,
  aClipRect, aDstRect, aColorTL, aColorTR, aColorBR, aColorBL, aBlend ))


/*******************************************************************************
* FUNCTION:
*   EwFillRoundedRectangle
*
* DESCRIPTION:
*   The function EwFillRoundedRectangle() fills the area aDstRect of the bitmap
*   aDst with a color gradient specified by the four color parameters aColorTL
*   .. aColorBL. All corners of the resulting rectangular shape are rounded by
*   radius specified in the parameter aRadiusXXX.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst        - Destination bitmap.
*   aDstFrameNo - Frame within the destination bitmap affected by the drawing
*     operation.
*   aClipRect   - Area to limit the drawing operation (Relative to the top-left
*     corner of the destination bitmap frame).
*   aDstRect    - Area to fill with the color gradient (Relative to the top-
*     left corner of the destination bitmap frame).
*   aRadiusTL,
*   aRadiusTR,
*   aRadiusBR,
*   aRadiusBL   - Corner radius in pixel.
*   aColorTL,
*   aColorTR,
*   aColorBR,
*   aColorBL    - Color values corresponding to the four corners of aDstRect.
*   aBlend      - If != 0, the drawn pixel will be alpha-blended with the pixel
*     in the background.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwFillRoundedRectangle_( XBitmap* aDst, XInt32 aDstFrameNo, XRect aClipRect,
  XRect aDstRect, XInt32 aRadiusTL, XInt32 aRadiusTR, XInt32 aRadiusBR,
  XInt32 aRadiusBL, XColor aColorTL, XColor aColorTR, 
  XColor aColorBR, XColor aColorBL, XBool aBlend )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XPath*   path;
    XBitmap* bitmap;
    XPoint   size;
    XPoint   size2;
    XRect    clip;
    XPoint   srcPos;
    int      noOfEdgesTL;
    int      noOfEdgesTR;
    int      noOfEdgesBR;
    int      noOfEdgesBL;
    int      maxRadius;
    int      minEdge = MIN( aDstRect.Point2.X - aDstRect.Point1.X,
                            aDstRect.Point2.Y - aDstRect.Point1.Y );

    /* Absolutely nothing to do */
    if (( aBlend && !( aColorTL.Alpha | aColorTR.Alpha | aColorBL.Alpha |
          aColorBR.Alpha )) || ( minEdge <= 0 ) ||
        ( aClipRect.Point2.X <= aClipRect.Point1.X ) || 
        ( aClipRect.Point2.Y <= aClipRect.Point1.Y ))
      return;

    /* The rounded corners may not exceed the size of a single rectangle edge */
    aRadiusTL = MIN( aRadiusTL, minEdge / 2 );
    aRadiusTR = MIN( aRadiusTR, minEdge / 2 );
    aRadiusBL = MIN( aRadiusBL, minEdge / 2 );
    aRadiusBR = MIN( aRadiusBR, minEdge / 2 );
    aRadiusTL = MAX( aRadiusTL, 0 );
    aRadiusTR = MAX( aRadiusTR, 0 );
    aRadiusBL = MAX( aRadiusBL, 0 );
    aRadiusBR = MAX( aRadiusBR, 0 );

    /* Estimate the biggest radius - it affects the size of shape to rasterize */
    maxRadius = MAX( aRadiusTL, aRadiusTR );
    maxRadius = MAX( maxRadius, aRadiusBR );
    maxRadius = MAX( maxRadius, aRadiusBL );

    /* Display as a regular rectangle? */
    if ( !maxRadius )
    {
      EwFillRectangle_( aDst, aDstFrameNo, aClipRect, aDstRect, aColorTL, aColorTR, 
                        aColorBR, aColorBL, aBlend );
      return;
    }

    /* Calculate the size of the bitmap */
    size. X = size. Y = maxRadius;
    size2.X = size2.Y = maxRadius * 2;

    /* Lookup in the 'Rounded Rectangle Bitmap Cache'. If possible, reuse an
       already created bitmap */
    bitmap = FindCachedRoundedRectangleBitmap( size2.X, size2.Y, 0, aRadiusTL,
               aRadiusTR, aRadiusBR, aRadiusBL, 0 );

    /* The bitmap does not exist in the cache. Rasterize the bitmap now. */
    if ( !bitmap )
    {
      /* Estimate the necessary number of edges for the corners. Note, the
         bigger the radius of an arc, the longer can be the edges it is
         composed of. */
      noOfEdgesTL = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( aRadiusTL + 1 ))));
      noOfEdgesTR = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( aRadiusTR + 1 ))));
      noOfEdgesBR = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( aRadiusBR + 1 ))));
      noOfEdgesBL = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( aRadiusBL + 1 ))));

      /* Prepare a path describing a circle */
      if ( !( path = EwCreatePath( 1 )))
        return;

      /* Reserve memory for the path */
      if ( !EwInitSubPath( path, 0, noOfEdgesTL + noOfEdgesTR + noOfEdgesBR + 
                           noOfEdgesBL + 5 ))
      {
        EwFreePath( path );
        return;
      }

      /* Store in the path the shape of a rectangle with four arcs. Start with
         the bottom right corner. */
      EwAddSubPathArc( path, 0, (float)( maxRadius - aRadiusBR ), 
                     (float)( maxRadius - aRadiusBR ), (float)aRadiusBR,
                     (float)aRadiusBR, 0.0f, 90.0f, noOfEdgesBR );
      EwAddSubPathArc( path, 0, (float)( aRadiusBL - maxRadius ), 
                     (float)( maxRadius - aRadiusBL ), (float)aRadiusBL,
                     (float)aRadiusBL, 90.0f, 180.0f, noOfEdgesBL );
      EwAddSubPathArc( path, 0, (float)( aRadiusTL - maxRadius ), 
                     (float)( aRadiusTL - maxRadius ), (float)aRadiusTL,
                     (float)aRadiusTL, 180.0f, 270.0f, noOfEdgesTL );
      EwAddSubPathArc( path, 0, (float)( maxRadius - aRadiusTR ), 
                     (float)( aRadiusTR - maxRadius ), (float)aRadiusTR,
                     (float)aRadiusTR, 270.0f, 360.0f, noOfEdgesTR );
      EwCloseSubPath( path, 0 );

      /* Raster a bitmap containing the circle */
      if ( !( bitmap = EwGetBitmapFromFillPath( size2, path, 0, size, 1, 0 )))
      {
        EwFreePath( path );
        return;
      }

      /* The path object is not needed anymore */
      EwFreePath( path );
    }

    /* Fill the area at the top edge of the rounded rectangle between the
       top corners */
    clip          = aClipRect;
    clip.Point1.X = MAX( clip.Point1.X, aDstRect.Point1.X + maxRadius );
    clip.Point2.X = MIN( clip.Point2.X, aDstRect.Point2.X - maxRadius );
    clip.Point2.Y = MIN( clip.Point2.Y, aDstRect.Point1.Y + maxRadius );
    EwFillRectangle( aDst, aDstFrameNo, clip, aDstRect, aColorTL, aColorTR, 
                     aColorBR, aColorBL, aBlend );

    /* Fill the area in the center of the rounded rectangle */
    clip          = aClipRect;
    clip.Point1.Y = MAX( clip.Point1.Y, aDstRect.Point1.Y + maxRadius );
    clip.Point2.Y = MIN( clip.Point2.Y, aDstRect.Point2.Y - maxRadius );
    EwFillRectangle( aDst, aDstFrameNo, clip, aDstRect, aColorTL, aColorTR, 
                     aColorBR, aColorBL, aBlend );

    /* Fill the area at the bottom edge of the rounded rectangle between the
       bottom corners */
    clip          = aClipRect;
    clip.Point1.X = MAX( clip.Point1.X, aDstRect.Point1.X + maxRadius );
    clip.Point2.X = MIN( clip.Point2.X, aDstRect.Point2.X - maxRadius );
    clip.Point1.Y = MAX( clip.Point1.Y, aDstRect.Point2.Y - maxRadius );
    EwFillRectangle( aDst, aDstFrameNo, clip, aDstRect, aColorTL, aColorTR, 
                     aColorBR, aColorBL, aBlend );

    /* Display the top-left corner */
    clip          = aClipRect;
    clip.Point2.X = MIN( clip.Point2.X, aDstRect.Point1.X + maxRadius );
    clip.Point2.Y = MIN( clip.Point2.Y, aDstRect.Point1.Y + maxRadius );
    srcPos.X      = 0;
    srcPos.Y      = 0;
    EwCopyBitmap( aDst, bitmap, aDstFrameNo, 0, clip, aDstRect, srcPos, aColorTL,
                  aColorTR, aColorBR, aColorBL, aBlend );

    /* Display the top-right corner */
    clip          = aClipRect;
    clip.Point1.X = MAX( clip.Point1.X, aDstRect.Point2.X - maxRadius );
    clip.Point2.Y = MIN( clip.Point2.Y, aDstRect.Point1.Y + maxRadius );
    srcPos.X      = maxRadius * 2 - ( aDstRect.Point2.X - aDstRect.Point1.X );
    srcPos.Y      = 0;
    EwCopyBitmap( aDst, bitmap, aDstFrameNo, 0, clip, aDstRect, srcPos, aColorTL,
                  aColorTR, aColorBR, aColorBL, aBlend );

    /* Display the bottom-left corner */
    clip          = aClipRect;
    clip.Point2.X = MIN( clip.Point2.X, aDstRect.Point1.X + maxRadius );
    clip.Point1.Y = MAX( clip.Point1.Y, aDstRect.Point2.Y - maxRadius );
    srcPos.X      = 0;
    srcPos.Y      = maxRadius * 2 - ( aDstRect.Point2.Y - aDstRect.Point1.Y );
    EwCopyBitmap( aDst, bitmap, aDstFrameNo, 0, clip, aDstRect, srcPos, aColorTL,
                  aColorTR, aColorBR, aColorBL, aBlend );

    /* Display the bottom-right corner */
    clip          = aClipRect;
    clip.Point1.X = MAX( clip.Point1.X, aDstRect.Point2.X - maxRadius );
    clip.Point1.Y = MAX( clip.Point1.Y, aDstRect.Point2.Y - maxRadius );
    srcPos.X      = maxRadius * 2 - ( aDstRect.Point2.X - aDstRect.Point1.X );
    srcPos.Y      = maxRadius * 2 - ( aDstRect.Point2.Y - aDstRect.Point1.Y );
    EwCopyBitmap( aDst, bitmap, aDstFrameNo, 0, clip, aDstRect, srcPos, aColorTL,
                  aColorTR, aColorBR, aColorBL, aBlend );

    /* Retain the bitmap in the 'Rounded Rectangle Cache' */
    CacheRoundedRectangleBitmap( bitmap, size2.X, size2.Y, 0, aRadiusTL, aRadiusTR,
                                 aRadiusBR, aRadiusBL, 0 );
  #else
    EW_UNUSED_ARG( aDst        );
    EW_UNUSED_ARG( aDstFrameNo );
    EW_UNUSED_ARG( aClipRect   );
    EW_UNUSED_ARG( aDstRect    );
    EW_UNUSED_ARG( aRadiusTL   );
    EW_UNUSED_ARG( aRadiusTR   );
    EW_UNUSED_ARG( aRadiusBR   );
    EW_UNUSED_ARG( aRadiusBL   );
    EW_UNUSED_ARG( aColorTL    );
    EW_UNUSED_ARG( aColorTR    );
    EW_UNUSED_ARG( aColorBR    );
    EW_UNUSED_ARG( aColorBL    );
    EW_UNUSED_ARG( aBlend      );
    EwError( 461 );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwFillRoundedRectangle, ( XBitmap* aDst, 
  XInt32 aDstFrameNo, XRect aClipRect, XRect aDstRect, XInt32 aRadiusTL,
  XInt32 aRadiusTR, XInt32 aRadiusBR, XInt32 aRadiusBL, XColor aColorTL, 
  XColor aColorTR, XColor aColorBR, XColor aColorBL, XBool aBlend ), ( aDst,
  aDstFrameNo, aClipRect, aDstRect, aRadiusTL, aRadiusTR, aRadiusBR, aRadiusBL,
  aColorTL, aColorTR, aColorBR, aColorBL, aBlend ))


/*******************************************************************************
* FUNCTION:
*   EwDrawBorder
*
* DESCRIPTION:
*   The function EwDrawBorder() draws a rectangle border within the area
*   aDstRect of the bitmap aDst with a color gradient specified by the four
*   color parameters aColorTL .. aColorBL. The parameter aEdgeWidth determines
*   the width of the border's edge.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst        - Destination bitmap.
*   aDstFrameNo - Frame within the destination bitmap affected by the drawing
*     operation.
*   aClipRect   - Area to limit the drawing operation (Relative to the top-left
*     corner of the destination bitmap frame).
*   aDstRect    - Area to draw the border with color gradient (Relative to the
*     top-left corner of the destination bitmap frame).
*   aEdgeWidth  - The width of the border in pixel.
*   aColorTL,
*   aColorTR,
*   aColorBR,
*   aColorBL    - Color values corresponding to the four corners of aDstRect.
*   aBlend      - If != 0, the drawn pixel will be alpha-blended with the pixel
*     in the background.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwDrawBorder_( XBitmap* aDst, XInt32 aDstFrameNo, XRect aClipRect,
  XRect aDstRect, XInt32 aEdgeWidth, XColor aColorTL, XColor aColorTR,
  XColor aColorBR, XColor aColorBL, XBool aBlend )
{
  XRect dstRect;
  XRect clipRect;

  /* Nothing to draw */
  if ( aEdgeWidth <= 0 )
    return;

  /* The edge is so big that the entire aDstRect area appears filled */
  if ((( aEdgeWidth * 2 ) >= ( aDstRect.Point2.X - aDstRect.Point1.X )) ||
      (( aEdgeWidth * 2 ) >= ( aDstRect.Point2.Y - aDstRect.Point1.Y )))
  {
    EwFillRectangle_( aDst, aDstFrameNo, aClipRect, aDstRect, aColorTL,
                      aColorTR, aColorBR, aColorBL, aBlend );
    return;
  }

  /* Calculate the area for the upper border edge */
  dstRect = aDstRect;
  dstRect.Point2.Y = aDstRect.Point1.Y + aEdgeWidth;
  clipRect = EwIntersectRect( aClipRect, dstRect );

  /* Draw the upper edge of the border */
  EwFillRectangle( aDst, aDstFrameNo, clipRect, aDstRect, aColorTL,
                   aColorTR, aColorBR, aColorBL, aBlend );

  /* Calculate the area for the bottom border edge */
  dstRect = aDstRect;
  dstRect.Point1.Y = aDstRect.Point2.Y - aEdgeWidth;
  clipRect = EwIntersectRect( aClipRect, dstRect );

  /* Draw the upper edge of the border */
  EwFillRectangle( aDst, aDstFrameNo, clipRect, aDstRect, aColorTL,
                   aColorTR, aColorBR, aColorBL, aBlend );

  /* Calculate the area for the left border edge */
  dstRect = aDstRect;
  dstRect.Point1.Y = aDstRect.Point1.Y + aEdgeWidth;
  dstRect.Point2.Y = aDstRect.Point2.Y - aEdgeWidth;
  dstRect.Point2.X = aDstRect.Point1.X + aEdgeWidth;
  clipRect = EwIntersectRect( aClipRect, dstRect );

  /* Draw the upper edge of the border */
  EwFillRectangle( aDst, aDstFrameNo, clipRect, aDstRect, aColorTL,
                   aColorTR, aColorBR, aColorBL, aBlend );

  /* Calculate the area for the left border edge */
  dstRect.Point1.X = aDstRect.Point2.X - aEdgeWidth;
  dstRect.Point2.X = aDstRect.Point2.X;
  clipRect = EwIntersectRect( aClipRect, dstRect );

  /* Draw the upper edge of the border */
  EwFillRectangle( aDst, aDstFrameNo, clipRect, aDstRect, aColorTL,
                   aColorTR, aColorBR, aColorBL, aBlend );
}


EW_INSTRUMENT_VOID_FUNC( EwDrawBorder, ( XBitmap* aDst, XInt32 aDstFrameNo,
  XRect aClipRect, XRect aDstRect, XInt32 aEdgeWidth, XColor aColorTL,
  XColor aColorTR, XColor aColorBR, XColor aColorBL, XBool aBlend ),
  ( aDst, aDstFrameNo, aClipRect, aDstRect, aEdgeWidth, aColorTL, aColorTR,
    aColorBR, aColorBL, aBlend ))


/*******************************************************************************
* FUNCTION:
*   EwDrawRoundedBorder
*
* DESCRIPTION:
*   The function EwDrawRoundedBorder() draws a border within the area aDstRect
*   of the bitmap aDst with a color gradient specified by the four parameters
*   aColorTL .. aColorBL. The parameter aEdgeWidth determines the width of the
*   border's edge. All corners of the resulting rectangular border are rounded
*   by radius specified in the parameter aRadiusXXX.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst        - Destination bitmap.
*   aDstFrameNo - Frame within the destination bitmap affected by the drawing
*     operation.
*   aClipRect   - Area to limit the drawing operation (Relative to the top-left
*     corner of the destination bitmap frame).
*   aDstRect    - Area to draw the border with color gradient (Relative to the
*     top-left corner of the destination bitmap frame).
*   aEdgeWidth  - The width of the border in pixel.
*   aRadiusTL,
*   aRadiusTR,
*   aRadiusBR,
*   aRadiusBL   - Corner radius in pixel.
*   aColorTL,
*   aColorTR,
*   aColorBR,
*   aColorBL    - Color values corresponding to the four corners of aDstRect.
*   aBlend      - If != 0, the drawn pixel will be alpha-blended with the pixel
*     in the background.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwDrawRoundedBorder_( XBitmap* aDst, XInt32 aDstFrameNo, XRect aClipRect,
  XRect aDstRect, XInt32 aEdgeWidth, XInt32 aRadiusTL, XInt32 aRadiusTR,
  XInt32 aRadiusBR, XInt32 aRadiusBL, XColor aColorTL, XColor aColorTR, 
  XColor aColorBR, XColor aColorBL, XBool aBlend )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XPath*   path;
    XBitmap* bitmap;
    XPoint   size;
    XPoint   size2;
    XRect    clip;
    XPoint   srcPos;
    int      noOfEdgesOTL;
    int      noOfEdgesOTR;
    int      noOfEdgesOBR;
    int      noOfEdgesOBL;
    int      noOfEdgesITL;
    int      noOfEdgesITR;
    int      noOfEdgesIBR;
    int      noOfEdgesIBL;
    int      maxRadius;
    int      minEdge = MIN( aDstRect.Point2.X - aDstRect.Point1.X,
                            aDstRect.Point2.Y - aDstRect.Point1.Y );

    /* Absolutely nothing to do */
    if (( aBlend && !( aColorTL.Alpha | aColorTR.Alpha | aColorBL.Alpha |
          aColorBR.Alpha )) || ( minEdge <= 0 ) || ( aEdgeWidth <= 0 ) ||
        ( aClipRect.Point2.X <= aClipRect.Point1.X ) || 
        ( aClipRect.Point2.Y <= aClipRect.Point1.Y ))
      return;

    /* The rounded corners may not exceed the size of a single rectangle egde */
    aRadiusTL = MIN( aRadiusTL, minEdge / 2 );
    aRadiusTR = MIN( aRadiusTR, minEdge / 2 );
    aRadiusBL = MIN( aRadiusBL, minEdge / 2 );
    aRadiusBR = MIN( aRadiusBR, minEdge / 2 );
    aRadiusTL = MAX( aRadiusTL, 0 );
    aRadiusTR = MAX( aRadiusTR, 0 );
    aRadiusBL = MAX( aRadiusBL, 0 );
    aRadiusBR = MAX( aRadiusBR, 0 );

    /* Estimate the biggest radius - it affects the size of shape to rasterize */
    maxRadius = MAX( aRadiusTL, aRadiusTR );
    maxRadius = MAX( maxRadius, aRadiusBR );
    maxRadius = MAX( maxRadius, aRadiusBL );

    /* Display as a regular border? */
    if ( !maxRadius )
    {
      EwDrawBorder_( aDst, aDstFrameNo, aClipRect, aDstRect, aEdgeWidth, aColorTL,
                     aColorTR, aColorBR, aColorBL, aBlend );
      return;
    }

    /* The edge is so big that the entire aDstRect area appears filled */
    if ((( aEdgeWidth * 2 ) >= ( aDstRect.Point2.X - aDstRect.Point1.X )) ||
        (( aEdgeWidth * 2 ) >= ( aDstRect.Point2.Y - aDstRect.Point1.Y )))
    {
      EwFillRoundedRectangle_( aDst, aDstFrameNo, aClipRect, aDstRect, aRadiusTL,
                               aRadiusTR, aRadiusBR, aRadiusBL, aColorTL, 
                               aColorTR, aColorBR, aColorBL, aBlend );
      return;
    }

    size. X = size. Y = maxRadius;
    size2.X = size2.Y = maxRadius * 2;

    /* Lookup in the 'Rounded Rectangle Bitmap Cache'. If possible, reuse an
       already created bitmap */
    bitmap = FindCachedRoundedRectangleBitmap( size2.X, size2.Y, aEdgeWidth,
                               aRadiusTL, aRadiusTR, aRadiusBR, aRadiusBL, 0 );

    /* The bitmap does not exist in the cache. Rasterize the bitmap now. */
    if ( !bitmap )
    {
      /* Inner radius for the corner */
      int radiusITL = MAX( aRadiusTL - aEdgeWidth, 0 );
      int radiusITR = MAX( aRadiusTR - aEdgeWidth, 0 );
      int radiusIBR = MAX( aRadiusBR - aEdgeWidth, 0 );
      int radiusIBL = MAX( aRadiusBL - aEdgeWidth, 0 );

      /* Estimate the necessary number of edges for the corners. Note, the
         bigger the radius of an arc, the longer can be the edges it is
         composed of. */
      noOfEdgesOTL = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( aRadiusTL + 1 ))));
      noOfEdgesOTR = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( aRadiusTR + 1 ))));
      noOfEdgesOBR = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( aRadiusBR + 1 ))));
      noOfEdgesOBL = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( aRadiusBL + 1 ))));
      noOfEdgesITL = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( radiusITL + 1 ))));
      noOfEdgesITR = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( radiusITR + 1 ))));
      noOfEdgesIBR = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( radiusIBR + 1 ))));
      noOfEdgesIBL = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( radiusIBL + 1 ))));

      /* Prepare a path describing a border */
      if ( !( path = EwCreatePath( 2 )))
        return;

      /* Reserve memory for the outer edge ... */
      if ( !EwInitSubPath( path, 0, noOfEdgesOTL + noOfEdgesOTR + noOfEdgesOBR + 
                           noOfEdgesOBL + 5 ))
      {
        EwFreePath( path );
        return;
      }

      /* ... and the inner edge */
      if (( maxRadius > aEdgeWidth ) && !EwInitSubPath( path, 1, noOfEdgesITL +
                           noOfEdgesITR + noOfEdgesIBR + noOfEdgesIBL + 5 ))
      {
        EwFreePath( path );
        return;
      }

      /* Store in the path the outer edge of a rectangle with four arcs. Start
         with the bottom right corner. */
      EwAddSubPathArc( path, 0, (float)( maxRadius - aRadiusBR ), 
                     (float)( maxRadius - aRadiusBR ), (float)aRadiusBR,
                     (float)aRadiusBR, 0.0f, 90.0f, noOfEdgesOBR );
      EwAddSubPathArc( path, 0, (float)( aRadiusBL - maxRadius ), 
                     (float)( maxRadius - aRadiusBL ), (float)aRadiusBL,
                     (float)aRadiusBL, 90.0f, 180.0f, noOfEdgesOBL );
      EwAddSubPathArc( path, 0, (float)( aRadiusTL - maxRadius ), 
                     (float)( aRadiusTL - maxRadius ), (float)aRadiusTL,
                     (float)aRadiusTL, 180.0f, 270.0f, noOfEdgesOTL );
      EwAddSubPathArc( path, 0, (float)( maxRadius - aRadiusTR ), 
                     (float)( aRadiusTR - maxRadius ), (float)aRadiusTR,
                     (float)aRadiusTR, 270.0f, 360.0f, noOfEdgesOTR );
      EwCloseSubPath( path, 0 );

      /* Store in the path the shape of the inner rectangle with the rounded
         corners */
      if ( maxRadius > aEdgeWidth )
      {
        EwAddSubPathArc( path, 1, (float)( maxRadius - aEdgeWidth - radiusIBR ),
                       (float)( maxRadius - aEdgeWidth - radiusIBR ),
                       (float)radiusIBR, (float)radiusIBR, 0.0f, 90.0f,
                       noOfEdgesIBR );
        EwAddSubPathArc( path, 1, (float)( radiusIBL + aEdgeWidth - maxRadius ),
                       (float)( maxRadius - aEdgeWidth - radiusIBL ), 
                       (float)radiusIBL, (float)radiusIBL, 90.0f, 180.0f,
                       noOfEdgesIBL );
        EwAddSubPathArc( path, 1, (float)( radiusITL + aEdgeWidth - maxRadius ),
                       (float)( radiusITL + aEdgeWidth - maxRadius ),
                       (float)radiusITL, (float)radiusITL, 180.0f, 270.0f,
                       noOfEdgesITL );
        EwAddSubPathArc( path, 1, (float)( maxRadius - aEdgeWidth - radiusITR ),
                       (float)( radiusITR + aEdgeWidth - maxRadius ),
                       (float)radiusITR, (float)radiusITR, 270.0f, 360.0f,
                       noOfEdgesITR );
        EwCloseSubPath( path, 1 );
      }

      /* Raster a bitmap containing the circle */
      if ( !( bitmap = EwGetBitmapFromFillPath( size2, path, 0, size, 1, 0 )))
      {
        EwFreePath( path );
        return;
      }

      /* The path object is not needed anymore */
      EwFreePath( path );
    }

    /* Fill the area at the top edge of the rounded border between the
       top corners */
    clip          = aClipRect;
    clip.Point1.X = MAX( clip.Point1.X, aDstRect.Point1.X + maxRadius );
    clip.Point2.X = MIN( clip.Point2.X, aDstRect.Point2.X - maxRadius );
    clip.Point2.Y = MIN( clip.Point2.Y, aDstRect.Point1.Y + maxRadius );
    EwDrawBorder( aDst, aDstFrameNo, clip, aDstRect, aEdgeWidth, aColorTL, 
                  aColorTR, aColorBR, aColorBL, aBlend );

    /* Fill the area in the center of the rounded border */
    clip          = aClipRect;
    clip.Point1.Y = MAX( clip.Point1.Y, aDstRect.Point1.Y + maxRadius );
    clip.Point2.Y = MIN( clip.Point2.Y, aDstRect.Point2.Y - maxRadius );
    EwDrawBorder( aDst, aDstFrameNo, clip, aDstRect, aEdgeWidth, aColorTL,
                  aColorTR, aColorBR, aColorBL, aBlend );

    /* Fill the area at the bottom edge of the rounded border between the
       bottom corners */
    clip          = aClipRect;
    clip.Point1.X = MAX( clip.Point1.X, aDstRect.Point1.X + maxRadius );
    clip.Point2.X = MIN( clip.Point2.X, aDstRect.Point2.X - maxRadius );
    clip.Point1.Y = MAX( clip.Point1.Y, aDstRect.Point2.Y - maxRadius );
    EwDrawBorder( aDst, aDstFrameNo, clip, aDstRect, aEdgeWidth, aColorTL,
                  aColorTR, aColorBR, aColorBL, aBlend );

    /* Display the top-left corner */
    clip          = aClipRect;
    clip.Point2.X = MIN( clip.Point2.X, aDstRect.Point1.X + maxRadius );
    clip.Point2.Y = MIN( clip.Point2.Y, aDstRect.Point1.Y + maxRadius );
    srcPos.X      = 0;
    srcPos.Y      = 0;
    EwCopyBitmap( aDst, bitmap, aDstFrameNo, 0, clip, aDstRect, srcPos, aColorTL,
                  aColorTR, aColorBR, aColorBL, aBlend );

    /* Display the top-right corner */
    clip          = aClipRect;
    clip.Point1.X = MAX( clip.Point1.X, aDstRect.Point2.X - maxRadius );
    clip.Point2.Y = MIN( clip.Point2.Y, aDstRect.Point1.Y + maxRadius );
    srcPos.X      = maxRadius * 2 - ( aDstRect.Point2.X - aDstRect.Point1.X );
    srcPos.Y      = 0;
    EwCopyBitmap( aDst, bitmap, aDstFrameNo, 0, clip, aDstRect, srcPos, aColorTL,
                  aColorTR, aColorBR, aColorBL, aBlend );

    /* Display the bottom-left corner */
    clip          = aClipRect;
    clip.Point2.X = MIN( clip.Point2.X, aDstRect.Point1.X + maxRadius );
    clip.Point1.Y = MAX( clip.Point1.Y, aDstRect.Point2.Y - maxRadius );
    srcPos.X      = 0;
    srcPos.Y      = maxRadius * 2 - ( aDstRect.Point2.Y - aDstRect.Point1.Y );
    EwCopyBitmap( aDst, bitmap, aDstFrameNo, 0, clip, aDstRect, srcPos, aColorTL,
                  aColorTR, aColorBR, aColorBL, aBlend );

    /* Display the bottom-right corner */
    clip          = aClipRect;
    clip.Point1.X = MAX( clip.Point1.X, aDstRect.Point2.X - maxRadius );
    clip.Point1.Y = MAX( clip.Point1.Y, aDstRect.Point2.Y - maxRadius );
    srcPos.X      = maxRadius * 2 - ( aDstRect.Point2.X - aDstRect.Point1.X );
    srcPos.Y      = maxRadius * 2 - ( aDstRect.Point2.Y - aDstRect.Point1.Y );
    EwCopyBitmap( aDst, bitmap, aDstFrameNo, 0, clip, aDstRect, srcPos, aColorTL,
                  aColorTR, aColorBR, aColorBL, aBlend );

    /* Retain the bitmap in the 'Rounded Rectangle Cache' */
    CacheRoundedRectangleBitmap( bitmap, size2.X, size2.Y, aEdgeWidth, aRadiusTL,
                                 aRadiusTR, aRadiusBR, aRadiusBL, 0 );
  #else
    EW_UNUSED_ARG( aDst        );
    EW_UNUSED_ARG( aDstFrameNo );
    EW_UNUSED_ARG( aClipRect   );
    EW_UNUSED_ARG( aDstRect    );
    EW_UNUSED_ARG( aEdgeWidth  );
    EW_UNUSED_ARG( aRadiusTL   );
    EW_UNUSED_ARG( aRadiusTR   );
    EW_UNUSED_ARG( aRadiusBR   );
    EW_UNUSED_ARG( aRadiusBL   );
    EW_UNUSED_ARG( aColorTL    );
    EW_UNUSED_ARG( aColorTR    );
    EW_UNUSED_ARG( aColorBR    );
    EW_UNUSED_ARG( aColorBL    );
    EW_UNUSED_ARG( aBlend      );
    EwError( 462 );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwDrawRoundedBorder, ( XBitmap* aDst, 
  XInt32 aDstFrameNo, XRect aClipRect, XRect aDstRect, XInt32 aEdgeWidth,
  XInt32 aRadiusTL, XInt32 aRadiusTR, XInt32 aRadiusBR, XInt32 aRadiusBL,
  XColor aColorTL, XColor aColorTR, XColor aColorBR, XColor aColorBL,
  XBool aBlend ), ( aDst, aDstFrameNo, aClipRect, aDstRect, aEdgeWidth,
  aRadiusTL, aRadiusTR, aRadiusBR, aRadiusBL, aColorTL, aColorTR, aColorBR,
  aColorBL, aBlend ))


/*******************************************************************************
* FUNCTION:
*   EwDrawRoundedShadow
*
* DESCRIPTION:
*   The function EwDrawRoundedShadow() renders within the bitmap aDst a shadow
*   around a rectangle aDstRect with color determined by aColor. All corners of
*   the rectangular shape can be rounded by radius specified in the parameter
*   aRadiusXXX. The parameter aBlurRadius determines the shadow radius.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
*   Please note, the function uses a box blur algorithm without involving any
*   GPU to perform the blur operation. This guarantees similar results on all
*   target systems with the blur radius not being restricted to any discrete
*   value.
*
* ARGUMENTS:
*   aDst        - Destination bitmap.
*   aDstFrameNo - Frame within the destination bitmap affected by the drawing
*     operation.
*   aClipRect   - Area to limit the drawing operation (Relative to the top-left
*     corner of the destination bitmap frame).
*   aDstRect    - Area identifying the rectangular shape to draw the shadow
*     around it (Relative to the top-left corner of the destination bitmap
*     frame).
*   aRadiusTL,
*   aRadiusTR,
*   aRadiusBR,
*   aRadiusBL   - Corner radius in pixel for the rectangular shape.
*   aBlurRadius - Determines the intensity of the blur filter effect. The
*     value is expressed in pixel as radius to blur the corresponding shape.
*     If the value is <= 0, no blur filter is applied. The blur radius is
*     limited to 64 pixel.
*   aColor      - Color value to draw the shadow.
*   aBlend      - If != 0, the drawn pixel will be alpha-blended with the pixel
*     in the background.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwDrawRoundedShadow_( XBitmap* aDst, XInt32 aDstFrameNo,
  XRect aClipRect, XRect aDstRect, XInt32 aRadiusTL, XInt32 aRadiusTR,
  XInt32 aRadiusBR, XInt32 aRadiusBL, XInt32 aBlurRadius, XColor aColor,
  XBool aBlend )
{
  #if !defined EW_DONT_USE_PATH_FUNCTIONS && !defined EW_DONT_USE_BLUR_FUNCTIONS
    XPath*   path;
    XBitmap* bitmap;
    XPoint   size;
    XPoint   srcPos;
    XRect    dstRect;
    XRect    srcRect;
    int      noOfEdgesTL;
    int      noOfEdgesTR;
    int      noOfEdgesBR;
    int      noOfEdgesBL;
    int      maxRadius;
    int      l, r, t, b;
    int      sw, sh;
    int      dw      = aDstRect.Point2.X - aDstRect.Point1.X;
    int      dh      = aDstRect.Point2.Y - aDstRect.Point1.Y;
    int      minEdge = MIN( dw, dh );

    /* Absolutely nothing to do */
    if (( aBlend && !aColor.Alpha ) || ( minEdge <= 0 ) ||
        ( aClipRect.Point2.X <= aClipRect.Point1.X ) || 
        ( aClipRect.Point2.Y <= aClipRect.Point1.Y ))
      return;

    /* Limit to supported values */
    if ( aBlurRadius <  0 ) aBlurRadius = 0;
    if ( aBlurRadius > 64 ) aBlurRadius = 64;

    /* Display without any blur? */
    if ( aBlurRadius <= 0 )
    {
      EwFillRoundedRectangle_( aDst, aDstFrameNo, aClipRect, aDstRect, aRadiusTL,
                               aRadiusTR, aRadiusBR, aRadiusBL, aColor, aColor, 
                               aColor, aColor, aBlend );
      return;
    }

    /* The rounded corners may not exceed the size of a single rectangle edge */
    aRadiusTL = MIN( aRadiusTL, minEdge / 2 );
    aRadiusTR = MIN( aRadiusTR, minEdge / 2 );
    aRadiusBL = MIN( aRadiusBL, minEdge / 2 );
    aRadiusBR = MIN( aRadiusBR, minEdge / 2 );
    aRadiusTL = MAX( aRadiusTL, 0 );
    aRadiusTR = MAX( aRadiusTR, 0 );
    aRadiusBL = MAX( aRadiusBL, 0 );
    aRadiusBR = MAX( aRadiusBR, 0 );

    /* Estimate the biggest radius - it affects the size of shape to rasterize */
    maxRadius = MAX( aRadiusTL, aRadiusTR );
    maxRadius = MAX( maxRadius, aRadiusBR );
    maxRadius = MAX( maxRadius, aRadiusBL );

    /* As source for the shadow a rounded rectangle is rasterized. Estimate the
       size if this rectangle. The rectangle should not exceed the destination
       area. If destination area is big add max 8 pixel for the middle area to
       tile the edges */
    l  = r = maxRadius + aBlurRadius;
    t  = b = maxRadius + aBlurRadius;
    l  =     MIN( l, dw / 2 );
    r  =     MIN( r, dw / 2 );
    t  =     MIN( t, dh / 2 );
    b  =     MIN( b, dh / 2 );
    sw =     MIN( l + r + 8, dw );
    sh =     MIN( t + b + 8, dh );

    /* If possible enlarge the areas enclosing the blurred corners. This
       produces better looking results. */
    if (( l + r ) < sw ) l++;
    if (( l + r ) < sw ) r++;
    if (( t + b ) < sh ) t++;
    if (( t + b ) < sh ) b++;
    if (( l + r ) < sw ) l++;
    if (( l + r ) < sw ) r++;
    if (( t + b ) < sh ) t++;
    if (( t + b ) < sh ) b++;

    /* The size of the bitmaps used to store the rounded rectangle and its blurred
       version */
    size.X   = sw + ( aBlurRadius * 2 );
    size.Y   = sh + ( aBlurRadius * 2 );
    srcPos.X = srcPos.Y = aBlurRadius;

    /* Lookup in the 'Rounded Rectangle Bitmap Cache'. If possible, reuse an
       already created bitmap */
    bitmap = FindCachedRoundedRectangleBitmap( size.X, size.Y, 0, aRadiusTL,
               aRadiusTR, aRadiusBR, aRadiusBL, aBlurRadius );

    /* The bitmap does not exist in the cache. Rasterize the bitmap now. */
    if ( !bitmap )
    {
      /* Estimate the necessary number of edges for the corners. Note, the
         bigger the radius of an arc, the longer can be the edges it is
         composed of. */
      noOfEdgesTL = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( aRadiusTL + 1 ))));
      noOfEdgesTR = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( aRadiusTR + 1 ))));
      noOfEdgesBR = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( aRadiusBR + 1 ))));
      noOfEdgesBL = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( aRadiusBL + 1 ))));

      /* Prepare a path describing a circle */
      if ( !( path = EwCreatePath( 1 )))
        return;

      /* Reserve memory for the path. Note, the path is constructured from 4 arc
         connected by straight line segments. Take in account the additional 
         segements as well as an additional segment to close the path. */
      if ( !EwInitSubPath( path, 0, noOfEdgesTL + noOfEdgesTR + noOfEdgesBR + 
                           noOfEdgesBL + 5 ))
      {
        EwFreePath( path );
        return;
      }

      /* Store in the path the shape of a rectangle with four arcs. Start with
         the bottom right corner. */
      EwAddSubPathArc( path, 0, (float)( sw - aRadiusBR ),
                     (float)( sh - aRadiusBR ), (float)aRadiusBR,
                     (float)aRadiusBR, 0.0f, 90.0f, noOfEdgesBR );
      EwAddSubPathArc( path, 0, (float)aRadiusBL, (float)( sh - aRadiusBL ),
                     (float)aRadiusBL, (float)aRadiusBL, 90.0f, 180.0f,
                     noOfEdgesBL );
      EwAddSubPathArc( path, 0, (float)aRadiusTL, (float)aRadiusTL,
                     (float)aRadiusTL, (float)aRadiusTL, 180.0f, 270.0f,
                     noOfEdgesTL );
      EwAddSubPathArc( path, 0, (float)( sw - aRadiusTR ), (float)aRadiusTR,
                     (float)aRadiusTR, (float)aRadiusTR, 270.0f, 360.0f,
                     noOfEdgesTR );
      EwCloseSubPath( path, 0 );

      /* Raster a bitmap containing the rounded rectangle shape being blurred */
      if ( !( bitmap = EwGetBlurredBitmapFromFillPath( size, path, 0, srcPos, 1, 0,
                                                       aBlurRadius )))
      {
        EwFreePath( path );
        return;
      }

      /* The path object is not needed anymore */
      EwFreePath( path );
    }

    /* Fill the area at the top edge of the shadow between the top corners. Note,
       we calculate with copy additional 4 pixel from the blurred image to avoid
       abrupt color changes */
    dstRect           = aDstRect;
    dstRect.Point1.X += l;
    dstRect.Point2.X -= r;
    dstRect.Point2.Y  = dstRect.Point1.Y + t;
    dstRect.Point1.Y -= aBlurRadius;
    srcPos.X          = 0;
    srcPos.Y          = 0;
    srcRect.Point1.X  = aBlurRadius + l;
    srcRect.Point2.X  = size.X - aBlurRadius - r;
    srcRect.Point1.Y  = 0;
    srcRect.Point2.Y  = aBlurRadius + t;
    EwTileBitmap( aDst, bitmap, aDstFrameNo, 0, aClipRect, dstRect, srcRect,
                  srcPos, aColor, aColor, aColor, aColor, aBlend );

    /* Fill the area at the bottom edge of the shadow between the bottom corners */
    dstRect           = aDstRect;
    dstRect.Point1.X += l;
    dstRect.Point2.X -= r;
    dstRect.Point1.Y  = dstRect.Point2.Y - b;
    dstRect.Point2.Y += aBlurRadius;
    srcRect.Point1.X  = aBlurRadius + l;
    srcRect.Point2.X  = size.X - aBlurRadius - r;
    srcRect.Point1.Y  = size.Y - aBlurRadius - b;
    srcRect.Point2.Y  = size.Y;
    EwTileBitmap( aDst, bitmap, aDstFrameNo, 0, aClipRect, dstRect, srcRect,
                  srcPos, aColor, aColor, aColor, aColor, aBlend );

    /* Fill the area at the left edge of the shadow between the left corners */
    dstRect           = aDstRect;
    dstRect.Point2.X  = dstRect.Point1.X + l;
    dstRect.Point1.X -= aBlurRadius;
    dstRect.Point1.Y += t;
    dstRect.Point2.Y -= b;
    srcRect.Point1.X  = 0;
    srcRect.Point2.X  = aBlurRadius + l;
    srcRect.Point1.Y  = aBlurRadius + t;
    srcRect.Point2.Y  = size.Y - aBlurRadius - b;
    EwTileBitmap( aDst, bitmap, aDstFrameNo, 0, aClipRect, dstRect, srcRect,
                  srcPos, aColor, aColor, aColor, aColor, aBlend );

    /* Fill the area at the right edge of the shadow between the right corners */
    dstRect           = aDstRect;
    dstRect.Point1.X  = dstRect.Point2.X - r;
    dstRect.Point2.X += aBlurRadius;
    dstRect.Point1.Y += t;
    dstRect.Point2.Y -= b;
    srcRect.Point1.X  = size.X - aBlurRadius - r;
    srcRect.Point2.X  = size.X;
    srcRect.Point1.Y  = aBlurRadius + t;
    srcRect.Point2.Y  = size.Y - aBlurRadius - b;
    EwTileBitmap( aDst, bitmap, aDstFrameNo, 0, aClipRect, dstRect, srcRect,
                  srcPos, aColor, aColor, aColor, aColor, aBlend );

    /* Display the top-left corner */
    dstRect           = aDstRect;
    dstRect.Point2.X  = dstRect.Point1.X + l;
    dstRect.Point1.X -= aBlurRadius;
    dstRect.Point2.Y  = dstRect.Point1.Y + t;
    dstRect.Point1.Y -= aBlurRadius;
    srcPos.X          = 0;
    srcPos.Y          = 0;
    EwCopyBitmap( aDst, bitmap, aDstFrameNo, 0, aClipRect, dstRect, srcPos,
                  aColor, aColor, aColor, aColor, aBlend );

    /* Display the top-right corner */
    dstRect           = aDstRect;
    dstRect.Point1.X  = dstRect.Point2.X - r;
    dstRect.Point2.X += aBlurRadius;
    dstRect.Point2.Y  = dstRect.Point1.Y + t;
    dstRect.Point1.Y -= aBlurRadius;
    srcPos.X          = size.X - aBlurRadius - r;
    srcPos.Y          = 0;
    EwCopyBitmap( aDst, bitmap, aDstFrameNo, 0, aClipRect, dstRect, srcPos,
                  aColor, aColor, aColor, aColor, aBlend );

    /* Display the bottom-left corner */
    dstRect           = aDstRect;
    dstRect.Point2.X  = dstRect.Point1.X + l;
    dstRect.Point1.X -= aBlurRadius;
    dstRect.Point1.Y  = dstRect.Point2.Y - b;
    dstRect.Point2.Y += aBlurRadius;
    srcPos.X          = 0;
    srcPos.Y          = size.Y - aBlurRadius - b;
    EwCopyBitmap( aDst, bitmap, aDstFrameNo, 0, aClipRect, dstRect, srcPos,
                  aColor, aColor, aColor, aColor, aBlend );

    /* Display the bottom-right corner */
    dstRect           = aDstRect;
    dstRect.Point1.X  = dstRect.Point2.X - r;
    dstRect.Point2.X += aBlurRadius;
    dstRect.Point1.Y  = dstRect.Point2.Y - b;
    dstRect.Point2.Y += aBlurRadius;
    srcPos.X          = size.X - aBlurRadius - r;
    srcPos.Y          = size.Y - aBlurRadius - b;
    EwCopyBitmap( aDst, bitmap, aDstFrameNo, 0, aClipRect, dstRect, srcPos,
                  aColor, aColor, aColor, aColor, aBlend );

    /* Finally fill the middle area of the shadow with a rectangle */
    dstRect           = aDstRect;
    dstRect.Point1.X += l;
    dstRect.Point2.X -= r;
    dstRect.Point1.Y += t;
    dstRect.Point2.Y -= b;
    EwFillRectangle( aDst, aDstFrameNo, aClipRect, dstRect, aColor, aColor, 
                     aColor, aColor, aBlend );

    /* Retain the bitmap in the 'Rounded Rectangle Cache' */
    CacheRoundedRectangleBitmap( bitmap, size.X, size.Y, 0, aRadiusTL,
                                 aRadiusTR, aRadiusBR, aRadiusBL, aBlurRadius );
  #else
    EW_UNUSED_ARG( aDst        );
    EW_UNUSED_ARG( aDstFrameNo );
    EW_UNUSED_ARG( aClipRect   );
    EW_UNUSED_ARG( aDstRect    );
    EW_UNUSED_ARG( aRadiusTL   );
    EW_UNUSED_ARG( aRadiusTR   );
    EW_UNUSED_ARG( aRadiusBR   );
    EW_UNUSED_ARG( aRadiusBL   );
    EW_UNUSED_ARG( aBlurRadius );
    EW_UNUSED_ARG( aColor      );
    EW_UNUSED_ARG( aBlend      );
    EwError( 463 );
  #endif /* !EW_DONT_USE_PATH_FUNCTIONS && !EW_DONT_USE_BLUR_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwDrawRoundedShadow, ( XBitmap* aDst, 
  XInt32 aDstFrameNo, XRect aClipRect, XRect aDstRect, XInt32 aRadiusTL,
  XInt32 aRadiusTR, XInt32 aRadiusBR, XInt32 aRadiusBL, XInt32 aBlurRadius,
  XColor aColor, XBool aBlend ), ( aDst, aDstFrameNo, aClipRect, aDstRect,
  aRadiusTL, aRadiusTR, aRadiusBR, aRadiusBL, aBlurRadius, aColor, aBlend ))


/*******************************************************************************
* FUNCTION:
*   EwCreateGradient
*
* DESCRIPTION:
*   The function EwCreateGradient() creates a new color gradient able to store
*   aMaxNoOfStops color stops. The color stops are interpolated along a straight
*   line segment or circle chord depending on the type of the gradient. To
*   specify the gradient type use the functions EwSetGradientTypeLinear() and
*   EwSetGradienTypeRadial().
*
*   Before the gradient can be used, all color stops have to be assigned by the
*   function EwAddGradientColorStop() or EwSetGradientColorStop().
*
* ARGUMENTS:
*   aMaxNoOfStops - Max. no of colors the gradient should describe. The valid 
*     range is between 2 and 256.
*
* RETURN VALUE:
*   If successful, the function returns a pointer to the newly created gradient.
*   Otherwise the function returns 0.
*
*******************************************************************************/
XColorGradient* EwCreateGradient_( XInt32 aMaxNoOfStops )
{
  #if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
    int             size = sizeof( XColorGradient ) + ( aMaxNoOfStops - 1 ) * 
                           sizeof( XColorStop );
    XColorGradient* gradient;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Is the number of stops valid? */
    if (( aMaxNoOfStops < 2 ) || ( aMaxNoOfStops > 256 ))
      return 0;

    /* Reserve memory for the gradient */
    do
      gradient = EwAlloc( size );
    while ( !gradient && EwImmediateReclaimMemory( 68 ));

    /* Was not able to reserve memory for the new gradient. */
    if ( !gradient )
    {
      EwError( 68 );
      return 0;
    }

    /* Initialize the just created gradient */
    EwZero( gradient, size );
    gradient->MaxNoOfStops = aMaxNoOfStops;

    /* Track the memory usage */
    EwResourcesMemory += size;

    /* Also track the max. memory pressure */
    if ( EwResourcesMemory > EwResourcesMemoryPeak )
      EwResourcesMemoryPeak = EwResourcesMemory;

    if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
      EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

    return gradient;
  #else
    EW_UNUSED_ARG( aMaxNoOfStops );
    EwError( 521 );
    return 0;
  #endif /* EW_DONT_USE_GRADIENTS && EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwCreateGradient, XColorGradient*, (  XInt32 aMaxNoOfStops ),
  ( aMaxNoOfStops ))


/*******************************************************************************
* FUNCTION:
*   EwFreeGradient
*
* DESCRIPTION:
*   The function EwFreeGradient() frees the memory occupied by the gradient.
*
* ARGUMENTS:
*   aGradient - Pointer to the gradient to free.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwFreeGradient_( XColorGradient* aGradient )
{
  #if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    if ( !aGradient )
      return;

    /* Take in account the memory occupied by the XColorGradient object and the
       list of color stops */
    EwResourcesMemory -= sizeof( XColorGradient ) + ( aGradient->MaxNoOfStops - 1 ) *
                         sizeof( XColorStop );

    aGradient->NoOfStops = 0;

    /* ... and finally the path object itself */
    EwFree( aGradient );
  #else
    EW_UNUSED_ARG( aGradient );
  #endif /* EW_DONT_USE_GRADIENTS && EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwFreeGradient, ( XColorGradient* aGradient ),
  ( aGradient ))


/*******************************************************************************
* FUNCTION:
*   EwSetGradientTypeLinear
*
* DESCRIPTION:
*   The function EwSetGradientTypeLinear() configures the given gradient as a
*   linear gradient intended to interpolate the color values along a straight
*   line segment.
*
*   If the coordinates aStart and aEnd are equal, the gradient is considered
*   as invalid. Using this gradient will result in no screen contents being
*   drawn.
*
* ARGUMENTS:
*   aGradient - Pointer to the gradient to configure.
*   aStart    - Start position of a straight line defining the gradient.
*   aEnd      - End position of a straight line defining the gradient.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwSetGradientTypeLinear_( XColorGradient* aGradient, XPoint aStart,
  XPoint aEnd )
{
  #if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    if ( !aGradient )
      return;

    /* Invalid gradient line */
    if (( aStart.X == aEnd.X ) && ( aStart.Y == aEnd.Y ))
    {
      aGradient->IsLinear  = 0;
      aGradient->IsRadial  = 0;
      return;
    }

    aGradient->IsLinear  = 1;
    aGradient->IsRadial  = 0;
    aGradient->Start     = aStart;
    aGradient->End       = aEnd;
    aGradient->Radius    = 0;
    aGradient->Matrix[0] = 1.0f;
    aGradient->Matrix[1] = 0.0f;
    aGradient->Matrix[2] = 0.0f;
    aGradient->Matrix[3] = 1.0f;
  #else
    EW_UNUSED_ARG( aGradient );
    EW_UNUSED_ARG( aStart );
    EW_UNUSED_ARG( aEnd );
  #endif /* EW_DONT_USE_GRADIENTS && EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwSetGradientTypeLinear, ( XColorGradient* aGradient,
  XPoint aStart, XPoint aEnd ), ( aGradient, aStart, aEnd ))


/*******************************************************************************
* FUNCTION:
*   EwSetGradientTypeRadial
*
* DESCRIPTION:
*   The function EwSetGradientTypeRadial() configures the given gradient as a
*   radial gradient intended to interpolate the color values along the circle
*   chord.
*
*   If the radius is <= 0, the gradient is considered as invalid. Using this
*   gradient will result in no screen contents being drawn.
*
* ARGUMENTS:
*   aGradient - Pointer to the gradient to configure.
*   aCenter   - Center position of a circle defining the gradient's start.
*   aRadius   - Radius of the circle defining the end position of the
*     gradient relative to its center position.
*   aMatrix0,
*   aMatrix3  - 2x2 component matrix describing scaling/rotation of the radius
*     around the center of the gradient.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwSetGradientTypeRadial_( XColorGradient* aGradient, XPoint aCenter,
  XInt32 aRadius, XFloat aMatrix0, XFloat aMatrix1, XFloat aMatrix2,
  XFloat aMatrix3 )
{
  #if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    if ( !aGradient )
      return;

    /* Invalid gradient radius */
    if ( aRadius <= 0 )
    {
      aGradient->IsRadial  = 0;
      aGradient->IsLinear  = 0;
      return;
    }

    aGradient->IsRadial  = 1;
    aGradient->IsLinear  = 0;
    aGradient->Start     = aCenter;
    aGradient->Radius    = aRadius;
    aGradient->End       = aCenter;
    aGradient->Matrix[0] = aMatrix0;
    aGradient->Matrix[1] = aMatrix1;
    aGradient->Matrix[2] = aMatrix2;
    aGradient->Matrix[3] = aMatrix3;
  #else
    EW_UNUSED_ARG( aGradient );
    EW_UNUSED_ARG( aCenter );
    EW_UNUSED_ARG( aRadius );
    EW_UNUSED_ARG( aMatrix0 );
    EW_UNUSED_ARG( aMatrix1 );
    EW_UNUSED_ARG( aMatrix2 );
    EW_UNUSED_ARG( aMatrix3 );
  #endif /* EW_DONT_USE_GRADIENTS && EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwSetGradientTypeRadial, ( XColorGradient* aGradient,
  XPoint aCenter, XInt32 aRadius, XFloat aMatrix0, XFloat aMatrix1,
  XFloat aMatrix2, XFloat aMatrix3 ), ( aGradient, aCenter, aRadius, aMatrix0,
  aMatrix1, aMatrix2, aMatrix3 ))


/*******************************************************************************
* FUNCTION:
*   EwAddGradientColorStop
*
* DESCRIPTION:
*   The function EwAddGradientColorStop() configures a new color stop in the
*   given color gradient.
*
* ARGUMENTS:
*   aGradient - Pointer to the gradient to store the color value.
*   aOffset   - Offset in range 0.0 .. 1.0 to assign to the color stop.
*   aColor    - Color value corresponding to the color stop.
*
* RETURN VALUE:
*   The number of the corresponding color stop or -1 if there is no free entry
*   in gradient to store the new color stop. The returned number can be used to
*   modify the color stop retrospectively by function EwSetGradientColorStop().
*
*******************************************************************************/
XInt32 EwAddGradientColorStop_( XColorGradient* aGradient, XFloat aOffset,
  XColor aColor )
{
  #if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* No free entry in the gradient */
    if ( !aGradient || ( aGradient->NoOfStops == aGradient->MaxNoOfStops ))
      return -1;

    /* Limit the offset */
    if ( aOffset < 0.0f ) aOffset = 0.0f;
    if ( aOffset > 1.0f ) aOffset = 1.0f;

    /* Store the value in the gradient */
    aGradient->Stops[ aGradient->NoOfStops ].Offset = aOffset;
    aGradient->Stops[ aGradient->NoOfStops ].Color  = aColor;

    return aGradient->NoOfStops++;
  #else
    EW_UNUSED_ARG( aGradient );
    EW_UNUSED_ARG( aOffset );
    EW_UNUSED_ARG( aColor );
    return -1;
  #endif /* EW_DONT_USE_GRADIENTS && EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwAddGradientColorStop, XInt32, ( XColorGradient* aGradient,
  XFloat aOffset, XColor aColor ), ( aGradient, aOffset, aColor ))


/*******************************************************************************
* FUNCTION:
*   EwSetGradientColorStop
*
* DESCRIPTION:
*   The function EwSetGradientColorStop() configures a color stop in the given
*   color gradient.
*
* ARGUMENTS:
*   aGradient    - Pointer to the gradient to store the color value.
*   aColorStopNo - Index of the color stop to configure. The first color stop
*     has the index 0. The total number of color stops is determined at the
*     creation time of the gradient in the invocation of EwCreateGradient().
*   aOffset      - Offset in range 0.0 .. 1.0 to assign to the color stop.
*   aColor       - Color value corresponding to the color stop.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwSetGradientColorStop_( XColorGradient* aGradient, XInt32 aColorStopNo,
  XFloat aOffset, XColor aColor )
{
  #if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    if ( !aGradient )
      return;

    /* Addressing invalid color stop? */
    if (( aColorStopNo < 0 ) || ( aColorStopNo >= aGradient->MaxNoOfStops ))
      return;

    /* Track the number of occupied color stop entries */
    if (( aColorStopNo + 1 ) > aGradient->NoOfStops )
      aGradient->NoOfStops = aColorStopNo + 1;

    /* Limit the offset */
    if ( aOffset < 0.0f ) aOffset = 0.0f;
    if ( aOffset > 1.0f ) aOffset = 1.0f;

    /* Store the value in the gradient */
    aGradient->Stops[ aColorStopNo ].Offset = aOffset;
    aGradient->Stops[ aColorStopNo ].Color  = aColor;
  #else
    EW_UNUSED_ARG( aGradient );
    EW_UNUSED_ARG( aColorStopNo );
    EW_UNUSED_ARG( aOffset );
    EW_UNUSED_ARG( aColor );
  #endif /* EW_DONT_USE_GRADIENTS && EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwSetGradientColorStop, ( XColorGradient* aGradient,
  XInt32 aColorStopNo, XFloat aOffset, XColor aColor ), ( aGradient,
  aColorStopNo, aOffset, aColor ))


/*******************************************************************************
* FUNCTION:
*   EwGetGradientMaxNoOfColorStops
*
* DESCRIPTION:
*   The function EwGetGradientMaxNoOfColorStops() returns the maximum number of
*   color stops the provided color gradient may store. This corresponds to the
*   value specified at the creation time of the gradient. See also the function
*   EwCreateGradient().
*
*  To query the number of already initialized color stops, use the function
*  EwGradientGetNoOfColorStops().

*
* ARGUMENTS:
*   aGradient - Pointer to the gradient to query the maximum number of color
*     stops it may store.
*
* RETURN VALUE:
*   Returns the maximum number of color stops (the capacity) of the gradient. 
*
*******************************************************************************/
XInt32 EwGetGradientMaxNoOfColorStops_( XColorGradient* aGradient )
{
  #if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Valid gradient? */
    if ( !aGradient )
      return 0;

    return aGradient->MaxNoOfStops;
  #else
    EW_UNUSED_ARG( aGradient );
    return 0;
  #endif /* EW_DONT_USE_GRADIENTS && EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwGetGradientMaxNoOfColorStops, XInt32, ( XColorGradient*
  aGradient ), ( aGradient ))


/*******************************************************************************
* FUNCTION:
*   EwGetGradientNoOfColorStops
*
* DESCRIPTION:
*   The function EwGetGradientNoOfColorStops() returns the number of color stops
*   stored already in the provided color gradient. To add a new a color stop to
*   the gradient the function EwGradientAddColorStop() is used.
*
*   To query the capacity of the gradient (the maximum number of color stops),
*   use the function EwGetGradientMaxNoOfColorStops()
*
* ARGUMENTS:
*   aGradient - Pointer to the gradient to query the number of initialized color
*     stops.
*
* RETURN VALUE:
*   Returns the number of color stops initialized already in the gradient. 
*
*******************************************************************************/
XInt32 EwGetGradientNoOfColorStops_( XColorGradient* aGradient )
{
  #if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Valid gradient? */
    if ( !aGradient )
      return 0;

    return aGradient->NoOfStops;
  #else
    EW_UNUSED_ARG( aGradient );
    return 0;
  #endif /* EW_DONT_USE_GRADIENTS && EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwGetGradientNoOfColorStops, XInt32, ( XColorGradient*
  aGradient ), ( aGradient ))


/*******************************************************************************
* FUNCTION:
*   EwCreatePath
*
* DESCRIPTION:
*   The function EwCreatePath() creates a new path and reserves memory for up
*   aMaxNoOfSubPaths sub-paths. The sub-paths are initially empty. Before data
*   can be stored in a sub-path the function EwInitSubPath() should be called.
*
*   Once the path is prepared and loaded with coordinate information, the path
*   can be passed to the EwFillPath() and EwStrokePath() functions. If not
*   used anymore the path should be freed by using the function EwFreePath().
*
* ARGUMENTS:
*   aMaxNoOfSubPaths - Max. number of sub-paths the new path can manage.
*
* RETURN VALUE:
*   If successful, the function returns a pointer to the newly created path.
*   Otherwise the function returns 0.
*
*******************************************************************************/
XPath* EwCreatePath_( XInt32 aMaxNoOfSubPaths )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    int    size = sizeof( XPath ) + ( aMaxNoOfSubPaths - 1 ) * sizeof( void* );
    XPath* path;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* The parameter is invalid */
    if ( aMaxNoOfSubPaths < 1 )
      return 0;

    /* Reserve memory for the path */
    do
      path = EwAlloc( size );
    while ( !path && EwImmediateReclaimMemory( 27 ));

    /* Was not able to reserve memory for the new path. */
    if ( !path )
    {
      EwError( 27 );
      return 0;
    }

    /* Initialize the just created path. At the moment it is empty and the matrix
       is initialized with the identity matrix */
    EwZero( path, size );
    path->Matrix[0]       = 1.0f;
    path->Matrix[4]       = 1.0f;
    path->IsValid         = 1;
    path->MaxNoOfSubPaths = aMaxNoOfSubPaths;

    /* Track the memory usage */
    EwResourcesMemory += size;

    /* Also track the max. memory pressure */
    if ( EwResourcesMemory > EwResourcesMemoryPeak )
      EwResourcesMemoryPeak = EwResourcesMemory;

    if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
      EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

    return path;
  #else
    EW_UNUSED_ARG( aMaxNoOfSubPaths );
    EwError( 191 );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwCreatePath, XPath*, (  XInt32 aMaxNoOfSubPaths ),
  ( aMaxNoOfSubPaths ))


/*******************************************************************************
* FUNCTION:
*   EwFreePath
*
* DESCRIPTION:
*   The function EwFreePath() frees the memory occupied by the path and its all
*   sub-paths.
*
* ARGUMENTS:
*   aPath - Pointer to the path to free.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwFreePath_( XPath* aPath )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    if ( !aPath )
      return;

    /* Take in account the memory occupied by the XPath object and the list of
       sub-paths */
    EwResourcesMemory -= sizeof( XPath ) + ( aPath->MaxNoOfSubPaths - 1 ) *
                         sizeof( void* );

    /* Release all entries existing actually on the matrix stack */
    while ( aPath->MatrixStack )
    {
      XPathMatrix* next = aPath->MatrixStack->Next;

      EwResourcesMemory -= sizeof( XPathMatrix );
      EwFree( aPath->MatrixStack );

      aPath->MatrixStack = next;
    }

    /* Release all sub-paths ... */
    while ( aPath->MaxNoOfSubPaths-- > 0 )
    {
      XSubPath** subPath = ((XSubPath**)aPath->SubPaths) + aPath->MaxNoOfSubPaths;

      /* Release the memory occupied by the sub-path */
      if ( *subPath )
      {
        EwResourcesMemory -= sizeof( XSubPath ) + ((*subPath)->Capacity + 1 ) *
                             sizeof( float ) * 2;
        EwFree( *subPath );
        *subPath = 0;
      }
    }

    aPath->MaxNoOfSubPaths = 0;

    /* ... and finally the path object itself */
    EwFree( aPath );
  #else
    EW_UNUSED_ARG( aPath );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwFreePath, ( XPath* aPath ), ( aPath ))


/*******************************************************************************
* FUNCTION:
*   EwGetMaxNoOfSubPaths
*
* DESCRIPTION:
*   The function EwGetMaxNoOfSubPaths() returns how many sub-paths the given
*   path can maximally store. The returned value corresponds to the parameter
*   passed in the invocation of the EwCreatePath() function.
*
* ARGUMENTS:
*   aPath - Pointer to the path to query the information.
*
* RETURN VALUE:
*   If successful, the function returns the max. number of sub-path the path
*   can store. Otherwise the function returns 0.
*
*******************************************************************************/
XInt32 EwGetMaxNoOfSubPaths_( XPath* aPath )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    if ( !aPath )
      return 0;

    return aPath->MaxNoOfSubPaths;
  #else
    EW_UNUSED_ARG( aPath );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwGetMaxNoOfSubPaths, XInt32, ( XPath* aPath ), ( aPath ))


/*******************************************************************************
* FUNCTION:
*   EwInitSubPath
*
* DESCRIPTION:
*   The function EwInitSubPath() prepares a sub-path to be able to store up to
*   aMaxNoOfEdges path edges. With this operation memory for the sub-path data
*   is reserved. Initially the just initialized sub-path is considered as being
*   still empty. To fill the sub-path with edge coordinates use the functions
*   EwAddSubPathLine(), EwAddSubPathArc(), etc.
*
*   If the affected sub-path has been already initialized in the past, the old
*   information is discarded before initializing the new sub-path.
*
* ARGUMENTS:
*   aPath         - Pointer to the path to initialize the sub-path.
*   aSubPathNo    - Number identifying the sub-path within aPath to initialize.
*     The first sub-path has the number 0. The second 1, and so far.
*   aMaxNoOfEdges - The max. number of edges you intend to store in the sub-
*     path. This is the max. capacity for the sub-path. Passing 0 (zero) in
*     this  parameter results in the existing sub-path data being released and
*     the sub-path is considered as empty again.
*
* RETURN VALUE:
*   If successful, the function returns != 0. If there is no available memory
*   for the sub-path allocation, 0 is returned.
*
*******************************************************************************/
XBool EwInitSubPath_( XPath* aPath, XInt32 aSubPathNo, XInt32 aMaxNoOfEdges )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = &((XSubPath**)aPath->SubPaths)[ aSubPathNo ];
    int        oldSize = 0;
    int        newSize = 0;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return 0;

    /* Limit the number of edges */
    if ( aMaxNoOfEdges <= 0 )
      aMaxNoOfEdges = 0;

    /* Calculate the size of the new sub-path. Take in account an additional edge
       to eventually close the sub-path */
    if ( aMaxNoOfEdges )
      newSize = sizeof( XSubPath ) + ( aMaxNoOfEdges + 1 ) * sizeof( float ) * 2;

    /* Determine the size of the old sub-path */
    if ( *subPath )
      oldSize = sizeof( XSubPath ) + ((*subPath)->Capacity + 1 ) *
                sizeof( float ) * 2;

    /* If the sub-path already exists but its size differ from the new size
       aMaxNoOfEdges - discard the old sub-path first */
    if ( oldSize && ( oldSize != newSize ))
    {
      EwResourcesMemory -= oldSize;
      EwFree( *subPath );
      *subPath = 0;
    }

    /* Allocate the sub-path if it doesn't exist */
    if ( !*subPath && newSize )
    {
      do
        *subPath = EwAlloc( newSize );
      while ( !*subPath && EwImmediateReclaimMemory( 28 ));

      /* Was not able to allocate memory for the new sub-path */
      if ( !*subPath )
      {
        EwError( 28 );
        return 0;
      }

      EwResourcesMemory += newSize;

      /* Also track the max. memory pressure */
      if ( EwResourcesMemory > EwResourcesMemoryPeak )
        EwResourcesMemoryPeak = EwResourcesMemory;

      if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
        EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;
    }

    /* Initialize the sub-path. The sub-path is completely empty */
    if ( *subPath )
    {
      EwZero( *subPath, sizeof( XSubPath ));
      (*subPath)->Capacity = aMaxNoOfEdges;
      (*subPath)->IsValid  = 1;
    }

    /* After this operation the path needs eventually an update */
    if ( oldSize )
      aPath->IsValid = 0;

    /* O.K. */
    return 1;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    EW_UNUSED_ARG( aMaxNoOfEdges );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwInitSubPath, XBool, ( XPath* aPath, XInt32 aSubPathNo,
  XInt32 aMaxNoOfEdges ), ( aPath, aSubPathNo, aMaxNoOfEdges ))


/*******************************************************************************
* FUNCTION:
*   EwBeginSubPath
*
* DESCRIPTION:
*   The function EwBeginSubPath() sets the start position for the sub-path. The
*   affected sub-path has to be initialized previously by calling the function
*   EwInitSubPath(). Beginning with the position, the path can be filled with
*   edges by calling functions like EwAddSubPathLine(), EwAddSubPathBezier2(),
*   etc.
*
*   Every sub-path contains exact one begin position. Calling this function for
*   a sub-path being already filled with edge coordinates will clear the actual
*   sub-path coordinate data and sets the new begin position.
*
* ARGUMENTS:
*   aPath      - Pointer to the path containing the affected sub-path.
*   aSubPathNo - Number identifying the sub-path within aPath to configure. The
*     first sub-path has the number 0. The second 1, and so far.
*   aX, aY     - The coordinates to be used as the start position for the sub-
*     path. The position is transformed by using the path transformation matrix.
*     See functions like EwScalePathMatrix(), EwRotatePathMatrix(), etc.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBeginSubPath_( XPath* aPath, XInt32 aSubPathNo, XFloat aX, XFloat aY )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;
    float*     m       = aPath->Matrix;
    float      x       = aX;
    float      y       = aY;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return;

    /* The sub-path is not initialized */
    if ( !*subPath )
      return;

    /* Transform the positions? */
    if (( m[0] != 1.0f ) || ( m[1] != 0.0f ) || ( m[2] != 0.0f ) ||
        ( m[3] != 0.0f ) || ( m[4] != 1.0f ) || ( m[5] != 0.0f ))
    {
      x = aX * m[0] + aY * m[1] + m[2];
      y = aX * m[3] + aY * m[4] + m[5];
    }

    /* Initialize the path as if it were empty */
    (*subPath)->IsClosed  = 0;
    (*subPath)->IsOpened  = 0;
    (*subPath)->IsValid   = 0;
    (*subPath)->NoOfEdges = 0;
    (*subPath)->HasData   = 1;
    (*subPath)->Data[0]   = x;
    (*subPath)->Data[1]   = y;
    aPath->IsValid        = 0;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    EW_UNUSED_ARG( aX );
    EW_UNUSED_ARG( aY );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwBeginSubPath, ( XPath* aPath, XInt32 aSubPathNo,
  XFloat aX, XFloat aY ), ( aPath, aSubPathNo, aX, aY ))


/*******************************************************************************
* FUNCTION:
*   EwAddSubPathLine
*
* DESCRIPTION:
*   The function EwAddSubPathLine() appends at the actual position in the sub-
*   path a new straight line segment consisting of one edge. Then the sub-path
*   actual position is moved to the end of the just added line.
*
*   The actual position results from the end position of the preceding sub-path
*   segment or it is the value specified in EwBeginSubPath() invocation. If the
*   sub-path is empty and no start position has been specified in the preceding
*   EwBeginSubPath() invocation, the function assumes the start position is X=0,
*   Y=0.
*
* ARGUMENTS:
*   aPath      - Pointer to the path containing the affected sub-path.
*   aSubPathNo - Number identifying the sub-path within aPath to add the line.
*     The first sub-path has the number 0. The second 1, and so far.
*   aX, aY     - The coordinates to be used as the end position for the new line
*     segment. The position is transformed by using the path transformation
*     matrix. See functions like EwScalePathMatrix(), EwRotatePathMatrix(), etc.
*
* RETURN VALUE:
*   Returns the index of the node within the sub-path where the end position
*   of the new line segment has bee stored. Knowing this index, the position
*   can be modified later by using the function EwSetSubPathNode().
*
*   If the sub-path has not been initialized previously by calling the function
*   EwInitSubPath(), the sub-path has been closed by EwCloseSubPath() or the
*   entire memory reserved for the sub-path is already occupied by other path
*   information, the function fails and returns 0.
*
*******************************************************************************/
XInt32 EwAddSubPathLine_( XPath* aPath, XInt32 aSubPathNo, XFloat aX, XFloat aY )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;
    float*     m       = aPath->Matrix;
    float      x       = aX;
    float      y       = aY;
    float*     d;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return 0;

    /* The sub-path is not initialized, closed or there is no free space in the
       sub-path for new edges */
    if ( !*subPath || (*subPath)->IsClosed ||
       (((*subPath)->NoOfEdges + 1 ) > (*subPath)->Capacity ))
      return 0;

    /* Till now, the sub-path was empty. Now it contains data */
    (*subPath)->HasData  = 1;
    (*subPath)->IsOpened = 1;
    (*subPath)->IsValid  = 0;
    aPath->IsValid       = 0;

    /* Transform the position */
    if (( m[0] != 1.0f ) || ( m[1] != 0.0f ) || ( m[2] != 0.0f ) ||
        ( m[3] != 0.0f ) || ( m[4] != 1.0f ) || ( m[5] != 0.0f ))
    {
      x = aX * m[0] + aY * m[1] + m[2];
      y = aX * m[3] + aY * m[4] + m[5];
    }

    /* Determine the address where to store the curve data */
    d = (float*)(*subPath)->Data + (*subPath)->NoOfEdges * 2 + 2;

    /* Store the end position of the line segment */
    *d++ = x;
    *d++ = y;

    return (*subPath)->NoOfEdges++;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    EW_UNUSED_ARG( aX );
    EW_UNUSED_ARG( aY );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwAddSubPathLine, XInt32, ( XPath* aPath, XInt32 aSubPathNo,
  XFloat aX, XFloat aY ), ( aPath, aSubPathNo, aX, aY ))


/*******************************************************************************
* FUNCTION:
*   EwAddSubPathBezier2
*
* DESCRIPTION:
*   The function EwAddSubPathBezier2() appends at the actual position in the
*   sub-path a new quadratic Bezier curve composed of exact aNoOfEdges straight
*   line segments. Then the sub-path actual position is moved to the end of the
*   just added curve.
*
*   The actual position results from the end position of the preceding sub-path
*   segment or it is the value specified in EwBeginSubPath() invocation. If the
*   sub-path is empty and no start position has been specified in the preceding
*   EwBeginSubPath() invocation, the function assumes the start position is X=0,
*   Y=0.
*
* ARGUMENTS:
*   aPath      - Pointer to the path containing the affected sub-path.
*   aSubPathNo - Number identifying the sub-path within aPath to add the curve.
*     The first sub-path has the number 0. The second 1, and so far.
*   aCPX, aCPY - The coordinates of the Bezier curve control point. The position
*     is transformed by using the path transformation matrix. See functions like
*     EwScalePathMatrix(), EwRotatePathMatrix(), etc.
*   aX, aY     - The coordinates to be used as the end position for the Bezier
*     curve. The position is transformed by using the path transformation matrix.
*     See functions like EwScalePathMatrix(), EwRotatePathMatrix(), etc.
*   aNoOfEdges - Number of straight line segments the Bezier curve should be
*     composed of. The more edges the smoother the resulting curve.
*
* RETURN VALUE:
*   Returns the index of the node within the sub-path where the position of the
*   first Bezier line segment has bee stored. Knowing this index and the number
*   of segments the Bezier curve is composed of (aNoOfEdges), the position of
*   every Bezier line segment can be modified later. See EwSetSubPathNode().
*
*   If the sub-path has not been initialized previously by calling the function
*   EwInitSubPath(), the sub-path has been closed by EwCloseSubPath() or there
*   is no sufficient memory in the sub-path for the new Bezier curve segments,
*   the function fails and returns 0.
*
*******************************************************************************/
XInt32 EwAddSubPathBezier2_( XPath* aPath, XInt32 aSubPathNo, XFloat aCPX,
  XFloat aCPY, XFloat aX, XFloat aY, XInt32 aNoOfEdges )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;
    float*     m       = aPath->Matrix;
    float      cpx     = aCPX;
    float      cpy     = aCPY;
    float      x       = aX;
    float      y       = aY;
    float      x0, y0;
    float      t,  s;
    float*     d;
    int        i;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Nothing to add */
    if ( aNoOfEdges <= 0 )
      return 0;

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return 0;

    /* The sub-path is not initialized, closed or there is no free space in the
       sub-path for new edges */
    if ( !*subPath || (*subPath)->IsClosed ||
       (((*subPath)->NoOfEdges + aNoOfEdges ) > (*subPath)->Capacity ))
      return 0;

    /* Till now, the sub-path was empty. Now it contains data */
    (*subPath)->HasData  = 1;
    (*subPath)->IsOpened = 1;
    (*subPath)->IsValid  = 0;
    aPath->IsValid       = 0;

    /* Transform the positions */
    if (( m[0] != 1.0f ) || ( m[1] != 0.0f ) || ( m[2] != 0.0f ) ||
        ( m[3] != 0.0f ) || ( m[4] != 1.0f ) || ( m[5] != 0.0f ))
    {
      cpx = aCPX * m[0] + aCPY * m[1] + m[2];
      cpy = aCPX * m[3] + aCPY * m[4] + m[5];
      x   = aX   * m[0] + aY   * m[1] + m[2];
      y   = aX   * m[3] + aY   * m[4] + m[5];
    }

    /* Determine the address where to store the curve data as well as the size
       of a single step to sample the Bezier curve */
    d  = (float*)(*subPath)->Data + (*subPath)->NoOfEdges * 2;
    s  = 1.0f / aNoOfEdges;
    x0 = *d++;
    y0 = *d++;

    /* Calculate aNoOfEdges smaples of the Bezier curve and store these in the
       sub-path */
    for ( t = s, i = 1; i < aNoOfEdges; i++, t += s )
    {
      float nt  = 1.0f - t;
      float nt2 = nt   * nt;
      float t2  = t    * t;
      float f2  = 2.0f * nt * t;

      *d++ = nt2 * x0 + f2 * cpx + t2 * x;
      *d++ = nt2 * y0 + f2 * cpy + t2 * y;
    }

    /* Store the end position of the Bezier curve */
    *d++ = x;
    *d++ = y;

    return ((*subPath)->NoOfEdges += i ) - i;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    EW_UNUSED_ARG( aCPX );
    EW_UNUSED_ARG( aCPY );
    EW_UNUSED_ARG( aX );
    EW_UNUSED_ARG( aY );
    EW_UNUSED_ARG( aNoOfEdges );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwAddSubPathBezier2, XInt32, ( XPath* aPath, XInt32 aSubPathNo,
  XFloat aCPX, XFloat aCPY, XFloat aX, XFloat aY, XInt32 aNoOfEdges ), ( aPath,
  aSubPathNo, aCPX, aCPY, aX, aY, aNoOfEdges ))


/*******************************************************************************
* FUNCTION:
*   EwAddSubPathBezier3
*
* DESCRIPTION:
*   The function EwAddSubPathBezier3() appends at the actual position in the
*   sub-path a new cubic Bezier curve composed of exact aNoOfEdges straight line
*   segments. Then the sub-path actual position is moved to the end of the just
*   added curve.
*
*   The actual position results from the end position of the preceding sub-path
*   segment or it is the value specified in EwBeginSubPath() invocation. If the
*   sub-path is empty and no start position has been specified in the preceding
*   EwBeginSubPath() invocation, the function assumes the start position is X=0,
*   Y=0.
*
* ARGUMENTS:
*   aPath        - Pointer to the path containing the affected sub-path.
*   aSubPathNo   - Number identifying the sub-path within aPath to add the
*     curve. The first sub-path has the number 0. The second 1, and so far.
*   aCP1X, aCP1Y - The coordinates of the first Bezier curve control point. The
*     position is transformed by using the path transformation matrix. See
*     functions like EwScalePathMatrix(), EwRotatePathMatrix(), etc.
*   aCP2X, aCP2Y - The coordinates of the second Bezier curve control point. The
*     position is transformed by using the path transformation matrix. See
*     functions like EwScalePathMatrix(), EwRotatePathMatrix(), etc.
*   aX, aY       - The coordinates to be used as the end position for the Bezier
*     curve. The position is transformed by using the path transformation matrix.
*     See functions like EwScalePathMatrix(), EwRotatePathMatrix(), etc.
*   aNoOfEdges   - Number of straight line segments the Bezier curve should be
*     composed of. The more edges the smoother the resulting curve.
*
* RETURN VALUE:
*   Returns the index of the node within the sub-path where the position of the
*   first Bezier line segment has bee stored. Knowing this index and the number
*   of segments the Bezier curve is composed of (aNoOfEdges), the position of
*   every Bezier line segment can be modified later. See EwSetSubPathNode().
*
*   If the sub-path has not been initialized previously by calling the function
*   EwInitSubPath(), the sub-path has been closed by EwCloseSubPath() or there
*   is no sufficient memory in the sub-path for the new Bezier curve segments,
*   the function fails and returns 0.
*
*******************************************************************************/
XInt32 EwAddSubPathBezier3_( XPath* aPath, XInt32 aSubPathNo, XFloat aCP1X,
  XFloat aCP1Y, XFloat aCP2X, XFloat aCP2Y, XFloat aX, XFloat aY,
  XInt32 aNoOfEdges )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;
    float*     m       = aPath->Matrix;
    float      cp1x    = aCP1X;
    float      cp1y    = aCP1Y;
    float      cp2x    = aCP2X;
    float      cp2y    = aCP2Y;
    float      x       = aX;
    float      y       = aY;
    float      x0, y0;
    float      t,  s;
    float*     d;
    int        i;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Nothing to add */
    if ( aNoOfEdges <= 0 )
      return 0;

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return 0;

    /* The sub-path is not initialized, closed or there is no free space in the
       sub-path for new edges */
    if ( !*subPath || (*subPath)->IsClosed ||
       (((*subPath)->NoOfEdges + aNoOfEdges ) > (*subPath)->Capacity ))
      return 0;

    /* Till now, the sub-path was empty. Now it contains data */
    (*subPath)->HasData  = 1;
    (*subPath)->IsOpened = 1;
    (*subPath)->IsValid  = 0;
    aPath->IsValid       = 0;

    /* Transform the positions */
    if (( m[0] != 1.0f ) || ( m[1] != 0.0f ) || ( m[2] != 0.0f ) ||
        ( m[3] != 0.0f ) || ( m[4] != 1.0f ) || ( m[5] != 0.0f ))
    {
      cp1x = aCP1X * m[0] + aCP1Y * m[1] + m[2];
      cp1y = aCP1X * m[3] + aCP1Y * m[4] + m[5];
      cp2x = aCP2X * m[0] + aCP2Y * m[1] + m[2];
      cp2y = aCP2X * m[3] + aCP2Y * m[4] + m[5];
      x    = aX    * m[0] + aY    * m[1] + m[2];
      y    = aX    * m[3] + aY    * m[4] + m[5];
    }

    /* Determine the address where to store the curve data as well as the size
       of a single step to sample the Bezier curve */
    d  = (float*)(*subPath)->Data + (*subPath)->NoOfEdges * 2;
    s  = 1.0f / aNoOfEdges;
    x0 = *d++;
    y0 = *d++;

    /* Calculate aNoOfEdges smaples of the Bezier curve and store these in the
       sub-path */
    for ( t = s, i = 1; i < aNoOfEdges; i++, t += s )
    {
      float nt  = 1.0f - t;
      float t2  = t    * t;
      float nt2 = nt   * nt;
      float f1  = nt   * nt2;
      float f2  = 3.0f * nt2 * t;
      float f3  = 3.0f * nt  * t2;
      float f4  = t    * t2;

      *d++ = f1 * x0 + f2 * cp1x + f3 * cp2x + f4 * x;
      *d++ = f1 * y0 + f2 * cp1y + f3 * cp2y + f4 * y;
    }

    /* Store the end position of the Bezier curve */
    *d++ = x;
    *d++ = y;

    return ((*subPath)->NoOfEdges += i ) - i;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    EW_UNUSED_ARG( aCP1X );
    EW_UNUSED_ARG( aCP1Y );
    EW_UNUSED_ARG( aCP2X );
    EW_UNUSED_ARG( aCP2Y );
    EW_UNUSED_ARG( aX );
    EW_UNUSED_ARG( aY );
    EW_UNUSED_ARG( aNoOfEdges );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwAddSubPathBezier3, XInt32, ( XPath* aPath, XInt32 aSubPathNo,
  XFloat aCP1X, XFloat aCP1Y, XFloat aCP2X, XFloat aCP2Y, XFloat aX, XFloat aY,
  XInt32 aNoOfEdges ), ( aPath, aSubPathNo, aCP1X, aCP1Y, aCP2X, aCP2Y, aX, aY,
  aNoOfEdges ))


/*******************************************************************************
* FUNCTION:
*   EwAddSubPathArc
*
* DESCRIPTION:
*   The function EwAddSubPathArc() adds to the sub-path a new arc curve composed
*   of exact aNoOfEdges straight line segments. If the sub-path contains already
*   any segment information, the start of the arc curve is connected with the
*   end of the last segment by an additional straight line.
*
*   Similarly, if start position for the sub-path has been specified by using
*   EwBeginSubPath(), an additional line segment is added to connect the curve
*   with the specified sub-path start position.
*
*   After the curve is stored in the path, the sub-path actual position is moved
*   to refer to the end position of the arc.
*
* ARGUMENTS:
*   aPath       - Pointer to the path containing the affected sub-path.
*   aSubPathNo  - Number identifying the sub-path within aPath to add the curve.
*     The first sub-path has the number 0. The second 1, and so far.
*   aCenterX,
*   aCenterY    - The coordinates of the center of the arc to calculate. The
*     position is transformed by using the path transformation matrix. See
*     functions like EwScalePathMatrix(), EwRotatePathMatrix(), etc.
*   aRadiusX,
*   aRadiusY    - Radius if the arc in X and Y direction.
*   aStartAngle,
*   aEndAngle   - Start- and end-angle of the arc expressed in degree and
*     measured clockwise relative to the positive X-axis.
*   aNoOfEdges  - Number of straight line segments the arc curve should be
*     composed of. The more edges the smoother the resulting curve.
*
* RETURN VALUE:
*   Returns the index of the node within the sub-path where the start position
*   of the first arc line segment has bee stored. Knowing this index and the
*   number of segments the arc curve is composed of (aNoOfEdges), the position
*   of every arc line segment can be modified later. See EwSetSubPathNode().
*
*   If the sub-path has not been initialized previously by calling the function
*   EwInitSubPath(), the sub-path has been closed by EwCloseSubPath() or there
*   is no sufficient memory in the sub-path for the new arc curve segments, the
*   function fails and returns 0.
*
*******************************************************************************/
XInt32 EwAddSubPathArc_( XPath* aPath, XInt32 aSubPathNo, XFloat aCenterX,
  XFloat aCenterY, XFloat aRadiusX, XFloat aRadiusY, XFloat aStartAngle,
  XFloat aEndAngle, XInt32 aNoOfEdges )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath   = (XSubPath**)aPath->SubPaths + aSubPathNo;
    int        noOfEdges = aNoOfEdges;
    float*     m         = aPath->Matrix;
    float*     d;
    float      s;
    int        i;
    int        doTransform;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Nothing to add */
    if (( aNoOfEdges <= 0 ) || ( aStartAngle == aEndAngle ))
      return 0;

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return 0;

    /* If the path contains already data, an additional edge is needed to
       connect the end position of the last segment with the first position
       of the arc */
    if ( *subPath && (*subPath)->HasData )
      noOfEdges++;

    /* The sub-path is not initialized, closed or there is no free space in the
       sub-path for new edges */
    if ( !*subPath || (*subPath)->IsClosed ||
       (((*subPath)->NoOfEdges + noOfEdges ) > (*subPath)->Capacity ))
      return 0;

    /* Till now, the sub-path was empty. Now it contains data */
    (*subPath)->HasData  = 1;
    (*subPath)->IsOpened = 1;
    (*subPath)->IsValid  = 0;
    aPath->IsValid       = 0;

    /* Determine the address where to store the curve data as well as the size
       of a single step to sample the arc curve*/
    d = (float*)(*subPath)->Data + (*subPath)->NoOfEdges * 2 +
        ( noOfEdges - aNoOfEdges ) * 2;
    s = ( aEndAngle - aStartAngle ) / aNoOfEdges;

    /* If the matrix is not an identity matrix - an additional transformation
       will be applied */
    doTransform = ( m[0] != 1.0f ) || ( m[1] != 0.0f ) || ( m[2] != 0.0f ) ||
                  ( m[3] != 0.0f ) || ( m[4] != 1.0f ) || ( m[5] != 0.0f );

    /* Sample the arc curve and calculate the position for every edge */
    for ( i = 0; i <= aNoOfEdges; i++, aStartAngle += s )
    {
      float a = ( i == aNoOfEdges )? aEndAngle : aStartAngle;
      float x = aCenterX + aRadiusX * EwMathCos( a );
      float y = aCenterY + aRadiusY * EwMathSin( a );

      /* Transform the positions? */
      if ( doTransform )
      {
        float xx = x;
        x = xx * m[0] + y * m[1] + m[2];
        y = xx * m[3] + y * m[4] + m[5];
      }

      /* The coordinate calculation for the arc edges is not precise. This may lead
         to a minimal difference between the coordinates for the last corner of the
         preceding arc and the start corner of the new arc. If this difference is
         less than 0.5 pixel, ensure the start position of the new arc is equal to
         the end position of the preceding arc */
      if (( i == 0 ) && ( noOfEdges > aNoOfEdges ))
      {
        float dx = x - d[-2];
        float dy = y - d[-1];

        /* Is the diffeence less than 0.5 pixel? */
        if ((( dx * dx ) + ( dy * dy )) < 0.25f )
        {
          x = d[-2];
          y = d[-1];
        }
      }

      /* Store the calculated coordinates */
      *d++ = x;
      *d++ = y;
    }

    return ((*subPath)->NoOfEdges += noOfEdges ) - aNoOfEdges;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    EW_UNUSED_ARG( aCenterX );
    EW_UNUSED_ARG( aCenterY );
    EW_UNUSED_ARG( aRadiusX );
    EW_UNUSED_ARG( aRadiusY );
    EW_UNUSED_ARG( aStartAngle );
    EW_UNUSED_ARG( aEndAngle );
    EW_UNUSED_ARG( aNoOfEdges );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwAddSubPathArc, XInt32, ( XPath* aPath, XInt32 aSubPathNo,
  XFloat aCenterX, XFloat aCenterY, XFloat aRadiusX, XFloat aRadiusY,
  XFloat aStartAngle, XFloat aEndAngle, XInt32 aNoOfEdges ), ( aPath, aSubPathNo,
  aCenterX, aCenterY, aRadiusX, aRadiusY, aStartAngle, aEndAngle, aNoOfEdges ))


/*******************************************************************************
* FUNCTION:
*   EwAddSubPathCopy
*
* DESCRIPTION:
*   The function EwAddSubPathCopy() adds to the sub-path a copy of another sub-
*   path. In this manner contents from different paths can be combined together
*   without the necessity to re-calculate them again.
*
*   If the destination sub-path contains already any segment information, the
*   start of the copied source sub-path is connected with the end of the last
*   segment by an additional straight line.
*
*   Similarly, if start position for the sub-path has been specified by using
*   EwBeginSubPath(), an additional line segment is added to connect it with
*   the copied sub-path.
*
*   If the transformation matrix of the destination path has been configured,
*   the copied source coordinates are transformed by using the matrix. (See
*   EwTranslatePath(), EwScalePath(), etc.)
*
*   After the copy is stored in the path, the sub-path actual position is moved
*   to refer to the end position of the copied sub-path.
*
* ARGUMENTS:
*   aPath         - Pointer to the destination path containing the affected
*     sub-path to add the copy.
*   aSubPathNo    - Number identifying the sub-path within aPath to add the
*     copy. The first sub-path has the number 0. The second 1, and so far.
*   aSrcPath      - Pointer to the source path containing the sub-path to copy.
*   aSrcSubPathNo - Number identifying the sub-path within aSrcPath to create
*     a copy. The first sub-path has the number 0. The second 1, and so far.
*   aSrcNodeNo    - The number of the node in the source sub-path to start the
*     copy operation. If this parameter is == 0, the operation starts with the
*     first node (the begin) of the source sub-path.
*   aNoOfEdges    - The number of edges to copy from the source sub-path
*     beginning with the node specified in the parameter aSrcNodeNo. In total,
*     ( aNoOfEdges + 1 ) will be copied. Specifying -1 in this parameter means
*     that all edges until the source sub-path end should be copied. If there
*     are less edges available in the source path, the function fails.
*
* RETURN VALUE:
*   Returns the index of the node within the destination sub-path where the
*   start position of the first copied segment has bee stored. Knowing this
*   index and the number of copied segments the, the position of every segment
*   can be modified later. See EwSetSubPathNode().
*
*   If the sub-path has not been initialized previously by calling the function
*   EwInitSubPath(), the sub-path has been closed by EwCloseSubPath(), there
*   is no sufficient memory in the destination sub-path for the complete copy
*   of the source sub-path or the source sub-path or the requested nodes do
*   not exist, the function fails and returns 0.
*
*******************************************************************************/
XInt32 EwAddSubPathCopy_( XPath* aPath, XInt32 aSubPathNo, XPath* aSrcPath,
  XInt32 aSrcSubPathNo, XInt32 aSrcNodeNo, XInt32 aNoOfEdges )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** dstSubPath = (XSubPath**)aPath->   SubPaths + aSubPathNo;
    XSubPath** srcSubPath = (XSubPath**)aSrcPath->SubPaths + aSrcSubPathNo;
    int        noOfEdges  = aNoOfEdges;
    float*     m          = aPath->Matrix;
    float*     d;
    float*     s;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding destination sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return 0;

    /* There is no corresponding source sub-path */
    if ( !aSrcPath || ( aSrcSubPathNo >= aSrcPath->MaxNoOfSubPaths ) ||
       ( aSrcSubPathNo < 0 ))
      return 0;

    /* The source sub-path is not initialized or the node is not valid */
    if ( !*srcSubPath || ( aSrcNodeNo < 0 ) || !aNoOfEdges )
      return 0;

    /* Should copy until the end of the source sub-path? */
    if ( aNoOfEdges < 0 )
      noOfEdges = aNoOfEdges = (*srcSubPath)->NoOfEdges - aSrcNodeNo;

    /* There is no sufficient nodes in the source path to copy */
    if (( aSrcNodeNo + noOfEdges ) > (*srcSubPath)->NoOfEdges )
      return 0;

    /* If the path contains already data, an additional edge is needed to
       connect the end position of the last segment with the first position
       of the coped sub-path data */
    if ( *dstSubPath && (*dstSubPath)->HasData )
      noOfEdges++;

    /* The destination sub-path is not initialized, closed or there is no free
       space in the sub-path for new edges */
    if ( !*dstSubPath || (*dstSubPath)->IsClosed ||
       (((*dstSubPath)->NoOfEdges + noOfEdges ) > (*dstSubPath)->Capacity ))
      return 0;

    /* Till now, the sub-path was empty. Now it contains data */
    (*dstSubPath)->HasData  = 1;
    (*dstSubPath)->IsOpened = 1;
    (*dstSubPath)->IsValid  = 0;
    aPath->IsValid          = 0;

    /* Determine the destination and the source addresses of the affected
       data to copy */
    d = (float*)(*dstSubPath)->Data + (*dstSubPath)->NoOfEdges * 2 +
        ( noOfEdges - aNoOfEdges ) * 2;
    s = (float*)(*srcSubPath)->Data + aSrcNodeNo * 2;

    /* If the matrix is not an identity matrix - an additional transformation
       will be applied */
    if (( m[0] != 1.0f ) || ( m[1] != 0.0f ) || ( m[2] != 0.0f ) ||
        ( m[3] != 0.0f ) || ( m[4] != 1.0f ) || ( m[5] != 0.0f ))
    {
      int i = 0;

      for ( ; i <= aNoOfEdges; i++, s += 2 )
      {
        *d++ = s[0] * m[0] + s[1] * m[1] + m[2];
        *d++ = s[0] * m[3] + s[1] * m[4] + m[5];
      }
    }

    /* Just copy without the transformation */
    else
      EwCopy( d, s, ( aNoOfEdges + 1 ) * 2 * sizeof( float ));

    return ((*dstSubPath)->NoOfEdges += noOfEdges ) - aNoOfEdges;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    EW_UNUSED_ARG( aSrcPath );
    EW_UNUSED_ARG( aSrcSubPathNo );
    EW_UNUSED_ARG( aSrcNodeNo );
    EW_UNUSED_ARG( aNoOfEdges );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwAddSubPathCopy, XInt32, ( XPath* aPath, XInt32 aSubPathNo,
  XPath* aSrcPath, XInt32 aSrcSubPathNo, XInt32 aSrcNodeNo, XInt32 aNoOfEdges ),
( aPath, aSubPathNo, aSrcPath, aSrcSubPathNo, aSrcNodeNo, aNoOfEdges ))


/*******************************************************************************
* FUNCTION:
*   EwCloseSubPath
*
* DESCRIPTION:
*   The function EwCloseSubPath() marks the affected sub-path as closed. The
*   function verifies whether the first and last position of the path are equal
*   and if this is not the case, adds an additional line segment to the path in
*   order to close it.
*
*   Once the function is called, no additional path information can be added to
*   the affected path unless it is initialized again by using EwInitSubPath()
*   or cleared by using EwBeginSubPath().
*
* ARGUMENTS:
*   aPath       - Pointer to the path containing the affected sub-path.
*   aSubPathNo  - Number identifying the sub-path within aPath to close. The
*     first sub-path has the number 0. The second 1, and so far.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwCloseSubPath_( XPath* aPath, XInt32 aSubPathNo )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;
    float*     d;
    float      dx, dy;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return;

    /* The sub-path is not initialized, it is already closed or the path is
       empty */
    if ( !*subPath || (*subPath)->IsClosed || !(*subPath)->IsOpened )
      return;

    /* With this operation the sub-path changes from opened to closed */
    (*subPath)->IsOpened = 0;
    (*subPath)->IsClosed = 1;
    aPath->IsValid       = 0;

    d  = (float*)(*subPath)->Data;
    dx = d[(*subPath)->NoOfEdges * 2 + 0 ] - d[0];
    dy = d[(*subPath)->NoOfEdges * 2 + 1 ] - d[1];

    /* If the first and the last sub-path positions are different, connect them
       with an additional line segment */
    if (( dx > 0.001f ) || ( dx < -0.001f ) || ( dy > 0.001f ) || ( dy < -0.001f ))
    {
      (*subPath)->NoOfEdges++;
      d[(*subPath)->NoOfEdges * 2 + 0 ] = d[0];
      d[(*subPath)->NoOfEdges * 2 + 1 ] = d[1];
    }

    /* The both position are (very) close */
    else
    {
      d[(*subPath)->NoOfEdges * 2 + 0 ] = d[0];
      d[(*subPath)->NoOfEdges * 2 + 1 ] = d[1];
    }
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwCloseSubPath, ( XPath* aPath, XInt32 aSubPathNo ),
  ( aPath, aSubPathNo ))


/*******************************************************************************
* FUNCTION:
*   EwShiftSubPathNodes
*
* DESCRIPTION:
*   The function EwShiftSubPathNodes() removes from the sub-path the specified
*   number of leading coordinate values. This results in the sub-path content
*   being shifted and the number of sub-path edges being reduced by the given
*   aNoOfNodes parameter. Thereupon new edge data can be appended to the path,
*   e.g. by using the function EwAddSubPathLine().
*
*   Applying the function on a sub-path closed by a preceding EwCloseSubPath()
*   is not possible and causes the function to return without any modification
*   on the sub-path data.
*
*   Moreover, the operation is limited to leave at least one node in the path.
*   In other words, it is not possible to clear the path completely. Use the
*   functions EwBeginSubPath() or EwInitSubPath() in such application cases.
*
* ARGUMENTS:
*   aPath       - Pointer to the path containing the affected sub-path.
*   aSubPathNo  - Number identifying the sub-path within aPath to close. The
*     first sub-path has the number 0. The second 1, and so far.
*   aNoOfNodes  - The number of X,Y coordinate pairs to remove from the sub-
*     path starting with the very first node # 0.
*   aTranslateX,
*   aTranslateY - Offset to add to all coordinates after the content is
*     shifted.
*
* RETURN VALUE:
*   Returns the number of nodes removed from the sub-path or 0 if the sub-path
*   doesn't exist, is not initialized (see EwInitSubPath()), is empty or it has
*   been closed by preceding EwCloseSubPath() invocation.
*
*
*******************************************************************************/
XInt32 EwShiftSubPathNodes_( XPath* aPath, XInt32 aSubPathNo, XInt32 aNoOfNodes,
  XFloat aTranslateX, XFloat aTranslateY )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return 0;

    /* The sub-path is not initialized or it is empty or closed */
    if ( !*subPath || !(*subPath)->HasData || (*subPath)->IsClosed )
      return 0;

    /* There is nothing to remove */
    if ( aNoOfNodes <= 0 )
      return 0;

    /* Limit the max. number of nodes to remove from the sub-path */
    if ( aNoOfNodes > (*subPath)->NoOfEdges )
      aNoOfNodes = (*subPath)->NoOfEdges;

    /* Move the nodes in the path */
    EwMove((*subPath)->Data, ((float*)(*subPath)->Data) + aNoOfNodes * 2,
           ((*subPath)->NoOfEdges - aNoOfNodes + 1 ) * 2 * sizeof( float ));

    /* Then apply the horizontal translation to all remaining coordinates */
    if (( aTranslateX != 0.0f ) || ( aTranslateY != 0.0f ))
    {
      int    i = (*subPath)->NoOfEdges;
      float* d = (float*)((*subPath)->Data);

      for ( ; i >= 0; i--, d += 2 )
      {
        d[0] += aTranslateX;
        d[1] += aTranslateY;
      }
    }

    /* Update the path state */
    (*subPath)->IsOpened  = aNoOfNodes < (*subPath)->NoOfEdges;
    (*subPath)->NoOfEdges = (*subPath)->NoOfEdges - aNoOfNodes;
    (*subPath)->IsValid   = 0;
    aPath->IsValid        = 0;

    return aNoOfNodes;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    EW_UNUSED_ARG( aNoOfNodes );
    EW_UNUSED_ARG( aTranslateX );
    EW_UNUSED_ARG( aTranslateY );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwShiftSubPathNodes, XInt32, ( XPath* aPath,
  XInt32 aSubPathNo, XInt32 aNoOfNodes, XFloat aTranslateX,
  XFloat aTranslateY ), ( aPath, aSubPathNo, aNoOfNodes, aTranslateX,
  aTranslateY ))


/*******************************************************************************
* FUNCTION:
*   EwSetSubPathNode
*
* DESCRIPTION:
*   The function EwSetSubPathNode() modifies the X,Y coordinate of the given
*   node within the path. In this manner it is not necessary to re-initialize
*   and re-calculate the complete path if only few path corners do move.
*
*   Trying to modify a not existing node is ignored.
*
* ARGUMENTS:
*   aPath       - Pointer to the path containing the affected sub-path.
*   aSubPathNo  - Number identifying the sub-path within aPath to modify a node.
*     The first sub-path has the number 0. The second 1, and so far.
*   aNodeNo     - The path node (the corner) affected by the modification. The
*     nodes are counted starting with 0.
*   aX, aY      - The coordinates to assign to the affected node. The position
*     is transformed by using the path transformation matrix. See functions like
*     EwScalePathMatrix(), EwRotatePathMatrix(), etc.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwSetSubPathNode_( XPath* aPath, XInt32 aSubPathNo, XInt32 aNodeNo,
  XFloat aX, XFloat aY )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;
    float*     m       = aPath->Matrix;
    float      x       = aX;
    float      y       = aY;
    float*     d;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return;

    /* The sub-path is not initialized or there is no corresponding node */
    if ( !*subPath || ( aNodeNo > (*subPath)->NoOfEdges ) || ( aNodeNo < 0 ))
      return;

    /* Transform the positions? */
    if (( m[0] != 1.0f ) || ( m[1] != 0.0f ) || ( m[2] != 0.0f ) ||
        ( m[3] != 0.0f ) || ( m[4] != 1.0f ) || ( m[5] != 0.0f ))
    {
      x = aX * m[0] + aY * m[1] + m[2];
      y = aX * m[3] + aY * m[4] + m[5];
    }

    d = (float*)(*subPath)->Data;

    /* Store the new position in the corresponding node */
    d[ aNodeNo * 2 + 0 ] = x;
    d[ aNodeNo * 2 + 1 ] = y;

    /* Modifying the first node of a closed path affects also the last node */
    if ( !aNodeNo && (*subPath)->IsClosed )
    {
      d[(*subPath)->NoOfEdges * 2 + 0 ] = x;
      d[(*subPath)->NoOfEdges * 2 + 1 ] = y;
    }

    /* Modifying the last node of a closed path affects also the first node */
    if (( aNodeNo == (*subPath)->NoOfEdges ) && (*subPath)->IsClosed )
    {
      d[0] = x;
      d[1] = y;
    }

    /* After this operation the path needs an update */
    (*subPath)->IsValid = 0;
    aPath->IsValid      = 0;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    EW_UNUSED_ARG( aNodeNo );
    EW_UNUSED_ARG( aX );
    EW_UNUSED_ARG( aY );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwSetSubPathNode, ( XPath* aPath, XInt32 aSubPathNo,
  XInt32 aNodeNo, XFloat aX, XFloat aY ), ( aPath, aSubPathNo, aNodeNo, aX, aY ))


/*******************************************************************************
* FUNCTION:
*   EwGetSubPathNodeX
*
* DESCRIPTION:
*   The function EwGetSubPathNodeX() returns the X coordinate of the given
*   node within the path.
*
* ARGUMENTS:
*   aPath       - Pointer to the path containing the affected sub-path.
*   aSubPathNo  - Number identifying the sub-path within aPath to get the node
*     coordinate. The first sub-path has the number 0. The second 1, and so far.
*   aNodeNo     - The path node (the corner) affected by the query ioperation.
*     The nodes are counted starting with 0.
*
* RETURN VALUE:
*   Returns the X coordinate stored in the specified node or 0.0 if the sub-
*   path doesn't exist, is not initialized (see EwInitSubPath()) or the desired
*   node is not available in the sub-apth.
*
*******************************************************************************/
XFloat EwGetSubPathNodeX_( XPath* aPath, XInt32 aSubPathNo, XInt32 aNodeNo )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return 0.0f;

    /* The sub-path is not initialized or there is no corresponding node */
    if ( !*subPath || ( aNodeNo > (*subPath)->NoOfEdges ) || ( aNodeNo < 0 ))
      return 0.0f;

    /* Return the X coordinate */
    return ((float*)(*subPath)->Data)[ aNodeNo * 2 + 0 ];
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    EW_UNUSED_ARG( aNodeNo );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwGetSubPathNodeX, XFloat, ( XPath* aPath, XInt32 aSubPathNo,
  XInt32 aNodeNo ), ( aPath, aSubPathNo, aNodeNo ))


/*******************************************************************************
* FUNCTION:
*   EwGetSubPathNodeY
*
* DESCRIPTION:
*   The function EwGetSubPathNodeY() returns the Y coordinate of the given
*   node within the path.
*
* ARGUMENTS:
*   aPath       - Pointer to the path containing the affected sub-path.
*   aSubPathNo  - Number identifying the sub-path within aPath to get the node
*     coordinate. The first sub-path has the number 0. The second 1, and so far.
*   aNodeNo     - The path node (the corner) affected by the query ioperation.
*     The nodes are counted starting with 0.
*
* RETURN VALUE:
*   Returns the Y coordinate stored in the specified node or 0.0 if the sub-
*   path doesn't exist, is not initialized (see EwInitSubPath()) or the desired
*   node is not available in the sub-apth.
*
*******************************************************************************/
XFloat EwGetSubPathNodeY_( XPath* aPath, XInt32 aSubPathNo, XInt32 aNodeNo )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return 0.0f;

    /* The sub-path is not initialized or there is no corresponding node */
    if ( !*subPath || ( aNodeNo > (*subPath)->NoOfEdges ) || ( aNodeNo < 0 ))
      return 0.0f;

    /* Return the Y coordinate */
    return ((float*)(*subPath)->Data)[ aNodeNo * 2 + 1 ];
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    EW_UNUSED_ARG( aNodeNo );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwGetSubPathNodeY, XFloat, ( XPath* aPath, XInt32 aSubPathNo,
  XInt32 aNodeNo ), ( aPath, aSubPathNo, aNodeNo ))


/*******************************************************************************
* FUNCTION:
*   EwSetNoOfSubPathEdges
*
* DESCRIPTION:
*   The function EwSetNoOfSubPathEdges() provides a convenient way to change the
*   number of edges (straight line segments) the affected sub-path uses actually
*   to store its coordinates. In this manner, the sub-path can be truncated or
*   enhanced by new nodes.
*
*   In case the sub-path grows, the new appended nodes are pre-initialized with
*   the coordinates X=0, Y=0. Also, please note the maximum capacity (maximum
*   number of edges) the sub-path is able to store. This value is determined in
*   the invocation of the EwInitSubPath() function.
*
*   In order to query the number of edges stored actually in the sub-path use
*   the functions EwGetNoOfSubPathEdges(). The number of still free edges can
*   be queried by the function EwGetNoOfFreeSubPathEdges();
*
* ARGUMENTS:
*   aPath       - Pointer to the path containing the affected sub-path.
*   aSubPathNo  - Number identifying the sub-path within aPath to query the
*     information. The first sub-path has the number 0. The second 1, and so
*     far.
*   aNoOfEdges  - Number of edges to adapt the sub-path.
*
* RETURN VALUE:
*   Returns the number of edges added or removed from the sub-path. The positive
*   value represents the number of edges added to the sub-path. If the value is
*   negative, it represents the number of truncated edges.
*
*   If the sub-path has not been initialized previously by calling the function
*   EwInitSubPath(), the sub-path has been closed by EwCloseSubPath() or there
*   is no sufficient memory in the sub-path for the new edges, the function
*   fails and returns 0.
*
*******************************************************************************/
XInt32 EwSetNoOfSubPathEdges_( XPath* aPath, XInt32 aSubPathNo, XInt32 aNoOfEdges )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;
    int        delta;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return 0;

    /* The sub-path is not initialized or it is closed */
    if ( !*subPath || (*subPath)->IsClosed )
      return 0;

    /* Limit the specified number of edges to the capacity of the sub-path */
    if ( aNoOfEdges < 0                    ) aNoOfEdges = 0;
    if ( aNoOfEdges > (*subPath)->Capacity ) aNoOfEdges = (*subPath)->Capacity;

    /* The alternation of the sub-path */
    delta =  aNoOfEdges - (*subPath)->NoOfEdges;

    /* No changes in the sub-path */
    if ( !delta )
      return 0;

    /* Enlarge the sub-path? Fill the new entries with zero */
    if ( delta > 0 )
    {
      float* d = (float*)(*subPath)->Data + (*subPath)->NoOfEdges * 2 + 2;
      EwZero( d, delta * 2 * sizeof( float ));
    }

    /* Adapt the state information related to the path */
    (*subPath)->NoOfEdges = aNoOfEdges;
    (*subPath)->HasData   = aNoOfEdges > 0;
    (*subPath)->IsOpened  = aNoOfEdges > 0;
    (*subPath)->IsValid   = 0;
    aPath->IsValid        = 0;

    return delta;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    EW_UNUSED_ARG( aNoOfEdges );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwSetNoOfSubPathEdges, XInt32, ( XPath* aPath,
  XInt32 aSubPathNo, XInt32 aNoOfEdges ), ( aPath, aSubPathNo, aNoOfEdges ))


/*******************************************************************************
* FUNCTION:
*   EwGetNoOfSubPathEdges
*
* DESCRIPTION:
*   The function EwGetNoOfSubPathEdges() returns how many edges (straight line
*   segments) the affected sub-path actually store.
*
* ARGUMENTS:
*   aPath       - Pointer to the path containing the affected sub-path.
*   aSubPathNo  - Number identifying the sub-path within aPath to query the
*     information. The first sub-path has the number 0. The second 1, and so
*     far.
*
* RETURN VALUE:
*   Returns the number of edges existing actually in the sub-path or 0 if the
*   sub-path doesn't exist, is not initialized (see EwInitSubPath()) or is
*   empty.
*
*******************************************************************************/
XInt32 EwGetNoOfSubPathEdges_( XPath* aPath, XInt32 aSubPathNo )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return 0;

    /* The sub-path is not initialized */
    if ( !*subPath )
      return 0;

    return (*subPath)->NoOfEdges;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwGetNoOfSubPathEdges, XInt32, ( XPath* aPath,
  XInt32 aSubPathNo ), ( aPath, aSubPathNo ))


/*******************************************************************************
* FUNCTION:
*   EwGetNoOfFreeSubPathEdges
*
* DESCRIPTION:
*   The function EwGetNoOfFreeSubPathEdges() returns how many edges (straight
*   line segments) can still be added to the affected sub-path.
*
* ARGUMENTS:
*   aPath       - Pointer to the path containing the affected sub-path.
*   aSubPathNo  - Number identifying the sub-path within aPath to query the
*     information. The first sub-path has the number 0. The second 1, and so
*     far.
*
* RETURN VALUE:
*   Returns the number of edges the sub-path can additionally accomodate or 0
*   if the sub-path doesn't exist, is not initialized (see EwInitSubPath()), is
*   closed (see EwCloseSubPath()) or is full.
*
*******************************************************************************/
XInt32 EwGetNoOfFreeSubPathEdges_( XPath* aPath, XInt32 aSubPathNo )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return 0;

    /* The sub-path is not initialized or it is already closed */
    if ( !*subPath || (*subPath)->IsClosed )
      return 0;

    return (*subPath)->Capacity - (*subPath)->NoOfEdges;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwGetNoOfFreeSubPathEdges, XInt32, ( XPath* aPath,
  XInt32 aSubPathNo ), ( aPath, aSubPathNo ))


/*******************************************************************************
* FUNCTION:
*   EwIsSubPathClosed
*
* DESCRIPTION:
*   The function EwIsSubPathClosed() returns != 0 if the affected sub-path has
*   been closed by calling the function EwCloseSubPath(). Once closed, no new
*   path segments can be added to the sub-path.
*
* ARGUMENTS:
*   aPath       - Pointer to the path containing the affected sub-path.
*   aSubPathNo  - Number identifying the sub-path within aPath to query the
*     information. The first sub-path has the number 0. The second 1, and so
*     far.
*
* RETURN VALUE:
*   Returns != 0 if the sub-path has been closed.
*
*******************************************************************************/
XBool EwIsSubPathClosed_( XPath* aPath, XInt32 aSubPathNo )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ))
      return 0;

    return *subPath && (*subPath)->IsClosed;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwIsSubPathClosed, XBool, ( XPath* aPath, XInt32 aSubPathNo ),
  ( aPath, aSubPathNo ))


/*******************************************************************************
* FUNCTION:
*   EwGetSubPathBounds
*
* DESCRIPTION:
*   The function EwGetSubPathBounds() returns the rectangular area enclosing
*   all nodes of the affected sub-path. The position and the size of the area
*   are rounded to the near integer value.
*
* ARGUMENTS:
*   aPath       - Pointer to the path containing the affected sub-path.
*   aSubPathNo  - Number identifying the sub-path within aPath to query the
*     information. The first sub-path has the number 0. The second 1, and so
*     far.
*
* RETURN VALUE:
*   Returns the area. If the specified sub-path does not exist, the function
*   returns an empty rectangle.
*
*******************************************************************************/
XRect EwGetSubPathBounds_( XPath* aPath, XInt32 aSubPathNo )
{
  XRect empty = {{ 0, 0 }, { 0, 0 }};

  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XSubPath** subPath = (XSubPath**)aPath->SubPaths + aSubPathNo;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath || ( aSubPathNo >= aPath->MaxNoOfSubPaths ) || ( aSubPathNo < 0 ) ||
         !*subPath )
      return empty;

    UpdatePath( aPath );

    return (*subPath)->Bounds;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aSubPathNo );
    return empty;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwGetSubPathBounds, XRect, ( XPath* aPath, XInt32 aSubPathNo ),
  ( aPath, aSubPathNo ))


/*******************************************************************************
* FUNCTION:
*   EwGetPathBounds
*
* DESCRIPTION:
*   The function EwGetPathBounds() returns the rectangular area enclosing all
*   nodes of all sub-paths of the given path. The position and the size of the
*   area are rounded to the near integer value.
*
* ARGUMENTS:
*   aPath - Pointer to the path to query the information.
*
* RETURN VALUE:
*   Returns the area. If the specified path does not contain any edges, the
*   function returns an empty rectangle.
*
*******************************************************************************/
XRect EwGetPathBounds_( XPath* aPath )
{
  XRect empty = {{ 0, 0 }, { 0, 0 }};

  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* There is no corresponding sub-path */
    if ( !aPath )
      return empty;

    UpdatePath( aPath );

    return aPath->Bounds;
  #else
    EW_UNUSED_ARG( aPath );
    return empty;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwGetPathBounds, XRect, ( XPath* aPath ), ( aPath ))


/*******************************************************************************
* FUNCTION:
*   EwTranslatePathMatrix
*
* DESCRIPTION:
*   The function EwTranslatePathMatrix() applies the given displacement to the
*   path matrix. This corresponds to the translation of the origin of the path
*   coordinate system by the given values in the X- and Y-direction.
*
*   The modification of the path matrix affects the position of line segments
*   added later to the sub-paths of the path.
*
* ARGUMENTS:
*   aPath    - Pointer to the path to apply the transformation.
*   aDeltaX,
*   aDeltaY  - Displacement to apply on the transformation matrix.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwTranslatePathMatrix_( XPath* aPath, XFloat aDeltaX, XFloat aDeltaY )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    float* m = aPath->Matrix;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* No valid path */
    if ( !aPath )
      return;

    /* Multiply the existing matrix with a new matrix describing the translation */
    m[2] = m[2] + ( m[0] * aDeltaX ) + ( m[1] * aDeltaY );
    m[5] = m[5] + ( m[3] * aDeltaX ) + ( m[4] * aDeltaY );
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aDeltaX );
    EW_UNUSED_ARG( aDeltaY );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwTranslatePathMatrix, ( XPath* aPath, XFloat aDeltaX,
  XFloat aDeltaY ), ( aPath, aDeltaX, aDeltaY ))


/*******************************************************************************
* FUNCTION:
*   EwScalePathMatrix
*
* DESCRIPTION:
*   The function EwScalePathMatrix() applies the given factors to the path
*   matrix. This corresponds to the scaling of the path coordinate system by
*   the given values in the X- and Y-direction.
*
*   The modification of the path matrix affects the position of line segments
*   added later to the sub-paths of the path.
*
* ARGUMENTS:
*   aPath    - Pointer to the path to apply the transformation.
*   aScaleX,
*   aScaleY  - Scaling factors to apply on the transformation matrix.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwScalePathMatrix_( XPath* aPath, XFloat aScaleX, XFloat aScaleY )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    float* m = aPath->Matrix;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* No valid path */
    if ( !aPath )
      return;

    /* Multiply the existing matrix with a new matrix describing the scale
       operation */
    m[0] *= aScaleX; m[1] *= aScaleY;
    m[3] *= aScaleX; m[4] *= aScaleY;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aScaleX );
    EW_UNUSED_ARG( aScaleY );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwScalePathMatrix, ( XPath* aPath, XFloat aScaleX,
  XFloat aScaleY ), ( aPath, aScaleX, aScaleY ))


/*******************************************************************************
* FUNCTION:
*   EwRotatePathMatrix
*
* DESCRIPTION:
*   The function EwRotatePathMatrix() applies the given angle to the path matrix.
*   This corresponds to the rotation of the path coordinate system around its
*   origin position.
*
*   The modification of the path matrix affects the position of line segments
*   added later to the sub-paths of the path.
*
* ARGUMENTS:
*   aPath  - Pointer to the path to apply the transformation.
*   aAngle - Rotation angle to apply on the transformation matrix. The angle is
*     expressed in degree and measured clockwise.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwRotatePathMatrix_( XPath* aPath, XFloat aAngle )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    float* m   = aPath->Matrix;
    float  sin = EwMathSin( aAngle );
    float  cos = EwMathCos( aAngle );
    float  nm0, nm1, nm3, nm4;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* No valid path */
    if ( !aPath )
      return;

    /* Multiply the existing matrix with a new matrix describing the rotation */
    nm0 = ( m[0] *  cos ) + ( m[1] * sin );
    nm1 = ( m[0] * -sin ) + ( m[1] * cos );
    nm3 = ( m[3] *  cos ) + ( m[4] * sin );
    nm4 = ( m[3] * -sin ) + ( m[4] * cos );

    /* Store the resulting matrix */
    m[0] = nm0; m[1] = nm1;
    m[3] = nm3; m[4] = nm4;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aAngle );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwRotatePathMatrix, ( XPath* aPath, XFloat aAngle ),
  ( aPath, aAngle ))


/*******************************************************************************
* FUNCTION:
*   EwPushPathMatrix
*
* DESCRIPTION:
*   The function EwPushPathMatrix() stores the current state of the path matrix
*   on its internal stack. This is very useful during creation of complex paths.
*
*   To restore the matrix again use the function EwPopPathMatrix().
*
* ARGUMENTS:
*   aPath  - Pointer to the path to store its matrix.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwPushPathMatrix_( XPath* aPath )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    float*       m = aPath->Matrix;
    XPathMatrix* stack;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* No valid path */
    if ( !aPath )
      return;

    /* Allocate memory for the new matrix stack entry */
    do
      stack = EwAlloc( sizeof( *stack ));
    while ( !stack && EwImmediateReclaimMemory( 29 ));

    /* Failed to allocate the memory */
    if ( !stack )
    {
      EwError( 29 );
      return;
    }

    /* Store the actual matrix in the just created stack entry */
    stack->Matrix[0] = m[0]; stack->Matrix[1] = m[1]; stack->Matrix[2] = m[2];
    stack->Matrix[3] = m[3]; stack->Matrix[4] = m[4]; stack->Matrix[5] = m[5];

    /* ... and assign the new entry to the path */
    stack->Next        = aPath->MatrixStack;
    aPath->MatrixStack = stack;

    EwResourcesMemory += sizeof( *stack );

    /* Also track the max. memory pressure */
    if ( EwResourcesMemory > EwResourcesMemoryPeak )
      EwResourcesMemoryPeak = EwResourcesMemory;

    if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
      EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

  #else
    EW_UNUSED_ARG( aPath );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwPushPathMatrix, ( XPath* aPath ), ( aPath ))


/*******************************************************************************
* FUNCTION:
*   EwPopPathMatrix
*
* DESCRIPTION:
*   The function EwPopPathMatrix() restores the current state of the path matrix
*   from its internal stack. The matrix has to be stored by the preceding call
*   to the EwPushPathMatrix() function.
*
*   If the stack is already empty, the identity matrix is loaded.
*
* ARGUMENTS:
*   aPath  - Pointer to the path to restore its matrix.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwPopPathMatrix_( XPath* aPath )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    float*       m     = aPath->Matrix;
    XPathMatrix* stack = aPath->MatrixStack;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* No valid path */
    if ( !aPath )
      return;

    /* If there is matrix stored on the stack - load it back again */
    if ( stack )
    {
      /* Store the actual matrix in the just created stack entry */
      m[0] = stack->Matrix[0]; m[1] = stack->Matrix[1]; m[2] = stack->Matrix[2];
      m[3] = stack->Matrix[3]; m[4] = stack->Matrix[4]; m[5] = stack->Matrix[5];

      aPath->MatrixStack = stack->Next;
      EwResourcesMemory -= sizeof( *stack );

      /* release the memory used by the stack entry  */
      EwFree( stack );
    }

    /* Otherwise load the identity matrix */
    else
    {
      m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f;
      m[3] = 0.0f; m[4] = 1.0f; m[5] = 0.0f;
    }
  #else
    EW_UNUSED_ARG( aPath );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwPopPathMatrix, ( XPath* aPath ), ( aPath ))


/*******************************************************************************
* FUNCTION:
*   EwInitPathMatrix
*
* DESCRIPTION:
*   The function EwInitPathMatrix() loads the identity matrix in the path.
*
* ARGUMENTS:
*   aPath  - Pointer to the path to load the matrix.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwInitPathMatrix_( XPath* aPath )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    float* m = aPath->Matrix;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* No valid path */
    if ( !aPath )
      return;

    m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f;
    m[3] = 0.0f; m[4] = 1.0f; m[5] = 0.0f;
  #else
    EW_UNUSED_ARG( aPath );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwInitPathMatrix, ( XPath* aPath ), ( aPath ))


/*******************************************************************************
* FUNCTION:
*   EwSetPathMatrix
*
* DESCRIPTION:
*   The function EwSetPathMatrix() loads the matrix in the path with the given
*   components according to the image below:
*
*   +----+----+----+
*   | aA | aB | aC |
*   +----+----+----+
*   | aD | aE | aF |
*   +----+----+----+
*   | 0  | 0  |  1 |
*   +----+----+----+
*
* ARGUMENTS:
*   aPath  - Pointer to the path to load the matrix.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwSetPathMatrix_( XPath* aPath, XFloat aA, XFloat aB, XFloat aC, XFloat aD,
  XFloat aE, XFloat aF )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    float* m = aPath->Matrix;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* No valid path */
    if ( !aPath )
      return;

    m[0] = aA; m[1] = aB; m[2] = aC;
    m[3] = aD; m[4] = aE; m[5] = aF;
  #else
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aA );
    EW_UNUSED_ARG( aB );
    EW_UNUSED_ARG( aC );
    EW_UNUSED_ARG( aD );
    EW_UNUSED_ARG( aE );
    EW_UNUSED_ARG( aF );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwSetPathMatrix, ( XPath* aPath, XFloat aA, XFloat aB,
  XFloat aC, XFloat aD, XFloat aE, XFloat aF ), ( aPath, aA, aB, aC, aD, aE,
  aF ))


/*******************************************************************************
* FUNCTION:
*   EwFillPath
*
* DESCRIPTION:
*   The function EwFillPath() fills within the rectangular area aDstRect of
*   the given bitmap aDst a polygon determined by the data stored in aPath. The
*   polygon is filled with a color gradient specified by the four color
*   parameters aColorTL .. aColorBL.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst            - Destination bitmap.
*   aPath           - Data object providing the path information consisting of
*     one or more sub-paths. Sub-paths, which are opened, are automatically
*     closed by connecting their start and end positions with a straight line
*     segment. All path coordinates are assumed as being relative to the top-
*     left corner of the aDstRect area, or if aFlipY is != 0, relative to the
*     bottom-left corner.
*   aDstFrameNo     - Frame within the destination bitmap affected by the
*     drawing operation.
*   aClipRect       - Area to limit the drawing operation (Relative to the top-
*     left corner of the destination bitmap frame).
*   aDstRect        - Area to fill with the color gradient (Relative to the top-
*     left corner of the destination bitmap frame).
*   aFlipY          - If != 0, the coordinate system of the path is vertically
*     mirrored and its origin is moved to the bottom-left edge of aDstRect.
*   aOffset         - Offset to move the origin of the path coordinate system.
*     Changing this value scrolls the displayed path content.
*   aColorTL,
*   aColorTR,
*   aColorBR,
*   aColorBL        - Color values corresponding to the four corners of aDstRect.
*   aBlend          - If != 0, the drawn pixel will be alpha-blended with the
*     pixel in the background.
*   aAntialiased    - If != 0, the function applies antialiasing to the pixel.
*     The antialiasing is based on supersampling with 4 samples in X and Y
*     direction.
*   aNonZeroWinding - Controls the fill rule to be used by the algorithm. If
*     this parameter is == 0, the even-odd fill rule is used. If this parameter
*     is != 0, the non-zero winding rule is used.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwFillPath_( XBitmap* aDst, XPath* aPath, XInt32 aDstFrameNo,
  XRect aClipRect, XRect aDstRect, XBool aFlipY, XPoint aOffset,
  XColor aColorTL, XColor aColorTR, XColor aColorBR, XColor aColorBL,
  XBool aBlend, XBool aAntialiased, XBool aNonZeroWinding )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XBitmapFrame*   dst          = MapBitmapFrame( aDst, aDstFrameNo );
    XFillPolygon*   data;
    XIssue*         issue;
    XTask*          task;
    int             x1, y1, x2, y2;
    unsigned int    colorTL      = PACK_COLOR( aColorTL, aDst );
    unsigned int    colorTR      = PACK_COLOR( aColorTR, aDst );
    unsigned int    colorBL      = PACK_COLOR( aColorBL, aDst );
    unsigned int    colorBR      = PACK_COLOR( aColorBR, aDst );
    XSubPath**      subPaths     = aPath? aPath->SubPaths : 0;
    int             noOfSubPaths = aPath? aPath->MaxNoOfSubPaths : 0;
    int             dstX         = aOffset.X;
    int             dstY         = aOffset.Y;
    int             flipY        = aFlipY? -1 : 1;
    int             count;
    int*            bufPath;

    /* Only screen/native surfaces are allowed as the destination */
    if ( !dst || (( dst->Surface->Format != EW_PIXEL_FORMAT_SCREEN ) &&
                  ( dst->Surface->Format != EW_PIXEL_FORMAT_NATIVE )))
    {
      EwErrorPD( 157, aDst, aDstFrameNo );
      return;
    }

    /* The support for Native surface as destination is disabled. */
    #ifdef EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION
      if ( dst->Surface->Format == EW_PIXEL_FORMAT_NATIVE )
      {
        EwErrorPD( 352, aDst, aDstFrameNo );
        return;
      }
    #endif

    /* Bitmaps loaded from resources can't be modified by drawing operations */
    if ( dst->Surface->Tag1 || dst->Surface->Tag2 )
    {
      EwErrorPD( 342, aDst, aDstFrameNo );
      return;
    }

    /* The support for color gradients is disabled. */
    #ifdef EW_DONT_USE_GRADIENTS
      if ( IS_LINEAR_GRADIENT4( colorTL, colorTR, colorBL, colorBR ) ||
           IS_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
      {
        EwError( 372 );
        return;
      }
    #endif

    /* No polygon information to draw */
    if ( !aPath )
      return;

    /* Eventually update internal path information if the path data has been
       modified in the past */
    UpdatePath( aPath );

    /* No polygon information to draw */
    if ( !aPath->NoOfEdges )
      return;

    /* Estimate the origin of the path coordinate system and the area occupied by
       the drawn polygon. Note, the coordinate system can be mirrored vertically */
    if ( !aFlipY )
    {
      dstY += aDstRect.Point1.Y;
      y1    = dstY + aPath->Bounds.Point1.Y - 1;
      y2    = dstY + aPath->Bounds.Point2.Y + 1;
    }
    else
    {
      dstY +=  aDstRect.Point2.Y;
      y1    = dstY - aPath->Bounds.Point2.Y - 1;
      y2    = dstY - aPath->Bounds.Point1.Y + 1;
    }

    dstX  += aDstRect.Point1.X;
    x1     = dstX + aPath->Bounds.Point1.X - 1;
    x2     = dstX + aPath->Bounds.Point2.X + 1;
    dstX   = ( dstX + dst->Origin.X ) << 4;
    dstY   = ( dstY + dst->Origin.Y ) << 4;

    /* Limit the clipping area to the area resulting from the polygon */
    x1 = MAX( x1, aClipRect.Point1.X );
    y1 = MAX( y1, aClipRect.Point1.Y );
    x2 = MIN( x2, aClipRect.Point2.X );
    y2 = MIN( y2, aClipRect.Point2.Y );

    /* Limit the fill area to the frame boundary and to the clipping area */
    x1 = MAX3( x1, aDstRect.Point1.X, 0 );
    y1 = MAX3( y1, aDstRect.Point1.Y, 0 );
    x2 = MIN3( x2, aDstRect.Point2.X, aDst->FrameSize.X );
    y2 = MIN3( y2, aDstRect.Point2.Y, aDst->FrameSize.Y );

    /* Nothing to do? */
    if (( x2 <= x1 ) || ( y2 <= y1 ) ||
        ( aBlend && IS_TRANSPARENT4( colorTL, colorTR, colorBL, colorBR )))
      return;

    /* Start the preparation of a new drawing operation */
    if (( issue = EwInitIssue( dst->Surface )) == 0 )
    {
      EwErrorPD( 125, aDst, 0 );
      return;
    }

    /* Estimate how large is the area on the issue buffer to allocate for the
       complete path data. The value is expressed in 'integers'. This is the
       worst case. */
    count = aPath->NoOfClosedPaths * 3 + aPath->NoOfOpenedPaths * 5 + 1 +
            aPath->NoOfEdges * 2;

    /* Test whether there is sufficient space on the issue buffer for the
       complete path data in the above worst case calculation */
    data = EwAllocTaskData( issue, sizeof( *data ) + count * sizeof( int ));

    /* Not enough space in the issue buffer? Flush the buffer */
    if ( !data )
    {
      EwDoneIssue( dst->Surface );
      EwFlushTasks( dst->Surface );

      /* Reinitialize the issue buffer */
      if (( issue = EwInitIssue( dst->Surface )) == 0 )
      {
        EwErrorPD( 125, aDst, 0 );
        return;
      }
    }

    /* Ok. There is enough space available. Release the memory again since it
       will be allocated step by step for every sub-path individually */
    else
      EwFreeTaskData( issue, data );

    /* Reserve memory for the operation description data structure and at least
       one integer indicating the end of the path data  */
    data    = EwAllocTaskData( issue, sizeof( *data ) + sizeof( int ));
    bufPath = (int*)( data + 1 );

    /* Initialize the drawing task */
    data->DstX1          = (short)( aDstRect.Point1.X + dst->Origin.X );
    data->DstY1          = (short)( aDstRect.Point1.Y + dst->Origin.Y );
    data->DstX2          = (short)( aDstRect.Point2.X + dst->Origin.X );
    data->DstY2          = (short)( aDstRect.Point2.Y + dst->Origin.Y );
    data->Colors[0]      = colorTL;
    data->Colors[1]      = colorTR;
    data->Colors[2]      = colorBR;
    data->Colors[3]      = colorBL;
    data->NonZeroWinding = aNonZeroWinding;
    data->Orientation    = 0;

    /* Now process the sub-paths of the path individually and append the resulting
       path information at the end of the just allocated data structure */
    for ( ; noOfSubPaths > 0; noOfSubPaths--, subPaths++ )
      if ( *subPaths && (*subPaths)->IsValid && (*subPaths)->NoOfEdges )
      {
        int noOfClosedPaths = (*subPaths)->IsClosed? 1 : 0;
        int noOfOpenedPaths = (*subPaths)->IsOpened? 1 : 0;
        int noOfEdges       = (*subPaths)->NoOfEdges;

        /* Release issue buffer memory unused by the preceding sub-path */
        EwFreeTaskData( issue, bufPath );

        /* Estimate how large is the area on the issue buffer to allocate for the
           actual sub-path data. The value is expressed in 'integers'. This is the
           worst case. Later the unused memory is released again */
        count = noOfClosedPaths * 3 + noOfOpenedPaths * 5 + 1 + noOfEdges * 2;

        /* Try to reserve memory to store the processed path data. If it was not
           possible, discard the eventually already prepared path information and
           return without drawing the path. */
        if (( bufPath = EwAllocTaskData( issue, count * sizeof( int ))) == 0 )
        {
          EwFreeTaskData( issue, data );
          EwDoneIssue( dst->Surface );
          EwErrorPD( 187, aDst, count );
          return;
        }

        /* Now copy the sub-path information into the issue buffer. Convert the
           coordinates in integer with .4 bit precision, etc. */
        bufPath = PrepareForFillPath( *subPaths, bufPath, dstX, dstY, flipY );
      }

    /* Terminate the path and release unused memory */
    *bufPath++ = 0;
    EwFreeTaskData( issue, bufPath );

    /* Enqueue the drawing operation by the issue */
    task = EwAllocTask( issue, 0 );
    task->Token     = EW_TASKID_FILL_POLYGON;
    task->Data      = data;
    task->X1        = (short)( x1 + dst->Origin.X );
    task->Y1        = (short)( y1 + dst->Origin.Y );
    task->X2        = (short)( x2 + dst->Origin.X );
    task->Y2        = (short)( y2 + dst->Origin.Y );
    task->Flags     = (short)(( aBlend? EW_TASK_ALPHABLEND : 0 ) |
                              ( aAntialiased? EW_TASK_HIGH_QUALITY : 0 ));

    /* What to do with the 4 colors? */
    #ifndef EW_DONT_USE_GRADIENTS
      if ( IS_LINEAR_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
        task->Flags |= EW_TASK_LINEAR_GRADIENT;
      else if ( IS_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
        task->Flags |= EW_TASK_GRADIENT;
      else
    #endif
      task->Flags |= EW_TASK_SOLID;

    /* Close the preparation. This may flush the issue */
    EwDoneIssue( dst->Surface );
  #else
    EW_UNUSED_ARG( aDst );
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aDstFrameNo );
    EW_UNUSED_ARG( aClipRect );
    EW_UNUSED_ARG( aDstRect );
    EW_UNUSED_ARG( aFlipY );
    EW_UNUSED_ARG( aOffset );
    EW_UNUSED_ARG( aColorTL );
    EW_UNUSED_ARG( aColorTR );
    EW_UNUSED_ARG( aColorBR );
    EW_UNUSED_ARG( aColorBL );
    EW_UNUSED_ARG( aBlend );
    EW_UNUSED_ARG( aAntialiased );
    EW_UNUSED_ARG( aNonZeroWinding );
    EwError( 192 );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwFillPath, ( XBitmap* aDst, XPath* aPath,
  XInt32 aDstFrameNo, XRect aClipRect, XRect aDstRect, XBool aFlipY,
  XPoint aOffset, XColor aColorTL, XColor aColorTR, XColor aColorBR,
  XColor aColorBL, XBool aBlend, XBool aAntialiased, XBool aNonZeroWinding ),
( aDst, aPath, aDstFrameNo, aClipRect, aDstRect, aFlipY, aOffset, aColorTL,
  aColorTR, aColorBR, aColorBL, aBlend, aAntialiased, aNonZeroWinding ))


/*******************************************************************************
* FUNCTION:
*   EwFillPathWithGradient
*
* DESCRIPTION:
*   The function EwFillPathWithGradient() fills within the rectangular area
*   aDstRect of the given bitmap aDst a polygon determined by the data stored in
*   aPath. The polygon is filled with a color gradient specified in aGradient.
*   The origin of the gradient coordinate system is mapped to the top left
*   corner of aDstRect area.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst            - Destination bitmap.
*   aPath           - Data object providing the path information consisting of
*     one or more sub-paths. Sub-paths, which are opened, are automatically
*     closed by connecting their start and end positions with a straight line
*     segment. All path coordinates are assumed as being relative to the top-
*     left corner of the aDstRect area, or if aFlipY is != 0, relative to the
*     bottom-left corner.
*   aDstFrameNo     - Frame within the destination bitmap affected by the
*     drawing operation.
*   aClipRect       - Area to limit the drawing operation (Relative to the top-
*     left corner of the destination bitmap frame).
*   aDstRect        - Area to fill with the color gradient (Relative to the top-
*     left corner of the destination bitmap frame).
*   aFlipY          - If != 0, the coordinate system of the path is vertically
*     mirrored and its origin is moved to the bottom-left edge of aDstRect.
*   aOffset         - Offset to move the origin of the path coordinate system.
*     Changing this value scrolls the displayed path content.
*   aGradient       - Color gradient to use for filling the path.
*   aOpacity        - Modulates the opacity of the pixel data resulting from
*     the gradient operation. This property can take values in range of 0 .. 255.
*   aBlend          - If != 0, the drawn pixel will be alpha-blended with the
*     pixel in the background.
*   aAntialiased    - If != 0, the function applies antialiasing to the pixel.
*     The antialiasing is based on supersampling with 4 samples in X and Y
*     direction.
*   aNonZeroWinding - Controls the fill rule to be used by the algorithm. If
*     this parameter is == 0, the even-odd fill rule is used. If this parameter
*     is != 0, the non-zero winding rule is used.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwFillPathWithGradient_( XBitmap* aDst, XPath* aPath, XInt32 aDstFrameNo,
  XRect aClipRect, XRect aDstRect, XBool aFlipY, XPoint aOffset, 
  XColorGradient* aGradient, XInt32 aOpacity, XBool aBlend, XBool aAntialiased,
  XBool aNonZeroWinding )
{
  #if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
    XBitmapFrame*  dst          = MapBitmapFrame( aDst, aDstFrameNo );
    XFillGradient* data;
    XIssue*        issue;
    XTask*         task;
    int            x1, y1, x2, y2;
    XSubPath**     subPaths     = aPath? aPath->SubPaths : 0;
    int            noOfSubPaths = aPath? aPath->MaxNoOfSubPaths : 0;
    int            dstX         = aOffset.X;
    int            dstY         = aOffset.Y;
    int            flipY        = aFlipY? -1 : 1;
    int            count;
    int*           bufPath;
    XGradientStop* stops;
    int            i;

    /* Only screen/native surfaces are allowed as the destination */
    if ( !dst || (( dst->Surface->Format != EW_PIXEL_FORMAT_SCREEN ) &&
                  ( dst->Surface->Format != EW_PIXEL_FORMAT_NATIVE )))
    {
      EwErrorPD( 535, aDst, aDstFrameNo );
      return;
    }

    /* The support for Native surface as destination is disabled. */
    #ifdef EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION
      if ( dst->Surface->Format == EW_PIXEL_FORMAT_NATIVE )
      {
        EwErrorPD( 537, aDst, aDstFrameNo );
        return;
      }
    #endif

    /* Bitmaps loaded from resources can't be modified by drawing operations */
    if ( dst->Surface->Tag1 || dst->Surface->Tag2 )
    {
      EwErrorPD( 539, aDst, aDstFrameNo );
      return;
    }

    /* No polygon or gradient information to draw */
    if ( !aPath || !aGradient || ( !aGradient->IsLinear && !aGradient->IsRadial ))
      return;

    /* Eventually update internal path information if the path data has been
       modified in the past */
    UpdatePath( aPath );

    /* No polygon information to draw */
    if ( !aPath->NoOfEdges )
      return;

    /* Limit opacity */
    if ( aOpacity < 0   ) aOpacity = 0;
    if ( aOpacity > 255 ) aOpacity = 255;

    /* Nothing to draw? */
    if ( !aOpacity && aBlend )
      return;

    /* Estimate the origin of the path coordinate system and the area occupied by
       the drawn polygon. Note, the coordinate system can be mirrored vertically */
    if ( !aFlipY )
    {
      dstY += aDstRect.Point1.Y;
      y1    = dstY + aPath->Bounds.Point1.Y - 1;
      y2    = dstY + aPath->Bounds.Point2.Y + 1;
    }
    else
    {
      dstY +=  aDstRect.Point2.Y;
      y1    = dstY - aPath->Bounds.Point2.Y - 1;
      y2    = dstY - aPath->Bounds.Point1.Y + 1;
    }

    dstX  += aDstRect.Point1.X;
    x1     = dstX + aPath->Bounds.Point1.X - 1;
    x2     = dstX + aPath->Bounds.Point2.X + 1;
    dstX   = ( dstX + dst->Origin.X ) << 4;
    dstY   = ( dstY + dst->Origin.Y ) << 4;

    /* Limit the clipping area to the area resulting from the polygon */
    x1 = MAX( x1, aClipRect.Point1.X );
    y1 = MAX( y1, aClipRect.Point1.Y );
    x2 = MIN( x2, aClipRect.Point2.X );
    y2 = MIN( y2, aClipRect.Point2.Y );

    /* Limit the fill area to the frame boundary and to the clipping area */
    x1 = MAX3( x1, aDstRect.Point1.X, 0 );
    y1 = MAX3( y1, aDstRect.Point1.Y, 0 );
    x2 = MIN3( x2, aDstRect.Point2.X, aDst->FrameSize.X );
    y2 = MIN3( y2, aDstRect.Point2.Y, aDst->FrameSize.Y );

    /* Nothing to do? */
    if (( x2 <= x1 ) || ( y2 <= y1 ))
      return;

    /* Start the preparation of a new drawing operation */
    if (( issue = EwInitIssue( dst->Surface )) == 0 )
    {
      EwErrorPD( 541, aDst, 0 );
      return;
    }

    /* Estimate how large is the area on the issue buffer to allocate for the
       complete path data. The value is expressed in 'integers'. This is the
       worst case. */
    count = aPath->NoOfClosedPaths * 3 + aPath->NoOfOpenedPaths * 5 + 1 +
            aPath->NoOfEdges * 2;

    /* Test whether there is sufficient space on the issue buffer for the
       complete path data in the above worst case calculation as well as
       the color stops */
    data = EwAllocTaskData( issue, sizeof( *data ) + count * sizeof( int ) +
                          (( aGradient->NoOfStops - 1 ) * sizeof( *stops )));

    /* Not enough space in the issue buffer? Flush the buffer */
    if ( !data )
    {
      EwDoneIssue( dst->Surface );
      EwFlushTasks( dst->Surface );

      /* Reinitialize the issue buffer */
      if (( issue = EwInitIssue( dst->Surface )) == 0 )
      {
        EwErrorPD( 541, aDst, 0 );
        return;
      }
    }

    /* Ok. There is enough space available. Release the memory again since it
       will be allocated step by step for every sub-path individually */
    else
      EwFreeTaskData( issue, data );

    /* Reserve memory for the operation description data structure, the color
       stops and at least one integer indicating the end of the path data  */
    data    = EwAllocTaskData( issue, sizeof( *data ) + sizeof( int ) +
                             (( aGradient->NoOfStops - 1 ) * sizeof( *stops )));
    stops   = (XGradientStop*)( data + 1 ) - 1;
    bufPath = (int*)( stops + aGradient->NoOfStops );

    /* Initialize the drawing task */
    data->DstX1          = (short)( aDstRect.Point1.X + dst->Origin.X );
    data->DstY1          = (short)( aDstRect.Point1.Y + dst->Origin.Y );
    data->DstX2          = (short)( aDstRect.Point2.X + dst->Origin.X );
    data->DstY2          = (short)( aDstRect.Point2.Y + dst->Origin.Y );
    data->NonZeroWinding = aNonZeroWinding;
    data->Orientation    = 0;
    data->IsRadial       = aGradient->IsRadial;
    data->StartX         = (short)( aGradient->Start.X +
                                    dst->Origin.X + aDstRect.Point1.X );
    data->StartY         = (short)( aGradient->Start.Y +
                                    dst->Origin.Y + aDstRect.Point1.Y );
    data->EndX           = (short)( aGradient->End.X   +
                                    dst->Origin.X + aDstRect.Point1.X );
    data->EndY           = (short)( aGradient->End.Y   +
                                    dst->Origin.Y + aDstRect.Point1.Y );
    data->Radius         = (short)aGradient->Radius;
    data->NoOfStops      = (short)aGradient->NoOfStops;
    data->Matrix[0]      = aGradient->Matrix[0];
    data->Matrix[1]      = aGradient->Matrix[1];
    data->Matrix[2]      = aGradient->Matrix[2];
    data->Matrix[3]      = aGradient->Matrix[3];

    /* Copy gradient information */
    for ( i = 0; i < aGradient->NoOfStops; i++ )
    {
      XColor color = aGradient->Stops[i].Color;

      color.Alpha = ( color.Alpha * ( aOpacity + 1 )) >> 8;
      stops[i].Offset = aGradient->Stops[i].Offset;
      stops[i].Color  = PACK_COLOR( color, aDst );
    }

    /* Ensure the color stops are stored in sorted order */
    SortColorStops( stops, aGradient->NoOfStops );

    /* Now process the sub-paths of the path individually and append the resulting
       path information at the end of the just allocated data structure */
    for ( ; noOfSubPaths > 0; noOfSubPaths--, subPaths++ )
      if ( *subPaths && (*subPaths)->IsValid && (*subPaths)->NoOfEdges )
      {
        int noOfClosedPaths = (*subPaths)->IsClosed? 1 : 0;
        int noOfOpenedPaths = (*subPaths)->IsOpened? 1 : 0;
        int noOfEdges       = (*subPaths)->NoOfEdges;

        /* Release issue buffer memory unused by the preceding sub-path */
        EwFreeTaskData( issue, bufPath );

        /* Estimate how large is the area on the issue buffer to allocate for the
           actual sub-path data. The value is expressed in 'integers'. This is the
           worst case. Later the unused memory is released again */
        count = noOfClosedPaths * 3 + noOfOpenedPaths * 5 + 1 + noOfEdges * 2;

        /* Try to reserve memory to store the processed path data. If it was not
           possible, discard the eventually already prepared path information and
           return without drawing the path. */
        if (( bufPath = EwAllocTaskData( issue, count * sizeof( int ))) == 0 )
        {
          EwFreeTaskData( issue, data );
          EwDoneIssue( dst->Surface );
          EwErrorPD( 543, aDst, count );
          return;
        }

        /* Now copy the sub-path information into the issue buffer. Convert the
           coordinates in integer with .4 bit precision, etc. */
        bufPath = PrepareForFillPath( *subPaths, bufPath, dstX, dstY, flipY );
      }

    /* Terminate the path and release unused memory */
    *bufPath++ = 0;
    EwFreeTaskData( issue, bufPath );

    /* Enqueue the drawing operation by the issue */
    task = EwAllocTask( issue, 0 );
    task->Token     = EW_TASKID_FILL_GRADIENT;
    task->Data      = data;
    task->X1        = (short)( x1 + dst->Origin.X );
    task->Y1        = (short)( y1 + dst->Origin.Y );
    task->X2        = (short)( x2 + dst->Origin.X );
    task->Y2        = (short)( y2 + dst->Origin.Y );
    task->Flags     = (short)(( aBlend? EW_TASK_ALPHABLEND : 0 ) |
                              ( aAntialiased? EW_TASK_HIGH_QUALITY : 0 ) |
                                EW_TASK_GRADIENT );

    /* Close the preparation. This may flush the issue */
    EwDoneIssue( dst->Surface );
  #else
    EW_UNUSED_ARG( aDst );
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aDstFrameNo );
    EW_UNUSED_ARG( aClipRect );
    EW_UNUSED_ARG( aDstRect );
    EW_UNUSED_ARG( aFlipY );
    EW_UNUSED_ARG( aOffset );
    EW_UNUSED_ARG( aGradient );
    EW_UNUSED_ARG( aOpacity );
    EW_UNUSED_ARG( aBlend );
    EW_UNUSED_ARG( aAntialiased );
    EW_UNUSED_ARG( aNonZeroWinding );
    EwError( 522 );
  #endif /* EW_DONT_USE_GRADIENTS && EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwFillPathWithGradient, ( XBitmap* aDst, XPath* aPath,
  XInt32 aDstFrameNo, XRect aClipRect, XRect aDstRect, XBool aFlipY,
  XPoint aOffset, XColorGradient* aGradient, XInt32 aOpacity, XBool aBlend,
  XBool aAntialiased, XBool aNonZeroWinding ),
( aDst, aPath, aDstFrameNo, aClipRect, aDstRect, aFlipY, aOffset, aGradient,
  aOpacity, aBlend, aAntialiased, aNonZeroWinding ))


/*******************************************************************************
* FUNCTION:
*   EwStrokePath
*
* DESCRIPTION:
*   The function EwStrokePath() strokes within the rectangular area aDstRect of
*   the given bitmap aDst a path determined by the data stored in aPath. The
*   path is stroked with line thickness specified in the parameter aWidth and
*   color gradient specified by the four color parameters aColorTL .. aColorBL.
*   With the parameter aStyle the cap and join points of the path are configured.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst            - Destination bitmap.
*   aPath           - Data object providing the path information consisting of
*     one or more sub-paths. Sub-paths, which are opened, are automatically
*     closed by connecting their start and end positions with a straight line
*     segment. All path coordinates are assumed as being relative to the top-
*     left corner of the aDstRect area, or if aFlipY is != 0, relative to the
*     bottom-left corner.
*   aDstFrameNo     - Frame within the destination bitmap affected by the
*     drawing operation.
*   aClipRect       - Area to limit the drawing operation (Relative to the top-
*     left corner of the destination bitmap frame).
*   aDstRect        - Area to fill with the color gradient (Relative to the top-
*     left corner of the destination bitmap frame).
*   aFlipY          - If != 0, the coordinate system of the path is vertically
*     mirrored and its origin is moved to the bottom-left edge of aDstRect.
*   aOffset         - Offset to move the origin of the path coordinate system.
*     Changing this value scrolls the displayed path content.
*   aWidth          - The width in pixel to stroke the path.
*   aMatrix0 ..
*   aMatrix3        - 2x2 component matrix describing scaling/rotation to apply
*     on the calculated outline coordinates. This has the effect of the stroke
*     being stretched.
*   aStyle          - Flags specifying how the path caps and join points should
*     appear. See the enumeration EW_PATH_CAP_XXX and EW_PATH_JOIN_XXX.
*   aMiterLimit     - In case aStyle is configured with EW_PATH_JOIN_MITER, this
*     parameter imposes a limit on the ratio between the miter length and the
*     half of the line thickness aWidth. If the limit is exceeded for a corner,
*     the corner appears as bevel (EW_PATH_JOIN_BEVEL) instead of miter.
*   aColorTL,
*   aColorTR,
*   aColorBR,
*   aColorBL        - Color values corresponding to the four corners of aDstRect.
*   aBlend          - If != 0, the drawn pixel will be alpha-blended with the
*     pixel in the background.
*   aAntialiased    - If != 0, the function applies antialiasing to the pixel.
*     The antialiasing is based on supersampling with 4 samples in X and Y
*     direction.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwStrokePath_( XBitmap* aDst, XPath* aPath, XInt32 aDstFrameNo,
  XRect aClipRect, XRect aDstRect, XBool aFlipY, XPoint aOffset, XFloat aWidth,
  XFloat aMatrix0, XFloat aMatrix1, XFloat aMatrix2, XFloat aMatrix3,
  XUInt32 aStyle, XFloat aMiterLimit, XColor aColorTL, XColor aColorTR,
  XColor aColorBR, XColor aColorBL, XBool aBlend, XBool aAntialiased )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XBitmapFrame*   dst          = MapBitmapFrame( aDst, aDstFrameNo );
    XFillPolygon*   data;
    XIssue*         issue;
    XTask*          task;
    int             x1, y1, x2, y2;
    unsigned int    colorTL      = PACK_COLOR( aColorTL, aDst );
    unsigned int    colorTR      = PACK_COLOR( aColorTR, aDst );
    unsigned int    colorBL      = PACK_COLOR( aColorBL, aDst );
    unsigned int    colorBR      = PACK_COLOR( aColorBR, aDst );
    XSubPath**      subPaths     = aPath? aPath->SubPaths : 0;
    int             noOfSubPaths = aPath? aPath->MaxNoOfSubPaths : 0;
    int             roundSteps   = 0;
    float           roundSin     = 0.0f;
    float           roundCos     = 0.0f;
    float           width2       = aWidth / 2.0f;
    float           strokeX      = width2 * ( aMatrix0 + aMatrix1 );
    float           strokeY      = width2 * ( aMatrix2 + aMatrix3 );
    float           stroke       = MAX( ABS( strokeX ), ABS( strokeY ));
    unsigned int    styleStart   = aStyle & 0x0000FF;
    unsigned int    styleEnd     = aStyle & 0x00FF00;
    unsigned int    styleJoin    = aStyle & 0xFF0000;
    int             dstX         = aOffset.X;
    int             dstY         = aOffset.Y;
    int             flipY        = aFlipY? -1 : 1;
    float           matrix[4]    = { aMatrix0, aMatrix1, aMatrix2, aMatrix3 };
    int             margin;
    int             count;
    int*            bufPath;

    /* Very thin lines don't need the rounded caps. Use the triangle
       instead */
    if (( styleStart == EW_PATH_CAP_START_ROUND ) && ( aWidth < 4.0f ))
      styleStart = EW_PATH_CAP_START_TRIANGLE;

    if (( styleEnd == EW_PATH_CAP_END_ROUND ) && ( aWidth < 4.0f ))
      styleEnd = EW_PATH_CAP_END_TRIANGLE;

    /* ... not rounded join points */
    if (( styleJoin == EW_PATH_JOIN_ROUND ) && ( aWidth < 3.0f ))
      styleJoin = EW_PATH_JOIN_BEVEL;

    /* Only screen/native surfaces are allowed as the destination */
    if ( !dst || (( dst->Surface->Format != EW_PIXEL_FORMAT_SCREEN ) &&
                  ( dst->Surface->Format != EW_PIXEL_FORMAT_NATIVE )))
    {
      EwErrorPD( 158, aDst, aDstFrameNo );
      return;
    }

    /* The support for Native surface as destination is disabled. */
    #ifdef EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION
      if ( dst->Surface->Format == EW_PIXEL_FORMAT_NATIVE )
      {
        EwErrorPD( 353, aDst, aDstFrameNo );
        return;
      }
    #endif

    /* Bitmaps loaded from resources can't be modified by drawing operations */
    if ( dst->Surface->Tag1 || dst->Surface->Tag2 )
    {
      EwErrorPD( 343, aDst, aDstFrameNo );
      return;
    }

    /* The support for color gradients is disabled. */
    #ifdef EW_DONT_USE_GRADIENTS
      if ( IS_LINEAR_GRADIENT4( colorTL, colorTR, colorBL, colorBR ) ||
           IS_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
      {
        EwError( 373 );
        return;
      }
    #endif

    /* No polygon information to draw */
    if ( !aPath || ( aWidth <= 0.0f ))
      return;

    /* Eventually update internal path information if the path data has been
       modified in the past */
    UpdatePath( aPath );

    /* No polygon information to draw */
    if ( !aPath->NoOfEdges )
      return;

    /* Calculate the max. (worst case) margin around the original path, which
       completely encloses the resulting polygon */
    if ( styleJoin == EW_PATH_JOIN_MITER )
      margin = (int)( MAX( aMiterLimit, 1.0f ) * stroke );
    else if (( styleStart == EW_PATH_CAP_START_SQUARE ) ||
             ( styleEnd   == EW_PATH_CAP_END_SQUARE  ))
      margin = (int)( stroke * 1.5f );
    else
      margin = (int)( stroke + 0.5f );

    /* Estimate the origin of the path coordinate system and the area occupied by
       the drawn polygon. Note, the coordinate system can be mirrored vertically.
       Take in account the width of the stroken path and estimate the max. area
       occupied by it */
    if ( !aFlipY )
    {
      dstY += aDstRect.Point1.Y;
      y1    = dstY + aPath->Bounds.Point1.Y - margin - 1;
      y2    = dstY + aPath->Bounds.Point2.Y + margin + 1;
    }
    else
    {
      dstY += aDstRect.Point2.Y;
      y1    = dstY - aPath->Bounds.Point2.Y - margin - 1;
      y2    = dstY - aPath->Bounds.Point1.Y + margin + 1;
    }

    dstX  += aDstRect.Point1.X;
    x1     = dstX + aPath->Bounds.Point1.X - margin - 2;
    x2     = dstX + aPath->Bounds.Point2.X + margin + 1;
    dstX   = ( dstX + dst->Origin.X ) << 4;
    dstY   = ( dstY + dst->Origin.Y ) << 4;

    /* Take in account the expected polygon boundary */
    x1 = MAX( x1, aClipRect.Point1.X );
    y1 = MAX( y1, aClipRect.Point1.Y );
    x2 = MIN( x2, aClipRect.Point2.X );
    y2 = MIN( y2, aClipRect.Point2.Y );

    /* Limit the fill area to the frame boundary and to the clipping area */
    x1 = MAX3( x1, aDstRect.Point1.X, 0 );
    y1 = MAX3( y1, aDstRect.Point1.Y, 0 );
    x2 = MIN3( x2, aDstRect.Point2.X, aDst->FrameSize.X );
    y2 = MIN3( y2, aDstRect.Point2.Y, aDst->FrameSize.Y );

    /* Nothing to do? */
    if (( x2 <= x1 ) || ( y2 <= y1 ) ||
        ( aBlend && IS_TRANSPARENT4( colorTL, colorTR, colorBL, colorBR )))
      return;

    /* Calculate the number of additional edges to add at cap and join points in
       order to let them appear as circles. The thicker the path the more edges
       are needed for get good looking results. Knowing the number of additional
       edges estimate the parameters for rotation matrix to use when calculating
       the round outline */
    if (( styleStart == EW_PATH_CAP_START_ROUND ) ||
        ( styleEnd   == EW_PATH_CAP_END_ROUND ) ||
        ( styleJoin  == EW_PATH_JOIN_ROUND ))
    {
      roundSteps = (int)EwMathCeil( stroke * 2.0f * 0.15f + 0.5f ) + 2;
      roundCos   = EwMathCos( 180.0f / roundSteps );
      roundSin   = EwMathSin( 180.0f / roundSteps );
    }

    /* Start the preparation of a new drawing operation */
    if (( issue = EwInitIssue( dst->Surface )) == 0 )
    {
      EwErrorPD( 126, aDst, 0 );
      return;
    }

    /* Estimate how large is the area on the issue buffer to allocate for the
       complete path data. The value is expressed in 'integers'. It takes in
       account all the special cases like path stroken with rounded corners, etc.
       At first we calculate with the worst case. Later, unused memory will be
       released again. */
    count = aPath->NoOfOpenedPaths * 3 + aPath->NoOfClosedPaths * 6 + 1 +
            aPath->NoOfEdges * 8 +
            ( aPath->NoOfOpenedPaths *
            (( styleStart == EW_PATH_CAP_START_ROUND    )? 2 * ( roundSteps - 1 ) :
             ( styleStart == EW_PATH_CAP_START_TRIANGLE )? 2 : 0 )) +
            ( aPath->NoOfOpenedPaths *
            (( styleEnd == EW_PATH_CAP_END_ROUND        )? 2 * ( roundSteps - 1 ) :
             ( styleEnd == EW_PATH_CAP_END_TRIANGLE     )? 2 : 0 )) +
            (( aPath->NoOfEdges - aPath->NoOfOpenedPaths ) *
            (( styleJoin == EW_PATH_JOIN_ROUND )? 2 * ( roundSteps - 1 ) :
            (( styleJoin == EW_PATH_JOIN_MITER )? 2 : 0 )));

    /* Test whether there is sufficient space on the issue buffer for the complete
       path data in the above worst case calculation */
    data = EwAllocTaskData( issue, sizeof( *data ) + count * sizeof( int ));

    /* Not enough space in the issue buffer? Flush the buffer */
    if ( !data )
    {
      EwDoneIssue( dst->Surface );
      EwFlushTasks( dst->Surface );

      /* Reinitialize the issue buffer */
      if (( issue = EwInitIssue( dst->Surface )) == 0 )
      {
        EwErrorPD( 126, aDst, 0 );
        return;
      }
    }

    /* Ok. There is enough space available. Release the memory again since it
       will be allocated step by step for every sub-path individually */
    else
      EwFreeTaskData( issue, data );

    /* Reserve memory for the operation description data structure and at least
       one integer indicating the end of the path data  */
    data    = EwAllocTaskData( issue, sizeof( *data ) + sizeof( int ));
    bufPath = (int*)( data + 1 );

    /* Initialize the drawing task */
    data->DstX1          = (short)( aDstRect.Point1.X + dst->Origin.X );
    data->DstY1          = (short)( aDstRect.Point1.Y + dst->Origin.Y );
    data->DstX2          = (short)( aDstRect.Point2.X + dst->Origin.X );
    data->DstY2          = (short)( aDstRect.Point2.Y + dst->Origin.Y );
    data->Colors[0]      = colorTL;
    data->Colors[1]      = colorTR;
    data->Colors[2]      = colorBR;
    data->Colors[3]      = colorBL;
    data->NonZeroWinding = 1;
    data->Orientation    = 0;

    /* Now process the sub-paths of the path individually and append the resulting
       path information at the end of the just allocated data structure */
    for ( ; noOfSubPaths > 0; noOfSubPaths--, subPaths++ )
      if ( *subPaths && (*subPaths)->IsValid && (*subPaths)->NoOfEdges )
      {
        XSubPath* subPath         = *subPaths;
        int       noOfOpenedPaths = subPath->IsOpened? 1 : 0;
        int       noOfClosedPaths = subPath->IsClosed? 1 : 0;

        /* Release issue buffer memory unused by the preceding sub-path */
        EwFreeTaskData( issue, bufPath );

        /* Again estimate the memory needed for the actual sub-path. */
        count = noOfOpenedPaths * 3 + noOfClosedPaths * 6 + 1 +
                subPath->NoOfEdges * 8 +
                ( noOfOpenedPaths *
                (( styleStart == EW_PATH_CAP_START_ROUND    )? 2 * ( roundSteps - 1 ) :
                 ( styleStart == EW_PATH_CAP_START_TRIANGLE )? 2 : 0 )) +
                ( noOfOpenedPaths *
                (( styleEnd == EW_PATH_CAP_END_ROUND        )? 2 * ( roundSteps - 1 ) :
                 ( styleEnd == EW_PATH_CAP_END_TRIANGLE     )? 2 : 0 )) +
                (( subPath->NoOfEdges - noOfOpenedPaths ) *
                (( styleJoin == EW_PATH_JOIN_ROUND )? 2 * ( roundSteps - 1 ) :
                (( styleJoin == EW_PATH_JOIN_MITER )? 2 : 0 )));

        /* Try to reserve memory to store the processed path data. If it was not
           possible, discard the eventually already prepared path information and
           return without drawing the path. */
        if (( bufPath = EwAllocTaskData( issue, count * sizeof( int ))) == 0 )
        {
          EwFreeTaskData( issue, data );
          EwDoneIssue( dst->Surface );
          EwErrorPD( 188, aDst, count );
          return;
        }

        /* Evaluate all sub-paths from the array aPaths. Note the area at the end
           is used as temporary buffer for precalculated edge specific information
           like the unit vector and the edge direction relative to the preceding
           edge */
        bufPath = PrepareForStrokePath( subPath, styleStart, styleEnd, styleJoin,
                    aMiterLimit, width2, bufPath, (float*)( bufPath + count ),
                    dstX, dstY, flipY, roundSteps, roundCos, roundSin, matrix );
      }

    /* Terminate the path and release unused memory */
    *bufPath++ = 0;
    EwFreeTaskData( issue, bufPath );

    /* Enqueue the drawing operation by the issue */
    task = EwAllocTask( issue, 0 );
    task->Token     = EW_TASKID_FILL_POLYGON;
    task->Data      = data;
    task->X1        = (short)( x1 + dst->Origin.X );
    task->Y1        = (short)( y1 + dst->Origin.Y );
    task->X2        = (short)( x2 + dst->Origin.X );
    task->Y2        = (short)( y2 + dst->Origin.Y );
    task->Flags     = (short)(( aBlend? EW_TASK_ALPHABLEND : 0 ) |
                              ( aAntialiased? EW_TASK_HIGH_QUALITY : 0 ));

    /* What to do with the 4 colors? */
    #ifndef EW_DONT_USE_GRADIENTS
      if ( IS_LINEAR_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
        task->Flags |= EW_TASK_LINEAR_GRADIENT;
      else if ( IS_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
        task->Flags |= EW_TASK_GRADIENT;
      else
    #endif
      task->Flags |= EW_TASK_SOLID;

    /* Close the preparation. This may flush the issue */
    EwDoneIssue( dst->Surface );
  #else
    EW_UNUSED_ARG( aDst );
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aDstFrameNo );
    EW_UNUSED_ARG( aClipRect );
    EW_UNUSED_ARG( aDstRect );
    EW_UNUSED_ARG( aFlipY );
    EW_UNUSED_ARG( aOffset );
    EW_UNUSED_ARG( aWidth );
    EW_UNUSED_ARG( aMatrix0 );
    EW_UNUSED_ARG( aMatrix1 );
    EW_UNUSED_ARG( aMatrix2 );
    EW_UNUSED_ARG( aMatrix3 );
    EW_UNUSED_ARG( aStyle );
    EW_UNUSED_ARG( aMiterLimit );
    EW_UNUSED_ARG( aColorTL );
    EW_UNUSED_ARG( aColorTR );
    EW_UNUSED_ARG( aColorBR );
    EW_UNUSED_ARG( aColorBL );
    EW_UNUSED_ARG( aBlend );
    EW_UNUSED_ARG( aAntialiased );
    EwError( 193 );
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwStrokePath, ( XBitmap* aDst, XPath* aPath,
  XInt32 aDstFrameNo, XRect aClipRect, XRect aDstRect, XBool aFlipY,
  XPoint aOffset, XFloat aWidth, XFloat aMatrix0, XFloat aMatrix1,
  XFloat aMatrix2, XFloat aMatrix3, XUInt32 aStyle, XFloat aMiterLimit,
  XColor aColorTL, XColor aColorTR, XColor aColorBR, XColor aColorBL,
  XBool aBlend, XBool aAntialiased ), ( aDst, aPath, aDstFrameNo, aClipRect,
  aDstRect, aFlipY, aOffset, aWidth, aMatrix0, aMatrix1, aMatrix2, aMatrix3, 
  aStyle, aMiterLimit, aColorTL, aColorTR, aColorBR, aColorBL, aBlend,
  aAntialiased ))


/*******************************************************************************
* FUNCTION:
*   EwStrokePathWithGradient
*
* DESCRIPTION:
*   The function EwStrokePathWithGradient() strokes within the rectangular area
*   aDstRect of the given bitmap aDst a path determined by the data stored in
*   aPath. The path is stroked with line thickness specified in the parameter
*   aWidth and a color gradient specified in aGradient. The origin of the
*   gradient coordinate system is mapped to the top left corner of aDstRect area.
*   With the parameter aStyle the cap and join points of the path are configured.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst            - Destination bitmap.
*   aPath           - Data object providing the path information consisting of
*     one or more sub-paths. Sub-paths, which are opened, are automatically
*     closed by connecting their start and end positions with a straight line
*     segment. All path coordinates are assumed as being relative to the top-
*     left corner of the aDstRect area, or if aFlipY is != 0, relative to the
*     bottom-left corner.
*   aDstFrameNo     - Frame within the destination bitmap affected by the
*     drawing operation.
*   aClipRect       - Area to limit the drawing operation (Relative to the top-
*     left corner of the destination bitmap frame).
*   aDstRect        - Area to fill with the color gradient (Relative to the top-
*     left corner of the destination bitmap frame).
*   aFlipY          - If != 0, the coordinate system of the path is vertically
*     mirrored and its origin is moved to the bottom-left edge of aDstRect.
*   aOffset         - Offset to move the origin of the path coordinate system.
*     Changing this value scrolls the displayed path content.
*   aWidth          - The width in pixel to stroke the path.
*   aMatrix0 ..
*   aMatrix3        - 2x2 component matrix describing scaling/rotation to apply
*     on the calculated outline coordinates. This has the effect of the stroke
*     being stretched.
*   aStyle          - Flags specifying how the path caps and join points should
*     appear. See the enumeration EW_PATH_CAP_XXX and EW_PATH_JOIN_XXX.
*   aMiterLimit     - In case aStyle is configured with EW_PATH_JOIN_MITER, this
*     parameter imposes a limit on the ratio between the miter length and the
*     half of the line thickness aWidth. If the limit is exceeded for a corner,
*     the corner appears as bevel (EW_PATH_JOIN_BEVEL) instead of miter.
*   aGradient       - Color gradient to use for stroking the path.
*   aOpacity        - Modulates the opacity of the pixel data resulting from
*     the gradient operation. This property can take values in range of 0 .. 255.
*   aBlend          - If != 0, the drawn pixel will be alpha-blended with the
*     pixel in the background.
*   aAntialiased    - If != 0, the function applies antialiasing to the pixel.
*     The antialiasing is based on supersampling with 4 samples in X and Y
*     direction.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwStrokePathWithGradient_( XBitmap* aDst, XPath* aPath, XInt32 aDstFrameNo,
  XRect aClipRect, XRect aDstRect, XBool aFlipY, XPoint aOffset, XFloat aWidth,
  XFloat aMatrix0, XFloat aMatrix1, XFloat aMatrix2, XFloat aMatrix3,
  XUInt32 aStyle, XFloat aMiterLimit, XColorGradient* aGradient, XInt32 aOpacity,
  XBool aBlend, XBool aAntialiased )
{
  #if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
    XBitmapFrame*  dst          = MapBitmapFrame( aDst, aDstFrameNo );
    XFillGradient* data;
    XIssue*        issue;
    XTask*         task;
    int            x1, y1, x2, y2;
    XSubPath**     subPaths     = aPath? aPath->SubPaths : 0;
    int            noOfSubPaths = aPath? aPath->MaxNoOfSubPaths : 0;
    int            roundSteps   = 0;
    float          roundSin     = 0.0f;
    float          roundCos     = 0.0f;
    float          width2       = aWidth / 2.0f;
    float          strokeX      = width2 * ( aMatrix0 + aMatrix1 );
    float          strokeY      = width2 * ( aMatrix2 + aMatrix3 );
    float          stroke       = MAX( ABS( strokeX ), ABS( strokeY ));
    unsigned int   styleStart   = aStyle & 0x0000FF;
    unsigned int   styleEnd     = aStyle & 0x00FF00;
    unsigned int   styleJoin    = aStyle & 0xFF0000;
    int            dstX         = aOffset.X;
    int            dstY         = aOffset.Y;
    int            flipY        = aFlipY? -1 : 1;
    float          matrix[4]    = { aMatrix0, aMatrix1, aMatrix2, aMatrix3 };
    int            margin;
    int            count;
    int*           bufPath;
    XGradientStop* stops;
    int            i;

    /* Very thin lines don't need the rounded caps. Use the triangle
       instead */
    if (( styleStart == EW_PATH_CAP_START_ROUND ) && ( aWidth < 4.0f ))
      styleStart = EW_PATH_CAP_START_TRIANGLE;

    if (( styleEnd == EW_PATH_CAP_END_ROUND ) && ( aWidth < 4.0f ))
      styleEnd = EW_PATH_CAP_END_TRIANGLE;

    /* ... not rounded join points */
    if (( styleJoin == EW_PATH_JOIN_ROUND ) && ( aWidth < 3.0f ))
      styleJoin = EW_PATH_JOIN_BEVEL;

    /* Only screen/native surfaces are allowed as the destination */
    if ( !dst || (( dst->Surface->Format != EW_PIXEL_FORMAT_SCREEN ) &&
                  ( dst->Surface->Format != EW_PIXEL_FORMAT_NATIVE )))
    {
      EwErrorPD( 536, aDst, aDstFrameNo );
      return;
    }

    /* The support for Native surface as destination is disabled. */
    #ifdef EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION
      if ( dst->Surface->Format == EW_PIXEL_FORMAT_NATIVE )
      {
        EwErrorPD( 538, aDst, aDstFrameNo );
        return;
      }
    #endif

    /* Bitmaps loaded from resources can't be modified by drawing operations */
    if ( dst->Surface->Tag1 || dst->Surface->Tag2 )
    {
      EwErrorPD( 540, aDst, aDstFrameNo );
      return;
    }

    /* No polygon or gradient information to draw */
    if ( !aPath || !aGradient || ( !aGradient->IsLinear && !aGradient->IsRadial ))
      return;

    /* No polygon information to draw */
    if ( !aPath || ( aWidth <= 0.0f ))
      return;

    /* Eventually update internal path information if the path data has been
       modified in the past */
    UpdatePath( aPath );

    /* No polygon information to draw */
    if ( !aPath->NoOfEdges )
      return;

    /* Limit opacity */
    if ( aOpacity < 0   ) aOpacity = 0;
    if ( aOpacity > 255 ) aOpacity = 255;

    /* Nothing to draw? */
    if ( !aOpacity && aBlend )
      return;

    /* Calculate the max. (worst case) margin around the original path, which
       completely encloses the resulting polygon */
    if ( styleJoin == EW_PATH_JOIN_MITER )
      margin = (int)( MAX( aMiterLimit, 1.0f ) * stroke );
    else if (( styleStart == EW_PATH_CAP_START_SQUARE ) ||
             ( styleEnd   == EW_PATH_CAP_END_SQUARE  ))
      margin = (int)( stroke * 1.5f );
    else
      margin = (int)( stroke + 0.5f );

    /* Estimate the origin of the path coordinate system and the area occupied by
       the drawn polygon. Note, the coordinate system can be mirrored vertically.
       Take in account the width of the stroken path and estimate the max. area
       occupied by it */
    if ( !aFlipY )
    {
      dstY += aDstRect.Point1.Y;
      y1    = dstY + aPath->Bounds.Point1.Y - margin - 1;
      y2    = dstY + aPath->Bounds.Point2.Y + margin + 1;
    }
    else
    {
      dstY += aDstRect.Point2.Y;
      y1    = dstY - aPath->Bounds.Point2.Y - margin - 1;
      y2    = dstY - aPath->Bounds.Point1.Y + margin + 1;
    }

    dstX  += aDstRect.Point1.X;
    x1     = dstX + aPath->Bounds.Point1.X - margin - 2;
    x2     = dstX + aPath->Bounds.Point2.X + margin + 1;
    dstX   = ( dstX + dst->Origin.X ) << 4;
    dstY   = ( dstY + dst->Origin.Y ) << 4;

    /* Take in account the expected polygon boundary */
    x1 = MAX( x1, aClipRect.Point1.X );
    y1 = MAX( y1, aClipRect.Point1.Y );
    x2 = MIN( x2, aClipRect.Point2.X );
    y2 = MIN( y2, aClipRect.Point2.Y );

    /* Limit the fill area to the frame boundary and to the clipping area */
    x1 = MAX3( x1, aDstRect.Point1.X, 0 );
    y1 = MAX3( y1, aDstRect.Point1.Y, 0 );
    x2 = MIN3( x2, aDstRect.Point2.X, aDst->FrameSize.X );
    y2 = MIN3( y2, aDstRect.Point2.Y, aDst->FrameSize.Y );

    /* Nothing to do? */
    if (( x2 <= x1 ) || ( y2 <= y1 ))
      return;

    /* Calculate the number of additional edges to add at cap and join points in
       order to let them appear as circles. The thicker the path the more edges
       are needed for get good looking results. Knowing the number of additional
       edges estimate the parameters for rotation matrix to use when calculating
       the round outline */
    if (( styleStart == EW_PATH_CAP_START_ROUND ) ||
        ( styleEnd   == EW_PATH_CAP_END_ROUND ) ||
        ( styleJoin  == EW_PATH_JOIN_ROUND ))
    {
      roundSteps = (int)EwMathCeil( stroke * 2.0f * 0.15f + 0.5f ) + 2;
      roundCos   = EwMathCos( 180.0f / roundSteps );
      roundSin   = EwMathSin( 180.0f / roundSteps );
    }

    /* Start the preparation of a new drawing operation */
    if (( issue = EwInitIssue( dst->Surface )) == 0 )
    {
      EwErrorPD( 542, aDst, 0 );
      return;
    }

    /* Estimate how large is the area on the issue buffer to allocate for the
       complete path data. The value is expressed in 'integers'. It takes in
       account all the special cases like path stroken with rounded corners, etc.
       At first we calculate with the worst case. Later, unused memory will be
       released again. */
    count = aPath->NoOfOpenedPaths * 3 + aPath->NoOfClosedPaths * 6 + 1 +
            aPath->NoOfEdges * 8 +
            ( aPath->NoOfOpenedPaths *
            (( styleStart == EW_PATH_CAP_START_ROUND    )? 2 * ( roundSteps - 1 ) :
             ( styleStart == EW_PATH_CAP_START_TRIANGLE )? 2 : 0 )) +
            ( aPath->NoOfOpenedPaths *
            (( styleEnd == EW_PATH_CAP_END_ROUND        )? 2 * ( roundSteps - 1 ) :
             ( styleEnd == EW_PATH_CAP_END_TRIANGLE     )? 2 : 0 )) +
            (( aPath->NoOfEdges - aPath->NoOfOpenedPaths ) *
            (( styleJoin == EW_PATH_JOIN_ROUND )? 2 * ( roundSteps - 1 ) :
            (( styleJoin == EW_PATH_JOIN_MITER )? 2 : 0 )));

    /* Test whether there is sufficient space on the issue buffer for the
       complete path data in the above worst case calculation as well as
       the color stops */
    data = EwAllocTaskData( issue, sizeof( *data ) + count * sizeof( int ) +
                          (( aGradient->NoOfStops - 1 ) * sizeof( *stops )));

    /* Not enough space in the issue buffer? Flush the buffer */
    if ( !data )
    {
      EwDoneIssue( dst->Surface );
      EwFlushTasks( dst->Surface );

      /* Reinitialize the issue buffer */
      if (( issue = EwInitIssue( dst->Surface )) == 0 )
      {
        EwErrorPD( 542, aDst, 0 );
        return;
      }
    }

    /* Ok. There is enough space available. Release the memory again since it
       will be allocated step by step for every sub-path individually */
    else
      EwFreeTaskData( issue, data );

    /* Reserve memory for the operation description data structure, the color
       stops and at least one integer indicating the end of the path data  */
    data    = EwAllocTaskData( issue, sizeof( *data ) + sizeof( int ) +
                             (( aGradient->NoOfStops - 1 ) * sizeof( *stops )));
    stops   = (XGradientStop*)( data + 1 ) - 1;
    bufPath = (int*)( stops + aGradient->NoOfStops );

    /* Initialize the drawing task */
    data->DstX1          = (short)( aDstRect.Point1.X + dst->Origin.X );
    data->DstY1          = (short)( aDstRect.Point1.Y + dst->Origin.Y );
    data->DstX2          = (short)( aDstRect.Point2.X + dst->Origin.X );
    data->DstY2          = (short)( aDstRect.Point2.Y + dst->Origin.Y );
    data->NonZeroWinding = 1;
    data->Orientation    = 0;
    data->IsRadial       = aGradient->IsRadial;
    data->StartX         = (short)( aGradient->Start.X +
                                    dst->Origin.X + aDstRect.Point1.X );
    data->StartY         = (short)( aGradient->Start.Y +
                                    dst->Origin.Y + aDstRect.Point1.Y );
    data->EndX           = (short)( aGradient->End.X   +
                                    dst->Origin.X + aDstRect.Point1.X );
    data->EndY           = (short)( aGradient->End.Y   +
                                    dst->Origin.Y + aDstRect.Point1.Y );
    data->Radius         = (short)aGradient->Radius;
    data->NoOfStops      = (short)aGradient->NoOfStops;
    data->Matrix[0]      = aGradient->Matrix[0];
    data->Matrix[1]      = aGradient->Matrix[1];
    data->Matrix[2]      = aGradient->Matrix[2];
    data->Matrix[3]      = aGradient->Matrix[3];

    /* Copy gradient information */
    for ( i = 0; i < aGradient->NoOfStops; i++ )
    {
      XColor color = aGradient->Stops[i].Color;

      color.Alpha = ( color.Alpha * ( aOpacity + 1 )) >> 8;
      stops[i].Offset = aGradient->Stops[i].Offset;
      stops[i].Color  = PACK_COLOR( color, aDst );
    }

    /* Ensure the color stops are stored in sorted order */
    SortColorStops( stops, aGradient->NoOfStops );

    /* Now process the sub-paths of the path individually and append the resulting
       path information at the end of the just allocated data structure */
    for ( ; noOfSubPaths > 0; noOfSubPaths--, subPaths++ )
      if ( *subPaths && (*subPaths)->IsValid && (*subPaths)->NoOfEdges )
      {
        XSubPath* subPath         = *subPaths;
        int       noOfOpenedPaths = subPath->IsOpened? 1 : 0;
        int       noOfClosedPaths = subPath->IsClosed? 1 : 0;

        /* Release issue buffer memory unused by the preceding sub-path */
        EwFreeTaskData( issue, bufPath );

        /* Again estimate the memory needed for the actual sub-path. */
        count = noOfOpenedPaths * 3 + noOfClosedPaths * 6 + 1 +
                subPath->NoOfEdges * 8 +
                ( noOfOpenedPaths *
                (( styleStart == EW_PATH_CAP_START_ROUND    )? 2 * ( roundSteps - 1 ) :
                 ( styleStart == EW_PATH_CAP_START_TRIANGLE )? 2 : 0 )) +
                ( noOfOpenedPaths *
                (( styleEnd == EW_PATH_CAP_END_ROUND        )? 2 * ( roundSteps - 1 ) :
                 ( styleEnd == EW_PATH_CAP_END_TRIANGLE     )? 2 : 0 )) +
                (( subPath->NoOfEdges - noOfOpenedPaths ) *
                (( styleJoin == EW_PATH_JOIN_ROUND )? 2 * ( roundSteps - 1 ) :
                (( styleJoin == EW_PATH_JOIN_MITER )? 2 : 0 )));

        /* Try to reserve memory to store the processed path data. If it was not
           possible, discard the eventually already prepared path information and
           return without drawing the path. */
        if (( bufPath = EwAllocTaskData( issue, count * sizeof( int ))) == 0 )
        {
          EwFreeTaskData( issue, data );
          EwDoneIssue( dst->Surface );
          EwErrorPD( 544, aDst, count );
          return;
        }

        /* Evaluate all sub-paths from the array aPaths. Note the area at the end
           is used as temporary buffer for precalculated edge specific information
           like the unit vector and the edge direction relative to the preceding
           edge */
        bufPath = PrepareForStrokePath( subPath, styleStart, styleEnd, styleJoin,
                    aMiterLimit, width2, bufPath, (float*)( bufPath + count ),
                    dstX, dstY, flipY, roundSteps, roundCos, roundSin, matrix );
      }

    /* Terminate the path and release unused memory */
    *bufPath++ = 0;
    EwFreeTaskData( issue, bufPath );

    /* Enqueue the drawing operation by the issue */
    task = EwAllocTask( issue, 0 );
    task->Token     = EW_TASKID_FILL_GRADIENT;
    task->Data      = data;
    task->X1        = (short)( x1 + dst->Origin.X );
    task->Y1        = (short)( y1 + dst->Origin.Y );
    task->X2        = (short)( x2 + dst->Origin.X );
    task->Y2        = (short)( y2 + dst->Origin.Y );
    task->Flags     = (short)(( aBlend? EW_TASK_ALPHABLEND : 0 ) |
                              ( aAntialiased? EW_TASK_HIGH_QUALITY : 0 ) |
                                EW_TASK_GRADIENT );

    /* Close the preparation. This may flush the issue */
    EwDoneIssue( dst->Surface );
  #else
    EW_UNUSED_ARG( aDst );
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aDstFrameNo );
    EW_UNUSED_ARG( aClipRect );
    EW_UNUSED_ARG( aDstRect );
    EW_UNUSED_ARG( aFlipY );
    EW_UNUSED_ARG( aOffset );
    EW_UNUSED_ARG( aWidth );
    EW_UNUSED_ARG( aMatrix0 );
    EW_UNUSED_ARG( aMatrix1 );
    EW_UNUSED_ARG( aMatrix2 );
    EW_UNUSED_ARG( aMatrix3 );
    EW_UNUSED_ARG( aStyle );
    EW_UNUSED_ARG( aMiterLimit );
    EW_UNUSED_ARG( aGradient );
    EW_UNUSED_ARG( aOpacity );
    EW_UNUSED_ARG( aBlend );
    EW_UNUSED_ARG( aAntialiased );
    EwError( 523 );
  #endif /* EW_DONT_USE_GRADIENTS && EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_VOID_FUNC( EwStrokePathWithGradient, ( XBitmap* aDst,
  XPath* aPath, XInt32 aDstFrameNo, XRect aClipRect, XRect aDstRect,
  XBool aFlipY, XPoint aOffset, XFloat aWidth, XFloat aMatrix0, XFloat aMatrix1,
  XFloat aMatrix2, XFloat aMatrix3, XUInt32 aStyle, XFloat aMiterLimit,
  XColorGradient* aGradient, XInt32 aOpacity, XBool aBlend, XBool aAntialiased ),
  ( aDst, aPath, aDstFrameNo, aClipRect, aDstRect, aFlipY, aOffset, aWidth,
    aMatrix0, aMatrix1, aMatrix2, aMatrix3, aStyle, aMiterLimit, aGradient,
    aOpacity, aBlend, aAntialiased ))


#ifndef EW_DONT_USE_PATH_FUNCTIONS

/* The following internal function rasterizes within an ALPHA8 surface a shape
   determined by the aPath data. The function returns != 0 if the operation was
   successfull. */
static int FillPathInSurfaceMemory( XSurfaceMemory* aMemory, XPoint aSize,
  XPath* aPath, XBool aFlipY, XPoint aOffset, XBool aAntialiased, 
  XBool aNonZeroWinding )
{
    XSubPath** subPaths     = aPath? aPath->SubPaths : 0;
    int        noOfSubPaths = aPath? aPath->MaxNoOfSubPaths : 0;
    int        dstX         = aOffset.X;
    int        dstY         = aOffset.Y;
    int        flipY        = aFlipY? -1 : 1;
    int        x1, y1, x2, y2;
    int        count;
    int*       bufPath;
    int*       bufPath2;

    /* Eventually update internal path information if the path data has been
       modified in the past */
    UpdatePath( aPath );

    /* Estimate the origin of the path coordinate system and the area occupied by
       the drawn polygon. Note, the coordinate system can be mirrored vertically */
    if ( !aFlipY )
    {
      y1    = dstY + aPath->Bounds.Point1.Y - 1;
      y2    = dstY + aPath->Bounds.Point2.Y + 1;
    }
    else
    {
      dstY += aSize.Y;
      y1    = dstY - aPath->Bounds.Point2.Y - 1;
      y2    = dstY - aPath->Bounds.Point1.Y + 1;
    }

    x1   = dstX + aPath->Bounds.Point1.X - 1;
    x2   = dstX + aPath->Bounds.Point2.X + 1;
    dstX = dstX << 4;
    dstY = dstY << 4;

    /* Limit the fill area to the frame boundary */
    x1 = MAX( x1, 0 );
    y1 = MAX( y1, 0 );
    x2 = MIN( x2, aSize.X );
    y2 = MIN( y2, aSize.Y );

    /* Estimate how large should be the buffer to allocate for the path data.
       The value is expressed in 'integers'. This is the worst case. */
    count = aPath->NoOfClosedPaths * 3 + aPath->NoOfOpenedPaths * 5 + 1 +
            aPath->NoOfEdges * 2;

    /* Get a storage area for the polygon data */
    do
      bufPath = bufPath2 = EwAlloc( count * sizeof( int ));
    while ( !bufPath && EwImmediateReclaimMemory( 30 ));

    /* No memory for the buffer */
    if ( !bufPath )
    {
      EwError( 30 );
      return 0;
    }

    /* Track the temporary used memory */
    EwResourcesMemory += count * sizeof( int );

    /* Also track the max. memory pressure */
    if ( EwResourcesMemory > EwResourcesMemoryPeak )
      EwResourcesMemoryPeak = EwResourcesMemory;

    if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
      EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

    /* Clear the entire surface */
    #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
      EwZero( aMemory->Pixel1, aMemory->Pitch1Y * aSize.X );
    #else
      EwZero( aMemory->Pixel1, aMemory->Pitch1Y * aSize.Y );
    #endif

    /* Now process the sub-paths of the path individually and append the resulting
       path information at the end of the just allocated data structure */
    for ( ; noOfSubPaths > 0; noOfSubPaths--, subPaths++ )
    {
      #if EW_SURFACE_ROTATION != 0
        int* bufPath3 = bufPath2 + 1;
      #endif

      if ( !*subPaths || !(*subPaths)->IsValid || !(*subPaths)->NoOfEdges )
        continue;

      bufPath2 = PrepareForFillPath( *subPaths, bufPath2, dstX, dstY, flipY );

      #if EW_SURFACE_ROTATION == 90
        for ( ; bufPath3 < bufPath2; bufPath3 += 2 )
        {
          int x = bufPath3[0];
          bufPath3[0] = ( aSize.Y << 4 ) - bufPath3[1];
          bufPath3[1] = x;
        }
      #endif

      #if EW_SURFACE_ROTATION == 180
        for ( ; bufPath3 < bufPath2; bufPath3 += 2 )
        {
          bufPath3[0] = ( aSize.X << 4 ) - bufPath3[0];
          bufPath3[1] = ( aSize.Y << 4 ) - bufPath3[1];
        }
      #endif

      #if EW_SURFACE_ROTATION == 270
        for ( ; bufPath3 < bufPath2; bufPath3 += 2 )
        {
          int y = bufPath3[1];
          bufPath3[1] = ( aSize.X << 4 ) - bufPath3[0];
          bufPath3[0] = y;
        }
      #endif
    }

    /* Terminate the path information */
    *bufPath2 = 0;

    /* Rasterize the path data within the surface memory */
    #if EW_SURFACE_ROTATION == 0
      EwRasterAlpha8Polygon( aMemory, bufPath, x1, y1, x2 - x1, y2 - y1,
                             x1 << 4, y1 << 4, aAntialiased, aNonZeroWinding );
    #endif

    #if EW_SURFACE_ROTATION == 90
      EwRasterAlpha8Polygon( aMemory, bufPath, aSize.Y - y2, x1, y2 - y1,
                             x2 - x1, ( aSize.Y - y2 ) << 4, x1 << 4,
                             aAntialiased, aNonZeroWinding );
    #endif

    #if EW_SURFACE_ROTATION == 180
      EwRasterAlpha8Polygon( aMemory, bufPath, aSize.X - x2, aSize.Y - y2,
                             x2 - x1, y2 - y1, ( aSize.X - x2 ) << 4,
                           ( aSize.Y - y2 ) << 4, aAntialiased, aNonZeroWinding );
    #endif

    #if EW_SURFACE_ROTATION == 270
      EwRasterAlpha8Polygon( aMemory, bufPath, y1, aSize.X - x2, y2 - y1,
                             x2 - x1, y1 << 4, ( aSize.X - x2 ) << 4,
                             aAntialiased, aNonZeroWinding );
    #endif

    /* Finally release the temporarily used memory and unlock the surface */
    EwFree( bufPath );
    EwResourcesMemory -= count * sizeof( int );

    return 1;
}

#endif /* EW_DONT_USE_PATH_FUNCTIONS */


/*******************************************************************************
* FUNCTION:
*   EwGetBitmapFromFillPath
*
* DESCRIPTION:
*   The function EwGetBitmapFromFillPath() creates an ALPHA8 bitmap consisting
*   of a single frame in the size aSize and fills within the bitmap a polygon
*   determined by the data stored in aPath. Finally, the function returns the
*   bitmap. Such bitmap can be used in copy operations to speed-up the screen
*   update without the necessity to rasterize the polygon again and again.
*
* ARGUMENTS:
*   aSize           - Size of the bitmap to create.
*   aPath           - Data object providing the path information consisting of
*     one or more sub-paths. Sub-paths, which are opened, are automatically
*     closed by connecting their start and end positions with a straight line
*     segment. All path coordinates are assumed as being relative to the top-
*     left corner of the bitmap area, or if aFlipY is != 0, relative to the
*     bottom-left corner.
*   aFlipY          - If != 0, the coordinate system of the path is vertically
*     mirrored and its origin is moved to the bottom-left edge of the bitmap.
*   aOffset         - Offset to move the origin of the path coordinate system.
*     Changing this value scrolls the displayed path content.
*   aAntialiased    - If != 0, the function applies antialiasing to the pixel.
*     The antialiasing is based on supersampling with 4 samples in X and Y
*     direction.
*   aNonZeroWinding - Controls the fill rule to be used by the algorithm. If
*     this parameter is == 0, the even-odd fill rule is used. If this parameter
*     is != 0, the non-zero winding rule is used.
*
* RETURN VALUE:
*   If successful, the function returns the just created bitmap. If the path
*   is empty or the operation fails, the function returns 0.
*
*******************************************************************************/
XBitmap* EwGetBitmapFromFillPath_( XPoint aSize, XPath* aPath, XBool aFlipY,
  XPoint aOffset, XBool aAntialiased, XBool aNonZeroWinding )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XBitmap*        bitmap;
    XBitmapFrame*   frame;
    XSurfaceLock    srfLock;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Nothing to do */
    if (( aSize.X <= 0 ) || ( aSize.Y <= 0 ) || !aPath )
      return 0;

    /* Evidently there is some path to draw within the bitmap. Create the bitmap
       now. */
    bitmap = EwCreateBitmap( EW_PIXEL_FORMAT_ALPHA8, aSize, 0, 1 );

    /* Failed to create the bitmap? */
    if ( !bitmap )
      return 0;

    /* The bitmap frame where we will draw the path */
    frame = MapBitmapFrame( bitmap, 0 );

    /* Try to lock the bitmap the frame for writing operation */
    if ( !EwLockSurface( frame->Surface, frame->Origin.X, frame->Origin.Y, aSize.X,
          aSize.Y, 0, 0, EW_LOCK_PIXEL_WRITE, &srfLock ))
    {
      EwErrorPD( 139, frame->Surface, 0 );
      EwFreeBitmap( bitmap );
      return 0;
    }

    /* Rasterize the path within the bitmap's memory. If failed, rewind. */
    if ( !FillPathInSurfaceMemory( &srfLock.Memory, aSize, aPath, aFlipY, aOffset,
                                   aAntialiased, aNonZeroWinding ))
    {
      EwFreeBitmap( bitmap );
      return 0;
    }

    /* Finally release the temporarily used memory and unlock the surface */
    EwUnlockSurface( frame->Surface, &srfLock );
    return bitmap;
  #else
    EW_UNUSED_ARG( aSize );
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aFlipY );
    EW_UNUSED_ARG( aOffset );
    EW_UNUSED_ARG( aAntialiased );
    EW_UNUSED_ARG( aNonZeroWinding );
    EwError( 194 );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwGetBitmapFromFillPath, XBitmap*, ( XPoint aSize,
  XPath* aPath, XBool aFlipY, XPoint aOffset, XBool aAntialiased,
  XBool aNonZeroWinding ), ( aSize, aPath, aFlipY, aOffset, aAntialiased,
  aNonZeroWinding ))


#ifndef EW_DONT_USE_PATH_FUNCTIONS

/* The following internal function rasterizes within an ALPHA8 surface a shape
   determined by the aPath data. The function returns != 0 if the operation was
   successfull. */
static int StrokePathInSurfaceMemory( XSurfaceMemory* aMemory, XPoint aSize,
  XPath* aPath, XBool aFlipY, XPoint aOffset, XFloat aWidth, XUInt32 aStyle,
  XFloat aMiterLimit, XBool aAntialiased )
{
  XSubPath**      subPaths     = aPath? aPath->SubPaths : 0;
  int             noOfSubPaths = aPath? aPath->MaxNoOfSubPaths : 0;
  int             roundSteps   = 0;
  float           roundSin     = 0.0f;
  float           roundCos     = 0.0f;
  float           width2       = aWidth / 2.0f;
  unsigned int    styleStart   = aStyle & 0x0000FF;
  unsigned int    styleEnd     = aStyle & 0x00FF00;
  unsigned int    styleJoin    = aStyle & 0xFF0000;
  int             dstX         = aOffset.X;
  int             dstY         = aOffset.Y;
  int             flipY        = aFlipY? -1 : 1;
  float           matrix[4]    = { 1.0f, 0.0f, 0.0f, 1.0f };
  int             x1, y1, x2, y2;
  int             margin;
  int             count;
  int*            bufPath;
  int*            bufPath2;
  float*          bufHelp;

  #if EW_SURFACE_ROTATION != 0
    int*          bufPath3;
    int           noOfEdges;
  #endif

  /* Eventually update internal path information if the path data has been
     modified in the past */
  UpdatePath( aPath );

  /* Very thin lines don't need the rounded caps. Use the triangle
     instead */
  if (( styleStart == EW_PATH_CAP_START_ROUND ) && ( aWidth < 4.0f ))
    styleStart = EW_PATH_CAP_START_TRIANGLE;

  if (( styleEnd == EW_PATH_CAP_END_ROUND ) && ( aWidth < 4.0f ))
    styleEnd = EW_PATH_CAP_END_TRIANGLE;

  /* ... not rounded join points */
  if (( styleJoin == EW_PATH_JOIN_ROUND ) && ( aWidth < 3.0f ))
    styleJoin = EW_PATH_JOIN_BEVEL;

  /* Calculate the max. (worst case) margin around the original path, which
     completely encloses the resulting polygon */
  if ( styleJoin == EW_PATH_JOIN_MITER )
  {
    if ( aMiterLimit > 1.0f ) margin = (int)( aMiterLimit * width2 );
    else                      margin = (int)width2;
  }
  else if (( styleStart == EW_PATH_CAP_START_SQUARE ) ||
           ( styleEnd   == EW_PATH_CAP_END_SQUARE  ))
    margin = (int)( width2 * 1.5f );
  else
    margin = (int)( width2 + 0.5f );

  /* Estimate the origin of the path coordinate system and the area occupied by
     the drawn polygon. Note, the coordinate system can be mirrored vertically.
     Take in account the width of the stroken path and estimate the max. area
     occupied by it */
  if ( !aFlipY )
  {
    y1    = dstY + aPath->Bounds.Point1.Y - margin - 1;
    y2    = dstY + aPath->Bounds.Point2.Y + margin + 1;
  }
  else
  {
    dstY += aSize.Y;
    y1    = dstY - aPath->Bounds.Point2.Y - margin - 1;
    y2    = dstY - aPath->Bounds.Point1.Y + margin + 1;
  }

  x1   = dstX + aPath->Bounds.Point1.X - margin - 2;
  x2   = dstX + aPath->Bounds.Point2.X + margin + 1;
  dstX = dstX << 4;
  dstY = dstY << 4;

  /* Limit the fill area to the frame boundary and to the clipping area */
  x1 = MAX( x1, 0 );
  y1 = MAX( y1, 0 );
  x2 = MIN( x2, aSize.X );
  y2 = MIN( y2, aSize.Y );

  /* Calculate the number of additional edges to add at cap and join points in
     order to let them appear as circles. The thicker the path the more edges
     are needed for good looking results. Knowing the number of additional
     edges estimate the parameters for rotation matrix to use when calculating
     the round outline */
  if (( styleStart == EW_PATH_CAP_START_ROUND ) ||
      ( styleEnd   == EW_PATH_CAP_END_ROUND ) ||
      ( styleJoin  == EW_PATH_JOIN_ROUND ))
  {
    roundSteps = (int)EwMathCeil( aWidth * 0.15f + 0.5f ) + 2;
    roundCos   = EwMathCos( 180.0f / roundSteps );
    roundSin   = EwMathSin( 180.0f / roundSteps );
  }

  /* Estimate the buffer size to reserve for the polygon data. It takes in account
     all the special cases like path stroken with rounded corners, etc. We calculate
     with the worst case. */
  count = aPath->NoOfOpenedPaths * 3 + aPath->NoOfClosedPaths * 6 + 1 +
          aPath->NoOfEdges * 8 +
          ( aPath->NoOfOpenedPaths *
          (( styleStart == EW_PATH_CAP_START_ROUND    )? 2 * ( roundSteps - 1 ) :
           ( styleStart == EW_PATH_CAP_START_TRIANGLE )? 2 : 0 )) +
          ( aPath->NoOfOpenedPaths *
          (( styleEnd == EW_PATH_CAP_END_ROUND        )? 2 * ( roundSteps - 1 ) :
           ( styleEnd == EW_PATH_CAP_END_TRIANGLE     )? 2 : 0 )) +
          (( aPath->NoOfEdges - aPath->NoOfOpenedPaths ) *
          (( styleJoin == EW_PATH_JOIN_ROUND )? 2 * ( roundSteps - 1 ) :
          (( styleJoin == EW_PATH_JOIN_MITER )? 2 : 0 )));

  /* Get a storage area for the polygon data */
  do
    bufPath = bufPath2 = EwAlloc( count * sizeof( int ));
  while ( !bufPath && EwImmediateReclaimMemory( 31 ));

  /* Not enough space? */
  if ( !bufPath )
  {
    EwError( 31 );
    return 0;
  }

  /* Track the temporary used memory */
  EwResourcesMemory += count * sizeof( int );

  /* Also track the max. memory pressure */
  if ( EwResourcesMemory > EwResourcesMemoryPeak )
    EwResourcesMemoryPeak = EwResourcesMemory;

  if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
    EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

  /* Clear the entire surface */
  #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
    EwZero( aMemory->Pixel1, aMemory->Pitch1Y * aSize.X );
  #else
    EwZero( aMemory->Pixel1, aMemory->Pitch1Y * aSize.Y );
  #endif

  /* The area at the end is used as temporary buffer for precalculated edge
     specific information like the unit vector and the edge direction relative
     to the preceding edge */
  bufHelp = (float*)( bufPath + count );

  /* Now process the sub-paths of the path individually and append the resulting
     path information at the end of the just allocated data structure */
  for ( ; noOfSubPaths > 0; noOfSubPaths--, subPaths++ )
    if ( *subPaths && (*subPaths)->IsValid && (*subPaths)->NoOfEdges )
      bufPath2 = PrepareForStrokePath( *subPaths, styleStart, styleEnd, styleJoin,
                   aMiterLimit, width2, bufPath2, bufHelp, dstX, dstY, flipY,
                   roundSteps, roundCos, roundSin, matrix );

  /* Terminate the path information */
  *bufPath2 = 0;

  #if EW_SURFACE_ROTATION == 90
    for ( bufPath3 = bufPath; *bufPath3 > 0; )
      for ( noOfEdges = *bufPath3++; noOfEdges >= 0; noOfEdges--, bufPath3 += 2 )
      {
        int x = bufPath3[0];
        bufPath3[0] = ( aSize.Y << 4 ) - bufPath3[1];
        bufPath3[1] = x;
      }
  #endif

  #if EW_SURFACE_ROTATION == 180
    for ( bufPath3 = bufPath; *bufPath3 > 0; )
      for ( noOfEdges = *bufPath3++; noOfEdges >= 0; noOfEdges--, bufPath3 += 2 )
      {
        bufPath3[0] = ( aSize.X << 4 ) - bufPath3[0];
        bufPath3[1] = ( aSize.Y << 4 ) - bufPath3[1];
      }
  #endif

  #if EW_SURFACE_ROTATION == 270
    for ( bufPath3 = bufPath; *bufPath3 > 0; )
      for ( noOfEdges = *bufPath3++; noOfEdges >= 0; noOfEdges--, bufPath3 += 2 )
      {
        int y = bufPath3[1];
        bufPath3[1] = ( aSize.X << 4 ) - bufPath3[0];
        bufPath3[0] = y;
      }
  #endif

  /* Rasterize the path data within the surface memory */
  #if EW_SURFACE_ROTATION == 0
    EwRasterAlpha8Polygon( aMemory, bufPath, x1, y1, x2 - x1, y2 - y1,
                           x1 << 4, y1 << 4, aAntialiased, 1 );
  #endif

  #if EW_SURFACE_ROTATION == 90
    EwRasterAlpha8Polygon( aMemory, bufPath, aSize.Y - y2, x1, y2 - y1,
                           x2 - x1, ( aSize.Y - y2 ) << 4, x1 << 4,
                           aAntialiased, 1 );
  #endif

  #if EW_SURFACE_ROTATION == 180
    EwRasterAlpha8Polygon( aMemory, bufPath, aSize.X - x2, aSize.Y - y2,
                           x2 - x1, y2 - y1, ( aSize.X - x2 ) << 4,
                         ( aSize.Y - y2 ) << 4, aAntialiased, 1 );
  #endif

  #if EW_SURFACE_ROTATION == 270
    EwRasterAlpha8Polygon( aMemory, bufPath, y1, aSize.X - x2, y2 - y1,
                           x2 - x1, y1 << 4, ( aSize.X - x2 ) << 4,
                           aAntialiased, 1 );
  #endif

  /* Finally release the temporarily used memory and unlock the surface */
  EwFree( bufPath );
  EwResourcesMemory -= count * sizeof( int );

  return 1;
}

#endif /* EW_DONT_USE_PATH_FUNCTIONS */


/*******************************************************************************
* FUNCTION:
*   EwGetBitmapFromStrokePath
*
* DESCRIPTION:
*   The function EwGetBitmapFromStrokePath() creates an ALPHA8 bitmap containing
*   a single frame in the size aSize and strokes within it a path determined by
*   the data stored in aPath. The path is stroked with line thickness specified
*   in the parameter aWidth. With the parameter aStyle the cap and join points
*   of the path are configured. Finally, the function returns the bitmap. Such
*   bitmap can be used in copy operations to speed-up the screen update without
*   the necessity to rasterize the polygon again and again.
*
* ARGUMENTS:
*   aSize           - Size of the bitmap to create.
*   aPath           - Data object providing the path information consisting of
*     one or more sub-paths. Sub-paths, which are opened, are automatically
*     closed by connecting their start and end positions with a straight line
*     segment. All path coordinates are assumed as being relative to the top-
*     left corner of the bitmap area, or if aFlipY is != 0, relative to the
*     bottom-left corner.
*   aFlipY          - If != 0, the coordinate system of the path is vertically
*     mirrored and its origin is moved to the bottom-left edge of the bitmap.
*   aOffset         - Offset to move the origin of the path coordinate system.
*     Changing this value scrolls the displayed path content.
*   aWidth          - The width in pixel to stroke the path.
*   aStyle          - Flags specifying how the path caps and join points should
*     appear. See the enumeration EW_PATH_CAP_XXX and EW_PATH_JOIN_XXX.
*   aMiterLimit     - In case aStyle is configured with EW_PATH_JOIN_MITER, this
*     parameter imposes a limit on the ratio between the miter length and the
*     half of the line thickness aWidth. If the limit is exceeded for a corner,
*     the corner appears as bevel (EW_PATH_JOIN_BEVEL) instead of miter.
*   aAntialiased    - If != 0, the function applies antialiasing to the pixel.
*     The antialiasing is based on supersampling with 4 samples in X and Y
*     direction.
*
* RETURN VALUE:
*   If successful, the function returns the just created bitmap. If the path
*   is empty or the operation fails, the function returns 0.
*
*******************************************************************************/
XBitmap* EwGetBitmapFromStrokePath_( XPoint aSize, XPath* aPath, XBool aFlipY,
  XPoint aOffset, XFloat aWidth, XUInt32 aStyle, XFloat aMiterLimit,
  XBool aAntialiased )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    XBitmap*        bitmap;
    XBitmapFrame*   frame;
    XSurfaceLock    srfLock;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Nothing to do */
    if (( aSize.X <= 0 ) || ( aSize.Y <= 0 ) || !aPath || ( aWidth <= 0.0f ))
      return 0;

    /* Evidently there is some path to draw within the bitmap. Create the bitmap
       now. */
    bitmap = EwCreateBitmap( EW_PIXEL_FORMAT_ALPHA8, aSize, 0, 1 );

    /* Failed to create the bitmap? */
    if ( !bitmap )
      return 0;

    /* The bitmap frame where we will draw the path */
    frame = MapBitmapFrame( bitmap, 0 );

    /* Try to lock the bitmap the frame for writing operation */
    if ( !EwLockSurface( frame->Surface, frame->Origin.X, frame->Origin.Y, aSize.X,
          aSize.Y, 0, 0, EW_LOCK_PIXEL_WRITE, &srfLock ))
    {
      EwErrorPD( 139, frame->Surface, 0 );
      EwFreeBitmap( bitmap );
      return 0;
    }

    /* Rasterize the path within the bitmap's memory. If failed, rewind. */
    if ( !StrokePathInSurfaceMemory( &srfLock.Memory, aSize, aPath, aFlipY, aOffset,
                                     aWidth, aStyle, aMiterLimit, aAntialiased ))
    {
      EwFreeBitmap( bitmap );
      return 0;
    }

    /* Finally release the temporarily used memory and unlock the surface */
    EwUnlockSurface( frame->Surface, &srfLock );
    return bitmap;
  #else
    EW_UNUSED_ARG( aSize );
    EW_UNUSED_ARG( aPath );
    EW_UNUSED_ARG( aFlipY );
    EW_UNUSED_ARG( aOffset );
    EW_UNUSED_ARG( aWidth );
    EW_UNUSED_ARG( aStyle );
    EW_UNUSED_ARG( aMiterLimit );
    EW_UNUSED_ARG( aAntialiased );
    EwError( 195 );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwGetBitmapFromStrokePath, XBitmap*, ( XPoint aSize,
  XPath* aPath, XBool aFlipY, XPoint aOffset, XFloat aWidth, XUInt32 aStyle,
  XFloat aMiterLimit, XBool aAntialiased ), ( aSize, aPath, aFlipY, aOffset,
  aWidth, aStyle, aMiterLimit, aAntialiased ))


#ifndef EW_DONT_USE_BLUR_FUNCTIONS

/* The following internal function creates a new ALPHA8 bitmap with the content
   of aMemory ALPHA8 surface being blurred. */
static XBitmap* GetBlurredBitmapFromAlpha8Memory( XPoint aSize, 
  XSurfaceMemory* aMemory, XInt32 aBlurRadius )
{
  XSurfaceLock    srfLock;
  XSurfaceMemory  memory;
  void*           tmp;
  XBitmap*        bitmap;
  XBitmapFrame*   frame;

  #if ( EW_SURFACE_ROTATION == 0 ) || ( EW_SURFACE_ROTATION == 180 )
    XPoint        size = aSize;
  #else
    XPoint        size = { aSize.Y, aSize.X };
  #endif

  /* Coordinates in source surface at the edges of the drawing area */
  int csx1 = 0;
  int csy1 = 0;
  int csx2 = csx1 + size.X;
  int csy2 = csy1 + size.Y;

  /* Since the blur is used, we need more of the source surface to process.
     The algorithm will read the source pixel beyond the edges of the drawing
     destination */
  int bsx1 = csx1 - aBlurRadius;
  int bsy1 = csy1 - aBlurRadius;
  int bsx2 = csx2 + aBlurRadius;
  int bsy2 = csy2 + aBlurRadius;

  /* The source area inclusive pixel to take in account during blur */
  int sx1  = MAX( bsx1, 0 );
  int sx2  = MIN( bsx2, size.X );
  int sy1  = MAX( bsy1, 0 );
  int sy2  = MIN( bsy2, size.Y );

  /* Distances relative to the edges of the drawing destination when start the
     clamping - here no clamping is used */
  int cl   = aBlurRadius;
  int ct   = aBlurRadius;
  int cr   = size.X + aBlurRadius;
  int cb   = size.Y + aBlurRadius;

  /* Size of the intermediate surface to store blurred rows/columns */
  int tmpW = sy2 - sy1;
  int tmpH = size.X;

  /* Nothing to do */
  if (( sy2 <= sy1 ) || ( sx2 <= sx1 ))
    return 0;

  /* Create a new bitmap where the blurred results are stored */
  bitmap = EwCreateBitmap( EW_PIXEL_FORMAT_ALPHA8, aSize, 0, 1 );

  /* No memory for the new bitmap */
  if ( !bitmap )
    return 0;

  /* The bitmap frame where we will draw the path */
  frame = MapBitmapFrame( bitmap, 0 );

  /* Try to lock the bitmap the frame for writing operation */
  if ( !EwLockSurface( frame->Surface, frame->Origin.X, frame->Origin.Y, aSize.X,
        aSize.Y, 0, 0, EW_LOCK_PIXEL_WRITE, &srfLock ))
  {
    EwErrorPD( 453, frame->Surface, 0 );
    EwFreeBitmap( bitmap );
    return 0;
  }

  /* Create a temporary surface to store the intermediate state of the blur
     operation in which the rows and columns are exchanged. See the size
     calculation above. Because of the blur effect the surface may be bigger
     than the clipping area to take in account the pixel rows intersecting the
     blur radius above/below the update area. */
  tmp = EwCreateAlpha8Surface( tmpW, tmpH );

  /* No memory for the temp. surface? Rewind! */
  if ( !tmp )
  {
    EwUnlockSurface( frame->Surface, &srfLock );
    EwFreeBitmap( bitmap );
    EwError( 454 );
    return 0;
  }

  /* Obtain direct access to the surface memory */
  EwGetAlpha8SurfaceMemory( tmp, 0, 0, 0, 1, &memory );

  /* Run the software pixel driver for the first phase of the blur effect. Here 
     the rows from the source are blured and stored in the intermediate surface
     tmp. Please note, depending on how the real surface content is orientend the
     coordinates need to be adapted. */
  EwEmulateBlurFilter( &memory, aMemory, 
    0, 0,
    tmpW, tmpH,
    csx1,
    sy1,
    0,
    size.X,
    cl,
    cr,
    aBlurRadius,
    255,
    0,
    EwAlpha8FilterAlpha8Blur );

  /* Run the software pixel driver for the second phase of the blur effect. Here 
     the content of the intermediate surface tmp is blured column-wise. Please
     note, depending on how the real surface content is orientend the coordinates
     need to be adapted. */
  EwEmulateBlurFilter( &srfLock.Memory, &memory, 
    0, 0,
    size.X, size.Y,
    csy1 - sy1,
    0,
    0,
    tmpW,
    ct,
    cb,
    aBlurRadius,
    255,
    0,
    EwAlpha8FilterAlpha8Blur );

  /* The temporary surface is not needed anymore. Unlock and release. */
  EwDestroyAlpha8Surface( tmp );

  /* Release the memory lock and return the just created bitmap */
  EwUnlockSurface( frame->Surface, &srfLock );
  return bitmap;
}

#endif


/*******************************************************************************
* FUNCTION:
*   EwGetBlurredBitmapFromFillPath
*
* DESCRIPTION:
*   The function EwGetBlurredBitmapFromFillPath() creates an ALPHA8 bitmap
*   consisting of a single frame in the size aSize and fills within the bitmap
*   a polygon determined by the data stored in aPath. The polygon content is
*   blurred according to the value specified in the parameter aBlurRadius.
*   Finally, the function returns the bitmap. Such bitmap can be used in copy
*   operations to speed-up the screen update without the necessity to rasterize
*   and blur the polygon again and again.
*
*   Please note, the function uses a box blur algorithm without involving any
*   GPU to perform the blur operation. This guarantees similar results on all
*   target systems with the blur radius not being restricted to any discrete
*   value.
*
* ARGUMENTS:
*   aSize           - Size of the bitmap to create.
*   aPath           - Data object providing the path information consisting of
*     one or more sub-paths. Sub-paths, which are opened, are automatically
*     closed by connecting their start and end positions with a straight line
*     segment. All path coordinates are assumed as being relative to the top-
*     left corner of the bitmap area, or if aFlipY is != 0, relative to the
*     bottom-left corner.
*   aFlipY          - If != 0, the coordinate system of the path is vertically
*     mirrored and its origin is moved to the bottom-left edge of the bitmap.
*   aOffset         - Offset to move the origin of the path coordinate system.
*     Changing this value scrolls the displayed path content.
*   aAntialiased    - If != 0, the function applies antialiasing to the pixel.
*     The antialiasing is based on supersampling with 4 samples in X and Y
*     direction.
*   aNonZeroWinding - Controls the fill rule to be used by the algorithm. If
*     this parameter is == 0, the even-odd fill rule is used. If this parameter
*     is != 0, the non-zero winding rule is used.
*   aBlurRadius     - Determines the intensity of the blur filter effect. The
*     value is expressed in pixel as radius to blur the corresponding source
*     image content. If the value is <= 0, no blur filter is applied. The blur
*     radius is limited to 64 pixel.
*
* RETURN VALUE:
*   If successful, the function returns the just created bitmap. If the path
*   is empty or the operation fails, the function returns 0.
*
*******************************************************************************/
XBitmap* EwGetBlurredBitmapFromFillPath_( XPoint aSize, XPath* aPath,
  XBool aFlipY, XPoint aOffset, XBool aAntialiased, XBool aNonZeroWinding,
  XInt32 aBlurRadius )
{
  #if !defined EW_DONT_USE_PATH_FUNCTIONS && !defined EW_DONT_USE_BLUR_FUNCTIONS
    void*          surface;
    XSurfaceMemory memory;
    XBitmap*       bitmap;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Nothing to do */
    if (( aSize.X <= 0 ) || ( aSize.Y <= 0 ) || !aPath )
      return 0;

    /* Limit the blur radius */
    if ( aBlurRadius <  0 ) aBlurRadius =  0;
    if ( aBlurRadius > 64 ) aBlurRadius = 64;

    /* No bluring desired - just rasterize the bitmap */
    if ( !aBlurRadius )
      return EwGetBitmapFromFillPath( aSize, aPath, aFlipY, aOffset, aAntialiased,
                                      aNonZeroWinding );

    /* Evidently there is some path to draw within the bitmap and blur effect is
       desired. Create an intermediate ALPHA8 surface. */
    #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
      surface = EwCreateAlpha8Surface( aSize.Y, aSize.X );
    #else
      surface = EwCreateAlpha8Surface( aSize.X, aSize.Y );
    #endif

    /* Failed to create the surface? */
    if ( !surface )
    {
      EwError( 451 );
      return 0;
    }

    /* Access the memory of of the surface */
    EwGetAlpha8SurfaceMemory( surface, 0, 0, 0, 1, &memory );

    /* Rasterize the path within the memory of the intermediate surface. If 
       failed, rewind. */
    if ( !FillPathInSurfaceMemory( &memory, aSize, aPath, aFlipY, aOffset,
                                   aAntialiased, aNonZeroWinding ))
    {
      EwDestroyAlpha8Surface( surface );
      return 0;
    }

    /* Now blur the content of the intermediate ALPHA8 surface */
    bitmap = GetBlurredBitmapFromAlpha8Memory( aSize, &memory, aBlurRadius );

    /* Release the temporarily used APHA8 surface */
    EwDestroyAlpha8Surface( surface );

    return bitmap;
  #else
    EW_UNUSED_ARG( aSize             );
    EW_UNUSED_ARG( aPath             );
    EW_UNUSED_ARG( aFlipY            );
    EW_UNUSED_ARG( aOffset           );
    EW_UNUSED_ARG( aAntialiased      );
    EW_UNUSED_ARG( aNonZeroWinding   );
    EW_UNUSED_ARG( aBlurRadius       );
    EwError( 465 );
    return 0;
  #endif /* !EW_DONT_USE_PATH_FUNCTIONS && !EW_DONT_USE_BLUR_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwGetBlurredBitmapFromFillPath, XBitmap*, ( XPoint aSize,
  XPath* aPath, XBool aFlipY, XPoint aOffset, XBool aAntialiased,
  XBool aNonZeroWinding, XInt32 aBlurRadius ), ( aSize, aPath, aFlipY, aOffset,
  aAntialiased, aNonZeroWinding, aBlurRadius ))


/*******************************************************************************
* FUNCTION:
*   EwGetBlurredBitmapFromStrokePath
*
* DESCRIPTION:
*   The function EwGetBlurredBitmapFromStrokePath() creates an ALPHA8 bitmap
*   consisting of a single in the size aSize and strokes within the bitmap a
*   path determined by the data stored in aPath. The path is stroked with line
*   thickness specified in the parameter aWidth. With the parameter aStyle the
*   cap and join points of the path are configured. The polygon content is
*   blurred according to the value specified in the parameter aBlurRadius.
*   Finally, the function returns the bitmap. Such bitmap can be used in copy
*   operations to speed-up the screen update without the necessity to rasterize
*   and blur the polygon again and again.
*
*   Please note, the function uses a box blur algorithm without involving any
*   GPU to perform the blur operation. This guarantees similar results on all
*   target systems with the blur radius not being restricted to any discrete
*   value.
*
* ARGUMENTS:
*   aSize           - Size of the bitmap to create.
*   aPath           - Data object providing the path information consisting of
*     one or more sub-paths. Sub-paths, which are opened, are automatically
*     closed by connecting their start and end positions with a straight line
*     segment. All path coordinates are assumed as being relative to the top-
*     left corner of the bitmap area, or if aFlipY is != 0, relative to the
*     bottom-left corner.
*   aFlipY          - If != 0, the coordinate system of the path is vertically
*     mirrored and its origin is moved to the bottom-left edge of the bitmap.
*   aOffset         - Offset to move the origin of the path coordinate system.
*     Changing this value scrolls the displayed path content.
*   aWidth          - The width in pixel to stroke the path.
*   aStyle          - Flags specifying how the path caps and join points should
*     appear. See the enumeration EW_PATH_CAP_XXX and EW_PATH_JOIN_XXX.
*   aMiterLimit     - In case aStyle is configured with EW_PATH_JOIN_MITER, this
*     parameter imposes a limit on the ratio between the miter length and the
*     half of the line thickness aWidth. If the limit is exceeded for a corner,
*     the corner appears as bevel (EW_PATH_JOIN_BEVEL) instead of miter.
*   aAntialiased    - If != 0, the function applies antialiasing to the pixel.
*     The antialiasing is based on supersampling with 4 samples in X and Y
*     direction.
*   aBlurRadius     - Determines the intensity of the blur filter effect. The
*     value is expressed in pixel as radius to blur the corresponding source
*     image content. If the value is <= 0, no blur filter is applied. The blur
*     radius is limited to 64 pixel.
*
* RETURN VALUE:
*   If successful, the function returns the just created bitmap. If the path
*   is empty or the operation fails, the function returns 0.
*
*******************************************************************************/
XBitmap* EwGetBlurredBitmapFromStrokePath_( XPoint aSize, XPath* aPath,
  XBool aFlipY, XPoint aOffset, XFloat aWidth, XUInt32 aStyle, 
  XFloat aMiterLimit, XBool aAntialiased, XInt32 aBlurRadius )
{
  #if !defined EW_DONT_USE_PATH_FUNCTIONS && !defined EW_DONT_USE_BLUR_FUNCTIONS
    void*          surface;
    XSurfaceMemory memory;
    XBitmap*       bitmap;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Nothing to do */
    if (( aSize.X <= 0 ) || ( aSize.Y <= 0 ) || !aPath || ( aWidth <= 0.0f ))
      return 0;

    /* Limit the blur radius */
    if ( aBlurRadius <  0 ) aBlurRadius =  0;
    if ( aBlurRadius > 64 ) aBlurRadius = 64;

    /* No bluring desired - just rasterize the bitmap */
    if ( !aBlurRadius )
      return EwGetBitmapFromStrokePath( aSize, aPath, aFlipY, aOffset, aWidth,
                                        aStyle, aMiterLimit, aAntialiased );

    /* Evidently there is some path to draw within the bitmap and blur effect is
       desired. Create an intermediate ALPHA8 surface. */
    #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
      surface = EwCreateAlpha8Surface( aSize.Y, aSize.X );
    #else
      surface = EwCreateAlpha8Surface( aSize.X, aSize.Y );
    #endif

    /* Failed to create the surface? */
    if ( !surface )
    {
      EwError( 452 );
      return 0;
    }

    /* Access the memory of of the surface */
    EwGetAlpha8SurfaceMemory( surface, 0, 0, 0, 1, &memory );

    /* Rasterize the path within the memory of the intermediate surface. If 
       failed, rewind. */
    if ( !StrokePathInSurfaceMemory( &memory, aSize, aPath, aFlipY, aOffset,
                                     aWidth, aStyle, aMiterLimit, aAntialiased ))
    {
      EwDestroyAlpha8Surface( surface );
      return 0;
    }

    /* Now blur the content of the intermediate ALPHA8 surface */
    bitmap = GetBlurredBitmapFromAlpha8Memory( aSize, &memory, aBlurRadius );

    /* Release the temporarily used APHA8 surface */
    EwDestroyAlpha8Surface( surface );

    return bitmap;
  #else
    EW_UNUSED_ARG( aSize             );
    EW_UNUSED_ARG( aPath             );
    EW_UNUSED_ARG( aFlipY            );
    EW_UNUSED_ARG( aOffset           );
    EW_UNUSED_ARG( aWidth            );
    EW_UNUSED_ARG( aStyle            );
    EW_UNUSED_ARG( aMiterLimit       );
    EW_UNUSED_ARG( aAntialiased      );
    EW_UNUSED_ARG( aBlurRadius       );
    EwError( 466 );
    return 0;
  #endif /* !EW_DONT_USE_PATH_FUNCTIONS && !EW_DONT_USE_BLUR_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwGetBlurredBitmapFromStrokePath, XBitmap*, ( XPoint aSize,
  XPath* aPath, XBool aFlipY, XPoint aOffset, XFloat aWidth, XUInt32 aStyle,
  XFloat aMiterLimit, XBool aAntialiased, XInt32 aBlurRadius ), ( aSize, aPath,
  aFlipY, aOffset, aWidth, aStyle, aMiterLimit, aAntialiased, aBlurRadius ))


/*******************************************************************************
* FUNCTION:
*   EwCopyBitmap
*
* DESCRIPTION:
*   The function EwCopyBitmap() copies a rectangular area from the bitmap aSrc
*   to the bitmap aDst. The areas affected by this operation are determined by
*   the both arguments aDstRect and aSrcPos. Optionally the copied pixel can be
*   modulated by a color gradient specified by the four parameters aColorTL ..
*   aColorBL.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst        - Destination bitmap.
*   aSrc        - Source bitmap.
*   aDstFrameNo - Frame within the destination bitmap affected by the drawing
*     operation.
*   aSrcFrameNo - Source bitmap frame affected by the operation.
*   aClipRect   - Area to limit the drawing operation (Relative to the top-left
*     corner of the destination bitmap frame).
*   aDstRect    - Area to fill with the copied pixel (Relative to the top-left
*     corner of the destination bitmap frame).
*   aSrcPos     - Origin of the area to copy from the source bitmap (Relative
*     to the top-left corner of the source bitmap frame). The size of the
*     source area corresponds to the size of the destination area as it is
*     specified in aDstRect.
*   aColorTL,
*   aColorTR,
*   aColorBR,
*   aColorBL    - Color values corresponding to the four corners of aDstRect.
*   aBlend      - If != 0, the drawn pixel will be alpha-blended with the pixel
*     in the background.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwCopyBitmap_( XBitmap* aDst, XBitmap* aSrc, XInt32 aDstFrameNo,
  XInt32 aSrcFrameNo, XRect aClipRect, XRect aDstRect, XPoint aSrcPos,
  XColor aColorTL, XColor aColorTR, XColor aColorBR, XColor aColorBL,
  XBool aBlend )
{
  XBitmapFrame*       dst     = MapBitmapFrame( aDst, aDstFrameNo );
  XBitmapFrame*       src     = MapBitmapFrame( aSrc, aSrcFrameNo );
  XCopySurface*       data;
  XIssue*             issue;
  XTask*              task;
  int                 x1      = aDstRect.Point1.X;
  int                 y1      = aDstRect.Point1.Y;
  int                 x2      = aDstRect.Point2.X;
  int                 y2      = aDstRect.Point2.Y;
  unsigned int        colorTL = PACK_COLOR( aColorTL, aDst );
  unsigned int        colorTR = PACK_COLOR( aColorTR, aDst );
  unsigned int        colorBL = PACK_COLOR( aColorBL, aDst );
  unsigned int        colorBR = PACK_COLOR( aColorBR, aDst );

  /* Only screen/native surfaces are allowed as the destination */
  if ( !dst || (( dst->Surface->Format != EW_PIXEL_FORMAT_SCREEN ) &&
                ( dst->Surface->Format != EW_PIXEL_FORMAT_NATIVE )))
  {
    EwErrorPD( 160, aDst, aDstFrameNo );
    return;
  }

  /* The support for Native surface as destination is disabled. */
  #ifdef EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION
    if ( dst->Surface->Format == EW_PIXEL_FORMAT_NATIVE )
    {
      EwErrorPD( 354, aDst, aDstFrameNo );
      return;
    }
  #endif

  /* Bitmaps loaded from resources can't be modified by drawing operations */
  if ( dst->Surface->Tag1 || dst->Surface->Tag2 )
  {
    EwErrorPD( 344, aDst, aDstFrameNo );
    return;
  }

  /* Is source surface valid? */
  if ( !src || ( src->Surface->Format == EW_PIXEL_FORMAT_SCREEN ))
  {
    EwErrorPD( 163, aSrc, aSrcFrameNo );
    return;
  }

  /* The support for color gradients is disabled. */
  #ifdef EW_DONT_USE_GRADIENTS
    if ( IS_LINEAR_GRADIENT4( colorTL, colorTR, colorBL, colorBR ) ||
         IS_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
    {
      EwError( 374 );
      return;
    }
  #endif

  /* RGB565 bitmaps don't contain transparancy. Alpha-blending can be avoided. */
  if ( aBlend && ( src->Surface->Format == EW_PIXEL_FORMAT_RGB565 ) &&
       IS_OPAQUE4( colorTL, colorTR, colorBL, colorBR ))
    aBlend = 0;

  /* Force the source surface to perform its own pending tasks */
  EwFlushTasks( src->Surface );

  /* Take in account the source frame boundary */
  x2 = MIN( x2, x1 + aSrc->FrameSize.X - aSrcPos.X );
  y2 = MIN( y2, y1 + aSrc->FrameSize.Y - aSrcPos.Y );
  x1 = MAX( x1, x1 - aSrcPos.X );
  y1 = MAX( y1, y1 - aSrcPos.Y );

  /* Limit the area to the destination frame boundary and to the clipping
     area */
  x1 = MAX3( aClipRect.Point1.X, x1, 0 );
  y1 = MAX3( aClipRect.Point1.Y, y1, 0 );
  x2 = MIN3( aClipRect.Point2.X, x2, aDst->FrameSize.X );
  y2 = MIN3( aClipRect.Point2.Y, y2, aDst->FrameSize.Y );

  /* Nothing to do? */
  if (( x2 <= x1 ) || ( y2 <= y1 ) ||
      ( aBlend && IS_TRANSPARENT4( colorTL, colorTR, colorBL, colorBR )))
    return;

  /* Mark the surface as involved in a drawing operation */
  src->Surface->Owned++;
  src->Surface->Used++;

  /* Start the preparation of a new drawing operation */
  if (( issue = EwInitIssue( dst->Surface )) == 0 )
  {
    src->Surface->Owned--;
    src->Surface->Used--;
    EwErrorPD( 127, aDst, 0 );
    return;
  }

  /* Get a storage area for the drawings parameter */
  data = EwAllocTaskData( issue, sizeof( *data ));
  data->DstX1     = (short)( aDstRect.Point1.X + dst->Origin.X );
  data->DstY1     = (short)( aDstRect.Point1.Y + dst->Origin.Y );
  data->DstX2     = (short)( aDstRect.Point2.X + dst->Origin.X );
  data->DstY2     = (short)( aDstRect.Point2.Y + dst->Origin.Y );
  data->SrcX      = (short)( aSrcPos.X + src->Origin.X );
  data->SrcY      = (short)( aSrcPos.Y + src->Origin.Y );
  data->Surface   = src->Surface;
  data->Colors[0] = colorTL;
  data->Colors[1] = colorTR;
  data->Colors[2] = colorBR;
  data->Colors[3] = colorBL;

  /* Enqueue the drawing operation by the issue */
  task = EwAllocTask( issue, 0 );
  task->Token     = EW_TASKID_COPY_SURFACE;
  task->Data      = data;
  task->X1        = (short)( x1 + dst->Origin.X );
  task->Y1        = (short)( y1 + dst->Origin.Y );
  task->X2        = (short)( x2 + dst->Origin.X );
  task->Y2        = (short)( y2 + dst->Origin.Y );
  task->Flags     = (short)EW_TASK_ENTIRE_AREA;

  /* Avoid slow alpha-blending if the bitmap pixel are opaque. Determine the
     opaque area of the bitmap frame */
  if ( aBlend && IS_OPAQUE4( colorTL, colorTR, colorBL, colorBR ))
  {
    x1 = MAX( task->X1, src->OpaqueRect.Point1.X + data->DstX1 - aSrcPos.X );
    y1 = MAX( task->Y1, src->OpaqueRect.Point1.Y + data->DstY1 - aSrcPos.Y );
    x2 = MIN( task->X2, src->OpaqueRect.Point2.X + data->DstX1 - aSrcPos.X );
    y2 = MIN( task->Y2, src->OpaqueRect.Point2.Y + data->DstY1 - aSrcPos.Y );

    /* The entire affected area is opaque - override the alpha-blend mode */
    if (( task->X1 == x1 ) && ( task->X2 == x2 ) &&
        ( task->Y1 == y1 ) && ( task->Y2 == y2 ))
      aBlend = 0;
  }

  /* Complete the task initialisation */
  task->Flags |= (short)( aBlend? EW_TASK_ALPHABLEND : 0 );

  /* What to do with the 4 colors? */
  #ifndef EW_DONT_USE_GRADIENTS
    if ( IS_LINEAR_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
      task->Flags |= EW_TASK_LINEAR_GRADIENT;
    else if ( IS_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
      task->Flags |= EW_TASK_GRADIENT;
    else
  #endif

  /* ... or global opacity value? */
  if (( src->Surface->Format == EW_PIXEL_FORMAT_ALPHA8 ) ||
      ( aColorTL.Alpha < 255 ))
    task->Flags |= EW_TASK_SOLID;

#ifdef EW_ELIMINATE_TASKS
  /* Avoid alpha blending of an opaque source sub-area */
  if ( aBlend && IS_OPAQUE4( colorTL, colorTR, colorBL, colorBR ) &&
       (( x2 - x1 ) >= EW_ELIMINATE_MIN_EDGE ) &&
       (( y2 - y1 ) >= EW_ELIMINATE_MIN_EDGE ))
  {
    /* Enqueue a new task ... */
    XTask* task2 = EwAllocTask( issue, 0 );

    /* to create a copy of the previous one. Limit it to the opaque pixel
       and mark the new task as 'optional' for the future optimization */
    task2->Token  = EW_TASKID_COPY_SURFACE;
    task2->Data   = data;
    task2->X1     = (short)x1;
    task2->Y1     = (short)y1;
    task2->X2     = (short)x2;
    task2->Y2     = (short)y2;
    task2->Flags  = task->Flags | (short)EW_TASK_OVERLAP;
    task2->Flags &= (short)~EW_TASK_ALPHABLEND;
  }
#endif

  /* The surface is waiting for drawing operation (it remain 'used'). */
  src->Surface->Owned--;

  /* Close the preparation. This may flush the issue */
  EwDoneIssue( dst->Surface );
}


EW_INSTRUMENT_VOID_FUNC( EwCopyBitmap, ( XBitmap* aDst, XBitmap* aSrc,
  XInt32 aDstFrameNo, XInt32 aSrcFrameNo, XRect aClipRect, XRect aDstRect,
  XPoint aSrcPos, XColor aColorTL, XColor aColorTR, XColor aColorBR,
  XColor aColorBL, XBool aBlend ), ( aDst, aSrc, aDstFrameNo, aSrcFrameNo,
  aClipRect, aDstRect, aSrcPos, aColorTL, aColorTR, aColorBR, aColorBL, aBlend ))


/*******************************************************************************
* FUNCTION:
*   EwTileBitmap
*
* DESCRIPTION:
*   The function EwTileBitmap() fills the rectangular area aDstRect of the aDst
*   bitmap with multiple copies of an area aSrcRect from the bitmap aSrc. The
*   copied pixel can optionally be modulated by a color gradient specified by
*   the four color parameters aColorTL .. aColorBL.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst        - Destination bitmap.
*   aSrc        - Source bitmap.
*   aDstFrameNo - Frame within the destination bitmap affected by the drawing
*     operation.
*   aSrcFrameNo - Source bitmap frame affected by the operation.
*   aClipRect   - Area to limit the drawing operation (Relative to the top-left
*     corner of the destination bitmap frame).
*   aDstRect    - Area to fill with the copied pixel (Relative to the top-left
*     corner of the destination bitmap frame).
*   aSrcRect    - Area to copy from the source bitmap (Relative to the top-left
*     corner of the source bitmap frame).
*   aSrcPos     - Position within the source area to start the operation. This
*     is an offset, which allows the scrolling of the drawn content within the
*     destination area. The source position has to lie within the aSrcRect.
*   aColorTL,
*   aColorTR,
*   aColorBR,
*   aColorBL    - Color values corresponding to the four corners of aDstRect.
*   aBlend      - If != 0, the drawn pixel will be alpha-blended with the pixel
*     in the background.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwTileBitmap_( XBitmap* aDst, XBitmap* aSrc, XInt32 aDstFrameNo,
  XInt32 aSrcFrameNo,  XRect aClipRect, XRect aDstRect, XRect aSrcRect,
  XPoint aSrcPos, XColor aColorTL, XColor aColorTR, XColor aColorBR,
  XColor aColorBL, XBool aBlend )
{
  XBitmapFrame*       dst     = MapBitmapFrame( aDst, aDstFrameNo );
  XBitmapFrame*       src     = MapBitmapFrame( aSrc, aSrcFrameNo );
  XTileSurface*       data;
  XIssue*             issue;
  XTask*              task;
  int                 x1      = aDstRect.Point1.X;
  int                 y1      = aDstRect.Point1.Y;
  int                 x2      = aDstRect.Point2.X;
  int                 y2      = aDstRect.Point2.Y;
  unsigned int        colorTL = PACK_COLOR( aColorTL, aDst );
  unsigned int        colorTR = PACK_COLOR( aColorTR, aDst );
  unsigned int        colorBL = PACK_COLOR( aColorBL, aDst );
  unsigned int        colorBR = PACK_COLOR( aColorBR, aDst );

  /* Only screen/native surfaces are allowed as the destination */
  if ( !dst || (( dst->Surface->Format != EW_PIXEL_FORMAT_SCREEN ) &&
                ( dst->Surface->Format != EW_PIXEL_FORMAT_NATIVE )))
  {
    EwErrorPD( 161, aDst, aDstFrameNo );
    return;
  }

  /* The support for Native surface as destination is disabled. */
  #ifdef EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION
    if ( dst->Surface->Format == EW_PIXEL_FORMAT_NATIVE )
    {
      EwErrorPD( 355, aDst, aDstFrameNo );
      return;
    }
  #endif

  /* Bitmaps loaded from resources can't be modified by drawing operations */
  if ( dst->Surface->Tag1 || dst->Surface->Tag2 )
  {
    EwErrorPD( 345, aDst, aDstFrameNo );
    return;
  }

  /* Is source surface valid? */
  if ( !src || ( src->Surface->Format == EW_PIXEL_FORMAT_SCREEN ))
  {
    EwErrorPD( 164, aSrc, aSrcFrameNo );
    return;
  }

  /* The support for color gradients is disabled. */
  #ifdef EW_DONT_USE_GRADIENTS
    if ( IS_LINEAR_GRADIENT4( colorTL, colorTR, colorBL, colorBR ) ||
         IS_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
    {
      EwError( 375 );
      return;
    }
  #endif

  /* RGB565 bitmaps don't contain transparancy. Alpha-blending can be avoided. */
  if ( aBlend && ( src->Surface->Format == EW_PIXEL_FORMAT_RGB565 ) &&
       IS_OPAQUE4( colorTL, colorTR, colorBL, colorBR ))
    aBlend = 0;

  /* Force the source surface to perform its own pending tasks */
  EwFlushTasks( src->Surface );

  /* Limit the source area to the source frame boundary */
  aSrcRect.Point1.X = MAX( aSrcRect.Point1.X, 0 );
  aSrcRect.Point1.Y = MAX( aSrcRect.Point1.Y, 0 );
  aSrcRect.Point2.X = MIN( aSrcRect.Point2.X, aSrc->FrameSize.X );
  aSrcRect.Point2.Y = MIN( aSrcRect.Point2.Y, aSrc->FrameSize.Y );

  /* Limit the area to the destination frame boundary and to the
     clipping area */
  x1 = MAX3( aClipRect.Point1.X, x1, 0 );
  y1 = MAX3( aClipRect.Point1.Y, y1, 0 );
  x2 = MIN3( aClipRect.Point2.X, x2, aDst->FrameSize.X );
  y2 = MIN3( aClipRect.Point2.Y, y2, aDst->FrameSize.Y );

  /* Nothing to do? */
  if (( x2 <= x1 ) || ( y2 <= y1 ) ||
      ( aSrcRect.Point2.X <= aSrcRect.Point1.X ) ||
      ( aSrcRect.Point2.Y <= aSrcRect.Point1.Y ) ||
      ( aBlend && IS_TRANSPARENT4( colorTL, colorTR, colorBL, colorBR )))
    return;

  /* aSrcPos should remain in the source area */
  aSrcPos.X = aSrcPos.X % ( aSrcRect.Point2.X - aSrcRect.Point1.X ) +
            (( aSrcPos.X < 0 )? ( aSrcRect.Point2.X - aSrcRect.Point1.X ) : 0 );
  aSrcPos.Y = aSrcPos.Y % ( aSrcRect.Point2.Y - aSrcRect.Point1.Y ) +
            (( aSrcPos.Y < 0 )? ( aSrcRect.Point2.Y - aSrcRect.Point1.Y ) : 0 );

  /* Mark the surface as involved in a drawing operation */
  src->Surface->Owned++;
  src->Surface->Used++;

  /* Start the preparation of a new drawing operation */
  if (( issue = EwInitIssue( dst->Surface )) == 0 )
  {
    src->Surface->Owned--;
    src->Surface->Used--;
    EwErrorPD( 128, aDst, 0 );
    return;
  }

  /* Get a storage area for the drawings parameter */
  data = EwAllocTaskData( issue, sizeof( *data ));
  data->DstX1     = (short)( aDstRect.Point1.X + dst->Origin.X );
  data->DstY1     = (short)( aDstRect.Point1.Y + dst->Origin.Y );
  data->DstX2     = (short)( aDstRect.Point2.X + dst->Origin.X );
  data->DstY2     = (short)( aDstRect.Point2.Y + dst->Origin.Y );
  data->SrcX1     = (short)( aSrcRect.Point1.X + src->Origin.X );
  data->SrcY1     = (short)( aSrcRect.Point1.Y + src->Origin.Y );
  data->SrcX2     = (short)( aSrcRect.Point2.X + src->Origin.X );
  data->SrcY2     = (short)( aSrcRect.Point2.Y + src->Origin.Y );
  data->OfsX      = (short)aSrcPos.X;
  data->OfsY      = (short)aSrcPos.Y;
  data->Surface   = src->Surface;
  data->Colors[0] = colorTL;
  data->Colors[1] = colorTR;
  data->Colors[2] = colorBR;
  data->Colors[3] = colorBL;

  /* Enqueue the drawing operation by the issue */
  task = EwAllocTask( issue, 0 );
  task->Token     = EW_TASKID_TILE_SURFACE;
  task->Data      = data;
  task->X1        = (short)( x1 + dst->Origin.X );
  task->Y1        = (short)( y1 + dst->Origin.Y );
  task->X2        = (short)( x2 + dst->Origin.X );
  task->Y2        = (short)( y2 + dst->Origin.Y );
  task->Flags     = (short)EW_TASK_ENTIRE_AREA;

  /* Avoid slow alpha-blending if the entire source area of the bitmap is
     opaque */
  if ( aBlend && IS_OPAQUE4( colorTL, colorTR, colorBL, colorBR ) &&
     ( src->OpaqueRect.Point1.X <= aSrcRect.Point1.X ) &&
     ( src->OpaqueRect.Point1.Y <= aSrcRect.Point1.Y ) &&
     ( src->OpaqueRect.Point2.X >= aSrcRect.Point2.X ) &&
     ( src->OpaqueRect.Point2.Y >= aSrcRect.Point2.Y ))
    aBlend = 0;

  /* Complete the task initialisation */
  task->Flags |= (short)( aBlend? EW_TASK_ALPHABLEND : 0 );

  /* What to do with the 4 colors? */
  #ifndef EW_DONT_USE_GRADIENTS
    if ( IS_LINEAR_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
      task->Flags |= EW_TASK_LINEAR_GRADIENT;
    else if ( IS_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
      task->Flags |= EW_TASK_GRADIENT;
    else
  #endif

  /* ... or global opacity value? */
  if (( src->Surface->Format == EW_PIXEL_FORMAT_ALPHA8 ) ||
      ( aColorTL.Alpha < 255 ))
    task->Flags |= EW_TASK_SOLID;

  /* The surface is waiting for drawing operation (it remain 'used'). */
  src->Surface->Owned--;

  /* Close the preparation. This may flush the issue */
  EwDoneIssue( dst->Surface );
}


EW_INSTRUMENT_VOID_FUNC( EwTileBitmap, ( XBitmap* aDst, XBitmap* aSrc,
  XInt32 aDstFrameNo, XInt32 aSrcFrameNo,  XRect aClipRect, XRect aDstRect,
  XRect aSrcRect, XPoint aSrcPos, XColor aColorTL, XColor aColorTR,
  XColor aColorBR, XColor aColorBL, XBool aBlend ), ( aDst, aSrc, aDstFrameNo,
  aSrcFrameNo,  aClipRect, aDstRect, aSrcRect, aSrcPos, aColorTL, aColorTR,
  aColorBR, aColorBL, aBlend ))


/*******************************************************************************
* FUNCTION:
*   EwWarpBitmap
*
* DESCRIPTION:
*   The function EwWarpBitmap() performs the projection of a rectangular source
*   bitmap area on a 4 corner polygon within the destination bitmap. The kind
*   of transformation is predetermined by the given polygon coordinates. That
*   way scaling, rotating, mirroring and even 3D perspective warp effects can
*   be performed. In case of a perspective correct projection, the coefficients
*   aW1 .. aW4 controls the perspective warp.
*
*   Please note that only convex polygons can be drawn with this technique.
*   Drawing non convex polygons can produce unexpected outputs depending on the
*   underlying graphics subsystem or the 3D hardware engine.
*
*   When performing the projection, the function assumes that the 4 corners of
*   of the source bitmap area are mapped to the four corners of the destination
*   polygon. The top-left source corner corresponds to the first polygon corner.
*   The top-right to the second, bottom-right to the third and the bottom-left
*   to the fourth.
*
*   The copied pixel can optionally be modulated by a color gradient specified
*   by the four color parameters aColor1 .. aColor4.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst        - Destination bitmap.
*   aSrc        - Source bitmap.
*   aDstFrameNo - Frame within the destination bitmap affected by the drawing
*     operation.
*   aSrcFrameNo - Source bitmap frame affected by the operation.
*   aClipRect   - Area to limit the drawing operation (Relative to the top-left
*     corner of the destination bitmap frame).
*   aDstX1,
*   aDstY1,
*   aDstW1,
*   ...
*   aDstX4,
*   aDstY4,
*   aDstW4      - Coordinates of the polygon to fill with the source bitmap as
*     floating point values for sub-pixel precision (Relative to the top-left
*     corner of the destination bitmap frame).
*   aSrcRect    - Area to copy from the source bitmap (Relative to the top-left
*     corner of the source bitmap frame).
*   aColor1,
*   aColor2,
*   aColor3,
*   aColor4     - Color values corresponding to the four corners of the polygon.
*   aBlend      - If != 0, the drawn pixel will be alpha-blended with the pixel
*     in the background.
*   aFilter     - If != 0, the source bitmap pixel will be bi-linear filtered
*     in order to get better output.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwWarpBitmap_( XBitmap* aDst, XBitmap* aSrc, XInt32 aDstFrameNo,
  XInt32 aSrcFrameNo, XRect aClipRect, XFloat aDstX1, XFloat aDstY1,
  XFloat aDstW1, XFloat aDstX2, XFloat aDstY2, XFloat aDstW2, XFloat aDstX3,
  XFloat aDstY3, XFloat aDstW3, XFloat aDstX4, XFloat aDstY4, XFloat aDstW4,
  XRect aSrcRect, XColor aColor1, XColor aColor2, XColor aColor3,
  XColor aColor4, XBool aBlend, XBool aFilter )
{
  #ifndef EW_DONT_USE_WARP_FUNCTIONS
    XBitmapFrame*       dst    = MapBitmapFrame( aDst, aDstFrameNo );
    XBitmapFrame*       src    = MapBitmapFrame( aSrc, aSrcFrameNo );
    XWarpSurface*       data;
    XIssue*             issue;
    XTask*              task;
    XFloat              dstX1  = MINF4( aDstX1, aDstX2, aDstX3, aDstX4 ) * 16.0f;
    XFloat              dstY1  = MINF4( aDstY1, aDstY2, aDstY3, aDstY4 ) * 16.0f;
    XFloat              dstX2  = MAXF4( aDstX1, aDstX2, aDstX3, aDstX4 ) * 16.0f;
    XFloat              dstY2  = MAXF4( aDstY1, aDstY2, aDstY3, aDstY4 ) * 16.0f;
    int                 x1     = (int)( dstX1 + 8.0f ) >> 4;
    int                 y1     = (int)( dstY1 + 8.0f ) >> 4;
    int                 x2     = (int)( dstX2 + 9.0f ) >> 4;
    int                 y2     = (int)( dstY2 + 9.0f ) >> 4;
    unsigned int        color1 = PACK_COLOR( aColor1, aDst );
    unsigned int        color2 = PACK_COLOR( aColor2, aDst );
    unsigned int        color3 = PACK_COLOR( aColor3, aDst );
    unsigned int        color4 = PACK_COLOR( aColor4, aDst );
    int                 affine = 0;
    int                 scale  = 0;
    float               dstOriginX;
    float               dstOriginY;

  #ifdef EW_ENABLE_COLOR_TABLE
    /* Index8 target pixel format doesn't support the bi-linear filtering */
    aFilter = 0;
  #endif

    /* Only screen/native surfaces are allowed as the destination */
    if ( !dst || (( dst->Surface->Format != EW_PIXEL_FORMAT_SCREEN ) &&
                  ( dst->Surface->Format != EW_PIXEL_FORMAT_NATIVE )))
    {
      EwErrorPD( 162, aDst, aDstFrameNo );
      return;
    }

  /* The support for Native surface as destination is disabled. */
  #ifdef EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION
    if ( dst->Surface->Format == EW_PIXEL_FORMAT_NATIVE )
    {
      EwErrorPD( 356, aDst, aDstFrameNo );
      return;
    }
  #endif

    /* Bitmaps loaded from resources can't be modified by drawing operations */
    if ( dst->Surface->Tag1 || dst->Surface->Tag2 )
    {
      EwErrorPD( 346, aDst, aDstFrameNo );
      return;
    }

    /* Is source surface valid? */
    if ( !src || ( src->Surface->Format == EW_PIXEL_FORMAT_SCREEN ))
    {
      EwErrorPD( 165, aSrc, aSrcFrameNo );
      return;
    }

    /* The destination area affected by the operation is too large to be calculated
       in integer without producing overflows. */
    if ((( dstX2 - dstX1 ) > 65536.0f ) || (( dstX2 - dstX1 ) < -65536.0f ) ||
        (( dstY2 - dstY1 ) > 65536.0f ) || (( dstY2 - dstY1 ) < -65536.0f ))
    {
      EwError( 189 );
      return;
    }

    /* The support for color gradients is disabled. */
    #ifdef EW_DONT_USE_GRADIENTS
      if ( IS_LINEAR_GRADIENT4( color1, color2, color3, color4 ) ||
           IS_GRADIENT4( color1, color2, color3, color4 ))
      {
        EwError( 376 );
        return;
      }
    #endif

    /* RGB565 bitmaps don't contain transparancy. Alpha-blending can be avoided. */
    if ( aBlend && ( src->Surface->Format == EW_PIXEL_FORMAT_RGB565 ) &&
         IS_OPAQUE4( color1, color2, color3, color4 ))
      aBlend = 0;

    /* Force the source surface to perform its own pending tasks */
    EwFlushTasks( src->Surface );

    /* Take in account the source frame boundary */
    aSrcRect.Point1.X = MAX( aSrcRect.Point1.X, 0 );
    aSrcRect.Point1.Y = MAX( aSrcRect.Point1.Y, 0 );
    aSrcRect.Point2.X = MIN( aSrcRect.Point2.X, aSrc->FrameSize.X );
    aSrcRect.Point2.Y = MIN( aSrcRect.Point2.Y, aSrc->FrameSize.Y );

    /* Limit the area to the destination frame boundary and to the clipping
       area */
    x1 = MAX3( aClipRect.Point1.X, x1, 0 );
    y1 = MAX3( aClipRect.Point1.Y, y1, 0 );
    x2 = MIN3( aClipRect.Point2.X, x2, aDst->FrameSize.X );
    y2 = MIN3( aClipRect.Point2.Y, y2, aDst->FrameSize.Y );

    /* Nothing to do? */
    if (( x2 <= x1 ) || ( y2 <= y1 ) ||
        ( aSrcRect.Point2.X <= aSrcRect.Point1.X ) ||
        ( aSrcRect.Point2.Y <= aSrcRect.Point1.Y ) ||
        ( aBlend && IS_TRANSPARENT4( color1, color2, color3, color4 )))
      return;

    /* The 'W' coefficients have always to be positive... */
    if (( aDstW1 <= 0.0f ) && ( aDstW2 <= 0.0f ) && ( aDstW3 <= 0.0f ) &&
        ( aDstW4 <= 0.0f ))
    {
      aDstW1 = -aDstW1; aDstW2 = -aDstW2;
      aDstW3 = -aDstW3; aDstW4 = -aDstW4;
    }

    /* Mixed signs can not be handled */
    if (( aDstW1 < 0.0f ) || ( aDstW2 < 0.0f ) || ( aDstW3 < 0.0f ) ||
        ( aDstW4 < 0.0f ))
    {
      EwError( 166 );
      return;
    }

    /* Kind of the transformation - affine, scale or perspective? Select 'scale'
       if entire pixel are affected only */
    affine = ( aDstW1 == aDstW2 ) && ( aDstW3 == aDstW4 ) && ( aDstW1 == aDstW3 );
    scale  =   affine &&
             ( aDstX1 == aDstX4 ) && ( aDstX2 == aDstX3 ) &&
             ( aDstY1 == aDstY2 ) && ( aDstY3 == aDstY4 ) &&
             ( aDstX1 <  aDstX2 ) && ( aDstY1 <  aDstY4 ) &&
             !((int)dstX1 & 15 ) && !((int)dstY1 & 15 ) &&
             !((int)dstX2 & 15 ) && !((int)dstY2 & 15 );

    /* For perspective transformation bring the 'W' coefficients in the common
       range 0.0 .. 1.0 */
    if ( !affine )
    {
      XFloat minW = aDstW1;

      if ( aDstW2 < minW ) minW = aDstW2;
      if ( aDstW3 < minW ) minW = aDstW3;
      if ( aDstW4 < minW ) minW = aDstW4;

      /* The shape is not convex */
      if ( !aDstW1 || !aDstW2 || !aDstW3 || !aDstW4 )
      {
        EwError( 272 );
        return;
      }

      aDstW1 = minW / aDstW1; aDstW2 = minW / aDstW2;
      aDstW3 = minW / aDstW3; aDstW4 = minW / aDstW4;
    }

    /* In case of pure affine transformation reset the 'W' coefficients */
    else
    {
      aDstW1 = 1.0f; aDstW2 = 1.0f;
      aDstW3 = 1.0f; aDstW4 = 1.0f;
    }

    dstOriginX = (float)dst->Origin.X;
    dstOriginY = (float)dst->Origin.Y;

    /* Mark the surface as involved in a drawing operation */
    src->Surface->Owned++;
    src->Surface->Used++;

    /* Start the preparation of a new drawing operation */
    if (( issue = EwInitIssue( dst->Surface )) == 0 )
    {
      src->Surface->Owned--;
      src->Surface->Used--;
      EwErrorPD( 129, aDst, 0 );
      return;
    }

    /* Get a storage area for the drawings parameter */
    data = EwAllocTaskData( issue, sizeof( *data ));
    data->DstX1     = (float)( aDstX1 + dstOriginX );
    data->DstY1     = (float)( aDstY1 + dstOriginY );
    data->DstW1     = (float)aDstW1;
    data->DstX2     = (float)( aDstX2 + dstOriginX );
    data->DstY2     = (float)( aDstY2 + dstOriginY );
    data->DstW2     = (float)aDstW2;
    data->DstX3     = (float)( aDstX3 + dstOriginX );
    data->DstY3     = (float)( aDstY3 + dstOriginY );
    data->DstW3     = (float)aDstW3;
    data->DstX4     = (float)( aDstX4 + dstOriginX );
    data->DstY4     = (float)( aDstY4 + dstOriginY );
    data->DstW4     = (float)aDstW4;
    data->SrcX1     = (short)( aSrcRect.Point1.X + src->Origin.X );
    data->SrcY1     = (short)( aSrcRect.Point1.Y + src->Origin.Y );
    data->SrcX2     = (short)( aSrcRect.Point2.X + src->Origin.X );
    data->SrcY2     = (short)( aSrcRect.Point2.Y + src->Origin.Y );
    data->Surface   = src->Surface;
    data->Colors[0] = color1;
    data->Colors[1] = color2;
    data->Colors[2] = color3;
    data->Colors[3] = color4;

    /* Enqueue the drawing operation by the issue */
    task = EwAllocTask( issue, 0 );
    task->Data      = data;
    task->X1        = (short)( x1 + dst->Origin.X );
    task->Y1        = (short)( y1 + dst->Origin.Y );
    task->X2        = (short)( x2 + dst->Origin.X );
    task->Y2        = (short)( y2 + dst->Origin.Y );
    task->Flags     = (short)( aFilter? EW_TASK_HIGH_QUALITY : 0 );

    /* Avoid slow alpha-blending if the entire source area of the bitmap is
       opaque - this works without problems with deactivated bi-linear filter. */
    if ( aBlend && !aFilter && IS_OPAQUE4( color1, color2, color3, color4 ) &&
       ( src->OpaqueRect.Point1.X <= aSrcRect.Point1.X ) &&
       ( src->OpaqueRect.Point1.Y <= aSrcRect.Point1.Y ) &&
       ( src->OpaqueRect.Point2.X >= aSrcRect.Point2.X ) &&
       ( src->OpaqueRect.Point2.Y >= aSrcRect.Point2.Y ))
      aBlend = 0;

    /* If the bi-linear filter is active, ensure that no semi-transparent pixel
       lying outside the copied area will be involved in the filter calculation.
       For this purpose simply take in account an additional 1 pixel wide border
       around this area. */
    if ( aBlend && aFilter && IS_OPAQUE4( color1, color2, color3, color4 ) &&
       ( src->OpaqueRect.Point1.X < aSrcRect.Point1.X ) &&
       ( src->OpaqueRect.Point1.Y < aSrcRect.Point1.Y ) &&
       ( src->OpaqueRect.Point2.X > aSrcRect.Point2.X ) &&
       ( src->OpaqueRect.Point2.Y > aSrcRect.Point2.Y ))
      aBlend = 0;

    /* Complete the task initialisation */
    task->Flags |= (short)( aBlend? EW_TASK_ALPHABLEND  : 0 );
    task->Flags |= (short)( scale?  EW_TASK_ENTIRE_AREA : 0 );

    /* What to do with the 4 colors? */
    #ifndef EW_DONT_USE_GRADIENTS
      if ( scale && IS_LINEAR_GRADIENT4( color1, color2, color4, color3 ))
        task->Flags |= EW_TASK_LINEAR_GRADIENT;
      else if ( IS_GRADIENT4( color1, color2, color3, color4 ))
        task->Flags |= EW_TASK_GRADIENT;
      else
    #endif

    /* ... or global opacity value? */
    if (( src->Surface->Format == EW_PIXEL_FORMAT_ALPHA8 ) ||
        ( aColor1.Alpha < 255 ))
      task->Flags |= EW_TASK_SOLID;

    /* Kind of the warp operation? */
    if      ( scale  ) task->Token = EW_TASKID_WARP_SCALE_SURFACE;
    else if ( affine ) task->Token = EW_TASKID_WARP_AFFINE_SURFACE;
    else               task->Token = EW_TASKID_WARP_PERSP_SURFACE;

    /* The surface is waiting for drawing operation (it remain 'used'). */
    src->Surface->Owned--;

    /* Close the preparation. This may flush the issue */
    EwDoneIssue( dst->Surface );
  #else
    XBitmapFrame* src = MapBitmapFrame( aSrc, aSrcFrameNo );

    /* Force the source surface to perform its own pending tasks */
    if ( src )
      EwFlushTasks( src->Surface );

    EW_UNUSED_ARG( aDst );
    EW_UNUSED_ARG( aDstFrameNo );
    EW_UNUSED_ARG( aSrcFrameNo );
    EW_UNUSED_ARG( aClipRect );
    EW_UNUSED_ARG( aDstX1 );
    EW_UNUSED_ARG( aDstY1 );
    EW_UNUSED_ARG( aDstW1 );
    EW_UNUSED_ARG( aDstX2 );
    EW_UNUSED_ARG( aDstY2 );
    EW_UNUSED_ARG( aDstW2 );
    EW_UNUSED_ARG( aDstX3 );
    EW_UNUSED_ARG( aDstY3 );
    EW_UNUSED_ARG( aDstW3 );
    EW_UNUSED_ARG( aDstX4 );
    EW_UNUSED_ARG( aDstY4 );
    EW_UNUSED_ARG( aDstW4 );
    EW_UNUSED_ARG( aSrcRect );
    EW_UNUSED_ARG( aColor1 );
    EW_UNUSED_ARG( aColor2 );
    EW_UNUSED_ARG( aColor3 );
    EW_UNUSED_ARG( aColor4 );
    EW_UNUSED_ARG( aBlend );
    EW_UNUSED_ARG( aFilter );
    EwError( 196 );
  #endif
}


EW_INSTRUMENT_VOID_FUNC( EwWarpBitmap, ( XBitmap* aDst, XBitmap* aSrc,
  XInt32 aDstFrameNo, XInt32 aSrcFrameNo, XRect aClipRect, XFloat aDstX1,
  XFloat aDstY1, XFloat aDstW1, XFloat aDstX2, XFloat aDstY2, XFloat aDstW2,
  XFloat aDstX3, XFloat aDstY3, XFloat aDstW3, XFloat aDstX4, XFloat aDstY4,
  XFloat aDstW4, XRect aSrcRect, XColor aColor1, XColor aColor2, XColor aColor3,
  XColor aColor4, XBool aBlend, XBool aFilter ), ( aDst, aSrc, aDstFrameNo,
  aSrcFrameNo, aClipRect, aDstX1, aDstY1, aDstW1, aDstX2, aDstY2, aDstW2, aDstX3,
  aDstY3, aDstW3, aDstX4, aDstY4, aDstW4, aSrcRect, aColor1, aColor2, aColor3,
  aColor4, aBlend, aFilter ))


/*******************************************************************************
* FUNCTION:
*   EwAdjustFilterBlurRadius
*
* DESCRIPTION:
*   The function EwAdjustFilterBlurRadius() estimates the resulting radius for
*   a blur filter operation. Since the blur algorithm may support few discrete
*   blur radius values only, the function permits the pre-selection of the best
*   matching radius.
*
* ARGUMENTS:
*   aBlurRadius - The desired blur radius expressed in pixel.
*
* RETURN VALUE:
*   The best matching blur radius for the value specified in the parameter
*   aBlurRadius.
*
*******************************************************************************/
XInt32 EwAdjustFilterBlurRadius_( XInt32 aBlurRadius )
{
  #ifdef EwGfxAdjustFilterBlurRadius
    return EwGfxAdjustFilterBlurRadius( aBlurRadius );
  #else
    if ( aBlurRadius <=  0 ) return 0;
    if ( aBlurRadius >  64 ) return 64;
    return aBlurRadius;
  #endif
}


EW_INSTRUMENT_FUNC( EwAdjustFilterBlurRadius, XInt32, ( XInt32 aBlurRadius ),
  ( aBlurRadius ))


/*******************************************************************************
* FUNCTION:
*   EwFilterBitmap
*
* DESCRIPTION:
*   The function EwFilterBitmap() copies a rectangular area from the bitmap aSrc
*   to the bitmap aDst by applying one or multiple filters. The destination area
*   affected by this operation is determined by the parameter aDstRect and the
*   position in the source bitmap to map to the top-left corner of this area is
*   determined by the parameter aSrcPos.
*
*   This function implements following three filter categories. Multiple filter
*   categories can be used together to create more sophisticated effects:
*
*   1 Mask: The parameter aMask can provide an optional ALPHA8 bitmap to use as
*     mask for the filter operation. If aMask is NULL, no masking is applied.
*     The position in the mask bitmap to map to the top-left corner of the area
*     aDstRect is determined by the parameter aMaskPos. The values from the mask
*     bitmap are used to modulate the opacity of the resulting pixel. The area
*     outside the mask bitmap is considered as transparent. With the parameter
*     aMaskInverted the opacity resulting from the mask is inverted.
*
*   2 Blur: This filter is controlled by the parameter aBlurRadius. If this
*     value is <= 0, the blur is disabled. The parameter aBlurClampToEdges
*     controls whether the blur effect should clamp abruptly at the edges of
*     the area aDstRect. To query the supported blur radius values use the
*     function EwAdjustFilterBlurRadius(). Please note: If used together with
*     'Mask' filter, the order in which blur and mask operations are performed
*     is significant. Per default the mask affects the pixel 'after' preceding
*     blur filter operation is done. By using the parameter aMaskBeforeBlur
*     the order of the operations can be reversed.
*
*   3 Tint: This filter calculates from the original color value a new color
*     value, which then is mixed with the original color value according to the
*     parameter aIntensity. To control the 'Tint' filter the parameters aMode
*     and aColor are used.
*
*   The colors resulting from all above mentioned filter operations are finally
*   modulated by the opacity value specified in the parameter aOpacity. This
*   value lies in range 0 .. 255. In this way, the effect of all active filters
*   can be faded-in/out.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last parameter aBlend controls the
*   mode how resulting pixel affect the pixel already existing in the drawing
*   destination. If aBlend is 'true', the resulting pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst            - Destination bitmap.
*   aSrc            - Source bitmap for the filter operation. Important: the
*     implementation of the filter functions restricts the source bitmap to
*     contain exact one frame. So-called multi-frame bitmaps are not supported.
*   aMask           - Optional bitmap to use as mask. The mask bitmap has to be
*     stored in the ALPHA8 format (See EW_PIXEL_FORMAT_XXX). Important: filters
*     implemented in this function restrict the mask bitmap to contain exact
*     one frame. So-called multi-frame bitmaps are not supported.
*   aDstFrameNo     - Frame within the destination bitmap to use as destination
*     for the drawing operation.
*   aClipRect      - Area to limit the drawing operation (Relative to the top-
*     left corner of the destination bitmap frame).
*   aDstRect       - Area affected by the drawing operation (relative to the
*     top-left corner of the destination bitmap frame).
*   aSrcPos         - Position within the source bitmap (parameter aSrc) to map
*     to the origin (top-left corner) of the aDstRect area.
*   aMaskPos        - Position within the mask bitmap (parameter aMask) to map
*     to the origin (top-left corner) of the aDstRect area.
*   aMaskInverted   - This parameter controls how pixel data from the bitmap
*     specified in the parameter aMask are evaluated. Setting aMaskInverted to
*     the value 'true' inverts the data from the mask resulting in opaque pixel
*     wherever the mask does contain a transparent pixel and transparent pixel
*     wherever an opaque pixel is found in the mask bitmap. Areas outside the
*     mask bitmap are conseqently considered as opaque when aMaskInverted is
*     set 'true'.
*   aMaskBeforeBlur - The parameter aMaskBeforeBlur controls the order in which
*     mask and blur operations are performed. If aMaskBeforeBlur is 'false',
*     the mask is applied after the blur effect. This allows the blur effect to
*     be clipped by the mask. If aMaskBeforeBlur is 'true', the blur effect is
*     applied on previously masked image content. The blur effect considers the
*     masked out areas as being transparent which allows the edges between the
*     regular and masked out areas to appear blurred.
*   aBlurRadius     - Determines the intensity of the blur filter effect. The
*     value is expressed in pixel as radius to blur the corresponding source
*     image content. If the value is <= 0, no blur filter is applied. With the
*     parameter aBlurClampToEdges the effect at the edges of the aDstRect area
*     can be controlled. Please note, the Graphics Engine may support only few
*     discrete intensity values for the blur filter. To query the real values
*     use the function EwAdjustFilterBlurRadius().
*   aBlurClampToEdges - Controls the blur effect at the edges of the source
*     bitmap. Providing 'true' in this parameter prevents the edges from being
*     transparent when the bitmap is aligned at edges of the aDstRect area.
*   aMode           - This parameter controls the tint filter. Depending on
*     the selected value, the original colors found in the source bitmap aSrc
*     are modified or replaced by the value aColor. The intensity of the effect
*     is controlled by the parameter aIntensity. See EW_TINT_MODE_XXX for more
*     details.
*   aIntensity      - This parameter controls the intensity of the tint filter.
*     This value lies in range of 0.0 .. 1.0. If the value is 1.0, the original
*     colors are completely replaced by values resulting from the filter effect.
*     In turn, the value equal to zero results in the original color values
*     without any tinting effect. Otherwise the colors are interpolated between
*     the original and the color value resulting from the filter effect.
*   aColor          - A color value to be used by the tint filter. See aMode
*     parameter.
*   aOpacity        - Modulates the opacity of the pixel data resulting from
*     the filter operation. This property can take values in range of 0 .. 255.
*   aBlend          - If != 0, the drawn pixel will be alpha-blended with the
*     pixel in the background.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwFilterBitmap_( XBitmap* aDst, XBitmap* aSrc, XBitmap* aMask,
  XInt32 aDstFrameNo, XRect aClipRect, XRect aDstRect, XPoint aSrcPos,
  XPoint aMaskPos, XBool aMaskInverted, XBool aMaskBeforeBlur,
  XInt32 aBlurRadius, XBool aBlurClampToEdges, XInt32 aMode, XFloat aIntensity,
  XColor aColor, XInt32 aOpacity, XBool aBlend )
{
  #if !defined EW_DONT_USE_BLUR_FUNCTIONS || \
      !defined EW_DONT_USE_MASK_FUNCTIONS || \
      !defined EW_DONT_USE_TINT_FUNCTIONS
    XBitmapFrame*   dst   = MapBitmapFrame( aDst, aDstFrameNo );
    XBitmapFrame*   src   = MapBitmapFrame( aSrc, 0 );
    XBitmapFrame*   mask  = 0;
    XFilterSurface* data;
    XIssue*         issue;
    XTask*          task;
    int             x1    = aDstRect.Point1.X;
    int             y1    = aDstRect.Point1.Y;
    int             x2    = aDstRect.Point2.X;
    int             y2    = aDstRect.Point2.Y;
    int             sx1, sy1, sx2, sy2;

    /* Only screen/native surfaces are allowed as the destination */
    if ( !dst || (( dst->Surface->Format != EW_PIXEL_FORMAT_SCREEN ) &&
                  ( dst->Surface->Format != EW_PIXEL_FORMAT_NATIVE )))
    {
      EwErrorPD( 410, aDst, aDstFrameNo );
      return;
    }

    /* The support for Native surface as destination is disabled. */
    #ifdef EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION
      if ( dst->Surface->Format == EW_PIXEL_FORMAT_NATIVE )
      {
        EwErrorPD( 359, aDst, aDstFrameNo );
        return;
      }
    #endif

    /* Bitmaps loaded from resources can't be modified by drawing operations */
    if ( dst->Surface->Tag1 || dst->Surface->Tag2 )
    {
      EwErrorPD( 349, aDst, aDstFrameNo );
      return;
    }

    /* Is source surface valid? */
    if ( !src || ( src->Surface->Format == EW_PIXEL_FORMAT_SCREEN ) ||
       ( aSrc->NoOfFrames > 1 ))
    {
      EwErrorPD( 411, aSrc, 0 );
      return;
    }

    /* Report an error if there is no support for mask operations */
    #ifdef EW_DONT_USE_MASK_FUNCTIONS
      if ( aMask )
      {
        aMask = 0;
        EwError( 417 );
      }
    #endif

    /* When mapping a mask frame, the previously mapped source frame may be
       discarded. Prevent this. */
    if ( aMask )
    {
      src->Surface->Used++;
      mask = MapBitmapFrame( aMask, 0 );
      src->Surface->Used--;
    }

    /* Is mask surface valid? */
    if (( mask && (( mask->Surface->Format != EW_PIXEL_FORMAT_ALPHA8 ) ||
                   ( aMask->NoOfFrames > 1 ))) || ( aMask && !mask ))
    {
      EwErrorPD( 412, aMask, 0 );
      return;
    }

    /* Report an error if there is no support for blur operations */
    #ifdef EW_DONT_USE_BLUR_FUNCTIONS
      if ( aBlurRadius > 0 )
      {
        aBlurRadius = 0;
        EwError( 416 );
      }
    #endif

    /* Clamp the parameters to their correct range */
    if ( aIntensity < 0.0f ) aIntensity = 0.0f;
    if ( aIntensity > 1.0f ) aIntensity = 1.0f;
    if ( aOpacity   <    0 ) aOpacity   =   0;
    if ( aOpacity   >  255 ) aOpacity   = 255;

    /* Adjust the parameters and take in account dependencies between them */
    aBlurRadius        = EwAdjustFilterBlurRadius( aBlurRadius );
    aBlurClampToEdges &= aBlurRadius > 0;
    aMaskInverted     &= !!mask;
    aMaskBeforeBlur   &= mask && ( aBlurRadius > 0 );
    aMode             &= ( aIntensity > 0.0f )? 3 : 0;

    /* GRAYSCALE mode is just a special case of the TINT_BY_LUMINACE mode
       modulating white color. */
    if ( aMode == EW_TINT_MODE_GRAYSCALE )
    {
      XColor c = { 255, 255, 255, 255 };
      aMode  = EW_TINT_MODE_TINT_BY_LUMINANCE;
      aColor = c;
    }

    /* The opacity in RGB565 sources is 1 for all pixel. 'Tint by opacity' has
       no effect. */
    if (( src->Surface->Format == EW_PIXEL_FORMAT_RGB565 ) &&
        ( aMode == EW_TINT_MODE_TINT_BY_OPACITY ))
      aMode = 0;

    /* Using ALPHA8 source enforces the 'tint by opacity' mode with white
       color. */
    if (( src->Surface->Format == EW_PIXEL_FORMAT_ALPHA8 ) && !aMode )
    {
      XColor c = { 255, 255, 255, 255 };
      aColor = c;
    }

    /* Using ALPHA8 source enforces the 'tint by opacity' mode */
    if ( src->Surface->Format == EW_PIXEL_FORMAT_ALPHA8 )
      aMode  = EW_TINT_MODE_TINT_BY_OPACITY;

    /* Report an error if there is no support for tint operations */
    #ifdef EW_DONT_USE_TINT_FUNCTIONS
      if ( aMode )
      {
        aMode = 0;
        EwError( 418 );

        if ( src->Surface->Format == EW_PIXEL_FORMAT_ALPHA8 )
          return;
      }
    #endif

    /* Force the source surface to perform its own pending tasks. Note, the
       flush may trigger the surface cache cleanup. This may end in the mask
       surface content being discarded. Mark the surface as used temporarily
       to prevent this. */
    if ( mask ) mask->Surface->Used++;
    EwFlushTasks( src->Surface );
    if ( mask ) mask->Surface->Used--;

    /* Blur operations may require a Native surface to store intermediate
       contents. Report an error if there is no support for Native surfaces.
       Note: ALPHA8 source surfaces may use ALPHA8 for intermediate storage if
       the Mask/Tint operation is performed AFTER the blur. */
    #if defined EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION || \
        defined EW_DONT_USE_NATIVE_SURFACES
      if (( aBlurRadius > 0 ) && ( aMaskBeforeBlur ||
          ( src->Surface->Format != EW_PIXEL_FORMAT_ALPHA8 )))
      {
        EwError( 419 );
        return;
      }
    #endif

    /* The operation will have no effect. All results will be transparent and
       alpha-blending is enbabled. */
    if ( aBlend && !aOpacity )
      return;

    /* The operation will have no effect. All results will be transparent and
       alpha-blending is enbabled. */
    if ( aBlend && ( aIntensity == 1.0f ) && !aColor.Alpha && aMode )
      return;

    /* No filter to apply. Just copy the source bitmap. */
    if ( !aBlurRadius && !mask && ( !aMode || ( aIntensity == 0.0f )))
    {
      XColor c = { 255, 255, 255, (XUInt8)aOpacity };
      EwCopyBitmap( aDst, aSrc, aDstFrameNo, 0, aClipRect, aDstRect, aSrcPos,
                    c, c, c, c, aBlend );
      return;
    }

    /* Mask filter with inverted mask. In such case areas lying outside the mask
       are considered as opaque - the source bitmap within those areas can be
       copied directly. */
    if ( aMaskInverted && !aMode && !aBlurRadius )
    {
      int    mx1 = ( aClipRect.Point1.X - x1 ) + aMaskPos.X;
      int    my1 = ( aClipRect.Point1.Y - y1 ) + aMaskPos.Y;
      int    mx2 = aMask->FrameSize.X - ( aClipRect.Point2.X - x1 ) - aMaskPos.X;
      int    my2 = aMask->FrameSize.Y - ( aClipRect.Point2.Y - y1 ) - aMaskPos.Y;
      XColor c   = { 255, 255, 255, (XUInt8)aOpacity };

      /* Any area above the mask to copy? */
      if ( my1 < 0 )
      {
        int cy2 = aClipRect.Point2.Y;
        aClipRect.Point2.Y = MIN( cy2, aClipRect.Point1.Y - my1 );
        EwCopyBitmap( aDst, aSrc, aDstFrameNo, 0, aClipRect, aDstRect, aSrcPos,
                      c, c, c, c, aBlend );
        aClipRect.Point1.Y = aClipRect.Point2.Y;
        aClipRect.Point2.Y = cy2;
      }

      /* Any area below the mask to copy? */
      if ( my2 < 0 )
      {
        int cy1 = aClipRect.Point1.Y;
        aClipRect.Point1.Y = MAX( cy1, aClipRect.Point2.Y + my2 );

        EwCopyBitmap( aDst, aSrc, aDstFrameNo, 0, aClipRect, aDstRect, aSrcPos,
                      c, c, c, c, aBlend );
        aClipRect.Point2.Y = aClipRect.Point1.Y;
        aClipRect.Point1.Y = cy1;
      }

      /* Any area on the left of the mask to copy? */
      if ( mx1 < 0 )
      {
        int cx2 = aClipRect.Point2.X;
        aClipRect.Point2.X = MIN( cx2, aClipRect.Point1.X - mx1 );
        EwCopyBitmap( aDst, aSrc, aDstFrameNo, 0, aClipRect, aDstRect, aSrcPos,
                      c, c, c, c, aBlend );
        aClipRect.Point1.X = aClipRect.Point2.X;
        aClipRect.Point2.X = cx2;
      }

      /* Any area on the right of the mask to copy? */
      if ( mx2 < 0 )
      {
        int cx1 = aClipRect.Point1.X;
        aClipRect.Point1.X = MAX( cx1, aClipRect.Point2.X + mx2 );

        EwCopyBitmap( aDst, aSrc, aDstFrameNo, 0, aClipRect, aDstRect, aSrcPos,
                      c, c, c, c, aBlend );
        aClipRect.Point2.X = aClipRect.Point1.X;
        aClipRect.Point1.X = cx1;
      }
    }

    /* The support for blur operations is restricted for target systems using
       RGB565 or RGB888 or RGBA8888 frame buffer. In case of other color formats
       the supported color space is too small for the fine gradients resulting
       from the blur effect. The blur is very ugly. */
    if (( aBlurRadius > 0 ) &&
        ( EwPixelDriverVariant != EW_DRIVER_VARIANT_RGBA8888        ) &&
        ( EwPixelDriverVariant != EW_DRIVER_VARIANT_RGB565          ) &&
        ( EwPixelDriverVariant != EW_DRIVER_VARIANT_RGB888          ) &&
        ( EwPixelDriverVariant != EW_DRIVER_VARIANT_RGB565_RGBA8888 ) &&
        ( EwPixelDriverVariant != EW_DRIVER_VARIANT_RGB888_RGBA8888 ))
      {
        EwError( 431 );
        return;
      }

    /* Position of the source surface in coordinates of the destination surface */
    sx1 = x1 - aSrcPos.X;
    sy1 = y1 - aSrcPos.Y;
    sx2 = x1 + aSrc->FrameSize.X - aSrcPos.X;
    sy2 = y1 + aSrc->FrameSize.Y - aSrcPos.Y;

    /* Limit the drawing area to the mask bitmap, if any. Note, the edges of the
       mask may appear blurred. Thus, enhance the area by the blur radius. */
    if ( aMask && !aMaskInverted )
    {
      int margin = aMaskBeforeBlur? aBlurRadius : 0;
      x2 = MIN( x2, x1 + aMask->FrameSize.X - aMaskPos.X + margin );
      y2 = MIN( y2, y1 + aMask->FrameSize.Y - aMaskPos.Y + margin );
      x1 = MAX( x1, x1 - aMaskPos.X - margin );
      y1 = MAX( y1, y1 - aMaskPos.Y - margin );
    }

    /* Take in account the source frame boundary. Note, the edges of the source
       may appear blurred. Thus, enhance the area by the blur radius. */
    x1 = MAX( x1, sx1 - aBlurRadius );
    y1 = MAX( y1, sy1 - aBlurRadius );
    x2 = MIN( x2, sx2 + aBlurRadius );
    y2 = MIN( y2, sy2 + aBlurRadius );

    /* Limit the area to the destination frame boundary and to the clipping
       area */
    x1 = MAX3( aClipRect.Point1.X, x1, 0 );
    y1 = MAX3( aClipRect.Point1.Y, y1, 0 );
    x2 = MIN3( aClipRect.Point2.X, x2, aDst->FrameSize.X );
    y2 = MIN3( aClipRect.Point2.Y, y2, aDst->FrameSize.Y );

    /* Nothing to do? */
    if (( x2 <= x1 ) || ( y2 <= y1 ))
      return;

    /* Mark the surfaces as involved in a drawing operation */
    src->Surface->Owned++; if ( mask ) mask->Surface->Owned++;
    src->Surface->Used++;  if ( mask ) mask->Surface->Used++;

    /* Start the preparation of a new drawing operation */
    if (( issue = EwInitIssue( dst->Surface )) == 0 )
    {
      src->Surface->Owned--; if ( mask ) mask->Surface->Owned--;
      src->Surface->Used--;  if ( mask ) mask->Surface->Used--;
      EwErrorPD( 413, aDst, 0 );
      return;
    }

    /* Get a storage area for the drawings parameter */
    data = EwAllocTaskData( issue, sizeof( *data ));
    data->DstX1            = (short)( aDstRect.Point1.X + dst->Origin.X );
    data->DstY1            = (short)( aDstRect.Point1.Y + dst->Origin.Y );
    data->DstX2            = (short)( aDstRect.Point2.X + dst->Origin.X );
    data->DstY2            = (short)( aDstRect.Point2.Y + dst->Origin.Y );
    data->SrcX1            = (short)src->Origin.X;
    data->SrcY1            = (short)src->Origin.Y;
    data->SrcX2            = (short)( src->Origin.X + aSrc->FrameSize.X );
    data->SrcY2            = (short)( src->Origin.Y + aSrc->FrameSize.Y );
    data->SrcPosX          = (short)( aSrcPos.X + src->Origin.X );
    data->SrcPosY          = (short)( aSrcPos.Y + src->Origin.Y );
    data->MaskX1           = (short)( mask? mask->Origin.X : 0 );
    data->MaskY1           = (short)( mask? mask->Origin.Y : 0 );
    data->MaskX2           = (short)( mask? mask->Origin.X +
                                            aMask->FrameSize.X : 0 );
    data->MaskY2           = (short)( mask? mask->Origin.Y +
                                            aMask->FrameSize.Y : 0 );
    data->MaskPosX         = (short)( mask? aMaskPos.X + mask->Origin.X : 0 );
    data->MaskPosY         = (short)( mask? aMaskPos.Y + mask->Origin.Y : 0 );
    data->SrcSurface       = src->Surface;
    data->MaskSurface      = mask? mask->Surface : 0;
    data->MaskInverted     = aMaskInverted;
    data->MaskBeforeBlur   = aMaskBeforeBlur;
    data->BlurRadius       = (short)aBlurRadius;
    data->BlurClampToEdges = aBlurClampToEdges;
    data->Mode             = (short)aMode;
    data->Intensity        = aIntensity;
    data->Color            = PACK_COLOR( aColor, aDst );
    data->Opacity          = (short)aOpacity;

    /* Enqueue the drawing operation by the issue */
    task = EwAllocTask( issue, 0 );
    task->Token     = EW_TASKID_FILTER_SURFACE;
    task->Data      = data;
    task->X1        = (short)( x1 + dst->Origin.X );
    task->Y1        = (short)( y1 + dst->Origin.Y );
    task->X2        = (short)( x2 + dst->Origin.X );
    task->Y2        = (short)( y2 + dst->Origin.Y );
    task->Flags     = (short)EW_TASK_ENTIRE_AREA;

    /* Complete the task initialisation */
    task->Flags |= (short)( aBlend? EW_TASK_ALPHABLEND : 0 );

    /* The surfaces are waiting for drawing operation (they remain 'used'). */
    src->Surface->Owned--; if ( mask ) mask->Surface->Owned--;

    /* Close the preparation. This may flush the issue */
    EwDoneIssue( dst->Surface );
  #else
    XBitmapFrame* src = MapBitmapFrame( aSrc, 0 );

    /* The source is not used. Nevertheless ensure that the eventually pending
       drawing operations are trigerred. Otherwise the operations may block. */
    if ( src )
      EwFlushTasks( src->Surface );

    EW_UNUSED_ARG( aDst );
    EW_UNUSED_ARG( aMask );
    EW_UNUSED_ARG( aDstFrameNo );
    EW_UNUSED_ARG( aClipRect );
    EW_UNUSED_ARG( aDstRect );
    EW_UNUSED_ARG( aSrcPos );
    EW_UNUSED_ARG( aMaskPos );
    EW_UNUSED_ARG( aMaskInverted );
    EW_UNUSED_ARG( aMaskBeforeBlur );
    EW_UNUSED_ARG( aBlurRadius );
    EW_UNUSED_ARG( aBlurClampToEdges );
    EW_UNUSED_ARG( aMode );
    EW_UNUSED_ARG( aIntensity );
    EW_UNUSED_ARG( aColor );
    EW_UNUSED_ARG( aOpacity );
    EW_UNUSED_ARG( aBlend );
    EwError( 415 );
  #endif
}


EW_INSTRUMENT_VOID_FUNC( EwFilterBitmap, ( XBitmap* aDst, XBitmap* aSrc,
  XBitmap* aMask, XInt32 aDstFrameNo, XRect aClipRect, XRect aDstRect,
  XPoint aSrcPos, XPoint aMaskPos, XBool aMaskInverted, XBool aMaskBeforeBlur,
  XInt32 aBlurRadius, XBool aBlurClampToEdges, XInt32 aMode, XFloat aIntensity,
  XColor aColor, XInt32 aOpacity, XBool aBlend ), ( aDst, aSrc, aMask,
  aDstFrameNo, aClipRect, aDstRect, aSrcPos, aMaskPos, aMaskInverted,
  aMaskBeforeBlur, aBlurRadius, aBlurClampToEdges, aMode, aIntensity, aColor,
  aOpacity, aBlend ))


/*******************************************************************************
* FUNCTION:
*   EwDrawLine
*
* DESCRIPTION:
*   The function EwDrawLine() draws a line between the coordinates aDstPos1 and
*   aDstPos2 within the destination bitmap aDst. The line will be drawn with a
*   color gradient specified by the both color values aColor1 and aColor2.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst        - Destination bitmap.
*   aDstFrameNo - Frame within the destination bitmap affected by the drawing
*     operation.
*   aClipRect   - Area to limit the drawing operation (Relative to the top-left
*     corner of the destination bitmap frame).
*   aDstPos1,
*   aDstPos2    - Start and end coordinates of the line (Relative to the top-
*     left corner of the destination bitmap frame).
*   aColor1,
*   aColor2     - Color values corresponding to the start and end of the line.
*   aBlend      - If != 0, the drawn pixel will be alpha-blended with the pixel
*     in the background.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwDrawLine_( XBitmap* aDst, XInt32 aDstFrameNo, XRect aClipRect,
  XPoint aDstPos1, XPoint aDstPos2, XColor aColor1, XColor aColor2,
  XBool aBlend )
{
  XBitmapFrame*   dst    = MapBitmapFrame( aDst, aDstFrameNo );
  XDrawLine*      data;
  XIssue*         issue;
  XTask*          task;
  int             x1, y1, x2, y2;
  int             dstX2  = aDstPos2.X;
  int             dstY2  = aDstPos2.Y;
  unsigned int    color1 = PACK_COLOR( aColor1, aDst );
  unsigned int    color2 = PACK_COLOR( aColor2, aDst );

  /* Only screen/native surfaces are allowed as the destination */
  if ( !dst || (( dst->Surface->Format != EW_PIXEL_FORMAT_SCREEN ) &&
                ( dst->Surface->Format != EW_PIXEL_FORMAT_NATIVE )))
  {
    EwErrorPD( 159, aDst, aDstFrameNo );
    return;
  }

  /* The support for Native surface as destination is disabled. */
  #ifdef EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION
    if ( dst->Surface->Format == EW_PIXEL_FORMAT_NATIVE )
    {
      EwErrorPD( 357, aDst, aDstFrameNo );
      return;
    }
  #endif

  /* Bitmaps loaded from resources can't be modified by drawing operations */
  if ( dst->Surface->Tag1 || dst->Surface->Tag2 )
  {
    EwErrorPD( 347, aDst, aDstFrameNo );
    return;
  }

  /* The support for color gradients is disabled. */
  #ifdef EW_DONT_USE_GRADIENTS
    if ( IS_GRADIENT2( color1, color2 ))
    {
      EwError( 377 );
      return;
    }
  #endif

  /* The end position refers to the non visible pixel - get the position of the
     last visible pixel */
  if ( ABS( aDstPos2.X - aDstPos1.X ) > ABS( aDstPos2.Y - aDstPos1.Y ))
  {
    if ( dstX2 > aDstPos1.X ) dstX2--;
    if ( dstX2 < aDstPos1.X ) dstX2++;
  }
  else
  {
    if ( dstY2 > aDstPos1.Y ) dstY2--;
    if ( dstY2 < aDstPos1.Y ) dstY2++;
  }

  /* Limit the fill area to the frame boundary and to the clipping area */
  x1 = MAX( aClipRect.Point1.X, 0 );
  y1 = MAX( aClipRect.Point1.Y, 0 );
  x2 = MIN( aClipRect.Point2.X, aDst->FrameSize.X );
  y2 = MIN( aClipRect.Point2.Y, aDst->FrameSize.Y );

  /* Limit the clipping area to the drawn line */
  x1 = MAX( x1, MIN( aDstPos1.X, dstX2 ));
  y1 = MAX( y1, MIN( aDstPos1.Y, dstY2 ));
  x2 = MIN( x2, MAX( aDstPos1.X, dstX2 ) + 1 );
  y2 = MIN( y2, MAX( aDstPos1.Y, dstY2 ) + 1 );

  /* Nothing to do? */
  if (( x2 <= x1 ) || ( y2 <= y1 ) ||
      ( aBlend && IS_TRANSPARENT2( color1, color2 )))
    return;

  /* Full opaque fill operation doesn't need the alpha blending */
  if ( aBlend && IS_OPAQUE2( color1, color2 ))
    aBlend = 0;

  /* Start the preparation of a new drawing operation */
  if (( issue = EwInitIssue( dst->Surface )) == 0 )
  {
    EwErrorPD( 130, aDst, 0 );
    return;
  }

  /* Get a storage area for the drawings parameter */
  data = EwAllocTaskData( issue, sizeof( *data ));
  data->DstX1     = (short)( aDstPos1.X + dst->Origin.X );
  data->DstY1     = (short)( aDstPos1.Y + dst->Origin.Y );
  data->DstX2     = (short)( aDstPos2.X + dst->Origin.X );
  data->DstY2     = (short)( aDstPos2.Y + dst->Origin.Y );
  data->Colors[0] = color1;
  data->Colors[1] = color2;

  /* Enqueue the drawing operation by the issue */
  task = EwAllocTask( issue, 0 );
  task->Token     = EW_TASKID_DRAW_LINE;
  task->Data      = data;
  task->X1        = (short)( x1 + dst->Origin.X );
  task->Y1        = (short)( y1 + dst->Origin.Y );
  task->X2        = (short)( x2 + dst->Origin.X );
  task->Y2        = (short)( y2 + dst->Origin.Y );
  task->Flags     = (short)( aBlend? EW_TASK_ALPHABLEND : 0 );

  /* What to do with the 4 colors? */
  #ifndef EW_DONT_USE_GRADIENTS
    if ( IS_GRADIENT2( color1, color2 ))
      task->Flags |= EW_TASK_GRADIENT;
    else
  #endif
    task->Flags |= EW_TASK_SOLID;

  /* Close the preparation. This may flush the issue */
  EwDoneIssue( dst->Surface );
}


EW_INSTRUMENT_VOID_FUNC( EwDrawLine, ( XBitmap* aDst, XInt32 aDstFrameNo,
  XRect aClipRect, XPoint aDstPos1, XPoint aDstPos2, XColor aColor1,
  XColor aColor2, XBool aBlend ), ( aDst, aDstFrameNo, aClipRect, aDstPos1,
  aDstPos2, aColor1, aColor2, aBlend ))


/* This helper function has the job to complete the actual text drawing instruction
   and done the issue. */
static void CompleteDrawTextTask( XBitmapFrame* aDst, XIssue* aIssue,
  XDrawText* aData, int aX1, int aY1, int aX2, int aY2, int aVXS, int aVXE,
  XRect aDstRect, XPoint aSrcPos, XInt32 aOrientation, unsigned int aColorTL,
  unsigned int aColorTR, unsigned int aColorBR, unsigned int aColorBL, int aBlend )
{
  /* Enqueue the drawing operation by the issue */
  XTask* task = EwAllocTask( aIssue, 0 );

  /* Limit the clipping area to the first and last visible glyphs */
  if ( aOrientation == 90 )
  {
    aY2 = MIN( aY2, ( aDstRect.Point2.Y + aSrcPos.X ) - aVXS );
    aY1 = MAX( aY1, ( aDstRect.Point2.Y + aSrcPos.X ) - aVXE );
  }
  else if ( aOrientation == 180 )
  {
    aX2 = MIN( aX2, ( aDstRect.Point2.X + aSrcPos.X ) - aVXS );
    aX1 = MAX( aX1, ( aDstRect.Point2.X + aSrcPos.X ) - aVXE );
  }
  else if ( aOrientation == 270 )
  {
    aY1 = MAX( aY1, ( aDstRect.Point1.Y - aSrcPos.X ) + aVXS );
    aY2 = MIN( aY2, ( aDstRect.Point1.Y - aSrcPos.X ) + aVXE );
  }
  else
  {
    aX1 = MAX( aX1, ( aDstRect.Point1.X - aSrcPos.X ) + aVXS );
    aX2 = MIN( aX2, ( aDstRect.Point1.X - aSrcPos.X ) + aVXE );
  }

  task->Token = EW_TASKID_DRAW_TEXT;
  task->Data  = aData;
  task->X1    = (short)( aX1 + aDst->Origin.X );
  task->Y1    = (short)( aY1 + aDst->Origin.Y );
  task->X2    = (short)( aX2 + aDst->Origin.X );
  task->Y2    = (short)( aY2 + aDst->Origin.Y );
  task->Flags = (short)( aBlend? EW_TASK_ALPHABLEND : 0 );

  /* What to do with the 4 colors? */
  #ifndef EW_DONT_USE_GRADIENTS
    if ( IS_LINEAR_GRADIENT4( aColorTL, aColorTR, aColorBL, aColorBR ))
      task->Flags |= EW_TASK_LINEAR_GRADIENT;
    else if ( IS_GRADIENT4( aColorTL, aColorTR, aColorBL, aColorBR ))
      task->Flags |= EW_TASK_GRADIENT;
    else
  #endif
    task->Flags |= EW_TASK_SOLID;

  /* Close the preparation. This may flush the issue */
  EwDoneIssue( aDst->Surface );
}


/*******************************************************************************
* FUNCTION:
*   EwDrawText
*
* DESCRIPTION:
*   The function EwDrawText() prints a single text row within the destination
*   bitmap aDst. The font and the characters to draw are specified in aFont and
*   aString. The area, where the text will be drawn is defined by aDstRect and
*   by aSrcPos. The copied pixel are modulated by a color gradient specified by
*   the four color parameters aColorTL .. aColorBL.
*
*   The parameter aMinWidth controls optionally the minimum width of the text to
*   draw. If applied, the function extends white space characters in order to
*   stretch the text. By using this parameter justified text output is possible.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
*   Please note, the function expects the characters within the string to be
*   stored according to order how the characters are displayed from the left
*   to right. To display RTL text (e.g. Arabic), the characters have to be
*   reordered in advance.
*
* ARGUMENTS:
*   aDst         - Destination bitmap.
*   aFont        - Font to draw the glyphs.
*   aString      - Text to process.
*   aCount       - Maximum number of text characters to draw or -1 if the entire
*     text should be drawn.
*   aDstFrameNo  - Frame within the destination bitmap affected by the drawing
*     operation.
*   aClipRect    - Area to limit the drawing operation (Relative to the top-left
*     corner of the destination bitmap frame).
*   aDstRect     - Area to fill with the text glyphs (Relative to the top-left
*     corner of the destination bitmap frame).
*   aSrcPos      - Displacement for the text baseline position relative to the
*     corner of aDstRect, which by taking in account the specified aOrientation
*     parameter serves as the origin for the drawing operation.
*   aMinWidth    - Minimum width of the text to draw. If text width is less than
*     aMinWidth, white space characters will be stretched automatically.
*   aOrientation - Orientation how to rotate the text. This parameter can assume
*     the values 0, 90, 180 or 270. The specified aOrientation implies the corner
*     of aDstRect serving as the origin relative to which the text is drawn. For
*     example, if aOrientation is 270, the text is drawn relative to the bottom-
*     right corner of aDstRect.
*   aColorTL,
*   aColorTR,
*   aColorBR,
*   aColorBL     - Color values corresponding to the four corners of aDstRect.
*   aBlend       - If != 0, the drawn pixel will be alpha-blended with the pixel
*     in the background.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwDrawText_( XBitmap* aDst, XFont* aFont, XChar* aString, XInt32 aCount,
  XInt32 aDstFrameNo, XRect aClipRect, XRect aDstRect, XPoint aSrcPos,
  XInt32 aMinWidth, XInt32 aOrientation, XColor aColorTL, XColor aColorTR,
  XColor aColorBR, XColor aColorBL, XBool aBlend )
{
  XBitmapFrame*   dst         = MapBitmapFrame( aDst, aDstFrameNo );
  int             length      = WcsLen( aString );
  XIssue*         issue       = 0;
  XDrawText*      data        = 0;
  int             x1, y1, x2, y2;
  unsigned int    colorTL     = PACK_COLOR( aColorTL, aDst );
  unsigned int    colorTR     = PACK_COLOR( aColorTR, aDst );
  unsigned int    colorBL     = PACK_COLOR( aColorBL, aDst );
  unsigned int    colorBR     = PACK_COLOR( aColorBR, aDst );
  int             stretchFac  = 0;
  int             stretchAcc  = 0x8000; /* == 0.5 pixel in 16.16 format */
  unsigned int    prevGlyphId = 0;
  void*           context;
  int             vx          = 0;
  int             vx1, vx2;
  int             vxs         = 0;
  int             vxe         = 0;
  int             i;

  /* Should process all characters from the string till the zero-terminator? */
  if ( aCount < 0 )
    aCount = length;

  /* Estimate the max. number of characters to process. */
  aCount = MIN( aCount, length );

  /* Nothing to do */
  if ( !aCount )
    return;

  /* Only screen/native surfaces are allowed as the destination */
  if ( !dst || (( dst->Surface->Format != EW_PIXEL_FORMAT_SCREEN ) &&
                ( dst->Surface->Format != EW_PIXEL_FORMAT_NATIVE )))
  {
    EwErrorPD( 167, aDst, aDstFrameNo );
    return;
  }

  /* The support for Native surface as destination is disabled. */
  #ifdef EW_DONT_USE_NATIVE_SURFACES_AS_DESTINATION
    if ( dst->Surface->Format == EW_PIXEL_FORMAT_NATIVE )
    {
      EwErrorPD( 358, aDst, aDstFrameNo );
      return;
    }
  #endif

  /* Bitmaps loaded from resources can't be modified by drawing operations */
  if ( dst->Surface->Tag1 || dst->Surface->Tag2 )
  {
    EwErrorPD( 348, aDst, aDstFrameNo );
    return;
  }

  /* Is the font valid? */
  if ( !aFont )
  {
    EwErrorPD( 168, aFont, 0 );
    return;
  }

  /* Verify the passed orientation value */
  if (( aOrientation != 90 ) && ( aOrientation != 180 ) && ( aOrientation != 270 ))
    aOrientation = 0;

  /* Printing rotated text expects Warp functions. Report error code if the
     Graphics Engine has been configured without this functionality. */
  #ifdef EW_DONT_USE_WARP_FUNCTIONS
    if ( aOrientation )
    {
      EwError( 361 );
      return;
    }
  #endif

  /* The support for color gradients is disabled. */
  #ifdef EW_DONT_USE_GRADIENTS
    if ( IS_LINEAR_GRADIENT4( colorTL, colorTR, colorBL, colorBR ) ||
         IS_GRADIENT4( colorTL, colorTR, colorBL, colorBR ))
    {
      EwError( 377 );
      return;
    }
  #endif

  /* Limit the draw area to the frame boundary and to the clipping area */
  x1 = MAX3( aClipRect.Point1.X, aDstRect.Point1.X, 0 );
  y1 = MAX3( aClipRect.Point1.Y, aDstRect.Point1.Y, 0 );
  x2 = MIN3( aClipRect.Point2.X, aDstRect.Point2.X, aDst->FrameSize.X );
  y2 = MIN3( aClipRect.Point2.Y, aDstRect.Point2.Y, aDst->FrameSize.Y );

  /* Limit the clipping area */
  if ( aOrientation == 90 )
  {
    int srcPosX = aDstRect.Point1.X - aSrcPos.Y;
    int srcPosY = aDstRect.Point2.Y + aSrcPos.X - 1;
    int leading = MAX( aFont->Leading, 0 );

    x1  = MAX( x1, srcPosX - aFont->Ascent      - leading );
    x2  = MIN( x2, srcPosX + aFont->Descent + 1 + leading );
    vx1 = srcPosY - y2 + 1;
    vx2 = srcPosY - y1 + 1;
  }
  else if ( aOrientation == 180 )
  {
    int srcPosX = aDstRect.Point2.X + aSrcPos.X - 1;
    int srcPosY = aDstRect.Point2.Y + aSrcPos.Y - 1;
    int leading = MAX( aFont->Leading, 0 );

    y1  = MAX( y1, srcPosY - aFont->Descent    - leading );
    y2  = MIN( y2, srcPosY + aFont->Ascent + 1 + leading );
    vx1 = srcPosX - x2 + 1;
    vx2 = srcPosX - x1 + 1;
  }
  else if ( aOrientation == 270 )
  {
    int srcPosX = aDstRect.Point2.X + aSrcPos.Y - 1;
    int srcPosY = aDstRect.Point1.Y - aSrcPos.X;
    int leading = MAX( aFont->Leading, 0 );

    x1  = MAX( x1, srcPosX - aFont->Descent    - leading );
    x2  = MIN( x2, srcPosX + aFont->Ascent + 1 + leading );
    vx1 = y1 - srcPosY;
    vx2 = y2 - srcPosY;
  }
  else
  {
    int srcPosX = aDstRect.Point1.X - aSrcPos.X;
    int srcPosY = aDstRect.Point1.Y - aSrcPos.Y;
    int leading = MAX( aFont->Leading, 0 );

    y1  = MAX( y1, srcPosY - aFont->Ascent      - leading );
    y2  = MIN( y2, srcPosY + aFont->Descent + 1 + leading );
    vx1 = x1 - srcPosX;
    vx2 = x2 - srcPosX;
  }

  /* Nothing to do? */
  if (( x2 <= x1 ) || ( y2 <= y1 ) ||
      ( aBlend && IS_TRANSPARENT4( colorTL, colorTR, colorBL, colorBR )))
    return;

  /* Stretch the text? Calculate the remaining area to stretch the white
     spaces */
  if ( aMinWidth > 0 )
    aMinWidth -= EwGetTextAdvance( aFont, aString, aCount );

  /* Calculate the factor to stretch a single white space */
  if ( aMinWidth > 0 )
  {
    int noOfSpaces = 0;

    /* Count white spaces incl. the non-breakable space */
    for ( i = 0; i < aCount; i++ )
      if (( aString[i] == ' ' ) || ( aString[i] == 0xA0 ))
        noOfSpaces++;

    /* Factor to stretch a single white space glyph in 16.16 format */
    if ( noOfSpaces )
      stretchFac = ( aMinWidth << 16 ) / noOfSpaces;
  }

  /* Prepare an object to store the shaper status */
  context = EwFntInitShaper();

  /* Process all characters of the string - cluster by cluster */
  while ( aCount > 0 )
  {
    /* For the moment we limit the clusters to be composed of max. 8 glyphs. */
    unsigned int glyphIds[8];
    short        deltasOriginX[8];
    short        deltasOriginY[8];
    short        deltasAdvance[8];
    int          lineEnd;
    int          noOfGlyphIds = sizeof( glyphIds ) / sizeof( glyphIds[0]);
    int          noOfChars;

    /* Following codes represent zero-width signs, partially needed to control
       the text processing. These signs are never displayed. Skip over the
       character codes. */
    if (( *aString == 0x061C ) || ( *aString == 0xFEFF )  ||
       (( *aString >= 0x200B ) && ( *aString <= 0x200F )) ||
       (( *aString >= 0x202A ) && ( *aString <= 0x202E )) ||
       (( *aString >= 0x2066 ) && ( *aString <= 0x2069 )))
    {
      aCount--;
      aString++;
      continue;
    }

    /* Following codes represent signs which are also not visible, but they
       isolate the adjacent glyphs. Skip over the codes and suppress the
       kerning for the adjacent glyphs. */
    if ( *aString == '\n' )
    {
      aCount--;
      aString++;
      prevGlyphId = 0;
      continue;
    }

    /* Shape the next text cluster. */
    noOfChars = EwFntShapeCluster( aFont->Handle, aString, MIN( aCount, 8 ),
                                   0, glyphIds, deltasOriginX, deltasOriginY,
                                   deltasAdvance, &noOfGlyphIds, &lineEnd,
                                   context );

    /* No matching glyph for the given cluster. Use the '.notdef' glyph. */
    if ( !noOfChars )
    {
      glyphIds[0]  = 0;
      noOfGlyphIds = 1;
      noOfChars    = 1;

      /* Print corresponding error message */
      EwErrorSD( 180, EwFntGetResourceName( aFont->Handle ), *aString );
    }

    /* Now process estimated glyphs. */
    for ( i = 0; i < noOfGlyphIds; i++ )
    {
      XGlyph* glyph;
      int     kern;
      char*   slot;

      /* Get the glyph for the given glyph id. If necessary flush the next
         pending issue. */
      do
      {
        glyph = GetGlyph( aFont, glyphIds[i]);

        /* Was not able to get the glyph and there is already some text drawing
           instruction prepared? Complete it now, so the glyph cache is empty
           again. */
        if ( !glyph && issue )
        {
          CompleteDrawTextTask( dst, issue, data, x1, y1, x2, y2, vxs, vxe,
                                aDstRect, aSrcPos, aOrientation, colorTL,
                                colorTR, colorBR, colorBL, aBlend );
          issue = 0;
        }
      }
      while ( !glyph && EwFlushTasks( 0 ));

      /* Could not obtain the glyph. Possibly the cache is too small. The glyph
         will not appear. */
      if ( !glyph )
      {
        EwErrorSD( 181, EwFntGetResourceName( aFont->Handle ), glyphIds[i]);
        prevGlyphId = 0;
        continue;
      }

      /* Estimate the kerning between the current and the preceding glyphs. */
      kern = EwFntGetKerning( aFont->Handle, prevGlyphId, glyphIds[i]);

      /* Stretching white spaces? (incl. the non-breakable space). The value to
         stretch is simply stored as kerning to the next following glyph. */
      if ( stretchFac && (( *aString == ' ' ) || ( *aString == 0xA0 )))
      {
        stretchAcc += stretchFac;
        kern       += stretchAcc >> 16;
        stretchAcc &= 0xFFFF;
      }

      /* Does the glyph lie on the left of the clipping area? Then skip over the
         glyph. */
      if ((( vx + kern + deltasOriginX[i] + glyph->OriginX + glyph->Width ) <= vx1 ) &&
            !issue )
      {
        vx         += kern + deltasAdvance[i] + glyph->Advance;
        prevGlyphId = glyphIds[i];
        EwFreeGlyph( glyph );
        continue;
      }

      /* Does the glyph lie on the right of the clipping area? Then there are
         no more glyphs to process. Stop. */
      if (( vx + kern + deltasOriginX[i] + glyph->OriginX ) >= vx2 )
      {
        EwFreeGlyph( glyph );
        aCount = 0;
        break;
      }

      /* The glyph should be drawn. Ensure there is a drawing instruction
         available where the glyph will be stored. */
      if ( !issue )
      {
        if (( issue = EwInitIssue( dst->Surface )) == 0 )
        {
          EwErrorPD( 131, aDst, 0 );
          EwFreeGlyph( glyph );
          EwFntDoneShaper( context );
          return;
        }

        /* Get a storage area for the drawings parameter */
        data = EwAllocTaskData( issue, sizeof( *data ));
        data->DstX1       = (short)( aDstRect.Point1.X + dst->Origin.X );
        data->DstY1       = (short)( aDstRect.Point1.Y + dst->Origin.Y );
        data->DstX2       = (short)( aDstRect.Point2.X + dst->Origin.X );
        data->DstY2       = (short)( aDstRect.Point2.Y + dst->Origin.Y );
        data->OfsX        = (short)( -aSrcPos.X );
        data->OfsY        = (short)( -aSrcPos.Y );
        data->Colors[0]   = colorTL;
        data->Colors[1]   = colorTR;
        data->Colors[2]   = colorBR;
        data->Colors[3]   = colorBL;
        data->Glyphs      = 0;
        data->Orientation = (short)aOrientation;

        /* For the moment the area enclosing the involved glyphs is empty. */
        vxs =  0x7FFFFFFF;
        vxe = -0x7FFFFFFF;
      }

      /* Ensure the glyph contains pixel data */
      if ( !MapGlyph( aFont, glyphIds[i], glyph ))
      {
        CompleteDrawTextTask( dst, issue, data, x1, y1, x2, y2, vxs, vxe,
                              aDstRect, aSrcPos, aOrientation, colorTL,
                              colorTR, colorBR, colorBL, aBlend );

        /* Repeat again with the actually processed glyph. */
        EwFreeGlyph( glyph );
        i--;
        issue = 0;

        /* Ensure all pending drawing operations are finished */
        EwFlushTasks( 0 );
        continue;
      }

      /* Append new entry at the end of the parameter block. Note, every entry
         stores the reference to affected glyph and its position */
      slot = EwAllocTaskData( issue, ( sizeof( int ) * 2 ) + sizeof( XGlyph** ));

      /* No memory to store the glyph. Complete the actual drawing instruction
         and try again. */
      if ( !slot )
      {
        CompleteDrawTextTask( dst, issue, data, x1, y1, x2, y2, vxs, vxe,
                              aDstRect, aSrcPos, aOrientation, colorTL,
                              colorTR, colorBR, colorBL, aBlend );

        /* Repeat again with the actually processed glyph. */
        EwFreeGlyph( glyph );
        i--;
        issue = 0;
        continue;
      }

      /* Store the glyph and the kerning in the instruction */
      ((int*)slot)[0]              = vx + kern + deltasOriginX[i] + glyph->OriginX;
      ((int*)slot)[1]              = deltasOriginY[i] + glyph->OriginY;
      *(XGlyph**)((int*)slot + 2 ) = glyph;
      data->Glyphs++;

      /* Track the area enclosing the glyphs for the actual drawing operation */
      vxs = MIN( vxs, vx + kern + deltasOriginX[i] + glyph->OriginX );
      vxe = MAX( vxe, vx + kern + deltasOriginX[i] + glyph->OriginX + glyph->Width );

      /* Calculate the position where to draw the next following glyph */
      vx += kern + deltasAdvance[i] + glyph->Advance;

      /* The code of the glyph to determine the kerning in the next iteration */
      prevGlyphId = glyphIds[i];
    }

    /* Skip over the processed characters */
    aCount  -= noOfChars;
    aString += noOfChars;
  }

  /* Release the shaper context. */
  EwFntDoneShaper( context );

  /* Complete the last drawing instruction */
  if ( issue )
    CompleteDrawTextTask( dst, issue, data, x1, y1, x2, y2, vxs, vxe,
                          aDstRect, aSrcPos, aOrientation, colorTL,
                          colorTR, colorBR, colorBL, aBlend );
}


EW_INSTRUMENT_VOID_FUNC( EwDrawText, ( XBitmap* aDst, XFont* aFont,
  XChar* aString, XInt32 aCount, XInt32 aDstFrameNo, XRect aClipRect,
  XRect aDstRect, XPoint aSrcPos, XInt32 aMinWidth, XInt32 aOrientation,
  XColor aColorTL, XColor aColorTR, XColor aColorBR, XColor aColorBL,
  XBool aBlend ),
  ( aDst, aFont, aString, aCount, aDstFrameNo, aClipRect, aDstRect, aSrcPos,
  aMinWidth, aOrientation, aColorTL, aColorTR, aColorBR, aColorBL, aBlend ))


/*******************************************************************************
* FUNCTION:
*   EwGetTextExtent
*
* DESCRIPTION:
*   The function EwGetTextExtent() calculates an area required to draw the text
*   aString with the font aFont. The size of the resulting rectangle determines
*   the space where character glyphs will be drawn. The origin of the rectangle
*   specifies the distance between a print position and the first drawn glyph.
*
*   The origin of the calculated area can be passed as aSrcPos to the function
*   EwDrawText(), if seamless text output relative to the top-left corner of
*   the destination area is desired.
*
*   Please note, the function expects the characters within the string to be
*   stored according to order how the characters are displayed from the left
*   to right. To display RTL text (e.g. Arabic), the characters have to be
*   reordered in advance.
*
* ARGUMENTS:
*   aFont   - Font to use for the text extent calculation.
*   aString - Text to process.
*   aCount  - Maximum number of text characters to evaluate or -1 if the entire
*     text should be evaluated.
*
* RETURN VALUE:
*   Returns the rectangular area needed to display the string.
*
*******************************************************************************/
XRect EwGetTextExtent_( XFont* aFont, XChar* aString, XInt32 aCount )
{
  XRect         extent      = {{ 0, 0 }, { 0, 0 }};
  int           x           = 0;
  unsigned int  prevGlyphId = 0;
  int           length      = WcsLen( aString );
  void*         context;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Should process all characters from the string till the zero-terminator? */
  if ( aCount < 0 )
    aCount = length;

  /* Estimate the max. number of characters to process. */
  aCount = MIN( aCount, length );

  /* Nothing to do */
  if ( !aCount )
    return extent;

  /* No valid font specified */
  if ( !aFont )
  {
    EwErrorPD( 169, aFont, 0 );
    return extent;
  }

  /* Prepare an object to store the shaper status */
  context = EwFntInitShaper();

  /* Process all characters of the string - cluster by cluster */
  while ( aCount )
  {
    /* For the moment we limit the clusters to be composed of max. 8 glyphs. */
    unsigned int glyphIds[8];
    short        deltasOriginX[8];
    short        deltasOriginY[8];
    short        deltasAdvance[8];
    int          lineEnd;
    int          noOfGlyphIds = sizeof( glyphIds ) / sizeof( glyphIds[0]);
    int          noOfChars;
    int          i;

    /* Following codes represent zero-width signs, partially needed to control
       the text processing. These signs are never displayed. Skip over the
       character codes. */
    if (( *aString == 0x061C ) || ( *aString == 0xFEFF )  ||
       (( *aString >= 0x200B ) && ( *aString <= 0x200F )) ||
       (( *aString >= 0x202A ) && ( *aString <= 0x202E )) ||
       (( *aString >= 0x2066 ) && ( *aString <= 0x2069 )))
    {
      aCount--;
      aString++;
      continue;
    }

    /* Following codes represent signs which are also not visible, but they
       isolate the adjacent glyphs. Skip over the codes and suppress the
       kerning for the adjacent glyphs. */
    if ( *aString == '\n' )
    {
      aCount--;
      aString++;
      prevGlyphId = 0;
      continue;
    }

    /* Shape the next text cluster. */
    noOfChars = EwFntShapeCluster( aFont->Handle, aString, MIN( aCount, 8 ),
                                   0, glyphIds, deltasOriginX, deltasOriginY,
                                   deltasAdvance, &noOfGlyphIds, &lineEnd,
                                   context );

    /* No matching glyph for the given cluster. Use the '.notdef' glyph. */
    if ( !noOfChars )
    {
      glyphIds[0]  = 0;
      noOfGlyphIds = 1;
      noOfChars    = 1;
    }

    /* Now calculate with the metrics of the estimated glyphs. */
    for ( i = 0; i < noOfGlyphIds; i++ )
    {
      XGlyph* glyph;

      /* Get the glyph for the given glyph id. If necessary flush the
         next pending issue */
      do
        glyph = GetGlyph( aFont, glyphIds[i]);
      while ( !glyph && EwFlushTasks( 0 ));

      /* Could not obtain the glyph. Possibly the cache is too small. The glyph
         will not appear. */
      if ( !glyph )
      {
        prevGlyphId = 0;
        continue;
      }

      /* Start with the first glyph */
      if ( !x )
        extent.Point1.X = glyph->OriginX + deltasOriginX[i];

      /* Following glyphs only extends the area */
      extent.Point1.Y = MIN( extent.Point1.Y, glyph->OriginY + deltasOriginY[i]);
      extent.Point2.Y = MAX( extent.Point2.Y, glyph->OriginY + deltasOriginY[i] +
                                              glyph->Height );

      /* First take in account the eventual kerning between the preceding and the
         actual glyph */
      x += EwFntGetKerning( aFont->Handle, prevGlyphId, glyphIds[i]);

      /* Ignore glyphs without content and advance */
      extent.Point2.X = MAX( extent.Point2.X, x + glyph->OriginX + 
                                              deltasOriginX[i] + glyph->Width );

      /* Print position for the next glyph */
      x += glyph->Advance + deltasAdvance[i];

      /* Also take in account white-space glyphs at the end of the text row.
         They haven't any width but they do occupy space */
      if ( !( glyph->OriginX + deltasOriginX[i] + glyph->Width ) && glyph->Advance )
        extent.Point2.X = MAX( x, extent.Point2.X );

      /* At fin free the glyph */
      EwFreeGlyph( glyph );

      /* The code of the glyph to determine the kerning in the next iteration */
      prevGlyphId = glyphIds[i];
    }

    /* Skip over the processed characters */
    aCount  -= noOfChars;
    aString += noOfChars;
  }

  /* Release the shaper context. */
  EwFntDoneShaper( context );

  return extent;
}


EW_INSTRUMENT_FUNC( EwGetTextExtent, XRect, ( XFont* aFont, XChar* aString,
  XInt32 aCount ), ( aFont, aString, aCount ))


/*******************************************************************************
* FUNCTION:
*   EwGetTextAdvance
*
* DESCRIPTION:
*   The function EwGetTextAdvance() calculates the advance of the entire text
*   aString with the font aFont. The value is calculated by the sum of advance
*   values of glyphs to display the text.
*
*   Please note, the function expects the characters within the string to be
*   stored according to order how the characters are displayed from the left
*   to right. To display RTL text (e.g. Arabic), the characters have to be
*   reordered in advance.
*
* ARGUMENTS:
*   aFont   - Font to use for the text calculation.
*   aString - Text to process.
*   aCount  - Maximum number of text characters to evaluate or -1 if the entire
*     text should be evaluated.
*
* RETURN VALUE:
*   Returns the advance width of the text to display.
*
*******************************************************************************/
XInt32 EwGetTextAdvance_( XFont* aFont, XChar* aString, XInt32 aCount )
{
  int           x           = 0;
  unsigned int  prevGlyphId = 0;
  int           length      = WcsLen( aString );
  void*         context;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Should process all characters from the string till the zero-terminator? */
  if ( aCount < 0 )
    aCount = length;

  /* Estimate the max. number of characters to process. */
  aCount = MIN( aCount, length );

  /* Nothing to do */
  if ( !aCount )
    return 0;

  /* No valid font specified */
  if ( !aFont )
  {
    EwErrorPD( 170, aFont, 0 );
    return 0;
  }

  /* Prepare an object to store the shaper status */
  context = EwFntInitShaper();

  /* Process all characters of the string - cluster by cluster */
  while ( aCount )
  {
    /* For the moment we limit the clusters to be composed of max. 8 glyphs. */
    unsigned int glyphIds[8];
    short        deltasDummy[8];
    short        deltasAdvance[8];
    int          lineEnd;
    int          noOfGlyphIds = sizeof( glyphIds ) / sizeof( glyphIds[0]);
    int          noOfChars;
    int          i;

    /* Following codes represent zero-width signs, partially needed to control
       the text processing. These signs are never displayed. Skip over the
       character codes. */
    if (( *aString == 0x061C ) || ( *aString == 0xFEFF )  ||
       (( *aString >= 0x200B ) && ( *aString <= 0x200F )) ||
       (( *aString >= 0x202A ) && ( *aString <= 0x202E )) ||
       (( *aString >= 0x2066 ) && ( *aString <= 0x2069 )))
    {
      aCount--;
      aString++;
      continue;
    }

    /* Following codes represent signs which are also not visible, but they
       isolate the adjacent glyphs. Skip over the codes and suppress the
       kerning for the adjacent glyphs. */
    if ( *aString == '\n' )
    {
      aCount--;
      aString++;
      prevGlyphId = 0;
      continue;
    }

    /* Shape the next text cluster. */
    noOfChars = EwFntShapeCluster( aFont->Handle, aString, MIN( aCount, 8 ),
                                   0, glyphIds, deltasDummy, deltasDummy,
                                   deltasAdvance, &noOfGlyphIds, &lineEnd,
                                   context );

    /* No matching glyph for the given cluster. Use the '.notdef' glyph. */
    if ( !noOfChars )
    {
      glyphIds[0]  = 0;
      noOfGlyphIds = 1;
      noOfChars    = 1;
    }

    /* Now calculate with the metrics of the estimated glyphs. */
    for ( i = 0; i < noOfGlyphIds; i++ )
    {
      XGlyph* glyph;

      /* Get the glyph for the given glyph id. If necessary flush the
         next pending issue */
      do
        glyph = GetGlyph( aFont, glyphIds[i]);
      while ( !glyph && EwFlushTasks( 0 ));

      /* Could not obtain the glyph. Possibly the cache is too small. The glyph
         will not appear. */
      if ( !glyph )
      {
        prevGlyphId = 0;
        continue;
      }

      /* Calculate the advance of the glyph. Also take in account kerning to the
         preceding glyph */
      x += EwFntGetKerning( aFont->Handle, prevGlyphId, glyphIds[i]) +
                            glyph->Advance + deltasAdvance[i];

      /* At fin free the glyph */
      EwFreeGlyph( glyph );

      /* The code of the glyph to determine the kerning in the next iteration */
      prevGlyphId = glyphIds[i];
    }

    /* Skip over the processed characters */
    aCount  -= noOfChars;
    aString += noOfChars;
  }

  /* Release the shaper context. */
  EwFntDoneShaper( context );

  return x;
}


EW_INSTRUMENT_FUNC( EwGetTextAdvance, XInt32, ( XFont* aFont, XChar* aString,
  XInt32 aCount ), ( aFont, aString, aCount ))


/*******************************************************************************
* FUNCTION:
*   EwGetTextColumnAtPosition
*
* DESCRIPTION:
*   The function EwGetTextColumnAtPosition() determines the character number in
*   the given text aString, which corresponds to a glyph enclosing the position
*   aX when aString would be printed by using the font aFont. The algorithm to
*   calculate the position is equal to the used by EwDrawText() to raster the
*   text.
*
*   The parameter aMinWidth controls optionally the minimum width of the text.
*   If applied, the function assumes all white space characters to be extended
*   in order to stretch the text. By using this parameter justified text output
*   is possible.
*
*   Please note, in complex scripts several characters may be considered as
*   belonging to so-called cluster. In this case, the function returns the
*   number of the character starting the cluster enclosing the position aX.
*
*   Please note, the function expects the characters within the string to be
*   stored according to order how the characters are displayed from the left
*   to right. To display RTL text (e.g. Arabic), the characters have to be
*   reordered in advance.
*
* ARGUMENTS:
*   aFont       - Font to be used for the calculation.
*   aString     - Text to process.
*   aCount      - Maximum number of text characters to draw or -1 if the entire
*     text should be drawn.
*   aX          - Position in pixel relative to the left edge of the text row
*     as if it would be rasterized by EwDrawText().
*   aMinWidth   - Minimum width of the text to consider. If text width is less
*     than aMinWidth, the function will calculate with white space characters
*     being stretched accordingly.
*
* RETURN VALUE:
*   Returns the number of the character in the string corresponding to a glyph
*   enclosing the position aX. The first character has the number 0, the second
*   1, and so far. If aX lies on the left of the first character the function
*   returns -1; If aX lies on the right of the last character, the function
*   returns the number of the character following it, which corresponds to the
*   number of characters in aString.
*
*******************************************************************************/
XInt32 EwGetTextColumnAtPosition_( XFont* aFont, XChar* aString, XInt32 aCount,
  XInt32 aX, XInt32 aMinWidth )
{
  int           stretchFac  = 0;
  int           stretchAcc  = 0x8000; /* == 0.5 pixel in 16.16 format */
  int           column      = 0;
  unsigned int  prevGlyphId = 0;
  int           length      = WcsLen( aString );
  void*         context;
  int           i;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Should process all characters from the string till the zero-terminator? */
  if ( aCount < 0 )
    aCount = length;

  /* Estimate the max. number of characters to process. */
  aCount = MIN( aCount, length );

  /* Nothing to do */
  if ( !aCount )
    return 0;

  if ( !aFont )
  {
    EwErrorPD( 171, aFont, 0 );
    return 0;
  }

  /* Addressing a non existing character on the left of the text */
  if ( aX < 0 )
    return -1;

  /* Stretch the text? Calculate the remaining area to stretch the white
     spaces */
  if ( aMinWidth > 0 )
    aMinWidth -= EwGetTextAdvance( aFont, aString, aCount );

  /* Calculate the factor to stretch a single white space */
  if ( aMinWidth > 0 )
  {
    int noOfSpaces = 0;

    /* Count white spaces incl. the non-breakable space */
    for ( i = 0; i < aCount; i++ )
      if (( aString[i] == ' ' ) || ( aString[i] == 0xA0 ))
        noOfSpaces++;

    /* Factor to stretch a single white space glyph in 16.16 format */
    if ( noOfSpaces )
      stretchFac = ( aMinWidth << 16 ) / noOfSpaces;
  }

  /* Prepare an object to store the shaper status */
  context = EwFntInitShaper();

  /* Process all characters of the string - cluster by cluster */
  while ( aCount )
  {
    /* For the moment we limit the clusters to be composed of max. 8 glyphs. */
    unsigned int glyphIds[8];
    short        deltasDummy[8];
    short        deltasAdvance[8];
    int          lineEnd;
    int          noOfGlyphIds = sizeof( glyphIds ) / sizeof( glyphIds[0]);
    int          advance      = 0;
    int          noOfChars;

    /* Following codes represent zero-width signs, partially needed to control
       the text processing. These signs are never displayed. Skip over the
       character codes. */
    if (( *aString == 0x061C ) || ( *aString == 0xFEFF )  ||
       (( *aString >= 0x200B ) && ( *aString <= 0x200F )) ||
       (( *aString >= 0x202A ) && ( *aString <= 0x202E )) ||
       (( *aString >= 0x2066 ) && ( *aString <= 0x2069 )))
    {
      aCount--;
      aString++;
      continue;
    }

    /* Following codes represent signs which are also not visible, but they
       isolate the adjacent glyphs. Skip over the codes and suppress the
       kerning for the adjacent glyphs. */
    if ( *aString == '\n' )
    {
      aCount--;
      aString++;
      prevGlyphId = 0;
      continue;
    }

    /* Shape the next text cluster. */
    noOfChars = EwFntShapeCluster( aFont->Handle, aString, MIN( aCount, 8 ),
                                   0, glyphIds, deltasDummy, deltasDummy,
                                   deltasAdvance, &noOfGlyphIds, &lineEnd,
                                   context );

    /* No matching glyph for the given cluster. Use the '.notdef' glyph. */
    if ( !noOfChars )
    {
      glyphIds[0]  = 0;
      noOfGlyphIds = 1;
      noOfChars    = 1;
    }

    /* Now calculate with the metrics of the estimated glyphs. */
    for ( i = 0; i < noOfGlyphIds; i++ )
    {
      XGlyph* glyph;

      /* Get the glyph for the given glyph id. If necessary flush the
         next pending issue */
      do
        glyph = GetGlyph( aFont, glyphIds[i]);
      while ( !glyph && EwFlushTasks( 0 ));

      /* Could not obtain the glyph. Possibly the cache is too small. The glyph
         will not appear. */
      if ( !glyph )
      {
        prevGlyphId = 0;
        continue;
      }

      /* The area occupied by the glyph */
      advance += EwFntGetKerning( aFont->Handle, prevGlyphId, glyphIds[i]);
      advance += glyph->Advance + deltasAdvance[i];

      /* Now free the glyph */
      EwFreeGlyph( glyph );

      /* The code of the glyph to determine the kerning in the next iteration */
      prevGlyphId = glyphIds[i];
    }

    /* Stretching white spaces? (incl. the non-breakable space) */
    if ( stretchFac && (( *aString == ' ' ) || ( *aString == 0xA0 )))
    {
      stretchAcc += stretchFac;
      advance    += stretchAcc >> 16;
      stretchAcc &= 0xFFFF;
    }

    /* The specified position seems to lie right to the affected cluster or very close
       to the next cluster */
    if ( aX < (( advance / 2 ) + 1 ))
      break;

    /* Skip over the processed characters */
    aCount  -= noOfChars;
    aString += noOfChars;
    column  += noOfChars;
    aX      -= advance;
  }

  /* Release the shaper context. */
  EwFntDoneShaper( context );

  return column;
}


EW_INSTRUMENT_FUNC( EwGetTextColumnAtPosition, XInt32, ( XFont* aFont,
  XChar* aString, XInt32 aCount, XInt32 aX, XInt32 aMinWidth ), ( aFont,
  aString, aCount, aX, aMinWidth ))


/*******************************************************************************
* FUNCTION:
*   EwGetPositionAtTextColumn
*
* DESCRIPTION:
*   The function EwGetPositionAtTextColumn() determines the start position for
*   the glyph corresponding to the character aColumn within the string aString
*   when aString would be printed by using the font aFont. The algorithm to
*   calculate the position is equal to the used by EwDrawText() to raster the
*   text.
*
*   The parameter aMinWidth controls optionally the minimum width of the text.
*   If applied, the function assumes all white space characters to be extended
*   in order to stretch the text. By using this parameter justified text output
*   is possible.
*
*   Please note, in complex scripts several characters may be considered as
*   belonging to so-called cluster. In this case, the function returns the
*   starting position of the cluster containing the character aColumn.
*
*   Please note, the function expects the characters within the string to be
*   stored according to order how the characters are displayed from the left
*   to right. To display RTL text (e.g. Arabic), the characters have to be
*   reordered in advance.
*
* ARGUMENTS:
*   aFont       - Font to be used for the calculation.
*   aString     - Text to process.
*   aCount      - Maximum number of text characters to draw or -1 if the entire
*     text should be drawn.
*   aColumn     - Number of the interesting character. The first character has
*     the number 0, the second 1, and so far.
*   aMinWidth   - Minimum width of the text to consider. If text width is less
*     than aMinWidth, the function will calculate with white space characters
*     being stretched accordingly.
*
* RETURN VALUE:
*   Returns the position in pixel of the found glyph relative to the left edge
*   of the text row as if it would be rasterized by EwDrawText(). If aColumn
*   is < 0, the function returns -1; If aColumn addresses a character not
*   existing in the string, the function returns the total length of the string.
*
*******************************************************************************/
XInt32 EwGetPositionAtTextColumn_( XFont* aFont, XChar* aString, XInt32 aCount,
  XInt32 aColumn, XInt32 aMinWidth )
{
  int           stretchFac  = 0;
  int           stretchAcc  = 0x8000; /* == 0.5 pixel in 16.16 format */
  int           x           = 0;
  unsigned int  prevGlyphId = 0;
  int           length      = WcsLen( aString );
  void*         context;
  int           i;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Should process all characters from the string till the zero-terminator? */
  if ( aCount < 0 )
    aCount = length;

  /* Estimate the max. number of characters to process. */
  aCount = MIN( aCount, length );

  /* Nothing to do */
  if ( !aCount )
    return 0;

  if ( !aFont )
  {
    EwErrorPD( 172, aFont, 0 );
    return 0;
  }

  /* Addressing a non existing character on the left the text */
  if ( aColumn < 0 )
    return -1;

  /* Stretch the text? Calculate the remaining area to stretch the white
     spaces */
  if ( aMinWidth > 0 )
    aMinWidth -= EwGetTextAdvance( aFont, aString, aCount );

  /* Calculate the factor to stretch a single white space */
  if ( aMinWidth > 0 )
  {
    int noOfSpaces = 0;

    /* Count white spaces incl. the non-breakable space */
    for ( i = 0; i < aCount; i++ )
      if (( aString[i] == ' ' ) || ( aString[i] == 0xA0 ))
        noOfSpaces++;

    /* Factor to stretch a single white space glyph in 16.16 format */
    if ( noOfSpaces )
      stretchFac = ( aMinWidth << 16 ) / noOfSpaces;
  }

  /* Prepare an object to store the shaper status */
  context = EwFntInitShaper();

  /* Process all characters of the string - cluster by cluster */
  while ( aCount )
  {
    /* For the moment we limit the clusters to be composed of max. 8 glyphs. */
    unsigned int glyphIds[8];
    short        deltasDummy[8];
    short        deltasAdvance[8];
    int          lineEnd;
    int          noOfGlyphIds = sizeof( glyphIds ) / sizeof( glyphIds[0]);
    int          noOfChars;

    /* Following codes represent zero-width signs, partially needed to control
       the text processing. These signs are never displayed. Skip over the
       character codes. */
    if (( *aString == 0x061C ) || ( *aString == 0xFEFF )  ||
       (( *aString >= 0x200B ) && ( *aString <= 0x200F )) ||
       (( *aString >= 0x202A ) && ( *aString <= 0x202E )) ||
       (( *aString >= 0x2066 ) && ( *aString <= 0x2069 )))
    {
      aCount--;
      aString++;
      continue;
    }

    /* Following codes represent signs which are also not visible, but they
       isolate the adjacent glyphs. Skip over the codes and suppress the
       kerning for the adjacent glyphs. */
    if ( *aString == '\n' )
    {
      aCount--;
      aString++;
      prevGlyphId = 0;
      continue;
    }

    /* Shape the next text cluster. */
    noOfChars = EwFntShapeCluster( aFont->Handle, aString, MIN( aCount, 8 ),
                                   0, glyphIds, deltasDummy, deltasDummy,
                                   deltasAdvance, &noOfGlyphIds, &lineEnd,
                                   context );

    /* No matching glyph for the given cluster. Use the '.notdef' glyph. */
    if ( !noOfChars )
    {
      glyphIds[0]  = 0;
      noOfGlyphIds = 1;
      noOfChars    = 1;
    }

    /* The latest processed cluster contains the specified character. */
    if ( noOfChars > aColumn )
      break;

    /* Now calculate with the metrics of the estimated glyphs. */
    for ( i = 0; i < noOfGlyphIds; i++ )
    {
      XGlyph* glyph;

      /* Get the glyph for the given glyph id. If necessary flush the
         next pending issue */
      do
        glyph = GetGlyph( aFont, glyphIds[i]);
      while ( !glyph && EwFlushTasks( 0 ));

      /* Could not obtain the glyph. Possibly the cache is too small. The glyph
         will not appear. */
      if ( !glyph )
      {
        prevGlyphId = 0;
        continue;
      }

      /* The area occupied by the glyph */
      x += EwFntGetKerning( aFont->Handle, prevGlyphId, glyphIds[i]);
      x += glyph->Advance + deltasAdvance[i];

      /* Now free the glyph */
      EwFreeGlyph( glyph );

      /* The code of the glyph to determine the kerning in the next iteration */
      prevGlyphId = glyphIds[i];
    }

    /* Stretching white spaces? (incl. the non-breakable space) */
    if ( stretchFac && (( *aString == ' ' ) || ( *aString == 0xA0 )))
    {
      stretchAcc += stretchFac;
      x          += stretchAcc >> 16;
      stretchAcc &= 0xFFFF;
    }

    /* Skip over the processed characters */
    aCount  -= noOfChars;
    aString += noOfChars;
    aColumn -= noOfChars;
  }

  /* Release the shaper context. */
  EwFntDoneShaper( context );

  return x;
}


EW_INSTRUMENT_FUNC( EwGetPositionAtTextColumn, XInt32, ( XFont* aFont,
  XChar* aString, XInt32 aCount, XInt32 aColumn, XInt32 aMinWidth ), ( aFont,
  aString, aCount, aColumn, aMinWidth ))


/*******************************************************************************
* FUNCTION:
*   EwIsGlyphAvailable
*
* DESCRIPTION:
*   The function EwIsGlyphAvailable() verifies, whether the given glyph is
*   available in the font.
*
* ARGUMENTS:
*   aFont     - Font to verify the glyph existence.
*   aCharCode - Character code of the glyph.
*
* RETURN VALUE:
*   If the glyph is available in the font, the function returns != 0. Otherwise
*   0 (zero) is returned.
*
*******************************************************************************/
int EwIsGlyphAvailable_( XFont* aFont, XChar aCharCode )
{
  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Following codes represent zero-width signs, partially needed to control
     the text processing. These signs are never displayed. Assume, the glyphs
     are not available */
  if (( aCharCode == 0x061C ) || ( aCharCode == 0xFEFF )  ||
     (( aCharCode >= 0x200B ) && ( aCharCode <= 0x200F )) ||
     (( aCharCode >= 0x202A ) && ( aCharCode <= 0x202E )) ||
     (( aCharCode >= 0x2066 ) && ( aCharCode <= 0x2069 )) ||
      ( aCharCode == '\n'   ))
    return 0;

  /* Is the glyph in font? */
  return EwFntIsGlyphAvailable( aFont->Handle, aCharCode );
}


EW_INSTRUMENT_FUNC( EwIsGlyphAvailable, int, ( XFont* aFont, XChar aCharCode ),
  ( aFont, aCharCode ))


/*******************************************************************************
* FUNCTION:
*   EwGetGlyphId
*
* DESCRIPTION:
*   The function EwFntGetGlyphId() will be called by the Graphics Engine in
*   order to query the glyph id for a given character.
*
* ARGUMENTS:
*   aFont     - Font to get the glyph id.
*   aCharCode - Character code of the glyph.
*
* RETURN VALUE:
*   The function returns the id of the glyph corresponding to the given
*   character code. Otherwise 0 is returned. The value 0 corresponds in this
*   case to the '.notdef' glyph.
*
*******************************************************************************/
unsigned int EwGetGlyphId_( XFont* aFont, XChar aCharCode )
{
  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Following codes represent zero-width signs, partially needed to control
     the text processing. These signs are never displayed. Assume, the glyphs
     are not available */
  if (( aCharCode == 0x061C ) || ( aCharCode == 0xFEFF )  ||
     (( aCharCode >= 0x200B ) && ( aCharCode <= 0x200F )) ||
     (( aCharCode >= 0x202A ) && ( aCharCode <= 0x202E )) ||
     (( aCharCode >= 0x2066 ) && ( aCharCode <= 0x2069 )) ||
      ( aCharCode == '\n'   ))
    return 0;

  /* Is the glyph in font? */
  return EwFntGetGlyphId( aFont->Handle, aCharCode );
}


EW_INSTRUMENT_FUNC( EwGetGlyphId, unsigned int, ( XFont* aFont, XChar aCharCode ),
  ( aFont, aCharCode ))


/*******************************************************************************
* FUNCTION:
*   EwGetGlyphMetrics
*
* DESCRIPTION:
*   The function EwGetGlyphMetrics() determines the glyph metrics of the given
*   font glyph. The function is useful when special application dependent text
*   flow calculations are necessary. The caller can determine the size and the
*   position of each glyph within the text.
*
* ARGUMENTS:
*   aFont    - Font to get the glyph metrics.
*   aGlyphId - Id of the glyph.
*   aMetrics - Pointer to the structure where the metrics should be returned.
*
* RETURN VALUE:
*   If successful, the function returns != 0. When the desired glyph doesn't
*   exist in the font and there is no default glyph defined, zero is returned.
*
*******************************************************************************/
int EwGetGlyphMetrics_( XFont* aFont, unsigned int aGlyphId,
  XGlyphMetrics* aMetrics )
{
  XGlyph* glyph;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Nothing to do */
  if ( !aFont || !aMetrics )
  {
    EwError( 173 );
    return 0;
  }

  /* Seek for the glyph in the cache - if necessary load it from the font
     resource. If there is no more space in the cache, try to flush all
     pending drawing operations and try again */
  do
    glyph = GetGlyph( aFont, aGlyphId );
  while ( !glyph && EwFlushTasks( 0 ));

  /* Couldn't load the glyph */
  if ( !glyph )
    return 0;

  /* Store the glyph metrics */
  aMetrics->Advance  = glyph->Advance;
  aMetrics->Origin.X = glyph->OriginX;
  aMetrics->Origin.Y = glyph->OriginY;
  aMetrics->Size.X   = glyph->Width;
  aMetrics->Size.Y   = glyph->Height;

  /* Dont forget to unlock the glyph */
  EwFreeGlyph( glyph );

  return 1;
}


EW_INSTRUMENT_FUNC( EwGetGlyphMetrics, int, ( XFont* aFont, unsigned int aGlyphId,
  XGlyphMetrics* aMetrics ), ( aFont, aGlyphId, aMetrics ))


/*******************************************************************************
* FUNCTION:
*   EwGetKerning
*
* DESCRIPTION:
*   The function EwGetKerning() determines the kerning to apply between the
*   given glyphs.
*
* ARGUMENTS:
*   aFont     - Font to determine the kerning.
*   aGlyphId1 - Id of the first glyph.
*   aGlyphId2 - Id of the second glyph.
*
* RETURN VALUE:
*   The function returns the kerning value for the given pair of glyphs or 0
*   if the glyphs are not affected by kerning or at least one of the glyphs is
*   not existing in the font.
*
*******************************************************************************/
XInt32 EwGetKerning_( XFont* aFont, unsigned int aGlyphId1, unsigned int aGlyphId2 )
{
  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Nothing to do */
  if ( !aFont )
  {
    EwError( 175 );
    return 0;
  }

  if ( !aGlyphId1 || !aGlyphId2 )
    return 0;

  return EwFntGetKerning( aFont->Handle, aGlyphId1, aGlyphId2 );
}


EW_INSTRUMENT_FUNC( EwGetKerning, XInt32, ( XFont* aFont, unsigned int aGlyphId1,
  unsigned int aGlyphId2 ), ( aFont, aGlyphId1, aGlyphId2 ))


/*******************************************************************************
* FUNCTION:
*   EwLockGlyph
*
* DESCRIPTION:
*   The function EwLockGlyph() provides a direct access to the pixel memory of
*   the given glyph. The function returns a lock object containing pointers to
*   memory, where the caller can read the glyph pixel values. Additional pitch
*   values also returned in the lock object allow the caller to calculate the
*   desired pixel addresses.
*
*   When finished the access cycle, the function EwUnlockGlyph() should be used
*   in order to release the lock.
*
*   Note, glyphs are stored in the Alpha8 pixel format -> one byte per pixel.
*   The pixel value 0 determines transparent pixel. The 255 full opaque pixel.
*   Values 1 .. 254 determine the semitransparent pixel.
*
* ARGUMENTS:
*   aFont    - Font to lock the glyph pixel memory.
*   aGlyphId - Glyph Id of the glyph.
*
* RETURN VALUE:
*   If successful, the function returns a temporary glyph lock object. If the
*   intended glyph doesn't exist, 0 is returned.
*
*******************************************************************************/
XGlyphLock* EwLockGlyph_( XFont* aFont, unsigned int aGlyphId )
{
  XGlyph*      glyph;
  XSurfaceLock srfLock;
  XGlyphLock*  glyphLock;

  /* Nothing to do */
  if ( !aFont )
  {
    EwError( 174 );
    return 0;
  }

 /* Seek for the glyph in the cache - if necessary load it from the font
    resource. If there is no more space in the cache, try to flush all
    pending drawing operations and try again */
  do
    glyph = GetGlyph( aFont, aGlyphId );
  while ( !glyph && EwFlushTasks( 0 ));

  /* Couldn't load the glyph */
  if ( !glyph )
    return 0;

 /* Ensure the glyph pixel data is loaded in the glyph cache surface. */
  if ( !MapGlyph( aFont, aGlyphId, glyph ))
  {
    EwFreeGlyph( glyph );
    return 0;
  }

  /* Ok, we got the glyph itself - now, prepare the temporary lock object */
  do
    glyphLock = EwAlloc( sizeof( XGlyphLock ) + sizeof( XSurfaceLock ) +
                         sizeof( XGlyph* ));
  while ( !glyphLock && EwImmediateReclaimMemory( 32 ));

  /* Out of memory ... */
  if ( !glyphLock )
  {
    EwFreeGlyph( glyph );
    EwError( 32 );
    return 0;
  }

  /* Glyphs are stored within the glyph cache surface - try to lock the glyph
     within this surface */
  if ( EwLockGlyphCache( glyph, EW_LOCK_PIXEL_READ | EW_LOCK_DONT_WAIT, &srfLock ))
  {
    /* The lock refers memory area inside the glyph cache surface. No temporary
       memory is used. */
    glyphLock->Size   = 0;

    /* Store the internal lock information in the hidden part of the structure
       for the later unlock */
    *(XSurfaceLock*)( glyphLock + 1 ) = srfLock;
  }

  /* In case of target systems without any direct read access to surfaces (e.g.
     OpenGL), create a copy of the glyph within the CPU memory - a kind of shadow
     cache */
  else
  {
    unsigned char* pixel;

    do
      pixel = EwAlloc(( glyph->Width * glyph->Height ) + 1 );
    while ( !pixel && EwImmediateReclaimMemory( 33 ));

    /* Could reserve memory for the shadow copy of the glyph pixel data? */
    if ( !pixel )
    {
      EwFreeGlyph( glyph );
      EwFree( glyphLock );
      EwError( 33 );
      return 0;
    }

    /* In this case a temporary memory area is needed to store there the copy of the
       pixel data. Remember this information in the lock data structure. */
    glyphLock->Size  = glyph->Width * glyph->Height + 1;

    /* Store the pointers to the shadow cache */
    srfLock.Memory.Pixel1  = pixel;
    srfLock.Memory.Pitch1X = 1;
    srfLock.Memory.Pitch1Y = glyph->Width;

    /* Raster the glyph pixel data into the shadow cache memory */
    if ( !EwFntLoadGlyph( glyph->Font, glyph->GlyphId, &srfLock.Memory ))
      EwErrorSD( 183, EwFntGetResourceName( aFont->Handle ), aGlyphId );

    /* Track the RAM usage */
    EwResourcesMemory += glyphLock->Size;
  }

  /* Let the glpyh lock refer the memory containing the pixel data */
  glyphLock->Pixel  = srfLock.Memory.Pixel1;
  glyphLock->PitchX = srfLock.Memory.Pitch1X;
  glyphLock->PitchY = srfLock.Memory.Pitch1Y;

  /* Store the internal lock information in the hidden part of the structure */
  *(XGlyph**)((XSurfaceLock*)( glyphLock + 1 ) + 1 ) = glyph;

  /* Track the RAM usage */
  EwResourcesMemory += sizeof( XGlyphLock ) + sizeof( XSurfaceLock ) +
                       sizeof( XGlyph* );

  /* Also track the max. memory pressure */
  if ( EwResourcesMemory > EwResourcesMemoryPeak )
    EwResourcesMemoryPeak = EwResourcesMemory;

  if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
    EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

  return glyphLock;
}


EW_INSTRUMENT_FUNC( EwLockGlyph, XGlyphLock*, ( XFont* aFont, unsigned int aGlyphId ),
  ( aFont, aGlyphId ))


/*******************************************************************************
* FUNCTION:
*   EwUnlockGlyph
*
* DESCRIPTION:
*   The function EwUnlockGlyph() provides a counterpart to EwLockGlyph(). When
*   called, the function releases the given lock.
*
*   After calling this function, the aLock structure will become invalid.
*
* ARGUMENTS:
*   aLock - Lock object returned by the previous EwLockGlyph() call.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwUnlockGlyph_( XGlyphLock* aLock )
{
  XSurfaceLock* srfLock = (XSurfaceLock*)( aLock + 1 );
  XGlyph**      glyph   = (XGlyph**)( srfLock + 1 );

  /* Invalid lock object or already released? */
  if ( !aLock || !*glyph )
    return;

  /* The glyph pixel is locked in the glyph cache surface. Release the lock. */
  if ( !aLock->Size )
    EwUnlockGlyphCache( *glyph, srfLock );

  /* ... it is stored in a temporary memory area. Free the memory */
  else
  {
    EwFree( aLock->Pixel );

    /* Track the RAM usage */
    EwResourcesMemory -= aLock->Size;
  }

  /* Release the glyph, mark the lock object as released and ... */
  EwFreeGlyph( *glyph );
  *glyph = 0;

  /* ... free the object memory */
  EwFree( aLock );

  /* Track the RAM usage */
  EwResourcesMemory -= sizeof( XGlyphLock ) + sizeof( XSurfaceLock ) +
                       sizeof( XGlyph* );
}


EW_INSTRUMENT_VOID_FUNC( EwUnlockGlyph, ( XGlyphLock* aLock ), ( aLock ))


/*******************************************************************************
* FUNCTION:
*   EwDrawBitmapFrame
*
* DESCRIPTION:
*   The function EwDrawBitmapFrame() draws a free scalable frame by composing it
*   from up to nine bitmap segments. These segments do correspond to the 4 frame
*   corners, 4 edges and to the frame interior areas. By filling these areas with
*   repeated copies of the bitmap segments, flexible scalable frame is drawn.
*
*   The segments come from the source bitmap aSrc, which for this purpose has to
*   be organized as 3 x 3 matrix of equal sized tiles --> the size of the source
*   area aSrcRect has to a multiple of 3.
*
*   The resulting size of the drawn frame is specified by aDstRect parameter.
*   The aDrawXXX parameters control which edges are drawn. Optionally the copied
*   pixel can be modulated by a color gradient specified by the four parameters
*   aColorTL .. aColorBL.
*
*   An additional clipping area aClipRect limits the operation. All pixel lying
*   outside this area will not be drawn. The last aBlend parameter controls the
*   mode how drawn pixel are combined with the pixel already existing in the
*   destination bitmap. If aBlend != 0, the drawn pixel are alpha-blended with
*   the background, otherwise the drawn pixel will overwrite the old content.
*
* ARGUMENTS:
*   aDst        - Destination bitmap.
*   aSrc        - Source bitmap.
*   aDstFrameNo - Frame within the destination bitmap affected by the drawing
*     operation.
*   aSrcFrameNo - Source bitmap frame affected by the operation.
*   aClipRect   - Area to limit the drawing operation (Relative to the top-left
*     corner of the destination bitmap frame).
*   aDstRect    - Area to fill with the segments (Relative to the top-left
*     corner of the destination bitmap frame).
*   aSrcRect    - Area of the source bitmap to use as source for the drawing
*     operation. This area is assumed as composed of 3x3 equal sized tiles.
*     The area lies relative to the top-left corner of the source bitmap frame.
*   aDrawLeftEdge,
*   aDrawTopEdge,
*   aDrawRightEdge,
*   aDrawBottomEdge,
*   aDrawInterior - Flags to control, whether the corresponding area of the
*     frame is drawn or not. Not drawn edges are filled by the interior area.
*   aColorTL,
*   aColorTR,
*   aColorBR,
*   aColorBL    - Color values corresponding to the four corners of aDstRect.
*   aBlend      - If != 0, the drawn pixel will be alpha-blended with the pixel
*     in the background.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwDrawBitmapFrame_( XBitmap* aDst, XBitmap* aSrc, XInt32 aDstFrameNo,
  XInt32 aSrcFrameNo, XRect aClipRect, XRect aDstRect, XRect aSrcRect,
  XBool aDrawLeftEdge, XBool aDrawTopEdge, XBool aDrawRightEdge,
  XBool aDrawBottomEdge, XBool aDrawInterior, XColor aColorTL, XColor aColorTR,
  XColor aColorBR, XColor aColorBL, XBool aBlend )
{
  XPoint        ofs      = { 0, 0 };
  int           dstW     = aDstRect.Point2.X - aDstRect.Point1.X;
  int           dstH     = aDstRect.Point2.Y - aDstRect.Point1.Y;
  int           bordW    = ( aSrcRect.Point2.X - aSrcRect.Point1.X ) / 3;
  int           bordH    = ( aSrcRect.Point2.Y - aSrcRect.Point1.Y ) / 3;
  int           interW   = aSrcRect.Point2.X - aSrcRect.Point1.X - 2 * bordW;
  int           interH   = aSrcRect.Point2.Y - aSrcRect.Point1.Y - 2 * bordH;
  int           ofsX     = 0;
  int           ofsY     = 0;
  XColor        colorITL = aColorTL;
  XColor        colorITR = aColorTR;
  XColor        colorIBL = aColorBL;
  XColor        colorIBR = aColorBR;
  XColor        colorTTL = aColorTL;
  XColor        colorTTR = aColorTR;
  XColor        colorBBL = aColorBL;
  XColor        colorBBR = aColorBR;
  XColor        colorLTL = aColorTL;
  XColor        colorRTR = aColorTR;
  XColor        colorLBL = aColorBL;
  XColor        colorRBR = aColorBR;
  unsigned int  colorTL  = PACK_COLOR( aColorTL, aDst );
  unsigned int  colorTR  = PACK_COLOR( aColorTR, aDst );
  unsigned int  colorBL  = PACK_COLOR( aColorBL, aDst );
  unsigned int  colorBR  = PACK_COLOR( aColorBR, aDst );

  /* Nothing to draw */
  if (( dstW <= 0 ) || ( dstH <= 0 ) || ( interW <= 0 ) || ( interH <= 0 ))
    return;

  /* Special case of the frame having exact the same size as the source area. In such case
     the operation corresponds to a simple copy of the source area to the destination area. */
  if ( aDrawLeftEdge && aDrawRightEdge && aDrawTopEdge && aDrawBottomEdge && aDrawInterior &&
     ( dstW == ( aSrcRect.Point2.X - aSrcRect.Point1.X )) &&
     ( dstH == ( aSrcRect.Point2.Y - aSrcRect.Point1.Y )))
  {
    EwTileBitmap( aDst, aSrc, aDstFrameNo, aSrcFrameNo, aClipRect, aDstRect, aSrcRect,
                  ofs, aColorTL, aColorTR, aColorBR, aColorBL, aBlend );
    return;
  }

  /* Draw the frame by using a gradient? Then interpolate the colors for the
     interior area. Take in account the special cases of ommited edges. In
     this case the interpolation changes! */
  if ( IS_GRADIENT4( colorTL, colorTR, colorBR, colorBL ))
  {
    if ( aDrawLeftEdge )
    {
      colorTTL = InterpolateColor( aColorTL, aColorTR, bordW, dstW );
      colorBBL = InterpolateColor( aColorBL, aColorBR, bordW, dstW );
    }

    if ( aDrawRightEdge )
    {
      colorTTR = InterpolateColor( aColorTR, aColorTL, bordW, dstW );
      colorBBR = InterpolateColor( aColorBR, aColorBL, bordW, dstW );
    }

    if ( aDrawTopEdge )
    {
      colorLTL = InterpolateColor( aColorTL, aColorBL, bordH, dstH );
      colorRTR = InterpolateColor( aColorTR, aColorBR, bordH, dstH );
    }

    if ( aDrawBottomEdge )
    {
      colorLBL = InterpolateColor( aColorBL, aColorTL, bordH, dstH );
      colorRBR = InterpolateColor( aColorBR, aColorTR, bordH, dstH );
    }

    if ( !aDrawLeftEdge  && !aDrawTopEdge    ) colorITL = aColorTL;
    if (  aDrawLeftEdge  && !aDrawTopEdge    ) colorITL = colorTTL;
    if ( !aDrawLeftEdge  &&  aDrawTopEdge    ) colorITL = colorLTL;
    if ( !aDrawRightEdge && !aDrawTopEdge    ) colorITR = aColorTR;
    if (  aDrawRightEdge && !aDrawTopEdge    ) colorITR = colorTTR;
    if ( !aDrawRightEdge &&  aDrawTopEdge    ) colorITR = colorRTR;
    if ( !aDrawLeftEdge  && !aDrawBottomEdge ) colorIBL = aColorBL;
    if (  aDrawLeftEdge  && !aDrawBottomEdge ) colorIBL = colorBBL;
    if ( !aDrawLeftEdge  &&  aDrawBottomEdge ) colorIBL = colorLBL;
    if ( !aDrawRightEdge && !aDrawBottomEdge ) colorIBR = aColorBR;
    if (  aDrawRightEdge && !aDrawBottomEdge ) colorIBR = colorBBR;
    if ( !aDrawRightEdge &&  aDrawBottomEdge ) colorIBR = colorRBR;

    if ( aDrawLeftEdge && aDrawTopEdge )
      colorITL = InterpolateColor( colorTTL, colorBBL, bordH, dstH );

    if ( aDrawLeftEdge && aDrawBottomEdge )
      colorIBL = InterpolateColor( colorBBL, colorTTL, bordH, dstH );

    if ( aDrawRightEdge && aDrawTopEdge )
      colorITR = InterpolateColor( colorTTR, colorBBR, bordH, dstH );

    if ( aDrawRightEdge && aDrawBottomEdge )
      colorIBR = InterpolateColor( colorBBR, colorTTR, bordH, dstH );
  }

  /* If the top or left edges are hidden, the stretchable contents should
     align to the right/bottom edges */
  if ( aDrawRightEdge  && !aDrawLeftEdge ) ofsX = bordW - dstW;
  if ( aDrawBottomEdge && !aDrawTopEdge  ) ofsY = bordH - dstH;

  /* Top-left segment of the source bitmap */
  aSrcRect.Point2.X = aSrcRect.Point1.X + bordW;
  aSrcRect.Point2.Y = aSrcRect.Point1.Y + bordH;
  aDstRect.Point2.X = aDstRect.Point1.X + bordW;
  aDstRect.Point2.Y = aDstRect.Point1.Y + bordH;

  /* Start with the top-left corner */
  if ( aDrawLeftEdge && aDrawTopEdge )
    EwTileBitmap( aDst, aSrc, aDstFrameNo, aSrcFrameNo, aClipRect, aDstRect,
      aSrcRect, ofs, aColorTL, colorTTL, colorITL, colorLTL, aBlend );

  aDstRect.Point1.X += dstW - bordW;
  aDstRect.Point2.X += dstW - bordW;
  aSrcRect.Point1.X += bordW + interW;
  aSrcRect.Point2.X += bordW + interW;

  /* Draw the top-right corner */
  if ( aDrawRightEdge && aDrawTopEdge )
    EwTileBitmap( aDst, aSrc, aDstFrameNo, aSrcFrameNo, aClipRect, aDstRect,
      aSrcRect, ofs, colorTTR, aColorTR, colorRTR, colorITR, aBlend );

  aDstRect.Point1.Y += dstH - bordH;
  aDstRect.Point2.Y += dstH - bordH;
  aSrcRect.Point1.Y += bordH + interH;
  aSrcRect.Point2.Y += bordH + interH;

  /* Draw the bottom-right corner */
  if ( aDrawRightEdge && aDrawBottomEdge )
    EwTileBitmap( aDst, aSrc, aDstFrameNo, aSrcFrameNo, aClipRect, aDstRect,
      aSrcRect, ofs, colorIBR, colorRBR, aColorBR, colorBBR, aBlend );

  aDstRect.Point1.X -= dstW - bordW;
  aDstRect.Point2.X -= dstW - bordW;
  aSrcRect.Point1.X -= bordW + interW;
  aSrcRect.Point2.X -= bordW + interW;

  /* Draw the bottom-left corner */
  if ( aDrawLeftEdge && aDrawBottomEdge )
    EwTileBitmap( aDst, aSrc, aDstFrameNo, aSrcFrameNo, aClipRect, aDstRect,
      aSrcRect, ofs, colorLBL, colorIBL, colorBBL, aColorBL, aBlend );

  aDstRect.Point1.Y -= dstH - bordH;
  aSrcRect.Point1.Y -= interH;
  aSrcRect.Point2.Y -= bordH;
  ofs.Y              = ofsY;

  if ( aDrawTopEdge    ) aDstRect.Point1.Y += bordH;
  if ( aDrawBottomEdge ) aDstRect.Point2.Y -= bordH;

  /* Draw the left edge? */
  if ( aDrawLeftEdge )
    EwTileBitmap( aDst, aSrc, aDstFrameNo, aSrcFrameNo, aClipRect,
      aDstRect, aSrcRect, ofs, colorLTL, colorITL, colorIBL, colorLBL,
      aBlend );

  aDstRect.Point1.X += dstW - bordW;
  aDstRect.Point2.X += dstW - bordW;
  aSrcRect.Point1.X += bordW + interW;
  aSrcRect.Point2.X += bordW + interW;

  /* Draw the right edge? */
  if ( aDrawRightEdge )
    EwTileBitmap( aDst, aSrc, aDstFrameNo, aSrcFrameNo, aClipRect,
      aDstRect, aSrcRect, ofs, colorITR, colorRTR, colorRBR, colorIBR,
      aBlend );

  if ( aDrawTopEdge ) aDstRect.Point1.Y -= bordH;

  aDstRect.Point2.Y  = aDstRect.Point1.Y + bordH;
  aDstRect.Point1.X -= dstW - bordW;
  aSrcRect.Point1.X -= interW;
  aSrcRect.Point2.X -= bordW;
  aSrcRect.Point1.Y -= bordH;
  aSrcRect.Point2.Y -= interH;
  ofs.X              = ofsX;
  ofs.Y              = 0;

  if ( aDrawLeftEdge  ) aDstRect.Point1.X += bordW;
  if ( aDrawRightEdge ) aDstRect.Point2.X -= bordW;

  /* Draw the top edge? */
  if ( aDrawTopEdge )
    EwTileBitmap( aDst, aSrc, aDstFrameNo, aSrcFrameNo, aClipRect,
      aDstRect, aSrcRect, ofs, colorTTL, colorTTR, colorITR, colorITL,
      aBlend );

  aDstRect.Point1.Y += dstH - bordH;
  aDstRect.Point2.Y += dstH - bordH;
  aSrcRect.Point1.Y += bordH + interH;
  aSrcRect.Point2.Y += bordH + interH;

  /* Draw the bottom edge? */
  if ( aDrawBottomEdge )
    EwTileBitmap( aDst, aSrc, aDstFrameNo, aSrcFrameNo, aClipRect,
      aDstRect, aSrcRect, ofs, colorIBL, colorIBR, colorBBR, colorBBL,
      aBlend );

  if ( aDrawLeftEdge  ) aDstRect.Point1.X -= bordW;

  aDstRect.Point2.X  = aDstRect.Point1.X + dstW;
  aDstRect.Point1.Y -= dstH - bordH;
  aSrcRect.Point1.Y -= interH;
  aSrcRect.Point2.Y -= bordH;
  ofs.Y              = ofsY;

  /* Coordinates of the interior area. Not drawn edges are filled with the
     interior area. */
  if ( aDrawLeftEdge   ) aDstRect.Point1.X += bordW;
  if ( aDrawTopEdge    ) aDstRect.Point1.Y += bordH;
  if ( aDrawRightEdge  ) aDstRect.Point2.X -= bordW;
  if ( aDrawBottomEdge ) aDstRect.Point2.Y -= bordH;

  /* Fill the interior area? */
  if ( aDrawInterior )
    EwTileBitmap( aDst, aSrc, aDstFrameNo, aSrcFrameNo, aClipRect,
      aDstRect, aSrcRect, ofs, colorITL, colorITR, colorIBR, colorIBL,
      aBlend );
}


EW_INSTRUMENT_VOID_FUNC( EwDrawBitmapFrame, ( XBitmap* aDst, XBitmap* aSrc,
  XInt32 aDstFrameNo, XInt32 aSrcFrameNo, XRect aClipRect, XRect aDstRect,
  XRect aSrcRect, XBool aDrawLeftEdge, XBool aDrawTopEdge, XBool aDrawRightEdge,
  XBool aDrawBottomEdge, XBool aDrawInterior, XColor aColorTL, XColor aColorTR,
  XColor aColorBR, XColor aColorBL, XBool aBlend ),
  ( aDst, aSrc, aDstFrameNo, aSrcFrameNo, aClipRect, aDstRect, aSrcRect,
  aDrawLeftEdge, aDrawTopEdge, aDrawRightEdge, aDrawBottomEdge, aDrawInterior,
  aColorTL, aColorTR, aColorBR, aColorBL, aBlend ))


/*******************************************************************************
* FUNCTION:
*   EwIndexToColor
*
* DESCRIPTION:
*   The function EwIndexToColor() returns the color entry from the global CLUT
*   (palette).
*
*   This functionality is available on Index8, palette based target systems
*   only.
*
* ARGUMENTS:
*   aIndex - Index of the desired color entry within the global CLUT/palette.
*
* RETURN VALUE:
*   The color value or a transparent color if there is no global CLUT available
*   or the entry index is invalid.
*
*******************************************************************************/
XColor EwIndexToColor_( XInt32 aIndex )
{
  static const XColor zero = { 0, 0, 0, 0 };

  #ifdef EW_ENABLE_COLOR_TABLE
    if (( aIndex >= 0 ) && ( aIndex <= 255 ))
    {
      unsigned int tmp = EwGlobalClut[ aIndex ];
      XColor       color;

      color.Red   = (unsigned char)( tmp >> 0  );
      color.Green = (unsigned char)( tmp >> 8  );
      color.Blue  = (unsigned char)( tmp >> 16 );
      color.Alpha = (unsigned char)( tmp >> 24 );

      return color;
    }
    else
      return zero;
  #else

    EW_UNUSED_ARG( aIndex );
    return zero;
  #endif
}


EW_INSTRUMENT_FUNC( EwIndexToColor, XColor, ( XInt32 aIndex ), ( aIndex ))


/*******************************************************************************
* FUNCTION:
*   EwColorToIndex
*
* DESCRIPTION:
*   The function EwColorToIndex() determines an entry within the global CLUT/
*   palette, which corresponds to the given color (nearest color matching).
*
*   This functionality is available on Index8, palette based target systems
*   only.
*
* ARGUMENTS:
*   aColor - Color to be found in the global CLUT/palette.
*
* RETURN VALUE:
*   The determined global CLUT/palette entry in range 0 .. 255. If there is no
*   global CLUT/palette functionality available, the returned value is 0.
*
*******************************************************************************/
XUInt8 EwColorToIndex_( XColor aColor )
{
  #ifdef EW_ENABLE_COLOR_TABLE
    unsigned int index = (( aColor.Red   & 0xF0 ) << 4 ) |
                         (( aColor.Green & 0xF0 ) >> 4 ) |
                         (( aColor.Blue  & 0xF0 ) << 0 ) |
                         (( aColor.Alpha & 0xC0 ) << 6 );

    return EwColorIndexTable[ index ];
  #else
    EW_UNUSED_ARG( aColor );
    return 0;
  #endif
}


EW_INSTRUMENT_FUNC( EwColorToIndex, XUInt8, ( XColor aColor ), ( aColor ))


/*******************************************************************************
* FUNCTION:
*   EwAllocUserColor
*
* DESCRIPTION:
*   The function EwAllocUserColor() tries to store the given user defined color
*   within an empty area in the global CLUT/palette. User defined colors exist
*   for external applications (native applications) only. In this manner the
*   external application can manage its own/private set of color values.
*
*   This functionality is available on Index8, palette based target systems
*   only.
*
* ARGUMENTS:
*   aColor - Color to be stored in the global CLUT/palette.
*
* RETURN VALUE:
*   The global CLUT/palette entry, where the color could be stored. If there
*   are no entries available for new colors, 0 is returned.
*
*******************************************************************************/
XUInt8 EwAllocUserColor_( XColor aColor )
{
  #ifdef EW_ENABLE_COLOR_TABLE
    char* cur = EwColorAllocTable + EwGlobalClutCount;
    char* end = EwColorAllocTable + 256;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Search for empty color entry */
    while (( cur < end ) && *cur )
      cur++;

    /* None free entry found ... */
    if ( cur == end )
    {
      EwError( 176 );
      return 0;
    }

    /* Store the color and mark the entry as occupied ... */
    EwGlobalClut[ cur - EwColorAllocTable ] = EwPackColor( aColor.Red,
                aColor.Green, aColor.Blue, aColor.Alpha, EW_PIXEL_FORMAT_NATIVE );
    *cur = 1;

    /* Load the color value into the global hardware CLUT */
    #ifdef EwGfxLoadClut
      #if defined __LP64__ || defined _LP64
        if ( !EwGfxLoadClut( EwGlobalClut + ( cur - EwColorAllocTable ),
                             cur - EwColorAllocTable, 1 ))
      #else
        if ( !EwGfxLoadClut((unsigned long*)EwGlobalClut +
                            ( cur - EwColorAllocTable ),
                              cur - EwColorAllocTable, 1 ))
      #endif
        EwError( 103 );
    #endif

    return (unsigned char)( cur - EwColorAllocTable );
  #else
    EW_UNUSED_ARG( aColor );
    return 0;
  #endif
}


EW_INSTRUMENT_FUNC( EwAllocUserColor, XUInt8, ( XColor aColor ), ( aColor ))


/*******************************************************************************
* FUNCTION:
*   EwFreeUserColor
*
* DESCRIPTION:
*   The function EwFreeUserColor() removes the user defined color entry from
*   the global CLUT/palette. After this the affected entry remains empty. User
*   defined colors exist for external applications (native applications) only.
*   In this manner the external application can manage its own/private set of
*   color values.
*
*   This functionality is available on Index8, palette based target systems
*   only.
*
* ARGUMENTS:
*   aIndex - Index of the user color entry within the global CLUT/palette.
*
* RETURN VALUE:
*   None.
*
*******************************************************************************/
void EwFreeUserColor_( XInt32 aIndex )
{
  #ifdef EW_ENABLE_COLOR_TABLE
    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    if (( aIndex >= EwGlobalClutCount ) && ( aIndex <= 255 ))
      EwColorAllocTable[ aIndex ] = 0;
    else
      EwErrorDD( 177, aIndex, 0 );
  #else
    EW_UNUSED_ARG( aIndex );
  #endif
}


EW_INSTRUMENT_VOID_FUNC( EwFreeUserColor, ( XInt32 aIndex ), ( aIndex ))


/*******************************************************************************
* FUNCTION:
*   EwSetUserColor
*
* DESCRIPTION:
*   The function EwSetUserColor() changes the color value of an user defined
*   color within the global CLUT/palette. User defined colors exist for external
*   applications (native applications) only. In this manner the application can
*   manage its own/private set of color values.
*
*   This functionality is available on Index8, palette based target systems
*   only.
*
* ARGUMENTS:
*   aIndex - Index of the user color entry within the global CLUT/palette.
*   aColor - New color to be replace the old color value.
*
* RETURN VALUE:
*   None.
*
*******************************************************************************/
void EwSetUserColor_( XInt32 aIndex, XColor aColor )
{
  #ifdef EW_ENABLE_COLOR_TABLE
    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    if (( aIndex >= EwGlobalClutCount ) && ( aIndex <= 255 ) &&
          EwColorAllocTable[ aIndex ])
    {
      EwGlobalClut[ aIndex ] = EwPackColor( aColor.Red, aColor.Green,
                            aColor.Blue, aColor.Alpha, EW_PIXEL_FORMAT_NATIVE );

      /* Load the color value into the global hardware CLUT */
      #ifdef EwGfxLoadClut
        #if defined __LP64__ || defined _LP64
          if ( !EwGfxLoadClut( EwGlobalClut + aIndex, aIndex, 1 ))
        #else
          if ( !EwGfxLoadClut((unsigned long*)EwGlobalClut + aIndex, aIndex, 1 ))
        #endif
            EwError( 104 );
      #endif
    }
    else
      EwErrorDD( 178, aIndex, 0 );
  #else
    EW_UNUSED_ARG( aIndex );
    EW_UNUSED_ARG( aColor );
  #endif
}


EW_INSTRUMENT_VOID_FUNC( EwSetUserColor, ( XInt32 aIndex, XColor aColor ),
  ( aIndex, aColor ))


/*******************************************************************************
* FUNCTION:
*   EwFindUserColor
*
* DESCRIPTION:
*   The function EwFindUserColor() searches the global CLUT/palette for an entry
*   containing exactly the given user defined color. If no corresponding entry
*   could be found, the function returns 0. In this case, the best fit color can
*   be found by using the function EwColorToIndex().
*
*   User defined colors exist for external applications (native applications)
*   only. In this manner the application can manage its own/private set of color
*   values.
*
*   This functionality is available on Index8, palette based target systems
*   only.
*
* ARGUMENTS:
*   aColor - Color to be found within the user defined color area of the global
*     CLUT/palette.
*
* RETURN VALUE:
*   The global CLUT/palette entry, where the desired color is stored. If no
*   corresponding entry could be found, the function returns 0.
*
*******************************************************************************/
XUInt8 EwFindUserColor_( XColor aColor )
{
  #ifdef EW_ENABLE_COLOR_TABLE
    unsigned int* clut  = EwGlobalClut      + EwGlobalClutCount;
    char*         cur   = EwColorAllocTable + EwGlobalClutCount;
    char*         end   = EwColorAllocTable + 256;
    unsigned int  color = EwPackColor( aColor.Red, aColor.Green, aColor.Blue,
                                       aColor.Alpha, EW_PIXEL_FORMAT_NATIVE );

    /* Search for empty color entry */
    while (( cur < end ) && ( !*cur || ( *clut != color )))
    {
      cur++;
      clut++;
    }

    /* None entry found ... */
    if ( cur == end )
      return 0;

    return (unsigned char)( cur - EwColorAllocTable );
  #else
    EW_UNUSED_ARG( aColor );
    return 0;
  #endif
}


EW_INSTRUMENT_FUNC( EwFindUserColor, XUInt8, ( XColor aColor ), ( aColor ))


/*******************************************************************************
* FUNCTION:
*   EwGetOverlayArea
*
* DESCRIPTION:
*  The function EwGetOverlayArea() is used internaly by the Mosaic framework
*  to obtain the additional area occupied by the overlay image. The Mosaic
*  framework uses the returned area to optimize the screen redrawing. Without
*  this information, the update process would result in an incomplete screen
*  showing only parts of the overlay.
*
*  Please note, this function can't supress the overlay from being shown.
*  It exists only for optimization purpose.
*
* ARGUMENTS:
*   aVisible - If != 0, the function returns the currently visible area of
*     the overlay. If the overlay is hidden, the function will return an
*     empty area.
*   aUpdate  - If != 0, the function returns the current update area of the
*     overlay. The update area results when overlay changes between the
*     visible and hidden state. If no state transition is recorded, an empty
*     area is returned.
*
* RETURN VALUE:
*   The currently visible area or the update area of the overlay. If no area
*   is available, the function returns an empty rectangle.
*
*******************************************************************************/
XRect EwGetOverlayArea( XBool aVisible, XBool aUpdate )
{
  const static XRect empty = {{ 0, 0 }, { 0, 0 }};

  /* Avoid warning due to unused arguments */
  EW_UNUSED_ARG( aVisible );
  EW_UNUSED_ARG( aUpdate );

  EW_EVAL_INC_6();

  return empty;
}


/* This function is invoked when the surface cache overflows for each surface
   which although being actually owned could be restored again. In the function
   the owner of the surface has to clear or references to the given surface as
   it were freed. In such case the function has to return != 0. If the owner
   don't want to discard the surface, the function has to return 0. aUrgency
   parameter can assume values between 0 .. 2 and determines the 'urgency'
   of the operation. */
int EwCanDiscardSurface( XSurface* aSurface, int aUrgency )
{
  XBitmap* bitmap = (XBitmap*)aSurface->Owner;
  int      i;

  /* In this mode all surfaces are loaded immediatelly and retained. Prevent
     the surface from being discarded. */
  if ( !EwLazyLoadBitmaps && !EwLazyLoadBitmapsIfAnimatedOnly )
    return 0;

  /* In this mode all surfaces are retained in memory */
  if ( !EwDiscardBitmaps && !EwDiscardBitmapsIfAnimatedOnly &&
       !EwDiscardBitmapsIfNotUsedInCurrentUpdate &&
       !EwDiscardBitmapsIfNotUsedInRecentUpdates )
    return 0;

  /* The system is configured to lazy load only surfaces if these do belong
     to a multi-frame/animated bitmaps. All other bitmaps are not affected. */
  if ( EwLazyLoadBitmapsIfAnimatedOnly && (( bitmap->NoOfVirtFrames < 2 ) ||
                                           ( bitmap->FrameDelay == 0 )))
    return 0;

  /* The system is configured to not discard surfaces if these do not belong
     to multi-frame/animated bitmaps. */
  if ( EwDiscardBitmapsIfAnimatedOnly && (( bitmap->NoOfVirtFrames < 2 ) ||
                                          ( bitmap->FrameDelay == 0 )))
    return 0;

  /* The system is configured to not discard surfaces if these have been used
     during actual screen update. */
  if ( EwDiscardBitmapsIfNotUsedInCurrentUpdate &&
     ( aSurface->Stamp == EwUpdateCycle ))
    return 0;

  /* The system is configured to not discard surfaces if these have been used
     during actual or preceding screen update. */
  if ( EwDiscardBitmapsIfNotUsedInRecentUpdates &&
     (( aSurface->Stamp == EwUpdateCycle ) ||
      ( aSurface->Stamp == ( EwUpdateCycle - 1 ))))
    return 0;

  /* Lowest urgency -> don't discard the surface unless the bitmap contains
     animated multiframe contents */
  if (( aUrgency == 0 ) && (( bitmap->NoOfVirtFrames < 2 ) ||
                            ( bitmap->FrameDelay == 0 )))
    return 0;

  /* Medium urgency -> don't discard the surface unless the bitmap contains
     multiframe contents */
  if (( aUrgency == 1 ) && ( bitmap->NoOfVirtFrames < 2 ))
    return 0;

  /* Search the list of frames and for each frame stored in the surface,
     deinitialize the frame */
  for ( i = 0; i < bitmap->NoOfFrames; i++ )
    if ( bitmap->Frames[i].Surface == aSurface )
      bitmap->Frames[i].Surface = 0;

  /* Search the list of surfaces associated to the bitmap and release the
     given surface */
  for ( i = 0; i < bitmap->NoOfSurfaces; i++ )
    if ( bitmap->Surfaces[i] == aSurface )
      bitmap->Surfaces[i] = 0;

  /* Count the discarded surfaces */
  EwNoOfDiscardedSurfaces++;
  EwDiscardedSurfacesMemory += aSurface->MemSize;

  return 1;
}


/* This helper function creates and initializes a new descriptor structure for
   a new bitmap with the given number of frames, the frame size, etc. */
static XBitmap* InitBitmap( XInt32 aFormat, XPoint aFrameSize, int aFrameDelay,
  int aNoOfFrames, int aNoOfVirtFrames, int aMaxNoOfFramesX, int aMaxNoOfFramesY,
  int aBorder, int aExtraBorder, int aFramesSurfaceBalance )
{
  XBitmap*        bitmap;
  XBitmapFrame*   frames;
  XSurface**      surfaces;
  unsigned short* mapping;
  int             maxNoOfFramesX;
  int             maxNoOfFramesY;
  int             maxNoOfFrames;
  int             noOfSurfaces;
  int             size;
  int             i;
  int             ob = aBorder? 1 : 0;
  int             ib = ( aExtraBorder? 2 : 1 ) * ob;

  /* A bitmap consists of at least one frame */
  if ( aNoOfFrames <= 0 )
    aNoOfFrames = 1;

  /* If the surfaces are created and loaded on demand - estimate the optimal
     balance between the number of frames within a surface and the capacity
     of the surface cache. The idea here is to have many small surfaces which
     can be discarded if the cache overflows. Too many surfaces can however
     become inefficient with the underlying target system. Therefore try to
     find balance between the both conditions. */
  if ( aFramesSurfaceBalance && ( aNoOfFrames > 1 ))
  {
    int a = EwMaxSurfaceCacheSize / ( 32 * aFrameSize.X * aFrameSize.Y );
    int b = ( 128 * 128 ) / ( aFrameSize.X * aFrameSize.Y );
    int c = (  32  * 32 ) / ( aFrameSize.X * aFrameSize.Y );

    a = MAX( a, c );
    b = MIN( a, b );
    a = ( a + b ) / 2;
    a = MAX( a, 1 );

    /* Not all frames will have space within a single surface. Determine how
       layout the frames */
    if ( a < aNoOfFrames )
    {
      if      (( aFrameSize.X > aFrameSize.Y ) && !aMaxNoOfFramesY )
        aMaxNoOfFramesY = a;
      else if (( aFrameSize.X < aFrameSize.Y ) && !aMaxNoOfFramesX )
        aMaxNoOfFramesX = a;
      else if ( !aMaxNoOfFramesX )
        aMaxNoOfFramesX = a;
      else if ( !aMaxNoOfFramesY )
        aMaxNoOfFramesY = a;

      if ( !aMaxNoOfFramesX ) aMaxNoOfFramesX = 1;
      if ( !aMaxNoOfFramesY ) aMaxNoOfFramesY = 1;
    }
  }

  /* Create a surface with the max. possible resolution? In this case ommit the borders
     around each surface frame */
  if ((( aFrameSize.X + ( 2 * ob )) > EW_MAX_SURFACE_WIDTH  ) ||
      (( aFrameSize.Y + ( 2 * ob )) > EW_MAX_SURFACE_HEIGHT ))
    ob = ib = 0;

  /* Is the desired FrameSize valid? Respect the maxim. surface size and the
     1 pixel wide border around every frame (we use the border to avoid ugly
     effects when bi-linear filter is applied to scaled or warped bitmaps) */
  if (( aFrameSize.X <= 0 ) || ( aFrameSize.Y <= 0 )  ||
      ( aFrameSize.X > ( EW_MAX_SURFACE_WIDTH  - ( 2 * ob ))) ||
      ( aFrameSize.Y > ( EW_MAX_SURFACE_HEIGHT - ( 2 * ob ))))
  {
    EwErrorDD( 179, aFrameSize.X, aFrameSize.Y );
    return 0;
  }

  /* How many frames may fit horizontally and vertically within a surface? Take
     in account the 1 pixel border around the frames. */
  maxNoOfFramesX  = ( EW_MAX_SURFACE_WIDTH  - 2 * ob + ib ) / ( aFrameSize.X + ib );
  maxNoOfFramesY  = ( EW_MAX_SURFACE_HEIGHT - 2 * ob + ib ) / ( aFrameSize.Y + ib );

  /* Accept evtl. constraints of how to layout frames within a surface area. */
  if (( aMaxNoOfFramesX > 0 ) && ( maxNoOfFramesX > aMaxNoOfFramesX ))
    maxNoOfFramesX = aMaxNoOfFramesX;

  if (( aMaxNoOfFramesY > 0 ) && ( maxNoOfFramesY > aMaxNoOfFramesY ))
    maxNoOfFramesY = aMaxNoOfFramesY;

  /* The resulting max. number of frames a single surface may contain */
  maxNoOfFrames  = maxNoOfFramesX * maxNoOfFramesY;

  /* Reserve memory for the bitmap descriptor. */
  noOfSurfaces = ( aNoOfFrames + maxNoOfFrames - 1 ) / maxNoOfFrames;
  size         = sizeof( XBitmap ) + sizeof( XSurface* ) * noOfSurfaces +
                 sizeof( XBitmapFrame ) * aNoOfFrames;

  /* Additional memory for a frame mapping table required? */
  if ( aNoOfVirtFrames > aNoOfFrames )
    size += aNoOfVirtFrames * sizeof( unsigned short );

  do
    bitmap = EwAlloc( size );
  while ( !bitmap && EwImmediateReclaimMemory( 34 ));

  surfaces = (XSurface**   )( bitmap + 1 );
  frames   = (XBitmapFrame*)( surfaces + noOfSurfaces );
  mapping  = (unsigned short*)( frames + aNoOfFrames );

  /* Couldn't create the new bitmap descriptor due to the resource deficit */
  if ( !bitmap )
  {
    EwError( 34 );
    return 0;
  }

  /* Reset the descriptor structure */
  EwZero( bitmap, size );

  /* Now initialize the list of embedded frames */
  for ( i = 0; i < aNoOfFrames; i++ )
  {
    /* Determine the frame position within a surface */
    int frameNo   = i % maxNoOfFrames;
    int originX   = frameNo % maxNoOfFramesX;
    int originY   = frameNo / maxNoOfFramesX;

    /* Arrange the frame within the surface */
    frames[i].Origin.X = ob + originX * ( aFrameSize.X + ib );
    frames[i].Origin.Y = ob + originY * ( aFrameSize.Y + ib );
  }

  /* Complete the initialization */
  bitmap->Format         = aFormat;
  bitmap->FrameSize      = aFrameSize;
  bitmap->FrameDelay     = aFrameDelay;
  bitmap->NoOfSurfaces   = noOfSurfaces;
  bitmap->NoOfFrames     = aNoOfFrames;
  bitmap->NoOfVirtFrames = aNoOfVirtFrames;
  bitmap->Surfaces       = surfaces;
  bitmap->Frames         = frames;
  bitmap->Mapping        = ( aNoOfVirtFrames > aNoOfFrames )? mapping : 0;

  /* Track the RAM usage */
  EwResourcesMemory += size;

  /* Also track the max. memory pressure */
  if ( EwResourcesMemory > EwResourcesMemoryPeak )
    EwResourcesMemoryPeak = EwResourcesMemory;

  if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
    EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

  return bitmap;
}


/* This helper function verifies whether the given bitmap frame is already mapped
   to a surface. If this is not the case, new surface is created and the frame is
   initialized with a reference to this surface. If the bitmap contains resource
   data, the just created surface is loaded with the respective frames. The
   function returns the given bitmap frame or 0 (zero) if the frame or bitmap
   are wrong. */
static XBitmapFrame* MapBitmapFrame( XBitmap* aBitmap, int aFrameNo )
{
  void*          resource     = 0;
  int            directAccess = 0;
  void*          tag1         = 0;
  void*          tag2         = 0;
  int            surfaceNo    = 0;
  #ifndef EW_DONT_USE_COMPRESSION
    int          loadClut     = 0;
    int          loadFrames   = 0;
  #endif
  int            frameNo      = aFrameNo;
  XBitmapFrame*  frame        = 0;
  XBitmapFrame*  frame1;
  XBitmapFrame*  frame2;
  XBitmapFrame*  frameS;
  XBitmapFrame*  frameL;
  XSurface*      surface;
  XInt32         format;
  int            x1, y1, x2, y2;
  int            border;
  XSurfaceMemory memory;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Is the queried frame existing? */
  if ( !aBitmap || ( aFrameNo < 0 ) || ( aFrameNo >= aBitmap->NoOfVirtFrames ))
    return 0;

  /* Does the bitmap contain shared frames? Then knowing the 'virtual' frame
     get the real frame number */
  if ( aBitmap->Mapping )
    aFrameNo = aBitmap->Mapping[ aFrameNo ];

  /* Is the frame mapping correct? */
  if ( aFrameNo >= aBitmap->NoOfFrames )
    return 0;

  /* Obtain access to the frame */
  frame = aBitmap->Frames + aFrameNo;

  /* The frame is already associated to a a surface */
  if ( frame->Surface )
  {
    /* Mark the surface as used during the actual update cycle */
    frame->Surface->Stamp = EwUpdateCycle;
    return frame;
  }

  EwStartPerfCounter( MapBitmapFrame );

  /* Search for a free entry in the list of associated surfaces */
  while (( surfaceNo < aBitmap->NoOfSurfaces ) && aBitmap->Surfaces[ surfaceNo ])
    surfaceNo++;

  /* Following should never occur unless the layout of the bitmap has been
     corrupted. */
  if ( surfaceNo == aBitmap->NoOfSurfaces )
  {
    EwErrorPD( 318, aBitmap->Resource, frameNo );
    EwStopPerfCounter( MapBitmapFrame );
    return 0;
  }

  /* The bitmap contains data loaded from a resource. Access the resource */
  if ( aBitmap->Resource && (( resource = EwBmpOpen( aBitmap->Resource )) == 0 ))
  {
    EwErrorPD( 132, aBitmap->Resource, 0 );
    EwStopPerfCounter( MapBitmapFrame );
    return 0;
  }

  /* How are the bitmap pixel information stored? Compressed or we can access
     it directly? Simply try to get a pointer to uncompressed pixel. */
  directAccess = resource && EwBmpGetFrameMemory( resource, 0, &memory );

  /* The bitmap is stored in compressed format, but the necessary decompression
     is excluded from the Graphics Engine */
  #ifdef EW_DONT_USE_COMPRESSION
    if ( !directAccess )
    {
      EwErrorPD( 392, aBitmap->Resource, 0 );
      EwStopPerfCounter( MapBitmapFrame );
      return 0;
    }
  #endif

  /* In following steps determine which frames do share the same surface
     and how large is the surface */
  format  = aBitmap->Format;
  frameS  = aBitmap->Frames;
  frameL  = aBitmap->Frames + aBitmap->NoOfFrames - 1;
  frame1  = frame;
  frame2  = frame;
  x1 = x2 = frame->Origin.X;
  y1 = y2 = frame->Origin.Y;

  /* Find preceding frames sharing the same surface. By the way estimate
     the area enclosing all frames. */
  while (( frame1 > frameS ) &&
         (
           (
             !directAccess &&
             (( frame1->Origin.X > frame1[-1].Origin.X ) ||
              ( frame1->Origin.Y > frame1[-1].Origin.Y ))
           ) ||
           (
             directAccess &&
             #if ( EW_SURFACE_ROTATION == 0 )
               ( frame1->Origin.Y > frame1[-1].Origin.Y )
             #endif
             #if ( EW_SURFACE_ROTATION == 90 )
               ( frame1->Origin.X > frame1[-1].Origin.X )
             #endif
             #if ( EW_SURFACE_ROTATION == 180 )
               ( frame1->Origin.Y < frame1[-1].Origin.Y )
             #endif
             #if ( EW_SURFACE_ROTATION == 270 )
               ( frame1->Origin.X < frame1[-1].Origin.X )
             #endif
           )
         ))
  {
    frame1--;
    x1 = MIN( x1, frame1->Origin.X );
    y1 = MIN( y1, frame1->Origin.Y );
    x2 = MAX( x2, frame1->Origin.X );
    y2 = MAX( y2, frame1->Origin.Y );
  }

  /* Find following frames sharing the same surface. By the way estimate
     the area enclosing all frames. */
  while (( frame2 < frameL ) &&
         (
           (
             !directAccess &&
             (( frame2->Origin.X < frame2[1].Origin.X ) ||
              ( frame2->Origin.Y < frame2[1].Origin.Y ))
           ) ||
           (
             directAccess &&
             #if ( EW_SURFACE_ROTATION == 0 )
               ( frame2->Origin.Y < frame2[1].Origin.Y )
             #endif
             #if ( EW_SURFACE_ROTATION == 90 )
               ( frame2->Origin.X < frame2[1].Origin.X )
             #endif
             #if ( EW_SURFACE_ROTATION == 180 )
               ( frame2->Origin.Y > frame2[1].Origin.Y )
             #endif
             #if ( EW_SURFACE_ROTATION == 270 )
               ( frame2->Origin.X > frame2[1].Origin.X )
             #endif
           )
         ))
  {
    frame2++;
    x1 = MIN( x1, frame2->Origin.X );
    y1 = MIN( y1, frame2->Origin.Y );
    x2 = MAX( x2, frame2->Origin.X );
    y2 = MAX( y2, frame2->Origin.Y );
  }

  /* The resulting area enclosing all affected frames. Note the eventually used
     border around the frames. This increases the entire area. */
  border = ( x1 == 1 ) && ( y1 == 1 );
  x2    += aBitmap->FrameSize.X + x1;
  y2    += aBitmap->FrameSize.Y + y1;

  /* If the bitmap is loaded from a resource? */
  if ( resource )
  {
    /* Tags to identify the surface for reuse */
    tag1 = (void*)EwBmpGetCacheSearchTag( aBitmap->Resource );
    tag2 = (void*)( frame1 - frameS );

    /* Is the resource stored in 'direct access' mode? Simply try to get a
       pointer to uncompressed pixel of the first frame sharing the same
       surface. */
    directAccess = EwBmpGetFrameMemory( resource, (int)( frame1 - frameS ),
                                        &memory );
  }

  /* First try to reuse a surface matching the search conditions. */
  surface = EwFindSurface( format, x2, y2, aBitmap, tag1, tag2 );

  /* Not found and the surface contains dynamic contents? */
  #ifndef EW_DONT_USE_COMPRESSION
    if ( !surface && !directAccess )
    {
      surface = EwCreateSurface( format, x2, y2, aBitmap, tag1, tag2 );

      /* Could not create the surface - out of memory */
      if ( !surface )
      {
        if ( format == EW_PIXEL_FORMAT_NATIVE ) EwErrorDD( 111, x2, y2 );
        if ( format == EW_PIXEL_FORMAT_ALPHA8 ) EwErrorDD( 112, x2, y2 );
        if ( format == EW_PIXEL_FORMAT_INDEX8 ) EwErrorDD( 113, x2, y2 );
        if ( format == EW_PIXEL_FORMAT_RGB565 ) EwErrorDD( 114, x2, y2 );

        if ( resource )
          EwBmpClose( resource );

        EwStopPerfCounter( MapBitmapFrame );
        return 0;
      }

      /* The surface has to be loaded from resource */
      loadFrames = resource != 0;
      loadClut   = loadFrames && ( format == EW_PIXEL_FORMAT_INDEX8 );
    }
  #endif

  /* Not found and the surface contains constant contents? */
  if ( !surface && directAccess )
  {
    /* Create the 'constant' surface using the bitmap resource pixel data */
    surface = EwCreateConstSurface( format, x2, y2, aBitmap, tag1, tag2,
                                    &memory );

    /* Could not create the surface - out of memory */
    if ( !surface )
    {
      if ( format == EW_PIXEL_FORMAT_NATIVE ) EwErrorDD( 119, x2, y2 );
      if ( format == EW_PIXEL_FORMAT_ALPHA8 ) EwErrorDD( 120, x2, y2 );
      if ( format == EW_PIXEL_FORMAT_INDEX8 ) EwErrorDD( 121, x2, y2 );
      if ( format == EW_PIXEL_FORMAT_RGB565 ) EwErrorDD( 122, x2, y2 );
      EwBmpClose( resource );
      EwStopPerfCounter( MapBitmapFrame );
      return 0;
    }
  }

  /* Store the surface in the bitmap */
  aBitmap->Surfaces[ surfaceNo ] = surface;

  /* Also assign the surface to all corresponding frames */
  for ( frameS = frame1; frameS <= frame2; frameS++ )
    frameS->Surface = surface;

  /* Should never occurte unless the internal surface mapping is corrupted */
  if ( !frame->Surface )
    return 0;

  /* Draw a transparent border around the frames. Note, with native surfaces
     intended to be used as off-screen buffers, the surface is cleared by the
     underlying graphics subsystem if this system is not able to retain old
     off-screen buffer contents. */
  if ( border && !resource && ( !EwFullOffScreenBufferUpdate ||
                              ( format != EW_PIXEL_FORMAT_NATIVE )))
    DrawFrameGrid( surface, aBitmap->FrameSize.X, aBitmap->FrameSize.Y );

  /* Draw a transparent border around the frames. Assuming, the surface
     is loaded with the resource content, draw the grid by locking the
     surface memory and filling it with zero. Note, RGB565 borders are
     not zeroed. Instead we will fill the border with the content of the
     adjacent edges */
  if ( border && resource && !directAccess && ( format != EW_PIXEL_FORMAT_RGB565 ))
    DrawFrameGrid( surface, aBitmap->FrameSize.X, aBitmap->FrameSize.Y );

  /* Load frames from resource? */
  #ifndef EW_DONT_USE_COMPRESSION
    for ( ; loadFrames && ( frame1 <= frame2 ); frame1++ )
    {
      XSurfaceLock  lock, lockLoad;
      int           ok;

      /* Get access to the pixel memory of the surface */
      if ( format == EW_PIXEL_FORMAT_INDEX8 )
        ok = EwLockSurface( surface, frame1->Origin.X, frame1->Origin.Y,
               aBitmap->FrameSize.X, aBitmap->FrameSize.Y, 0, 256,
               EW_LOCK_PIXEL_WRITE | EW_LOCK_CLUT_WRITE, &lock );
      else if ( border && ( format == EW_PIXEL_FORMAT_RGB565 ))
        ok = EwLockSurface( surface, frame1->Origin.X - 1, frame1->Origin.Y - 1,
               aBitmap->FrameSize.X + 2, aBitmap->FrameSize.Y + 2, 0, 0,
               EW_LOCK_PIXEL_WRITE, &lock );
      else
        ok = EwLockSurface( surface, frame1->Origin.X, frame1->Origin.Y,
               aBitmap->FrameSize.X, aBitmap->FrameSize.Y, 0, 0,
               EW_LOCK_PIXEL_WRITE, &lock );

      if ( !ok )
        EwErrorPD( 136, surface, 0 );

      lockLoad = lock;

      /* In case of RGB565 bitmaps we have to copy the border around every
          bitmap frame. Therefore the locked area includes the border. For
          the load operation, however, the pointer to the pixel data is
          required. */
      if ( ok && border && ( format == EW_PIXEL_FORMAT_RGB565 ))
        lockLoad.Memory.Pixel1 = (char*)lock.Memory.Pixel1 +
                                 lock.Memory.Pitch1Y + lock.Memory.Pitch1X;

      /* With the first frame load also the associated CLUT */
      if ( ok && loadClut )
      {
        ok = EwBmpLoadClut( resource, &lockLoad.Memory );
        loadClut = 0;

        if ( !ok )
          EwErrorPD( 142, aBitmap->Resource, 0 );
      }

      /* Decompress the frames individually */
      if ( ok )
        ok = EwBmpLoadFrame( resource, (int)( frame1 - aBitmap->Frames ),
                             &lockLoad.Memory );

      /* RGB565 has no alpha-information. The 1-pixel wide transparent borders
         used in other color formats will cause RGB565 bitmaps to appear with
         dark edges when the bitmap is stretched, rotated, etc. To avoid this
         effect we have to copy the outer edges of every frame to its border. */
      if ( ok && border && ( format == EW_PIXEL_FORMAT_RGB565 ))
      {
        char* pixel  = lockLoad.Memory.Pixel1;
        int   pitchY = lock.Memory.Pitch1Y;
        int   width  = lock.Width - 2;
        int   height = lock.Height - 2;
        int   rows   = height + 2;

        /* Copy the top edge */
        EwCopy( pixel - pitchY, pixel, width * sizeof( short ));

        /* Copy the bottom edge */
        EwCopy( pixel + pitchY * height, pixel + pitchY * ( height - 1 ),
                width * sizeof( short ));

        /* Copy the left and right edges */
        for ( pixel -= pitchY; rows > 0; rows--, pixel += pitchY )
        {
          *(short*)( pixel - sizeof( short )) = *(short*)pixel;
          *(short*)( pixel + width * sizeof( short )) =
            *(short*)( pixel + ( width - 1 ) * sizeof( short ));
        }
      }

      EwUnlockSurface( surface, &lock );

      if ( !ok )
        EwErrorPD( 135, aBitmap->Resource, 0 );

      /* During prototyping we track the memory usage. The algorithm used to
         decompress bitmaps also requires internally some memory. Thus, if the
         algorithm has been used, remember it. */
      #ifdef EW_PROTOTYPING
        EwUseDecompression++;
      #endif
    }
  #endif

  /* Finished */
  if ( resource )
    EwBmpClose( resource );

  /* Mark the surface as used during the actual update cycle */
  frame->Surface->Stamp = EwUpdateCycle;

  EwStopPerfCounter( MapBitmapFrame );
  return frame;
}


/* The following function helps to fill the surface with a transparent color
   grid as it is necessary to separate frames within multi-frame bitmaps. The
   operation will be executed by locking and filling the surface with zero. */
static void DrawFrameGrid( XSurface* aSurface, int aWidth, int aHeight )
{
  XSurfaceLock lock;
  int          noOfCols = ( aSurface->Width  - 1 ) / ( aWidth  + 1 );
  int          noOfRows = ( aSurface->Height - 1 ) / ( aHeight + 1 );
  int          col      = 0;
  int          row      = 0;

  /* Fill horizontal strips of the grid */
  for ( ; row <= noOfRows; row++ )
    if ( EwLockSurface( aSurface, 0, row * ( aHeight + 1 ), aSurface->Width, 1,
                        0, 0, EW_LOCK_PIXEL_WRITE, &lock ))
    {
      #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
        unsigned char* ptr1   = lock.Memory.Pixel1;
        unsigned char* ptr2   = lock.Memory.Pixel2;
        int            count1 = aSurface->Width;
        int            count2 = aSurface->Width;

        if ( ptr1 )
          for ( ; count1 > 0; count1--, ptr1 += lock.Memory.Pitch1Y )
            EwZero( ptr1, lock.Memory.Pitch1X );

        if ( ptr2 )
          for ( ; count2 > 0; count2--, ptr2 += lock.Memory.Pitch2Y )
            EwZero( ptr2, lock.Memory.Pitch2X );
      #endif

      #if ( EW_SURFACE_ROTATION == 0 ) || ( EW_SURFACE_ROTATION == 180 )
        if ( lock.Memory.Pixel1 )
          EwZero( lock.Memory.Pixel1, aSurface->Width * lock.Memory.Pitch1X );

        if ( lock.Memory.Pixel2 )
          EwZero( lock.Memory.Pixel2, aSurface->Width * lock.Memory.Pitch2X );
      #endif

      EwUnlockSurface( aSurface, &lock );
    }

  /* Tasks for vertical strips of the grid */
  for ( ; col <= noOfCols; col++ )
    if ( EwLockSurface( aSurface, col * ( aWidth + 1 ), 0, 1, aSurface->Height,
                        0, 0, EW_LOCK_PIXEL_WRITE, &lock ))
    {
      #if ( EW_SURFACE_ROTATION == 0 ) || ( EW_SURFACE_ROTATION == 180 )
        unsigned char* ptr1   = lock.Memory.Pixel1;
        unsigned char* ptr2   = lock.Memory.Pixel2;
        int            count1 = aSurface->Height;
        int            count2 = aSurface->Height;

        if ( ptr1 )
          for ( ; count1 > 0; count1--, ptr1 += lock.Memory.Pitch1Y )
            EwZero( ptr1, lock.Memory.Pitch1X );

        if ( ptr2 )
          for ( ; count2 > 0; count2--, ptr2 += lock.Memory.Pitch2Y )
            EwZero( ptr2, lock.Memory.Pitch2X );
      #endif

      #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
        if ( lock.Memory.Pixel1 )
          EwZero( lock.Memory.Pixel1, aSurface->Height * lock.Memory.Pitch1X );

        if ( lock.Memory.Pixel2 )
          EwZero( lock.Memory.Pixel2, aSurface->Height * lock.Memory.Pitch2X );
      #endif

      EwUnlockSurface( aSurface, &lock );
    }
}


/* This helper function seeks in the cache for a glyph. If necessary, a new
   glyph will be loaded into the cache. For all new loaded glyphs there is
   no pixel information stored primarily.  */
static XGlyph* GetGlyph( XFont* aFont, unsigned int aGlyphId )
{
  int          width   = 0;
  int          height  = 0;
  int          originX = 0;
  int          originY = 0;
  int          advance = 0;
  XGlyph*      glyph;

  /* Try to re-use an existing glyphs. Search in the cache for a glyph with
     the given id. */
  if (( glyph = EwFindGlyph( aFont->Tag, aGlyphId )) != 0 )
    return glyph;

  /* First time trying to get the glyph for one of the zero-width characters.
     In such case create a new glyph without any content and with all metrics
     being initialized 0 */
  if ( aGlyphId == 0xFFFFFFFF )
    return EwCreateGlyph( aFont->Tag, aGlyphId, 0, 0, 0, 0, 0 );

  /* Query metrics for the desired glyph. Assuming, a valid glyph-id has been
     obtained from the font before, the operation should not fail. */
  if ( !EwFntGetGlyphMetrics( aFont->Handle, aGlyphId, &originX, &originY,
                              &width, &height, &advance ))
  {
    EwErrorSD( 180, EwFntGetResourceName( aFont->Handle ), aGlyphId );
    return 0;
  }

  /* Reserve space in the glyph cache */
  return EwCreateGlyph( aFont->Tag, aGlyphId, originX, originY, width,
                        height, advance );
}


/* This helper function verifies whether the given glyph is already loaded
   into the glyph surface cache (it is mapped). If necessary, the function
   takes care of loading the glyph pixel data. If successful the function
   return != 0. */
static int MapGlyph( XFont* aFont, unsigned int aGlyphId, XGlyph* aGlyph )
{
  XSurfaceLock lock;
  int          load;

  /* Verify whether the glyph cache is large enough */
  if ((( aGlyph->Width  + 2 ) > EwMaxGlyphSurfaceWidth  ) ||
      (( aGlyph->Height + 2 ) > EwMaxGlyphSurfaceHeight ))
  {
    EwErrorSD( 148, EwFntGetResourceName( aFont->Handle ), aGlyphId );
    return 0;
  }

  /* Try to map the glyph within the glyph cache surface. */
  if ( !EwMapGlyph( aGlyph, &load ))
    return 0;

  /* Already loaded - nothing to do */
  if ( !load )
    return 1;

  /* Obtain an access to the pixel memory of tne glyph */
  if ( EwLockGlyphCache( aGlyph, EW_LOCK_PIXEL_WRITE | EW_LOCK_DONT_WAIT, &lock ))
  {
    /* At fin raster the glyph and unlock the memory */
    if ( !EwFntLoadGlyph( aFont->Handle, aGlyphId, &lock.Memory ))
    {
      EwErrorSD( 184, EwFntGetResourceName( aFont->Handle ), aGlyphId );
      EwUnlockGlyphCache( aGlyph, &lock );

      return 0;
    }

    /* An additional one-pixel wide border reserved around the glyph? Then clear
       the border after loading the glyph into the cache */
    #ifdef EW_BORDER_AROUND_GLYPHS
    {
      int   w   = aGlyph->Width  + 2;
      int   h   = aGlyph->Height + 2;
      char* ptr = (char*)lock.Memory.Pixel1 - lock.Memory.Pitch1Y -
                  lock.Memory.Pitch1X;

      #if ( EW_SURFACE_ROTATION == 0 ) || ( EW_SURFACE_ROTATION == 180 )
        EwZero( ptr, w * lock.Memory.Pitch1X );
        EwZero( ptr + lock.Memory.Pitch1Y * ( h - 1 ), w * lock.Memory.Pitch1X );

        for ( ; h > 0; h--, ptr += lock.Memory.Pitch1Y )
        {
          EwZero( ptr, lock.Memory.Pitch1X );
          EwZero( ptr + ( w - 1 ) * lock.Memory.Pitch1X, lock.Memory.Pitch1X );
        }
      #endif

      #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
        EwZero( ptr, h * lock.Memory.Pitch1X );
        EwZero( ptr + lock.Memory.Pitch1Y * ( w - 1 ), h * lock.Memory.Pitch1X );

        for ( ; w > 0; w--, ptr += lock.Memory.Pitch1Y )
        {
          EwZero( ptr, lock.Memory.Pitch1X );
          EwZero( ptr + ( h - 1 ) * lock.Memory.Pitch1X, lock.Memory.Pitch1X );
        }
      #endif
    }
    #endif

    EwUnlockGlyphCache( aGlyph, &lock );
  }

  /* Lock operation is failed */
  else
    EwErrorSD( 185, EwFntGetResourceName( aFont->Handle ), aGlyphId );

  return 1;
}


/* This helper function calculates the color value in the range aColor 1 ..
   aColor2 depending on the Factor, which lies in the range 0 .. aRange. */
static XColor InterpolateColor( XColor aColor1, XColor aColor2, int aFactor,
  int aRange )
{
  int r = aColor1.Red   + (( aColor2.Red   - aColor1.Red   ) * aFactor ) / aRange;
  int g = aColor1.Green + (( aColor2.Green - aColor1.Green ) * aFactor ) / aRange;
  int b = aColor1.Blue  + (( aColor2.Blue  - aColor1.Blue  ) * aFactor ) / aRange;
  int a = aColor1.Alpha + (( aColor2.Alpha - aColor1.Alpha ) * aFactor ) / aRange;

  aColor1.Red   = (XUInt8)r;
  aColor1.Green = (XUInt8)g;
  aColor1.Blue  = (XUInt8)b;
  aColor1.Alpha = (XUInt8)a;

  return aColor1;
}


#ifndef EW_DONT_USE_PATH_FUNCTIONS

/* This helper function verifies whether the path information is still valid and
   if this is not the case, updates the path. */
static void UpdatePath( XPath* aPath )
{
  XSubPath** subPaths        = aPath->SubPaths;
  int        noOfSubPaths    = aPath->MaxNoOfSubPaths;
  XRect      bounds          = {{ 0, 0 }, { 0, 0 }};
  int        noOfOpenedPaths = 0;
  int        noOfClosedPaths = 0;
  int        noOfEdges       = 0;

  /* The path is already up to date */
  if ( aPath->IsValid )
    return;

  /* Traverse all sub-paths and calculate the rectangular 'bounds' area enclosing
     all of them */
  for ( ; noOfSubPaths > 0; noOfSubPaths--, subPaths++ )
  {
    XSubPath* subPath = *subPaths;

    /* Is this path up to date? If not recalculate its own 'bounds' area */
    if ( subPath && !subPath->IsValid && subPath->NoOfEdges )
    {
      float  x1    = subPath->Data[0];
      float  y1    = subPath->Data[1];
      float  x2    = x1;
      float  y2    = y1;
      float* data  = (float*)subPath->Data + 2;
      int    count = subPath->NoOfEdges;

      /* Evaluate all coordinate pairs belonging to the sub-path and get the
         enclosing rectangular area */
      for ( ; count > 0; count--, data += 2 )
      {
        if ( data[0] < x1 ) x1 = data[0];
        if ( data[0] > x2 ) x2 = data[0];
        if ( data[1] < y1 ) y1 = data[1];
        if ( data[1] > y2 ) y2 = data[1];
      }

      /* Store the just calculated bounds area in the sub-path */
      subPath->Bounds  = EwNewRect((int)x1, (int)y1, (int)x2 + 1, (int)y2 + 1 );
      subPath->IsValid = 1;
    }

    /* The path counts the state of all embedded sub-paths */
    if ( subPath && subPath->IsValid )
    {
      noOfOpenedPaths += subPath->IsOpened? 1 : 0;
      noOfClosedPaths += subPath->IsClosed? 1 : 0;
      noOfEdges       += subPath->NoOfEdges;

      /* Calculate the unin enclosing all sub-paths */
      bounds = EwUnionRect( bounds, subPath->Bounds );
    }
  }

  /* Store the calculated bounds area */
  aPath->NoOfOpenedPaths = noOfOpenedPaths;
  aPath->NoOfClosedPaths = noOfClosedPaths;
  aPath->NoOfEdges       = noOfEdges;
  aPath->Bounds          = bounds;
  aPath->IsValid         = 1;
}


/* This helper function is used to copy path information so that it can be
   rasterized. The function copies the path data into the buffer aBufPath
   and returns the address within the buffer where the copied information
   ends */
static int* PrepareForFillPath( XSubPath* aSubPath, int* aBufPath, int aDstX,
  int aDstY, int aFlipY )
{
  int*   bufPath2 = aBufPath + 1;
  float* data     = (float*)aSubPath->Data;
  int    count    = aSubPath->NoOfEdges;
  float  xp, yp;

  /* The start position of the path */
  *bufPath2++ = (int)(( xp = *data++ ) * 16.0f )          + aDstX;
  *bufPath2++ = (int)(( yp = *data++ ) * 16.0f ) * aFlipY + aDstY;

  /* For every edge copy its coordinates. Ignore edges with the length 0 */
  for ( ; count > 0; count--, data += 2 )
    if (( data[0] != xp ) || ( data[1] != yp ))
    {
      *bufPath2++ = (int)(( xp = data[0]) * 16.0f )          + aDstX;
      *bufPath2++ = (int)(( yp = data[1]) * 16.0f ) * aFlipY + aDstY;
    }

  /* The path is evidently opened. Add an additional edge */
  if (( bufPath2[-2] != aBufPath[1]) || ( bufPath2[-1] != aBufPath[2]))
  {
    *bufPath2++ = aBufPath[1];
    *bufPath2++ = aBufPath[2];
  }

  /* Did the path contain any data? */
  if (( bufPath2 - aBufPath ) >= 5 )
  {
    *aBufPath = (int)(( bufPath2 - aBufPath - 3 ) >> 1 );
     aBufPath = bufPath2;
  }

  return aBufPath;
}


/* Helper function to find a scaling factor for a direction vector describing
   a line B so that this line intersects the line A. The line A is described by
   the equation ( A + VA * S ) and the line B by the equation ( B + VB * T ).
   If successfull the function stores the scaling factor for the direction
   vector of line B in the operand aT and returns != 0. If lines are parallel
   (no intersection is possible), the function aborts with the value 0. */
static int Intersect2Lines( float aAX, float aAY, float aVAX, float aVAY,
  float aBX, float aBY, float aVBX, float aVBY, float* aT )
{
  float q = ( aVBX * aVAY ) - ( aVBY * aVAX );

  if ( q == 0.0f )
    return 0;

  *aT = ((( aBY - aAY ) * aVAX ) - (( aBX - aAX ) * aVAY )) / q;
  return 1;
}


/* This helper function is used to prepare and copy path information so that
   it can be rasterized. The function copies the path data into the buffer
   aBufPath and returns the address within the buffer where the copied
  information ends */
static int* PrepareForStrokePath( XSubPath* aSubPath, int aStyleStart,
  int aStyleEnd, int aStyleJoin, float aMiterLimit, float aWidth2,
  int* aBufPath, float* aBufHelp, int aDstX, int aDstY, int aFlipY,
  int aRoundSteps, float aRoundCos, float aRoundSin, float* aMatrix )
{
  float* data      = (float*)aSubPath->Data;
  int    count     = aSubPath->NoOfEdges;
  int    closed    = aSubPath->IsClosed;
  int*   bufPath2  = aBufPath;
  float* bufHelp2  = aBufHelp;
  float  xp        = *data++;
  float  yp        = *data++;
  float  uvxp      = 0.0f;
  float  uvyp      = 0.0f;
  int    progress  = 1;
  float  miterMax  = aMiterLimit;
  float  miterMin  = 0.0f;
  float  det       = ( aMatrix[0] * aMatrix[3]) - ( aMatrix[1] * aMatrix[2]);
  float  invMatrix[4];
  int    edge;

  /* Get the inverse of the matrix. It is necessary to obtain from the path its
     original coordinates and based on them calculate the path outline. */
  if ( det != 0.0f )
  {
    invMatrix[0] =  aMatrix[3] / det; invMatrix[1] = -aMatrix[1] / det;
    invMatrix[2] = -aMatrix[2] / det; invMatrix[3] =  aMatrix[0] / det;
  }
  else
  {
    invMatrix[0] = 1.0f; invMatrix[1] = 0.0f;
    invMatrix[2] = 0.0f; invMatrix[3] = 1.0f;
  }

  /* From the miter limit calculate a factor to limit sharp angle corners.
     Ignore miter if there are less then 2 pixel to connect with the miter */
  if ( aStyleJoin == EW_PATH_JOIN_MITER )
  {
    miterMax = miterMax * miterMax;
    miterMin = 4.0f / ( aWidth2 * aWidth2 );
  }

  /* Process all edges of the actual sub-path and calculate for every edge the
     corresponding unit vector and its direction relative to the preceding
     edge. Store the information at the end of the available memory area */
  for ( edge = 0; edge < count; edge++ )
  {
    float x   = *data++;
    float y   = *data++;
    float vx  = x - xp;
    float vy  = y - yp;
    float uvx = ( vx * invMatrix[0]) + ( vy * invMatrix[1]);
    float uvy = ( vx * invMatrix[2]) + ( vy * invMatrix[3]);
    float len = EwMathSqrt(( uvx * uvx ) + ( uvy * uvy ));

    /* Convert the edge in a unit vector */
    if ( len > 0.0f ) { uvx /= len; uvy /= len; }

    /* Store the unit vector and its direction relative to the preceding
       unit vector */
    *--bufHelp2 = uvxp * uvy - uvyp * uvx;
    *--bufHelp2 = uvy;
    *--bufHelp2 = uvx;

    /* Start coordinates for the next edge */
    if (( x != xp ) || ( y != yp ))
    {
      xp = x; uvxp = uvx;
      yp = y; uvyp = uvy;
    }
  }

  /* If the path is closed take in account the direction between the last
     and the first edge */
  aBufHelp[-1] = uvxp * aBufHelp[-2] - uvyp * aBufHelp[-3];
  bufHelp2[-1] = aBufHelp[-1];
  data         = (float*)aSubPath->Data;
  bufHelp2     = aBufHelp - 3;
  xp           = *data++;
  yp           = *data++;

  /* Traverse along the path and generate the outline polygon */
  for ( edge = -count + 1; edge <= count; edge++ )
  {
    float x    = data[0];
    float y    = data[1];
    float uvx  = ( progress < 0 )? -bufHelp2[0]  : bufHelp2[0];
    float uvy  = ( progress < 0 )? -bufHelp2[1]  : bufHelp2[1];
    float dir  = ( progress < 0 )? -bufHelp2[-1] : bufHelp2[2];
    float tvx  = aWidth2 * uvx;
    float tvy  = aWidth2 * uvy;

    /* Edge with zero length is ignored. Skip over and continue with the
       next one */
    if (( x == xp ) && ( y == yp ))
    {
      if ( !edge )
        progress = -progress;
      else
        bufHelp2 -= progress * 3;

      data += progress * 2;
      continue;
    }

    /* Should the cap at the begin of the path appear square? */
    if ( !closed &&
       ( aStyleStart == EW_PATH_CAP_START_SQUARE ) && ( aBufPath == bufPath2 ))
    {
      float hdx = aMatrix[0] * tvx + aMatrix[1] * tvy;
      float hdy = aMatrix[2] * tvx + aMatrix[3] * tvy;
      xp -= hdx;
      yp -= hdy;
    }

    /* Should the cap at the end of the path appear square? */
    if ( !closed &&
       ((( aStyleStart == EW_PATH_CAP_START_SQUARE ) && ( edge == count )) ||
        (( aStyleEnd   == EW_PATH_CAP_END_SQUARE   ) &&  !edge )))
    {
      float hdx = aMatrix[0] * tvx + aMatrix[1] * tvy;
      float hdy = aMatrix[2] * tvx + aMatrix[3] * tvy;
      x += hdx;
      y += hdy;
    }

    /* Join the edges by a miter corner? */
    if (( aStyleJoin == EW_PATH_JOIN_MITER  ) && ( dir > 0.0f ) &&
        ( closed || (( bufPath2 != aBufPath ) && ( edge != 1 ))))
    {
      float kx   = (( aMatrix[0] * uvyp ) + ( aMatrix[1] * -uvxp )) * aWidth2;
      float ky   = (( aMatrix[2] * uvyp ) + ( aMatrix[3] * -uvxp )) * aWidth2;
      float lx   = (( aMatrix[0] * uvy  ) + ( aMatrix[1] * -uvx  )) * aWidth2;
      float ly   = (( aMatrix[2] * uvy  ) + ( aMatrix[3] * -uvx  )) * aWidth2;
      float kuvx = (  aMatrix[0] * uvxp ) + ( aMatrix[1] *  uvyp );
      float kuvy = (  aMatrix[2] * uvxp ) + ( aMatrix[3] *  uvyp );
      float luvx = (  aMatrix[0] * uvx  ) + ( aMatrix[1] *  uvy  );
      float luvy = (  aMatrix[2] * uvx  ) + ( aMatrix[3] *  uvy  );
      float s    = 0.0f;
      int   ok   = Intersect2Lines( xp + kx, yp + ky, kuvx, kuvy, xp + lx,
                                    yp + ly, -luvx, -luvy, &s );
      float hdx  = xp + lx + ( -luvx * ( ok? s : 0.0f ));
      float hdy  = yp + ly + ( -luvy * ( ok? s : 0.0f ));

      /* Miter length calculation */
      float mx   = ( invMatrix[0] * ( hdx - xp )) + ( invMatrix[1] * ( hdy - yp ));
      float my   = ( invMatrix[2] * ( hdx - xp )) + ( invMatrix[3] * ( hdy - yp ));
      float ml   = ( mx * mx + my * my ) / ( aWidth2 * aWidth2 );

      /* If the angle between the edges is not too acute then prolongate the
         end position of the preceding edge and append the new edge to it.
         No additional edges are needed. */
      if (( ml <= miterMax ) && ( ml >= miterMin ))
      {
        float hdx = xp + lx + ( -luvx * s );
        float hdy = yp + ly + ( -luvy * s );

        /* Just at the begin of the path or already inside the path between two
           edges? */
        if ( bufPath2 == aBufPath )
        {
          *++bufPath2 = (int)( hdx * 16.0f ) +          aDstX;
          *++bufPath2 = (int)( hdy * 16.0f ) * aFlipY + aDstY;
        }
        else
        {
          bufPath2[-1] = (int)( hdx * 16.0f ) +          aDstX;
          bufPath2[0]  = (int)( hdy * 16.0f ) * aFlipY + aDstY;
        }
      }

      /* If the angle is too acute. Connect the end of the preceding edges with
         the begin of the new edge by an additional bevel */
      else
      {
        float hdx = aMatrix[0] * tvy + aMatrix[1] * -tvx;
        float hdy = aMatrix[2] * tvy + aMatrix[3] * -tvx;

        *++bufPath2 = (int)(( xp + hdx ) * 16.0f ) +          aDstX;
        *++bufPath2 = (int)(( yp + hdy ) * 16.0f ) * aFlipY + aDstY;
      }
    }

    /* Join the edges by a rounded corner? */
    else if (( aStyleJoin == EW_PATH_JOIN_ROUND  ) && ( dir > 0.0f ) &&
             ( closed || (( bufPath2 != aBufPath ) && ( edge != 1 ))))
    {
      float tvxp  =  uvyp * aWidth2;
      float tvyp  = -uvxp * aWidth2;
      int   count = aRoundSteps;
      float hdx;
      float hdy;

      while ( count-- )
      {
        /* Starting with the preceding segment calculate the position
           of the next segment. Rotate it */
        float tvxp2 = tvxp * aRoundCos - tvyp * aRoundSin;
        float tvyp2 = tvxp * aRoundSin + tvyp * aRoundCos;

        /* Have the just calculated segment reached the right edge? */
        if (( tvxp2 * -tvx - tvyp2 * tvy ) <= 0.0f )
          break;

        hdx = aMatrix[0] * tvxp2 + aMatrix[1] * tvyp2;
        hdy = aMatrix[2] * tvxp2 + aMatrix[3] * tvyp2;

        *++bufPath2 = (int)(( xp + hdx ) * 16.0f ) +          aDstX;
        *++bufPath2 = (int)(( yp + hdy ) * 16.0f ) * aFlipY + aDstY;

        /* The segment for the next iteration */
        tvxp = tvxp2;
        tvyp = tvyp2;
      }

      hdx = aMatrix[0] * tvy + aMatrix[1] * -tvx;
      hdy = aMatrix[2] * tvy + aMatrix[3] * -tvx;

      /* The start position of the new edge */
      *++bufPath2 = (int)(( xp + hdx ) * 16.0f ) +          aDstX;
      *++bufPath2 = (int)(( yp + hdy ) * 16.0f ) * aFlipY + aDstY;
    }

    /* Join the edges by a bevel corner? */
    else
    {
      float hdx = aMatrix[0] * tvy + aMatrix[1] * -tvx;
      float hdy = aMatrix[2] * tvy + aMatrix[3] * -tvx;
      *++bufPath2 = (int)(( xp + hdx ) * 16.0f ) +          aDstX;
      *++bufPath2 = (int)(( yp + hdy ) * 16.0f ) * aFlipY + aDstY;
    }

    {
      float hdx = aMatrix[0] * tvy + aMatrix[1] * -tvx;
      float hdy = aMatrix[2] * tvy + aMatrix[3] * -tvx;

      /* The end position of the new edge */
      *++bufPath2 = (int)(( x + hdx ) * 16.0f ) +          aDstX;
      *++bufPath2 = (int)(( y + hdy ) * 16.0f ) * aFlipY + aDstY;

      /* Should the cap at the both ends appear as triangle? */
      if ( !closed &&
         ((( aStyleStart == EW_PATH_CAP_START_TRIANGLE ) &&
           ( edge == count )) ||
          (( aStyleEnd == EW_PATH_CAP_END_TRIANGLE ) && !edge )))
      {
        float hdx = aMatrix[0] * tvx + aMatrix[1] * tvy;
        float hdy = aMatrix[2] * tvx + aMatrix[3] * tvy;
        *++bufPath2 = (int)(( x + hdx ) * 16.0f ) +          aDstX;
        *++bufPath2 = (int)(( y + hdy ) * 16.0f ) * aFlipY + aDstY;
      }

      /* Should the cap at the both ends appear round? */
      if ( !closed &&
         ((( aStyleStart == EW_PATH_CAP_START_ROUND ) &&
           ( edge == count )) ||
          (( aStyleEnd == EW_PATH_CAP_END_ROUND ) && !edge )))
      {
        float tvx2 =  tvy;
        float tvy2 = -tvx;
        int   i;

        for ( i = 0; i < aRoundSteps - 1; i++ )
        {
          float tvx3 = tvx2 * aRoundCos - tvy2 * aRoundSin;
          float tvy3 = tvx2 * aRoundSin + tvy2 * aRoundCos;
          float hdx  = aMatrix[0] * tvx3 + aMatrix[1] * tvy3;
          float hdy  = aMatrix[2] * tvx3 + aMatrix[3] * tvy3;

          *++bufPath2 = (int)(( x + hdx ) * 16.0f ) +          aDstX;
          *++bufPath2 = (int)(( y + hdy ) * 16.0f ) * aFlipY + aDstY;

          tvx2 = tvx3;
          tvy2 = tvy3;
        }
      }
    }

    /* We are done with the left outline of the path and the path is
       closed. In such case close the sub-path and start with a new one
       for the right outline */
    if ( closed && !edge )
    {
      uvx = -aBufHelp[-3];
      uvy = -aBufHelp[-2];

      *++bufPath2 = aBufPath[1];
      *++bufPath2 = aBufPath[2];
      *aBufPath   = (int)(( bufPath2 - aBufPath - 2 ) >> 1 );
       aBufPath   = ++bufPath2;
    }

    /* The begin of the path has been reached. Change the direction now.
       Otherwise just skip to the next entry in the help buffer */
    if ( !edge )
      progress = -progress;
    else
      bufHelp2 -= progress * 3;

    /* Start coordinates for the next edge */
    xp    = x;
    yp    = y;
    uvxp  = uvx;
    uvyp  = uvy;
    data += progress * 2;
  }

  /* Close the last sub-path */
  *++bufPath2 = aBufPath[1];
  *++bufPath2 = aBufPath[2];

  /* Did the path contain any data? */
  if (( bufPath2 - aBufPath ) >= 4 )
  {
    *aBufPath = (int)(( bufPath2 - aBufPath - 2 ) >> 1 );
     aBufPath = bufPath2 + 1;
  }

  return aBufPath;
}

#endif /* EW_DONT_USE_PATH_FUNCTIONS */


#if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS

/* This helper function sorts the aCount color stops according their
   offset values. */
static void SortColorStops( XGradientStop* aStops, int aCount )
{
  int i;

  for ( ; aCount > 1; aCount-- )
    for ( i = 0; i < aCount - 1; i++ )
      if ( aStops[i].Offset > aStops[i+1].Offset )
      {
        XGradientStop tmp = aStops[i];
        aStops[i]   = aStops[i+1];
        aStops[i+1] = tmp;
      }
}

#endif /* EW_DONT_USE_GRADIENTS && EW_DONT_USE_PATH_FUNCTIONS */


#ifndef EW_DONT_USE_PATH_FUNCTIONS


/* The following callback is invoked when surface cached in the 'Rounded
   Rectangle Cache' is about to be discarded */
static void OnDiscardRoundedRectangleSurfaceProc( XSurface* aSurface, 
  void* aTag1, void* aTag2 )
{
  XCachedRoundedRectangleBitmap* entry = (XCachedRoundedRectangleBitmap*)aTag1;

  EW_UNUSED_ARG( aSurface );
  EW_UNUSED_ARG( aTag2 );

  /* Remove the cache entry */
  if ( entry->Prev ) entry->Prev->Next = entry->Next;
  else               EwRoundedRectangleBitmapCacheHead = entry->Next;

  if ( entry->Next ) entry->Next->Prev = entry->Prev;
  else               EwRoundedRectangleBitmapCacheTail = entry->Prev;

  /* Free the memory used by the cache entry */
  EwFree( entry );

  /* Track the RAM usage */
  EwResourcesMemory -= sizeof( XCachedRoundedRectangleBitmap );
}


/* Following internal function stores the given bitmap in the 'Rounded Rectangle
   Bitmap Cache'. Thereupon the bitmap can be reused. */
static void CacheRoundedRectangleBitmap( XBitmap* aBitmap, int aWidth, 
  int aHeight, int aBorderWidth, int aRadiusTL, int aRadiusTR, int aRadiusBR,
  int aRadiusBL, int aBlurRadius )
{
  XCachedRoundedRectangleBitmap* entry;

  do
    entry = EwAlloc( sizeof( XCachedRoundedRectangleBitmap ));
  while ( !entry && EwImmediateReclaimMemory( 55 ));

  /* Couldn't create the cache object due to the resource deficit - the bitmap
     will not be cached. Just release it. */
  if ( !entry )
  {
    EwFree( aBitmap );
    EwError( 55 );
    return;
  }

  /* Track the RAM usage */
  EwResourcesMemory += sizeof( XCachedRoundedRectangleBitmap );

  /* Also track the max. memory pressure */
  if ( EwResourcesMemory > EwResourcesMemoryPeak )
    EwResourcesMemoryPeak = EwResourcesMemory;

  if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
    EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

  /* Store parameters identifying the bitmap's content */
  entry->Width       = aWidth;
  entry->Height      = aHeight;
  entry->BorderWidth = aBorderWidth;
  entry->RadiusTL    = aRadiusTL;
  entry->RadiusTR    = aRadiusTR;
  entry->RadiusBL    = aRadiusBL;
  entry->RadiusBR    = aRadiusBR;
  entry->BlurRadius  = aBlurRadius;
  entry->Surface     = aBitmap->Surfaces[0];

  /* Store a new entry at the beginning of the cache */
  entry->Next = EwRoundedRectangleBitmapCacheHead;
  entry->Prev = 0;

  if ( EwRoundedRectangleBitmapCacheHead )
    EwRoundedRectangleBitmapCacheHead->Prev = entry;
  else
    EwRoundedRectangleBitmapCacheTail = entry;

  EwRoundedRectangleBitmapCacheHead = entry;

  // The owner of the surface changes to this cache entry
  entry->Surface->Used++;
  entry->Surface->Owned++;

  /* The bitmap is cached now and we can release its ownership */
  EwFreeBitmap( aBitmap );

  /* Let the surface refer the cache entry. When the system is about to discard
     the surface, the callback OnDiscardRoundedRectangleSurfaceProc() is
     invoked. */
  EwSetSurfaceCacheTags( entry->Surface, entry, 0,
                         OnDiscardRoundedRectangleSurfaceProc );
}


/* Following function searches in the 'Rounded Rectangle Bitmap Cache' for a
   bitmap created originally according to the specified parameters. If found,
   the bitmap is removed from the cache and returned. If not found, the function
   returns NULL. */
static XBitmap* FindCachedRoundedRectangleBitmap( int aWidth, int aHeight,
  int aBorderWidth, int aRadiusTL, int aRadiusTR, int aRadiusBR, int aRadiusBL,
  int aBlurRadius )
{
  XCachedRoundedRectangleBitmap* entry = EwRoundedRectangleBitmapCacheHead;
  XBitmap*                       bitmap;

  /* Search in the 'Rounded Rectangle Cache' for an enry matching the given
     parameter */
  while ( entry && (( entry->Width       != aWidth       ) ||
                    ( entry->Height      != aHeight      ) ||
                    ( entry->BorderWidth != aBorderWidth ) ||
                    ( entry->RadiusTL    != aRadiusTL    ) ||
                    ( entry->RadiusTR    != aRadiusTR    ) ||
                    ( entry->RadiusBR    != aRadiusBR    ) ||
                    ( entry->RadiusBL    != aRadiusBL    ) ||
                    ( entry->BlurRadius  != aBlurRadius  )))
    entry = entry->Next;

  /* Not found */
  if ( !entry )
    return 0;

  /* Create and initialize a bitmap descriptor structure. This call prepares
     the list of frames and assigns them the appropriate positions within the
     respective surfaces. The surfaces, however, are not created until the
     frames are accessed. */
  bitmap = InitBitmap( EW_PIXEL_FORMAT_ALPHA8, EwNewPoint( aWidth, aHeight ), 0,
                       1, 1, 0, 0, 1, 0, 0 );

  /* Failed to create a Bitmap structure */
  if ( !bitmap )
    return 0;

  /* Complete the bitmap structure initialization */
  bitmap->Surfaces[0]       = entry->Surface;
  bitmap->Frames[0].Surface = entry->Surface;

  /* Unlink the surface from the cache entry. */
  EwSetSurfaceCacheTags( entry->Surface, 0, 0, 0 );

  /* Remove the cache entry */
  if ( entry->Prev ) entry->Prev->Next = entry->Next;
  else               EwRoundedRectangleBitmapCacheHead = entry->Next;

  if ( entry->Next ) entry->Next->Prev = entry->Prev;
  else               EwRoundedRectangleBitmapCacheTail = entry->Prev;

  /* Free the memory used by the cache entry */
  EwFree( entry );

  /* Track the RAM usage */
  EwResourcesMemory -= sizeof( XCachedRoundedRectangleBitmap );

  return bitmap;
}


#endif /* EW_DONT_USE_PATH_FUNCTIONS */


/* WcsLen() returns the number of wide-characters in the string aString
   without the zero-terminator sign */
static int WcsLen( const XChar* aString )
{
  const XChar* tmp = aString;

  /* Null string -> Nothing to do */
  if ( !tmp )
    return 0;

  /* Look for the zero-terminator sign */
  while ( *tmp )
    tmp++;

  return (int)( tmp - aString );
}


/* Helper function for minimum value determination */
static int MIN3( int a, int b, int c )
{
  if ( b < a )
    a = b;

  return ( a < c )? a : c;
}


/* Helper function for maximum value determination */
static int MAX3( int a, int b, int c )
{
  if ( b > a )
    a = b;

  return ( a > c )? a : c;
}


#ifndef EW_DONT_USE_WARP_FUNCTIONS
  /* Helper function for minimum value determination */
  static XFloat MINF4( XFloat a, XFloat b, XFloat c, XFloat d )
  {
    if ( b < a ) a = b;
    if ( d < c ) c = d;

    return ( a < c )? a : c;
  }


  /* Helper function for maximum value determination */
  static XFloat MAXF4( XFloat a, XFloat b, XFloat c, XFloat d )
  {
    if ( b > a ) a = b;
    if ( d > c ) c = d;

    return ( a > c )? a : c;
  }
#endif


/* pba */
