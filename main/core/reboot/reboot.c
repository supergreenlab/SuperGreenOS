/*
 * Copyright (C) 2019  SuperGreenLab <towelie@supergreenlab.com>
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

#include "reboot.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "../log/log.h"
#include "../kv/kv.h"
#include "../ota/ota.h"

#define MAX_SHORT_REBOOTS 5
#define N_SHORT_REBOOTS "NSHRBTS"

static void reboot_task();

void init_reboot() {
  defaulti(N_SHORT_REBOOTS, 0);
  int n = geti(N_SHORT_REBOOTS);
  if (n >= MAX_SHORT_REBOOTS) {
    seti(N_SHORT_REBOOTS, 0);
    reset_defaults();
    esp_restart();
  }
  ESP_LOGI(SGO_LOG_EVENT, "@REBOOT N_SHORT_REBOOTS=%d", n);
  seti(N_SHORT_REBOOTS, ++n);

  xTaskCreate(reboot_task, "REBOOT", 2048, NULL, 10, NULL);
}

static void reboot_task() {
  // reset n_short_reboots to zero
  vTaskDelay(60 * 1000 / portTICK_PERIOD_MS);
  ESP_LOGI(SGO_LOG_EVENT, "@REBOOT N_SHORT_REBOOTS=0");
  seti(N_SHORT_REBOOTS, 0);

  // Temporary failsafe restart after 2 hours
  /* vTaskDelay(2 * 60 * 60 * 1000 / portTICK_PERIOD_MS);
  while(true) {
    // avoid interrupting OTA
    if (get_ota_status() != OTA_STATUS_IN_PROGRESS) {
      esp_restart();
    }
    vTaskDelay(60 * 1000 / portTICK_PERIOD_MS);
  }*/
  vTaskDelete(NULL);
}

/*
 * http callback
 */

int on_set_reboot(int value) {
  esp_restart();
}
