/**
 * @file InfDevice.c
 * @brief Infusion Device Control Module (Message-based Implementation)
 *
 * This file implements the control and configuration logic for an infusion device.
 * Public API functions generate messages that are sent to a message queue. A dedicated
 * worker thread processes the queued messages based on the current device state.
 * The implementation supports commands for initialization, configuration (flow rate, VTBI,
 * and infusion time), starting, stopping, resuming, and various pause conditions (user-requested,
 * upstream/downstream pressure, and air-bubble detection).
 *
 * New modifications in this version:
 *   - A FreeRTOS timer "InfusionUpdateTimer" is created (in OFF mode) with a 1-second period.
 *   - A callback function vInfusionUpdateTimerCallback() is defined to update:
 *         - InfusionElapsedTimeInSecs
 *         - RemainingTimeInSecs
 *         - VolumeInfusedx100
 *         - And to adjust InfusionTimeInSecs based on VTBIx100 and FlowRatex100 (expectedTime = (3600 * VTBIx100) / FlowRatex100)
 *   - The timer is started when transitioning to the INFUSING state and stopped when leaving that state.
 *
 * @author  
 *         Radhakrishnan Rajaram
 * @company 
 *         Aria Innovations Pvt Ltd
 * @version 1.1
 * @date    2025-02-18 (modified: 2025-04-10)
 * @copyright Copyright (c) 2025 Aria Innovations Pvt Ltd. All rights reserved.
 *
 * @note This code is provided for demonstration purposes.
 */

#include "stddef.h"
#include "stdio.h"
#include "string.h"

#include "ewrte.h"
#include "ew_bsp_inout.h"
#include "ew_bsp_os.h"

#include "HwStepperCtrl.h"
#include "InfDevice.h"
#include "DoorHandler.h"
#include "timers.h"
#include "HwQuadEncoder.h"

/*===========================================================================
 * Macro Definitions
 *===========================================================================*/
#define INF_DEVICE_PPS_MIN (10)
#define INF_DEVICE_PPS_MAX (1000)
#define INF_DEVICE_TIME_IN_EACH_PPS (2) // 30 seconds in each pps

#define INF_DEVICE_FLOW_RATE_MIN_x100 (1)      /**< 0.01f * 100 */
#define INF_DEVICE_FLOW_RATE_MAX_x100 (120000)   /**< 1200 * 100 */

#define INF_DEVICE_VTBI_MIN_x100 (1000)          /**< 10.0f * 100 */
#define INF_DEVICE_VTBI_MAX_x100 (120000)          /**< 1200 * 100 */

#define INF_DEVICE_INFUSION_TIME_SECS_MIN (60)     /**< Minimum infusion time: 1 minute */
#define INF_DEVICE_INFUSION_TIME_SECS_MAX (86400)    /**< Maximum infusion time: 24 hours */

#define INF_DEVICE_SECS_PER_HOUR (3600)

#define INF_DEVICE_TASK_WAIT (1000)              /**< Task wait time in milliseconds */

#define INF_DEVICE_TIME_IN_EACH_PPS (2)            /**< Time in each PPS unit */

/*
 * PPS = 0.09333 x FLOWRATE, with 0.5 added for rounding.
 */
/*
 *#define INF_DEVICE_PPS_TO_FLOWRATE_CONST (2.2685f)
 *
 */
#define INF_DEVICE_PPS_TO_FLOWRATE_CONST (0.73958)
#define INF_DEVICE_CONVERT_FLOWRATE_TO_PPS(x) ( ( (((int)((float)(x) * INF_DEVICE_PPS_TO_FLOWRATE_CONST) + 0.5) / 100.0) ) )

/*===========================================================================
 * Type Definitions
 *===========================================================================*/

/**
 * @brief Enumeration of message types.
 */
typedef enum {
    INF_DEVICE_INIT              = 0x0001,
    INF_DEVICE_CFG_SET_VTBI      = 0x0002,
    INF_DEVICE_CFG_SET_FLOWRATE  = 0x0003,
    INF_DEVICE_CFG_SET_TIME      = 0x0004,
    INF_DEVICE_START             = 0x0005,
    INF_DEVICE_STOP              = 0x0006,
    INF_DEVICE_PAUSE_BY_USER     = 0x0007,
    INF_DEVICE_PAUSE_UPSTREAM    = 0x0008,
    INF_DEVICE_PAUSE_DOWNSTREAM  = 0x0009,
    INF_DEVICE_PAUSE_AIRBUBBLE   = 0x000A,
    INF_DEVICE_RESUME            = 0x000B,
    INF_DEVICE_MSG_MAX
} InfMessageType_t;

/**
 * @brief Structure representing a message.
 */
typedef struct {
    uint16_t msgType;    /**< Message type identifier. */
    uint8_t  data[8];    /**< Payload data for the message. */
} InfMessage_t;

/**
 * @brief Function pointer type for message handlers.
 */
typedef void (*InfMsgHandler_t)(InfMessage_t msg);

/**
 * @brief Enumeration for configuration modifications.
 */
typedef enum {
    CFG_NONE,
    CFG_FLOWRATE,
    CFG_VTBI,
    CFG_INFUSIONTIME
} InfCfgModified_t;

/*===========================================================================
 * Global and Static Variables
 *===========================================================================*/
static volatile int InfDeviceInitialized = 0;  /**< Flag indicating whether the device has been initialized. */

/**
 * @brief Structure holding configuration and runtime data for the infusion device.
 */
typedef struct {
    InfDeviceState_t State;                    /**< Current state of the infusion device. */
    unsigned long int FlowRatex100;              /**< Flow rate value multiplied by 100. */
    unsigned long int VTBIx100;                  /**< VTBI value multiplied by 100. */
    unsigned long int VolumeInfusedx100;         /**< Volume infused multiplied by 100. */
    unsigned long int RemainingTimeInSecs;       /**< Remaining infusion time in seconds. */
    unsigned long int InfusionTimeInSecs;        /**< Total infusion time in seconds. */
    unsigned long int InfusionElapsedTimeInSecs; /**< Elapsed infusion time in seconds. */
    unsigned long int PpsToStepperMotor;         /**< Calculated PPS for the stepper motor. */
    InfCfgModified_t  ModifiedParameter;         /**< Indicator of modified configuration parameter. */
} InfDevice_s;


static TimerHandle_t xInitTimer = NULL;
/* --- New Global Variable for the Infusion Update Timer --- */
/**
 * @brief FreeRTOS timer handle for updating infusion parameters every second.
 */
static TimerHandle_t xInfusionUpdateTimer = NULL;

/*===========================================================================
 * Forward Declarations for All State Machine Handlers
 *===========================================================================*/
static void InfDeviceWorkerThread( const void *arg );
/* (Existing forward declarations for state handlers follow) */

static void ProcessInitInInit(InfMessage_t msg);
static void ProcessCfgSetVTBIInInit(InfMessage_t msg);
static void ProcessCfgSetFlowRateInInit(InfMessage_t msg);
static void ProcessCfgSetTimeInInit(InfMessage_t msg);
static void ProcessStartInInit(InfMessage_t msg);
static void ProcessStopInInit(InfMessage_t msg);
static void ProcessPauseByUserInInit(InfMessage_t msg);
static void ProcessPauseUpstreamInInit(InfMessage_t msg);
static void ProcessPauseDownstreamInInit(InfMessage_t msg);
static void ProcessPauseAirbubbleInInit(InfMessage_t msg);
static void ProcessResumeInInit(InfMessage_t msg);

static void ProcessInitInSelfTest(InfMessage_t msg);
static void ProcessCfgSetVTBIInSelfTest(InfMessage_t msg);
static void ProcessCfgSetFlowRateInSelfTest(InfMessage_t msg);
static void ProcessCfgSetTimeInSelfTest(InfMessage_t msg);
static void ProcessStartInSelfTest(InfMessage_t msg);
static void ProcessStopInSelfTest(InfMessage_t msg);
static void ProcessPauseByUserInSelfTest(InfMessage_t msg);
static void ProcessPauseUpstreamInSelfTest(InfMessage_t msg);
static void ProcessPauseDownstreamInSelfTest(InfMessage_t msg);
static void ProcessPauseAirbubbleInSelfTest(InfMessage_t msg);
static void ProcessResumeInSelfTest(InfMessage_t msg);

