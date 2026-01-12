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
*   This is an internal module of the Embedded Wizard Graphics Engine EWGFX.
*
*   This module implements the functionality to perform the optimization and
*   elimination steps of drawing tasks and to dispatch the tasks to underlying
*   graphics subsystem or to the emulated software pixel driver.
*
* SUBROUTINES:
*   EwEliminateTasks
*   EwReverseTasks
*   EwReorderTasks
*   EwExecuteTasks
*   EwCompleteTasks
*   EwCountTasks
*   EwTraceTasks
*
*******************************************************************************/

#include "ewrte.h"
#include "ewgfxdriver.h"
#include "ewgfxcore.h"
#include "ewgfxtasks.h"
#include "ewextgfx.h"
#include "ewgfxdefs.h"
#include "ewgfxlinks.h"


/* Helper macro for fast color evaluation */
#define IS_HORZ_GRADIENT( aColors )                                            \
  (( aColors[0] != aColors[1]) || ( aColors[2] != aColors[3]))

#define IS_VERT_GRADIENT( aColors )                                            \
  (( aColors[0] != aColors[3]) || ( aColors[1] != aColors[2]))

#define IS_LINEAR_GRADIENT( aTaskFlags )                                       \
  (( aTaskFlags & EW_TASK_LINEAR_GRADIENT ) == EW_TASK_LINEAR_GRADIENT )


/* The following helper function has the job to traverse the list of drawing
   tasks with the objective to determine, whether the drawing operation can be
   done by the underlying graphics subsystem or by the software pisel driver.
   Tasks, which do need the software emulation will be signed with the flag
   EW_TASK_EMULATION */
#ifdef EW_NEED_DRIVER_TABLES 
  static void PreprocessTasks( XIssue* aIssue );
#endif


/* The following helper functions implement different strategies for the task
   execution. Depending on the registered driver/worker functions, the tasks
   will be executed by the real graphics hardware or emulated by the software
   pixel driver */
#ifdef EW_NEED_DRIVER_TABLES 
  static void DrawLine1     ( XSurface* aDst, XTask* aTask, int aFuncNo );
  static void FillRectangle1( XSurface* aDst, XTask* aTask, int aFuncNo );
  static void CopySurface1  ( XSurface* aDst, XTask* aTask, int aFuncNo );
  static void TileSurface1  ( XSurface* aDst, XTask* aTask, int aFuncNo );
  static void TileSurface2  ( XSurface* aDst, XTask* aTask, int aFuncNo );
  static void DrawText1     ( XSurface* aDst, XTask* aTask, int aFuncNo );

  #ifndef EW_DONT_USE_WARP_FUNCTIONS
    static void DrawText3   ( XSurface* aDst, XTask* aTask, int aFuncNo );
    static void WarpSurface1( XSurface* aDst, XTask* aTask,
                              const XWarpDriver* aDrivers,  int aFuncNo );
  #endif

  #ifndef EW_DONT_USE_PATH_FUNCTIONS
    static void FillPolygon1( XSurface* aDst, XTask* aTask, int aFuncNo );
  #endif

  #if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
    static void FillGradient1( XSurface* aDst, XTask* aTask, int aFuncNo );
  #endif

  #if !defined EW_DONT_USE_BLUR_FUNCTIONS || \
      !defined EW_DONT_USE_MASK_FUNCTIONS || \
      !defined EW_DONT_USE_TINT_FUNCTIONS
    static void Filter1     ( XSurface* aDst, XTask* aTask, int aFuncNo );
  #endif
#endif

static void DrawLine2     ( XSurface* aDst, XTask* aTask, int aFuncNo );
static void FillRectangle2( XSurface* aDst, XTask* aTask, int aFuncNo );
static void CopySurface2  ( XSurface* aDst, XTask* aTask, int aFuncNo );
static void TileSurface3  ( XSurface* aDst, XTask* aTask, int aFuncNo );
static void DrawText2     ( XSurface* aDst, XTask* aTask, int aFuncNo );

#ifndef EW_DONT_USE_WARP_FUNCTIONS
  static void DrawText4   ( XSurface* aDst, XTask* aTask, int aFuncNo );
  static void WarpSurface2( XSurface* aDst, XTask* aTask,
                            const XWarpWorker* aWorkers,  int aFuncNo );
#endif

#ifndef EW_DONT_USE_PATH_FUNCTIONS
  static void FillPolygon2( XSurface* aDst, XTask* aTask, int aFuncNo );
#endif

#if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
  static void FillGradient2( XSurface* aDst, XTask* aTask, int aFuncNo );
#endif

#if !defined EW_DONT_USE_MASK_FUNCTIONS || !defined EW_DONT_USE_TINT_FUNCTIONS
  static void Filter2     ( XSurface* aDst, XTask* aTask, int aFuncNo1,
                            int aFuncNo2 );
#endif

/* Target systems using CLUT (Index8 format of the frame buffer) are not able
   to perform blur operations. The color space is too smal for the gradients
   resulting from the blurs. */
#if !defined EW_DONT_USE_BLUR_FUNCTIONS
  static void Filter3     ( XSurface* aDst, XTask* aTask, int aFuncNo1,
                            int aFuncNo2, int aRadius );

  #if !defined EW_DONT_USE_MASK_FUNCTIONS || !defined EW_DONT_USE_TINT_FUNCTIONS
    static void Filter4   ( XSurface* aDst, XTask* aTask, int aFuncNo0,
                            int aFuncNo1, int aFuncNo2, int aFuncNo3,
                            int aFuncNo4, int aFuncNo5, int aRadius );
    static void Filter5   ( XSurface* aDst, XTask* aTask, int aFuncNo1,
                            int aFuncNo2, int aFuncNo3, int aFuncNo4,
                            int aFuncNo5, int aFilter6, int aRadius );
  #endif
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

#ifdef ABS
  #undef ABS
#endif
#define ABS( a ) (((a) < 0 )? (-(a)) : (a))


/* Access to the surface containing glyphs (for text output) */
extern XSurface* EwGlyphCacheSurface;

/* Debugging mode */
extern int EwPrintGfxTasks;


/* Currently used and locked surfaces as destination and source */
XSurface*    EwDstSurface  = 0;
XSurface*    EwSrcSurface  = 0;
XSurface*    EwMaskSurface = 0;
XSurfaceLock EwDstSurfaceLock;
XSurfaceLock EwSrcSurfaceLock;
XSurfaceLock EwMaskSurfaceLock;


/* The following helper functions lock the specified surfaces and return they
   pixel memory. */
static XSurfaceMemory* LockDstSurface ( XSurface* aSurface );
static XSurfaceMemory* LockSrcSurface ( XSurface* aSurface );
static XSurfaceMemory* LockMaskSurface( XSurface* aSurface );


/* The following variables stores user defined callback function to call for
   each executed drawing task - this is kind of monitoring. */
XTraceTasksProc EwTraceTasksProc = 0;
void*           EwTraceTasksArg1 = 0;
void*           EwTraceTasksArg2 = 0;


/* Performance counter for performance investigation and debugging only */
EW_PERF_COUNTER( EwGfxDrawLine,     Platform_Integration_API )
EW_PERF_COUNTER( EwGfxFill,         Platform_Integration_API )
EW_PERF_COUNTER( EwGfxCopy,         Platform_Integration_API )
EW_PERF_COUNTER( EwGfxTile,         Platform_Integration_API )
EW_PERF_COUNTER( EwGfxDraw,         Platform_Integration_API )
EW_PERF_COUNTER( EwGfxWarp,         Platform_Integration_API )
EW_PERF_COUNTER( EwGfxFilter,       Platform_Integration_API )
EW_PERF_COUNTER( EwGfxFillPolygon,  Platform_Integration_API )
EW_PERF_COUNTER( EwGfxFillGradient, Platform_Integration_API )


/*******************************************************************************
* FUNCTION:
*   EwGfxTasksInit
*
* DESCRIPTION:
*   The function EwGfxTasksInit() is called during the initialization of the
*   Graphics Engine. Its intention is to give this module a chance to initialize
*   its private variables etc..
*
* ARGUMENTS:
*   aArgs - User argument passed in the EwInitGraphicsEngine().
*
* RETURN VALUE:
*   If successful, returns != 0.
*
*******************************************************************************/
int EwGfxTasksInit( void* aArgs )
{
  EW_UNUSED_ARG( aArgs );

  /* Prepare performance counters */
  EwAddPerfCounter( EwGfxDrawLine     );
  EwAddPerfCounter( EwGfxFill         );
  EwAddPerfCounter( EwGfxCopy         );
  EwAddPerfCounter( EwGfxTile         );
  EwAddPerfCounter( EwGfxDraw         );
  EwAddPerfCounter( EwGfxWarp         );
  EwAddPerfCounter( EwGfxFilter       );
  EwAddPerfCounter( EwGfxFillPolygon  );
  EwAddPerfCounter( EwGfxFillGradient );

  return 1;
}


/*******************************************************************************
* FUNCTION:
*   EwReorderTasks
*
* DESCRIPTION:
*  The function EwReorderTasks() has the job to change the order of the drawing 
*  tasks with the objective to put together all the software emulated tasks.
*
* ARGUMENTS:
*   aIssue - Issue containing the tasks to change the order.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwReorderTasks( XIssue* aIssue )
{
  /* Omit the reordering if none of the drawing operations has been redirected
     to the low-level driver. */
  #ifdef EW_NEED_DRIVER_TABLES
    XTask* task1 = aIssue->Tasks;
    XTask* task2 = task1? task1->Next : 0;
    XTask* tmp;

    /* For each task, determine whether it will be executed by the underlying
       graphics subsystem or by the software pixel driver */
    PreprocessTasks( aIssue );

    /* Break the list in two separate lists: 'task1' and 'task2' with a gap
       between them */
    if ( task2 )
      task1->Next = 0;

    /* Traverse the list and reorder software emulated tasks - if possible */
    while ( task2 )
    {
      /* Detect sequences of alternating software emulated and 'real' hardware 
         tasks which do not interfere and promote the software tasks to the front
         of the screen -> try to group software tasks together */
      if (
           !( task1->Flags & EW_TASK_EMULATION ) && 
            ( task2->Flags & EW_TASK_EMULATION ) &&
            (
              ( task1->X1 >= task2->X2 ) || ( task1->Y1 >= task2->Y2 ) ||
              ( task2->X1 >= task1->X2 ) || ( task2->Y1 >= task1->Y2 )
            )
         )
      {
        /* Exchange the order of the both tasks - Note the case, when the first
           task of the list is affected by the operation */
        if ( task1->Next )
        {
          tmp         = task1->Next;
          task1->Next = task2->Next;
          task2->Next = task1;
          task1       = tmp;
        }
        else
        {
          tmp         = task2;
          task1->Next = task2;
          task2       = task2->Next;
          tmp->Next   = 0;
        }
      }

      /* Just continue with the next task pair without changing the order */
      else
      {
        tmp         = task2->Next;
        task2->Next = task1;
        task1       = task2;
        task2       = tmp;
      }
    }

    /* Note the change order of tasks in the issue */
    aIssue->Tasks = task1;
  #else
    EwReverseTasks( aIssue );
  #endif
}


/*******************************************************************************
* FUNCTION:
*   EwReverseTasks
*
* DESCRIPTION:
*  The function EwReverseTasks() has the job to reverse the order of all tasks
*  within the issue.
*
* ARGUMENTS:
*   aIssue - Issue containing the tasks to change the order.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwReverseTasks( XIssue* aIssue )
{
  XTask* task  = aIssue->Tasks;
  XTask* tasks = 0;

  /* Traverse the list and build a new task chain */
  while ( task )
  {
    XTask* tmp = task;

    task      = task->Next;
    tmp->Next = tasks;
    tasks     = tmp;
  }

  aIssue->Tasks = tasks;
}


/* Helper macro for the switch/case statement in the EwEliminateTasks() 
   function */
#define INTERSECTION_CASE( aMode, aX1, aX2, aY1, aY2, aNoOfTasks )             \
  case aMode :                                                                 \
    if ((( aX1 - aX2 ) < EW_ELIMINATE_MIN_EDGE ) ||                            \
        (( aY1 - aY2 ) < EW_ELIMINATE_MIN_EDGE ) ||                            \
        (                                                                      \
          aNoOfTasks &&                                                        \
          (( tasks = EwAllocTasks( aIssue, aNoOfTasks, task )) == 0 )          \
        ))                                                                     \
      break;


/*******************************************************************************
* FUNCTION:
*   EwEliminateTasks
*
* DESCRIPTION:
*  The function EwEliminateTasks() has the job to find and eliminate superfluous
*  drawing operations in the given issue.
*
* ARGUMENTS:
*   aIssue - Issue containing the tasks to eliminate.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwEliminateTasks( XIssue* aIssue )
{
  XTask* task    = aIssue->Tasks;
  XTask* prev    = 0;
  XTask* opqTask = 0;
  short  opqX1   = 0;
  short  opqX2   = 0;
  short  opqY1   = 0;
  short  opqY2   = 0;

  /* Process the tasks. Look for opaque tasks and eliminate other tasks, which
     are covered by the opaque areas */
  for ( ; task; prev = task, task = task->Next )
  {
    int    mode  = 0;
    XTask* tasks = 0;

    /* Look for full opaque tasks */
    if (
         !opqTask &&
         (( task->Flags & ( EW_TASK_ENTIRE_AREA | EW_TASK_ALPHABLEND )) == 
                            EW_TASK_ENTIRE_AREA ) &&
         (( task->X2 - task->X1 ) >= EW_ELIMINATE_MIN_EDGE ) &&
         (( task->Y2 - task->Y1 ) >= EW_ELIMINATE_MIN_EDGE )
       )
    {
      opqTask = task;
      opqX1   = task->X1;
      opqY1   = task->Y1;
      opqX2   = task->X2;
      opqY2   = task->Y2;

      /* Dont't eliminate the task by itself */
      continue;
    }

    /* Quick test, whether the current task is covered by an opaque task */
    if ( !opqTask || 
         ( task->X1 >= opqX2 ) || ( task->Y1 >= opqY2 ) ||
         ( task->X2 <= opqX1 ) || ( task->Y2 <= opqY1 ))
    {
      /* Restart the evaluation for the next following opaque task */
      if ( opqTask && !task->Next )
      {
        task    = opqTask;
        opqTask = 0;
      }

      continue;
    }

    /* Determine the kind of intersection between the current and the opaque
       task */
    if  ( task->X1 >= opqX1 ) mode |= 0x1;
    if  ( task->Y1 >= opqY1 ) mode |= 0x2;
    if  ( task->X2 <= opqX2 ) mode |= 0x4;
    if  ( task->Y2 <= opqY2 ) mode |= 0x8;

    /* Depending of the intersection mode - select the appropriate strategy
       to eliminate/optimize the current task */
    switch ( mode )
    {
      /* The covered area of the task lies in its middle */
      INTERSECTION_CASE( 0, opqX2, opqX1, opqY2, opqY1, 3 )
      {
        XTask* task2 = tasks;
        XTask* task3 = task2->Next;
        XTask* task4 = task3->Next;
    
        task->Y2  = opqY1;
        task2->Y1 = opqY2;
        task3->Y1 = opqY1; task3->Y2 = opqY2; task3->X2 = opqX1;
        task4->Y1 = opqY1; task4->Y2 = opqY2; task4->X1 = opqX2;
        task      = task2;
      }
      break;

      /* The covered area of the task intersects its left edge */
      INTERSECTION_CASE( 1, opqX2, task->X1, opqY2, opqY1, 2 )
      {
        XTask* task2 = tasks;
        XTask* task3 = task2->Next;
      
        task->X1  = opqX2;
        task2->X2 = opqX2; task2->Y2 = opqY1;
        task3->X2 = opqX2; task3->Y1 = opqY2;
        task      = task2;
      }
      break;

      /* The covered area of the task intersects its upper edge */
      INTERSECTION_CASE( 2, opqX2, opqX1, opqY2, task->Y1, 2 )
      {
        XTask* task2 = tasks;
        XTask* task3 = task2->Next;
    
        task->Y1  = opqY2;
        task2->X2 = opqX1; task2->Y2 = opqY2;
        task3->X1 = opqX2; task3->Y2 = opqY2;
        task      = task2;
      }
      break;

      /* The covered area of the task intersects its upper-left corner */
      INTERSECTION_CASE( 3, opqX2, task->X1, opqY2, task->Y1, 1 )
      {
        XTask* task2 = tasks;
      
        task->Y1  = opqY2;
        task2->Y2 = opqY2; task2->X1 = opqX2;
        task      = task2;
      }
      break;

      /* The covered area of the task intersects its right edge */
      INTERSECTION_CASE( 4, task->X2, opqX1, opqY2, opqY1, 2 )
      {
        XTask* task2 = tasks;
        XTask* task3 = task2->Next;

        task->X2  = opqX1;
        task2->X1 = opqX1; task2->Y2 = opqY1;
        task3->X1 = opqX1; task3->Y1 = opqY2;
        task      = task2;
      }
      break;

      /* The covered area of the task intersects its upper and bottom edges */
      INTERSECTION_CASE( 5, task->X2, task->X1, opqY2, opqY1, 1 )
      {
        XTask* task2 = tasks;

        task->Y2  = opqY1;
        task2->Y1 = opqY2;
        task      = task2;
      }
      break;

      /* The covered area of the task intersects its upper-right corner */
      INTERSECTION_CASE( 6, task->X2, opqX1, opqY2, task->Y1, 1 )
      {
        XTask* task2 = tasks;
      
        task->Y1  = opqY2;
        task2->Y2 = opqY2; task2->X2 = opqX1;
        task      = task2;
      } break;

      /* The covered area of the task intersects its upper half */
      case 7 :
      {
        task->Y1 = opqY2;
      } break;

      /* The covered area of the task intersects its bottom edge */
      INTERSECTION_CASE( 8, opqX2, opqX1, task->Y2, opqY1, 2 )
      {
        XTask* task2 = tasks;
        XTask* task3 = task2->Next;
    
        task->Y2  = opqY1;
        task2->X2 = opqX1; task2->Y1 = opqY1;
        task3->X1 = opqX2; task3->Y1 = opqY1;
        task      = task2;
      } break;
  
      /* The covered area of the task intersects its bottom-left corner */
      INTERSECTION_CASE( 9, opqX2, task->X1, task->Y2, opqY1, 1 )
      {
        XTask* task2 = tasks;
      
        task->Y2  = opqY1;
        task2->Y1 = opqY1; task2->X1 = opqX2;
        task      = task2;
      } break;
  
      /* The covered area of the task intersects its top and bottom edges */
      INTERSECTION_CASE( 10, opqX2, opqX1, task->Y2, task->Y1, 1 )
      {
        XTask* task2 = tasks;

        task->X2  = opqX1;
        task2->X1 = opqX2;
        task      = task2;
      } break;
  
      /* The covered area of the task intersects its left half */
      case 11 :
      {
        task->X1 = opqX2;
      } break;

      /* The covered area of the task intersects its bottom-right corner */
      INTERSECTION_CASE( 12, task->X2, opqX1, task->Y2, opqY1, 1 )
      {
        XTask* task2 = tasks;
      
        task->Y2  = opqY1;
        task2->Y1 = opqY1; task2->X2 = opqX1;
        task      = task2;
      } break;

      /* The covered area of the task intersects its lower half */
      case 13 :
      {
        task->Y2 = opqY1;
      } break;
  
      /* The covered area of the task intersects its right half */
      case 14 :
      {
        task->X2 = opqX1;
      } break;
  
      /* The covered area encloses the entire task - remove the task from the
         list */
      case 15 :
      {
        prev->Next = task->Next;
        task       = prev;
      } break;
    }

    /* Restart the evaluation for the next following opaque task */
    if ( !task->Next && opqTask )
    {
      task    = opqTask;
      opqTask = 0;
    }
  }
}


/*******************************************************************************
* FUNCTION:
*   EwExecuteTasks
*
* DESCRIPTION:
*  The function EwExecuteTasks() has the job to traverse the list of drawing
*  task and to invoke the appropriate driver functions for their execution.
*
* ARGUMENTS:
*   aIssue - Issue containing the tasks to execute.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwExecuteTasks( XIssue* aIssue )
{
  XTask* task = aIssue->Tasks;

  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
    {
      EwPrint( "EXECUTE TASKS for surface 0x%p\n", aIssue->Surface );
      EwPrint( "{\n" );
    }
  #endif

  /* Repeat until all tasks have been executed */
  for ( ; task; task = task->Next )
  {
    /* The drawing mode determines the appropriate drawing strategy */
    int funcNo = task->Flags & EW_TASK_MODE_MASK;

    /* What kind of operations should be done? */
    switch ( task->Token )
    {
      case EW_TASKID_DRAW_LINE :
      {
        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 8;
        #endif

        /* Eliminate unused code */
        #ifdef EW_NEED_DRIVER_TABLES
          if ( LineDrivers[ funcNo ])
            DrawLine1( aIssue->Surface, task, funcNo );
          else
        #endif
          DrawLine2( aIssue->Surface, task, funcNo );
      }
      break;

      case EW_TASKID_FILL_RECTANGLE :
      {
        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 8;
        #endif

        /* Eliminate unused code */
        #ifdef EW_NEED_DRIVER_TABLES
          if ( FillDrivers[ funcNo ])
            FillRectangle1( aIssue->Surface, task, funcNo );
          else
        #endif
          FillRectangle2( aIssue->Surface, task, funcNo );
      }
      break;

      case EW_TASKID_COPY_SURFACE :
      {
        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 32;
        #endif

        /* Involve the source surface format in the strategy selection */
        funcNo += ((XCopySurface*)task->Data)->Surface->Format * 8;

        /* Eliminate unused code */
        #ifdef EW_NEED_DRIVER_TABLES
          if ( CopyDrivers[ funcNo ])
            CopySurface1( aIssue->Surface, task, funcNo );
          else
        #endif
          CopySurface2( aIssue->Surface, task, funcNo );
      }
      break;

      case EW_TASKID_TILE_SURFACE :
      {
        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 32;
        #endif

        /* Involve the source surface format in the strategy selection */
        funcNo += ((XTileSurface*)task->Data)->Surface->Format * 8;

        /* If no tile driver available - try to use the copy driver */
        /* Eliminate unused code */
        #ifdef EW_NEED_DRIVER_TABLES
          if ( TileDrivers[ funcNo ])
            TileSurface1( aIssue->Surface, task, funcNo );
          else if ( CopyDrivers[ funcNo ])
            TileSurface2( aIssue->Surface, task, funcNo );
          else
        #endif
          TileSurface3( aIssue->Surface, task, funcNo );
      }
      break;

      case EW_TASKID_DRAW_TEXT :
      {
        XDrawText* data = (XDrawText*)task->Data;

        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
          {
            if ( data->Orientation )
              funcNo += 64;
            else
              funcNo += 32;
          }
        #endif

        /* Text without rotation */
        if ( !data->Orientation )
        {
          funcNo += EW_PIXEL_FORMAT_ALPHA8 * 8;

          /* Eliminate unused code */
          #ifdef EW_NEED_DRIVER_TABLES
            if ( CopyDrivers[ funcNo ])
              DrawText1( aIssue->Surface, task, funcNo );
            else
          #endif
            DrawText2( aIssue->Surface, task, funcNo );
        }

        /* Eliminate unused code */
        #ifndef EW_DONT_USE_WARP_FUNCTIONS
          /* Text with rotation */
          else
          {
            funcNo += EW_PIXEL_FORMAT_ALPHA8 * 16;

            /* Eliminate unused code */
            #ifdef EW_NEED_DRIVER_TABLES
              if ( WarpAffineDrivers[ funcNo ])
                DrawText3( aIssue->Surface, task, funcNo );
              else
            #endif
              DrawText4( aIssue->Surface, task, funcNo );
          }
          #endif
      }
      break;

      case EW_TASKID_WARP_PERSP_SURFACE :
      {
        /* Eliminate unused code */
        #ifndef EW_DONT_USE_WARP_FUNCTIONS
          /* If destination has the screen pixel format -> switch to the 
             corresponding set of drawing functions */
          #ifdef EW_USE_PIXEL_FORMAT_SCREEN
            if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
              funcNo += 64;
          #endif

          /* Involve the source surface format in the strategy selection */
          funcNo += ((XWarpSurface*)task->Data)->Surface->Format * 16;

          /* Eliminate unused code */
          #ifdef EW_NEED_DRIVER_TABLES
            if ( WarpPerspDrivers[ funcNo ])
              WarpSurface1( aIssue->Surface, task, WarpPerspDrivers, funcNo );
            else
          #endif
            WarpSurface2( aIssue->Surface, task, WarpPerspWorkers, funcNo );
        #endif
      }
      break;

      case EW_TASKID_WARP_AFFINE_SURFACE :
      {
        /* Eliminate unused code */
        #ifndef EW_DONT_USE_WARP_FUNCTIONS
          /* If destination has the screen pixel format -> switch to the 
             corresponding set of drawing functions */
          #ifdef EW_USE_PIXEL_FORMAT_SCREEN
            if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
              funcNo += 64;
          #endif

          /* Involve the source surface format in the strategy selection */
          funcNo += ((XWarpSurface*)task->Data)->Surface->Format * 16;

          /* Eliminate unused code */
          #ifdef EW_NEED_DRIVER_TABLES
            if ( WarpAffineDrivers[ funcNo ])
              WarpSurface1( aIssue->Surface, task, WarpAffineDrivers, funcNo );
            else
          #endif
            WarpSurface2( aIssue->Surface, task, WarpAffineWorkers, funcNo );
        #endif
      }
      break;

      case EW_TASKID_WARP_SCALE_SURFACE :
      {
        /* Eliminate unused code */
        #ifndef EW_DONT_USE_WARP_FUNCTIONS
          /* If destination has the screen pixel format -> switch to the 
             corresponding set of drawing functions */
          #ifdef EW_USE_PIXEL_FORMAT_SCREEN
            if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
              funcNo += 64;
          #endif

          /* Involve the source surface format in the strategy selection */
          funcNo += ((XWarpSurface*)task->Data)->Surface->Format * 16;

          /* Eliminate unused code */
          #ifdef EW_NEED_DRIVER_TABLES
            if ( WarpScaleDrivers[ funcNo ])
              WarpSurface1( aIssue->Surface, task, WarpScaleDrivers,  funcNo );
            else
          #endif
            WarpSurface2( aIssue->Surface, task, WarpAffineWorkers, funcNo );
        #endif
      }
      break;

      case EW_TASKID_FILTER_SURFACE :
      {
        /* Eliminate unused code */
        #if !defined EW_DONT_USE_BLUR_FUNCTIONS || \
            !defined EW_DONT_USE_MASK_FUNCTIONS || \
            !defined EW_DONT_USE_TINT_FUNCTIONS

          XFilterSurface* data       = (XFilterSurface*)task->Data;
          int             blur       = ( data->BlurRadius   > 0 )? 1 : 0;
          int             mask       = ( data->MaskSurface != 0 )? 2 : 0;
          int             tint       = 0;
          int             blurRadius = data->BlurRadius;

          /* When considering a real (Gauss) blur, the pixel near the borders
             of the blur radius don't contribute to the total blur effect. The
             weights for affected pixel are very very small. When performing
             the box blur our intention is to get similar results as good as
             possible. For this purpose the pixel near the borders of the blur
             radius are ignored. It is as if we would calculate with a smaller
             radius. The reduction correlates to the original radius. */
          if ( blurRadius > 1 )
            blurRadius = ( blurRadius * 7 ) / 8;

          /* Which tunt mode is used? */
          if      ( data->Mode == EW_TINT_MODE_TINT_BY_OPACITY   ) tint = 4;
          else if ( data->Mode == EW_TINT_MODE_TINT_BY_LUMINANCE ) tint = 8;

          /* Filter operations follow a different numbering convention regardless
             of the task mode. */
          funcNo = blur + mask + tint;

          /* If destination has the screen pixel format -> switch to the 
             corresponding set of drawing functions */
          #ifdef EW_USE_PIXEL_FORMAT_SCREEN
            if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
              funcNo += 48;
          #endif

          /* Involve the source surface format in the strategy selection */
          funcNo += data->SrcSurface->Format * 12;

          /* Eliminate unused code */
          #ifdef EW_NEED_DRIVER_TABLES
            if ( FilterDrivers[ funcNo ])
              Filter1( aIssue->Surface, task, funcNo );
            else
          #endif

          /* Mask or/and tint filter without any blur operation */ 
          if ( !blur )
          {
            #if !defined EW_DONT_USE_MASK_FUNCTIONS || \
                !defined EW_DONT_USE_TINT_FUNCTIONS
              Filter2( aIssue->Surface, task, funcNo >> 1, ( funcNo >> 1 ) & ~1 );
            #endif
          }

          #if !defined EW_DONT_USE_BLUR_FUNCTIONS
            /* ... or blur filter without mask/tint */
            else if ( !mask && !tint )
            {
              int funcNo1 = data->SrcSurface->Format;
              int funcNo2 = 0;

              /* If destination has the screen pixel format -> switch to the 
                 corresponding set of drawing functions */
              #ifdef EW_USE_PIXEL_FORMAT_SCREEN
                if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
                  funcNo2 += 5;
              #endif

              Filter3( aIssue->Surface, task, funcNo1, funcNo2, blurRadius );
            }

            #if !defined EW_DONT_USE_MASK_FUNCTIONS || \
                !defined EW_DONT_USE_TINT_FUNCTIONS

              /* Combination of blur and mask/tint filter with the mask being applied
                 before the blur operation */
              else if ( data->MaskBeforeBlur )
              {
                int funcNo1 = (( mask + tint ) >> 1 ) + data->SrcSurface->Format * 6;
                int funcNo3 = 0;
                int funcNo4 = data->SrcSurface->Format;
                int funcNo5 = 0;

                /* If destination has the screen pixel format -> switch to the 
                   corresponding set of drawing functions */
                #ifdef EW_USE_PIXEL_FORMAT_SCREEN
                  if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
                    funcNo5 += 5;
                #endif

                Filter4( aIssue->Surface, task, data->SrcSurface->Format, funcNo1,
                         funcNo1 & ~1, funcNo3, funcNo4, funcNo5, blurRadius );
              }

              /* Combination of blur and mask/tint filter with the mask being applied
                 after the blur operation or even without any mask - just tint */
              else
              {
                int funcNo1 = data->SrcSurface->Format;
                int funcNo2 = 0;
                int funcNo3 = 0;
                int funcNo4 = ( mask + tint ) >> 1;
                int funcNo6 = 0;

                /* Special case of the blur filter applied on an ALPHA8 surface. Here
                   we can optimize and use ALPHA8 as intermediate surface */
                if ( data->SrcSurface->Format == EW_PIXEL_FORMAT_ALPHA8 )
                {
                  funcNo1  = 4;
                  funcNo2  = 4;
                  funcNo4 += 12;
                }

                /* If destination has the screen pixel format -> switch to the 
                   corresponding set of drawing functions */
                #ifdef EW_USE_PIXEL_FORMAT_SCREEN
                  if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
                  {
                    funcNo3 += 5;
                    funcNo4 += 24;
                    funcNo6 += 1;
                  }
                #endif

                Filter5( aIssue->Surface, task, funcNo1, funcNo2, funcNo3, funcNo4,
                         funcNo4 & ~1, funcNo6, blurRadius );
              }
            #endif
          #endif
        #endif
      }
      break;

      case EW_TASKID_FILL_POLYGON :
      {
        /* Eliminate unused code */
        #ifndef EW_DONT_USE_PATH_FUNCTIONS
          /* If destination has the screen pixel format -> switch to the 
             corresponding set of drawing functions */
          #ifdef EW_USE_PIXEL_FORMAT_SCREEN
            if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
              funcNo += 32;
          #endif

          /* Eliminate unused code */
          #ifdef EW_NEED_DRIVER_TABLES
            if ( PolygonDrivers[ funcNo ])
              FillPolygon1( aIssue->Surface, task, funcNo );
            else
          #endif
            FillPolygon2( aIssue->Surface, task, funcNo );
        #endif
      }
      break;

      case EW_TASKID_FILL_GRADIENT :
      {
        /* Eliminate unused code */
        #if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS
          #ifdef EW_NEED_DRIVER_TABLES
            XFillGradient* data      = (XFillGradient*)task->Data;
            int            drvFuncNo;

            /* Number identifying the corresponding drawing function */
            drvFuncNo = ( data->IsRadial? 4 : 0 ) +
                        (( funcNo & EW_TASK_HIGH_QUALITY )? 2 : 0 ) +
                        (( funcNo & EW_TASK_ALPHABLEND   )? 1 : 0 );
          #endif

          /* If destination has the screen pixel format -> switch to the 
             corresponding set of drawing functions */
          #ifdef EW_USE_PIXEL_FORMAT_SCREEN
            if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            {
              #ifdef EW_NEED_DRIVER_TABLES
                drvFuncNo += 8;
              #endif
              funcNo      += 32;
            }
          #endif

          /* Eliminate unused code */
          #ifdef EW_NEED_DRIVER_TABLES
            if ( GradientDrivers[ drvFuncNo ])
              FillGradient1( aIssue->Surface, task, drvFuncNo );
            else
          #endif
            FillGradient2( aIssue->Surface, task, funcNo );
        #endif
      }
      break;
    }

    /* Task execution trace callback function installed? */
    if ( EwTraceTasksProc )
      EwTraceTasksProc( aIssue->Surface, task, EwTraceTasksArg1, 
        EwTraceTasksArg2 );
  }

  /* Before exit - release any previously locked surfaces */
  LockDstSurface ( 0 );
  LockSrcSurface ( 0 );
  LockMaskSurface( 0 );

  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "}\n" );
  #endif
}


