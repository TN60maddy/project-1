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
*   This module implements the SVG (scalable vector graphics) processing of the
*   Embedded Wizard Graphics Engine EWGFX. This includes the loading of SVG
*   files and displaying the SVG contents.
*
*   Due to the enormous complexity of the SVG standard, Embedded Wizard limits
*   to support following features of SVG only:
*
*   <svg>, <rect>, <circle>, <ellipse>, <line>, <polyline>, <polygon>, <path>
*   <g>, <use>
*   <linearGradient>, <radialGradient>
*   <style>
*
* SUBROUTINES:
*   EwInitSVG
*   EwCreatePathFromSVGString
*   EwCreateSVGObjectFromSVGString
*   EwLoadSVGObject
*   EwFreeSVGObject
*   EwGetSVGParserStatus
*   EwGetSVGParserErrorPos
*   EwCalcSizeOfSVGObject
*   EwDrawSVGObject
*
*******************************************************************************/

#include "ewrte.h"
#include "ewgfxdriver.h"
#include "ewgfxres.h"
#include "ewgfx.h"


/* If path functionality is remove, also remove SVG functionality */
#ifdef EW_DONT_USE_PATH_FUNCTIONS
  #define EW_DONT_USE_SVG_FUNCTIONS
#endif

/* If SVG functionality is removed, also remove the SVG reader functionality */
#ifdef EW_DONT_USE_SVG_FUNCTIONS
  #define EW_DONT_USE_SVG_READER
#endif


/* Helper macros for minimum and maximum calculation */
#ifdef MIN
  #undef MIN
#endif
#define MIN( a, b ) (((a) < (b))? (a) : (b))

#ifdef MAX
  #undef MAX
#endif
#define MAX( a, b ) (((a) > (b))? (a) : (b))


/* Helper macro to calculate the distance between two points */
#define DISTANCE( aX1, aY1, aX2, aY2 )                                         \
  EwMathSqrt(((aX1) - (aX2)) * ((aX1) - (aX2)) +                               \
             ((aY1) - (aY2)) * ((aY1) - (aY2)))


/* Helper macros to access and convert values during execution of SVG drawing
   commands. */
#define INT32( aData )                                                         \
  ( useReader? *(int*)EwFlashAreaReaderProc( aData, 0 ) : *(int*)(aData))

#define UINT32( aData )                                                        \
  ( useReader? *(unsigned int*)EwFlashAreaReaderProc( aData, 0 ) :             \
               *(unsigned int*)(aData))

#define FLOAT( aData )                                                         \
  ( useReader? *(float*)EwFlashAreaReaderProc( aData, 0 ) : *(float*)(aData))

#define OPACITY( aData )                                                       \
  ((unsigned char)( FLOAT(aData) * 255.0f ))


/* Helper macros to convert coordinates */
#define CALC_RANGE( aData, aUnit, aRange )                                     \
  (((aUnit) == Unit_Percent )? (aData) * (aRange) : (aData))

#define CALC_HORZ( aData, aUnit )                                              \
  CALC_RANGE( aData, aUnit, state->RangeHorz )

#define CALC_VERT( aData, aUnit )                                              \
  CALC_RANGE( aData, aUnit, state->RangeVert )

#define CALC_DIAG( aData, aUnit )                                              \
  (((aUnit) == Unit_Percent )? (aData) * state->RangeDiag : (aData))

#define TRANSFORM_X( aX, aY )                                                  \
  (((aX) * state->Matrix[0]) + ((aY) * state->Matrix[1]) + state->Matrix[2])

#define TRANSFORM_Y( aX, aY )                                                  \
  (((aX) * state->Matrix[3]) + ((aY) * state->Matrix[4]) + state->Matrix[5])


/* Units for the processed values. */
#define Unit_None     0
#define Unit_Percent  1
#define Unit_IN       2
#define Unit_CM       3
#define Unit_MM       4
#define Unit_PT       5
#define Unit_PC       6
#define Unit_PX       7


/* Memory usage profiler */
extern int EwResourcesMemory;
extern int EwResourcesMemoryPeak;
extern int EwObjectsMemory;
extern int EwStringsMemory;
extern int EwMemoryPeak;


/* Following variables describe Flash memory which is not directly accessible
   by the CPU. In order to read the Flash memory, a user own reader procedure
   is used. Please see the function EwRegisterFlashAreaReader(). */
extern XFlashAreaReaderProc EwFlashAreaReaderProc;
extern void*                EwFlashAreaStartAddress;
extern void*                EwFlashAreaEndAddress;
extern int                  EwFlashAreaBlockSize;


/* Helper macro to test whether the given address is lying in not directly
   accessible memory area. */
#define USE_FLASH_READER( aAddress )                                           \
  ( EwFlashAreaReaderProc &&                                                   \
  ((const void*)(aAddress) >= EwFlashAreaStartAddress ) &&                     \
  ((const void*)(aAddress) <= EwFlashAreaEndAddress  ))


/* Exclude path functionality? It includes the path string parsing */
#ifndef EW_DONT_USE_PATH_FUNCTIONS
  /* The following both variables store the status of the last SVG parsing and
     the position of the error in the processed SVG content. */
  int EwSVGParserStatus   = EW_SVG_PARSER_SUCCESS;
  int EwSVGParserErrorPos = -1;
#endif


/* Exclude path functionality? It includes the path string parsing */
#ifndef EW_DONT_USE_PATH_FUNCTIONS

/* XBuffer stores the commands to compose an SVG image. This buffer can
   grow in order to take more commands. It's used internally while the SVG
   text is parsed. */
typedef struct
{
  /* The entire allocated buffer */
  unsigned int*     Buffer;
  int               Size;

  /* Pointer to the next free entry in the buffer */
  unsigned int*     Ptr;

  /* If not NULL, pointer to a DWORD to store up to 4 commands.
     Additionally the number of already stored commands in the DWORD. */
  unsigned int*     InstPtr;
  int               InstCount;

  /* Flag indicating an error in memory allocation. The owner of the buffer
     has to abort the operation if the flag is set. */
  int               OutOfMemory;
} XBuffer;


/* Stores the given data value in aBuffer. If necessary the buffer is enlarged
   to accomodate the new data. Returns != 0 if successful. If there is no memory
   to enlarge the buffer, returns 0. */
static void AppendUInt32( XBuffer* aBuffer, unsigned int aValue );

/* Appends additional 'no operation' op-codes to completely fill the current
   commands quad. It should ensure that the next command starts at the
   next free dword. */
static void AlignBuffer( XBuffer* aBuffer );

/* This function frees the buffer and it's entire content */
static void FreeBuffer( XBuffer* aBuffer );

/* This helper function tries to parse a sequence of SVG path commands found in
   aText. The function returns a number of sub-paths recognized and stored as
   commands in aDest. In error case the variables aErrorCode and aErrorPos
   describe the error and its position relative to the beginning of aText. */
static unsigned int ParseSVGPath( const XChar** aText, XBuffer* aDest,
  int* aErrorCode, int* aErrorPos );

/* Creates a new path object described by path commands stored in aData. If
   aBoundingBox != 0, the parameter is used as array of 4 entries to track
   the x1,y1,x2,y2 coordinates of the bounding box surrounding the path.
   If there is no commands to process, no path is created and the function
   returns 0. */
static XPath* CreatePath( float aMatrix[6], const unsigned int* aData,
  float* aBoundingBox );

#endif /* EW_DONT_USE_PATH_FUNCTIONS */


/* Exclude SVG reader functionality? It includes the path string parsing */
#ifndef EW_DONT_USE_SVG_READER

/* XAtom represents a unique element id. The ids are collected while
   parsing the SVG document. To each id we associate a unique number. */
typedef struct _XAtom
{
  struct _XAtom*    Next;
  const XChar*      TextStart;
  const XChar*      TextEnd;
  int               Id;
} XAtom;


/* Searches in the atom list for an entry corresponding to the given text. If
   such entry already exists, returns its associated id. If the text is not
   yet stored in the list, adds to the list a new entry representing this text.
   If the operation failed due to memory shortage, the function returns 0. */
static int GetAtom( XAtom** aAtomList, const XChar* aTextStart,
  const XChar* aTextEnd );

/* Releases all entries existing in the list. */
static void FreeAtoms( XAtom** aAtomList );

/* This function parses an SVG document found in aText. If the function was
   successful, the function returns a value != 0. In error case the variables
   aErrorCode and aErrorPos describe the error and its position relative to
   the beginning of aText. */
static int ParseSVG( const XChar* aText, XBuffer* aDest,
  XAtom** aAtomList, int* aErrorCode, int* aErrorPos );

#endif /* EW_DONT_USE_SVG_READER */


/* Exclude path functionality? It includes the path string parsing */
#ifndef EW_DONT_USE_PATH_FUNCTIONS

/* This helper function skips over white space signs. Returns != 0 if at least
   one white space sign was found. */
static int SkipSpace( const XChar** aText );

#endif /* EW_DONT_USE_PATH_FUNCTIONS */


/* Exclude SVG functionality? */
#ifndef EW_DONT_USE_SVG_FUNCTIONS

/* Following data structure represents a single entry on the SVG state stack.
   It accumulates the state for the recently processed vector graphic element
   and its attributes. By evaluating this state corresponding drawing commands
   are executed. */
typedef struct _XSVGState
{
  struct _XSVGState*  Next;

  /* Drawing destination related parameters */
  XBitmap*            Dst;
  int                 DstFrameNo;
  XRect               ClipRect;
  XPoint              Offset;

  /* Id of the element belonging to the state or 0 if it is unknown */
  int                 IdAtom;

  /* Current transformation matrix */
  float               Matrix[6];

  /* Factors for percentage calculation */
  float               RangeHorz;
  float               RangeVert;
  float               RangeDiag;

  /* Common opacity and visibility */
  unsigned char       Opacity;
  char                Hidden;

  /* Values resulting from the 'fill' attribute */
  char                FillPaintMode;
  unsigned char       FillOpacity;
  XColor              FillColor;
  const unsigned int* FillGradient;

  /* Values resulting from the 'stroke' attribute */
  char                StrokePaintMode;
  unsigned char       StrokeOpacity;
  XColor              StrokeColor;
  const unsigned int* StrokeGradient;
  char                VectorEffect;

  /* Fill and stroke parameters */
  char                FillRule;
  char                StrokeLineJoin;
  char                StrokeLineCap;
  float               StrokeMiter;
  float               StrokeWidth;

  /* Values resulting from the color gradient stop */
  float               StopOffset;
  unsigned char       StopOpacity;
  XColor              StopColor;

  /* Gradient parameters */
  char                GradientUnits;
}
XSVGState;

/* The following function allocates memory for a new state and stores it in the
   state list aState. If successful returns a pointer to the new state. */
static XSVGState* PushState( XSVGState** aState );

/* The following function frees memory for the top most state and restores
   the preceding state. Returns a pointer to the new state. */
static XSVGState* PopState( XSVGState** aState );

/* Following function executes vector graphic instructions from the sequence
   starting at aPtr whereby the address space valid for access is limited to
   the range aStart..aEnd. Returns 0 if the operation has failed. */
static int ProcessSVGCommands( XColorGradient* aGradient, XPath* aPath,
  float* aBoundingBox, const unsigned int* aPtr, const unsigned int* aStart,
  const unsigned int* aEnd, XSVGState** aState, XColor aCurrentColor );

/* Searches in the memory aStart..aEnd for an element definitions matching the
   given aIdAtom and element type in range aElementFirst..aElementLast. The
   found element is thereupon returned. */
static const unsigned int* FindElementWithId( const unsigned int* aStart,
  const unsigned int* aEnd, int aIdAtom, int aElementFirst, int aElementLast );

/* Searches in the memory aStart..aEnd for style definitions matching elements
   with given aElement type, aIdAtom and aClassAtom. Found styles are thereupon
   executed and affect the current aState. Returns 0 if an error is occurred. */
static int ProcessCSS( XColorGradient* aGradient, XPath* aPath,
  float* aBoundingBox, const unsigned int* aStart, const unsigned int* aEnd,
  XSVGState** aState, XColor aCurrentColor, int aIdAtom, int aClassAtom,
  int aElement );

/* Counts the <stop> elements in the sequence starting with aPtr whereby the
   address space valid for access is limited to the range aStart..aEnd */
static int CountGradientStops( const unsigned int* aPtr,
  const unsigned int* aStart, const unsigned int* aEnd );

#endif /* EW_DONT_USE_SVG_FUNCTIONS */


/* Performance counter for performance investigation and debugging only */
EW_PERF_COUNTER( EwCreatePathFromSVGString,      Graphics_Engine_API )
EW_PERF_COUNTER( EwCreateSVGObjectFromSVGString, Graphics_Engine_API )
EW_PERF_COUNTER( EwLoadSVGObject,                Graphics_Engine_API )
EW_PERF_COUNTER( EwFreeSVGObject,                Graphics_Engine_API )
EW_PERF_COUNTER( EwCalcSizeOfSVGObject,          Graphics_Engine_API )
EW_PERF_COUNTER( EwDrawSVGObject,                Graphics_Engine_API )


/* Map the Graphics Engine API to the corresponding functions if no performance
   counters are active  */
#ifndef EW_PRINT_PERF_COUNTERS
  #define EwCreatePathFromSVGString_      EwCreatePathFromSVGString
  #define EwCreateSVGObjectFromSVGString_ EwCreateSVGObjectFromSVGString
  #define EwLoadSVGObject_                EwLoadSVGObject
  #define EwFreeSVGObject_                EwFreeSVGObject
  #define EwCalcSizeOfSVGObject_          EwCalcSizeOfSVGObject
  #define EwDrawSVGObject_                EwDrawSVGObject
#endif


/* Following are diverse modes used at the drawing time of the SVG content. */
#define FillRule_NonZero                              0
#define FillRule_EvenOdd                              1
#define GradientUnits_ObjectBoundingBox               0
#define GradientUnits_UserSpaceOnUse                  1
#define StrokeLineJoin_Miter                          0
#define StrokeLineJoin_Round                          1
#define StrokeLineJoin_Bevel                          2
#define StrokeLineCap_Butt                            0
#define StrokeLineCap_Round                           1
#define StrokeLineCap_Square                          2
#define PaintMode_None                                0
#define PaintMode_Color                               1
#define PaintMode_Gradient                            2
#define VectorEffect_None                             0
#define VectorEffect_NonScaling                       1


/*******************************************************************************
* FUNCTION:
*   EwInitSVG
*
* DESCRIPTION:
*   The function EwInitSVG() is called during the initialization of the
*   Graphics Engine. Its intention is to give the SVG module a chance to
*   initialize its private variables etc..
*
* ARGUMENTS:
*   aArgs - User argument passed in the EwInitGraphicsEngine().
*
* RETURN VALUE:
*   If successful, returns != 0.
*
*******************************************************************************/
int EwInitSVG( void* aArgs )
{
  EW_UNUSED_ARG( aArgs );

  /* Prepare performance counters */
  EwAddPerfCounter( EwCreatePathFromSVGString      );
  EwAddPerfCounter( EwCreateSVGObjectFromSVGString );
  EwAddPerfCounter( EwLoadSVGObject                );
  EwAddPerfCounter( EwFreeSVGObject                );
  EwAddPerfCounter( EwCalcSizeOfSVGObject          );
  EwAddPerfCounter( EwDrawSVGObject                );

  return 1;
}


/*******************************************************************************
* FUNCTION:
*   EwCreatePathFromSVGString
*
* DESCRIPTION:
*   The function EwCreatePathFromSVGString() creates a new path according to
*   SVG path instructions found in the passed aSVGString parameter.
*
* ARGUMENTS:
*   aSVGString - String containing the SVG instructions.
*   aScaleX,
*   aScaleY    - Scaling factor to apply on the original SVG coordinates. The
*     values affect also how smooth curves are composed from line segments.
*     The larger a curve the more segments are used.
*   aDeltaX,
*   aDeltaY    - Additional offset to add to the original SVG coordinates.
*     This results in a translation of the SVG path.
*   aAngle     - Additional angle to apply a rotation transformation on the
*     original SVG coordinates. The angle is expressed in degree and measured
*     clockwise relative to the positive X-axis. The rotation is performed
*     around the origin position (X:0, Y:0) of the original SVG coordinates.
*
* RETURN VALUE:
*   If successful, the function returns a pointer to the newly created path.
*   Otherwise the function returns 0. If the specified SVG string contains
*   errors, the function stops and returns the already prepared path without
*   evaluating further SVG data. The success of the operation or error status
*   can be queried by the functions EwGetSVGParserStatus() and
*   EwGetSVGParserErrorPos().
*
*******************************************************************************/
XPath* EwCreatePathFromSVGString_( XString aSVGString, XFloat aScaleX,
  XFloat aScaleY, XFloat aDeltaX, XFloat aDeltaY, XFloat aAngle )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    const XChar* ptr      = aSVGString;
    XBuffer      buffer   = { 0 };
    float        m[6]     = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
    XPath*       path;
    int          noOfSubPaths;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Assume, no errors */
    EwSVGParserStatus   = EW_SVG_PARSER_SUCCESS;
    EwSVGParserErrorPos = -1;

    /* At the beginning of the sequence are found two counters determining the
       number of following DWORDs as well as the number of enclosed sub-paths. */
    AppendUInt32( &buffer, 0 );
    AppendUInt32( &buffer, 0 );

    /* Try to parse the SVG string. This results in a sequence of EW_SVG_XXX
       opcodes */
    noOfSubPaths = ParseSVGPath( &ptr, &buffer, &EwSVGParserStatus,
                                 &EwSVGParserErrorPos );

    /* At least one sub-path created? */
    if ( !noOfSubPaths )
    {
      FreeBuffer( &buffer );
      return 0;
    }

    /* Update the number of DWORDs in the buffer */
    AlignBuffer( &buffer );
    buffer.Buffer[0] = (unsigned int)( buffer.Ptr - buffer.Buffer - 1 );
    buffer.Buffer[1] = (unsigned int)( noOfSubPaths );

    /* Translation, scaling and rotation factors to apply on all subsequent
       line and curve data. Initialize a transformation matrix. */
    if (( aDeltaX != 0.0f ) || ( aDeltaY != 0.0f ) ||
        ( aScaleX != 1.0f ) || ( aScaleY != 1.0f ) ||
        ( aAngle  != 0.0f ))
    {
      float  sin = EwMathSin( aAngle );
      float  cos = EwMathCos( aAngle );
      m[0] = cos * aScaleX; m[1] = -sin * aScaleY; m[2] = aDeltaX;
      m[3] = sin * aScaleX; m[4] =  cos * aScaleY; m[5] = aDeltaY;
    }

    /* Synthese from the parsed SVG string a path. Take in account the
       transformation matrix. */
    path = CreatePath( m, buffer.Buffer, 0 );

    /* Not enough memory for the path */
    if (( EwSVGParserStatus == EW_SVG_PARSER_SUCCESS ) && buffer.OutOfMemory )
    {
      EwSVGParserStatus   = EW_SVG_PARSER_OUT_OF_MEMORY;
      EwSVGParserErrorPos = -1;
    }

    /* Free the buffer storing the op-codes. */
    FreeBuffer( &buffer );

    /* Return the resulting path */
    return path;
  #else
    EW_UNUSED_ARG( aSVGString );
    EW_UNUSED_ARG( aScaleX );
    EW_UNUSED_ARG( aScaleY );
    EW_UNUSED_ARG( aDeltaX );
    EW_UNUSED_ARG( aDeltaY );
    EW_UNUSED_ARG( aAngle );
    EwError( 191 );
    return 0;
  #endif /* EW_DONT_USE_PATH_FUNCTIONS */
}


EW_INSTRUMENT_FUNC( EwCreatePathFromSVGString, XPath*, (  XString aSVGString,
  XFloat aScaleX, XFloat aScaleY, XFloat aDeltaX, XFloat aDeltaY, XFloat aAngle ),
  ( aSVGString, aScaleX, aScaleY, aDeltaX, aDeltaY, aAngle ))


/*******************************************************************************
* FUNCTION:
*   EwCreateSVGObjectFromSVGString
*
* DESCRIPTION:
*   The function EwCreateSVGObjectFromSVGString() evaluates aSVGString as XML
*   document containing description of a scalable vector graphic (SVG) and
*   returns an XSVGObject representing all relevant SVG elements and attributes
*   found in the passed SVG document. The returned object can then be used to
*   display the vector graphic by the function EwDrawSVGObject().
*
* ARGUMENTS:
*   aSVGString - String containing the SVG elements stored as XML document.
*
* RETURN VALUE:
*   If successful, the function returns a pointer to the newly created object.
*   In case of an error in the SVG string or in case of memory shortage, the
*   function fails returning 0. The success of the operation or error status
*   can then be queried by the functions EwGetSVGParserStatus() and
*   EwGetSVGParserErrorPos().
*
*******************************************************************************/
XSVGObject* EwCreateSVGObjectFromSVGString_( XString aSVGString )
{
  #ifndef EW_DONT_USE_SVG_READER
    XBuffer        buffer     = { 0 };
    XAtom*         atomList   = 0;
    XSVGCommands*  svgCommands;
    XSVGObject*    svgObject;
    int            count;
    int            errorCode;
    int            errorPos;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Reset the error status when parsing a new SVG content */
    EwSVGParserStatus   = EW_SVG_PARSER_SUCCESS;
    EwSVGParserErrorPos = -1;

    /* Any SVG data to process? If not, the SVG is empty. This is legal. */
    if ( !aSVGString || !*aSVGString )
    {
      EwSVGParserStatus = EW_SVG_PARSER_EMPTY_STRING;
      return 0;
    }

    /* First try to parse the SVG document. If failed, revert */
    if ( !ParseSVG( aSVGString, &buffer, &atomList, &errorCode, &errorPos ))
    {
      FreeBuffer( &buffer );
      FreeAtoms( &atomList );
      EwSVGParserStatus   = errorCode;
      EwSVGParserErrorPos = errorPos;
      return 0;
    }

    /* Successfully processed the SVG document. Release unnecessary memory */
    FreeAtoms( &atomList );

    /* How many DWORDs are occupied by the instructions and their operands? */
    count = (int)( buffer.Ptr - buffer.Buffer );

    /* Allocate a new data structure representing the instruction sequence */
    do
      svgObject = EwAlloc( sizeof( XSVGObject ) + sizeof( XSVGCommands ) +
                           count * sizeof( float ));
    while ( !svgObject && EwImmediateReclaimMemory( 61 ));

    /* Report a message if there is no more memory */
    if ( !svgObject )
    {
      FreeBuffer( &buffer );
      EwError( 61 );
      EwSVGParserStatus = EW_SVG_PARSER_OUT_OF_MEMORY;
      return 0;
    }

    /* Track the temporary used memory */
    EwResourcesMemory += sizeof( XSVGObject ) + sizeof( XSVGCommands ) +
                         count * sizeof( float );

    /* Also track the max. memory pressure */
    if ( EwResourcesMemory > EwResourcesMemoryPeak )
      EwResourcesMemoryPeak = EwResourcesMemory;

    if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
      EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

    /* Copy the instructions and free unused memory */
    svgCommands = (XSVGCommands*)( svgObject + 1 );
    svgCommands->Count = count;
    EwCopy( svgCommands->Data, buffer.Buffer, count * sizeof( float ));
    FreeBuffer( &buffer );

    /* Complete the SVG object */
    svgObject->Commands = svgCommands;
    svgObject->IsConst  = 0;

    return svgObject;
  #else
    EW_UNUSED_ARG( aSVGString );
    EwError( 511 );
    return 0;
  #endif /* EW_DONT_USE_SVG_READER */
}


/* Wrapper function if performance counters are enabled */
EW_INSTRUMENT_FUNC( EwCreateSVGObjectFromSVGString, XSVGObject*,
  ( XString aSVGString ), ( aSVGString ))


/*******************************************************************************
* FUNCTION:
*   EwLoadSVGObject
*
* DESCRIPTION:
*   The function EwLoadSVGObject() creates a new SVG object and loads it with
*   the content of the passed SVG resource.
*
* ARGUMENTS:
*   aResource - Descriptor of the SVG resource to load. The content of this
*     descriptor depends on the particular platform system.
*
* RETURN VALUE:
*   If sucessful, the function returns a new SVG object initialized with the
*   content of the resource. If failed, the function returns null.
*
*******************************************************************************/
XSVGObject* EwLoadSVGObject_( const struct XSVGRes* aResource )
{
  #ifndef EW_DONT_USE_SVG_FUNCTIONS
    void*               handle;
    const XSVGCommands* commands;
    XSVGObject*         svgObject;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Couldn't open the SVG resource */
    if ( !aResource || (( handle = EwSVGOpen( aResource )) == 0 ))
    {
      EwErrorPD( 501, aResource, 0 );
      return 0;
    }

    /* Query the SVG commands */
    if ( !EwSVGGetConstData( handle, &commands ))
    {
      EwSVGClose( handle );
      EwErrorPD( 502, aResource, 0 );
      return 0;
    }

    /* Close the resource */
    EwSVGClose( handle );

    /* Allocate a new data structure representing the SVG object */
    do
      svgObject = EwAlloc( sizeof( XSVGObject ));
    while ( !svgObject && EwImmediateReclaimMemory( 62 ));

    /* Report a message if there is no more memory */
    if ( !svgObject )
    {
      EwError( 62 );
      return 0;
    }

    /* Complete the initialization of the SVG object */
    svgObject->Commands = commands;
    svgObject->IsConst  = 1;

    /* Track the temporary used memory */
    EwResourcesMemory += sizeof( XSVGObject );

    /* Also track the max. memory pressure */
    if ( EwResourcesMemory > EwResourcesMemoryPeak )
      EwResourcesMemoryPeak = EwResourcesMemory;

    if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
      EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

    return svgObject;
  #else
    EW_UNUSED_ARG( aResource );
    EwError( 512 );
    return 0;
  #endif /* EW_DONT_USE_SVG_FUNCTIONS */
}


/* Wrapper function if performance counters are enabled */
EW_INSTRUMENT_FUNC( EwLoadSVGObject, XSVGObject*,
  ( const struct XSVGRes* aResource ), ( aResource ))


/*******************************************************************************
* FUNCTION:
*   EwFreeSVGObject
*
* DESCRIPTION:
*   The function EwFreeSVGObject() frees the memory occupied by the SVG object.
*
* ARGUMENTS:
*   aSVGObject - Pointer to the SVG object to free.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwFreeSVGObject_( XSVGObject* aSVGObject )
{
  #ifndef EW_DONT_USE_SVG_FUNCTIONS
    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Ensure the given aSVGObject is still valid */
    if ( !aSVGObject || !aSVGObject->Commands )
      return;

    /* Track the RAM usage */
    EwResourcesMemory -= sizeof( XSVGObject );

    /* Are the SVG commands stored locally together with the SVG object? */
    if ( !aSVGObject->IsConst )
    {
      EwResourcesMemory -= sizeof( XSVGCommands );
      EwResourcesMemory -= aSVGObject->Commands->Count * sizeof( float );
    }

    /* Free the memory */
    aSVGObject->Commands = 0;
    EwFree( aSVGObject );
  #else
    EW_UNUSED_ARG( aSVGObject );
    EwError( 513 );
  #endif /* EW_DONT_USE_SVG_FUNCTIONS */
}


/* Wrapper function if performance counters are enabled */
EW_INSTRUMENT_VOID_FUNC( EwFreeSVGObject, ( XSVGObject* aSVGObject ),
  ( aSVGObject ))


/*******************************************************************************
* FUNCTION:
*   EwGetSVGParserStatus
*
* DESCRIPTION:
*   The function EwGetSVGParserStatus() returns the status resulting from the
*   preceding invocation of the function EwCreatePathFromSVGString(). Possible
*   values are defined in the macros EW_SVG_PARSER_XXX.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   Returns EW_SVG_PARSER_SUCCESS if the parsed SVG string did not contain any
*   errors. Otherwise another value defined in EW_SVG_PARSER_XXX is returned.
*   In such case use the function EwGetSVGParserErrorPos() to get the position
*   within the parsed SVG string, which has raised the error status.
*
*******************************************************************************/
int EwGetSVGParserStatus( void )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    return EwSVGParserStatus;
  #else
    return EW_SVG_PARSER_SUCCESS;
  #endif
}


/*******************************************************************************
* FUNCTION:
*   EwGetSVGParserErrorPos
*
* DESCRIPTION:
*   The function EwGetSVGParserErrorPos() returns the position within the SVG
*   string at which the function EwCreatePathFromSVGString() has encountered an
*   error. To query the error status use the function EwGetSVGParserStatus().
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   Returns the position (in characters) within the SVG string starting with 0
*   for the first character. In the case there is no error recorded, a value -1
*   is returned.
*
*******************************************************************************/
XInt32 EwGetSVGParserErrorPos( void )
{
  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    return EwSVGParserErrorPos;
  #else
    return -1;
  #endif
}


