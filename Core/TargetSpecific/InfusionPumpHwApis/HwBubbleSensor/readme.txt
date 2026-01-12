#How to use the APIs

This file explains the procedure to test the Door Clamp API's used.
API Details:

 HwBubbleSensorInit( void ) => Initializes the Air Bubble Sensor.
 HwBubbleSensorRead( void ) => Read the Air Bubble Sensor Status.
                               0 => No Bubble detected  
                               1 => Bubble detection
 HwBubbleSensor_Selftest(int action) => Start (or) Stop the Self Test.
                               action = 1, start the self test.
                               action = 0, start the self test. 							   

Steps for Integration:

Include the API's related files inside the main.c File.

STEP 1 : Include the header files:
         Ensure that the header files are included in your main source file.
         
STEP 2: Initialize the Air Bubble Sensor:
        Call the HwBubbleSensorInit() function.

STEP 3: Read the Air Bubble Sensor:
        Call the HwBubbleSensorRead() function and pass the arguments (HwDoorClampStatus_t *pStatus) for read status of door clamp.
        

Example:
Below is an example of how to test the APIs in the main function:

#include "HwBubbleSensor.h"
#include "main.h"

/*To test Air Bubble Sensor Status */

/*Initialize Air Bubble Sensor Sensor*/
  uint8_t status;
  HwBubbleSensorInit();
  
/*Read Status DoorClamp Sensor */
  status = HwBubbleSensorRead();
  printf("Status : %d\n",status);



Note : Tested with GPIO PINS.
PC2 & PC3.

/******************************************************************************************************************/
