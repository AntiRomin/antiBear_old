#ifndef __I2C_H_
#define __I2C_H_

#include "stm32h7xx_hal.h"
#include <stdbool.h>

extern I2C_HandleTypeDef hi2c1;

void i2cInit(void);

#endif /* __I2C_H_ */
