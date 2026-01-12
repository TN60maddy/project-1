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
*   The module 'ewresource.c' contains an implementation of the Embedded Wizard
*   Resource Manager. The Resource Manager manages the loading and discarding
*   of resources. Each time a resource should be loaded, the Resource Manager
*   creates an object of a class which fits the required resource class and 
*   invokes the object to load the resource from the code memory into the RAM.
*
*   To support resource loading and discarding the resource class has to 
*   contain its own implementation of the Init() and Done() method. Within
*   these methods user defined code will be executed in order to load or to
*   discard the resource. The detailed implementation of Init() and Done() is
*   platform dependent. The resource class is a 'driver' between the platform
*   independent Chora code and the platform dependent resources.
*
*   To avoid multiple copies of a single resource in the RAM, the Resource
*   Manager stores all loaded resources in a global list called MapList. This
*   technique allowes the callers to share all loaded resources and it reduces
*   the RAM usage.
*
* SUBROUTINES:
*   EwRegisterResource
*   EwDeregisterResource
*   EwLoadResource
*   EwGetLanguage
*   EwSetLanguage
*   EwGetStyles
*   EwSetStyles
*   EwStylesContains
*   EwGetVariantOf
*   EwGetVariantOfLangId
*   EwGetVariantOfStylesSet
*   EwDecompress
*   EwAdaptByteOrder2
*   EwAdaptByteOrder4
*   EwRegisterFlashAreaReader
*   EwSetBlobData
*
*******************************************************************************/

#include "ewrte.h"


/* Undo the macro overloading of following functions */
#undef EwLoadResource
#undef EwGetVariantOf


/* The structure XMapItem stores a pointer to a resource in ROM and a pointer
   to the object where the resource has been loaded in. All Embedded Wizard
   resources need to be loaded before they can be used. The resources will
   be loaded automatically in the EwLoadResource() function. This function
   verifies whether the resource is already loaded, and otherwise the
   function creates an object corresponding to the class of the resource,
   so that the object can load the resource properly.
   XMapItem is used to store all loaded/registered resource-object pairs. */
typedef struct _XMapItem
{
  struct _XMapItem* Next;
  struct _XMapItem* Prev;
  const void*       Resource;

  #ifdef EW_USE_BLOB_DATA
    int             BlobOffset;
    int             BlobSize;
  #endif

  XObject           Object;
} XMapItem;


/* MapListHead and MapListHead store a list of object-resource pairs. This
   global list will be used to find out, whether a resource is already loaded
   or not. */
static XMapItem* MapListHead = 0;

/* EwLangId contains the ID of the currently selected language. LangId will be
   used to find out the correct language variant of a resource, constant, etc. 
   The value == 0 corresponds to the 'default' language */
int             EwLangId = 0; 

/* EwStylesSet contains a set of currently active style IDs. StylesSet will be
   used to find out the correct variant of a resource, constant or class. The 
   value == 0 corresponds to an empty styles set -> No styles are active */
unsigned int    EwStylesSet = 0;

/* Following variables describe Flash memory which is not directly accessible
   by the CPU. In order to read the Flash memory, a user own reader procedure
   is used. Please see the function EwRegisterFlashAreaReader(). */
XFlashAreaReaderProc EwFlashAreaReaderProc   = 0;
void*                EwFlashAreaStartAddress = 0;
void*                EwFlashAreaEndAddress   = 0;
int                  EwFlashAreaBlockSize    = 0;


/* Internal representation of the BLOB file header. Important: its size has to
   be multiple of 4-byte. */
typedef struct
{
  unsigned int      MagicNo;
  unsigned int      Version;
  unsigned int      Checksum1;
  unsigned int      Checksum2;
  unsigned int      NoOfItems;
  int               ItemsOffset;
} XBlobHeader;


#ifdef EW_USE_BLOB_DATA
  /* Following variable describes the external BLOB contents. */
  const char*         EwBlobStartAddress = 0;
  const char*         EwBlobEndAddress   = 0;
  int                 EwBlobUseReader    = 0;
  unsigned int        EwNoOfBlobItems    = 0;
  const XBlobItem*    EwBlobItemsAddress = 0;

  /* Checksum to test compatibility of BLOB files. */
  extern unsigned int EwBlobChecksum[];
#endif


/* DecompressBuffer points to a buffer used internally during decompression. */
static unsigned short* DecompressBuffer = 0;

/* Memory usage profiler */
extern int EwResourcesMemory;
extern int EwResourcesMemoryPeak;
extern int EwObjectsMemory;
extern int EwStringsMemory;
extern int EwMemoryPeak;


/* This helper function evaluates the endian architecture of the target CPU. */
static int IsBigEndianArch( void );

/* The function CacheItem() stores the resource item aItem at the begin of the
   global list. */
static void CacheItem( XMapItem* aItem );

/* The function UncacheItem() removes the item aItem from the global list. */
static void UncacheItem( XMapItem* aItem );

#ifdef EW_USE_BLOB_DATA
  /* The function FindBlobItem() searches in the blob file for an item identified
     by the given name ids. If sucessfull, returns a pointer to the item or NULL
     if the item is not existing. Note, the returned pointer is valid until the
     next EwBlobAreaReadProc() invocation. */
  static const XBlobItem* FindBlobItem( int aId1, int aId2, int aId3 );
#endif


