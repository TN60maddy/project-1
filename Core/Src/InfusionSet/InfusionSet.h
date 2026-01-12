/**
 * @file InfusionSet.h
 * @brief Header for infusion set parameter management.
 * @author Radhakrishnan Rajaram
 * @company Aria Innovations Pvt Ltd
 * @version 1.0
 * @copyright Copyright (c) 2025 Aria Innovations Pvt Ltd.
 */

#ifndef INFUSIONSET_H
#define INFUSIONSET_H

#include <stdint.h>

/**
 * @brief Set the bolus rate.
 * @param rate Bolus rate in ml/hour.
 */
void InfusionSet_SetBolusRate(float rate);

/**
 * @brief Get the bolus rate.
 * @return Current bolus rate in ml/hour.
 */
float InfusionSet_GetBolusRate(void);

/**
 * @brief Set the KVO (Keep-Vein-Open) rate.
 * @param rate KVO rate in ml/hour.
 */
void InfusionSet_SetKvoRate(float rate);

/**
 * @brief Get the KVO (Keep-Vein-Open) rate.
 * @return Current KVO rate in ml/hour.
 */
float InfusionSet_GetKVORate(void);

/**
 * @brief Set the maximum flow rate.
 * @param rate Maximum flow rate in ml/hour.
 */
void InfusionSet_SetMaxFlowRate(float rate);

/**
 * @brief Get the maximum flow rate.
 * @return Current maximum flow rate in ml/hour.
 */
float InfusionSet_GetMaxFlowRate(void);

/**
 * @brief Set the occlusion pressure.
 * @param pressure Occlusion pressure in mmHg.
 */
void InfusionSet_SetOcclusionPressure(float pressure);

/**
 * @brief Get the occlusion pressure.
 * @return Current occlusion pressure in mmHg.
 */
float InfusionSet_GetOcclusionPressure(void);

/**
 * @brief Set the air line sensitivity.
 * @param sensitivity Air line sensitivity (0-65535).
 */
void InfusionSet_SetAirLineSensitivity(uint16_t sensitivity);

/**
 * @brief Get the air line sensitivity.
 * @return Current air line sensitivity.
 */
uint16_t InfusionSet_GetAirLineSensitivity(void);

/**
 * @brief Set the infusion completion alarm setting.
 * @param setting Alarm time before completion in seconds.
 */
void InfusionSet_SetInfusionCompletionAlarmSetting(uint16_t setting);

/**
 * @brief Get the infusion completion alarm setting.
 * @return Current alarm time before completion in seconds.
 */
uint16_t InfusionSet_GetInfusionCompletionAlarmSetting(void);

#endif // INFUSIONSET_H
