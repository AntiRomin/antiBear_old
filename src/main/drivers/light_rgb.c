#include "light_rgb.h"

#define __IS_VALID_ALPHA(alpha) (alpha > ARGB_ALPHA_MAX ? false : true)
#define __IS_VALID_RGB(red, green, blue) (red > ARGB_RED_MAX ? false : (green > ARGB_GREEN_MAX ? false : (blue > ARGB_BLUE_MAX ? false : true)))
#define __IS_VALID_ARGB(alpha, red, green, blue) (!__IS_VALID_RGB(red, green, blue) ? false : __IS_VALID_ALPHA(alpha))
#define __IS_VALID_BRIGHTNESS(__PWMRGB__, brightness) (__PWMRGB__->maxBrightness >= brightness ? true : false)

void gpioRGBInit(gpioRGB_t *gpioRGB, gpioLed_t *LED_R, gpioLed_t *LED_G, gpioLed_t *LED_B)
{
    gpioRGB->LED_R = LED_R;
    gpioRGB->LED_G = LED_G;
    gpioRGB->LED_B = LED_B;
}

void gpioRGBSetColor(const gpioRGB_t *gpioRGB, gpioRGBColorType_e color)
{
    switch (color)
    {
    case GPIORGB_COLORTYPE_BLACK:
        gpioLedSet(gpioRGB->LED_R, false);
        gpioLedSet(gpioRGB->LED_G, false);
        gpioLedSet(gpioRGB->LED_B, false);
        break;

    case GPIORGB_COLORTYPE_RED:
        gpioLedSet(gpioRGB->LED_R, true);
        gpioLedSet(gpioRGB->LED_G, false);
        gpioLedSet(gpioRGB->LED_B, false);
        break;

    case GPIORGB_COLORTYPE_GREEN:
        gpioLedSet(gpioRGB->LED_R, false);
        gpioLedSet(gpioRGB->LED_G, true);
        gpioLedSet(gpioRGB->LED_B, false);
        break;

    case GPIORGB_COLORTYPE_BLUE:
        gpioLedSet(gpioRGB->LED_R, false);
        gpioLedSet(gpioRGB->LED_G, false);
        gpioLedSet(gpioRGB->LED_B, true);
        break;

    case GPIORGB_COLORTYPE_YELLOW:
        gpioLedSet(gpioRGB->LED_R, true);
        gpioLedSet(gpioRGB->LED_G, true);
        gpioLedSet(gpioRGB->LED_B, false);
        break;

    case GPIORGB_COLORTYPE_MAGENTA:
        gpioLedSet(gpioRGB->LED_R, true);
        gpioLedSet(gpioRGB->LED_G, false);
        gpioLedSet(gpioRGB->LED_B, true);
        break;

    case GPIORGB_COLORTYPE_CYAN:
        gpioLedSet(gpioRGB->LED_R, false);
        gpioLedSet(gpioRGB->LED_G, true);
        gpioLedSet(gpioRGB->LED_B, true);
        break;

    case GPIORGB_COLORTYPE_WHITE:
        gpioLedSet(gpioRGB->LED_R, true);
        gpioLedSet(gpioRGB->LED_G, true);
        gpioLedSet(gpioRGB->LED_B, true);
        break;
    }
}

