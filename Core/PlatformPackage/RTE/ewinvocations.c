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
*   The module 'ewinvocations.c' contains a set of EWRTE functions purpose-
*   built for recording of function invocations triggered in context of a
*   foreign thread or interrupt service routines. The recorded invocations can
*   thereupon be executed in the regular context of the Embedded Wizard
*   application. The underlying functioality implements a queue.
*
* SUBROUTINES:
*   EwInitInvocations
*   EwDoneInvocations
*   EwInvoke
*   EwInvokeCopy
*   EwProcessInvocations
*
*******************************************************************************/

#include "ewrte.h"
#include "ewextrte.h"


/* The following code is used for debbuging only. */
extern int EwObjectsMemory;
extern int EwObjectsMemoryPeak;
extern int EwStringsMemory;
extern int EwResourcesMemory;
extern int EwMemoryPeak;
extern int EwInvocationsMemory;


/* The function EwAtomicFetchAndAdd() implements a read-modify-write operation
   for an atomic, not interruptible addition. This prevents race-conditions in
   case of an application is running multiple threads or implementing interrupt
   service routines. */
extern int EwAtomicFetchAndAdd( XAtomic* aAtomic, int aArg );


/* The following variables manage a queue intended to record pending function
   invocations. */
static int             QueueSize = 0;
static volatile void** Queue     = 0;
static XAtomic         QueueFC   = 0;
static XAtomic         QueueWI   = 0;
static volatile int    QueueRI   = 0;


/* Following state variables are used to track errors detected in EwInvoke()
   or EwInvokeCopy() functions since these functions may run in context of
   foreign threads or interrupt service routines and reporting an error from
   the function may result in inpredicable behavior. */
static int             QueueErr441 = 0;
static int             QueueErr442 = 0;
static int             QueueErr443 = 0;
static int             QueueErr444 = 0;
static int             QueueErr445 = 0;


/* This helper function zeroes aCount queue entries starting with the entry
   aIndex. */
static void ZeroQueue( int aIndex, int aCount )
{
  for ( ; aCount > 0; aIndex = 0 )
    for ( ; ( aIndex < QueueSize ) && ( aCount > 0 ); aIndex++, aCount-- )
      Queue[ aIndex ] = 0;
}


/* This helper function copies aSize bytes from aData memory to the queue
   starting with the entry aIndex. */
static void CopyToQueue( int aIndex, const void* aData, int aSize )
{
  volatile char* queue     = (volatile char*)Queue;
  int            queueSize = QueueSize * sizeof( void* );
  const char*    data      = (const char*)aData;
  int            index     = aIndex * sizeof( void* );

  for ( ; aSize > 0; index = 0 )
    for ( ; ( index < queueSize ) && ( aSize > 0 ); index++, aSize-- )
      queue[ index ] = *data++;
}


/* This helper function copies aCount queue entries from the queue starting with
   the entry aIndex to the memory aData; */
static void CopyFromQueue( int aIndex, void* aData, int aCount )
{
  void** data = (void**)aData;

  for ( ; aCount > 0; aIndex = 0 )
    for ( ; ( aIndex < QueueSize ) && ( aCount > 0 ); aIndex++, aCount-- )
      *data++ = (void*)Queue[ aIndex ];
}


/* The following function verifies whether there is an invokation avaiable in
   the queue and pending for its execution. The function processes thereupon
   the invocation, removes it from the queue and returns != 0. If there is no
   pending invocation, the function returns 0. */
