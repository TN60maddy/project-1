/**
 * @file DoorHandler.c
 * @brief Source file for the DoorHandler module.
 *
 * This module implements a FreeRTOS task that processes door commands and sensor update messages.
 * It creates a software timer that reads the door position sensor every DOOR_SENSOR_TIMER_PERIOD_MS ms (by calling
 * HwDoorPositionSensorReadStatus) and posts the sensor value to the DoorHandler task.
 *
 * When a DOOR_CMD_OPEN_CLOSE command is received and the current state is either DOOR_STATE_CLOSED or DOOR_STATE_HALF_CLOSED,
 * the module changes the state to DOOR_STATE_OPENING and configures and starts the stepper motor (with reverse direction)
 * to open the door.
 *
 * In the update state function (triggered by DOOR_CMD_SENSOR_UPDATE messages):
 *   - If the current state is DOOR_STATE_OPENING and the sensor value is between DOOR_OPEN_STATE_SENSOR_MIN and DOOR_OPEN_STATE_SENSOR_MAX,
 *     the stepper motor is stopped and the state is changed to DOOR_STATE_OPEN.
 *   - If the current state is DOOR_STATE_OPEN and the sensor value is between DOOR_CLOSE_DETECT_SENSOR_MIN and DOOR_CLOSE_DETECT_SENSOR_MAX,
 *     the stepper motor is reconfigured (with forward direction) and started, and the state is set to DOOR_STATE_CLOSE_DETECT.
 *   - If the current state is DOOR_STATE_CLOSE_DETECT and the sensor value is between DOOR_HALF_CLOSED_SENSOR_MIN and DOOR_HALF_CLOSED_SENSOR_MAX,
 *     the stepper motor is stopped and the state is changed to DOOR_STATE_HALF_CLOSED.
 * For other sensor values the state is updated based on fixed thresholds.
 *
 * When a DOOR_CMD_FULL_CLOSE command is received, a full door close operation is performed.
 *
 * @author
 *         Radhakrishnan Rajaram
 * @company
 *         Aria Innovations
 * @date
 *         2025-02-11
 * @revision History:
 *         - 1.0 2025-02-11: Initial version.
 *         - 1.1 2025-02-XX: Updated error handling so that any HwStepperCtrl function returning non-zero causes an error.
 *         - 1.2 2025-02-XX: Implemented door state updates from sensor values and added DOOR_CMD_FULL_CLOSE support.
 *         - 1.3 2025-02-XX: Renamed DOOR_STATE_FULL_CLOSED to DOOR_STATE_OPEN and updated corresponding macro names.
 *         - 1.4 2025-02-XX: Updated DOOR_HOME_OPEN_SENSOR_THRESHOLD to 195 and DOOR_OPEN_STATE_SENSOR_MAX to 195.
 *         - 1.5 2025-02-XX: Increased DOOR_OPEN_PPS from 475 to 5000.
 *         - 1.6 2025-02-XX: Added transitional state DOOR_STATE_OPENING and updated state transitions in the command handler and update function.
 *         - 1.7 2025-02-XX: Added DoorHandlerGetState() to retrieve the current door state.
 */

#include "DoorHandler.h"
#include "stm32h7xx_hal.h"            /* HAL header for STM32H7 series */
#include "HwDoorPositionSensor.h"     /* Provides HwDoorPositionSensorInit and HwDoorPositionSensorReadStatus */
#include "HwStepperCtrl.h"            /* Provides HwStepperCtrlInit, HwStepperCtrlConfigure, HwStepperCtrlStart, and HwStepperCtrlStop */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "ewrte.h"

/* Macros for configuration parameters */
#define DOOR_OPEN_PPS                     500//1000
#define DOOR_SENSOR_TIMER_PERIOD_MS       100
#define DOOR_QUEUE_LENGTH                 10
#define DOOR_TASK_STACK_SIZE              512
#define DOOR_TASK_PRIORITY                (tskIDLE_PRIORITY + 4)

/* Macros for door sensor value ranges */
#define DOOR_CLOSED_SENSOR_MIN            32
#define DOOR_CLOSED_SENSOR_MAX            34
#define DOOR_HALF_CLOSED_SENSOR_MIN       93
#define DOOR_HALF_CLOSED_SENSOR_MAX       96
/* Renamed macros for door open state */
#define DOOR_OPEN_STATE_SENSOR_MIN        142
#define DOOR_OPEN_STATE_SENSOR_MAX        143
#define DOOR_CLOSE_DETECT_SENSOR_MIN      138
#define DOOR_CLOSE_DETECT_SENSOR_MAX      140
#define DOOR_HOME_OPEN_SENSOR_THRESHOLD   144

