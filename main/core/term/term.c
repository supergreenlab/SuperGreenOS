/*
 * Copyright (C) 2021  SuperGreenLab <towelie@supergreenlab.com>
 * Author: Constantin Clauzel <constantin.clauzel@gmail.com>
 *
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

#include <string.h>

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_vfs_dev.h"

#include "../log/log.h"
#include "../kv/kv.h"
#include "../cmd/cmd.h"

#define TERM_LENGTH 256

static char buf_term[TERM_LENGTH] = {0};

static void term_task(void *param) {
  //setvbuf(stdin, NULL, _IONBF, 0);

  int i = 0;
  while (true) {
    vTaskDelay(20 / portTICK_PERIOD_MS);
    int c = getchar();
    if (c <= 0) {
      continue;
    }
    if (i == TERM_LENGTH) {
      memset(buf_term, 0, TERM_LENGTH);
      i = 0;
    }

    if (c == 0x0A) {
      execute_cmd(i, buf_term);
      memset(buf_term, 0, TERM_LENGTH);
      i = 0;
    } else {
      buf_term[i++] = c;
    }
  }
}

void init_term() {
  ESP_LOGI(SGO_LOG_EVENT, "@TERM Intializing TERM task");

  BaseType_t ret = xTaskCreatePinnedToCore(term_task, "TERM", 8192, NULL, 10, NULL, 1);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@TERM Failed to create task");
  }
}
