/*
 * =====================================================================================
 *
 *       Filename:  onoff.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/13/2018 15:34:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef ONOFF_H_
#define ONOFF_H_

#include "esp_gatt_common_api.h"

#ifdef __cplusplus
extern "C" {
#endif

  extern const uint8_t ON_HOUR_UUID[ESP_UUID_LEN_128];
  extern const uint8_t ON_MIN_UUID[ESP_UUID_LEN_128];
  extern const uint8_t OFF_HOUR_UUID[ESP_UUID_LEN_128];
  extern const uint8_t OFF_MIN_UUID[ESP_UUID_LEN_128];

  void init_onoff();
  void start_onoff();
  void stop_onoff();
  void onoff_task();

  void on_set_on_hour(int value);
  void on_set_on_min(int value);
  void on_set_off_hour(int value);
  void on_set_off_min(int value);

#ifdef __cplusplus
}
#endif

#endif
