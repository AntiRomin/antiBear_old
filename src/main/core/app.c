#include "core/app.h"

#include "drivers/timer.h"
#include "drivers/light_led.h"
#include "drivers/light_rgb.h"

// gpioLed_t LED_R;
// gpioLed_t LED_G;
// gpioLed_t LED_B;

// gpioRGB_t gpioRGB;

pwmLed_t LED_R;
pwmLed_t LED_G;
pwmLed_t LED_B;

pwmRGB_t pwmRGB;

void appInit(void)
{
    // gpioLedInit(&LED_R, LED_R_GPIO_Port, LED_R_Pin, LED_INVERSIONTYPE_INVERTED);
    // gpioLedInit(&LED_G, LED_G_GPIO_Port, LED_G_Pin, LED_INVERSIONTYPE_INVERTED);
    // gpioLedInit(&LED_B, LED_B_GPIO_Port, LED_B_Pin, LED_INVERSIONTYPE_INVERTED);

    // gpioRGBInit(&gpioRGB, &LED_R, &LED_G, &LED_B);

    pwmLedInit(&LED_R, &htim3, TIM_CHANNEL_3, 2047, LED_INVERSIONTYPE_INVERTED);
    pwmLedInit(&LED_G, &htim3, TIM_CHANNEL_4, 2047, LED_INVERSIONTYPE_INVERTED);
    pwmLedInit(&LED_B, &htim2, TIM_CHANNEL_4, 2047, LED_INVERSIONTYPE_INVERTED);

    pwmRGBInit(&pwmRGB, &LED_R, &LED_G, &LED_B);
    pwmRGBSetRGB(&pwmRGB, 0, 147, 211);

    // static uint32_t brightness = 0;
}

void run(void)
{
    /* Infinite loop */
    while (1)
    {
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_BLACK);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_RED);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_GREEN);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_BLUE);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_YELLOW);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_MAGENTA);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_CYAN);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_WHITE);
        // HAL_Delay(250);

        // pwmRGBSetRGB(&pwmRGB, 0x00, 0x00, 0x00);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0xFF, 0x00, 0x00);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0x00, 0xFF, 0x00);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0x00, 0x00, 0xFF);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0xFF, 0xFF, 0x00);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0xFF, 0x00, 0xFF);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0x00, 0xFF, 0xFF);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0xFF, 0xFF, 0xFF);
        // HAL_Delay(250);

        // pwmRGBSetBrightness(&pwmRGB, brightness);

        // for (uint16_t i = 0; i < 1024; i++)
        // {
        //     pwmRGBSetBrightness(&pwmRGB , i);
        //     HAL_Delay(1);
        // }
        // for (uint16_t i = 1023; i > 0; i--)
        // {
        //     pwmRGBSetBrightness(&pwmRGB , i);
        //     HAL_Delay(1);
        // }

        for (uint16_t i = 0; i < 256; i++)
        {
            pwmRGBSetAlpha(&pwmRGB, i);
            HAL_Delay(8);
        }
        for (uint16_t i = 255; i > 0; i--)
        {
            pwmRGBSetAlpha(&pwmRGB, i);
            HAL_Delay(8);
        }
    }
}
