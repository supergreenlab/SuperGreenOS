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

#ifndef BLE_H_
#define BLE_H_

#include "ble_db.h"

void init_ble();
void notify_handle(enum idx i, const uint8_t *notify_data, uint16_t notify_data_length);
void notify_attr(enum idx i);

void set_attr_value(enum idx i, const uint8_t *value, uint16_t value_length);

void set_attr_value_and_notify(enum idx i, const uint8_t *value, uint16_t value_length);

#endif