/*******************************************************************************
* FUNCTION:
*   EwCompleteTasks
*
* DESCRIPTION:
*  The function EwCompleteTasks() has the job to release resources used by the
*  tasks contained within the given issue.
*
* ARGUMENTS:
*   aIssue - Issue containing the tasks to complete.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwCompleteTasks( XIssue* aIssue )
{
  XTask* task     = (XTask*)aIssue->UpperHeap;
  XTask* upperEnd = (XTask*)aIssue->UpperEnd;

  /* Repeat until all tasks have been evaluated and the affected resources
     fred */
  while ( task < upperEnd )
  {
    /* What kind of task is it? */
    switch ( task->Token )
    {
      /* Copy task can involve a source surface */
      case EW_TASKID_COPY_SURFACE :
      {
        XCopySurface* data = (XCopySurface*)task->Data;

        /* If still not released - release the involved surface */
        if ( data->Surface )
        {
          data->Surface->Used--;
          data->Surface = 0;
        }
      }
      break;

      /* Tile task can involve a source surface */
      case EW_TASKID_TILE_SURFACE :
      {
        XTileSurface* data = (XTileSurface*)task->Data;

        /* If still not released - release the involved surface */
        if ( data->Surface )
        {
          data->Surface->Used--;
          data->Surface = 0;
        }
      }
      break;

      /* Draw text task can involve a list of glyphs */
      case EW_TASKID_DRAW_TEXT :
      {
        XDrawText* data  = (XDrawText*)task->Data;
        char*      slot  = (char*)( data + 1 ) + ( sizeof( int ) * 2 );
        int        count = data->Glyphs;

        /* If still not released - release the involved glyphs */
        while ( count-- > 0 )
        {
          (*(XGlyph**)slot)->Used--;
          slot += sizeof( XGlyph* ) + ( sizeof( int ) * 2 );
        }

        data->Glyphs = 0;
      }
      break;

      /* Warp task can involve a source surface */
      case EW_TASKID_WARP_PERSP_SURFACE  :
      case EW_TASKID_WARP_AFFINE_SURFACE :
      case EW_TASKID_WARP_SCALE_SURFACE  :
      {
        XWarpSurface* data = (XWarpSurface*)task->Data;

        /* If still not released - release the involved surface */
        if ( data->Surface )
        {
          data->Surface->Used--;
          data->Surface = 0;
        }
      }
      break;

      /* Filter task can involve a source and a mask surface */
      case EW_TASKID_FILTER_SURFACE :
      {
        XFilterSurface* data = (XFilterSurface*)task->Data;

        /* If still not released - release the involved surface */
        if ( data->SrcSurface )
        {
          data->SrcSurface->Used--;
          data->SrcSurface = 0;
        }

        /* If still not released - release the involved surface */
        if ( data->MaskSurface )
        {
          data->MaskSurface->Used--;
          data->MaskSurface = 0;
        }
      }
      break;
    }

    /* Continue with the next task */
    task++;
  }
}


/*******************************************************************************
* FUNCTION:
*   EwCountTasks
*
* DESCRIPTION:
*  The function EwCountTasks() exists for statistic purpose only. The function
*  evaluates the tasks, counts them and calculates the amount of pixel to copy
*  and to blend.
*
* ARGUMENTS:
*   aIssue     - Issue containing the tasks to cout.
*   aNoOfTasks - Pointer to variable, where the resulting number of tasks is
*     returned.
*   aCopyArea  - Pointer to variable, where the resulting pixel copy area is
*     returned.
*   aBlendArea - Pointer to variable, where the resulting pixel blend area is
*     returned.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwCountTasks( XIssue* aIssue, int* aNoOfTasks, int* aCopyArea,
  int* aBlendArea )
{
  XTask* task      = aIssue->Tasks;
  int    noOfTasks = 0;
  int    copyArea  = 0;
  int    blendArea = 0;

  for ( ; task; task = task->Next )
  {
    noOfTasks++;

    if ( task->Flags & EW_TASK_ALPHABLEND )
      blendArea += ( task->X2 - task->X1 ) * ( task->Y2 - task->Y1 );
    else
      copyArea  += ( task->X2 - task->X1 ) * ( task->Y2 - task->Y1 );
  }

  *aNoOfTasks = noOfTasks;
  *aCopyArea  = copyArea;
  *aBlendArea = blendArea;
} 


/*******************************************************************************
* FUNCTION:
*   EwTraceTasks
*
* DESCRIPTION:
*  The function EwTraceTasks() provides a mechanism to monitor task execution.
*  EwTraceTasks() registers a user defined callback function aProc to call when
*  a task is executed.
*
*  The registered function is called for each executed task until EwTraceTasks()
*  is called again with 0 (zero) as aProc paramater.
*
* ARGUMENTS:
*   aProc     - User defined callback function to call for each executed task.
*   aUserArg1 - User argument to pass additionally to the called user function.
*   aUserArg2 - User argument to pass additionally to the called user function.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwTraceTasks( XTraceTasksProc aProc, void* aUserArg1, void* aUserArg2 )
{
  EwTraceTasksProc = aProc;
  EwTraceTasksArg1 = aUserArg1;
  EwTraceTasksArg2 = aUserArg2;
}


/* Eliminate not needed code */
#ifdef EW_NEED_DRIVER_TABLES 

/* The following helper function has the job to traverse the list of drawing
   tasks with the objective to determine, whether the drawing operation can be
   done by the underlying graphics subsystem or by the software pixel driver.
   Tasks, which do need the software emulation will be signed with the flag
   EW_TASK_EMULATION */
static void PreprocessTasks( XIssue* aIssue )
{
  XTask* task = aIssue->Tasks;

  /* Repeat until all tasks have been evaluated and for every task a driver or
     a worker function has been determined */
  for ( ; task; task = task->Next )
  {
    /* The drawing mode determines the appropriate drawing strategy */
    int funcNo  = task->Flags & EW_TASK_MODE_MASK;
    int emulate = 0;

    /* What kind of task is it? */
    switch ( task->Token )
    {
      case EW_TASKID_DRAW_LINE :
      {
        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 8;
        #endif

        emulate = !LineDrivers[ funcNo ];
      }
      break;

      case EW_TASKID_FILL_RECTANGLE :
      {
        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 8;
        #endif

        emulate = !FillDrivers[ funcNo ];
      }
      break;

      case EW_TASKID_COPY_SURFACE :
      {
        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 32;
        #endif

        /* Involve the source surface format in the strategy selection */
        funcNo += ((XCopySurface*)task->Data)->Surface->Format * 8;
        emulate = !CopyDrivers[ funcNo ];
      }
      break;
      
      case EW_TASKID_TILE_SURFACE :
      {
        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 32;
        #endif

        /* Involve the source surface format in the strategy selection */
        funcNo += ((XTileSurface*)task->Data)->Surface->Format * 8;
        emulate = !TileDrivers[ funcNo ] && !CopyDrivers[ funcNo ];
      }
      break;
      
      case EW_TASKID_DRAW_TEXT :
      {
        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
          {
            if (((XDrawText*)task->Data)->Orientation )
              funcNo += 64;
            else
              funcNo += 32;
          }
        #endif

        if (((XDrawText*)task->Data)->Orientation )
          emulate = !WarpAffineDrivers[ funcNo + ( EW_PIXEL_FORMAT_ALPHA8 * 16 )];
        else
          emulate = !CopyDrivers[ funcNo + ( EW_PIXEL_FORMAT_ALPHA8 * 8 )];
      }
      break;

      case EW_TASKID_WARP_PERSP_SURFACE :
      {
        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 64;
        #endif

        /* Involve the source surface format in the strategy selection */
        funcNo += ((XWarpSurface*)task->Data)->Surface->Format * 16;
        emulate = !WarpPerspDrivers[ funcNo ];
      }
      break;

      case EW_TASKID_WARP_AFFINE_SURFACE :
      {
        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 64;
        #endif

        /* Involve the source surface format in the strategy selection */
        funcNo += ((XWarpSurface*)task->Data)->Surface->Format * 16;
        emulate = !WarpAffineDrivers[ funcNo ];
      }
      break;

      case EW_TASKID_WARP_SCALE_SURFACE :
      {
        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 64;
        #endif

        /* Involve the source surface format in the strategy selection */
        funcNo += ((XWarpSurface*)task->Data)->Surface->Format * 16;
        emulate = !WarpScaleDrivers[ funcNo ];
      }
      break;

      case EW_TASKID_FILTER_SURFACE :
      {
        XFilterSurface* data   = (XFilterSurface*)task->Data;
        int             blur   = ( data->BlurRadius   > 0 )? 1 : 0;
        int             mask   = ( data->MaskSurface != 0 )? 2 : 0;
        int             tint   = 0;

        /* Which tunt mode is used? */
        if      ( data->Mode == EW_TINT_MODE_TINT_BY_OPACITY   ) tint = 4;
        else if ( data->Mode == EW_TINT_MODE_TINT_BY_LUMINANCE ) tint = 8;

        /* Filter operations follow a different numbering convention regardless
           of the task mode. */
        funcNo = blur + mask + tint;

        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 48;
        #endif

        /* Involve the source surface format in the strategy selection */
        funcNo += data->SrcSurface->Format * 12;
        emulate = !FilterDrivers[ funcNo ];
      }
      break;
      
      case EW_TASKID_FILL_POLYGON :
      {
        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 32;
        #endif

        emulate = !PolygonDrivers[ funcNo ];
      }

      case EW_TASKID_FILL_GRADIENT :
      {
        XFillGradient* data = (XFillGradient*)task->Data;

        /* Number identifying the corresponding drawing function */
        funcNo = ( data->IsRadial? 4 : 0 ) +
                 (( funcNo & EW_TASK_HIGH_QUALITY )? 2 : 0 ) +
                 (( funcNo & EW_TASK_ALPHABLEND   )? 1 : 0 );

        /* If destination has the screen pixel format -> switch to the 
           corresponding set of drawing functions */
        #ifdef EW_USE_PIXEL_FORMAT_SCREEN
          if ( aIssue->Surface->Format == EW_PIXEL_FORMAT_SCREEN )
            funcNo += 8;
        #endif

        emulate = !GradientDrivers[ funcNo ];
      }
      break;
    }

    /* Mark the task for software emulated execution */
    task->Flags |= emulate? EW_TASK_EMULATION : 0;
  }
}

#endif /* EW_NEED_DRIVER_TABLES */


/* The following helper function locks the specified surface and returns its
   pixel memory. If there was already a surface locked - the function unlocks
   the old surface first. */
static XSurfaceMemory* LockDstSurface( XSurface* aSurface )
{
  /* Try to lock an already locked surface? Then nothing to do ... */
  if ( aSurface && ( aSurface == EwDstSurface ))
    return &EwDstSurfaceLock.Memory;

  /* ... otherwise release the previously locked surface */
  if ( EwDstSurface )
  {
    EwUnlockSurface( EwDstSurface, &EwDstSurfaceLock );
    EwDstSurface = 0;
  }

  /* Now lock the new surface */
  if ( aSurface && EwLockSurface( aSurface, 0, 0, aSurface->Width, 
         aSurface->Height, 0, 256, EW_LOCK_PIXEL_READ_WRITE | EW_LOCK_DONT_WAIT,
         &EwDstSurfaceLock ))
    EwDstSurface = aSurface;

  return EwDstSurface? &EwDstSurfaceLock.Memory : 0;
}


/* The following helper function locks the specified surface and returns its
   pixel memory. If there was already a surface locked - the function unlocks
   the old surface first. */
static XSurfaceMemory* LockSrcSurface( XSurface* aSurface )
{
  /* Try to lock an already locked surface? Then nothing to do ... */
  if ( aSurface && ( aSurface == EwSrcSurface ))
    return &EwSrcSurfaceLock.Memory;

  /* ... otherwise release the previously locked surface */
  if ( EwSrcSurface )
  {
    EwUnlockSurface( EwSrcSurface, &EwSrcSurfaceLock );
    EwSrcSurface = 0;
  }

  /* Now lock the new surface */
  if ( aSurface && EwLockSurface( aSurface, 0, 0, aSurface->Width, 
         aSurface->Height, 0, 256, EW_LOCK_PIXEL_READ | EW_LOCK_CLUT_READ |
         EW_LOCK_DONT_WAIT, &EwSrcSurfaceLock ))
    EwSrcSurface = aSurface;

  return EwSrcSurface? &EwSrcSurfaceLock.Memory : 0;
}


/* The following helper function locks the specified surface and returns its
   pixel memory. If there was already a surface locked - the function unlocks
   the old surface first. */
static XSurfaceMemory* LockMaskSurface( XSurface* aSurface )
{
  /* Try to lock an already locked surface? Then nothing to do ... */
  if ( aSurface && ( aSurface == EwMaskSurface ))
    return &EwMaskSurfaceLock.Memory;

  /* ... otherwise release the previously locked surface */
  if ( EwMaskSurface )
  {
    EwUnlockSurface( EwMaskSurface, &EwMaskSurfaceLock );
    EwMaskSurface = 0;
  }

  /* Now lock the new surface */
  if ( aSurface && EwLockSurface( aSurface, 0, 0, aSurface->Width, 
         aSurface->Height, 0, 256, EW_LOCK_PIXEL_READ | EW_LOCK_DONT_WAIT,
         &EwMaskSurfaceLock ))
    EwMaskSurface = aSurface;

  return EwMaskSurface? &EwMaskSurfaceLock.Memory : 0;
}


/* Eliminate not needed code */
#ifdef EW_NEED_DRIVER_TABLES 

/* This helper function maps the 'draw line' task to the driver function of the
   underlying graphics subsystem. */
static void DrawLine1( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XDrawLine* data = (XDrawLine*)aTask->Data;
  int        clpW = aTask->X2 - aTask->X1;
  int        clpH = aTask->Y2 - aTask->Y1;

  /* On 64-Bit target convert the 32-bit color list to a list of 64-bit color
     values. It is a workaround to not break the low-level driver interface in
     existing Platform Packages */
  #if defined __LP64__ || defined _LP64
    unsigned long  colors[2] = { data->Colors[0], data->Colors[1]};
  #else
    unsigned long* colors    = (unsigned long*)data->Colors;
  #endif

  /* First release any existing surface locks */
  LockDstSurface ( 0 );
  LockSrcSurface ( 0 );
  LockMaskSurface( 0 );

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "DrawLine(( %d, %d )-( %d, %d )=( %d x %d ), %s )\n", 
               aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, clpH,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  EwStartPerfCounter( EwGfxDrawLine );

  /* Invoke the external driver function to the underlying graphics subsystem.
     Please note, depending on how the real surface content is orientend the
     coordinates need to be converted respectively. */
  #if EW_SURFACE_ROTATION == 0
    LineDrivers[ aFuncNo ]( aDst->Handle,
      data->DstX1, data->DstY1,
      data->DstX2, data->DstY2,
      aTask->X1,   aTask->Y1,
      clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, colors );
  #endif

  #if EW_SURFACE_ROTATION == 90
    LineDrivers[ aFuncNo ]( aDst->Handle,
      aDst->Height - data->DstY1 - 1, data->DstX1,
      aDst->Height - data->DstY2 - 1, data->DstX2,
      aDst->Height - aTask->Y2,       aTask->X1,
      clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, colors );
  #endif

  #if EW_SURFACE_ROTATION == 180
    LineDrivers[ aFuncNo ]( aDst->Handle,
      aDst->Width - data->DstX1 - 1, aDst->Height - data->DstY1 - 1,
      aDst->Width - data->DstX2 - 1, aDst->Height - data->DstY2 - 1,
      aDst->Width - aTask->X2,       aDst->Height - aTask->Y2,
      clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, colors );
  #endif

  #if EW_SURFACE_ROTATION == 270
    LineDrivers[ aFuncNo ]( aDst->Handle,
      data->DstY1, aDst->Width - data->DstX1 - 1,
      data->DstY2, aDst->Width - data->DstX2 - 1,
      aTask->Y1,   aDst->Width - aTask->X2,
      clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, colors );
  #endif

  EwStopPerfCounter( EwGfxDrawLine );
}

#endif /* EW_NEED_DRIVER_TABLES */


/* This helper function maps the 'draw line' task to the software emulated pixel
   driver. */
static void DrawLine2( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XDrawLine*      data = (XDrawLine*)aTask->Data;
  XSurfaceMemory* dst  = LockDstSurface( aDst );
  int             w    = ABS( data->DstX2 - data->DstX1 ) + 1;
  int             h    = ABS( data->DstY2 - data->DstY1 ) + 1;
  int             len  = MAX( w, h );
  XGradient       gradient;
  unsigned int    colors[4];

  /* No direct access to the surface memory */
  if ( !dst )
    return;

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "DrawLine(( %d, %d )-( %d, %d )=( %d x %d ), %s ) SW\n", 
               aTask->X1, aTask->Y1, aTask->X2, aTask->Y2,
               aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  /* The line provides only two colors */
  colors[0] = data->Colors[0]; colors[1] = data->Colors[0];
  colors[3] = data->Colors[1]; colors[2] = data->Colors[1];

  /* Prepare the colors for the following operation */
  EwInitColorGradient( len, len, colors, &gradient );

  EwStartPerfCounter( EwGfxDrawLine );

  /* Run the software pixel driver. Please note, depending on how the real
     surface content is orientend the coordinates need to be converted 
     respectively. */
  #if EW_SURFACE_ROTATION == 0
    EwEmulateLine( dst,
      data->DstX1, data->DstY1,
      data->DstX2, data->DstY2,
      aTask->X1,   aTask->Y1,
      aTask->X2,   aTask->Y2,
      &gradient, LineWorkers[ aFuncNo ]);
  #endif

  #if EW_SURFACE_ROTATION == 90
    EwEmulateLine( dst,
      aDst->Height - data->DstY1 - 1, data->DstX1,
      aDst->Height - data->DstY2 - 1, data->DstX2,
      aDst->Height - aTask->Y2,       aTask->X1,
      aDst->Height - aTask->Y1,       aTask->X2,
      &gradient, LineWorkers[ aFuncNo ]);
  #endif

  #if EW_SURFACE_ROTATION == 180
    EwEmulateLine( dst,
      aDst->Width - data->DstX1 - 1, aDst->Height - data->DstY1 - 1,
      aDst->Width - data->DstX2 - 1, aDst->Height - data->DstY2 - 1,
      aDst->Width - aTask->X2,       aDst->Height - aTask->Y2,
      aDst->Width - aTask->X1,       aDst->Height - aTask->Y1,
      &gradient, LineWorkers[ aFuncNo ]);
  #endif

  #if EW_SURFACE_ROTATION == 270
    EwEmulateLine( dst,
      data->DstY1, aDst->Width - data->DstX1 - 1,
      data->DstY2, aDst->Width - data->DstX2 - 1,
      aTask->Y1,   aDst->Width - aTask->X2,
      aTask->Y2,   aDst->Width - aTask->X1,
      &gradient, LineWorkers[ aFuncNo ]);
  #endif

  EwStopPerfCounter( EwGfxDrawLine );
}


/* Eliminate not needed code */
#ifdef EW_NEED_DRIVER_TABLES 

/* This helper function maps the 'fill rectangle' task to the driver function
   of the underlying graphics subsystem. */
