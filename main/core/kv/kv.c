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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../log/log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

#include "kv.h"
#include "kv_ble.h"
#include "../include_modules.h"

nvs_handle open_handle() {
  nvs_handle kv_handle;
  esp_err_t err = nvs_open("kv_store", NVS_READWRITE, &kv_handle);
  if (err != ESP_OK) {
    ESP_LOGI(SGO_LOG_EVENT, "@KV Error (%s) opening NVS handle!\n", esp_err_to_name(err));
  }
  return kv_handle;
}

void preinit_kv() {
  // Initialize NVS
  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
    // NVS partition was truncated and needs to be erased
    // Retry nvs_flash_init
    ESP_ERROR_CHECK(nvs_flash_erase());
    err = nvs_flash_init();
  }
  ESP_ERROR_CHECK( err );

  open_handle();

  /*
   * [GENERATED]
   */

  defaultstr(WIFI_SSID, "");
  defaultstr(WIFI_PASS, "");
  defaulti(TIME, 0);
  defaultstr(OTA_SERVER_IP, CONFIG_OTA_SERVER_IP);
  defaultstr(OTA_SERVER_HOSTNAME, CONFIG_OTA_SERVER_HOSTNAME);
  defaultstr(OTA_SERVER_PORT, CONFIG_OTA_SERVER_PORT);
  defaultstr(OTA_VERSION_FILENAME, CONFIG_OTA_VERSION_FILENAME);
  defaultstr(OTA_FILENAME, CONFIG_OTA_FILENAME);
  defaulti(I2C_SDA, DEFAULT_I2C_SDA);
  defaulti(I2C_SCL, DEFAULT_I2C_SCL);
  defaulti(STATE, FIRST_RUN);
  defaultstr(DEVICE_NAME, "SuperGreenDriver");
  defaulti(TIMER_TYPE, TIMER_MANUAL);
  defaulti(TIMER_OUTPUT, 0);
  defaulti(STARTED_AT, 0);
  defaulti(ON_HOUR, 1);
  defaulti(ON_MIN, 0);
  defaulti(OFF_HOUR, 19);
  defaulti(OFF_MIN, 0);
  defaulti(STRETCH, 0);
  defaulti(LED_DIM, 0);
  defaulti(BLOWER, 50);
  defaulti(BLOWER_GPIO, DEFAULT_BLOWER_GPIO);
  defaulti(SHT1X_TEMP_C, -1000000);
  defaulti(SHT1X_TEMP_F, -1000000);
  defaulti(SHT1X_HUMI, -1000000);
  defaultstr(LED_INFO, "0");
  defaulti(LED_0_DUTY, 0);
  defaulti(LED_1_DUTY, 0);
  defaulti(LED_2_DUTY, 0);
  defaulti(LED_3_DUTY, 0);
  defaulti(LED_4_DUTY, 0);
  defaulti(LED_5_DUTY, 0);
  defaulti(LED_0_GPIO, 0);
  defaulti(LED_1_GPIO, 0);
  defaulti(LED_2_GPIO, 0);
  defaulti(LED_3_GPIO, 0);
  defaulti(LED_4_GPIO, 0);
  defaulti(LED_5_GPIO, 0);
  defaulti(LED_0_X, 0);
  defaulti(LED_1_X, 0);
  defaulti(LED_2_X, 0);
  defaulti(LED_3_X, 0);
  defaulti(LED_4_X, 0);
  defaulti(LED_5_X, 0);
  defaulti(LED_0_Y, 0);
  defaulti(LED_1_Y, 0);
  defaulti(LED_2_Y, 0);
  defaulti(LED_3_Y, 0);
  defaulti(LED_4_Y, 0);
  defaulti(LED_5_Y, 0);
  defaulti(LED_0_Z, 0);
  defaulti(LED_1_Z, 0);
  defaulti(LED_2_Z, 0);
  defaulti(LED_3_Z, 0);
  defaulti(LED_4_Z, 0);
  defaulti(LED_5_Z, 0);

  /*
   * [/GENERATED]
   */
}

