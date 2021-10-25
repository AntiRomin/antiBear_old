#include "drivers/eeprom_at24c02c.h"

#define AT24C02C_DEVICE_ADDRESS 0xA0

#define AT24C02C_PAGE_SIZE 32
#define AT24C02C_BYTES_PER_PAGE 8
#define AT24C02C_MAX_SIZE (AT24C02C_PAGE_SIZE * AT24C02C_BYTES_PER_PAGE)
#define AT24C02C_ROW_MSK 0x07

#define AT24C02C_T_WR 5

static void eepromWriteByte(at24c02cHandle_t *at24c02cHandle, uint8_t memAddress, uint8_t *data);
static void eepromWritePage(at24c02cHandle_t *at24c02cHandle, uint8_t memAddress, uint8_t *data, uint8_t length);
static void eppromReadCurrent(at24c02cHandle_t *at24c02cHandle, uint8_t *data);
static void eppromReadRandom(at24c02cHandle_t *at24c02cHandle, uint8_t memAddress, uint8_t *data);
static void eepromReadSequential(at24c02cHandle_t *at24c02cHandle, uint8_t memAddress, uint8_t *data, uint16_t length);

void eepromInit(at24c02cHandle_t *at24c02cHandle, I2C_HandleTypeDef *i2c)
{
    at24c02cHandle->i2c = i2c;
}

bool eepromIsReady(at24c02cHandle_t *at24c02cHandle)
{
    return (HAL_I2C_IsDeviceReady(at24c02cHandle->i2c, AT24C02C_DEVICE_ADDRESS, 1, AT24C02C_T_WR) == HAL_OK) ? true : false;
}

void eepromWrite(at24c02cHandle_t *at24c02cHandle, uint8_t memAddress, uint8_t *data, uint16_t length)
{
    if ((memAddress + length <= AT24C02C_MAX_SIZE) && (length > 0))
    {
        do
        {
            if ((memAddress & AT24C02C_ROW_MSK) == 0)
            {
                if (length <= 8)
                {
                    eepromWritePage(at24c02cHandle, memAddress, data, length);
                    length = 0;
                }
                else
                {
                    eepromWritePage(at24c02cHandle, memAddress, data, 8);
                    data += 8;
                    length -= 8;
                    memAddress += 8;
                }
            }
            else
            {
                if (((memAddress | AT24C02C_ROW_MSK) + length <= 8))
                {
                    eepromWritePage(at24c02cHandle, memAddress, data, length);
                    length = 0;
                }
                else
                {
                    eepromWritePage(at24c02cHandle, memAddress, data, (8 - (memAddress & AT24C02C_ROW_MSK)));
                    data += (8 - (memAddress & AT24C02C_ROW_MSK));
                    length -= (8 - (memAddress & AT24C02C_ROW_MSK));
                    memAddress += (8 - (memAddress & AT24C02C_ROW_MSK));
                }
            }
        } while (length != 0);
    }
}

void eepromRead(at24c02cHandle_t *at24c02cHandle, uint8_t memAddress, uint8_t *data, uint16_t length)
{
    eepromReadSequential(at24c02cHandle, memAddress, data, length);
}

static void eepromWriteByte(at24c02cHandle_t *at24c02cHandle, uint8_t memAddress, uint8_t *data)
{
    UNUSED(eepromWriteByte);
    while (!eepromIsReady(at24c02cHandle))
        ;
    HAL_I2C_Mem_Write(at24c02cHandle->i2c, AT24C02C_DEVICE_ADDRESS, memAddress, I2C_MEMADD_SIZE_8BIT, data, 1, AT24C02C_T_WR);
}

static void eepromWritePage(at24c02cHandle_t *at24c02cHandle, uint8_t memAddress, uint8_t *data, uint8_t length)
{
    if (((memAddress & AT24C02C_ROW_MSK) + length <= 8) && (length > 0))
    {
        while (!eepromIsReady(at24c02cHandle))
            ;
        HAL_I2C_Mem_Write(at24c02cHandle->i2c, AT24C02C_DEVICE_ADDRESS, memAddress, I2C_MEMADD_SIZE_8BIT, data, length, AT24C02C_T_WR * length);
    }
}

static void eppromReadCurrent(at24c02cHandle_t *at24c02cHandle, uint8_t *data)
{
    UNUSED(eppromReadCurrent);
    HAL_I2C_Master_Receive(at24c02cHandle->i2c, AT24C02C_DEVICE_ADDRESS, data, 1, AT24C02C_T_WR);
}

static void eppromReadRandom(at24c02cHandle_t *at24c02cHandle, uint8_t memAddress, uint8_t *data)
{
    UNUSED(eppromReadRandom);
    HAL_I2C_Mem_Read(at24c02cHandle->i2c, AT24C02C_DEVICE_ADDRESS, memAddress, I2C_MEMADD_SIZE_8BIT, data, 1, AT24C02C_T_WR);
}

static void eepromReadSequential(at24c02cHandle_t *at24c02cHandle, uint8_t memAddress, uint8_t *data, uint16_t length)
{
    if ((memAddress + length) <= AT24C02C_MAX_SIZE)
    {
        while (!eepromIsReady(at24c02cHandle))
            ;
        HAL_I2C_Mem_Read(at24c02cHandle->i2c, AT24C02C_DEVICE_ADDRESS, memAddress, I2C_MEMADD_SIZE_8BIT, data, length, AT24C02C_T_WR * length);
    }
}