/* Identification for the BLOB content */
#define BLOB_MAGIC_NUMBER                  0x4C425745
#define BLOB_MAGIC_NUMBER_WRONG_BYTE_ORDER 0x4557424C


/*******************************************************************************
* FUNCTION:
*   EwRegisterResource
*
* DESCRIPTION:
*   The function EwRegisterResource() registers a resource object aObject in the
*   global MapList, so the resource stored in the object can be shared between
*   different callers. EwRegisterResource() searches in the MapList for the
*   entry representing the resource and stores in the entry the pointer to the
*   given object.
*
*   If the MapList is full, the function throws an error.
*
* ARGUMENTS:
*   aObject   - Pointer to the object where the resource has been loaded.
*   aResource - Pointer to the resource.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwRegisterResource( XObject aObject, const void* aResource )
{
  XMapItem* item = MapListHead;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Nothing to do */
  if ( !aObject || !aResource )
    return;

  /* repeat until the desired item has been found or all item are evaluated */
  while ( item && ( item->Resource != aResource ))
    item = item->Next;

  /* No matching entry or the item is already associated to an object. Then no
     registration possible. */
  if ( !item || item->Object )
    return;

  /* Register the object as representing the loaded resource */
  item->Object = aObject;
}


/*******************************************************************************
* FUNCTION:
*   EwDeregisterResource
*
* DESCRIPTION:
*   The function EwDeregisterResource() removes the resource object aObject 
*   from the global MapList. After the object has been removed, the resource
*   stored in the object can not be shared anymore.
*
* ARGUMENTS:
*   aObject - Pointer to the resource object to remove from the MapList.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwDeregisterResource( XObject aObject )
{
  XMapItem* item = MapListHead;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Nothing to do */
  if ( !aObject )
    return;

  /* repeat until the desired item has been found or all item are evaluated */
  while ( item && ( item->Object != aObject ))
    item = item->Next;

  /* Not found? */
  if ( !item )
    return;

  /* Track the RAM usage */
  EwResourcesMemory -= sizeof( XMapItem );

  #ifdef EW_USE_BLOB_DATA
    EwResourcesMemory -= item->BlobSize;
  #endif

  /* remove and release the item */
  UncacheItem( item );
  EwFree( item );
}


/*******************************************************************************
* FUNCTION:
*   EwLoadResource
*
* DESCRIPTION:
*   The function EwLoadResource() will be called from the automatic generated
*   'C' code in order to load a resource. EwLoadResource() verifies whether the
*   required resource is already loaded and if it's true, the function returns
*   the pointer to the object where the resource is stored in.
*
*   If the requested resource is not loaded yet, EwLoadResource() creates a new
*   object of the class aClass and invokes it in order to load the resource.
*
* ARGUMENTS:
*   aResource - Pointer to the resource in the ROM code.
*   aClass    - The class of the resource.
*   aFile     - aFile stores the module name, where the resource object has 
*     been created. aFile is for debugging purpose only.
*   aLine     - aLine stores the line number, at this the resource object has 
*     been created. aLine is for debugging purpose only.
*
* RETURN VALUE:
*   Returns a pointer to the resource object wich stores the required resource.
*
*******************************************************************************/
XObject EwLoadResource( const XVariant* aResource, const void* aClass )
{
  XMapItem*        item = MapListHead;
  const XResource* res;
  XObject          obj;

  /* Perform check operations to detect when the code is running out the CPU
     stack or it is executed in context of a foreign task other than the task
     used by the Embedded Wizard application. */
  EW_CHECK_THREAD_CONTEXT

  /* Nothing to do */
  if ( !aResource )
    return 0;

  /* Look for the version of the resource which fits to the currently
     selected language EwLangId and to the styles set EwStylesSet */
  res = (const XResource*)EwGetVariantOf( aResource, sizeof( XResource ));

  /* The requested resource is managed in an external BLOB. */
  if ( res->LangId == 0x424C4F42 )
  {
    #ifdef EW_USE_BLOB_DATA
      const XBlobLink* bl = (const XBlobLink*)res;
      const XBlobItem* bi = EwFindBlobItem( bl );
      const void*      content;

      /* The requested resource is not available in the BLOB */
      if ( !bi )
      {
        EwErrorDD( 611, bl->UnitId, bl->MemberId );
        return 0;
      }

      /* The found entry does not represent a resource */
      if ( bi->DataType != EW_BLOB_TYPE_RESOURCE )
      {
        EwErrorDD( 612, bl->UnitId, bl->MemberId );
        return 0;
      }

      /* Verify whether the requested resource is already loaded ... */
      while ( item && ( item->BlobOffset != bi->DataOffset ))
        item = item->Next;

      /* ... and if it's return the object of the found resource immediatelly */
      if ( item )
      {
        /* Sort the item in front of the list to find it faster next time */
        UncacheItem( item );
        CacheItem( item );
        return item->Object;
      }

      /* Not yet loaded. Create a new resource map item */
      do
        item = EwAlloc( sizeof( XMapItem ) + bi->DataSize );
      while ( !item && EwImmediateReclaimMemory( 8 ));

      /* Out of memory */
      if ( !item )
      {
        EwError( 8 );
        return 0;
      }

      EwZero( item, sizeof( XMapItem ) + bi->DataSize );
      item->BlobOffset = bi->DataOffset;
      item->BlobSize   = bi->DataSize;
      item->Resource   = item + 1;

      content = EwBlobStartAddress + item->BlobOffset;

      /* The BLOB content is not directly addressible. Map the data in CPU 
         space. */
      if ( EwBlobUseReader )
        content = EwFlashAreaReaderProc( content, item->BlobSize );

      /* Copy the content of the resource */
      EwCopy( item + 1, content, item->BlobSize );

      /* Track the RAM usage */
      EwResourcesMemory += sizeof( XMapItem ) + item->BlobSize;
    #else
      EwError( 632 );
      return 0;
    #endif
  }

  /* The requested resource is stored as static data in ROM. */
  else
  {
    /* Verify whether the requested resource is already loaded ... */
    while ( item && ( item->Resource != res->Resource ))
      item = item->Next;

    /* ... and if it's return the object of the found resource immediatelly */
    if ( item )
    {
      /* Sort the item in front of the list to find it faster next time */
      UncacheItem( item );
      CacheItem( item );
      return item->Object;
    }

    /* Not yet loaded. Create a new resource map item */
    do
      item = EwAlloc( sizeof( XMapItem ));
    while ( !item && EwImmediateReclaimMemory( 8 ));

    /* Out of memory */
    if ( !item )
    {
      EwError( 8 );
      return 0;
    }

    EwZero( item, sizeof( XMapItem ));
    item->Resource = res->Resource; 

    /* Track the RAM usage */
    EwResourcesMemory += sizeof( XMapItem );
  }

  /* Also track the max. memory pressure */
  if ( EwResourcesMemory > EwResourcesMemoryPeak )
    EwResourcesMemoryPeak = EwResourcesMemory;

  if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
    EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

  /* Append a new entry at the end of the MapList */
  CacheItem( item );

  /* Otherwise create a new object of the given resource class aClass and load 
     the resource */
  obj = EwNewObjectIndirect( aClass, (XHandle)item->Resource );

  /* The initialization is failed */
  if ( !item->Object )
  {
    /* Track the RAM usage */
    EwResourcesMemory -= sizeof( XMapItem );

    #ifdef EW_USE_BLOB_DATA
      EwResourcesMemory -= item->BlobSize;
    #endif

    /* remove and release the item */
    UncacheItem( item );
    EwFree( item );
    return 0;
  }

  return obj;
}


