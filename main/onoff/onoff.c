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

#include "onoff.h"

#include <time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "../timer/timer.h"
#include "../core/log/log.h"
#include "../core/kv/kv.h"
#include "../core/kv/kv_ble.h"
#include "../core/ble/ble.h"
#include "../core/ble/ble_db.h"

void init_onoff() {
}

int get_output_for_hour_min() {
  int on_hour = geti(ON_HOUR);
  int on_min = geti(ON_MIN);
  int off_hour = geti(OFF_HOUR);
  int off_min = geti(OFF_MIN);

  time_t now;
  struct tm tm_now;
  time(&now);
  localtime_r(&now, &tm_now); 

  int on_sec = on_hour * 3600 + on_min * 60;
  int off_sec = off_hour * 3600 + off_min * 60;
  int cur_sec = tm_now.tm_hour * 3600 + tm_now.tm_min * 60;

  ESP_LOGI(SGO_LOG_EVENT, "@ONOFF on_sec = %d, off_sec = %d, cur_sec = %d", on_sec, off_sec, cur_sec);

  if (on_sec < off_sec && on_sec < cur_sec && off_sec > cur_sec) {
    return 100;
  } else if (on_sec > off_sec && (on_sec < cur_sec || cur_sec < off_sec)) {
    return 100;
  }

  return 0; 
}

void start_onoff() {
  ESP_LOGI(SGO_LOG_EVENT, "@ONOFF start_onoff");
  onoff_task();
}

void stop_onoff() {
  ESP_LOGI(SGO_LOG_EVENT, "@ONOFF stop_onoff");
}

void onoff_task() {
  update_output(get_output_for_hour_min());
}
