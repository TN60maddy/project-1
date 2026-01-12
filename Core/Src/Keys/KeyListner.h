/**
 * @file KeyListner.h
 * @brief Header file for the KeyListner module.
 *
 * This module scans keys using a FreeRTOS software timer (with debounce logic) and
 * signals a task when any key is pressed.
 *
 * @author
 *         Radhakrishnan Rajaram
 * @company
 *         Aria Innovations
 * @date
 *         2025-02-11
 * @revision History:
 *         - 1.0 2025-02-11: Initial version.
 */

#ifndef KEYLISTNER_H
#define KEYLISTNER_H

#ifdef __cplusplus
extern "C" {
#endif

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

/**
 * @brief Enumeration of key messages.
 */
typedef enum {
    KEY_MSG_STOP = 0,       /**< Message for the STOP button press */
    KEY_MSG_OPEN_CLOSE,     /**< Message for the OPEN/CLOSE button press */
    KEY_MSG_PWR             /**< Message for the POWER button press */
} KeyMessage_t;

/**
 * @brief Initializes the KeyListner module.
 *
 * This function initializes the GPIO ports for the buttons, creates the software timer,
 * the key message queue and the KeyListner task.
 */
void KeyListnerInit(void);

#ifdef __cplusplus
}
#endif

#endif /* KEYLISTNER_H */
