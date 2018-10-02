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
#include "../log/log.h"

#define LEDC_FADE_TIME         (50)

#define LED_MIN_DUTY           (0)
#define LED_MAX_DUTY           (8191)

#define RED_GPIO  19
#define BLUE_GPIO 18

ledc_channel_config_t red;
ledc_channel_config_t blue;

static void fade_no_wait_led(ledc_channel_config_t ledc_channel, int duty) {
  ledc_set_fade_with_time(ledc_channel.speed_mode,
      ledc_channel.channel, duty, LEDC_FADE_TIME);
  ledc_fade_start(ledc_channel.speed_mode,
      ledc_channel.channel, LEDC_FADE_NO_WAIT);
}

static void status_led_task(void *param) {
  double i = 0;
  while (1) {
    fade_no_wait_led(red, (int)((cosf(i) + 1) / 2 * 8191));
    fade_no_wait_led(blue, (int)((-cosf(i / 2) + 1) / 2 * 8191));

    i += M_PI / 10;
    vTaskDelay(1 * LEDC_FADE_TIME / portTICK_PERIOD_MS);
  }
}

void init_status_led() {
  ESP_LOGI(TAG, "Status led");

  ledc_timer_config_t ledc_timer = {
    speed_mode:       LEDC_LOW_SPEED_MODE,
    { duty_resolution:  LEDC_TIMER_13_BIT, },
    timer_num:        LEDC_TIMER_3,
    freq_hz:          120,
  };
  ledc_timer_config(&ledc_timer);

  red = (ledc_channel_config_t) {
    gpio_num:    RED_GPIO,
    speed_mode:  LEDC_LOW_SPEED_MODE,
    channel:     LEDC_CHANNEL_6,
    intr_type:   LEDC_INTR_FADE_END,
    timer_sel:   LEDC_TIMER_3,
    duty:        0,
  };
  ledc_channel_config(&red);

  blue = (ledc_channel_config_t) {
    gpio_num:    BLUE_GPIO,
    speed_mode:  LEDC_LOW_SPEED_MODE,
    channel:     LEDC_CHANNEL_7,
    intr_type:   LEDC_INTR_FADE_END,
    timer_sel:   LEDC_TIMER_3,
    duty:        0,
  };
  ledc_channel_config(&blue);

  ledc_fade_func_install(0);

  xTaskCreate(status_led_task, "Status Led task", 2048, NULL, 10, NULL);
}
