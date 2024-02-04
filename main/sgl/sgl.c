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

CommandFunction commandFns[CMD_COUNT] = { 0 };

void set_command(CommandType type, CommandFunction fn) {
  commandFns[type] = fn;
}

UpdateFunction updateFns[CMD_COUNT] = { 0 };

void set_command_update(CommandType type, UpdateFunction fn) {
  updateFns[type] = fn;
}

static void sgl_task(void *param);

void init_sgl() {
  ESP_LOGI(SGO_LOG_EVENT, "@SGL Initializing sgl module");

  xTaskCreatePinnedToCore(sgl_task, "SGL", 4096, NULL, 10, NULL, 1);
}

static void sgl_task(void *param) {

  while (true) {

    if (connected) {
      for (int i = 0; i < CMD_COUNT; ++i) {
        if (updateFns[i] != NULL) {
          updateFns[i]();
        }
      }
    }

    vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
  }
}

void mqtt_message(const char *str, int len) {
  //ESP_LOGI(SGO_LOG_EVENT, "@SGL MQTT received %.*s", len, str);
  if (str[0] < CMD_COUNT && commandFns[(int)str[0]] != NULL) {
    commandFns[(int)str[0]](str, len);
  }
}
