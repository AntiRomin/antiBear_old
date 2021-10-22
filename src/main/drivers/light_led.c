#include "light_led.h"

void IOWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, bool hi);
void pwmAutoReloadSet(TIM_HandleTypeDef *htim, uint32_t period);
void pwmOutputSet(TIM_HandleTypeDef *htim, uint32_t channel, bool state);
void pwmCompareSet(TIM_HandleTypeDef *htim, uint32_t channel, uint32_t pwmBrightness);

void gpioLedInit(gpioLed_t *gpioLed, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, ledInversionType_e inversion)
{
    gpioLed->GPIOx = GPIOx;
    gpioLed->GPIO_Pin = GPIO_Pin;
    gpioLed->inversion = inversion;

    IOWrite(gpioLed->GPIOx, gpioLed->GPIO_Pin, inversion ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void gpioLedSet(const gpioLed_t *gpioLed, bool state)
{
    IOWrite(gpioLed->GPIOx, gpioLed->GPIO_Pin, state ? !(gpioLed->inversion) : (gpioLed->inversion));
}

void pwmLedInit(pwmLed_t *pwmLed, TIM_HandleTypeDef *htim, uint32_t channel, uint32_t pwmBrightnessLevel, ledInversionType_e inversion)
{
    pwmLed->htim = htim;
    pwmLed->channel = channel;
    pwmLed->pwmBrightnessLevel = pwmBrightnessLevel - 1;
    pwmLed->inversion = inversion;

    pwmAutoReloadSet(pwmLed->htim, pwmLed->pwmBrightnessLevel);
    pwmCompareSet(pwmLed->htim, pwmLed->channel, inversion ? pwmLed->pwmBrightnessLevel : 0);
}

void pwmLedSet(const pwmLed_t *pwmLed, bool state)
{
    pwmOutputSet(pwmLed->htim, pwmLed->channel, state);
}

void pwmLedSetBrightnessLevel(const pwmLed_t *pwmLed, uint32_t brightnessLevel)
{
    if ((brightnessLevel - 1) <= pwmLed->pwmBrightnessLevel && (brightnessLevel - 1) > 0)
    {
        pwmCompareSet(pwmLed->htim, pwmLed->channel, pwmLed->inversion ? (pwmLed->pwmBrightnessLevel - (brightnessLevel - 1)) : (brightnessLevel - 1));
    }
}

void IOWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, bool hi)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, hi ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void pwmAutoReloadSet(TIM_HandleTypeDef *htim, uint32_t period)
{
    __HAL_TIM_SET_AUTORELOAD(htim, period);
}

void pwmOutputSet(TIM_HandleTypeDef *htim, uint32_t channel, bool state)
{
    if (state == true)
    {
        HAL_TIM_PWM_Start(htim, channel);
    }
    else
    {
        HAL_TIM_PWM_Start(htim, channel);
    }
}

void pwmCompareSet(TIM_HandleTypeDef *htim, uint32_t channel, uint32_t pwmBrightness)
{
    __HAL_TIM_SET_COMPARE(htim, channel, pwmBrightness);
}
