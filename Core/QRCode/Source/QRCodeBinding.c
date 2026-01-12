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

/****************************************************************************
 * SECTION: Includes
 ****************************************************************************/

#include "QRCodeBinding.h"
#include "qrcodegen.h"

#include <stdio.h>
#include <string.h>


/****************************************************************************
 * SECTION: typedef
 ****************************************************************************/

 /****************************************************************************
  * TYPE: QRCodeStruct
  *
  * DESCRIPTION:
  *   The structure defines the memory of the QRCode.
  *
  * COMPONENTS:
  *   qr0        - Buffer which is used to encode the qr code.
  *   tempBuffer - Buffer which is used to encode the qr code.
  ****************************************************************************/
typedef struct QRCodeStruct
{
  uint8_t qr0[qrcodegen_BUFFER_LEN_MAX];
  uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];

} QRCodeStruct;


/****************************************************************************
 * TYPE: QRCode
 *
 * DESCRIPTION:
 *   Defines a pointer to the qr code structure.
 ****************************************************************************/
typedef struct QRCodeStruct * QRCode;


/****************************************************************************
 * SECTION: Definition of private functions
 ****************************************************************************/

static 
XBool QRCodeBindingXStringToAnsi (
	XString       aSrc,
	char *        aDst,
	unsigned long aMaxLen);


/****************************************************************************
 * SECTION: Implementation of public functions
 ****************************************************************************/

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
XHandle QRCodeBindingCreate()
{
  QRCode This;

  This = (QRCode)EwAlloc(sizeof( QRCodeStruct ));
  if ( ! This )
    return 0;

  memset( This, 0, sizeof( QRCodeStruct ));

  return (XHandle)This;
}


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
void QRCodeBindingDestroy( XHandle aThis )
{
  if ( aThis )
    EwFree( (void*)aThis );
}


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
XBool QRCodeBindingEncodeText( XHandle aThis, XString aText, XInt32 aMinVersion, XInt32 aMaxVersion )
{
  char * Text;
  int size = 0;
  XBool success;
  QRCode This = (QRCode)aThis;
  if ( ! This )
    return 0;
  
  size = EwGetStringLength(aText) + 1;
  
  Text = (char*)EwAlloc( sizeof(char) * size );
  if ( Text == NULL )
    return 0;

  QRCodeBindingXStringToAnsi( aText, Text, size );

  success = qrcodegen_encodeText( Text, This->tempBuffer, This->qr0, qrcodegen_Ecc_MEDIUM, 
    aMinVersion, aMaxVersion, qrcodegen_Mask_AUTO, true);

  EwFree( Text );

  return success;
}


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
XInt32 QRCodeBindingGetSize( XHandle aThis )
{
  QRCode This = (QRCode)aThis;
  if ( ! This )
    return 0;

  return qrcodegen_getSize( This->qr0 );
}


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
XBool QRCodeBindingGetModule( XHandle aThis, XInt32 aXPos, XInt32 aYPos )
{
  QRCode This = (QRCode)aThis;
  if ( ! This )
    return 0;

  return qrcodegen_getModule( This->qr0, aXPos, aYPos );
}


/****************************************************************************
 * SECTION: Implementation of private functions
 ****************************************************************************/
 
/****************************************************************************
* FUNCTION: QRCodeBindingXStringToAnsi
*
* DESCRIPTION:
*   Converts the given wide character string to an ASCII character string.
*
* ARGUMENTS:
*   aSrc    - The source string.
*   aDst    - The destination buffer.
*   aMaxLen - The maximal length of the destination buffer.
*
* RETURN VALUE:
*   TRUE if success, otherwise FALSE.
*
****************************************************************************/
static 
XBool QRCodeBindingXStringToAnsi (
	XString       aSrc,
	char *        aDst,
	unsigned long aMaxLen)
{
	register char* dst = aDst;

	if (!aDst || !aSrc)
		return 0;

	while ((*aSrc != 0) && aMaxLen)
	{
		*dst++ = (char)*aSrc++;
		aMaxLen--;
	}

	*dst = 0;

	return 1;
}

/* jwi */
