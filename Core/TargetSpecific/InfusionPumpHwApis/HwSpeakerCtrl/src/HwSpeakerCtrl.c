/*******************************************************************************
*
*    INFUSION PUMP PROJECT
*
*                                    Copyright (c) Aria Innovations
*
*
*
********************************************************************************
*
* DESCRIPTION:
*   This file implements a generic HW Interface of Speaker used in Infusion Pump
*
********************************************************************************/



#include "../inc/HwSpeakerCtrl.h"
#include "../inc/HwSpeakerConfig.h"
#include "stm32h7xx_hal_sai.h"
#include "math.h"

/* Handlers for Speaker */
SAI_HandleTypeDef HwSpeaker_handler;
DMA_HandleTypeDef HwSpeaker_dmahandler;


/* Private Function Declaration */

static int HwSpeaker_MspDeInit(void);
static void HwSpeaker_DMA_Init(void);


// Private Definitions

typedef struct {
    const unsigned char *buffer;  // Pointer to the raw audio data
    uint32_t totalSize;           // Total size of the raw audio data
    uint32_t currentOffset;       // Current read offset in the audio data
    uint8_t isPlaying;            // Flag to indicate if audio is playing
    float volume;                 // Volume level (0.0 to 1.0)
} AudioPlayback_t;

#define CHUNK_SIZE 1024  // Define the size of each chunk for DMA transfer

static AudioPlayback_t audioPlayback;
static uint8_t buffer0[CHUNK_SIZE];  // First buffer for double buffering
static uint8_t buffer1[CHUNK_SIZE];  // Second buffer for double buffering
static volatile uint8_t currentBuffer = 0;  // Track the current buffer being used


/**
  * Enable DMA controller clock
  */
static void HwSpeaker_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

}

static int HwSpeaker_MspDeInit(void)
{
/* Peripheral Clock Disable */

	HWSPEAKER_SAI_CLK_DISABLE();

    /* DeInitialize  GPIO Configuration used for Speaker */
    HAL_GPIO_DeInit(HWSPEAKER_GPIO_PORT, HWSPEAKER_SCK_PIN|HWSPEAKER_FS_PIN|HWSPEAKER_SDA_PIN|HWSPEAKER_SDB_PIN);

    HAL_GPIO_DeInit(HWSPEAKER_MCLK_PORT, HWSPEAKER_MCLK_PIN);

    /* SPEAKER DMA De init */
    HAL_DMA_DeInit(HwSpeaker_handler.hdmarx);
    HAL_DMA_DeInit(HwSpeaker_handler.hdmatx);

    return 0;

}

/**
  * @brief Initializes the SAI (Serial Audio Interface) to control the speaker.
  *        This function configures the SAI peripheral, sets up the audio interface,
  *        and prepares the speaker for playback.
  * @param void
  * * @retval int
  *         0 = Success (SAI interface and speaker initialized successfully).
  *         1 = Failure (Initialization failed due to an error).
  */



