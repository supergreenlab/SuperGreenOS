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

#include "../core/ble/ble_db.h"
#include "../core/kv/kv.h"
#include "../core/kv/kv_ble.h"
#include "../core/ble/ble.h"
#include "../core/log/log.h"
#include "../led/led.h"
#include "../state/state.h"
#include "../timer/timer.h"

#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

static void mixer_task();
static void set_all_duty(int value);

void init_mixer() {
  BaseType_t ret = xTaskCreate(mixer_task, "MIXER", 6084, NULL, tskIDLE_PRIORITY, NULL);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@MIXER Failed to create task");
  }
}

static void set_duty(int i, int duty) {
  set_led_duty(i, duty);
  ledc_channels[i].setter(duty);
}

static void set_duty_3d(double x, double y, double z, int duty, int min_duty) {
  double min_dist = DBL_MAX;
  double max_dist = DBL_MIN;
  for (int i = 0; i < N_LEDS; ++i) {
    double dist = sqrtf(pow(fabs(x - ledc_channels[i].x), 2) + pow(fabs(y - ledc_channels[i].y), 2) + pow(fabs(z - ledc_channels[i].z), 2));
    min_dist = min(min_dist, dist);
    max_dist = max(max_dist, dist);
  }

  ESP_LOGI(SGO_LOG_EVENT, "@MIXER min_dist = %f, max_dist = %f, x = %f, y = %f, z = %f", min_dist, max_dist, x, y, z);

  for (int i = 0; i < N_LEDS; ++i) {
    double dist = sqrtf(pow(fabs(x - ledc_channels[i].x), 2) + pow(fabs(y - ledc_channels[i].y), 2) + pow(fabs(z - ledc_channels[i].z), 2));
    double d = min_duty + (double)(duty - min_duty) * ((max_dist - dist) / (max_dist - min_dist));
    ESP_LOGI(SGO_LOG_EVENT, "@MIXER i = %d, d = %f", i, d);
    set_duty(i, d);
  }
}

static void mixer_duty() {
  double timerOutput = geti(TIMER_OUTPUT);
  double duty = max(0, min(100, timerOutput));

  int stretch = geti(STRETCH);

  if (stretch == 0 || duty == 0) {
    set_all_duty(duty);
  } else if (duty != 0) {
    set_duty_3d((double)max_x / 2, (double)max_y / 2, max_z * 1.25, duty + ((double)stretch / 100 * 25), 30 - ((double)stretch / 100 * 25));
  }
}

static void mixer_task() {
  time_t now;

  while (1) {
    enum state s = geti(STATE);
    if (s != RUNNING) {
      vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
      continue;
    }

    time(&now);
    int led_dim = geti(LED_DIM);
    if (now - led_dim < 60) {
      vTaskDelay((now - led_dim + 1) * 1000 / portTICK_PERIOD_MS);
      continue;
    }

    mixer_duty();

    vTaskDelay(30 * 1000 / portTICK_PERIOD_MS);
  }
}

static void set_all_duty(int value) {
  for (int i = 0; i < N_LEDS; ++i) {
    set_duty(i, value);
  }
}

//  BLE Callbacks

int on_set_led_dim(int value) {
  set_all_duty(5);
  refresh_led(-1);
  return value;
}

int on_set_stretch(int value) {
  mixer_duty();
  refresh_led(-1);
  return value;
}
