#ifndef __EEPROM_AT24C02C_H_
#define __EEPROM_AT24C02C_H_

#include "stm32h7xx_hal.h"
#include <stdbool.h>

#define AT24C02C_MAX_MEMADDRESS 0xFF

typedef struct at24c02cHandle_s
{
    I2C_HandleTypeDef *i2c;
} at24c02cHandle_t;

void eepromInit(at24c02cHandle_t *at24c02cHandle, I2C_HandleTypeDef *i2c);
bool eepromIsReady(at24c02cHandle_t *at24c02cHandle);
void eepromWrite(at24c02cHandle_t *at24c02cHandle, uint8_t memAddress, uint8_t *data, uint16_t length);
void eepromRead(at24c02cHandle_t *at24c02cHandle, uint8_t memAddress, uint8_t *data, uint16_t length);

#endif /* __EEPROM_AT24C02C_H_ */
