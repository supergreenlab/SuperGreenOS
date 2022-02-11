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

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "log/log.h"
#include "kv/kv.h"
#include "tester/tester.h"
#include "cmd/cmd.h"
#include "term/term.h"
#include "reboot/reboot.h"
#include "mqtt/mqtt.h"
#include "wifi/wifi.h"
#include "vpn/vpn.h"
#include "time/time.h"
#include "i2c/i2c.h"
#include "ota/ota.h"
#include "stat_dump/stat_dump.h"
#include "httpd/httpd.h"

void preinit_app();
void init_app(bool tester);

void app_main() {
  ESP_LOGI(SGO_LOG_EVENT, "@MAIN Welcome to SuperGreenOS version=%s\n", CONFIG_VERSION);

  open_kv();
  init_reboot();

  mqtt_intercept_log();

  init_kv();
  set_n_restarts(get_n_restarts()+1);

  preinit_app();

  init_cmd();
  init_term();

  init_spiffs();

  init_tester();

  init_wifi();
  init_vpn();

  init_mqtt();
  init_ota();
  init_time();
  init_i2c();

  bool tester_enabled = get_tester_enabled() != 0;
  init_app(tester_enabled);
  if (tester_enabled) {
    reset_on_next_reboot();
  }

  init_stat_dump();

  init_httpd();

  fflush(stdout);
}
