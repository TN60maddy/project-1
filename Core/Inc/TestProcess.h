/**
  ******************************************************************************
  * @file    TestProcess.h
  * @brief   Header file for the TestProcess task.
  * @author
  *          Radhakrishnan Rajaram
  * @company Aria Innovations Pvt Ltd.
  * @version 1.0
  * @date    2025-02-06
  * @details This task processes Modbus requests (read and write) received via queue.
  *          The read operation supports registers 1 to 1000 and the write operation supports
  *          registers 1000 to 1100.
  ******************************************************************************
  * @attention
  *   Modify register ranges as necessary for your application.
  ******************************************************************************
  */

#ifndef TESTPROCESS_H
#define TESTPROCESS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Modbus.h"

/**
  * @brief Task for processing Modbus requests.
  *
  * This task receives Modbus requests from the queue, verifies that
  * the requested register addresses are within valid ranges, performs
  * read or write operations on simulated registers, and posts a response.
  *
  * Valid ranges:
  * - Read (FC 0x03): Registers 1 to MODBUS_READ_REGISTER_COUNT.
  * - Write (FC 0x10): Registers MODBUS_WRITE_START_ADDRESS to MODBUS_WRITE_END_ADDRESS.
  *
  * @param pvParameters Not used.
  */
void TestProcess_Task(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif /* TESTPROCESS_H */