static void FillRectangle1( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XFillRectangle* data   = (XFillRectangle*)aTask->Data;
  int             clpW   = aTask->X2 - aTask->X1;
  int             clpH   = aTask->Y2 - aTask->Y1;
  unsigned int*   colors = data->Colors;

  #ifndef EW_DONT_USE_GRADIENTS
    unsigned int  interColors[4];
  #endif

  /* First release any existing surface locks */
  LockDstSurface ( 0 );
  LockSrcSurface ( 0 );
  LockMaskSurface( 0 );

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "FillRectangle(( %d, %d )-( %d, %d )=( %d x %d ), %s )\n", 
               aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, clpH,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  /* Filling a clipped area of a gradient? Then interpolate the color values
     for the clipped edges before passing the call to the driver */
  #ifndef EW_DONT_USE_GRADIENTS
    if (
         ( aTask->Flags & EW_TASK_GRADIENT ) && 
         (
           ( aTask->X1 > data->DstX1 ) || ( aTask->Y1 > data->DstY1 ) ||
           ( aTask->X2 < data->DstX2 ) || ( aTask->Y2 < data->DstY2 )
         )
       )
    {
      int       x1 = aTask->X1 - data->DstX1;
      int       y1 = aTask->Y1 - data->DstY1;
      int       x2 = aTask->X2 - data->DstX1;
      int       y2 = aTask->Y2 - data->DstY1;
      XGradient gradient;

      /* Prepare the colors for the following operation */
      EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
        colors, &gradient );

      interColors[0] = EwGetColorFromGradient( &gradient, x1, y1 );
      interColors[1] = EwGetColorFromGradient( &gradient, x2, y1 );
      interColors[2] = EwGetColorFromGradient( &gradient, x2, y2 );
      interColors[3] = EwGetColorFromGradient( &gradient, x1, y2 );
      colors         = interColors;
    }
  
    /* If the filling operation with gradient should be performed and the surface
       content is rotated then the order of colors in the 'colors' array need
       an adaptation accordingly to the surface rotation. To do this the colors
       need to be transfered in an intermediate color array. This step can be
       avoided, however, when the intermediate array is already initialized in
       the preceding step. */
    #if EW_SURFACE_ROTATION != 0
      if (( aTask->Flags & EW_TASK_GRADIENT ) && ( colors == data->Colors ))
      {
        interColors[0] = colors[0]; interColors[1] = colors[1];
        interColors[2] = colors[2]; interColors[3] = colors[3];
        colors         = interColors;
      }
    #endif
  #endif

  EwStartPerfCounter( EwGfxFill );

  /* Invoke the external driver function to the underlying graphics subsystem.
     Please note, depending on how the real surface content is orientend the
     coordinates and the order of colors need to be adapted respectively. */
  #if EW_SURFACE_ROTATION == 0
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      FillDrivers[ aFuncNo ]( aDst->Handle,
        aTask->X1,  aTask->Y1, 
        clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, tmp );
    }
    #else
      FillDrivers[ aFuncNo ]( aDst->Handle,
        aTask->X1,  aTask->Y1, 
        clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 90
    if ( colors != data->Colors )
    {
      unsigned int tmp = colors[0];
      colors[0] = colors[3]; colors[3] = colors[2];
      colors[2] = colors[1]; colors[1] = tmp;
    }    

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      FillDrivers[ aFuncNo ]( aDst->Handle,
        aDst->Height - aTask->Y2, aTask->X1,
        clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, tmp );
    }
    #else
      FillDrivers[ aFuncNo ]( aDst->Handle,
        aDst->Height - aTask->Y2, aTask->X1,
        clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 180
    if ( colors != data->Colors )
    {
      unsigned int tmp1 = colors[0];
      unsigned int tmp2 = colors[1];
      colors[0] = colors[2]; colors[2] = tmp1;
      colors[1] = colors[3]; colors[3] = tmp2;
    }    

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      FillDrivers[ aFuncNo ]( aDst->Handle,
        aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
        clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, tmp );
    }
    #else
      FillDrivers[ aFuncNo ]( aDst->Handle,
        aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
        clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 270
    if ( colors != data->Colors )
    {
      unsigned int tmp = colors[0];
      colors[0] = colors[1]; colors[1] = colors[2];
      colors[2] = colors[3]; colors[3] = tmp;
    }    

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      FillDrivers[ aFuncNo ]( aDst->Handle,
        aTask->Y1, aDst->Width - aTask->X2,
        clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, tmp );
    }
    #else
      FillDrivers[ aFuncNo ]( aDst->Handle,
        aTask->Y1, aDst->Width - aTask->X2,
        clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
    #endif
  #endif

  EwStopPerfCounter( EwGfxFill );
}

#endif /* EW_NEED_DRIVER_TABLES */


/* This helper function maps the 'fill rectangle' task to the software emulated
   pixel driver. */
static void FillRectangle2( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XFillRectangle*  data = (XFillRectangle*)aTask->Data;
  int              clpW = aTask->X2 - aTask->X1;
  int              clpH = aTask->Y2 - aTask->Y1;
  XSurfaceMemory*  dst  = LockDstSurface( aDst );
  XGradient        gradient;

  #if EW_SURFACE_ROTATION != 0
    unsigned int  interColors[4];
    unsigned int* colors = data->Colors;
  #endif

  /* No direct access to the surface memory */
  if ( !dst )
    return;

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "FillRectangle(( %d, %d )-( %d, %d )=( %d x %d ), %s ) SW\n",
               aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, clpH,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  /* In case of vertical/horizontal only gradients, the rows/columns can be drawn
     with solid colors - no in-row interpolation is necessary. Select the faster
     (solid) version of the worker function. Note the special cases of rotated
     surface content. */
  #if ( EW_SURFACE_ROTATION == 0  ) || ( EW_SURFACE_ROTATION == 180 )
    if ( IS_LINEAR_GRADIENT( aTask->Flags ) && !IS_HORZ_GRADIENT( data->Colors ))
      aFuncNo += EW_TASK_SOLID - EW_TASK_LINEAR_GRADIENT;
  #endif

  #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
    if ( IS_LINEAR_GRADIENT( aTask->Flags ) && !IS_VERT_GRADIENT( data->Colors ))
      aFuncNo += EW_TASK_SOLID - EW_TASK_LINEAR_GRADIENT;
  #endif

  EwStartPerfCounter( EwGfxFill );

  /* Run the software pixel driver. Please note, depending on how the real
     surface content is orientend the coordinates and the order of colors need
     to be adapted respectively. */
  #if EW_SURFACE_ROTATION == 0
    EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
      data->Colors, &gradient );

    EwEmulateFill( dst,
      aTask->X1,  aTask->Y1,
      clpW, clpH, &gradient, 
      aTask->X1 - data->DstX1, aTask->Y1 - data->DstY1,
      FillWorkers[ aFuncNo ]);
  #endif

  #if EW_SURFACE_ROTATION == 90
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[3]; interColors[1] = colors[0];
      interColors[2] = colors[1]; interColors[3] = colors[2];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstY2 - data->DstY1, data->DstX2 - data->DstX1,
      colors, &gradient );

    EwEmulateFill( dst, 
      aDst->Height - aTask->Y2, aTask->X1,
      clpH, clpW, &gradient,
      -aTask->Y2 + data->DstY2, aTask->X1 - data->DstX1,
      FillWorkers[ aFuncNo ]);
  #endif

  #if EW_SURFACE_ROTATION == 180
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[2]; interColors[1] = colors[3];
      interColors[2] = colors[0]; interColors[3] = colors[1];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
      colors, &gradient );

    EwEmulateFill( dst, 
      aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
      clpW, clpH, &gradient,
      -aTask->X2 + data->DstX2, -aTask->Y2 + data->DstY2,
      FillWorkers[ aFuncNo ]);
  #endif

  #if EW_SURFACE_ROTATION == 270
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[1]; interColors[1] = colors[2];
      interColors[2] = colors[3]; interColors[3] = colors[0];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstY2 - data->DstY1, data->DstX2 - data->DstX1,
      colors, &gradient );

    EwEmulateFill( dst, 
      aTask->Y1,  aDst->Width - aTask->X2,
      clpH, clpW, &gradient,
      aTask->Y1 - data->DstY1, -aTask->X2 + data->DstX2,
      FillWorkers[ aFuncNo ]);
  #endif

  EwStopPerfCounter( EwGfxFill );
}


/* Eliminate not needed code */
#ifdef EW_NEED_DRIVER_TABLES 

/* This helper function maps the 'copy surface' task to the driver function of
   the underlying graphics subsystem. */
static void CopySurface1( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XCopySurface*  data   = (XCopySurface*)aTask->Data;
  int            clpW   = aTask->X2 - aTask->X1;
  int            clpH   = aTask->Y2 - aTask->Y1;
  unsigned int*  colors = data->Colors;

  #ifndef EW_DONT_USE_GRADIENTS
    unsigned int interColors[4];
  #endif

  /* First release any existing surface locks */
  LockDstSurface ( 0 );
  LockSrcSurface ( 0 );
  LockMaskSurface( 0 );

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "CopySurface( 0x%p, ( %d, %d )-( %d, %d )=( %d x %d ), %s )\n",
               data->Surface, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, 
               clpH, (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  /* Copying a clipped area of a gradient? Then interpolate the color values
     for the clipped edges before passing the call to the driver */
  #ifndef EW_DONT_USE_GRADIENTS
    if (
         ( aTask->Flags & EW_TASK_GRADIENT ) && 
         (
           ( aTask->X1 > data->DstX1 ) || ( aTask->Y1 > data->DstY1 ) ||
           ( aTask->X2 < data->DstX2 ) || ( aTask->Y2 < data->DstY2 )
         )
       )
    {
      int       x1 = aTask->X1 - data->DstX1;
      int       y1 = aTask->Y1 - data->DstY1;
      int       x2 = aTask->X2 - data->DstX1;
      int       y2 = aTask->Y2 - data->DstY1;
      XGradient gradient;

      /* Prepare the colors for the following operation */
      EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
        colors, &gradient );

      interColors[0] = EwGetColorFromGradient( &gradient, x1, y1 );
      interColors[1] = EwGetColorFromGradient( &gradient, x2, y1 );
      interColors[2] = EwGetColorFromGradient( &gradient, x2, y2 );
      interColors[3] = EwGetColorFromGradient( &gradient, x1, y2 );
      colors         = interColors;
    }
  
    /* If the copying surfaces with gradient should be performed and the surface
       content is rotated then the order of colors in the 'colors' array need
       an adaptation accordingly to the surface rotation. To do this the colors
       need to be transfered in an intermediate color array. This step can be
       avoided, however, when the intermediate array is already initialized in
       the preceding step. */
    #if EW_SURFACE_ROTATION != 0
      if (( aTask->Flags & EW_TASK_GRADIENT ) && ( colors == data->Colors ))
      {
        interColors[0] = colors[0]; interColors[1] = colors[1];
        interColors[2] = colors[2]; interColors[3] = colors[3];
        colors         = interColors;
      }
    #endif
  #endif

  EwStartPerfCounter( EwGfxCopy );

  /* Invoke the external driver function to the underlying graphics subsystem.
     Please note, depending on how the real surface content is orientend the
     coordinates and the order of colors need to be adapted respectively. */
  #if EW_SURFACE_ROTATION == 0
    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aTask->X1, aTask->Y1,
        data->SrcX + aTask->X1 - data->DstX1,
        data->SrcY + aTask->Y1 - data->DstY1,
        clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, tmp );
    }
    #else
      CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aTask->X1, aTask->Y1,
        data->SrcX + aTask->X1 - data->DstX1,
        data->SrcY + aTask->Y1 - data->DstY1,
        clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 90
    if ( colors != data->Colors )
    {
      unsigned int tmp = colors[0];
      colors[0] = colors[3]; colors[3] = colors[2];
      colors[2] = colors[1]; colors[1] = tmp;
    }    

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aDst->Height - aTask->Y2, aTask->X1,
        data->Surface->Height - data->SrcY - clpH - aTask->Y1 + data->DstY1,
        data->SrcX + aTask->X1 - data->DstX1,
        clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, tmp );
    }
    #else
      CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aDst->Height - aTask->Y2, aTask->X1,
        data->Surface->Height - data->SrcY - clpH - aTask->Y1 + data->DstY1,
        data->SrcX + aTask->X1 - data->DstX1,
        clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 180
    if ( colors != data->Colors )
    {
      unsigned int tmp1 = colors[0];
      unsigned int tmp2 = colors[1];
      colors[0] = colors[2]; colors[2] = tmp1;
      colors[1] = colors[3]; colors[3] = tmp2;
    }    

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
        data->Surface->Width  - data->SrcX - clpW - aTask->X1 + data->DstX1,
        data->Surface->Height - data->SrcY - clpH - aTask->Y1 + data->DstY1,
        clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, tmp );
    }
    #else
      CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
        data->Surface->Width  - data->SrcX - clpW - aTask->X1 + data->DstX1,
        data->Surface->Height - data->SrcY - clpH - aTask->Y1 + data->DstY1,
        clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 270
    if ( colors != data->Colors )
    {
      unsigned int tmp = colors[0];
      colors[0] = colors[1]; colors[1] = colors[2];
      colors[2] = colors[3]; colors[3] = tmp;
    }    

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aTask->Y1, aDst->Width - aTask->X2,
        data->SrcY + aTask->Y1 - data->DstY1,
        data->Surface->Width - data->SrcX - clpW - aTask->X1 + data->DstX1,
        clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, tmp );
    }
    #else
      CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aTask->Y1, aDst->Width - aTask->X2,
        data->SrcY + aTask->Y1 - data->DstY1,
        data->Surface->Width - data->SrcX - clpW - aTask->X1 + data->DstX1,
        clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
    #endif
  #endif

  EwStopPerfCounter( EwGfxCopy );
}

#endif /* EW_NEED_DRIVER_TABLES */


/* This helper function maps the 'copy surface' task to the software emulated
   pixel driver. */
static void CopySurface2( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XCopySurface*    data = (XCopySurface*)aTask->Data;
  int              clpW = aTask->X2 - aTask->X1;
  int              clpH = aTask->Y2 - aTask->Y1;
  XSurfaceMemory*  dst  = LockDstSurface( aDst );
  XSurfaceMemory*  src  = LockSrcSurface( data->Surface );
  XGradient        gradient;

  #if EW_SURFACE_ROTATION != 0
    unsigned int  interColors[4];
    unsigned int* colors = data->Colors;
  #endif

  /* No direct access to the surface memory */
  if ( !dst || !src )
    return;

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "CopySurface( 0x%p, ( %d, %d )-( %d, %d )=( %d x %d ), %s ) SW\n", 
               data->Surface, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, 
               clpH, (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  /* In case of vertical/horizontal only gradients, the rows/columns can be drawn
     with solid colors - no in-row interpolation is necessary. Select the faster
     (solid) version of the worker function. Note the special cases of rotated
     surface content. */
  #if ( EW_SURFACE_ROTATION == 0  ) || ( EW_SURFACE_ROTATION == 180 )
    if ( IS_LINEAR_GRADIENT( aTask->Flags ) && !IS_HORZ_GRADIENT( data->Colors ))
      aFuncNo += EW_TASK_SOLID - EW_TASK_LINEAR_GRADIENT;
  #endif

  #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
    if ( IS_LINEAR_GRADIENT( aTask->Flags ) && !IS_VERT_GRADIENT( data->Colors ))
      aFuncNo += EW_TASK_SOLID - EW_TASK_LINEAR_GRADIENT;
  #endif

  EwStartPerfCounter( EwGfxCopy );

  /* Run the software pixel driver. Please note, depending on how the real
     surface content is orientend the coordinates and the order of colors need
     to be adapted respectively. */
  #if EW_SURFACE_ROTATION == 0
    EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
      data->Colors, &gradient );

    EwEmulateCopy( dst, src,
      aTask->X1, aTask->Y1,
      clpW, clpH,
      data->SrcX + aTask->X1 - data->DstX1,
      data->SrcY + aTask->Y1 - data->DstY1,
      &gradient, 
      aTask->X1 - data->DstX1, aTask->Y1 - data->DstY1,
      CopyWorkers[ aFuncNo ]); 
  #endif

  #if EW_SURFACE_ROTATION == 90
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[3]; interColors[1] = colors[0];
      interColors[2] = colors[1]; interColors[3] = colors[2];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstY2 - data->DstY1, data->DstX2 - data->DstX1,
      colors, &gradient );

    EwEmulateCopy( dst, src,
      aDst->Height - aTask->Y2, aTask->X1,
      clpH, clpW,
      data->Surface->Height - data->SrcY - clpH - aTask->Y1 + data->DstY1,
      data->SrcX + aTask->X1 - data->DstX1,
      &gradient, 
      -aTask->Y2 + data->DstY2, aTask->X1 - data->DstX1,
      CopyWorkers[ aFuncNo ]); 
  #endif

  #if EW_SURFACE_ROTATION == 180
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[2]; interColors[1] = colors[3];
      interColors[2] = colors[0]; interColors[3] = colors[1];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
      colors, &gradient );

    EwEmulateCopy( dst, src,
      aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
      clpW, clpH,
      data->Surface->Width  - data->SrcX - clpW - aTask->X1 + data->DstX1,
      data->Surface->Height - data->SrcY - clpH - aTask->Y1 + data->DstY1,
      &gradient, 
      -aTask->X2 + data->DstX2, -aTask->Y2 + data->DstY2,
      CopyWorkers[ aFuncNo ]); 
  #endif

  #if EW_SURFACE_ROTATION == 270
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[1]; interColors[1] = colors[2];
      interColors[2] = colors[3]; interColors[3] = colors[0];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstY2 - data->DstY1, data->DstX2 - data->DstX1,
      colors, &gradient );

    EwEmulateCopy( dst, src,
      aTask->Y1, aDst->Width - aTask->X2,
      clpH, clpW,
      data->SrcY + aTask->Y1 - data->DstY1,
      data->Surface->Width - data->SrcX - clpW - aTask->X1 + data->DstX1,
      &gradient, 
      aTask->Y1 - data->DstY1, -aTask->X2 + data->DstX2,
      CopyWorkers[ aFuncNo ]); 
  #endif

  EwStopPerfCounter( EwGfxCopy );
}


/* Eliminate not needed code */
#ifdef EW_NEED_DRIVER_TABLES

/* This helper function maps the 'tile surface' task to the corresponding driver
   function of the underlying graphics subsystem. */
static void TileSurface1( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XTileSurface*  data   = (XTileSurface*)aTask->Data;
  int            clpW   = aTask->X2 - aTask->X1;
  int            clpH   = aTask->Y2 - aTask->Y1;
  int            srcW   = data->SrcX2 - data->SrcX1;
  int            srcH   = data->SrcY2 - data->SrcY1;
  unsigned int*  colors = data->Colors;

  #ifndef EW_DONT_USE_GRADIENTS
    unsigned int interColors[4];
  #endif

  /* First release any existing surface locks */
  LockDstSurface ( 0 );
  LockSrcSurface ( 0 );
  LockMaskSurface( 0 );

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "TileSurface( 0x%p, ( %d, %d )-( %d, %d )=( %d x %d ), %s )\n", 
               data->Surface, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW,
               clpH, (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  /* Copying a clipped area of a gradient? Then interpolate the color values
     for the clipped edges before passing the call to the driver */
  #ifndef EW_DONT_USE_GRADIENTS
    if (
         ( aTask->Flags & EW_TASK_GRADIENT ) && 
         (
           ( aTask->X1 > data->DstX1 ) || ( aTask->Y1 > data->DstY1 ) ||
           ( aTask->X2 < data->DstX2 ) || ( aTask->Y2 < data->DstY2 )
         )
       )
    {
      int       x1 = aTask->X1 - data->DstX1;
      int       y1 = aTask->Y1 - data->DstY1;
      int       x2 = aTask->X2 - data->DstX1;
      int       y2 = aTask->Y2 - data->DstY1;
      XGradient gradient;

      /* Prepare the colors for the following operation */
      EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
        colors, &gradient );

      interColors[0] = EwGetColorFromGradient( &gradient, x1, y1 );
      interColors[1] = EwGetColorFromGradient( &gradient, x2, y1 );
      interColors[2] = EwGetColorFromGradient( &gradient, x2, y2 );
      interColors[3] = EwGetColorFromGradient( &gradient, x1, y2 );
      colors         = interColors;
    }

    /* If the copying surfaces with gradient should be performed and the surface
       content is rotated then the order of colors in the 'colors' array need
       an adaptation accordingly to the surface rotation. To do this the colors
       need to be transfered in an intermediate color array. This step can be
       avoided, however, when the intermediate array is already initialized in
       the preceding step. */
    #if EW_SURFACE_ROTATION != 0
      if (( aTask->Flags & EW_TASK_GRADIENT ) && ( colors == data->Colors ))
      {
        interColors[0] = colors[0]; interColors[1] = colors[1];
        interColors[2] = colors[2]; interColors[3] = colors[3];
        colors         = interColors;
      }
    #endif
  #endif

  EwStartPerfCounter( EwGfxTile );

  /* Invoke the external driver function to the underlying graphics subsystem.
     Please note, depending on how the real surface content is orientend the
     coordinates and the order of colors need to be adapted respectively. */
  #if EW_SURFACE_ROTATION == 0
    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      TileDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aTask->X1, aTask->Y1,
        clpW, clpH,
        data->SrcX1, data->SrcY1,
        srcW, srcH,
        ( aTask->X1 - data->DstX1 + data->OfsX ) % srcW,
        ( aTask->Y1 - data->DstY1 + data->OfsY ) % srcH,
        aTask->Flags & EW_TASK_ALPHABLEND, tmp );
    }
    #else
      TileDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aTask->X1, aTask->Y1,
        clpW, clpH,
        data->SrcX1, data->SrcY1,
        srcW, srcH,
        ( aTask->X1 - data->DstX1 + data->OfsX ) % srcW,
        ( aTask->Y1 - data->DstY1 + data->OfsY ) % srcH,
        aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
   #endif
  #endif

  #if EW_SURFACE_ROTATION == 90
    if ( colors != data->Colors )
    {
      unsigned int tmp = colors[0];
      colors[0] = colors[3]; colors[3] = colors[2];
      colors[2] = colors[1]; colors[1] = tmp;
    }    

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      TileDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aDst->Height - aTask->Y2, aTask->X1,
        clpH, clpW,
        data->Surface->Height - data->SrcY2, data->SrcX1,
        srcH, srcW,
        ( srcH - (( aTask->Y2 - data->DstY1 + data->OfsY ) % srcH )) % srcH,
        ( aTask->X1 - data->DstX1 + data->OfsX ) % srcW,
        aTask->Flags & EW_TASK_ALPHABLEND, tmp );
    }
    #else
      TileDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aDst->Height - aTask->Y2, aTask->X1,
        clpH, clpW,
        data->Surface->Height - data->SrcY2, data->SrcX1,
        srcH, srcW,
        ( srcH - (( aTask->Y2 - data->DstY1 + data->OfsY ) % srcH )) % srcH,
        ( aTask->X1 - data->DstX1 + data->OfsX ) % srcW,
        aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 180
    if ( colors != data->Colors )
    {
      unsigned int tmp1 = colors[0];
      unsigned int tmp2 = colors[1];
      colors[0] = colors[2]; colors[2] = tmp1;
      colors[1] = colors[3]; colors[3] = tmp2;
    }    

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      TileDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
        clpW, clpH,
        data->Surface->Width - data->SrcX2, data->Surface->Height - data->SrcY2,
        srcW, srcH,
        ( srcW - (( aTask->X2 - data->DstX1 + data->OfsX ) % srcW )) % srcW,
        ( srcH - (( aTask->Y2 - data->DstY1 + data->OfsY ) % srcH )) % srcH,
        aTask->Flags & EW_TASK_ALPHABLEND, tmp );
    }
    #else
      TileDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
        clpW, clpH,
        data->Surface->Width - data->SrcX2, data->Surface->Height - data->SrcY2,
        srcW, srcH,
        ( srcW - (( aTask->X2 - data->DstX1 + data->OfsX ) % srcW )) % srcW,
        ( srcH - (( aTask->Y2 - data->DstY1 + data->OfsY ) % srcH )) % srcH,
        aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 270
    if ( colors != data->Colors )
    {
      unsigned int tmp = colors[0];
      colors[0] = colors[1]; colors[1] = colors[2];
      colors[2] = colors[3]; colors[3] = tmp;
    }    

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      TileDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aTask->Y1, aDst->Width - aTask->X2,
        clpH, clpW,
        data->SrcY1,  data->Surface->Width - data->SrcX2,
        srcH, srcW,
        ( aTask->Y1 - data->DstY1 + data->OfsY ) % srcH,
        ( srcW - (( aTask->X2 - data->DstX1 + data->OfsX ) % srcW )) % srcW,
        aTask->Flags & EW_TASK_ALPHABLEND, tmp );
    }
    #else
      TileDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        aTask->Y1, aDst->Width - aTask->X2,
        clpH, clpW,
        data->SrcY1,  data->Surface->Width - data->SrcX2,
        srcH, srcW,
        ( aTask->Y1 - data->DstY1 + data->OfsY ) % srcH,
        ( srcW - (( aTask->X2 - data->DstX1 + data->OfsX ) % srcW )) % srcW,
        aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
    #endif
  #endif

  EwStopPerfCounter( EwGfxTile );
}


/* This helper function maps the 'tile surface' task to the 'copy surface'
   driver function of the underlying graphics subsystem. */
