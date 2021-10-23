#ifndef __PWM_H_
#define __PWM_H_

#include "stm32h7xx_hal.h"
#include <stdbool.h>

void pwmSetOutput(TIM_HandleTypeDef *htim, uint32_t channel, bool state);
void pwmSetAutoReload(TIM_HandleTypeDef *htim, uint32_t period);
uint32_t pwmGetAutoReload(TIM_HandleTypeDef *htim);
void pwmSetCompare(TIM_HandleTypeDef *htim, uint32_t channel, uint32_t pwmBrightness);
uint32_t pwmGetCompare(TIM_HandleTypeDef *htim, uint32_t channel);

#endif /* __PWM_H_ */
