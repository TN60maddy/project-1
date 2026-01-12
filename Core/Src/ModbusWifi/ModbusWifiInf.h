/**
 ******************************************************************************
 * @file    ModbusWifiInf.h
 * @brief   Header file for the Modbus WiFi Infusion module.
 *
 * This file declares the public function for initializing the Modbus
 * WiFi Infusion module.
 *
 * Device parameters, infusion parameters, and network parameters are mapped
 * to a register table, whose layout is detailed in the implementation file.
 *
 * @author
 *          Radhakrishnan Rajaram
 * @company
 *          Aria Innovations Pvt Ltd
 * @version
 *          1.3
 * @date
 *          2025-04-09
 * @copyright Copyright (c) 2025 Aria Innovations Pvt Ltd.
 *            All rights reserved.
 ******************************************************************************
 */

#ifndef MODBUSWIFIINF_H
#define MODBUSWIFIINF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "modbus.h"  // Referencing definitions from modbus.h

#define MODBUSWIFIINF_VERSION "1.3"

/**
 * @brief Initializes the Modbus WiFi Infusion module.
 *
 * This function calls Modbus_Init on the UART4 channel and registers the process
 * function that handles Modbus requests.
 *
 * @return int16_t 0 on success; nonzero on error.
 */
int16_t ModbusWifiInf_Init(void);

#ifdef __cplusplus
}
#endif

#endif // MODBUSWIFIINF_H
