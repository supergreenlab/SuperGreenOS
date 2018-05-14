/*
 * =====================================================================================
 *
 *       Filename:  wifi.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/16/2018 19:25:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef WIFI_H_
#define WIFI_H_

#include "esp_gatts_api.h"

#ifdef __cplusplus
extern "C" {
#endif

  extern const uint8_t WIFI_STATUS_UUID[ESP_UUID_LEN_128];
  extern const uint8_t WIFI_SSID_UUID[ESP_UUID_LEN_128];
  extern const uint8_t WIFI_PASS_UUID[ESP_UUID_LEN_128];

  void init_wifi();

  void wait_connected();

  void on_set_wifi_ssid(const char *ssid);
  void on_set_wifi_password(const char *pass);

#ifdef __cplusplus
}
#endif

#endif