/*******************************************************************************
* FUNCTION:
*   EwCalcSizeOfSVGObject
*
* DESCRIPTION:
*   The function EwCalcSizeOfSVGObject() estimates the pixel size of the vector
*   graphic so that it fits inside the specified area aViewSize. This operation
*   respects the aspect ratio and size constraints of the first SVG element
*   inside aSVGObject.
*
*   Please note, the SVG content may override the value aViewSize resulting in
*   an area smaller or larger than aViewSize.
*
* ARGUMENTS:
*   aSVGObject - Pointer to the SVG object to estimate its pixel size.
*   aViewSize  - Default area to render the vector graphic inside it. It
*     corresponds to the denomination 'viewport' from SVG specification.
*
* RETURN VALUE:
*   Returns the estimated size of the vector graphic in pixel so it fits inside
*   aViewSize. If there is no content to display, the function returns an empty
*   size <0,0>.
*
*******************************************************************************/
XPoint EwCalcSizeOfSVGObject_( XSVGObject* aSVGObject, XPoint aViewSize )
{
  const static XPoint nullSize = { 0, 0 };

  #ifndef EW_DONT_USE_SVG_FUNCTIONS
    int                 useReader;
    const unsigned int* ptr;
    const unsigned int* end;
    unsigned int        instQuad;
    int                 instCount  = 0;
    char                unit       = Unit_None;
    float               vpWidth    = (float)aViewSize.X;
    float               vpHeight   = (float)aViewSize.Y;
    float               width      = vpWidth;
    float               height     = vpHeight;
    float               vbWidth    = 0.0f;
    float               vbHeight   = 0.0f;
    int                 isSVG      = 0;
    int                 viewBoxSet = 0;

    /* Perform check operations to detect when the code is running out the CPU
       stack or it is executed in context of a foreign task other than the task
       used by the Embedded Wizard application. */
    EW_CHECK_THREAD_CONTEXT

    /* Ensure the given aSVGObject is valid */
    if ( !aSVGObject || !aSVGObject->Commands )
      return nullSize;

    /* Is the resource content directly accessible? If not, use reader 
       interface. */
    useReader = USE_FLASH_READER( aSVGObject->Commands );

    ptr      = aSVGObject->Commands->Data;
    end      = ptr + UINT32( &aSVGObject->Commands->Count );
    instQuad = UINT32( ptr++ );

    /* Process the instructions */
    while ( ptr < end )
    {
      int inst = ( instQuad >> ( instCount * 8 )) & 0xFF;

      /* Expect SVG definition to be the first one */
      if ( !isSVG && ( inst != EW_SVG_EnterSVG ))
        return nullSize;

      /* All attributes belonging to an SVG element have been evaluated. Now the
         size of the image can be estimated. */
      if ( isSVG && ( inst >= EW_SVG_EnterG ) && ( inst <= EW_SVG_EnterStyle ))
      {
        /* The content has an area = 0 */
        if (( width <= 0.0f ) || ( height <= 0.0f ))
          return nullSize;

        /* View-Box is empty - nothing to draw */
        if ( viewBoxSet && (( vbWidth <= 0.0f ) || ( vbHeight <= 0.0f )))
          return nullSize;

        /* If view box is configured, it determines the aspect ratio of the image. */
        if ( viewBoxSet )
        {
          float scaleX = width  / vbWidth;
          float scaleY = height / vbHeight;

          if ( scaleX > scaleY ) scaleX = scaleY;
          if ( scaleY > scaleX ) scaleY = scaleX;

          width  = vbWidth  * scaleX;
          height = vbHeight * scaleY;
        }

        return EwNewPoint((int)( width + 0.5f ), (int)( height + 0.5f ));
      }

      /* Entering an SVG instruction detected. Remember this state. */
      if ( inst == EW_SVG_EnterSVG )
        isSVG = 1;

      /* Process instructions controlling the size of the image values. Accumulate
         all values. */
      switch ( inst )
      {
        case EW_SVG_SetUnitPercentage :
          unit   = Unit_Percent;
        break;
        case EW_SVG_SetWidth :
          width  = ( unit == Unit_Percent )? FLOAT( ptr++ ) * vpWidth :
                                             FLOAT( ptr++ );
        break;
        case EW_SVG_SetHeight :
          height = ( unit == Unit_Percent )? FLOAT( ptr++ ) * vpHeight :
                                             FLOAT( ptr++ );
        break;
        case EW_SVG_SetViewBox :
          if (( ptr += 4 ) < end )
          {
            vbWidth    = FLOAT( ptr - 2 );
            vbHeight   = FLOAT( ptr - 1 );
            viewBoxSet = 1;
          }
        break;
      }

      /* After the instruction is processed - restore the default unit */
      if ( inst != EW_SVG_SetUnitPercentage )
        unit = Unit_None;

      /* Get the op-code for the next instruction */
      if (( ++instCount == 4 ) && ( ptr < end ))
      {
        instCount = 0;
        instQuad  = UINT32( ptr++ );
      }
    }

    return nullSize;
  #else
    EW_UNUSED_ARG( aSVGObject );
    EW_UNUSED_ARG( aViewSize );
    EwError( 514 );
    return nullSize;
  #endif /* EW_DONT_USE_SVG_FUNCTIONS */
}


/* Wrapper function if performance counters are enabled */
EW_INSTRUMENT_FUNC( EwCalcSizeOfSVGObject, XPoint, ( XSVGObject* aSVGObject,
  XPoint aViewSize ), ( aSVGObject, aViewSize ))


/*******************************************************************************
* FUNCTION:
*   EwDrawSVGObject
*
* DESCRIPTION:
*   The function EwDrawSVGObject() interprets the commands stored in aSVGObject
*   and renders it as scalable vector graphic inside the aClipRect area of the
*   bitmap aDst. aClipRect determines a clipping area to limit the operation.
*   All pixel lying outside this area will not be drawn.
*
*   The components aMatrixA..aMatrixF specify a transformation to apply on the
*   original coordinates from aSVGObject. In this manner the vector graphic can
*   be scaled, rotated and the position of the graphic inside the destination
*   bitmap can be determined.
*
* ARGUMENTS:
*   aDst          - Destination bitmap.
*   aSVGObject    - SVG object containing drawing instructions for the vector
*     graphic.
*   aDstFrameNo   - Frame within the destination bitmap affected by the drawing
*     operation.
*   aClipRect     - Area to limit the drawing operation (Relative to the top-
*     left corner of the destination bitmap frame).
*   aViewSize     - Default area to render the vector graphic inside it. It
*     corresponds to the denomination 'viewport' from SVG specification.
*   aMatrixA ..
*   aMatrixF      - Components of a matrix describing a transformation for the
*     displayed vector graphic.
*   aCurrentColor - Color value to use wherever 'current-color' is used in the
*     original SVG.
*   aFillColor    - Default color value for the fill painting if no 'fill' 
*     attribute is defined in the SVG document.
*   aStrokeColor  - Default color value for the stroke painting if no 'stroke'
*     attribute is defined in the SVG document.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwDrawSVGObject_( XBitmap* aDst, XSVGObject* aSVGObject, XInt32 aDstFrameNo,
  XRect aClipRect, XPoint aViewSize, XFloat aMatrixA, XFloat aMatrixB,
  XFloat aMatrixC, XFloat aMatrixD, XFloat aMatrixE, XFloat aMatrixF,
  XColor aCurrentColor, XColor aFillColor, XColor aStrokeColor )
{
  #ifndef EW_DONT_USE_SVG_FUNCTIONS
    XSVGState*          state = 0;
    int                 useReader;
    const unsigned int* ptr;
    const unsigned int* end;

    /* Push the initial state */
    PushState( &state );

    /* Assign the drawing destimation related parameters to the state */
    state->Dst        = aDst;
    state->DstFrameNo = aDstFrameNo;
    state->ClipRect   = aClipRect;

    /* Initialize the state with default color values */
    state->FillColor       = aFillColor;
    state->StrokeColor     = aStrokeColor;
    state->FillPaintMode   = ( aFillColor.  Alpha )? PaintMode_Color : PaintMode_None;
    state->StrokePaintMode = ( aStrokeColor.Alpha )? PaintMode_Color : PaintMode_None;

    state->RangeHorz = (float)( aViewSize.X );
    state->RangeVert = (float)( aViewSize.Y );
    state->RangeDiag = EwMathSqrt(( state->RangeHorz * state->RangeHorz ) +
                                  ( state->RangeVert * state->RangeVert )) /
                                    1.4142136f;

    /* Setup the initial state of the transformation matrix */
    state->Matrix[0] = aMatrixA; state->Matrix[1] = aMatrixB;
    state->Matrix[2] = aMatrixC; state->Matrix[3] = aMatrixD;
    state->Matrix[4] = aMatrixE; state->Matrix[5] = aMatrixF;

    /* Is the resource content directly accessible? If not, use reader 
       interface. */
    useReader = USE_FLASH_READER( aSVGObject->Commands );
    ptr       = aSVGObject->Commands->Data;
    end       = ptr + UINT32( &aSVGObject->Commands->Count );

    /* Execute the drawing commands */
    ProcessSVGCommands( 0, 0, 0, ptr, ptr, end, &state, aCurrentColor );

    /* Restore the stack */
    while ( PopState( &state ))
      ;
  #else
    EW_UNUSED_ARG( aDst          );
    EW_UNUSED_ARG( aSVGObject    );
    EW_UNUSED_ARG( aDstFrameNo   );
    EW_UNUSED_ARG( aClipRect     );
    EW_UNUSED_ARG( aViewSize     );
    EW_UNUSED_ARG( aMatrixA      );
    EW_UNUSED_ARG( aMatrixB      );
    EW_UNUSED_ARG( aMatrixC      );
    EW_UNUSED_ARG( aMatrixD      );
    EW_UNUSED_ARG( aMatrixE      );
    EW_UNUSED_ARG( aMatrixF      );
    EW_UNUSED_ARG( aCurrentColor );
    EW_UNUSED_ARG( aFillColor );
    EW_UNUSED_ARG( aStrokeColor );
    EwError( 515 );
  #endif /* EW_DONT_USE_SVG_FUNCTIONS */
}


/* Wrapper function if performance counters are enabled */
EW_INSTRUMENT_VOID_FUNC( EwDrawSVGObject, ( XBitmap* aDst,
  XSVGObject* aSVGObject, XInt32 aDstFrameNo, XRect aClipRect, XPoint aViewSize,
  XFloat aMatrixA, XFloat aMatrixB, XFloat aMatrixC, XFloat aMatrixD,
  XFloat aMatrixE, XFloat aMatrixF, XColor aCurrentColor, XColor aFillColor,
  XColor aStrokeColor ),
  ( aDst, aSVGObject, aDstFrameNo, aClipRect, aViewSize, aMatrixA, aMatrixB,
    aMatrixC, aMatrixD, aMatrixE, aMatrixF, aCurrentColor, aFillColor,
    aStrokeColor ))


/* Exclude path functionality? It includes the path string parsing */
#ifndef EW_DONT_USE_PATH_FUNCTIONS

/* This function ensures, that the given buffer has enought space for up to
   aCount additional DWORDs. If not, the buffer will grow. The function returns
   a value != 0, if the required DWORDs can be written into the buffer. If the
   growing is failed, the function sets the flag 'OutOfMemory' in the buffer and
   returns 0 */
static int RequireBuffer( XBuffer* aBuffer, int aCount )
{
  /* Memory allocation for the buffer is already failed */
  if ( aBuffer->OutOfMemory )
    return 0;

  /* Check, whether there is space for aCount DWORDs */
  if (( aBuffer->Size - ( aBuffer->Ptr - aBuffer->Buffer )) < aCount )
  {
    int           tmpSize   = (int)( aBuffer->Ptr - aBuffer->Buffer );
    int           newSize   = tmpSize + aCount;
    unsigned int* oldBuffer = aBuffer->Buffer;
    unsigned int* tmpBuffer = oldBuffer;
    unsigned int* newBuffer = 0;

    /* Calculate the size of the new buffer - align it to the next 1kB
       border. */
    newSize  += 256 - ( newSize % 256 );

    /* Then try to allocate memory for this new buffer. */
    do
      newBuffer = EwAlloc( newSize * sizeof( unsigned int ));
    while ( !newBuffer && EwImmediateReclaimMemory( 63 ));

    /* Report a message if there is no more memory */
    if ( !newBuffer )
    {
      EwError( 63 );
      aBuffer->OutOfMemory++;
      return 0;
    }

    /* Track the temporary used memory */
    EwResourcesMemory += newSize * sizeof( unsigned int );

    /* Also track the max. memory pressure */
    if ( EwResourcesMemory > EwResourcesMemoryPeak )
      EwResourcesMemoryPeak = EwResourcesMemory;

    if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
      EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

    EwResourcesMemory -= aBuffer->Size * sizeof( unsigned int );

    /* Ok, store the pointer to the new buffer */
    aBuffer->Buffer   = newBuffer;
    aBuffer->Ptr     += newBuffer - oldBuffer;
    aBuffer->Size     = newSize;

    /* ... adjust the pointert to the DWORD containing actually composed
       commands quad ... */
    if ( aBuffer->InstPtr )
      aBuffer->InstPtr += newBuffer - oldBuffer;

    /* ... and copy the old content to this new buffer */
    EwMove( newBuffer, oldBuffer, tmpSize * sizeof( unsigned int ));

    /* Release the old buffer */
    if ( tmpBuffer )
      EwFree( tmpBuffer );
  }

  /* Ok - the dwords may be written into the buffer */
  return 1;
}


/* This function frees the buffer and it's entire content */
static void FreeBuffer( XBuffer* aBuffer )
{
  /* Release the buffer's content */
  if ( aBuffer->Buffer )
  {
    EwFree( aBuffer->Buffer );
    EwResourcesMemory -= aBuffer->Size * sizeof( unsigned int );
  }
}

#endif /* EW_DONT_USE_PATH_FUNCTIONS */


/* Exclude SVG reader? */
#ifndef EW_DONT_USE_SVG_READER

/* Remembers the buffer state. This state can be used later to restore the
   buffer if e.g. an operation is failed. */
static void SaveBuffer( XBuffer* aBuffer, XBuffer* aState )
{
  *aState = *aBuffer;
}


/* Restores the previously stored state of the buffer. */
static void RestoreBuffer( XBuffer* aBuffer, XBuffer* aState )
{
  aBuffer->Ptr = aBuffer->Buffer + ( aState->Ptr - aState->Buffer );

  if ( aState->InstPtr )
    aBuffer->InstPtr = aBuffer->Buffer + ( aState->InstPtr - aState->Buffer );
  else
    aBuffer->InstPtr = 0;

  aBuffer->InstCount = aState->InstCount;

  if ( aBuffer->InstPtr )
  {
    if ( aBuffer->InstCount == 3 ) *aBuffer->InstPtr &= 0x00FFFFFF;
    if ( aBuffer->InstCount == 2 ) *aBuffer->InstPtr &= 0x0000FFFF;
    if ( aBuffer->InstCount == 1 ) *aBuffer->InstPtr &= 0x000000FF;
    if ( aBuffer->InstCount == 0 ) *aBuffer->InstPtr &= 0x00000000;
  }
}

#endif /* EW_DONT_USE_SVG_READER */


/* Exclude path functionality? It includes the path string parsing */
#ifndef EW_DONT_USE_PATH_FUNCTIONS

/* Stores the given command in aBuffer. If necessary the buffer is enlarged
   to accomodate the new data. */
static void AppendInstruction( XBuffer* aBuffer, int aInstruction )
{
  /* Does need to allocate a new command quad? */
  if ( !aBuffer->InstPtr && !RequireBuffer( aBuffer, 1 ))
    return;

  /* Initialize a new quad with 0 (4 x End command) */
  if ( !aBuffer->InstPtr )
  {
    aBuffer->InstPtr    = aBuffer->Ptr++;
    aBuffer->InstPtr[0] = 0;
    aBuffer->InstCount  = 0;
  }

  /* Append the command to the command quad */
  *aBuffer->InstPtr |= ( aInstruction & 0xFF ) << ( aBuffer->InstCount++ * 8 );

  /* Quad is full? */
  if ( aBuffer->InstCount == 4 )
    aBuffer->InstPtr = 0;
}


/* Stores the given data value in aBuffer. If necessary the buffer is enlarged
   to accomodate the new data. */
static void AppendFloat( XBuffer* aBuffer, float aValue )
{
  if ( !RequireBuffer( aBuffer, 1 ))
    return;

  /* Store the value at the next free entry in the buffer */
  *(float*)aBuffer->Ptr++ = aValue;
}


/* Stores the given data value in aBuffer. If necessary the buffer is enlarged
   to accomodate the new data. Returns != 0 if successful. If there is no memory
   to enlarge the buffer, returns 0. */
static void AppendUInt32( XBuffer* aBuffer, unsigned int aValue )
{
  if ( !RequireBuffer( aBuffer, 1 ))
    return;

  /* Store the value at the next free entry in the buffer */
  *aBuffer->Ptr++ = aValue;
}


#endif /* EW_DONT_USE_PATH_FUNCTIONS */


/* Exclude path functionality? It includes the path string parsing */
#ifndef EW_DONT_USE_PATH_FUNCTIONS

/* Appends additional 'no operation' op-codes to completely fill the current
   commands quad. It should ensure that the next command starts at the
   next free dword. */
static void AlignBuffer( XBuffer* aBuffer )
{
  aBuffer->InstPtr = 0;
}

#endif


/* Helper macro to test whether the operand is a white-space sign. */
#define IsSpaceChar( aChar )                                                   \
  (((aChar) ==  ' ' ) || ((aChar) == '\t' ) || ((aChar) == '\n' ) ||           \
   ((aChar) == '\r' ))

/* Helper macro to test whether the operand is an 'A' .. 'Z' sign. */
#define IsAlphaChar( aChar )                                                   \
   ((((aChar) >= 'A' ) && ((aChar) <= 'Z' )) ||                                \
    (((aChar) >= 'a' ) && ((aChar) <= 'z' )))

/* Helper macro to test whether the operand is a digit sign. */
#define IsDigitChar( aChar )                                                   \
  (((aChar) >= '0' ) && ((aChar) <= '9' ))

/* Helper macro to test whether the operand is a hex. digit sign. */
#define IsXDigitChar( aChar )                                                  \
  ( IsDigitChar( aChar ) ||                                                    \
   (((aChar) >= 'A' ) && ((aChar) <= 'F' )) ||                                 \
   (((aChar) >= 'a' ) && ((aChar) <= 'f' )))

/* Helper macro to test whether the operand is a name starting sign. We limit
   the names to ASCII signs. In fact, XML is more generous concerning the
   suppported code range. */
#define IsNameStartChar( aChar )                                               \
  ( IsAlphaChar( aChar ) || ((aChar) == '_' ))

/* Helper macro to test whether the operand is a name sign. We limit the names
   to ASCII signs. In fact, XML is more generous concerning the suppported code
   range. */
#define IsNameChar( aChar )                                                    \
  ( IsNameStartChar( aChar ) || IsDigitChar( aChar ) ||                        \
  ((aChar) == '-' ) || ((aChar) == '.' ))


/* Exclude SVG reader */
#ifndef EW_DONT_USE_SVG_READER

/* Helper function to convert a hex. digit in a dec. value. */
static int Hex2Dec( XChar aChar )
{
  if (( aChar >= '0' ) && ( aChar <= '9' )) return aChar - '0';
  if (( aChar >= 'A' ) && ( aChar <= 'F' )) return aChar - 'A' + 10;
  if (( aChar >= 'a' ) && ( aChar <= 'f' )) return aChar - 'a' + 10;
  return 0;
}


/* This helper function compares the given text fragment with a list of text
   fragments (tokens). If a match is found, return the index of the found entry
   or -1 if no entry is found. The array with tokens is zero terminated. */
static int FindToken( const XChar* aTextStart, const XChar* aTextEnd,
  const char** aTokens )
{
  const char** tokens = aTokens;

  /* Process all entries in the array */
  for ( ; *tokens; tokens++ )
  {
    const XChar* text  = aTextStart;
    const char*  token = *tokens;

    /* Compare the token */
    for ( ; ( text < aTextEnd ) && ( *text == *token ); text++, token++ )
      ;

    /* Is the text completely evaluated? */
    if (( text == aTextEnd ) && !*token )
      return (int)( tokens - aTokens );
  }

  return -1;
}

#endif /* EW_DONT_USE_SVG_RAEDER */


/* Exclude path functionality? It includes the path string parsing */
#ifndef EW_DONT_USE_PATH_FUNCTIONS

/* This helper function skips over white space signs. Returns != 0 if at least
   one white space sign was found. */
static int SkipSpace( const XChar** aText )
{
  const XChar* ptr = *aText;

  /* At least one white space sign? */
  if ( !IsSpaceChar( *ptr ))
    return 0;

  /* Skip over the white space signs */
  do
    ptr++;
  while ( IsSpaceChar( *ptr ));

  *aText = ptr;
  return 1;
}


/* This helper function skips over comma-white space signs. Returns ',' if at
   least one comma sign was found. If only ' ' was found returtns ' '. */
static int SkipCommaSpace( const XChar** aText )
{
  const XChar* ptr   = *aText;
  int          comma = 0;

  /* At least one white space or comma sign? */
  if ( !IsSpaceChar( *ptr ) && ( *ptr != ',' ))
    return 0;

  /* Skip over the white space signs */
  while ( IsSpaceChar( *ptr ))
    ptr++;

  /* Skip over the comma sign */
  if ( *ptr == ',' )
  {
    ptr++;
    comma = 1;
  }

  /* Skip over the white space signs */
  while ( IsSpaceChar( *ptr ))
    ptr++;

  *aText = ptr;
  return comma? ',' : ' ';
}

#endif /* EW_DONT_USE_PATH_FUNCTIONS */


/* Exclude SVG reader functionality  */
#ifndef EW_DONT_USE_SVG_READER

/* This helper function compares the text with the given name. If equal, the
   function skips over the name and returns != 0. */
static int SkipName( const XChar** aText, const char* aName )
{
  const XChar* ptr = *aText;

  /* Compare the name */
  for ( ; *aName && ( *ptr == *aName ); aName++, ptr++ )
    ;

  /* Is the name completely evaluated? */
  if ( *aName || IsNameChar( *ptr ))
    return 0;

  *aText = ptr;
  return 1;
}


/* This helper function tries to parse an unsigned integer number literal found
   in the string aText and stored in hex.dec. notation. If the function was
   successful, the number is stored in the parameter aNumber and the function
   returns a value != 0.  */
static int ParseHex( const XChar** aText, unsigned int* aNumber )
{
  const XChar* ptr   = *aText;
  unsigned int num = 0;

  /* Not a number */
  if ( !IsXDigitChar( *ptr ))
    return 0;

  /* Process digits */
  for ( ; IsXDigitChar( *ptr ); ptr++ )
    num = ( num << 4 ) + (unsigned int)Hex2Dec( *ptr );

  *aText   = ptr;
  *aNumber = num;
  return 1;
}

#endif /* EW_DONT_USE_SVG_READER */


/* Exclude path functionality? It includes the path string parsing */
#ifndef EW_DONT_USE_PATH_FUNCTIONS

/* This helper function tries to parse a real number literal found in the string
   aText. If the function was successful, the number is stored in the parameter
   aNumber and the function returns a value != 0.  */
static int ParseReal( const XChar** aText, float* aNumber )
{
  const XChar* start = *aText;
  const XChar* ptr   = start;
  XFloat num         = 0.0f;
  XFloat exp         = 0.1f;
  int    count       = 0;
  int    sign        = 1;

  /* Evaluate the +/- sign */
  if (( *ptr == '+' ) || ( *ptr == '-' ))
    sign = ( *ptr++ == '-' )? -1 : 1;

  /* Skip over leading digits */
  while (( *ptr >= '0'  ) && ( *ptr <= '9' ))
  {
    num = num * 10.0f + (XFloat)( *ptr++ - '0' );
    count++;
  }

  /* Skip over the period sign  */
  if ( *ptr == '.' )
    ptr++;

  /* Skip over following digits */
  while (( *ptr >= '0'  ) && ( *ptr <= '9' ))
  {
    num += exp * (XFloat)( *ptr++ - '0' );
    exp *= 0.1f;
    count++;
  }

  /* No valid number found */
  if ( !count )
  {
    *aText = start;
    return 0;
  }

  /* scientific notation e^x ? */
  if (( *ptr == 'e' ) || ( *ptr == 'E' ))
  {
    int    eSign  = 1;
    XFloat eNum   = 0.0f;
    int    eCount = 0;

    /* Skip over the 'e' sign */
    ptr++;

    /* Evaluate the +/- sign */
    if (( *ptr == '+' ) || ( *ptr == '-' ))
      eSign = ( *ptr++ == '-' )? -1 : 1;

    /* Skip over digits */
    while (( *ptr >= '0'  ) && ( *ptr <= '9' ))
    {
      eNum = eNum * 10.0f + (XFloat)( *ptr++ - '0' );
      eCount++;
    }

    /* No valid number found */
    if ( !eCount )
    {
      *aText = start;
      return 0;
    }

    /* Calculate the exponent part */
    num = num * EwMathPow( 10.0f, ( eSign < 0 )? -eNum : eNum );
  }

  /* Retun the parsed number */
  *aText   = ptr;
  *aNumber = ( sign < 0 )? -num : num;
  return 1;
}

#endif /* EW_DONT_USE_PATH_FUNCTIONS */


/* Exclude SVG reader functionality  */
#ifndef EW_DONT_USE_SVG_READER

/* This helper function tries to parse a color literal in the syntax #RGB, #RGBA
   #RRGGBB or #RRGGBBAA found in aText. If the function was successful, the RGB
   values are stored in the parameter aColor in the order ARGB and the function
   returns a value != 0. */
static int ParseColorLiteral( const XChar** aText, unsigned int* aColor )
{
  const    XChar* ptr = *aText;
  unsigned int    clr = 0;
  unsigned char   r, g, b, a;

  /* Not hex. notation? */
  if ( *ptr != '#' )
    return 0;

  /* Skip over '#' sign */
  ptr++;

  if ( !ParseHex( &ptr, &clr ))
    return 0;

  /* Three hex-digit notation #RGB */
  if (( ptr - *aText ) == 4 )
  {
    r = (unsigned char)(( clr >> 8 ) & 0xF ); r |= r << 4;
    g = (unsigned char)(( clr >> 4 ) & 0xF ); g |= g << 4;
    b = (unsigned char)(( clr >> 0 ) & 0xF ); b |= b << 4;
    a = 255;
  }

  /* Four hex-digit notation #RGBA */
  else if (( ptr - *aText ) == 5 )
  {
    r = (unsigned char)(( clr >> 12 ) & 0xF ); r |= r << 4;
    g = (unsigned char)(( clr >>  8 ) & 0xF ); g |= g << 4;
    b = (unsigned char)(( clr >>  4 ) & 0xF ); b |= b << 4;
    a = (unsigned char)(( clr >>  0 ) & 0xF ); a |= a << 4;
  }

  /* Six hex-digit notation #RRGGBB */
  else if (( ptr - *aText ) == 7 )
  {
    r = (unsigned char)( clr >> 16 );
    g = (unsigned char)( clr >> 8 );
    b = (unsigned char)( clr >> 0 );
    a = 255;
  }

  /* Eight hex-digit notation #RRGGBBAA */
  else if (( ptr - *aText ) == 9 )
  {
    r = (unsigned char)( clr >> 24 );
    g = (unsigned char)( clr >> 16);
    b = (unsigned char)( clr >>  8 );
    a = (unsigned char)( clr >>  0 );
  }

  else
    return 0;

  *aColor = ( a << 24 ) | ( r << 16 ) | ( g << 8 ) | b;
  *aText  = ptr;
  return 1;
}


/* This helper function tries to parse an rgb( ... ) and rgba() expression
   found in aText. If the function was successful, the RGB values are stored
   in the parameter aColor in the order ARGB and the function returns a
   value != 0. */
static int ParseRGBFunc( const XChar** aText, unsigned int* aColor )
{
  const XChar*  ptr      = *aText;
  int           noOfOps  = 0;
  float         ops[4];
  int           isRGB    = 0;
  int           isRGBA   = 0;
  int           expectOp = 0;
  int           i;
  unsigned char r, g, b, a;

  if      ( SkipName( &ptr, "rgb("  )) isRGB  = 1;
  else if ( SkipName( &ptr, "rgba(" )) isRGBA = 1;

  /* 'rgb(' or 'rgba(' as starting sequence? */
  if ( !isRGB && !isRGBA )
    return 0;

  /* Up to four operands for RGBA values */
  while ( noOfOps < 4 )
  {
    /* Skip over white space */
    SkipSpace( &ptr );

    /* No value for the cooor component? Assume 0 */
    if ( SkipName( &ptr, "none" ))
    {
      ops[ noOfOps++ ] = 0.0f;
      expectOp = 0;
    }

    /* ... otherwise a number is expected */
    else if ( ParseReal( &ptr, &ops[ noOfOps ]))
    {
      /* Percent notation for RGB values - not ALPHA! */
      if (( *ptr == '%' ) && ( noOfOps < 3 ))
      {
        ops[ noOfOps ] *= 2.55f;
        ptr++;
      }

      noOfOps++;
      expectOp = 0;
    }

    else
      break;

    SkipSpace( &ptr );

    /* Separate the operands by optional ','. The alpha operand can be separated
       by a '/' sign */
    if (( *ptr == ',' ) || (( noOfOps == 3 ) && ( *ptr == '/' )))
    {
      expectOp = 1;
      ptr++;
    }
  }

  /* Closing ')' sign expected */
  if ( *ptr != ')' )
    return 0;

  /* Missing operand after ',' or '/' */
  if ( expectOp )
    return 0;

  /* rgb() expects at leats three operands */
  if ( isRGB && ( noOfOps < 3 ))
    return 0;

  /* rgba() expects exact four operands */
  if ( isRGBA && ( noOfOps != 4 ))
    return 0;

  /* Clamp the values */
  for ( i = 0; i < noOfOps; i++ )
  {
    if ( ops[i] > 255.0f ) ops[i] = 255.0f;
    if ( ops[i] <   0.0f ) ops[i] =   0.0f;
  }

  r = (unsigned char)( ops[0] + 0.5f );
  g = (unsigned char)( ops[1] + 0.5f );
  b = (unsigned char)( ops[2] + 0.5f );
  a = ( noOfOps == 4 )? (unsigned char)( ops[2] + 0.5f ) : 255;

  *aColor = ( a << 24 ) | ( r << 16 ) | ( g << 8 ) | b;
  *aText  = ptr + 1;
  return 1;
}


/* This helper function Compares the content in aText with predetermined
   color names according to CSS specification. If the function was
   successful, the RGB values are stored in the parameter aColor in the order
   ARGB and the function returns a value != 0. */
