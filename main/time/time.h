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

#ifndef TIME_H_
#define TIME_H_

#include "esp_gatt_common_api.h"

#ifdef __cplusplus
extern "C" {
#endif

  extern const uint8_t TIME_SERVICE[ESP_UUID_LEN_128];
  extern const uint8_t TIME_UUID[ESP_UUID_LEN_128];
  extern const uint8_t SIMULATED_TIME_UUID[ESP_UUID_LEN_128];
  extern const uint8_t START_DATE_MONTH_UUID[ESP_UUID_LEN_128];
  extern const uint8_t START_DATE_DAY_UUID[ESP_UUID_LEN_128];
  extern const uint8_t DURATION_DAYS_UUID[ESP_UUID_LEN_128];
  extern const uint8_t SIMULATION_DURATION_DAYS_UUID[ESP_UUID_LEN_128];
  extern const uint8_t STARTED_AT_UUID[ESP_UUID_LEN_128];

  void init_time();
  time_t get_box_time();

  void on_set_time(time_t value);
  void on_set_start_date_month(int value);
  void on_set_start_date_day(int value);
  void on_set_duration_days(int value);
  void on_set_simulation_duration_days(int value);
  void on_set_started_at(int value);

#ifdef __cplusplus
}
#endif

#endif
