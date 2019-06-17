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

#define LED_MIN_ZERO           (5)
#define LED_DUTY_RESOLUTION 9
#define LED_MIN_DUTY           (0)
#define LED_MAX_DUTY           (511)

int min_x = INT_MAX;
int max_x = INT_MIN;

int min_y = INT_MAX;
int max_y = INT_MIN;

int min_z = INT_MAX;
int max_z = INT_MIN;

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

#define LEDC_FADE_TIME         (1000)

typedef struct {
  int box_id;
  int led_id;
  int fade_time;
} cmd_refresh_led;
static QueueHandle_t cmd;

static void fade_no_wait_led(ledc_channel_config_t ledc_channel, int duty, int fade_time) {
  uint32_t current_duty = ledc_get_duty(ledc_channel.speed_mode, ledc_channel.channel); 
  if (current_duty == duty) {
    return;
  }
  ledc_set_fade_with_time(ledc_channel.speed_mode,
      ledc_channel.channel, duty, fade_time);
  ledc_fade_start(ledc_channel.speed_mode,
      ledc_channel.channel, LEDC_FADE_NO_WAIT);
}

static void update_led(int i, int fade_time) {
  if (ledc_channels[i].enabled != 1) {
    return;
  }

  double dim = get_led_dim(i);
  double duty = get_led_duty(i) * dim / 100;
  duty = (duty < LED_MIN_ZERO) ? 0 : duty;
  if (get_led_fade(i) == 1) {
    double real_duty = LED_MIN_DUTY + (double)(LED_MAX_DUTY - LED_MIN_DUTY) * duty / 100;
    ESP_LOGI(SGO_LOG_EVENT, "@LED REAL_DUTY_%d=%d", i, (int)real_duty);

    fade_no_wait_led(ledc_channels[i].channel_config, real_duty, fade_time);
  } else {
    duty = (duty == 0 ? duty : LED_MAX_DUTY);
    ledc_set_duty(ledc_channels[i].channel_config.speed_mode, ledc_channels[i].channel_config.channel, duty);
    ledc_update_duty(ledc_channels[i].channel_config.speed_mode, ledc_channels[i].channel_config.channel);
  }
}

static void led_task(void *param) {

  cmd_refresh_led c;

  while(1) {
    if (!xQueueReceive(cmd, &c, 5 * 1000 / portTICK_PERIOD_MS)) {
      c.box_id = -1;
      c.led_id = -1;
      c.fade_time = LEDC_FADE_TIME;
    }
    for (int i = 0; i < N_LEDS; ++i) {
      if (c.box_id != -1 && (c.box_id != ledc_channels[i].box || get_box_enabled(ledc_channels[i].box) != 1)) {
        continue;
      }
      if (c.led_id != -1 && (i != c.led_id || ledc_channels[i].enabled != 1)) {
        continue;
      }
      update_led(i, c.fade_time);
    }
  }
}

void init_led_info(int box_id, char *led_info) {
  sprintf(led_info, "n:%d", N_LEDS);
  for (int i = 0; i < N_LEDS; ++i) {
    int bi = get_led_box(i);
    if (ledc_channels[i].enabled != 1 || bi != box_id || get_box_enabled(bi) != 1) {
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

  ledc_timer_config_t ledc_timer = {
    speed_mode:       LEDC_HIGH_SPEED_MODE,
    { duty_resolution:  LED_DUTY_RESOLUTION, },
    timer_num:        LEDC_TIMER_0,
    freq_hz:          500,
  };
  ledc_timer_config(&ledc_timer);

  // TODO remove led array, it's useless now
  for (int i = 0; i < N_LEDS; ++i) {
    ledc_channels[i].enabled = get_led_enabled(i);

    ledc_channels[i].x = get_led_x(i);
    ledc_channels[i].y = get_led_y(i);
    ledc_channels[i].z = get_led_z(i);

    ledc_channels[i].box = get_led_box(i);

    ledc_channels[i].channel_config.gpio_num = get_led_gpio(i);

    if (ledc_channels[i].enabled != 1 || get_box_enabled(ledc_channels[i].box) != 1) {
      continue;
    }

    ledc_channel_config(&ledc_channels[i].channel_config);
  }

  char led_info[CHAR_VAL_LEN_MAX] = {0};
  init_led_info(0, led_info); set_box_0_led_info(led_info);

  cmd = xQueueCreate(10, sizeof(cmd_refresh_led));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@LED Unable to create led queue");
  }

  ledc_fade_func_install(0);

  xTaskCreate(led_task, "LED", 4096, NULL, 10, NULL);
}

void refresh_led(int box_id, int led_id, int fade_time) {
  cmd_refresh_led cmd_data = {
    box_id: box_id,
    led_id: led_id,
    fade_time: fade_time < 0 ? LEDC_FADE_TIME : fade_time,
  };
  xQueueSend(cmd, &cmd_data, 0);
}

/* KV Callbacks */

int on_set_led_duty(int led_id, int value) {
  value = min(100, max(value, 0));
  set_led_duty(led_id, value);
  refresh_led(-1, led_id, 500);
  return value;
}

int on_set_led_dim(int led_id, int value) {
  value = min(100, max(value, 0));
  set_led_dim(led_id, value);
  refresh_led(-1, led_id, 500);
  return value;
}