static int ParseColorName( const XChar** aText, unsigned int* aColor )
{
  /* CSS level 1 colors */
  const static char* colorNames1[] =
  {
    "black", "silver", "gray", "white", "maroon", "red", "purple",
    "fuchsia", "green", "lime",  "olive", "yellow", "navy", "blue", "teal",
    "aqua"
  };
  const static unsigned int colors1[] = 
  {
    0xff000000, 0xffc0c0c0, 0xff808080, 0xffffffff, 0xff800000, 0xffff0000,
    0xff800080, 0xffff00ff, 0xff008000, 0xff00ff00, 0xff808000, 0xffffff00,
    0xff000080, 0xff0000ff, 0xff008080, 0xff00ffff
  };

  /* CSS level 3 colors */
  const static char* colorNames3[] =
  {
    "aliceblue", "antiquewhite", "aquamarine", "azure", "beige", "bisque",
    "blanchedalmond", "blueviolet", "brown", "burlywood", "cadetblue",
    "chartreuse", "chocolate", "coral", "cornflowerblue", "cornsilk",
    "crimson", "cyan", "darkblue", "darkcyan", "darkgoldenrod", "darkgray",
    "darkgreen", "darkgrey", "darkkhaki", "darkmagenta", "darkolivegreen",
    "darkorange", "darkorchid", "darkred", "darksalmon", "darkseagreen",
    "darkslateblue", "darkslategray", "darkslategrey", "darkturquoise",
    "darkviolet", "deeppink", "deepskyblue", "dimgray", "dimgrey", "dodgerblue",
    "firebrick", "floralwhite", "forestgreen", "gainsboro", "ghostwhite",
    "gold", "goldenrod", "greenyellow", "grey", "honeydew", "hotpink",
    "indianred", "indigo", "ivory", "khaki", "lavender", "lavenderblush",
    "lawngreen", "lemonchiffon", "lightblue", "lightcoral", "lightcyan",
    "lightgoldenrodyellow", "lightgray", "lightgreen", "lightgrey",
    "lightpink", "lightsalmon", "lightseagreen", "lightskyblue",
    "lightslategray", "lightslategrey", "lightsteelblue", "lightyellow",
    "limegreen", "linen", "magenta", "mediumaquamarine", "mediumblue",
    "mediumorchid", "mediumpurple", "mediumseagreen", "mediumslateblue",
    "mediumspringgreen", "mediumturquoise", "mediumvioletred", "midnightblue",
    "mintcream", "mistyrose", "moccasin", "navajowhite", "oldlace", "olivedrab",
    "orange", "orangered", "orchid", "palegoldenrod", "palegreen",
    "paleturquoise", "palevioletred", "papayawhip", "peachpuff", "peru", "pink",
    "plum", "powderblue", "rebeccapurple", "rosybrown", "royalblue",
    "saddlebrown", "salmon", "sandybrown", "seagreen", "seashell", "sienna",
    "skyblue", "slateblue", "slategray", "slategrey", "snow", "springgreen",
    "steelblue", "tan", "thistle", "tomato", "transparent", "turquoise",
    "violet", "wheat", "whitesmoke", "yellowgreen"
  };
  const static unsigned int colors3[] = 
  {
    0xfff0f8ff, 0xfffaebd7, 0xff7fffd4, 0xfff0ffff, 0xfff5f5dc, 0xffffe4c4,
    0xffffebcd, 0xff8a2be2, 0xffa52a2a, 0xffdeb887, 0xff5f9ea0, 0xff7fff00,
    0xffd2691e, 0xffff7f50, 0xff6495ed, 0xfffff8dc, 0xffdc143c, 0xff00ffff,
    0xff00008b, 0xff008b8b, 0xffb8860b, 0xffa9a9a9, 0xff006400, 0xffa9a9a9,
    0xffbdb76b, 0xff8b008b, 0xff556b2f, 0xffff8c00, 0xff9932cc, 0xff8b0000,
    0xffe9967a, 0xff8fbc8f, 0xff483d8b, 0xff2f4f4f, 0xff2f4f4f, 0xff00ced1,
    0xff9400d3, 0xffff1493, 0xff00bfff, 0xff696969, 0xff696969, 0xff1e90ff,
    0xffb22222, 0xfffffaf0, 0xff228b22, 0xffdcdcdc, 0xfff8f8ff, 0xffffd700,
    0xffdaa520, 0xffadff2f, 0xff808080, 0xfff0fff0, 0xffff69b4, 0xffcd5c5c,
    0xff4b0082, 0xfffffff0, 0xfff0e68c, 0xffe6e6fa, 0xfffff0f5, 0xff7cfc00,
    0xfffffacd, 0xffadd8e6, 0xfff08080, 0xffe0ffff, 0xfffafad2, 0xffd3d3d3,
    0xff90ee90, 0xffd3d3d3, 0xffffb6c1, 0xffffa07a, 0xff20b2aa, 0xff87cefa,
    0xff778899, 0xff778899, 0xffb0c4de, 0xffffffe0, 0xff32cd32, 0xfffaf0e6,
    0xffff00ff, 0xff66cdaa, 0xff0000cd, 0xffba55d3, 0xff9370db, 0xff3cb371,
    0xff7b68ee, 0xff00fa9a, 0xff48d1cc, 0xffc71585, 0xff191970, 0xfff5fffa,
    0xffffe4e1, 0xffffe4b5, 0xffffdead, 0xfffdf5e6, 0xff6b8e23, 0xffffa500,
    0xffff4500, 0xffda70d6, 0xffeee8aa, 0xff98fb98, 0xffafeeee, 0xffdb7093,
    0xffffefd5, 0xffffdab9, 0xffcd853f, 0xffffc0cb, 0xffdda0dd, 0xffb0e0e6,
    0xff663399, 0xffbc8f8f, 0xff4169e1, 0xff8b4513, 0xfffa8072, 0xfff4a460,
    0xff2e8b57, 0xfffff5ee, 0xffa0522d, 0xff87ceeb, 0xff6a5acd, 0xff708090,
    0xff708090, 0xfffffafa, 0xff00ff7f, 0xff4682b4, 0xffd2b48c, 0xffd8bfd8,
    0xffff6347, 0x00000000, 0xff40e0d0, 0xffee82ee, 0xfff5deb3, 0xfff5f5f5,
    0xff9acd32
  };

  unsigned char r, g, b, a;
  int           i;

  /* Fast test - is it a name? */
  if ( !IsNameStartChar( **aText ))
    return 0;

  /* Compare with color names from CSS level 1 */
  for ( i = 0; i < ( sizeof( colors1 ) / sizeof( *colors1 )); i++ )
    if ( SkipName( aText, colorNames1[i]))
    {
      r = (unsigned char)( colors1[i] >> 16 );
      g = (unsigned char)( colors1[i] >>  8 );
      b = (unsigned char)( colors1[i] >>  0 );
      a = (unsigned char)( colors1[i] >> 24 );

      *aColor = ( a << 24 ) | ( r << 16 ) | ( g << 8 ) | b;
      return 1;
    }

  /* Compare with color names from CSS level 3 */
  for ( i = 0; i < ( sizeof( colors3 ) / sizeof( *colors3 )); i++ )
    if ( SkipName( aText, colorNames3[i]))
    {
      r = (unsigned char)( colors3[i] >> 16 );
      g = (unsigned char)( colors3[i] >>  8 );
      b = (unsigned char)( colors3[i] >>  0 );
      a = (unsigned char)( colors3[i] >> 24 );

      *aColor = ( a << 24 ) | ( r << 16 ) | ( g << 8 ) | b;
      return 1;
    }

  return 0;
}


/* This helper function tries to parse the url(#id) expression found in aText.
   If the function was successful, pointers to the id are stored in aIdStart
   and aIdEnd parameters and the function returns a value != 0. */
static int ParseURLFunc( const XChar** aText, const XChar** aIdStart,
  const XChar** aIdEnd )
{
  const XChar* ptr = *aText;
  const XChar* start;
  const XChar* end;
  XChar        q   = 0;

  /* Expects 'url(' as starting sequence */
  if ( !SkipName( &ptr, "url(" ))
    return 0;

  /* Skip over white space */
  SkipSpace( &ptr );

  /* Is the url expression enclosed in quote signs? */
  if (( *ptr == '\'' ) || ( *ptr == '"' ))
    q = *ptr++;

  start = ptr;

  /* Skip to end of the id */
  while ( *ptr && ( q || !IsSpaceChar( *ptr )) && ( *ptr != ')' ) && ( *ptr != q ))
    ptr++;

  end = ptr;

  /* Missing closing quote sign */
  if ( q && ( *ptr != q ))
    return 0;

  /* Skip over the quote sign */
  if ( q )
    ptr++;

  /* Skip over white space */
  SkipSpace( &ptr );

  /* Closing ')' sign expected */
  if ( *ptr != ')' )
    return 0;

  *aText    = ptr + 1;
  *aIdStart = start;
  *aIdEnd   = end;
  return 1;
}


/* This helper function tries to parse the transformation expression found in
   aText. If the function was successful, the corresponding transformation
   command is generated in aDest buffer and a value != 0 is returned. */
static int ParseTransformFunc( const XChar** aText, XBuffer* aDest )
{
  static const char* funcNames[] = { "translate", "scale", "rotate", "skewX",
                                     "skewY", "matrix" };
  float              ops[6]      = { 0.0f };
  const XChar*       ptr         = *aText;
  int                sep         = 0;
  int                funcNo;
  int                noOfOps;

  /* Search for the function name */
  for ( funcNo = 0; funcNo < 6; funcNo++ )
    if ( SkipName( &ptr, funcNames[ funcNo ]))
      break;

  /* No function found */
  if ( funcNo == 6 )
    return 0;

  SkipSpace( &ptr );

  /* '(' expected */
  if ( *ptr != '(' )
    return 0;

  /* Skip over '(' */
  ptr++;
  SkipSpace( &ptr );

  /* Parse up to six operands */
  for ( noOfOps = 0; noOfOps < 6; noOfOps++ )
    if ( ParseReal( &ptr, &ops[ noOfOps ]))
      sep = SkipCommaSpace( &ptr );
    else
      break;

  /* Missing an operand after ',' separator */
  if ( sep == ',' )
    return 0;

  /* At least one operand expected */
  if ( !noOfOps )
    return 0;

  /* Max. number of operands allowed? */
  if ((( funcNo >= 0 ) && ( funcNo  <= 1 ) && ( noOfOps  > 2 )) ||
      (( funcNo == 2 ) && ( noOfOps != 1 ) && ( noOfOps != 3 )) ||
      (( funcNo >= 3 ) && ( funcNo  <= 4 ) && ( noOfOps  > 1 )))
    return 0;

  /* matrix() expects exact. 6 operands */
  if (( funcNo == 5 ) && ( noOfOps != 6 ))
    return 0;

  SkipSpace( &ptr );

  /* ')' expected */
  if ( *ptr != ')' )
    return 0;

  /* translate( tx [ty] ) */
  if ( funcNo == 0 )
  {
    AppendInstruction( aDest, ( noOfOps > 1 )? EW_SVG_Translate2 :
                                               EW_SVG_Translate1 );
    AppendFloat( aDest, ops[0]);

    if ( noOfOps > 1 )
      AppendFloat( aDest, ops[1]);
  }

  /* scale( sx [sy] ) */
  else if ( funcNo == 1 )
  {
    AppendInstruction( aDest, ( noOfOps > 1 )? EW_SVG_Scale2 : EW_SVG_Scale1 );
    AppendFloat( aDest, ops[0]);

    if ( noOfOps > 1 )
      AppendFloat( aDest, ops[1]);
  }

  /* rotate( angle [ cx cy ]) */
  else if ( funcNo == 2 )
  {
    AppendInstruction( aDest, ( noOfOps > 1 )? EW_SVG_Rotate3 :
                                               EW_SVG_Rotate1 );
    AppendFloat( aDest, ops[0]);

    if ( noOfOps > 1 )
    {
      AppendFloat( aDest, ops[1]);
      AppendFloat( aDest, ops[2]);
    }
  }

  /* skewX( angle ) */
  else if ( funcNo == 3 )
  {
    AppendInstruction( aDest, EW_SVG_SkewX );
    AppendFloat( aDest, ops[0]);
  }

  /* skewY( angle ) */
  else if ( funcNo == 4 )
  {
    AppendInstruction( aDest, EW_SVG_SkewY );
    AppendFloat( aDest, ops[0]);
  }

  /* matrix( a, b, c, d, e, f ) */
  else if ( funcNo == 5 )
  {
    AppendInstruction( aDest, EW_SVG_Matrix );

    for ( noOfOps = 0; noOfOps < 6; noOfOps++ )
      AppendFloat( aDest, ops[ noOfOps ]);
  }

  *aText = ptr + 1;
  return 1;
}

#endif /* EW_DONT_USE_SVG_READER */


/* Exclude path functionality? It includes the path string parsing */
#ifndef EW_DONT_USE_PATH_FUNCTIONS

/* Following function works similar to above ParseReal() with the additional
   difference to allow white space or comma signs in front of the number. */
static int ParseCommaReal( const XChar** aText, float* aNumber )
{
  const XChar* ptr;

  /* Skip over evtl. leading white -space signs */
  SkipSpace( aText );
  ptr = *aText;

  /* Accept ',' signs in SVG path string */
  if ( *ptr == ',' )
  {
    ptr++;
    SkipSpace( &ptr );
  }

  /* Try to parse the number */
  if ( ParseReal( &ptr, aNumber ))
  {
    *aText = ptr;
    return 1;
  }

  return 0;
}


/* This helper function tries to parse a flag literal (0 or 1) found in the
   string aText. Any leading white-space or comma signs are skipped over.
   If the function was successful, the flag is stored in the parameter aFlag
   and the function returns a value != 0.  */
static int ParsePathFlag( const XChar** aText, int* aFlag )
{
  const XChar* ptr;

  /* Skip over evtl. leading white -space signs */
  SkipSpace( aText );
  ptr = *aText;

  /* Accept ',' signs in SVG path string */
  if ( *ptr == ',' )
  {
    ptr++;
    SkipSpace( &ptr );
  }

  /* Flag found? */
  if (( *ptr == '0' ) || ( *ptr == '1' ))
  {
    *aFlag = *ptr++ == '1';
    *aText = ptr;
    return 1;
  }

  return 0;
}


/* This helper function tries to parse a sequence of SVG path commands found in
   aText. The function returns a number of sub-paths recognized and stored as
   commands in aDest. In error case the variables aErrorCode and aErrorPos
   describe the error and its position relative to the beginning of aText. */
static unsigned int ParseSVGPath( const XChar** aText, XBuffer* aDest,
  int* aErrorCode, int* aErrorPos )
{
  const XChar* ptr          = *aText;
  unsigned int noOfSubPaths = 0;
  XFloat       angle        = 0;
  XFloat       bpx          = 0;
  XFloat       bpy          = 0;
  XFloat       cpx          = 0;
  XFloat       cpy          = 0;
  XFloat       x1           = 0;
  XFloat       y1           = 0;
  XFloat       x2           = 0;
  XFloat       y2           = 0;
  XFloat       x3           = 0;
  XFloat       y3           = 0;
  XFloat       rx           = 0;
  XFloat       ry           = 0;
  int          f1           = 0;
  int          f2           = 0;
  XChar        prevCmd      = 0;
  XChar        cmd          = 0;

  if ( ptr )
    SkipSpace( &ptr );

  /* No content to process */
  if ( !ptr || !*ptr )
    goto EMPTY_STRING;

  /* The path has always to begin with a MOVE command */
  if (( *ptr != 'm' ) && ( *ptr != 'M' ))
    goto SYNTAX_ERROR;

  /* Process the SVG string sub-path by sub-path. Evaluate the commands. */
  while ( *ptr )
  {
    prevCmd = cmd;
    cmd     = *ptr++;

    /* Initiates a new sub-path followed by optional straight line
       segments. */
    if (( cmd == 'm' ) || ( cmd == 'M' ))
    {
      SkipSpace( &ptr );

      if ( !ParseReal( &ptr, &x1 ) || !ParseCommaReal( &ptr, &y1 ))
        goto SYNTAX_ERROR;

      if ( cmd == 'M' ) { cpx  = x1; cpy  = y1; }
      else              { cpx += x1; cpy += y1; }

      /* Generate the corresponding command to start a new sub-path */
      AppendInstruction( aDest, EW_SVG_BeginPath );
      AppendFloat( aDest, cpx );
      AppendFloat( aDest, cpy );

      /* Count the sub-path */
      noOfSubPaths++;

      /* Remember the position where the path started */
      bpx = cpx; bpy = cpy;

      /* Followed by optional line segments? */
      while ( ParseCommaReal( &ptr, &x1 ))
      {
        if ( !ParseCommaReal( &ptr, &y1 ))
          goto SYNTAX_ERROR;

        if ( cmd == 'M' ) { cpx  = x1; cpy  = y1; }
        else              { cpx += x1; cpy += y1; }

        /* Generate the corresponding command */
        AppendInstruction( aDest, EW_SVG_AddLine );
        AppendFloat( aDest, cpx );
        AppendFloat( aDest, cpy );
      }
    }

    /* Straight line command */
    else if (( cmd == 'l' ) || ( cmd == 'L' ))
    {
      SkipSpace( &ptr );

      if ( !ParseReal( &ptr, &x1 ))
        goto SYNTAX_ERROR;

      /* Repeat as long as line segments follow */
      do
      {
        if ( !ParseCommaReal( &ptr, &y1 ))
          goto SYNTAX_ERROR;

        /* New 'add' command after the 'close path' start a new sub-path. */
        if (( prevCmd == 'z' ) || ( prevCmd == 'Z' ))
        {
          AppendInstruction( aDest, EW_SVG_BeginPath );
          AppendFloat( aDest, cpx );
          AppendFloat( aDest, cpy );
          noOfSubPaths++;
          prevCmd = 0;
        }

        if ( cmd == 'L' ) { cpx  = x1; cpy  = y1; }
        else              { cpx += x1; cpy += y1; }

        /* Generate the corresponding command */
        AppendInstruction( aDest, EW_SVG_AddLine );
        AppendFloat( aDest, cpx );
        AppendFloat( aDest, cpy );
      }
      while ( ParseCommaReal( &ptr, &x1 ));
    }

    /* Horizontal straight line command */
    else if (( cmd == 'h' ) || ( cmd == 'H' ))
    {
      SkipSpace( &ptr );

      if ( !ParseReal( &ptr, &x1 ))
        goto SYNTAX_ERROR;

      /* New 'add' command after the 'close path' start a new sub-path. */
      if (( prevCmd == 'z' ) || ( prevCmd == 'Z' ))
      {
        AppendInstruction( aDest, EW_SVG_BeginPath );
        AppendFloat( aDest, cpx );
        AppendFloat( aDest, cpy );
        noOfSubPaths++;
        prevCmd = 0;
      }

      /* Repeat as long as line segments follow */
      do
      {
        if ( cmd == 'H' ) cpx  = x1;
        else              cpx += x1;

        /* Generate the corresponding command */
        AppendInstruction( aDest, EW_SVG_AddLine );
        AppendFloat( aDest, cpx );
        AppendFloat( aDest, cpy );
      }
      while ( ParseCommaReal( &ptr, &x1 ));
    }

    /* Vertical straight line command */
    else if (( cmd == 'v' ) || ( cmd == 'V' ))
    {
      SkipSpace( &ptr );

      if ( !ParseReal( &ptr, &y1 ))
        goto SYNTAX_ERROR;

      /* New 'add' command after the 'close path' start a new sub-path. */
      if (( prevCmd == 'z' ) || ( prevCmd == 'Z' ))
      {
        AppendInstruction( aDest, EW_SVG_BeginPath );
        AppendFloat( aDest, cpx );
        AppendFloat( aDest, cpy );
        noOfSubPaths++;
        prevCmd = 0;
      }

      /* Repeat as long as line segments follow */
      do
      {
        if ( cmd == 'V' ) cpy  = y1;
        else              cpy += y1;

        /* Generate the corresponding command */
        AppendInstruction( aDest, EW_SVG_AddLine );
        AppendFloat( aDest, cpx );
        AppendFloat( aDest, cpy );
      }
      while ( ParseCommaReal( &ptr, &y1 ));
    }

    /* Curve to sequence */
    else if (( cmd == 'c' ) || ( cmd == 'C' ))
    {
      SkipSpace( &ptr );

      if ( !ParseReal( &ptr, &x1 ))
        goto SYNTAX_ERROR;

      /* Repeat as long as curve coordinates follow */
      do
      {
        if ( !ParseCommaReal( &ptr, &y1 ) || !ParseCommaReal( &ptr, &x2 ) ||
             !ParseCommaReal( &ptr, &y2 ) || !ParseCommaReal( &ptr, &x3 ) ||
             !ParseCommaReal( &ptr, &y3 ))
          goto SYNTAX_ERROR;

        /* New 'add' command after the 'close path' start a new sub-path. */
        if (( prevCmd == 'z' ) || ( prevCmd == 'Z' ))
        {
          AppendInstruction( aDest, EW_SVG_BeginPath );
          AppendFloat( aDest, cpx );
          AppendFloat( aDest, cpy );
          noOfSubPaths++;
          prevCmd = 0;
        }

        if ( cmd == 'c' )
          { x1 += cpx; y1 += cpy; x2 += cpx; y2 += cpy; x3 += cpx; y3 += cpy; }

        /* Generate the corresponding command */
        AppendInstruction( aDest, EW_SVG_AddBezier3 );
        AppendFloat( aDest, x1 ); AppendFloat( aDest, y1 );
        AppendFloat( aDest, x2 ); AppendFloat( aDest, y2 );
        AppendFloat( aDest, x3 ); AppendFloat( aDest, y3 );

        cpx = x3; cpy = y3;
      }
      while ( ParseCommaReal( &ptr, &x1 ));
    }

    /* Smooth curve to sequence */
    else if (( cmd == 's' ) || ( cmd == 'S' ))
    {
      x1 = x2; y1 = y2;

      SkipSpace( &ptr );

      if ( !ParseReal( &ptr, &x2 ))
        goto SYNTAX_ERROR;

      /* Repeat as long as curve coordinates follow */
      do
      {
        if ( !ParseCommaReal( &ptr, &y2 ) || !ParseCommaReal( &ptr, &x3 ) ||
             !ParseCommaReal( &ptr, &y3 ))
          goto SYNTAX_ERROR;

        /* New 'add' command after the 'close path' start a new sub-path. */
        if (( prevCmd == 'z' ) || ( prevCmd == 'Z' ))
        {
          AppendInstruction( aDest, EW_SVG_BeginPath );
          AppendFloat( aDest, cpx );
          AppendFloat( aDest, cpy );
          noOfSubPaths++;
          prevCmd = 0;
        }

        if ( cmd == 's' )
          { x2 += cpx; y2 += cpy; x3 += cpx; y3 += cpy; }

        /* Control point 1 is a reflection of control point 2 of the preceding
           curve */
        if (( prevCmd == 'C' ) || ( prevCmd == 'c' ) ||
            ( prevCmd == 'S' ) || ( prevCmd == 's' ))
        {
          x1 = cpx - ( x1 - cpx );
          y1 = cpy - ( y1 - cpy );
        }

        /* No preceding command? The first control point is coincident with the
           current position */
        else
          { x1 = cpx; y1 = cpy; }

        /* Generate the corresponding command */
        AppendInstruction( aDest, EW_SVG_AddBezier3 );
        AppendFloat( aDest, x1 ); AppendFloat( aDest, y1 );
        AppendFloat( aDest, x2 ); AppendFloat( aDest, y2 );
        AppendFloat( aDest, x3 ); AppendFloat( aDest, y3 );

        cpx = x3; cpy = y3; x1 = x2; y1 = y2; prevCmd = cmd;
      }
      while ( ParseCommaReal( &ptr, &x2 ));
    }

    /* Quadratic Bezier sequence */
    else if (( cmd == 'q' ) || ( cmd == 'Q' ))
    {
      SkipSpace( &ptr );

      if ( !ParseReal( &ptr, &x1 ))
        goto SYNTAX_ERROR;

      /* Repeat as long as curve coordinates follow */
      do
      {
        if ( !ParseCommaReal( &ptr, &y1 ) || !ParseCommaReal( &ptr, &x2 ) ||
             !ParseCommaReal( &ptr, &y2 ))
          goto SYNTAX_ERROR;

        /* New 'add' command after the 'close path' start a new sub-path. */
        if (( prevCmd == 'z' ) || ( prevCmd == 'Z' ))
        {
          AppendInstruction( aDest, EW_SVG_BeginPath );
          AppendFloat( aDest, cpx );
          AppendFloat( aDest, cpy );
          noOfSubPaths++;
          prevCmd = 0;
        }

        if ( cmd == 'q' )
          { x1 += cpx; y1 += cpy; x2 += cpx; y2 += cpy; }

        /* Generate the corresponding command */
        AppendInstruction( aDest, EW_SVG_AddBezier2 );
        AppendFloat( aDest, x1 ); AppendFloat( aDest, y1 );
        AppendFloat( aDest, x2 ); AppendFloat( aDest, y2 );

        cpx = x2; cpy = y2;
      }
      while ( ParseCommaReal( &ptr, &x1 ));
    }

    /* Smooth quadratic Bezier sequence */
    else if (( cmd == 't' ) || ( cmd == 'T' ))
    {
      SkipSpace( &ptr );

      if ( !ParseReal( &ptr, &x2 ))
        goto SYNTAX_ERROR;

      /* Repeat as long as coordinates follow */
      do
      {
        if ( !ParseCommaReal( &ptr, &y2 ))
          goto SYNTAX_ERROR;

        /* New 'add' command after the 'close path' start a new sub-path. */
        if (( prevCmd == 'z' ) || ( prevCmd == 'Z' ))
        {
          AppendInstruction( aDest, EW_SVG_BeginPath );
          AppendFloat( aDest, cpx );
          AppendFloat( aDest, cpy );
          noOfSubPaths++;
          prevCmd = 0;
        }

        if ( cmd == 't' )
          { x2 += cpx; y2 += cpy; }

        /* Control point is a reflection of control point of the preceding
           curve */
        if (( prevCmd == 'Q' ) || ( prevCmd == 'q' ) ||
            ( prevCmd == 'T' ) || ( prevCmd == 't' ))
        {
          x1 = cpx - ( x1 - cpx );
          y1 = cpy - ( y1 - cpy );
        }

        /* No preceding command? The first control point is coincident with the
           current position */
        else
          { x1 = cpx; y1 = cpy; }

        /* Generate the corresponding command */
        AppendInstruction( aDest, EW_SVG_AddBezier2 );
        AppendFloat( aDest, x1 ); AppendFloat( aDest, y1 );
        AppendFloat( aDest, x2 ); AppendFloat( aDest, y2 );

        cpx = x2; cpy = y2; prevCmd = cmd;
      }
      while ( ParseCommaReal( &ptr, &x2 ));
    }

    /* Elliptical arc sequence */
    else if (( cmd == 'a' ) || ( cmd == 'A' ))
    {
      float cx, cy;
      float startAngle, deltaAngle;
      float s_phi, c_phi;
      float hd_x, hd_y;
      float hs_x, hs_y;
      float x1_, y1_;
      float lambda;
      float rxry;
      float rxy1_, ryx1_;
      float sum;
      float abs;
      float coe;
      float cx_, cy_;
      float xcr1, ycr1;
      float xcr2, ycr2;
      float tmp;

      SkipSpace( &ptr );

      if ( !ParseReal( &ptr, &rx ))
        goto SYNTAX_ERROR;

      /* Repeat as long as coordinates follow */
      do
      {
        x1 = cpx;
        y1 = cpy;

        if ( !ParseCommaReal( &ptr, &ry ) || !ParseCommaReal( &ptr, &angle ) ||
             !ParsePathFlag ( &ptr, &f1 ) || !ParsePathFlag ( &ptr, &f2    ) ||
             !ParseCommaReal( &ptr, &x2 ) || !ParseCommaReal( &ptr, &y2    ))
          goto SYNTAX_ERROR;

        if ( cmd == 'a' )
          { x2 += cpx; y2 += cpy; }

        /* radius rx or ry cannot be zero or negative */
        if (( rx <= 0.0f ) || ( ry <= 0.0f ))
          goto ARGUMENT_ERROR;

        /* Conversion from SVG endpoint paremeterization to center parameterization
           according https://www.w3.org/TR/SVG/implnote.html */
        s_phi = EwMathSin( angle );
        c_phi = EwMathCos( angle );
        hd_x  = ( x1 - x2 ) / 2.0f;
        hd_y  = ( y1 - y2 ) / 2.0f;
        hs_x  = ( x1 + x2 ) / 2.0f;
        hs_y  = ( y1 + y2 ) / 2.0f;

        /* equation 5.1 */
        x1_ = c_phi * hd_x + s_phi * hd_y;
        y1_ = c_phi * hd_y - s_phi * hd_x;

        /* equation 6.2 and 6.3 - ensure radii are large enough */
        lambda = ( x1_ * x1_ ) / ( rx * rx ) + ( y1_ * y1_ ) / ( ry * ry );

        if ( lambda > 1.0f )
        {
          rx = rx * EwMathSqrt( lambda );
          ry = ry * EwMathSqrt( lambda );
        }

        /* equation 5.2 */
        rxry  = rx * ry;
        rxy1_ = rx * y1_;
        ryx1_ = ry * x1_;
        sum   = rxy1_ * rxy1_ + ryx1_ * ryx1_;

        if ( sum == 0.0f )
          goto ARGUMENT_ERROR;

        abs = (rxry * rxry - sum) / sum;
        if ( abs < 0.0f ) abs = -abs;
        coe = EwMathSqrt( abs );
        if ( f1 == f2 ) coe = -coe;
        cx_ =  coe * rxy1_ / ry;
        cy_ = -coe * ryx1_ / rx;

        /* equation 5.3 */
        cx = c_phi * cx_ - s_phi * cy_ + hs_x;
        cy = s_phi * cx_ + c_phi * cy_ + hs_y;

        xcr1 = ( x1_ - cx_ ) / rx; xcr2 = ( x1_ + cx_ ) / rx;
        ycr1 = ( y1_ - cy_ ) / ry; ycr2 = ( y1_ + cy_ ) / ry;

        /* equation 5.5 */
        tmp = xcr1 * xcr1 + ycr1 * ycr1;

        if ( tmp == 0.0f )
          goto ARGUMENT_ERROR;

        startAngle = EwMathArcCos( xcr1 / EwMathSqrt( tmp ));

        if ( ycr1 < 0.0f )
          startAngle = -startAngle;

        /* equation 5.6 */
        tmp = ( xcr1 * xcr1 + ycr1 * ycr1 ) * ( xcr2 * xcr2 + ycr2 * ycr2 );

        if ( tmp == 0.0f )
          goto ARGUMENT_ERROR;

        deltaAngle = EwMathArcCos(( xcr1 * -xcr2 + ycr1 * -ycr2 ) /
                     EwMathSqrt( tmp ));

        if (( xcr1 * -ycr2 - ycr1 * -xcr2 ) < 0.0f )
          deltaAngle = -deltaAngle;

        while ( deltaAngle >  360.0f ) { deltaAngle = deltaAngle - 360.0f; }
        while ( deltaAngle < -360.0f ) { deltaAngle = deltaAngle + 360.0f; }
        if ( !f2 && ( deltaAngle > 0.0f )) deltaAngle = deltaAngle - 360.0f;
        if (  f2 && ( deltaAngle < 0.0f )) deltaAngle = deltaAngle + 360.0f;

        /* New 'add' command after the 'close path' start a new sub-path. */
        if (( prevCmd == 'z' ) || ( prevCmd == 'Z' ))
        {
          AppendInstruction( aDest, EW_SVG_BeginPath );
          AppendFloat( aDest, cpx );
          AppendFloat( aDest, cpy );
          noOfSubPaths++;
          prevCmd = 0;
        }

        /* Generate the corresponding command */
        AppendInstruction( aDest, EW_SVG_AddArc );
        AppendFloat( aDest, cx );    AppendFloat( aDest, cy );
        AppendFloat( aDest, rx );    AppendFloat( aDest, ry );
        AppendFloat( aDest, angle ); AppendFloat( aDest, startAngle );
        AppendFloat( aDest, startAngle + deltaAngle ); 

        cpx = x2; cpy = y2;
      }
      while ( ParseCommaReal( &ptr, &rx ));
    }

    /* Close the sub-path */
    else if (( cmd == 'Z' ) || ( cmd == 'z' ))
    {
      SkipSpace( &ptr );

      /* Generate the corresponding command */
      AppendInstruction( aDest, EW_SVG_ClosePath );

      /* With closed path, the end and the begin positions overlap. The next
         following position is thus the last one known begin position. */
      cpx = bpx; cpy = bpy;
    }

    /* Unknown command found. Stop */
    else
    {
      ptr--;
      goto FINISHED;
    }
  }

  FINISHED:
  {
    *aText = ptr;
    return noOfSubPaths;
  }

  /* The path contains a syntax error */
  EMPTY_STRING:
  {
    if ( aErrorCode ) *aErrorCode = EW_SVG_PARSER_EMPTY_STRING;
    if ( aErrorPos  ) *aErrorPos  = -1;
    return 0;
  }

  /* The path contains a syntax error */
  SYNTAX_ERROR:
  {
    if ( aErrorCode ) *aErrorCode = EW_SVG_PARSER_SYNTAX_ERROR;
    if ( aErrorPos  ) *aErrorPos  = (int)( ptr - *aText );
    return noOfSubPaths;
  }

  /* The path contains an invalid argument value */
  ARGUMENT_ERROR:
  {
    if ( aErrorCode ) *aErrorCode = EW_SVG_PARSER_INVALID_ARGUMENT;
    if ( aErrorPos  ) *aErrorPos  = (int)( ptr - *aText );
    return noOfSubPaths;
  }
}

