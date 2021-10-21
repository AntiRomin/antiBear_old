#include "light_led.h"

void IOWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, bool hi);
	
void gpioLedInit(gpioLed_t *gpioLed, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, ledInversionType_e inversion)
{
    gpioLed->GPIOx = GPIOx;
    gpioLed->GPIO_Pin = GPIO_Pin;
    gpioLed->inversion = inversion;
}

void gpioLedSet(const gpioLed_t *gpioLed, bool state)
{
    IOWrite(gpioLed->GPIOx, gpioLed->GPIO_Pin, state ? !(gpioLed->inversion) : (gpioLed->inversion));
}

void IOWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, bool hi)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, hi ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
