#include "init.h"

#include "drivers/system.h"
#include "drivers/io.h"
#include "drivers/timer.h"
#include "drivers/i2c.h"
#include "drivers/qspi.h"

RTC_HandleTypeDef hrtc;

static void MX_RTC_Init(void);

void init(void)
{
    systemInit();

    IOInit();
    timerInit();
    i2cInit();
    qspiInit();

    MX_RTC_Init();
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{
    /** Initialize RTC Only
    */
    hrtc.Instance = RTC;
    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv = 127;
    hrtc.Init.SynchPrediv = 255;
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
    if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        Error_Handler();
    }
}
