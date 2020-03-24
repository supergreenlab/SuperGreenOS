/*
 * Copyright (C) 2020  SuperGreenLab <towelie@supergreenlab.com>
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

#include "../core/log/log.h"
#include "sht1x.h"
#include "sht1x_driver.h"
#include "../core/i2c/i2c.h"
#include "../core/kv/kv.h"
#include "../box/box.h"

void init_sht1x(int portId, int sda, int sdk) {
  int boxId = portId;

  ESP_LOGI(SGO_LOG_EVENT, "@SHT1X_%d Initializing sht1x pseudo i2c device", boxId);
}

void loop_sht1x(int portId, int sda, int sck) {
  int boxId = portId;

  esp_log_level_set("gpio", ESP_LOG_NONE);
  stop_i2c(portId);
  float temp_c = read_temperature_c(sda, sck);
  float temp_f = read_temperature_f(sda, sck);
  float humi = read_humidity(sda, sck);
  set_box_sht1x_temp_c(boxId, temp_c);
  set_box_sht1x_temp_f(boxId, temp_f);
  set_box_sht1x_humi(boxId, humi);

  ESP_LOGI(SGO_LOG_METRIC, "@SHT1X_%d temp_c=%f, temp_f=%f, humi=%f", boxId, temp_c, temp_f, humi);

  release_gpios(sda, sck);
}
