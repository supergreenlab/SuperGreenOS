/*
 * =====================================================================================
 *
 *       Filename:  timer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/13/2018 12:05:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "esp_gatt_common_api.h"

extern const uint8_t TIMER_TYPE_UUID[ESP_UUID_LEN_128];
extern const uint8_t TIMER_OUTPUT_UUID[ESP_UUID_LEN_128];
extern const uint8_t STARTED_AT_UUID[ESP_UUID_LEN_128];

enum timer {
  TIMER_MANUAL,
  TIMER_ONOFF,
  TIMER_SEASON,
};

#define TIMER_TYPE "TIMER_T"
#define TIMER_OUTPUT "TIMER_O"
#define STARTED_AT "ST_AT"

void update_output(int output);

void init_timer();
void on_set_timer_type(enum timer t);
void on_set_timer_output(int value);
void on_set_started_at(int value);

#endif
