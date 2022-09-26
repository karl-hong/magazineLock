/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

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
#define Gled_Pin GPIO_PIN_0
#define Gled_GPIO_Port GPIOA
#define Rled_Pin GPIO_PIN_1
#define Rled_GPIO_Port GPIOA
#define Lock_Dect_Pin GPIO_PIN_0
#define Lock_Dect_GPIO_Port GPIOB
#define Lock_Dect_EXTI_IRQn EXTI0_1_IRQn
#define Lock_On_Pin GPIO_PIN_1
#define Lock_On_GPIO_Port GPIOB
#define HX711_Dat_Pin GPIO_PIN_3
#define HX711_Dat_GPIO_Port GPIOB
#define HX711_Sck_Pin GPIO_PIN_4
#define HX711_Sck_GPIO_Port GPIOB
#define Dsip_Sck_Pin GPIO_PIN_7
#define Dsip_Sck_GPIO_Port GPIOB
#define Disp_STB_Pin GPIO_PIN_8
#define Disp_STB_GPIO_Port GPIOB
#define Disp_Dat_Pin GPIO_PIN_9
#define Disp_Dat_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
