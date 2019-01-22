/*
 * Copyright (C) 2019  SuperGreenLab <towelie@supergreenlab.com>
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

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "kv.h"
#include "kv_ble.h"
#include "../ble/ble.h"

/*
 * [GENERATED]
 */

StaticSemaphore_t mutex_buffer;


static SemaphoreHandle_t _mutex_wifi_status;
static int _wifi_status = 0;

int get_wifi_status() {
  xSemaphoreTake(_mutex_wifi_status, 0);
  int v = _wifi_status;
  xSemaphoreGive(_mutex_wifi_status);
  return v;
}

void set_wifi_status(int value) {
  xSemaphoreTake(_mutex_wifi_status, 0);
  _wifi_status = value;
  xSemaphoreGive(_mutex_wifi_status);
  set_attr_value_and_notify(IDX_CHAR_VAL_WIFI_STATUS, (uint8_t *)&value, sizeof(int));
}




void get_wifi_ssid(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(WIFI_SSID, dest, len);
}

void set_wifi_ssid(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(WIFI_SSID, value);
  set_attr_value(IDX_CHAR_VAL_WIFI_SSID, (uint8_t *)value, strlen(value));
}



void get_wifi_password(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(WIFI_PASSWORD, dest, len);
}

void set_wifi_password(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(WIFI_PASSWORD, value);
}


int get_time() {
  return geti(TIME);
}

void set_time(int value) {
  seti(TIME, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_TIME, (uint8_t *)&value, sizeof(int));
}



int get_n_restarts() {
  return geti(N_RESTARTS);
}

void set_n_restarts(int value) {
  seti(N_RESTARTS, value);
}



int get_ota_timestamp() {
  return geti(OTA_TIMESTAMP);
}

void set_ota_timestamp(int value) {
  seti(OTA_TIMESTAMP, value);
}




void get_ota_server_ip(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_IP, dest, len);
}

void set_ota_server_ip(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(OTA_SERVER_IP, value);
}



void get_ota_server_hostname(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_HOSTNAME, dest, len);
}

void set_ota_server_hostname(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(OTA_SERVER_HOSTNAME, value);
}



void get_ota_server_port(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_PORT, dest, len);
}

void set_ota_server_port(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(OTA_SERVER_PORT, value);
}



void get_ota_version_filename(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_VERSION_FILENAME, dest, len);
}

void set_ota_version_filename(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(OTA_VERSION_FILENAME, value);
}



void get_ota_filename(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_FILENAME, dest, len);
}

void set_ota_filename(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(OTA_FILENAME, value);
}



void get_broker_url(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(BROKER_URL, dest, len);
}

void set_broker_url(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(BROKER_URL, value);
}


int get_i2c_0_sda() {
  return geti(I2C_0_SDA);
}

void set_i2c_0_sda(int value) {
  seti(I2C_0_SDA, value);
}



int get_i2c_0_scl() {
  return geti(I2C_0_SCL);
}

void set_i2c_0_scl(int value) {
  seti(I2C_0_SCL, value);
}



int get_i2c_0_enabled() {
  return geti(I2C_0_ENABLED);
}

void set_i2c_0_enabled(int value) {
  seti(I2C_0_ENABLED, value);
}



int get_i2c_1_sda() {
  return geti(I2C_1_SDA);
}

void set_i2c_1_sda(int value) {
  seti(I2C_1_SDA, value);
}



int get_i2c_1_scl() {
  return geti(I2C_1_SCL);
}

void set_i2c_1_scl(int value) {
  seti(I2C_1_SCL, value);
}



int get_i2c_1_enabled() {
  return geti(I2C_1_ENABLED);
}

void set_i2c_1_enabled(int value) {
  seti(I2C_1_ENABLED, value);
}



int get_state() {
  return geti(STATE);
}

void set_state(int value) {
  seti(STATE, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_STATE, (uint8_t *)&value, sizeof(int));
}




void get_device_name(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(DEVICE_NAME, dest, len);
}

