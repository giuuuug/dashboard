/**
 * @file    callback.h
 * @author  Matteo Giuliani [matteo.giuliani.sc@gmail.com]
 * @date    2024-12-06 (date of creation)
 * @version v0.0.1
 * @prefix  TMP
 *
 * @brief   Header file of callback
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 
 *          see LICENSE file in the root directory of this software component
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CALLBACK_H_
#define _CALLBACK_H_

/* ---------- Includes ------------------------------------------------------*/
#include "ili9488.h"
#include "lvgl.h"
#include "spi.h"

/* ---------- Exported types ------------------------------------------------*/

/* ---------- Exported constants --------------------------------------------*/
#define BYTES_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB888))
#define BUFFER_SIZE     (VERTICAL_RES * HORIZONTAL_RES * BYTES_PER_PIXEL / 7)
/* ---------- Exported variables --------------------------------------------*/
extern uint8_t buf1[];
/* ---------- Exported macros -----------------------------------------------*/

/* ---------- Exported functions --------------------------------------------*/

/* ---------- Private types -------------------------------------------------*/

/* ---------- Private variables ---------------------------------------------*/

/* ---------- Private constants ---------------------------------------------*/

/* ---------- Private Macros ------------------------------------------------*/

void lvgl_flush_callback(lv_display_t *display, const lv_area_t *area, uint8_t *px_map);
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);

#endif