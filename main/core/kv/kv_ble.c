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
#include <string.h>

#include "../log/log.h"
#include "./kv.h"
#include "./kv_ble.h"

#include "../ble/ble.h"

void sync_ble_i8(const char *key, enum idx i) {
  int8_t value = geti8(key);
  set_attr_value(i, (const uint8_t *)&value, sizeof(value));
}

void sync_ble_i16(const char *key, enum idx i) {
  int16_t value = geti16(key);
  set_attr_value(i, (const uint8_t *)&value, sizeof(value));
}

void sync_ble_i32(const char *key, enum idx i) {
  int32_t value = geti32(key);
  set_attr_value(i, (const uint8_t *)&value, sizeof(value));
}

void sync_ble_str(const char *key, enum idx i) {
  char value[517] = {0};
  getstr(key, value, sizeof(value) - 1);
  set_attr_value(i, (const uint8_t *)value, strlen(value));
}
