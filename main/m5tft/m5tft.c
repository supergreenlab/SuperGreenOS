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

#include "spi_master_lobo.h"
#include "button.h"
#include "tftspi.h"
#include "wire.h"
#include "AXP192.h"
#include "bitmaps.h"
#include "bitmaps_definitions.h"
#include "node.h"

#include "screensaver.h"
#include "splash.h"

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
Node* root;

void force_frame() {
  bool val = true;
  xQueueSend(cmd, &val, 0);
}

void init_m5tft() {
  ESP_LOGI(SGO_LOG_EVENT, "@M5TFT Initializing m5tft module");

  if (xTaskCreatePinnedToCore(m5tft_task, "M5TFT", 4096, NULL, 10, NULL, 1) != pdPASS) {
    ESP_LOGE(SGO_LOG_NOSEND, "Could not create M5TFT task");
  }
}

void init_screen() {
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

  max_rdclock = DEFAULT_SPI_CLOCK;

  TFT_PinsInit();

  spi_lobo_bus_config_t buscfg = {};
  buscfg.mosi_io_num = PIN_NUM_MOSI; // set SPI MOSI pin
  buscfg.sclk_io_num = PIN_NUM_CLK;  // set SPI CLK pin
  buscfg.quadwp_io_num = -1;
  buscfg.quadhd_io_num = -1;

  spi_lobo_device_interface_config_t devcfg = {};
  devcfg.clock_speed_hz = DEFAULT_SPI_CLOCK;     // Initial clock out at 8 MHz
  devcfg.mode = 0;             // SPI mode 0
  devcfg.spics_io_num = PIN_NUM_CS; // external CS pin
  devcfg.flags = LB_SPI_DEVICE_HALFDUPLEX; // ALWAYS SET  to HALF DUPLEX MODE!! for display spi

  e = spi_lobo_bus_add_device(TFT_HSPI_HOST, &buscfg, &devcfg, &disp_spi);
  if (e != ESP_OK)
  {
    ESP_LOGE(SGO_LOG_NOSEND, "Error adding display to SPI bus: %s", esp_err_to_name(e));
    return;
  }

  TFT_display_init();

  TFT_setRotation(LANDSCAPE);

  cmd = xQueueCreate(1, sizeof(bool));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@LED Unable to create led queue");
  }

  render_mutex = xSemaphoreCreateMutex();
  root = create_node(0, 0, NULL, NULL, NULL);
}

static void m5tft_task(void *param) {
  vTaskDelay(1000 / portTICK_PERIOD_MS); // Looks like we have a race confition with wifi
  init_screen();
  init_splash(root);

  bool c;
  while(true) {
    TickType_t xLastWakeTime = xTaskGetTickCount();

    TickType_t tickTime = root_render(root);
    flush_frame();

    TickType_t xEndTime = xTaskGetTickCount();  // Capture the end time
    float timeSpent = (xEndTime - xLastWakeTime) * portTICK_PERIOD_MS;  // Calculate time spent in ms

    float delayTime = TARGET_FRAME_TIME_MS - timeSpent;  // Calculate actual delay time
    if (delayTime < 10) delayTime = 10;  // Ensure delay time is never below 10ms

    TickType_t waitTicks = delayTime / portTICK_PERIOD_MS > tickTime ? delayTime / portTICK_PERIOD_MS : tickTime;
    xQueueReceive(cmd, &c, waitTicks);
  }
}
