/* This program is free software: you can redistribute it and/or modify
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

#include "math.h"
#include "spi_master_lobo.h"
#include "button.h"
#include "tftspi.h"
#include "wire.h"
#include "AXP192.h"
#include "bitmaps.h"
#include "bitmaps_definitions.h"
#include "node.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"

uint8_t axp192_init_list[28] = {
	'A', 'X', 'P',
	0x06, 0, 11,
	0x10, 0xff, //1
	0x28, 0xCC, //2
	0x82, 0xff, //3
	0x33, 0xC1, //4
	0xB8, 0x80, //5
	0x12, 0x4D, //6
	0x36, 0x0C, //7
	0x90, 0x02, //8
	0x30, 0xec, //9
	0x39, 0xFC, //10
	0x35, 0xA2, //11
};

static void m5tft_task(void *param);

void buttonEvent(void *handler_arg, esp_event_base_t base, int32_t id, void *event_data) {
	if ((base == button_a.esp_event_base) && (id == BUTTON_PRESSED_EVENT)) {
		ESP_LOGI(SGO_LOG_NOSEND, "Button a");
	}

	if ((base == button_b.esp_event_base) && (id == BUTTON_PRESSED_EVENT)) {
		ESP_LOGI(SGO_LOG_NOSEND, "Button b");
	}
}

void init_m5tft() {
  ESP_LOGI(SGO_LOG_EVENT, "@M5TFT Initializing m5tft module");

  esp_err_t e;

  ESP_LOGI(SGO_LOG_NOSEND, "Setting up I2C");
  e = InitI2CWire(&wire0);
  if (e == ESP_OK) {
    AxpInitFromList(&wire0, axp192_init_list);
  }
  else {
    ESP_LOGE(SGO_LOG_NOSEND, "Error setting up I2C: %s", esp_err_to_name(e));
    return;
  }

  e = ButtonInit();
  if (e != ESP_OK) {
    ESP_LOGE(SGO_LOG_NOSEND, "Error initializing button");
    return;
  }

	esp_event_handler_register_with(event_loop, BUTTON_A_EVENT_BASE, BUTTON_PRESSED_EVENT, buttonEvent, NULL);
	esp_event_handler_register_with(event_loop, BUTTON_B_EVENT_BASE, BUTTON_PRESSED_EVENT, buttonEvent, NULL);

  max_rdclock = DEFAULT_SPI_CLOCK;

  TFT_PinsInit();

  spi_lobo_bus_config_t buscfg = {};
  buscfg.mosi_io_num = PIN_NUM_MOSI; // set SPI MOSI pin
  buscfg.sclk_io_num = PIN_NUM_CLK;  // set SPI CLK pin
  buscfg.quadwp_io_num = -1;
  buscfg.quadhd_io_num = -1;

  spi_lobo_device_interface_config_t devcfg = {};
  devcfg.clock_speed_hz = DEFAULT_SPI_CLOCK;		 // Initial clock out at 8 MHz
  devcfg.mode = 0;						 // SPI mode 0
  devcfg.spics_io_num = PIN_NUM_CS;	// external CS pin
  devcfg.flags = LB_SPI_DEVICE_HALFDUPLEX; // ALWAYS SET  to HALF DUPLEX MODE!! for display spi

  e = spi_lobo_bus_add_device(TFT_HSPI_HOST, &buscfg, &devcfg, &disp_spi);
  if (e != ESP_OK)
  {
    ESP_LOGE(SGO_LOG_NOSEND, "Error adding display to SPI bus: %s", esp_err_to_name(e));
    return;
  }

  TFT_display_init();

  TFT_setRotation(LANDSCAPE);

  xTaskCreatePinnedToCore(m5tft_task, "M5TFT", 4096, NULL, 10, NULL, 1);
}

color_t frame[DEFAULT_TFT_DISPLAY_HEIGHT * DEFAULT_TFT_DISPLAY_WIDTH];

void flush_frame() {
  int buffer_size = DEFAULT_TFT_DISPLAY_HEIGHT * DEFAULT_TFT_DISPLAY_WIDTH/4;
  send_data(0, 0, DEFAULT_TFT_DISPLAY_HEIGHT-1, 19, buffer_size, frame);
  send_data(0, 20, DEFAULT_TFT_DISPLAY_HEIGHT-1, 39, buffer_size, frame+buffer_size);
  send_data(0, 40, DEFAULT_TFT_DISPLAY_HEIGHT-1, 59, buffer_size, frame+buffer_size*2);
  send_data(0, 60, DEFAULT_TFT_DISPLAY_HEIGHT-1, 79, buffer_size, frame+buffer_size*3);
}

static void m5tft_task(void *param) {
  Node* root = create_node(0, 0, NULL, NULL, NULL);

  AnimationParams *params = (AnimationParams*)malloc(sizeof(AnimationParams));
  params->dest_x = 110;
  params->dest_y = 40;
  params->speed = 2;

  Node* child1 = create_node(10, 10, &bmp_db_0, simple_animation, params);

  add_child(root, child1);

  render_node(root, 0, 0);

  while(true) {
    for (int i = 0; i < DEFAULT_TFT_DISPLAY_HEIGHT * DEFAULT_TFT_DISPLAY_WIDTH; ++i) {
      frame[i] = (color_t){43, 63, 81};
    }
    render_node(root, 0, 0);
    flush_frame();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}


/*static void m5tft_task(void *param) {
  int inc = 5;
  int height = 40;
	float sinA = 0;
  while(true) {
    for (int x = 0; x < DEFAULT_TFT_DISPLAY_HEIGHT; ++x) {
      for (int y = 0; y < DEFAULT_TFT_DISPLAY_WIDTH; ++y) {
        if (y < height) {
          frame[x + y*DEFAULT_TFT_DISPLAY_HEIGHT] = (color_t){x+30, 255-x, y*3};
        } else {
          frame[x + y*DEFAULT_TFT_DISPLAY_HEIGHT] = (color_t){y * 3, 255-y*3, 255-x};
        }
      }
    }

    int x = 0;
		int y = 5 + (int)(sinf(sinA) * 40);
    draw_bitmap(&bmp_db_0, x, y);
    x += bmp_db_0.width;
    draw_bitmap(&bmp_db_1, x, y);
    x += bmp_db_1.width;
    draw_bitmap(&bmp_db_2, x, y);
    x += bmp_db_2.width;
    draw_bitmap(&bmp_db_3, x, y);
    x += bmp_db_3.width;
    draw_bitmap(&bmp_db_4, x, y);

    x = 0;
    draw_bitmap(&bmp_db_5, x, y + 45);
    x += bmp_db_5.width;
    draw_bitmap(&bmp_db_6, x, y + 45);
    x += bmp_db_5.width;
    draw_bitmap(&bmp_db_6, x, y + 45);
    x += bmp_db_5.width;
    draw_bitmap(&bmp_db_6, x, y + 45);
    x += bmp_db_6.width;

    height += inc;
    if (height <= 1 || height >= 80) {
      height = height <= 1 ? 1 : 79;
      inc = -inc;
    }
		sinA += 0.1;
    flush_frame();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}*/
