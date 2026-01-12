
/*
 * HwQuadEncoder.h
 */


#ifndef TARGETSPECIFIC_HWQUADENCODER_H_
#define TARGETSPECIFIC_HWQUADENCODER_H_


#ifdef __cplusplus
  extern "C"
  {
#endif

/**
* Typedefs
*/
typedef enum
{
	HW_QUADENCODER_DIR_NONE = 0,
    HW_QUADENCODER_DIR_FWD,
    HW_QUADENCODER_DIR_REV,
    HW_QUADENCODER_DIR_NUM_MAX
}HwQuadEncoderDir_t;


typedef enum
{
	HW_QUADENCODER_POS_NONE = 0,
    HW_QUADENCODER_POS_1,
    HW_QUADENCODER_POS_1AND2,
    HW_QUADENCODER_POS_2,
    HW_QUADENCODER_POS_NUM_MAX,
}HwQuadEncoderPos_t;

typedef struct
{
    unsigned long int  SpeedInPulsesPerSec; 
    HwQuadEncoderDir_t Direction; 
    HwQuadEncoderPos_t Pos;
}HwPQuadEncoderValues_s;


/**
*    Function Prototypes
*/

/**
  * @brief Quadrature Encoder HW Interface Initialization
  *        This function is to initialize the underlying HAL
  *        to configure peripherals like GPIO,Timer/Encoder 
  * @param None
  *
  * @retval int 0 if Successful else error code in negative sign
  */

int HwQuadEncoderInit( void );

/**
  * @brief Start Counting Quadrature Encoder 
  *
  * @param None
  *
  * @retval int 0 if Successful else error code in negative sign
  */

int HwQuadEncoderStart( void );

/**
  * @brief Stop Counting Quadrature Encoder 
  *
  * @param None
  *
  * @retval int 0 if Successful else error code in negative sign
  */

int HwQuadEncoderStop( void );



/**
  * @brief Read Counts in mSec from Speed in pulses per second and Direction
  *
  * @param HwPQuadEncoderValues_s*
  *
  * @retval int 0 if Successful (Values stored in output parameter psValues),
  *         else error code in negative sign
  */

int HwQuadEncoderRead( HwPQuadEncoderValues_s  *psValues);

/**
  * @brief Read Position
  * 
  * POSITION 1
  *                              |- Optical Sensor2
  *                             ***
  *                             *   **
  *                             *     *
  *     Optical Sensor1 -|      *      *
  *                             *       *
  *                    **********        *
  *                    *                 * --- Rotating Shaft
  *                    *                 *
  *                     *               *
  *                      *             *
  *                        **       **
  *                           *****
  *                         
  * POSITION 1AND2
  *                               |- Optical Sensor2
  *       Optical Sensor1 -|        **
  *                      *         *   *
  *                     *  *      *     *
  *                    *    *    *       *
  *                    *      * *        * -- Rotating Shaft
  *                    *       *         *
  *                    *                 *
  *                     *               *
  *                      *             *
  *                        **       **
  *                           *****
  * POSITION 2
  *                               |- Optical Sensor2
  *                                 **
  *                      *         *   *
  *                     *  *      *     *
  *  Optical Sensor1 -|*    *    *       *
  *                    *      * *        *
  *                    *       *         *  -- Rotating Shaft
  *                    *                 *
  *                     *               *
  *                      *             *
  *                        **       **
  *                           *****                             
  * POSITION NONE   
  * 
  *                             ***
  *                             *  **
  *                             *     *
  *                             *      *
  *                             *       *
  *                    **********        *    -- Rotating Shaft
  * Optical Sensor2 -| *                 *
  *                    *                 *
  * Optical Sensor1 -|  *               *
  *                      *             *
  *                        **       **
  *                          *****                             
  *
  *
  * @param HwQuadEncoderPos_t*
  *
  * @retval int 0 if Successful (Position stored in output parameter pPos),
  *         else error code in negative sign
  */

int HwQuadEncoderReadPosition( HwQuadEncoderPos_t  *pPos);


void HwQuadEncoder_incrementPulses(uint16_t GPIO_Pin);

#endif /* TARGETSPECIFIC_HWQUADENCODER_H_ */

    
