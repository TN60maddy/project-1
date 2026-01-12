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
*   This file contains the implementation of an SVG resource provider intended
*   to load SVG resources directly from the code memory as they are generated
*   by Embedded Wizard resource converters.
*
*******************************************************************************/

#include "ewrte.h"
#include "ewextsvg.h"
#include "ewgfxdriver.h"
#include "ewextgfx.h"


#ifdef EW_USE_BLOB_DATA
  /* Following variable describes the start address to access an external BLOB
     contents. Please see the function EwSetBlobData(). */
  extern const char* EwBlobStartAddress;

  /* Helper macro to read a pointer from the XSVGRes data structure. The macro
     automatically distinguish between the structure stored in code or BLOB
     memory. */
  #define RES_PTR( aMember )                                                   \
    ( isBlob?                                                                  \
    ( EwBlobStartAddress + ((const XBlobSVGRes*)res)->aMember ) :              \
    (const char*)res->aMember )
#else
  /* Helper macro to read a pointer from the XBmpRes data structure. The macro
     automatically distinguish between the structure stored in code or BLOB
     memory. */
  #define RES_PTR( aMember )                                                   \
    ((const char*)res->aMember )
#endif /* EW_USE_BLOB_DATA */


/*******************************************************************************
* FUNCTION:
*   EwSVGInit
*
* DESCRIPTION:
*   The function EwSVGInit() is called during the initialization of the Graphics
*   Engine. Its intention is to give the external loader a chance to initialize
*   its private variables.
*
* ARGUMENTS:
*   aArgs - User argument passed in the EwInitGraphicsEngine().
*
* RETURN VALUE:
*   If successful, returns != 0.
*
*******************************************************************************/
int EwSVGInit( void* aArgs )
{
  EW_UNUSED_ARG( aArgs );
  return 1;
}


/*******************************************************************************
* FUNCTION:
*   EwSVGDone
*
* DESCRIPTION:
*   The function EwSVGDone() will be called during the shutdown of the Graphics
*   Engine. It gives the loader a chance to deinitialize itself just before the
*   Graphics Engine terminates.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwSVGDone( void )
{
}


/*******************************************************************************
* FUNCTION:
*   EwSVGOpen
*
* DESCRIPTION:
*   The function EwSVGOpen() will be called by the Graphics Engine in order to
*   initiate the access to the given SVG resource. Depending on the manner, the
*   resources are handled in the particular platform system, the function can
*   open an image file or it can access bitmap information available in the code
*   memory.
*
*   The function should return a handle to the opened resource. By using this
*   handle, the SVG content can be requested by the Graphics Engine without
*   taking in account any platform specific aspects.
*
* ARGUMENTS:
*   aResource - Descriptor of the SVG resource to open. The content of this
*     descriptor depends on the particular platform system.
*
* RETURN VALUE:
*   If sucessful, the function returns the handle to the opened SVG resource.
*   If failed, the function returns null.
*
*******************************************************************************/
void* EwSVGOpen( const struct XSVGRes* aResource )
{
  /* Verify, whether the binary resource does fit to this loader */
  if (( aResource->MagicNo != EW_MAGIC_NO_SVG ) &&
      ( aResource->MagicNo != EW_MAGIC_NO_SVG_BLOB ))
  {
    EwError( 503 );
    EwPanic();
    return 0;
  }

  /* This interface works with the original data structures as it was stored in
     the code memory */
  return (void*)aResource;
}


/*******************************************************************************
* FUNCTION:
*   EwSVGClose
*
* DESCRIPTION:
*   The function EwSVGClose() will be called by the Graphics Engine to finish
*   the processing of an SVG resource. Depending on the manner, the resources
*   are handled in the particular platform system, the function can close the
*   previously opened file and free any temporarily reserved resources.
*
* ARGUMENTS:
*   aHandle - Handle to the SVG resource to terminate the access.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwSVGClose( void* aHandle )
{
  EW_UNUSED_ARG( aHandle );
}


/*******************************************************************************
* FUNCTION:
*   EwSVGGetConstData
*
* DESCRIPTION:
*   The function EwSVGGetConstData() will be called by the Graphics Engine to
*   access a command list describing the SVG elements and their attributes. By
*   evaluating the command list, the SVG content can be rendered. This function
*   assumes, the commands list is stored as const data. 
*
* ARGUMENTS:
*   aHandle   - Handle to the bitmap resource to determine its attributes.
*   aCommands - Pointer to a variable to receive the address of SVG commands.

* RETURN VALUE:
*   If sucessful, the function returns != 0.
*
*******************************************************************************/
int EwSVGGetConstData( void* aHandle, const XSVGCommands** aCommands )
{
  const XSVGRes* res    = (const XSVGRes*)aHandle;
  #ifdef EW_USE_BLOB_DATA
    int          isBlob = res->MagicNo == EW_MAGIC_NO_SVG_BLOB;
  #endif
  const void*    data   = RES_PTR( Data );

  *aCommands = (const XSVGCommands*)data;
  return 1;
}


/* pba */
