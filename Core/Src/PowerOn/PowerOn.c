

/*
 * @file    poweron.c
 * @brief   Power On/Off control implementation with debounce and FreeRTOS support
 * @company Aria Innovations Pvt Ltd
 * @author  Radhakrishnan Rajaram
 * @version 1.2
 * @date    2025-06-27
 * @copyright © 2025 Aria Innovations Pvt Ltd. All rights reserved.
 */

#include "poweron.h"

/* FreeRTOS semaphore handle for button events */
static SemaphoreHandle_t xPowerButtonSemaphore = NULL;

/* Forward declaration of the task function */
static void PowerOn_Task(void *pvParameters);

/**
 * @brief  Initialize GPIO pins and EXTI for the power button, plus power latch output.
 */
void PowerOn_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Enable GPIO clocks */
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    /* Configure power button (PG7) as input with EXTI interrupt on rising edge */
    GPIO_InitStruct.Pin  = SYS_PWR_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SYS_PWR_GPIO_PORT, &GPIO_InitStruct);

    /* Enable and set EXTI line interrupt priority */
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    /* Configure power latch (PH4) as output push-pull */
    GPIO_InitStruct.Pin   = SYS_PWR_ON_OFF_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SYS_PWR_ON_OFF_PORT, &GPIO_InitStruct);
    HAL_Delay( 1000 );


    /*while( 1 )
    {
    	if (HAL_GPIO_ReadPin(SYS_PWR_GPIO_PORT, SYS_PWR_GPIO_PIN) == GPIO_PIN_RESET) {
    		HAL_Delay( 100 );
    	    	} else {
    	    	break;
    	    	}
    }*/
    /* Ensure power latch is ON by default */
    HAL_GPIO_WritePin(SYS_PWR_ON_OFF_PORT, SYS_PWR_ON_OFF_PIN, GPIO_PIN_SET);
    HAL_Delay( 1000 );


}

/**
 * @brief  Create semaphore and start the PowerOn task.
 */
void PowerOn_Start(void)
{
    /* Create a binary semaphore for button press events */
    xPowerButtonSemaphore = xSemaphoreCreateBinary();
    configASSERT(xPowerButtonSemaphore != NULL);

    /* Create the task to handle debounce and shutdown */
    xTaskCreate(
        PowerOn_Task,          /* Task function */
        "PowerOnTask",        /* Name */
        128,                   /* Stack depth */
        NULL,                  /* Parameters */
        tskIDLE_PRIORITY + 4,  /* Priority */
        NULL                   /* Task handle */
    );
}


/**
 * @brief  FreeRTOS task to debounce the power button and initiate shutdown.
 * @param  pvParameters Not used.
 */
static void PowerOn_Task(void *pvParameters)
{
	static int count = 0;
	while( 1 )
	{
		if (HAL_GPIO_ReadPin(SYS_PWR_GPIO_PORT, SYS_PWR_GPIO_PIN) == GPIO_PIN_RESET) {

	    	vTaskDelay( pdMS_TO_TICKS (100 ) );
				} else {
				break;
				}
	}
    (void) pvParameters;
    for (;;)
    {

    	vTaskDelay( pdMS_TO_TICKS (100 ) );
    	if (HAL_GPIO_ReadPin(SYS_PWR_GPIO_PORT, SYS_PWR_GPIO_PIN) == GPIO_PIN_RESET) {
    	   count++;
    	} else {
    		count=0;
    	    // pin is high
    	}

#if 0
        /* Wait indefinitely for button event */
        if (xSemaphoreTake(xPowerButtonSemaphore, portMAX_DELAY) == pdTRUE)
        {
            /* Debounce delay */
            vTaskDelay(pdMS_TO_TICKS(BUTTON_DEBOUNCE_MS));

            /* Placeholder: call external shutdown sequence */
            //extern void External_ShutdownProcess(void);
            //External_ShutdownProcess();

            /* Switch off power latch */
            HAL_GPIO_WritePin(SYS_PWR_ON_OFF_PORT, SYS_PWR_ON_OFF_PIN, GPIO_PIN_RESET);
        }
#endif
        if( 20 <= count )
        {
        	   HAL_GPIO_WritePin(SYS_PWR_ON_OFF_PORT, SYS_PWR_ON_OFF_PIN, GPIO_PIN_RESET);
        }
    }
}
void PowerOn_handleIntr( void )
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xPowerButtonSemaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
/**
 * @brief  IRQ handler for EXTI lines 9 to 5 (covers PG7).
 */
void EXTI9_5_IRQnHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(SYS_PWR_GPIO_PIN);
}
