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

#define SUN_MOVING_MULTI 800.0f
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

static double range_progress(double on_sec, double off_sec, double cur_sec, double cos_multi) {
  if (on_sec < 0) {
    on_sec += 24*3600;
  }
  if (off_sec >= 24*3600) {
    off_sec -= 24*3600;
  }
  if (on_sec < off_sec && on_sec < cur_sec && off_sec > cur_sec) {
    return max(0, min(100, sin((cur_sec - on_sec) / (off_sec - on_sec) * M_PI) * cos_multi));
  } else if (on_sec > off_sec && (on_sec < cur_sec || cur_sec < off_sec)) {
    float on_since = (cur_sec > on_sec ? cur_sec - on_sec : (24*60*60 - on_sec) + cur_sec);
    return max(0, min(100, sin(on_since / (24*60*60-(on_sec - off_sec)) * M_PI) * cos_multi));
  }
  return 0; 
}

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

  return range_progress(on_sec, off_sec, cur_sec, SUN_MOVING_MULTI);
}

#define EMERSON_OFFSET 16*60 // Add 1 min to the usual 15minx2 emerson effect to arrange with progressive on/off

static int get_emerson_output_for_hour_min(int boxId) {
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

  if (on_sec == off_sec) return 0;

  double e_range1_on = on_sec - EMERSON_OFFSET;
  double e_range1_off = on_sec + EMERSON_OFFSET;
  double progress1 = range_progress(e_range1_on, e_range1_off, cur_sec, 800);

  double e_range2_on = off_sec - EMERSON_OFFSET;
  double e_range2_off = off_sec + EMERSON_OFFSET;
  double progress2 = range_progress(e_range2_on, e_range2_off, cur_sec, 800);

  return max(progress1, progress2); 
}

#define UVA_DURATION 2*60*60 // Add 1 min to the usual 15minx2 emerson effect to arrange with progressive on/off

static int get_uva_output_for_hour_min(int boxId) {
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

  if (on_sec == off_sec) return 0;

  if (off_sec < on_sec) {
    off_sec += 24*60*60;
  }

  double mid_sec = (on_sec + off_sec)/2;
  double range_on = mid_sec - UVA_DURATION/2;
  double range_off = mid_sec + UVA_DURATION/2;

  if (range_on < 0) {
    range_on += 24*60*60;
  }

  range_off = (int)range_off % (24*60*60);

  return range_progress(range_on, range_off, cur_sec, 800);
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
  set_box_emerson_timer_output(boxId, get_emerson_output_for_hour_min(boxId));
  set_box_uva_timer_output(boxId, get_uva_output_for_hour_min(boxId));
}
