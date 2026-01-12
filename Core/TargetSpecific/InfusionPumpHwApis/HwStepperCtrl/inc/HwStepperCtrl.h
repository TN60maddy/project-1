/*
 * HwStepperCtrl.h
 */


#ifndef TARGETSPECIFIC_HWSTEPPERCRTL_H_
#define TARGETSPECIFIC_HWSTEPPERCRTL_H_


#ifdef __cplusplus
  extern "C"
  {
#endif

/**
* Defines
*/
typedef enum
{
	HW_STEPPER_NUM_1 = 0,
	HW_STEPPER_NUM_2 ,
	HW_STEPPER_NUM_MAX
}HwStepperNum_t;

typedef enum
{
	HW_STEPPER_DIR_FWD = 0,
	HW_STEPPER_DIR_REV ,
	HW_STEPPER_DIR_MAX
}HwStepperDir_t;

/**
  * @brief Stepper HW Interface Initialization
  *        This function is to initialize the underlying HAL
  *        to configure peripherals like Timer, UART, Input and Output used to control
  *        Stepper Motors for the Infusion System
  * @param HwStepperNum_t
  *
  * @retval int 0 if Successful else error code in negative sign
  */

int HwStepperCtrlInit( HwStepperNum_t hwStpr );

/**
  * @brief Stepper Interface For Stop
  *        This function is used to stop the stop the specified stepper Motor
  *
  * @param enum HwStepperNum_t
  *
  *
  * @retval int 0 if Successful else error code in negative sign
  */

int HwStepperCtrlStop( HwStepperNum_t stpr );
/**
  * @brief Stepper Interface For Configuration
  *        This function is used to stop the stop the specified stepper Motor
  *
  * @param enum HwStepperNum_t, enum HwStepperDir_t dir, unsigned int pps
  *
  *
  * @retval int 0 if Successful else error code in negative sign
  */

int HwStepperCtrlConfigure( HwStepperNum_t stpr,HwStepperDir_t dir, unsigned int pps  );

/**
  * @brief Stepper Interface For Start
  *        This function is used to used to start rotating particular stepper motor with
  *        already configured parameters like speed and direction.
  *
  * @param enum HwStepperNum_t
  *
  *
  * @retval int 0 if Successful else error code in negative sign
  */

int HwStepperCtrlStart( HwStepperNum_t stpr );

int HwStepperChangePps( HwStepperNum_t stpr, unsigned int pps  );





#endif /* TARGETSPECIFIC_HWSTEPPERCRTL_H_ */
