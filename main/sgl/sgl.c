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
#include <string.h>
#include <math.h>
#include "sgl.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"
#include "../core/mqtt/mqtt.h"

static void sgl_task(void *param);


void init_sgl() {
  ESP_LOGI(SGO_LOG_EVENT, "@SGL Initializing sgl module");

  xTaskCreatePinnedToCore(sgl_task, "SGL", 4096, NULL, 10, NULL, 1);
}

static void sgl_task(void *param) {
  int i = 0;
  char msg[MAX_QUEUE_ITEM_SIZE] = { 0 };

  while (true) {
		memset(msg, 0, sizeof(msg));

    int len = snprintf(msg, sizeof(msg) - 1, "Pouet poeuwt pout wepout wpeout %d", i++);
    ESP_LOGI(SGO_LOG_NOSEND, "Sending %s %d", msg, (int)(ceilf((float)len/16.0f)*16));

    send_screen_message(msg, len);

    vTaskDelay(2 * 1000 / portTICK_PERIOD_MS);
  }
}

void mqtt_message(const char *str, int len) {
  ESP_LOGI(SGO_LOG_EVENT, "@SGL MQTT received %.*s", len, str);
}