static int ProcessNextInvocation( void )
{
  int         inxP  = QueueRI      % QueueSize;
  int         inxD  = ( inxP + 1 ) % QueueSize;
  int         inxS  = ( inxD + 1 ) % QueueSize;
  int         inxC  = ( inxS + 1 ) % QueueSize;
  const void* data  = 0;
  void*       heap  = 0;
  int         count;
  int         fc    = EwAtomicFetchAndAdd( &QueueFC, 0 );

  /* Track the max. usage of the invocation queue */
  if (( fc * (int)sizeof( void*)) > EwInvocationsMemory )
    EwInvocationsMemory = fc * (int)sizeof( void* );

  /* No completed invoke requests pending at the actual read position in the
     queue. */
  if ( !fc || !Queue[ inxP ])
    return 0;

  /* How many queue entries are used to store a copy of the originally provided
     data? */
  count = (int)((unsigned long)Queue[ inxS ]);

  /* The data is available as copy in the queue. */
  if ( count )
  {
    /* If the data is stored as two parts at the end and at the begining of the
       queue? Reserve a temp. buffer to merge the both fragments. */
    if (( inxC + count ) > QueueSize )
    {
      do
        data = heap = EwAlloc( count * sizeof( void* ));
      while ( !heap && EwImmediateReclaimMemory( 53 ));

      /* No memory for the internal buffer */
      if ( !heap )
        EwError( 53 );

      /* Copy the fragments */
      if ( heap )
      {
        CopyFromQueue( inxC, heap, count );

        /* Track the RAM usage */
        EwObjectsMemory += count * sizeof( void* );

        /* Also track the max. memory pressure */
        if ( EwObjectsMemory > EwObjectsMemoryPeak )
          EwObjectsMemoryPeak = EwObjectsMemory;

        if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
          EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;
      }
    }
    else
      data = (const void*)&Queue[ inxC ];
  }

  /* No copy. The queue stores the original pointer passed in the Invoke()
     operation. */
  else
    data = (const void*)Queue[ inxD ];

  /* Invoke the recorde function. */
  ((XInvokeProc)Queue[ inxP ])( data );

  /* Free temp. used buffers */
  if ( heap )
  {
    EwFree( heap );

    /* Track the RAM usage */
    EwObjectsMemory -= count * sizeof( void* );
  }

  /* Clear the queue areas. */
  ZeroQueue( inxC, count );

  Queue[ inxS ] = 0;
  Queue[ inxD ] = 0;
  Queue[ inxP ] = 0;

  QueueRI += 3 + count;
  EwAtomicFetchAndAdd( &QueueFC, -3 - count );

  return 1;
}


/*******************************************************************************
* FUNCTION:
*   EwInitInvocations
*
* DESCRIPTION:
*   The function EwInitInvocations() initializes the internal invocation queue.
*   This queue is used to store function invocations scheduled in context of
*   foreign threads or interrupt service routines. The functions can then be
*   executed in the safe context of the Embedded Wizard application.
*
* ARGUMENTS:
*   aQueueSize - Determines the size of the invocation queue in bytes. The
*     value has to be at least 32 bytes large.
*
* RETURN VALUE:
*   Returns != 0 if successful.
*
*******************************************************************************/
int EwInitInvocations( int aQueueSize )
{
  /* The min. size of the queue. */
  if ( aQueueSize <= 32 )
    aQueueSize = 32;

  /* First clear all pointers and counters */
  QueueSize = 0; QueueErr441 = 0;
  Queue     = 0; QueueErr442 = 0;
  QueueFC   = 0; QueueErr443 = 0;
  QueueWI   = 0; QueueErr444 = 0;
  QueueRI   = 0; QueueErr445 = 0;

  /* Queue size in queue entries, which are void* pointers */
  QueueSize = ( aQueueSize + sizeof( void* ) - 1 ) / sizeof( void* );
  Queue     = EwAlloc( QueueSize * sizeof( void* ));

  /* Failed to reserve memory for the queue */
  if ( !Queue )
  {
    QueueSize = 0;
    EwError( 52 );
    return 0;
  }

  /* Ensure the queue is zeroed at its initialisiation time */
  ZeroQueue( 0, QueueSize );

  /* Track the RAM usage */
  EwObjectsMemory += QueueSize * sizeof( void* );

  /* Also track the max. memory pressure */
  if ( EwObjectsMemory > EwObjectsMemoryPeak )
    EwObjectsMemoryPeak = EwObjectsMemory;

  if (( EwObjectsMemory + EwStringsMemory + EwResourcesMemory ) > EwMemoryPeak )
    EwMemoryPeak = EwObjectsMemory + EwStringsMemory + EwResourcesMemory;

  return 1;
}


/*******************************************************************************
* FUNCTION:
*   EwDoneInvocations
*
* DESCRIPTION:
*   The function EwDoneInvocations() deinitializes the invocations queue.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwDoneInvocations( void )
{
  /* No queue initialized */
  if ( !Queue )
    return;

  /* Free the memory used by the queue */
  EwFree((void*)Queue );

  /* Track the RAM usage */
  EwObjectsMemory -= QueueSize * sizeof( void* );

  /* No queue anymore. Clear all variables. */
  Queue     = 0; QueueErr441 = 0;
  QueueSize = 0; QueueErr442 = 0;
  QueueFC   = 0; QueueErr443 = 0;
  QueueWI   = 0; QueueErr444 = 0;
  QueueRI   = 0; QueueErr445 = 0;
}