int HwSpeakerInit(void)
{
	      /* USER CODE BEGIN SAI1_Init 0 */
		  GPIO_InitTypeDef GPIO_InitStruct;
		  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

		  /* Initialize the DMA Clock */
		  __HAL_RCC_SAI1_CLK_ENABLE();
	       HwSpeaker_DMA_Init();

	  /* SPEAKER _Init 1 */
	HwSpeaker_handler.Instance = HWSPEAKER_SAI_BLOCK;
	HwSpeaker_handler.Init.AudioMode = HWSPEAKER_SAI_BLOCKMODE;
	HwSpeaker_handler.Init.Synchro = HWSPEAKER_SAI_SYNC;
	HwSpeaker_handler.Init.OutputDrive = HWSPEAKER_SAI_OUTPUT_DRIVE;
	HwSpeaker_handler.Init.NoDivider = HWSPEAKER_SAI_BLOCK_DIV;
	HwSpeaker_handler.Init.FIFOThreshold = HWSPEAKER_SAI_BLOCK_FIFO;
	HwSpeaker_handler.Init.AudioFrequency = HWSPEAKER_SAMPLINGRATE;//SAI_AUDIO_FREQUENCY_16K;
	HwSpeaker_handler.Init.SynchroExt = HWSPEAKER_SAI_EXT_SYNC;
	HwSpeaker_handler.Init.MonoStereoMode = HWSPEAKER_SAI_MONOSTEREO_MODE;
	HwSpeaker_handler.Init.CompandingMode = HWSPEAKER_SAI_BLOCK_COM_MODE;
	HwSpeaker_handler.Init.TriState = HWSPEAKER_SAI_TRISTATE_MGT;
	if (HAL_SAI_InitProtocol(&HwSpeaker_handler, HWSPEAKER_SAI_PROTOCOL, HWSPEAKER_SAI_DATASIZE, 2) != HAL_OK)
	{
	    //Error_Handler();
		return -1;
	}

	else
	{
		    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SAI1;
		    PeriphClkInitStruct.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLL;
		    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		    {
		      //Error_Handler();
		    	return -1;
		    }

		    /*  Enable Clock for Speaker GPIO Pins */
		    __HAL_RCC_GPIOE_CLK_ENABLE();
		    __HAL_RCC_GPIOA_CLK_ENABLE();
		    __HAL_RCC_GPIOG_CLK_ENABLE();

		   GPIO_InitStruct.Pin = HWSPEAKER_SCK_PIN|HWSPEAKER_FS_PIN|HWSPEAKER_SDB_PIN|HWSPEAKER_SDA_PIN;
		   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		   GPIO_InitStruct.Pull = GPIO_NOPULL;
		   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		   GPIO_InitStruct.Alternate = HWSPEAKER_GPIO_PIN_ALTERNATE;
		   HAL_GPIO_Init(HWSPEAKER_GPIO_PORT, &GPIO_InitStruct);

		   GPIO_InitStruct.Pin = HWSPEAKER_MCLK_PIN;
		   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		   GPIO_InitStruct.Pull = GPIO_NOPULL;
		   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		   GPIO_InitStruct.Alternate = HWSPEAKER_GPIO_PIN_ALTERNATE;
		   HAL_GPIO_Init(HWSPEAKER_MCLK_PORT, &GPIO_InitStruct);

		       /*Configure GPIO pin : MCO_Pin */
		 GPIO_InitStruct.Pin = HWSPEAKER_MCO_PIN;
		 GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		 GPIO_InitStruct.Pull = GPIO_NOPULL;
		 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		 GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
		 HAL_GPIO_Init(HWSPEAKER_MCO_PORT, &GPIO_InitStruct);

		  /* Peripheral DMA init*/

		 HwSpeaker_dmahandler.Instance = HWSPEAKER_DMA_STREAM;
		 HwSpeaker_dmahandler.Init.Request = HWSPEAKER_DMA_REQUEST;
		 HwSpeaker_dmahandler.Init.Direction = HWSPEAKER_DMA_TRANSFER_DIR;
		 HwSpeaker_dmahandler.Init.PeriphInc = HWSPEAKER_DMA_PERIPHERAL_INC_MODE;
		 HwSpeaker_dmahandler.Init.MemInc = HWSPEAKER_DMA_MEM_INC_MODE;
		 HwSpeaker_dmahandler.Init.PeriphDataAlignment = HWSPEAKER_DMA_PERIPHERAL_DAT_SZ;
		 HwSpeaker_dmahandler.Init.MemDataAlignment = HWSPEAKER_DMA_MEM_DATA_SZ;
		 HwSpeaker_dmahandler.Init.Mode = HWSPEAKER_DMA_MODE;
		 HwSpeaker_dmahandler.Init.Priority = HWSPEAKER_DMA_PRIORITY_LVL;
		 HwSpeaker_dmahandler.Init.FIFOMode = HWSPEAKER_DMA_FIFO_MODE;
		 HwSpeaker_dmahandler.Init.FIFOThreshold = HWSPEAKER_DMA_FIFO_THRESHOLD;
		 HwSpeaker_dmahandler.Init.MemBurst = HWSPEAKER_DMA_MEMBURST;
		 HwSpeaker_dmahandler.Init.PeriphBurst = HWSPEAKER_DMA_PBURST;
		    if (HAL_DMA_Init(&HwSpeaker_dmahandler) != HAL_OK)
		    {
		      //Error_Handler();
		    	return -1;
		    }

		    /* Several peripheral DMA handle pointers point to the same DMA handle.
		         Be aware that there is only one channel to perform all the requested DMAs. */
		__HAL_LINKDMA(&HwSpeaker_handler,hdmarx,HwSpeaker_dmahandler);

		__HAL_LINKDMA(&HwSpeaker_handler,hdmatx,HwSpeaker_dmahandler);

}

	return 0;
}


