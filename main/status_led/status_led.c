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

#include <stdlib.h>
#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/ledc.h"

#include "status_led.h"
#include "../core/log/log.h"
#include "../core/kv/kv.h"

static QueueHandle_t cmd;

status_led_timeline DEFAULT_TIMELINE = {
  .loop = true,
  .fade = true,
  .step = 0.07,
  .red = {LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY},
  .green = {LED_MAX_DUTY, LED_MAX_DUTY, LED_MAX_DUTY/5, LED_MAX_DUTY/5, LED_MAX_DUTY, LED_MAX_DUTY, LED_MAX_DUTY/5, LED_MAX_DUTY/5},
};

ledc_channel_config_t red;
ledc_channel_config_t green;

static double set_duty(ledc_channel_config_t ledc_channel, double led_dim, double duty1, double duty2, double adv) {
  double duty = duty1 + (duty2 - duty1) * adv;
  duty = LED_MAX_DUTY - (duty * led_dim);
  ledc_set_duty_and_update(ledc_channel.speed_mode, ledc_channel.channel, duty, 0);
  return duty;
}

static void status_led_task(void *param) {
  status_led_timeline current_timeline = DEFAULT_TIMELINE;
  double led_dim = (double)get_status_led_dim() / 100.0f;
  double i = 0;
  while (1) {
    if (xQueueReceive(cmd, &current_timeline, 100 / portTICK_PERIOD_MS) == pdTRUE) {
      ESP_LOGI(SGO_LOG_NOSEND, "NEW STATUS TIMELINE");
      i = 0;
    }
    if (is_status_led_dim_changed()) {
      led_dim = (double)get_status_led_dim() / 100.0f;
      reset_status_led_dim_changed();
    }
    double adv = i - (int)i;
    if (current_timeline.fade == false) {
      adv = roundf(adv);
    }
    int i1 = (int)i % STATUS_LED_TIMELINE_LENGTH;
    int i2 = ((int)i+1) % STATUS_LED_TIMELINE_LENGTH;
    set_duty(red, led_dim, current_timeline.red[i1], current_timeline.red[i2], adv);
    set_duty(green, led_dim, current_timeline.green[i1], current_timeline.green[i2], adv);

    i += current_timeline.step;
    if (i2 == 0) {
      if (current_timeline.loop == false) {
        current_timeline = DEFAULT_TIMELINE;
        i = 0;
      }
    }
  }
}

void set_status_led_timeline(status_led_timeline timeline) {
  xQueueSend(cmd, &timeline, 0);
}

void init_status_led() {
  ESP_LOGI(SGO_LOG_EVENT, "@STATUS_LED Initializing status_led module");

  cmd = xQueueCreate(10, sizeof(status_led_timeline));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@MOTOR Unable to create motor queue");
  }

  ledc_timer_config_t ledc_timer = {
    speed_mode:       LEDC_LOW_SPEED_MODE,
    { duty_resolution:  9, },
    timer_num:        LEDC_TIMER_1,
    freq_hz:          5000,
  };
  ledc_timer_config(&ledc_timer);

  int red_gpio = get_status_led_red_gpio();
  red = (ledc_channel_config_t) {
    gpio_num:    red_gpio,
    speed_mode:  LEDC_LOW_SPEED_MODE,
    channel:     LEDC_CHANNEL_0,
    timer_sel:   LEDC_TIMER_1,
    hpoint:      0,
    duty:        0,
  };
  ledc_channel_config(&red);

  int green_gpio = get_status_led_green_gpio();
  green = (ledc_channel_config_t) {
    gpio_num:    green_gpio,
    speed_mode:  LEDC_LOW_SPEED_MODE,
    channel:     LEDC_CHANNEL_1,
    timer_sel:   LEDC_TIMER_1,
    hpoint:      0,
    duty:        0,
  };
  ledc_channel_config(&green);

  BaseType_t ret = xTaskCreatePinnedToCore(status_led_task, "STATUS_LED", 4096, NULL, 10, NULL, 1);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@STATUS_LED Failed to create task");
  }
}
