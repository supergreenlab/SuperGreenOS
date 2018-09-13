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

#ifndef TIMER_H_
#define TIMER_H_

#include "esp_gatt_common_api.h"

extern const uint8_t TIMER_TYPE_UUID[ESP_UUID_LEN_128];
extern const uint8_t TIMER_OUTPUT_UUID[ESP_UUID_LEN_128];
extern const uint8_t STARTED_AT_UUID[ESP_UUID_LEN_128];

enum timer {
  TIMER_MANUAL,
  TIMER_ONOFF,
  TIMER_SEASON,
};

#define TIMER_TYPE "TIMER_T"
#define TIMER_OUTPUT "TIMER_O"
#define STARTED_AT "ST_AT"

void update_output(int output);

void init_timer();
void on_set_timer_type(enum timer t);
void on_set_timer_output(int value);
void on_set_started_at(int value);

#endif
