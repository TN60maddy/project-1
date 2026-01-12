#How to use the APIs

This file explains the procedure to test the Door Clamp API's used.
API Details:

 HwDoorClampSensorInit( void ) => Initializes the GPIO's for Door Clamp.
 HwDoorClampSensorReadStatus( HwDoorClampStatus_t *pStatus ) => Read the Door Clamp Status

Steps for Integration:

Include the API's related files inside the main.c File.

STEP 1 : Include the header files:
         Ensure that the header files are included in your main source file.
         
STEP 2: Initialize the DoorClamp Sensor:
        Call the HwDoorClampSensorInit() function.

STEP 3: Read the DoorClamp Sensor:
        Call the HwDoorClampSensorReadStatus() function and pass the arguments (HwDoorClampStatus_t *pStatus) for read status of door clamp.
        

Example:
Below is an example of how to test the APIs in the main function:

#include "HwDoorClampSensor.h"
#include "main.h"

/*To test Door Clamp Status */

/*Initialize DoorCalmp Sensor*/
  HwDoorClampSensorInit();
  
/*Read Status DoorClamp Sensor */
HwDoorClampStatus_t door_clamp;

HwDoorClampSensorReadStatus(&door_clamp);
if (door_clamp == HW_DOORCLAMP_CLOSED)
{
	printf("Door Closed\n");
}
else if (door_clamp == HW_DOORCLAMP_OPEN)
{
	printf("Door Opened\n");
}





