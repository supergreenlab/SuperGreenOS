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

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <float.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_err.h"

#include "led.h"
#include "led_db.h"
#include "../core/ble/ble_db.h"
#include "../core/kv/kv.h"
#include "../core/kv/kv_ble.h"
#include "../core/ble/ble.h"
#include "../core/ble/ble_utils.h"
#include "../core/log/log.h"
#include "../core/time/time.h"
#include "../state/state.h"

int min_x = INT_MAX;
int max_x = INT_MIN;

int min_y = INT_MAX;
int max_y = INT_MIN;

int min_z = INT_MAX;
int max_z = INT_MIN;

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

#define LEDC_FADE_TIME         (500)

void init_led_timers();
int get_led_param(int i, const char *param);

static QueueHandle_t cmd;

static void fade_no_wait_led(ledc_channel_config_t ledc_channel, int duty) {
  uint32_t current_duty = ledc_get_duty(ledc_channel.speed_mode, ledc_channel.channel); 
  if (current_duty == duty) {
    return;
  }
  ledc_set_fade_with_time(ledc_channel.speed_mode,
      ledc_channel.channel, duty, LEDC_FADE_TIME);
  ledc_fade_start(ledc_channel.speed_mode,
      ledc_channel.channel, LEDC_FADE_NO_WAIT);
}

/* static void fade_and_wait_led(ledc_channel_config_t ledc_channel, int duty) {
  ledc_set_fade_with_time(ledc_channel.speed_mode,
      ledc_channel.channel, duty, LEDC_FADE_TIME);
  ledc_fade_start(ledc_channel.speed_mode,
      ledc_channel.channel, LEDC_FADE_WAIT_DONE);
} */

static void update_led(int i) {
  double duty = get_led_param(i, "D");
  double real_duty = LED_MIN_DUTY + (double)(LED_MAX_DUTY - LED_MIN_DUTY) * duty / 100;
  ESP_LOGI(SGO_LOG_EVENT, "@LED REAL_DUTY_%d=%d", i, (int)real_duty);

  fade_no_wait_led(ledc_channels[i].channel_config, real_duty);
}

static void led_task(void *param) {

  int c;

  for (int i = 0; i < N_LEDS; ++i) {
    ledc_channel_config(&ledc_channels[i].channel_config);
    update_led(i);
  }

  while(1) {
    if (xQueueReceive(cmd, &c, 30 * 1000 / portTICK_PERIOD_MS)) {
      if (c != -1) {
        update_led(c);
        continue;
      }
    }
    for (int i = 0; i < N_LEDS; ++i) {
      update_led(i);
    }
  }
}

void init_led_info() {
  char led_info[CHAR_VAL_LEN_MAX] = {0};

  sprintf(led_info, "%d", N_LEDS);
  for (int i = 0; i < N_LEDS; ++i) {
    char led[32] = {0};
    sprintf(led, "x:%d;y:%d;z:%d;gpio_num:%d", ledc_channels[i].x, ledc_channels[i].y, ledc_channels[i].z, ledc_channels[i].channel_config.gpio_num);
    if (strlen(led_info) + strlen(led) + 1 >= CHAR_VAL_LEN_MAX) {
      ESP_LOGE(SGO_LOG_EVENT, "@LED Not enough space to build LED_INFO !!!");
      break;
    }
    sprintf(led_info, "%s|%s", led_info, led);
    min_x = min(min_x, ledc_channels[i].x);
    max_x = max(max_x, ledc_channels[i].x);

    min_y = min(min_y, ledc_channels[i].y);
    max_y = max(max_y, ledc_channels[i].y);

    min_z = min(min_z, ledc_channels[i].z);
    max_z = max(max_z, ledc_channels[i].z);
  }
  set_led_info(led_info);
}

void init_led() {
  ESP_LOGI(SGO_LOG_EVENT, "@LED Initializing led task");

  // TODO init led array + set defaults with kv
  for (int i = 0; i < N_LEDS; ++i) {
    ledc_channels[i].channel_config.gpio_num = get_led_param(i, "IO");

    ledc_channels[i].x = get_led_param(i, "X");
    ledc_channels[i].y = get_led_param(i, "Y");
    ledc_channels[i].z = get_led_param(i, "Z");
  }

  init_led_info();

  cmd = xQueueCreate(10, sizeof(int));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@LED Unable to create led queue");
  }

  init_led_timers();

  ledc_fade_func_install(0);

  xTaskCreate(led_task, "LED", 4096, NULL, 10, NULL);
}

void refresh_led(int i) {
  xQueueSend(cmd, &i, 0);
}

int get_led_param(int i, const char *param) {
  char key[16] = {0};
  sprintf(key, "L_%d_%s", i, param);
  return geti(key);
}

int get_led_duty(int i) {
  return get_led_param(i, "D");
}

int set_led_duty(int i, int value) {
  value = min(100, max(value, 0));
  refresh_led(i);
  return value;
}

/* BLE Callbacks */

#define LED_CB(i) int on_set_led_##i##_duty(int value) { \
  return set_led_duty(i, value); \
}

LED_CB(0)
LED_CB(1)
LED_CB(2)
LED_CB(3)
LED_CB(4)
LED_CB(5)