void pwmRGBInit(pwmRGB_t *pwmRGB, pwmLed_t *LED_R, pwmLed_t *LED_G, pwmLed_t *LED_B)
{
    pwmRGB->LED_R = LED_R;
    pwmRGB->LED_G = LED_G;
    pwmRGB->LED_B = LED_B;

    uint32_t tempMaxRedBrightness = __PWMLED_GET_MAX_BRIGHTNESS(pwmRGB->LED_R);
    uint32_t tempMaxGreenBrightness = __PWMLED_GET_MAX_BRIGHTNESS(pwmRGB->LED_G);
    uint32_t tempMaxBlueBrightness = __PWMLED_GET_MAX_BRIGHTNESS(pwmRGB->LED_B);

    pwmRGB->maxBrightness = tempMaxRedBrightness > tempMaxGreenBrightness ? (tempMaxGreenBrightness > tempMaxBlueBrightness ? tempMaxBlueBrightness : tempMaxGreenBrightness)
                                                                          : (tempMaxRedBrightness > tempMaxBlueBrightness ? tempMaxBlueBrightness : tempMaxRedBrightness);

    pwmLedSetMaxBrightness(pwmRGB->LED_R, pwmRGB->maxBrightness);
    pwmLedSetMaxBrightness(pwmRGB->LED_G, pwmRGB->maxBrightness);
    pwmLedSetMaxBrightness(pwmRGB->LED_B, pwmRGB->maxBrightness);

    pwmLedSet(pwmRGB->LED_R, true);
    pwmLedSet(pwmRGB->LED_G, true);
    pwmLedSet(pwmRGB->LED_B, true);
}

void pwmRGBSetRGB(pwmRGB_t *pwmRGB, uint8_t red, uint8_t green, uint8_t blue)
{
    if (__IS_VALID_RGB(red, green, blue))
    {
        float redRatio = (float)red / ARGB_RED_MAX;
        float greenRatio = (float)green / ARGB_GREEN_MAX;
        float blueRatio = (float)blue / ARGB_BLUE_MAX;
        pwmLedSetBrightness(pwmRGB->LED_R, (redRatio * pwmRGB->maxBrightness));
        pwmLedSetBrightness(pwmRGB->LED_G, (greenRatio * pwmRGB->maxBrightness));
        pwmLedSetBrightness(pwmRGB->LED_B, (blueRatio * pwmRGB->maxBrightness));

        pwmRGB->red = red;
        pwmRGB->green = green;
        pwmRGB->blue = blue;
    }
}

void pwmRGBSetARGB(pwmRGB_t *pwmRGB, uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue)
{
    if (__IS_VALID_ARGB(alpha, red, green, blue))
    {
        float alphaRatio = (float)alpha / ARGB_ALPHA_MAX;
        float redRatio = ((float)red / ARGB_RED_MAX) * alphaRatio;
        float greenRatio = ((float)green / ARGB_GREEN_MAX) * alphaRatio;
        float blueRatio = ((float)blue / ARGB_BLUE_MAX) * alphaRatio;
        pwmLedSetBrightness(pwmRGB->LED_R, (redRatio * pwmRGB->maxBrightness));
        pwmLedSetBrightness(pwmRGB->LED_G, (greenRatio * pwmRGB->maxBrightness));
        pwmLedSetBrightness(pwmRGB->LED_B, (blueRatio * pwmRGB->maxBrightness));

        pwmRGB->red = red;
        pwmRGB->green = green;
        pwmRGB->blue = blue;
    }
}

void pwmRGBSetBrightness(const pwmRGB_t *pwmRGB, uint32_t brightness)
{
    if (__IS_VALID_BRIGHTNESS(pwmRGB, brightness))
    {
        float redRatio = (float)pwmRGB->red / ARGB_RED_MAX;
        float greenRatio = (float)pwmRGB->green / ARGB_GREEN_MAX;
        float blueRatio = (float)pwmRGB->blue / ARGB_BLUE_MAX;
        pwmLedSetBrightness(pwmRGB->LED_R, (redRatio * brightness));
        pwmLedSetBrightness(pwmRGB->LED_G, (greenRatio * brightness));
        pwmLedSetBrightness(pwmRGB->LED_B, (blueRatio * brightness));
    }
}

void pwmRGBSetAlpha(const pwmRGB_t *pwmRGB, uint8_t alpha)
{
    if (__IS_VALID_ALPHA(alpha))
    {
        float alphaRatio = (float)alpha / ARGB_ALPHA_MAX;
        pwmRGBSetBrightness(pwmRGB, (alphaRatio * pwmRGB->maxBrightness));
    }
}
