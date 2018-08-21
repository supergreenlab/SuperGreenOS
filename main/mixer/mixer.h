/*
 * =====================================================================================
 *
 *       Filename:  mixer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/16/2018 15:49:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef MIXER_H_
#define MIXER_H_

#include "esp_gatt_common_api.h"

extern const uint8_t LED_DIM_UUID[ESP_UUID_LEN_128];

void init_mixer();

// BLE Callbacks

void on_set_led_dim(int value);

#endif
