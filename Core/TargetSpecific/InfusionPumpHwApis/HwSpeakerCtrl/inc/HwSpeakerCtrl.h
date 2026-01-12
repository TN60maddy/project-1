/*
 * HwSpeakerCtrl.h
 *
 */

#ifndef HWAPIS_HWSPEAKERCTRL_INC_HWSPEAKERCTRL_H_
#define HWAPIS_HWSPEAKERCTRL_INC_HWSPEAKERCTRL_H_

#include "stdint.h"

// Structure for the audio buffer
typedef struct {
    uint8_t* buffer;           // Pointer to the audio buffer
    uint32_t size;             // Size of the audio buffer in bytes
} HwSpeakerDataBuffer_t;

#define HW_SPEAKER_MUTE       0.0f
#define HW_SPEAKER_VOL_10    0.1f
#define HW_SPEAKER_VOL_20    0.2f
#define HW_SPEAKER_VOL_30    0.3f
#define HW_SPEAKER_VOL_40    0.4f
#define HW_SPEAKER_VOL_50    0.5f
#define HW_SPEAKER_VOL_60    0.6f
#define HW_SPEAKER_VOL_70    0.7f
#define HW_SPEAKER_VOL_80    0.8f
#define HW_SPEAKER_VOL_90    0.9f
#define HW_SPEAKER_VOL_100  1.0f


// Initialize the speaker with the provided configuration
int HwSpeakerInit(void);

// DeInitialize the Speaker
int HwSpeakerDeInit(void);

// Control the speaker to play audio, adjust volume, and manage the buffer
int HwSpeakerCtrl(const unsigned char *audiorawData, float volumeLevel, uint32_t Size);

#endif /* HWAPIS_HWSPEAKERCTRL_INC_HWSPEAKERCTRL_H_ */
