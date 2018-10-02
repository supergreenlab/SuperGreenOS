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

#include "../conf/ble_db.h"
#include "../kv/kv.h"
#include "../kv/kv_ble.h"
#include "../ble/ble.h"
#include "../log/log.h"
#include "../led/led.h"
#include "../state/state.h"
#include "../timers/timer.h"

/*  UUID string: a66375f6-7677-ba29-46b7-0fde55b0db61 */
const uint8_t LED_DIM_UUID[ESP_UUID_LEN_128] = {0x61,0xdb,0xb0,0x55,0xde,0x0f,0xb7,0x46,0x29,0xba,0x77,0x76,0xf6,0x75,0x63,0xa6};
/*  UUID string: 7072326b-95b0-4822-a5e1-b2cc47875ae5 */
const uint8_t STRETCH_UUID[ESP_UUID_LEN_128] = {0xe5,0x5a,0x87,0x47,0xcc,0xb2,0xe1,0xa5,0x22,0x48,0xb0,0x95,0x6b,0x32,0x72,0x70};

#define LED_DIM "LED_DIM"
#define STRETCH "STRETCH"

#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

static void mixer_task();
static void set_all_duty(int value);

void init_mixer() {
  defaulti(STRETCH, 0);
  defaulti(LED_DIM, 0);

  sync_ble_i(STRETCH, IDX_VALUE(STRETCH));
  sync_ble_i(LED_DIM, IDX_VALUE(LED_DIM));

  BaseType_t ret = xTaskCreate(mixer_task, "Mixer task", 3072, NULL, tskIDLE_PRIORITY, NULL);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@MIXER Failed to create task");
  }
}

static void set_duty(int i, int duty) {
  set_led_duty(i, duty);
  set_attr_value_and_notify(ledc_channels[i].duty_val_idx, (uint8_t *)&duty, sizeof(int));
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
    set_duty_3d((double)max_x / 2, (double)max_y / 2, max_z, duty + ((double)stretch / 100 * 25), 30 - ((double)stretch / 100 * 25));
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

void on_set_led_dim(int value) {
  seti(LED_DIM, value); 
  set_all_duty(5);
  refresh_led(-1);
}

void on_set_stretch(int value) {
  seti(STRETCH, value);
  mixer_duty();
  refresh_led(-1);
}
