/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "button.h"
#include "led.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// #define DEBOUNCE_MS 15
// #define LONG_PRESS_MS 500
// #define DOUBLE_CLICK_WINDOW_MS 400
// #define BLINK_INTERVAL_MS   150
// #define BLINK_BURST_TOGGLES 6 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// Button Handle PV
// uint8_t button_current = 1; // 0 = Click - 1 = Unclick
// uint8_t button_last = 1; 
// uint8_t button_filter = 1;
// uint8_t is_debouncing = 0;
// uint32_t time_debounce = 0;

// uint32_t time_press_start = 0;
// uint8_t  click_count      = 0;
// uint32_t time_first_click = 0;
// uint8_t is_holding = 0;
// uint8_t event_single_click = 0;
// uint8_t event_double_click = 0;

// //LED Handle PV
// uint8_t  burst_remaining = 0;
// uint32_t time_last_burst = 0;
// uint32_t time_last_blink = 0;
// static uint8_t was_holding = 0; 

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// void button_handle(void)
// {
//   // --- Debounce ---
//   uint8_t button_state = HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin);
//   if(button_state != button_filter)
//   {
//     button_filter = button_state;
//     is_debouncing = 1;
//     time_debounce = HAL_GetTick();
//   }

//   if(is_debouncing && (HAL_GetTick()-time_debounce) >= DEBOUNCE_MS)
//   {
//     button_current = button_filter;
//     is_debouncing = 0;
//   }

//   // --- Click and Unclick ---
//   if(button_current != button_last)
//   {
//     if(button_current == 0)
//     {
//       time_press_start = HAL_GetTick();
//     }
//     else if(is_holding) // Check if holding
//     {
//       is_holding = 0;
//     }
//     else // check if double click
//     {
//       if(click_count == 0)
//       {
//         click_count = 1;
//         time_first_click = HAL_GetTick();
//       }
//       else
//       {
//         click_count = 0;
//         event_double_click = 1;
//       }
//     }
//     button_last = button_current;
//   }

//   // --- Holding ---
//   if(button_current == 0 && !is_holding && (HAL_GetTick() - time_press_start >= LONG_PRESS_MS))
//   {
//     is_holding = 1;
//     click_count = 0;
//   }

//   if(click_count == 1 && (HAL_GetTick() - time_first_click > DOUBLE_CLICK_WINDOW_MS))
//   {
//     click_count = 0;
//     event_single_click = 1;
//   }
// }

// void led_handle(void)
// {
//   // One Click
//   if(event_single_click)
//   {
//     event_single_click = 0;
//     HAL_GPIO_TogglePin(LEDY_GPIO_Port, LEDY_Pin);
//   }

//   // Double click
//   if(event_double_click)
//   {
//     event_double_click = 0;
//     burst_remaining = BLINK_BURST_TOGGLES;
//     time_last_burst = HAL_GetTick();
//   }
//   if(burst_remaining > 0 &&  (HAL_GetTick()-time_last_burst) >= BLINK_INTERVAL_MS)
//   {
//     HAL_GPIO_TogglePin(LEDY_GPIO_Port, LEDY_Pin);
//     time_last_burst = HAL_GetTick();
//     burst_remaining--;
//   }

//   // Hold
//   if(is_holding)
//   {
//     if((HAL_GetTick()-time_last_blink) >= BLINK_INTERVAL_MS)
//     {
//       HAL_GPIO_TogglePin(LEDY_GPIO_Port, LEDY_Pin);
//       time_last_blink = HAL_GetTick();
//     }
//   }
//   else if(was_holding)
//   {
//     HAL_GPIO_WritePin(LEDY_GPIO_Port, LEDY_Pin, GPIO_PIN_RESET);
//   }
//   was_holding = is_holding;
// }
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    Button_Handle();
    LED_Handle();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LEDY_GPIO_Port, LEDY_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Button_Pin */
  GPIO_InitStruct.Pin = Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LEDY_Pin */
  GPIO_InitStruct.Pin = LEDY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LEDY_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