static void TileSurface2( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XTileSurface*   data = (XTileSurface*)aTask->Data;
  int             srcW = data->SrcX2 - data->SrcX1;
  int             srcH = data->SrcY2 - data->SrcY1;
  int             dstY = aTask->Y1;
  XGradient       gradient;
  unsigned int    colors[4];

  /* First release any existing surface locks */
  LockDstSurface ( 0 );
  LockSrcSurface ( 0 );
  LockMaskSurface( 0 );

  /* Assume, there is no gradient to apply */
  colors[0] = data->Colors[0]; colors[1] = data->Colors[1];
  colors[3] = data->Colors[3]; colors[2] = data->Colors[2];

  /* Prepare the opacities for the following operation */
  if ( aTask->Flags & EW_TASK_GRADIENT )
    EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - 
      data->DstY1, colors, &gradient );

  /* Loop row-wise */
  while ( dstY < aTask->Y2 )
  {
    int dstX = aTask->X1;
    int srcY = data->SrcY1 + (( dstY - data->DstY1 + data->OfsY ) % srcH );
    int h    = MIN( aTask->Y2 - dstY, data->SrcY2 - srcY );

    /* Loop column-wise */
    while ( dstX < aTask->X2 )
    {
      int srcX = data->SrcX1 + (( dstX - data->DstX1 + data->OfsX ) % srcW );
      int w    = MIN( aTask->X2 - dstX, data->SrcX2 - srcX );

      /* Interpolate the color values if color gradient has been applied */
      #ifndef EW_DONT_USE_GRADIENTS
        if ( aTask->Flags & EW_TASK_GRADIENT )
        {
         int x1 = dstX - data->DstX1;
         int y1 = dstY - data->DstY1;
         int x2 = x1 + w;
         int y2 = y1 + h;

          #if EW_SURFACE_ROTATION == 0
            colors[0] = EwGetColorFromGradient( &gradient, x1, y1 );
            colors[1] = EwGetColorFromGradient( &gradient, x2, y1 );
            colors[2] = EwGetColorFromGradient( &gradient, x2, y2 );
            colors[3] = EwGetColorFromGradient( &gradient, x1, y2 );
          #endif

          #if EW_SURFACE_ROTATION == 90
            colors[0] = EwGetColorFromGradient( &gradient, x1, y2 );
            colors[1] = EwGetColorFromGradient( &gradient, x1, y1 );
            colors[2] = EwGetColorFromGradient( &gradient, x2, y1 );
            colors[3] = EwGetColorFromGradient( &gradient, x2, y2 );
          #endif

          #if EW_SURFACE_ROTATION == 180
            colors[0] = EwGetColorFromGradient( &gradient, x2, y2 );
            colors[1] = EwGetColorFromGradient( &gradient, x1, y2 );
            colors[2] = EwGetColorFromGradient( &gradient, x1, y1 );
            colors[3] = EwGetColorFromGradient( &gradient, x2, y1 );
          #endif

          #if EW_SURFACE_ROTATION == 270
            colors[0] = EwGetColorFromGradient( &gradient, x2, y1 );
            colors[1] = EwGetColorFromGradient( &gradient, x2, y2 );
            colors[2] = EwGetColorFromGradient( &gradient, x1, y2 );
            colors[3] = EwGetColorFromGradient( &gradient, x1, y1 );
          #endif
        }
      #endif

      /* Track the drawing operations */
      #ifdef EW_SUPPORT_GFX_TASK_TRACING
        if ( EwPrintGfxTasks )
          EwPrint( "CopySurface( 0x%p, ( %d, %d )-( %d, %d )=( %d x %d ), %s )\n",
                   data->Surface, dstX, dstY, dstX + w, dstY + h,
                   aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
                   (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
      #endif

      EwStartPerfCounter( EwGfxCopy );

      /* Invoke the external driver function to the underlying graphics subsystem.
         Please note, depending on how the real surface content is orientend the
         coordinates need to be adapted respectively. */
      #if EW_SURFACE_ROTATION == 0
        /* On 64-bit target convert the 32-bit color list to 64-bit colors */
        #if defined __LP64__ || defined _LP64
        {
          unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

          CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
            dstX, dstY,
            srcX, srcY,
            w, h, aTask->Flags & EW_TASK_ALPHABLEND, tmp );
        }
        #else
          CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
            dstX, dstY,
            srcX, srcY,
            w, h, aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
        #endif
      #endif

      #if EW_SURFACE_ROTATION == 90
        /* On 64-bit target convert the 32-bit color list to 64-bit colors */
        #if defined __LP64__ || defined _LP64
        {
          unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

          CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
            aDst->Height - dstY - h, dstX,
            data->Surface->Height - srcY - h, srcX,
            h, w, aTask->Flags & EW_TASK_ALPHABLEND, tmp );
        }
        #else
          CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
            aDst->Height - dstY - h, dstX,
            data->Surface->Height - srcY - h, srcX,
            h, w, aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
        #endif
      #endif

      #if EW_SURFACE_ROTATION == 180
        /* On 64-bit target convert the 32-bit color list to 64-bit colors */
        #if defined __LP64__ || defined _LP64
        {
          unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

          CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
            aDst->Width - dstX - w, aDst->Height - dstY - h,
            data->Surface->Width - srcX - w, data->Surface->Height - srcY - h,
            w, h, aTask->Flags & EW_TASK_ALPHABLEND, tmp );
        }
        #else
          CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
            aDst->Width - dstX - w, aDst->Height - dstY - h,
            data->Surface->Width - srcX - w, data->Surface->Height - srcY - h,
            w, h, aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
        #endif
      #endif

      #if EW_SURFACE_ROTATION == 270
        /* On 64-bit target convert the 32-bit color list to 64-bit colors */
        #if defined __LP64__ || defined _LP64
        {
          unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

          CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
            dstY, aDst->Width - dstX - w,
            srcY, data->Surface->Width - srcX - w,
            h, w, aTask->Flags & EW_TASK_ALPHABLEND, tmp );
        }
        #else
          CopyDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
            dstY, aDst->Width - dstX - w,
            srcY, data->Surface->Width - srcX - w,
            h, w, aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
        #endif
      #endif

      EwStopPerfCounter( EwGfxCopy );
      dstX += w;
    }

    dstY += h;
  }
}

#endif /* EW_NEED_DRIVER_TABLES */


/* This helper function maps the 'tile surface' task to the software emulated
   pixel driver. */
static void TileSurface3( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XTileSurface*    data = (XTileSurface*)aTask->Data;
  int              srcW = data->SrcX2 - data->SrcX1;
  int              srcH = data->SrcY2 - data->SrcY1;
  int              dstY = aTask->Y1;
  XSurfaceMemory*  dst  = LockDstSurface( aDst );
  XSurfaceMemory*  src  = LockSrcSurface( data->Surface );
  XGradient        gradient;

  #if EW_SURFACE_ROTATION != 0
    unsigned int  interColors[4];
    unsigned int* colors = data->Colors;
  #endif

  /* No direct access to the surface memory */
  if ( !dst || !src )
    return;

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "TileSurface( 0x%p, ( %d, %d )-( %d, %d )=( %d x %d ), %s ) SW\n",
               data->Surface, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2,
               aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  /* In case of vertical/horizontal only gradients, the rows/columns can be drawn
     with solid colors - no in-row interpolation is necessary. Select the faster
     (solid) version of the worker function. Note the special cases of rotated
     surface content. */
  #if ( EW_SURFACE_ROTATION == 0  ) || ( EW_SURFACE_ROTATION == 180 )
    if ( IS_LINEAR_GRADIENT( aTask->Flags ) && !IS_HORZ_GRADIENT( data->Colors ))
      aFuncNo += EW_TASK_SOLID - EW_TASK_LINEAR_GRADIENT;
  #endif

  #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
    if ( IS_LINEAR_GRADIENT( aTask->Flags ) && !IS_VERT_GRADIENT( data->Colors ))
      aFuncNo += EW_TASK_SOLID - EW_TASK_LINEAR_GRADIENT;
  #endif

  #if EW_SURFACE_ROTATION == 0
    EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
      data->Colors, &gradient );
  #endif

  #if EW_SURFACE_ROTATION == 90
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[3]; interColors[1] = colors[0];
      interColors[2] = colors[1]; interColors[3] = colors[2];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstY2 - data->DstY1, data->DstX2 - data->DstX1,
      colors, &gradient );
  #endif

  #if EW_SURFACE_ROTATION == 180
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[2]; interColors[1] = colors[3];
      interColors[2] = colors[0]; interColors[3] = colors[1];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
      colors, &gradient );
  #endif

  #if EW_SURFACE_ROTATION == 270
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[1]; interColors[1] = colors[2];
      interColors[2] = colors[3]; interColors[3] = colors[0];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstY2 - data->DstY1, data->DstX2 - data->DstX1,
      colors, &gradient );
  #endif

  /* Loop row-wise */
  while ( dstY < aTask->Y2 )
  {
    int dstX = aTask->X1;
    int srcY = data->SrcY1 + (( dstY - data->DstY1 + data->OfsY ) % srcH );
    int h    = MIN( aTask->Y2 - dstY, data->SrcY2 - srcY );

    /* Loop column-wise */
    while ( dstX < aTask->X2 )
    {
      int srcX = data->SrcX1 + (( dstX - data->DstX1 + data->OfsX ) % srcW );
      int w    = MIN( aTask->X2 - dstX, data->SrcX2 - srcX ); 

      EwStartPerfCounter( EwGfxCopy );

      /* Run the software pixel driver. Please note, depending on how the real
         surface content is orientend the coordinates and the order of colors need
         to be adapted respectively. */
      #if EW_SURFACE_ROTATION == 0
        EwEmulateCopy( dst, src,
          dstX, dstY,
          w, h,
          srcX, srcY, 
          &gradient, 
          dstX - data->DstX1, dstY - data->DstY1,
          CopyWorkers[ aFuncNo ]);
      #endif

      #if EW_SURFACE_ROTATION == 90
        EwEmulateCopy( dst, src,
          aDst->Height - dstY - h, dstX,
          h, w,
          data->Surface->Height - srcY - h, srcX, 
          &gradient, 
          -dstY - h + data->DstY2, dstX - data->DstX1,
          CopyWorkers[ aFuncNo ]);
      #endif

      #if EW_SURFACE_ROTATION == 180
        EwEmulateCopy( dst, src,
          aDst->Width - dstX - w, aDst->Height - dstY - h,
          w, h,
          data->Surface->Width - srcX - w, data->Surface->Height - srcY - h,
          &gradient, 
          -dstX - w + data->DstX2, -dstY - h + data->DstY2,
          CopyWorkers[ aFuncNo ]);
      #endif

      #if EW_SURFACE_ROTATION == 270
        EwEmulateCopy( dst, src,
          dstY, aDst->Width - dstX - w,
          h, w,
          srcY, data->Surface->Width - srcX - w,
          &gradient, 
          dstY - data->DstY1, -dstX - w + data->DstX2,
          CopyWorkers[ aFuncNo ]);
      #endif

      EwStopPerfCounter( EwGfxCopy );
      dstX += w;
    }

    dstY += h;
  }
}


/* Eliminate not needed code */
#ifdef EW_NEED_DRIVER_TABLES

/* This helper function maps the 'draw text' task to the driver function of
   the underlying graphics subsystem. */
static void DrawText1( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XDrawText*   data    = (XDrawText*)aTask->Data;
  char*        slot    = (char*)( data + 1 );
  char*        last    = slot + data->Glyphs * (( sizeof( int ) * 2 ) + 
                                                  sizeof( void* ));
  int          ofsX    = data->DstX1 + data->OfsX;
  int          ofsY    = data->DstY1 + data->OfsY;
  int          x1      = aTask->X1;
  int          y1      = aTask->Y1;
  int          x2      = aTask->X2;
  int          y2      = aTask->Y2;
  XGradient    gradient;
  unsigned int colors[4];
  int          noOfGlyphs = 0;

  /* First release any existing surface locks */
  LockDstSurface ( 0 );
  LockSrcSurface ( 0 );
  LockMaskSurface( 0 );

  /* Assume, there is no gradient to apply */
  colors[0] = data->Colors[0]; colors[1] = data->Colors[1];
  colors[3] = data->Colors[3]; colors[2] = data->Colors[2];

  /* Prepare the opacities for the following operation */
  if ( aTask->Flags & EW_TASK_GRADIENT )
    EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - 
      data->DstY1, colors, &gradient );

  /* Process the serie of text glyphs */
  for ( ; slot < last; slot += ( sizeof( int ) * 2 ) + sizeof( XGlyph* ))
  {
    int     posX  = ((int*)slot)[0];
    int     posY  = ((int*)slot)[1];
    XGlyph* glyph = *(XGlyph**)((int*)slot + 2 );
    int     dstX1 = MAX( ofsX + posX, x1 );
    int     dstY1 = MAX( ofsY + posY, y1 );
    int     dstX2 = MIN( ofsX + posX + glyph->Width,   x2 );
    int     dstY2 = MIN( ofsY + posY + glyph->Height,  y2 );
    int     srcX  = glyph->CacheX + dstX1 - ( ofsX + posX );
    int     srcY  = glyph->CacheY + dstY1 - ( ofsY + posY );

    /* Take in account the additional one-pixel wide border around the glyph */
    #ifdef EW_BORDER_AROUND_GLYPHS
      srcX += 1;
      srcY += 1; 
    #endif

    /* Any visible parts of the glyph after the clipping? Then run the pixel
       driver */
    if (( dstX2 > dstX1 ) && ( dstY2 > dstY1 ))
    {
      /* Interpolate the color values if color gradient has been applied */
      #ifndef EW_DONT_USE_GRADIENTS
        if ( aTask->Flags & EW_TASK_GRADIENT )
        {
          int x1 = dstX1 - data->DstX1;
          int y1 = dstY1 - data->DstY1;
          int x2 = dstX2 - data->DstX1;
          int y2 = dstY2 - data->DstY1;

          #if EW_SURFACE_ROTATION == 0
            colors[0] = EwGetColorFromGradient( &gradient, x1, y1 );
            colors[1] = EwGetColorFromGradient( &gradient, x2, y1 );
            colors[2] = EwGetColorFromGradient( &gradient, x2, y2 );
            colors[3] = EwGetColorFromGradient( &gradient, x1, y2 );
          #endif

          #if EW_SURFACE_ROTATION == 90
            colors[0] = EwGetColorFromGradient( &gradient, x1, y2 );
            colors[1] = EwGetColorFromGradient( &gradient, x1, y1 );
            colors[2] = EwGetColorFromGradient( &gradient, x2, y1 );
            colors[3] = EwGetColorFromGradient( &gradient, x2, y2 );
          #endif

          #if EW_SURFACE_ROTATION == 180
            colors[0] = EwGetColorFromGradient( &gradient, x2, y2 );
            colors[1] = EwGetColorFromGradient( &gradient, x1, y2 );
            colors[2] = EwGetColorFromGradient( &gradient, x1, y1 );
            colors[3] = EwGetColorFromGradient( &gradient, x2, y1 );
          #endif

          #if EW_SURFACE_ROTATION == 270
            colors[0] = EwGetColorFromGradient( &gradient, x2, y1 );
            colors[1] = EwGetColorFromGradient( &gradient, x2, y2 );
            colors[2] = EwGetColorFromGradient( &gradient, x1, y2 );
            colors[3] = EwGetColorFromGradient( &gradient, x1, y1 );
          #endif
        }
      #endif

      noOfGlyphs++;

      EwStartPerfCounter( EwGfxCopy );

      /* Invoke the external driver function to the underlying graphics subsystem.
         Please note, depending on how the real surface content is orientend the
         coordinates need to be adapted respectively. */
      #if EW_SURFACE_ROTATION == 0
        /* On 64-bit target convert the 32-bit color list to 64-bit colors */
        #if defined __LP64__ || defined _LP64
        {
          unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

          CopyDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            dstX1, dstY1,
            srcX,  srcY,
            dstX2 - dstX1, dstY2 - dstY1,
            aTask->Flags & EW_TASK_ALPHABLEND, tmp );
        }
        #else
          CopyDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            dstX1, dstY1,
            srcX,  srcY,
            dstX2 - dstX1, dstY2 - dstY1,
            aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
        #endif
      #endif

      #if EW_SURFACE_ROTATION == 90
        /* On 64-bit target convert the 32-bit color list to 64-bit colors */
        #if defined __LP64__ || defined _LP64
        {
          unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

          CopyDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            aDst->Height - dstY2, dstX1,
            EwGlyphCacheSurface->Height - srcY - dstY2 + dstY1, srcX,
            dstY2 - dstY1, dstX2 - dstX1,
            aTask->Flags & EW_TASK_ALPHABLEND, tmp );
        }
        #else
          CopyDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            aDst->Height - dstY2, dstX1,
            EwGlyphCacheSurface->Height - srcY - dstY2 + dstY1, srcX,
            dstY2 - dstY1, dstX2 - dstX1,
            aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
        #endif
      #endif

      #if EW_SURFACE_ROTATION == 180
        /* On 64-bit target convert the 32-bit color list to 64-bit colors */
        #if defined __LP64__ || defined _LP64
        {
          unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

          CopyDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            aDst->Width - dstX2, aDst->Height - dstY2,
            EwGlyphCacheSurface->Width  - srcX - dstX2 + dstX1,
            EwGlyphCacheSurface->Height - srcY - dstY2 + dstY1,
            dstX2 - dstX1, dstY2 - dstY1,
            aTask->Flags & EW_TASK_ALPHABLEND, tmp );
        }
        #else
          CopyDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            aDst->Width - dstX2, aDst->Height - dstY2,
            EwGlyphCacheSurface->Width  - srcX - dstX2 + dstX1,
            EwGlyphCacheSurface->Height - srcY - dstY2 + dstY1,
            dstX2 - dstX1, dstY2 - dstY1,
            aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
        #endif
      #endif

      #if EW_SURFACE_ROTATION == 270
        /* On 64-bit target convert the 32-bit color list to 64-bit colors */
        #if defined __LP64__ || defined _LP64
        {
          unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

          CopyDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            dstY1, aDst->Width - dstX2,
            srcY,  EwGlyphCacheSurface->Width - srcX - dstX2 + dstX1,
            dstY2 - dstY1, dstX2 - dstX1,
            aTask->Flags & EW_TASK_ALPHABLEND, tmp );
        }
        #else
          CopyDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            dstY1, aDst->Width - dstX2,
            srcY,  EwGlyphCacheSurface->Width - srcX - dstX2 + dstX1,
            dstY2 - dstY1, dstX2 - dstX1,
            aTask->Flags & EW_TASK_ALPHABLEND, (unsigned long*)colors );
        #endif
      #endif

      EwStopPerfCounter( EwGfxCopy );
    }
  }

  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "DrawText( %d glyphs, ( %d, %d )-( %d, %d )=( %d x %d ), %s )\n",
               noOfGlyphs, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2,
               aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif
}

#endif /* EW_NEED_DRIVER_TABLES */


/* This helper function maps the 'draw text' task to the software emulated
   pixel driver. */
static void DrawText2( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XDrawText*       data       = (XDrawText*)aTask->Data;
  char*            slot       = (char*)( data + 1 );
  char*            last       = slot + data->Glyphs * (( sizeof( int ) * 2 ) + 
                                                         sizeof( void* ));
  int              ofsX       = data->DstX1 + data->OfsX;
  int              ofsY       = data->DstY1 + data->OfsY;
  int              x1         = aTask->X1;
  int              y1         = aTask->Y1;
  int              x2         = aTask->X2;
  int              y2         = aTask->Y2;
  XSurfaceMemory*  dst        = LockDstSurface( aDst );
  XSurfaceMemory*  src        = LockSrcSurface( EwGlyphCacheSurface );
  int              noOfGlyphs = 0;
  XGradient        gradient;

  #if EW_SURFACE_ROTATION != 0
    unsigned int   interColors[4];
    unsigned int*  colors = data->Colors;
  #endif

  /* No direct access to the surface memory */
  if ( !dst || !src )
    return;

  /* In case of vertical/horizontal only gradients, the rows/columns can be drawn
     with solid colors - no in-row interpolation is necessary. Select the faster
     (solid) version of the worker function. Note the special cases of rotated
     surface content. */
  #if ( EW_SURFACE_ROTATION == 0  ) || ( EW_SURFACE_ROTATION == 180 )
    if ( IS_LINEAR_GRADIENT( aTask->Flags ) && !IS_HORZ_GRADIENT( data->Colors ))
      aFuncNo += EW_TASK_SOLID - EW_TASK_LINEAR_GRADIENT;
  #endif

  #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
    if ( IS_LINEAR_GRADIENT( aTask->Flags ) && !IS_VERT_GRADIENT( data->Colors ))
      aFuncNo += EW_TASK_SOLID - EW_TASK_LINEAR_GRADIENT;
  #endif

  #if EW_SURFACE_ROTATION == 0
    EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
      data->Colors, &gradient );
  #endif

  #if EW_SURFACE_ROTATION == 90
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[3]; interColors[1] = colors[0];
      interColors[2] = colors[1]; interColors[3] = colors[2];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstY2 - data->DstY1, data->DstX2 - data->DstX1,
      colors, &gradient );
  #endif

  #if EW_SURFACE_ROTATION == 180
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[2]; interColors[1] = colors[3];
      interColors[2] = colors[0]; interColors[3] = colors[1];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
      colors, &gradient );
  #endif

  #if EW_SURFACE_ROTATION == 270
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[1]; interColors[1] = colors[2];
      interColors[2] = colors[3]; interColors[3] = colors[0];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstY2 - data->DstY1, data->DstX2 - data->DstX1,
      colors, &gradient );
  #endif

  /* Process the serie of text glyphs */
  for ( ; slot < last; slot += ( sizeof( int ) * 2 ) + sizeof( XGlyph* ))
  {
    int     posX  = ((int*)slot)[0];
    int     posY  = ((int*)slot)[1];
    XGlyph* glyph = *(XGlyph**)((int*)slot + 2 );
    int     dstX1 = MAX( ofsX + posX, x1 );
    int     dstY1 = MAX( ofsY + posY, y1 );
    int     dstX2 = MIN( ofsX + posX + glyph->Width,   x2 );
    int     dstY2 = MIN( ofsY + posY + glyph->Height,  y2 );
    int     srcX  = glyph->CacheX + dstX1 - ( ofsX + posX );
    int     srcY  = glyph->CacheY + dstY1 - ( ofsY + posY );

    /* Take in account the additional one-pixel wide border around the glyph */
    #ifdef EW_BORDER_AROUND_GLYPHS
      srcX += 1;
      srcY += 1; 
    #endif

    /* Any visible parts of the glyph after the clipping? Then run the pixel
       driver */
    if (( dstX2 > dstX1 ) && ( dstY2 > dstY1 ))
    {
      EwStartPerfCounter( EwGfxCopy );

      #if EW_SURFACE_ROTATION == 0
        EwEmulateCopy( dst, src,
          dstX1, dstY1,
          dstX2 - dstX1, dstY2 - dstY1, 
          srcX, srcY,
          &gradient,
          dstX1 - data->DstX1, dstY1 - data->DstY1,
          CopyWorkers[ aFuncNo ]);
      #endif

      #if EW_SURFACE_ROTATION == 90
        EwEmulateCopy( dst, src,
          aDst->Height - dstY2, dstX1,
          dstY2 - dstY1, dstX2 - dstX1,
          EwGlyphCacheSurface->Height - srcY - dstY2 + dstY1, srcX,
          &gradient,
          -dstY2 + data->DstY2, dstX1 - data->DstX1,
          CopyWorkers[ aFuncNo ]);
      #endif

      #if EW_SURFACE_ROTATION == 180
        EwEmulateCopy( dst, src,
          aDst->Width - dstX2, aDst->Height - dstY2,
          dstX2 - dstX1, dstY2 - dstY1, 
          EwGlyphCacheSurface->Width  - srcX - dstX2 + dstX1,
          EwGlyphCacheSurface->Height - srcY - dstY2 + dstY1,
          &gradient,
          -dstX2 + data->DstX2, -dstY2 + data->DstY2,
          CopyWorkers[ aFuncNo ]);
      #endif

      #if EW_SURFACE_ROTATION == 270
        EwEmulateCopy( dst, src,
          dstY1, aDst->Width - dstX2,
          dstY2 - dstY1, dstX2 - dstX1,
          srcY,  EwGlyphCacheSurface->Width - srcX - dstX2 + dstX1,
          &gradient,
          dstY1 - data->DstY1, -dstX2 + data->DstX2,
          CopyWorkers[ aFuncNo ]);
      #endif

      EwStopPerfCounter( EwGfxCopy );

      noOfGlyphs++;
    }
  }

  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "DrawText( %d glyphs, ( %d, %d )-( %d, %d )=( %d x %d ), %s ) SW\n",
               noOfGlyphs, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2,
               aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif
}


/* Eliminate not needed code */
#if defined EW_NEED_DRIVER_TABLES && !defined EW_DONT_USE_WARP_FUNCTIONS

/* This helper function maps the 'draw text' task to the driver function of
   the underlying graphics subsystem in case of rotated text. */
