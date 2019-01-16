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

void init_helpers();

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

  init_helpers();
  const char *default_wifi_ssid = "";
  defaultstr(WIFI_SSID, default_wifi_ssid);
  const char *default_wifi_password = "";
  defaultstr(WIFI_PASSWORD, default_wifi_password);
  int default_time = 0;
  defaulti(TIME, default_time);
  int default_n_restarts = 0;
  defaulti(N_RESTARTS, default_n_restarts);
  int default_ota_timestamp = OTA_BUILD_TIMESTAMP;
  defaulti(OTA_TIMESTAMP, default_ota_timestamp);
  const char *default_ota_server_ip = CONFIG_OTA_SERVER_IP;
  defaultstr(OTA_SERVER_IP, default_ota_server_ip);
  const char *default_ota_server_hostname = CONFIG_OTA_SERVER_HOSTNAME;
  defaultstr(OTA_SERVER_HOSTNAME, default_ota_server_hostname);
  const char *default_ota_server_port = CONFIG_OTA_SERVER_PORT;
  defaultstr(OTA_SERVER_PORT, default_ota_server_port);
  const char *default_ota_version_filename = CONFIG_OTA_VERSION_FILENAME;
  defaultstr(OTA_VERSION_FILENAME, default_ota_version_filename);
  const char *default_ota_filename = CONFIG_OTA_FILENAME;
  defaultstr(OTA_FILENAME, default_ota_filename);
  const char *default_broker_url = CONFIG_BROKER_URL;
  defaultstr(BROKER_URL, default_broker_url);
  int default_i2c_sda = DEFAULT_I2C_SDA;
  defaulti(I2C_SDA, default_i2c_sda);
  int default_i2c_scl = DEFAULT_I2C_SCL;
  defaulti(I2C_SCL, default_i2c_scl);
  int default_state = FIRST_RUN;
  defaulti(STATE, default_state);
  const char *default_device_name = "SuperGreenDriver";
  defaultstr(DEVICE_NAME, default_device_name);
  int default_timer_type = TIMER_MANUAL;
  defaulti(TIMER_TYPE, default_timer_type);
  int default_timer_output = 0;
  defaulti(TIMER_OUTPUT, default_timer_output);
  int default_started_at = 0;
  defaulti(STARTED_AT, default_started_at);
  int default_on_hour = 1;
  defaulti(ON_HOUR, default_on_hour);
  int default_on_min = 0;
  defaulti(ON_MIN, default_on_min);
  int default_off_hour = 19;
  defaulti(OFF_HOUR, default_off_hour);
  int default_off_min = 0;
  defaulti(OFF_MIN, default_off_min);
  int default_stretch = 0;
  defaulti(STRETCH, default_stretch);
  int default_led_dim = 0;
  defaulti(LED_DIM, default_led_dim);
  int default_blower = 50;
  defaulti(BLOWER, default_blower);
  int default_blower_gpio = DEFAULT_BLOWER_GPIO;
  defaulti(BLOWER_GPIO, default_blower_gpio);
  int default_sht1x_temp_c = -1000000;
  defaulti(SHT1X_TEMP_C, default_sht1x_temp_c);
  int default_sht1x_temp_f = -1000000;
  defaulti(SHT1X_TEMP_F, default_sht1x_temp_f);
  int default_sht1x_humi = -1000000;
  defaulti(SHT1X_HUMI, default_sht1x_humi);
  int default_led_0_duty = 0;
  defaulti(LED_0_DUTY, default_led_0_duty);
  int default_led_1_duty = 0;
  defaulti(LED_1_DUTY, default_led_1_duty);
  int default_led_2_duty = 0;
  defaulti(LED_2_DUTY, default_led_2_duty);
  int default_led_3_duty = 0;
  defaulti(LED_3_DUTY, default_led_3_duty);
  int default_led_4_duty = 0;
  defaulti(LED_4_DUTY, default_led_4_duty);
  int default_led_5_duty = 0;
  defaulti(LED_5_DUTY, default_led_5_duty);
  int default_led_0_gpio = DEFAULT_LED_0_GPIO;
  defaulti(LED_0_GPIO, default_led_0_gpio);
  int default_led_1_gpio = DEFAULT_LED_1_GPIO;
  defaulti(LED_1_GPIO, default_led_1_gpio);
  int default_led_2_gpio = DEFAULT_LED_2_GPIO;
  defaulti(LED_2_GPIO, default_led_2_gpio);
  int default_led_3_gpio = DEFAULT_LED_3_GPIO;
  defaulti(LED_3_GPIO, default_led_3_gpio);
  int default_led_4_gpio = DEFAULT_LED_4_GPIO;
  defaulti(LED_4_GPIO, default_led_4_gpio);
  int default_led_5_gpio = DEFAULT_LED_5_GPIO;
  defaulti(LED_5_GPIO, default_led_5_gpio);
  int default_led_0_x = 0;
  defaulti(LED_0_X, default_led_0_x);
  int default_led_1_x = 0;
  defaulti(LED_1_X, default_led_1_x);
  int default_led_2_x = 0;
  defaulti(LED_2_X, default_led_2_x);
  int default_led_3_x = 0;
  defaulti(LED_3_X, default_led_3_x);
  int default_led_4_x = 0;
  defaulti(LED_4_X, default_led_4_x);
  int default_led_5_x = 0;
  defaulti(LED_5_X, default_led_5_x);
  int default_led_0_y = 0;
  defaulti(LED_0_Y, default_led_0_y);
  int default_led_1_y = 0;
  defaulti(LED_1_Y, default_led_1_y);
  int default_led_2_y = 0;
  defaulti(LED_2_Y, default_led_2_y);
  int default_led_3_y = 0;
  defaulti(LED_3_Y, default_led_3_y);
  int default_led_4_y = 0;
  defaulti(LED_4_Y, default_led_4_y);
  int default_led_5_y = 0;
  defaulti(LED_5_Y, default_led_5_y);
  int default_led_0_z = 0;
  defaulti(LED_0_Z, default_led_0_z);
  int default_led_1_z = 0;
  defaulti(LED_1_Z, default_led_1_z);
  int default_led_2_z = 0;
  defaulti(LED_2_Z, default_led_2_z);
  int default_led_3_z = 0;
  defaulti(LED_3_Z, default_led_3_z);
  int default_led_4_z = 0;
  defaulti(LED_4_Z, default_led_4_z);
  int default_led_5_z = 0;
  defaulti(LED_5_Z, default_led_5_z);

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

  // Initialize non-nvs keys
  int default_wifi_status = DISCONNECTED;
  set_wifi_status(default_wifi_status);
  const char *default_led_info = "";
  set_led_info(default_led_info);


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
