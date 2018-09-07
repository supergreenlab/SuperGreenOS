/*
 * =====================================================================================
 *
 *       Filename:  blower.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/13/2018 15:27:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BLOWER_H_
#define BLOWER_H_

#include "esp_gatt_common_api.h"

extern const uint8_t BLOWER_UUID[ESP_UUID_LEN_128];

void init_blower();

/* BLE Callbacks */

void on_set_blower(int value);

#endif