static void ProcessInitInSelfTestFail(InfMessage_t msg);
static void ProcessCfgSetVTBIInSelfTestFail(InfMessage_t msg);
static void ProcessCfgSetFlowRateInSelfTestFail(InfMessage_t msg);
static void ProcessCfgSetTimeInSelfTestFail(InfMessage_t msg);
static void ProcessStartInSelfTestFail(InfMessage_t msg);
static void ProcessStopInSelfTestFail(InfMessage_t msg);
static void ProcessPauseByUserInSelfTestFail(InfMessage_t msg);
static void ProcessPauseUpstreamInSelfTestFail(InfMessage_t msg);
static void ProcessPauseDownstreamInSelfTestFail(InfMessage_t msg);
static void ProcessPauseAirbubbleInSelfTestFail(InfMessage_t msg);
static void ProcessResumeInSelfTestFail(InfMessage_t msg);

static void ProcessInitInIdle(InfMessage_t msg);
static void ProcessCfgSetVTBIInIdle(InfMessage_t msg);
static void ProcessCfgSetFlowRateInIdle(InfMessage_t msg);
static void ProcessCfgSetTimeInIdle(InfMessage_t msg);
static void ProcessStartInIdle(InfMessage_t msg);
static void ProcessStopInIdle(InfMessage_t msg);
static void ProcessPauseByUserInIdle(InfMessage_t msg);
static void ProcessPauseUpstreamInIdle(InfMessage_t msg);
static void ProcessPauseDownstreamInIdle(InfMessage_t msg);
static void ProcessPauseAirbubbleInIdle(InfMessage_t msg);
static void ProcessResumeInIdle(InfMessage_t msg);

static void ProcessInitInCfgSet(InfMessage_t msg);
static void ProcessCfgSetVTBIInCfgSet(InfMessage_t msg);
static void ProcessCfgSetFlowRateInCfgSet(InfMessage_t msg);
static void ProcessCfgSetTimeInCfgSet(InfMessage_t msg);
static void ProcessStartInCfgSet(InfMessage_t msg);
static void ProcessStopInCfgSet(InfMessage_t msg);
static void ProcessPauseByUserInCfgSet(InfMessage_t msg);
static void ProcessPauseUpstreamInCfgSet(InfMessage_t msg);
static void ProcessPauseDownstreamInCfgSet(InfMessage_t msg);
static void ProcessPauseAirbubbleInCfgSet(InfMessage_t msg);
static void ProcessResumeInCfgSet(InfMessage_t msg);

static void ProcessInitInInfusing(InfMessage_t msg);
static void ProcessCfgSetVTBIInInfusing(InfMessage_t msg);
static void ProcessCfgSetFlowRateInInfusing(InfMessage_t msg);
static void ProcessCfgSetTimeInInfusing(InfMessage_t msg);
static void ProcessStartInInfusing(InfMessage_t msg);
static void ProcessStopInInfusing(InfMessage_t msg);
static void ProcessPauseByUserInInfusing(InfMessage_t msg);
static void ProcessPauseUpstreamInInfusing(InfMessage_t msg);
static void ProcessPauseDownstreamInInfusing(InfMessage_t msg);
static void ProcessPauseAirbubbleInInfusing(InfMessage_t msg);
static void ProcessResumeInInfusing(InfMessage_t msg);

static void ProcessInitInPausedByUser(InfMessage_t msg);
static void ProcessCfgSetVTBIInPausedByUser(InfMessage_t msg);
static void ProcessCfgSetFlowRateInPausedByUser(InfMessage_t msg);
static void ProcessCfgSetTimeInPausedByUser(InfMessage_t msg);
static void ProcessStartInPausedByUser(InfMessage_t msg);
static void ProcessStopInPausedByUser(InfMessage_t msg);
static void ProcessResumeInPausedByUser(InfMessage_t msg);

static void ProcessInitInPausedUpStreamLow(InfMessage_t msg);
static void ProcessCfgSetVTBIInPausedUpStreamLow(InfMessage_t msg);
static void ProcessCfgSetFlowRateInPausedUpStreamLow(InfMessage_t msg);
static void ProcessCfgSetTimeInPausedUpStreamLow(InfMessage_t msg);
static void ProcessStartInPausedUpStreamLow(InfMessage_t msg);
static void ProcessStopInPausedUpStreamLow(InfMessage_t msg);
static void ProcessResumeInPausedUpStreamLow(InfMessage_t msg);

static void ProcessInitInPausedDownStreamLow(InfMessage_t msg);
static void ProcessCfgSetVTBIInPausedDownStreamLow(InfMessage_t msg);
static void ProcessCfgSetFlowRateInPausedDownStreamLow(InfMessage_t msg);
static void ProcessCfgSetTimeInPausedDownStreamLow(InfMessage_t msg);
static void ProcessStartInPausedDownStreamLow(InfMessage_t msg);
static void ProcessStopInPausedDownStreamLow(InfMessage_t msg);
static void ProcessResumeInPausedDownStreamLow(InfMessage_t msg);

static void ProcessInitInPausedUpStreamHigh(InfMessage_t msg);
static void ProcessCfgSetVTBIInPausedUpStreamHigh(InfMessage_t msg);
static void ProcessCfgSetFlowRateInPausedUpStreamHigh(InfMessage_t msg);
static void ProcessCfgSetTimeInPausedUpStreamHigh(InfMessage_t msg);
static void ProcessStartInPausedUpStreamHigh(InfMessage_t msg);
static void ProcessStopInPausedUpStreamHigh(InfMessage_t msg);
static void ProcessResumeInPausedUpStreamHigh(InfMessage_t msg);

static void ProcessInitInPausedDownStreamHigh(InfMessage_t msg);
static void ProcessCfgSetVTBIInPausedDownStreamHigh(InfMessage_t msg);
static void ProcessCfgSetFlowRateInPausedDownStreamHigh(InfMessage_t msg);
static void ProcessCfgSetTimeInPausedDownStreamHigh(InfMessage_t msg);
static void ProcessStartInPausedDownStreamHigh(InfMessage_t msg);
static void ProcessStopInPausedDownStreamHigh(InfMessage_t msg);
static void ProcessResumeInPausedDownStreamHigh(InfMessage_t msg);

static void ProcessInitInPausedAirbubble(InfMessage_t msg);
static void ProcessCfgSetVTBIInPausedAirbubble(InfMessage_t msg);
static void ProcessCfgSetFlowRateInPausedAirbubble(InfMessage_t msg);
static void ProcessCfgSetTimeInPausedAirbubble(InfMessage_t msg);
static void ProcessStartInPausedAirbubble(InfMessage_t msg);
static void ProcessStopInPausedAirbubble(InfMessage_t msg);
static void ProcessResumeInPausedAirbubble(InfMessage_t msg);

/*===========================================================================
 * Global Variables
 *===========================================================================*/

/**
 * @brief Global infusion device structure.
 */
static InfDevice_s InfDevice;

/**
 * @brief Global message queue handle.
 */
static QueueHandle_t xInfQueue = NULL;

/**
 * @brief Global worker thread handle.
 */
static volatile XThreadHandle InfWorkerThread = 0;

/**
 * @brief Macro to calculate flow rate from PPS.
 */
#define INF_DEVICE_CALC_FLOWRATE_FROM_PPS() ( ( ( float )( InfDevice.PpsToStepperMotor / INF_DEVICE_PPS_TO_FLOWRATE_CONST ) )

/**
 * @brief Function pointer table mapping [State][MessageType-1] to handler functions.
 * The second index (0 to 10) corresponds to:
 *  0: INIT,
 *  1: CFG_SET_VTBI,
 *  2: CFG_SET_FLOWRATE,
 *  3: CFG_SET_TIME,
 *  4: START,
 *  5: STOP,
 *  6: PAUSE_BY_USER,
 *  7: PAUSE_UPSTREAM,
 *  8: PAUSE_DOWNSTREAM,
 *  9: PAUSE_AIRBUBBLE,
 * 10: RESUME.
 */
