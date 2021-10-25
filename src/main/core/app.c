#include "core/app.h"

#include "drivers/timer.h"
#include "drivers/i2c.h"
#include "drivers/light_led.h"
#include "drivers/light_rgb.h"
#include "drivers/eeprom_at24c02c.h"

pwmLed_t LED_R;
pwmLed_t LED_G;
pwmLed_t LED_B;

pwmRGB_t pwmRGB;

at24c02cHandle_t at24c02cHandle;

uint8_t writeData[256];
uint8_t readData[256];

void appInit(void)
{
    pwmLedInit(&LED_R, &htim3, TIM_CHANNEL_3, 2047, LED_INVERSIONTYPE_INVERTED);
    pwmLedInit(&LED_G, &htim3, TIM_CHANNEL_4, 2047, LED_INVERSIONTYPE_INVERTED);
    pwmLedInit(&LED_B, &htim2, TIM_CHANNEL_4, 2047, LED_INVERSIONTYPE_INVERTED);

    pwmRGBInit(&pwmRGB, &LED_R, &LED_G, &LED_B);
    pwmRGBSetRGB(&pwmRGB, 0x00, 0xFF, 0x00);

    eepromInit(&at24c02cHandle, &hi2c1);
}

void run(void)
{
    /* Infinite loop */
    while (1)
    {
        while (!eepromIsReady(&at24c02cHandle))
            ;
        for (uint16_t i = 0; i < 256; i++)
        {
            for (uint16_t j = 0; j < (256 - i); j++)
            {
                writeData[j] = j;
            }
            eepromWrite(&at24c02cHandle, i, writeData, 256 - i);
            eepromRead(&at24c02cHandle, i, readData, 256 - i);
            for (uint16_t j = 0; j < (256 - i); j++)
            {
                if (writeData[j] != readData[j])
                {
                    pwmRGBSetRGB(&pwmRGB, 0xFF, 0x00, 0x00);
                }
            }
        }
    }
}