#endif /* EW_DONT_USE_PATH_FUNCTIONS */


/* Exclude SVG reader functionality? */
#ifndef EW_DONT_USE_SVG_READER


/* Search for the beginning of an XML tag following the position aText. Returns
   the pointer to the location where processing stopped. The caller has to test
   whether the returned location is really the beginning of a tag or handle the
   error accordingly. Valid tag starts with '<' sign. */
static const XChar* FindNextXMLTag( const XChar* aText )
{
  /* The search operation begins with the next following sign. */
  if ( *aText )
    aText++;

  /* Process tags and skip over uninteresting contents */
  while ( *aText )
  {
    /* Search for the beginning of a tag. The specification allows Character
       and Entity References as well as signs other than '<' to exist inside
       the element content (between tags). Since this information is not
       relevant, skip over it. */
    if ( *aText != '<' )
    {
      aText++;
      continue;
    }

    /* Skip over comments '<!-- comment -->' */
    if (( aText[1] == '!' ) && ( aText[2] == '-' ) && ( aText[3] == '-' ))
    {
      aText += 4;

      /* Find the end of the comment block '-->' */
      while ( *aText && (( aText[0] != '-' ) || ( aText[1] != '-' ) ||
                         ( aText[2] != '>' )))
        aText++;

      if ( *aText )
        aText += 3;
    }

    /* Skip over processing commands '<? ... ?>' */
    else if ( aText[1] == '?' )
    {
      aText += 2;

      /* Find the end of the processing command '?>' */
      while ( *aText && (( aText[0] != '?' ) || ( aText[1] != '>' )))
        aText++;

      if ( *aText )
        aText += 2;
    }

    /* Skip over CDATA sections '<![CDATA[ ... ]]>' */
    else if (( aText[1] == '!' ) && ( aText[2] == '[' ) && ( aText[3] == 'C' ) &&
             ( aText[4] == 'D' ) && ( aText[5] == 'A' ) && ( aText[6] == 'T' ) &&
             ( aText[7] == 'A' ) && ( aText[8] == '[' ))
    {
      aText += 9;

      /* Find the end of the CDATA section ']]>' */
      while ( *aText && (( aText[0] != ']' ) || ( aText[1] != ']' ) ||
                         ( aText[2] != '>' )))
        aText++;

      if ( *aText )
        aText += 3;
    }

    /* Skip over DOCTYPE sections '<!DOCTYPE ... >' */
    else if (( aText[1] == '!' ) && ( aText[2] == 'D' ) && ( aText[3] == 'O' ) &&
             ( aText[4] == 'C' ) && ( aText[5] == 'T' ) && ( aText[6] == 'Y' ) &&
             ( aText[7] == 'P' ) && ( aText[8] == 'E' ))
    {
      int iss = 0;
      int q1  = 0;
      int q2  = 0;

      aText += 9;

      /* Find the end of the DOCTYPE section '>'. Note the eventually embedded
         intSubset enclosed by the pair of [...]. Also, the tag may contain
         strings enclosed between quotes. */
      while ( *aText && (( *aText != '>' ) || iss || q1 || q2 ))
      {
        if      ( !q1  && !q2 && ( *aText == '['  )) iss = 1;
        else if ( !q1  && !q2 && ( *aText == ']'  )) iss = 0;
        else if ( !iss && !q1 && ( *aText == '"'  )) q2  = !q2;
        else if ( !iss && !q2 && ( *aText == '\'' )) q1  = !q1;
        aText++;
      }

      if ( *aText )
        aText += 1;
    }

    /* Any other text portion starting with '<' found - it is probably a tag. */
    else
      break;
  }

  return aText;
}


/* Compares the name of the tag starting at aText. If tags name is equal to
   aName, the function returns != 0. Note, in case of an end tag the provided
   name has to start with '/'. */
static int IsXMLTagWithName( const XChar* aText, const char* aName )
{
  /* Is it a valid tag? */
  if ( *aText++ != '<' )
    return 0;

  /* Compare the tag name */
  return SkipName( &aText, aName );
}


/* Compares the name of the tag starting at aText. If tags name is equal to
   one of the names specified in the zero terminated array aNames, the function
   returns the index to the corresponding array entry. If no match is found, 
   the function return -1. Note, in case of an end tag the provided name has to
   start with '/'. */
static int IsXMLTagWithNames( const XChar* aText, const char** aNames )
{
  const char** names = aNames;

  /* Is it a valid tag? */
  if (( *aText++ != '<' ) || !aNames )
    return -1;

  /* Try all names from the aNames array */
  for ( ; *aNames; aNames++ )
    if ( SkipName( &aText, *aNames ))
      return (int)( aNames - names );

  return -1;
}


/* Searches for the end of a tag. If the tag is not correctly terminated, stops
   at the start position of the next following tag. The caller has to test
   whether the returned location is really the end of a tag or handle the error
   accordingly. Valid tag ends with '>' sign. */
static const XChar* FindEndOfXMLTag( const XChar* aText )
{
  int q1 = 0;
  int q2 = 0;

  /* Is it a valid tag? If not return the current location. */
  if ( *aText != '<' )
    return aText;

  /* Ignore the beginning of the current tag */
  aText++;

  /* While searching for the '>' sign correctly skip over attribute
     values enclosed between quote signs. */
  for ( ; *aText; aText++ )
  {
    if      ( !q1 && ( *aText == '"'  )) q2 = !q2;
    else if ( !q2 && ( *aText == '\'' )) q1 = !q1;
    else if ( !q1 && !q2 && (( *aText == '>' ) || ( *aText == '<' )))
      break;
  }

  return aText;
}


/* Searches for the closing counter part of the tag referenced by aText.
   Note, For the sake of simplicity the function limits to count and balance
   the start and end tags. No tag names are compared. Returns the pointer to
   the location where processing stopped. The caller has to test whether the
   returned location is really a beginning of a tag or handle the error
   accordingly. Valid tag starts with '<' sign. */
static const XChar* FindXMLEndTag( const XChar* aText )
{
  int          level = 0;
  const XChar* eot;

  do
  {
    /* Is it a valid tag? If not return the current location. */
    if ( *aText != '<' )
      return aText;

     eot = FindEndOfXMLTag( aText );

    /* End of tag expected but not found. Return the current location. */
    if ( *eot != '>' )
      return eot;

    /* Count opening and closing tags. */
    if      (( eot[-1] != '/' ) && ( aText[1] != '/' )) level++;
    else if (( eot[-1] != '/' ) && ( aText[1] == '/' )) level--;

    if ( level <= 0 )
      return aText;
  }
  while ( *( aText = FindNextXMLTag( eot )));

  return aText;
}


/* Searches for the next tag attribute starting at aText position and returns a
   pointer to found attribute name. If no attribute could be found, the function
   returns a pointer to location where the processing stopped. The caller has to
   test whether the returned location is really the beginning of an attribute or
   handle the error accordingly. To perform the test use IsNameStartChar(). */
static const XChar* FindNextXMLAttr( const XChar* aText )
{
  int q1 = 0;
  int q2 = 0;

  /* Skip over the beginning of the tag as well as the end of a value */
  if (( *aText == '<' ) || ( *aText == '\'' ) || ( *aText == '"' ))
    aText++;

  /* Attributes are separated from preceding content by space characters.
     Search for a space character. Skip over attribute values enclosed in
     quote signs. */
  for ( ; *aText; aText++ )
  {
    if      ( !q1 && ( *aText == '"'  )) q2 = !q2;
    else if ( !q2 && ( *aText == '\'' )) q1 = !q1;

    if ( !q1 && !q2 && 
       ( IsSpaceChar( *aText ) || ( *aText == '>' ) || ( *aText == '<' ) ||
       ( *aText == '/' )))
      break;
  }

  /* Skip over the space */
  SkipSpace( &aText );

  return aText;
}


/* Compares the name of the attribute starting at aText. If the name is equal,
   the function returns != 0. */
static int IsXMLAttrWithName( const XChar* aText, const char* aName )
{
  return SkipName( &aText, aName );
}


/* Searches for the next attribute value enclosed between a pair of "" or ''
   signs. If no value could be found, the function returns a pointer to
   location where the processing stopped. The caller has to test whether the
   returned location is really the beginning of an attribute value or handle
   the error accordingly. Valid values starts with '"' or ''' sign. */
static const XChar* FindNextXMLValue( const XChar* aText )
{
  /* Values are separated from preceding content by '=' character. */
  while ( *aText && ( *aText != '=' ) && ( *aText != '<' ) && ( *aText != '>' ))
    aText++;

  /* No '=' character found. */
  if ( *aText != '=' )
    return aText;

  /* Skip over the '=' and eventually following space */
  aText++;
  SkipSpace( &aText );

  return aText;
}


/* Searches for the end of the attribute value starting at aText position. If
   the end could not be found, the function returns a pointer to location where
   the processing stopped. The caller has to test whether the returned location
   is really the end of an attribute value or handle the error accordingly.
   Valid values ends with exact the same signs the value started. */
static const XChar* FindEndOfXMLValue( const XChar* aText )
{
  XChar mark = *aText;

  /* aText does not refer the beginning of a value */
  if (( mark != '"' ) && ( mark != '\'' ))
    return aText;

  /* Search the closing quote sign */
  do
    aText++;
  while ( *aText && ( *aText != mark ));

  return aText;
}


/* Compares the given value with the XML content. Returns != 0 if both are
   equal. Any leading or final space signs are ignored. */
static int IsXMLValue( const XChar* aTextStart, const XChar* aTextEnd,
  const char* aValue )
{
  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* No match? */
  if ( !SkipName( &aTextStart, aValue ))
    return 0;

  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* The entire value has been processed */
  return aTextStart == aTextEnd;
}


/* Searches in the atom list for an entry corresponding to the given text. If
   such entry already exists, returns its associated id. If the text is not
   yet stored in the list, adds to the list a new entry representing this text.
   If the operation failed due to memory shortage, the function returns 0. */
static int GetAtom( XAtom** aAtomList, const XChar* aTextStart,
  const XChar* aTextEnd )
{
  XAtom* entry = *aAtomList;

  /* Compare the text with the entries existing in the list */
  for ( ; entry; entry = entry->Next )
  {
    const XChar* textStart    = aTextStart;
    const XChar* refTextStart = entry->TextStart;

    /* If the text fragments have different length - they are different */
    if (( aTextEnd - textStart ) != ( entry->TextEnd - refTextStart ))
      continue;

    /* Text fragments have qual length. Compare them sign by sign */
    for ( ; ( textStart < aTextEnd ) && ( *textStart == *refTextStart );
              textStart++, refTextStart++ )
      ;

    /* All signs are equal */
    if ( textStart == aTextEnd )
      break;
  }

  /* Found? */
  if ( entry )
    return entry->Id;

  /* Not found. Try to allocate memory for a new list entry. */
  do
    entry = EwAlloc( sizeof( XAtom ));
  while ( !entry && EwImmediateReclaimMemory( 64 ));

  /* Report a message if there is no more memory */
  if ( !entry )
  {
    EwError( 64 );
    return 0;
  }

  /* Prepare the new entry and store it in the list.  */
  entry->Next      = *aAtomList;
  entry->TextStart = aTextStart;
  entry->TextEnd   = aTextEnd;
  entry->Id        = entry->Next? entry->Next->Id + 1 : 1;
  *aAtomList       = entry;

  /* Track the temporary used memory */
  EwResourcesMemory += sizeof( XAtom );

  /* Also track the max. memory pressure */
  if ( EwResourcesMemory > EwResourcesMemoryPeak )
    EwResourcesMemoryPeak = EwResourcesMemory;

  if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
    EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

  return entry->Id;
}


/* Releases all entries existing in the list. */
static void FreeAtoms( XAtom** aAtomList )
{
  XAtom* entry = *aAtomList;

  while ( entry )
  {
    XAtom* tmp = entry;
    entry = tmp->Next;
    EwFree( tmp );
    EwResourcesMemory -= sizeof( XAtom );
  }

  *aAtomList = 0;
}


/* Verifies whether the XML content does correspond to one of the strings
   stored in the zero terminated array aOptions. If successful, generates
   a new command in aDest with corresponding op-code from the array
   aOpCodes. Evtl. leading and final space signs are ignored. */
static void ParseSVGOption( const XChar* aTextStart, const XChar* aTextEnd,
  const char** aOptions, const unsigned char* aOpCodes, XBuffer* aDest )
{
  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* Search for the matching option */
  for ( ; *aOptions; aOptions++, aOpCodes++ )
    if ( SkipName( &aTextStart, *aOptions ))
      break;

  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* The entire value has been processed? Then append the corresponding
     command. Otherwise the attribute is ignored. */
  if ( aTextStart == aTextEnd )
    AppendInstruction( aDest, *aOpCodes );
}


/* Verifies whether the XML content is a number value. It parses the number
   and returns != 0. Any leading or final space signs are ignored. */
static int ParseSVGNumber( const XChar* aTextStart, const XChar* aTextEnd,
  float* aValue, char* aUnit )
{
  float value;
  char  unit = Unit_None;

  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* Try to parse the number */
  if ( !ParseReal( &aTextStart, &value ))
    return 0;

  /* Evtl. '%' unit following the number? */
  if ( *aTextStart == '%' )
  {
    unit = Unit_Percent;
    aTextStart++;
  }

  /* Evtl. 'in', 'cm', 'mm', 'pt', 'pc' or 'px' unit following the number? */
  else
    switch (( aTextStart[0] << 8 ) + aTextStart[1])
    {
      case 0x696E : unit = Unit_IN; aTextStart += 2; break;
      case 0x636D : unit = Unit_CM; aTextStart += 2; break;
      case 0x6D6D : unit = Unit_MM; aTextStart += 2; break;
      case 0x7074 : unit = Unit_PT; aTextStart += 2; break;
      case 0x7063 : unit = Unit_PC; aTextStart += 2; break;
      case 0x7078 : unit = Unit_PX; aTextStart += 2; break;
    }

  /* Skip over white space */
  SkipSpace( & aTextStart );

  /* The entire value has been processed */
  if ( aTextStart != aTextEnd )
    return 0;

  *aValue = value;
  *aUnit  = unit;
  return 1;
}


/* Verifies whether the XML content is a valid coordinate expression composed
   of a number followed by an optional unit. If successful generates a new
   command in aDest with the specified op-code: aOpCode. If the value is
   followed by the unit '%' the op-code is prefixed by EW_SVG_SetUnitPercentage.
   Evtl. leading and final space signs are ignored. */
static void ParseSVGCoordinate( const XChar* aTextStart, const XChar* aTextEnd,
  unsigned char aOpCode, XBuffer* aDest )
{
  float value;
  char  unit;

  /* Try to parse the number */
  if ( !ParseSVGNumber( aTextStart, aTextEnd, &value, &unit ))
    return;

  /* Adjust the value according to its unit. SVG spec. defines 1in = 96px */
  switch ( unit )
  {
    case Unit_Percent : value *= 0.01f;         break;
    case Unit_IN      : value *= 96.0f;         break;
    case Unit_CM      : value *= 96.0f / 2.54f; break;
    case Unit_MM      : value *= 96.0f / 25.4f; break;
    case Unit_PT      : value *= 96.0f / 72.0f; break;
    case Unit_PC      : value *= 16.0f;         break;
  }

  /* Is it a relative value? */
  if ( unit == Unit_Percent )
    AppendInstruction( aDest, EW_SVG_SetUnitPercentage );

  AppendInstruction( aDest, aOpCode );
  AppendFloat( aDest, value );
}


/* Verifies whether the XML content is a valid length expression composed
   of a number followed by an optional unit. If successful generates a new
   command in aDest with the specified op-code: aOpCode. If the value is
   followed by the unit '%' the op-code is prefixed by EW_SVG_SetUnitPercentage.
   If the length is less than 0, the attribute is ignored. Evtl. leading and
   final space signs are ignored. */
static void ParseSVGLength( const XChar* aTextStart, const XChar* aTextEnd,
  unsigned char aOpCode, XBuffer* aDest )
{
  float value;
  char  unit;

  /* Try to parse the number */
  if ( !ParseSVGNumber( aTextStart, aTextEnd, &value, &unit ))
    return;

  /* Adjust the value according to its unit. SVG spec. defines 1in = 96px */
  switch ( unit )
  {
    case Unit_Percent : value *= 0.01f;         break;
    case Unit_IN      : value *= 96.0f;         break;
    case Unit_CM      : value *= 96.0f / 2.54f; break;
    case Unit_MM      : value *= 96.0f / 25.4f; break;
    case Unit_PT      : value *= 96.0f / 72.0f; break;
    case Unit_PC      : value *= 16.0f;         break;
  }

  /* Is a valid length? */
  if ( value < 0.0f )
    return;

  /* Is it a relative value? */
  if ( unit == Unit_Percent )
    AppendInstruction( aDest, EW_SVG_SetUnitPercentage );

  AppendInstruction( aDest, aOpCode );
  AppendFloat( aDest, value );
}


/* Verifies whether the XML content is a valid opacity expression composed
   of a number followed by an optional %. If successful generates a new
   command in aDest with the specified aOpCode. The opacity value is
   clamped to the range [0..1]. Evtl. leading and final space signs are
   ignored. */
static void ParseSVGOpacity( const XChar* aTextStart, const XChar* aTextEnd,
  unsigned char aOpCode, XBuffer* aDest )
{
  float value;
  char  unit;

  /* Try to parse the number */
  if ( !ParseSVGNumber( aTextStart, aTextEnd, &value, &unit ))
    return;

  /* Opacity in % notation */
  if ( unit == Unit_Percent )
  {
    value *= 0.01f;
    unit   = Unit_None;
  }

  /* No unit allowed in opacity */
  if ( unit != Unit_None )
    return;

  /* Clamp the value */
  if ( value <= 0.0f ) value = 0.0f;
  if ( value >= 1.0f ) value = 1.0f;

  AppendInstruction( aDest, aOpCode );
  AppendFloat( aDest, value );
}


/* Verifies whether the XML content is a valid miter limit expression
   composed of a number without any units. If successful generates a new
   command in aDest with the specified aOpCode. If the miter limit value
   is less than 1, the operand is ignored. Evtl. leading and final space signs
   are ignored. */
static void ParseSVGMiter( const XChar* aTextStart, const XChar* aTextEnd,
  unsigned char aOpCode, XBuffer* aDest )
{
  float value;
  char  unit;

  /* Try to parse the number */
  if ( !ParseSVGNumber( aTextStart, aTextEnd, &value, &unit ))
    return;

  /* No unit allowed in opacity */
  if ( unit != Unit_None )
    return;

  /* Is a valid miter value? */
  if ( value < 1.0f )
    return;

  AppendInstruction( aDest, aOpCode );
  AppendFloat( aDest, value );
}


/* Verifies whether the XML content is a color expression. If successful
   generates a new command in aDest with one of the specified op-codes
   aOpCodeColor or aOpCodeCurrentColor. Evtl. leading and final space signs
   are ignored. */
static void ParseSVGColor( const XChar* aTextStart, const XChar* aTextEnd,
  unsigned char aOpCodeColor, unsigned char aOpCodeCurrentColor,
  XBuffer* aDest )
{
  unsigned int c;
  char         isCurrent = 0;

  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* Color value can have different syntax representation. */
  if      ( ParseColorLiteral( &aTextStart, &c             )) ;
  else if ( ParseRGBFunc     ( &aTextStart, &c             )) ;
  else if ( ParseColorName   ( &aTextStart, &c             )) ;
  else if ( SkipName         ( &aTextStart, "currentColor" )) isCurrent = 1;
  else
    return;

  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* The entire value has been processed */
  if ( aTextStart != aTextEnd )
    return;

  AppendInstruction( aDest, isCurrent? aOpCodeCurrentColor : aOpCodeColor );
  if ( !isCurrent )
    AppendUInt32( aDest, c );
}


/* Verifies whether the XML content is a valid paint expression. This includes
   references to existing gradient elements. If successful generates a new
   command in aDest with one of the specified op-codes aOpCodeNone,
   aOpCodeColor, aOpCodeCurrentColor, aOpCodeGradient. Evtl. leading and final
   space signs are ignored. */
static void ParseSVGPaint( const XChar* aTextStart, const XChar* aTextEnd,
  unsigned char aOpCodeNone, unsigned char aOpCodeColor,
  unsigned char aOpCodeCurrentColor, unsigned char aOpCodeGradient,
  XAtom** aAtomList, XBuffer* aDest )
{
  unsigned int c;
  int          isCurrent = 0;
  int          isNone    = 0;
  int          isRGB     = 0;
  int          isURL;
  const XChar* idStart;
  const XChar* idEnd;

  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* Reference to an element inside this SVG document? */
  isURL = ParseURLFunc( &aTextStart, &idStart, &idEnd );

  /* Skip over white space */
  if ( isURL )
    SkipSpace( &aTextStart );

  /* Only local URL starting with '# are accepted */
  if ( isURL && ( *idStart != '#' ))
    isURL = 0;

  /* Skip over the '#' sign */
  if ( isURL )
    idStart++;

  /* No URL specified? */
  if ( isURL && ( idStart == idEnd ))
    isURL = 0;

  /* Alternative or optionally a fallback color value */
  if      ( ParseColorLiteral( &aTextStart, &c             )) isRGB     = 1;
  else if ( ParseRGBFunc     ( &aTextStart, &c             )) isRGB     = 1;
  else if ( ParseColorName   ( &aTextStart, &c             )) isRGB     = 1;
  else if ( SkipName         ( &aTextStart, "currentColor" )) isCurrent = 1;
  else if ( SkipName         ( &aTextStart, "none"         )) isNone    = 1;

  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* The entire value has been processed */
  if ( aTextStart != aTextEnd )
    return;

  /* First generate fall-back commands for the case of an non existing
     gradient */
  if ( isNone )
    AppendInstruction( aDest, aOpCodeNone );

  /* Painint using externally defined color */
  else if ( isCurrent )
    AppendInstruction( aDest, aOpCodeCurrentColor );

  /* Painint using solid color */
  else if ( isRGB )
  {
    AppendInstruction( aDest, aOpCodeColor );
    AppendUInt32( aDest, c );
  }

  /* Then generate an command addressing the gradient element. Limit to
     store the id corresponding to its name. */
  if ( isURL )
  {
    int id = GetAtom( aAtomList, idStart, idEnd );

    /* Out of memory ... */
    if ( !id )
    {
      aDest->OutOfMemory++;
      return;
    }

    AppendInstruction( aDest, aOpCodeGradient );
    AppendUInt32( aDest, id );
  }
}


/* Verifies whether the XML content is a valid id as reference to other element.
   If successful generates a new command in aDest with the specified op-code
   aOpCode. Evtl. leading and final space signs are ignored. */
static void ParseSVGRef( const XChar* aTextStart, const XChar* aTextEnd,
  unsigned char aOpCode, XAtom** aAtomList, XBuffer* aDest )
{
  const XChar* idStart;
  const XChar* idEnd;
  int          id;

  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* Only locale references are supported */
  if ( *aTextStart != '#' )
    return;

  /* Skip over the leading '#' sign */
  idStart = ++aTextStart;

  /* Skip to the end of the identifier */
  while (( aTextStart < aTextEnd ) && !IsSpaceChar( *aTextStart ))
    aTextStart++;

  idEnd = aTextStart;

  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* The entire value has been processed */
  if ( aTextStart != aTextEnd )
    return;

  /* No identifier specified */
  if ( idStart == idEnd )
    return;

  id = GetAtom( aAtomList, idStart, idEnd );

  /* Out of memory ... */
  if ( !id )
  {
    aDest->OutOfMemory++;
    return;
  }

  AppendInstruction( aDest, aOpCode );
  AppendUInt32( aDest, id );
}


/* Verifies whether the XML content is a valid viewbox expression composed
   of four numbers separated by comma and/or spaces. If successful generates
   a new command in aDest with the aOpCode. Evtl. leading and final space
   signs are ignored. */
static void ParseSVGViewBox( const XChar* aTextStart, const XChar* aTextEnd,
  unsigned char aOpCode, XBuffer* aDest )
{
  float values[4];
  int   i;
  int   sep = 0;

  /* Skip over white space */
  SkipSpace( &aTextStart );

  for ( i = 0; i < 4; i++ )
    if ( ParseReal( &aTextStart, &values[i]))
      sep = SkipCommaSpace( &aTextStart );
    else
      break;

  /* Missing operands after a ',' sign */
  if (( sep == ',' ) || ( i != 4 ))
    return;

  SkipSpace( &aTextStart );

  /* The entire value has been processed */
  if ( aTextStart != aTextEnd )
    return;

  /* Negative values are not supported. */
  if (( values[2] < 0.0f ) || ( values[3] < 0.0f ))
    return;

  AppendInstruction( aDest, aOpCode );
  for ( i = 0; i < 4; i++ )
    AppendFloat( aDest, values[i]);
}


/* Verifies whether the XML content is a transformation expression. If
   successful, generates for each transformation the corresponding
   command in the aDest buffer. Any leading and final space signs are
   ignored. */
static void ParseSVGTransform( const XChar* aTextStart, const XChar* aTextEnd,
  XBuffer* aDest )
{
  XBuffer state;

  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* No transformation -> identity matrix */
  if ( IsXMLValue( aTextStart, aTextEnd, "none" ))
    return;

  /* Save the current state of the buffer */
  SaveBuffer( aDest, &state );

  /* At least one transformation is expected */
  if ( !ParseTransformFunc( &aTextStart, aDest ))
    return;

  /* ... can be followed by any number of further transformations. */
  do
    SkipSpace( &aTextStart );
  while ( ParseTransformFunc( &aTextStart, aDest ));

  /* If not the entire value has been processed - ignore the entire
     expression */
  if ( aTextStart != aTextEnd )
    RestoreBuffer( aDest, &state );
}


/* Verifies whether the XML content is a sequence of coordinate values.
   If successful, generates in aDest an command aOpCode followed by
   the coordinate values. Any leading and final space signs are ignored. */
