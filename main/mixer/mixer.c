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

#include <float.h>
#include <math.h>

#include "mixer.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "time.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"
#include "../state/state.h"
#include "../led/led.h"

#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

static void mixer_task();
static void set_all_duty(int boxId, int value);

void init_mixer() {
  ESP_LOGI(SGO_LOG_EVENT, "@MIXER Initializing mixer module");

  BaseType_t ret = xTaskCreate(mixer_task, "MIXER", 4096, NULL, tskIDLE_PRIORITY, NULL);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@MIXER Failed to create task");
  }
}

static void set_duty(int i, int duty) {
  duty = min(100, max(duty, 0));
  set_led_duty(i, duty);
}

static void set_duty_3d(int boxId, double x, double y, double z, int duty, int min_duty) {
  double min_dist = DBL_MAX;
  double max_dist = DBL_MIN;

  for (int i = 0; i < N_LED; ++i) {
    if (get_led_box(i) != boxId) {
      continue;
    }

    double dist = sqrtf(pow(fabs(x - get_led_x(i)), 2) + pow(fabs(y - get_led_y(i)), 2) + pow(fabs(z - get_led_z(i)), 2));
    min_dist = min(min_dist, dist);
    max_dist = max(max_dist, dist);
  }

  for (int i = 0; i < N_LED; ++i) {
    if (get_led_box(i) != boxId) {
      continue;
    }

    double dist = sqrtf(pow(fabs(x - get_led_x(i)), 2) + pow(fabs(y - get_led_y(i)), 2) + pow(fabs(z - get_led_z(i)), 2));
    double d = min_duty + (double)(duty - min_duty) * ((max_dist - dist) / (max_dist - min_dist));
    set_duty(i, d);
  }
}

static void mixer_duty(int boxId) {
  double timer_output = get_box_timer_output(boxId);
  double duty = max(0, min(100, timer_output));

  int stretch = get_box_stretch(boxId);

  if (stretch == 0 || duty == 0) {
    set_all_duty(boxId, duty);
  } else if (duty != 0) {
    int max_x = INT_MIN;
    int max_y = INT_MIN;
    int max_z = INT_MIN;

    for (int i = 0; i < N_LED; ++i) {
      if (get_led_box(i) != boxId) {
        continue;
      }

      max_x = max(max_x, get_led_x(i));
      max_y = max(max_y, get_led_y(i));
      max_z = max(max_z, get_led_z(i));
    }

    set_duty_3d(boxId, (double)max_x / 2, (double)max_y / 2, max_z * 1.25, duty + ((double)stretch / 100 * 25), 30 - ((double)stretch / 100 * 25));
  }
  refresh_led(boxId, -1, -1);
}

static void mixer_task() {
  time_t now;

  while (1) {
    enum state s = get_state();
    if (s != RUNNING) {
      vTaskDelay(5000 / portTICK_PERIOD_MS);
      continue;
    }

    time(&now);
    for (int i = 0; i < N_BOX; ++i) {
      if (get_box_enabled(i) != 1) continue;

      int led_dim = get_box_led_dim(i);
      if (now - led_dim < 60) {
        continue;
      }

      mixer_duty(i);
    }

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

static void set_all_duty(int boxId, int value) {
  for (int i = 0; i < N_LED; ++i) {
    if (get_led_box(i) != boxId) {
      continue;
    }

    set_duty(i, value);
  }
}

//  KV Callbacks

int on_set_box_led_dim(int boxId, int value) {
  set_all_duty(boxId, 5);
  refresh_led(boxId, -1, -1);
  return value;
}

int on_set_box_stretch(int boxId, int value) {
  mixer_duty(boxId);
  refresh_led(boxId, -1, -1);
  return value;
}