void set_device_name(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  setstr(DEVICE_NAME, value);
  set_attr_value(IDX_CHAR_VAL_DEVICE_NAME, (uint8_t *)value, strlen(value));
}


int get_box_0_enabled() {
  return geti(BOX_0_ENABLED);
}

void set_box_0_enabled(int value) {
  seti(BOX_0_ENABLED, value);
}



int get_box_0_timer_type() {
  return geti(BOX_0_TIMER_TYPE);
}

void set_box_0_timer_type(int value) {
  seti(BOX_0_TIMER_TYPE, value);
}



int get_box_0_timer_output() {
  return geti(BOX_0_TIMER_OUTPUT);
}

void set_box_0_timer_output(int value) {
  seti(BOX_0_TIMER_OUTPUT, value);
}



int get_box_0_started_at() {
  return geti(BOX_0_STARTED_AT);
}

void set_box_0_started_at(int value) {
  seti(BOX_0_STARTED_AT, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_STARTED_AT, (uint8_t *)&value, sizeof(int));
}



int get_box_0_on_hour() {
  return geti(B_0_ON_HOUR);
}

void set_box_0_on_hour(int value) {
  seti(B_0_ON_HOUR, value);
}



int get_box_0_on_min() {
  return geti(BOX_0_ON_MIN);
}

void set_box_0_on_min(int value) {
  seti(BOX_0_ON_MIN, value);
}



int get_box_0_off_hour() {
  return geti(BOX_0_OFF_HOUR);
}

void set_box_0_off_hour(int value) {
  seti(BOX_0_OFF_HOUR, value);
}



int get_box_0_off_min() {
  return geti(BOX_0_OFF_MIN);
}

void set_box_0_off_min(int value) {
  seti(BOX_0_OFF_MIN, value);
}



int get_box_0_stretch() {
  return geti(BOX_0_STRETCH);
}

void set_box_0_stretch(int value) {
  seti(BOX_0_STRETCH, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_STRETCH, (uint8_t *)&value, sizeof(int));
}



int get_box_0_led_dim() {
  return geti(BOX_0_LED_DIM);
}

void set_box_0_led_dim(int value) {
  seti(BOX_0_LED_DIM, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_LED_DIM, (uint8_t *)&value, sizeof(int));
}



int get_box_0_blower() {
  return geti(BOX_0_BLOWER);
}

void set_box_0_blower(int value) {
  seti(BOX_0_BLOWER, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_BLOWER, (uint8_t *)&value, sizeof(int));
}



int get_box_0_blower_mode() {
  return geti(BOX_0_BLOWER_MODE);
}

void set_box_0_blower_mode(int value) {
  seti(BOX_0_BLOWER_MODE, value);
}



int get_box_0_blower_gpio() {
  return geti(BOX_0_BLOWER_GPIO);
}

void set_box_0_blower_gpio(int value) {
  seti(BOX_0_BLOWER_GPIO, value);
}



int get_box_0_sht1x_temp_c() {
  return geti(BOX_0_SHT1X_TEMP_C);
}

void set_box_0_sht1x_temp_c(int value) {
  seti(BOX_0_SHT1X_TEMP_C, value);
}



int get_box_0_sht1x_temp_f() {
  return geti(BOX_0_SHT1X_TEMP_F);
}

void set_box_0_sht1x_temp_f(int value) {
  seti(BOX_0_SHT1X_TEMP_F, value);
}



int get_box_0_sht1x_humi() {
  return geti(BOX_0_SHT1X_HUMI);
}

void set_box_0_sht1x_humi(int value) {
  seti(BOX_0_SHT1X_HUMI, value);
}



int get_box_0_arduino_co2() {
  return geti(BOX_0_ARDUINO_CO2);
}

void set_box_0_arduino_co2(int value) {
  seti(BOX_0_ARDUINO_CO2, value);
}



int get_box_0_dust_gpy2y10() {
  return geti(BOX_0_DUST_GPY2Y10);
}