InfMsgHandler_t InfProcessFuncTable[INF_DEVICE_STATE_MAX][ INF_DEVICE_MSG_MAX - 1 ] = {
    /* State: INIT */
    {
      ProcessInitInInit,
      ProcessCfgSetVTBIInInit,
      ProcessCfgSetFlowRateInInit,
      ProcessCfgSetTimeInInit,
      ProcessStartInInit,
      ProcessStopInInit,
      ProcessPauseByUserInInit,
      ProcessPauseUpstreamInInit,
      ProcessPauseDownstreamInInit,
      ProcessPauseAirbubbleInInit,
      ProcessResumeInInit
    },
    /* SELFTEST_INPROGRESS */
    {
      ProcessInitInSelfTest,
      ProcessCfgSetVTBIInSelfTest,
      ProcessCfgSetFlowRateInSelfTest,
      ProcessCfgSetTimeInSelfTest,
      ProcessStartInSelfTest,
      ProcessStopInSelfTest,
      ProcessPauseByUserInSelfTest,
      ProcessPauseUpstreamInSelfTest,
      ProcessPauseDownstreamInSelfTest,
      ProcessPauseAirbubbleInSelfTest,
      ProcessResumeInSelfTest
    },
    /* SELFTEST_FAILED */
    {
      ProcessInitInSelfTestFail,
      ProcessCfgSetVTBIInSelfTestFail,
      ProcessCfgSetFlowRateInSelfTestFail,
      ProcessCfgSetTimeInSelfTestFail,
      ProcessStartInSelfTestFail,
      ProcessStopInSelfTestFail,
      ProcessPauseByUserInSelfTestFail,
      ProcessPauseUpstreamInSelfTestFail,
      ProcessPauseDownstreamInSelfTestFail,
      ProcessPauseAirbubbleInSelfTestFail,
      ProcessResumeInSelfTestFail
    },
    /* IDLE */
    {
      ProcessInitInIdle,
      ProcessCfgSetVTBIInIdle,
      ProcessCfgSetFlowRateInIdle,
      ProcessCfgSetTimeInIdle,
      ProcessStartInIdle,
      ProcessStopInIdle,
      ProcessPauseByUserInIdle,
      ProcessPauseUpstreamInIdle,
      ProcessPauseDownstreamInIdle,
      ProcessPauseAirbubbleInIdle,
      ProcessResumeInIdle
    },
    /* CFG_SET */
    {
      ProcessInitInCfgSet,
      ProcessCfgSetVTBIInCfgSet,
      ProcessCfgSetFlowRateInCfgSet,
      ProcessCfgSetTimeInCfgSet,
      ProcessStartInCfgSet,
      ProcessStopInCfgSet,
      ProcessPauseByUserInCfgSet,
      ProcessPauseUpstreamInCfgSet,
      ProcessPauseDownstreamInCfgSet,
      ProcessPauseAirbubbleInCfgSet,
      ProcessResumeInCfgSet
    },
    /* INFUSING */
    {
      ProcessInitInInfusing,
      ProcessCfgSetVTBIInInfusing,
      ProcessCfgSetFlowRateInInfusing,
      ProcessCfgSetTimeInInfusing,
      ProcessStartInInfusing,
      ProcessStopInInfusing,
      ProcessPauseByUserInInfusing,
      ProcessPauseUpstreamInInfusing,
      ProcessPauseDownstreamInInfusing,
      ProcessPauseAirbubbleInInfusing,
      ProcessResumeInInfusing
    },
    /* PAUSED_BY_USER */
    {
      ProcessInitInPausedByUser,
      ProcessCfgSetVTBIInPausedByUser,
      ProcessCfgSetFlowRateInPausedByUser,
      ProcessCfgSetTimeInPausedByUser,
      ProcessStartInPausedByUser,
      ProcessStopInPausedByUser,
      NULL, /* PAUSE_BY_USER not allowed in PAUSED_BY_USER state */
      NULL,
      NULL,
      NULL,
      ProcessResumeInPausedByUser
    },
    /* PAUSED_UPSTREAM_PRESS_LOW */
    {
      ProcessInitInPausedUpStreamLow,
      ProcessCfgSetVTBIInPausedUpStreamLow,
      ProcessCfgSetFlowRateInPausedUpStreamLow,
      ProcessCfgSetTimeInPausedUpStreamLow,
      ProcessStartInPausedUpStreamLow,
      ProcessStopInPausedUpStreamLow,
      NULL,
      NULL,
      NULL,
      NULL,
      ProcessResumeInPausedUpStreamLow
    },
    /* PAUSED_DOWNSTREAM_PRESS_LOW */
    {
      ProcessInitInPausedDownStreamLow,
      ProcessCfgSetVTBIInPausedDownStreamLow,
      ProcessCfgSetFlowRateInPausedDownStreamLow,
      ProcessCfgSetTimeInPausedDownStreamLow,
      ProcessStartInPausedDownStreamLow,
      ProcessStopInPausedDownStreamLow,
      NULL,
      NULL,
      NULL,
      NULL,
      ProcessResumeInPausedDownStreamLow
    },
    /* PAUSED_UPSTREAM_PRESS_HIGH */
    {
      ProcessInitInPausedUpStreamHigh,
      ProcessCfgSetVTBIInPausedUpStreamHigh,
      ProcessCfgSetFlowRateInPausedUpStreamHigh,
      ProcessCfgSetTimeInPausedUpStreamHigh,
      ProcessStartInPausedUpStreamHigh,
      ProcessStopInPausedUpStreamHigh,
      NULL,
      NULL,
      NULL,
      NULL,
      ProcessResumeInPausedUpStreamHigh
    },
    /* PAUSED_DOWNSTREAM_PRESS_HIGH */
    {
      ProcessInitInPausedDownStreamHigh,
      ProcessCfgSetVTBIInPausedDownStreamHigh,
      ProcessCfgSetFlowRateInPausedDownStreamHigh,
      ProcessCfgSetTimeInPausedDownStreamHigh,
      ProcessStartInPausedDownStreamHigh,
      ProcessStopInPausedDownStreamHigh,
      NULL,
      NULL,
      NULL,
      NULL,
      ProcessResumeInPausedDownStreamHigh
    },
    /* PAUSED_AIRBUBBLE */
    {
      ProcessInitInPausedAirbubble,
      ProcessCfgSetVTBIInPausedAirbubble,
      ProcessCfgSetFlowRateInPausedAirbubble,
      ProcessCfgSetTimeInPausedAirbubble,
      ProcessStartInPausedAirbubble,
      ProcessStopInPausedAirbubble,
      NULL,
      NULL,
      NULL,
      NULL,
      ProcessResumeInPausedAirbubble
    }
};

/*===========================================================================
 * Helper Functions
 *===========================================================================*/
int Check_for_HomePosition()
{
    HwPQuadEncoderValues_s EcValues;

    // Initial read
    HwQuadEncoderRead(&EcValues);

    // Wait until encoder position reaches HOME_POSITION
    while (EcValues.Pos != 1)
    {
        HwQuadEncoderRead(&EcValues);
    }

    // Once reached, return success
    if (EcValues.Pos == 1)
        return 0;

    return -1;  // Should never reach here if loop works correctly
}

void SetHome_Position()
{
    int Hp_Set;
    int hwStpr;
    int dir;

    /* Initialize the Quad Encoder */
    HwQuadEncoderInit();

    /* Configure the Stepper Motor */
    hwStpr = HW_STEPPER_NUM_2;
    dir = HW_STEPPER_DIR_REV;

    HwStepperCtrlConfigure(hwStpr, dir, 10);

    /* Run the Stepper Motor  */
    HwStepperCtrlStart(hwStpr);

    /* Wait until home position is reached */
    Hp_Set = Check_for_HomePosition();
    if(Hp_Set == 0)
    {
        /* Stop the Stepper Motor if it reaches the Home Position */
        HwStepperCtrlStop(hwStpr);
    }
    else
    {
        EwPrint("Home Position not Set\r\n");
    }
}



/**
 * @brief Returns the string representation of the current device state.
 *
 * @param state  The current device state.
 * @return const char*  A string representing the state.
 */