static void DrawText3( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XDrawText*   data       = (XDrawText*)aTask->Data;
  char*        slot       = (char*)( data + 1 );
  char*        last       = slot + data->Glyphs * (( sizeof( int ) * 2 ) + 
                                                     sizeof( void* ));
  int          orient     = data->Orientation;
  int          dstX1      = data->DstX1;
  int          dstY1      = data->DstY1;
  int          dstX2      = data->DstX2;
  int          dstY2      = data->DstY2;
  int          ofsX       = data->OfsX;
  int          ofsY       = data->OfsY;
  int          noOfGlyphs = 0;
  int          dstW, dstH;
  int          x1, y1, x2, y2;
  XGradient    gradient;
  unsigned int colors[4];

  /* First release any existing surface locks */
  LockDstSurface ( 0 );
  LockSrcSurface ( 0 );
  LockMaskSurface( 0 );

  /* To simplify the implementation we map the rotation aspects in 'virtual' 
     destination area (dstW, dstH) and clipping area (x12..y2) */
  if ( orient == 90 )
  {
    dstH = dstX2 - dstX1;        dstW = dstY2 - dstY1;
    x1   = dstY2 - aTask->Y2;    y1   = aTask->X1 - dstX1;
    x2   = dstY2 - aTask->Y1;    y2   = aTask->X2 - dstX1;
    colors[0] = data->Colors[3]; colors[1] = data->Colors[0];
    colors[3] = data->Colors[2]; colors[2] = data->Colors[1];
  }
  else if ( orient == 180 )
  {
    dstW = dstX2 - dstX1;        dstH = dstY2 - dstY1;
    x1   = dstX2 - aTask->X2;    y1   = dstY2 - aTask->Y2;
    x2   = dstX2 - aTask->X1;    y2   = dstY2 - aTask->Y1;
    colors[0] = data->Colors[2]; colors[1] = data->Colors[3];
    colors[3] = data->Colors[1]; colors[2] = data->Colors[0];
  }
  else /* 270 */
  {
    dstH = dstX2 - dstX1;        dstW = dstY2 - dstY1;
    x1   = aTask->Y1 - dstY1;    y1   = dstX2 - aTask->X2;
    x2   = aTask->Y2 - dstY1;    y2   = dstX2 - aTask->X1;
    colors[0] = data->Colors[1]; colors[1] = data->Colors[2];
    colors[3] = data->Colors[0]; colors[2] = data->Colors[3];
  }

  /* Prepare a gradient describing the colors within the 'virtual' destination
     area. */
  EwInitColorGradient( dstW, dstH, colors, &gradient );

  /* Process the serie of text glyphs */
  for ( ; slot < last; slot += ( sizeof( int ) * 2 ) + sizeof( XGlyph* ))
  {
    int     posX  = ((int*)slot)[0];
    int     posY  = ((int*)slot)[1];
    XGlyph* glyph = *(XGlyph**)((int*)slot + 2 );
    int     dstX1 = MAX( ofsX + posX, x1 );
    int     dstY1 = MAX( ofsY + posY, y1 );
    int     dstX2 = MIN( ofsX + posX + glyph->Width,   x2 );
    int     dstY2 = MIN( ofsY + posY + glyph->Height,  y2 );
    int     srcX  = glyph->CacheX + dstX1 - ( ofsX + posX );
    int     srcY  = glyph->CacheY + dstY1 - ( ofsY + posY );
    int     srcW  = dstX2 - dstX1;
    int     srcH  = dstY2 - dstY1;

    /* Take in account the additional one-pixel wide border around the glyph */
    #ifdef EW_BORDER_AROUND_GLYPHS
      srcX += 1;
      srcY += 1; 
    #endif

    /* Any visible parts of the glyph after the clipping? Then run the pixel
       driver */
    if (( srcW > 0 ) && ( srcH > 0 ))
    {
      int xs[4], ys[4];

      /* Pick the gradient colors for the four corners of the glyph */
      #ifndef EW_DONT_USE_GRADIENTS
        if ( aTask->Flags & EW_TASK_GRADIENT )
        {
          #if EW_SURFACE_ROTATION == 0
            colors[0] = EwGetColorFromGradient( &gradient, dstX1, dstY1 );
            colors[1] = EwGetColorFromGradient( &gradient, dstX2, dstY1 );
            colors[2] = EwGetColorFromGradient( &gradient, dstX2, dstY2 );
            colors[3] = EwGetColorFromGradient( &gradient, dstX1, dstY2 );
          #endif

          #if EW_SURFACE_ROTATION == 90
            colors[0] = EwGetColorFromGradient( &gradient, dstX1, dstY2 );
            colors[1] = EwGetColorFromGradient( &gradient, dstX1, dstY1 );
            colors[2] = EwGetColorFromGradient( &gradient, dstX2, dstY1 );
            colors[3] = EwGetColorFromGradient( &gradient, dstX2, dstY2 );
          #endif

          #if EW_SURFACE_ROTATION == 180
            colors[0] = EwGetColorFromGradient( &gradient, dstX2, dstY2 );
            colors[1] = EwGetColorFromGradient( &gradient, dstX1, dstY2 );
            colors[2] = EwGetColorFromGradient( &gradient, dstX1, dstY1 );
            colors[3] = EwGetColorFromGradient( &gradient, dstX2, dstY1 );
          #endif

          #if EW_SURFACE_ROTATION == 270
            colors[0] = EwGetColorFromGradient( &gradient, dstX2, dstY1 );
            colors[1] = EwGetColorFromGradient( &gradient, dstX2, dstY2 );
            colors[2] = EwGetColorFromGradient( &gradient, dstX1, dstY2 );
            colors[3] = EwGetColorFromGradient( &gradient, dstX1, dstY1 );
          #endif
        }
      #endif

      /* Determine the destinatipon coordinates for the four corners where to
         display the glyph */
      if ( orient == 90 )
      {
        xs[0] = dstY1 + data->DstX1; ys[0] = dstW - dstX1 + data->DstY1;
        xs[2] = dstY2 + data->DstX1; ys[2] = dstW - dstX2 + data->DstY1;
        xs[1] = xs[0];               ys[1] = ys[2];
        xs[3] = xs[2];               ys[3] = ys[0];
      }
      else if ( orient == 180 )
      {
        xs[0] = dstW - dstX1 + data->DstX1; ys[0] = dstH - dstY1 + data->DstY1;
        xs[2] = dstW - dstX2 + data->DstX1; ys[2] = dstH - dstY2 + data->DstY1;
        xs[1] = xs[2];                      ys[1] = ys[0];
        xs[3] = xs[0];                      ys[3] = ys[2];
      }
      else /* 270 */
      {
        xs[0] = dstH - dstY1 + data->DstX1; ys[0] = dstX1 + data->DstY1;
        xs[2] = dstH - dstY2 + data->DstX1; ys[2] = dstX2 + data->DstY1;
        xs[1] = xs[0];                      ys[1] = ys[2];
        xs[3] = xs[2];                      ys[3] = ys[0];
      }

      EwStartPerfCounter( EwGfxWarp );

      /* Invoke the external driver function to the underlying graphics subsystem.
         Please note, depending on how the real surface content is orientend the
         coordinates need to be adapted respectively. */
      #if EW_SURFACE_ROTATION == 0
        /* On 64-bit target convert the 32-bit color list to 64-bit colors */
        #if defined __LP64__ || defined _LP64
        {
          unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

          WarpAffineDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            (float)xs[0], (float)ys[0], 1.0f, (float)xs[1], (float)ys[1], 1.0f,
            (float)xs[2], (float)ys[2], 1.0f, (float)xs[3], (float)ys[3], 1.0f,
            srcX, srcY, srcW, srcH,
            aTask->X1, aTask->Y1, aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
            aTask->Flags & EW_TASK_ALPHABLEND, 0, tmp );
        }
        #else
          WarpAffineDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            (float)xs[0], (float)ys[0], 1.0f, (float)xs[1], (float)ys[1], 1.0f,
            (float)xs[2], (float)ys[2], 1.0f, (float)xs[3], (float)ys[3], 1.0f,
            srcX, srcY, srcW, srcH,
            aTask->X1, aTask->Y1, aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
            aTask->Flags & EW_TASK_ALPHABLEND, 0, (unsigned long*)colors );
        #endif
      #endif

      #if EW_SURFACE_ROTATION == 90
        /* On 64-bit target convert the 32-bit color list to 64-bit colors */
        #if defined __LP64__ || defined _LP64
        {
          unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

          WarpAffineDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            (float)( aDst->Height - ys[3]), (float)xs[3], 1.0f,
            (float)( aDst->Height - ys[0]), (float)xs[0], 1.0f,
            (float)( aDst->Height - ys[1]), (float)xs[1], 1.0f,
            (float)( aDst->Height - ys[2]), (float)xs[2], 1.0f,
            EwGlyphCacheSurface->Height - ( srcY + srcH ), srcX, srcH, srcW,
            aDst->Height - aTask->Y2, aTask->X1,
            aTask->Y2 - aTask->Y1, aTask->X2 - aTask->X1,
            aTask->Flags & EW_TASK_ALPHABLEND, 0, tmp );
        }
        #else
          WarpAffineDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            (float)( aDst->Height - ys[3]), (float)xs[3], 1.0f, 
            (float)( aDst->Height - ys[0]), (float)xs[0], 1.0f,
            (float)( aDst->Height - ys[1]), (float)xs[1], 1.0f,
            (float)( aDst->Height - ys[2]), (float)xs[2], 1.0f,
            EwGlyphCacheSurface->Height - ( srcY + srcH ), srcX, srcH, srcW,
            aDst->Height - aTask->Y2, aTask->X1,
            aTask->Y2 - aTask->Y1, aTask->X2 - aTask->X1,
            aTask->Flags & EW_TASK_ALPHABLEND, 0, (unsigned long*)colors );
        #endif
      #endif

      #if EW_SURFACE_ROTATION == 180
        /* On 64-bit target convert the 32-bit color list to 64-bit colors */
        #if defined __LP64__ || defined _LP64
        {
          unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

          WarpAffineDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            (float)( aDst->Width - xs[2]), (float)( aDst->Height - ys[2]), 1.0f,
            (float)( aDst->Width - xs[3]), (float)( aDst->Height - ys[3]), 1.0f,
            (float)( aDst->Width - xs[0]), (float)( aDst->Height - ys[0]), 1.0f,
            (float)( aDst->Width - xs[1]), (float)( aDst->Height - ys[1]), 1.0f,
            EwGlyphCacheSurface->Width  - ( srcX + srcW ), 
            EwGlyphCacheSurface->Height - ( srcY + srcH ),
            srcW, srcH,
            aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
            aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
            aTask->Flags & EW_TASK_ALPHABLEND, 0, tmp );
        }
        #else
          WarpAffineDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            (float)( aDst->Width - xs[2]), (float)( aDst->Height - ys[2]), 1.0f,
            (float)( aDst->Width - xs[3]), (float)( aDst->Height - ys[3]), 1.0f,
            (float)( aDst->Width - xs[0]), (float)( aDst->Height - ys[0]), 1.0f,
            (float)( aDst->Width - xs[1]), (float)( aDst->Height - ys[1]), 1.0f,
            EwGlyphCacheSurface->Width  - ( srcX + srcW ), 
            EwGlyphCacheSurface->Height - ( srcY + srcH ),
            srcW, srcH,
            aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
            aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
            aTask->Flags & EW_TASK_ALPHABLEND, 0, (unsigned long*)colors );
        #endif
      #endif

      #if EW_SURFACE_ROTATION == 270
        /* On 64-bit target convert the 32-bit color list to 64-bit colors */
        #if defined __LP64__ || defined _LP64
        {
          unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

          WarpAffineDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            (float)ys[1], (float)( aDst->Width - xs[1]), 1.0f,
            (float)ys[2], (float)( aDst->Width - xs[2]), 1.0f,
            (float)ys[3], (float)( aDst->Width - xs[3]), 1.0f,
            (float)ys[0], (float)( aDst->Width - xs[0]), 1.0f,
            srcY, EwGlyphCacheSurface->Width - ( srcX + srcW ), srcH, srcW,
            aTask->Y1, aDst->Width - aTask->X2,
            aTask->Y2 - aTask->Y1, aTask->X2 - aTask->X1,
            aTask->Flags & EW_TASK_ALPHABLEND, 0, tmp );
        }
        #else
          WarpAffineDrivers[ aFuncNo ]( aDst->Handle, EwGlyphCacheSurface->Handle,
            (float)ys[1], (float)( aDst->Width - xs[1]), 1.0f,
            (float)ys[2], (float)( aDst->Width - xs[2]), 1.0f,
            (float)ys[3], (float)( aDst->Width - xs[3]), 1.0f,
            (float)ys[0], (float)( aDst->Width - xs[0]), 1.0f,
            srcY, EwGlyphCacheSurface->Width - ( srcX + srcW ), srcH, srcW,
            aTask->Y1, aDst->Width - aTask->X2,
            aTask->Y2 - aTask->Y1, aTask->X2 - aTask->X1,
            aTask->Flags & EW_TASK_ALPHABLEND, 0, (unsigned long*)colors );
        #endif
      #endif

      EwStopPerfCounter( EwGfxWarp );

      noOfGlyphs++;
    }
  }

  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "DrawText_%d( %d glyphs, ( %d, %d )-( %d, %d )=( %d x %d ), %s )\n",
               orient, noOfGlyphs, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2,
               aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif
}

#endif /* EW_NEED_DRIVER_TABLES && !EW_DONT_USE_WARP_FUNCTIONS*/


/* Eliminate not needed code */
#ifndef EW_DONT_USE_WARP_FUNCTIONS

/* This helper function maps the 'draw text' task to the software emulated
   pixel driver in case of rotated text. */
static void DrawText4( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XDrawText*       data       = (XDrawText*)aTask->Data;
  char*            slot       = (char*)( data + 1 );
  char*            last       = slot + data->Glyphs * (( sizeof( int ) * 2 ) +
                                                         sizeof( void* ));
  int              orient     = data->Orientation;
  int              dstX1      = data->DstX1;
  int              dstY1      = data->DstY1;
  int              dstX2      = data->DstX2;
  int              dstY2      = data->DstY2;
  int              ofsX       = data->OfsX;
  int              ofsY       = data->OfsY;
  XSurfaceMemory*  dst        = LockDstSurface( aDst );
  XSurfaceMemory*  src        = LockSrcSurface( EwGlyphCacheSurface );
  int              isGradient = aTask->Flags & EW_TASK_GRADIENT;
  int              noOfGlyphs = 0;
  int              dstW, dstH;
  int              x1, y1, x2, y2;
  XGradient        gradient, interGradient;
  XGradient*       glyphGradient = isGradient? &interGradient : &gradient;
  unsigned int     colors[4];

  /* No direct access to the surface memory */
  if ( !dst || !src )
    return;

  /* In case of vertical/horizontal only gradients, the rows/columns can be drawn
     with solid colors - no in-row interpolation is necessary. Select the faster
     (solid) version of the worker function. Note the special cases of rotated
     surface content. */
  #if ( EW_SURFACE_ROTATION == 0  ) || ( EW_SURFACE_ROTATION == 180 )
    if ( IS_LINEAR_GRADIENT( aTask->Flags ) && !IS_HORZ_GRADIENT( data->Colors ))
      aFuncNo += EW_TASK_SOLID - EW_TASK_LINEAR_GRADIENT;
  #endif

  #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
    if ( IS_LINEAR_GRADIENT( aTask->Flags ) && !IS_VERT_GRADIENT( data->Colors ))
      aFuncNo += EW_TASK_SOLID - EW_TASK_LINEAR_GRADIENT;
  #endif

  /* To simplify the implementation we map the rotation aspects in 'virtual' 
     destination area (dstW, dstH) and clipping area (x12..y2) */
  if ( orient == 90 )
  {
    dstH = dstX2 - dstX1;        dstW = dstY2 - dstY1;
    x1   = dstY2 - aTask->Y2;    y1   = aTask->X1 - dstX1;
    x2   = dstY2 - aTask->Y1;    y2   = aTask->X2 - dstX1;
    colors[0] = data->Colors[3]; colors[1] = data->Colors[0];
    colors[3] = data->Colors[2]; colors[2] = data->Colors[1];
  }
  else if ( orient == 180 )
  {
    dstW = dstX2 - dstX1;        dstH = dstY2 - dstY1;
    x1   = dstX2 - aTask->X2;    y1   = dstY2 - aTask->Y2;
    x2   = dstX2 - aTask->X1;    y2   = dstY2 - aTask->Y1;
    colors[0] = data->Colors[2]; colors[1] = data->Colors[3];
    colors[3] = data->Colors[1]; colors[2] = data->Colors[0];
  }
  else /* 270 */
  {
    dstH = dstX2 - dstX1;        dstW = dstY2 - dstY1;
    x1   = aTask->Y1 - dstY1;    y1   = dstX2 - aTask->X2;
    x2   = aTask->Y2 - dstY1;    y2   = dstX2 - aTask->X1;
    colors[0] = data->Colors[1]; colors[1] = data->Colors[2];
    colors[3] = data->Colors[0]; colors[2] = data->Colors[3];
  }

  /* Prepare a gradient describing the colors within the 'virtual' destination
     area. */
  EwInitColorGradient( dstW, dstH, colors, &gradient );

  /* Process the serie of text glyphs */
  for ( ; slot < last; slot += ( sizeof( int ) * 2 ) + sizeof( XGlyph* ))
  {
    int     posX  = ((int*)slot)[0];
    int     posY  = ((int*)slot)[1];
    XGlyph* glyph = *(XGlyph**)((int*)slot + 2 );
    int     dstX1 = MAX( ofsX + posX, x1 );
    int     dstY1 = MAX( ofsY + posY, y1 );
    int     dstX2 = MIN( ofsX + posX + glyph->Width,   x2 );
    int     dstY2 = MIN( ofsY + posY + glyph->Height,  y2 );
    int     srcX  = glyph->CacheX + dstX1 - ( ofsX + posX );
    int     srcY  = glyph->CacheY + dstY1 - ( ofsY + posY );
    int     srcW  = dstX2 - dstX1;
    int     srcH  = dstY2 - dstY1;

    /* Take in account the additional one-pixel wide border around the glyph */
    #ifdef EW_BORDER_AROUND_GLYPHS
      srcX += 1;
      srcY += 1; 
    #endif

    /* Any visible parts of the glyph after the clipping? Then run the pixel
       driver */
    if (( srcW > 0 ) && ( srcH > 0 ))
    {
      int xs[4], ys[4];

      /* Pick the gradient colors for the four corners of the glyph */
      #ifndef EW_DONT_USE_GRADIENTS
        if ( isGradient )
        {
          colors[0] = EwGetColorFromGradient( &gradient, dstX1, dstY1 );
          colors[1] = EwGetColorFromGradient( &gradient, dstX2, dstY1 );
          colors[2] = EwGetColorFromGradient( &gradient, dstX2, dstY2 );
          colors[3] = EwGetColorFromGradient( &gradient, dstX1, dstY2 );
        }
      #endif

      /* Determine the destinatipon coordinates for the four corners where to
         display the glyph */
      if ( orient == 90 )
      {
        xs[0] = dstY1 + data->DstX1; ys[0] = dstW - dstX1 + data->DstY1;
        xs[2] = dstY2 + data->DstX1; ys[2] = dstW - dstX2 + data->DstY1;
        xs[1] = xs[0];               ys[1] = ys[2];
        xs[3] = xs[2];               ys[3] = ys[0];
      }
      else if ( orient == 180 )
      {
        xs[0] = dstW - dstX1 + data->DstX1; ys[0] = dstH - dstY1 + data->DstY1;
        xs[2] = dstW - dstX2 + data->DstX1; ys[2] = dstH - dstY2 + data->DstY1;
        xs[1] = xs[2];                      ys[1] = ys[0];
        xs[3] = xs[0];                      ys[3] = ys[2];
      }
      else /* 270 */
      {
        xs[0] = dstH - dstY1 + data->DstX1; ys[0] = dstX1 + data->DstY1;
        xs[2] = dstH - dstY2 + data->DstX1; ys[2] = dstX2 + data->DstY1;
        xs[1] = xs[0];                      ys[1] = ys[2];
        xs[3] = xs[2];                      ys[3] = ys[0];
      }

      EwStartPerfCounter( EwGfxWarp );

      /* Run the software pixel driver. Please note, depending on how the real
         surface content is orientend the coordinates and the order of colors need
         to be adapted respectively. */
      #if EW_SURFACE_ROTATION == 0
        if ( isGradient )
          EwInitColorGradient( srcW, srcH, colors, &interGradient );

        EwEmulateWarp( dst, src,
          xs[0] << 3, ys[0] << 3, 65536, xs[1] << 3, ys[1] << 3, 65536,
          xs[2] << 3, ys[2] << 3, 65536, xs[3] << 3, ys[3] << 3, 65536,
          srcX, srcY, srcW, srcH,
          aTask->X1, aTask->Y1, aTask->X2, aTask->Y2,
          glyphGradient, WarpAffineWorkers[ aFuncNo ]); 
      #endif

      #if EW_SURFACE_ROTATION == 90
        if ( isGradient )
        {
          unsigned int  interColors[4];

          interColors[0] = colors[3]; interColors[1] = colors[0];
          interColors[2] = colors[1]; interColors[3] = colors[2];
          EwInitColorGradient( srcH, srcW, interColors, &interGradient );
        }

        EwEmulateWarp( dst, src,
          ( aDst->Height - ys[3]) << 3, xs[3] << 3, 65536,
          ( aDst->Height - ys[0]) << 3, xs[0] << 3, 65536,
          ( aDst->Height - ys[1]) << 3, xs[1] << 3, 65536,
          ( aDst->Height - ys[2]) << 3, xs[2] << 3, 65536,
          EwGlyphCacheSurface->Height - ( srcY + srcH ), srcX, srcH, srcW,
          aDst->Height - aTask->Y2, aTask->X1,
          aDst->Height - aTask->Y1, aTask->X2,
          glyphGradient, WarpAffineWorkers[ aFuncNo ]); 
      #endif

      #if EW_SURFACE_ROTATION == 180
        if ( isGradient )
        {
          unsigned int  interColors[4];

          interColors[0] = colors[2]; interColors[1] = colors[3];
          interColors[2] = colors[0]; interColors[3] = colors[1];

          EwInitColorGradient( srcW, srcH, interColors, &interGradient );
        }

        EwEmulateWarp( dst, src,
          ( aDst->Width - xs[2]) << 3, ( aDst->Height - ys[2]) << 3, 65536,
          ( aDst->Width - xs[3]) << 3, ( aDst->Height - ys[3]) << 3, 65536,
          ( aDst->Width - xs[0]) << 3, ( aDst->Height - ys[0]) << 3, 65536,
          ( aDst->Width - xs[1]) << 3, ( aDst->Height - ys[1]) << 3, 65536,
          EwGlyphCacheSurface->Width  - ( srcX + srcW ), 
          EwGlyphCacheSurface->Height - ( srcY + srcH ),
          srcW, srcH,
          aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
          aDst->Width - aTask->X1, aDst->Height - aTask->Y1,
          glyphGradient, WarpAffineWorkers[ aFuncNo ]); 
      #endif

      #if EW_SURFACE_ROTATION == 270
        if ( aTask->Flags & EW_TASK_GRADIENT )
        {
          unsigned int  interColors[4];

          interColors[0] = colors[1]; interColors[1] = colors[2];
          interColors[2] = colors[3]; interColors[3] = colors[0];
          EwInitColorGradient( srcH, srcW, interColors, &interGradient );
        }

        EwEmulateWarp( dst, src,
          ys[1] << 3, ( aDst->Width - xs[1]) << 3, 65536,
          ys[2] << 3, ( aDst->Width - xs[2]) << 3, 65536,
          ys[3] << 3, ( aDst->Width - xs[3]) << 3, 65536,
          ys[0] << 3, ( aDst->Width - xs[0]) << 3, 65536,
          srcY, EwGlyphCacheSurface->Width - ( srcX + srcW ), srcH, srcW,
          aTask->Y1, aDst->Width - aTask->X2,
          aTask->Y2, aDst->Width - aTask->X1,
          glyphGradient, WarpAffineWorkers[ aFuncNo ]); 
      #endif

      EwStopPerfCounter( EwGfxWarp );

      noOfGlyphs++;
    }
  }

  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "DrawText_%d( %d glyphs, ( %d, %d )-( %d, %d )=( %d x %d ), %s ) SW\n",
               orient, noOfGlyphs, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2,
               aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif
}

#endif /* EW_DONT_USE_WARP_FUNCTIONS */


/* Helper macro for the float -> 29.3 and 16.16 fixed point format conversion */
#define ROUND3( a ) (int)(( a ) * 8.0f + 0.5f )
#define ROUND16( a ) (int)(( a ) * 65536.0f )


/* Eliminate not needed code */
#if defined EW_NEED_DRIVER_TABLES && !defined EW_DONT_USE_WARP_FUNCTIONS

/* This helper function maps the 'warp surface' task to the driver function of
   the underlying graphics subsystem. */
static void WarpSurface1( XSurface* aDst, XTask* aTask, 
  const XWarpDriver* aDrivers, int aFuncNo )
{
  XWarpSurface* data = (XWarpSurface*)aTask->Data;

  #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 180 )
    float dstH = (float)( aDst->Height );
  #endif

  #if ( EW_SURFACE_ROTATION == 180 ) || ( EW_SURFACE_ROTATION == 270 )
    float dstW = (float)( aDst->Width  );
  #endif

  #if EW_SURFACE_ROTATION != 0
    unsigned int* colors = data->Colors;
    unsigned int  interColors[4];
  #endif

  /* First release any existing surface locks */
  LockDstSurface ( 0 );
  LockSrcSurface ( 0 );
  LockMaskSurface( 0 );

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "WarpSurface( 0x%p, ( %d, %d )-( %d, %d )=( %d x %d ), %s )\n",
               data->Surface, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2,
               aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  EwStartPerfCounter( EwGfxWarp );

  #if EW_SURFACE_ROTATION == 0
    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { data->Colors[0], data->Colors[1], 
                               data->Colors[2], data->Colors[3]};

      aDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        data->DstX1, data->DstY1, data->DstW1,
        data->DstX2, data->DstY2, data->DstW2,
        data->DstX3, data->DstY3, data->DstW3,
        data->DstX4, data->DstY4, data->DstW4,
        data->SrcX1, data->SrcY1, 
        data->SrcX2 - data->SrcX1, data->SrcY2 - data->SrcY1,
        aTask->X1, aTask->Y1, aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
        aTask->Flags & EW_TASK_ALPHABLEND, aTask->Flags & EW_TASK_HIGH_QUALITY,
        tmp );
    }
    #else
      aDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        data->DstX1, data->DstY1, data->DstW1,
        data->DstX2, data->DstY2, data->DstW2,
        data->DstX3, data->DstY3, data->DstW3,
        data->DstX4, data->DstY4, data->DstW4,
        data->SrcX1, data->SrcY1, 
        data->SrcX2 - data->SrcX1, data->SrcY2 - data->SrcY1,
        aTask->X1, aTask->Y1, aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
        aTask->Flags & EW_TASK_ALPHABLEND, aTask->Flags & EW_TASK_HIGH_QUALITY,
        (unsigned long*)data->Colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 90
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[3]; interColors[1] = colors[0];
      interColors[2] = colors[1]; interColors[3] = colors[2];
      colors         = interColors;
    }    

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      aDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        dstH - data->DstY4, data->DstX4, data->DstW4,
        dstH - data->DstY1, data->DstX1, data->DstW1,
        dstH - data->DstY2, data->DstX2, data->DstW2,
        dstH - data->DstY3, data->DstX3, data->DstW3,
        data->Surface->Height - data->SrcY2, data->SrcX1,
        data->SrcY2 - data->SrcY1, data->SrcX2 - data->SrcX1,
        aDst->Height - aTask->Y2, aTask->X1,
        aTask->Y2 - aTask->Y1, aTask->X2 - aTask->X1,
        aTask->Flags & EW_TASK_ALPHABLEND, aTask->Flags & EW_TASK_HIGH_QUALITY,
        tmp );
    }
    #else
      aDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        dstH - data->DstY4, data->DstX4, data->DstW4,
        dstH - data->DstY1, data->DstX1, data->DstW1,
        dstH - data->DstY2, data->DstX2, data->DstW2,
        dstH - data->DstY3, data->DstX3, data->DstW3,
        data->Surface->Height - data->SrcY2, data->SrcX1,
        data->SrcY2 - data->SrcY1, data->SrcX2 - data->SrcX1,
        aDst->Height - aTask->Y2, aTask->X1,
        aTask->Y2 - aTask->Y1, aTask->X2 - aTask->X1,
        aTask->Flags & EW_TASK_ALPHABLEND, aTask->Flags & EW_TASK_HIGH_QUALITY,
        (unsigned long*)colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 180
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[2]; interColors[1] = colors[3];
      interColors[2] = colors[0]; interColors[3] = colors[1];
      colors         = interColors;
    }    

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      aDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        dstW - data->DstX3, dstH - data->DstY3, data->DstW3,
        dstW - data->DstX4, dstH - data->DstY4, data->DstW4,
        dstW - data->DstX1, dstH - data->DstY1, data->DstW1,
        dstW - data->DstX2, dstH - data->DstY2, data->DstW2,
        data->Surface->Width - data->SrcX2, data->Surface->Height - data->SrcY2,
        data->SrcX2 - data->SrcX1, data->SrcY2 - data->SrcY1,
        aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
        aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
        aTask->Flags & EW_TASK_ALPHABLEND, aTask->Flags & EW_TASK_HIGH_QUALITY,
        tmp );
    }
    #else
      aDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        dstW - data->DstX3, dstH - data->DstY3, data->DstW3,
        dstW - data->DstX4, dstH - data->DstY4, data->DstW4,
        dstW - data->DstX1, dstH - data->DstY1, data->DstW1,
        dstW - data->DstX2, dstH - data->DstY2, data->DstW2,
        data->Surface->Width - data->SrcX2, data->Surface->Height - data->SrcY2,
        data->SrcX2 - data->SrcX1, data->SrcY2 - data->SrcY1,
        aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
        aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
        aTask->Flags & EW_TASK_ALPHABLEND, aTask->Flags & EW_TASK_HIGH_QUALITY,
        (unsigned long*)colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 270
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[1]; interColors[1] = colors[2];
      interColors[2] = colors[3]; interColors[3] = colors[0];
      colors         = interColors;
    }    

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      aDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        data->DstY2, dstW - data->DstX2, data->DstW2,
        data->DstY3, dstW - data->DstX3, data->DstW3,
        data->DstY4, dstW - data->DstX4, data->DstW4,
        data->DstY1, dstW - data->DstX1, data->DstW1,
        data->SrcY1, data->Surface->Width - data->SrcX2,
        data->SrcY2 - data->SrcY1, data->SrcX2 - data->SrcX1,
        aTask->Y1, aDst->Width - aTask->X2,
        aTask->Y2 - aTask->Y1, aTask->X2 - aTask->X1,
        aTask->Flags & EW_TASK_ALPHABLEND, aTask->Flags & EW_TASK_HIGH_QUALITY,
        tmp );
    }
    #else
      aDrivers[ aFuncNo ]( aDst->Handle, data->Surface->Handle,
        data->DstY2, dstW - data->DstX2, data->DstW2,
        data->DstY3, dstW - data->DstX3, data->DstW3,
        data->DstY4, dstW - data->DstX4, data->DstW4,
        data->DstY1, dstW - data->DstX1, data->DstW1,
        data->SrcY1, data->Surface->Width - data->SrcX2,
        data->SrcY2 - data->SrcY1, data->SrcX2 - data->SrcX1,
        aTask->Y1, aDst->Width - aTask->X2,
        aTask->Y2 - aTask->Y1, aTask->X2 - aTask->X1,
        aTask->Flags & EW_TASK_ALPHABLEND, aTask->Flags & EW_TASK_HIGH_QUALITY,
        (unsigned long*)colors );
    #endif
  #endif

  EwStopPerfCounter( EwGfxWarp );
}

