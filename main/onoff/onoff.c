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
#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "../timer/timer.h"
#include "../core/log/log.h"
#include "../core/kv/kv.h"
#include "../box/box.h"

#define SUN_MOVING_MULTI 800
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

static int get_output_for_hour_min(int boxId) {
  int on_hour = get_box_on_hour(boxId);
  int on_min = get_box_on_min(boxId);
  int off_hour = get_box_off_hour(boxId);
  int off_min = get_box_off_min(boxId);

  time_t now;
  struct tm tm_now;
  time(&now);
  localtime_r(&now, &tm_now); 

  double on_sec = on_hour * 3600 + on_min * 60;
  double off_sec = off_hour * 3600 + off_min * 60;
  double cur_sec = tm_now.tm_hour * 3600 + tm_now.tm_min * 60;

  if (on_sec == off_sec) return 100;

  if (on_sec < off_sec && on_sec < cur_sec && off_sec > cur_sec) {
    return max(0, min(100, sin((cur_sec - on_sec) / (off_sec - on_sec) * M_PI) * SUN_MOVING_MULTI));
  } else if (on_sec > off_sec && (on_sec < cur_sec || cur_sec < off_sec)) {
    float on_since = (cur_sec > on_sec ? cur_sec - on_sec : (24*60*60 - on_sec) + cur_sec);
    return max(0, min(100, sin(on_since / (24*60*60-(on_sec - off_sec)) * M_PI) * SUN_MOVING_MULTI));
  }

  return 0; 
}

void start_onoff(int boxId) {
  ESP_LOGI(SGO_LOG_NOSEND, "@ONOFF_%d start_onoff", boxId);
  onoff_task(boxId);
}

void stop_onoff(int boxId) {
  ESP_LOGI(SGO_LOG_NOSEND, "@ONOFF_%d stop_onoff", boxId);
  set_box_timer_output(boxId, 0);
}

void onoff_task(int boxId) {
  set_box_timer_output(boxId, get_output_for_hour_min(boxId));
}
