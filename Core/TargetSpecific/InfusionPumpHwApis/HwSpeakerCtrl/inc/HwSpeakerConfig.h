/*
 * HwSpeakerCtrl.h
 *
 */

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_sai.h"

#ifndef HWAPIS_HWSPEAKERCTRL_INC_HWSPEAKERCONFIG_H_
#define HWAPIS_HWSPEAKERCTRL_INC_HWSPEAKERCONFIG_H_



/* Definitions for Speaker */

#define HWSPEAKER_SAI_CLK_ENABLE()                         __HAL_RCC_SAI1_CLK_ENABLE()
#define HWSPEAKER_SAI_CLK_DISABLE()                        __HAL_RCC_SAI1_CLK_DISABLE()
#define HWSPEAKER_PERIPHCLK_SEL()                            RCC_PERIPHCLK_SAI1
#define HWSPEAKER_SAI_CLKSRC_SEL()                          RCC_SAI1CLKSOURCE_PLL


#define HWSPEAKER_SAI_BLOCK 									    SAI1_Block_A
#define HWSPEAKER_SAI_BLOCKMODE 							SAI_MODEMASTER_TX
#define HWSPEAKER_SAI_SYNC                                        SAI_ASYNCHRONOUS
#define HWSPEAKER_SAI_OUTPUT_DRIVE                        SAI_OUTPUTDRIVE_ENABLE
#define HWSPEAKER_SAI_BLOCK_DIV                              SAI_MASTERDIVIDER_ENABLE
#define HWSPEAKER_SAI_BLOCK_FIFO                            SAI_FIFOTHRESHOLD_EMPTY
#define HWSPEAKER_SAI_EXT_SYNC                                SAI_SYNCEXT_DISABLE
#define HWSPEAKER_SAI_MONOSTEREO_MODE             SAI_MONOMODE
#define HWSPEAKER_SAI_BLOCK_COM_MODE                SAI_NOCOMPANDING
#define HWSPEAKER_SAI_TRISTATE_MGT                         SAI_OUTPUT_NOTRELEASED
#define HWSPEAKER_SAMPLINGRATE 								SAI_AUDIO_FREQUENCY_48K
#define HWSPEAKER_SAI_PROTOCOL 								SAI_I2S_STANDARD
#define HWSPEAKER_SAI_DATASIZE 								SAI_PROTOCOL_DATASIZE_16BIT


/*  Definitions used for Speaker DMA */

#define HWSPEAKER_DMA_CLK_ENABLE                         __HAL_RCC_DMA1_CLK_ENABLE


#define HWSPEAKER_DMA_STREAM                                      DMA1_Stream0
#define HWSPEAKER_DMA_REQUEST                                     DMA_REQUEST_SAI1_A
#define HWSPEAKER_DMA_TRANSFER_DIR 							 DMA_MEMORY_TO_PERIPH
#define HWSPEAKER_DMA_PERIPHERAL_INC_MODE 			 DMA_PINC_DISABLE
#define HWSPEAKER_DMA_MEM_INC_MODE                        DMA_MINC_ENABLE
#define HWSPEAKER_DMA_PERIPHERAL_DAT_SZ                DMA_PDATAALIGN_HALFWORD
#define HWSPEAKER_DMA_MEM_DATA_SZ                           DMA_MDATAALIGN_HALFWORD
#define HWSPEAKER_DMA_MODE                 						     DMA_CIRCULAR
#define HWSPEAKER_DMA_PRIORITY_LVL                             DMA_PRIORITY_LOW
#define HWSPEAKER_DMA_FIFO_MODE                                 DMA_FIFOMODE_ENABLE
#define HWSPEAKER_DMA_FIFO_THRESHOLD                      DMA_FIFO_THRESHOLD_FULL
#define HWSPEAKER_DMA_MEMBURST                                 DMA_MBURST_SINGLE
#define HWSPEAKER_DMA_PBURST                                        DMA_PBURST_SINGLE


/*  Definitions of Speaker GPIO Pins */

#define HWSPEAKER_SCKGPIOCLK_ENABLE() 			__HAL_RCC_GPIOE_CLK_ENABLE()
#define HWSPEAKER_FSGPIOCLK_ENABLE() 				__HAL_RCC_GPIOE_CLK_ENABLE()
#define HWSPEAKER_SDAGPIOCLK_ENABLE() 	        __HAL_RCC_GPIOE_CLK_ENABLE()
#define HWSPEAKER_SDBGPIOCLK_ENABLE()          __HAL_RCC_GPIOE_CLK_ENABLE()

#define HWSPEAKER_GPIOCLK_ENABLE()          __HAL_RCC_GPIOE_CLK_ENABLE()
#define HWSPEAKER_GPIOCLK_DISABLE()          __HAL_RCC_GPIOE_CLK_DISABLE()



#define HWSPEAKER_SCK_PORT 								GPIOE
#define HWSPEAKER_SCK_PIN                                  GPIO_PIN_5

#define HWSPEAKER_FS_PORT 								    GPIOE
#define HWSPEAKER_FS_PIN  									GPIO_PIN_4

#define HWSPEAKER_SDA_PORT 								GPIOE
#define HWSPEAKER_SDA_PIN  								GPIO_PIN_6

#define HWSPEAKER_SDB_PORT 								GPIOE
#define HWSPEAKER_SDB_PIN 									 GPIO_PIN_3

#define HWSPEAKER_MCLK_PORT                            GPIOG
#define HWSPEAKER_MCLK_PIN                                GPIO_PIN_7

#define HWSPEAKER_MCO_PORT                            GPIOA
#define HWSPEAKER_MCO_PIN                                GPIO_PIN_8


#define HWSPEAKER_GPIO_MODE                             GPIO_MODE_AF_PP
#define HWSPEAKER_GPIO_PULL                               GPIO_NOPULL
#define HWSPEAKER_GPIO_OUT_FREQ                      GPIO_SPEED_FREQ_LOW
#define HWSPEAKER_GPIO_PIN_ALTERNATE 			  GPIO_AF6_SAI1

#define HWSPEAKER_GPIO_PORT                                GPIOE





#endif /* HWAPIS_HWSPEAKERCTRL_INC_HWSPEAKERCONFIG_H_ */