#endif /* EW_NEED_DRIVER_TABLES && !EW_DONT_USE_WARP_FUNCTIONS */


/* Eliminate not needed code */
#ifndef EW_DONT_USE_WARP_FUNCTIONS

/* This helper function maps the 'warp surface' task to the software emulated
   pixel driver. */
static void WarpSurface2( XSurface* aDst, XTask* aTask, 
  const XWarpWorker* aWorkers, int aFuncNo )
{
  XWarpSurface*    data = (XWarpSurface*)aTask->Data;
  XSurfaceMemory*  dst  = LockDstSurface( aDst );
  XSurfaceMemory*  src  = LockSrcSurface( data->Surface );
  XGradient        gradient;

  #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 180 )
    float dstH = (float)( aDst->Height );
  #endif

  #if ( EW_SURFACE_ROTATION == 180 ) || ( EW_SURFACE_ROTATION == 270 )
    float dstW = (float)( aDst->Width  );
  #endif

  #if EW_SURFACE_ROTATION != 0
    unsigned int* colors = data->Colors;
    unsigned int  interColors[4];
  #endif

  /* No direct access to the surface memory */
  if ( !dst || !src )
    return;

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "WarpSurface( 0x%p, ( %d, %d )-( %d, %d )=( %d x %d ), %s ) SW\n",
               data->Surface, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2,
               aTask->X2 - aTask->X1, aTask->Y2 - aTask->Y1,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  EwStartPerfCounter( EwGfxWarp );

  /* Run the software pixel driver. Please note, depending on how the real
     surface content is orientend the coordinates and the order of colors need
     to be adapted respectively. */
  #if EW_SURFACE_ROTATION == 0
    EwInitColorGradient( data->SrcX2 - data->SrcX1, data->SrcY2 - data->SrcY1,
      data->Colors, &gradient );

    EwEmulateWarp( dst, src,
      ROUND3( data->DstX1 ), ROUND3( data->DstY1 ), ROUND16( data->DstW1 ),
      ROUND3( data->DstX2 ), ROUND3( data->DstY2 ), ROUND16( data->DstW2 ),
      ROUND3( data->DstX3 ), ROUND3( data->DstY3 ), ROUND16( data->DstW3 ),
      ROUND3( data->DstX4 ), ROUND3( data->DstY4 ), ROUND16( data->DstW4 ),
      data->SrcX1, data->SrcY1,
      data->SrcX2 - data->SrcX1, data->SrcY2 - data->SrcY1,
      aTask->X1, aTask->Y1, aTask->X2, aTask->Y2,
      &gradient, aWorkers[ aFuncNo ]); 
  #endif

  #if EW_SURFACE_ROTATION == 90
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[3]; interColors[1] = colors[0];
      interColors[2] = colors[1]; interColors[3] = colors[2];
      colors         = interColors;
    }

    EwInitColorGradient( data->SrcY2 - data->SrcY1, data->SrcX2 - data->SrcX1,
      colors, &gradient );

    EwEmulateWarp( dst, src,
      ROUND3( dstH - data->DstY4 ), ROUND3( data->DstX4 ), ROUND16( data->DstW4 ),
      ROUND3( dstH - data->DstY1 ), ROUND3( data->DstX1 ), ROUND16( data->DstW1 ),
      ROUND3( dstH - data->DstY2 ), ROUND3( data->DstX2 ), ROUND16( data->DstW2 ),
      ROUND3( dstH - data->DstY3 ), ROUND3( data->DstX3 ), ROUND16( data->DstW3 ),
      data->Surface->Height - data->SrcY2, data->SrcX1,
      data->SrcY2 - data->SrcY1, data->SrcX2 - data->SrcX1,
      aDst->Height - aTask->Y2, aTask->X1,
      aDst->Height - aTask->Y1, aTask->X2,
      &gradient, aWorkers[ aFuncNo ]); 
  #endif

  #if EW_SURFACE_ROTATION == 180
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[2]; interColors[1] = colors[3];
      interColors[2] = colors[0]; interColors[3] = colors[1];
      colors         = interColors;
    }

    EwInitColorGradient( data->SrcX2 - data->SrcX1, data->SrcY2 - data->SrcY1,
      colors, &gradient );

    EwEmulateWarp( dst, src,
      ROUND3( dstW - data->DstX3 ), ROUND3( dstH - data->DstY3 ), ROUND16( data->DstW3 ),
      ROUND3( dstW - data->DstX4 ), ROUND3( dstH - data->DstY4 ), ROUND16( data->DstW4 ),
      ROUND3( dstW - data->DstX1 ), ROUND3( dstH - data->DstY1 ), ROUND16( data->DstW1 ),
      ROUND3( dstW - data->DstX2 ), ROUND3( dstH - data->DstY2 ), ROUND16( data->DstW2 ),
      data->Surface->Width - data->SrcX2, data->Surface->Height - data->SrcY2,
      data->SrcX2 - data->SrcX1, data->SrcY2 - data->SrcY1,
      aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
      aDst->Width - aTask->X1, aDst->Height - aTask->Y1,
      &gradient, aWorkers[ aFuncNo ]); 
  #endif

  #if EW_SURFACE_ROTATION == 270
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[1]; interColors[1] = colors[2];
      interColors[2] = colors[3]; interColors[3] = colors[0];
      colors         = interColors;
    }

    EwInitColorGradient( data->SrcY2 - data->SrcY1, data->SrcX2 - data->SrcX1,
      colors, &gradient );

    EwEmulateWarp( dst, src,
      ROUND3( data->DstY2 ), ROUND3( dstW - data->DstX2 ), ROUND16( data->DstW2 ),
      ROUND3( data->DstY3 ), ROUND3( dstW - data->DstX3 ), ROUND16( data->DstW3 ),
      ROUND3( data->DstY4 ), ROUND3( dstW - data->DstX4 ), ROUND16( data->DstW4 ),
      ROUND3( data->DstY1 ), ROUND3( dstW - data->DstX1 ), ROUND16( data->DstW1 ),
      data->SrcY1, data->Surface->Width - data->SrcX2,
      data->SrcY2 - data->SrcY1, data->SrcX2 - data->SrcX1,
      aTask->Y1, aDst->Width - aTask->X2,
      aTask->Y2, aDst->Width - aTask->X1,
      &gradient, aWorkers[ aFuncNo ]); 
  #endif

  EwStopPerfCounter( EwGfxWarp );
}

#endif /* EW_DONT_USE_WARP_FUNCTIONS */


/* Eliminate not needed code */
#if defined EW_NEED_DRIVER_TABLES       && \
  ( !defined EW_DONT_USE_BLUR_FUNCTIONS || \
    !defined EW_DONT_USE_MASK_FUNCTIONS || \
    !defined EW_DONT_USE_TINT_FUNCTIONS )

/* This helper function maps the 'filter' task to the driver function of
   the underlying graphics subsystem. */
