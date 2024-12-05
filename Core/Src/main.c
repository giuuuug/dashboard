/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

#include "adc.h"
#include "can.h"
#include "dac.h"
#include "dma.h"
#include "gpio.h"
#include "i2c.h"
#include "iwdg.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp.h"
#include "colors.h"
#include "dashboard.h"
#include "global_vars.h"
#include "ili9488.h"
#include "log.h"
#include "lvgl.h"
#include "pca9555.h"
#include "screen_loader.h"
#include "ui.h"

#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BYTES_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB888))

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/*UART1 variabls*/
char msg[80]   = "";
char value[60] = "";
static uint8_t buf1[VERTICAL_RES * HORIZONTAL_RES * BYTES_PER_PIXEL/7];
static volatile uint8_t flush_in_progress = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void my_flush_cb(lv_display_t *display, const lv_area_t *area, uint8_t *px_map) {
    if (flush_in_progress) {
        return;
    }

    flush_in_progress = 1;  // Imposta il flag per indicare che la trasmissione è in corso

    set_draw_window(area->x1, area->y1, area->x2, area->y2);

    uint32_t width = area->x2 - area->x1 + 1;
    uint32_t height = area->y2 - area->y1 + 1;
    uint32_t pixel_count = width * height;

    HAL_GPIO_WritePin(LCD_TFT_DC_GPIO_Port, LCD_TFT_DC_Pin, GPIO_PIN_SET);  
    HAL_GPIO_WritePin(LCD_TFT_CS_GPIO_Port, LCD_TFT_CS_Pin, GPIO_PIN_RESET); 

    HAL_SPI_Transmit_DMA(&hspi3, px_map, pixel_count * 3);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
  if (hspi->Instance == SPI3) {
        HAL_GPIO_WritePin(LCD_TFT_CS_GPIO_Port, LCD_TFT_CS_Pin, GPIO_PIN_SET);
        flush_in_progress = 0;  

        lv_display_flush_ready(lv_disp_get_default());
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
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
    MX_DMA_Init();
    MX_TIM2_Init();
    MX_ADC1_Init();
    // MX_CAN1_Init();
    MX_SPI3_Init();
    MX_USART1_UART_Init();
    MX_TIM7_Init();
    // MX_CAN2_Init();
    MX_DAC_Init();
    MX_I2C1_Init();
    MX_TIM3_Init();
    MX_IWDG_Init();
    /* USER CODE BEGIN 2 */
    // Start the counter
    HAL_TIM_Base_Start_IT(&COUNTER_TIM);

    // SetupDashBoard();

    // InitDashBoard();

    lcd_init_spi();

    lv_init();
    lv_tick_set_cb(HAL_GetTick);
    lv_display_t *display1 = lv_display_create(HORIZONTAL_RES, VERTICAL_RES);
    lv_display_set_buffers(display1, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(display1, my_flush_cb);
#if LV_USE_LOG
    lv_log_register_print_cb(lvgl_log_callback);
#endif

    custom_ui_init();

    int i = 0;
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        // CoreDashBoard();

        lv_obj_t *scr_act = lv_scr_act();
        if (scr_act != NULL) {
            lv_obj_del(lv_scr_act());
        }

        switch ((i++) % 4) {
            case 0:
                create_screen_main();
                lv_scr_load(objects.main);
                break;
            case 1:
                create_screen_tires();
                lv_scr_load(objects.tires);
                break;
            case 2:
                create_screen_inverters();
                lv_scr_load(objects.inverters);
                break;
            case 3:
                create_screen_extra();
                lv_scr_load(objects.extra);
                break;
        }

        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */

        HAL_IWDG_Refresh(&hiwdg);
        lv_timer_periodic_handler();
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
  */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
    RCC_OscInitStruct.LSIState       = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM       = 4;
    RCC_OscInitStruct.PLL.PLLN       = 180;
    RCC_OscInitStruct.PLL.PLLP       = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ       = 2;
    RCC_OscInitStruct.PLL.PLLR       = 2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Activate the Over-Drive mode
  */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
  */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
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
void assert_failed(uint8_t *file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       eg: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
