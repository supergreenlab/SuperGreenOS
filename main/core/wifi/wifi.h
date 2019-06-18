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

#define DEFAULT_AP_SSID "🤖🍁"
#define DEFAULT_AP_PASSWORD "multipass"

typedef enum {
  DISCONNECTED = 1,
  CONNECTING,
  CONNECTED,
  FAILED,
  AP,
} wifi_status;

void init_wifi();

void wait_connected();

const char *on_set_wifi_ssid(const char *ssid);
const char *on_set_wifi_password(const char *pass);

#endif
