/*
 * =====================================================================================
 *
 *       Filename:  state.h
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

#ifndef STATE_H_
#define STATE_H_

#include "esp_gatt_common_api.h"

#define STATE "STATE"

extern const uint8_t STATE_UUID[ESP_UUID_LEN_128];
extern const uint8_t DEVICE_NAME_UUID[ESP_UUID_LEN_128];

enum state {
  FIRST_RUN,
  IDLE,
  RUNNING
};

void init_state();

// BLE Callbacks

void on_set_state(enum state value);
void on_set_device_name(const char *value);

#endif
