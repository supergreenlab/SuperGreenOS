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
#include "freertos/queue.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"
#include "../led/led.h"
#include "../mixer/mixer.h"
#include "../box/box.h"

#include "../manual/manual.h"
#include "../onoff/onoff.h"
#include "../season/season.h"
#include "../state/state.h"

typedef enum {
  CMD_NO_ACTION,
  CMD_REFRESH,
} timer_cmd;

static QueueHandle_t cmd;

static void timer_task(void *param);
static void stop(int boxId, enum timer t);
static void start(int boxId, enum timer t);

void init_timer() {
  ESP_LOGI(SGO_LOG_NOSEND, "@TIMER Initializing timer task");
  cmd = xQueueCreate(10, sizeof(timer_cmd));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_NOSEND, "@TIMER Unable to create timer queue");
  }

  for (int i = 0; i < N_BOX; ++i) {
    if (get_box_enabled(i) != 1) continue;
    start(i, get_box_timer_type(i));
  }

  BaseType_t ret = xTaskCreatePinnedToCore(timer_task, "TIMER", 4096, NULL, tskIDLE_PRIORITY, NULL, 1);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_NOSEND, "@TIMER Failed to create task");
  }
}

static void stop(int boxId, enum timer t) {
  switch(t) {
    case TIMER_MANUAL:
      stop_manual(boxId);
      break;
    case TIMER_ONOFF:
      stop_onoff(boxId);
      break;
    case TIMER_SEASON:
      stop_season(boxId);
      break;
  }
}

static void start(int boxId, enum timer t) {
  switch(t) {
    case TIMER_MANUAL:
      start_manual(boxId);
      break;
    case TIMER_ONOFF:
      start_onoff(boxId);
      break;
    case TIMER_SEASON:
      start_season(boxId);
      break;
  }
}

static void timer_task(void *param) {
  timer_cmd c = CMD_NO_ACTION;

  while (1) {
    for (int i = 0; i < N_BOX; ++i) {
      if (get_box_enabled(i) != 1) {
        set_box_timer_output(i, 0);
        set_box_uva_timer_output(i, 0);
        set_box_db_timer_output(i, 0);
        set_box_dr_timer_output(i, 0);
        set_box_fr_timer_output(i, 0);
        continue;
      }
      enum timer t = get_box_timer_type(i);

      switch(t) {
        case TIMER_MANUAL:
          manual_task(i);
          break;
        case TIMER_ONOFF:
          onoff_task(i);
          break;
        case TIMER_SEASON:
          season_task(i);
          break;
      }
    }
    if (c == CMD_REFRESH) {
      refresh_led(-1, -1);
      c = CMD_NO_ACTION;
    }
    if (xQueueReceive(cmd, &c, 1000 / portTICK_PERIOD_MS) == pdTRUE) {
    }
  }
}

void refresh_timer() {
  timer_cmd c = CMD_REFRESH;
  xQueueSend(cmd, &c, 0);
}

// KV Callbacks

int on_set_box_timer_type(int boxId, int value) {
  int old = get_box_timer_type(boxId);
  if (old == value) return value;

  set_box_timer_type(boxId, value);
  stop(boxId, old);
  start(boxId, value);

  if (value == 0) {
    set_all_duty(boxId, 0, -1);
  }
  refresh_led(boxId, -1);
  return value;
}
