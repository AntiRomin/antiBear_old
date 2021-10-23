/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
#include "light_led.h"
#include "light_rgb.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

// gpioLed_t LED_R;
// gpioLed_t LED_G;
// gpioLed_t LED_B;

// gpioRGB_t gpioRGB;

pwmLed_t LED_R;
pwmLed_t LED_G;
pwmLed_t LED_B;

pwmRGB_t pwmRGB;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);

/* Private user code ---------------------------------------------------------*/
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_RTC_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();

    // gpioLedInit(&LED_R, LED_R_GPIO_Port, LED_R_Pin, LED_INVERSIONTYPE_INVERTED);
    // gpioLedInit(&LED_G, LED_G_GPIO_Port, LED_G_Pin, LED_INVERSIONTYPE_INVERTED);
    // gpioLedInit(&LED_B, LED_B_GPIO_Port, LED_B_Pin, LED_INVERSIONTYPE_INVERTED);

    // gpioRGBInit(&gpioRGB, &LED_R, &LED_G, &LED_B);

    pwmLedInit(&LED_R, &htim3, TIM_CHANNEL_3, 2047, LED_INVERSIONTYPE_INVERTED);
    pwmLedInit(&LED_G, &htim3, TIM_CHANNEL_4, 2047, LED_INVERSIONTYPE_INVERTED);
    pwmLedInit(&LED_B, &htim2, TIM_CHANNEL_4, 2047, LED_INVERSIONTYPE_INVERTED);

    pwmRGBInit(&pwmRGB, &LED_R, &LED_G, &LED_B);
    pwmRGBSetRGB(&pwmRGB, 123, 112, 255);

    // static uint32_t brightness = 0;

    /* Infinite loop */
    while (1)
    {
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_BLACK);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_RED);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_GREEN);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_BLUE);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_YELLOW);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_MAGENTA);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_CYAN);
        // HAL_Delay(250);
        // gpioRGBSetColor(&gpioRGB, GPIORGB_COLORTYPE_WHITE);
        // HAL_Delay(250);

        // pwmRGBSetRGB(&pwmRGB, 0x00, 0x00, 0x00);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0xFF, 0x00, 0x00);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0x00, 0xFF, 0x00);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0x00, 0x00, 0xFF);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0xFF, 0xFF, 0x00);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0xFF, 0x00, 0xFF);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0x00, 0xFF, 0xFF);
        // HAL_Delay(250);
        // pwmRGBSetRGB(&pwmRGB, 0xFF, 0xFF, 0xFF);
        // HAL_Delay(250);

        // pwmRGBSetBrightness(&pwmRGB, brightness);

        // for (uint16_t i = 0; i < 1024; i++)
        // {
        //     pwmRGBSetBrightness(&pwmRGB , i);
        //     HAL_Delay(1);
        // }
        // for (uint16_t i = 1023; i > 0; i--)
        // {
        //     pwmRGBSetBrightness(&pwmRGB , i);
        //     HAL_Delay(1);
        // }

        for (uint16_t i = 0; i < 256; i++)
        {
            pwmRGBSetAlpha(&pwmRGB , i);
            HAL_Delay(8);
        }
        for (uint16_t i = 255; i > 0; i--)
        {
            pwmRGBSetAlpha(&pwmRGB , i);
            HAL_Delay(8);
        }
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Supply configuration update enable
    */
    HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
    /** Configure the main internal regulator output voltage
    */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY))
    {
    }
    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 5;
    RCC_OscInitStruct.PLL.PLLN = 192;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
        Error_Handler();
    }
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

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 65535;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 65535;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_TIM_MspPostInit(&htim2);
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 0;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 65535;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 65535;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_TIM_MspPostInit(&htim3);
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
    // GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // /*Configure GPIO pin Output Level */
    // HAL_GPIO_WritePin(GPIOB, LED_G_Pin | LED_R_Pin, GPIO_PIN_SET);

    // /*Configure GPIO pin Output Level */
    // HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET);

    // /*Configure GPIO pins : LED_G_Pin LED_R_Pin */
    // GPIO_InitStruct.Pin = LED_G_Pin | LED_R_Pin;
    // GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    // GPIO_InitStruct.Pull = GPIO_NOPULL;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    // HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // /*Configure GPIO pin : LED_B_Pin */
    // GPIO_InitStruct.Pin = LED_B_Pin;
    // GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    // GPIO_InitStruct.Pull = GPIO_NOPULL;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    // HAL_GPIO_Init(LED_B_GPIO_Port, &GPIO_InitStruct);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
