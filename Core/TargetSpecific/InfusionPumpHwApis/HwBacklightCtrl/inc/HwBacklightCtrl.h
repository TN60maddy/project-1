/*
 * HwBacklightCtrl.h
 */

#include "stm32h7xx_hal.h"


#ifndef SRC_HWBACKLIGHTCTRL_INC_HWBACKLIGHTCTRL_H_
#define SRC_HWBACKLIGHTCTRL_INC_HWBACKLIGHTCTRL_H_


typedef enum{
	HW_BL_INTENSITY_0,
	HW_BL_INTENSITY_1,
	HW_BL_INTENSITY_2,
	HW_BL_INTENSITY_3,
	HW_BL_INTENSITY_4,
	HW_BL_INTENSITY_5,
	HW_BL_INTENSITY_6,
	HW_BL_INTENSITY_7,
	HW_BL_INTENSITY_8,
	HW_BL_INTENSITY_9,
	HW_BL_INTENSITY_MAX
}HwBLIntensityLevel_t;

int HwBacklightCtrlInit(void);
int HwBacklightCtrlON(void);
int HwBacklightCtrlOFF(void);
int HwBacklightCtrlSetLevel(HwBLIntensityLevel_t Level);

#endif /* SRC_HWBACKLIGHTCTRL_INC_HWBACKLIGHTCTRL_H_ */
