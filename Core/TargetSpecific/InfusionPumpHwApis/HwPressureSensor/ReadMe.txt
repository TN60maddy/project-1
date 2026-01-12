#How to use the APIs

This file explains the procedure to test the Pressure Sensor API's used.

API Details:
 
 HwPressureSensorInit( HwPressureSensorNum_t hwPressure) => Initializes the I2C used for Pressure Sensors.
 HwPressureSensorRead( HwPressureSensorNum_t hwPressure, HwPressureSensorValues_s *psValues) => Reads the Pressure Sensor Values.

 

STEPS for Integration:

Include the API's related files inside the main.c File.

STEP 1 : Include the header files: 
		 Ensure that the header files are included in your main source file.

STEP 2 : Initialize the stepper motors: 
		 Call the HwPressureSensorInit() function and pass the argument (HwPressureSensorNum_t hwPressure) of each Pressure Sensor you wish to test.
		 
STEP 3 : Read the Pressure Sensor Values:
         Call the HwPressureSensorRead() API and pass the Pressure Sensor Number and Variable to store the pressure value as argument(HwPressureSensorNum_t hwPressure, HwPressureSensorValues_s *psValues).
         

  
/****************************************************************************************************************************************************/ 
         

Example:
Below is an example of how to test the APIs in the main function:

#include "HwStepperCtrl.h"
#include "main.h"

TEST CASE :

HwPressureSensorValues_s upstream;
HwPressureSensorValues_s downstream;

/*To test Pressure Sensor 1  */
  
/*Initialize Stepper Motor 1 & 2 */
HwPressureSensorInit(HW_PRESSURE_NUM_1);
HwPressureSensorInit(HW_PRESSURE_NUM_2);
  
 
/* Read the Pressure Sensor Values */ 

while(1)
{
	HwPressureSensorRead(HW_PRESSURE_NUM_1,&upstream);
	HAL_Delay(500);
	HwPressureSensorRead(HW_PRESSURE_NUM_2,&downstream);
	HAL_Delay(500);

	printf("Upstream Pressure : %f\n ",upstream.PressureValue);
	printf("downstream Pressure: %f\n",downstream.PressureValue);
}  
  






    
                  