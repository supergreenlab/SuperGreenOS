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

#define RED_TIMER_OFFSET (16*60)

static void timer_output_task(int boxId, double on_sec, double off_sec, double cur_sec) {
  double value;
  if (on_sec == off_sec) {
    value = 100;
  } else {
    value = range_progress(on_sec, off_sec, cur_sec, SUN_MOVING_MULTI);
  }

  set_box_timer_output(boxId, value);

  double e_range1_on = on_sec - RED_TIMER_OFFSET;
  double e_range1_off = on_sec;
  double progress1 = range_progress(e_range1_on, e_range1_off, cur_sec, 600);
  set_box_dr_timer_output(boxId, progress1);

  double e_range2_on = off_sec;
  double e_range2_off = off_sec + RED_TIMER_OFFSET;
  double progress2 = range_progress(e_range2_on, e_range2_off, cur_sec, 600);
  set_box_fr_timer_output(boxId, progress2);
}

#define UVA_DURATION (2*60*60)

static void uva_output_task(int boxId, double on_sec, double off_sec, double cur_sec) {
  if (on_sec == off_sec) {
    set_box_uva_timer_output(boxId, 0);
    return;
  }

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
  set_box_uva_timer_output(boxId, range_progress(range_on, range_off, cur_sec, 400));
}

static void perks_stretch_output_task(int boxId, double on_sec, double off_sec, double cur_sec) {
  double current = get_box_fr_timer_output(boxId);
  double timer_output = get_box_timer_output(boxId);
  set_box_fr_timer_output(boxId, max(current, timer_output));
  set_box_dr_timer_output(boxId, 0);
}

static void perks_thicken_output_task(int boxId, double on_sec, double off_sec, double cur_sec) {
  double current = get_box_dr_timer_output(boxId);
  double timer_output = get_box_timer_output(boxId);
  set_box_fr_timer_output(boxId, 0);
  set_box_dr_timer_output(boxId, max(current, timer_output));
}

#define TRICHOMES_UVA_DURATION (15*60)
#define TRICHOMES_UVA_PERIOD (2*60*60)

static void perks_trichomes_output_task(int boxId, double on_sec, double off_sec, double cur_sec) {
  double timer_output = get_box_timer_output(boxId);
  if (timer_output == 100) {
    double progress = (((int)cur_sec % TRICHOMES_UVA_PERIOD) / TRICHOMES_UVA_DURATION);
    if (progress < 1) {
      double current = get_box_uva_timer_output(boxId);
      double value = max(0, min(100, sin(progress * M_PI) * 1000));
      set_box_uva_timer_output(boxId, max(current, value));
    }
  }
}

static void perks_emerson_output_task(int boxId, double on_sec, double off_sec, double cur_sec) {
  double timer_output = get_box_timer_output(boxId);
  double emerson_ratio = get_box_onoff_emerson_ratio(boxId) / 10;
  double dr_ratio = 1;
  double fr_ratio = 1/emerson_ratio;

  if (emerson_ratio < 1) {
    dr_ratio = emerson_ratio;
    fr_ratio = 1;
  }

  {
    double current = get_box_dr_timer_output(boxId);
    set_box_dr_timer_output(boxId, max(current, min(100, timer_output * dr_ratio)));
  }

  {
    double current = get_box_fr_timer_output(boxId);
    set_box_fr_timer_output(boxId, max(current, min(100, timer_output * fr_ratio)));
  }
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

  timer_output_task(boxId, on_sec, off_sec, cur_sec);
  uva_output_task(boxId, on_sec, off_sec, cur_sec);

  int perks = get_box_onoff_perks(boxId);

  if (perks & PERKS_STRETCH) {
    perks_stretch_output_task(boxId, on_sec, off_sec, cur_sec);
  } else if (perks & PERKS_THICKEN) {
    perks_thicken_output_task(boxId, on_sec, off_sec, cur_sec);
  }

  if (perks & PERKS_TRICHOMES) {
    perks_trichomes_output_task(boxId, on_sec, off_sec, cur_sec);
  }

  if (perks & PERKS_EMERSON) {
    perks_emerson_output_task(boxId, on_sec, off_sec, cur_sec);
  }
}
