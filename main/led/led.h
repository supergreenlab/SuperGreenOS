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

#ifndef LED_H_
#define LED_H_

#include "../core/ble/ble_db.h"
#include "driver/ledc.h"
#include "led_helpers.h"

typedef struct led_config {
  bool enabled;

  int x;
  int y;
  int z;

  int box;

  ledc_channel_config_t channel_config;
  void (*setter)(int);
} led_config_t;

extern int min_x;
extern int max_x;

extern int min_y;
extern int max_y;

extern int min_z;
extern int max_z;

extern led_config_t ledc_channels[];

#define CHANNEL(i, lenabled, lx, ly, lz, b, gpio, timer, chan) { \
    enabled: lenabled, \
    \
    x: lx, \
    y: ly, \
    z: lz, \
    \
    box: b, \
    \
    channel_config: { \
      gpio_num:    gpio, \
      speed_mode:  LEDC_LOW_SPEED_MODE, \
      channel:     LEDC_CHANNEL_##chan, \
      intr_type:   LEDC_INTR_FADE_END, \
      timer_sel:   LEDC_TIMER_##timer, \
      duty:        0, \
    }, \
    setter: set_led_##i##_duty, \
  }

extern const unsigned int N_LEDS;

void init_led();
void refresh_led(int i);

int rset_led_duty(int i, int value);
int rget_led_duty(int i);

#define DEFAULT_LED_0_GPIO 32
#define DEFAULT_LED_1_GPIO 17
#define DEFAULT_LED_2_GPIO 33
#define DEFAULT_LED_3_GPIO 16
#define DEFAULT_LED_4_GPIO 25
#define DEFAULT_LED_5_GPIO 4

/* BLE Callbacks */

int on_set_led_duty(int ledId, int value);

#endif
