/**
 * @file qspi.c
 * @author Romin (cx413196205@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "qspi.h"

#include "drivers/system.h"

QSPI_HandleTypeDef hqspi;

static void MX_QUADSPI_Init(void);

void qspiInit(void)
{
    MX_QUADSPI_Init();
}

/**
  * @brief QUADSPI Initialization Function
  * @param None
  * @retval None
  */
static void MX_QUADSPI_Init(void)
{
    /* QUADSPI parameter configuration*/
    hqspi.Instance = QUADSPI;
    hqspi.Init.ClockPrescaler = 255;
    hqspi.Init.FifoThreshold = 1;
    hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
    hqspi.Init.FlashSize = 1;
    hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
    hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
    hqspi.Init.DualFlash = QSPI_DUALFLASH_ENABLE;
    if (HAL_QSPI_Init(&hqspi) != HAL_OK)
    {
        Error_Handler();
    }
}