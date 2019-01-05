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

#ifndef WIFI_H_
#define WIFI_H_

#include "esp_gatts_api.h"

#ifdef __cplusplus
extern "C" {
#endif

  extern const uint8_t WIFI_STATUS_UUID[ESP_UUID_LEN_128];
  extern const uint8_t WIFI_SSID_UUID[ESP_UUID_LEN_128];
  extern const uint8_t WIFI_PASS_UUID[ESP_UUID_LEN_128];

  void init_wifi();

  void wait_connected();

  void on_set_wifi_ssid(const char *ssid);
  void on_set_wifi_password(const char *pass);

#ifdef __cplusplus
}
#endif

#endif