static void Filter1( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XFilterSurface* data  = (XFilterSurface*)aTask->Data;
  int             clpW  = aTask->X2 - aTask->X1;
  int             clpH  = aTask->Y2 - aTask->Y1;

  #if ( EW_SURFACE_ROTATION == 180 ) || ( EW_SURFACE_ROTATION == 270 )
    int           maskW = data->MaskSurface? data->MaskSurface->Width  : 0;
    int           srcW  = data->SrcSurface->Width;
  #endif
  #if ( EW_SURFACE_ROTATION == 180 ) || ( EW_SURFACE_ROTATION == 90 )
    int           maskH = data->MaskSurface? data->MaskSurface->Height : 0;
    int           srcH  = data->SrcSurface->Height;
  #endif

  /* First release any existing surface locks */
  LockDstSurface ( 0 );
  LockSrcSurface ( 0 );
  LockMaskSurface( 0 );

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "FilterSurface( 0x%p, ( %d, %d )-( %d, %d )=( %d x %d ), %s )\n",
               data->SrcSurface, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, 
               clpH, (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  EwStartPerfCounter( EwGfxFilter );

  /* Invoke the external driver function to the underlying graphics subsystem.
     Please note, depending on how the real surface content is orientend the
     coordinates need to be adapted respectively. */
  #if EW_SURFACE_ROTATION == 0
    FilterDrivers[ aFuncNo ]( aDst->Handle, data->SrcSurface->Handle,
      data->MaskSurface? data->MaskSurface->Handle : 0,
      data->DstX1,    data->DstY1,
      data->DstX2  -  data->DstX1,  data->DstY2 - data->DstY1,
      data->SrcX1,    data->SrcY1,
      data->SrcX2  -  data->SrcX1,  data->SrcY2 - data->SrcY1,
      data->SrcPosX,  data->SrcPosY,
      data->MaskPosX, data->MaskPosY,
      aTask->X1, aTask->Y1,
      clpW, clpH, 
      data->MaskInverted, data->MaskBeforeBlur, data->BlurRadius,
      data->BlurClampToEdges, data->Mode, data->Intensity, data->Color,
      data->Opacity, aTask->Flags & EW_TASK_ALPHABLEND );
  #endif

  #if EW_SURFACE_ROTATION == 90
    FilterDrivers[ aFuncNo ]( aDst->Handle, data->SrcSurface->Handle,
      data->MaskSurface? data->MaskSurface->Handle : 0,
      aDst->Height - data->DstY2, data->DstX1,
      data->DstY2  - data->DstY1, data->DstX2  -  data->DstX1,
      srcH         - data->SrcY2, data->SrcX1,
      data->SrcY2  - data->SrcY1, data->SrcX2  -  data->SrcX1,  
      srcH  - data->SrcPosY  - ( data->DstY2 - data->DstY1 ), data->SrcPosX,
      maskH - data->MaskPosY - ( data->DstY2 - data->DstY1 ), data->MaskPosX,
      aDst->Height - aTask->Y2, aTask->X1,
      clpH, clpW, 
      data->MaskInverted, data->MaskBeforeBlur, data->BlurRadius,
      data->BlurClampToEdges, data->Mode, data->Intensity, data->Color,
      data->Opacity, aTask->Flags & EW_TASK_ALPHABLEND );
  #endif

  #if EW_SURFACE_ROTATION == 180
    FilterDrivers[ aFuncNo ]( aDst->Handle, data->SrcSurface->Handle,
      data->MaskSurface? data->MaskSurface->Handle : 0,
      aDst->Width - data->DstX2, aDst->Height - data->DstY2,
      data->DstX2 - data->DstX1, data->DstY2  - data->DstY1,
      srcW        - data->SrcX2, srcH         - data->SrcY2,
      data->SrcX2 - data->SrcX1, data->SrcY2  - data->SrcY1,
      srcW  - data->SrcPosX  - ( data->DstX2 - data->DstX1 ),
      srcH  - data->SrcPosY  - ( data->DstY2 - data->DstY1 ),
      maskW - data->MaskPosX - ( data->DstX2 - data->DstX1 ),
      maskH - data->MaskPosY - ( data->DstY2 - data->DstY1 ),
      aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
      clpW, clpH,
      data->MaskInverted, data->MaskBeforeBlur, data->BlurRadius,
      data->BlurClampToEdges, data->Mode, data->Intensity, data->Color,
      data->Opacity, aTask->Flags & EW_TASK_ALPHABLEND );
  #endif

  #if EW_SURFACE_ROTATION == 270
    FilterDrivers[ aFuncNo ]( aDst->Handle, data->SrcSurface->Handle,
      data->MaskSurface? data->MaskSurface->Handle : 0,
      data->DstY1,               aDst->Width - data->DstX2, 
      data->DstY2 - data->DstY1, data->DstX2 - data->DstX1,
      data->SrcY1,               srcW        - data->SrcX2, 
      data->SrcY2 - data->SrcY1, data->SrcX2 -  data->SrcX1,
      data->SrcPosY,  srcW  - data->SrcPosX  - ( data->DstX2 - data->DstX1 ), 
      data->MaskPosY, maskW - data->MaskPosX - ( data->DstX2 - data->DstX1 ),
      aTask->Y1, aDst->Width - aTask->X2, 
      clpH, clpW, 
      data->MaskInverted, data->MaskBeforeBlur, data->BlurRadius,
      data->BlurClampToEdges, data->Mode, data->Intensity, data->Color,
      data->Opacity, aTask->Flags & EW_TASK_ALPHABLEND );
  #endif

  EwStopPerfCounter( EwGfxFilter );
}

#endif /* EW_NEED_DRIVER_TABLES && !EW_DONT_USE_{FILTER}_FUNCTIONS */


/* Eliminate unused code */
#if !defined EW_DONT_USE_MASK_FUNCTIONS || !defined EW_DONT_USE_TINT_FUNCTIONS

/* This helper function maps the 'filter' task to the software emulated
   pixel driver. This function takes care of mask/tint filter operations
   only without any blur effects. */
static void Filter2( XSurface* aDst, XTask* aTask, int aFuncNo1, int aFuncNo2 )
{
  XFilterSurface*  data  = (XFilterSurface*)aTask->Data;
  int              clpW  = aTask->X2 - aTask->X1;
  int              clpH  = aTask->Y2 - aTask->Y1;
  XSurfaceMemory*  dst   = LockDstSurface ( aDst );
  XSurfaceMemory*  src   = LockSrcSurface ( data->SrcSurface );
  XSurfaceMemory*  mask  = LockMaskSurface( data->MaskSurface );
  XGradient        gradient;

  #if ( EW_SURFACE_ROTATION == 180 ) || ( EW_SURFACE_ROTATION == 270 )
    int            maskW = data->MaskSurface? data->MaskSurface->Width  : 0;
    int            srcW  = data->SrcSurface->Width;
  #endif
  #if ( EW_SURFACE_ROTATION == 180 ) || ( EW_SURFACE_ROTATION == 90 )
    int            maskH = data->MaskSurface? data->MaskSurface->Height : 0;
    int            srcH  = data->SrcSurface->Height;
  #endif

  /* No direct access to the surface memory */
  if ( !dst || !src || ( !mask && data->MaskSurface ))
    return;

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "FilterSurface( 0x%p, ( %d, %d )-( %d, %d )=( %d x %d ), %s ) SW\n",
               data->SrcSurface, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, 
               clpH, (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  EwStartPerfCounter( EwGfxFilter );

  /* Prepare the color as XGradient structure */
  EwInitSingleColorGradient( data->Color, &gradient );

  /* Run the software pixel driver. Please note, depending on how the real
     surface content is orientend the coordinates need to be adapted. */
  #if EW_SURFACE_ROTATION == 0
    EwEmulateMaskTintFilter( dst, src, mask,
      aTask->X1, aTask->Y1,
      clpW, clpH,
      data->SrcPosX  + aTask->X1 - data->DstX1,
      data->SrcPosY  + aTask->Y1 - data->DstY1,
      data->MaskPosX + aTask->X1 - data->DstX1,
      data->MaskPosY + aTask->Y1 - data->DstY1,
      data->MaskX1, data->MaskY1,
      data->MaskX2, data->MaskY2,
      data->MaskInverted,
      &gradient,
      (int)( data->Intensity * 255.0f ),
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      MaskTintWorkers[ aFuncNo1 ], MaskTintWorkers[ aFuncNo2 ]); 
  #endif

  #if EW_SURFACE_ROTATION == 90
    EwEmulateMaskTintFilter( dst, src, mask,
      aDst->Height - aTask->Y2, aTask->X1,
      clpH, clpW,
      srcH  - data->SrcPosY  - clpH - aTask->Y1 + data->DstY1,
      data->SrcPosX  + aTask->X1 - data->DstX1,
      maskH - data->MaskPosY - clpH - aTask->Y1 + data->DstY1,
      data->MaskPosX + aTask->X1 - data->DstX1,
      maskH - data->MaskY2, data->MaskX1,
      maskH - data->MaskY1, data->MaskX2,
      data->MaskInverted,
      &gradient,
      (int)( data->Intensity * 255.0f ),
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      MaskTintWorkers[ aFuncNo1 ], MaskTintWorkers[ aFuncNo2 ]); 
  #endif

  #if EW_SURFACE_ROTATION == 180
    EwEmulateMaskTintFilter( dst, src, mask,
      aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
      clpW, clpH,
      srcW  - data->SrcPosX  - clpW - aTask->X1 + data->DstX1,
      srcH  - data->SrcPosY  - clpH - aTask->Y1 + data->DstY1,
      maskW - data->MaskPosX - clpW - aTask->X1 + data->DstX1,
      maskH - data->MaskPosY - clpH - aTask->Y1 + data->DstY1,
      maskW - data->MaskX2, maskH - data->MaskY2,
      maskW - data->MaskX1, maskH - data->MaskY1,
      data->MaskInverted,
      &gradient,
      (int)( data->Intensity * 255.0f ),
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      MaskTintWorkers[ aFuncNo1 ], MaskTintWorkers[ aFuncNo2 ]); 
  #endif

  #if EW_SURFACE_ROTATION == 270
    EwEmulateMaskTintFilter( dst, src, mask,
      aTask->Y1, aDst->Width - aTask->X2,
      clpH, clpW,
      data->SrcPosY + aTask->Y1 - data->DstY1,
      srcW - data->SrcPosX - clpW - aTask->X1 + data->DstX1,
      data->MaskPosY + aTask->Y1 - data->DstY1,
      maskW - data->MaskPosX - clpW - aTask->X1 + data->DstX1,
      data->MaskY1, maskW - data->MaskX2,
      data->MaskY2, maskW - data->MaskX1,
      data->MaskInverted,
      &gradient,
      (int)( data->Intensity * 255.0f ),
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      MaskTintWorkers[ aFuncNo1 ], MaskTintWorkers[ aFuncNo2 ]); 
  #endif

  EwStopPerfCounter( EwGfxFilter );
}

#endif /* !EW_DONT_USE_MASK_FUNCTIONS || !EW_DONT_USE_TINT_FUNCTIONS */


#if !defined EW_DONT_USE_BLUR_FUNCTIONS

/* This helper function maps the 'filter' task to the software emulated pixel
   driver. This function takes care of blur filter operations only without any
   blur effects. */
static void Filter3( XSurface* aDst, XTask* aTask, int aFuncNo1, int aFuncNo2,
  int aRadius )
{
  XFilterSurface*  data = (XFilterSurface*)aTask->Data;
  int              clpW = aTask->X2 - aTask->X1;
  int              clpH = aTask->Y2 - aTask->Y1;
  int              blur = data->BlurRadius;
  XSurfaceMemory*  src  = LockSrcSurface( data->SrcSurface );
  XSurfaceMemory*  dst;
  XSurface*        tmp;

  #if ( EW_SURFACE_ROTATION == 180 ) || ( EW_SURFACE_ROTATION == 270 )
    int            srcW  = data->SrcSurface->Width;
  #endif
  #if ( EW_SURFACE_ROTATION == 180 ) || ( EW_SURFACE_ROTATION == 90 )
    int            srcH  = data->SrcSurface->Height;
  #endif

  /* Coordinates in source surface at the edges of the drawing area */
  int csx1 = data->SrcPosX + aTask->X1 - data->DstX1;
  int csy1 = data->SrcPosY + aTask->Y1 - data->DstY1;
  int csx2 = csx1 + clpW;
  int csy2 = csy1 + clpH;

  /* Since the blur is used, we need more of the source surface to process.
     The algorithm will read the source pixel beyond the edges of the drawing
     destination */
  int bsx1 = csx1 - blur;
  int bsy1 = csy1 - blur;
  int bsx2 = csx2 + blur;
  int bsy2 = csy2 + blur;

  /* The source area inclusive pixel to take in account during blur */
  int sx1  = MAX( bsx1, data->SrcX1 );
  int sx2  = MIN( bsx2, data->SrcX2 );
  int sy1  = MAX( bsy1, data->SrcY1 );
  int sy2  = MIN( bsy2, data->SrcY2 );

  /* Distances relative to the edges of the drawing destination when start the
     clamping */
  int cl   = data->BlurClampToEdges? aTask->X1 - data->DstX1 : blur;
  int ct   = data->BlurClampToEdges? aTask->Y1 - data->DstY1 : blur;
  int cr   = data->BlurClampToEdges? data->DstX2 - aTask->X1 : clpW + blur;
  int cb   = data->BlurClampToEdges? data->DstY2 - aTask->Y1 : clpH + blur;

  /* Size of the intermediate surface to store blurred rows/columns */
  #if ( EW_SURFACE_ROTATION == 0 ) || ( EW_SURFACE_ROTATION == 180 )
    int tmpW = sy2 - sy1;
    int tmpH = clpW;
  #endif

  #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
    int tmpW = clpH;
    int tmpH = sx2 - sx1;
  #endif

  /* Nothing to do */
  if (( sy2 <= sy1 ) || ( sx2 <= sx1 ))
    return;

  /* Create a temporary surface to store the intermediate state of the blur
     operation in which the rows and columns are exchanged. See the size
     calculation above. Because of the blur effect the surface may be bigger
     than the clipping area to take in account the pixel rows intersecting the
     blur radius above/below the update area. */
  tmp = EwCreateSurface( EW_PIXEL_FORMAT_NATIVE, tmpW, tmpH, 0, 0, 0 );

  /* No memory for the temp. surface? */
  if ( !tmp )
  {
    EwError( 420 );
    return;
  }

  /* Obtain direct access to the surface memory */
  dst = LockDstSurface( tmp );

  /* No direct access to the surface memory */
  if ( !dst || !src )
  {
    LockDstSurface( 0 );
    EwFreeSurface( tmp );
    return;
  }

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "FilterSurface( 0x%p, ( %d, %d )-( %d, %d )=( %d x %d ), %s ) SW\n",
               data->SrcSurface, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, 
               clpH, (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  EwStartPerfCounter( EwGfxFilter );

  /* Run the software pixel driver for the first phase of the blur effect. Here 
     the rows from the source are blured and stored in the intermediate surface
     tmp. Please note, depending on how the real surface content is orientend the
     coordinates need to be adapted. */
  #if EW_SURFACE_ROTATION == 0
    EwEmulateBlurFilter( dst, src, 
      0, 0,
      tmpW, tmpH,
      csx1,
      sy1,
      data->SrcX1,
      data->SrcX2,
      cl,
      cr,
      aRadius,
      255,
      0,
      BlurWorkers[ aFuncNo1 ]);
  #endif

  #if EW_SURFACE_ROTATION == 90
    EwEmulateBlurFilter( dst, src, 
      0, 0,
      tmpH, tmpW,
      srcH - csy2,
      sx1,
      srcH - data->SrcY2, srcH - data->SrcY1,
      cb - clpH,
      ct + clpH,
      aRadius,
      255,
      0,
      BlurWorkers[ aFuncNo1 ]);
  #endif

  #if EW_SURFACE_ROTATION == 180
    EwEmulateBlurFilter( dst, src, 
      0, 0,
      tmpW, tmpH,
      srcW - csx1 - tmpH,
      srcH - sy1  - tmpW,
      srcW - data->SrcX2,
      srcW - data->SrcX1,
      cr - clpW,
      cl + clpW,
      aRadius,
      255,
      0,
      BlurWorkers[ aFuncNo1 ]);
  #endif

  #if EW_SURFACE_ROTATION == 270
    EwEmulateBlurFilter( dst, src, 
      0, 0,
      tmpH, tmpW,
      csy1,
      srcW - sx2,
      data->SrcY1, data->SrcY2,
      ct,
      cb,
      aRadius,
      255,
      0,
      BlurWorkers[ aFuncNo1 ]);
  #endif

  /* Prepare for the second phase where the contents from the intermediate
     surface are blured column-wise and stored in the final destination */
  src = LockSrcSurface( tmp );
  dst = LockDstSurface( aDst );

  /* Run the software pixel driver for the second phase of the blur effect. Here 
     the content of the intermediate surface tmp is blured column-wise. Please
     note, depending on how the real surface content is orientend the coordinates
     need to be adapted. */
  #if EW_SURFACE_ROTATION == 0
    EwEmulateBlurFilter( dst, src, 
      aTask->X1, aTask->Y1,
      clpW, clpH,
      csy1 - sy1,
      0,
      0,
      tmpW,
      ct,
      cb,
      aRadius,
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      BlurWorkers[ aFuncNo2 ]);
  #endif

  #if EW_SURFACE_ROTATION == 90
    EwEmulateBlurFilter( dst, src, 
      aDst->Height - aTask->Y2, aTask->X1,
      clpH, clpW,
      csx1 - sx1,
      0,
      0,
      tmpH,
      cl,
      cr,
      aRadius,
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      BlurWorkers[ aFuncNo2 ]);
  #endif

  #if EW_SURFACE_ROTATION == 180
    EwEmulateBlurFilter( dst, src, 
      aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
      clpW, clpH,
      tmpW - ( csy1 - sy1 ) - clpH,
      0,
      0,
      tmpW,
      cb - clpH,
      ct + clpH,
      aRadius,
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      BlurWorkers[ aFuncNo2 ]);
  #endif

  #if EW_SURFACE_ROTATION == 270
    EwEmulateBlurFilter( dst, src, 
      aTask->Y1, aDst->Width - aTask->X2,
      clpH, clpW,
      sx2 - csx2,
      0,
      0,
      tmpH,
      cr - clpW,
      cl + clpW,
      aRadius,
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      BlurWorkers[ aFuncNo2 ]);
  #endif

  EwStopPerfCounter( EwGfxFilter );

  /* The temporary surface is not needed anymore. Unlock and release. */
  LockSrcSurface( 0 );
  EwFreeSurface( tmp );
}

#endif /* !EW_DONT_USE_BLUR_FUNCTIONS */


#if !defined EW_DONT_USE_BLUR_FUNCTIONS && \
  ( !defined EW_DONT_USE_MASK_FUNCTIONS || \
    !defined EW_DONT_USE_TINT_FUNCTIONS ) 

/* This helper function maps the 'filter' task to the software emulated pixel
   driver. This function performs the complex filter operation composed of
   mask/tint filter and the following blur filter. The parameter aFuncNoX are
   responsable for selecting the appropriate worker functions. Following is the
   meaning of the functions:
   aFuncNo0 - Copy-Worker used to copy between the source surface and a NATIVE
     surface for areas lying beyond an inverted mask without applying any tint
     filter.
   aFuncNo1 - Worker used to mask and evtl. tint between a source surface and
     a NATIVE surface.
   aFuncNo2 - Worker used to tint only between a source and a NATIVE surface.
   aFuncNo3 - Worker used to blur between two NATIVE surfaces.
   aFuncNo4 - Worker used to blur between the source and a NATIVE surface.
   aFuncNo5 - Worker used to blur between a NATIVE and the destination
     surface. */
static void Filter4( XSurface* aDst, XTask* aTask, int aFuncNo0, int aFuncNo1,
  int aFuncNo2, int aFuncNo3, int aFuncNo4, int aFuncNo5, int aRadius )
{
  XFilterSurface*  data   = (XFilterSurface*)aTask->Data;
  int              clpW   = aTask->X2 - aTask->X1;
  int              clpH   = aTask->Y2 - aTask->Y1;
  int              blur   = data->BlurRadius;
  int              maskNI = data->MaskSurface && !data->MaskInverted;
  XSurfaceMemory*  src    = LockSrcSurface ( data->SrcSurface );
  XSurfaceMemory*  mask   = LockMaskSurface( data->MaskSurface );
  XSurfaceMemory*  dst;
  XSurfaceLock     aux;
  XSurface*        tmp1;
  XSurface*        tmp2;
  XGradient        gradient;

  #if ( EW_SURFACE_ROTATION == 180 ) || ( EW_SURFACE_ROTATION == 270 )
    int            maskW = data->MaskSurface? data->MaskSurface->Width  : 0;
    int            srcW  = data->SrcSurface->Width;
  #endif
  #if ( EW_SURFACE_ROTATION == 180 ) || ( EW_SURFACE_ROTATION == 90 )
    int            maskH = data->MaskSurface? data->MaskSurface->Height : 0;
    int            srcH  = data->SrcSurface->Height;
  #endif

  /* Coordinates in source surface at the edges of the drawing area */
  int csx1    = data->SrcPosX + aTask->X1 - data->DstX1;
  int csy1    = data->SrcPosY + aTask->Y1 - data->DstY1;
  int csx2    = csx1 + clpW;
  int csy2    = csy1 + clpH;

  /* Since the blur is used, we need more of the source surface to process.
     The algorithm will read the source pixel beyond the edges of the drawing
     destination */
  int bsx1    = csx1 - blur;
  int bsy1    = csy1 - blur;
  int bsx2    = csx2 + blur;
  int bsy2    = csy2 + blur;

  /* The valid area of the source and mask surface relative to the top-left
     corner of the drawing destination */
  int gSrcX1  = data->SrcX1  - data->SrcPosX;
  int gSrcY1  = data->SrcY1  - data->SrcPosY;
  int gSrcX2  = data->SrcX2  - data->SrcPosX;
  int gSrcY2  = data->SrcY2  - data->SrcPosY;
  int gMaskX1 = data->MaskX1 - data->MaskPosX;
  int gMaskY1 = data->MaskY1 - data->MaskPosY;
  int gMaskX2 = data->MaskX2 - data->MaskPosX;
  int gMaskY2 = data->MaskY2 - data->MaskPosY;

  /* Assuming the operation is performed with mask, the mask 'clips' the source
     accordingly. The resulting valid area of the source in this case is: */
  int rSrcX1  = MAX( gSrcX1, gMaskX1 ) + data->SrcPosX;
  int rSrcY1  = MAX( gSrcY1, gMaskY1 ) + data->SrcPosY;
  int rSrcX2  = MIN( gSrcX2, gMaskX2 ) + data->SrcPosX;
  int rSrcY2  = MIN( gSrcY2, gMaskY2 ) + data->SrcPosY;

  /* The finally resulting area of the source surface to take in account. All
     pixel lying outside this area are considered as transparent. */
  int srcX1   = maskNI? rSrcX1 : data->SrcX1;
  int srcY1   = maskNI? rSrcY1 : data->SrcY1;
  int srcX2   = maskNI? rSrcX2 : data->SrcX2;
  int srcY2   = maskNI? rSrcY2 : data->SrcY2;

  /* The source area inclusive pixel to take in account during blur */
  int sx1     = MAX( bsx1, srcX1 );
  int sy1     = MAX( bsy1, srcY1 );
  int sx2     = MIN( bsx2, srcX2 );
  int sy2     = MIN( bsy2, srcY2 );

  /* Distances relative to the edges of the drawing destination when start the
     clamping */
  int cl      = data->BlurClampToEdges? aTask->X1 - data->DstX1 : blur;
  int ct      = data->BlurClampToEdges? aTask->Y1 - data->DstY1 : blur;
  int cr      = data->BlurClampToEdges? data->DstX2 - aTask->X1 : clpW + blur;
  int cb      = data->BlurClampToEdges? data->DstY2 - aTask->Y1 : clpH + blur;

  /* Size of the intermediate surface to store blurred rows/columns */
  #if ( EW_SURFACE_ROTATION == 0 ) || ( EW_SURFACE_ROTATION == 180 )
    int tmp1W = sy2 - sy1;
    int tmp1H = clpW;
    int tmp2W = data->SrcSurface->Width;
  #endif

  #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
    int tmp1W = clpH;
    int tmp1H = sx2 - sx1;
    int tmp2W = data->SrcSurface->Height;
  #endif

  /* Coordinates in the mask surface corresponding to the origin of the filter
     operation when drawing inside the intermediate surface */
  int mx1     = data->MaskPosX + aTask->X1 - data->DstX1;
  int my1     = data->MaskPosY + aTask->Y1 - data->DstY1;

  /* Nothing to do */
  if (( sy2 <= sy1 ) || ( sx2 <= sx1 ))
    return;

  /* Create a temporary surface to store the intermediate state of the blur
     operation in which the rows and columns are exchanged. See the size
     calculation above. Because of the blur effect the surface may be bigger
     than the clipping area to take in account the pixel rows intersecting the
     blur radius above/below the update area. */
  tmp1 = EwCreateSurface( EW_PIXEL_FORMAT_NATIVE, tmp1W, tmp1H, 0, 0, 0 );

  /* No memory for the temp. surface? */
  if ( !tmp1 )
  {
    EwError( 421 );
    return;
  }

  /* Create a scond temp. surface large enough to store a single pixel row of
     the source surface. This surface will be used as row-buffer for mask/tint
     filter operation */
  tmp2 = EwCreateSurface( EW_PIXEL_FORMAT_NATIVE, tmp2W, 1, 0, 0, 0 );

  /* No memory for the temp. surface? */
  if ( !tmp2 )
  {
    EwFreeSurface( tmp1 );
    EwError( 422 );
    return;
  }

  /* Obtain direct access to the surface memory */
  dst = LockDstSurface( tmp1 );

  /* No direct access to the surface memory */
  if ( !dst || !src || ( !mask && data->MaskSurface ))
  {
    LockDstSurface( 0 );
    EwFreeSurface( tmp1 );
    EwFreeSurface( tmp2 );
    return;
  }

  /* Also obtain access to the aux. surface */
  if ( !EwLockSurface( tmp2, 0, 0, tmp2->Width, tmp2->Height, 0, 256,
                       EW_LOCK_PIXEL_READ_WRITE | EW_LOCK_DONT_WAIT, &aux ))
  {
    LockDstSurface( 0 );
    EwFreeSurface( tmp1 );
    EwFreeSurface( tmp2 );
    return;
  }

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "FilterSurface( 0x%p, ( %d, %d )-( %d, %d )=( %d x %d ), %s ) SW\n",
               data->SrcSurface, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, 
               clpH, (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  EwStartPerfCounter( EwGfxFilter );

  /* Prepare the color as XGradient structure */
  EwInitSingleColorGradient( data->Color, &gradient );

  /* Pre-initialize the aux. buffer */
  EwZero( aux.Memory.Pixel1, tmp2W * aux.Memory.Pitch1X );

  /* Run the software pixel driver for the first phase of the blur effect. Here 
     the rows from the source are blured and stored in the intermediate surface
     tmp. Please note, depending on how the real surface content is orientend the
     coordinates need to be adapted. */
  #if EW_SURFACE_ROTATION == 0
    EwEmulateMaskTintBlurFilter( dst, src, mask, &aux.Memory,
      0, 0,
      tmp1W, tmp1H,
      csx1,
      sy1,
      sx1,
      sx2,
      mx1,
      my1 - ( csy1 - sy1 ),
      data->MaskX1, data->MaskY1,
      data->MaskX2, data->MaskY2,
      data->MaskInverted,
      &gradient,
      (int)( data->Intensity * 255.0f ),
      cl,
      cr,
      aRadius,
      CopyOnlyWorkers[ aFuncNo0 ],
      MaskTintWorkers[ aFuncNo1 ], MaskTintWorkers[ aFuncNo2 ],
      BlurWorkers[ aFuncNo3 ], BlurWorkers[ aFuncNo4 ]);
  #endif

  #if EW_SURFACE_ROTATION == 90
    EwEmulateMaskTintBlurFilter( dst, src, mask, &aux.Memory,
      0, 0,
      tmp1H, tmp1W,
      srcH - csy2,
      sx1,
      srcH - sy2, srcH - sy1,
      maskH - my1 - clpH,
      mx1 - ( csx1 - sx1 ),
      maskH - data->MaskY2, data->MaskX1,
      maskH - data->MaskY1, data->MaskX2,
      data->MaskInverted,
      &gradient,
      (int)( data->Intensity * 255.0f ),
      cb - clpH,
      ct + clpH,
      aRadius,
      CopyOnlyWorkers[ aFuncNo0 ],
      MaskTintWorkers[ aFuncNo1 ], MaskTintWorkers[ aFuncNo2 ],
      BlurWorkers[ aFuncNo3 ], BlurWorkers[ aFuncNo4 ]);
  #endif

  #if EW_SURFACE_ROTATION == 180
    EwEmulateMaskTintBlurFilter( dst, src, mask, &aux.Memory,
      0, 0,
      tmp1W, tmp1H,
      srcW - csx1 - tmp1H,
      srcH - sy1  - tmp1W,
      srcW - sx2,
      srcW - sx1,
      maskW - mx1 - tmp1H,
      maskH - my1 + ( csy1 - sy1 ) - tmp1W,
      maskW - data->MaskX2, maskH - data->MaskY2,
      maskW - data->MaskX1, maskH - data->MaskY1,
      data->MaskInverted,
      &gradient,
      (int)( data->Intensity * 255.0f ),
      cl,
      cr,
      aRadius,
      CopyOnlyWorkers[ aFuncNo0 ],
      MaskTintWorkers[ aFuncNo1 ], MaskTintWorkers[ aFuncNo2 ],
      BlurWorkers[ aFuncNo3 ], BlurWorkers[ aFuncNo4 ]);
  #endif

  #if EW_SURFACE_ROTATION == 270
    EwEmulateMaskTintBlurFilter( dst, src, mask, &aux.Memory,
      0, 0,
      tmp1H, tmp1W,
      csy1,
      srcW - sx2,
      data->SrcY1, data->SrcY2,
      my1,
      maskW - mx1 - ( sx2 - csx2 ) - clpW,
      data->MaskY1, maskW - data->MaskX2,
      data->MaskY2, maskW - data->MaskX1,
      data->MaskInverted,
      &gradient,
      (int)( data->Intensity * 255.0f ),
      ct,
      cb,
      aRadius,
      CopyOnlyWorkers[ aFuncNo0 ],
      MaskTintWorkers[ aFuncNo1 ], MaskTintWorkers[ aFuncNo2 ],
      BlurWorkers[ aFuncNo3 ], BlurWorkers[ aFuncNo4 ]);
  #endif

  /* The aux. surface is not needed anymore */
  EwUnlockSurface( tmp2, &aux );
  EwFreeSurface( tmp2 );

  /* Prepare for the second phase where the contents from the intermediate
     surface are blured column-wise and stored in the final destination */
  src = LockSrcSurface( tmp1 );
  dst = LockDstSurface( aDst );

  /* Run the software pixel driver for the second phase of the blur effect. Here 
     the content of the intermediate surface tmp is blured column-wise. Please
     note, depending on how the real surface content is orientend the coordinates
     need to be adapted. */
  #if EW_SURFACE_ROTATION == 0
    EwEmulateBlurFilter( dst, src, 
      aTask->X1, aTask->Y1,
      clpW, clpH,
      csy1 - sy1,
      0,
      0,
      tmp1W,
      ct,
      cb,
      aRadius,
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      BlurWorkers[ aFuncNo5 ]);
  #endif

  #if EW_SURFACE_ROTATION == 90
    EwEmulateBlurFilter( dst, src, 
      aDst->Height - aTask->Y2, aTask->X1,
      clpH, clpW,
      csx1 - sx1,
      0,
      0,
      tmp1H,
      cl,
      cr,
      aRadius,
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      BlurWorkers[ aFuncNo5 ]);
  #endif

  #if EW_SURFACE_ROTATION == 180
    EwEmulateBlurFilter( dst, src, 
      aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
      clpW, clpH,
      tmp1W - ( csy1 - sy1 ) - clpH,
      0,
      0,
      tmp1W,
      cb - clpH,
      ct + clpH,
      aRadius,
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      BlurWorkers[ aFuncNo5 ]);
  #endif

  #if EW_SURFACE_ROTATION == 270
    EwEmulateBlurFilter( dst, src, 
      aTask->Y1, aDst->Width - aTask->X2,
      clpH, clpW,
      sx2 - csx2,
      0,
      0,
      tmp1H,
      cr - clpW,
      cl + clpW,
      aRadius,
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      BlurWorkers[ aFuncNo5 ]);
  #endif

  EwStopPerfCounter( EwGfxFilter );

  /* The temporary surface is not needed anymore. Unlock and release. */
  LockSrcSurface( 0 );
  EwFreeSurface( tmp1 );
}


/* This helper function maps the 'filter' task to the software emulated pixel
   driver. This function performs the complex filter operation composed of
   blur filter and the following mask/tint filter. The parameter aFuncNoX are
   responsable for selecting the appropriate worker functions. Following is the
   meaning of the functions:
   aFuncNo1 - Worker used to blur between the source and NATIVE surface. If
     source is ALPHA8, the worker should blur between two ALPHA8 surfaces.
   aFuncNo2 - Worker used to blur between two NATIVE surfaces. If source is
     ALPHA8, the worker should blur between two ALPHA8 surfaces.
   aFuncNo3 - Worker used to blur between NATIVE and the destination surface.
   aFuncNo4 - Worker used to mask and evtl. tint between a NATIVE surface and
     the destination surface. If source is ALPHA8, the worker should operate
     on ALPHA8 surface as source.
   aFuncNo5 - Worker used to tint only between a NATIVE surface and the
     destination surface. If source is ALPHA8, the worker should operate on
     ALPHA8 surface as source.
   aFuncNo6 - Copy-Worker to transfer the results into the destination surface
     by exchanging rows with columns. */
static void Filter5( XSurface* aDst, XTask* aTask, int aFuncNo1, int aFuncNo2,
  int aFuncNo3, int aFuncNo4, int aFuncNo5, int aFuncNo6, int aRadius )
{
  XFilterSurface*  data   = (XFilterSurface*)aTask->Data;
  int              clpW   = aTask->X2 - aTask->X1;
  int              clpH   = aTask->Y2 - aTask->Y1;
  int              blur   = data->BlurRadius;
  XSurfaceMemory*  src    = LockSrcSurface ( data->SrcSurface );
  XSurfaceMemory*  mask   = LockMaskSurface( data->MaskSurface );
  XSurfaceMemory*  dst;
  XSurfaceLock     aux;
  XSurface*        tmp1;
  XSurface*        tmp2;
  XGradient        gradient;

  #if ( EW_SURFACE_ROTATION == 180 ) || ( EW_SURFACE_ROTATION == 270 )
    int            maskW = data->MaskSurface? data->MaskSurface->Width  : 0;
    int            srcW  = data->SrcSurface->Width;
  #endif
  #if ( EW_SURFACE_ROTATION == 180 ) || ( EW_SURFACE_ROTATION == 90 )
    int            maskH = data->MaskSurface? data->MaskSurface->Height : 0;
    int            srcH  = data->SrcSurface->Height;
  #endif

  /* Coordinates in source surface at the edges of the drawing area */
  int csx1    = data->SrcPosX + aTask->X1 - data->DstX1;
  int csy1    = data->SrcPosY + aTask->Y1 - data->DstY1;
  int csx2    = csx1 + clpW;
  int csy2    = csy1 + clpH;

  /* Since the blur is used, we need more of the source surface to process.
     The algorithm will read the source pixel beyond the edges of the drawing
     destination */
  int bsx1    = csx1 - blur;
  int bsy1    = csy1 - blur;
  int bsx2    = csx2 + blur;
  int bsy2    = csy2 + blur;

  /* The source area inclusive pixel to take in account during blur */
  int sx1     = MAX( bsx1, data->SrcX1 );
  int sy1     = MAX( bsy1, data->SrcY1 );
  int sx2     = MIN( bsx2, data->SrcX2 );
  int sy2     = MIN( bsy2, data->SrcY2 );

  /* Distances relative to the edges of the drawing destination when start the
     clamping */
  int cl      = data->BlurClampToEdges? aTask->X1 - data->DstX1 : blur;
  int ct      = data->BlurClampToEdges? aTask->Y1 - data->DstY1 : blur;
  int cr      = data->BlurClampToEdges? data->DstX2 - aTask->X1 : clpW + blur;
  int cb      = data->BlurClampToEdges? data->DstY2 - aTask->Y1 : clpH + blur;

  /* Size of the intermediate surface to store blurred rows/columns */
  #if ( EW_SURFACE_ROTATION == 0 ) || ( EW_SURFACE_ROTATION == 180 )
    int tmp1W = sy2 - sy1;
    int tmp1H = clpW;
    int tmp2W = aDst->Height;
  #endif

  #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
    int tmp1W = clpH;
    int tmp1H = sx2 - sx1;
    int tmp2W = aDst->Width;
  #endif

  /* Coordinates in the mask surface corresponding to the origin of the filter
     operation when drawing inside the intermediate surface */
  int mx1     = data->MaskPosX + aTask->X1 - data->DstX1;
  int my1     = data->MaskPosY + aTask->Y1 - data->DstY1;

  /* Nothing to do */
  if (( sy2 <= sy1 ) || ( sx2 <= sx1 ))
    return;

  /* Create a temporary surface to store the intermediate state of the blur
     operation in which the rows and columns are exchanged. See the size
     calculation above. Because of the blur effect the surface may be bigger
     than the clipping area to take in account the pixel rows intersecting the
     blur radius above/below the update area. Note the special case of ALPHA8
     operation. In such case the intermediate surface should also be ALPHA8. */
  tmp1 = EwCreateSurface(( aFuncNo1 == 4 )? 
                           EW_PIXEL_FORMAT_ALPHA8 : EW_PIXEL_FORMAT_NATIVE,
                           tmp1W, tmp1H, 0, 0, 0 );

  /* No memory for the temp. surface? */
  if ( !tmp1 )
  {
    EwError( 423 );
    return;
  }

  /* Create a scond temp. surface large enough to store a single pixel column of
     the destination surface. This surface will be used as buffer for mask/tint
     filter operation during the last stage of the blur/mask/tint filter */
  tmp2 = EwCreateSurface(( aFuncNo1 == 4 )? 
                           EW_PIXEL_FORMAT_ALPHA8 : EW_PIXEL_FORMAT_NATIVE,
                           tmp2W, 1, 0, 0, 0 );

  /* No memory for the temp. surface? */
  if ( !tmp2 )
  {
    EwFreeSurface( tmp1 );
    EwError( 424 );
    return;
  }

  /* Obtain direct access to the surface memory */
  dst = LockDstSurface( tmp1 );

  /* No direct access to the surface memory */
  if ( !dst || !src || ( !mask && data->MaskSurface ))
  {
    LockDstSurface( 0 );
    EwFreeSurface( tmp1 );
    EwFreeSurface( tmp2 );
    return;
  }

  /* Also obtain access to the aux. surface */
  if ( !EwLockSurface( tmp2, 0, 0, tmp2->Width, tmp2->Height, 0, 256,
                       EW_LOCK_PIXEL_READ_WRITE | EW_LOCK_DONT_WAIT, &aux ))
  {
    LockDstSurface( 0 );
    EwFreeSurface( tmp1 );
    EwFreeSurface( tmp2 );
    return;
  }

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "FilterSurface( 0x%p, ( %d, %d )-( %d, %d )=( %d x %d ), %s ) SW\n",
               data->SrcSurface, aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, 
               clpH, (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  EwStartPerfCounter( EwGfxFilter );

  /* Prepare the color as XGradient structure */
  EwInitSingleColorGradient( data->Color, &gradient );

  /* Pre-initialize the aux. buffer */
  EwZero( aux.Memory.Pixel1, tmp2W * aux.Memory.Pitch1X );

  /* Run the software pixel driver for the first phase of the blur effect. Here 
     the rows from the source are blured and stored in the intermediate surface
     tmp. Please note, depending on how the real surface content is orientend the
     coordinates need to be adapted. */
  #if EW_SURFACE_ROTATION == 0
    EwEmulateBlurFilter( dst, src, 
      0, 0,
      tmp1W, tmp1H,
      csx1,
      sy1,
      data->SrcX1,
      data->SrcX2,
      cl,
      cr,
      aRadius,
      255,
      0,
      BlurWorkers[ aFuncNo1 ]);
  #endif

  #if EW_SURFACE_ROTATION == 90
    EwEmulateBlurFilter( dst, src, 
      0, 0,
      tmp1H, tmp1W,
      srcH - csy2,
      sx1,
      srcH - data->SrcY2, srcH - data->SrcY1,
      cb - clpH,
      ct + clpH,
      aRadius,
      255,
      0,
      BlurWorkers[ aFuncNo1 ]);
  #endif

  #if EW_SURFACE_ROTATION == 180
    EwEmulateBlurFilter( dst, src, 
      0, 0,
      tmp1W, tmp1H,
      srcW - csx1 - tmp1H,
      srcH - sy1  - tmp1W,
      srcW - data->SrcX2,
      srcW - data->SrcX1,
      cr - tmp1H,
      cl + tmp1H,
      aRadius,
      255,
      0,
      BlurWorkers[ aFuncNo1 ]);
  #endif

  #if EW_SURFACE_ROTATION == 270
    EwEmulateBlurFilter( dst, src, 
      0, 0,
      tmp1H, tmp1W,
      csy1,
      srcW - sx2,
      data->SrcY1, data->SrcY2,
      ct,
      cb,
      aRadius,
      255,
      0,
      BlurWorkers[ aFuncNo1 ]);
  #endif

  /* Prepare for the second phase where the contents from the intermediate
     surface are blured column-wise, then masked/tinted and stored in the final
     destination */
  src = LockSrcSurface( tmp1 );
  dst = LockDstSurface( aDst );

  /* Run the software pixel driver for the second phase of the blur effect. Here 
     the rows from the intermediate surface are blured, masked/tinted and stored
     in the destination surface. Please note, depending on how the real surface
     content is orientend the coordinates need to be adapted. */
  #if EW_SURFACE_ROTATION == 0
    EwEmulateBlurMaskTintFilter( dst, src, mask, &aux.Memory,
      aTask->X1, aTask->Y1,
      clpW, clpH,
      csy1 - sy1,
      0,
      0,
      tmp1W,
      mx1,
      my1,
      data->MaskX1, data->MaskY1,
      data->MaskX2, data->MaskY2,
      data->MaskInverted,
      &gradient,
      (int)( data->Intensity * 255.0f ),
      ct,
      cb,
      aRadius,
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      BlurWorkers[ aFuncNo2 ],
      BlurWorkers[ aFuncNo3 ],
      MaskTintWorkers[ aFuncNo4 ],
      MaskTintWorkers[ aFuncNo5 ],
      NoFilterWorkers[ aFuncNo6 ]);
  #endif

  #if EW_SURFACE_ROTATION == 90
    EwEmulateBlurMaskTintFilter( dst, src, mask, &aux.Memory,
      aDst->Height - aTask->Y2, aTask->X1,
      clpH, clpW,
      csx1 - sx1,
      0,
      0,
      tmp1H,
      maskH - my1 - clpH,
      mx1,
      maskH - data->MaskY2, data->MaskX1,
      maskH - data->MaskY1, data->MaskX2,
      data->MaskInverted,
      &gradient,
      (int)( data->Intensity * 255.0f ),
      cl,
      cr,
      aRadius,
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      BlurWorkers[ aFuncNo2 ],
      BlurWorkers[ aFuncNo3 ],
      MaskTintWorkers[ aFuncNo4 ],
      MaskTintWorkers[ aFuncNo5 ],
      NoFilterWorkers[ aFuncNo6 ]);
  #endif

  #if EW_SURFACE_ROTATION == 180
    EwEmulateBlurMaskTintFilter( dst, src, mask, &aux.Memory,
      aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
      clpW, clpH,
      tmp1W - ( csy1 - sy1 ) - clpH,
      0,
      0,
      tmp1W,
      maskW - mx1 - clpW,
      maskH - my1 - clpH,
      maskW - data->MaskX2, maskH - data->MaskY2,
      maskW - data->MaskX1, maskH - data->MaskY1,
      data->MaskInverted,
      &gradient,
      (int)( data->Intensity * 255.0f ),
      cb - clpH,
      ct + clpH,
      aRadius,
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      BlurWorkers[ aFuncNo2 ],
      BlurWorkers[ aFuncNo3 ],
      MaskTintWorkers[ aFuncNo4 ],
      MaskTintWorkers[ aFuncNo5 ],
      NoFilterWorkers[ aFuncNo6 ]);
  #endif

  #if EW_SURFACE_ROTATION == 270
    EwEmulateBlurMaskTintFilter( dst, src, mask, &aux.Memory,
      aTask->Y1, aDst->Width - aTask->X2,
      clpH, clpW,
      sx2 - csx2,
      0,
      0,
      tmp1H,
      my1,
      maskW - mx1 - clpW,
      data->MaskY1, maskW - data->MaskX2,
      data->MaskY2, maskW - data->MaskX1,
      data->MaskInverted,
      &gradient,
      (int)( data->Intensity * 255.0f ),
      cr - clpW,
      cl + clpW,
      aRadius,
      data->Opacity,
      aTask->Flags & EW_TASK_ALPHABLEND,
      BlurWorkers[ aFuncNo2 ],
      BlurWorkers[ aFuncNo3 ],
      MaskTintWorkers[ aFuncNo4 ],
      MaskTintWorkers[ aFuncNo5 ],
      NoFilterWorkers[ aFuncNo6 ]);
  #endif

  EwStopPerfCounter( EwGfxFilter );

  /* The temporary surfaces are not needed anymore. Unlock and release. */
  EwUnlockSurface( tmp2, &aux );
  LockSrcSurface( 0 );
  EwFreeSurface( tmp1 );
  EwFreeSurface( tmp2 );
}

#endif /* !defined EW_DONT_USE_BLUR_FUNCTIONS && 
        ( !defined EW_DONT_USE_MASK_FUNCTIONS || 
          !defined EW_DONT_USE_TINT_FUNCTIONS ) */


/* Eliminate not needed code */
#if defined EW_NEED_DRIVER_TABLES && !defined EW_DONT_USE_PATH_FUNCTIONS

/* This helper function maps the 'fill polygon' task to the driver function of
   the underlying graphics subsystem. */
static void FillPolygon1( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XFillPolygon*   data    = (XFillPolygon*)aTask->Data;
  int*            paths   = (int*)( data + 1 );
  int             clpW    = aTask->X2 - aTask->X1;
  int             clpH    = aTask->Y2 - aTask->Y1;
  int             quality = aFuncNo & EW_TASK_HIGH_QUALITY;
  unsigned int*   colors  = data->Colors;

  #ifndef EW_DONT_USE_GRADIENTS
    unsigned int  interColors[4];
  #endif

  #if EW_SURFACE_ROTATION != 0
    int           noOfEdges;
  #endif

  /* First release any existing surface locks */
  LockDstSurface ( 0 );
  LockSrcSurface ( 0 );
  LockMaskSurface( 0 );

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "FillPolygon(( %d, %d )-( %d, %d )=( %d x %d ), %s )\n", 
               aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, clpH,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  /* Filling a clipped area of a gradient? Then interpolate the color values
     for the clipped edges before passing the call to the driver */
  #ifndef EW_DONT_USE_GRADIENTS
    if (
         ( aTask->Flags & EW_TASK_GRADIENT ) && 
         (
           ( aTask->X1 > data->DstX1 ) || ( aTask->Y1 > data->DstY1 ) ||
           ( aTask->X2 < data->DstX2 ) || ( aTask->Y2 < data->DstY2 )
         )
       )
    {
      int       x1 = aTask->X1 - data->DstX1;
      int       y1 = aTask->Y1 - data->DstY1;
      int       x2 = aTask->X2 - data->DstX1;
      int       y2 = aTask->Y2 - data->DstY1;
      XGradient gradient;

      /* Prepare the colors for the following operation */
      EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
        colors, &gradient );

      interColors[0] = EwGetColorFromGradient( &gradient, x1, y1 );
      interColors[1] = EwGetColorFromGradient( &gradient, x2, y1 );
      interColors[2] = EwGetColorFromGradient( &gradient, x2, y2 );
      interColors[3] = EwGetColorFromGradient( &gradient, x1, y2 );
      colors         = interColors;
    }
  
    /* If the filling operation with gradient should be performed and the surface
       content is rotated then the order of colors in the 'colors' array need
       an adaptation accordingly to the surface rotation. To do this the colors
       need to be transfered in an intermediate color array. This step can be
       avoided, however, when the intermediate array is already initialized in
       the preceding step. */
    if (( aTask->Flags & EW_TASK_GRADIENT ) && ( colors == data->Colors ))
    {
      interColors[0] = colors[0]; interColors[1] = colors[1];
      interColors[2] = colors[2]; interColors[3] = colors[3];
      colors         = interColors;
    }
  #endif

  EwStartPerfCounter( EwGfxFillPolygon );

  /* Invoke the external driver function to the underlying graphics subsystem.
     Please note, depending on how the real surface content is orientend the
     coordinates and the order of colors need to be adapted respectively. */
  #if EW_SURFACE_ROTATION == 0
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      PolygonDrivers[ aFuncNo ]( aDst->Handle, paths,
        aTask->X1,  aTask->Y1, 
        clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, quality, 
        data->NonZeroWinding, tmp );
    }
    #else
      PolygonDrivers[ aFuncNo ]( aDst->Handle, paths,
        aTask->X1,  aTask->Y1, 
        clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, quality, 
        data->NonZeroWinding, (unsigned long*)colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 90
    if ( colors != data->Colors )
    {
      unsigned int tmp = colors[0];
      colors[0] = colors[3]; colors[3] = colors[2];
      colors[2] = colors[1]; colors[1] = tmp;
    }    

    /* If the polygon coordinates are in wrong rotation - adapt them first before
       performing the operation */
    if ( data->Orientation != 90 )
    {
      while ( *paths > 0 )
        for ( noOfEdges = *paths++; noOfEdges >= 0; noOfEdges--, paths += 2 )
        {
          int x = paths[0];
          paths[0] = ( aDst->Height << 4 ) - paths[1]; 
          paths[1] = x;
        }

      /* The path data has been adapted */
      data->Orientation = 90;
      paths             = (int*)( data + 1 );
    }

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      PolygonDrivers[ aFuncNo ]( aDst->Handle, paths,
        aDst->Height - aTask->Y2, aTask->X1,
        clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, quality, 
        data->NonZeroWinding, tmp );
    }
    #else
      PolygonDrivers[ aFuncNo ]( aDst->Handle, paths,
        aDst->Height - aTask->Y2, aTask->X1,
        clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, quality, 
        data->NonZeroWinding, (unsigned long*)colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 180
    if ( colors != data->Colors )
    {
      unsigned int tmp1 = colors[0];
      unsigned int tmp2 = colors[1];
      colors[0] = colors[2]; colors[2] = tmp1;
      colors[1] = colors[3]; colors[3] = tmp2;
    }    

    /* If the polygon coordinates are in wrong rotation - adapt them first before
       performing the operation */
    if ( data->Orientation != 180 )
    {
      while ( *paths > 0 )
        for ( noOfEdges = *paths++; noOfEdges >= 0; noOfEdges--, paths += 2 )
        {
          paths[0] = ( aDst->Width  << 4 ) - paths[0]; 
          paths[1] = ( aDst->Height << 4 ) - paths[1]; 
        }

      /* The path data has been adapted */
      data->Orientation = 180;
      paths             = (int*)( data + 1 );
    }

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      PolygonDrivers[ aFuncNo ]( aDst->Handle, paths,
        aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
        clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, quality, 
        data->NonZeroWinding, tmp );
    }
    #else
      PolygonDrivers[ aFuncNo ]( aDst->Handle, paths,
        aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
        clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, quality, 
        data->NonZeroWinding, (unsigned long*)colors );
    #endif
  #endif

  #if EW_SURFACE_ROTATION == 270
    if ( colors != data->Colors )
    {
      unsigned int tmp = colors[0];
      colors[0] = colors[1]; colors[1] = colors[2];
      colors[2] = colors[3]; colors[3] = tmp;
    }    

    /* If the polygon coordinates are in wrong rotation - adapt them first before
       performing the operation */
    if ( data->Orientation != 270 )
    {
      while ( *paths > 0 )
        for ( noOfEdges = *paths++; noOfEdges >= 0; noOfEdges--, paths += 2 )
        {
          int y = paths[1];
          paths[1] = ( aDst->Width << 4 ) - paths[0]; 
          paths[0] = y;
        }

      /* The path data has been adapted */
      data->Orientation = 270;
      paths             = (int*)( data + 1 );
    }

    /* On 64-bit target convert the 32-bit color list to 64-bit colors */
    #if defined __LP64__ || defined _LP64
    {
      unsigned long tmp[4] = { colors[0], colors[1], colors[2], colors[3]};

      PolygonDrivers[ aFuncNo ]( aDst->Handle, paths,
        aTask->Y1, aDst->Width - aTask->X2,
        clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, quality, 
        data->NonZeroWinding, tmp );
    }
    #else
      PolygonDrivers[ aFuncNo ]( aDst->Handle, paths,
        aTask->Y1, aDst->Width - aTask->X2,
        clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, quality, 
        data->NonZeroWinding, (unsigned long*)colors );
    #endif
  #endif

  EwStopPerfCounter( EwGfxFillPolygon );
}

#endif /* EW_NEED_DRIVER_TABLES && !EW_DONT_USE_PATH_FUNCTIONS */


/* Eliminate unused code */
#ifndef EW_DONT_USE_PATH_FUNCTIONS

/* This helper function maps the 'fill polygon' task to the software emulated
   pixel driver. */
static void FillPolygon2( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XFillPolygon*    data    = (XFillPolygon*)aTask->Data;
  int*             paths   = (int*)( data + 1 );
  int              clpW    = aTask->X2 - aTask->X1;
  int              clpH    = aTask->Y2 - aTask->Y1;
  int              quality = aFuncNo & EW_TASK_HIGH_QUALITY;
  XSurfaceMemory*  dst     = LockDstSurface( aDst );
  XGradient        gradient;

  #if EW_SURFACE_ROTATION != 0
    unsigned int  interColors[4];
    unsigned int* colors = data->Colors;
    int           noOfEdges;
  #endif

  /* No direct access to the surface memory */
  if ( !dst )
    return;

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "FillPolygon(( %d, %d )-( %d, %d )=( %d x %d ), %s ) SW\n",
               aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, clpH,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  /* Antialiasing is not handled by the worker function */
  aFuncNo &= ~EW_TASK_HIGH_QUALITY;

  /* In case of vertical/horizontal only gradients, the rows/columns can be drawn
     with solid colors - no in-row interpolation is necessary. Select the faster
     (solid) version of the worker function. Note the special cases of rotated
     surface content. */
  #if ( EW_SURFACE_ROTATION == 0  ) || ( EW_SURFACE_ROTATION == 180 )
    if ( IS_LINEAR_GRADIENT( aTask->Flags ) && !IS_HORZ_GRADIENT( data->Colors ))
      aFuncNo += EW_TASK_SOLID - EW_TASK_LINEAR_GRADIENT;
  #endif

  #if ( EW_SURFACE_ROTATION == 90 ) || ( EW_SURFACE_ROTATION == 270 )
    if ( IS_LINEAR_GRADIENT( aTask->Flags ) && !IS_VERT_GRADIENT( data->Colors ))
      aFuncNo += EW_TASK_SOLID - EW_TASK_LINEAR_GRADIENT;
  #endif

  /* The function performs the drawing with an internal ALPHA8 surface */
  aFuncNo += EW_PIXEL_FORMAT_ALPHA8 * 8;

  EwStartPerfCounter( EwGfxFillPolygon );

  /* Run the software pixel driver. Please note, depending on how the real
     surface content is orientend the coordinates and the order of colors need
     to be adapted respectively. */
  #if EW_SURFACE_ROTATION == 0
    EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
      data->Colors, &gradient );

    EwEmulateFillPolygon( dst, paths,
      aTask->X1, aTask->Y1,
      clpW, clpH,
      quality, data->NonZeroWinding,
      &gradient, 
      aTask->X1 - data->DstX1, aTask->Y1 - data->DstY1,
      CopyWorkers[ aFuncNo ]); 
  #endif

  #if EW_SURFACE_ROTATION == 90
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[3]; interColors[1] = colors[0];
      interColors[2] = colors[1]; interColors[3] = colors[2];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstY2 - data->DstY1, data->DstX2 - data->DstX1,
      colors, &gradient );

    /* If the polygon coordinates are in wrong rotation - adapt them first before
       performing the operation */
    if ( data->Orientation != 90 )
    {
      while ( *paths > 0 )
        for ( noOfEdges = *paths++; noOfEdges >= 0; noOfEdges--, paths += 2 )
        {
          int x = paths[0];
          paths[0] = ( aDst->Height << 4 ) - paths[1]; 
          paths[1] = x;
        }

      /* The path data has been adapted */
      data->Orientation = 90;
      paths             = (int*)( data + 1 );
    }

    EwEmulateFillPolygon( dst, paths,
      aDst->Height - aTask->Y2, aTask->X1,
      clpH, clpW,
      quality, data->NonZeroWinding,
      &gradient, 
      -aTask->Y2 + data->DstY2, aTask->X1 - data->DstX1,
      CopyWorkers[ aFuncNo ]); 
  #endif

  #if EW_SURFACE_ROTATION == 180
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[2]; interColors[1] = colors[3];
      interColors[2] = colors[0]; interColors[3] = colors[1];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstX2 - data->DstX1, data->DstY2 - data->DstY1,
      colors, &gradient );

    /* If the polygon coordinates are in wrong rotation - adapt them first before
       performing the operation */
    if ( data->Orientation != 180 )
    {
      while ( *paths > 0 )
        for ( noOfEdges = *paths++; noOfEdges >= 0; noOfEdges--, paths += 2 )
        {
          paths[0] = ( aDst->Width  << 4 ) - paths[0]; 
          paths[1] = ( aDst->Height << 4 ) - paths[1]; 
        }

      /* The path data has been adapted */
      data->Orientation = 180;
      paths             = (int*)( data + 1 );
    }

    EwEmulateFillPolygon( dst, paths,
      aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
      clpW, clpH,
      quality, data->NonZeroWinding,
      &gradient, 
      -aTask->X2 + data->DstX2, -aTask->Y2 + data->DstY2,
      CopyWorkers[ aFuncNo ]); 
  #endif

  #if EW_SURFACE_ROTATION == 270
    if ( aTask->Flags & EW_TASK_GRADIENT )
    {
      interColors[0] = colors[1]; interColors[1] = colors[2];
      interColors[2] = colors[3]; interColors[3] = colors[0];
      colors         = interColors;
    }

    EwInitColorGradient( data->DstY2 - data->DstY1, data->DstX2 - data->DstX1,
      colors, &gradient );

    /* If the polygon coordinates are in wrong rotation - adapt them first before
       performing the operation */
    if ( data->Orientation != 270 )
    {
      while ( *paths > 0 )
        for ( noOfEdges = *paths++; noOfEdges >= 0; noOfEdges--, paths += 2 )
        {
          int y = paths[1];
          paths[1] = ( aDst->Width << 4 ) - paths[0]; 
          paths[0] = y;
        }

      /* The path data has been adapted */
      data->Orientation = 270;
      paths             = (int*)( data + 1 );
    }

    EwEmulateFillPolygon( dst, paths,
      aTask->Y1, aDst->Width - aTask->X2,
      clpH, clpW,
      quality, data->NonZeroWinding,
      &gradient, 
      aTask->Y1 - data->DstY1, -aTask->X2 + data->DstX2,
      CopyWorkers[ aFuncNo ]); 
  #endif

  EwStopPerfCounter( EwGfxFillPolygon );
}

