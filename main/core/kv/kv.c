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
#include "../stat_dump/stat_dump.h"

nvs_handle open_handle() {
  nvs_handle kv_handle;
  esp_err_t err = nvs_open("kv_store", NVS_READWRITE, &kv_handle);
  if (err != ESP_OK) {
    ESP_LOGI(SGO_LOG_EVENT, "@KV Error (%s) opening NVS handle!\n", esp_err_to_name(err));
  }
  return kv_handle;
}

void init_kv() {
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
  sync_ble_str(WIFI_SSID, IDX_VALUE(WIFI_SSID));
  defaultstr(WIFI_PASS, "");
  sync_ble_str(WIFI_PASS, IDX_VALUE(WIFI_PASS));
  defaulti(TIME, 0);
  sync_ble_i(TIME, IDX_VALUE(TIME));
  defaultstr(OTA_SERVER_IP, CONFIG_OTA_SERVER_IP);
  sync_ble_str(OTA_SERVER_IP, IDX_VALUE(OTA_SERVER_IP));
  defaultstr(OTA_SERVER_HOSTNAME, CONFIG_OTA_SERVER_HOSTNAME);
  sync_ble_str(OTA_SERVER_HOSTNAME, IDX_VALUE(OTA_SERVER_HOSTNAME));
  defaultstr(OTA_SERVER_PORT, CONFIG_OTA_SERVER_PORT);
  sync_ble_str(OTA_SERVER_PORT, IDX_VALUE(OTA_SERVER_PORT));
  defaultstr(OTA_VERSION_FILENAME, CONFIG_OTA_VERSION_FILENAME);
  sync_ble_str(OTA_VERSION_FILENAME, IDX_VALUE(OTA_VERSION_FILENAME));
  defaultstr(OTA_FILENAME, CONFIG_OTA_FILENAME);
  sync_ble_str(OTA_FILENAME, IDX_VALUE(OTA_FILENAME));

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
  add_kvi_dump(key);
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
  
  if (!skip) {
    add_kvs_dump(key);
  }
  if (!hasstr(key)) {
    setstr(key, value);
  } else {
    char buf[MAX_KVALUE_SIZE] = {0};
    getstr(key, buf, sizeof(buf) - 1);
    ESP_LOGI(skip ? SGO_LOG_NOSEND : SGO_LOG_METRIC, "@KV %s=%s", key, buf);
  }
}
