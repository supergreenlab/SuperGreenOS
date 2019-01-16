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

#include <stdlib.h>
#include "timer.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/kv/kv.h"
#include "../core/ble/ble.h"
#include "../core/kv/kv_ble.h"
#include "../core/log/log.h"
#include "../core/ble/ble_db.h"
#include "../led/led.h"

#include "../manual/manual.h"
#include "../onoff/onoff.h"
#include "../state/state.h"

static void timer_task(void *param);
static void stop(enum timer t);
static void start(enum timer t);

void init_timer() {
  start(get_timer_type());

  BaseType_t ret = xTaskCreate(timer_task, "TIMER", 4096, NULL, tskIDLE_PRIORITY, NULL);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@TIMER Failed to create task");
  }
}

static void stop(enum timer t) {
  switch(t) {
    case TIMER_MANUAL:
      stop_manual();
      break;
    case TIMER_ONOFF:
      stop_onoff();
      break;
  }
}

static void start(enum timer t) {
  switch(t) {
    case TIMER_MANUAL:
      start_manual();
      break;
    case TIMER_ONOFF:
      start_onoff();
      break;
  }
}

void update_output(int output) {
  ESP_LOGI(SGO_LOG_EVENT, "@TIMER update_output %d", output);
  set_timer_output(output);
}

static void timer_task(void *param) {
  while (1) {
    enum state s = get_state();
    if (s != RUNNING) {
      vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
      continue;
    }

    enum timer t = get_timer_type();

    switch(t) {
      case TIMER_MANUAL:
        manual_task();
        break;
      case TIMER_ONOFF:
        onoff_task();
        break;
    }
    vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
  }
}

// BLE Callbacks

int on_set_timer_type(int value) {
  int old = get_timer_type();

  if (old == value) return value;
  set_timer_type(value);
  stop(old);
  start(value);
  refresh_led(-1);
  return value;
}