void set_box_0_dust_gpy2y10(int value) {
  seti(BOX_0_DUST_GPY2Y10, value);
}



static SemaphoreHandle_t _mutex_box_0_led_info;
static char _box_0_led_info[MAX_KVALUE_SIZE] = {0};

void get_box_0_led_info(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_box_0_led_info, 0);
  strncpy(dest, _box_0_led_info, len);
  xSemaphoreGive(_mutex_box_0_led_info);
}

void set_box_0_led_info(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_box_0_led_info, 0);
  strncpy(_box_0_led_info, value, strlen(value));
  xSemaphoreGive(_mutex_box_0_led_info);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_LED_INFO, (uint8_t *)value, strlen(value));
}


int get_box_1_enabled() {
  return geti(BOX_1_ENABLED);
}

void set_box_1_enabled(int value) {
  seti(BOX_1_ENABLED, value);
}



int get_box_1_timer_type() {
  return geti(BOX_1_TIMER_TYPE);
}

void set_box_1_timer_type(int value) {
  seti(BOX_1_TIMER_TYPE, value);
}



int get_box_1_timer_output() {
  return geti(BOX_1_TIMER_OUTPUT);
}

void set_box_1_timer_output(int value) {
  seti(BOX_1_TIMER_OUTPUT, value);
}



int get_box_1_started_at() {
  return geti(BOX_1_STARTED_AT);
}

void set_box_1_started_at(int value) {
  seti(BOX_1_STARTED_AT, value);
}



int get_box_1_on_hour() {
  return geti(B_1_ON_HOUR);
}

void set_box_1_on_hour(int value) {
  seti(B_1_ON_HOUR, value);
}



int get_box_1_on_min() {
  return geti(BOX_1_ON_MIN);
}

void set_box_1_on_min(int value) {
  seti(BOX_1_ON_MIN, value);
}



int get_box_1_off_hour() {
  return geti(BOX_1_OFF_HOUR);
}

void set_box_1_off_hour(int value) {
  seti(BOX_1_OFF_HOUR, value);
}



int get_box_1_off_min() {
  return geti(BOX_1_OFF_MIN);
}

void set_box_1_off_min(int value) {
  seti(BOX_1_OFF_MIN, value);
}



int get_box_1_stretch() {
  return geti(BOX_1_STRETCH);
}

void set_box_1_stretch(int value) {
  seti(BOX_1_STRETCH, value);
}



int get_box_1_led_dim() {
  return geti(BOX_1_LED_DIM);
}

void set_box_1_led_dim(int value) {
  seti(BOX_1_LED_DIM, value);
}



int get_box_1_blower() {
  return geti(BOX_1_BLOWER);
}

void set_box_1_blower(int value) {
  seti(BOX_1_BLOWER, value);
}



int get_box_1_blower_mode() {
  return geti(BOX_1_BLOWER_MODE);
}

void set_box_1_blower_mode(int value) {
  seti(BOX_1_BLOWER_MODE, value);
}



int get_box_1_blower_gpio() {
  return geti(BOX_1_BLOWER_GPIO);
}

void set_box_1_blower_gpio(int value) {
  seti(BOX_1_BLOWER_GPIO, value);
}



int get_box_1_sht1x_temp_c() {
  return geti(BOX_1_SHT1X_TEMP_C);
}

void set_box_1_sht1x_temp_c(int value) {
  seti(BOX_1_SHT1X_TEMP_C, value);
}



int get_box_1_sht1x_temp_f() {
  return geti(BOX_1_SHT1X_TEMP_F);
}

void set_box_1_sht1x_temp_f(int value) {
  seti(BOX_1_SHT1X_TEMP_F, value);
}



int get_box_1_sht1x_humi() {
  return geti(BOX_1_SHT1X_HUMI);
}

void set_box_1_sht1x_humi(int value) {
  seti(BOX_1_SHT1X_HUMI, value);
}



