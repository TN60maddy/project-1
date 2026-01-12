/*
 *HwBubbleSensor.h
 */
#ifndef HWAPIS_HWBUBBLESENSOR_INC_HWBUBBLESENSOR_H_
#define HWAPIS_HWBUBBLESENSOR_INC_HWBUBBLESENSOR_H_


// Self-test status
#define BUBBLE_SENSOR_SELFTEST_START 1
#define BUBBLE_SENSOR_SELFTEST_STOP  0

// Error Codes
#define HW_BUBBLE_SENSOR_OK          0
#define HW_BUBBLE_SENSOR_ERROR       -1
#define HW_BUBBLE_SENSOR_SELFTEST_ERROR -2

int HwBubbleSensorInit(void);
int HwBubbleSensorRead(void);
int HwBubbleSensor_SelfTest(int action);  // action = 1 to start, 0 to stop


#endif /* HWAPIS_HWBUBBLESENSOR_INC_HWBUBBLESENSOR_H_ */