#endif /* EW_DONT_USE_PATH_FUNCTIONS */


#if defined EW_NEED_DRIVER_TABLES && !defined EW_DONT_USE_GRADIENTS && \
   !defined EW_DONT_USE_PATH_FUNCTIONS

/* This helper function maps the 'fill polygon with gradient' task to the
   driver function of the underlying graphics subsystem. */
static void FillGradient1( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XFillGradient*  data    = (XFillGradient*)aTask->Data;
  XGradientStop*  stops   = data->Stops;
  int*            paths   = (int*)( stops + data->NoOfStops );
  int             clpW    = aTask->X2 - aTask->X1;
  int             clpH    = aTask->Y2 - aTask->Y1;
  int             quality = aFuncNo & 2;

  #if EW_SURFACE_ROTATION != 0
    int           noOfEdges;
  #endif

  /* First release any existing surface locks */
  LockDstSurface ( 0 );
  LockSrcSurface ( 0 );
  LockMaskSurface( 0 );

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "FillGradient(( %d, %d )-( %d, %d )=( %d x %d ), %s )\n", 
               aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, clpH,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  EwStartPerfCounter( EwGfxFillGradient );

  /* Invoke the external driver function to the underlying graphics subsystem.
     Please note, depending on how the real surface content is orientend the
     coordinates and the order of colors need to be adapted respectively. */
  #if EW_SURFACE_ROTATION == 0
    GradientDrivers[ aFuncNo ]( aDst->Handle, paths,
      aTask->X1,  aTask->Y1, 
      clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, quality, 
      data->NonZeroWinding,
      data->IsRadial,
      data->StartX, data->StartY,
      data->EndX,   data->EndY,
      data->Radius, data->Matrix,
      data->NoOfStops, data->Stops );
  #endif

  #if EW_SURFACE_ROTATION == 90
    /* If the polygon coordinates are in wrong rotation - adapt them first before
       performing the operation */
    if ( data->Orientation != 90 )
    {
      while ( *paths > 0 )
        for ( noOfEdges = *paths++; noOfEdges >= 0; noOfEdges--, paths += 2 )
        {
          int x = paths[0];
          paths[0] = ( aDst->Height << 4 ) - paths[1]; 
          paths[1] = x;
        }

      /* The path data has been adapted */
      data->Orientation = 90;
      paths             = (int*)( stops + data->NoOfStops );
    }

    GradientDrivers[ aFuncNo ]( aDst->Handle, paths,
      aDst->Height - aTask->Y2, aTask->X1,
      clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, quality, 
      data->NonZeroWinding,
      data->IsRadial,
      aDst->Height - data->StartY - 1, data->StartX,
      aDst->Height - data->EndY   - 1, data->EndX,
      data->Radius, data->Matrix,
      data->NoOfStops, data->Stops );
  #endif

  #if EW_SURFACE_ROTATION == 180
    /* If the polygon coordinates are in wrong rotation - adapt them first before
       performing the operation */
    if ( data->Orientation != 180 )
    {
      while ( *paths > 0 )
        for ( noOfEdges = *paths++; noOfEdges >= 0; noOfEdges--, paths += 2 )
        {
          paths[0] = ( aDst->Width  << 4 ) - paths[0]; 
          paths[1] = ( aDst->Height << 4 ) - paths[1]; 
        }

      /* The path data has been adapted */
      data->Orientation = 180;
      paths             = (int*)( stops + data->NoOfStops );
    }

    GradientDrivers[ aFuncNo ]( aDst->Handle, paths,
      aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
      clpW, clpH, aTask->Flags & EW_TASK_ALPHABLEND, quality, 
      data->NonZeroWinding,
      data->IsRadial,
      aDst->Width - data->StartX - 1, aDst->Height - data->StartY - 1,
      aDst->Width - data->EndX   - 1, aDst->Height - data->EndY   - 1,
      data->Radius, data->Matrix,
      data->NoOfStops, data->Stops );
  #endif

  #if EW_SURFACE_ROTATION == 270
    /* If the polygon coordinates are in wrong rotation - adapt them first before
       performing the operation */
    if ( data->Orientation != 270 )
    {
      while ( *paths > 0 )
        for ( noOfEdges = *paths++; noOfEdges >= 0; noOfEdges--, paths += 2 )
        {
          int y = paths[1];
          paths[1] = ( aDst->Width << 4 ) - paths[0]; 
          paths[0] = y;
        }

      /* The path data has been adapted */
      data->Orientation = 270;
      paths             = (int*)( stops + data->NoOfStops );
    }

    GradientDrivers[ aFuncNo ]( aDst->Handle, paths,
      aTask->Y1, aDst->Width - aTask->X2,
      clpH, clpW, aTask->Flags & EW_TASK_ALPHABLEND, quality, 
      data->NonZeroWinding,
      data->IsRadial,
      data->StartY, aDst->Width - data->StartX - 1,
      data->EndY,   aDst->Width - data->EndX   - 1,
      data->Radius, data->Matrix,
      data->NoOfStops, data->Stops );
  #endif

  EwStopPerfCounter( EwGfxFillGradient );
}

#endif /* EW_NEED_DRIVER_TABLES && EW_DONT_USE_GRADIENTS &&
          EW_DONT_USE_PATH_FUNCTIONS */


#if !defined EW_DONT_USE_GRADIENTS && !defined EW_DONT_USE_PATH_FUNCTIONS

/* This helper function maps the 'fill gradient' task to the software emulated
   pixel driver. */
static void FillGradient2( XSurface* aDst, XTask* aTask, int aFuncNo )
{
  XFillGradient*            data    = (XFillGradient*)aTask->Data;
  XGradientStop*            stops   = data->Stops;
  int*                      paths   = (int*)( stops + data->NoOfStops );
  int                       clpW    = aTask->X2 - aTask->X1;
  int                       clpH    = aTask->Y2 - aTask->Y1;
  int                       quality = aFuncNo & EW_TASK_HIGH_QUALITY;
  XSurfaceMemory*           dst     = LockDstSurface( aDst );
  XFillLinearGradientWorker worker1;
  XFillRadialGradientWorker worker2;

  #if EW_SURFACE_ROTATION != 0
    int           noOfEdges;
  #endif

  /* No direct access to the surface memory */
  if ( !dst )
    return;

  /* Track the drawing operations */
  #ifdef EW_SUPPORT_GFX_TASK_TRACING
    if ( EwPrintGfxTasks )
      EwPrint( "FillGradient(( %d, %d )-( %d, %d )=( %d x %d ), %s ) SW\n",
               aTask->X1, aTask->Y1, aTask->X2, aTask->Y2, clpW, clpH,
               (( aTask->Flags & EW_TASK_ALPHABLEND )? "BLEND" : "OVER" ));
  #endif

  /* Select the appropriate worker function */
  #ifdef EW_USE_PIXEL_FORMAT_SCREEN
    if ( aFuncNo > 32 )
      if ( aFuncNo & EW_TASK_ALPHABLEND )
      {
        worker1 = EwScreenFillLinearGradientRowBlend;
        worker2 = EwScreenFillRadialGradientRowBlend;
      }
      else
      {
        worker1 = EwScreenFillLinearGradientRow;
        worker2 = EwScreenFillRadialGradientRow;
      }
    else
  #endif
    if ( aFuncNo & EW_TASK_ALPHABLEND )
    {
      worker1 = EwFillLinearGradientRowBlend;
      worker2 = EwFillRadialGradientRowBlend;
    }
    else
    {
      worker1 = EwFillLinearGradientRow;
      worker2 = EwFillRadialGradientRow;
    }

  EwStartPerfCounter( EwGfxFillGradient );

  /* Run the software pixel driver. Please note, depending on how the real
     surface content is orientend the coordinates need to be adapted
     respectively. */
  #if EW_SURFACE_ROTATION == 0
    if ( data->IsRadial )
      EwEmulateFillRadialGradient( dst, paths,
        aTask->X1, aTask->Y1,
        clpW, clpH,
        quality, data->NonZeroWinding,
        data->StartX, data->StartY,
        data->Radius, data->Matrix,
        data->NoOfStops, data->Stops,
        worker2 ); 
    else
      EwEmulateFillLinearGradient( dst, paths,
        aTask->X1, aTask->Y1,
        clpW, clpH,
        quality, data->NonZeroWinding,
        data->StartX, data->StartY,
        data->EndX,   data->EndY,
        data->NoOfStops, data->Stops,
        worker1 ); 
  #endif

  #if EW_SURFACE_ROTATION == 90
    /* If the polygon coordinates are in wrong rotation - adapt them first before
       performing the operation */
    if ( data->Orientation != 90 )
    {
      while ( *paths > 0 )
        for ( noOfEdges = *paths++; noOfEdges >= 0; noOfEdges--, paths += 2 )
        {
          int x = paths[0];
          paths[0] = ( aDst->Height << 4 ) - paths[1]; 
          paths[1] = x;
        }

      /* The path data has been adapted */
      data->Orientation = 90;
      paths             = (int*)( stops + data->NoOfStops );
    }

    if ( data->IsRadial )
      EwEmulateFillRadialGradient( dst, paths,
        aDst->Height - aTask->Y2, aTask->X1,
        clpH, clpW,
        quality, data->NonZeroWinding,
        aDst->Height - data->StartY - 1, data->StartX,
        data->Radius,  data->Matrix,
        data->NoOfStops, data->Stops,
        worker2 ); 
    else
      EwEmulateFillLinearGradient( dst, paths,
        aDst->Height - aTask->Y2, aTask->X1,
        clpH, clpW,
        quality, data->NonZeroWinding,
        aDst->Height - data->StartY - 1, data->StartX,
        aDst->Height - data->EndY   - 1, data->EndX,
        data->NoOfStops, data->Stops,
        worker1 ); 
  #endif

  #if EW_SURFACE_ROTATION == 180
    /* If the polygon coordinates are in wrong rotation - adapt them first before
       performing the operation */
    if ( data->Orientation != 180 )
    {
      while ( *paths > 0 )
        for ( noOfEdges = *paths++; noOfEdges >= 0; noOfEdges--, paths += 2 )
        {
          paths[0] = ( aDst->Width  << 4 ) - paths[0]; 
          paths[1] = ( aDst->Height << 4 ) - paths[1]; 
        }

      /* The path data has been adapted */
      data->Orientation = 180;
      paths             = (int*)( stops + data->NoOfStops );
    }

    if ( data->IsRadial )
      EwEmulateFillRadialGradient( dst, paths,
        aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
        clpW, clpH,
        quality, data->NonZeroWinding,
        aDst->Width - data->StartX - 1, aDst->Height - data->StartY - 1,
        data->Radius, data->Matrix,
        data->NoOfStops, data->Stops,
        worker2 ); 
    else
      EwEmulateFillLinearGradient( dst, paths,
        aDst->Width - aTask->X2, aDst->Height - aTask->Y2,
        clpW, clpH,
        quality, data->NonZeroWinding,
        aDst->Width - data->StartX - 1, aDst->Height - data->StartY - 1,
        aDst->Width - data->EndX   - 1, aDst->Height - data->EndY   - 1,
        data->NoOfStops, data->Stops,
        worker1 ); 
  #endif

  #if EW_SURFACE_ROTATION == 270
    /* If the polygon coordinates are in wrong rotation - adapt them first before
       performing the operation */
    if ( data->Orientation != 270 )
    {
      while ( *paths > 0 )
        for ( noOfEdges = *paths++; noOfEdges >= 0; noOfEdges--, paths += 2 )
        {
          int y = paths[1];
          paths[1] = ( aDst->Width << 4 ) - paths[0]; 
          paths[0] = y;
        }

      /* The path data has been adapted */
      data->Orientation = 270;
      paths             = (int*)( stops + data->NoOfStops );
    }

    if ( data->IsRadial )
      EwEmulateFillRadialGradient( dst, paths,
        aTask->Y1, aDst->Width - aTask->X2,
        clpH, clpW,
        quality, data->NonZeroWinding,
        data->StartY, aDst->Width - data->StartX - 1,
        data->Radius, data->Matrix,
        data->NoOfStops, data->Stops,
        worker2 ); 
    else
      EwEmulateFillLinearGradient( dst, paths,
        aTask->Y1, aDst->Width - aTask->X2,
        clpH, clpW,
        quality, data->NonZeroWinding,
        data->StartY, aDst->Width - data->StartX - 1,
        data->EndY,   aDst->Width - data->EndX   - 1,
        data->NoOfStops,data->Stops,
        worker1 ); 
  #endif

  EwStopPerfCounter( EwGfxFillGradient );
}

#endif /* EW_DONT_USE_GRADIENTS && EW_DONT_USE_PATH_FUNCTIONS */


/* pba */
