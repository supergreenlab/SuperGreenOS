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
#include "freertos/queue.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"

const float TARGET_FRAME_TIME_MS = 1000.0f / 32.0f;

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

static QueueHandle_t cmd;

void force_frame() {
  bool val = true;
  xQueueSend(cmd, &val, 0);
}

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

  cmd = xQueueCreate(10, sizeof(bool));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@LED Unable to create led queue");
  }

  xTaskCreatePinnedToCore(m5tft_task, "M5TFT", 8192, NULL, 10, NULL, 1);
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

  SineAnimationParams *params1 = (SineAnimationParams*)malloc(sizeof(SineAnimationParams));
  params1->center_x = 15;
  params1->center_y = 20;
  params1->magnitude_x = 20;
  params1->magnitude_y = 10;
  params1->elapsedTime = 0;
  params1->speed=0.1;

 	SineTransparencyAnimationParams *params1trans = (SineTransparencyAnimationParams*)malloc(sizeof(SineTransparencyAnimationParams));
	params1trans->min_transparency = 0.2;
	params1trans->max_transparency = 0.8;
	params1trans->elapsed_time = 0;
	params1trans->speed = 0.0666666;

  char text1[5] = "0001";
  Node* textNode1 = create_text_node(10, 10, 4, text1, (color_t){217, 69, 184}, NORMAL_FONT_SIZE);
  textNode1->funcParams[0] = params1;
  textNode1->funcs[0] = sine_animation;
	textNode1->renderOpts.transparency = 0.5;

	textNode1->funcParams[1] = params1trans;
  textNode1->funcs[1] = sine_transparency_animation;

  add_child(root, textNode1);

  SineAnimationParams *params2 = (SineAnimationParams*)malloc(sizeof(SineAnimationParams));
  params2->center_x = 15;
  params2->center_y = 15;
  params2->magnitude_x = -20;
  params2->magnitude_y = -20;
  params2->elapsedTime = 0;
  params2->speed=-0.05;

	SineTransparencyAnimationParams *params2trans = (SineTransparencyAnimationParams*)malloc(sizeof(SineTransparencyAnimationParams));
	params2trans->min_transparency = 0.2;
	params2trans->max_transparency = 0.8;
	params2trans->elapsed_time = 0;
	params2trans->speed = -0.1333333;

  char text2[5] = "9999";
  Node* textNode2 = create_text_node(10, 10, 4, text2, (color_t){51, 203, 212}, SMALL_FONT_SIZE);
  textNode2->funcParams[0] = params2;
  textNode2->funcs[0] = sine_animation;

	textNode2->funcParams[1] = params2trans;
  textNode2->funcs[1] = sine_transparency_animation;

  add_child(root, textNode2);

  SineAnimationParams *params3 = (SineAnimationParams*)malloc(sizeof(SineAnimationParams));
  params3->center_x = 55;
  params3->center_y = 35;
  params3->magnitude_x = -20;
  params3->magnitude_y = -40;
  params3->elapsedTime = 0;
  params3->speed=0.075;

	SineTransparencyAnimationParams *params3trans = (SineTransparencyAnimationParams*)malloc(sizeof(SineTransparencyAnimationParams));
	params3trans->min_transparency = 0.2;
	params3trans->max_transparency = 0.8;
	params3trans->elapsed_time = M_PI/2;
	params3trans->speed = -0.1333333;

  char text3[5] = "9999";
  Node* textNode3 = create_text_node(10, 10, 4, text3, (color_t){212, 203, 51}, SMALL_FONT_SIZE);
  textNode3->funcParams[0] = params3;
  textNode3->funcs[0] = sine_animation;

	textNode3->funcParams[1] = params3trans;
  textNode3->funcs[1] = sine_transparency_animation;

  add_child(root, textNode3);

  SineAnimationParams *params4 = (SineAnimationParams*)malloc(sizeof(SineAnimationParams));
  params4->center_x = 20;
  params4->center_y = 30;
  params4->magnitude_x = -30;
  params4->magnitude_y = -40;
  params4->elapsedTime = 0;
  params4->speed=0.1;

	SineTransparencyAnimationParams *params4trans = (SineTransparencyAnimationParams*)malloc(sizeof(SineTransparencyAnimationParams));
	params4trans->min_transparency = 0.2;
	params4trans->max_transparency = 0.8;
	params4trans->elapsed_time = M_PI/2;
	params4trans->speed = -0.2666666;

  char text4[5] = "9999";
  Node* textNode4 = create_text_node(10, 10, 4, text4, (color_t){0, 51, 203}, NORMAL_FONT_SIZE);
  textNode4->funcParams[0] = params4;
  textNode4->funcs[0] = sine_animation;

	textNode4->funcParams[1] = params4trans;
  textNode4->funcs[1] = sine_transparency_animation;

  add_child(root, textNode4);


  float n = 1;
  bool c;
  while(true) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (int i = 0; i < DEFAULT_TFT_DISPLAY_HEIGHT * DEFAULT_TFT_DISPLAY_WIDTH; ++i) {
      frame[i] = (color_t){43, 63, 81};
    }

    sprintf(text1, "%04d", (int)++n);
    set_text_node(textNode1, text1, NORMAL_FONT_SIZE);

    sprintf(text2, "%04d", (int)(9999 - n));
    set_text_node(textNode2, text2, SMALL_FONT_SIZE);

    sprintf(text3, "%04d", (int)(9999 - n));
    set_text_node(textNode3, text3, SMALL_FONT_SIZE);

    sprintf(text4, "%04d", (int)(9999 - n));
    set_text_node(textNode4, text4, NORMAL_FONT_SIZE);

    n = (int)n % 10000;

    root_render(root);
    flush_frame();

    TickType_t xEndTime = xTaskGetTickCount();  // Capture the end time
    float timeSpent = (xEndTime - xLastWakeTime) * portTICK_PERIOD_MS;  // Calculate time spent in ms

    float delayTime = TARGET_FRAME_TIME_MS - timeSpent;  // Calculate actual delay time
    if (delayTime < 10) delayTime = 10;  // Ensure delay time is never below 10ms

    xQueueReceive(cmd, &c, delayTime / portTICK_PERIOD_MS);
  }
}
