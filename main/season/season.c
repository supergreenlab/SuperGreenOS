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

#include "season.h"

#include <time.h>
#include <string.h>

#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../timer/timer.h"
#include "../core/log/log.h"
#include "../core/time/utils.h"
#include "../core/kv/kv.h"

#define START_DATE_MONTH "SIM_S_M"
#define START_DATE_DAY "SIM_S_D"
#define DURATION_DAYS "DUR_D"
#define SIMULATION_DURATION_DAYS "SIM_DUR_D"

#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

#define YEAR_ADV_OFFSET (time_t)(10*24*60*60) // solstice is 21st June, that's the 172nd day in year

time_t get_box_time(int boxId) {
  int start_date_month = get_box_start_month(boxId);
  int start_date_day = get_box_start_day(boxId);
  int duration_days = get_box_duration_days(boxId);
  int simulation_duration_days = get_box_sim_duration_days(boxId);
  int started_at = get_box_started_at(boxId);

  time_t now;
  struct tm tm_now;
  time(&now);
  localtime_r(&now, &tm_now); 

  time_t started_at_t = (time_t)started_at;
  struct tm tm_started_at;
  localtime_r(&started_at_t, &tm_started_at);

  double duration = (double)((int)now - (int)started_at_t) / (double)(24 * 60 * 60);
  double adv = min(1, (double)duration / (double)simulation_duration_days);

  struct tm tm_simulated;
  memset(&tm_simulated, 0, sizeof(tm_simulated));
  tm_simulated.tm_year = tm_started_at.tm_year;
  tm_simulated.tm_mon = start_date_month;
  tm_simulated.tm_mday = start_date_day;
  tm_simulated.tm_hour = tm_now.tm_hour;
  tm_simulated.tm_min = tm_now.tm_min;
  tm_simulated.tm_sec = tm_now.tm_sec;

  time_t simulated_time = mktime(&tm_simulated);
  int seconds_to_adv = adv * duration_days * 24 * 60 * 60;
  simulated_time += seconds_to_adv - (seconds_to_adv % (24 * 60 * 60));
  localtime_r(&simulated_time, &tm_simulated);

  return simulated_time;
}

int get_output_for_time(int boxId) {
  time_t now = get_box_time(boxId) - YEAR_ADV_OFFSET;

  struct tm timeinfo;
  localtime_r(&now, &timeinfo); 

  double day_adv = (double)(timeinfo.tm_hour*60*60 + timeinfo.tm_min*60 + timeinfo.tm_sec) / (double)(24*60*60);
  double year_adv = (double)(timeinfo.tm_yday) / (double) 365;

  double output = cos(year_adv * M_PI * 2) * 0.25 - cos(day_adv * M_PI * 2) * ((-cos(year_adv * M_PI * 2) + 1) / 2 * 1 + 1) + 0.25;
  ESP_LOGI(SGO_LOG_METRIC, "@SEASON year_adv = %f, day_adv = %f, output = %f", year_adv, day_adv, output);
  return min(100, max(0, output * 100));
}

void start_season(int boxId) {
  ESP_LOGI(SGO_LOG_EVENT, "@SEASON start_season");
  season_task();
}

void stop_season(int boxId) {
  ESP_LOGI(SGO_LOG_EVENT, "@SEASON stop_season");
}

void season_task(int boxId) {
  time_t box_time = get_box_time(boxId);
  ESP_LOGI(SGO_LOG_METRIC, "@SEASON SIMULATED_TIME = %lu", box_time);
  print_time(SGO_LOG_NOSEND, "SEASON", box_time);
  set_box_simulated_time(boxId, box_time);

  set_box_timer_output(boxId, get_output_for_time(boxId));
}