int get_box_1_arduino_co2() {
  return geti(BOX_1_ARDUINO_CO2);
}

void set_box_1_arduino_co2(int value) {
  seti(BOX_1_ARDUINO_CO2, value);
}



int get_box_1_dust_gpy2y10() {
  return geti(BOX_1_DUST_GPY2Y10);
}

void set_box_1_dust_gpy2y10(int value) {
  seti(BOX_1_DUST_GPY2Y10, value);
}



static SemaphoreHandle_t _mutex_box_1_led_info;
static char _box_1_led_info[MAX_KVALUE_SIZE] = {0};

void get_box_1_led_info(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_box_1_led_info, 0);
  strncpy(dest, _box_1_led_info, len);
  xSemaphoreGive(_mutex_box_1_led_info);
}

void set_box_1_led_info(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_box_1_led_info, 0);
  strncpy(_box_1_led_info, value, strlen(value));
  xSemaphoreGive(_mutex_box_1_led_info);
}


int get_box_2_enabled() {
  return geti(BOX_2_ENABLED);
}

void set_box_2_enabled(int value) {
  seti(BOX_2_ENABLED, value);
}



int get_box_2_timer_type() {
  return geti(BOX_2_TIMER_TYPE);
}

void set_box_2_timer_type(int value) {
  seti(BOX_2_TIMER_TYPE, value);
}



int get_box_2_timer_output() {
  return geti(BOX_2_TIMER_OUTPUT);
}

void set_box_2_timer_output(int value) {
  seti(BOX_2_TIMER_OUTPUT, value);
}



int get_box_2_started_at() {
  return geti(BOX_2_STARTED_AT);
}

void set_box_2_started_at(int value) {
  seti(BOX_2_STARTED_AT, value);
}



int get_box_2_on_hour() {
  return geti(B_2_ON_HOUR);
}

void set_box_2_on_hour(int value) {
  seti(B_2_ON_HOUR, value);
}



int get_box_2_on_min() {
  return geti(BOX_2_ON_MIN);
}

void set_box_2_on_min(int value) {
  seti(BOX_2_ON_MIN, value);
}



int get_box_2_off_hour() {
  return geti(BOX_2_OFF_HOUR);
}

void set_box_2_off_hour(int value) {
  seti(BOX_2_OFF_HOUR, value);
}



int get_box_2_off_min() {
  return geti(BOX_2_OFF_MIN);
}

void set_box_2_off_min(int value) {
  seti(BOX_2_OFF_MIN, value);
}



int get_box_2_stretch() {
  return geti(BOX_2_STRETCH);
}

void set_box_2_stretch(int value) {
  seti(BOX_2_STRETCH, value);
}



int get_box_2_led_dim() {
  return geti(BOX_2_LED_DIM);
}

void set_box_2_led_dim(int value) {
  seti(BOX_2_LED_DIM, value);
}



int get_box_2_blower() {
  return geti(BOX_2_BLOWER);
}

void set_box_2_blower(int value) {
  seti(BOX_2_BLOWER, value);
}



int get_box_2_blower_mode() {
  return geti(BOX_2_BLOWER_MODE);
}

void set_box_2_blower_mode(int value) {
  seti(BOX_2_BLOWER_MODE, value);
}



int get_box_2_blower_gpio() {
  return geti(BOX_2_BLOWER_GPIO);
}

void set_box_2_blower_gpio(int value) {
  seti(BOX_2_BLOWER_GPIO, value);
}



int get_box_2_sht1x_temp_c() {
  return geti(BOX_2_SHT1X_TEMP_C);
}

void set_box_2_sht1x_temp_c(int value) {
  seti(BOX_2_SHT1X_TEMP_C, value);
}



int get_box_2_sht1x_temp_f() {
  return geti(BOX_2_SHT1X_TEMP_F);
}

void set_box_2_sht1x_temp_f(int value) {
  seti(BOX_2_SHT1X_TEMP_F, value);
}



