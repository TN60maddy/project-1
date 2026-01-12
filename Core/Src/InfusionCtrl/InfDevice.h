/**
 * @file InfDevice.h
 * @brief Public API for the Infusion Device Control Module.
 *
 * This header file declares the public API functions as well as the
 * error code and device state enumerations for controlling an infusion device.
 *
 * @author
 *         Radhakrishnan Rajaram
 * @company
 *         Aria Innovations Pvt Ltd
 * @version 1.0
 * @date    2025-02-18
 * @copyright Copyright (c) 2025 Aria Innovations Pvt Ltd. All rights reserved.
 */

#ifndef INFDEVICE_H
#define INFDEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>  // Standard integer types

/**
 * @brief Error code definitions.
 */
typedef enum
{
    INFDEVICE_ERROR_NONE = 0,                         /**< No error. */
    INFDEVICE_ERROR_OPERATION_NOT_ALLOWED = -1,       /**< Operation not allowed. */
    INFDEVICE_ERROR_UNKNOWN = 0xFF                      /**< Unknown error. */
} InfDeviceErrorCode_t;

/**
 * @brief Device state definitions.
 */
typedef enum
{
    INF_DEVICE_STATE_INIT = 0,                        /**< Device is initializing. */
    INF_DEVICE_STATE_SELFTEST_INPROGRESS,             /**< Self-test is in progress. */
    INF_DEVICE_STATE_SELFTEST_FAILED,                 /**< Self-test failed. */
    INF_DEVICE_STATE_IDLE,                            /**< Idle state. */
    INF_DEVICE_STATE_CFG_SET,                         /**< Configuration has been set. */
    INF_DEVICE_STATE_INFUSING,                        /**< Infusing in progress. */
    INF_DEVICE_STATE_PAUSED_BYUSER,                   /**< Paused by user request. */
    INF_DEVICE_STATE_PAUSED_UPSTREAM_PRESS_LOW,       /**< Paused due to upstream low pressure. */
    INF_DEVICE_STATE_PAUSED_DOWNSTREAM_PRESS_LOW,     /**< Paused due to downstream low pressure. */
    INF_DEVICE_STATE_PAUSED_UPSTREAM_PRESS_HIGH,      /**< Paused due to upstream high pressure. */
    INF_DEVICE_STATE_PAUSED_DOWNSTREAM_PRESS_HIGH,    /**< Paused due to downstream high pressure. */
    INF_DEVICE_STATE_PAUSED_AIRBUBBLE,                /**< Paused due to air-bubble detection. */
    INF_DEVICE_STATE_MAX                              /**< Maximum state value. */
} InfDeviceState_t;

/**
 * @brief Infusion device status structure.
 *
 * This structure holds infusion parameters including rates, volumes, and timing details.
 */
typedef struct {
    uint32_t FlowRatex100;              /**< Flow rate value multiplied by 100. */
    uint32_t VTBIx100;                  /**< VTBI value multiplied by 100. */
    uint32_t VolumeInfusedx100;         /**< Volume infused multiplied by 100. */
    uint32_t RemainingTimeInSecs;       /**< Remaining infusion time in seconds. */
    uint32_t InfusionTimeInSecs;        /**< Total infusion time in seconds. */
    uint32_t InfusionElapsedTimeInSecs; /**< Elapsed infusion time in seconds. */
    float OcculsionPressure;            /**< Occulsion Pressure. */
    float BolusRate;                    /**< Bolus Rate. */
    float KVORate;                      /**< KVO Rate. */
    float MaxFlowRate;                  /**< Max Flow Rate. */
    uint16_t AirLineSensitivity;        /**< Air Line Sensitivity. */
    uint16_t AlarmSetting;              /**< Alarm Setting. */
} InfusionStatus_t;

/*===========================================================================
 * Public API Function Prototypes
 *===========================================================================*/

/**
 * @brief Initializes the infusion device and runs a self-test.
 *
 * This function initializes the hardware (e.g., stepper motor controller),
 * creates the message queue, and spawns the worker thread required for
 * processing device commands. It performs a self-test and sets the device state accordingly.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success (INFDEVICE_ERROR_NONE) or failure.
 *
 * @author
 *         Radhakrishnan Rajaram
 */
InfDeviceErrorCode_t InfDevice_InitWithSelfTest(void);

