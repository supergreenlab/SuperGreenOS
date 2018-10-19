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

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "log/log.h"
#include "conf/version.h"
#include "status_led/status_led.h"
#include "kv/kv.h"
#include "mqtt/mqtt.h"
#include "ble/ble.h"
#include "state/state.h"
#include "wifi/wifi.h"
#include "time/time.h"
#include "led/led.h"
#include "timers/timer.h"
#include "timers/manual/manual.h"
#include "timers/onoff/onoff.h"
#include "timers/season/season.h"
#include "mixer/mixer.h"
#include "fans/fans.h"
#include "blower/blower.h"
#include "i2c/i2c.h"
#include "ota/ota.h"
#include "status_led/status_led.h"

void app_main() {
    mqtt_intercept_log();
    printf("Welcome to SuperGreenOS (version: %s)\n", VERSION);

    init_status_led();
    init_kv();
    init_ble();
    init_state();
    init_wifi();
    init_mqtt();
    init_ota();
    init_led();
    init_time();
    init_fans();
    init_blower();
    init_i2c();

    init_timer();
    init_manual();
    init_onoff();
    init_season();

    init_mixer();

    fflush(stdout);

    int n_tasks = uxTaskGetNumberOfTasks();
    TaskStatus_t *statuses = malloc(n_tasks * sizeof(TaskStatus_t));
    while(1) {
      uxTaskGetSystemState(statuses, n_tasks, NULL);
      for (int i = 0; i < n_tasks; ++i) {
        ESP_LOGI(SGO_LOG_METRIC, "@%s stack_left=%d, counter=%d", statuses[i].pcTaskName, statuses[i].usStackHighWaterMark, statuses[i].ulRunTimeCounter);
      }
      vTaskDelay(30000 / portTICK_PERIOD_MS);
    }
}
