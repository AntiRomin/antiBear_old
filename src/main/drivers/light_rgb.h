#ifndef __LIGHT_RGB_H
#define __LIGHT_RGB_H

#include "stm32h7xx_hal.h"

#include "light_led.h"

#define ARGB_RED_MAX 255
#define ARGB_GREEN_MAX 255
#define ARGB_BLUE_MAX 255
#define ARGB_ALPHA_MAX 255

typedef enum
{
    GPIORGB_COLORTYPE_BLACK = 0x01, // #000000
    GPIORGB_COLORTYPE_RED,          // #FF0000
    GPIORGB_COLORTYPE_GREEN,        // #00FF00
    GPIORGB_COLORTYPE_BLUE,         // #0000FF
    GPIORGB_COLORTYPE_YELLOW,       // #FFFF00
    GPIORGB_COLORTYPE_MAGENTA,      // #FF00FF
    GPIORGB_COLORTYPE_CYAN,         // #00FFFF
    GPIORGB_COLORTYPE_WHITE         // #FFFFFF
} gpioRGBColorType_e;

typedef struct gpioRGB_s
{
    gpioLed_t *LED_R;
    gpioLed_t *LED_G;
    gpioLed_t *LED_B;
} gpioRGB_t;

typedef struct pwmRGB_s
{
    pwmLed_t *LED_R;
    pwmLed_t *LED_G;
    pwmLed_t *LED_B;

    uint32_t maxBrightness;

    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pwmRGB_t;

void gpioRGBInit(gpioRGB_t *gpioRGB, gpioLed_t *LED_R, gpioLed_t *LED_G, gpioLed_t *LED_B);
void gpioRGBSetColor(const gpioRGB_t *gpioRGB, gpioRGBColorType_e color);

void pwmRGBInit(pwmRGB_t *pwmRGB, pwmLed_t *LED_R, pwmLed_t *LED_G, pwmLed_t *LED_B);
void pwmRGBSetMaxBrightness(pwmLed_t *pwmLed, uint32_t maxBrightness);
void pwmRGBSetRGB(pwmRGB_t *pwmRGB, uint8_t red, uint8_t green, uint8_t blue);
void pwmRGBSetARGB(pwmRGB_t *pwmRGB, uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);
void pwmRGBSetBrightness(const pwmRGB_t *pwmRGB, uint32_t brightness);
void pwmRGBSetAlpha(const pwmRGB_t *pwmRGB, uint8_t alpha);

#endif /* __LIGHT_RGB_H */