static void ParseSVGPoints( const XChar* aTextStart, const XChar* aTextEnd,
  unsigned char aOpCode, XBuffer* aDest )
{
  unsigned int noOfOps = 0;
  int          sep     = 0;
  float        v;
  XBuffer      state1;
  XBuffer      state2;

  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* Save the buffer so it can be restored if an error is detected in the
     coordinate values. */
  SaveBuffer( aDest, &state1 );

  /* Generate dummy command and dummy 'no_of_points' operand */
  AppendInstruction( aDest, 0 );
  AppendUInt32( aDest, 0 );

  /* Process the nu,mbers as long as they follow */
  while ( ParseReal( &aTextStart, &v ))
  {
    AppendFloat( aDest, v );
    noOfOps++;
    sep = SkipCommaSpace( &aTextStart );
  }

  /* A value expected after ',' sign */
  if ( sep == ',' )
  {
    RestoreBuffer( aDest, &state1 );
    return;
  }

  /* No or odd number of operands results in an unsupported value. */
  if ( !noOfOps || ( noOfOps % 2 ))
  {
    RestoreBuffer( aDest, &state1 );
    return;
  }

  /* The entire value has been processed */
  if ( aTextStart != aTextEnd )
  {
    RestoreBuffer( aDest, &state1 );
    return;
  }

  /* The coordinate values are valid. Just complete the command */
  SaveBuffer( aDest, &state2 );
  RestoreBuffer( aDest, &state1 );
  AppendInstruction( aDest, aOpCode );
  AppendUInt32( aDest, noOfOps );
  RestoreBuffer( aDest, &state2 );
}


/* Verifies whether the XML content is a sequence of path formating commands.
   If successful, generates in aDest an command aOpCode followed by
   the formatting commands. Any leading and final space signs are ignored. */
static void ParseSVGString( const XChar* aTextStart, const XChar* aTextEnd,
  unsigned char aOpCode, XBuffer* aDest )
{
  XBuffer      state1;
  XBuffer      state2;
  unsigned int noOfDWords;
  unsigned int noOfSubPaths;

  /* Skip over white space */
  SkipSpace( &aTextStart );

  /* Nothing to process */
  if ( aTextStart >= aTextEnd )
    return;

  /* Generate the command and ensure that following commands are aligned
     at the next dword boundary */
  AppendInstruction( aDest, aOpCode );
  AlignBuffer( aDest );

  /* Save the buffer to update the values 'no_of_dwords' and 'no_of_sub_paths'
     later. For the moment 'no_of_dwords' and 'no_of_sub_paths' are unknown
     and 0 */
  SaveBuffer( aDest, &state1 );
  AppendUInt32( aDest, 0 );
  AppendUInt32( aDest, 0 );

  /* Process the commands. Note, if the path contains incorrect commands
     the parts processed already are retained. Limit to ignore the incorrect
     part. */
  noOfSubPaths = ParseSVGPath( &aTextStart, aDest, 0, 0 );

  /* Ensure the command following the path data is dword aligned */
  AlignBuffer( aDest );
  noOfDWords = (unsigned int)(( aDest->Ptr - aDest->Buffer ) -
                              ( state1.Ptr - state1.Buffer ));

  /* The path data is valid. Just complete the command */
  SaveBuffer( aDest, &state2 );
  RestoreBuffer( aDest, &state1 );
  AppendUInt32( aDest, noOfDWords - 1 );
  AppendUInt32( aDest, noOfSubPaths   );
  RestoreBuffer( aDest, &state2 );
}


/* Processes the SVG attribute with given name and content. If successful,
   op-codes for the attribute are generated in aDest. aTag identifies the
   type of the tag for which the attributes are evaluated. if aTag == -1
   the function limit to attributes which can be configured via CSS only. */
static void ParseSVGAttr( const XChar* aName, const XChar* aValueStart,
  const XChar* aValueEnd, int aTag, XBuffer* aDest,
  XAtom** aAtomList )
{
  const static char*         fillRuleOptions[]       =
    { "nonzero", "evenodd", 0 };
  const static char*         strokeLineCapOptions[]  =
    { "butt", "round", "square", 0 };
  const static char*         strokeLineJoinOptions[] =
    { "miter", "round", "bevel", 0 };
  const static char*         gradientUnitsOptions[]  =
    { "userSpaceOnUse", "objectBoundingBox", 0 };
  const static char*         vectorEffectOptions[]  =
    { "none", "non-scaling-stroke", 0 };
  const static unsigned char fillRuleOpCodes[]       =
    { EW_SVG_SetFillRule_NonZero, EW_SVG_SetFillRule_EvenOdd };
  const static unsigned char strokeLineCapOpCodes[]  =
    { EW_SVG_SetLineCap_Butt, EW_SVG_SetLineCap_Round,
      EW_SVG_SetLineCap_Square };
  const static unsigned char strokeLineJoinOpCodes[] =
    { EW_SVG_SetLineJoin_Miter, EW_SVG_SetLineJoin_Round,
      EW_SVG_SetLineJoin_Bevel };
  const static unsigned char gradientUnitsOpCodes[]  =
    { EW_SVG_SetGradientUnits_UserSpaceOnUse,
      EW_SVG_SetGradientUnits_ObjectBoundingBox };
  const static unsigned char vectorEffectOpCodes[]  =
    { EW_SVG_SetVectorEffect_None, EW_SVG_SetVectorEffect_NonScaling };

  /* Process the 'x' attribute. Valid for 'rect' and 'use' elements only. */
  if ((( aTag == 1 ) || ( aTag == 8 )) && IsXMLAttrWithName( aName, "x" ))
    ParseSVGCoordinate( aValueStart, aValueEnd, EW_SVG_SetX, aDest );

  /* Process the 'y' attribute. Valid for 'rect' and 'use' element only. */
  else if ((( aTag == 1 ) || ( aTag == 8 )) && IsXMLAttrWithName( aName, "y" ))
    ParseSVGCoordinate( aValueStart, aValueEnd, EW_SVG_SetY, aDest );

  /* Process the 'width' attribute. Valid for 'rect' and 'svg' element
     only. */
  else if ((( aTag == 1 ) || ( aTag == 12 )) &&
              IsXMLAttrWithName( aName, "width" ))
    ParseSVGLength( aValueStart, aValueEnd, EW_SVG_SetWidth, aDest );

  /* Process the 'height' attribute. Valid for 'rect' and 'svg' element
     only. */
  else if ((( aTag == 1 ) || ( aTag == 12 )) &&
              IsXMLAttrWithName( aName, "height" ))
    ParseSVGLength( aValueStart, aValueEnd, EW_SVG_SetHeight, aDest );

  /* Process the 'rx' attribute. Valid for 'rect' and 'ellipse' elements
     only. */
  else if ((( aTag == 1 ) || ( aTag == 3 )) &&
              IsXMLAttrWithName( aName, "rx" ))
    ParseSVGLength( aValueStart, aValueEnd, EW_SVG_SetRX, aDest );

  /* Process the 'ry' attribute. Valid for 'rect' and 'ellipse' elements
     only. */
  else if ((( aTag == 1 ) || ( aTag == 3 )) &&
              IsXMLAttrWithName( aName, "ry" ))
    ParseSVGLength( aValueStart, aValueEnd, EW_SVG_SetRY, aDest );

  /* Process the 'cx' attribute. Valid for 'circle', 'ellipse' and
     'radialGradient' elements only. */
  else if ((( aTag == 2 ) || ( aTag == 3 ) || ( aTag == 10 )) &&
              IsXMLAttrWithName( aName, "cx" ))
    ParseSVGCoordinate( aValueStart, aValueEnd, EW_SVG_SetCX, aDest );

  /* Process the 'cy' attribute. Valid for 'circle', 'ellipse' and
     'radialGradient' elements only. */
  else if ((( aTag == 2 ) || ( aTag == 3 ) || ( aTag == 10 )) &&
              IsXMLAttrWithName( aName, "cy" ))
    ParseSVGCoordinate( aValueStart, aValueEnd, EW_SVG_SetCY, aDest );

  /* Process the 'r' attribute. Valid for 'circle' and 'radialGradient'
     elements only. */
  else if ((( aTag == 2 ) || ( aTag == 10 )) &&
              IsXMLAttrWithName( aName, "r" ))
    ParseSVGLength( aValueStart, aValueEnd, EW_SVG_SetR, aDest );

  /* Process the 'x1' attribute. Valid for 'line' and 'linearGradient'
     elements only. */
  else if ((( aTag == 4 ) || ( aTag == 9 )) &&
              IsXMLAttrWithName( aName, "x1" ))
    ParseSVGCoordinate( aValueStart, aValueEnd, EW_SVG_SetX1, aDest );

  /* Process the 'y1' attribute. Valid for 'line' and 'linearGradient'
     elements only. */
  else if ((( aTag == 4 ) || ( aTag == 9 )) &&
              IsXMLAttrWithName( aName, "y1" ))
    ParseSVGCoordinate( aValueStart, aValueEnd, EW_SVG_SetY1, aDest );

  /* Process the 'x2' attribute. Valid for 'line' and 'linearGradient'
     elements only. */
  else if ((( aTag == 4 ) || ( aTag == 9 )) &&
              IsXMLAttrWithName( aName, "x2" ))
    ParseSVGCoordinate( aValueStart, aValueEnd, EW_SVG_SetX2, aDest );

  /* Process the 'y2' attribute. Valid for 'line' and 'linearGradient'
     elements only. */
  else if ((( aTag == 4 ) || ( aTag == 9 )) &&
              IsXMLAttrWithName( aName, "y2" ))
    ParseSVGCoordinate( aValueStart, aValueEnd, EW_SVG_SetY2, aDest );

  /* Process the 'opacity' attribute. Valid for all shape and 'g'
     elements. */
  else if (((( aTag >= 0 ) && ( aTag <= 8 )) || ( aTag == 12 ) ||
             ( aTag < 0 )) && IsXMLAttrWithName( aName, "opacity" ))
    ParseSVGOpacity( aValueStart, aValueEnd, EW_SVG_SetOpacity, aDest );

  /* Process the 'fill' attribute. Valid for all shape and 'g' elements. */
  else if (((( aTag >= 0 ) && ( aTag <= 8 )) || ( aTag == 12 ) ||
             ( aTag < 0 )) && IsXMLAttrWithName( aName, "fill" ))
    ParseSVGPaint( aValueStart, aValueEnd, EW_SVG_SetFillNone,
                   EW_SVG_SetFillColor, EW_SVG_SetFillCurrentColor,
                   EW_SVG_SetFillGradient, aAtomList, aDest );

  /* Process the 'fill-opacity' attribute. Valid for all shape and 'g'
     elements. */
  else if (((( aTag >= 0 ) && ( aTag <= 8 )) || ( aTag == 12 ) ||
             ( aTag < 0 )) && IsXMLAttrWithName( aName, "fill-opacity" ))
    ParseSVGOpacity( aValueStart, aValueEnd, EW_SVG_SetFillOpacity, aDest );

  /* Process the 'stroke' attribute. Valid for all shape and 'g' elements. */
  else if (((( aTag >= 0 ) && ( aTag <= 8 )) || ( aTag == 12 ) ||
             ( aTag < 0 )) && IsXMLAttrWithName( aName, "stroke" ))
    ParseSVGPaint( aValueStart, aValueEnd, EW_SVG_SetStrokeNone,
                   EW_SVG_SetStrokeColor, EW_SVG_SetStrokeCurrentColor,
                   EW_SVG_SetStrokeGradient, aAtomList, aDest );

  /* Process the 'stroke-opacity' attribute. Valid for all shape and 'g'
     elements. */
  else if (((( aTag >= 0 ) && ( aTag <= 8 )) || ( aTag == 12 ) ||
             ( aTag < 0 )) && IsXMLAttrWithName( aName, "stroke-opacity" ))
    ParseSVGOpacity( aValueStart, aValueEnd, EW_SVG_SetStrokeOpacity, aDest );

  /* Process the 'stroke-width' attribute. Valid for all shape and 'g'
     elements. */
  else if (((( aTag >= 0 ) && ( aTag <= 8 )) || ( aTag == 12 ) ||
             ( aTag < 0 )) && IsXMLAttrWithName( aName, "stroke-width" ))
    ParseSVGLength( aValueStart, aValueEnd, EW_SVG_SetStrokeWidth, aDest );

  /* Process the 'stroke-miterlimit' attribute. Valid for all shape and 'g'
     elements. */
  else if (((( aTag >= 0 ) && ( aTag <= 8 )) || ( aTag == 12 ) ||
             ( aTag < 0 )) && IsXMLAttrWithName( aName, "stroke-miterlimit" ))
    ParseSVGMiter( aValueStart, aValueEnd, EW_SVG_SetStrokeMiter, aDest );

  /* Process the 'fill-rule' attribute. Valid for all shape and 'g'
     elements. */
  else if (((( aTag >= 0 ) && ( aTag <= 8 )) || ( aTag == 12 ) ||
             ( aTag < 0 )) && IsXMLAttrWithName( aName, "fill-rule" ))
    ParseSVGOption( aValueStart, aValueEnd, fillRuleOptions, fillRuleOpCodes,
                    aDest );

  /* Process the 'stroke-linecap' attribute. Valid for all shape and 'g'
     elements. */
  else if (((( aTag >= 0 ) && ( aTag <= 8 )) || ( aTag == 12 ) ||
             ( aTag < 0 )) && IsXMLAttrWithName( aName, "stroke-linecap" ))
    ParseSVGOption( aValueStart, aValueEnd, strokeLineCapOptions,
                    strokeLineCapOpCodes, aDest );

  /* Process the 'stroke-linejoin' attribute. Valid for all shape and 'g'
     elements. */
  else if (((( aTag >= 0 ) && ( aTag <= 8 )) || ( aTag == 12 ) ||
             ( aTag < 0 )) && IsXMLAttrWithName( aName, "stroke-linejoin" ))
    ParseSVGOption( aValueStart, aValueEnd, strokeLineJoinOptions,
                    strokeLineJoinOpCodes, aDest );

  /* Process the 'vector-effect' attribute. Valid for all shape and 'g'
     elements. */
  else if (((( aTag >= 0 ) && ( aTag <= 8 )) || ( aTag == 12 )) && 
             IsXMLAttrWithName( aName, "vector-effect" ))
    ParseSVGOption( aValueStart, aValueEnd, vectorEffectOptions,
                    vectorEffectOpCodes, aDest );

  /* Process the 'gradientUnits' attribute. Valid for gradient elements
     only. */
  else if ((( aTag == 9 ) || ( aTag == 10 )) && 
              IsXMLAttrWithName( aName, "gradientUnits" ))
    ParseSVGOption( aValueStart, aValueEnd, gradientUnitsOptions,
                    gradientUnitsOpCodes, aDest );

  /* Process the 'offset' attribute. Valid for 'stop' element only. */
  else if ((( aTag == 11 ) || ( aTag < 0 )) &&
              IsXMLAttrWithName( aName, "offset" ))
    ParseSVGOpacity( aValueStart, aValueEnd, EW_SVG_SetOffset, aDest );

  /* Process the 'stop-color' attribute. Valid for 'stop' element only. */
  else if ((( aTag == 11 ) || ( aTag < 0 )) &&
              IsXMLAttrWithName( aName, "stop-color" ))
    ParseSVGColor( aValueStart, aValueEnd, EW_SVG_SetStopColor,
                   EW_SVG_SetStopCurrentColor, aDest );

  /* Process the 'stop-opacity' attribute. Valid for 'stop' element only. */
  else if ((( aTag == 11 ) || ( aTag < 0 )) &&
              IsXMLAttrWithName( aName, "stop-opacity" ))
    ParseSVGOpacity( aValueStart, aValueEnd, EW_SVG_SetStopOpacity, aDest );

  /* Process the 'viewBox' attribute. Valid for 'svg' element only. */
  else if (( aTag == 12 ) && IsXMLAttrWithName( aName, "viewBox" ))
    ParseSVGViewBox( aValueStart, aValueEnd, EW_SVG_SetViewBox, aDest );

  /* Process the 'points' attribute. Valid for 'polyline' and 'polygon'
     elements only. */
  else if ((( aTag == 5 ) || ( aTag == 6 )) && 
              IsXMLAttrWithName( aName, "points" ))
    ParseSVGPoints( aValueStart, aValueEnd, EW_SVG_SetPoints, aDest );

  /* Process the 'd' attribute. Valid for 'path' element only. */
  else if (( aTag == 7 ) && IsXMLAttrWithName( aName, "d" ))
    ParseSVGString( aValueStart, aValueEnd, EW_SVG_SetPath, aDest );

  /* Process the 'transform' attribute. Valid for all shape elements and
     'g' element. */
  else if (( aTag >= 0 ) && ( aTag <= 8 ) && 
             IsXMLAttrWithName( aName, "transform" ))
    ParseSVGTransform( aValueStart, aValueEnd, aDest );

  /* Process the 'gradientTransform' attribute. Valid for all gradient
     elements only. */
  else if ((( aTag == 9 ) || ( aTag == 10 )) && 
             IsXMLAttrWithName( aName, "gradientTransform" ))
    ParseSVGTransform( aValueStart, aValueEnd, aDest );

  /* Process the 'href' attribute. Valid for 'use' element only. */
  else if (( aTag == 8 ) && IsXMLAttrWithName( aName, "href" ))
    ParseSVGRef( aValueStart, aValueEnd, EW_SVG_SetRef, aAtomList, aDest );

  else if (( aTag == 8 ) && IsXMLAttrWithName( aName, "xlink:href" ))
    ParseSVGRef( aValueStart, aValueEnd, EW_SVG_SetRef, aAtomList, aDest );
}


/* Verifies whether the XML content as a sequence of CSS attributes. If
   successful, generates in aDest commands corresponding to the attributes.
   Any leading and final space signs are ignored. */
static void ParseStyle( const XChar* aTextStart, const XChar* aTextEnd,
  XBuffer* aDest, XAtom** aAtomList )
{
  /* Process the entier content of the 'styles' attribute */
  while ( aTextStart < aTextEnd )
  {
    const XChar* name       = 0;
    const XChar* valueStart = 0;
    const XChar* valueEnd   = 0;
    int          isColon    = 0;

    /* Skip over white space */
    SkipSpace( &aTextStart );

    /* Begining of an attribute name? */
    if (( aTextStart < aTextEnd ) && IsNameStartChar( *aTextStart ))
      name = aTextStart;

    /* Skip to the end of the attribute name */
    while (( aTextStart < aTextEnd ) && IsNameChar( *aTextStart ))
      aTextStart++;

    /* Skip over white space */
    SkipSpace( &aTextStart );

    /* Name : Value separator? */
    if (( aTextStart < aTextEnd ) && ( *aTextStart == ':' ))
    {
      isColon = 1;
      aTextStart++;
    }

    /* Skip over white space */
    SkipSpace( &aTextStart );

    /* Begining of a value? */
    if (( aTextStart < aTextEnd ) && ( *aTextStart != ';' ))
      valueStart = aTextStart;

    /* Skip to the end of the value */
    while (( aTextStart < aTextEnd ) && ( *aTextStart != ';' ))
      aTextStart++;

    /* Where does the value end */
    if ( valueStart )
      valueEnd = aTextStart;

    /* An attribute found? Process it */
    if ( name && isColon && valueStart && valueEnd )
      ParseSVGAttr( name, valueStart, valueEnd, -1, aDest, aAtomList );

    /* Skip over the ';' */
    if (( aTextStart < aTextEnd ) && ( *aTextStart == ';' ))
      aTextStart++;
  }
}


/* Verifies whether the XML content as a sequence of CSS attributes. If
   successful, generates in aDest commands corresponding to the attributes.
   aTag identifies the type of the tag for which the attributes are
   evaluated. Any leading and final space signs are ignored. */
static void ParseCSS( const XChar* aTextStart, const XChar* aTextEnd,
  XBuffer* aDest, XAtom** aAtomList )
{
  /* The order of names within this array has to correspond to the array
     in the function ParseSVG(). Unique peculiarity is the leading '*'
     name */
  static const char* tagNames[] =
    { "*",              "g",              "rect",    "circle",  "ellipse",
      "line",           "polyline",       "polygon", "path",    "use",
      "linearGradient", "radialGradient", "stop",    "svg",     0 };

  /* Process the entire content of the 'styles' attribute. It can be composed of
     multiple style definitions, each starting with multiple CSS selectors */
  while ( aTextStart < aTextEnd )
  {
    const XChar* contentStart = 0;
    const XChar* contentEnd   = 0;
    int          selCount     = 0;
    XBuffer      state;

    /* Save the state of the buffer to rever it in case of an error in the CSS */
    SaveBuffer( aDest, &state );

    /* Indicate the beginning of CSS style definition */
    AlignBuffer( aDest );
    AppendInstruction( aDest, EW_SVG_EnterStyle );

    /* Parse a list of comma separated CSS selectors */
    while ( aTextStart < aTextEnd )
    {
      const XChar* elementStart = 0;
      const XChar* classStart   = 0;
      const XChar* idStart      = 0;
      const XChar* selEnd       = 0;
      int          elementId    = -1;
      int          classAtom    = 0;
      int          idAtom       = 0;

      /* Skip over white space */
      SkipSpace( &aTextStart );

      /* Start of the element name in the selector? */
      if (( aTextStart < aTextEnd ) && ( IsAlphaChar( *aTextStart ) ||
          ( *aTextStart == '*' )))
        elementStart = aTextStart;

      /* Search for the next selector component. It can be the class or id */
      while (( aTextStart < aTextEnd ) && !IsSpaceChar( *aTextStart ) && 
             ( *aTextStart != '.' ) && ( *aTextStart != '#' ) &&
             ( *aTextStart != '{' ) && ( *aTextStart != '}' ) &&
             ( *aTextStart != ',' ))
        aTextStart++;

      /* Is it the beginning of the class name in the selector? */
      if (( aTextStart < aTextEnd ) && ( *aTextStart == '.' ))
        classStart = aTextStart;

      /* Search for the next selector component. It can be the id */
      while (( aTextStart < aTextEnd ) && !IsSpaceChar( *aTextStart ) && 
             ( *aTextStart != '#' ) && ( *aTextStart != '{' ) &&
             ( *aTextStart != '}' ) && ( *aTextStart != ',' ))
        aTextStart++;

      /* Is it beginning of the id in the selector? */
      if (( aTextStart < aTextEnd ) && ( *aTextStart == '#' ))
        idStart = aTextStart;

      /* Search for the end of the selector. It can be the id */
      while (( aTextStart < aTextEnd ) && !IsSpaceChar( *aTextStart ) && 
             ( *aTextStart != '{' ) && ( *aTextStart != '}' )  &&
             ( *aTextStart != ',' ))
        aTextStart++;

      /* Remember the end position of the selector */
      if ( elementStart || classStart || idStart )
        selEnd = aTextStart;

      /* Skip over white space */
      SkipSpace( &aTextStart );

      /* The content of the style definition or further selector expected */
      if (( aTextStart >= aTextEnd ) || (( *aTextStart != '{' ) &&
          ( *aTextStart != ',' )))
      {
        RestoreBuffer( aDest, &state );
        return;
      }

      /* Determine the element component in the selector */
      if ( elementStart && selEnd )
      {
        const XChar* elementEnd = selEnd;

        if ( idStart    ) elementEnd = idStart;
        if ( classStart ) elementEnd = classStart;

        /* Evaluate the specified element name. If not valid, ignore the selector */
        if (( elementId = FindToken( elementStart, elementEnd, tagNames )) < 0 )
          selEnd = 0;
      }

      /* Determine the class component in the selector */
      if ( classStart && selEnd )
      {
        const XChar* classEnd = idStart? idStart : selEnd;

        /* Skip over the leading '.' sign. */
        if (( classEnd - ++classStart ) > 0 )
        {
          /* No memory to store the atoms. Abort */
          if ( !( classAtom = GetAtom( aAtomList, classStart, classEnd )))
          {
            RestoreBuffer( aDest, &state );
            aDest->OutOfMemory++;
            return;
          }
        }

        /* Invalid class component in the selector. Ignore this style definition */
        else
          selEnd = 0;
      }

      /* Determine the id component in the selector */
      if ( idStart && selEnd )
      {
        /* Skip over the leading '#' sign. */
        if (( selEnd - ++idStart ) > 0 )
        {
          /* No memory to store the atoms */
          if ( !( idAtom = GetAtom( aAtomList, idStart, selEnd )))
          {
            RestoreBuffer( aDest, &state );
            aDest->OutOfMemory++;
            return;
          }
        }

        /* Invalid id component in the selector. Ignore this style definition */
        else
          selEnd = 0;
      }

      /* Store the element component of the selector. Note: value 0 represents
         the wildcard selector. Values > 0 the respective tags as found in the
         arra 'tagNames' */
      if (( elementId >= 0 ) && selEnd )
      {
        AppendInstruction( aDest, EW_SVG_SetElement );
        AppendUInt32( aDest, elementId );
        selCount++;
      }

      /* Store the class component of the selector. */
      if (( classAtom ) && selEnd )
      {
        AppendInstruction( aDest, EW_SVG_SetClass );
        AppendUInt32( aDest, classAtom );
        selCount++;
      }

      /* Store the id component of the selector. */
      if ( idAtom && selEnd )
      {
        AppendInstruction( aDest, EW_SVG_SetId );
        AppendUInt32( aDest, idAtom );
        selCount++;
      }

      /* Instruction to trigger the selector evaluation */
      if ( selCount )
        AppendInstruction( aDest, EW_SVG_SelectCSS );

      /* No further selector to process */
      if (( aTextStart >= aTextEnd ) || ( *aTextStart != ',' ))
        break;

      /* Skip over the ',' sign */
      aTextStart++;
    }

    /* Start of the style content? */
    if (( aTextStart < aTextEnd ) && ( *aTextStart == '{' ))
    {
      /* Position where the content begins */
      contentStart = ++aTextStart;

      /* Search for the end of the content */
      while (( aTextStart < aTextEnd ) && ( *aTextStart != '}' ))
        aTextStart++;

      /* End of the content found? */
      if (( aTextStart < aTextEnd ) && ( *aTextStart == '}' ))
        contentEnd = aTextStart;

      /* Skip over the '}' sign */
      aTextStart++;
    }

    /* Process the content? Do this only when there was at least one selector
       generated. */
    if (( contentEnd > contentStart ) && selCount )
    {
      ParseStyle( contentStart, contentEnd, aDest, aAtomList );
      AppendInstruction( aDest, EW_SVG_LeaveStyle );
    }

    /* ... otherwise discard the CSS style definition */
    else
      RestoreBuffer( aDest, &state );
  }
}


/* This function parses an SVG document found in aText. If the function was
   successful, the function returns a value != 0. In error case the variables
   aErrorCode and aErrorPos describe the error and its position relative to
   the beginning of aText. */
