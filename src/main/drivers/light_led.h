#ifndef __LIGHT_LED_H
#define __LIGHT_LED_H

#include "stm32h7xx_hal.h"
#include <stdbool.h>

typedef enum
{
    LED_INVERSIONTYPE_NORMAL = 0x00,
    LED_INVERSIONTYPE_INVERTED,
} ledInversionType_e;

typedef struct gpioLed_s
{
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;

    ledInversionType_e inversion;
} gpioLed_t;

typedef struct pwmLed_s
{
    TIM_HandleTypeDef *htim;
    uint32_t channel;

    uint32_t pwmBrightnessLevel;
    ledInversionType_e inversion;
} pwmLed_t;

void gpioLedInit(gpioLed_t *gpioLed, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, ledInversionType_e inversion);
void gpioLedSet(const gpioLed_t *gpioLed, bool state);

void pwmLedInit(pwmLed_t *pwmLed, TIM_HandleTypeDef *htim, uint32_t channel, uint32_t pwmBrightnessLevel, ledInversionType_e inversion);
void pwmLedSet(const pwmLed_t *pwmLed, bool state);
void pwmLedSetBrightnessLevel(const pwmLed_t *pwmLed, uint32_t brightnessLevel);

#endif /* __LIGHT_LED_H */
