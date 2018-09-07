/*
 * =====================================================================================
 *
 *       Filename:  time.h
 *
 *    Description:  ej
 *
 *        Version:  1.0
 *        Created:  04/16/2018 19:26:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef SEASON_SIMULATOR_H_
#define SEASON_SIMULATOR_H_

#include "esp_gatt_common_api.h"

extern const uint8_t SIMULATED_TIME_UUID[ESP_UUID_LEN_128];
extern const uint8_t START_DATE_MONTH_UUID[ESP_UUID_LEN_128];
extern const uint8_t START_DATE_DAY_UUID[ESP_UUID_LEN_128];
extern const uint8_t DURATION_DAYS_UUID[ESP_UUID_LEN_128];
extern const uint8_t SIMULATION_DURATION_DAYS_UUID[ESP_UUID_LEN_128];

void init_season();
void start_season();
void stop_season();
void season_task();

time_t get_box_time();

void on_set_start_date_month(int value);
void on_set_start_date_day(int value);
void on_set_duration_days(int value);
void on_set_simulation_duration_days(int value);

#endif
