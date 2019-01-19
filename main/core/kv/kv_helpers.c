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


int get_i2c_sda() {
  return geti(I2C_SDA);
}

void set_i2c_sda(int value) {
  seti(I2C_SDA, value);
}



int get_i2c_scl() {
  return geti(I2C_SCL);
}

void set_i2c_scl(int value) {
  seti(I2C_SCL, value);
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


int get_timer_type() {
  return geti(TIMER_TYPE);
}

void set_timer_type(int value) {
  seti(TIMER_TYPE, value);
}



int get_timer_output() {
  return geti(TIMER_OUTPUT);
}

void set_timer_output(int value) {
  seti(TIMER_OUTPUT, value);
}



int get_started_at() {
  return geti(STARTED_AT);
}

void set_started_at(int value) {
  seti(STARTED_AT, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_STARTED_AT, (uint8_t *)&value, sizeof(int));
}



int get_on_hour() {
  return geti(ON_HOUR);
}

void set_on_hour(int value) {
  seti(ON_HOUR, value);
}



int get_on_min() {
  return geti(ON_MIN);
}

void set_on_min(int value) {
  seti(ON_MIN, value);
}



int get_off_hour() {
  return geti(OFF_HOUR);
}

void set_off_hour(int value) {
  seti(OFF_HOUR, value);
}



int get_off_min() {
  return geti(OFF_MIN);
}

void set_off_min(int value) {
  seti(OFF_MIN, value);
}



int get_stretch() {
  return geti(STRETCH);
}

void set_stretch(int value) {
  seti(STRETCH, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_STRETCH, (uint8_t *)&value, sizeof(int));
}



int get_led_dim() {
  return geti(LED_DIM);
}

void set_led_dim(int value) {
  seti(LED_DIM, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_LED_DIM, (uint8_t *)&value, sizeof(int));
}



int get_blower() {
  return geti(BLOWER);
}

void set_blower(int value) {
  seti(BLOWER, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_BLOWER, (uint8_t *)&value, sizeof(int));
}



int get_blower_mode() {
  return geti(BLOWER_MODE);
}

void set_blower_mode(int value) {
  seti(BLOWER_MODE, value);
}



int get_blower_gpio() {
  return geti(BLOWER_GPIO);
}

void set_blower_gpio(int value) {
  seti(BLOWER_GPIO, value);
}



int get_sht1x_temp_c() {
  return geti(SHT1X_TEMP_C);
}

void set_sht1x_temp_c(int value) {
  seti(SHT1X_TEMP_C, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_SHT1X_TEMP_C, (uint8_t *)&value, sizeof(int));
}



int get_sht1x_temp_f() {
  return geti(SHT1X_TEMP_F);
}

void set_sht1x_temp_f(int value) {
  seti(SHT1X_TEMP_F, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_SHT1X_TEMP_F, (uint8_t *)&value, sizeof(int));
}



int get_sht1x_humi() {
  return geti(SHT1X_HUMI);
}

void set_sht1x_humi(int value) {
  seti(SHT1X_HUMI, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_SHT1X_HUMI, (uint8_t *)&value, sizeof(int));
}



static SemaphoreHandle_t _mutex_led_info;
static char _led_info[MAX_KVALUE_SIZE] = {0};

void get_led_info(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_led_info, 0);
  strncpy(dest, _led_info, len);
  xSemaphoreGive(_mutex_led_info);
}

void set_led_info(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_led_info, 0);
  strncpy(_led_info, value, strlen(value));
  xSemaphoreGive(_mutex_led_info);
  set_attr_value_and_notify(IDX_CHAR_VAL_LED_INFO, (uint8_t *)value, strlen(value));
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


void init_helpers() {
  _mutex_wifi_status = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_info = xSemaphoreCreateMutexStatic(&mutex_buffer);
}

/*
 * [/GENERATED]
 */
