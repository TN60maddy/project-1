/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <TestPressure.h>
#include "main.h"
#include "string.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "ewmain.h"
#include "ewrte.h"
#include "ew_bsp_system.h"
#include "ew_bsp_console.h"
#include "ew_bsp_os.h"
#include "ew_bsp_inout.h"
#include "InfDevice.h"
#include "../../BSP/Components/tsc2007/tsc2007.h"
#include "../../BSP/STM32H743I-EVAL/stm32h743i_eval_lcd.h"


#include "stm32h7xx_hal.h"     // HAL header for STM32H7 series
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "HwDoorPositionSensor.h"
#include "HwBacklightCtrl.h"
#include "HwStepperCtrl.h"
#include "KeyListner.h"
#include "DoorHandler.h"
#include "Modbus.h"
#include "TestProcess.h"
#include "usb_device.h"

#include "ModbusWifiInf.h"
#include "ModbusInfusion.h"
#include "InfDevice.h"
#include "PowerOn.h"

#include "BattMonitoring.h"
#include "HwBattCtrl.h"
#include "DeviceParam.h"


/* --- External Hardware API declarations --- */
/* These functions and types are assumed to be defined in your hardware libraries. */


extern  void LCD_Init( void );
extern void TSC2007_GPIO_Init();

/** @def MODBUS_TASK_STACK_SIZE
  * @brief Stack size for the Modbus task.
  */

#define MODBUS_TASK_STACK_SIZE       512U
/** @def TESTPROCESS_TASK_STACK_SIZE
  * @brief Stack size for the TestProcess task.
  */
#define TESTPROCESS_TASK_STACK_SIZE  512U
/** @def MODBUS_TASK_PRIORITY
  * @brief Priority for the Modbus task.
  */
#define MODBUS_TASK_PRIORITY         (tskIDLE_PRIORITY + 2U)
/** @def TESTPROCESS_TASK_PRIORITY
  * @brief Priority for the TestProcess task.
  */
#define TESTPROCESS_TASK_PRIORITY    (tskIDLE_PRIORITY + 1U)



/* --- Message IDs for the timers --- */
#define DOOR_TIMER_MSG      1
#define TEN_SEC_TIMER_MSG   2

/* --- Global FreeRTOS objects --- */
//static QueueHandle_t xDoorQueue = NULL;
static void MX_GPIO_Init(void);



/* Private includes ----------------------------------------------------------*/
static char msgBuf[128] = "infusion_pump";
//msgBuf={"infusion_pump"};

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/


static void GuiThread( const void* arg );
//static void DoorSensorTest(void);

//static void vDoorMonitoringTask(void *pvParameters);

/* --------------------------------------------------------------------
 * Replacement of HAL_Delay() that is RTOS-aware
 * ------------------------------------------------------------------*/
/* --------------------------------------------------------------------------
   Replacement HAL_Delay() – works
   • before scheduler starts (after tasks are created)
   • after scheduler starts
   • still fine in bare-metal builds if you ever drop FreeRTOS
   -------------------------------------------------------------------------- */

/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
   EwBspSystemInit();
   MX_GPIO_Init();


   __HAL_RCC_GPIOG_CLK_ENABLE();

   // 4. Configure PG14 as open‑drain output, no pull‑up/down, low speed
   GPIO_InitTypeDef GPIO_InitStruct = {0};
   GPIO_InitStruct.Pin   = GPIO_PIN_14;
   GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
   GPIO_InitStruct.Pull  = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

   // 5. Set PG14 HIGH (open‑drain: the line will float high if you have an external pull‑up)
   HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);

	  /* initialize console interface for debug messages */
   EwBspConsoleInit();

  MX_USB_GPIO_Init();
 MX_USB_DEVICE_Init();


// HAL_Delay(1000);
 PowerOn_Init( );
int s1 = HwPressureSensorInit(HW_PRESSURE_NUM_1);
   int s2 = HwPressureSensorInit(HW_PRESSURE_NUM_2);
   if (s1 != 0 || s2 != 0) {
     snprintf(msgBuf, sizeof(msgBuf),
              "Pressure sensor init failed (S1=%d, S2=%d)", s1, s2);
     EwPrint(msgBuf);
   } else {
     EwPrint("Pressure sensors ready");
   }
 BattMonitoring_Init( );
 PowerOn_Start( );


 InfDevice_InitWithSelfTest( );
 DeviceParam_Init( );
 ModbusWifiInf_Init( );
 ModbusInfusion_Init( );

EwBspOsThreadCreate( GuiThread, EW_BSP_OS_THREAD_PRIORITY_NORMAL, EW_GUI_THREAD_STACK_SIZE, 0 );

/* Initialize DoorHandle module */
DoorHandlerInit();
  //TestPressure_Init( );
   /* Initialize KeyListner module */
KeyListnerInit();

  /* ...and start scheduler */

 EwBspOsStartScheduler();

  /* restore console */
  EwBspConsoleDone();

  /* terminate the system */
  EwBspSystemDone();



  while (1)
  {
  }

}



/**
  * @brief  Initializes the GPIO pins.
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
}


void Error_Handler(void)
{

  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }

}
/*******************************************************************************
* FUNCTION:
*   GuiThread
*
* DESCRIPTION:
*   The EwThread processes the Embeded Wizard application.
*
* ARGUMENTS:
*   arg - not used.
*
* RETURN VALUE:
*   None.
*
*******************************************************************************/
static void GuiThread( const void* arg )
{
  unsigned int stack;

  /* determine the stack area and provide it to the Runtime Environmnet */
  EwSetStackAddressArea( &stack, (void*)((unsigned int)&stack - EW_GUI_THREAD_STACK_SIZE ));

  /* initialize Embedded Wizard application */
  LCD_Init( );
  LCD_BKLIGHTCTRL_Init();
  TSC2007_GPIO_Init();
  if ( EwInit() == 0 )
    return;

  EwPrintSystemInfo();

  /* process the Embedded Wizard main loop */
  while( EwProcess());

  /* de-initialize Embedded Wizard application */
  EwDone();



}
/* main.c - STM32H753 example using FreeRTOS with two timers */








#if ( configSUPPORT_STATIC_ALLOCATION == 1 )
/*
 * The following function is required to provide the memory that is used by the Timer service task.
 * This implementation statically allocates the TCB and stack for the Timer task.
 */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
    /* Allocate statically the Timer task TCB. */
    static StaticTask_t xTimerTaskTCB;

    /* Allocate statically the Timer task stack. */
    static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out pointers to the static memory. */
    *ppxTimerTaskTCBBuffer   = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize   = configTIMER_TASK_STACK_DEPTH;
}
#endif /* configSUPPORT_STATIC_ALLOCATION */

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