/*******************************************************************************
* FUNCTION:
*   EwInvoke
*
* DESCRIPTION:
*   The function EwInvoke() schedules the function aProc to be called during the
*   next iteration through Embedded Wizard application's main loop. This ensures
*   that aProc is invoked in the safe context of Embedded Wizard's own thread or
*   task. The implementation of aProc can thereupon access and use all Embedded
*   Wizard functionality without any restriction.
*
*   Unlike all other Embedded Wizard functions, EwInvoke() is explicitly allowed
*   to be called in context of foreign threads, tasks or even interrupt service
*   routines. In this manner, the thread, task or interrupt service routine can
*   easily communicate with Embedded Wizard application. It can, for example,
*   trigger system events in the GUI application or send data to it.
*
*   The pointer aData may refer a data structure to pass during the execution of
*   aProc. aProc can thereupon access this data structure. Doing this, remember
*   that aProc will be executed asynchronously. You have to ensure that the data
*   pointed by aData remains valid when aProc is executed.
*
*   Alternatively you can use the function EwInvokeCopy(), which copies the data
*   referred by aData. You don't need to worry about the memory management in
*   this case.
*
*   All scheduled invocations are stored within an internal queue. If there is
*   not sufficient space in the queue to record aProc, EwInvoke() will fail and
*   return 0. Your implementation should then wait a while and call EwInvoke()
*   again. Please note, when EwInvoke() is called in context of an interrupt
*   service routine, you may not wait. In such case, ensure in advance that the
*   queue is large enough for the worst case.
*
* ARGUMENTS:
*   aProc   - Function to schedule its invocation in context of Embedded
*     Wizard's own thread or task.
*   aData   - Pointer to pass in the invocation of aProc.
*
* RETURN VALUE:
*   If the invocation could be scheduled, the function returns != 0. If there
*   was not enough space in the internal queue, the function returns 0.
*
*******************************************************************************/
int EwInvoke( XInvokeProc aProc, const void* aData )
{
  int inxP;
  int inxD;
  int inxS;

  /* No queue configured to use EwInvoke(). */
  if ( !QueueSize )
  {
    QueueErr443++;
    return 0;
  }

  /* Try to reserve space on the internal queue large enough to store there
     aProc, aData and count info. If the queue is already full, abort and
     return error. */
  if ( EwAtomicFetchAndAdd( &QueueFC, 3 ) > ( QueueSize - 3 ))
  {
    EwAtomicFetchAndAdd( &QueueFC, -3 );
    return 0;
  }

  /* Get the pointer inside the queue where to store aProc, aData and the
     count info. */
  inxP = EwAtomicFetchAndAdd( &QueueWI, 3 ) % QueueSize;
  inxD = ( inxP + 1 )                       % QueueSize;
  inxS = ( inxD + 1 )                       % QueueSize;

  /* Test for race conditions. The following condition should never become
     'true' unless EwAtomicFetchAndAdd() is not working propertly. */
  if ( Queue[ inxP ] || Queue[ inxD ] || Queue[ inxS ])
    QueueErr441++;

  /* Store the proc and data pointers in the queue. Note, size is 0 because
     no further data is copied into the queue. */
  Queue[ inxS ] = 0;
  Queue[ inxD ] = (volatile void*)aData;
  Queue[ inxP ] = (volatile void*)aProc;

  /* All ok. */
  return 1;
}


