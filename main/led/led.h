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

#include "esp_gatt_common_api.h"
#include "driver/ledc.h"

#include "../conf/ble_db.h"

extern const uint8_t LED_INFO_UUID[ESP_UUID_LEN_128];

/*  UUID string: 4291ec1b-65df-19c4-c5f1-e4259071fc00 */
#define LED_DUTY_UUID_HEADER(i) extern const uint8_t LED_##i##_DUTY_UUID[ESP_UUID_LEN_128];
#define LED_DUTY_UUID(i) const uint8_t LED_##i##_DUTY_UUID[ESP_UUID_LEN_128] = {i,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x42};

typedef struct led_config {
  enum idx       duty_val_idx;

  int min_duty;
  int max_duty;

  int x;
  int y;
  int z;

  ledc_channel_config_t channel_config;
} led_config_t;

extern int min_x;
extern int max_x;

extern int min_y;
extern int max_y;

extern int min_z;
extern int max_z;

extern led_config_t ledc_channels[];

#define CHANNEL(i, min_d, max_d, lx, ly, lz, gpio, timer, chan) { \
    duty_val_idx: IDX_VALUE(LED_##i##_DUTY), \
    min_duty: min_d, \
    max_duty: max_d, \
    x: lx, \
    y: ly, \
    z: lz, \
    \
    channel_config: { \
      gpio_num:    gpio, \
      speed_mode:  LEDC_LOW_SPEED_MODE, \
      channel:     LEDC_CHANNEL_##chan, \
      intr_type:   LEDC_INTR_FADE_END, \
      timer_sel:   LEDC_TIMER_##timer, \
      duty:        0, \
    } \
  }

extern const unsigned int N_LEDS;

void init_led();
void refresh_led(int i);

void set_led_duty(int i, int value);
int get_led_duty(int i);

/* BLE Callbacks */

void on_set_led_duty(enum idx iv, int i, int value);

#endif
