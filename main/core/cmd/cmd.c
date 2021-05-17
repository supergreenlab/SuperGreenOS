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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "../log/log.h"
#include "../kv/kv.h"

#define CMD_LENGTH 256

static QueueHandle_t cmd;
static char buf_cmd[CMD_LENGTH] = {0};

void execute_cmd(int length, const char *cmdData) {
  if (length > CMD_LENGTH-1) {
    ESP_LOGE(SGO_LOG_EVENT, "@CMD Sending command failed, too long.");
  } else {
    char cmdStr[CMD_LENGTH] = {0};
    memcpy(cmdStr, cmdData, length);
    xQueueSend(cmd, cmdStr, 0);
  }
}

static void cmd_task(void *param) {
  while (true) {
    if (xQueueReceive(cmd, buf_cmd, portMAX_DELAY) != pdTRUE) {
      continue;
    }
    ESP_LOGI(SGO_LOG_NOSEND, "@CMD received cmdStr: %s", buf_cmd);
    memset(buf_cmd, 0, CMD_LENGTH);
  }
}

void init_cmd() {
  ESP_LOGI(SGO_LOG_EVENT, "@CMD Intializing CMD task");

  cmd = xQueueCreate(1, CMD_LENGTH);
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@CMD Unable to create cmd queue");
  }

  BaseType_t ret = xTaskCreatePinnedToCore(cmd_task, "CMD", 8192, NULL, 10, NULL, 1);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@CMD Failed to create task");
  }
}