/*******************************************************************************
* FUNCTION:
*   EwInvokeCopy
*
* DESCRIPTION:
*   The function EwInvokeCopy() schedules the function aProc to be called during
*   the next iteration through Embedded Wizard application's main loop. This
*   ensures that aProc is invoked in the safe context of Embedded Wizard's own
*   thread or task. The implementation of aProc can thereupon access and use all
*   Embedded Wizard functionality without any restriction.
*
*   Unlike all other Embedded Wizard functions, EwInvokeCopy() is explicitly
*   allowed to be called in context of foreign threads, tasks or even interrupt
*   service routines. In this manner, the thread, task or interrupt service
*   routine can easily communicate with Embedded Wizard application. It can, for
*   example, trigger system events in the GUI application or send data to it.
*
*   The pointer aData refers to a data structure to pass during the execution of
*   aProc. aProc can thereupon access this data structure. Unlike EwInvoke() the
*   function EwInvokeCopy() copies the data structure on the internal queue,
*   what frees you from the necessity to take care of the memory management. You
*   don't need to worry about the validity of aData when aProc is executed. The
*   function aProc will simply receive a pointer to the copied data.
*
*   All scheduled invocations are stored within an internal queue. If there is
*   not sufficient space in the queue to record aProc and the copy of aData,
*   EwInvokeCopy() will fail and return 0. Your implementation should then wait
*   a while and call EwInvokeCopy() again. Please note, when EwInvokeCopy() is
*   called in context of an interrupt service routine, you may not wait. In such
*   case, ensure in advance that the queue is large enough for the worst case.
*
* ARGUMENTS:
*   aProc   - Function to schedule its invocation in context of Embedded
*     Wizard's own thread or task.
*   aData   - Pointer to a data structure to be copied and passed in the
*     invocation of aProc.
*   aSize   - Size of the data structure aData in bytes to copy and pass in
*     the invocation of aProc.
*
* RETURN VALUE:
*   If the invocation could be scheduled, the function returns != 0. If there
*   was not enough space in the internal queue, the function returns 0.
*
*******************************************************************************/
int EwInvokeCopy( XInvokeProc aProc, const void* aData, int aSize )
{
  int count = ( aSize + sizeof( void* ) - 1 ) / sizeof( void* );
  int inxP;
  int inxD;
  int inxS;
  int inxC;

  /* No queue configured to use EwInvokeCopy(). */
  if ( !QueueSize )
  {
    QueueErr444++;
    return 0;
  }

  /* Nothing to copy? Then use the simple version of Invoke(). */
  if ( aSize <= 0 )
    return EwInvoke( aProc, 0 );

  /* The data will never fit inside the queue even if it is completely empty. */
  if (( count + 3 ) > QueueSize )
  {
    QueueErr445++;
    return 0;
  }

  /* Try to reserve space on the internal queue large enough to store there
     aProc, aData, count info and the copied data. If the queue is already
     full, abort and return error. */
  if ( EwAtomicFetchAndAdd( &QueueFC, 3 + count ) > ( QueueSize - 3 - count ))
  {
    EwAtomicFetchAndAdd( &QueueFC, -3 - count );
    return 0;
  }

  /* Get the pointer inside the queue where to store aProc, aData, the count
     info and the data copy. */
  inxP = EwAtomicFetchAndAdd( &QueueWI, 3 + count ) % QueueSize;
  inxD = ( inxP + 1 )                               % QueueSize;
  inxS = ( inxD + 1 )                               % QueueSize;
  inxC = ( inxS + 1 )                               % QueueSize;

  /* Test for race conditions. The following condition should never become
     'true' unless EwAtomicAdd() is not working propertly. */
  if ( Queue[ inxP ] || Queue[ inxD ] || Queue[ inxS ] || Queue[ inxC ])
    QueueErr442++;

  /* Create a copy of the data within the queue */
  CopyToQueue( inxC, aData, aSize );

  /* Store the proc and copied data size. Note, the data pointer is 0 because
     the data is within the queue as copy. */
  Queue[ inxS ] = (volatile void*)(unsigned long)count;
  Queue[ inxD ] = 0;
  Queue[ inxP ] = (volatile void*)aProc;

  /* All ok. */
  return 1;
}


/*******************************************************************************
* FUNCTION:
*   EwProcessInvocations
*
* DESCRIPTION:
*   The function EwProcessInvocations() processes all invocations stored
*   actually in the invocation queue. The invocatins are stored by using the
*   both functions EwInvoke() and EwInvokeCopy().
*
*   If there is no invocation pending for execution, the function does nothing
*   and returns immediately the value 0.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   If no invocations were pending for execution, the function returns 0.
*   Otherwise != 0 is returned.
*
*******************************************************************************/
int EwProcessInvocations( void )
{
  int count = 0;

  /* If error were counted during preceding EwInvoke() or EwInvokeCopy(),
     report the error now, in context of Embedded Wizard thead or task. */
  if ( QueueErr441 ) { EwError( 441 ); QueueErr441 = 0; }
  if ( QueueErr442 ) { EwError( 442 ); QueueErr442 = 0; }
  if ( QueueErr443 ) { EwError( 443 ); QueueErr443 = 0; }
  if ( QueueErr444 ) { EwError( 444 ); QueueErr444 = 0; }
  if ( QueueErr445 ) { EwError( 445 ); QueueErr445 = 0; }

  /* Repeat as long as there are pending invocations. */
  while ( QueueSize && ProcessNextInvocation())
    count++;

  return count > 0;
}


/* pba, msy */
