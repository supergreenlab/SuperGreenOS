/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#ifndef BLE_H_
#define BLE_H_

#include "../ble_db.h"

void init_ble();
void notify_handle(enum idx i, const uint8_t *notify_data, uint16_t notify_data_length);
void notify_attr(enum idx i);

void set_attr_value(enum idx i, const uint8_t *value, uint16_t value_length);

#endif