/**
  * @brief De - Initializes the SAI (Serial Audio Interface) to control the speaker.
  * @param void
  * * @retval int
  *         0 = Success (SAI interface De-initialized successfully).
  *         1 = Failure (De-Initialization failed due to an error).
  */

int HwSpeakerDeInit(void)
{
	if(HwSpeaker_MspDeInit() == 0)
		        return -1;

	return 0;
}

/**
  * @brief Controls the volume of the speaker by adjusting the audio data.
  *        This function modifies the audio data buffer to apply the specified volume level.
  *        It scales the audio samples according to the volume parameter.
  * @param WrkgBuff
  *        	A pointer to the audio data buffer that will be modified.
  *        volume
  *         The volume level to apply. Range: 0.0 (mute) to 1.0 (maximum volume).
  *        size
  *        	The size of the audio data buffer in bytes.
  *  @retval uint8_t
  *         0 = Success (Volume applied successfully to the audio data).
  *         1 = Failure (Invalid parameters or operation failed).
  */

static uint8_t HwSpeakerVolumeCtrl(uint8_t *WrkgBuff, float volume, uint32_t size) {
    if (WrkgBuff == NULL || size == 0 || volume < 0.0f || volume > 1.0f) {
        return -1;  // Error
    }

    if (size % 2 != 0) size -= 1;  // Ensure size is even

    for (uint16_t i = 0; i < size; i += 2) {  // Each sample is 2 bytes
        int16_t sample = (int16_t)((WrkgBuff[i + 1] << 8) | WrkgBuff[i]);
        int32_t scaledSample = (int32_t)(sample * volume);

        if (scaledSample > 32767) scaledSample = 32767;
        if (scaledSample < -32768) scaledSample = -32768;

        WrkgBuff[i] = (unsigned char)(scaledSample & 0xFF);          // LSB
        WrkgBuff[i + 1] = (unsigned char)((scaledSample >> 8) & 0xFF);  // MSB
    }

    return 0;  // Success
}

/**
  * @brief Plays the provided audio data through the speaker.
  *        This function sends the audio data to the speaker using the configured audio interface (e.g., SAI).\@param audioData
  *        A pointer to the `AudioPlayback_t` structure containing the audio data and metadata
  *        (e.g., buffer, size, sample rate, etc.).
  *         @retval uint8_t
  *         0 = Success (Audio data played successfully).
  *         1 = Failure (Playback failed due to invalid data or hardware error).
  */


static uint8_t HwSpeakerPlaySound(AudioPlayback_t *audioData) {
    if (audioData == NULL || audioData->buffer == NULL) return -1;

    uint16_t chunkSize = (audioData->totalSize > CHUNK_SIZE) ? CHUNK_SIZE : audioData->totalSize;
    if (chunkSize % 2 != 0) chunkSize -= 1;  // Ensure size is even

    // Fill the first buffer
    for (uint16_t i = 0; i < chunkSize; i++) {
        buffer0[i] = audioData->buffer[audioPlayback.currentOffset + i];
    }

    // Apply volume control to the first buffer
    HwSpeakerVolumeCtrl(buffer0, audioData->volume, chunkSize);

    // Set up DMA with circular mode using both buffers
    HAL_SAI_Transmit_DMA(&HwSpeaker_handler, buffer0, CHUNK_SIZE);


    audioPlayback.currentOffset += chunkSize;  // Update offset
    currentBuffer = 1;  // Indicate that the next buffer to fill is buffer1

    return 0;  // Success
}

