/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include "m5tft.h"

#include "spi_master_lobo.h"
#include "tftspi.h"
#include "tft.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"

#define M5DISPLAY_TYPE DISP_TYPE_ST7735S  /* !< Display type for display driver */
#define M5DISPLAY_WIDTH 160               /* !< Display width in pixels after rotation */
#define M5DISPLAY_HEIGHT 80               /* !< Display height in pixels after rotation */

spi_lobo_device_handle_t m5_display_spi;

static void m5tft_task(void *param);

void init_m5tft() {
  ESP_LOGI(SGO_LOG_EVENT, "@M5TFT Initializing m5tft module");

	esp_err_t e;

	tft_disp_type = M5DISPLAY_TYPE;
	_width = 80;   // smaller dimension
	_height = 160; // larger dimension
	max_rdclock = 25000000;

	TFT_PinsInit();

	spi_lobo_bus_config_t buscfg = {};
	buscfg.miso_io_num = PIN_NUM_MISO; // set SPI MISO pin
	buscfg.mosi_io_num = PIN_NUM_MOSI; // set SPI MOSI pin
	buscfg.sclk_io_num = PIN_NUM_CLK;  // set SPI CLK pin
	buscfg.quadwp_io_num = -1;
	buscfg.quadhd_io_num = -1;
	buscfg.max_transfer_sz = 6 * 1024;

	spi_lobo_device_interface_config_t devcfg = {};
	devcfg.clock_speed_hz = 25000000;		 // Initial clock out at 8 MHz
	devcfg.mode = 0;						 // SPI mode 0
	devcfg.spics_io_num = -1;				 // we will use external CS pin
	devcfg.spics_ext_io_num = PIN_NUM_CS;	// external CS pin
	devcfg.flags = LB_SPI_DEVICE_HALFDUPLEX; // ALWAYS SET  to HALF DUPLEX MODE!! for display spi

	e = spi_lobo_bus_add_device(TFT_HSPI_HOST, &buscfg, &devcfg, &m5_display_spi);
	if (e != ESP_OK)
	{
		ESP_LOGE(SGO_LOG_NOSEND, "Error adding display to SPI bus: %s", esp_err_to_name(e));
		return;
	}

	disp_spi = m5_display_spi;

	// ==== Test select/deselect ====
	e = spi_lobo_device_select(m5_display_spi, 1);
	if (e != ESP_OK)
	{
		ESP_LOGE(SGO_LOG_NOSEND, "Error selecting display to SPI bus: %s", esp_err_to_name(e));
		return;
	}

	e = spi_lobo_device_deselect(m5_display_spi);
	if (e != ESP_OK)
	{
		ESP_LOGE(SGO_LOG_NOSEND, "Error deselecting display to SPI bus: %s", esp_err_to_name(e));
		return;
	}

	gpio_set_level((gpio_num_t)PIN_NUM_RST, 1);
	vTaskDelay(5 / portTICK_PERIOD_MS);
	gpio_set_level((gpio_num_t)PIN_NUM_RST, 0);
	vTaskDelay(20 / portTICK_PERIOD_MS);
	gpio_set_level((gpio_num_t)PIN_NUM_RST, 1);

	TFT_display_init();
	TFT_invertDisplay(INVERT_ON);

	// ==== Set SPI clock used for display operations ====
	e = spi_lobo_set_speed(m5_display_spi, DEFAULT_SPI_CLOCK);
	if (e == 0)
	{
		ESP_LOGE(SGO_LOG_NOSEND, "Error setting speed display to SPI bus: %s", esp_err_to_name(e));
		return;
	}
  ESP_LOGI(SGO_LOG_NOSEND, "Ok set speed to: %d", e);

	font_rotate = 0;
	text_wrap = 0;
	font_transparent = 0;
	font_forceFixed = 0;
	gray_scale = 0;
	TFT_setGammaCurve(DEFAULT_GAMMA_CURVE);
	TFT_setRotation(LANDSCAPE);
	TFT_setFont(DEFAULT_FONT, NULL);
	TFT_resetclipwin();
  TFT_fillScreen(TFT_BLACK);

  xTaskCreatePinnedToCore(m5tft_task, "M5TFT", 4096, NULL, 10, NULL, 1);
}

static void m5tft_task(void *param) {
  while (true) {
    char strbuff[50];

    int temp = get_box_temp(0);
    int humi = get_box_humi(0);
    int co2 = get_box_co2(0);

    TFT_fillScreen(TFT_BLACK);
    TFT_print("SuperGreenTips", 5, 10);
    sprintf((char *)strbuff, "Temp: %d\nHumi: %d\nco2: %d", temp, humi, co2);
    TFT_print((char *)strbuff, CENTER, 30);

    vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
  }
}

