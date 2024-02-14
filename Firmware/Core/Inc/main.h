/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_ERROR_Pin GPIO_PIN_3
#define LED_ERROR_GPIO_Port GPIOE
#define LED_OK_Pin GPIO_PIN_4
#define LED_OK_GPIO_Port GPIOE
#define ETH_INT_Pin GPIO_PIN_0
#define ETH_INT_GPIO_Port GPIOC
#define RTC_CHARGE_Pin GPIO_PIN_0
#define RTC_CHARGE_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_1
#define BUZZER_GPIO_Port GPIOB
#define IN_1_Pin GPIO_PIN_2
#define IN_1_GPIO_Port GPIOB
#define IN_2_Pin GPIO_PIN_7
#define IN_2_GPIO_Port GPIOE
#define IN_3_Pin GPIO_PIN_8
#define IN_3_GPIO_Port GPIOE
#define IN_4_Pin GPIO_PIN_9
#define IN_4_GPIO_Port GPIOE
#define IN_5_Pin GPIO_PIN_10
#define IN_5_GPIO_Port GPIOE
#define IN_6_Pin GPIO_PIN_11
#define IN_6_GPIO_Port GPIOE
#define IN_7_Pin GPIO_PIN_12
#define IN_7_GPIO_Port GPIOE
#define IN_8_Pin GPIO_PIN_13
#define IN_8_GPIO_Port GPIOE
#define IN_9_Pin GPIO_PIN_14
#define IN_9_GPIO_Port GPIOE
#define IN_10_Pin GPIO_PIN_15
#define IN_10_GPIO_Port GPIOE
#define IN_11_Pin GPIO_PIN_10
#define IN_11_GPIO_Port GPIOB
#define W25Q64_CS_Pin GPIO_PIN_15
#define W25Q64_CS_GPIO_Port GPIOB
#define W25Q64_WP_Pin GPIO_PIN_8
#define W25Q64_WP_GPIO_Port GPIOD
#define W25Q64_HOLD_Pin GPIO_PIN_9
#define W25Q64_HOLD_GPIO_Port GPIOD
#define USART1_DE_Pin GPIO_PIN_9
#define USART1_DE_GPIO_Port GPIOC
#define USART1_RE_Pin GPIO_PIN_8
#define USART1_RE_GPIO_Port GPIOA
#define OUT_10_Pin GPIO_PIN_15
#define OUT_10_GPIO_Port GPIOA
#define OUT_9_Pin GPIO_PIN_10
#define OUT_9_GPIO_Port GPIOC
#define OUT_8_Pin GPIO_PIN_11
#define OUT_8_GPIO_Port GPIOC
#define OUT_7_Pin GPIO_PIN_12
#define OUT_7_GPIO_Port GPIOC
#define OUT_6_Pin GPIO_PIN_2
#define OUT_6_GPIO_Port GPIOD
#define OUT_5_Pin GPIO_PIN_3
#define OUT_5_GPIO_Port GPIOD
#define OUT_4_Pin GPIO_PIN_4
#define OUT_4_GPIO_Port GPIOD
#define OUT_3_Pin GPIO_PIN_5
#define OUT_3_GPIO_Port GPIOD
#define OUT_2_Pin GPIO_PIN_6
#define OUT_2_GPIO_Port GPIOD
#define OUT_1_Pin GPIO_PIN_7
#define OUT_1_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
