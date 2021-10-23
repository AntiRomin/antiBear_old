#include "pwm.h"

void pwmSetOutput(TIM_HandleTypeDef *htim, uint32_t channel, bool state)
{
    if (state == true)
    {
        HAL_TIM_PWM_Start(htim, channel);
    }
    else
    {
        HAL_TIM_PWM_Stop(htim, channel);
    }
}

void pwmSetAutoReload(TIM_HandleTypeDef *htim, uint32_t period)
{
    __HAL_TIM_SET_AUTORELOAD(htim, period);
}

uint32_t pwmGetAutoReload(TIM_HandleTypeDef *htim)
{
    return __HAL_TIM_GET_AUTORELOAD(htim);
}

void pwmSetCompare(TIM_HandleTypeDef *htim, uint32_t channel, uint32_t pwmBrightness)
{
    __HAL_TIM_SET_COMPARE(htim, channel, pwmBrightness);
}

uint32_t pwmGetCompare(TIM_HandleTypeDef *htim, uint32_t channel)
{
    return __HAL_TIM_GET_COMPARE(htim, channel);
}
