/*
 *HwDoorClampSensor.h
 */


#ifndef TARGETSPECIFIC_HWDOORCLAMPSENSOR_H_
#define TARGETSPECIFIC_HWDOORCLAMPSENSOR_H_


#ifdef __cplusplus
  extern "C"
  {
#endif

/**
* Typedefs
*/
typedef enum
{
	HW_DOORCLAMP_OPEN = 0,
	HW_DOORCLAMP_CLOSED,
    HW_DOORCLAMP_NUM_MAX
}HwDoorClampStatus_t;


/**
*    Function Prototypes
*/

/**
  * @brief HW Interface Initialization
  *        This function is to initialize the underlying HAL
  *        to configure peripherals like GPIO used to detect Status of 
  *        Front Door Clamp
  * @param None
  *
  * @retval int 0 if Successful else error code in negative sign
  */

int HwDoorClampSensorInit( void );

/**
  * @brief Get the status of Door OPEN/CLOSE 
  *
  * @param HwDoorClampStatus_t*
  *
  * @retval int 0 if Successful (Values stored in output parameter psValues),
  *         else error code in negative sign
  */

int HwDoorClampSensorReadStatus( HwDoorClampStatus_t *pStatus );


#endif /* TARGETSPECIFIC_HWDOORCLAMPSENSOR_H_ */

    
