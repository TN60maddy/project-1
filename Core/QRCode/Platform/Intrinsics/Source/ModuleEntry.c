/****************************************************************************
 *
 * Preamble of Intellectual Property Rights (IPR) and Copyright (C) 
 * TARA Systems GmbH Munich
 *
 * This software and related documentation (the "Software") are intellectual
 * property owned by TARA Systems and are copyright of TARA Systems.
 * Any copying, reproduction or redistribution of the Software in whole
 * or in part by any means not in accordance with the License Agreement
 * between Licensee and TARA Systems is expressly prohibited.
 *
 * This shall mean if not agreed upon in writing otherwise:
 *   - removal of this preamble is expressly prohibited
 *   - Software usage without signed License Agreement is prohibited
 *   - no distribution of source or object code to third party
 *
 ****************************************************************************
 * FILE: ModuleEntry.c
 *
 * DESCRIPTION:
 *   EntryPoint of the EmWiTest intrinsics module.
 ****************************************************************************/

#include "intrinsics.h"
#include "QRCodeBinding.h"

/****************************************************************************
 * SECTION: Declaration of private data
 ****************************************************************************/
 

/****************************************************************************
 * SECTION: Description of this Embedded Wizard Module
 ****************************************************************************/

EW_MODULE
(
  INTRINSICS_IFC_VERSION,
  L"IntrinsicsModule",
  L"QRCode Intrinsic Module"
)


/****************************************************************************
 * SECTION: Intrinsic table
 *
 * DESCRIPTION:
 *   This is the intrinsics-table. This table contains registration-entries
 *   for intrinsics implemented in this Embedded Wizard module.
 ****************************************************************************/

EW_DEFINE_INTRINSICS

   /* QRCodeBinding */
   EW_INTRINSIC( L"QRCodeBindingCreate", L"handle", 0, L"", L"", QRCodeBindingCreate)
   EW_INTRINSIC( L"QRCodeBindingDestroy", L"void", 1, L"handle", L"aThis", QRCodeBindingDestroy)
   EW_INTRINSIC (L"QRCodeBindingEncodeText", L"bool", 2, L"handle,string,int32,int32", L"aThis,aText,aMinVersion,aMaxVersion", QRCodeBindingEncodeText)
   EW_INTRINSIC (L"QRCodeBindingGetSize", L"int32", 1, L"handle", L"aThis", QRCodeBindingGetSize)
   EW_INTRINSIC (L"QRCodeBindingGetModule", L"bool", 3, L"handle,int32,int32", L"aThis,aXPos,aYPos", QRCodeBindingGetModule)

EW_END_OF_INTRINSICS



/****************************************************************************
 * FUNCTION: EwInitModule
 *
 * DESCRIPTION:
 *   Initialize a new instance of this intrinsics module.
 ****************************************************************************/

EW_ENTRYPOINT void*
EwInitModule ( void )
{
  return (void*) 1;
}


/****************************************************************************
 * FUNCTION: EwDoneModule
 *
 * DESCRIPTION:
 *   Deinitialize the instance.
 ****************************************************************************/

EW_ENTRYPOINT void
EwDoneModule (
   void* aContext )
{
  aContext;
}


/****************************************************************************
 * FUNCTION: EwLinkModule
 *
 * DESCRIPTION:
 *   This function is called as soon as all ewis have been loaded.
 ****************************************************************************/

EW_ENTRYPOINT void EwLinkModule( XModuleContext* aList )
{
  (void) aList;
}


/****************************************************************************
 * FUNCTION: EwUnlinkModule
 ****************************************************************************/

EW_ENTRYPOINT void EwUnlinkModule( void )
{
  /* All modules are unloaded now */
}


/****************************************************************************
 * FUNCTION: EwIntrinsicsProlog
 *
 * DESCRIPTION:
 *   Restore the state of the global variable, so the following intrinsic
 *   call is safe.
 ****************************************************************************/

EW_ENTRYPOINT void
EwIntrinsicsProlog (
   void* aContext )
{
  aContext;
}


/****************************************************************************
 * FUNCTION: EwIntrinsicsEpilog
 *
 * DESCRIPTION:
 *   Store the state of the global variable for the next time, an intrinsic
 *   should be called.
 ****************************************************************************/

EW_ENTRYPOINT void
EwIntrinsicsEpilog (
  void* aContext )
{
  aContext;
}

/* eof */
