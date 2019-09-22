/*
 * Copyright (C) 2018  SuperGreenLab <towelie@supergreenlab.com>
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

#include "blower.h"

#include "math.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "../core/log/log.h"
#include "../core/ble/ble_db.h"
#include "../core/kv/kv.h"
#include "../core/kv/kv_ble.h"

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

static void blower_task(void *param) {
  while (1) {
    for (int i = 0; i < N_BOX; ++i) {
      if (get_box_enabled(i) != 1) continue;
      int vday = get_box_blower_day(i);
      int vnight = get_box_blower_night(i);
      int timerOutput = get_box_timer_output(i);
      int v = (float)vnight + ((vday - vnight) * (float)timerOutput / 100.0f);
      set_box_blower_duty(i, v);
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void init_blower() {
  ESP_LOGI(SGO_LOG_EVENT, "@BLOWER Initializing blower task");

  BaseType_t ret = xTaskCreate(blower_task, "BLOWER", 4096, NULL, 10, NULL);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@BLOWER Failed to create task");
  }
}

/* BLE Callbacks */

int on_set_box_blower_day(int boxId, int value) {
  value = min(100, max(value, 0));
  return value;
}

int on_set_box_blower_night(int boxId, int value) {
  value = min(100, max(value, 0));
  return value;
}
