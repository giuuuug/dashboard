/**
 * @file    callback.c
 * @author  Matteo Giuliani [matteo.giuliani.sc@gmail.com]
 * @date    2024-12-06 (date of creation)
 * @version v0.0.1
 * @prefix  TMP
 *
 * @brief   Implementation of callback
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 
 *          see LICENSE file in the root directory of this software component
 */

/*---------- Includes -------------------------------------------------------*/

#include "callback.h"

/*---------- Private define -------------------------------------------------*/

/*---------- Private macro --------------------------------------------------*/

/*---------- Private variables ----------------------------------------------*/
uint8_t buf1[BUFFER_SIZE];
static volatile uint8_t flush_in_progress = 0;

/*---------- Private function prototypes ------------------------------------*/

/*---------- Exported Variables ---------------------------------------------*/

/*---------- Exported Functions ---------------------------------------------*/

/*---------- Private Functions ---------------------------------------------*/
void lvgl_flush_callback(lv_display_t *display, const lv_area_t *area, uint8_t *px_map) {
    if (flush_in_progress) {
        return;
    }

    flush_in_progress = 1;  // Imposta il flag per indicare che la trasmissione è in corso

    set_draw_window(area->x1, area->y1, area->x2, area->y2);

    uint32_t width       = area->x2 - area->x1 + 1;
    uint32_t height      = area->y2 - area->y1 + 1;
    uint32_t pixel_count = width * height;

    HAL_GPIO_WritePin(LCD_TFT_DC_GPIO_Port, LCD_TFT_DC_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_TFT_CS_GPIO_Port, LCD_TFT_CS_Pin, GPIO_PIN_RESET);

    HAL_SPI_Transmit_DMA(&hspi3, px_map, pixel_count * 3);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi->Instance == SPI3) {
        HAL_GPIO_WritePin(LCD_TFT_CS_GPIO_Port, LCD_TFT_CS_Pin, GPIO_PIN_SET);
        flush_in_progress = 0;

        lv_display_flush_ready(lv_disp_get_default());
    }
}