static int ParseSVG( const XChar* aText, XBuffer* aDest,
  XAtom** aAtomList, int* aErrorCode, int* aErrorPos )
{
  /* When modifying the order of names in this array adapt the numbers in if
     conditions below. Note also the order of defines EW_SVG_EnterXXX and
     EW_SVG_LeaveXXX also correspond to the order of the names below. */
  static const char*         tagNames[] =
    { "g",               "rect",     "circle",  "ellipse",  "line",
      "polyline",        "polygon",  "path",    "use",      "linearGradient",
      "radialGradient",  "stop",     "svg",     "defs",     "style",
      "/g",              "/rect",    "/circle", "/ellipse", "/line",
      "/polyline",       "/polygon", "/path",   "/use",     "/linearGradient",
      "/radialGradient", "/stop",    "/svg",    "/defs",    "/style", 0 };

  /* Stack to track the nested SVG tags */
  signed char  stack[ 32 ];
  signed char* stackTop = stack;
  const XChar* start    = aText;
  const XChar* cssStart = 0;
  int          dummyG   = 1;

  /* State of the buffer representing the recently opened element. */
  XBuffer      startOfElement = { 0 };

  /* An SVG file may start with an '<?xml ...' tag */
  if ( IsXMLTagWithName( aText, "?xml" ))
    aText = FindNextXMLTag( aText );

  /* Is it an SVG data? */
  if ( !IsXMLTagWithName( aText, "svg" ))
    goto SVG_ERROR;

  /* Process all SVG elements */
  do
  {
    int          tag        = IsXMLTagWithNames( aText, tagNames );
    const XChar* styleStart = 0;
    const XChar* styleEnd   = 0;

    /* Phase 1: Validate the just found tag. Tags which are not expected are
       skipped over  */

    /* <svg> element is allowed only at the root level. The stack has to be
       empty at this moment. */
    if (( tag == 12 ) && ( stackTop > stack ))
      tag = -1;

    /* <defs> element is allowed inside <svg> element only. */
    else if (( tag == 13 ) && (( stackTop == stack ) || ( stackTop[-1] != 12 )))
      tag = -1;

    /* Shape and <g> elements are allowed inside <svg>, <defs> or <g> elements
       only. */
    else if (( tag >= 0 ) && ( tag <= 7 ) && 
            (( stackTop == stack ) || (( stackTop[-1] != 0  ) && 
             ( stackTop[-1] != 12 ) && ( stackTop[-1] != 13 ))))
      tag = -1;

    /* <use> elements are allowed inside <svg> or <g> elements only. */
    else if (( tag == 8 ) && 
            (( stackTop == stack ) || (( stackTop[-1] != 0 ) && 
             ( stackTop[-1] != 12 ))))
      tag = -1;

    /* Gradient elements are allowed inside all elements except <style>. Nesting
       of gradient elements is not supported. */
    else if (( tag >= 9 ) && ( tag <= 10 ) && 
            (( stackTop == stack )  || ( stackTop[-1]  < 0 ) ||
             ( stackTop[-1] == 14 ) || ( stackTop[-1] == 9 ) ||
             ( stackTop[-1] == 10 )))
      tag = -1;

    /* <stop> element is allowed inside gradient elements only. */
    else if (( tag == 11 ) && 
            (( stackTop == stack ) || (( stackTop[-1] != 9 ) &&
             ( stackTop[-1] != 10 ))))
      tag = -1;

    /* <style> element is allowed inside any element. However for the simplicity
       nesting of <style> elements is not supported */
    else if (( tag == 14 ) && 
            (( stackTop == stack ) || (( stackTop[-1] < 0 ) ||
             ( stackTop[-1] > 13 ))))
      tag = -1;

    /* End tags are allowed only as counter parts to their start tags */
    else if (( tag >= 15 ) && (( stackTop == stack ) || 
                               ( stackTop[-1] != ( tag - 15 ))))
      goto XML_ERROR;

    /* The tag is not supported or it is misplaced. Skip over the element. */
    if ( tag < 0 )
    {
      aText = FindXMLEndTag( aText );

      /* No tag could be found? */
      if ( !*aText || ( *aText != '<' ))
        goto XML_ERROR;

      continue;
    }

    /* Too many nested elements? */
    if (( tag <= 14 ) && (( stackTop - stack ) == sizeof( stack )))
        goto STACK_OVERFLOW;

    /* Track the tags on a tag stack */
    if ( tag <= 14 )
      *stackTop++ = (signed char)tag;

    /* Processing the first element other than the <svg> root element itself.
       Synthese a dummy <g> element to enclose all shapes inside. This dummy
       group is used to handle semi-transparance if such is defined at the
       <svg> root element */
    if (( tag != 12 ) && dummyG )
    {
      AppendInstruction( aDest, EW_SVG_EnterG );
      dummyG = 0;
    }

    /* Generate an command for the beginning of an element. In order to
       simply refer named elements, align the buffer to the next dword in order
       to get an offset where the corresponding command will start. Note:
       'style' element is handled separately. */
    if ( tag <= 13 )
    {
      AlignBuffer( aDest );
      SaveBuffer( aDest, &startOfElement );
      AppendInstruction( aDest, EW_SVG_EnterG + tag );
    }

    /* Beginning of an element? Reset state variables */
    if ( tag <= 14 )
      cssStart = 0;

    /* Beginning of a <style> element? Remember a pointer to the first character
       inside this element */
    if ( tag == 14 )
    {
      const XChar* ptr = FindEndOfXMLTag( aText );

      if ( *ptr == '>' )
        cssStart = ptr + 1;
    }

    /* No sufficient memory to enlarge the buffer */
    if ( aDest->OutOfMemory )
      goto OUT_OF_MEMORY;

    /* Phase 2: Process the attributes of the just found tag. Decode their
       values and generate corresponding commands in the buffer. */

    /* Process all attributes belonging to the tag. Ignore end tags. */
    while (( tag <= 14 ) && *( aText = FindNextXMLAttr( aText )) &&
             IsNameStartChar( *aText ))
    {
      const XChar* valueStart = FindNextXMLValue( aText );
      const XChar* valueEnd   = FindEndOfXMLValue( valueStart );

      /* Is the value correct? If not, ignore the attribute. */
      if ((( *valueStart != '"' ) && ( *valueEnd != '\'' )) ||
           ( *valueStart != *valueEnd ))
      {
        aText = valueEnd;
        continue;
      }

      /* Skip over the leading quote sign. valueStart..valueEnd shoult refer
         the content of the attribute only. */
      valueStart++;

      /* Process the 'id' attribute. Valid for all shape and gradient elements.
         Store the id as unique number. */
      if (( tag >= 0 ) && ( tag <= 11 ) && IsXMLAttrWithName( aText, "id" ))
      {
        int id = GetAtom( aAtomList, valueStart, valueEnd );

        /* No memory to store a new atom */
        if ( !id )
          goto OUT_OF_MEMORY;

        /* Generate an instruction to set the id */
        AppendInstruction( aDest, EW_SVG_SetId );
        AppendUInt32( aDest, id );
      }

      /* Process the 'class' attribute. Valid for all shape and gradient elements.
         Store the class name as unique number. */
      else if (( tag >= 0 ) && ( tag <= 11 ) &&
                 IsXMLAttrWithName( aText, "class" ))
      {
        int id = GetAtom( aAtomList, valueStart, valueEnd );

        /* No memory to store a new atom */
        if ( !id )
          goto OUT_OF_MEMORY;

        /* Generate an instruction to set the class */
        AppendInstruction( aDest, EW_SVG_SetClass );
        AppendUInt32( aDest, id );
      }

      /* Process the 'style' attribute. The contained list of CSS attributes
         should be evaluated similarly to regular XML attributes. The
         evaluation, however, should occur when all other attributes of the
         element are processed. */
      else if (( tag >= 0 ) && ( tag <= 13 ) &&
                 IsXMLAttrWithName( aText, "style" ))
      {
        styleStart = valueStart;
        styleEnd   = valueEnd;
      }

      /* Process all other attributes */
      else if ( tag <= 13 )
        ParseSVGAttr( aText, valueStart, valueEnd, tag, aDest,
                      aAtomList );

      /* No sufficient memory to enlarge the buffer */
      if ( aDest->OutOfMemory )
        goto OUT_OF_MEMORY;

      /* The next attribute starts after the value */
      aText = valueEnd;
    }

    /* All attributes of a starting tag have been processed. Trigger the evtl.
       evaluation of CSS. */
    if (( tag >= 0 ) && ( tag <= 13 ))
      AppendInstruction( aDest, EW_SVG_ProcessCSS );

    /* If the element had own CSS styles defined, process them as last step. */
    if ( styleStart && styleEnd )
      ParseStyle( styleStart, styleEnd, aDest, aAtomList );

    /* End of <style> element? Parse the style definitions found inside
       the element. */
    if (( tag == 29 ) && cssStart )
      ParseCSS( cssStart, aText, aDest, aAtomList );

    /* The <svg> contains always an embedded <g> element. Leave the <g>
       element when leaving <svg> element */
    if ( tag == 27 )
      AppendInstruction( aDest, EW_SVG_LeaveG );

    /* Generate a command at the end of an element */
    if (( tag >= 15 ) && ( tag < 29 ))
      AppendInstruction( aDest, EW_SVG_LeaveG + tag - 15 );

    /* Is it an end tag? Restore the preceding state. */
    if ( tag >= 15 )
      stackTop--;

    /* Is it an empty element? Restore the preceding state. */
    else if (( *aText == '/' ) && ( tag <= 13 ))
    {
      AppendInstruction( aDest, EW_SVG_LeaveG + tag );
      stackTop--;
    }

    /* End tags are not parsed for attributes. Just skip to the end of the tag */
    if ( tag >= 15 )
    {
      if ( *( aText = FindEndOfXMLTag( aText )) != '>' )
        goto XML_ERROR;
    }
  }
  while ( *( aText = FindNextXMLTag( aText )) == '<' );

  /* Any open elements? Then it is an error. */
  if ( stackTop != stack )
    goto XML_ERROR;

  /* Terminate the sequence */
  AlignBuffer( aDest );
  AppendInstruction( aDest, EW_SVG_NoOp );

  /* Everything is o.k. */
  if ( !aDest->OutOfMemory )
    return 1;

  OUT_OF_MEMORY:
  {
    if ( aErrorCode ) *aErrorCode = EW_SVG_PARSER_OUT_OF_MEMORY;
    if ( aErrorPos  ) *aErrorPos  = (int)( aText - start );
    return 0;
  }

  STACK_OVERFLOW:
  {
    if ( aErrorCode ) *aErrorCode = EW_SVG_PARSER_OUT_OF_MEMORY;
    if ( aErrorPos  ) *aErrorPos  = (int)( aText - start );
    return 0;
  }

  SVG_ERROR:
  {
    if ( aErrorCode ) *aErrorCode = EW_SVG_PARSER_SYNTAX_ERROR;
    if ( aErrorPos  ) *aErrorPos  = (int)( aText - start );
    return 0;
  }

  XML_ERROR:
  {
    if ( aErrorCode ) *aErrorCode = EW_SVG_PARSER_SYNTAX_ERROR;
    if ( aErrorPos  ) *aErrorPos  = (int)( aText - start );
    return 0;
  }
}

#endif /* EW_DONT_USE_SVG_READER */


/* Exclude SVG functionality? */
#ifndef EW_DONT_USE_SVG_FUNCTIONS

/* This helper function estimates the number of operands in aData belonging to
   the command with the given aOpCode. */
static int GetNoOfOperands( const unsigned int* aData, int aOpCode )
{
  /* Instructions involving one operand. Skip over the operands. */
  if ((( aOpCode >= EW_SVG_SetId              ) &&
       ( aOpCode <= EW_SVG_SetElement        )) ||
      (( aOpCode >= EW_SVG_SetX               ) &&
       ( aOpCode <= EW_SVG_SetStrokeMiter    )) ||
      (( aOpCode >= EW_SVG_SetFillGradient    ) &&
       ( aOpCode <= EW_SVG_SetStrokeGradient )) ||
      (( aOpCode >= EW_SVG_SetFillColor       ) && 
       ( aOpCode <= EW_SVG_SetStopColor      )) ||
      (( aOpCode >= EW_SVG_SetOpacity         ) &&
       ( aOpCode <= EW_SVG_SetStopOpacity    )) ||
      (( aOpCode >= EW_SVG_Translate1         ) &&
       ( aOpCode <= EW_SVG_SkewY             )) ||
       ( aOpCode == EW_SVG_SetOffset         )  ||
       ( aOpCode == EW_SVG_SetRef            ))
    return 1;

  /* Instructions involving two operands. Skip over the operands. */
  if (( aOpCode >= EW_SVG_Translate2 ) && ( aOpCode <= EW_SVG_Scale2 ))
    return 2;

  /* Instructions involving three operands. Skip over the operands. */
  if ( aOpCode == EW_SVG_Rotate3 )
    return 3;

  /* Instructions involving four operands. Skip over the operands. */
  if ( aOpCode == EW_SVG_SetViewBox )
    return 4;

  /* Instructions involving six operands. Skip over the operands. */
  if ( aOpCode == EW_SVG_Matrix )
    return 6;

  /* Instruction involving dynamic number of operands */
  else if (( aOpCode == EW_SVG_SetPoints ) || ( aOpCode == EW_SVG_SetPath ))
  {
    int useReader = USE_FLASH_READER( aData );
    return UINT32( aData ) + 1;
  }

  return 0;
}


/* The following function allocates memory for a new state and stores it in the
   state list aState. If successful returns a pointer to the new state. */
static XSVGState* PushState( XSVGState** aState )
{
  XSVGState* state;

  /* Allocate memory for a new stack entry */
  do
    state = EwAlloc( sizeof( XSVGState ));
  while ( !state && EwImmediateReclaimMemory( 66 ));

  /* Report a message if there is no more memory */
  if ( !state )
  {
    EwError( 66 );
    return 0;
  }

  /* Copy the content of the recent state or initialize the first state? */
  if ( *aState )
  {
    EwCopy( state, *aState, sizeof( *state ));
    state->IdAtom = 0;
  }
  else
  {
    EwZero( state, sizeof( *state ));
    state->FillPaintMode   = PaintMode_Color;
    state->FillColor.Alpha = 255;
    state->Opacity         = 255;
    state->FillOpacity     = 255;
    state->StrokeOpacity   = 255;
    state->StrokeWidth     = 1.0f;
    state->StrokeMiter     = 4.0f;
    state->StopColor.Alpha = 255;
    state->StopOpacity     = 255;
    state->Matrix[0]       = 1.0f;
    state->Matrix[4]       = 1.0f;
  }

  /* Manage the states in a list */
  state->Next = *aState;
  *aState     = state;

  /* Track the temporary used memory */
  EwResourcesMemory += sizeof( XSVGState );

  /* Also track the max. memory pressure */
  if ( EwResourcesMemory > EwResourcesMemoryPeak )
    EwResourcesMemoryPeak = EwResourcesMemory;

  if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
    EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

  /* All o.k. */
  return state;
}


/* The following function frees memory for the top most state and restores
   the preceding state. Returns a pointer to the new state. */
static XSVGState* PopState( XSVGState** aState )
{
  XSVGState* tmp = *aState;

  *aState = tmp? tmp->Next : 0;

  /* The just popped state used a tempo. created bitmap. Release the bitmap */
  if ( tmp->Dst && *aState && ((*aState)->Dst != tmp->Dst ))
  {
    EwFreeBitmap( tmp->Dst );
    tmp->Dst = 0;
  }

  /* Free the memory */
  if ( tmp )
  {
    EwFree( tmp );
    EwResourcesMemory -= sizeof( XSVGState );
  }

  return *aState;
}


/* Multiplies aMatrix1 with aMatrix2 and stores the results in aMatrix1. */
static void MultiplyMatrix( float aMatrix1[6], float aMatrix2[6])
{
  float nm[6];

  /* Avoid time intensive multiplication with an identity matrix. */
  if (( aMatrix2[0] == 1.0f ) && ( aMatrix2[1] == 0.0f ) &&
      ( aMatrix2[2] == 0.0f ) && ( aMatrix2[3] == 0.0f ) &&
      ( aMatrix2[4] == 1.0f ) && ( aMatrix2[5] == 0.0f ))
    return;

  /* Avoid time intensive multiplication with an identity matrix. */
  if (( aMatrix1[0] == 1.0f ) && ( aMatrix1[1] == 0.0f ) &&
      ( aMatrix1[2] == 0.0f ) && ( aMatrix1[3] == 0.0f ) &&
      ( aMatrix1[4] == 1.0f ) && ( aMatrix1[5] == 0.0f ))
  {
    EwCopy( aMatrix1, aMatrix2, sizeof( float ) * 6 );
    return;
  }

  /* Multiply the matrices */
  nm[0]        = ( aMatrix1[0] * aMatrix2[0]) + ( aMatrix1[1] * aMatrix2[3]);
  nm[1]        = ( aMatrix1[0] * aMatrix2[1]) + ( aMatrix1[1] * aMatrix2[4]);
  aMatrix1[2] += ( aMatrix1[0] * aMatrix2[2]) + ( aMatrix1[1] * aMatrix2[5]);
  nm[3]        = ( aMatrix1[3] * aMatrix2[0]) + ( aMatrix1[4] * aMatrix2[3]);
  nm[4]        = ( aMatrix1[3] * aMatrix2[1]) + ( aMatrix1[4] * aMatrix2[4]);
  aMatrix1[5] += ( aMatrix1[3] * aMatrix2[2]) + ( aMatrix1[4] * aMatrix2[5]);
  aMatrix1[0]  = nm[0];
  aMatrix1[1]  = nm[1];
  aMatrix1[3]  = nm[3];
  aMatrix1[4]  = nm[4];
}


/* Creates a new path object representing a rectangle with sharp corners. If
   aBoundingBox != 0, the parameter is used as array of 4 entries to track
   the x1,y1,x2,y2 coordinates of the bounding box surrounding the shape.
   If the rectangle is empty (its size is 0), no path is created and the
   function returns 0. */
static XPath* CreateRect( float aMatrix[6], float aX, float aY, float aWidth,
  float aHeight, float* aBoundingBox )
{
  XPath* path;

  /* Does the rectangle have an area? */
  if (( aWidth <= 0.0f ) || ( aHeight <= 0.0f ))
    return 0;

  /* Create a new path object */
  if ( !( path = EwCreatePath( 1 )))
    return 0;

  /* Set the transformation matrix for the path coordinates */
  EwSetPathMatrix( path, aMatrix[0], aMatrix[1], aMatrix[2], aMatrix[3],
                   aMatrix[4], aMatrix[5]);

  /* Compose the path from straight line segments */
  EwInitSubPath   ( path, 0, 4 );
  EwBeginSubPath  ( path, 0, aX, aY );
  EwAddSubPathLine( path, 0, aX + aWidth, aY );
  EwAddSubPathLine( path, 0, aX + aWidth, aY + aHeight );
  EwAddSubPathLine( path, 0, aX,          aY + aHeight );
  EwCloseSubPath  ( path, 0 );

  /* Track the bounding box surrounding the shape */
  if ( aBoundingBox )
  {
    aBoundingBox[0] = MIN( aX,           aBoundingBox[0]);
    aBoundingBox[1] = MIN( aY,           aBoundingBox[1]);
    aBoundingBox[2] = MAX( aX + aWidth,  aBoundingBox[2]);
    aBoundingBox[3] = MAX( aY + aHeight, aBoundingBox[3]);
  }

  return path;
}


/* Creates a new path object representing a rectangle with rounded corners. If
   aBoundingBox != 0, the parameter is used as array of 4 entries to track the
   x1,y1,x2,y2 coordinates of the bounding box surrounding the shape. If the
   rectangle is empty (its size is 0), no path is created and the function
   returns 0. */
static XPath* CreateRoundedRect( float aMatrix[6], float aX, float aY, float aWidth,
  float aHeight, float aRX, float aRY, float* aBoundingBox )
{
  float  width2  = aWidth  * 0.5f;
  float  height2 = aHeight * 0.5f;
  float  pixelRX;
  float  pixelRY;
  float  pixel;
  int    noOfEdges;
  XPath* path;

  /* Does the rectangle have an area? */
  if (( aWidth <= 0.0f ) || ( aHeight <= 0.0f ))
    return 0;

  /* Create a new path object */
  if ( !( path = EwCreatePath( 1 )))
    return 0;

  /* Align the horizontal and vertical radius values */
  if ( aRX == 0.0f ) aRX = aRY;
  if ( aRY == 0.0f ) aRY = aRX;

  /* Limit the radius to the half of the rectangle edge */
  aRX = MIN( aRX, width2  );
  aRY = MIN( aRY, height2 );

  /* Estimate the average length of a radius in pixel by taking in account the
     effect of the transformation matrix. */
  pixelRX = aRX * aMatrix[0] + aRY * aMatrix[1];
  pixelRY = aRX * aMatrix[3] + aRY * aMatrix[4];
  pixel   = EwMathSqrt( pixelRX * pixelRX + pixelRY * pixelRY );

  /* Estimate the necessary number of edges for a single rounded corner. Note,
     the bigger the radius of an arc, the longer can be the edges of. */
  noOfEdges = 1 + ( 90 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( pixel + 1 ))));

  /* Set the transformation matrix for the path coordinates */
  EwSetPathMatrix( path, aMatrix[0], aMatrix[1], aMatrix[2], aMatrix[3],
                   aMatrix[4], aMatrix[5]);

  /* Compose the path from 4 arcs */
  EwInitSubPath   ( path, 0, noOfEdges * 4 + 4 );
  EwAddSubPathArc ( path, 0, aX + aRX, aY + aRY, aRX, aRY, 180.0f, 270.0f,
                    noOfEdges );
  EwAddSubPathArc ( path, 0, aX + aWidth - aRX, aY + aRY, aRX, aRY, 270.0f,
                    360.0f, noOfEdges );
  EwAddSubPathArc ( path, 0, aX + aWidth - aRX, aY + aHeight - aRY, aRX, aRY,
                    0.0f, 90.0f, noOfEdges );
  EwAddSubPathArc ( path, 0, aX + aRX, aY + aHeight - aRY, aRX, aRY, 90.0f,
                    180.0f, noOfEdges );
  EwCloseSubPath  ( path, 0 );

  /* Track the bounding box surrounding the shape */
  if ( aBoundingBox )
  {
    aBoundingBox[0] = MIN( aX,           aBoundingBox[0]);
    aBoundingBox[1] = MIN( aY,           aBoundingBox[1]);
    aBoundingBox[2] = MAX( aX + aWidth,  aBoundingBox[2]);
    aBoundingBox[3] = MAX( aY + aHeight, aBoundingBox[3]);
  }

  return path;
}


/* Creates a new path object representing an ellipsis. If aBoundingBox != 0, the
   parameter is used as array of 4 entries to track the x1,y1,x2,y2 coordinates
   of the bounding box surrounding the shape. If the ellipsis is empty
   (radius <= 0), no path is created and the function returns 0. */
static XPath* CreateEllipse( float aMatrix[6], float aCX, float aCY, float aRX,
  float aRY, float* aBoundingBox )
{
  float  pixelRX;
  float  pixelRY;
  float  pixel;
  int    noOfEdges;
  XPath* path;

  /* Does the ellipse have an area? */
  if (( aRX <= 0.0f ) && ( aRY <= 0.0f ))
    return 0;

  /* Create a new path object */
  if ( !( path = EwCreatePath( 1 )))
    return 0;

  /* Align the horizontal and vertical radius values */
  if ( aRX == 0.0f ) aRX = aRY;
  if ( aRY == 0.0f ) aRY = aRX;

  /* Estimate the average length of a radius in pixel by taking in account the
     effect of the transformation matrix. */
  pixelRX = aRX * aMatrix[0] + aRY * aMatrix[1];
  pixelRY = aRX * aMatrix[3] + aRY * aMatrix[4];
  pixel   = EwMathSqrt( pixelRX * pixelRX + pixelRY * pixelRY );

  /* Estimate the necessary number of edges for the entire ellipsis. Note,
     the bigger the radius of an arc, the longer can be the edges of. */
  noOfEdges = 1 + ( 360 / (int)EwMathArcCos( 1.0f - ( 0.5f / ( pixel + 1 ))));

  /* Set the transformation matrix for the path coordinates */
  EwSetPathMatrix( path, aMatrix[0], aMatrix[1], aMatrix[2], aMatrix[3],
                   aMatrix[4], aMatrix[5]);

  /* Compose the path from an arc */
  EwInitSubPath   ( path, 0, noOfEdges + 1 );
  EwAddSubPathArc ( path, 0, aCX, aCY, aRX, aRY, 0.0f, 360.0f, noOfEdges );
  EwCloseSubPath  ( path, 0 );

  /* Track the bounding box surrounding the shape */
  if ( aBoundingBox )
  {
    aBoundingBox[0] = MIN( aCX - aRX, aBoundingBox[0]);
    aBoundingBox[1] = MIN( aCY - aRY, aBoundingBox[1]);
    aBoundingBox[2] = MAX( aCX + aRX, aBoundingBox[2]);
    aBoundingBox[3] = MAX( aCY + aRY, aBoundingBox[3]);
  }

  return path;
}


/* Creates a new path object representing a straight line segment. If
   aBoundingBox != 0, the parameter is used as array of 4 entries to track
   the x1,y1,x2,y2 coordinates of the bounding box surrounding the shape.
   If the line has no length, no path is created and the function returns 0. */
static XPath* CreateLine( float aMatrix[6], float aX1, float aY1, float aX2,
  float aY2, float* aBoundingBox )
{
  XPath* path;

  /* Does the line have a length? */
  if (( aX1 == aX2 ) && ( aY1 == aY2 ))
    return 0;

  /* Create a new path object */
  if ( !( path = EwCreatePath( 1 )))
    return 0;

  /* Set the transformation matrix for the path coordinates */
  EwSetPathMatrix( path, aMatrix[0], aMatrix[1], aMatrix[2], aMatrix[3],
                   aMatrix[4], aMatrix[5]);

  /* Compose the path from a single line */
  EwInitSubPath   ( path, 0, 1 );
  EwBeginSubPath  ( path, 0, aX1, aY1 );
  EwAddSubPathLine( path, 0, aX2, aY2 );

  /* Track the bounding box surrounding the shape */
  if ( aBoundingBox )
  {
    aBoundingBox[0] = MIN( aX1, aBoundingBox[0]);
    aBoundingBox[1] = MIN( aY1, aBoundingBox[1]);
    aBoundingBox[2] = MAX( aX1, aBoundingBox[2]);
    aBoundingBox[3] = MAX( aY1, aBoundingBox[3]);
    aBoundingBox[0] = MIN( aX2, aBoundingBox[0]);
    aBoundingBox[1] = MIN( aY2, aBoundingBox[1]);
    aBoundingBox[2] = MAX( aX2, aBoundingBox[2]);
    aBoundingBox[3] = MAX( aY2, aBoundingBox[3]);
  }

  return path;
}


/* Creates a new path object representing an opened polyline. If aBoundingBox
   != 0, the parameter is used as array of 4 entries to track the x1,y1,x2,y2
   coordinates of the bounding box surrounding the polyline. If the polyline
   is empty, no path is created and the function returns 0. */
static XPath* CreatePolyline( float aMatrix[6], const unsigned int* aData,
  float* aBoundingBox )
{
  int          useReader  = USE_FLASH_READER( aData );
  int          noOfValues = aData? UINT32( aData ): 0;
  const float* values     = (const float*)( aData + 1 );
  float        x, y;
  XPath*       path;
  int          i;

  /* Any valid data for the path */
  if (( noOfValues < 4 ) || ( noOfValues % 2 ))
    return 0;

  /* Create a new path object */
  if ( !( path = EwCreatePath( 1 )))
    return 0;

  /* Starting point of the path */
  x = FLOAT( values + 0 );
  y = FLOAT( values + 1 );

  /* Set the transformation matrix for the path coordinates */
  EwSetPathMatrix( path, aMatrix[0], aMatrix[1], aMatrix[2], aMatrix[3],
                   aMatrix[4], aMatrix[5]);

  /* Set the start position of the polyline */
  EwInitSubPath ( path, 0, noOfValues / 2 );
  EwBeginSubPath( path, 0, x, y );

  /* Add the just processed point to the bounding box */
  if ( aBoundingBox )
  {
    aBoundingBox[0] = MIN( x, aBoundingBox[0]);
    aBoundingBox[1] = MIN( y, aBoundingBox[1]);
    aBoundingBox[2] = MAX( x, aBoundingBox[2]);
    aBoundingBox[3] = MAX( y, aBoundingBox[3]);
  }

  /* Compose the path from line segments */
  for ( i = 2; i < noOfValues; i += 2 )
  {
    x = FLOAT( values + i );
    y = FLOAT( values + i + 1 );

    EwAddSubPathLine( path, 0, x, y );

    /* Add the just processed point to the bounding box */
    if ( aBoundingBox )
    {
      aBoundingBox[0] = MIN( x, aBoundingBox[0]);
      aBoundingBox[1] = MIN( y, aBoundingBox[1]);
      aBoundingBox[2] = MAX( x, aBoundingBox[2]);
      aBoundingBox[3] = MAX( y, aBoundingBox[3]);
    }
  }

  return path;
}

#endif /* EW_DONT_USE_SVG_FUNCTIONS */


/* Exclude path functionality? It includes the path string parsing */
#ifndef EW_DONT_USE_PATH_FUNCTIONS

/* The following function is used during creation of SVG paths. It verifies,
   whether the given sub-path has enough space for at least aNoOfEdges new
   coordinate values. Is this the case, the function does nothing and returns
   != 0. If there is not enough space, the function tries to reallocate the
   already collected sub-path data to the next sub-path by increasing its
   capacity. The function returns != 0 if the operation was successful. */
static int EnlargeSVGBufPath( XPath* aPath, int* aSubPathNo, int aNoOfEdges )
{
  int noOfFreeEdges = EwGetNoOfFreeSubPathEdges( aPath, *aSubPathNo );
  int noOfEdges     = EwGetNoOfSubPathEdges( aPath, *aSubPathNo );
  int newSubPathNo  = ( *aSubPathNo + 1 ) % 2;

  /* Not necessary to enlarge the buffer? */
  if ( noOfFreeEdges >= aNoOfEdges )
     return 1;

  /* Try to enlarge the buffer */
  if ( !EwInitSubPath( aPath, newSubPathNo, noOfEdges + aNoOfEdges + 256 ))
    return 0;

  /* Transfer the path data to the enlarged sub-path. Free the memory used
     by the old sub-path */
  EwAddSubPathCopy( aPath, newSubPathNo, aPath, *aSubPathNo, 0, noOfEdges );
  EwInitSubPath( aPath, *aSubPathNo, 1 );

  *aSubPathNo = newSubPathNo;
  return 1;
}


/* Creates a new path object described by path commands stored in aData. If
   aBoundingBox != 0, the parameter is used as array of 4 entries to track
   the x1,y1,x2,y2 coordinates of the bounding box surrounding the path.
   If there is no commands to process, no path is created and the function
   returns 0. */