/*******************************************************************************
* FUNCTION:
*   EwGetLanguage
*
* DESCRIPTION:
*   The function EwGetLanguage() returns the language ID corresponding to the 
*   currently selected language. The function returns 0 if the 'default' 
*   language is selected.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   Returns the ID of the selected language.
*
*******************************************************************************/
XLangId EwGetLanguage( void )
{
  return (XLangId)EwLangId;
}


/*******************************************************************************
* FUNCTION:
*   EwSetLanguage
*
* DESCRIPTION:
*   The function EwSetLanguage() changes the selected language ID to aLangId.
*   To select the default language pass 0 (zero) in the argument to this 
*   function.
*
*   After the language has been selected, the Resource Manager tries to find
*   resource which fit the selected language.
*
* ARGUMENTS:
*   aLangId - The ID of the desired language.
*
* RETURN VALUE:
*   Returns the assigned aLangId value.
*
*******************************************************************************/
XLangId EwSetLanguage( XLangId aLangId )
{
  /* Any chages? */
  if ( EwLangId == (int)aLangId )
    return aLangId;

  /* Remember the new language and update all objects */
  EwLangId = (int)aLangId;
  EwReconstructObjects();

  return aLangId;
}


/*******************************************************************************
* FUNCTION:
*   EwGetStyles
*
* DESCRIPTION:
*   The function EwGetStyles() returns the set corresponding to the currently 
*   active styles. The function returns 0 if no styles are active.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   Returns the set containing the active styles.
*
*******************************************************************************/
XStylesSet EwGetStyles( void )
{
  return EwStylesSet;
}


/*******************************************************************************
* FUNCTION:
*   EwSetStyles
*
* DESCRIPTION:
*   The function EwSetStyles() changes the set of active styles to the new value
*   aStyles.
*
* ARGUMENTS:
*   aStylesSet - The new styles set.
*
* RETURN VALUE:
*   Returns the assigned aStylesSet value.
*
*******************************************************************************/
XStylesSet EwSetStyles( XStylesSet aStylesSet )
{
  /* Any chages? */
  if ( EwStylesSet == aStylesSet )
    return aStylesSet;

  /* Remember the new styles and update all objects */
  EwStylesSet = aStylesSet;
  EwReconstructObjects();

  return aStylesSet;
}


/*******************************************************************************
* FUNCTION:
*   EwStylesContains
*
* DESCRIPTION:
*   The function EwStylesContains() implements the Chora instant method 
*   'styles.contains()'.
*
* ARGUMENTS:
*   aStylesSet1 - The first style to verify its content.
*   aStylesSet2 - The second style.
*
* RETURN VALUE:
*   The function returns != 0, if the second style aStylesSet2 is contained
*   in the given aStylesSet1.
*
*******************************************************************************/
int EwStylesContains( XStylesSet aStylesSet1, XStylesSet aStylesSet2 )
{
  return aStylesSet2 && (( aStylesSet1 & aStylesSet2 ) == aStylesSet2 );
}


