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

void gpioLedInit(gpioLed_t *gpioLed, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, ledInversionType_e inversion);
void gpioLedSet(const gpioLed_t *gpioLed, bool state);

#endif /* __LIGHT_LED_H */