void postinit_kv() {
  /*
   * [GENERATED]
   */

  sync_ble_str(WIFI_SSID, IDX_VALUE(WIFI_SSID));
  sync_ble_i(TIME, IDX_VALUE(TIME));
  sync_ble_str(OTA_SERVER_IP, IDX_VALUE(OTA_SERVER_IP));
  sync_ble_str(OTA_SERVER_HOSTNAME, IDX_VALUE(OTA_SERVER_HOSTNAME));
  sync_ble_str(OTA_SERVER_PORT, IDX_VALUE(OTA_SERVER_PORT));
  sync_ble_str(OTA_VERSION_FILENAME, IDX_VALUE(OTA_VERSION_FILENAME));
  sync_ble_str(OTA_FILENAME, IDX_VALUE(OTA_FILENAME));
  sync_ble_i(STATE, IDX_VALUE(STATE));
  sync_ble_str(DEVICE_NAME, IDX_VALUE(DEVICE_NAME));
  sync_ble_i(TIMER_TYPE, IDX_VALUE(TIMER_TYPE));
  sync_ble_i(STARTED_AT, IDX_VALUE(STARTED_AT));
  sync_ble_i(ON_HOUR, IDX_VALUE(ON_HOUR));
  sync_ble_i(ON_MIN, IDX_VALUE(ON_MIN));
  sync_ble_i(OFF_HOUR, IDX_VALUE(OFF_HOUR));
  sync_ble_i(OFF_MIN, IDX_VALUE(OFF_MIN));
  sync_ble_i(STRETCH, IDX_VALUE(STRETCH));
  sync_ble_i(LED_DIM, IDX_VALUE(LED_DIM));
  sync_ble_i(BLOWER, IDX_VALUE(BLOWER));
  sync_ble_i(SHT1X_TEMP_C, IDX_VALUE(SHT1X_TEMP_C));
  sync_ble_i(SHT1X_TEMP_F, IDX_VALUE(SHT1X_TEMP_F));
  sync_ble_i(SHT1X_HUMI, IDX_VALUE(SHT1X_HUMI));
  sync_ble_str(LED_INFO, IDX_VALUE(LED_INFO));

  /*
   * [/GENERATED]
   */
}

bool hasi(const char * key) {
  int32_t value;
  nvs_handle kv_handle = open_handle();
  esp_err_t err = nvs_get_i32(kv_handle, (const char *)key, &value);
  nvs_close(kv_handle);
  return err == ESP_OK;
}

int geti(const char * key) {
  nvs_handle kv_handle = open_handle();
  int32_t value;
  esp_err_t err = nvs_get_i32(kv_handle, (const char *)key, &value);
  ESP_ERROR_CHECK(err);
  nvs_close(kv_handle);
  return (int)value;
}

void seti(const char * key, int value) {
  nvs_handle kv_handle = open_handle();
  esp_err_t err = nvs_set_i32(kv_handle, (const char *)key, (int32_t)value);
  ESP_ERROR_CHECK(err);
  nvs_commit(kv_handle);
  nvs_close(kv_handle);
  ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", key, value);
}

void defaulti(const char * key, int value) {
  if (!hasi(key)) {
    seti(key, value);
  } else {
    int v = geti(key);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", key, v);
  }
}

bool hasstr(const char * key) {
  nvs_handle kv_handle = open_handle();
  size_t length;
  esp_err_t err = nvs_get_str(kv_handle, (const char *)key, NULL, &length);
  nvs_close(kv_handle);
  return err == ESP_OK;
}

void getstr(const char * key, char *value, size_t length) {
  nvs_handle kv_handle = open_handle();
  esp_err_t err = nvs_get_str(kv_handle, key, value, &length);
  ESP_ERROR_CHECK(err);
  nvs_close(kv_handle);
}

void setstr(const char * key, const char * value) {
  nvs_handle kv_handle = open_handle();
  esp_err_t err = nvs_set_str(kv_handle, (const char *)key, value);
  ESP_ERROR_CHECK(err);
  nvs_commit(kv_handle);
  nvs_close(kv_handle);

  ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", key, value);
}

void defaultstr(const char * key, const char * value) {
  bool skip = strcmp(key, "WPASS") == 0;
  
  if (!hasstr(key)) {
    setstr(key, value);
  } else {
    char buf[MAX_KVALUE_SIZE] = {0};
    getstr(key, buf, sizeof(buf) - 1);
    ESP_LOGI(skip ? SGO_LOG_NOSEND : SGO_LOG_METRIC, "@KV %s=%s", key, buf);
  }
}
