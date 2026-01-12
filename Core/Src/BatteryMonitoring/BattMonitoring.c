/**
 * @file BattMonitoring.c
 * @brief Battery Monitoring Module implementation.
 *
 * This module implements battery monitoring using a FreeRTOS task and timer.
 * A one-second periodic RTOS timer calls the BatteryTimerCallback function, which retrieves the
 * latest battery information via HwBattCtrl_GetBatteryInfo and sends it to the monitoring task using a queue.
 * The BatteryMonitoringTask receives these messages and prints the battery info using EwPrint.
 * Additionally, every 4 seconds the task prints extra battery data:
 *   - HwBattCtrl_IsBatteryConnected
 *   - HwBattCtrl_GetBatteryStatus
 *   - HwBattCtrl_GetPowerSource
 *
 * A deinitialization function is provided to stop and clean up resources used by this module.
 *
 * @author
 *   Radhakrishnan Rajaram
 * @company
 *   Aria Innovation Pvt Limited
 * @version
 *   1.0.2
 * @date
 *   2025-03-27
 *
 * @copyright
 *   Copyright (c) 2025 Aria Innovation Pvt Limited. All rights reserved.
 */

#include "BattMonitoring.h"
#include "HwBattCtrl.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* External print function similar to printf */
extern void EwPrint(const char* aFormat, ...);

/* Queue handle to transfer BatteryInfo_t data */
static QueueHandle_t battInfoQueue = NULL;

/* Timer handle for periodic battery info retrieval */
static TimerHandle_t batteryTimerHandle = NULL;

/* Task handle for battery monitoring task */
static TaskHandle_t batteryMonitoringTaskHandle = NULL;

/**
 * @brief RTOS Timer callback for battery monitoring.
 *
 * This callback is executed every 1 second by the RTOS timer. It retrieves battery information
 * using HwBattCtrl_GetBatteryInfo and sends it to the monitoring task via a queue.
 *
 * @param xTimer Timer handle (unused in this callback).
 */
static void BatteryTimerCallback(TimerHandle_t xTimer)
{
    BatteryInfo_t batteryInfo;
    HwBattCtrl_GetBatteryInfo(&batteryInfo);

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xQueueSendFromISR(battInfoQueue, &batteryInfo, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/**
 * @brief Battery monitoring task.
 *
 * This task continuously receives battery information from the queue and prints it using EwPrint.
 * In addition, every 4 seconds it prints the battery connection status, battery status,
 * and active power source. The additional information is printed after checking the elapsed tick count.
 *
 * @param pvParameters Task parameter (unused).
 */
static void BatteryMonitoringTask(void *pvParameters)
{
    (void)pvParameters;
    uint32_t lastAdditionalInfoTick = xTaskGetTickCount();
    BatteryInfo_t batteryInfo;

    for (;;)
    {
        /* Block until battery info is received from the queue */
        if (xQueueReceive(battInfoQueue, &batteryInfo, portMAX_DELAY) == pdPASS)
        {
            EwPrint("Battery Info: Voltage: %u mV\r\n Temperature: %d C\r\n Charge Level: %u%%\r\n Time to Empty: %u min\r\n Time to Full: %u min\r\n Status: %u\r\n",
                    batteryInfo.voltage_mV,
                    batteryInfo.temperature_C,
                    batteryInfo.charge_level,
                    batteryInfo.time_to_empty_min,
                    batteryInfo.time_to_full_min,
                    batteryInfo.status);
        }

        /* Check if 4 seconds have elapsed */
        if ((xTaskGetTickCount() - lastAdditionalInfoTick) >= pdMS_TO_TICKS(4000))
        {
            bool batteryConnected = HwBattCtrl_IsBatteryConnected();
            BatteryStatus_t battStatus = HwBattCtrl_GetBatteryStatus();
            PowerSource_t powerSource = HwBattCtrl_GetPowerSource();

            EwPrint("Additional Info: Battery Connected: %d, Battery Status: %u, Power Source: %u\r\n",
                    batteryConnected,
                    battStatus,
                    powerSource);

            lastAdditionalInfoTick = xTaskGetTickCount();
        }
    }
}

/**
 * @brief Initialize the Battery Monitoring Module.
 *
 * This function performs the following actions:
 *  - Calls HwBattCtrl_Init() to initialize the battery control hardware.
 *  - Creates a FreeRTOS queue to hold BatteryInfo_t messages.
 *  - Creates a battery monitoring task that prints battery information.
 *  - Creates and starts an RTOS timer with a 1-second period that retrieves battery info.
 *
 * @return int 0 on success, -1 on error.
 */
int BattMonitoring_Init(void)
{
    int status = 0;

    /* Initialize the Battery Control Hardware */
    status = HwBattCtrl_Init();
    if (status != 0)
    {
        EwPrint("HwBattCtrl_Init failed with status: %d\r\n", status);
        return -1;
    }

    /* Create the queue for battery information (queue length: 10 messages) */
    battInfoQueue = xQueueCreate(10, sizeof(BatteryInfo_t));
    if (battInfoQueue == NULL)
    {
        EwPrint("Failed to create battery info queue\r\n");
        return -1;
    }

    /* Create the Battery Monitoring Task */
    if (xTaskCreate(BatteryMonitoringTask, "BattMonTask", configMINIMAL_STACK_SIZE + 256, NULL, tskIDLE_PRIORITY + 1, &batteryMonitoringTaskHandle) != pdPASS)
    {
        EwPrint("Failed to create Battery Monitoring Task\r\n");
        return -1;
    }

    /* Create a periodic timer that triggers every 1 second */
    batteryTimerHandle = xTimerCreate("BattTimer", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, BatteryTimerCallback);
    if (batteryTimerHandle == NULL)
    {
        EwPrint("Failed to create Battery Timer\r\n");
        return -1;
    }

    /* Start the timer */
    if (xTimerStart(batteryTimerHandle, 0) != pdPASS)
    {
        EwPrint("Failed to start Battery Timer\r\n");
        return -1;
    }

    return 0;
}

/**
 * @brief Deinitialize the Battery Monitoring Module.
 *
 * This function stops and deletes the RTOS timer, deletes the battery information queue,
 * and deletes the battery monitoring task.
 *
 * @return int 0 on success, -1 on error.
 */
int BattMonitoring_Deinit(void)
{
    /* Stop and delete the timer */
    if (batteryTimerHandle != NULL)
    {
        if (xTimerStop(batteryTimerHandle, 0) != pdPASS)
        {
            EwPrint("Failed to stop Battery Timer\r\n");
            return -1;
        }
        if (xTimerDelete(batteryTimerHandle, 0) != pdPASS)
        {
            EwPrint("Failed to delete Battery Timer\r\n");
            return -1;
        }
        batteryTimerHandle = NULL;
    }

    /* Delete the queue */
    if (battInfoQueue != NULL)
    {
        vQueueDelete(battInfoQueue);
        battInfoQueue = NULL;
    }

    /* Delete the battery monitoring task */
    if (batteryMonitoringTaskHandle != NULL)
    {
        vTaskDelete(batteryMonitoringTaskHandle);
        batteryMonitoringTaskHandle = NULL;
    }

    return 0;
}
