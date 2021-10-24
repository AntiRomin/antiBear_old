#ifndef __TIMER_H_
#define __TIMER_H_

#include "stm32h7xx_hal.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

void timerInit(void);

#endif /* __TIMER_H_ */