int get_box_2_sht1x_humi() {
  return geti(BOX_2_SHT1X_HUMI);
}

void set_box_2_sht1x_humi(int value) {
  seti(BOX_2_SHT1X_HUMI, value);
}



int get_box_2_arduino_co2() {
  return geti(BOX_2_ARDUINO_CO2);
}

void set_box_2_arduino_co2(int value) {
  seti(BOX_2_ARDUINO_CO2, value);
}



int get_box_2_dust_gpy2y10() {
  return geti(BOX_2_DUST_GPY2Y10);
}

void set_box_2_dust_gpy2y10(int value) {
  seti(BOX_2_DUST_GPY2Y10, value);
}



static SemaphoreHandle_t _mutex_box_2_led_info;
static char _box_2_led_info[MAX_KVALUE_SIZE] = {0};

void get_box_2_led_info(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_box_2_led_info, 0);
  strncpy(dest, _box_2_led_info, len);
  xSemaphoreGive(_mutex_box_2_led_info);
}

void set_box_2_led_info(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_box_2_led_info, 0);
  strncpy(_box_2_led_info, value, strlen(value));
  xSemaphoreGive(_mutex_box_2_led_info);
}


int get_led_0_duty() {
  return geti(LED_0_DUTY);
}

void set_led_0_duty(int value) {
  seti(LED_0_DUTY, value);
}



int get_led_1_duty() {
  return geti(LED_1_DUTY);
}

void set_led_1_duty(int value) {
  seti(LED_1_DUTY, value);
}



int get_led_2_duty() {
  return geti(LED_2_DUTY);
}

void set_led_2_duty(int value) {
  seti(LED_2_DUTY, value);
}



int get_led_3_duty() {
  return geti(LED_3_DUTY);
}

void set_led_3_duty(int value) {
  seti(LED_3_DUTY, value);
}



int get_led_4_duty() {
  return geti(LED_4_DUTY);
}

void set_led_4_duty(int value) {
  seti(LED_4_DUTY, value);
}



int get_led_5_duty() {
  return geti(LED_5_DUTY);
}

void set_led_5_duty(int value) {
  seti(LED_5_DUTY, value);
}



int get_led_0_gpio() {
  return geti(LED_0_GPIO);
}

void set_led_0_gpio(int value) {
  seti(LED_0_GPIO, value);
}



int get_led_1_gpio() {
  return geti(LED_1_GPIO);
}

void set_led_1_gpio(int value) {
  seti(LED_1_GPIO, value);
}



int get_led_2_gpio() {
  return geti(LED_2_GPIO);
}

void set_led_2_gpio(int value) {
  seti(LED_2_GPIO, value);
}



int get_led_3_gpio() {
  return geti(LED_3_GPIO);
}

void set_led_3_gpio(int value) {
  seti(LED_3_GPIO, value);
}



int get_led_4_gpio() {
  return geti(LED_4_GPIO);
}

void set_led_4_gpio(int value) {
  seti(LED_4_GPIO, value);
}



int get_led_5_gpio() {
  return geti(LED_5_GPIO);
}

void set_led_5_gpio(int value) {
  seti(LED_5_GPIO, value);
}



int get_led_0_x() {
  return geti(LED_0_X);
}

void set_led_0_x(int value) {
  seti(LED_0_X, value);
}



int get_led_1_x() {
  return geti(LED_1_X);
}

void set_led_1_x(int value) {
  seti(LED_1_X, value);
}



int get_led_2_x() {
  return geti(LED_2_X);
}

void set_led_2_x(int value) {
  seti(LED_2_X, value);
}



int get_led_3_x() {
  return geti(LED_3_X);
}

void set_led_3_x(int value) {
  seti(LED_3_X, value);
}



int get_led_4_x() {
  return geti(LED_4_X);
}

void set_led_4_x(int value) {
  seti(LED_4_X, value);
}



int get_led_5_x() {
  return geti(LED_5_X);
}

