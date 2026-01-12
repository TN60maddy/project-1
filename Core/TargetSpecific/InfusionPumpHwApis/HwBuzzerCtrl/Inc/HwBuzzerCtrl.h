/*
 * HwBuzzerCtrl.h
 */

#ifndef HWAPIS_HWBUZZERCTRL_INC_HWBUZZERCTRL_H_
#define HWAPIS_HWBUZZERCTRL_INC_HWBUZZERCTRL_H_

#include "stm32h7xx_hal.h"

typedef enum {
	HWBuzz_Vol_0    = 0,     // 0%
	HWBuzz_Vol_10   = 10,    // 10%
	HWBuzz_Vol_20   = 20,    // 20%
	HWBuzz_Vol_30   = 30,    // 30%
	HWBuzz_Vol_40   = 40,    // 40%
	HWBuzz_Vol_50   = 50,    // 50%
	HWBuzz_Vol_60   = 60,    // 60%
	HWBuzz_Vol_70   = 70,    // 70%
	HWBuzz_Vol_80   = 80,    // 80%
	HWBuzz_Vol_90   = 90,    // 90%
	HWBuzz_Vol_100  = 100,   // 100%
	HWBuzz_DEFAULT  = 200
} HWBuzz_Vol_Ctrl;


int HwBuzzerCtrlInit(void);
int HwBuzzerCtrlON(HWBuzz_Vol_Ctrl val);
int HwBuzzerCtrlOFF(void);

#endif /* HWAPIS_HWBUZZERCTRL_INC_HWBUZZERCTRL_H_ */
