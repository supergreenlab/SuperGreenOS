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
#include "../box/box.h"

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

typedef struct {
  int boxId;
  int ledId;
} cmd_refresh_led;
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
  if (ledc_channels[i].enabled != 1) {
    return;
  }

  double duty = get_led_param(i, "D");
  double real_duty = LED_MIN_DUTY + (double)(LED_MAX_DUTY - LED_MIN_DUTY) * duty / 100;
  ESP_LOGI(SGO_LOG_EVENT, "@LED REAL_DUTY_%d=%d", i, (int)real_duty);

  fade_no_wait_led(ledc_channels[i].channel_config, real_duty);
}

static void led_task(void *param) {

  cmd_refresh_led c;

  for (int i = 0; i < N_LEDS; ++i) {
    if (ledc_channels[i].enabled != 1) {
      continue;
    }

    ledc_channel_config(&ledc_channels[i].channel_config);
    update_led(i);
  }

  while(1) {
    if (xQueueReceive(cmd, &c, 30 * 1000 / portTICK_PERIOD_MS)) {
      for (int i = 0; i < N_LEDS; ++i) {
        if (c.boxId != -1 && (c.boxId != ledc_channels[i].box || get_box_enabled(ledc_channels[i].box) != 1)) {
          continue;
        }
        if (c.ledId != -1 && (i != c.ledId || ledc_channels[i].enabled != 1)) {
          continue;
        }
        update_led(i);
      }
    }
  }
}

void init_led_info(int boxId, char *led_info) {
  sprintf(led_info, "n:%d", N_LEDS);
  for (int i = 0; i < N_LEDS; ++i) {
    int bi = get_led_box(i);
    if (ledc_channels[i].enabled != 1 || bi != boxId || get_box_enabled(bi) != 1) {
      continue;
    }
    char led[32] = {0};
    sprintf(led, "i:%d;x:%d;y:%d;z:%d;gpio_num:%d", i, ledc_channels[i].x, ledc_channels[i].y, ledc_channels[i].z, ledc_channels[i].channel_config.gpio_num);
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
}

void init_led() {
  ESP_LOGI(SGO_LOG_EVENT, "@LED Initializing led task");

  // TODO init led array + set defaults with kv
  for (int i = 0; i < N_LEDS; ++i) {
    ledc_channels[i].enabled = get_led_param(i, "E");

    ledc_channels[i].x = get_led_param(i, "X");
    ledc_channels[i].y = get_led_param(i, "Y");
    ledc_channels[i].z = get_led_param(i, "Z");

    ledc_channels[i].box = get_led_param(i, "B");

    ledc_channels[i].channel_config.gpio_num = get_led_param(i, "IO");
  }

  char led_info[CHAR_VAL_LEN_MAX] = {0};
  init_led_info(0, led_info); set_box_0_led_info(led_info);
  init_led_info(1, led_info); set_box_1_led_info(led_info);
  init_led_info(2, led_info); set_box_2_led_info(led_info);

  cmd = xQueueCreate(10, sizeof(cmd_refresh_led));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@LED Unable to create led queue");
  }

  init_led_timers();

  ledc_fade_func_install(0);

  xTaskCreate(led_task, "LED", 4096, NULL, 10, NULL);
}

void refresh_led(int boxId, int ledId) {
  cmd_refresh_led cmd_data = {
    boxId: boxId,
    ledId: ledId,
  };
  xQueueSend(cmd, &cmd_data, 0);
}

int get_led_param(int i, const char *param) {
  char key[16] = {0};
  sprintf(key, "L_%d_%s", i, param);
  return geti(key);
}

/* KV Callbacks */

int on_set_led_duty(int ledId, int value) {
  return rset_led_duty(ledId, value);
}