/**
 * @brief Sets the infusion flow rate.
 *
 * Configures the desired flow rate for the infusion. The flow rate is specified as a floating point value.
 *
 * @param FlowRate_f  Flow rate value (in float).
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 *
 * @author
 *         Radhakrishnan Rajaram
 */
InfDeviceErrorCode_t InfDevice_SetFlowRate(float FlowRate_f);

/**
 * @brief Sets the VTBI (Volume To Be Infused).
 *
 * This function sets the VTBI parameter that determines the total
 * volume to be infused during the therapy.
 *
 * @param VTBI_f  VTBI value specified as a float.
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 *
 * @author
 *         Radhakrishnan Rajaram
 */
InfDeviceErrorCode_t InfDevice_SetVTBI(float VTBI_f);

/**
 * @brief Sets the infusion time.
 *
 * Configures the infusion time in seconds.
 *
 * @param InfusionTimeInSecs  Infusion time in seconds.
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 *
 * @author
 *         Radhakrishnan Rajaram
 */
InfDeviceErrorCode_t InfDevice_SetInfusionTime(int InfusionTimeInSecs);

/**
 * @brief Starts the infusion process.
 *
 * This function sends the start command to the device to begin the infusion.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 *
 * @author
 *         Radhakrishnan Rajaram
 */
InfDeviceErrorCode_t InfDevice_EvStart(void);

/**
 * @brief Stops the infusion process.
 *
 * Sends a stop command to the infusion device, halting the current process.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 *
 * @author
 *         Radhakrishnan Rajaram
 */
InfDeviceErrorCode_t InfDevice_EvStop(void);

/**
 * @brief Resumes the infusion process.
 *
 * Resumes the infusion if it was previously paused.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 *
 * @author
 *         Radhakrishnan Rajaram
 */
InfDeviceErrorCode_t InfDevice_EvResume(void);

/**
 * @brief Pauses the infusion process as initiated by the user.
 *
 * Pauses the infusion process upon a user's request.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 *
 * @author
 *         Radhakrishnan Rajaram
 */
InfDeviceErrorCode_t InfDevice_EvPauseByUser(void);

/**
 * @brief Pauses the infusion process due to upstream pressure conditions.
 *
 * Initiates a pause when the upstream pressure is below the acceptable threshold.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 *
 * @author
 *         Radhakrishnan Rajaram
 */
InfDeviceErrorCode_t InfDevice_EvPauseUpstream(void);

/**
 * @brief Pauses the infusion process due to downstream pressure conditions.
 *
 * Initiates a pause when the downstream pressure is below the acceptable threshold.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 *
 * @author
 *         Radhakrishnan Rajaram
 */
InfDeviceErrorCode_t InfDevice_EvPauseDownstream(void);

/**
 * @brief Pauses the infusion process due to air-bubble detection.
 *
 * This function is called when the system detects an air bubble,
 * resulting in a pause of the infusion process.
 *
 * @return InfDeviceErrorCode_t  Error code indicating success or failure.
 *
 * @author
 *         Radhakrishnan Rajaram
 */
InfDeviceErrorCode_t InfDevice_EvPauseAirbubble(void);

/**
 * @brief Retrieves the current state of the infusion device.
 *
 * @return InfDeviceState_t  The current state of the device.
 *
 * @author
 *         Radhakrishnan Rajaram
 */
InfDeviceState_t InfDevice_getState(void);

/**
 * @brief Retrieves the current infusion device status.
 *
 * This function updates the given InfusionStatus_t structure pointer with parameters
 * from the internal device status. The following parameters are copied from the global
 * structure:
 *   - FlowRatex100
 *   - VTBIx100
 *   - VolumeInfusedx100
 *   - RemainingTimeInSecs
 *   - InfusionTimeInSecs
 *   - InfusionElapsedTimeInSecs
 * And these fields are set to fixed values:
 *   - OcculsionPressure  ==> 9.0
 *   - BolusRate          ==> 1200.00
 *   - KVORate            ==> 0.01
 *   - MaxFlowRate        ==> 1200.00
 *   - AirLineSensitivity ==> 90
 *   - AlarmSetting       ==> 600
 *
 * @param status Pointer to an InfusionStatus_t structure to be updated.
 * @return int16_t Returns 0 on success, or -1 if the pointer is NULL.
 */
int16_t InfDevice_GetStatus(InfusionStatus_t *status);


#ifdef __cplusplus
}
#endif

#endif /* INFDEVICE_H */
