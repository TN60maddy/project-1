/*
 * Uart.h
 *
 */

#ifndef INC_HWUARTCONFIG_H_
#define INC_HWUARTCONFIG_H_


#define HW_STM_WIFI_UART                           UART4
#define HW_STM_WIFI_UART_BAUDRATE		           115200
#define HW_STM_WIFI_UART_STOPBITS                  UART_STOPBITS_1
#define HW_STM_WIFI_UART_PARITY			           UART_PARITY_NONE
#define HW_STM_WIFI_UART_HWFLOWCTRL			       UART_HWCONTROL_NONE

#define HW_STM_WIFI_UART_CLK_ENABLE()              __HAL_RCC_UART4_CLK_ENABLE()
#define HW_STM_WIFI_UART_RX_TX_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()


#define HW_STM_WIFI_UART_TX_PIN                    GPIO_PIN_0
#define HW_STM_WIFI_UART_RX_TX_GPIO_PORT           GPIOA
#define HW_STM_WIFI_UART_RX_TX_AF                  GPIO_AF8_UART4
#define HW_STM_WIFI_UART_RX_PIN                    GPIO_PIN_1


//STM to Renasis Uart Configurations

#define HW_STM_RENESAS_UART                        USART1
#define HW_STM_RENESAS_UART_BAUDRATE               115200
#define HW_STM_RENESAS_UART_STOPBITS               UART_STOPBITS_1
#define HW_STM_RENESAS_UART_PARITY                 UART_PARITY_NONE
#define HW_STM_RENESAS_UART_HWFLOWCTRL             UART_HWCONTROL_NONE

#define HW_STM_RENESAS_UART_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE()
#define HW_STM_RENESAS_UART_RX_TX_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()


#define HW_STM_RENESAS_UART_TX_PIN                 GPIO_PIN_14
#define HW_STM_RENESAS_UART_RX_TX_GPIO_PORT        GPIOB
#define HW_STM_RENESAS_UART_RX_TX_AF               GPIO_AF4_USART1
#define HW_STM_RENESAS_UART_RX_PIN                 GPIO_PIN_15

//STM Debug Uart Configurations

#define HW_STM_DEBUG_UART                          UART7
#define HW_STM_DEBUG_UART_BAUDRATE                 115200
#define HW_STM_DEBUG_UART_STOPBITS                 UART_STOPBITS_1
#define HW_STM_DEBUG_UART_PARITY                   UART_PARITY_NONE
#define HW_STM_DEBUG_UART_HWFLOWCTRL               UART_HWCONTROL_NONE

#define HW_STM_DEBUG_UART_CLK_ENABLE()             __HAL_RCC_UART7_CLK_ENABLE()
#define HW_STM_DEBUG_UART_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define HW_STM_DEBUG_UART_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
/* Definition for UART7 Pins */
#define HW_STM_DEBUG_UART_TX_PIN                   GPIO_PIN_15
#define HW_STM_DEBUG_UART_TX_GPIO_PORT_TX      	   GPIOA
#define HW_STM_DEBUG_UART_RX_GPIO_PORT_RX          GPIOB
#define HW_STM_DEBUG_UART_RX_TX_AF                 GPIO_AF11_UART7
#define HW_STM_DEBUG_UART_RX_PIN                   GPIO_PIN_3


int MX_USART1_Init(void);
int MX_UART4_Init(void);
int MX_UART7_Init(void);



#endif /* INC_UART_H_ */
