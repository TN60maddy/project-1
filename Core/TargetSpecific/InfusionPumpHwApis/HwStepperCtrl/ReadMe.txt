#How to use the APIs

This file explains the procedure to test the Stepper Control API's used.

API Details:
 
 HwStepperCtrlInit(HwStepperNum_t stpr) => Initializes the Timer & GPIO's for Stepper Motor Control.
 HwStepperCtrlConfigure(HwStepperNum_t stpr, HwStepperDir_t dir, unsigned int pps) =>  Configures the Stepper Motor Direction and PPS Value.
 HwStepperCtrlStart(HwStepperNum_t stpr)                => Start the Stepper Motor.
 HwStepperCtrlStop(HwStepperNum_t stpr)                 => Stop the Stepper Motor
 

STEPS for Integration:

Include the API's related files inside the main.c File.

STEP 1 : Include the header files: 
		 Ensure that the header files are included in your main source file.

STEP 2 : Initialize the stepper motors: 
		 Call the HwStepperCtrlInit() function and pass the argument (HwStepperNum_t stpr) of each motor you wish to test.
		 
STEP 3:  Configure the stepper motors:
		 Call the HwStepperCtrlConfigure() function and pass the arguments (HwStepperNum_t stpr, HwStepperDir_t dir, unsigned int pps) 
		  for each motor to set the desired configuration.

STEP 4:  Control the stepper motors:
         Call the HwStepperCtrlStart() API and pass the stepper motor Number as argument(HwStepperNum_t stpr) to start the motors.
         
STEP 5 : Control the stepper motors:
         Call the HwStepperCtrlStop() API and pass the stepper motor Number as argument(HwStepperNum_t stpr) to stop the motors.
         

  
/****************************************************************************************************************************************************/ 
         

Example:
Below is an example of how to test the APIs in the main function:

#include "HwStepperCtrl.h"
#include "main.h"

TEST CASE 1:

/*To test Stepper Motor 1 with 10 PPS and clockwise direction */
  
  /*Initialize Stepper Motor 1*/
  HwStepperCtrlInit(HW_STEPPER_NUM_1);
  
  /*Configure Stepper Motor 1 with dir = clockwise and PPS = 10 */
  HwStepperCtrlConfigure(HW_STEPPER_NUM_1,0,10);
   
  /*Start Stepper Motor 1 */
  HwStepperCtrlStart(HW_STEPPER_NUM_1);
  
  /*Stop Stepper Motor 1 */
  HwStepperCtrlStop(HW_STEPPER_NUM_1);
  
  
TEST CASE 2 :

/*To test Stepper Motor 1 with 10 PPS and clockwise direction */
  
  /*Initialize Stepper Motor 1*/
  HwStepperCtrlInit(HW_STEPPER_NUM_1);
  
  /*Configure Stepper Motor 1 with dir = anti-clockwise and PPS = 10 */
  HwStepperCtrlConfigure(HW_STEPPER_NUM_1,1,10);
   
  /*Start Stepper Motor 1 */
  HwStepperCtrlStart(HW_STEPPER_NUM_1);
  
  /*Stop Stepper Motor 1 */
  HwStepperCtrlStop(HW_STEPPER_NUM_1); 
  
  
 TEST CASE 3:
 
/*To test Stepper Motor 2 with 10 PPS and clockwise direction */
 
  /*Initialize Stepper Motor 2*/
  HwStepperCtrlInit(HW_STEPPER_NUM_2);
  
  /*Configure Stepper Motor 2 with dir = clockwise and PPS = 10 */
  HwStepperCtrlConfigure(HW_STEPPER_NUM_2,0,10);
  
  /*Start Stepper Motor 1 */
  HwStepperCtrlStart(HW_STEPPER_NUM_2);
  
  /*Stop Stepper Motor 2 */
  HwStepperCtrlStop(HW_STEPPER_NUM_2);

TEST CASE 4:
	
/*To test Stepper Motor 2 with 10 PPS and anti-clockwise direction */
 
  /*Initialize Stepper Motor 2*/
  HwStepperCtrlInit(HW_STEPPER_NUM_2);
  
  /*Configure Stepper Motor 2 with dir = anti-clockwise and PPS = 10 */
  HwStepperCtrlConfigure(HW_STEPPER_NUM_2,1,10);
  
  /*Start Stepper Motor 1 */
  HwStepperCtrlStart(HW_STEPPER_NUM_2);
  
  /*Stop Stepper Motor 2 */
  HwStepperCtrlStop(HW_STEPPER_NUM_2);





    
                  