/* FreeRTOS objects */
static QueueHandle_t xDoorQueue = NULL;
static TaskHandle_t xDoorHandleTaskHandle = NULL;
static TimerHandle_t xDoorSensorTimer = NULL;

/* Enumeration for door commands */
typedef enum {
    DOOR_CMD_OPEN_CLOSE = 0,    /**< Command to open the door */
    DOOR_CMD_SENSOR_UPDATE,     /**< Command carrying a door sensor update */
    DOOR_CMD_FULL_CLOSE         /**< Command to fully close the door */
} DoorCommandType_t;

/* Global variable to store the current door state; defaults to NA */
static DoorState_t currentDoorState = DOOR_STATE_NA;

/* Structure for door messages */
typedef struct {
    DoorCommandType_t command;   /**< Door command type */
    int sensorValue;             /**< Sensor value for sensor update command */
} DoorMessage_t;

/**
 * @brief Error handler.
 *
 * This function is executed in case of a critical error.
 */
static void DoorHandlerError_Handler(void)
{
    while (1)
    {
        /* In an actual application, an LED might be toggled here to indicate an error */
    }
}

/**
 * @brief Callback function for the door sensor timer.
 *
 * This callback is executed every DOOR_SENSOR_TIMER_PERIOD_MS ms.
 * It reads the door position sensor using HwDoorPositionSensorReadStatus() and sends the sensor value to the DoorHandler task.
 *
 * @param xTimer Timer handle (unused).
 */