static XPath* CreatePath( float aMatrix[6], const unsigned int* aData,
  float* aBoundingBox )
{
  int                 useReader    = USE_FLASH_READER( aData );
  int                 noOfValues   = aData? INT32( aData ) : 0;
  int                 noOfSubPaths = aData? INT32( aData + 1 ) : 0;
  const unsigned int* ptr          = aData + 2;
  const unsigned int* end          = aData + 1 + noOfValues;
  unsigned int        instQuad     = ptr? UINT32( ptr++ ): 0;
  int                 instCount    = 0;
  XPath*              path;
  XPath*              bufPath;
  int                 bufSubPathNo = 0;
  int                 subPathNo    = 0;
  int                 noOfEdges    = 0;
  float               pixel2Edges  = 1.0f;
  int                 subPathDone  = 0;

  /* The path is empty */
  if ( !noOfSubPaths )
    return 0;

  /* Create a new path object */
  if ( !( path = EwCreatePath( noOfSubPaths )))
    return 0;

  /* Also create a 'buffer' path used to store the intermediate path data
     resulting from the progressive processing the path commands. The
     path will have only 2 sub-path which grow sucessively. */
  if (( bufPath = EwCreatePath( 2 )) == 0 )
  {
    EwFreePath( path );
    return 0;
  }

  /* Set the transformation matrix for the path coordinates */
  EwSetPathMatrix( path, aMatrix[0], aMatrix[1], aMatrix[2], aMatrix[3],
                   aMatrix[4], aMatrix[5]);

  /* Reserve memory for the first set of path data */
  if ( !EwInitSubPath( bufPath, 0, 256 ))
  {
    EwFreePath( bufPath );
    EwFreePath( path );
    return 0;
  }

  /* Calculate a factor to estimate the necessary number of edges. To obtain
     good looking results we assume a straight edge of a curve should not
     exceed 8 px. The factor takes in account the scaling effect resulting
     from the path transformation. */
  pixel2Edges = EwMathSqrt((( aMatrix[0] + aMatrix[1]) *
                            ( aMatrix[0] + aMatrix[1])) +
                           (( aMatrix[3] + aMatrix[4]) *
                            ( aMatrix[3] + aMatrix[4]))) / 8.0f;

  /* Process commands describing a sub-path */
  while (( ptr < end ) || ( instCount < 4 ))
  {
    int opCode = ( instQuad >> ( instCount * 8 )) & 0xFF;

    /* A sub-path is finished or a new sub-path begins? */
    if ( subPathDone || ( opCode == EW_SVG_BeginPath ))
    {
      /* How many edges do belong to the last processed path? */
      noOfEdges = EwGetNoOfSubPathEdges( bufPath, bufSubPathNo );

      /* Any path data still pending in the buf path?  */
      if (( noOfEdges > 0 ) && ( subPathNo < noOfSubPaths ))
      {
        /* Reserve memory for the path */
        if ( !EwInitSubPath( path, subPathNo, noOfEdges ))
          goto OUT_OF_MEMORY;

        /* ... and copy the path */
        EwAddSubPathCopy( path, subPathNo++, bufPath, bufSubPathNo, 0,
                          noOfEdges );

        /* Don't forget to close the sub path, if necessary */
        if ( EwIsSubPathClosed( bufPath, bufSubPathNo ))
          EwCloseSubPath( path, subPathNo - 1 );

        /* Calculate the bounding box of the just created subpath? */
        if ( aBoundingBox )
        {
          XRect b         = EwGetSubPathBounds( bufPath, bufSubPathNo );
          aBoundingBox[0] = MIN((float)b.Point1.X, aBoundingBox[0]);
          aBoundingBox[1] = MIN((float)b.Point1.Y, aBoundingBox[1]);
          aBoundingBox[2] = MAX((float)b.Point2.X, aBoundingBox[2]);
          aBoundingBox[3] = MAX((float)b.Point2.Y, aBoundingBox[3]);
        }
      }

      subPathDone = 0;
    }

    /* What kind of command is processed? */
    switch ( opCode )
    {
      /* Set the start position for a sub-path */
      case EW_SVG_BeginPath :
        if (( ptr += 2 ) > end )
          break;

        EwBeginSubPath( bufPath, bufSubPathNo, FLOAT( ptr-2 ),
                        FLOAT( ptr-1 ));
      break;

      /* Append a straight line sehment to the sub-path */
      case EW_SVG_AddLine :
        if (( ptr += 2 ) > end )
          break;

        if ( !EnlargeSVGBufPath( bufPath, &bufSubPathNo, 1 ))
          goto OUT_OF_MEMORY;

        EwAddSubPathLine( bufPath, bufSubPathNo, FLOAT( ptr-2 ),
                          FLOAT( ptr-1 ));
      break;

      /* Append a quadratic Bezier curve to the sub-path */
      case EW_SVG_AddBezier2 :
      {
        float x0, y0, x1, y1, x2, y2;

        if (( ptr += 4 ) > end )
          break;

        noOfEdges = EwGetNoOfSubPathEdges( bufPath, bufSubPathNo );
        x0        = EwGetSubPathNodeX( bufPath, bufSubPathNo, noOfEdges );
        y0        = EwGetSubPathNodeY( bufPath, bufSubPathNo, noOfEdges );
        x1        = FLOAT( ptr-4 ); y1 = FLOAT( ptr-3 );
        x2        = FLOAT( ptr-2 ); y2 = FLOAT( ptr-1 );

        noOfEdges = (int)(( DISTANCE( x1, y1, x0, y0 ) +
                            DISTANCE( x2, y2, x1, y1   )) * pixel2Edges );

        /* Very small shape. Add some edges so that it is more precise */
        if ( noOfEdges < 8 )
          noOfEdges += 2;

        if ( !EnlargeSVGBufPath( bufPath, &bufSubPathNo, noOfEdges + 1 ))
          goto OUT_OF_MEMORY;

        EwAddSubPathBezier2( bufPath, bufSubPathNo, x1, y1, x2, y2,
                             noOfEdges + 1 );
      }
      break;

      /* Append a cubic Bezier curve to the sub-path */
      case EW_SVG_AddBezier3 :
      {
        float x0, y0, x1, y1, x2, y2, x3, y3;

        if (( ptr += 6 ) > end )
          break;

        noOfEdges = EwGetNoOfSubPathEdges( bufPath, bufSubPathNo );
        x0        = EwGetSubPathNodeX( bufPath, bufSubPathNo, noOfEdges );
        y0        = EwGetSubPathNodeY( bufPath, bufSubPathNo, noOfEdges );
        x1        = FLOAT( ptr-6 ); y1 = FLOAT( ptr-5 );
        x2        = FLOAT( ptr-4 ); y2 = FLOAT( ptr-3 );
        x3        = FLOAT( ptr-2 ); y3 = FLOAT( ptr-1 );

        /* Estimate the length of the curve in pixel. Knowing this estimate
           the number of edges */
        noOfEdges = (int)(( DISTANCE( x1, y1, x0, y0 ) +
                            DISTANCE( x2, y2, x1, y1 ) +
                            DISTANCE( x3, y3, x2, y2 )) * pixel2Edges );

        /* Very small shape. Add some edges so that it is more precise */
        if ( noOfEdges < 8 )
          noOfEdges += 2;

        if ( !EnlargeSVGBufPath( bufPath, &bufSubPathNo, noOfEdges + 1 ))
          goto OUT_OF_MEMORY;

        EwAddSubPathBezier3( bufPath, bufSubPathNo, x1, y1, x2, y2, x3, y3,
                             noOfEdges + 1 );
      }
      break;

      /* Append an arc to the sub-path */
      case EW_SVG_AddArc :
      {
        float cx, cy, rx, ry, rotateAngle, startAngle, endAngle;

        if (( ptr += 7 ) > end )
          break;

        cx          = FLOAT( ptr-7 ); cy       = FLOAT( ptr-6 );
        rx          = FLOAT( ptr-5 ); ry       = FLOAT( ptr-4 );
        rotateAngle = FLOAT( ptr-3 );
        startAngle  = FLOAT( ptr-2 ); endAngle = FLOAT( ptr-1 );

        /* Estimate the number of edges to compose the arc of */
        noOfEdges = (int)(( rx + ry ) * ( endAngle - startAngle ) *
                          ( 3.14f / 360.0f ) * pixel2Edges );

        if ( noOfEdges < 0 )
          noOfEdges = -noOfEdges;

        /* Very small shape. Add some edges so that it is more precise */
        if ( noOfEdges < 8 )
          noOfEdges += 2;

        if ( !EnlargeSVGBufPath( bufPath, &bufSubPathNo, noOfEdges + 1 ))
          goto OUT_OF_MEMORY;

        EwPushPathMatrix( bufPath );
        EwTranslatePathMatrix( bufPath, cx, cy);
        EwRotatePathMatrix( bufPath, rotateAngle );
        EwAddSubPathArc( bufPath, bufSubPathNo, 0, 0, rx, ry, startAngle,
                         endAngle, noOfEdges + 1 );
        EwPopPathMatrix( bufPath );
      }
      break;

      /* Close a sub path */
      case EW_SVG_ClosePath :
      {
        EwCloseSubPath( bufPath, bufSubPathNo );
        subPathDone++;
      }
      break;
    }

    /* Get the op-code for the next command */
    if (( ++instCount == 4 ) && ( ptr < end ))
    {
      instCount = 0;
      instQuad  = UINT32( ptr++ );
    }
  }

  /* How many edges do belong to the last processed path? */
  noOfEdges = EwGetNoOfSubPathEdges( bufPath, bufSubPathNo );

  /* Any path data still pending in the buf path?  */
  if (( noOfEdges > 0 ) && ( subPathNo < noOfSubPaths ))
  {
    /* Reserve memory for the path */
    if ( !EwInitSubPath( path, subPathNo, noOfEdges ))
      goto OUT_OF_MEMORY;

    /* ... and copy the path */
    EwAddSubPathCopy( path, subPathNo, bufPath, bufSubPathNo, 0, noOfEdges );

    /* Don't forget to close the sub path, if necessary */
    if ( EwIsSubPathClosed( bufPath, bufSubPathNo ))
      EwCloseSubPath( path, subPathNo );

    /* Calculate the bounding box of the just created subpath? */
    if ( aBoundingBox )
    {
      XRect b         = EwGetSubPathBounds( bufPath, bufSubPathNo );
      aBoundingBox[0] = MIN((float)b.Point1.X, aBoundingBox[0]);
      aBoundingBox[1] = MIN((float)b.Point1.Y, aBoundingBox[1]);
      aBoundingBox[2] = MAX((float)b.Point2.X, aBoundingBox[2]);
      aBoundingBox[3] = MAX((float)b.Point2.Y, aBoundingBox[3]);
    }
  }

  /* All ok. Release the temporary used path and finish */
  EwFreePath( bufPath );
  return path;

 OUT_OF_MEMORY :
  EwFreePath( bufPath );
  return path;
}

#endif /* EW_DONT_USE_PATH_FUNCTIONS */


/* Exclude SVG functionality */
#ifndef EW_DONT_USE_SVG_FUNCTIONS

/* The function modulates the given color with the opacity values and returns 
   the new resulting color value. */
static XColor ModulateColor( XColor aColor, unsigned char aOpacity )
{
  if ( aOpacity != 255 )
    aColor.Alpha = ( aColor.Alpha * ( aOpacity + 1 )) >> 8;
  return aColor;
}


/* Returns a styles bit-mask for the EwStrokePath() operation based on the
   stroke parameters from SVG. */
static unsigned int GetStrokeStyle( char aLineCap, char aLineJoin )
{
  unsigned int style = 0;

  if ( aLineCap == StrokeLineCap_Butt )
    style |= EW_PATH_CAP_START_FLAT   | EW_PATH_CAP_END_FLAT;
  else if ( aLineCap == StrokeLineCap_Square )
    style |= EW_PATH_CAP_START_SQUARE | EW_PATH_CAP_END_SQUARE;
  if ( aLineCap == StrokeLineCap_Round )
    style |= EW_PATH_CAP_START_ROUND  | EW_PATH_CAP_END_ROUND;

  if ( aLineJoin == StrokeLineJoin_Miter )
    style |= EW_PATH_JOIN_MITER;
  else if ( aLineJoin == StrokeLineJoin_Bevel )
    style |= EW_PATH_JOIN_BEVEL;
  else if ( aLineJoin == StrokeLineJoin_Round )
    style |= EW_PATH_JOIN_ROUND;

  return style;
}


/* Traverses the SVG state stack looking for an active drawing operation
   involving the element with aIdAtom ID. */
static int IsDrawingElement( XSVGState* aState, int aIdAtom )
{
  while ( aState && ( aState->IdAtom != aIdAtom ))
    aState = aState->Next;

  return aState != 0;
}


/* Following function executes vector graphic instructions from the sequence
   starting at aPtr whereby the address space valid for access is limited to
   the range aStart..aEnd. */
