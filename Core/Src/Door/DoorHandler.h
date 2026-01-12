/**
 * @file DoorHandler.h
 * @brief Header file for the DoorHandler module.
 *
 * This module provides functions for initializing door handling, sending door commands,
 * and retrieving the current door state.
 *
 * @author
 *         Radhakrishnan Rajaram
 * @company
 *         Aria Innovations
 * @date
 *         2025-02-11
 */

#ifndef DOORHANDLER_H
#define DOORHANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/**
 * @brief Enumeration for door states.
 */
typedef enum {
    DOOR_STATE_NA = 0,          /**< Door state not available (initialization state) */
    DOOR_STATE_CLOSED,          /**< Door Closed State */
    DOOR_STATE_HALF_CLOSED,     /**< Door Half Closed State */
    DOOR_STATE_OPENING,         /**< Transitional state: Door is in the process of opening */
    DOOR_STATE_OPEN,            /**< Door Open State */
    DOOR_STATE_CLOSE_DETECT,    /**< Door Close Detect State */
    DOOR_STATE_HOME_OPEN        /**< Door Home Open Position State */
} DoorState_t;

/**
 * @brief Initializes the DoorHandler module.
 *
 * This function initializes the door position sensor hardware, the stepper motor,
 * creates the command queue and sensor timer, and starts the door handling task.
 */
void DoorHandlerInit(void);

/**
 * @brief Sends a door open/close command.
 *
 * This function can be called (e.g., by the KeyListner module) to trigger a door open/close operation.
 */
void DoorHandlerSendMessage(void);

/**
 * @brief Sends a full door close command.
 *
 * This function can be called from other modules to trigger a full door close operation.
 */
void DoorHandlerSendFullCloseMessage(void);

/**
 * @brief Retrieves the current door state.
 *
 * @return DoorState_t The current door state.
 */
DoorState_t DoorHandlerGetState(void);

#ifdef __cplusplus
}
#endif

#endif /* DOORHANDLER_H */
