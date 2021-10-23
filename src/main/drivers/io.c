#include "io.h"

bool IORead(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    return !! HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

void IOWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, bool hi)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, hi ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
