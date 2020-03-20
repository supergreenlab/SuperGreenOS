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
#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_err.h"

#include "led.h"
#include "../core/kv/kv.h"
#include "../core/log/log.h"

#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

#define LED_MIN_ZERO           5
#define LED_DUTY_RESOLUTION    10
#define LED_MIN_DUTY           0
#define LED_MAX_DUTY           pow(2, LED_DUTY_RESOLUTION)
#define LED_FREQ_FAST          20000
#define LED_FREQ_SLOW          2000

#define LEDC_FADE_TIME         (500)
#define SPEED_MODE LEDC_HIGH_SPEED_MODE
#define LEDC_CHANNEL(i) LEDC_CHANNEL_0+i

typedef struct {
  int box_id;
  int led_id;
} cmd_refresh_led;
static QueueHandle_t cmd;

static void fade_no_wait_led(int i, int duty) {
  uint32_t current_duty = ledc_get_duty(SPEED_MODE, LEDC_CHANNEL(i)); 
  if (current_duty == duty) {
    return;
  }
  ledc_set_fade_with_time(SPEED_MODE, LEDC_CHANNEL(i), duty, LEDC_FADE_TIME);
  ledc_fade_start(SPEED_MODE, LEDC_CHANNEL(i), LEDC_FADE_NO_WAIT);
}

static void update_led(int i) {
  double dim = get_led_dim(i);
  double duty = get_led_duty(i) * dim / 100;
  duty = (duty < LED_MIN_ZERO) ? 0 : duty;
  if (get_led_fade(i) == 1) {
    double real_duty = LED_MIN_DUTY + (double)(LED_MAX_DUTY - LED_MIN_DUTY) * duty / 100;
    //ESP_LOGI(SGO_LOG_EVENT, "@LED REAL_DUTY_%d=%d", i, (int)real_duty);

    fade_no_wait_led(i, real_duty);
  } else {
    duty = (duty == 0 ? duty : LED_MAX_DUTY);
    ledc_set_duty(SPEED_MODE, LEDC_CHANNEL(i), duty);
    ledc_update_duty(SPEED_MODE, LEDC_CHANNEL(i));
  }
}

static void led_task(void *param) {

  cmd_refresh_led c;

  while(1) {
    if (!xQueueReceive(cmd, &c, 5000 / portTICK_PERIOD_MS)) {
      c.box_id = -1;
      c.led_id = -1;
    }
    for (int i = 0; i < N_LED; ++i) {
      if (c.box_id != -1 && c.box_id != get_led_box(i)) {
        continue;
      }
      if (c.led_id != -1 && i != c.led_id) {
        continue;
      }
      update_led(i);
    }
    vTaskDelay((LEDC_FADE_TIME * 1.1) / portTICK_RATE_MS);
  }
}

void init_led() {
  ESP_LOGI(SGO_LOG_EVENT, "@LED Initializing led task");

  ledc_timer_config_t ledc_timer = {
    speed_mode:       LEDC_HIGH_SPEED_MODE,
    { duty_resolution:  LED_DUTY_RESOLUTION, },
    timer_num:        LEDC_TIMER_0,
    freq_hz:          get_leds_fastmode() ? LED_FREQ_FAST : LED_FREQ_SLOW,
  };
  ledc_timer_config(&ledc_timer);

  // TODO remove led array, it's useless now
  for (int i = 0; i < N_LED; ++i) {
    ledc_channel_config_t channel_config = {
      gpio_num:    get_led_gpio(i),
      speed_mode:  SPEED_MODE,
      channel:     LEDC_CHANNEL(i),
      timer_sel:   LEDC_TIMER_0,
      hpoint:      0,
      duty:        0,
    };
    ledc_channel_config(&channel_config);
  }

  cmd = xQueueCreate(10, sizeof(cmd_refresh_led));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@LED Unable to create led queue");
  }

  ledc_fade_func_install(0);

  BaseType_t ret = xTaskCreatePinnedToCore(led_task, "LED", 4096, NULL, 10, NULL, 1);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@LED Failed to create task");
  }
}

void refresh_led(int box_id, int led_id) {
  cmd_refresh_led cmd_data = {
    box_id: box_id,
    led_id: led_id,
  };
  xQueueSend(cmd, &cmd_data, 0);
}

/* KV Callbacks */

int on_set_led_duty(int led_id, int value) {
  value = min(100, max(value, 0));
  set_led_duty(led_id, value);
  refresh_led(-1, led_id);
  return value;
}

int on_set_led_dim(int led_id, int value) {
  value = min(100, max(value, 0));
  set_led_dim(led_id, value);
  refresh_led(-1, led_id);
  return value;
}
