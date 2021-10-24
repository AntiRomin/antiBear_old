/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define LED_G_Pin GPIO_PIN_1
#define LED_G_GPIO_Port GPIOB
#define LED_B_Pin GPIO_PIN_3
#define LED_B_GPIO_Port GPIOA
#define LED_R_Pin GPIO_PIN_0
#define LED_R_GPIO_Port GPIOB

#endif /* __MAIN_H */