/**
  * @brief Controls the speaker by adjusting the audio data & Volume.
  *        This function modifies the audio data buffer to apply the specified volume level.
  *        It scales the audio samples according to the volume parameter.
  * @param WrkgBuff
  *        	A pointer to the audio data buffer that will be modified.
  *        volume
  *         The volume level to apply. Range: 0.0 (mute) to 1.0 (maximum volume).
  *        size
  *        	The size of the audio data buffer in bytes.
  *  @retval uint8_t
  *         0 = Success (Volume applied successfully to the audio data).
  *         1 = Failure (Invalid parameters or operation failed).
  */



int HwSpeakerCtrl(const unsigned char *audiorawData, float volumeLevel, uint32_t size) {
    if (audiorawData == NULL || size == 0) {
        return -1; // Error: Invalid parameters
    }

    // Initialize the playback structure
    audioPlayback.buffer = audiorawData;    // Assign the raw PCM data buffer
    audioPlayback.totalSize = size;        // Total size of the audio data
    audioPlayback.currentOffset = 0;       // Reset playback offset
    audioPlayback.isPlaying = 1;           // Indicate that playback is active
    audioPlayback.volume = volumeLevel;    // Store the volume level for scaling

    // Ensure size is even (for 16-bit audio samples)
    if (audioPlayback.totalSize % 2 != 0) {
        audioPlayback.totalSize -= 1; // Align size to an even value
    }

    // Start the audio playback using the updated HwSpeakerPlaySound function
    if (HwSpeakerPlaySound(&audioPlayback) != 0) {
        audioPlayback.isPlaying = 0; // Reset isPlaying flag if playback fails
        return -1;                   // Error starting playback
    }

    return 0; // Success
}

/* SAI DMA Transfer Half Transfer Callback Function */


void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai) {
    if (hsai == &HwSpeaker_handler) {
        // Refill buffer0 (the first half of the circular buffer)
        if (audioPlayback.currentOffset < audioPlayback.totalSize) {
            uint16_t chunkSize = (audioPlayback.totalSize - audioPlayback.currentOffset > CHUNK_SIZE)
                                     ? CHUNK_SIZE
                                     : (audioPlayback.totalSize - audioPlayback.currentOffset);

            if (chunkSize % 2 != 0) chunkSize -= 1;  // Ensure size is even

            for (uint16_t i = 0; i < chunkSize; i++) {
                buffer0[i] = audioPlayback.buffer[audioPlayback.currentOffset + i];
            }

            HwSpeakerVolumeCtrl(buffer0, audioPlayback.volume, chunkSize);

            audioPlayback.currentOffset += chunkSize;
        }
    }
}

/* SAI DMA Transfer Complete Transfer Callback Function */

void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai) {
    if (hsai == &HwSpeaker_handler) {
        // Refill buffer1 (the second half of the circular buffer)
        if (audioPlayback.currentOffset < audioPlayback.totalSize) {
            uint16_t chunkSize = (audioPlayback.totalSize - audioPlayback.currentOffset > CHUNK_SIZE)
                                     ? CHUNK_SIZE
                                     : (audioPlayback.totalSize - audioPlayback.currentOffset);

            if (chunkSize % 2 != 0) chunkSize -= 1;  // Ensure size is even

            for (uint16_t i = 0; i < chunkSize; i++) {
                buffer1[i] = audioPlayback.buffer[audioPlayback.currentOffset + i];
            }

            HwSpeakerVolumeCtrl(buffer1, audioPlayback.volume, chunkSize);

            audioPlayback.currentOffset += chunkSize;
        } else {
            // Stop playback when all data is transmitted
            HAL_SAI_DMAStop(&HwSpeaker_handler);
            audioPlayback.isPlaying = 0;
        }
    }
}