static void vDoorSensorTimerCallback(TimerHandle_t xTimer)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    HwDoorPosition_t sensorValue = 0;

    /* Read door position sensor status */
    HwDoorPositionSensorReadStatus(&sensorValue);

    /* Create a sensor update message */
    DoorMessage_t msg;
    msg.command = DOOR_CMD_SENSOR_UPDATE;
    msg.sensorValue = sensorValue;

    /* Send the sensor update message to the door queue from ISR context */
    xQueueSendFromISR(xDoorQueue, &msg, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/**
 * @brief Updates the current door state based on the sensor value.
 *
 * This function implements transitional behavior:
 *   - If in DOOR_STATE_OPENING and sensorValue is between DOOR_OPEN_STATE_SENSOR_MIN and DOOR_OPEN_STATE_SENSOR_MAX,
 *     the stepper motor is stopped and the state is set to DOOR_STATE_OPEN.
 *   - If in DOOR_STATE_OPEN and sensorValue is between DOOR_CLOSE_DETECT_SENSOR_MIN and DOOR_CLOSE_DETECT_SENSOR_MAX,
 *     the stepper motor is configured for closing (forward) and started, and the state is set to DOOR_STATE_CLOSE_DETECT.
 *   - If in DOOR_STATE_CLOSE_DETECT and sensorValue is between DOOR_HALF_CLOSED_SENSOR_MIN and DOOR_HALF_CLOSED_SENSOR_MAX,
 *     the stepper motor is stopped and the state is set to DOOR_STATE_HALF_CLOSED.
 * For other cases, the state is updated based solely on fixed thresholds.
 *
 * @param sensorVal The door sensor value.
 */
static void updateDoorState(int sensorVal)
{

	static int count = 0;
	if( ++count == 20 )
	{
	//	EwPrint(" Door Sensor Value: %d\n", sensorVal );
		count = 0;
	}


    if (currentDoorState == DOOR_STATE_OPENING) {
        if ((sensorVal >= DOOR_OPEN_STATE_SENSOR_MIN) && (sensorVal <= DOOR_OPEN_STATE_SENSOR_MAX)) {
            if (HwStepperCtrlStop(HW_STEPPER_NUM_1) != 0) {
                DoorHandlerError_Handler();
            }
            currentDoorState = DOOR_STATE_OPEN;
        }
    }
    else if (currentDoorState == DOOR_STATE_OPEN) {

        if ((sensorVal >= DOOR_CLOSE_DETECT_SENSOR_MIN) && (sensorVal <= DOOR_CLOSE_DETECT_SENSOR_MAX)) {
            if (HwStepperCtrlConfigure(HW_STEPPER_NUM_1, HW_STEPPER_DIR_FWD, DOOR_OPEN_PPS) != 0) {
                DoorHandlerError_Handler();
            }
            if (HwStepperCtrlStart(HW_STEPPER_NUM_1) != 0) {
                DoorHandlerError_Handler();
            }
            currentDoorState = DOOR_STATE_CLOSE_DETECT;
        }
    }
    else if (currentDoorState == DOOR_STATE_CLOSE_DETECT) {
        if ((sensorVal >= DOOR_HALF_CLOSED_SENSOR_MIN) && (sensorVal <= DOOR_HALF_CLOSED_SENSOR_MAX)) {
            if (HwStepperCtrlStop(HW_STEPPER_NUM_1) != 0) {
                DoorHandlerError_Handler();
            }
            currentDoorState = DOOR_STATE_HALF_CLOSED;
        }
    }
    else {
        /* For other states, update based on sensor value */
        if ((sensorVal >= DOOR_CLOSED_SENSOR_MIN) && (sensorVal <= DOOR_CLOSED_SENSOR_MAX)) {
            currentDoorState = DOOR_STATE_CLOSED;
        }
        else if ((sensorVal >= DOOR_HALF_CLOSED_SENSOR_MIN) && (sensorVal <= DOOR_HALF_CLOSED_SENSOR_MAX)) {
            currentDoorState = DOOR_STATE_HALF_CLOSED;
        }
        else if (sensorVal > DOOR_HOME_OPEN_SENSOR_THRESHOLD) {
            currentDoorState = DOOR_STATE_HOME_OPEN;
        }
        else {
            currentDoorState = DOOR_STATE_NA;
        }
    }
}

/**
 * @brief DoorHandler task.
 *
 * This task processes door messages from the queue.
 *
 * - For a DOOR_CMD_OPEN_CLOSE command: if the current state is DOOR_STATE_CLOSED or DOOR_STATE_HALF_CLOSED,
 *   the state is changed to DOOR_STATE_OPENING and the stepper motor is configured (reverse direction)
 *   and started to open the door.
 *
 * - For a DOOR_CMD_SENSOR_UPDATE command, the door state is updated based on the sensor value.
 *
 * - For a DOOR_CMD_FULL_CLOSE command, a full door close operation is performed:
 *   1. Configures the stepper motor for full close (forward direction).
 *   2. Starts the stepper motor.
 *   3. Stops the door sensor timer.
 *   4. Polls the door sensor every DOOR_SENSOR_TIMER_PERIOD_MS ms until the sensor value indicates door closed
 *      (between DOOR_CLOSED_SENSOR_MIN and DOOR_CLOSED_SENSOR_MAX), then stops the motor and restarts the timer.
 *
 * @param argument Not used.
 */
static void vDoorHandleTask(void *argument)
{
    DoorMessage_t receivedMsg;
    (void) argument;

    for (;;) {
        if (xQueueReceive(xDoorQueue, &receivedMsg, portMAX_DELAY) == pdPASS) {
            switch (receivedMsg.command) {
                case DOOR_CMD_OPEN_CLOSE:
                {
                    /* Process the open command only if door is closed or half closed */
                    if ((currentDoorState == DOOR_STATE_CLOSED)
                    		|| (currentDoorState == DOOR_STATE_HALF_CLOSED)
							|| (currentDoorState == DOOR_STATE_NA ) ) {
                        currentDoorState = DOOR_STATE_OPENING;
                        if (HwStepperCtrlConfigure(HW_STEPPER_NUM_1, HW_STEPPER_DIR_REV, DOOR_OPEN_PPS) != 0) {
                            DoorHandlerError_Handler();
                        }
                        if (HwStepperCtrlStart(HW_STEPPER_NUM_1) != 0) {
                            DoorHandlerError_Handler();
                        }

                    }
                    break;
                }

                case DOOR_CMD_SENSOR_UPDATE:
                {
                    /* Update the door state based on the sensor value */
                    updateDoorState(receivedMsg.sensorValue);
                    break;
                }

                case DOOR_CMD_FULL_CLOSE:
                {
                    HwDoorPosition_t sensorValue = 0;
                    if (HwStepperCtrlConfigure(HW_STEPPER_NUM_1, HW_STEPPER_DIR_FWD, DOOR_OPEN_PPS) != 0) {
                        DoorHandlerError_Handler();
                    }
                    if (HwStepperCtrlStart(HW_STEPPER_NUM_1) != 0) {
                        DoorHandlerError_Handler();
                    }
                    if (xTimerStop(xDoorSensorTimer, portMAX_DELAY) != pdPASS) {
                        DoorHandlerError_Handler();
                    }

                    for (;;) {

                        HwDoorPositionSensorReadStatus(&sensorValue);
                        vTaskDelay(pdMS_TO_TICKS(DOOR_SENSOR_TIMER_PERIOD_MS));

                        if ((sensorValue >= DOOR_CLOSED_SENSOR_MIN) && (sensorValue <= DOOR_CLOSED_SENSOR_MAX)) {
                            if (HwStepperCtrlStop(HW_STEPPER_NUM_1) != 0) {
                                DoorHandlerError_Handler();
                            }
                            if (xTimerStart(xDoorSensorTimer, portMAX_DELAY) != pdPASS) {
                                DoorHandlerError_Handler();
                            }
                            break;
                        }
                        if (xTimerStart(xDoorSensorTimer, portMAX_DELAY) != pdPASS) {
                                                DoorHandlerError_Handler();
                                            }
                    }
                    break;
                }

                default:
                    break;
            }
         }
        }
    }


/**
 * @brief Initializes the DoorHandler module.
 *
 * This function performs the following:
 *  - Initializes the door position sensor hardware.
 *  - Initializes the stepper motor hardware by calling HwStepperCtrlInit() with HW_STEPPER_NUM_1.
 *  - Creates a FreeRTOS queue for door messages.
 *  - Creates a periodic software timer to read the door sensor every DOOR_SENSOR_TIMER_PERIOD_MS ms.
 *  - Creates the DoorHandler task.
 */
void DoorHandlerInit(void)
{
    HwDoorPositionSensorInit();

   if (HwStepperCtrlInit(HW_STEPPER_NUM_1) != 0) {
          DoorHandlerError_Handler();
       }

    xDoorQueue = xQueueCreate(DOOR_QUEUE_LENGTH, sizeof(DoorMessage_t));
    if (xDoorQueue == NULL) {
        DoorHandlerError_Handler();
    }

    xDoorSensorTimer = xTimerCreate("DoorSensorTimer",
                                    pdMS_TO_TICKS(DOOR_SENSOR_TIMER_PERIOD_MS),
                                    pdTRUE,
                                    (void *)0,
                                    vDoorSensorTimerCallback);
    if (xDoorSensorTimer == NULL) {
        DoorHandlerError_Handler();
    }
    if (xTimerStart(xDoorSensorTimer, portMAX_DELAY) != pdPASS) {
        DoorHandlerError_Handler();
    }

    if (xTaskCreate(vDoorHandleTask,
                    "DoorHandleTask",
                    DOOR_TASK_STACK_SIZE,
                    NULL,
                    DOOR_TASK_PRIORITY,
                    &xDoorHandleTaskHandle) != pdPASS)
    {
        DoorHandlerError_Handler();
    }
}

/**
 * @brief Sends a door open/close command.
 *
 * This function can be called (for example, by the KeyListner module) to trigger a door open/close operation.
 */
void DoorHandlerSendMessage(void)
{
    DoorMessage_t msg;
    msg.command = DOOR_CMD_OPEN_CLOSE;
    msg.sensorValue = 0; /* Not used for open/close command */

    if (xQueueSend(xDoorQueue, &msg, portMAX_DELAY) != pdPASS) {
        DoorHandlerError_Handler();
    }
}

/**
 * @brief Sends a full door close command.
 *
 * This function can be called from other modules to trigger a full door close operation.
 */
void DoorHandlerSendFullCloseMessage(void)
{
    DoorMessage_t msg;
    msg.command = DOOR_CMD_FULL_CLOSE;
    msg.sensorValue = 0; /* Not used for full close command */

    if (xQueueSend(xDoorQueue, &msg, portMAX_DELAY) != pdPASS) {
        DoorHandlerError_Handler();
    }
}

/**
 * @brief Retrieves the current door state.
 *
 * @return DoorState_t The current door state.
 */
DoorState_t DoorHandlerGetState(void)
{
    return currentDoorState;
}
