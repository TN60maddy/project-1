/**
 * @file InfusionSet.c
 * @brief Implementation of infusion set parameter management.
 * @author Radhakrishnan Rajaram
 * @company Aria Innovations Pvt Ltd
 * @version 1.0
 * @copyright Copyright (c) 2025 Aria Innovations Pvt Ltd.
 */

#include "InfusionSet.h"

/** Static global variables with default values */
static float bolusRate = 1200.00f;
static float kvoRate = 0.01f;
static float maxFlowRate = 1200.00f;
static float occlusionPressure = 30.00f;
static uint16_t airLineSensitivity = 10u;
static uint16_t infusionCompletionAlarmSetting = 5u;

/**
 * @brief Set the bolus rate.
 * @param rate Bolus rate in ml/hour.
 */
void InfusionSet_SetBolusRate(float rate)
{
    bolusRate = rate;
}

/**
 * @brief Get the current bolus rate.
 * @return Current bolus rate in ml/hour.
 */
float InfusionSet_GetBolusRate(void)
{
    return bolusRate;
}

/**
 * @brief Set the KVO rate.
 * @param rate KVO rate in ml/hour.
 */
void InfusionSet_SetKVORate(float rate)
{
    kvoRate = rate;
}

/**
 * @brief Get the current KVO rate.
 * @return Current KVO rate in ml/hour.
 */
float InfusionSet_GetKVORate(void)
{
    return kvoRate;
}

/**
 * @brief Set the maximum flow rate.
 * @param rate Maximum flow rate in ml/hour.
 */
void InfusionSet_SetMaxFlowRate(float rate)
{
    maxFlowRate = rate;
}

/**
 * @brief Get the current maximum flow rate.
 * @return Current maximum flow rate in ml/hour.
 */
float InfusionSet_GetMaxFlowRate(void)
{
    return maxFlowRate;
}

/**
 * @brief Set the occlusion pressure.
 * @param pressure Occlusion pressure in mmHg.
 */
void InfusionSet_SetOcclusionPressure(float pressure)
{
    occlusionPressure = pressure;
}

/**
 * @brief Get the current occlusion pressure.
 * @return Current occlusion pressure in mmHg.
 */
float InfusionSet_GetOcclusionPressure(void)
{
    return occlusionPressure;
}

/**
 * @brief Set the air line sensitivity.
 * @param sensitivity Air line sensitivity level (unitless).
 */
void InfusionSet_SetAirLineSensitivity(uint16_t sensitivity)
{
    airLineSensitivity = sensitivity;
}

/**
 * @brief Get the current air line sensitivity.
 * @return Current air line sensitivity level.
 */
uint16_t InfusionSet_GetAirLineSensitivity(void)
{
    return airLineSensitivity;
}

/**
 * @brief Set the infusion completion alarm setting.
 * @param setting Alarm time before infusion completion in seconds.
 */
void InfusionSet_SetInfusionCompletionAlarmSetting(uint16_t setting)
{
    infusionCompletionAlarmSetting = setting;
}

/**
 * @brief Get the current infusion completion alarm setting.
 * @return Alarm time before infusion completion in seconds.
 */
uint16_t InfusionSet_GetInfusionCompletionAlarmSetting(void)
{
    return infusionCompletionAlarmSetting;
}