static const char* GetStateName(InfDeviceState_t state)
{
    switch(state)
    {
        case INF_DEVICE_STATE_INIT: return "INIT";
        case INF_DEVICE_STATE_SELFTEST_INPROGRESS: return "SELFTEST_INPROGRESS";
        case INF_DEVICE_STATE_SELFTEST_FAILED: return "SELFTEST_FAILED";
        case INF_DEVICE_STATE_IDLE: return "IDLE";
        case INF_DEVICE_STATE_CFG_SET: return "CFG_SET";
        case INF_DEVICE_STATE_INFUSING: return "INFUSING";
        case INF_DEVICE_STATE_PAUSED_BYUSER: return "PAUSED_BY_USER";
        case INF_DEVICE_STATE_PAUSED_UPSTREAM_PRESS_LOW: return "PAUSED_UPSTREAM_PRESS_LOW";
        case INF_DEVICE_STATE_PAUSED_DOWNSTREAM_PRESS_LOW: return "PAUSED_DOWNSTREAM_PRESS_LOW";
        case INF_DEVICE_STATE_PAUSED_UPSTREAM_PRESS_HIGH: return "PAUSED_UPSTREAM_PRESS_HIGH";
        case INF_DEVICE_STATE_PAUSED_DOWNSTREAM_PRESS_HIGH: return "PAUSED_DOWNSTREAM_PRESS_HIGH";
        case INF_DEVICE_STATE_PAUSED_AIRBUBBLE: return "PAUSED_AIRBUBBLE";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Generic handler that prints a message indicating an invalid command.
 *
 * @param funcName  Name of the function that received the invalid command.
 */
static void GenericNotAllowedHandler(const char *funcName)
{
    //EwPrint("%s: Command not allowed in state %s.\n", funcName, GetStateName(InfDevice.State));
}

/*===========================================================================
 * New Code: Infusion Update Timer Callback
 *===========================================================================*/
/**
 * @brief Callback function for the InfusionUpdateTimer.
 *
 * This function is called every second when the timer is active. It updates the global
 * InfDevice structure with:
 *   - Incremented infusion elapsed time.
 *   - Adjusted infusion time (expected infusion time calculated from VTBI and FlowRate).
 *   - Updated remaining time.
 *   - Updated volume infused.
 *
 * If the volume infused (scaled by 100) is greater than or equal to VTBIx100 or if the
 * remaining time is 0, it posts an INF_DEVICE_STOP message to the device queue.
 *
 * @param xTimer The timer handle (unused).
 */
static void vInfusionUpdateTimerCallback(TimerHandle_t xTimer)
{
    /* Only update parameters if the device is in the INFUSING state */
    if (InfDevice.State == INF_DEVICE_STATE_INFUSING)
    {
        /* Increment elapsed infusion time */
        InfDevice.InfusionElapsedTimeInSecs++;

        /* Calculate expected total infusion time (in seconds) based on VTBI and FlowRate.
         * Use integer arithmetic; note that both parameters are scaled by 100.
         */
        if(InfDevice.FlowRatex100 != 0)
        {
            unsigned long int expectedTime = (3600UL * InfDevice.VTBIx100) / InfDevice.FlowRatex100;
            /* Adjust the infusion time if it does not match the computed expected time */
            if(InfDevice.InfusionTimeInSecs != expectedTime)
            {
                InfDevice.InfusionTimeInSecs = expectedTime;
                //EwPrint("vInfusionUpdateTimerCallback: Adjusted InfusionTimeInSecs to %lu seconds.\n", InfDevice.InfusionTimeInSecs);
            }
        }

        /* Update remaining time (ensure it does not go negative) */
        if (InfDevice.InfusionElapsedTimeInSecs < InfDevice.InfusionTimeInSecs)
        {
            InfDevice.RemainingTimeInSecs = InfDevice.InfusionTimeInSecs - InfDevice.InfusionElapsedTimeInSecs;
        }
        else
        {
            InfDevice.RemainingTimeInSecs = 0;
        }

        /* Calculate volume infused:
         * VolumeInfusedx100 = (FlowRatex100 * InfusionElapsedTimeInSecs) / 3600
         */
        InfDevice.VolumeInfusedx100 = (InfDevice.FlowRatex100 * InfDevice.InfusionElapsedTimeInSecs) / 3600;

        //EwPrint("Infusion update - Elapsed: %lu sec, Remaining: %lu sec, Volume Infused: %lu (x100)\n",
        //        InfDevice.InfusionElapsedTimeInSecs,
         //       InfDevice.RemainingTimeInSecs,
          //      InfDevice.VolumeInfusedx100);

        /* Check if infusion is complete:
         * If the volume infused is >= VTBI (both are scaled by 100) or remaining time is 0,
         * then post an INF_DEVICE_STOP message.
         */
        if ((InfDevice.VolumeInfusedx100 >= InfDevice.VTBIx100) || (InfDevice.RemainingTimeInSecs == 0))
        {
            InfMessage_t msgStop;
            msgStop.msgType = INF_DEVICE_STOP;
            memset(msgStop.data, 0, sizeof(msgStop.data));

            if (xInfQueue != NULL)
            {
                xQueueSend(xInfQueue, &msgStop, portMAX_DELAY);
                //EwPrint("vInfusionUpdateTimerCallback: Infusion complete, posted INF_DEVICE_STOP message.\n");
            }
        }
    }
}


/*===========================================================================
 * Public API Functions: Message Sending Interface
 *===========================================================================*/

/**
 * @brief Enqueues a message to the device message queue.
 *
 * @param msg  Pointer to the message to be enqueued.
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 */
static InfDeviceErrorCode_t SendMessage(InfMessage_t *msg)
{
    if(xQueueSend(xInfQueue, msg, portMAX_DELAY) != pdPASS)
    {
        return INFDEVICE_ERROR_UNKNOWN;
    }else
    {
     vTaskDelay( 50 );
    }
    return INFDEVICE_ERROR_NONE;
}

/**
 * @brief Callback function for the INIT soft timer.
 *
 * This callback is invoked when the soft timer expires. It creates an INIT message
 * and posts it to the infusion device message queue (xInfQueue).
 *
 * @param xTimer Timer handle (not used in this callback).
 */
static void vInitTimerCallback(TimerHandle_t xTimer)
{
    InfMessage_t msg;
    msg.msgType = INF_DEVICE_INIT;  /* Message type corresponding to "INIT" */
    memset(msg.data, 0, sizeof(msg.data)); // Clear data array if needed

    if (xInfQueue != NULL) {
        xQueueSend(xInfQueue, &msg, portMAX_DELAY);
        //EwPrint("vInitTimerCallback: INIT message posted to the queue.\n");
    }
}

/**
 * @brief Retrieves the current infusion device status.
 *
 * Updates the provided status pointer with parameters from the internal InfDevice structure.
 *
 * @param status Pointer to an InfusionStatus_t structure to be updated.
 * @return int16_t Returns 0 on success, or -1 if the pointer is NULL.
 */
int16_t InfDevice_GetStatus(InfusionStatus_t *status)
{
    if (status == NULL)
    {
        return INFDEVICE_ERROR_OPERATION_NOT_ALLOWED;  // Typically defined as -1 in your enum.
    }

    /* Copy values from the global internal structure. */
    status->FlowRatex100              = InfDevice.FlowRatex100;
    status->VTBIx100                  = InfDevice.VTBIx100;
    status->VolumeInfusedx100         = InfDevice.VolumeInfusedx100;
    status->RemainingTimeInSecs       = InfDevice.RemainingTimeInSecs;
    status->InfusionTimeInSecs        = InfDevice.InfusionTimeInSecs;
    status->InfusionElapsedTimeInSecs = InfDevice.InfusionElapsedTimeInSecs;

    /* Set fixed values for the other parameters. */
    status->OcculsionPressure = 9.0f;
    status->BolusRate         = 1200.00f;
    status->KVORate           = 0.01f;
    status->MaxFlowRate       = 1200.00f;
    status->AirLineSensitivity= 90;
    status->AlarmSetting      = 600;

    return 0;
}

/*===========================================================================
 * Public API Functions: Message Sending Interface
 *===========================================================================*/

/**
 * @brief Initializes the infusion device including self-test.
 *
 * This function initializes the hardware components, creates the message queue,
 * starts the worker thread, and then creates FreeRTOS soft timers.
 * In addition to the existing INIT timer (xInitTimer), it creates the
 * InfusionUpdateTimer which is set to fire every 1 second (auto-reload mode)
 * but is not started until the device enters the INFUSING state.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success (INFDEVICE_ERROR_NONE)
 *         or failure (INFDEVICE_ERROR_UNKNOWN).
 */
InfDeviceErrorCode_t InfDevice_InitWithSelfTest(void)
{
    InfDeviceErrorCode_t retErrorCode = INFDEVICE_ERROR_NONE;
    if(0 != HwStepperCtrlInit(HW_STEPPER_NUM_2))
    {
        retErrorCode = INFDEVICE_ERROR_UNKNOWN;
    }
    else
    {
        InfDevice.State = INF_DEVICE_STATE_INIT;
        xInfQueue = xQueueCreate(10, sizeof(InfMessage_t));
        if(xInfQueue == NULL)
        {
            printf("Error: Failed to create message queue.\n");
            for(;;);
        }

        /* --- Create the InfusionUpdateTimer in OFF mode (do not start yet) --- */
        xInfusionUpdateTimer = xTimerCreate("InfusionUpdateTimer",
                                             pdMS_TO_TICKS(1000),    /* Period: 1 second */
                                             pdTRUE,                 /* Auto-reload */
                                             (void *)0,
                                             vInfusionUpdateTimerCallback);
        if(xInfusionUpdateTimer == NULL)
        {
            //EwPrint("InfDevice_InitWithSelfTest: Failed to create InfusionUpdateTimer.\n");
        }
        else
        {
            //EwPrint("InfDevice_InitWithSelfTest: InfusionUpdateTimer created (currently off).\n");
        }

        InfWorkerThread = EwBspOsThreadCreate(InfDeviceWorkerThread, EW_BSP_OS_THREAD_PRIORITY_NORMAL, 4096, 0);
        if(InfWorkerThread == NULL)
        {
            retErrorCode = INFDEVICE_ERROR_UNKNOWN;
        }
        else
        {
            InfDeviceInitialized = 1;

            /* Create a FreeRTOS soft timer to post an INIT message after 200 ms */
            xInitTimer = xTimerCreate("InitTimer", pdMS_TO_TICKS(200), pdTRUE, (void *)0, vInitTimerCallback);
            if(xInitTimer != NULL)
            {
                xTimerStart(xInitTimer, 0);
                //EwPrint("InfDevice_InitWithSelfTest: INIT timer started.\n");
            }
            else
            {
                //EwPrint("InfDevice_InitWithSelfTest: Failed to create INIT timer.\n");
            }
          //  SetHome_Position( );
        }
    }
    return retErrorCode;
}

/**
 * @brief Sets the infusion flow rate.
 *
 * Configures the flow rate for the infusion process.
 *
 * @param FlowRate_f  Flow rate value in float.
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 */
InfDeviceErrorCode_t InfDevice_SetFlowRate(float FlowRate_f)
{
    InfMessage_t msg;
    msg.msgType = INF_DEVICE_CFG_SET_FLOWRATE;

    memcpy(msg.data, &FlowRate_f, sizeof(float));
    return SendMessage(&msg);
}

/**
 * @brief Sets the VTBI (Volume To Be Infused).
 *
 * Updates the VTBI parameter for the infusion device.
 *
 * @param VTBI_f  VTBI value in float.
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 */
InfDeviceErrorCode_t InfDevice_SetVTBI(float VTBI_f)
{
    InfMessage_t msg;
    msg.msgType = INF_DEVICE_CFG_SET_VTBI;
    memcpy(msg.data, &VTBI_f, sizeof(float));

    return SendMessage(&msg);
}

/**
 * @brief Sets the infusion time.
 *
 * Configures the total infusion time (in seconds) for the device.
 *
 * @param InfusionTimeInSecs  Infusion time in seconds.
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 */
InfDeviceErrorCode_t InfDevice_SetInfusionTime(int InfusionTimeInSecs)
{
    InfMessage_t msg;
    msg.msgType = INF_DEVICE_CFG_SET_TIME;
    memcpy(msg.data, &InfusionTimeInSecs, sizeof(int));

    return SendMessage(&msg);
}

/**
 * @brief Starts the infusion process.
 *
 * Sends a message to initiate the infusion process after configuration.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 */
InfDeviceErrorCode_t InfDevice_EvStart(void)
{
    InfMessage_t msg;
    msg.msgType = INF_DEVICE_START;
    return SendMessage(&msg);
}

/**
 * @brief Stops the infusion process.
 *
 * Sends a command to stop the ongoing infusion process.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 */
InfDeviceErrorCode_t InfDevice_EvStop(void)
{
    InfMessage_t msg;
    msg.msgType = INF_DEVICE_STOP;
    return SendMessage(&msg);
}

/**
 * @brief Resumes the infusion process.
 *
 * Resumes the infusion after it has been paused.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 */
InfDeviceErrorCode_t InfDevice_EvResume(void)
{
    InfMessage_t msg;
    msg.msgType = INF_DEVICE_RESUME;
    return SendMessage(&msg);
}

/**
 * @brief Pauses the infusion process as requested by the user.
 *
 * Sends a command to pause the infusion process due to a user request.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 */
InfDeviceErrorCode_t InfDevice_EvPauseByUser(void)
{
    InfMessage_t msg;
    msg.msgType = INF_DEVICE_PAUSE_BY_USER;
    return SendMessage(&msg);
}

/**
 * @brief Pauses the infusion process due to upstream pressure.
 *
 * Sends a command to pause the infusion process when upstream pressure is too low.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 */
InfDeviceErrorCode_t InfDevice_EvPauseUpstream(void)
{
    InfMessage_t msg;
    msg.msgType = INF_DEVICE_PAUSE_UPSTREAM;
    return SendMessage(&msg);
}

/**
 * @brief Pauses the infusion process due to downstream pressure.
 *
 * Sends a command to pause the infusion process when downstream pressure is too low.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 */
InfDeviceErrorCode_t InfDevice_EvPauseDownstream(void)
{
    InfMessage_t msg;
    msg.msgType = INF_DEVICE_PAUSE_DOWNSTREAM;
    return SendMessage(&msg);
}

/**
 * @brief Pauses the infusion process due to air-bubble detection.
 *
 * Sends a command to pause the infusion process when an air bubble is detected.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 */
InfDeviceErrorCode_t InfDevice_EvPauseAirbubble(void)
{
    InfMessage_t msg;
    msg.msgType = INF_DEVICE_PAUSE_AIRBUBBLE;
    return SendMessage(&msg);
}

/**
 * @brief Retrieves the current state of the infusion device.
 *
 * @return InfDeviceState_t  The current state of the device.
 */
InfDeviceState_t InfDevice_getState(void)
{
    return InfDevice.State;
}

/*===========================================================================
 * Worker Thread: Message Processing Loop
 *===========================================================================*/

/**
 * @brief Worker thread that processes incoming messages.
 *
 * This task continuously waits for messages on the queue and dispatches them to
 * the appropriate state machine handler based on the current device state.
 *
 * @param arg  Not used.
 */
static void InfDeviceWorkerThread(const void *arg)
{
    InfMessage_t receivedMsg;
    for(;;)
    {
        if(xQueueReceive(xInfQueue, &receivedMsg, INF_DEVICE_TASK_WAIT) == pdPASS)
        {
            uint16_t msgIndex = receivedMsg.msgType - 1; // Convert message type to index (0..10)
            if(msgIndex < (INF_DEVICE_MSG_MAX - 1) && InfDevice.State < INF_DEVICE_STATE_MAX)
            {
                InfMsgHandler_t handler = InfProcessFuncTable[InfDevice.State][msgIndex];
                if(handler != NULL)
                {
                    handler(receivedMsg);
                }
                else
                {
                    //EwPrint("No handler for message type %d in state %s.\n", receivedMsg.msgType, GetStateName(InfDevice.State));
                }
            }
            else
            {
                printf("Invalid message type or state.\n");
            }
        }
    }
}

/*===========================================================================
 * State Machine Handler Implementations
 * (Static functions below are used for internal state machine processing.)
 *===========================================================================*/

/* ----------------- State: INIT ----------------- */
static void ProcessInitInInit( InfMessage_t msg )
{
    //EwPrint("ProcessInitInInit: Transitioning from INIT to SELFTEST_INPROGRESS.\n");
    InfDevice.State = INF_DEVICE_STATE_SELFTEST_INPROGRESS;
}
static void ProcessCfgSetVTBIInInit( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessCfgSetVTBIInInit"); }
static void ProcessCfgSetFlowRateInInit( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessCfgSetFlowRateInInit"); }
static void ProcessCfgSetTimeInInit( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessCfgSetTimeInInit"); }
static void ProcessStartInInit( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessStartInInit"); }
static void ProcessStopInInit( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessStopInInit"); }
static void ProcessPauseByUserInInit( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseByUserInInit"); }
static void ProcessPauseUpstreamInInit( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseUpstreamInInit"); }
static void ProcessPauseDownstreamInInit( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseDownstreamInInit"); }
static void ProcessPauseAirbubbleInInit( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseAirbubbleInInit"); }
static void ProcessResumeInInit( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessResumeInInit"); }

/* ----------------- State: SELFTEST_INPROGRESS ----------------- */
static void ProcessInitInSelfTest( InfMessage_t msg )
{
    xTimerStop(xInitTimer, 0);
    //EwPrint("ProcessInitInSelfTest: Performing self-test...\n");

    //EwPrint("Self-test passed. Transitioning to IDLE.\n");
    InfDevice.State = INF_DEVICE_STATE_IDLE;
}
static void ProcessCfgSetVTBIInSelfTest( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessCfgSetVTBIInSelfTest"); }
static void ProcessCfgSetFlowRateInSelfTest( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessCfgSetFlowRateInSelfTest"); }
static void ProcessCfgSetTimeInSelfTest( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessCfgSetTimeInSelfTest"); }
static void ProcessStartInSelfTest( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessStartInSelfTest"); }
static void ProcessStopInSelfTest( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessStopInSelfTest"); }
static void ProcessPauseByUserInSelfTest( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseByUserInSelfTest"); }
static void ProcessPauseUpstreamInSelfTest( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseUpstreamInSelfTest"); }
static void ProcessPauseDownstreamInSelfTest( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseDownstreamInSelfTest"); }
static void ProcessPauseAirbubbleInSelfTest( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseAirbubbleInSelfTest"); }
static void ProcessResumeInSelfTest( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessResumeInSelfTest"); }

/* ----------------- State: SELFTEST_FAILED ----------------- */
static void ProcessInitInSelfTestFail( InfMessage_t msg ) { //EwPrint("SELFTEST_FAILED: Ignoring INIT.\n");
	}

static void ProcessCfgSetVTBIInSelfTestFail( InfMessage_t msg ) { //EwPrint("SELFTEST_FAILED: Cannot set VTBI.\n");
	}

static void ProcessCfgSetFlowRateInSelfTestFail( InfMessage_t msg ) { //EwPrint("SELFTEST_FAILED: Cannot set FlowRate.\n");
	}

static void ProcessCfgSetTimeInSelfTestFail( InfMessage_t msg ) { //EwPrint("SELFTEST_FAILED: Cannot set Infusion Time.\n");

}

static void ProcessStartInSelfTestFail( InfMessage_t msg ) { //EwPrint("SELFTEST_FAILED: Cannot start infusion.\n");
	}

static void ProcessStopInSelfTestFail( InfMessage_t msg ) { //EwPrint("SELFTEST_FAILED: Cannot stop infusion.\n");
	}

static void ProcessPauseByUserInSelfTestFail( InfMessage_t msg ) { //EwPrint("SELFTEST_FAILED: Cannot pause infusion.\n");
	}

static void ProcessPauseUpstreamInSelfTestFail( InfMessage_t msg ) { //EwPrint("SELFTEST_FAILED: Cannot pause infusion.\n");
	}

static void ProcessPauseDownstreamInSelfTestFail( InfMessage_t msg ) { //EwPrint("SELFTEST_FAILED: Cannot pause infusion.\n");
	}

static void ProcessPauseAirbubbleInSelfTestFail( InfMessage_t msg ) { //EwPrint("SELFTEST_FAILED: Cannot pause infusion.\n");
	}

static void ProcessResumeInSelfTestFail( InfMessage_t msg ) { //EwPrint("SELFTEST_FAILED: Cannot resume infusion.\n");

}

/* ----------------- State: IDLE ----------------- */
static void ProcessInitInIdle( InfMessage_t msg )
{
    //EwPrint("ProcessInitInIdle: Already in IDLE. Resetting parameters.\n");
    InfDevice.FlowRatex100 = 0;
    InfDevice.VTBIx100 = 0;
    InfDevice.InfusionTimeInSecs = 0;
    InfDevice.VolumeInfusedx100 = 0;
}
static void ProcessCfgSetVTBIInIdle( InfMessage_t msg )
{
    float vtbi = 0.0f;
    memcpy(&vtbi, msg.data, sizeof(float));
    InfDevice.VTBIx100 = (unsigned long int)(vtbi * 100);
    InfDevice.ModifiedParameter = CFG_VTBI;
    //EwPrint("ProcessCfgSetVTBIInIdle: VTBI = %f (stored %lu).\n", vtbi, InfDevice.VTBIx100);
    InfDevice.State = INF_DEVICE_STATE_CFG_SET;
}
static void ProcessCfgSetFlowRateInIdle( InfMessage_t msg )
{
    float flowRate = 0.0f;
    memcpy(&flowRate, msg.data, sizeof(float));
    InfDevice.FlowRatex100 = (unsigned long int)(flowRate * 100);
    InfDevice.ModifiedParameter = CFG_FLOWRATE;
    //EwPrint("ProcessCfgSetFlowRateInIdle: FlowRate = %f (stored %lu).\n", flowRate, InfDevice.FlowRatex100);
    InfDevice.State = INF_DEVICE_STATE_CFG_SET;
}
static void ProcessCfgSetTimeInIdle( InfMessage_t msg )
{
    unsigned long int infusionTime = 0;
    memcpy(&infusionTime, msg.data, sizeof(unsigned long int));
    InfDevice.InfusionTimeInSecs = infusionTime;
    InfDevice.ModifiedParameter = CFG_INFUSIONTIME;
    //EwPrint("ProcessCfgSetTimeInIdle: InfusionTime = %lu seconds.\n", infusionTime);
    InfDevice.State = INF_DEVICE_STATE_CFG_SET;
}
static void ProcessStartInIdle( InfMessage_t msg )
{
//	uint32_t pps;
    if(InfDevice.FlowRatex100 != 0)
    {


        //EwPrint("ProcessStartInCfgSet: Sending door close command...\n");
#warning "Door Close to be enabled in Actual Build"
#if 1
        DoorHandlerSendFullCloseMessage();


        while(1)
        {
           vTaskDelay(pdMS_TO_TICKS(200));
            if(DoorHandlerGetState() == DOOR_STATE_CLOSED)
                break;
        }
#endif
        InfDevice.PpsToStepperMotor = INF_DEVICE_CONVERT_FLOWRATE_TO_PPS(InfDevice.FlowRatex100);
        EwPrint(" PPS To Inf. Stepper Motor %d\r\n ", InfDevice.PpsToStepperMotor );
		 HwStepperCtrlConfigure(HW_STEPPER_NUM_2, HW_STEPPER_DIR_FWD, InfDevice.PpsToStepperMotor);
		 HwStepperCtrlStart(HW_STEPPER_NUM_2);


        InfDevice.State = INF_DEVICE_STATE_INFUSING;
        InfDevice.InfusionElapsedTimeInSecs = 0;
        //EwPrint("ProcessStartInCfgSet: Transitioning to INFUSING.\n");

        /* Start the InfusionUpdateTimer now that infusion is active */
        if(xInfusionUpdateTimer != NULL)
        {
            xTimerStart(xInfusionUpdateTimer, 0);
        }
    }
    else
    {
        //EwPrint("ProcessStartInCfgSet: FlowRate not set.\n");
    }
}
static void ProcessStopInIdle( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessStopInIdle"); }
static void ProcessPauseByUserInIdle( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseByUserInIdle"); }
static void ProcessPauseUpstreamInIdle( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseUpstreamInIdle"); }
static void ProcessPauseDownstreamInIdle( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseDownstreamInIdle"); }
static void ProcessPauseAirbubbleInIdle( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseAirbubbleInIdle"); }
static void ProcessResumeInIdle( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessResumeInIdle"); }

/* ----------------- State: CFG_SET ----------------- */
static void ProcessInitInCfgSet( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessInitInCfgSet"); }
static void ProcessCfgSetVTBIInCfgSet( InfMessage_t msg ) { ProcessCfgSetVTBIInIdle(msg); }
static void ProcessCfgSetFlowRateInCfgSet( InfMessage_t msg ) { ProcessCfgSetFlowRateInIdle(msg); }
static void ProcessCfgSetTimeInCfgSet( InfMessage_t msg ) { ProcessCfgSetTimeInIdle(msg); }

/**
 * @brief Handler for START in CFG_SET.
 *
 * When a START message is received in CFG_SET state:
 *   - If the flow rate is set, the door is closed and the stepper motor is configured.
 *   - The state transitions to INFUSING.
 *   - Elapsed infusion time is reset.
 *   - The InfusionUpdateTimer is started.
 */
static void ProcessStartInCfgSet( InfMessage_t msg )
{
//	uint32_t pps;
    if(InfDevice.FlowRatex100 != 0)
    {



        //EwPrint("ProcessStartInCfgSet: Sending door close command...\n");
#warning "Door Close to be enabled in Actual Build"
#if 1
        DoorHandlerSendFullCloseMessage();


        while(1)
        {
           vTaskDelay(pdMS_TO_TICKS(200));
            if(DoorHandlerGetState() == DOOR_STATE_CLOSED)
                break;
        }
#endif
        InfDevice.PpsToStepperMotor = INF_DEVICE_CONVERT_FLOWRATE_TO_PPS(InfDevice.FlowRatex100);
        EwPrint(" PPS To Inf. Stepper Motor %d\r\n ", InfDevice.PpsToStepperMotor );
		 HwStepperCtrlConfigure(HW_STEPPER_NUM_2, HW_STEPPER_DIR_FWD, InfDevice.PpsToStepperMotor);
		 HwStepperCtrlStart(HW_STEPPER_NUM_2);


        InfDevice.State = INF_DEVICE_STATE_INFUSING;
        InfDevice.InfusionElapsedTimeInSecs = 0;
        //EwPrint("ProcessStartInCfgSet: Transitioning to INFUSING.\n");

        /* Start the InfusionUpdateTimer now that infusion is active */
        if(xInfusionUpdateTimer != NULL)
        {
            xTimerStart(xInfusionUpdateTimer, 0);
        }
    }
    else
    {
        //EwPrint("ProcessStartInCfgSet: FlowRate not set.\n");
    }
}
static void ProcessStopInCfgSet( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessStopInCfgSet"); }
static void ProcessPauseByUserInCfgSet( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseByUserInCfgSet"); }
static void ProcessPauseUpstreamInCfgSet( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseUpstreamInCfgSet"); }
static void ProcessPauseDownstreamInCfgSet( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseDownstreamInCfgSet"); }
static void ProcessPauseAirbubbleInCfgSet( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessPauseAirbubbleInCfgSet"); }
static void ProcessResumeInCfgSet( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessResumeInCfgSet"); }

/* ----------------- State: INFUSING ----------------- */
static void ProcessInitInInfusing( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessInitInInfusing"); }
static void ProcessCfgSetVTBIInInfusing( InfMessage_t msg )
{
    float vtbi = 0.0f;
    memcpy(&vtbi, msg.data, sizeof(float));
    InfDevice.VTBIx100 = (unsigned long int)(vtbi * 100);
    InfDevice.ModifiedParameter = CFG_VTBI;
    //EwPrint("ProcessCfgSetVTBIInInfusing: VTBI updated to %f (stored %lu).\n", vtbi, InfDevice.VTBIx100);
}
static void ProcessCfgSetFlowRateInInfusing( InfMessage_t msg )
{
    float flowRate = 0.0f;
    memcpy(&flowRate, msg.data, sizeof(float));
    InfDevice.FlowRatex100 = (unsigned long int)(flowRate * 100);
    InfDevice.ModifiedParameter = CFG_FLOWRATE;
    //EwPrint("ProcessCfgSetFlowRateInInfusing: FlowRate updated to %f (stored %lu).\n", flowRate, InfDevice.FlowRatex100);
}
static void ProcessCfgSetTimeInInfusing( InfMessage_t msg )
{
    unsigned long int infusionTime = 0;
    memcpy(&infusionTime, msg.data, sizeof(unsigned long int));
    InfDevice.InfusionTimeInSecs = infusionTime;
    InfDevice.ModifiedParameter = CFG_INFUSIONTIME;
    //EwPrint("ProcessCfgSetTimeInInfusing: InfusionTime updated to %lu.\n", infusionTime);
}

/* START is not allowed in INFUSING state */
static void ProcessStartInInfusing( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessStartInInfusing"); }

/**
 * @brief Handler for STOP in the INFUSING state.
 *
 * Stops the stepper motor, resets infusion parameters, and transitions the state
 * to IDLE. Also stops the InfusionUpdateTimer.
 */
static void ProcessStopInInfusing( InfMessage_t msg )
{
    HwStepperCtrlStop(HW_STEPPER_NUM_2);
    InfDevice.State = INF_DEVICE_STATE_IDLE;

    InfDevice.InfusionElapsedTimeInSecs = 0;
    InfDevice.RemainingTimeInSecs = 0;
    InfDevice.VolumeInfusedx100 = 0;
    InfDevice.ModifiedParameter = CFG_NONE;
   // SetHome_Position( );
    //EwPrint("ProcessStopInInfusing: Stopping infusion; transitioning to IDLE.\n");

    /* Stop the InfusionUpdateTimer when infusion stops */
    if(xInfusionUpdateTimer != NULL)
    {
        xTimerStop(xInfusionUpdateTimer, 0);
    }
}

/**
 * @brief Handler for PAUSE (by user) in the INFUSING state.
 *
 * Stops the stepper motor, transitions the state to PAUSED_BY_USER, and stops the
 * InfusionUpdateTimer.
 */
static void ProcessPauseByUserInInfusing( InfMessage_t msg )
{
    HwStepperCtrlStop(HW_STEPPER_NUM_2);
    InfDevice.State = INF_DEVICE_STATE_PAUSED_BYUSER;
    //EwPrint("ProcessPauseByUserInInfusing: Pausing infusion (by user).\n");

    /* Stop the InfusionUpdateTimer while infusion is paused */
    if(xInfusionUpdateTimer != NULL)
    {
        xTimerStop(xInfusionUpdateTimer, 0);
    }
}
static void ProcessPauseUpstreamInInfusing( InfMessage_t msg )
{
    HwStepperCtrlStop(HW_STEPPER_NUM_2);
    InfDevice.State = INF_DEVICE_STATE_PAUSED_UPSTREAM_PRESS_LOW;
    //EwPrint("ProcessPauseUpstreamInInfusing: Pausing infusion (upstream pressure low).\n");

    if(xInfusionUpdateTimer != NULL)
    {
        xTimerStop(xInfusionUpdateTimer, 0);
    }
}
static void ProcessPauseDownstreamInInfusing( InfMessage_t msg )
{
    HwStepperCtrlStop(HW_STEPPER_NUM_2);
    InfDevice.State = INF_DEVICE_STATE_PAUSED_DOWNSTREAM_PRESS_LOW;
    //EwPrint("ProcessPauseDownstreamInInfusing: Pausing infusion (downstream pressure low).\n");

    if(xInfusionUpdateTimer != NULL)
    {
        xTimerStop(xInfusionUpdateTimer, 0);
    }
}
static void ProcessPauseAirbubbleInInfusing( InfMessage_t msg )
{
    HwStepperCtrlStop(HW_STEPPER_NUM_2);
    InfDevice.State = INF_DEVICE_STATE_PAUSED_AIRBUBBLE;
    //EwPrint("ProcessPauseAirbubbleInInfusing: Pausing infusion (air-bubble detected).\n");

    if(xInfusionUpdateTimer != NULL)
    {
        xTimerStop(xInfusionUpdateTimer, 0);
    }
}
static void ProcessResumeInInfusing( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessResumeInInfusing"); }

/* ----------------- State: PAUSED_BY_USER ----------------- */
static void ProcessInitInPausedByUser( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessInitInPausedByUser"); }
static void ProcessCfgSetVTBIInPausedByUser( InfMessage_t msg )
{
    float vtbi = 0.0f;
    memcpy(&vtbi, msg.data, sizeof(float));
    InfDevice.VTBIx100 = (unsigned long int)(vtbi * 100);
    InfDevice.ModifiedParameter = CFG_VTBI;
    //EwPrint("ProcessCfgSetVTBIInPausedByUser: VTBI updated to %f (stored %lu).\n", vtbi, InfDevice.VTBIx100);
}
static void ProcessCfgSetFlowRateInPausedByUser( InfMessage_t msg )
{
    float flowRate = 0.0f;
    memcpy(&flowRate, msg.data, sizeof(float));
    InfDevice.FlowRatex100 = (unsigned long int)(flowRate * 100);
    InfDevice.ModifiedParameter = CFG_FLOWRATE;
    //EwPrint("ProcessCfgSetFlowRateInPausedByUser: FlowRate updated to %f (stored %lu).\n", flowRate, InfDevice.FlowRatex100);
}
static void ProcessCfgSetTimeInPausedByUser( InfMessage_t msg )
{
    unsigned long int infusionTime = 0;
    memcpy(&infusionTime, msg.data, sizeof(unsigned long int));
    InfDevice.InfusionTimeInSecs = infusionTime;
    InfDevice.ModifiedParameter = CFG_INFUSIONTIME;
    //EwPrint("ProcessCfgSetTimeInPausedByUser: InfusionTime updated to %lu.\n", infusionTime);
}

/**
 * @brief Handler for START in PAUSED_BY_USER state.
 *
 * Resumes infusion by ensuring the door is closed, configuring and starting the stepper motor,
 * transitioning the state to INFUSING, resetting the elapsed time, and restarting the
 * InfusionUpdateTimer.
 */
static void ProcessStartInPausedByUser( InfMessage_t msg )
{
    if(InfDevice.FlowRatex100 != 0)
    {
        //EwPrint("ProcessStartInPausedByUser: Resuming infusion...\n");
#warning "Door Close to be enabled in Actual Build"
#if 1
        DoorHandlerSendFullCloseMessage();
        while(1)
        {
            vTaskDelay(pdMS_TO_TICKS(200));
            if(DoorHandlerGetState() == DOOR_STATE_CLOSED)
                break;
        }
#endif
        InfDevice.PpsToStepperMotor = INF_DEVICE_CONVERT_FLOWRATE_TO_PPS(InfDevice.FlowRatex100);
        HwStepperCtrlConfigure(HW_STEPPER_NUM_2, HW_STEPPER_DIR_FWD, InfDevice.PpsToStepperMotor);
        HwStepperCtrlStart(HW_STEPPER_NUM_2);
        InfDevice.State = INF_DEVICE_STATE_INFUSING;
        InfDevice.InfusionElapsedTimeInSecs = 0;
        //EwPrint("ProcessStartInPausedByUser: Transitioning to INFUSING.\n");

        /* Restart the InfusionUpdateTimer upon resuming */
        if(xInfusionUpdateTimer != NULL)
        {
            xTimerStart(xInfusionUpdateTimer, 0);
        }
    }
}
static void ProcessStopInPausedByUser( InfMessage_t msg )
{
    HwStepperCtrlStop(HW_STEPPER_NUM_2);
    InfDevice.State = INF_DEVICE_STATE_IDLE;

    InfDevice.InfusionElapsedTimeInSecs = 0;
    InfDevice.RemainingTimeInSecs = 0;


    InfDevice.VolumeInfusedx100 = 0;
    InfDevice.ModifiedParameter = CFG_NONE;
    //EwPrint("ProcessStopInPausedByUser: Stopping infusion; transitioning to IDLE.\n");

    /* Stop the InfusionUpdateTimer if running */
    if(xInfusionUpdateTimer != NULL)
    {
        xTimerStop(xInfusionUpdateTimer, 0);
    }
}
static void ProcessResumeInPausedByUser( InfMessage_t msg )
{
    if(InfDevice.FlowRatex100 != 0)
    {
        //EwPrint("ProcessResumeInPausedByUser: Resuming infusion...\n");


				//EwPrint("ProcessStartInCfgSet: Sending door close command...\n");
#warning "Door Close to be enabled in Actual Build"
#if 1
				DoorHandlerSendFullCloseMessage();


				while(1)
				{
				   vTaskDelay(pdMS_TO_TICKS(200));
					if(DoorHandlerGetState() == DOOR_STATE_CLOSED)
						break;
				}
#endif

        InfDevice.PpsToStepperMotor = INF_DEVICE_CONVERT_FLOWRATE_TO_PPS(InfDevice.FlowRatex100);
        HwStepperCtrlConfigure(HW_STEPPER_NUM_2, HW_STEPPER_DIR_FWD, InfDevice.PpsToStepperMotor);
        HwStepperCtrlStart(HW_STEPPER_NUM_2);
        InfDevice.State = INF_DEVICE_STATE_INFUSING;
        InfDevice.InfusionElapsedTimeInSecs = 0;
        //EwPrint("ProcessResumeInPausedByUser: Resumed infusion (transition to INFUSING).\n");

        /* Restart the InfusionUpdateTimer after resuming infusion */
        if(xInfusionUpdateTimer != NULL)
        {
            xTimerStart(xInfusionUpdateTimer, 0);
        }
    }
}

/* ----------------- States: PAUSED_UPSTREAM_PRESS_LOW, PAUSED_DOWNSTREAM_PRESS_LOW,
                      PAUSED_UPSTREAM_PRESS_HIGH, PAUSED_DOWNSTREAM_PRESS_HIGH,
                      PAUSED_AIRBUBBLE ----------------- */
/* For brevity, these handlers call the same functions as for PAUSED_BY_USER */
static void ProcessInitInPausedUpStreamLow( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessInitInPausedUpStreamLow"); }
static void ProcessCfgSetVTBIInPausedUpStreamLow( InfMessage_t msg ) { ProcessCfgSetVTBIInPausedByUser(msg); }
static void ProcessCfgSetFlowRateInPausedUpStreamLow( InfMessage_t msg ) { ProcessCfgSetFlowRateInPausedByUser(msg); }
static void ProcessCfgSetTimeInPausedUpStreamLow( InfMessage_t msg ) { ProcessCfgSetTimeInPausedByUser(msg); }
static void ProcessStartInPausedUpStreamLow( InfMessage_t msg ) { ProcessStartInPausedByUser(msg); }
static void ProcessStopInPausedUpStreamLow( InfMessage_t msg ) { ProcessStopInPausedByUser(msg); }
static void ProcessResumeInPausedUpStreamLow( InfMessage_t msg ) { ProcessResumeInPausedByUser(msg); }

static void ProcessInitInPausedDownStreamLow( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessInitInPausedDownStreamLow"); }
static void ProcessCfgSetVTBIInPausedDownStreamLow( InfMessage_t msg ) { ProcessCfgSetVTBIInPausedByUser(msg); }
static void ProcessCfgSetFlowRateInPausedDownStreamLow( InfMessage_t msg ) { ProcessCfgSetFlowRateInPausedByUser(msg); }
static void ProcessCfgSetTimeInPausedDownStreamLow( InfMessage_t msg ) { ProcessCfgSetTimeInPausedByUser(msg); }
static void ProcessStartInPausedDownStreamLow( InfMessage_t msg ) { ProcessStartInPausedByUser(msg); }
static void ProcessStopInPausedDownStreamLow( InfMessage_t msg ) { ProcessStopInPausedByUser(msg); }
static void ProcessResumeInPausedDownStreamLow( InfMessage_t msg ) { ProcessResumeInPausedByUser(msg); }

static void ProcessInitInPausedUpStreamHigh( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessInitInPausedUpStreamHigh"); }
static void ProcessCfgSetVTBIInPausedUpStreamHigh( InfMessage_t msg ) { ProcessCfgSetVTBIInPausedByUser(msg); }
static void ProcessCfgSetFlowRateInPausedUpStreamHigh( InfMessage_t msg ) { ProcessCfgSetFlowRateInPausedByUser(msg); }
static void ProcessCfgSetTimeInPausedUpStreamHigh( InfMessage_t msg ) { ProcessCfgSetTimeInPausedByUser(msg); }
static void ProcessStartInPausedUpStreamHigh( InfMessage_t msg ) { ProcessStartInPausedByUser(msg); }
static void ProcessStopInPausedUpStreamHigh( InfMessage_t msg ) { ProcessStopInPausedByUser(msg); }
static void ProcessResumeInPausedUpStreamHigh( InfMessage_t msg ) { ProcessResumeInPausedByUser(msg); }

static void ProcessInitInPausedDownStreamHigh( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessInitInPausedDownStreamHigh"); }
static void ProcessCfgSetVTBIInPausedDownStreamHigh( InfMessage_t msg ) { ProcessCfgSetVTBIInPausedByUser(msg); }
static void ProcessCfgSetFlowRateInPausedDownStreamHigh( InfMessage_t msg ) { ProcessCfgSetFlowRateInPausedByUser(msg); }
static void ProcessCfgSetTimeInPausedDownStreamHigh( InfMessage_t msg ) { ProcessCfgSetTimeInPausedByUser(msg); }
static void ProcessStartInPausedDownStreamHigh( InfMessage_t msg ) { ProcessStartInPausedByUser(msg); }
static void ProcessStopInPausedDownStreamHigh( InfMessage_t msg ) { ProcessStopInPausedByUser(msg); }
static void ProcessResumeInPausedDownStreamHigh( InfMessage_t msg ) { ProcessResumeInPausedByUser(msg); }

static void ProcessInitInPausedAirbubble( InfMessage_t msg ) { GenericNotAllowedHandler("ProcessInitInPausedAirbubble"); }
static void ProcessCfgSetVTBIInPausedAirbubble( InfMessage_t msg ) { ProcessCfgSetVTBIInPausedByUser(msg); }
static void ProcessCfgSetFlowRateInPausedAirbubble( InfMessage_t msg ) { ProcessCfgSetFlowRateInPausedByUser(msg); }
static void ProcessCfgSetTimeInPausedAirbubble( InfMessage_t msg ) { ProcessCfgSetTimeInPausedByUser(msg); }
static void ProcessStartInPausedAirbubble( InfMessage_t msg ) { ProcessStartInPausedByUser(msg); }
static void ProcessStopInPausedAirbubble( InfMessage_t msg ) { ProcessStopInPausedByUser(msg); }
static void ProcessResumeInPausedAirbubble( InfMessage_t msg ) { ProcessResumeInPausedByUser(msg); }

/*===========================================================================
 * End of State Machine Handlers
 *===========================================================================*/
