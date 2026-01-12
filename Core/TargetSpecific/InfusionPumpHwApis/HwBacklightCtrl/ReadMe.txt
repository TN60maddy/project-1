#How to use the APIs

This file explains the procedure to test the LCD Backlight control API's used.

API Details:
 
 HwBacklightCtrlInit(void) => Initializes the Timer used for LCD Backlight control.
 HwBacklightCtrlStart(void) => start the Timer used for LCD Backlight control.
 HwBacklightCtrlStop(void) =>  stop the Timer used for LCD Backlight control
 HwBacklightSetIntensity(HwBLIntensityLevel_t Level) => Set the Intensity of the Backlight Control.
 
 STEPS for Integration:

Include the API's related files inside the main.c File.

STEP 1 : Include the header files: 
		 Ensure that the header files are included in your main source file.

STEP 2 : Initialize the Backlight Timer: 
		 Call the HwBacklightCtrlInit() function.
		 
STEP 3 : Configure the Backlight Control Intensity:
         Call the HwBacklightSetIntensity(Level) API.           // Level 0 to 9
		 
STEP 4 : Start the Backlight Control:
         Call the HwBacklightCtrlStart() API.
         

/****************************************************************************************************************************************************/ 
         

Example:
Below is an example of how to test the APIs in the main function:

#include "HwBacklightCtrl.h"
#include "main.h"

TEST CASE :

int level = 0;

/* Initialize and start the Backlight for LCD */
HwBacklightCtrlInit();
HwBacklightCtrlStart();

/* Change the Backlight Intensity LOW to High  */
while(1)
	{
  		 if(level < HW_BL_INTENSITY_MAX)
  		{
		HwBacklightSetIntensity(level);
		HAL_Delay(100);
		level = level++;
		}
		else
		{
	    level = 0;
		}
	}  
}
  






    
                  