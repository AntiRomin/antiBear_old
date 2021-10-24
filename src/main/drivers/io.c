#include "io.h"

static void MX_GPIO_Init(void);

bool IORead(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    return !! HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

void IOWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, bool hi)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, hi ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void IOInit(void)
{
    MX_GPIO_Init();
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