/*******************************************************************************
* FUNCTION:
*   EwFindBlobItem
*
* DESCRIPTION:
*   The function EwFindBlobItem() searches the BLOB file for an entry described
*   by aBlobLink. The search operation first limits to items for the currently
*   selected language. If no matching item is found, the operation repeats
*   looking for an item for the language 'Default'.
*
*   See also EwSetBlobData().
*
* ARGUMENTS:
*   aBlobLink - Contains the IDs of the item to search for in the BLOB file.
*
* RETURN VALUE:
*   Returns the pointer to the found BLOB item or NULL if BLOB does not contain
*   an item described in aBlobLink.
*
*******************************************************************************/
const XBlobItem* EwFindBlobItem( const XBlobLink* aBlobLink )
{
  #ifdef EW_USE_BLOB_DATA
    const XBlobItem* bi;

    /* First search for a variant of the resource matching the actually
       selected language */
    bi = FindBlobItem( aBlobLink->UnitId, aBlobLink->MemberId, EwLangId );

    /* If not found, in second pass search for the default version of the
       resource. Do this only, when the current language is not the 'default'
       one. */
    if ( !bi && EwLangId )
      bi = FindBlobItem( aBlobLink->UnitId, aBlobLink->MemberId, 0 );

    return bi;
  #else
    EW_UNUSED_ARG( aBlobLink );
    return 0;
  #endif
}


