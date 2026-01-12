/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This software is delivered "as is" and shows the usage of other software
* components. It is provided as an example software which is intended to be
* modified and extended according to particular requirements.
*
* TARA Systems hereby disclaims all warranties and conditions with regard to the
* software, including all implied warranties and conditions of merchantability
* and non-infringement of any third party IPR or other rights which may result
* from the use or the inability to use the software.
*
********************************************************************************
*
* DESCRIPTION:
*  This file implemenents the binding between the Embedded Wizard generated
*  unit 'QRCode' and the native code at 'qrcodegen.c'.
*
*******************************************************************************/

#ifndef QRCODEBINDING_H
#define QRCODEBINDING_H

#ifdef __cplusplus
  extern "C" {
#endif

/*
   Include the Embedded Wizard runtime environment which defines the used
   primitives.
*/
#include "ewrte.h"


/*******************************************************************************
* FUNCTION:
*   QRCodeBindingCreate
*
* DESCRIPTION:
*   The function QRCodeBindingCreate() gets called once per instance of this qr
*   code component to allocate needed memory.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   On success the handle to the allocated memory, otherwise NULL. 
*
*******************************************************************************/
XHandle QRCodeBindingCreate();


/*******************************************************************************
* FUNCTION:
*   QRCodeBindingDestroy
*
* DESCRIPTION:
*   The function QRCodeBindingDestroy() gets called once per instance of this 
*   qr code component to destroy and free the native allocated memory.
*
* ARGUMENTS:
*   aThis - The native handle of specific qr code component instance.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void QRCodeBindingDestroy( XHandle aThis );


/*******************************************************************************
* FUNCTION:
*   QRCodeBindingEncodeText
*
* DESCRIPTION:
*   The function QRCodeBindingEncodeText() gets called called to encode the text
*   which should be display at the qr code component.
*
* ARGUMENTS:
*   aThis - The native handle of specific qr code component instance.
*   aText - The text which should be displayed.
*   aMinVersion - The minimum qr code version which determines the minimum 
*                 number of qr code modules used.
*   aMaxVersion - The maximum qr code version which determines the maximum 
*                 number of qr code modules used.
*
* RETURN VALUE:
*   TRUE on success, FALSE otherwise.
*
*******************************************************************************/
XBool QRCodeBindingEncodeText( XHandle aThis, XString aText, XInt32 aMinVersion, XInt32 aMaxVersion );


/*******************************************************************************
* FUNCTION:
*   QRCodeBindingGetSize
*
* DESCRIPTION:
*   The function QRCodeBindingGetSize() gets called to obtain the needed border 
*   width to display the previous encoded text.
*
* ARGUMENTS:
*   aThis - The native handle of specific qr code component instance.
*
* RETURN VALUE:
*   The border width number of needed cubes.
*
*******************************************************************************/
XInt32 QRCodeBindingGetSize( XHandle aThis );


/*******************************************************************************
* FUNCTION:
*   QRCodeBindingGetModule
*
* DESCRIPTION:
*   The function QRCodeBindingGetModule() gets called to obtain whether a cube
*   at a given position should be drawn or not.
*
* ARGUMENTS:
*   aThis - The native handle of specific qr code component instance.
*   aXPos - The x-Position of the cube. Starting with zero from the left-top 
*           corner.
*   aYPos - The y-Position of the cube. Starting with zero from the left-top
*           corner.
*
* RETURN VALUE:
*   TRUE if the cube should be drawn, otherwise FALSE.
*
*******************************************************************************/
XBool QRCodeBindingGetModule( XHandle aThis, XInt32 aXPos, XInt32 aYPos );


#ifdef __cplusplus
  }
#endif

#endif /* QRCODEBINDING_H */

/* jwi */