static int ProcessSVGCommands( XColorGradient* aGradient, XPath* aPath,
  float* aBoundingBox, const unsigned int* aPtr, const unsigned int* aStart,
  const unsigned int* aEnd, XSVGState** aState, XColor aCurrentColor )
{
  XSVGState*          orgState   = *aState;
  XSVGState*          state      = orgState;
  int                 useReader  = USE_FLASH_READER( aPtr );
  unsigned int        instQuad   = UINT32( aPtr++ );
  int                 instCount  = 0;
  int                 i;

  /* Values resulting from the recently parsed element. These are non-
     inhertitable and valid in context of the element only. */
  char                unit       = Unit_None;
  float               attrs[8]   = { 0.0f };
  char                units[8]   = { Unit_None };
  float               bMatrix0   = 1.0f;
  float               bMatrix1   = 0.0f;
  float               bMatrix2   = 0.0f;
  float               bMatrix3   = 1.0f;
  const unsigned int* data       = 0;
  int                 inDefs     = 0;
  int                 inStyle    = 0;
  int                 inLinGrad  = 0;
  int                 inRadGrad  = 0;
  int                 viewBoxSet = 0;
  int                 idAtom     = 0;
  int                 classAtom  = 0;
  int                 element    = 0;
  int                 refAtom    = 0;
  int                 isSVG      = 0;
  int                 isG        = 0;
  int                 isLinGrad  = 0;
  int                 isRadGrad  = 0;

  /* Process the instructions */
  while ( aPtr < aEnd )
  {
    int inst = ( instQuad >> ( instCount * 8 )) & 0xFF;

    /* Entering a nested 'defs', 'style' or 'gradient' sections? This content is
       irrelevant during the drawing operation. */
    if ( *aState != orgState )
    {
      if ( inst == EW_SVG_EnterDefs           ) inDefs++;
      if ( inst == EW_SVG_EnterStyle          ) inStyle++;
      if ( inst == EW_SVG_EnterLinearGradient ) inLinGrad++;
      if ( inst == EW_SVG_EnterRadialGradient ) inRadGrad++;
    }

    /* Skip over all instructions existing inside a 'defs', 'style' or 'gradient'
       section */
    if ( inDefs || inStyle || inLinGrad || inRadGrad )
    {
      if ( inDefs    && ( inst == EW_SVG_LeaveDefs           )) inDefs--;
      if ( inStyle   && ( inst == EW_SVG_LeaveStyle          )) inStyle--;
      if ( inLinGrad && ( inst == EW_SVG_LeaveLinearGradient )) inLinGrad--;
      if ( inRadGrad && ( inst == EW_SVG_LeaveRadialGradient )) inRadGrad--;

      aPtr += GetNoOfOperands( aPtr, inst );
      goto NEXT_INST;
    }

    /* All attributes belonging to an SVG element have been evaluated. Now the
       coordinate systems for the SVG element can be calculated. */
    if ( isSVG && ( inst >= EW_SVG_EnterG ) && ( inst <= EW_SVG_EnterSVG ))
    {
      float eWidth     = CALC_HORZ( attrs[2], units[2]);
      float eHeight    = CALC_VERT( attrs[3], units[3]);
      float vbMinX     = attrs[4];
      float vbMinY     = attrs[5];
      float vbWidth    = attrs[6];
      float vbHeight   = attrs[7];

      /* The content has an area = 0 */
      if (( eWidth <= 0.0f ) || ( eHeight <= 0.0f ))
        return 1;

      /* View-Box is empty - nothing to draw */
      if ( viewBoxSet && (( vbWidth <= 0.0f ) || ( vbHeight <= 0.0f )))
        return 1;

      /* Calculate a matrix for the transformation between the user and viewport
         coordinate spaces. */
      if ( viewBoxSet )
      {
        float scaleX = eWidth  / vbWidth;
        float scaleY = eHeight / vbHeight;

        if ( scaleX > scaleY ) scaleX = scaleY;
        if ( scaleY > scaleX ) scaleY = scaleX;

        state->Matrix[0] *= scaleX;
        state->Matrix[3] *= scaleX;
        state->Matrix[1] *= scaleY;
        state->Matrix[4] *= scaleY;
        state->Matrix[2] -= vbMinX * scaleX;
        state->Matrix[5] -= vbMinY * scaleY;

        eWidth  = vbWidth;
        eHeight = vbHeight;
      }

      state->RangeHorz  = eWidth;
      state->RangeVert  = eHeight;
      state->RangeDiag  = EwMathSqrt(( eWidth  * eWidth  ) +
                                     ( eHeight * eHeight )) / 1.4142136f;

      /* Base scaling estimated at the root SVG element. It will be used to
         calculate the stroke width */
      bMatrix0 = state->Matrix[0];
      bMatrix1 = state->Matrix[1];
      bMatrix2 = state->Matrix[3];
      bMatrix3 = state->Matrix[4];
      isSVG    = 0;
    }

    /* All attributes belonging to a linear gradient element have been evaluated.
       Initialize the gradient. */
    if ( isLinGrad && ( inst >= EW_SVG_EnterG ) && ( inst <= EW_SVG_EnterSVG ))
    {
      /* Gradient coordinates are in user space */
      if ( aGradient && ( state->GradientUnits == GradientUnits_UserSpaceOnUse ))
      {
        float  x1    = CALC_HORZ( attrs[4], units[4]);
        float  y1    = CALC_VERT( attrs[5], units[5]);
        float  x2    = CALC_HORZ( attrs[6], units[6]);
        float  y2    = CALC_VERT( attrs[7], units[7]);
        XPoint start = {(int)( TRANSFORM_X( x1, y1 ) + 0.5f ),
                        (int)( TRANSFORM_Y( x1, y1 ) + 0.5f )};
        XPoint end   = {(int)( TRANSFORM_X( x2, y2 ) + 0.5f ),
                        (int)( TRANSFORM_Y( x2, y2 ) + 0.5f )};

        start.X += state->Offset.X;
        start.Y += state->Offset.Y;
        end.X   += state->Offset.X;
        end.Y   += state->Offset.Y;

        EwSetGradientTypeLinear( aGradient, start, end );
      }

      /* Gradient coordinates are in object bounding box */
      else if ( aGradient && aPath && aBoundingBox )
      {
        float  bbw   = aBoundingBox[2] - aBoundingBox[0];
        float  bbh   = aBoundingBox[3] - aBoundingBox[1];
        float  x1    = CALC_RANGE( attrs[4], units[4], bbw ) + aBoundingBox[0];
        float  y1    = CALC_RANGE( attrs[5], units[5], bbh ) + aBoundingBox[1];
        float  x2    = CALC_RANGE( attrs[6], units[6], bbw ) + aBoundingBox[0];
        float  y2    = CALC_RANGE( attrs[7], units[7], bbh ) + aBoundingBox[1];
        XPoint start = {(int)( TRANSFORM_X( x1, y1 ) + 0.5f ),
                        (int)( TRANSFORM_Y( x1, y1 ) + 0.5f )};
        XPoint end   = {(int)( TRANSFORM_X( x2, y2 ) + 0.5f ),
                        (int)( TRANSFORM_Y( x2, y2 ) + 0.5f )};

        start.X += state->Offset.X;
        start.Y += state->Offset.Y;
        end.X   += state->Offset.X;
        end.Y   += state->Offset.Y;

        EwSetGradientTypeLinear( aGradient, start, end );
      }

      isLinGrad = 0;
    }

    /* All attributes belonging to a radial gradient element have been evaluated.
       Initialize the gradient. */
    if ( isRadGrad && ( inst >= EW_SVG_EnterG ) && ( inst <= EW_SVG_EnterSVG ))
    {
      /* Gradient coordinates are in user space */
      if ( aGradient && ( state->GradientUnits == GradientUnits_UserSpaceOnUse ))
      {
        float  cx    = CALC_HORZ( attrs[0], units[0]);
        float  cy    = CALC_VERT( attrs[1], units[1]);
        float  r     = CALC_DIAG( attrs[4], units[4]);
        XPoint start = {(int)( TRANSFORM_X( cx, cy ) + 0.5f ),
                        (int)( TRANSFORM_Y( cx, cy ) + 0.5f )};
        float  det   = ( state->Matrix[0] * state->Matrix[4]) -
                       ( state->Matrix[1] * state->Matrix[3]);

        start.X += state->Offset.X;
        start.Y += state->Offset.Y;

        /* When working with radial gradients note the scaling and rotation effect
           caused by the transformation matrix. Use an inverse of the matrix. */
        if ( aGradient && ( det != 0.0f ))
          EwSetGradientTypeRadial( aGradient, start, (int)r,
                                   state->Matrix[4] / det,
                                  -state->Matrix[1] / det,
                                  -state->Matrix[3] / det,
                                   state->Matrix[0] / det );
      }

      /* Gradient coordinates are in object bounding box */
      else if ( aGradient && aPath && aBoundingBox )
      {
        float  bbw   = aBoundingBox[2] - aBoundingBox[0];
        float  bbh   = aBoundingBox[3] - aBoundingBox[1];
        float  cx    = CALC_RANGE( attrs[0], units[0], bbw ) + aBoundingBox[0];
        float  cy    = CALC_RANGE( attrs[1], units[1], bbh ) + aBoundingBox[1];
        float  rx    = CALC_RANGE( attrs[4], units[4], bbw );
        float  ry    = CALC_RANGE( attrs[4], units[4], bbh );
        float  r     = MIN( rx, ry );
        float  sx    = r / rx;
        float  sy    = r / ry;
        XPoint start = {(int)( TRANSFORM_X( cx, cy ) + 0.5f ),
                        (int)( TRANSFORM_Y( cx, cy ) + 0.5f )};
        float  det   = ( state->Matrix[0] * state->Matrix[4]) -
                       ( state->Matrix[1] * state->Matrix[3]);

        start.X += state->Offset.X;
        start.Y += state->Offset.Y;

        /* When working with radial gradients note the scaling and rotation effect
           caused by the transformation matrix. Use an inverse of the matrix. 
           Additionally note, that the radius is scaled in the bounding box to
           fill it completely. */
        if ( aGradient && ( det != 0.0f ))
          EwSetGradientTypeRadial( aGradient, start, (int)r,
                                 (  state->Matrix[4] / det ) * sx,
                                 ( -state->Matrix[1] / det ) * sx,
                                 ( -state->Matrix[3] / det ) * sy,
                                 (  state->Matrix[0] / det ) * sy );
      }

      isRadGrad = 0;
    }

    /* All attributes belonging to a group element have been evaluated. Is the
       group configured as semitransparent? Then create a new off-screen bitmap
       to store the content of the group temporarily and when all drawings are
       does display this bitmap with the specified opacity */
    if ( isG && ( inst >= EW_SVG_EnterG ) && ( inst <= EW_SVG_EnterSVG ))
    {
      /* Entering a group - save the current state. */
      if ( !( state = PushState( aState )))
        return 0;

      /* The group is fully transparent. Its content is hidden */
      if ( !state->Opacity )
        state->Hidden = 1;

      /* The content of the group is semi-transparent. create an off-screen
         bitmap to store this content. */
      if (( state->Opacity < 255 ) && state->Opacity && !state->Hidden )
      {
        XColor transp = { 0, 0, 0, 0 };
        XPoint size;

        size.X = state->ClipRect.Point2.X - state->ClipRect.Point1.X;
        size.Y = state->ClipRect.Point2.Y - state->ClipRect.Point1.Y;

        /* Create an off-screen bitmap as termporary drawing destination */
        state->Dst = EwCreateBitmap( EW_PIXEL_FORMAT_NATIVE, size, 0, 1 );

        /* No memory for the bitmap */
        if ( !state->Dst )
          return 0;

        /* The new set of drawing destination parameters */
        state->DstFrameNo        = 0;
        state->Offset.X          = 0;
        state->Offset.Y          = 0;
        state->ClipRect.Point1.X = 0;
        state->ClipRect.Point1.Y = 0;
        state->ClipRect.Point2.X = size.X;
        state->ClipRect.Point2.Y = size.Y;
        state->Opacity           = 255;

        /* Clear the bitmap */
        EwFillRectangle( state->Dst, 0, state->ClipRect, state->ClipRect, transp,
                         transp, transp, transp, 0 );
      }

      isG = 0;
    }

    /* Entering a particular element. Remember this state. */
    if ( inst == EW_SVG_EnterSVG            ) isSVG     = 1;
    if ( inst == EW_SVG_EnterG              ) isG       = 1;
    if ( inst == EW_SVG_EnterLinearGradient ) isLinGrad = 1;
    if ( inst == EW_SVG_EnterRadialGradient ) isRadGrad = 1;

    /* Start of an element? Duplicate current state on the stack and initialize
       its state appropriately. Abort if there is no memory for the state. */
    if (( inst >= EW_SVG_EnterG ) && ( inst <= EW_SVG_EnterSVG ) &&
        !( state = PushState( aState )))
      return 0;

    /* Start of a new element? Set defauilt values for all attributes */
    if (( inst >= EW_SVG_EnterG ) && ( inst <= EW_SVG_EnterSVG ))
    {
      for ( i = 0; i < 8; i++ ) { attrs[i] = 0.0f; units[i] = Unit_None; }
      data      = 0;
      idAtom    = 0;
      refAtom   = 0;
      classAtom = 0;
      element   = inst - EW_SVG_EnterG + 1;

      /* Per default the SVG element fills the entire available viewport */
      if ( inst == EW_SVG_EnterSVG )
      {
        attrs[2] = 1.0f; units[2] = Unit_Percent;
        attrs[3] = 1.0f; units[3] = Unit_Percent;
      }

      /* Set default coordinates for the linear gradient element */
      if ( inst == EW_SVG_EnterLinearGradient )
      {
        attrs[4] = 0.0f; units[4] = Unit_Percent;
        attrs[5] = 0.0f; units[5] = Unit_Percent;
        attrs[6] = 1.0f; units[6] = Unit_Percent;
        attrs[7] = 0.0f; units[7] = Unit_Percent;
      }

      /* Set default coordinates for the radial gradient element */
      if ( inst == EW_SVG_EnterRadialGradient )
      {
        attrs[0] = 0.5f; units[0] = Unit_Percent;
        attrs[1] = 0.5f; units[1] = Unit_Percent;
        attrs[4] = 0.5f; units[4] = Unit_Percent;
      }
    }

    /* Process instructions affecting attribute values. Accumulate all values
       in the current state structure. */
    switch ( inst )
    {
      case EW_SVG_SetUnitPercentage :
        unit                     = Unit_Percent;            break;
      case EW_SVG_SetX :
        attrs[0]                 = FLOAT( aPtr++ );
        units[0]                 = unit;                    break;
      case EW_SVG_SetY :
        attrs[1]                 = FLOAT( aPtr++ );
        units[1]                 = unit;                    break;
      case EW_SVG_SetWidth :
        attrs[2]                 = FLOAT( aPtr++ );
        units[2]                 = unit;                    break;
      case EW_SVG_SetHeight :
        attrs[3]                 = FLOAT( aPtr++ );
        units[3]                 = unit;                    break;
      case EW_SVG_SetCX :
        attrs[0]                 = FLOAT( aPtr++ );
        units[0]                 = unit;                    break;
      case EW_SVG_SetCY :
        attrs[1]                 = FLOAT( aPtr++ );
        units[1]                 = unit;                    break;
      case EW_SVG_SetX1 :
        attrs[4]                 = FLOAT( aPtr++ );
        units[4]                 = unit;                    break;
      case EW_SVG_SetY1 :
        attrs[5]                 = FLOAT( aPtr++ );
        units[5]                 = unit;                    break;
      case EW_SVG_SetX2 :
        attrs[6]                 = FLOAT( aPtr++ );
        units[6]                 = unit;                    break;
      case EW_SVG_SetY2 :
        attrs[7]                 = FLOAT( aPtr++ );
        units[7]                 = unit;                    break;
      case EW_SVG_SetR :
        attrs[4]                 = FLOAT( aPtr++ );
        units[4]                 = unit;                    break;
      case EW_SVG_SetRX :
        attrs[4]                 = FLOAT( aPtr++ );
        units[4]                 = unit;                    break;
      case EW_SVG_SetRY :
        attrs[5]                 = FLOAT( aPtr++ );
        units[5]                 = unit;                    break;
      case EW_SVG_SetStrokeWidth :
      {
        float r = FLOAT( aPtr++ );
        state->StrokeWidth       = CALC_DIAG( r, unit );
      }
      break;
      case EW_SVG_SetStrokeMiter :
        state->StrokeMiter       = FLOAT( aPtr++ );         break;
      case EW_SVG_SetFillNone :
        state->FillPaintMode     = PaintMode_None;          break;
      case EW_SVG_SetFillCurrentColor :
        state->FillColor         = aCurrentColor;
        state->FillPaintMode     = PaintMode_Color;
      break;
      case EW_SVG_SetStrokeNone :
        state->StrokePaintMode   = PaintMode_None;          break;
      case EW_SVG_SetStrokeCurrentColor :
        state->StrokeColor       = aCurrentColor;
        state->StrokePaintMode   = PaintMode_Color;
      break;
      case EW_SVG_SetFillRule_NonZero :
        state->FillRule          = FillRule_NonZero;        break;
      case EW_SVG_SetFillRule_EvenOdd :
        state->FillRule          = FillRule_EvenOdd;        break;
      case EW_SVG_SetLineCap_Butt :
        state->StrokeLineCap     = StrokeLineCap_Butt;      break;
      case EW_SVG_SetLineCap_Round :
        state->StrokeLineCap     = StrokeLineCap_Round;     break;
      case EW_SVG_SetLineCap_Square :
        state->StrokeLineCap     = StrokeLineCap_Square;    break;
      case EW_SVG_SetLineJoin_Miter :
        state->StrokeLineJoin    = StrokeLineJoin_Miter;    break;
      case EW_SVG_SetLineJoin_Round :
        state->StrokeLineJoin    = StrokeLineJoin_Round;    break;
      case EW_SVG_SetLineJoin_Bevel :
        state->StrokeLineJoin    = StrokeLineJoin_Bevel;    break;
      case EW_SVG_SetVectorEffect_None :
        state->VectorEffect      = VectorEffect_None;       break;
      case EW_SVG_SetVectorEffect_NonScaling :
        state->VectorEffect      = VectorEffect_NonScaling; break;
      case EW_SVG_SetOpacity :
        state->Opacity           = OPACITY( aPtr++ );       break;
      case EW_SVG_SetFillOpacity :
        state->FillOpacity       = OPACITY( aPtr++ );       break;
      case EW_SVG_SetStrokeOpacity :
        state->StrokeOpacity     = OPACITY( aPtr++ );       break;
      case EW_SVG_SetFillColor :
      {
        unsigned int color = UINT32( aPtr++ );
        state->FillColor.Alpha   = (unsigned char)( color >> 24 );
        state->FillColor.Red     = (unsigned char)( color >> 16 );
        state->FillColor.Green   = (unsigned char)( color >>  8 );
        state->FillColor.Blue    = (unsigned char)( color >>  0 );
        state->FillPaintMode     = PaintMode_Color;
      }
      break;
      case EW_SVG_SetStrokeColor :
      {
        unsigned int color = UINT32( aPtr++ );
        state->StrokeColor.Alpha = (unsigned char)( color >> 24 );
        state->StrokeColor.Red   = (unsigned char)( color >> 16 );
        state->StrokeColor.Green = (unsigned char)( color >>  8 );
        state->StrokeColor.Blue  = (unsigned char)( color >>  0 );
        state->StrokePaintMode   = PaintMode_Color;
      }
      break;
      case EW_SVG_SetFillGradient :
      {
        int id = INT32( aPtr++ );

        if ( id )
        {
          /* Search for the referenced element. Limit to gradients only */
          const unsigned int* ptr = FindElementWithId( aStart, aEnd, id,
                                      EW_SVG_EnterLinearGradient,
                                      EW_SVG_EnterRadialGradient );

          /* Gradient found? */
          if ( ptr )
          {
            state->FillGradient    = ptr;
            state->FillPaintMode   = PaintMode_Gradient;
          }
        }
      }
      break;
      case EW_SVG_SetStrokeGradient :
      {
        int id = INT32( aPtr++ );

        if ( id )
        {
          /* Search for the referenced element. Limit to gradients only */
          const unsigned int* ptr = FindElementWithId( aStart, aEnd, id,
                                      EW_SVG_EnterLinearGradient,
                                      EW_SVG_EnterRadialGradient );

          /* Gradient found? */
          if ( ptr )
          {
            state->StrokeGradient  = ptr;
            state->StrokePaintMode = PaintMode_Gradient;
          }
        }
      }
      break;
      case EW_SVG_SetStopOpacity :
        state->StopOpacity         = OPACITY( aPtr++ );       break;
      case EW_SVG_SetStopCurrentColor :
        state->StopColor           = aCurrentColor;           break;
      case EW_SVG_SetStopColor :
      {
        unsigned int color = UINT32( aPtr++ );

        state->StopColor.Alpha     = (unsigned char)( color >> 24 );
        state->StopColor.Red       = (unsigned char)( color >> 16 );
        state->StopColor.Green     = (unsigned char)( color >>  8 );
        state->StopColor.Blue      = (unsigned char)( color >>  0 );
      }
      break;
      case EW_SVG_SetOffset :
        state->StopOffset          = FLOAT( aPtr++ );         break;
      case EW_SVG_SetGradientUnits_UserSpaceOnUse :
        state->GradientUnits       = GradientUnits_UserSpaceOnUse;    break;
      case EW_SVG_SetGradientUnits_ObjectBoundingBox :
        state->GradientUnits       = GradientUnits_ObjectBoundingBox; break;
      case EW_SVG_SetViewBox :
        if (( aPtr += 4 ) < aEnd )
        {
          attrs[4]   = FLOAT( aPtr - 4 );
          attrs[5]   = FLOAT( aPtr - 3 );
          attrs[6]   = FLOAT( aPtr - 2 );
          attrs[7]   = FLOAT( aPtr - 1 );
          viewBoxSet = 1;
        }
      break;
      case EW_SVG_SetPoints :
      case EW_SVG_SetPath :
      {
        unsigned int count = UINT32( aPtr );

        if (( aPtr + count ) < aEnd )
          data = aPtr;
        aPtr += count + 1;
      }
      break;
      case EW_SVG_Translate1 :
        state->Matrix[2]   += state->Matrix[0] * FLOAT( aPtr   );
        state->Matrix[5]   += state->Matrix[3] * FLOAT( aPtr++ );
      break;
      case EW_SVG_Translate2 :
        if (( aPtr += 2 ) < aEnd )
        {
          state->Matrix[2] += state->Matrix[0] * FLOAT( aPtr - 2 );
          state->Matrix[5] += state->Matrix[3] * FLOAT( aPtr - 2 );
          state->Matrix[2] += state->Matrix[1] * FLOAT( aPtr - 1 );
          state->Matrix[5] += state->Matrix[4] * FLOAT( aPtr - 1 );
        }
      break;
      case EW_SVG_Scale1 :
        state->Matrix[0] *= FLOAT( aPtr   );
        state->Matrix[3] *= FLOAT( aPtr   );
        state->Matrix[1] *= FLOAT( aPtr   );
        state->Matrix[4] *= FLOAT( aPtr++ );
      break;
      case EW_SVG_Scale2 :
        if (( aPtr += 2 ) < aEnd )
        {
          state->Matrix[0] *= FLOAT( aPtr - 2 );
          state->Matrix[3] *= FLOAT( aPtr - 2 );
          state->Matrix[1] *= FLOAT( aPtr - 1 );
          state->Matrix[4] *= FLOAT( aPtr - 1 );
        }
      break;
      case EW_SVG_Rotate1 :
      {
        float sin = EwMathSin( FLOAT( aPtr   ));
        float cos = EwMathCos( FLOAT( aPtr++ ));
        float nm0, nm1, nm3, nm4;

        /* Multiply the existing matrix with a new matrix describing the rotation */
        nm0 = ( state->Matrix[0] *  cos ) + ( state->Matrix[1] * sin );
        nm1 = ( state->Matrix[0] * -sin ) + ( state->Matrix[1] * cos );
        nm3 = ( state->Matrix[3] *  cos ) + ( state->Matrix[4] * sin );
        nm4 = ( state->Matrix[3] * -sin ) + ( state->Matrix[4] * cos );

        /* Store the resulting matrix */
        state->Matrix[0] = nm0; state->Matrix[1] = nm1;
        state->Matrix[3] = nm3; state->Matrix[4] = nm4;
      }
      break;
      case EW_SVG_Rotate3 :
        if (( aPtr += 3 ) < aEnd )
        {
          float sin = EwMathSin( FLOAT( aPtr - 3 ));
          float cos = EwMathCos( FLOAT( aPtr - 3 ));
          float nm0, nm1, nm3, nm4;

          /* Rotation around a specified center position? Apply translation first */
          state->Matrix[2] += state->Matrix[0] * FLOAT( aPtr - 2 );
          state->Matrix[5] += state->Matrix[3] * FLOAT( aPtr - 2 );
          state->Matrix[2] += state->Matrix[1] * FLOAT( aPtr - 1 );
          state->Matrix[5] += state->Matrix[4] * FLOAT( aPtr - 1 );

          /* Multiply the existing matrix with a new matrix describing the rotation */
          nm0 = ( state->Matrix[0] *  cos ) + ( state->Matrix[1] * sin );
          nm1 = ( state->Matrix[0] * -sin ) + ( state->Matrix[1] * cos );
          nm3 = ( state->Matrix[3] *  cos ) + ( state->Matrix[4] * sin );
          nm4 = ( state->Matrix[3] * -sin ) + ( state->Matrix[4] * cos );

          /* Store the resulting matrix */
          state->Matrix[0] = nm0; state->Matrix[1] = nm1;
          state->Matrix[3] = nm3; state->Matrix[4] = nm4;

          /* Rotation around a specified center position? Restore the translation */
          state->Matrix[2] += state->Matrix[0] * -FLOAT( aPtr - 2 );
          state->Matrix[5] += state->Matrix[3] * -FLOAT( aPtr - 2 );
          state->Matrix[2] += state->Matrix[1] * -FLOAT( aPtr - 1 );
          state->Matrix[5] += state->Matrix[4] * -FLOAT( aPtr - 1 );
        }
      break;
      case EW_SVG_SkewX :
      {
        float tan = EwMathTan( FLOAT( aPtr++ ));
        state->Matrix[1] += state->Matrix[0] * tan;
        state->Matrix[4] += state->Matrix[3] * tan;
      }
      break;
      case EW_SVG_SkewY :
      {
        float tan = EwMathTan( FLOAT( aPtr++ ));
        state->Matrix[0] += state->Matrix[1] * tan;
        state->Matrix[3] += state->Matrix[4] * tan;
      }
      break;
      case EW_SVG_Matrix :
        if (( aPtr += 6 ) < aEnd )
        {
          float m[6];
          m[0] = FLOAT( aPtr - 6 ); m[1] = FLOAT( aPtr - 4 );
          m[2] = FLOAT( aPtr - 2 ); m[3] = FLOAT( aPtr - 5 );
          m[4] = FLOAT( aPtr - 3 ); m[5] = FLOAT( aPtr - 1 );
          MultiplyMatrix( state->Matrix, m );
        }
      break;
      case EW_SVG_SetId :
        state->IdAtom = idAtom = INT32( aPtr++ );
      break;
      case EW_SVG_SetClass :
        classAtom = INT32( aPtr++ );
      break;
      case EW_SVG_SetElement :
        aPtr++;
      break;
      case EW_SVG_ProcessCSS :
        if ( !ProcessCSS( aGradient, aPath, aBoundingBox, aStart, aEnd, aState,
                          aCurrentColor, idAtom, classAtom, element ))
          return 0;
      break;
      case EW_SVG_SetRef :
        refAtom = INT32( aPtr++ );
      break;
    }

    /* All attributes affecting a 'stop' element are processed. Now the information can
       be stored in the gradient. */
    if (( inst == EW_SVG_LeaveStop ) && aGradient )
      EwAddGradientColorStop( aGradient, state->StopOffset,
                              ModulateColor( state->StopColor, state->StopOpacity ));

    /* All attributes affecting an 'use' element are processed. Now, the element
       referenced by 'use' can be seareched and drawn. */
    if (( inst == EW_SVG_LeaveUse ) && refAtom )
    {
      /* Search for the referenced element. Limit to shapes only */
      const unsigned int* ptr = FindElementWithId( aStart, aEnd, refAtom,
                                  EW_SVG_EnterG, EW_SVG_EnterPath );

      /* To avoid endless recursion in 'use' dependencies, check whether the 
         element with given id is already in drawing mode */
      if ( ptr && IsDrawingElement( *aState, refAtom ))
         ptr = 0;

      /* Take in account the x, y position specified in the 'use' element */
      if ( ptr )
      {
        float x = CALC_HORZ( attrs[0], units[0]);
        float y = CALC_HORZ( attrs[1], units[1]);

        state->Matrix[2] += state->Matrix[0] * x;
        state->Matrix[5] += state->Matrix[3] * x;
        state->Matrix[2] += state->Matrix[1] * y;
        state->Matrix[5] += state->Matrix[4] * y;
      }

      /* If the element was found, process the instructions */
      if ( ptr && !ProcessSVGCommands( 0, 0, 0, ptr, aStart, aEnd, aState,
                                       aCurrentColor ))
        return 0;
    }

    /* All attributes affecting a shape element are processed. Now, the element
       can be drawn. */
    if (( inst >= EW_SVG_LeaveRect ) && ( inst <= EW_SVG_LeavePath ))
    {
      XPath*     path     = 0;
      float      box[4]   = { 0.0f };
      int        doFill   = 0;
      int        doStroke = 0;
      XSVGState* state2   = state;

      /* Will the drawing operation have a fill effect? */
      if (( inst != EW_SVG_LeaveLine )  && !state->Hidden &&
          ( state->FillOpacity > 0 ) && ( state->Opacity > 0 ) &&
          ((( state->FillPaintMode == PaintMode_Color ) &&
            ( state->FillColor.Alpha > 0 )) ||
           ( state->FillPaintMode == PaintMode_Gradient )))
        doFill = 1;

      /* Will the drawing operation have a stroke effect? */
      if (( state->StrokeOpacity > 0 ) && ( state->Opacity > 0 ) &&
          ( state->StrokeWidth > 0.0f ) && !state->Hidden &&
          ((( state->StrokePaintMode == PaintMode_Color ) &&
            ( state->StrokeColor.Alpha > 0 )) ||
           ( state->StrokePaintMode == PaintMode_Gradient )))
        doStroke = 1;

      /* Initialize an empty bounding box, which then is enhanced successivelly
         with each new calculated path */
      box[0] = +1.0e10f;
      box[1] = +1.0e10f;
      box[2] = -1.0e10f;
      box[3] = -1.0e10f;

      /* Determine the type of the drawing operation (the shape). Create a
         path describing the shape. */
      if ( doFill || doStroke )
        switch ( inst )
        {
          /* Is it a rectangular shape? */
          case EW_SVG_LeaveRect :
          {
            float x  = CALC_HORZ( attrs[0], units[0]);
            float y  = CALC_VERT( attrs[1], units[1]);
            float w  = CALC_HORZ( attrs[2], units[2]);
            float h  = CALC_VERT( attrs[3], units[3]);
            float rx = CALC_HORZ( attrs[4], units[4]);
            float ry = CALC_VERT( attrs[5], units[5]);
 
            if (( rx > 0.0f ) || ( ry > 0.0f ))
              path = CreateRoundedRect( state->Matrix, x, y, w, h, rx, ry, box );
            else
              path = CreateRect( state->Matrix, x, y, w, h, box );
          }
          break;

          /* Is it a single line segment?  */
          case EW_SVG_LeaveLine :
          {
            float x1 = CALC_HORZ( attrs[4], units[4]);
            float y1 = CALC_VERT( attrs[5], units[5]);
            float x2 = CALC_HORZ( attrs[6], units[6]);
            float y2 = CALC_VERT( attrs[7], units[7]);

            path = CreateLine( state->Matrix, x1, y1, x2, y2, box );
          }
          break;

          /* Is it a circle? */
          case EW_SVG_LeaveCircle :
          {
            float cx = CALC_HORZ( attrs[0], units[0]);
            float cy = CALC_VERT( attrs[1], units[1]);
            float r  = CALC_DIAG( attrs[4], units[4]);

            path = CreateEllipse( state->Matrix, cx, cy, r, r, box );
          }
          break;

          /* Is it an ellipse? */
          case EW_SVG_LeaveEllipse :
          {
            float cx = CALC_HORZ( attrs[0], units[0]);
            float cy = CALC_VERT( attrs[1], units[1]);
            float rx = CALC_HORZ( attrs[4], units[4]);
            float ry = CALC_VERT( attrs[5], units[5]);

            path = CreateEllipse( state->Matrix, cx, cy, rx, ry, box );
          }
          break;

          /* Is it an opened polyline? */
          case EW_SVG_LeavePolyline :
            if ( data )
              path = CreatePolyline( state->Matrix, data, box );
          break;

          /* Is it a closed polygon? */
          case EW_SVG_LeavePolygon :
            if ( data )
              path = CreatePolyline( state->Matrix, data, box );
            if ( path )
              EwCloseSubPath( path, 0 );
          break;

          /* Is it a path described by SVG path string? */
          case EW_SVG_LeavePath :
            if ( data )
              path = CreatePath( state->Matrix, data, box );
          break;
        }

      /* No shape known - nothing to draw */
      if ( !path ) { doFill = 0; doStroke = 0; }

      /* Filling and stroking a semitransparent shape. This requires the drawing
         operations to be performed inside an-offscreen bitmap, which then is
         displayed with specified opacity. Prepare the bitmap */
      if ( doFill && doStroke && ( state->Opacity < 255 ))
      {
        /* Get the bounding box enclosing the shape */
        XRect  bounds      = EwGetPathBounds( path );
        XColor transp      = { 0, 0, 0, 0 };
        float  matrix0     = state->Matrix[0];
        float  matrix1     = state->Matrix[1];
        float  matrix2     = state->Matrix[3];
        float  matrix3     = state->Matrix[4];
        float  strokeX;
        float  strokeY;
        XPoint size;

        /* No scaling of the stroke to apply? */
        if ( state->VectorEffect == VectorEffect_NonScaling )
        {
          matrix0 = bMatrix0;
          matrix1 = bMatrix1;
          matrix2 = bMatrix2;
          matrix3 = bMatrix3;
        }

        /* Stroke width in X and Y direction */
        strokeX = state->StrokeWidth * ( matrix0 + matrix1 );
        strokeY = state->StrokeWidth * ( matrix2 + matrix3 );

        if ( strokeX < 0.0f ) strokeX = -strokeX;
        if ( strokeY < 0.0f ) strokeY = -strokeY;

        /* Enhance the bounding box by stroke width and calculate its size */
        bounds.Point1.X -= (int)strokeX + 2;
        bounds.Point1.Y -= (int)strokeY + 2;
        bounds.Point2.X += (int)strokeX + 2;
        bounds.Point2.Y += (int)strokeY + 2;
        size.X           = bounds.Point2.X - bounds.Point1.X;
        size.Y           = bounds.Point2.Y - bounds.Point1.Y;

        /* Save the actualy state */
        state = PushState( aState );

        /* No memory for the new state */
        if ( !state )
          return 0;

        /* Create an off-screen bitmap as termporary drawing destination */
        state->Dst = EwCreateBitmap( EW_PIXEL_FORMAT_NATIVE, size, 0, 1 );

        /* No memory for the bitmap */
        if ( !state->Dst )
          return 0;

        /* The new set of drawing destination parameters */
        state->DstFrameNo        = 0;
        state->ClipRect.Point1.X = 0;
        state->ClipRect.Point1.Y = 0;
        state->ClipRect.Point2.X = size.X;
        state->ClipRect.Point2.Y = size.Y;
        state->Offset.X          = -bounds.Point1.X;
        state->Offset.Y          = -bounds.Point1.Y;
        state->Opacity           = 255;

        /* Clear the bitmap */
        EwFillRectangle( state->Dst, 0, state->ClipRect, state->ClipRect, transp,
                         transp, transp, transp, 0 );
      }

      /* Fill the shape with a solid color? */
      if ( doFill && ( state->FillPaintMode == PaintMode_Color ))
      {
        XColor color = state->FillColor;

        color = ModulateColor( color, state->FillOpacity );
        color = ModulateColor( color, state->Opacity );

        EwFillPath( state->Dst, path, state->DstFrameNo, state->ClipRect,
                    state->ClipRect, 0, state->Offset, color, color, color,
                    color, 1, 1, state->FillRule == FillRule_NonZero );
      }

      /* Fill the shape with a color gradient? */
      if ( doFill && ( state->FillPaintMode == PaintMode_Gradient ))
      {
        XColorGradient* gradient  = EwCreateGradient( CountGradientStops(
                                       state->FillGradient, aStart, aEnd ));
        int             opacity   = (( state->FillOpacity + 1 ) *
                                       state->Opacity ) >> 8;

        if ( !gradient )
          return 0;

        /* Load the gradient with its color stops and attributes */
        if ( !ProcessSVGCommands( gradient, path, box, state->FillGradient,
                                  aStart, aEnd, aState, aCurrentColor ))
          return 0;

        /* Raster the shape using the gradient data */
        EwFillPathWithGradient( state->Dst, path, state->DstFrameNo, state->ClipRect,
                                state->ClipRect, 0, state->Offset, gradient, opacity,
                                1, 1, state->FillRule == FillRule_NonZero );

        EwFreeGradient( gradient );
      }

      /* Draw the outline of the shape with a solid color? */
      if ( doStroke && ( state->StrokePaintMode == PaintMode_Color ))
      {
        XColor  color   = state->StrokeColor;
        XUInt32 style   = GetStrokeStyle( state->StrokeLineCap,
                                          state->StrokeLineJoin );
        float   matrix0 = state->Matrix[0];
        float   matrix1 = state->Matrix[1];
        float   matrix2 = state->Matrix[3];
        float   matrix3 = state->Matrix[4];

        /* No scaling of the stroke to apply? */
        if ( state->VectorEffect == VectorEffect_NonScaling )
        {
          matrix0 = bMatrix0;
          matrix1 = bMatrix1;
          matrix2 = bMatrix2;
          matrix3 = bMatrix3;
        }

        color = ModulateColor( color, state->StrokeOpacity );
        color = ModulateColor( color, state->Opacity );

        EwStrokePath( state->Dst, path, state->DstFrameNo, state->ClipRect,
                      state->ClipRect, 0, state->Offset, state->StrokeWidth,
                      matrix0, matrix1, matrix2, matrix3, style,
                      state->StrokeMiter, color, color, color, color, 1, 1 );
      }

      /* Stroke the shape with a color gradient? */
      if ( doStroke && ( state->StrokePaintMode == PaintMode_Gradient ))
      {
        XColorGradient* gradient    = EwCreateGradient( CountGradientStops(
                                        state->StrokeGradient, aStart, aEnd ));
        XUInt32         style       = GetStrokeStyle( state->StrokeLineCap,
                                        state->StrokeLineJoin );
        float           matrix0     = state->Matrix[0];
        float           matrix1     = state->Matrix[1];
        float           matrix2     = state->Matrix[3];
        float           matrix3     = state->Matrix[4];
        int             opacity     = (( state->StrokeOpacity + 1 ) *
                                         state->Opacity ) >> 8;

        /* No scaling of the stroke to apply? */
        if ( state->VectorEffect == VectorEffect_NonScaling )
        {
          matrix0 = bMatrix0;
          matrix1 = bMatrix1;
          matrix2 = bMatrix2;
          matrix3 = bMatrix3;
        }

        if ( !gradient )
          return 0;

        /* Load the gradient with its color stops and attributes */
        if ( !ProcessSVGCommands( gradient, path, box, state->StrokeGradient,
                                  aStart, aEnd, aState, aCurrentColor ))
          return 0;

        /* Raster the shape using the gradient data */
        EwStrokePathWithGradient( state->Dst, path, state->DstFrameNo,
                    state->ClipRect, state->ClipRect, 0, state->Offset,
                    state->StrokeWidth, matrix0, matrix1, matrix2, matrix3,
                    style, state->StrokeMiter, gradient, opacity, 1, 1 );

        EwFreeGradient( gradient );
      }

      /* Restore the state if an off-screen bitmap was used */
      if ( state != state2 )
      {
        XColor color = { 255, 255, 255, 255 };
        color.Alpha = state2->Opacity;

        EwCopyBitmap( state2->Dst, state->Dst, state2->DstFrameNo,
                      state->DstFrameNo, state2->ClipRect, state2->ClipRect,
                      state->Offset, color, color, color, color, 1 );
        state = PopState( aState );
      }

      /* Drawing of the shape is done. Release the path data. */
      if ( path )
        EwFreePath( path );
    }

    /* Returning from a group which was buffered by an off-screen bitmap? */
    if ( inst == EW_SVG_LeaveG )
    {
      XSVGState* state2 = state->Next;

      /* Does the state have an associated off-screen bitmap? */
      if ( state2->Dst != state->Dst )
      {
        XColor color  = { 255, 255, 255, 255 };
        color.Alpha   = state2->Opacity;

        /* Copy the content of the bitmap */
        EwCopyBitmap( state2->Dst, state->Dst, state2->DstFrameNo,
                      state->DstFrameNo, state2->ClipRect, state2->ClipRect,
                      state->Offset, color, color, color, color, 1 );
      }

      state = PopState( aState );
    }

    /* All instructions belonging to the element are processed */
    if (( inst >= EW_SVG_LeaveG ) && ( inst <= EW_SVG_LeaveSVG ) &&
        ( state != orgState ))
      state = PopState( aState );

    /* Reaching a 'leave' instruction correspponding to the 'enter' instruction
       at the start of the function. Stop the execution. */
    if (( inst >= EW_SVG_LeaveG ) && ( inst <= EW_SVG_LeaveStyle ) &&
        ( state == orgState ))
      break;

  NEXT_INST:
    /* After the instruction is processed - restore the default unit */
    if ( inst != EW_SVG_SetUnitPercentage )
      unit = Unit_None;

    /* Get the op-code for the next instruction */
    if (( ++instCount == 4 ) && ( aPtr < aEnd ))
    {
      instCount = 0;
      instQuad  = UINT32( aPtr++ );
    }
  }

  return 1;
}


/* Searches in the memory aStart..aEnd for an element definitions matching the
   given aIdAtom and element type in range aElementFirst..aElementLast. The
   found element is thereupon returned. */
static const unsigned int* FindElementWithId( const unsigned int* aStart,
  const unsigned int* aEnd, int aIdAtom, int aElementFirst, int aElementLast )
{
  int                 useReader  = USE_FLASH_READER( aStart );
  const unsigned int* ptr        = aStart;
  unsigned int        instQuad   = UINT32( ptr++ );
  int                 instCount  = 0;
  const unsigned int* elementPtr = 0;

  /* Process the instructions and search for styles definitions corresponding
     to the element, its class and id */
  while ( ptr < aEnd )
  {
    int inst = ( instQuad >> ( instCount * 8 )) & 0xFF;

    if (( inst >= EW_SVG_EnterG ) && ( inst <= EW_SVG_LeaveStyle ))
      elementPtr = 0;

    /* Focus on elements with requested type only */
    if (( inst >= aElementFirst ) && ( inst <= aElementLast ))
      elementPtr = ptr - 1;

    if (( inst == EW_SVG_SetId ) && elementPtr && ((int)INT32( ptr ) == aIdAtom ))
      return elementPtr;

    /* Skip over the operands of the instruction */
    ptr += GetNoOfOperands( ptr, inst );

    /* Get the op-code for the next instruction */
    if (( ++instCount == 4 ) && ( ptr < aEnd ))
    {
      instCount = 0;
      instQuad  = UINT32( ptr++ );
    }
  }

  return 0;
}


/* Searches in the memory aStart..aEnd for style definitions matching elements
   with given aElement type, aIdAtom and aClassAtom. Found styles are thereupon
   executed and affect the current aState. Returns 0 if an error is occurred. */
static int ProcessCSS( XColorGradient* aGradient, XPath* aPath,
  float* aBoundingBox, const unsigned int* aStart, const unsigned int* aEnd,
  XSVGState** aState, XColor aCurrentColor, int aIdAtom, int aClassAtom,
  int aElement )
{
  int useReader = USE_FLASH_READER( aStart );
  int any       = 0;
  int i;

  /* Styles are applied in a particular order according to the associated
     selector. The less specific the selector, the lower the priority of the
     style definition. Styles with highest specifity are applied at the end
     end of the processing. Search for the styles according to this order.
     Avoid the repetitions if there is no style matching the element. */
  for ( i = 0; ( i < 8 ) && ( any || !i ); i++ )
  {
    const unsigned int* ptr       = aStart;
    unsigned int        instQuad  = UINT32( ptr++ );
    int                 instCount = 0;
    int                 classAtom = 0;
    int                 idAtom    = 0;
    int                 element   = 0;
    const unsigned int* stylePtr  = 0;

    /* Process the instructions and search for styles definitions corresponding
       to the element, its class and id */
    while ( ptr < aEnd )
    {
      int inst = ( instQuad >> ( instCount * 8 )) & 0xFF;

      /* When inside the style definition, track the selector relevant
         attributes. These attributes always start the list of attributes inside
         a style */
      if ( stylePtr && ( inst == EW_SVG_SetId      )) idAtom    = INT32( ptr );
      if ( stylePtr && ( inst == EW_SVG_SetClass   )) classAtom = INT32( ptr );
      if ( stylePtr && ( inst == EW_SVG_SetElement )) element   = INT32( ptr );

      /* All selector relevant attributes are processed. Does the selector match
         to the given element? */
      if ( stylePtr && ( inst == EW_SVG_SelectCSS )  &&
         ( !element   || ( element   == aElement   )) &&
         ( !classAtom || ( classAtom == aClassAtom )) &&
         ( !idAtom    || ( idAtom    == aIdAtom    )))
      {
        int apply = 0;

        /* At least one style is matching the element  */
        any = 1;

        /* Styles are applied in a particular order according to the associated
           selector. The less specific the selector, the lower the priority of
           the style definition. Styles with highest specifity are applied at
           the end end of the processing. */
        if (( i == 0 ) && !element && !classAtom && !idAtom ) apply = 1;
        if (( i == 1 ) && !element &&  classAtom && !idAtom ) apply = 1;
        if (( i == 2 ) && !element && !classAtom &&  idAtom ) apply = 1;
        if (( i == 3 ) && !element &&  classAtom &&  idAtom ) apply = 1;
        if (( i == 4 ) &&  element && !classAtom && !idAtom ) apply = 1;
        if (( i == 5 ) &&  element &&  classAtom && !idAtom ) apply = 1;
        if (( i == 6 ) &&  element && !classAtom &&  idAtom ) apply = 1;
        if (( i == 7 ) &&  element &&  classAtom &&  idAtom ) apply = 1;

        /* Can the style be applied? */
        if ( apply &&
             !ProcessSVGCommands( aGradient, aPath, aBoundingBox, stylePtr,
                                  aStart, aEnd, aState, aCurrentColor ))
          return 0;
      }

      /* Track the begining of a style definition */
      if ( inst == EW_SVG_EnterStyle )
        stylePtr = ptr - 1;

      /* End of style definition found - forget it */
      if ( inst == EW_SVG_LeaveStyle )
        stylePtr  = 0;

      /* All selector relevant attributes are processed. Forget the selector */
      if ( inst == EW_SVG_SelectCSS )
      {
        element   = 0;
        classAtom = 0;
        idAtom    = 0;
      }

      /* Skip over the operands of the instruction */
      ptr += GetNoOfOperands( ptr, inst );

      /* Get the op-code for the next instruction */
      if (( ++instCount == 4 ) && ( ptr < aEnd ))
      {
        instCount = 0;
        instQuad  = UINT32( ptr++ );
      }
    }
  }

  return 1;
}


/* Counts the <stop> elements in the sequence starting with aPtr whereby the
   address space valid for access is limited to the range aStart..aEnd */
static int CountGradientStops( const unsigned int* aPtr,
  const unsigned int* aStart, const unsigned int* aEnd )
{
  int          useReader  = USE_FLASH_READER( aPtr );
  unsigned int instQuad   = UINT32( aPtr++ );
  int          instCount  = 0;
  int          noOfStops  = 0;

  /* Process the instructions and search for <stop> definitions */
  while ( aPtr < aEnd )
  {
    int inst = ( instQuad >> ( instCount * 8 )) & 0xFF;

    /* Count the stops */
    if ( inst == EW_SVG_LeaveStop )
      noOfStops++;

    /* End of the gradient definition found */
    if (( inst == EW_SVG_LeaveLinearGradient ) ||
        ( inst == EW_SVG_LeaveRadialGradient ))
      break;

    /* Skip over the operands of the instruction */
    aPtr += GetNoOfOperands( aPtr, inst );

    /* Get the op-code for the next instruction */
    if (( ++instCount == 4 ) && ( aPtr < aEnd ))
    {
      instCount = 0;
      instQuad  = UINT32( aPtr++ );
    }
  }

  return noOfStops;
}


#endif /* EW_DONT_USE_SVG_FUNCTIONS */


/* pba */
