/*
 * Uart.c
 *
 */

#include "stm32h7xx_hal.h"
#include "Uart.h"

UART_HandleTypeDef huart_uart4;
UART_HandleTypeDef huart_usart1;
UART_HandleTypeDef huart_uart7;


int MX_USART1_Init(void)
{
	int retStatus = 0;
	huart_usart1.Instance = HW_STM_RENESAS_UART;
	huart_usart1.Init.BaudRate = HW_STM_RENESAS_UART_BAUDRATE;
	huart_usart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart_usart1.Init.StopBits = HW_STM_RENESAS_UART_STOPBITS;
	huart_usart1.Init.Parity = HW_STM_RENESAS_UART_PARITY;
	huart_usart1.Init.Mode = UART_MODE_TX_RX;
	huart_usart1.Init.HwFlowCtl = HW_STM_RENESAS_UART_HWFLOWCTRL;
	huart_usart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart_usart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart_usart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart_usart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart_usart1) != HAL_OK)
	{
		retStatus = -1;
	}

	if (HAL_UARTEx_SetTxFifoThreshold(&huart_usart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		retStatus = -1;
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart_usart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		retStatus = -1;
	}
	if (HAL_UARTEx_DisableFifoMode(&huart_usart1) != HAL_OK)
	{
		retStatus = -1;
	}

	return retStatus;
}

int MX_UART4_Init(void)
{

	int retStatus = 0;
	huart_uart4.Instance = HW_STM_WIFI_UART;
	huart_uart4.Init.BaudRate = HW_STM_WIFI_UART_BAUDRATE;
	huart_uart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart_uart4.Init.StopBits = HW_STM_WIFI_UART_STOPBITS;
	huart_uart4.Init.Parity = HW_STM_WIFI_UART_PARITY;
	huart_uart4.Init.Mode = UART_MODE_TX_RX;
	huart_uart4.Init.HwFlowCtl = HW_STM_WIFI_UART_HWFLOWCTRL;
	huart_uart4.Init.OverSampling = UART_OVERSAMPLING_16;
	huart_uart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart_uart4.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart_uart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart_uart4) != HAL_OK)
	{
		retStatus = -1;
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart_uart4, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		retStatus = -1;
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart_uart4, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		retStatus = -1;
	}
	if (HAL_UARTEx_DisableFifoMode(&huart_uart4) != HAL_OK)
	{
		retStatus = -1;
	}

	return retStatus;
}

int MX_UART7_Init(void)
{
	int retStatus = 0;
	huart_uart7.Instance = HW_STM_DEBUG_UART;
	huart_uart7.Init.BaudRate = HW_STM_DEBUG_UART_BAUDRATE;
	huart_uart7.Init.WordLength = UART_WORDLENGTH_8B;
	huart_uart7.Init.StopBits = HW_STM_DEBUG_UART_STOPBITS;
	huart_uart7.Init.Parity = HW_STM_DEBUG_UART_PARITY;
	huart_uart7.Init.Mode = UART_MODE_TX_RX;
	huart_uart7.Init.HwFlowCtl = HW_STM_DEBUG_UART_HWFLOWCTRL;
	huart_uart7.Init.OverSampling = UART_OVERSAMPLING_16;
	huart_uart7.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart_uart7.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart_uart7.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart_uart7) != HAL_OK)
	{
		retStatus = -1;
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart_uart7, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		retStatus = -1;
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart_uart7, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		retStatus = -1;
	}
	if (HAL_UARTEx_DisableFifoMode(&huart_uart7) != HAL_OK)
	{
		retStatus = -1;
	}	

	return retStatus;
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{

  GPIO_InitTypeDef  GPIO_InitStruct;

  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};


  if(huart->Instance == UART7)
	{
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART7;
		PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;

		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		{

		}

		/* Peripheral clock enable */
		HW_STM_DEBUG_UART_CLK_ENABLE();
		HW_STM_DEBUG_UART_RX_GPIO_CLK_ENABLE();
		HW_STM_DEBUG_UART_TX_GPIO_CLK_ENABLE();


		GPIO_InitStruct.Pin = HW_STM_DEBUG_UART_TX_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = HW_STM_DEBUG_UART_RX_TX_AF;
		HAL_GPIO_Init(HW_STM_DEBUG_UART_TX_GPIO_PORT_TX, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = HW_STM_DEBUG_UART_RX_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF11_UART7;
		HAL_GPIO_Init(HW_STM_DEBUG_UART_RX_GPIO_PORT_RX, &GPIO_InitStruct);

		/* USART1 interrupt Init */
		HAL_NVIC_SetPriority(UART7_IRQn, 6, 0);
		HAL_NVIC_EnableIRQ(UART7_IRQn);
	}

	if(huart->Instance == UART4)
	{
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART4;
		PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		{

		}
		/* Peripheral clock enable */
		HW_STM_WIFI_UART_CLK_ENABLE();

		HW_STM_WIFI_UART_RX_TX_GPIO_CLK_ENABLE();

		GPIO_InitStruct.Pin = HW_STM_WIFI_UART_RX_PIN|HW_STM_WIFI_UART_TX_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = HW_STM_WIFI_UART_RX_TX_AF;
		HAL_GPIO_Init(HW_STM_WIFI_UART_RX_TX_GPIO_PORT, &GPIO_InitStruct);


		/* UART4 interrupt Init */
			HAL_NVIC_SetPriority(UART4_IRQn, 6, 0);
			HAL_NVIC_EnableIRQ(UART4_IRQn);
	}
	if(huart->Instance == USART1)
	{
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
		PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		{

		}

		/* Peripheral clock enable */
		HW_STM_RENESAS_UART_CLK_ENABLE();

		HW_STM_RENESAS_UART_RX_TX_GPIO_CLK_ENABLE();

		GPIO_InitStruct.Pin = HW_STM_RENESAS_UART_RX_PIN|HW_STM_RENESAS_UART_TX_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = HW_STM_RENESAS_UART_RX_TX_AF;
		HAL_GPIO_Init(HW_STM_RENESAS_UART_RX_TX_GPIO_PORT, &GPIO_InitStruct);

		/* USART1 interrupt Init */
		HAL_NVIC_SetPriority(USART1_IRQn, 6, 0);
	    HAL_NVIC_EnableIRQ(USART1_IRQn);
	}
}