/*******************************************************************************
* FUNCTION:
*   EwGetBlobConstant
*
* DESCRIPTION:
*   The function EwGetBlobConstant() searches the BLOB file for a constant
*   described by aBlobLink and data type aType. If such entry is found, the
*   function returns a pointer to the memory containing the constant. If no
*   matching entry is found, the function returns NULL.
*
*   See also EwSetBlobData().
*
* ARGUMENTS:
*   aBlobLink - Contains the IDs of the item to search for in the BLOB file.
*   aBlobType - Expected type of the constant (see EW_BLOB_TYPE_XXX).
*
* RETURN VALUE:
*   Returns the pointer to the content of the constant or NULL if BLOB does not
*   contain an item described in aBlobLink and aType.
*
*******************************************************************************/
const void* EwGetBlobConstant( const XBlobLink* aBlobLink, int aBlobType )
{
  #ifdef EW_USE_BLOB_DATA
    /* Search for the constant in the BLOB file. */
    const XBlobItem* bi      = EwFindBlobItem( aBlobLink );
    const char*      content;

    /* The requested resource is not available in the BLOB */
    if ( !bi )
    {
      EwErrorDD( 621, aBlobLink->UnitId, aBlobLink->MemberId );
      return 0;
    }

    /* The found entry does not represent a resource */
    if ( bi->DataType != aBlobType )
    {
      EwErrorDD( 622, aBlobLink->UnitId, aBlobLink->MemberId );
      return 0;
    }

    /* The address of the constant within the BLOB */
    content = EwBlobStartAddress + bi->DataOffset;

    /* The BLOB content is not directly addressible. Map the data in CPU 
       space. */
    if ( EwBlobUseReader )
      content = (const char*)EwFlashAreaReaderProc( content, bi->DataSize );

    return content;
  #else
    EW_UNUSED_ARG( aBlobLink );
    EW_UNUSED_ARG( aBlobType );
    EwError( 633 );
    return 0;
  #endif
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOf
*
* DESCRIPTION:
*   The function EwGetVariantOf() will be called to determinate a multilingual/
*   multivariant value of the constant or resource aVariant, depending on the 
*   currently selected language and the styles set.
*
*   If the currently selected language could not be found, the function returns
*   the value corresponding to the default language (LangId == 0). In case of a
*   multivariant definition, the function evaluates the variants in order to 
*   find one, which fits the styles currently active in the styles set.
*
* ARGUMENTS:
*   aVariant - A pointer to the affected multilingual/multivariant definition.
*   aSize    - The size to a single entry in the language table of the affected
*     definition.
*
* RETURN VALUE:
*   Returns the pointer to the found value of the definition.
*
*******************************************************************************/
const void* EwGetVariantOf( const XVariant* aVariant, int aSize )
{
  const void* value     = 0;
  const void* defValue  = 0;

  /* Traverse the derivation hierarchy of the variants and look for the one,
     which fits to the currently active styles */
  while ( aVariant )
  {
    int                noOfLang   = aVariant->NoOfLanguages;
    const char*        content    = aVariant->Content;
    const XSubVariant* subVariant = aVariant->SubVariants;

    /* Verify, whether the variant does contain a value for the currently
       selected language */
    for ( ; noOfLang > 0; noOfLang--, content += aSize )
    {
      /* Remember, where the language dependent value is stored in */
      if ( *(int*)(void*)content == EwLangId )
        value = content;

      /* Also remember the location of the default, language independent value 
         of this constant variant */
      if ( !*(int*)(void*)content )
        defValue = content;

      /* The content of the resource is found in an externally managed BLOB?
         This special case is signed by a resource associated to language with
         the special ID 0x424C4F42 = 'BLOB'. Check the BLOB for the existence
         of the given variant. */
      #ifdef EW_USE_BLOB_DATA
        if ( *(int*)(void*)content == 0x424C4F42 )
        {
          const XBlobLink* blobLink = (const XBlobLink*)content;

          /* Language specific value found in BLOB */
          if ( FindBlobItem( blobLink->UnitId, blobLink->MemberId, EwLangId ))
            value = content;

          /* Language default value found in BLOB */
          else if ( FindBlobItem( blobLink->UnitId, blobLink->MemberId, 0 ))
            defValue = content;
        }
      #endif
    }

    /* If the variant does own sub variants, verify whether one of them does 
       fit to the currently active styles */
    if ( subVariant )
    {
      /* Repeat until all sub variants are evaluated or the evaluated sub variant
         does fit to the currently active styles set */
      while ( subVariant->Style && !( subVariant->Style & EwStylesSet ))
        subVariant++;

      /* No sub variant does fit to the styles set - Forget it! */
      if ( !subVariant->Variant )
        subVariant = 0;
    }

    /* A sub variant could been found - continue the evaluation with this sub
       variant */
    if ( subVariant )
      aVariant = subVariant->Variant;
    else
      aVariant = 0;
  }

  /* If the language dependet value could be found? */
  if ( value )
    return value;

  /* Otherwise return the default value */
  return defValue;
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfLangId
*
* DESCRIPTION:
*   The function EwGetVariantOfLangId() will be called to determinate a value
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
*   aVariants - A pointer to the constant containing multiple language id
*     values.
*
* RETURN VALUE:
*   Returns the determinated language id value.
*
*******************************************************************************/
XLangId EwGetVariantOfLangId( const XVariant* aConstant )
{
  return ((const XVariantOfLangId*)EwGetVariantOf( aConstant, 
    sizeof( XVariantOfLangId )))->Value;
}


/*******************************************************************************
* FUNCTION:
*   EwGetVariantOfStylesSet
*
* DESCRIPTION:
*   The function EwGetVariantOfStylesSet() will be called to determinate a value
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
*   aVariants - A pointer to the constant containing multiple styles set values.
*
* RETURN VALUE:
*   Returns the determinated styles set value.
*
*******************************************************************************/
XStylesSet EwGetVariantOfStylesSet( const XVariant* aConstant )
{
  return ((const XVariantOfStylesSet*)EwGetVariantOf( aConstant, 
    sizeof( XVariantOfStylesSet )))->Value;
}


/*******************************************************************************
* FUNCTION:
*   EwDecompress
*
* DESCRIPTION:
*   The function EwDecompress() implements a simple algorithm used for the 
*   decompression of resources, constants, etc. The function decompresses the 
*   entire compressed data block aData and stores the result in aDest memory.
*
*   When decompressing bitmap contents, the arguments aWidth and aOffset provide
*   the decompressor with the information about the memory layout of the bitmap.
*   This is also useful, when decompressing non continuous memory contents.
*
* ARGUMENTS:
*   aData   - Pointer to compressed data.
*   aDest   - Pointer to the memory where the decompressed data should be stored
*     in.
*   aWidth  - In case of bitmap decompression, the width of a single pixel row
*     in bytes. If the destination is a continuous memory area, aWidth should be
*     0.
*   aPitch  - In case of bitmap decompression, the distance between two pixel
*     rows. If the destination is a continuous memory area, aPitch should be 0.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwDecompress( const unsigned int* aData, unsigned char* aDest, 
  int aWidth, int aPitch )
{
  static unsigned short* lValues;
  static unsigned char*  rValues;
  static unsigned char*  stack;
  unsigned int           acc1      = 0;
  unsigned int           acc2      = 0;
  int                    depth     = 9;
  int                    len       = 32;
  unsigned short         mask      = 0x01FF;
  unsigned short         nextCode  = 258;
  unsigned short         oldCode   = 0xFFFF;
  unsigned short         curCode;
  unsigned int           count     = aWidth;
  const unsigned int*    data      = aData;
  int                    useReader = EwFlashAreaReaderProc && 
                                     ((void*)aData >= EwFlashAreaStartAddress ) && 
                                     ((void*)aData <= EwFlashAreaEndAddress );

  /* For the first time reserve memory for decompression buffers */
  if ( !DecompressBuffer )
  {
    int size = (( 4096 - 258 ) * sizeof( short )) + ( 4096 - 258 ) + 4096;

    do
      DecompressBuffer = EwAlloc( size );
    while ( !DecompressBuffer && EwImmediateReclaimMemory( 9 ));

    /* Not enough memory for the buffer */
    if ( !DecompressBuffer )
    {
      EwError( 9 );
      EwPanic();
      return;
    }

    /* Track the RAM usage */
    EwResourcesMemory += size;

    /* Also track the max. memory pressure */
    if ( EwResourcesMemory > EwResourcesMemoryPeak )
      EwResourcesMemoryPeak = EwResourcesMemory;

    if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
      EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;
  }

  /* Internally used buffers for decompression */
  lValues = DecompressBuffer;
  rValues = (unsigned char*)( lValues + 4096 - 258 );
  stack   = rValues + 4096 - 258;

  /* The data is stored in not directly accessible memory area - load the block 
     containing the data first */
  if ( useReader )
    data = EwFlashAreaReaderProc( aData, 0 );

  /* First data word is loaded in the 'acc' register */
  acc1 = *data++;
  aData++;

  /* Read the first code word from the 'acc' register */
  curCode = (unsigned short)( acc1 & mask );
  acc1  >>= depth;
  len    -= depth;

  /* repeat until the END_OF_DATA code word is found */
  while ( curCode != 257 )
  {
    unsigned short tmp = curCode;
    int            ofs = 0;

    /* CLEAR_CODE found? Then reset the decompressors tables and the state
       machine */
    if ( curCode == 256 )
    {
      depth    = 9;
      mask     = 0x01FF;
      nextCode = 258;
      curCode  = 0xFFFF;
      goto L1;
    }

    /* Special case -> the found code word is not yet stored in the table.
       In this case we can reconstruct the missing code word from the last 
       evaluated code word. */
    if ( curCode == nextCode )
    {
      tmp = oldCode;
      ofs++;
    }

    /* Extract the compressed bytes and store them on the internal stack.
       The stack is used to reverse the order of extracted bytes. */
    while ( tmp > 257 )
    {
      tmp -= 258;
      stack[ ofs++ ] = rValues[ tmp ];
      tmp            = lValues[ tmp ];
    }

    /* The last code word is equal the uncompressed byte */
    stack[ ofs++ ] = (unsigned char)tmp;

    /* Continue with the special case: repeat the first character from the
       last sequenz */
    if ( curCode == nextCode )
      stack[ 0 ] = stack[ ofs - 1 ];

    /* Append new entry to the table */
    if ( oldCode != 0xFFFF )
    {
      lValues[ nextCode - 258 ] = oldCode;
      rValues[ nextCode - 258 ] = stack[ ofs - 1 ];

      /* Calculate the code word depth */
      if ((( nextCode ^ ( nextCode + 1 )) > nextCode ) && ( depth < 12 ))
      {
        depth++;
        mask = (unsigned short)(( mask << 1 ) | 1 );
      }

      nextCode++;
    }

    /* Write the content of the stack in revers order to the aDest memory.
       Note the optional layout parameters of the destination memory block */
    if ( !aWidth || !aPitch )
      while ( ofs-- )
        *aDest++ = stack[ ofs ];

    /* The destination memory consists of rows with gaps. Skip over these 
       gaps */
    else
      while ( ofs-- )
      {
        *aDest++ = stack[ ofs ];

        /* check for end of line */
        if ( --count == 0 )
        {
          /* add offset to destination pointer */
          aDest += aPitch - aWidth;

          /* restart counter */
          count = aWidth;
        }
      }

   L1:
    /* move the next data word to the 'acc' register? */
    if ( len <= 16 )
    {
      /* The data from the previously loaded block is processed. Get the next 
         block. */
      if ( useReader && !((unsigned long)aData & ( EwFlashAreaBlockSize - 1 )))
        data = EwFlashAreaReaderProc( aData, 0 );

      acc2   = *data++;
      acc1  |= acc2 << len;
      acc2 >>= 32 - len;
      len   += 32;
      aData++;
    }

    /* Read the next code word */
    oldCode = curCode;
    curCode = (unsigned short)( acc1 & mask );
    acc1  >>= depth;
    acc1   |= acc2 << ( 32 - depth );
    acc2  >>= depth;
    len    -= depth;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwAdaptByteOrder2
*
* DESCRIPTION:
*   The function EwAdaptByteOrder2() provides a re-order function to convert
*   an array of short words from the default little-endian format to the target
*   CPU dependent endian format.
*
*   If the endian format of the target CPU is already little, no modification
*   will take place here and the function returns immediatelly.
*
* ARGUMENTS:
*   aData  - Pointer to the array containing short words.
*   aCount - Number of words within the array to convert.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwAdaptByteOrder2( void* aData, int aCount )
{
  unsigned short* data = aData;

  if ( !IsBigEndianArch())
    return;

  /* Evaluate all entries within the array */
  for ( ; aCount > 0; aCount--, data++ )
  {
    unsigned short tmp = *data;
    *data = (unsigned short)(( tmp >> 8 ) | ( tmp << 8 ));
  }
}


/*******************************************************************************
* FUNCTION:
*   EwAdaptByteOrder4
*
* DESCRIPTION:
*   The function EwAdaptByteOrder4() provides a re-order function to convert
*   an array of long words from the default little-endian format to the target
*   CPU dependent endian format.
*
*   If the endian format of the target CPU is already little, no modification
*   will take place here and the function returns immediatelly.
*
* ARGUMENTS:
*   aData  - Pointer to the array containing long words.
*   aCount - Number of words within the array to convert.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwAdaptByteOrder4( void* aData, int aCount )
{
  unsigned int* data = (unsigned int*)aData;

  if ( !IsBigEndianArch())
    return;

  /* Evaluate all entries within the array */
  for ( ; aCount > 0; aCount--, data++ )
  {
    unsigned int tmp = *data;

    *data = ( tmp << 24 ) | ( tmp >> 24 ) | (( tmp & 0xFF00 ) << 8 ) | 
            (( tmp >> 8 ) & 0xFF00 );
  }
}


/*******************************************************************************
* FUNCTION:
*   EwReleaseDecompressBuffers
*
* DESCRIPTION:
*   The function EwReleaseDecompressBuffers() frees the memory used internally 
*   by the decompress routines. This function is very usefull for a safe
*   shutdown of the Runtime Environment.
*
*   It is important to free all memory before the Runtime Environment will be
*   shut down.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwReleaseDecompressBuffers( void )
{
  /* No buffer to free */
  if ( !DecompressBuffer )
    return;

  /* Free the buffer memory */
  EwFree( DecompressBuffer );
  DecompressBuffer = 0;

  /* Track the RAM usage */
  EwResourcesMemory -= (( 4096 - 258 ) * sizeof( short )) + ( 4096 - 258 ) +
                          4096;
}


/* This internal function initializes the signals module functionality. */
void EwInitResources( void )
{
  MapListHead             = 0;
  EwLangId                = 0; 
  EwStylesSet             = 0;
  EwFlashAreaReaderProc   = 0;
  EwFlashAreaStartAddress = 0;
  EwFlashAreaEndAddress   = 0;
  EwFlashAreaBlockSize    = 0;
  DecompressBuffer        = 0;

  #ifdef EW_USE_BLOB_DATA
    EwBlobStartAddress    = 0;
    EwBlobEndAddress      = 0;
    EwBlobUseReader       = 0;
    EwNoOfBlobItems       = 0;
    EwBlobItemsAddress    = 0;
  #endif
}


/* This internal function de-initializes the signals module functionality. */
void EwDoneResources( void )
{
  /* Release all mapped resources */
  while ( MapListHead )
  {
    XMapItem* tmp = MapListHead;

    /* Track the RAM usage */
    EwResourcesMemory -= sizeof( XMapItem );

    #ifdef EW_USE_BLOB_DATA
      EwResourcesMemory -= tmp->BlobSize;
    #endif

    /* remove and release the item */
    UncacheItem( tmp );
    EwFree( tmp );
  }

  EwReleaseDecompressBuffers();
}


/*******************************************************************************
* FUNCTION:
*   EwRegisterFlashAreaReader
*
* DESCRIPTION:
*   The function EwRegisterFlashAreaReader() registers a specified memory area
*   as belonging to Flash memory not intended to be directly addressed by the
*   CPU. In order to access this Flash memory, the respective Flash pages need
*   to be loaded first into internal buffer. This 'reading' operation has to be
*   handled by external function, specified in the first parameter aReaderProc.
*   The implementation of the function is up to the user.
*   
*   Embedded Wizard allows only one reader to be registered at the same time.
*   Invoking the function EwRegisterFlashAreaReader() twice with different
*   start/end addresses reports an error. In order to remove the previously 
*   registered reader, invoke the function with the previously specified start
*   and end addresses and NULL in the aReaderProc parameter.
*
*   This function should be invoked before invoking EwInitGraphicsEngine().
*
* ARGUMENTS:
*   aReaderProc   - User implemented function to read Flash memory areas into
*     internal buffers. See the description for XFlashAreaReaderProc.
*   aStartAddress - Start address of the Flash area to take in account.
*   aEndAddress   - End address of the Flash area to take in account.
*   aBlockSize    - Size of of the page or block, the function will read from
*     the Flash memory. The value is expressed in bytes and it should by a
*     power of two value (e.g. 512, 1024, ... 4096, etc.).
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwRegisterFlashAreaReader( XFlashAreaReaderProc aReaderProc, 
  void* aStartAddress, void* aEndAddress, int aBlockSize )
{
  /* Trying to specify a further Flash area reader? */
  if ( aReaderProc && EwFlashAreaReaderProc && 
     (( EwFlashAreaStartAddress != aStartAddress ) ||
      ( EwFlashAreaEndAddress   != aEndAddress )))
  {
    EwError( 271 );
    EwPanic();
  }

  /* Register the reader? */
  if ( aReaderProc )
  {
    EwFlashAreaStartAddress = aStartAddress;
    EwFlashAreaEndAddress   = aEndAddress;
    EwFlashAreaBlockSize    = aBlockSize;
    EwFlashAreaReaderProc   = aReaderProc;
  }

  /* De-register the reader? */
  else
  {
    EwFlashAreaStartAddress = 0;
    EwFlashAreaEndAddress   = 0;
    EwFlashAreaBlockSize    = 0;
    EwFlashAreaReaderProc   = 0;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwSetBlobData
*
* DESCRIPTION:
*   The function EwSetBlobData() registers the given memory area as containing
*   resources and constants to be used by the Embedded Wizard application.
*   Unlike resources and constants stored in C code, the data can thus be setup
*   after the application has be compiled and linked. Even exchanging the data
*   retrospectively is possible.
*
*   Following are the most typical scenarios:
*
*   1. The entire BLOB content is existing in CPU addressable flash space. In
*      this case provide in the parameter aStartAddress and aEndAddress the
*      start and the end addresses of the BLOB memory area.
*
*   2. The entire BLOB content is loaded from e.g. a file system into the RAM.
*      It is thus CPU addressable. In this case provide in the parameter
*      aStartAddress and aEndAddress the start and the end addresses of the
*      BLOB memory area.
*
*   3. The BLOB content is existing in an external, not CPU addressable flash
*      memory. In this case configure the linker to exclude an area with size
*      at least as large as the BLOB content. This address area has to be
*      reserved for the BLOB content exclusively.
*
*      Then register a flash area reader to map accesses to the excluded area.
*      In the implementation of the reader take care of loading memory pages
*      from the external flash in RAM and provide access to so cached BLOB
*      contents. For more details see EwRegisterFlashAreaReader().
*
*      Finally, invoke EwSetBlobData() with the start and end addresses of the
*      excluded area.
*
*   4. The BLOB content is stored on a file system, so it is not available in
*      any memory area. In this case configure the linker to exclude an area
*      with size at least as large as the BLOB content. This address area has
*      to be reserved for the BLOB content exclusively.
*
*      Then register a flash area reader to map accesses to the excluded area.
*      In the implementation of the reader take care of loading memory pages
*      from the file in RAM and provide access to so cached BLOB contents.
*      For more details see EwRegisterFlashAreaReader().
*
*      Finally, invoke EwSetBlobData() with the start and end addresses of the
*      excluded area.
*
*   Embedded Wizard allows only one BLOB to be setup at the same time. Invoking
*   the function EwSetBlobData() twice reports an error. To change the BLOB
*   content it is inevitable to restart the system.
*
*   This function should be invoked before invoking EwInitGraphicsEngine() and
*   after EwRegisterFlashAreaReader().
*
* ARGUMENTS:
*   aStartAddress - Start address of the BLOB area.
*   aEndAddress   - End address of the BLOB area.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwSetBlobData( const void* aStartAddress, const void* aEndAddress )
{
  #ifdef EW_USE_BLOB_DATA
    const XBlobHeader* header    = (const XBlobHeader*)aStartAddress;
    int                useReader = EwFlashAreaReaderProc && 
                                   ((void*)header >= EwFlashAreaStartAddress ) &&
                                   ((void*)header <= EwFlashAreaEndAddress   );

    /* Changing the BLOB content at the runtime is not foreseen. Already loaded
       resources retain dependenies to the original BLOB contents. Therefore,
       to use other BLOB content, it is necessary to restart the GUI system. */
    if ( EwBlobStartAddress || EwBlobEndAddress )
    {
      EwError( 601 );
      return;
    }

    /* Is the address range valid? */
    if ( aEndAddress <= aStartAddress )
    {
      EwError( 602 );
      return;
    }

    /* To avoid bus errors due to unaligned accesses, the BLOB has to start at a
       modulo 4-byte address. */
    if ((unsigned long)header % 4 )
    {
      EwError( 603 );
      return;
    }

    /* The BLOB content is not directly accessible. Map the data in CPU space */
    if ( useReader )
      header = EwFlashAreaReaderProc( header, sizeof( *header ));

    /* Check the byte order of the BLOB file. */
    if ( header->MagicNo == BLOB_MAGIC_NUMBER_WRONG_BYTE_ORDER )
    {
      EwError( 604 );
      return;
    }

    /* Does the reader provide a real BLOB file */
    if ( header->MagicNo != BLOB_MAGIC_NUMBER )
    {
      EwError( 605 );
      return;
    }

    /* Does the version of the BLOB correspond to the version of the RTE? */
    if (( header->Version ^ EW_RTE_VERSION ) & 0xFFFF0000 )
    {
      EwError( 606 );
      return;
    }

    /* Is the BLOB file correctly linked to the binary? */
    if (( header->Checksum1 != EwBlobChecksum[0]) ||
        ( header->Checksum2 != EwBlobChecksum[1]))
    {
      EwError( 607 );
      return;
    }

    /* The BLOB is o.k. Remember the common BLOB data. */
    EwBlobStartAddress = (const char*)aStartAddress;
    EwBlobEndAddress   = (const char*)aEndAddress;
    EwBlobUseReader    = useReader;
    EwNoOfBlobItems    = header->NoOfItems;
    EwBlobItemsAddress = (const XBlobItem*)( EwBlobStartAddress +
                                             header->ItemsOffset );
  #else
    EW_UNUSED_ARG( aStartAddress );
    EW_UNUSED_ARG( aEndAddress );
    EwError( 631 );
  #endif
}


/* This helper function evaluates the endian architecture of the target CPU. */
static int IsBigEndianArch( void )
{
  unsigned int   tmpL = 0x12345678;
  unsigned char* tmpC = (unsigned char*)(void*)&tmpL;

  return *tmpC != 0x78;
}


/* The function CacheItem() stores the resource item aItem at the begin of the
   global list. */
static void CacheItem( XMapItem* aItem )
{
  /* insert the item into the list */
  aItem->Next = MapListHead;
  aItem->Prev = 0;

  if ( MapListHead )
    MapListHead->Prev = aItem;

  MapListHead = aItem;
}


/* The function UncacheItem() removes the item aItem from the global list. */
static void UncacheItem( XMapItem* aItem )
{
  /* remove the block from the list */
  if ( aItem->Next )
    aItem->Next->Prev = aItem->Prev;

  if ( aItem->Prev )
    aItem->Prev->Next = aItem->Next;
  else
    MapListHead = aItem->Next;

  aItem->Next = 0;
  aItem->Prev = 0;
}


#ifdef EW_USE_BLOB_DATA
  /* The function FindBlobItem() searches in the blob file for an item identified
     by the given name ids. If sucessfull, returns a pointer to the item or NULL
     if the item is not existing. Note, the returned pointer is valid until the
     next EwBlobAreaReadProc() invocation. */
  static const XBlobItem* FindBlobItem( int aId1, int aId2, int aId3 )
  {
    int min = 0;
    int max = EwNoOfBlobItems - 1;

    /* Search the list of BLOB items for an item identified by the given ids */
    while ( max >= min )
    {
      int              index = ( max + min ) / 2;
      const XBlobItem* bi    = EwBlobItemsAddress + index;
      int              comp;

      /* The BLOB content is not directly accessible. Map the data in CPU space */
      if ( EwBlobUseReader )
        bi = EwFlashAreaReaderProc( bi, sizeof( *bi ));

      /* Compare the item */
      comp               = bi->Id[0] - aId1;
      if ( !comp ) comp  = bi->Id[1] - aId2;
      if ( !comp ) comp  = bi->Id[2] - aId3;

      if      ( comp > 0 ) min = index + 1 ;
      else if ( comp < 0 ) max = index - 1;

      /* ok, found. */
      else
        return bi;
    }

    /* Not found */
    return 0;
  }
#endif


/* pba, msy */
