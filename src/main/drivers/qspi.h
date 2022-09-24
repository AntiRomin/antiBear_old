/**
 * @file qspi.h
 * @author Romin (cx413196205@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __QSPI_H
#define __QSPI_H

#include "stm32h7xx_hal.h"
#include <stdbool.h>

extern QSPI_HandleTypeDef hqspi;

void qspiInit(void);

#endif /* __QSIP_H */