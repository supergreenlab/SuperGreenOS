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

#ifndef MIXER_H_
#define MIXER_H_

#include "esp_gatt_common_api.h"

extern const uint8_t LED_DIM_UUID[ESP_UUID_LEN_128];
extern const uint8_t STRETCH_UUID[ESP_UUID_LEN_128];

void init_mixer();

// BLE Callbacks

int on_set_led_dim(int value);
int on_set_stretch(int value);

#endif
