/*
 *  HwDoorPOsitionSensor.h
 */

#ifndef TARGETSPECIFIC_HWDOORPOSITIONSENSOR_H_
#define TARGETSPECIFIC_HWDOORPOSITIONSENSOR_H_

#include<stdint.h>
#ifdef __cplusplus
  extern "C"
  {
#endif

/**
* Typedefs
*/
typedef uint32_t HwDoorPosition_t;

/**
*    Function Prototypes
*/

/**
  * @brief HW Interface Initialization
  *        This function is to initialize the underlying HAL
  *        to configure peripherals like ADC used to detect Position of 
  *        Front Door 
  * @param None
  *
  * @retval int 0 if Successful else error code in negative sign
  */

int HwDoorPositionSensorInit( void );

/**
  * @brief Get the status of Door FULLOPEN/HALFOPEN/CLOSE 
  *
  * @param HwDoorPosition_t*
  *
  * @retval int 0 if Successful (Values stored in output parameter psValues),
  *         else error code in negative sign
  */

int HwDoorPositionSensorReadStatus( HwDoorPosition_t *pStatus );


#endif /* TARGETSPECIFIC_HWDOORPOSITIONSENSOR_H_ */

    
