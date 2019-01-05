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

#include "ble.h"
#include "ble_utils.h"

void notify_handle(enum idx i, const uint8_t *notify_data, uint16_t notify_data_length) {
  if (profile_tab[PROFILE_APP_IDX].gatts_if == ESP_GATT_IF_NONE || profile_tab[PROFILE_APP_IDX].conn_id == UINT16_MAX) return;

  ESP_ERROR_CHECK(esp_ble_gatts_send_indicate(profile_tab[PROFILE_APP_IDX].gatts_if, profile_tab[PROFILE_APP_IDX].conn_id, handle_table[i], notify_data_length, (uint8_t *)notify_data, false));
}

void notify_attr(enum idx i) {
  if (profile_tab[PROFILE_APP_IDX].gatts_if == ESP_GATT_IF_NONE || profile_tab[PROFILE_APP_IDX].conn_id == UINT16_MAX) return;

  const uint8_t *value;
  uint16_t value_length;
  
  ESP_ERROR_CHECK(esp_ble_gatts_get_attr_value(handle_table[i], &value_length, &value));
  notify_handle(i, value, value_length);
}

void set_attr_value(enum idx i, const uint8_t *value, uint16_t value_length) {
  ESP_ERROR_CHECK(esp_ble_gatts_set_attr_value(handle_table[i], value_length, value));
}

void set_attr_value_and_notify(enum idx i, const uint8_t *value, uint16_t value_length) {
  set_attr_value(i, value, value_length);
  notify_handle(i, value, value_length);
}
