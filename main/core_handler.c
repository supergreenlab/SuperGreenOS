/*
 * Copyright (C) 2021  SuperGreenLab <towelie@supergreenlab.com>
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

#include "./core/wifi/wifi.h"
#include "./core/kv/kv.h"
#include "./core/log/log.h"

#include "./status_led/status_led.h"

status_led_timeline connecting_timeline = {
  .reset = true,
  .loop = true,
  .fade = false,
  .step = 0.4,
  .red = {LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY, LED_MAX_DUTY/10},
  .green = {LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY, LED_MAX_DUTY/10},
};

status_led_timeline connected_timeline = {
  .reset = true,
  .loop = false,
  .fade = false,
  .step = 1,
  .red = {LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY},
  .green = {LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY, LED_MAX_DUTY/10},
};

status_led_timeline connection_failed_timeline = {
  .reset = true,
  .loop = false,
  .fade = false,
  .step = 1,
  .red = {LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY, LED_MAX_DUTY/10},
  .green = {LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY},
};

void on_wifi_status_changed() {
  wifi_status status = get_wifi_status();

  if (status == CONNECTING) {
    set_status_led_timeline(connecting_timeline);
  } else if (status == CONNECTED) {
    set_status_led_timeline(connected_timeline);
  } else if (status == FAILED) {
    set_status_led_timeline(connection_failed_timeline);
  }
}
