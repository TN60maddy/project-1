/*
 * HwTCA9546_MuxConfig.h
 */

#ifndef INC_HWI2CMUXCONFIG_H_
#define INC_HWI2CMUXCONFIG_H_

#define BUS_I2C1_FREQUENCY 0

#define HwI2CMux_CLK_ENABLE()        __HAL_RCC_I2C1_CLK_ENABLE();
#define HwI2CMux_CLK_DISABLE()       __HAL_RCC_I2C1_CLK_DISABLE()
#define HwI2CMux_SCL_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE();
#define HwI2CMux_SDA_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE();
#define HwI2CMux_SCL_CLK_DISABLE()  __HAL_RCC_GPIOB_CLK_DISABLE();
#define HwI2CMux_SDA_CLK_DISABLE()  __HAL_RCC_GPIOB_CLK_DISABLE();


#define HwI2CMux_FORCE_RESET         __HAL_RCC_I2C1_FORCE_RESET()
#define HwI2CMux_RELEASE_RESET        __HAL_RCC_I2C1_RELEASE_RESET()



/* Definition for Pressure Sensor 1  */
#define HwI2CMux_I2C                             I2C1
#define HwI2CMux_SDA_PORT                        GPIOB
#define HwI2CMux_SDA_PIN                         GPIO_PIN_7
#define HwI2CMux_SCL_PORT                        GPIOB
#define HwI2CMux_SCL_PIN                         GPIO_PIN_6

#define HwI2CMux_PIN_MODE                        GPIO_MODE_AF_OD
#define HwI2CMux_PIN_PULLUP                      GPIO_NOPULL
#define HwI2CMux_PIN_SPEED                       GPIO_SPEED_FREQ_LOW
#define HwI2CMux_PIN_ALTERNATE                   GPIO_AF6_I2C4
#define HwI2CMux_GPIO_PORT                       GPIOB
#define HwI2CMux_SCL_ALT_FUN                     GPIO_AF4_I2C1
#define HwI2CMux_SDA_ALT_FUN                     GPIO_AF4_I2C1


#ifndef BUS_I2C1_FREQUENCY
   #define BUS_I2C1_FREQUENCY  100000U                 /* Frequency of I2Cn = 100 KHz*/
#endif

#define HwI2CMux_TIMING_PARAMETER                 0x00707CBB
#define HwI2CMux_ADDRESS_MODE                     I2C_ADDRESSINGMODE_7BIT
#define HwI2CMux_PER_CLOCK                        RCC_PERIPHCLK_I2C1
#define HwI2CMux_PER_CLOCK_SRC                    RCC_I2C123CLKSOURCE_D2PCLK1





#endif /* INC_HWI2CMUXCONFIG_H_ */
