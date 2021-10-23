#include "light_led.h"

#include "io.h"
#include "pwm.h"

#ifdef PWM_GAMMA_CORRECTION
#include <math.h>
#endif

#define __IS_VALID_MAXBRIGHTNESS(__HANDLE__, maxBrightness) (pwmGetAutoReload(__HANDLE__) >= maxBrightness ? true : false)
#define __IS_VALID_BRIGHTNESS(__PWMLED__, brightness) (__PWMLED__->maxBrightness >= brightness ? true : false)

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

void pwmLedInit(pwmLed_t *pwmLed, TIM_HandleTypeDef *htim, uint32_t channel, uint32_t maxBrightness, ledInversionType_e inversion)
{
    if (__IS_VALID_MAXBRIGHTNESS(htim, maxBrightness))
    {
        pwmLed->htim = htim;
        pwmLed->channel = channel;
        pwmLed->maxBrightness = maxBrightness;
        pwmLed->inversion = inversion;

        pwmSetAutoReload(pwmLed->htim, pwmLed->maxBrightness);
        pwmSetCompare(pwmLed->htim, pwmLed->channel, inversion ? pwmLed->maxBrightness : 0);
    }
}

void pwmLedSetMaxBrightness(pwmLed_t *pwmLed, uint32_t maxBrightness)
{
    if (__IS_VALID_MAXBRIGHTNESS(pwmLed->htim, maxBrightness))
    {
        pwmLed->maxBrightness = maxBrightness;

        pwmSetAutoReload(pwmLed->htim, pwmLed->maxBrightness);
        pwmSetCompare(pwmLed->htim, pwmLed->channel, pwmLed->inversion ? pwmLed->maxBrightness : 0);
    }
}

void pwmLedSet(const pwmLed_t *pwmLed, bool state)
{
    pwmSetOutput(pwmLed->htim, pwmLed->channel, state);
}

void pwmLedSetBrightness(const pwmLed_t *pwmLed, uint32_t brightness)
{
    if (__IS_VALID_BRIGHTNESS(pwmLed, brightness))
    {
#ifdef PWM_GAMMA_CORRECTION
        float gammaRatio = pow(((float)brightness / (float)pwmLed->maxBrightness), PWM_GAMMA);
        brightness = pwmLed->maxBrightness * gammaRatio;
#endif
        pwmSetCompare(pwmLed->htim, pwmLed->channel, pwmLed->inversion ? (pwmLed->maxBrightness - brightness) : brightness);
    }
}

uint32_t pwmLedGetBrightness(const pwmLed_t *pwmLed)
{
    return (pwmLed->inversion == LED_INVERSIONTYPE_NORMAL ? pwmGetCompare(pwmLed->htim, pwmLed->channel) : (pwmLed->maxBrightness - pwmGetCompare(pwmLed->htim, pwmLed->channel)));
}
