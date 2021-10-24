#ifndef __IO_H_
#define __IO_H_

#include "stm32h7xx_hal.h"
#include <stdbool.h>

bool IORead(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void IOWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, bool hi);

void IOInit(void);

#endif /* __IO_H_ */