void set_led_5_x(int value) {
  seti(LED_5_X, value);
}



int get_led_0_y() {
  return geti(LED_0_Y);
}

void set_led_0_y(int value) {
  seti(LED_0_Y, value);
}



int get_led_1_y() {
  return geti(LED_1_Y);
}

void set_led_1_y(int value) {
  seti(LED_1_Y, value);
}



int get_led_2_y() {
  return geti(LED_2_Y);
}

void set_led_2_y(int value) {
  seti(LED_2_Y, value);
}



int get_led_3_y() {
  return geti(LED_3_Y);
}

void set_led_3_y(int value) {
  seti(LED_3_Y, value);
}



int get_led_4_y() {
  return geti(LED_4_Y);
}

void set_led_4_y(int value) {
  seti(LED_4_Y, value);
}



int get_led_5_y() {
  return geti(LED_5_Y);
}

void set_led_5_y(int value) {
  seti(LED_5_Y, value);
}



int get_led_0_z() {
  return geti(LED_0_Z);
}

void set_led_0_z(int value) {
  seti(LED_0_Z, value);
}



int get_led_1_z() {
  return geti(LED_1_Z);
}

void set_led_1_z(int value) {
  seti(LED_1_Z, value);
}



int get_led_2_z() {
  return geti(LED_2_Z);
}

void set_led_2_z(int value) {
  seti(LED_2_Z, value);
}



int get_led_3_z() {
  return geti(LED_3_Z);
}

void set_led_3_z(int value) {
  seti(LED_3_Z, value);
}



int get_led_4_z() {
  return geti(LED_4_Z);
}

void set_led_4_z(int value) {
  seti(LED_4_Z, value);
}



int get_led_5_z() {
  return geti(LED_5_Z);
}

void set_led_5_z(int value) {
  seti(LED_5_Z, value);
}



int get_led_0_enable() {
  return geti(LED_0_ENABLE);
}

void set_led_0_enable(int value) {
  seti(LED_0_ENABLE, value);
}



int get_led_1_enable() {
  return geti(LED_1_ENABLE);
}

void set_led_1_enable(int value) {
  seti(LED_1_ENABLE, value);
}



int get_led_2_enable() {
  return geti(LED_2_ENABLE);
}

void set_led_2_enable(int value) {
  seti(LED_2_ENABLE, value);
}



int get_led_3_enable() {
  return geti(LED_3_ENABLE);
}

void set_led_3_enable(int value) {
  seti(LED_3_ENABLE, value);
}



int get_led_4_enable() {
  return geti(LED_4_ENABLE);
}

void set_led_4_enable(int value) {
  seti(LED_4_ENABLE, value);
}



int get_led_5_enable() {
  return geti(LED_5_ENABLE);
}

void set_led_5_enable(int value) {
  seti(LED_5_ENABLE, value);
}



int get_led_0_box() {
  return geti(LED_0_BOX);
}

void set_led_0_box(int value) {
  seti(LED_0_BOX, value);
}



int get_led_1_box() {
  return geti(LED_1_BOX);
}

void set_led_1_box(int value) {
  seti(LED_1_BOX, value);
}



int get_led_2_box() {
  return geti(LED_2_BOX);
}

void set_led_2_box(int value) {
  seti(LED_2_BOX, value);
}



int get_led_3_box() {
  return geti(LED_3_BOX);
}

void set_led_3_box(int value) {
  seti(LED_3_BOX, value);
}



int get_led_4_box() {
  return geti(LED_4_BOX);
}

void set_led_4_box(int value) {
  seti(LED_4_BOX, value);
}



int get_led_5_box() {
  return geti(LED_5_BOX);
}

void set_led_5_box(int value) {
  seti(LED_5_BOX, value);
}


void init_helpers() {
  _mutex_wifi_status = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_led_info = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_led_info = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_led_info = xSemaphoreCreateMutexStatic(&mutex_buffer);
}

/*
 * [/GENERATED]
 */
