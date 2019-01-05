/*
 * Copyright (C) 2019  SuperGreenLab <towelie@supergreenlab.com>
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

#include <string.h>

#include "kv.h"
#include "kv_ble.h"
#include "../ble/ble.h"

/*
 * [GENERATED]
 */

void set_wifi_ssid(const char *value) {
  setstr(WIFI_SSID, value);
}
void set_wifi_password(const char *value) {
  setstr(WIFI_PASS, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_WIFI_PASS, (uint8_t *)value, strlen(value));
}
void set_time(int value) {
  seti(TIME, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_TIME, (uint8_t *)&value, sizeof(int));
}
void set_ota_server_ip(const char *value) {
  setstr(OTA_SERVER_IP, value);
}
void set_ota_server_hostname(const char *value) {
  setstr(OTA_SERVER_HOSTNAME, value);
}

/*
 * [/GENERATED]
 */
