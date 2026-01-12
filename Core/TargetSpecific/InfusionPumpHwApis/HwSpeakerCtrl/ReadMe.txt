#How to use the APIs

This file explains the procedure to test the Speaker Control API's used.
Audio data is stored inside a separate header file in the inc folder. ../core/inc/Audio1.h

API Details:
 
 int HwSpeakerInit(void) => Initializes the SAI Interface with DMA to transfer Audio Data to the CODEC.
 int HwSpeakerCtrl(HwSpeakerDataBuffer_t* audio, float volumeLevel)=> Control the Speaker Data and Volume.

 
 STEPS for Integration:

Include the API's related files inside the main.c File.

STEP 1 : Include the header files: 
		 Ensure that the header files are included in your main source file.

STEP 2 : Initialize the Backlight Timer: 
		 Call the HwSpeakerInit() function.

STEP 3 : Start the speaker audio by calling the API:
         Call the HwSpeakerCtrl() API.
		 
		 where,
		  HwSpeakerDataBuffer_t => structue holds the audio data and size of the data.
		  float volumeLevel     => Volume control of the speaker 
		                           0.0 = Mute
                                   0.1 = Minumum DB
                                   1.0 = Maximum DB 								   
         

/****************************************************************************************************************************************************/ 
         

Example:
Below is an example of how to test the APIs in the main function:

#include "HwSpeakerCtrl.h"
#include "Audio1.h"
#include "main.h"

TEST CASE :
in the main.c file add the below code.

int main()
{
  HwSpeakerDataBuffer_t audio;
  audio.buffer = audio1;
  audio.size  = (uint32_t)sizeof(audio1);


  HwSpeakerInit();
  HwSpeakerCtrl(&audio,HW_SPEAKER_VOL_10);

/* Change the Backlight Intensity LOW to High  */
while(1)
	{
  		
}
  
}





    
                  