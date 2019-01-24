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


static SemaphoreHandle_t _mutex_wifi_status; // TODO check RAM weight of creating so many semaphores :/
static bool _wifi_status_changed = true;

void reset_wifi_status_changed() {
  xSemaphoreTake(_mutex_wifi_status, 0);
  _wifi_status_changed = false;
  xSemaphoreGive(_mutex_wifi_status);
}

bool is_wifi_status_changed() {
  xSemaphoreTake(_mutex_wifi_status, 0);
  bool v = _wifi_status_changed;
  xSemaphoreGive(_mutex_wifi_status);
  return v;
}


static int _wifi_status = 0;

int get_wifi_status() {
  xSemaphoreTake(_mutex_wifi_status, 0);
  int v = _wifi_status;
  xSemaphoreGive(_mutex_wifi_status);
  return v;
}

void set_wifi_status(int value) {
  xSemaphoreTake(_mutex_wifi_status, 0);
  if (_wifi_status == value) return;
  _wifi_status = value;
  _wifi_status_changed = true;
  xSemaphoreGive(_mutex_wifi_status);
  set_attr_value_and_notify(IDX_CHAR_VAL_WIFI_STATUS, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_wifi_ssid; // TODO check RAM weight of creating so many semaphores :/
static bool _wifi_ssid_changed = true;

void reset_wifi_ssid_changed() {
  xSemaphoreTake(_mutex_wifi_ssid, 0);
  _wifi_ssid_changed = false;
  xSemaphoreGive(_mutex_wifi_ssid);
}

bool is_wifi_ssid_changed() {
  xSemaphoreTake(_mutex_wifi_ssid, 0);
  bool v = _wifi_ssid_changed;
  xSemaphoreGive(_mutex_wifi_ssid);
  return v;
}




void get_wifi_ssid(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(WIFI_SSID, dest, len);
  xSemaphoreTake(_mutex_wifi_ssid, 0);
  _wifi_ssid_changed = true;
  xSemaphoreGive(_mutex_wifi_ssid);
}

void set_wifi_ssid(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(WIFI_SSID, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(WIFI_SSID, value);
  xSemaphoreTake(_mutex_wifi_ssid, 0);
  _wifi_ssid_changed = true;
  xSemaphoreGive(_mutex_wifi_ssid);
  set_attr_value(IDX_CHAR_VAL_WIFI_SSID, (uint8_t *)value, strlen(value));
}

static SemaphoreHandle_t _mutex_wifi_password; // TODO check RAM weight of creating so many semaphores :/
static bool _wifi_password_changed = true;

void reset_wifi_password_changed() {
  xSemaphoreTake(_mutex_wifi_password, 0);
  _wifi_password_changed = false;
  xSemaphoreGive(_mutex_wifi_password);
}

bool is_wifi_password_changed() {
  xSemaphoreTake(_mutex_wifi_password, 0);
  bool v = _wifi_password_changed;
  xSemaphoreGive(_mutex_wifi_password);
  return v;
}




void get_wifi_password(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(WIFI_PASSWORD, dest, len);
  xSemaphoreTake(_mutex_wifi_password, 0);
  _wifi_password_changed = true;
  xSemaphoreGive(_mutex_wifi_password);
}

void set_wifi_password(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(WIFI_PASSWORD, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(WIFI_PASSWORD, value);
  xSemaphoreTake(_mutex_wifi_password, 0);
  _wifi_password_changed = true;
  xSemaphoreGive(_mutex_wifi_password);
}

static SemaphoreHandle_t _mutex_time; // TODO check RAM weight of creating so many semaphores :/
static bool _time_changed = true;

void reset_time_changed() {
  xSemaphoreTake(_mutex_time, 0);
  _time_changed = false;
  xSemaphoreGive(_mutex_time);
}

bool is_time_changed() {
  xSemaphoreTake(_mutex_time, 0);
  bool v = _time_changed;
  xSemaphoreGive(_mutex_time);
  return v;
}



int get_time() {
  return geti(TIME);
}

void set_time(int value) {
  if (geti(TIME) == value) return;
  seti(TIME, value);
  xSemaphoreTake(_mutex_time, 0);
  _time_changed = true;
  xSemaphoreGive(_mutex_time);
  set_attr_value_and_notify(IDX_CHAR_VAL_TIME, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_n_restarts; // TODO check RAM weight of creating so many semaphores :/
static bool _n_restarts_changed = true;

void reset_n_restarts_changed() {
  xSemaphoreTake(_mutex_n_restarts, 0);
  _n_restarts_changed = false;
  xSemaphoreGive(_mutex_n_restarts);
}

bool is_n_restarts_changed() {
  xSemaphoreTake(_mutex_n_restarts, 0);
  bool v = _n_restarts_changed;
  xSemaphoreGive(_mutex_n_restarts);
  return v;
}



int get_n_restarts() {
  return geti(N_RESTARTS);
}

void set_n_restarts(int value) {
  if (geti(N_RESTARTS) == value) return;
  seti(N_RESTARTS, value);
  xSemaphoreTake(_mutex_n_restarts, 0);
  _n_restarts_changed = true;
  xSemaphoreGive(_mutex_n_restarts);
}


static SemaphoreHandle_t _mutex_ota_timestamp; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_timestamp_changed = true;

void reset_ota_timestamp_changed() {
  xSemaphoreTake(_mutex_ota_timestamp, 0);
  _ota_timestamp_changed = false;
  xSemaphoreGive(_mutex_ota_timestamp);
}

bool is_ota_timestamp_changed() {
  xSemaphoreTake(_mutex_ota_timestamp, 0);
  bool v = _ota_timestamp_changed;
  xSemaphoreGive(_mutex_ota_timestamp);
  return v;
}



int get_ota_timestamp() {
  return geti(OTA_TIMESTAMP);
}

void set_ota_timestamp(int value) {
  if (geti(OTA_TIMESTAMP) == value) return;
  seti(OTA_TIMESTAMP, value);
  xSemaphoreTake(_mutex_ota_timestamp, 0);
  _ota_timestamp_changed = true;
  xSemaphoreGive(_mutex_ota_timestamp);
}


static SemaphoreHandle_t _mutex_ota_server_ip; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_server_ip_changed = true;

void reset_ota_server_ip_changed() {
  xSemaphoreTake(_mutex_ota_server_ip, 0);
  _ota_server_ip_changed = false;
  xSemaphoreGive(_mutex_ota_server_ip);
}

bool is_ota_server_ip_changed() {
  xSemaphoreTake(_mutex_ota_server_ip, 0);
  bool v = _ota_server_ip_changed;
  xSemaphoreGive(_mutex_ota_server_ip);
  return v;
}




void get_ota_server_ip(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_IP, dest, len);
  xSemaphoreTake(_mutex_ota_server_ip, 0);
  _ota_server_ip_changed = true;
  xSemaphoreGive(_mutex_ota_server_ip);
}

void set_ota_server_ip(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(OTA_SERVER_IP, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(OTA_SERVER_IP, value);
  xSemaphoreTake(_mutex_ota_server_ip, 0);
  _ota_server_ip_changed = true;
  xSemaphoreGive(_mutex_ota_server_ip);
}

static SemaphoreHandle_t _mutex_ota_server_hostname; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_server_hostname_changed = true;

void reset_ota_server_hostname_changed() {
  xSemaphoreTake(_mutex_ota_server_hostname, 0);
  _ota_server_hostname_changed = false;
  xSemaphoreGive(_mutex_ota_server_hostname);
}

bool is_ota_server_hostname_changed() {
  xSemaphoreTake(_mutex_ota_server_hostname, 0);
  bool v = _ota_server_hostname_changed;
  xSemaphoreGive(_mutex_ota_server_hostname);
  return v;
}




void get_ota_server_hostname(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_HOSTNAME, dest, len);
  xSemaphoreTake(_mutex_ota_server_hostname, 0);
  _ota_server_hostname_changed = true;
  xSemaphoreGive(_mutex_ota_server_hostname);
}

void set_ota_server_hostname(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(OTA_SERVER_HOSTNAME, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(OTA_SERVER_HOSTNAME, value);
  xSemaphoreTake(_mutex_ota_server_hostname, 0);
  _ota_server_hostname_changed = true;
  xSemaphoreGive(_mutex_ota_server_hostname);
}

static SemaphoreHandle_t _mutex_ota_server_port; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_server_port_changed = true;

void reset_ota_server_port_changed() {
  xSemaphoreTake(_mutex_ota_server_port, 0);
  _ota_server_port_changed = false;
  xSemaphoreGive(_mutex_ota_server_port);
}

bool is_ota_server_port_changed() {
  xSemaphoreTake(_mutex_ota_server_port, 0);
  bool v = _ota_server_port_changed;
  xSemaphoreGive(_mutex_ota_server_port);
  return v;
}




void get_ota_server_port(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_PORT, dest, len);
  xSemaphoreTake(_mutex_ota_server_port, 0);
  _ota_server_port_changed = true;
  xSemaphoreGive(_mutex_ota_server_port);
}

void set_ota_server_port(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(OTA_SERVER_PORT, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(OTA_SERVER_PORT, value);
  xSemaphoreTake(_mutex_ota_server_port, 0);
  _ota_server_port_changed = true;
  xSemaphoreGive(_mutex_ota_server_port);
}

static SemaphoreHandle_t _mutex_ota_version_filename; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_version_filename_changed = true;

void reset_ota_version_filename_changed() {
  xSemaphoreTake(_mutex_ota_version_filename, 0);
  _ota_version_filename_changed = false;
  xSemaphoreGive(_mutex_ota_version_filename);
}

bool is_ota_version_filename_changed() {
  xSemaphoreTake(_mutex_ota_version_filename, 0);
  bool v = _ota_version_filename_changed;
  xSemaphoreGive(_mutex_ota_version_filename);
  return v;
}




void get_ota_version_filename(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_VERSION_FILENAME, dest, len);
  xSemaphoreTake(_mutex_ota_version_filename, 0);
  _ota_version_filename_changed = true;
  xSemaphoreGive(_mutex_ota_version_filename);
}

void set_ota_version_filename(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(OTA_VERSION_FILENAME, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(OTA_VERSION_FILENAME, value);
  xSemaphoreTake(_mutex_ota_version_filename, 0);
  _ota_version_filename_changed = true;
  xSemaphoreGive(_mutex_ota_version_filename);
}

static SemaphoreHandle_t _mutex_ota_filename; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_filename_changed = true;

void reset_ota_filename_changed() {
  xSemaphoreTake(_mutex_ota_filename, 0);
  _ota_filename_changed = false;
  xSemaphoreGive(_mutex_ota_filename);
}

bool is_ota_filename_changed() {
  xSemaphoreTake(_mutex_ota_filename, 0);
  bool v = _ota_filename_changed;
  xSemaphoreGive(_mutex_ota_filename);
  return v;
}




void get_ota_filename(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_FILENAME, dest, len);
  xSemaphoreTake(_mutex_ota_filename, 0);
  _ota_filename_changed = true;
  xSemaphoreGive(_mutex_ota_filename);
}

void set_ota_filename(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(OTA_FILENAME, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(OTA_FILENAME, value);
  xSemaphoreTake(_mutex_ota_filename, 0);
  _ota_filename_changed = true;
  xSemaphoreGive(_mutex_ota_filename);
}

static SemaphoreHandle_t _mutex_broker_url; // TODO check RAM weight of creating so many semaphores :/
static bool _broker_url_changed = true;

void reset_broker_url_changed() {
  xSemaphoreTake(_mutex_broker_url, 0);
  _broker_url_changed = false;
  xSemaphoreGive(_mutex_broker_url);
}

bool is_broker_url_changed() {
  xSemaphoreTake(_mutex_broker_url, 0);
  bool v = _broker_url_changed;
  xSemaphoreGive(_mutex_broker_url);
  return v;
}




void get_broker_url(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(BROKER_URL, dest, len);
  xSemaphoreTake(_mutex_broker_url, 0);
  _broker_url_changed = true;
  xSemaphoreGive(_mutex_broker_url);
}

void set_broker_url(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(BROKER_URL, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(BROKER_URL, value);
  xSemaphoreTake(_mutex_broker_url, 0);
  _broker_url_changed = true;
  xSemaphoreGive(_mutex_broker_url);
}

static SemaphoreHandle_t _mutex_i2c_0_sda; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_0_sda_changed = true;

void reset_i2c_0_sda_changed() {
  xSemaphoreTake(_mutex_i2c_0_sda, 0);
  _i2c_0_sda_changed = false;
  xSemaphoreGive(_mutex_i2c_0_sda);
}

bool is_i2c_0_sda_changed() {
  xSemaphoreTake(_mutex_i2c_0_sda, 0);
  bool v = _i2c_0_sda_changed;
  xSemaphoreGive(_mutex_i2c_0_sda);
  return v;
}



int get_i2c_0_sda() {
  return geti(I2C_0_SDA);
}

void set_i2c_0_sda(int value) {
  if (geti(I2C_0_SDA) == value) return;
  seti(I2C_0_SDA, value);
  xSemaphoreTake(_mutex_i2c_0_sda, 0);
  _i2c_0_sda_changed = true;
  xSemaphoreGive(_mutex_i2c_0_sda);
}


static SemaphoreHandle_t _mutex_i2c_0_scl; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_0_scl_changed = true;

void reset_i2c_0_scl_changed() {
  xSemaphoreTake(_mutex_i2c_0_scl, 0);
  _i2c_0_scl_changed = false;
  xSemaphoreGive(_mutex_i2c_0_scl);
}

bool is_i2c_0_scl_changed() {
  xSemaphoreTake(_mutex_i2c_0_scl, 0);
  bool v = _i2c_0_scl_changed;
  xSemaphoreGive(_mutex_i2c_0_scl);
  return v;
}



int get_i2c_0_scl() {
  return geti(I2C_0_SCL);
}

void set_i2c_0_scl(int value) {
  if (geti(I2C_0_SCL) == value) return;
  seti(I2C_0_SCL, value);
  xSemaphoreTake(_mutex_i2c_0_scl, 0);
  _i2c_0_scl_changed = true;
  xSemaphoreGive(_mutex_i2c_0_scl);
}


static SemaphoreHandle_t _mutex_i2c_0_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_0_enabled_changed = true;

void reset_i2c_0_enabled_changed() {
  xSemaphoreTake(_mutex_i2c_0_enabled, 0);
  _i2c_0_enabled_changed = false;
  xSemaphoreGive(_mutex_i2c_0_enabled);
}

bool is_i2c_0_enabled_changed() {
  xSemaphoreTake(_mutex_i2c_0_enabled, 0);
  bool v = _i2c_0_enabled_changed;
  xSemaphoreGive(_mutex_i2c_0_enabled);
  return v;
}



int get_i2c_0_enabled() {
  return geti(I2C_0_ENABLED);
}

void set_i2c_0_enabled(int value) {
  if (geti(I2C_0_ENABLED) == value) return;
  seti(I2C_0_ENABLED, value);
  xSemaphoreTake(_mutex_i2c_0_enabled, 0);
  _i2c_0_enabled_changed = true;
  xSemaphoreGive(_mutex_i2c_0_enabled);
}


static SemaphoreHandle_t _mutex_i2c_1_sda; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_1_sda_changed = true;

void reset_i2c_1_sda_changed() {
  xSemaphoreTake(_mutex_i2c_1_sda, 0);
  _i2c_1_sda_changed = false;
  xSemaphoreGive(_mutex_i2c_1_sda);
}

bool is_i2c_1_sda_changed() {
  xSemaphoreTake(_mutex_i2c_1_sda, 0);
  bool v = _i2c_1_sda_changed;
  xSemaphoreGive(_mutex_i2c_1_sda);
  return v;
}



int get_i2c_1_sda() {
  return geti(I2C_1_SDA);
}

void set_i2c_1_sda(int value) {
  if (geti(I2C_1_SDA) == value) return;
  seti(I2C_1_SDA, value);
  xSemaphoreTake(_mutex_i2c_1_sda, 0);
  _i2c_1_sda_changed = true;
  xSemaphoreGive(_mutex_i2c_1_sda);
}


static SemaphoreHandle_t _mutex_i2c_1_scl; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_1_scl_changed = true;

void reset_i2c_1_scl_changed() {
  xSemaphoreTake(_mutex_i2c_1_scl, 0);
  _i2c_1_scl_changed = false;
  xSemaphoreGive(_mutex_i2c_1_scl);
}

bool is_i2c_1_scl_changed() {
  xSemaphoreTake(_mutex_i2c_1_scl, 0);
  bool v = _i2c_1_scl_changed;
  xSemaphoreGive(_mutex_i2c_1_scl);
  return v;
}



int get_i2c_1_scl() {
  return geti(I2C_1_SCL);
}

void set_i2c_1_scl(int value) {
  if (geti(I2C_1_SCL) == value) return;
  seti(I2C_1_SCL, value);
  xSemaphoreTake(_mutex_i2c_1_scl, 0);
  _i2c_1_scl_changed = true;
  xSemaphoreGive(_mutex_i2c_1_scl);
}


static SemaphoreHandle_t _mutex_i2c_1_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_1_enabled_changed = true;

void reset_i2c_1_enabled_changed() {
  xSemaphoreTake(_mutex_i2c_1_enabled, 0);
  _i2c_1_enabled_changed = false;
  xSemaphoreGive(_mutex_i2c_1_enabled);
}

bool is_i2c_1_enabled_changed() {
  xSemaphoreTake(_mutex_i2c_1_enabled, 0);
  bool v = _i2c_1_enabled_changed;
  xSemaphoreGive(_mutex_i2c_1_enabled);
  return v;
}



int get_i2c_1_enabled() {
  return geti(I2C_1_ENABLED);
}

void set_i2c_1_enabled(int value) {
  if (geti(I2C_1_ENABLED) == value) return;
  seti(I2C_1_ENABLED, value);
  xSemaphoreTake(_mutex_i2c_1_enabled, 0);
  _i2c_1_enabled_changed = true;
  xSemaphoreGive(_mutex_i2c_1_enabled);
}


static SemaphoreHandle_t _mutex_state; // TODO check RAM weight of creating so many semaphores :/
static bool _state_changed = true;

void reset_state_changed() {
  xSemaphoreTake(_mutex_state, 0);
  _state_changed = false;
  xSemaphoreGive(_mutex_state);
}

bool is_state_changed() {
  xSemaphoreTake(_mutex_state, 0);
  bool v = _state_changed;
  xSemaphoreGive(_mutex_state);
  return v;
}



int get_state() {
  return geti(STATE);
}

void set_state(int value) {
  if (geti(STATE) == value) return;
  seti(STATE, value);
  xSemaphoreTake(_mutex_state, 0);
  _state_changed = true;
  xSemaphoreGive(_mutex_state);
  set_attr_value_and_notify(IDX_CHAR_VAL_STATE, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_device_name; // TODO check RAM weight of creating so many semaphores :/
static bool _device_name_changed = true;

void reset_device_name_changed() {
  xSemaphoreTake(_mutex_device_name, 0);
  _device_name_changed = false;
  xSemaphoreGive(_mutex_device_name);
}

bool is_device_name_changed() {
  xSemaphoreTake(_mutex_device_name, 0);
  bool v = _device_name_changed;
  xSemaphoreGive(_mutex_device_name);
  return v;
}




void get_device_name(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(DEVICE_NAME, dest, len);
  xSemaphoreTake(_mutex_device_name, 0);
  _device_name_changed = true;
  xSemaphoreGive(_mutex_device_name);
}

void set_device_name(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(DEVICE_NAME, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(DEVICE_NAME, value);
  xSemaphoreTake(_mutex_device_name, 0);
  _device_name_changed = true;
  xSemaphoreGive(_mutex_device_name);
  set_attr_value(IDX_CHAR_VAL_DEVICE_NAME, (uint8_t *)value, strlen(value));
}

static SemaphoreHandle_t _mutex_box_0_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_enabled_changed = true;

void reset_box_0_enabled_changed() {
  xSemaphoreTake(_mutex_box_0_enabled, 0);
  _box_0_enabled_changed = false;
  xSemaphoreGive(_mutex_box_0_enabled);
}

bool is_box_0_enabled_changed() {
  xSemaphoreTake(_mutex_box_0_enabled, 0);
  bool v = _box_0_enabled_changed;
  xSemaphoreGive(_mutex_box_0_enabled);
  return v;
}



int get_box_0_enabled() {
  return geti(BOX_0_ENABLED);
}

void set_box_0_enabled(int value) {
  if (geti(BOX_0_ENABLED) == value) return;
  seti(BOX_0_ENABLED, value);
  xSemaphoreTake(_mutex_box_0_enabled, 0);
  _box_0_enabled_changed = true;
  xSemaphoreGive(_mutex_box_0_enabled);
}


static SemaphoreHandle_t _mutex_box_0_timer_type; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_timer_type_changed = true;

void reset_box_0_timer_type_changed() {
  xSemaphoreTake(_mutex_box_0_timer_type, 0);
  _box_0_timer_type_changed = false;
  xSemaphoreGive(_mutex_box_0_timer_type);
}

bool is_box_0_timer_type_changed() {
  xSemaphoreTake(_mutex_box_0_timer_type, 0);
  bool v = _box_0_timer_type_changed;
  xSemaphoreGive(_mutex_box_0_timer_type);
  return v;
}



int get_box_0_timer_type() {
  return geti(BOX_0_TIMER_TYPE);
}

void set_box_0_timer_type(int value) {
  if (geti(BOX_0_TIMER_TYPE) == value) return;
  seti(BOX_0_TIMER_TYPE, value);
  xSemaphoreTake(_mutex_box_0_timer_type, 0);
  _box_0_timer_type_changed = true;
  xSemaphoreGive(_mutex_box_0_timer_type);
}


static SemaphoreHandle_t _mutex_box_0_timer_output; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_timer_output_changed = true;

void reset_box_0_timer_output_changed() {
  xSemaphoreTake(_mutex_box_0_timer_output, 0);
  _box_0_timer_output_changed = false;
  xSemaphoreGive(_mutex_box_0_timer_output);
}

bool is_box_0_timer_output_changed() {
  xSemaphoreTake(_mutex_box_0_timer_output, 0);
  bool v = _box_0_timer_output_changed;
  xSemaphoreGive(_mutex_box_0_timer_output);
  return v;
}



int get_box_0_timer_output() {
  return geti(BOX_0_TIMER_OUTPUT);
}

void set_box_0_timer_output(int value) {
  if (geti(BOX_0_TIMER_OUTPUT) == value) return;
  seti(BOX_0_TIMER_OUTPUT, value);
  xSemaphoreTake(_mutex_box_0_timer_output, 0);
  _box_0_timer_output_changed = true;
  xSemaphoreGive(_mutex_box_0_timer_output);
}


static SemaphoreHandle_t _mutex_box_0_started_at; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_started_at_changed = true;

void reset_box_0_started_at_changed() {
  xSemaphoreTake(_mutex_box_0_started_at, 0);
  _box_0_started_at_changed = false;
  xSemaphoreGive(_mutex_box_0_started_at);
}

bool is_box_0_started_at_changed() {
  xSemaphoreTake(_mutex_box_0_started_at, 0);
  bool v = _box_0_started_at_changed;
  xSemaphoreGive(_mutex_box_0_started_at);
  return v;
}



int get_box_0_started_at() {
  return geti(BOX_0_STARTED_AT);
}

void set_box_0_started_at(int value) {
  if (geti(BOX_0_STARTED_AT) == value) return;
  seti(BOX_0_STARTED_AT, value);
  xSemaphoreTake(_mutex_box_0_started_at, 0);
  _box_0_started_at_changed = true;
  xSemaphoreGive(_mutex_box_0_started_at);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_STARTED_AT, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_box_0_on_hour; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_on_hour_changed = true;

void reset_box_0_on_hour_changed() {
  xSemaphoreTake(_mutex_box_0_on_hour, 0);
  _box_0_on_hour_changed = false;
  xSemaphoreGive(_mutex_box_0_on_hour);
}

bool is_box_0_on_hour_changed() {
  xSemaphoreTake(_mutex_box_0_on_hour, 0);
  bool v = _box_0_on_hour_changed;
  xSemaphoreGive(_mutex_box_0_on_hour);
  return v;
}



int get_box_0_on_hour() {
  return geti(BOX_0_ON_HOUR);
}

void set_box_0_on_hour(int value) {
  if (geti(BOX_0_ON_HOUR) == value) return;
  seti(BOX_0_ON_HOUR, value);
  xSemaphoreTake(_mutex_box_0_on_hour, 0);
  _box_0_on_hour_changed = true;
  xSemaphoreGive(_mutex_box_0_on_hour);
}


static SemaphoreHandle_t _mutex_box_0_on_min; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_on_min_changed = true;

void reset_box_0_on_min_changed() {
  xSemaphoreTake(_mutex_box_0_on_min, 0);
  _box_0_on_min_changed = false;
  xSemaphoreGive(_mutex_box_0_on_min);
}

bool is_box_0_on_min_changed() {
  xSemaphoreTake(_mutex_box_0_on_min, 0);
  bool v = _box_0_on_min_changed;
  xSemaphoreGive(_mutex_box_0_on_min);
  return v;
}



int get_box_0_on_min() {
  return geti(BOX_0_ON_MIN);
}

void set_box_0_on_min(int value) {
  if (geti(BOX_0_ON_MIN) == value) return;
  seti(BOX_0_ON_MIN, value);
  xSemaphoreTake(_mutex_box_0_on_min, 0);
  _box_0_on_min_changed = true;
  xSemaphoreGive(_mutex_box_0_on_min);
}


static SemaphoreHandle_t _mutex_box_0_off_hour; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_off_hour_changed = true;

void reset_box_0_off_hour_changed() {
  xSemaphoreTake(_mutex_box_0_off_hour, 0);
  _box_0_off_hour_changed = false;
  xSemaphoreGive(_mutex_box_0_off_hour);
}

bool is_box_0_off_hour_changed() {
  xSemaphoreTake(_mutex_box_0_off_hour, 0);
  bool v = _box_0_off_hour_changed;
  xSemaphoreGive(_mutex_box_0_off_hour);
  return v;
}



int get_box_0_off_hour() {
  return geti(BOX_0_OFF_HOUR);
}

void set_box_0_off_hour(int value) {
  if (geti(BOX_0_OFF_HOUR) == value) return;
  seti(BOX_0_OFF_HOUR, value);
  xSemaphoreTake(_mutex_box_0_off_hour, 0);
  _box_0_off_hour_changed = true;
  xSemaphoreGive(_mutex_box_0_off_hour);
}


static SemaphoreHandle_t _mutex_box_0_off_min; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_off_min_changed = true;

void reset_box_0_off_min_changed() {
  xSemaphoreTake(_mutex_box_0_off_min, 0);
  _box_0_off_min_changed = false;
  xSemaphoreGive(_mutex_box_0_off_min);
}

bool is_box_0_off_min_changed() {
  xSemaphoreTake(_mutex_box_0_off_min, 0);
  bool v = _box_0_off_min_changed;
  xSemaphoreGive(_mutex_box_0_off_min);
  return v;
}



int get_box_0_off_min() {
  return geti(BOX_0_OFF_MIN);
}

void set_box_0_off_min(int value) {
  if (geti(BOX_0_OFF_MIN) == value) return;
  seti(BOX_0_OFF_MIN, value);
  xSemaphoreTake(_mutex_box_0_off_min, 0);
  _box_0_off_min_changed = true;
  xSemaphoreGive(_mutex_box_0_off_min);
}


static SemaphoreHandle_t _mutex_box_0_stretch; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_stretch_changed = true;

void reset_box_0_stretch_changed() {
  xSemaphoreTake(_mutex_box_0_stretch, 0);
  _box_0_stretch_changed = false;
  xSemaphoreGive(_mutex_box_0_stretch);
}

bool is_box_0_stretch_changed() {
  xSemaphoreTake(_mutex_box_0_stretch, 0);
  bool v = _box_0_stretch_changed;
  xSemaphoreGive(_mutex_box_0_stretch);
  return v;
}



int get_box_0_stretch() {
  return geti(BOX_0_STRETCH);
}

void set_box_0_stretch(int value) {
  if (geti(BOX_0_STRETCH) == value) return;
  seti(BOX_0_STRETCH, value);
  xSemaphoreTake(_mutex_box_0_stretch, 0);
  _box_0_stretch_changed = true;
  xSemaphoreGive(_mutex_box_0_stretch);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_STRETCH, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_box_0_led_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_led_dim_changed = true;

void reset_box_0_led_dim_changed() {
  xSemaphoreTake(_mutex_box_0_led_dim, 0);
  _box_0_led_dim_changed = false;
  xSemaphoreGive(_mutex_box_0_led_dim);
}

bool is_box_0_led_dim_changed() {
  xSemaphoreTake(_mutex_box_0_led_dim, 0);
  bool v = _box_0_led_dim_changed;
  xSemaphoreGive(_mutex_box_0_led_dim);
  return v;
}



int get_box_0_led_dim() {
  return geti(BOX_0_LED_DIM);
}

void set_box_0_led_dim(int value) {
  if (geti(BOX_0_LED_DIM) == value) return;
  seti(BOX_0_LED_DIM, value);
  xSemaphoreTake(_mutex_box_0_led_dim, 0);
  _box_0_led_dim_changed = true;
  xSemaphoreGive(_mutex_box_0_led_dim);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_LED_DIM, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_box_0_blower; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_blower_changed = true;

void reset_box_0_blower_changed() {
  xSemaphoreTake(_mutex_box_0_blower, 0);
  _box_0_blower_changed = false;
  xSemaphoreGive(_mutex_box_0_blower);
}

bool is_box_0_blower_changed() {
  xSemaphoreTake(_mutex_box_0_blower, 0);
  bool v = _box_0_blower_changed;
  xSemaphoreGive(_mutex_box_0_blower);
  return v;
}



int get_box_0_blower() {
  return geti(BOX_0_BLOWER);
}

void set_box_0_blower(int value) {
  if (geti(BOX_0_BLOWER) == value) return;
  seti(BOX_0_BLOWER, value);
  xSemaphoreTake(_mutex_box_0_blower, 0);
  _box_0_blower_changed = true;
  xSemaphoreGive(_mutex_box_0_blower);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_BLOWER, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_box_0_blower_mode; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_blower_mode_changed = true;

void reset_box_0_blower_mode_changed() {
  xSemaphoreTake(_mutex_box_0_blower_mode, 0);
  _box_0_blower_mode_changed = false;
  xSemaphoreGive(_mutex_box_0_blower_mode);
}

bool is_box_0_blower_mode_changed() {
  xSemaphoreTake(_mutex_box_0_blower_mode, 0);
  bool v = _box_0_blower_mode_changed;
  xSemaphoreGive(_mutex_box_0_blower_mode);
  return v;
}



int get_box_0_blower_mode() {
  return geti(BOX_0_BLOWER_MODE);
}

void set_box_0_blower_mode(int value) {
  if (geti(BOX_0_BLOWER_MODE) == value) return;
  seti(BOX_0_BLOWER_MODE, value);
  xSemaphoreTake(_mutex_box_0_blower_mode, 0);
  _box_0_blower_mode_changed = true;
  xSemaphoreGive(_mutex_box_0_blower_mode);
}


static SemaphoreHandle_t _mutex_box_0_blower_gpio; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_blower_gpio_changed = true;

void reset_box_0_blower_gpio_changed() {
  xSemaphoreTake(_mutex_box_0_blower_gpio, 0);
  _box_0_blower_gpio_changed = false;
  xSemaphoreGive(_mutex_box_0_blower_gpio);
}

bool is_box_0_blower_gpio_changed() {
  xSemaphoreTake(_mutex_box_0_blower_gpio, 0);
  bool v = _box_0_blower_gpio_changed;
  xSemaphoreGive(_mutex_box_0_blower_gpio);
  return v;
}



int get_box_0_blower_gpio() {
  return geti(BOX_0_BLOWER_GPIO);
}

void set_box_0_blower_gpio(int value) {
  if (geti(BOX_0_BLOWER_GPIO) == value) return;
  seti(BOX_0_BLOWER_GPIO, value);
  xSemaphoreTake(_mutex_box_0_blower_gpio, 0);
  _box_0_blower_gpio_changed = true;
  xSemaphoreGive(_mutex_box_0_blower_gpio);
}


static SemaphoreHandle_t _mutex_box_0_blower_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_blower_enabled_changed = true;

void reset_box_0_blower_enabled_changed() {
  xSemaphoreTake(_mutex_box_0_blower_enabled, 0);
  _box_0_blower_enabled_changed = false;
  xSemaphoreGive(_mutex_box_0_blower_enabled);
}

bool is_box_0_blower_enabled_changed() {
  xSemaphoreTake(_mutex_box_0_blower_enabled, 0);
  bool v = _box_0_blower_enabled_changed;
  xSemaphoreGive(_mutex_box_0_blower_enabled);
  return v;
}



int get_box_0_blower_enabled() {
  return geti(BOX_0_BLOWER_ENABLED);
}

void set_box_0_blower_enabled(int value) {
  if (geti(BOX_0_BLOWER_ENABLED) == value) return;
  seti(BOX_0_BLOWER_ENABLED, value);
  xSemaphoreTake(_mutex_box_0_blower_enabled, 0);
  _box_0_blower_enabled_changed = true;
  xSemaphoreGive(_mutex_box_0_blower_enabled);
}


static SemaphoreHandle_t _mutex_box_0_sht1x_temp_c; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_sht1x_temp_c_changed = true;

void reset_box_0_sht1x_temp_c_changed() {
  xSemaphoreTake(_mutex_box_0_sht1x_temp_c, 0);
  _box_0_sht1x_temp_c_changed = false;
  xSemaphoreGive(_mutex_box_0_sht1x_temp_c);
}

bool is_box_0_sht1x_temp_c_changed() {
  xSemaphoreTake(_mutex_box_0_sht1x_temp_c, 0);
  bool v = _box_0_sht1x_temp_c_changed;
  xSemaphoreGive(_mutex_box_0_sht1x_temp_c);
  return v;
}



int get_box_0_sht1x_temp_c() {
  return geti(BOX_0_SHT1X_TEMP_C);
}

void set_box_0_sht1x_temp_c(int value) {
  if (geti(BOX_0_SHT1X_TEMP_C) == value) return;
  seti(BOX_0_SHT1X_TEMP_C, value);
  xSemaphoreTake(_mutex_box_0_sht1x_temp_c, 0);
  _box_0_sht1x_temp_c_changed = true;
  xSemaphoreGive(_mutex_box_0_sht1x_temp_c);
}


static SemaphoreHandle_t _mutex_box_0_sht1x_temp_f; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_sht1x_temp_f_changed = true;

void reset_box_0_sht1x_temp_f_changed() {
  xSemaphoreTake(_mutex_box_0_sht1x_temp_f, 0);
  _box_0_sht1x_temp_f_changed = false;
  xSemaphoreGive(_mutex_box_0_sht1x_temp_f);
}

bool is_box_0_sht1x_temp_f_changed() {
  xSemaphoreTake(_mutex_box_0_sht1x_temp_f, 0);
  bool v = _box_0_sht1x_temp_f_changed;
  xSemaphoreGive(_mutex_box_0_sht1x_temp_f);
  return v;
}



int get_box_0_sht1x_temp_f() {
  return geti(BOX_0_SHT1X_TEMP_F);
}

void set_box_0_sht1x_temp_f(int value) {
  if (geti(BOX_0_SHT1X_TEMP_F) == value) return;
  seti(BOX_0_SHT1X_TEMP_F, value);
  xSemaphoreTake(_mutex_box_0_sht1x_temp_f, 0);
  _box_0_sht1x_temp_f_changed = true;
  xSemaphoreGive(_mutex_box_0_sht1x_temp_f);
}


static SemaphoreHandle_t _mutex_box_0_sht1x_humi; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_sht1x_humi_changed = true;

void reset_box_0_sht1x_humi_changed() {
  xSemaphoreTake(_mutex_box_0_sht1x_humi, 0);
  _box_0_sht1x_humi_changed = false;
  xSemaphoreGive(_mutex_box_0_sht1x_humi);
}

bool is_box_0_sht1x_humi_changed() {
  xSemaphoreTake(_mutex_box_0_sht1x_humi, 0);
  bool v = _box_0_sht1x_humi_changed;
  xSemaphoreGive(_mutex_box_0_sht1x_humi);
  return v;
}



int get_box_0_sht1x_humi() {
  return geti(BOX_0_SHT1X_HUMI);
}

void set_box_0_sht1x_humi(int value) {
  if (geti(BOX_0_SHT1X_HUMI) == value) return;
  seti(BOX_0_SHT1X_HUMI, value);
  xSemaphoreTake(_mutex_box_0_sht1x_humi, 0);
  _box_0_sht1x_humi_changed = true;
  xSemaphoreGive(_mutex_box_0_sht1x_humi);
}


static SemaphoreHandle_t _mutex_box_0_arduino_co2; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_arduino_co2_changed = true;

void reset_box_0_arduino_co2_changed() {
  xSemaphoreTake(_mutex_box_0_arduino_co2, 0);
  _box_0_arduino_co2_changed = false;
  xSemaphoreGive(_mutex_box_0_arduino_co2);
}

bool is_box_0_arduino_co2_changed() {
  xSemaphoreTake(_mutex_box_0_arduino_co2, 0);
  bool v = _box_0_arduino_co2_changed;
  xSemaphoreGive(_mutex_box_0_arduino_co2);
  return v;
}



int get_box_0_arduino_co2() {
  return geti(BOX_0_ARDUINO_CO2);
}

void set_box_0_arduino_co2(int value) {
  if (geti(BOX_0_ARDUINO_CO2) == value) return;
  seti(BOX_0_ARDUINO_CO2, value);
  xSemaphoreTake(_mutex_box_0_arduino_co2, 0);
  _box_0_arduino_co2_changed = true;
  xSemaphoreGive(_mutex_box_0_arduino_co2);
}


static SemaphoreHandle_t _mutex_box_0_dust_gpy2y10; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_dust_gpy2y10_changed = true;

void reset_box_0_dust_gpy2y10_changed() {
  xSemaphoreTake(_mutex_box_0_dust_gpy2y10, 0);
  _box_0_dust_gpy2y10_changed = false;
  xSemaphoreGive(_mutex_box_0_dust_gpy2y10);
}

bool is_box_0_dust_gpy2y10_changed() {
  xSemaphoreTake(_mutex_box_0_dust_gpy2y10, 0);
  bool v = _box_0_dust_gpy2y10_changed;
  xSemaphoreGive(_mutex_box_0_dust_gpy2y10);
  return v;
}



int get_box_0_dust_gpy2y10() {
  return geti(BOX_0_DUST_GPY2Y10);
}

void set_box_0_dust_gpy2y10(int value) {
  if (geti(BOX_0_DUST_GPY2Y10) == value) return;
  seti(BOX_0_DUST_GPY2Y10, value);
  xSemaphoreTake(_mutex_box_0_dust_gpy2y10, 0);
  _box_0_dust_gpy2y10_changed = true;
  xSemaphoreGive(_mutex_box_0_dust_gpy2y10);
}


static SemaphoreHandle_t _mutex_box_0_led_info; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_led_info_changed = true;

void reset_box_0_led_info_changed() {
  xSemaphoreTake(_mutex_box_0_led_info, 0);
  _box_0_led_info_changed = false;
  xSemaphoreGive(_mutex_box_0_led_info);
}

bool is_box_0_led_info_changed() {
  xSemaphoreTake(_mutex_box_0_led_info, 0);
  bool v = _box_0_led_info_changed;
  xSemaphoreGive(_mutex_box_0_led_info);
  return v;
}



static char _box_0_led_info[MAX_KVALUE_SIZE] = {0};

void get_box_0_led_info(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_box_0_led_info, 0);
  _box_0_led_info_changed = true;
  strncpy(dest, _box_0_led_info, len);
  xSemaphoreGive(_mutex_box_0_led_info);
}

void set_box_0_led_info(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_box_0_led_info, 0);
  if (!strcmp(_box_0_led_info, value)) return;
  strncpy(_box_0_led_info, value, strlen(value));
  _box_0_led_info_changed = true;
  xSemaphoreGive(_mutex_box_0_led_info);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_LED_INFO, (uint8_t *)value, strlen(value));
}

static SemaphoreHandle_t _mutex_box_1_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_enabled_changed = true;

void reset_box_1_enabled_changed() {
  xSemaphoreTake(_mutex_box_1_enabled, 0);
  _box_1_enabled_changed = false;
  xSemaphoreGive(_mutex_box_1_enabled);
}

bool is_box_1_enabled_changed() {
  xSemaphoreTake(_mutex_box_1_enabled, 0);
  bool v = _box_1_enabled_changed;
  xSemaphoreGive(_mutex_box_1_enabled);
  return v;
}



int get_box_1_enabled() {
  return geti(BOX_1_ENABLED);
}

void set_box_1_enabled(int value) {
  if (geti(BOX_1_ENABLED) == value) return;
  seti(BOX_1_ENABLED, value);
  xSemaphoreTake(_mutex_box_1_enabled, 0);
  _box_1_enabled_changed = true;
  xSemaphoreGive(_mutex_box_1_enabled);
}


static SemaphoreHandle_t _mutex_box_1_timer_type; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_timer_type_changed = true;

void reset_box_1_timer_type_changed() {
  xSemaphoreTake(_mutex_box_1_timer_type, 0);
  _box_1_timer_type_changed = false;
  xSemaphoreGive(_mutex_box_1_timer_type);
}

bool is_box_1_timer_type_changed() {
  xSemaphoreTake(_mutex_box_1_timer_type, 0);
  bool v = _box_1_timer_type_changed;
  xSemaphoreGive(_mutex_box_1_timer_type);
  return v;
}



int get_box_1_timer_type() {
  return geti(BOX_1_TIMER_TYPE);
}

void set_box_1_timer_type(int value) {
  if (geti(BOX_1_TIMER_TYPE) == value) return;
  seti(BOX_1_TIMER_TYPE, value);
  xSemaphoreTake(_mutex_box_1_timer_type, 0);
  _box_1_timer_type_changed = true;
  xSemaphoreGive(_mutex_box_1_timer_type);
}


static SemaphoreHandle_t _mutex_box_1_timer_output; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_timer_output_changed = true;

void reset_box_1_timer_output_changed() {
  xSemaphoreTake(_mutex_box_1_timer_output, 0);
  _box_1_timer_output_changed = false;
  xSemaphoreGive(_mutex_box_1_timer_output);
}

bool is_box_1_timer_output_changed() {
  xSemaphoreTake(_mutex_box_1_timer_output, 0);
  bool v = _box_1_timer_output_changed;
  xSemaphoreGive(_mutex_box_1_timer_output);
  return v;
}



int get_box_1_timer_output() {
  return geti(BOX_1_TIMER_OUTPUT);
}

void set_box_1_timer_output(int value) {
  if (geti(BOX_1_TIMER_OUTPUT) == value) return;
  seti(BOX_1_TIMER_OUTPUT, value);
  xSemaphoreTake(_mutex_box_1_timer_output, 0);
  _box_1_timer_output_changed = true;
  xSemaphoreGive(_mutex_box_1_timer_output);
}


static SemaphoreHandle_t _mutex_box_1_started_at; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_started_at_changed = true;

void reset_box_1_started_at_changed() {
  xSemaphoreTake(_mutex_box_1_started_at, 0);
  _box_1_started_at_changed = false;
  xSemaphoreGive(_mutex_box_1_started_at);
}

bool is_box_1_started_at_changed() {
  xSemaphoreTake(_mutex_box_1_started_at, 0);
  bool v = _box_1_started_at_changed;
  xSemaphoreGive(_mutex_box_1_started_at);
  return v;
}



int get_box_1_started_at() {
  return geti(BOX_1_STARTED_AT);
}

void set_box_1_started_at(int value) {
  if (geti(BOX_1_STARTED_AT) == value) return;
  seti(BOX_1_STARTED_AT, value);
  xSemaphoreTake(_mutex_box_1_started_at, 0);
  _box_1_started_at_changed = true;
  xSemaphoreGive(_mutex_box_1_started_at);
}


static SemaphoreHandle_t _mutex_box_1_on_hour; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_on_hour_changed = true;

void reset_box_1_on_hour_changed() {
  xSemaphoreTake(_mutex_box_1_on_hour, 0);
  _box_1_on_hour_changed = false;
  xSemaphoreGive(_mutex_box_1_on_hour);
}

bool is_box_1_on_hour_changed() {
  xSemaphoreTake(_mutex_box_1_on_hour, 0);
  bool v = _box_1_on_hour_changed;
  xSemaphoreGive(_mutex_box_1_on_hour);
  return v;
}



int get_box_1_on_hour() {
  return geti(B_1_ON_HOUR);
}

void set_box_1_on_hour(int value) {
  if (geti(B_1_ON_HOUR) == value) return;
  seti(B_1_ON_HOUR, value);
  xSemaphoreTake(_mutex_box_1_on_hour, 0);
  _box_1_on_hour_changed = true;
  xSemaphoreGive(_mutex_box_1_on_hour);
}


static SemaphoreHandle_t _mutex_box_1_on_min; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_on_min_changed = true;

void reset_box_1_on_min_changed() {
  xSemaphoreTake(_mutex_box_1_on_min, 0);
  _box_1_on_min_changed = false;
  xSemaphoreGive(_mutex_box_1_on_min);
}

bool is_box_1_on_min_changed() {
  xSemaphoreTake(_mutex_box_1_on_min, 0);
  bool v = _box_1_on_min_changed;
  xSemaphoreGive(_mutex_box_1_on_min);
  return v;
}



int get_box_1_on_min() {
  return geti(BOX_1_ON_MIN);
}

void set_box_1_on_min(int value) {
  if (geti(BOX_1_ON_MIN) == value) return;
  seti(BOX_1_ON_MIN, value);
  xSemaphoreTake(_mutex_box_1_on_min, 0);
  _box_1_on_min_changed = true;
  xSemaphoreGive(_mutex_box_1_on_min);
}


static SemaphoreHandle_t _mutex_box_1_off_hour; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_off_hour_changed = true;

void reset_box_1_off_hour_changed() {
  xSemaphoreTake(_mutex_box_1_off_hour, 0);
  _box_1_off_hour_changed = false;
  xSemaphoreGive(_mutex_box_1_off_hour);
}

bool is_box_1_off_hour_changed() {
  xSemaphoreTake(_mutex_box_1_off_hour, 0);
  bool v = _box_1_off_hour_changed;
  xSemaphoreGive(_mutex_box_1_off_hour);
  return v;
}



int get_box_1_off_hour() {
  return geti(BOX_1_OFF_HOUR);
}

void set_box_1_off_hour(int value) {
  if (geti(BOX_1_OFF_HOUR) == value) return;
  seti(BOX_1_OFF_HOUR, value);
  xSemaphoreTake(_mutex_box_1_off_hour, 0);
  _box_1_off_hour_changed = true;
  xSemaphoreGive(_mutex_box_1_off_hour);
}


static SemaphoreHandle_t _mutex_box_1_off_min; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_off_min_changed = true;

void reset_box_1_off_min_changed() {
  xSemaphoreTake(_mutex_box_1_off_min, 0);
  _box_1_off_min_changed = false;
  xSemaphoreGive(_mutex_box_1_off_min);
}

bool is_box_1_off_min_changed() {
  xSemaphoreTake(_mutex_box_1_off_min, 0);
  bool v = _box_1_off_min_changed;
  xSemaphoreGive(_mutex_box_1_off_min);
  return v;
}



int get_box_1_off_min() {
  return geti(BOX_1_OFF_MIN);
}

void set_box_1_off_min(int value) {
  if (geti(BOX_1_OFF_MIN) == value) return;
  seti(BOX_1_OFF_MIN, value);
  xSemaphoreTake(_mutex_box_1_off_min, 0);
  _box_1_off_min_changed = true;
  xSemaphoreGive(_mutex_box_1_off_min);
}


static SemaphoreHandle_t _mutex_box_1_stretch; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_stretch_changed = true;

void reset_box_1_stretch_changed() {
  xSemaphoreTake(_mutex_box_1_stretch, 0);
  _box_1_stretch_changed = false;
  xSemaphoreGive(_mutex_box_1_stretch);
}

bool is_box_1_stretch_changed() {
  xSemaphoreTake(_mutex_box_1_stretch, 0);
  bool v = _box_1_stretch_changed;
  xSemaphoreGive(_mutex_box_1_stretch);
  return v;
}



int get_box_1_stretch() {
  return geti(BOX_1_STRETCH);
}

void set_box_1_stretch(int value) {
  if (geti(BOX_1_STRETCH) == value) return;
  seti(BOX_1_STRETCH, value);
  xSemaphoreTake(_mutex_box_1_stretch, 0);
  _box_1_stretch_changed = true;
  xSemaphoreGive(_mutex_box_1_stretch);
}


static SemaphoreHandle_t _mutex_box_1_led_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_led_dim_changed = true;

void reset_box_1_led_dim_changed() {
  xSemaphoreTake(_mutex_box_1_led_dim, 0);
  _box_1_led_dim_changed = false;
  xSemaphoreGive(_mutex_box_1_led_dim);
}

bool is_box_1_led_dim_changed() {
  xSemaphoreTake(_mutex_box_1_led_dim, 0);
  bool v = _box_1_led_dim_changed;
  xSemaphoreGive(_mutex_box_1_led_dim);
  return v;
}



int get_box_1_led_dim() {
  return geti(BOX_1_LED_DIM);
}

void set_box_1_led_dim(int value) {
  if (geti(BOX_1_LED_DIM) == value) return;
  seti(BOX_1_LED_DIM, value);
  xSemaphoreTake(_mutex_box_1_led_dim, 0);
  _box_1_led_dim_changed = true;
  xSemaphoreGive(_mutex_box_1_led_dim);
}


static SemaphoreHandle_t _mutex_box_1_blower; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_blower_changed = true;

void reset_box_1_blower_changed() {
  xSemaphoreTake(_mutex_box_1_blower, 0);
  _box_1_blower_changed = false;
  xSemaphoreGive(_mutex_box_1_blower);
}

bool is_box_1_blower_changed() {
  xSemaphoreTake(_mutex_box_1_blower, 0);
  bool v = _box_1_blower_changed;
  xSemaphoreGive(_mutex_box_1_blower);
  return v;
}



int get_box_1_blower() {
  return geti(BOX_1_BLOWER);
}

void set_box_1_blower(int value) {
  if (geti(BOX_1_BLOWER) == value) return;
  seti(BOX_1_BLOWER, value);
  xSemaphoreTake(_mutex_box_1_blower, 0);
  _box_1_blower_changed = true;
  xSemaphoreGive(_mutex_box_1_blower);
}


static SemaphoreHandle_t _mutex_box_1_blower_mode; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_blower_mode_changed = true;

void reset_box_1_blower_mode_changed() {
  xSemaphoreTake(_mutex_box_1_blower_mode, 0);
  _box_1_blower_mode_changed = false;
  xSemaphoreGive(_mutex_box_1_blower_mode);
}

bool is_box_1_blower_mode_changed() {
  xSemaphoreTake(_mutex_box_1_blower_mode, 0);
  bool v = _box_1_blower_mode_changed;
  xSemaphoreGive(_mutex_box_1_blower_mode);
  return v;
}



int get_box_1_blower_mode() {
  return geti(BOX_1_BLOWER_MODE);
}

void set_box_1_blower_mode(int value) {
  if (geti(BOX_1_BLOWER_MODE) == value) return;
  seti(BOX_1_BLOWER_MODE, value);
  xSemaphoreTake(_mutex_box_1_blower_mode, 0);
  _box_1_blower_mode_changed = true;
  xSemaphoreGive(_mutex_box_1_blower_mode);
}


static SemaphoreHandle_t _mutex_box_1_blower_gpio; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_blower_gpio_changed = true;

void reset_box_1_blower_gpio_changed() {
  xSemaphoreTake(_mutex_box_1_blower_gpio, 0);
  _box_1_blower_gpio_changed = false;
  xSemaphoreGive(_mutex_box_1_blower_gpio);
}

bool is_box_1_blower_gpio_changed() {
  xSemaphoreTake(_mutex_box_1_blower_gpio, 0);
  bool v = _box_1_blower_gpio_changed;
  xSemaphoreGive(_mutex_box_1_blower_gpio);
  return v;
}



int get_box_1_blower_gpio() {
  return geti(BOX_1_BLOWER_GPIO);
}

void set_box_1_blower_gpio(int value) {
  if (geti(BOX_1_BLOWER_GPIO) == value) return;
  seti(BOX_1_BLOWER_GPIO, value);
  xSemaphoreTake(_mutex_box_1_blower_gpio, 0);
  _box_1_blower_gpio_changed = true;
  xSemaphoreGive(_mutex_box_1_blower_gpio);
}


static SemaphoreHandle_t _mutex_box_1_blower_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_blower_enabled_changed = true;

void reset_box_1_blower_enabled_changed() {
  xSemaphoreTake(_mutex_box_1_blower_enabled, 0);
  _box_1_blower_enabled_changed = false;
  xSemaphoreGive(_mutex_box_1_blower_enabled);
}

bool is_box_1_blower_enabled_changed() {
  xSemaphoreTake(_mutex_box_1_blower_enabled, 0);
  bool v = _box_1_blower_enabled_changed;
  xSemaphoreGive(_mutex_box_1_blower_enabled);
  return v;
}



int get_box_1_blower_enabled() {
  return geti(BOX_1_BLOWER_ENABLED);
}

void set_box_1_blower_enabled(int value) {
  if (geti(BOX_1_BLOWER_ENABLED) == value) return;
  seti(BOX_1_BLOWER_ENABLED, value);
  xSemaphoreTake(_mutex_box_1_blower_enabled, 0);
  _box_1_blower_enabled_changed = true;
  xSemaphoreGive(_mutex_box_1_blower_enabled);
}


static SemaphoreHandle_t _mutex_box_1_sht1x_temp_c; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_sht1x_temp_c_changed = true;

void reset_box_1_sht1x_temp_c_changed() {
  xSemaphoreTake(_mutex_box_1_sht1x_temp_c, 0);
  _box_1_sht1x_temp_c_changed = false;
  xSemaphoreGive(_mutex_box_1_sht1x_temp_c);
}

bool is_box_1_sht1x_temp_c_changed() {
  xSemaphoreTake(_mutex_box_1_sht1x_temp_c, 0);
  bool v = _box_1_sht1x_temp_c_changed;
  xSemaphoreGive(_mutex_box_1_sht1x_temp_c);
  return v;
}



int get_box_1_sht1x_temp_c() {
  return geti(BOX_1_SHT1X_TEMP_C);
}

void set_box_1_sht1x_temp_c(int value) {
  if (geti(BOX_1_SHT1X_TEMP_C) == value) return;
  seti(BOX_1_SHT1X_TEMP_C, value);
  xSemaphoreTake(_mutex_box_1_sht1x_temp_c, 0);
  _box_1_sht1x_temp_c_changed = true;
  xSemaphoreGive(_mutex_box_1_sht1x_temp_c);
}


static SemaphoreHandle_t _mutex_box_1_sht1x_temp_f; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_sht1x_temp_f_changed = true;

void reset_box_1_sht1x_temp_f_changed() {
  xSemaphoreTake(_mutex_box_1_sht1x_temp_f, 0);
  _box_1_sht1x_temp_f_changed = false;
  xSemaphoreGive(_mutex_box_1_sht1x_temp_f);
}

bool is_box_1_sht1x_temp_f_changed() {
  xSemaphoreTake(_mutex_box_1_sht1x_temp_f, 0);
  bool v = _box_1_sht1x_temp_f_changed;
  xSemaphoreGive(_mutex_box_1_sht1x_temp_f);
  return v;
}



int get_box_1_sht1x_temp_f() {
  return geti(BOX_1_SHT1X_TEMP_F);
}

void set_box_1_sht1x_temp_f(int value) {
  if (geti(BOX_1_SHT1X_TEMP_F) == value) return;
  seti(BOX_1_SHT1X_TEMP_F, value);
  xSemaphoreTake(_mutex_box_1_sht1x_temp_f, 0);
  _box_1_sht1x_temp_f_changed = true;
  xSemaphoreGive(_mutex_box_1_sht1x_temp_f);
}


static SemaphoreHandle_t _mutex_box_1_sht1x_humi; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_sht1x_humi_changed = true;

void reset_box_1_sht1x_humi_changed() {
  xSemaphoreTake(_mutex_box_1_sht1x_humi, 0);
  _box_1_sht1x_humi_changed = false;
  xSemaphoreGive(_mutex_box_1_sht1x_humi);
}

bool is_box_1_sht1x_humi_changed() {
  xSemaphoreTake(_mutex_box_1_sht1x_humi, 0);
  bool v = _box_1_sht1x_humi_changed;
  xSemaphoreGive(_mutex_box_1_sht1x_humi);
  return v;
}



int get_box_1_sht1x_humi() {
  return geti(BOX_1_SHT1X_HUMI);
}

void set_box_1_sht1x_humi(int value) {
  if (geti(BOX_1_SHT1X_HUMI) == value) return;
  seti(BOX_1_SHT1X_HUMI, value);
  xSemaphoreTake(_mutex_box_1_sht1x_humi, 0);
  _box_1_sht1x_humi_changed = true;
  xSemaphoreGive(_mutex_box_1_sht1x_humi);
}


static SemaphoreHandle_t _mutex_box_1_arduino_co2; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_arduino_co2_changed = true;

void reset_box_1_arduino_co2_changed() {
  xSemaphoreTake(_mutex_box_1_arduino_co2, 0);
  _box_1_arduino_co2_changed = false;
  xSemaphoreGive(_mutex_box_1_arduino_co2);
}

bool is_box_1_arduino_co2_changed() {
  xSemaphoreTake(_mutex_box_1_arduino_co2, 0);
  bool v = _box_1_arduino_co2_changed;
  xSemaphoreGive(_mutex_box_1_arduino_co2);
  return v;
}



int get_box_1_arduino_co2() {
  return geti(BOX_1_ARDUINO_CO2);
}

void set_box_1_arduino_co2(int value) {
  if (geti(BOX_1_ARDUINO_CO2) == value) return;
  seti(BOX_1_ARDUINO_CO2, value);
  xSemaphoreTake(_mutex_box_1_arduino_co2, 0);
  _box_1_arduino_co2_changed = true;
  xSemaphoreGive(_mutex_box_1_arduino_co2);
}


static SemaphoreHandle_t _mutex_box_1_dust_gpy2y10; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_dust_gpy2y10_changed = true;

void reset_box_1_dust_gpy2y10_changed() {
  xSemaphoreTake(_mutex_box_1_dust_gpy2y10, 0);
  _box_1_dust_gpy2y10_changed = false;
  xSemaphoreGive(_mutex_box_1_dust_gpy2y10);
}

bool is_box_1_dust_gpy2y10_changed() {
  xSemaphoreTake(_mutex_box_1_dust_gpy2y10, 0);
  bool v = _box_1_dust_gpy2y10_changed;
  xSemaphoreGive(_mutex_box_1_dust_gpy2y10);
  return v;
}



int get_box_1_dust_gpy2y10() {
  return geti(BOX_1_DUST_GPY2Y10);
}

void set_box_1_dust_gpy2y10(int value) {
  if (geti(BOX_1_DUST_GPY2Y10) == value) return;
  seti(BOX_1_DUST_GPY2Y10, value);
  xSemaphoreTake(_mutex_box_1_dust_gpy2y10, 0);
  _box_1_dust_gpy2y10_changed = true;
  xSemaphoreGive(_mutex_box_1_dust_gpy2y10);
}


static SemaphoreHandle_t _mutex_box_1_led_info; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_led_info_changed = true;

void reset_box_1_led_info_changed() {
  xSemaphoreTake(_mutex_box_1_led_info, 0);
  _box_1_led_info_changed = false;
  xSemaphoreGive(_mutex_box_1_led_info);
}

bool is_box_1_led_info_changed() {
  xSemaphoreTake(_mutex_box_1_led_info, 0);
  bool v = _box_1_led_info_changed;
  xSemaphoreGive(_mutex_box_1_led_info);
  return v;
}



static char _box_1_led_info[MAX_KVALUE_SIZE] = {0};

void get_box_1_led_info(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_box_1_led_info, 0);
  _box_1_led_info_changed = true;
  strncpy(dest, _box_1_led_info, len);
  xSemaphoreGive(_mutex_box_1_led_info);
}

void set_box_1_led_info(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_box_1_led_info, 0);
  if (!strcmp(_box_1_led_info, value)) return;
  strncpy(_box_1_led_info, value, strlen(value));
  _box_1_led_info_changed = true;
  xSemaphoreGive(_mutex_box_1_led_info);
}

static SemaphoreHandle_t _mutex_box_2_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_enabled_changed = true;

void reset_box_2_enabled_changed() {
  xSemaphoreTake(_mutex_box_2_enabled, 0);
  _box_2_enabled_changed = false;
  xSemaphoreGive(_mutex_box_2_enabled);
}

bool is_box_2_enabled_changed() {
  xSemaphoreTake(_mutex_box_2_enabled, 0);
  bool v = _box_2_enabled_changed;
  xSemaphoreGive(_mutex_box_2_enabled);
  return v;
}



int get_box_2_enabled() {
  return geti(BOX_2_ENABLED);
}

void set_box_2_enabled(int value) {
  if (geti(BOX_2_ENABLED) == value) return;
  seti(BOX_2_ENABLED, value);
  xSemaphoreTake(_mutex_box_2_enabled, 0);
  _box_2_enabled_changed = true;
  xSemaphoreGive(_mutex_box_2_enabled);
}


static SemaphoreHandle_t _mutex_box_2_timer_type; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_timer_type_changed = true;

void reset_box_2_timer_type_changed() {
  xSemaphoreTake(_mutex_box_2_timer_type, 0);
  _box_2_timer_type_changed = false;
  xSemaphoreGive(_mutex_box_2_timer_type);
}

bool is_box_2_timer_type_changed() {
  xSemaphoreTake(_mutex_box_2_timer_type, 0);
  bool v = _box_2_timer_type_changed;
  xSemaphoreGive(_mutex_box_2_timer_type);
  return v;
}



int get_box_2_timer_type() {
  return geti(BOX_2_TIMER_TYPE);
}

void set_box_2_timer_type(int value) {
  if (geti(BOX_2_TIMER_TYPE) == value) return;
  seti(BOX_2_TIMER_TYPE, value);
  xSemaphoreTake(_mutex_box_2_timer_type, 0);
  _box_2_timer_type_changed = true;
  xSemaphoreGive(_mutex_box_2_timer_type);
}


static SemaphoreHandle_t _mutex_box_2_timer_output; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_timer_output_changed = true;

void reset_box_2_timer_output_changed() {
  xSemaphoreTake(_mutex_box_2_timer_output, 0);
  _box_2_timer_output_changed = false;
  xSemaphoreGive(_mutex_box_2_timer_output);
}

bool is_box_2_timer_output_changed() {
  xSemaphoreTake(_mutex_box_2_timer_output, 0);
  bool v = _box_2_timer_output_changed;
  xSemaphoreGive(_mutex_box_2_timer_output);
  return v;
}



int get_box_2_timer_output() {
  return geti(BOX_2_TIMER_OUTPUT);
}

void set_box_2_timer_output(int value) {
  if (geti(BOX_2_TIMER_OUTPUT) == value) return;
  seti(BOX_2_TIMER_OUTPUT, value);
  xSemaphoreTake(_mutex_box_2_timer_output, 0);
  _box_2_timer_output_changed = true;
  xSemaphoreGive(_mutex_box_2_timer_output);
}


static SemaphoreHandle_t _mutex_box_2_started_at; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_started_at_changed = true;

void reset_box_2_started_at_changed() {
  xSemaphoreTake(_mutex_box_2_started_at, 0);
  _box_2_started_at_changed = false;
  xSemaphoreGive(_mutex_box_2_started_at);
}

bool is_box_2_started_at_changed() {
  xSemaphoreTake(_mutex_box_2_started_at, 0);
  bool v = _box_2_started_at_changed;
  xSemaphoreGive(_mutex_box_2_started_at);
  return v;
}



int get_box_2_started_at() {
  return geti(BOX_2_STARTED_AT);
}

void set_box_2_started_at(int value) {
  if (geti(BOX_2_STARTED_AT) == value) return;
  seti(BOX_2_STARTED_AT, value);
  xSemaphoreTake(_mutex_box_2_started_at, 0);
  _box_2_started_at_changed = true;
  xSemaphoreGive(_mutex_box_2_started_at);
}


static SemaphoreHandle_t _mutex_box_2_on_hour; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_on_hour_changed = true;

void reset_box_2_on_hour_changed() {
  xSemaphoreTake(_mutex_box_2_on_hour, 0);
  _box_2_on_hour_changed = false;
  xSemaphoreGive(_mutex_box_2_on_hour);
}

bool is_box_2_on_hour_changed() {
  xSemaphoreTake(_mutex_box_2_on_hour, 0);
  bool v = _box_2_on_hour_changed;
  xSemaphoreGive(_mutex_box_2_on_hour);
  return v;
}



int get_box_2_on_hour() {
  return geti(B_2_ON_HOUR);
}

void set_box_2_on_hour(int value) {
  if (geti(B_2_ON_HOUR) == value) return;
  seti(B_2_ON_HOUR, value);
  xSemaphoreTake(_mutex_box_2_on_hour, 0);
  _box_2_on_hour_changed = true;
  xSemaphoreGive(_mutex_box_2_on_hour);
}


static SemaphoreHandle_t _mutex_box_2_on_min; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_on_min_changed = true;

void reset_box_2_on_min_changed() {
  xSemaphoreTake(_mutex_box_2_on_min, 0);
  _box_2_on_min_changed = false;
  xSemaphoreGive(_mutex_box_2_on_min);
}

bool is_box_2_on_min_changed() {
  xSemaphoreTake(_mutex_box_2_on_min, 0);
  bool v = _box_2_on_min_changed;
  xSemaphoreGive(_mutex_box_2_on_min);
  return v;
}



int get_box_2_on_min() {
  return geti(BOX_2_ON_MIN);
}

void set_box_2_on_min(int value) {
  if (geti(BOX_2_ON_MIN) == value) return;
  seti(BOX_2_ON_MIN, value);
  xSemaphoreTake(_mutex_box_2_on_min, 0);
  _box_2_on_min_changed = true;
  xSemaphoreGive(_mutex_box_2_on_min);
}


static SemaphoreHandle_t _mutex_box_2_off_hour; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_off_hour_changed = true;

void reset_box_2_off_hour_changed() {
  xSemaphoreTake(_mutex_box_2_off_hour, 0);
  _box_2_off_hour_changed = false;
  xSemaphoreGive(_mutex_box_2_off_hour);
}

bool is_box_2_off_hour_changed() {
  xSemaphoreTake(_mutex_box_2_off_hour, 0);
  bool v = _box_2_off_hour_changed;
  xSemaphoreGive(_mutex_box_2_off_hour);
  return v;
}



int get_box_2_off_hour() {
  return geti(BOX_2_OFF_HOUR);
}

void set_box_2_off_hour(int value) {
  if (geti(BOX_2_OFF_HOUR) == value) return;
  seti(BOX_2_OFF_HOUR, value);
  xSemaphoreTake(_mutex_box_2_off_hour, 0);
  _box_2_off_hour_changed = true;
  xSemaphoreGive(_mutex_box_2_off_hour);
}


static SemaphoreHandle_t _mutex_box_2_off_min; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_off_min_changed = true;

void reset_box_2_off_min_changed() {
  xSemaphoreTake(_mutex_box_2_off_min, 0);
  _box_2_off_min_changed = false;
  xSemaphoreGive(_mutex_box_2_off_min);
}

bool is_box_2_off_min_changed() {
  xSemaphoreTake(_mutex_box_2_off_min, 0);
  bool v = _box_2_off_min_changed;
  xSemaphoreGive(_mutex_box_2_off_min);
  return v;
}



int get_box_2_off_min() {
  return geti(BOX_2_OFF_MIN);
}

void set_box_2_off_min(int value) {
  if (geti(BOX_2_OFF_MIN) == value) return;
  seti(BOX_2_OFF_MIN, value);
  xSemaphoreTake(_mutex_box_2_off_min, 0);
  _box_2_off_min_changed = true;
  xSemaphoreGive(_mutex_box_2_off_min);
}


static SemaphoreHandle_t _mutex_box_2_stretch; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_stretch_changed = true;

void reset_box_2_stretch_changed() {
  xSemaphoreTake(_mutex_box_2_stretch, 0);
  _box_2_stretch_changed = false;
  xSemaphoreGive(_mutex_box_2_stretch);
}

bool is_box_2_stretch_changed() {
  xSemaphoreTake(_mutex_box_2_stretch, 0);
  bool v = _box_2_stretch_changed;
  xSemaphoreGive(_mutex_box_2_stretch);
  return v;
}



int get_box_2_stretch() {
  return geti(BOX_2_STRETCH);
}

void set_box_2_stretch(int value) {
  if (geti(BOX_2_STRETCH) == value) return;
  seti(BOX_2_STRETCH, value);
  xSemaphoreTake(_mutex_box_2_stretch, 0);
  _box_2_stretch_changed = true;
  xSemaphoreGive(_mutex_box_2_stretch);
}


static SemaphoreHandle_t _mutex_box_2_led_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_led_dim_changed = true;

void reset_box_2_led_dim_changed() {
  xSemaphoreTake(_mutex_box_2_led_dim, 0);
  _box_2_led_dim_changed = false;
  xSemaphoreGive(_mutex_box_2_led_dim);
}

bool is_box_2_led_dim_changed() {
  xSemaphoreTake(_mutex_box_2_led_dim, 0);
  bool v = _box_2_led_dim_changed;
  xSemaphoreGive(_mutex_box_2_led_dim);
  return v;
}



int get_box_2_led_dim() {
  return geti(BOX_2_LED_DIM);
}

void set_box_2_led_dim(int value) {
  if (geti(BOX_2_LED_DIM) == value) return;
  seti(BOX_2_LED_DIM, value);
  xSemaphoreTake(_mutex_box_2_led_dim, 0);
  _box_2_led_dim_changed = true;
  xSemaphoreGive(_mutex_box_2_led_dim);
}


static SemaphoreHandle_t _mutex_box_2_blower; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_blower_changed = true;

void reset_box_2_blower_changed() {
  xSemaphoreTake(_mutex_box_2_blower, 0);
  _box_2_blower_changed = false;
  xSemaphoreGive(_mutex_box_2_blower);
}

bool is_box_2_blower_changed() {
  xSemaphoreTake(_mutex_box_2_blower, 0);
  bool v = _box_2_blower_changed;
  xSemaphoreGive(_mutex_box_2_blower);
  return v;
}



int get_box_2_blower() {
  return geti(BOX_2_BLOWER);
}

void set_box_2_blower(int value) {
  if (geti(BOX_2_BLOWER) == value) return;
  seti(BOX_2_BLOWER, value);
  xSemaphoreTake(_mutex_box_2_blower, 0);
  _box_2_blower_changed = true;
  xSemaphoreGive(_mutex_box_2_blower);
}


static SemaphoreHandle_t _mutex_box_2_blower_mode; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_blower_mode_changed = true;

void reset_box_2_blower_mode_changed() {
  xSemaphoreTake(_mutex_box_2_blower_mode, 0);
  _box_2_blower_mode_changed = false;
  xSemaphoreGive(_mutex_box_2_blower_mode);
}

bool is_box_2_blower_mode_changed() {
  xSemaphoreTake(_mutex_box_2_blower_mode, 0);
  bool v = _box_2_blower_mode_changed;
  xSemaphoreGive(_mutex_box_2_blower_mode);
  return v;
}



int get_box_2_blower_mode() {
  return geti(BOX_2_BLOWER_MODE);
}

void set_box_2_blower_mode(int value) {
  if (geti(BOX_2_BLOWER_MODE) == value) return;
  seti(BOX_2_BLOWER_MODE, value);
  xSemaphoreTake(_mutex_box_2_blower_mode, 0);
  _box_2_blower_mode_changed = true;
  xSemaphoreGive(_mutex_box_2_blower_mode);
}


static SemaphoreHandle_t _mutex_box_2_blower_gpio; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_blower_gpio_changed = true;

void reset_box_2_blower_gpio_changed() {
  xSemaphoreTake(_mutex_box_2_blower_gpio, 0);
  _box_2_blower_gpio_changed = false;
  xSemaphoreGive(_mutex_box_2_blower_gpio);
}

bool is_box_2_blower_gpio_changed() {
  xSemaphoreTake(_mutex_box_2_blower_gpio, 0);
  bool v = _box_2_blower_gpio_changed;
  xSemaphoreGive(_mutex_box_2_blower_gpio);
  return v;
}



int get_box_2_blower_gpio() {
  return geti(BOX_2_BLOWER_GPIO);
}

void set_box_2_blower_gpio(int value) {
  if (geti(BOX_2_BLOWER_GPIO) == value) return;
  seti(BOX_2_BLOWER_GPIO, value);
  xSemaphoreTake(_mutex_box_2_blower_gpio, 0);
  _box_2_blower_gpio_changed = true;
  xSemaphoreGive(_mutex_box_2_blower_gpio);
}


static SemaphoreHandle_t _mutex_box_2_blower_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_blower_enabled_changed = true;

void reset_box_2_blower_enabled_changed() {
  xSemaphoreTake(_mutex_box_2_blower_enabled, 0);
  _box_2_blower_enabled_changed = false;
  xSemaphoreGive(_mutex_box_2_blower_enabled);
}

bool is_box_2_blower_enabled_changed() {
  xSemaphoreTake(_mutex_box_2_blower_enabled, 0);
  bool v = _box_2_blower_enabled_changed;
  xSemaphoreGive(_mutex_box_2_blower_enabled);
  return v;
}



int get_box_2_blower_enabled() {
  return geti(BOX_2_BLOWER_ENABLED);
}

void set_box_2_blower_enabled(int value) {
  if (geti(BOX_2_BLOWER_ENABLED) == value) return;
  seti(BOX_2_BLOWER_ENABLED, value);
  xSemaphoreTake(_mutex_box_2_blower_enabled, 0);
  _box_2_blower_enabled_changed = true;
  xSemaphoreGive(_mutex_box_2_blower_enabled);
}


static SemaphoreHandle_t _mutex_box_2_sht1x_temp_c; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_sht1x_temp_c_changed = true;

void reset_box_2_sht1x_temp_c_changed() {
  xSemaphoreTake(_mutex_box_2_sht1x_temp_c, 0);
  _box_2_sht1x_temp_c_changed = false;
  xSemaphoreGive(_mutex_box_2_sht1x_temp_c);
}

bool is_box_2_sht1x_temp_c_changed() {
  xSemaphoreTake(_mutex_box_2_sht1x_temp_c, 0);
  bool v = _box_2_sht1x_temp_c_changed;
  xSemaphoreGive(_mutex_box_2_sht1x_temp_c);
  return v;
}



int get_box_2_sht1x_temp_c() {
  return geti(BOX_2_SHT1X_TEMP_C);
}

void set_box_2_sht1x_temp_c(int value) {
  if (geti(BOX_2_SHT1X_TEMP_C) == value) return;
  seti(BOX_2_SHT1X_TEMP_C, value);
  xSemaphoreTake(_mutex_box_2_sht1x_temp_c, 0);
  _box_2_sht1x_temp_c_changed = true;
  xSemaphoreGive(_mutex_box_2_sht1x_temp_c);
}


static SemaphoreHandle_t _mutex_box_2_sht1x_temp_f; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_sht1x_temp_f_changed = true;

void reset_box_2_sht1x_temp_f_changed() {
  xSemaphoreTake(_mutex_box_2_sht1x_temp_f, 0);
  _box_2_sht1x_temp_f_changed = false;
  xSemaphoreGive(_mutex_box_2_sht1x_temp_f);
}

bool is_box_2_sht1x_temp_f_changed() {
  xSemaphoreTake(_mutex_box_2_sht1x_temp_f, 0);
  bool v = _box_2_sht1x_temp_f_changed;
  xSemaphoreGive(_mutex_box_2_sht1x_temp_f);
  return v;
}



int get_box_2_sht1x_temp_f() {
  return geti(BOX_2_SHT1X_TEMP_F);
}

void set_box_2_sht1x_temp_f(int value) {
  if (geti(BOX_2_SHT1X_TEMP_F) == value) return;
  seti(BOX_2_SHT1X_TEMP_F, value);
  xSemaphoreTake(_mutex_box_2_sht1x_temp_f, 0);
  _box_2_sht1x_temp_f_changed = true;
  xSemaphoreGive(_mutex_box_2_sht1x_temp_f);
}


static SemaphoreHandle_t _mutex_box_2_sht1x_humi; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_sht1x_humi_changed = true;

void reset_box_2_sht1x_humi_changed() {
  xSemaphoreTake(_mutex_box_2_sht1x_humi, 0);
  _box_2_sht1x_humi_changed = false;
  xSemaphoreGive(_mutex_box_2_sht1x_humi);
}

bool is_box_2_sht1x_humi_changed() {
  xSemaphoreTake(_mutex_box_2_sht1x_humi, 0);
  bool v = _box_2_sht1x_humi_changed;
  xSemaphoreGive(_mutex_box_2_sht1x_humi);
  return v;
}



int get_box_2_sht1x_humi() {
  return geti(BOX_2_SHT1X_HUMI);
}

void set_box_2_sht1x_humi(int value) {
  if (geti(BOX_2_SHT1X_HUMI) == value) return;
  seti(BOX_2_SHT1X_HUMI, value);
  xSemaphoreTake(_mutex_box_2_sht1x_humi, 0);
  _box_2_sht1x_humi_changed = true;
  xSemaphoreGive(_mutex_box_2_sht1x_humi);
}


static SemaphoreHandle_t _mutex_box_2_arduino_co2; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_arduino_co2_changed = true;

void reset_box_2_arduino_co2_changed() {
  xSemaphoreTake(_mutex_box_2_arduino_co2, 0);
  _box_2_arduino_co2_changed = false;
  xSemaphoreGive(_mutex_box_2_arduino_co2);
}

bool is_box_2_arduino_co2_changed() {
  xSemaphoreTake(_mutex_box_2_arduino_co2, 0);
  bool v = _box_2_arduino_co2_changed;
  xSemaphoreGive(_mutex_box_2_arduino_co2);
  return v;
}



int get_box_2_arduino_co2() {
  return geti(BOX_2_ARDUINO_CO2);
}

void set_box_2_arduino_co2(int value) {
  if (geti(BOX_2_ARDUINO_CO2) == value) return;
  seti(BOX_2_ARDUINO_CO2, value);
  xSemaphoreTake(_mutex_box_2_arduino_co2, 0);
  _box_2_arduino_co2_changed = true;
  xSemaphoreGive(_mutex_box_2_arduino_co2);
}


static SemaphoreHandle_t _mutex_box_2_dust_gpy2y10; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_dust_gpy2y10_changed = true;

void reset_box_2_dust_gpy2y10_changed() {
  xSemaphoreTake(_mutex_box_2_dust_gpy2y10, 0);
  _box_2_dust_gpy2y10_changed = false;
  xSemaphoreGive(_mutex_box_2_dust_gpy2y10);
}

bool is_box_2_dust_gpy2y10_changed() {
  xSemaphoreTake(_mutex_box_2_dust_gpy2y10, 0);
  bool v = _box_2_dust_gpy2y10_changed;
  xSemaphoreGive(_mutex_box_2_dust_gpy2y10);
  return v;
}



int get_box_2_dust_gpy2y10() {
  return geti(BOX_2_DUST_GPY2Y10);
}

void set_box_2_dust_gpy2y10(int value) {
  if (geti(BOX_2_DUST_GPY2Y10) == value) return;
  seti(BOX_2_DUST_GPY2Y10, value);
  xSemaphoreTake(_mutex_box_2_dust_gpy2y10, 0);
  _box_2_dust_gpy2y10_changed = true;
  xSemaphoreGive(_mutex_box_2_dust_gpy2y10);
}


static SemaphoreHandle_t _mutex_box_2_led_info; // TODO check RAM weight of creating so many semaphores :/
static bool _box_2_led_info_changed = true;

void reset_box_2_led_info_changed() {
  xSemaphoreTake(_mutex_box_2_led_info, 0);
  _box_2_led_info_changed = false;
  xSemaphoreGive(_mutex_box_2_led_info);
}

bool is_box_2_led_info_changed() {
  xSemaphoreTake(_mutex_box_2_led_info, 0);
  bool v = _box_2_led_info_changed;
  xSemaphoreGive(_mutex_box_2_led_info);
  return v;
}



static char _box_2_led_info[MAX_KVALUE_SIZE] = {0};

void get_box_2_led_info(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_box_2_led_info, 0);
  _box_2_led_info_changed = true;
  strncpy(dest, _box_2_led_info, len);
  xSemaphoreGive(_mutex_box_2_led_info);
}

void set_box_2_led_info(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  xSemaphoreTake(_mutex_box_2_led_info, 0);
  if (!strcmp(_box_2_led_info, value)) return;
  strncpy(_box_2_led_info, value, strlen(value));
  _box_2_led_info_changed = true;
  xSemaphoreGive(_mutex_box_2_led_info);
}

static SemaphoreHandle_t _mutex_led_0_duty; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_duty_changed = true;

void reset_led_0_duty_changed() {
  xSemaphoreTake(_mutex_led_0_duty, 0);
  _led_0_duty_changed = false;
  xSemaphoreGive(_mutex_led_0_duty);
}

bool is_led_0_duty_changed() {
  xSemaphoreTake(_mutex_led_0_duty, 0);
  bool v = _led_0_duty_changed;
  xSemaphoreGive(_mutex_led_0_duty);
  return v;
}



int get_led_0_duty() {
  return geti(LED_0_DUTY);
}

void set_led_0_duty(int value) {
  if (geti(LED_0_DUTY) == value) return;
  seti(LED_0_DUTY, value);
  xSemaphoreTake(_mutex_led_0_duty, 0);
  _led_0_duty_changed = true;
  xSemaphoreGive(_mutex_led_0_duty);
}


static SemaphoreHandle_t _mutex_led_1_duty; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_duty_changed = true;

void reset_led_1_duty_changed() {
  xSemaphoreTake(_mutex_led_1_duty, 0);
  _led_1_duty_changed = false;
  xSemaphoreGive(_mutex_led_1_duty);
}

bool is_led_1_duty_changed() {
  xSemaphoreTake(_mutex_led_1_duty, 0);
  bool v = _led_1_duty_changed;
  xSemaphoreGive(_mutex_led_1_duty);
  return v;
}



int get_led_1_duty() {
  return geti(LED_1_DUTY);
}

void set_led_1_duty(int value) {
  if (geti(LED_1_DUTY) == value) return;
  seti(LED_1_DUTY, value);
  xSemaphoreTake(_mutex_led_1_duty, 0);
  _led_1_duty_changed = true;
  xSemaphoreGive(_mutex_led_1_duty);
}


static SemaphoreHandle_t _mutex_led_2_duty; // TODO check RAM weight of creating so many semaphores :/
static bool _led_2_duty_changed = true;

void reset_led_2_duty_changed() {
  xSemaphoreTake(_mutex_led_2_duty, 0);
  _led_2_duty_changed = false;
  xSemaphoreGive(_mutex_led_2_duty);
}

bool is_led_2_duty_changed() {
  xSemaphoreTake(_mutex_led_2_duty, 0);
  bool v = _led_2_duty_changed;
  xSemaphoreGive(_mutex_led_2_duty);
  return v;
}



int get_led_2_duty() {
  return geti(LED_2_DUTY);
}

void set_led_2_duty(int value) {
  if (geti(LED_2_DUTY) == value) return;
  seti(LED_2_DUTY, value);
  xSemaphoreTake(_mutex_led_2_duty, 0);
  _led_2_duty_changed = true;
  xSemaphoreGive(_mutex_led_2_duty);
}


static SemaphoreHandle_t _mutex_led_3_duty; // TODO check RAM weight of creating so many semaphores :/
static bool _led_3_duty_changed = true;

void reset_led_3_duty_changed() {
  xSemaphoreTake(_mutex_led_3_duty, 0);
  _led_3_duty_changed = false;
  xSemaphoreGive(_mutex_led_3_duty);
}

bool is_led_3_duty_changed() {
  xSemaphoreTake(_mutex_led_3_duty, 0);
  bool v = _led_3_duty_changed;
  xSemaphoreGive(_mutex_led_3_duty);
  return v;
}



int get_led_3_duty() {
  return geti(LED_3_DUTY);
}

void set_led_3_duty(int value) {
  if (geti(LED_3_DUTY) == value) return;
  seti(LED_3_DUTY, value);
  xSemaphoreTake(_mutex_led_3_duty, 0);
  _led_3_duty_changed = true;
  xSemaphoreGive(_mutex_led_3_duty);
}


static SemaphoreHandle_t _mutex_led_4_duty; // TODO check RAM weight of creating so many semaphores :/
static bool _led_4_duty_changed = true;

void reset_led_4_duty_changed() {
  xSemaphoreTake(_mutex_led_4_duty, 0);
  _led_4_duty_changed = false;
  xSemaphoreGive(_mutex_led_4_duty);
}

bool is_led_4_duty_changed() {
  xSemaphoreTake(_mutex_led_4_duty, 0);
  bool v = _led_4_duty_changed;
  xSemaphoreGive(_mutex_led_4_duty);
  return v;
}



int get_led_4_duty() {
  return geti(LED_4_DUTY);
}

void set_led_4_duty(int value) {
  if (geti(LED_4_DUTY) == value) return;
  seti(LED_4_DUTY, value);
  xSemaphoreTake(_mutex_led_4_duty, 0);
  _led_4_duty_changed = true;
  xSemaphoreGive(_mutex_led_4_duty);
}


static SemaphoreHandle_t _mutex_led_5_duty; // TODO check RAM weight of creating so many semaphores :/
static bool _led_5_duty_changed = true;

void reset_led_5_duty_changed() {
  xSemaphoreTake(_mutex_led_5_duty, 0);
  _led_5_duty_changed = false;
  xSemaphoreGive(_mutex_led_5_duty);
}

bool is_led_5_duty_changed() {
  xSemaphoreTake(_mutex_led_5_duty, 0);
  bool v = _led_5_duty_changed;
  xSemaphoreGive(_mutex_led_5_duty);
  return v;
}



int get_led_5_duty() {
  return geti(LED_5_DUTY);
}

void set_led_5_duty(int value) {
  if (geti(LED_5_DUTY) == value) return;
  seti(LED_5_DUTY, value);
  xSemaphoreTake(_mutex_led_5_duty, 0);
  _led_5_duty_changed = true;
  xSemaphoreGive(_mutex_led_5_duty);
}


static SemaphoreHandle_t _mutex_led_0_gpio; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_gpio_changed = true;

void reset_led_0_gpio_changed() {
  xSemaphoreTake(_mutex_led_0_gpio, 0);
  _led_0_gpio_changed = false;
  xSemaphoreGive(_mutex_led_0_gpio);
}

bool is_led_0_gpio_changed() {
  xSemaphoreTake(_mutex_led_0_gpio, 0);
  bool v = _led_0_gpio_changed;
  xSemaphoreGive(_mutex_led_0_gpio);
  return v;
}



int get_led_0_gpio() {
  return geti(LED_0_GPIO);
}

void set_led_0_gpio(int value) {
  if (geti(LED_0_GPIO) == value) return;
  seti(LED_0_GPIO, value);
  xSemaphoreTake(_mutex_led_0_gpio, 0);
  _led_0_gpio_changed = true;
  xSemaphoreGive(_mutex_led_0_gpio);
}


static SemaphoreHandle_t _mutex_led_1_gpio; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_gpio_changed = true;

void reset_led_1_gpio_changed() {
  xSemaphoreTake(_mutex_led_1_gpio, 0);
  _led_1_gpio_changed = false;
  xSemaphoreGive(_mutex_led_1_gpio);
}

bool is_led_1_gpio_changed() {
  xSemaphoreTake(_mutex_led_1_gpio, 0);
  bool v = _led_1_gpio_changed;
  xSemaphoreGive(_mutex_led_1_gpio);
  return v;
}



int get_led_1_gpio() {
  return geti(LED_1_GPIO);
}

void set_led_1_gpio(int value) {
  if (geti(LED_1_GPIO) == value) return;
  seti(LED_1_GPIO, value);
  xSemaphoreTake(_mutex_led_1_gpio, 0);
  _led_1_gpio_changed = true;
  xSemaphoreGive(_mutex_led_1_gpio);
}


static SemaphoreHandle_t _mutex_led_2_gpio; // TODO check RAM weight of creating so many semaphores :/
static bool _led_2_gpio_changed = true;

void reset_led_2_gpio_changed() {
  xSemaphoreTake(_mutex_led_2_gpio, 0);
  _led_2_gpio_changed = false;
  xSemaphoreGive(_mutex_led_2_gpio);
}

bool is_led_2_gpio_changed() {
  xSemaphoreTake(_mutex_led_2_gpio, 0);
  bool v = _led_2_gpio_changed;
  xSemaphoreGive(_mutex_led_2_gpio);
  return v;
}



int get_led_2_gpio() {
  return geti(LED_2_GPIO);
}

void set_led_2_gpio(int value) {
  if (geti(LED_2_GPIO) == value) return;
  seti(LED_2_GPIO, value);
  xSemaphoreTake(_mutex_led_2_gpio, 0);
  _led_2_gpio_changed = true;
  xSemaphoreGive(_mutex_led_2_gpio);
}


static SemaphoreHandle_t _mutex_led_3_gpio; // TODO check RAM weight of creating so many semaphores :/
static bool _led_3_gpio_changed = true;

void reset_led_3_gpio_changed() {
  xSemaphoreTake(_mutex_led_3_gpio, 0);
  _led_3_gpio_changed = false;
  xSemaphoreGive(_mutex_led_3_gpio);
}

bool is_led_3_gpio_changed() {
  xSemaphoreTake(_mutex_led_3_gpio, 0);
  bool v = _led_3_gpio_changed;
  xSemaphoreGive(_mutex_led_3_gpio);
  return v;
}



int get_led_3_gpio() {
  return geti(LED_3_GPIO);
}

void set_led_3_gpio(int value) {
  if (geti(LED_3_GPIO) == value) return;
  seti(LED_3_GPIO, value);
  xSemaphoreTake(_mutex_led_3_gpio, 0);
  _led_3_gpio_changed = true;
  xSemaphoreGive(_mutex_led_3_gpio);
}


static SemaphoreHandle_t _mutex_led_4_gpio; // TODO check RAM weight of creating so many semaphores :/
static bool _led_4_gpio_changed = true;

void reset_led_4_gpio_changed() {
  xSemaphoreTake(_mutex_led_4_gpio, 0);
  _led_4_gpio_changed = false;
  xSemaphoreGive(_mutex_led_4_gpio);
}

bool is_led_4_gpio_changed() {
  xSemaphoreTake(_mutex_led_4_gpio, 0);
  bool v = _led_4_gpio_changed;
  xSemaphoreGive(_mutex_led_4_gpio);
  return v;
}



int get_led_4_gpio() {
  return geti(LED_4_GPIO);
}

void set_led_4_gpio(int value) {
  if (geti(LED_4_GPIO) == value) return;
  seti(LED_4_GPIO, value);
  xSemaphoreTake(_mutex_led_4_gpio, 0);
  _led_4_gpio_changed = true;
  xSemaphoreGive(_mutex_led_4_gpio);
}


static SemaphoreHandle_t _mutex_led_5_gpio; // TODO check RAM weight of creating so many semaphores :/
static bool _led_5_gpio_changed = true;

void reset_led_5_gpio_changed() {
  xSemaphoreTake(_mutex_led_5_gpio, 0);
  _led_5_gpio_changed = false;
  xSemaphoreGive(_mutex_led_5_gpio);
}

bool is_led_5_gpio_changed() {
  xSemaphoreTake(_mutex_led_5_gpio, 0);
  bool v = _led_5_gpio_changed;
  xSemaphoreGive(_mutex_led_5_gpio);
  return v;
}



int get_led_5_gpio() {
  return geti(LED_5_GPIO);
}

void set_led_5_gpio(int value) {
  if (geti(LED_5_GPIO) == value) return;
  seti(LED_5_GPIO, value);
  xSemaphoreTake(_mutex_led_5_gpio, 0);
  _led_5_gpio_changed = true;
  xSemaphoreGive(_mutex_led_5_gpio);
}


static SemaphoreHandle_t _mutex_led_0_x; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_x_changed = true;

void reset_led_0_x_changed() {
  xSemaphoreTake(_mutex_led_0_x, 0);
  _led_0_x_changed = false;
  xSemaphoreGive(_mutex_led_0_x);
}

bool is_led_0_x_changed() {
  xSemaphoreTake(_mutex_led_0_x, 0);
  bool v = _led_0_x_changed;
  xSemaphoreGive(_mutex_led_0_x);
  return v;
}



int get_led_0_x() {
  return geti(LED_0_X);
}

void set_led_0_x(int value) {
  if (geti(LED_0_X) == value) return;
  seti(LED_0_X, value);
  xSemaphoreTake(_mutex_led_0_x, 0);
  _led_0_x_changed = true;
  xSemaphoreGive(_mutex_led_0_x);
}


static SemaphoreHandle_t _mutex_led_1_x; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_x_changed = true;

void reset_led_1_x_changed() {
  xSemaphoreTake(_mutex_led_1_x, 0);
  _led_1_x_changed = false;
  xSemaphoreGive(_mutex_led_1_x);
}

bool is_led_1_x_changed() {
  xSemaphoreTake(_mutex_led_1_x, 0);
  bool v = _led_1_x_changed;
  xSemaphoreGive(_mutex_led_1_x);
  return v;
}



int get_led_1_x() {
  return geti(LED_1_X);
}

void set_led_1_x(int value) {
  if (geti(LED_1_X) == value) return;
  seti(LED_1_X, value);
  xSemaphoreTake(_mutex_led_1_x, 0);
  _led_1_x_changed = true;
  xSemaphoreGive(_mutex_led_1_x);
}


static SemaphoreHandle_t _mutex_led_2_x; // TODO check RAM weight of creating so many semaphores :/
static bool _led_2_x_changed = true;

void reset_led_2_x_changed() {
  xSemaphoreTake(_mutex_led_2_x, 0);
  _led_2_x_changed = false;
  xSemaphoreGive(_mutex_led_2_x);
}

bool is_led_2_x_changed() {
  xSemaphoreTake(_mutex_led_2_x, 0);
  bool v = _led_2_x_changed;
  xSemaphoreGive(_mutex_led_2_x);
  return v;
}



int get_led_2_x() {
  return geti(LED_2_X);
}

void set_led_2_x(int value) {
  if (geti(LED_2_X) == value) return;
  seti(LED_2_X, value);
  xSemaphoreTake(_mutex_led_2_x, 0);
  _led_2_x_changed = true;
  xSemaphoreGive(_mutex_led_2_x);
}


static SemaphoreHandle_t _mutex_led_3_x; // TODO check RAM weight of creating so many semaphores :/
static bool _led_3_x_changed = true;

void reset_led_3_x_changed() {
  xSemaphoreTake(_mutex_led_3_x, 0);
  _led_3_x_changed = false;
  xSemaphoreGive(_mutex_led_3_x);
}

bool is_led_3_x_changed() {
  xSemaphoreTake(_mutex_led_3_x, 0);
  bool v = _led_3_x_changed;
  xSemaphoreGive(_mutex_led_3_x);
  return v;
}



int get_led_3_x() {
  return geti(LED_3_X);
}

void set_led_3_x(int value) {
  if (geti(LED_3_X) == value) return;
  seti(LED_3_X, value);
  xSemaphoreTake(_mutex_led_3_x, 0);
  _led_3_x_changed = true;
  xSemaphoreGive(_mutex_led_3_x);
}


static SemaphoreHandle_t _mutex_led_4_x; // TODO check RAM weight of creating so many semaphores :/
static bool _led_4_x_changed = true;

void reset_led_4_x_changed() {
  xSemaphoreTake(_mutex_led_4_x, 0);
  _led_4_x_changed = false;
  xSemaphoreGive(_mutex_led_4_x);
}

bool is_led_4_x_changed() {
  xSemaphoreTake(_mutex_led_4_x, 0);
  bool v = _led_4_x_changed;
  xSemaphoreGive(_mutex_led_4_x);
  return v;
}



int get_led_4_x() {
  return geti(LED_4_X);
}

void set_led_4_x(int value) {
  if (geti(LED_4_X) == value) return;
  seti(LED_4_X, value);
  xSemaphoreTake(_mutex_led_4_x, 0);
  _led_4_x_changed = true;
  xSemaphoreGive(_mutex_led_4_x);
}


static SemaphoreHandle_t _mutex_led_5_x; // TODO check RAM weight of creating so many semaphores :/
static bool _led_5_x_changed = true;

void reset_led_5_x_changed() {
  xSemaphoreTake(_mutex_led_5_x, 0);
  _led_5_x_changed = false;
  xSemaphoreGive(_mutex_led_5_x);
}

bool is_led_5_x_changed() {
  xSemaphoreTake(_mutex_led_5_x, 0);
  bool v = _led_5_x_changed;
  xSemaphoreGive(_mutex_led_5_x);
  return v;
}



int get_led_5_x() {
  return geti(LED_5_X);
}

void set_led_5_x(int value) {
  if (geti(LED_5_X) == value) return;
  seti(LED_5_X, value);
  xSemaphoreTake(_mutex_led_5_x, 0);
  _led_5_x_changed = true;
  xSemaphoreGive(_mutex_led_5_x);
}


static SemaphoreHandle_t _mutex_led_0_y; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_y_changed = true;

void reset_led_0_y_changed() {
  xSemaphoreTake(_mutex_led_0_y, 0);
  _led_0_y_changed = false;
  xSemaphoreGive(_mutex_led_0_y);
}

bool is_led_0_y_changed() {
  xSemaphoreTake(_mutex_led_0_y, 0);
  bool v = _led_0_y_changed;
  xSemaphoreGive(_mutex_led_0_y);
  return v;
}



int get_led_0_y() {
  return geti(LED_0_Y);
}

void set_led_0_y(int value) {
  if (geti(LED_0_Y) == value) return;
  seti(LED_0_Y, value);
  xSemaphoreTake(_mutex_led_0_y, 0);
  _led_0_y_changed = true;
  xSemaphoreGive(_mutex_led_0_y);
}


static SemaphoreHandle_t _mutex_led_1_y; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_y_changed = true;

void reset_led_1_y_changed() {
  xSemaphoreTake(_mutex_led_1_y, 0);
  _led_1_y_changed = false;
  xSemaphoreGive(_mutex_led_1_y);
}

bool is_led_1_y_changed() {
  xSemaphoreTake(_mutex_led_1_y, 0);
  bool v = _led_1_y_changed;
  xSemaphoreGive(_mutex_led_1_y);
  return v;
}



int get_led_1_y() {
  return geti(LED_1_Y);
}

void set_led_1_y(int value) {
  if (geti(LED_1_Y) == value) return;
  seti(LED_1_Y, value);
  xSemaphoreTake(_mutex_led_1_y, 0);
  _led_1_y_changed = true;
  xSemaphoreGive(_mutex_led_1_y);
}


static SemaphoreHandle_t _mutex_led_2_y; // TODO check RAM weight of creating so many semaphores :/
static bool _led_2_y_changed = true;

void reset_led_2_y_changed() {
  xSemaphoreTake(_mutex_led_2_y, 0);
  _led_2_y_changed = false;
  xSemaphoreGive(_mutex_led_2_y);
}

bool is_led_2_y_changed() {
  xSemaphoreTake(_mutex_led_2_y, 0);
  bool v = _led_2_y_changed;
  xSemaphoreGive(_mutex_led_2_y);
  return v;
}



int get_led_2_y() {
  return geti(LED_2_Y);
}

void set_led_2_y(int value) {
  if (geti(LED_2_Y) == value) return;
  seti(LED_2_Y, value);
  xSemaphoreTake(_mutex_led_2_y, 0);
  _led_2_y_changed = true;
  xSemaphoreGive(_mutex_led_2_y);
}


static SemaphoreHandle_t _mutex_led_3_y; // TODO check RAM weight of creating so many semaphores :/
static bool _led_3_y_changed = true;

void reset_led_3_y_changed() {
  xSemaphoreTake(_mutex_led_3_y, 0);
  _led_3_y_changed = false;
  xSemaphoreGive(_mutex_led_3_y);
}

bool is_led_3_y_changed() {
  xSemaphoreTake(_mutex_led_3_y, 0);
  bool v = _led_3_y_changed;
  xSemaphoreGive(_mutex_led_3_y);
  return v;
}



int get_led_3_y() {
  return geti(LED_3_Y);
}

void set_led_3_y(int value) {
  if (geti(LED_3_Y) == value) return;
  seti(LED_3_Y, value);
  xSemaphoreTake(_mutex_led_3_y, 0);
  _led_3_y_changed = true;
  xSemaphoreGive(_mutex_led_3_y);
}


static SemaphoreHandle_t _mutex_led_4_y; // TODO check RAM weight of creating so many semaphores :/
static bool _led_4_y_changed = true;

void reset_led_4_y_changed() {
  xSemaphoreTake(_mutex_led_4_y, 0);
  _led_4_y_changed = false;
  xSemaphoreGive(_mutex_led_4_y);
}

bool is_led_4_y_changed() {
  xSemaphoreTake(_mutex_led_4_y, 0);
  bool v = _led_4_y_changed;
  xSemaphoreGive(_mutex_led_4_y);
  return v;
}



int get_led_4_y() {
  return geti(LED_4_Y);
}

void set_led_4_y(int value) {
  if (geti(LED_4_Y) == value) return;
  seti(LED_4_Y, value);
  xSemaphoreTake(_mutex_led_4_y, 0);
  _led_4_y_changed = true;
  xSemaphoreGive(_mutex_led_4_y);
}


static SemaphoreHandle_t _mutex_led_5_y; // TODO check RAM weight of creating so many semaphores :/
static bool _led_5_y_changed = true;

void reset_led_5_y_changed() {
  xSemaphoreTake(_mutex_led_5_y, 0);
  _led_5_y_changed = false;
  xSemaphoreGive(_mutex_led_5_y);
}

bool is_led_5_y_changed() {
  xSemaphoreTake(_mutex_led_5_y, 0);
  bool v = _led_5_y_changed;
  xSemaphoreGive(_mutex_led_5_y);
  return v;
}



int get_led_5_y() {
  return geti(LED_5_Y);
}

void set_led_5_y(int value) {
  if (geti(LED_5_Y) == value) return;
  seti(LED_5_Y, value);
  xSemaphoreTake(_mutex_led_5_y, 0);
  _led_5_y_changed = true;
  xSemaphoreGive(_mutex_led_5_y);
}


static SemaphoreHandle_t _mutex_led_0_z; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_z_changed = true;

void reset_led_0_z_changed() {
  xSemaphoreTake(_mutex_led_0_z, 0);
  _led_0_z_changed = false;
  xSemaphoreGive(_mutex_led_0_z);
}

bool is_led_0_z_changed() {
  xSemaphoreTake(_mutex_led_0_z, 0);
  bool v = _led_0_z_changed;
  xSemaphoreGive(_mutex_led_0_z);
  return v;
}



int get_led_0_z() {
  return geti(LED_0_Z);
}

void set_led_0_z(int value) {
  if (geti(LED_0_Z) == value) return;
  seti(LED_0_Z, value);
  xSemaphoreTake(_mutex_led_0_z, 0);
  _led_0_z_changed = true;
  xSemaphoreGive(_mutex_led_0_z);
}


static SemaphoreHandle_t _mutex_led_1_z; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_z_changed = true;

void reset_led_1_z_changed() {
  xSemaphoreTake(_mutex_led_1_z, 0);
  _led_1_z_changed = false;
  xSemaphoreGive(_mutex_led_1_z);
}

bool is_led_1_z_changed() {
  xSemaphoreTake(_mutex_led_1_z, 0);
  bool v = _led_1_z_changed;
  xSemaphoreGive(_mutex_led_1_z);
  return v;
}



int get_led_1_z() {
  return geti(LED_1_Z);
}

void set_led_1_z(int value) {
  if (geti(LED_1_Z) == value) return;
  seti(LED_1_Z, value);
  xSemaphoreTake(_mutex_led_1_z, 0);
  _led_1_z_changed = true;
  xSemaphoreGive(_mutex_led_1_z);
}


static SemaphoreHandle_t _mutex_led_2_z; // TODO check RAM weight of creating so many semaphores :/
static bool _led_2_z_changed = true;

void reset_led_2_z_changed() {
  xSemaphoreTake(_mutex_led_2_z, 0);
  _led_2_z_changed = false;
  xSemaphoreGive(_mutex_led_2_z);
}

bool is_led_2_z_changed() {
  xSemaphoreTake(_mutex_led_2_z, 0);
  bool v = _led_2_z_changed;
  xSemaphoreGive(_mutex_led_2_z);
  return v;
}



int get_led_2_z() {
  return geti(LED_2_Z);
}

void set_led_2_z(int value) {
  if (geti(LED_2_Z) == value) return;
  seti(LED_2_Z, value);
  xSemaphoreTake(_mutex_led_2_z, 0);
  _led_2_z_changed = true;
  xSemaphoreGive(_mutex_led_2_z);
}


static SemaphoreHandle_t _mutex_led_3_z; // TODO check RAM weight of creating so many semaphores :/
static bool _led_3_z_changed = true;

void reset_led_3_z_changed() {
  xSemaphoreTake(_mutex_led_3_z, 0);
  _led_3_z_changed = false;
  xSemaphoreGive(_mutex_led_3_z);
}

bool is_led_3_z_changed() {
  xSemaphoreTake(_mutex_led_3_z, 0);
  bool v = _led_3_z_changed;
  xSemaphoreGive(_mutex_led_3_z);
  return v;
}



int get_led_3_z() {
  return geti(LED_3_Z);
}

void set_led_3_z(int value) {
  if (geti(LED_3_Z) == value) return;
  seti(LED_3_Z, value);
  xSemaphoreTake(_mutex_led_3_z, 0);
  _led_3_z_changed = true;
  xSemaphoreGive(_mutex_led_3_z);
}


static SemaphoreHandle_t _mutex_led_4_z; // TODO check RAM weight of creating so many semaphores :/
static bool _led_4_z_changed = true;

void reset_led_4_z_changed() {
  xSemaphoreTake(_mutex_led_4_z, 0);
  _led_4_z_changed = false;
  xSemaphoreGive(_mutex_led_4_z);
}

bool is_led_4_z_changed() {
  xSemaphoreTake(_mutex_led_4_z, 0);
  bool v = _led_4_z_changed;
  xSemaphoreGive(_mutex_led_4_z);
  return v;
}



int get_led_4_z() {
  return geti(LED_4_Z);
}

void set_led_4_z(int value) {
  if (geti(LED_4_Z) == value) return;
  seti(LED_4_Z, value);
  xSemaphoreTake(_mutex_led_4_z, 0);
  _led_4_z_changed = true;
  xSemaphoreGive(_mutex_led_4_z);
}


static SemaphoreHandle_t _mutex_led_5_z; // TODO check RAM weight of creating so many semaphores :/
static bool _led_5_z_changed = true;

void reset_led_5_z_changed() {
  xSemaphoreTake(_mutex_led_5_z, 0);
  _led_5_z_changed = false;
  xSemaphoreGive(_mutex_led_5_z);
}

bool is_led_5_z_changed() {
  xSemaphoreTake(_mutex_led_5_z, 0);
  bool v = _led_5_z_changed;
  xSemaphoreGive(_mutex_led_5_z);
  return v;
}



int get_led_5_z() {
  return geti(LED_5_Z);
}

void set_led_5_z(int value) {
  if (geti(LED_5_Z) == value) return;
  seti(LED_5_Z, value);
  xSemaphoreTake(_mutex_led_5_z, 0);
  _led_5_z_changed = true;
  xSemaphoreGive(_mutex_led_5_z);
}


static SemaphoreHandle_t _mutex_led_0_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_enabled_changed = true;

void reset_led_0_enabled_changed() {
  xSemaphoreTake(_mutex_led_0_enabled, 0);
  _led_0_enabled_changed = false;
  xSemaphoreGive(_mutex_led_0_enabled);
}

bool is_led_0_enabled_changed() {
  xSemaphoreTake(_mutex_led_0_enabled, 0);
  bool v = _led_0_enabled_changed;
  xSemaphoreGive(_mutex_led_0_enabled);
  return v;
}



int get_led_0_enabled() {
  return geti(LED_0_ENABLED);
}

void set_led_0_enabled(int value) {
  if (geti(LED_0_ENABLED) == value) return;
  seti(LED_0_ENABLED, value);
  xSemaphoreTake(_mutex_led_0_enabled, 0);
  _led_0_enabled_changed = true;
  xSemaphoreGive(_mutex_led_0_enabled);
}


static SemaphoreHandle_t _mutex_led_1_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_enabled_changed = true;

void reset_led_1_enabled_changed() {
  xSemaphoreTake(_mutex_led_1_enabled, 0);
  _led_1_enabled_changed = false;
  xSemaphoreGive(_mutex_led_1_enabled);
}

bool is_led_1_enabled_changed() {
  xSemaphoreTake(_mutex_led_1_enabled, 0);
  bool v = _led_1_enabled_changed;
  xSemaphoreGive(_mutex_led_1_enabled);
  return v;
}



int get_led_1_enabled() {
  return geti(LED_1_ENABLED);
}

void set_led_1_enabled(int value) {
  if (geti(LED_1_ENABLED) == value) return;
  seti(LED_1_ENABLED, value);
  xSemaphoreTake(_mutex_led_1_enabled, 0);
  _led_1_enabled_changed = true;
  xSemaphoreGive(_mutex_led_1_enabled);
}


static SemaphoreHandle_t _mutex_led_2_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _led_2_enabled_changed = true;

void reset_led_2_enabled_changed() {
  xSemaphoreTake(_mutex_led_2_enabled, 0);
  _led_2_enabled_changed = false;
  xSemaphoreGive(_mutex_led_2_enabled);
}

bool is_led_2_enabled_changed() {
  xSemaphoreTake(_mutex_led_2_enabled, 0);
  bool v = _led_2_enabled_changed;
  xSemaphoreGive(_mutex_led_2_enabled);
  return v;
}



int get_led_2_enabled() {
  return geti(LED_2_ENABLED);
}

void set_led_2_enabled(int value) {
  if (geti(LED_2_ENABLED) == value) return;
  seti(LED_2_ENABLED, value);
  xSemaphoreTake(_mutex_led_2_enabled, 0);
  _led_2_enabled_changed = true;
  xSemaphoreGive(_mutex_led_2_enabled);
}


static SemaphoreHandle_t _mutex_led_3_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _led_3_enabled_changed = true;

void reset_led_3_enabled_changed() {
  xSemaphoreTake(_mutex_led_3_enabled, 0);
  _led_3_enabled_changed = false;
  xSemaphoreGive(_mutex_led_3_enabled);
}

bool is_led_3_enabled_changed() {
  xSemaphoreTake(_mutex_led_3_enabled, 0);
  bool v = _led_3_enabled_changed;
  xSemaphoreGive(_mutex_led_3_enabled);
  return v;
}



int get_led_3_enabled() {
  return geti(LED_3_ENABLED);
}

void set_led_3_enabled(int value) {
  if (geti(LED_3_ENABLED) == value) return;
  seti(LED_3_ENABLED, value);
  xSemaphoreTake(_mutex_led_3_enabled, 0);
  _led_3_enabled_changed = true;
  xSemaphoreGive(_mutex_led_3_enabled);
}


static SemaphoreHandle_t _mutex_led_4_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _led_4_enabled_changed = true;

void reset_led_4_enabled_changed() {
  xSemaphoreTake(_mutex_led_4_enabled, 0);
  _led_4_enabled_changed = false;
  xSemaphoreGive(_mutex_led_4_enabled);
}

bool is_led_4_enabled_changed() {
  xSemaphoreTake(_mutex_led_4_enabled, 0);
  bool v = _led_4_enabled_changed;
  xSemaphoreGive(_mutex_led_4_enabled);
  return v;
}



int get_led_4_enabled() {
  return geti(LED_4_ENABLED);
}

void set_led_4_enabled(int value) {
  if (geti(LED_4_ENABLED) == value) return;
  seti(LED_4_ENABLED, value);
  xSemaphoreTake(_mutex_led_4_enabled, 0);
  _led_4_enabled_changed = true;
  xSemaphoreGive(_mutex_led_4_enabled);
}


static SemaphoreHandle_t _mutex_led_5_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _led_5_enabled_changed = true;

void reset_led_5_enabled_changed() {
  xSemaphoreTake(_mutex_led_5_enabled, 0);
  _led_5_enabled_changed = false;
  xSemaphoreGive(_mutex_led_5_enabled);
}

bool is_led_5_enabled_changed() {
  xSemaphoreTake(_mutex_led_5_enabled, 0);
  bool v = _led_5_enabled_changed;
  xSemaphoreGive(_mutex_led_5_enabled);
  return v;
}



int get_led_5_enabled() {
  return geti(LED_5_ENABLED);
}

void set_led_5_enabled(int value) {
  if (geti(LED_5_ENABLED) == value) return;
  seti(LED_5_ENABLED, value);
  xSemaphoreTake(_mutex_led_5_enabled, 0);
  _led_5_enabled_changed = true;
  xSemaphoreGive(_mutex_led_5_enabled);
}


static SemaphoreHandle_t _mutex_led_0_box; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_box_changed = true;

void reset_led_0_box_changed() {
  xSemaphoreTake(_mutex_led_0_box, 0);
  _led_0_box_changed = false;
  xSemaphoreGive(_mutex_led_0_box);
}

bool is_led_0_box_changed() {
  xSemaphoreTake(_mutex_led_0_box, 0);
  bool v = _led_0_box_changed;
  xSemaphoreGive(_mutex_led_0_box);
  return v;
}



int get_led_0_box() {
  return geti(LED_0_BOX);
}

void set_led_0_box(int value) {
  if (geti(LED_0_BOX) == value) return;
  seti(LED_0_BOX, value);
  xSemaphoreTake(_mutex_led_0_box, 0);
  _led_0_box_changed = true;
  xSemaphoreGive(_mutex_led_0_box);
}


static SemaphoreHandle_t _mutex_led_1_box; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_box_changed = true;

void reset_led_1_box_changed() {
  xSemaphoreTake(_mutex_led_1_box, 0);
  _led_1_box_changed = false;
  xSemaphoreGive(_mutex_led_1_box);
}

bool is_led_1_box_changed() {
  xSemaphoreTake(_mutex_led_1_box, 0);
  bool v = _led_1_box_changed;
  xSemaphoreGive(_mutex_led_1_box);
  return v;
}



int get_led_1_box() {
  return geti(LED_1_BOX);
}

void set_led_1_box(int value) {
  if (geti(LED_1_BOX) == value) return;
  seti(LED_1_BOX, value);
  xSemaphoreTake(_mutex_led_1_box, 0);
  _led_1_box_changed = true;
  xSemaphoreGive(_mutex_led_1_box);
}


static SemaphoreHandle_t _mutex_led_2_box; // TODO check RAM weight of creating so many semaphores :/
static bool _led_2_box_changed = true;

void reset_led_2_box_changed() {
  xSemaphoreTake(_mutex_led_2_box, 0);
  _led_2_box_changed = false;
  xSemaphoreGive(_mutex_led_2_box);
}

bool is_led_2_box_changed() {
  xSemaphoreTake(_mutex_led_2_box, 0);
  bool v = _led_2_box_changed;
  xSemaphoreGive(_mutex_led_2_box);
  return v;
}



int get_led_2_box() {
  return geti(LED_2_BOX);
}

void set_led_2_box(int value) {
  if (geti(LED_2_BOX) == value) return;
  seti(LED_2_BOX, value);
  xSemaphoreTake(_mutex_led_2_box, 0);
  _led_2_box_changed = true;
  xSemaphoreGive(_mutex_led_2_box);
}


static SemaphoreHandle_t _mutex_led_3_box; // TODO check RAM weight of creating so many semaphores :/
static bool _led_3_box_changed = true;

void reset_led_3_box_changed() {
  xSemaphoreTake(_mutex_led_3_box, 0);
  _led_3_box_changed = false;
  xSemaphoreGive(_mutex_led_3_box);
}

bool is_led_3_box_changed() {
  xSemaphoreTake(_mutex_led_3_box, 0);
  bool v = _led_3_box_changed;
  xSemaphoreGive(_mutex_led_3_box);
  return v;
}



int get_led_3_box() {
  return geti(LED_3_BOX);
}

void set_led_3_box(int value) {
  if (geti(LED_3_BOX) == value) return;
  seti(LED_3_BOX, value);
  xSemaphoreTake(_mutex_led_3_box, 0);
  _led_3_box_changed = true;
  xSemaphoreGive(_mutex_led_3_box);
}


static SemaphoreHandle_t _mutex_led_4_box; // TODO check RAM weight of creating so many semaphores :/
static bool _led_4_box_changed = true;

void reset_led_4_box_changed() {
  xSemaphoreTake(_mutex_led_4_box, 0);
  _led_4_box_changed = false;
  xSemaphoreGive(_mutex_led_4_box);
}

bool is_led_4_box_changed() {
  xSemaphoreTake(_mutex_led_4_box, 0);
  bool v = _led_4_box_changed;
  xSemaphoreGive(_mutex_led_4_box);
  return v;
}



int get_led_4_box() {
  return geti(LED_4_BOX);
}

void set_led_4_box(int value) {
  if (geti(LED_4_BOX) == value) return;
  seti(LED_4_BOX, value);
  xSemaphoreTake(_mutex_led_4_box, 0);
  _led_4_box_changed = true;
  xSemaphoreGive(_mutex_led_4_box);
}


static SemaphoreHandle_t _mutex_led_5_box; // TODO check RAM weight of creating so many semaphores :/
static bool _led_5_box_changed = true;

void reset_led_5_box_changed() {
  xSemaphoreTake(_mutex_led_5_box, 0);
  _led_5_box_changed = false;
  xSemaphoreGive(_mutex_led_5_box);
}

bool is_led_5_box_changed() {
  xSemaphoreTake(_mutex_led_5_box, 0);
  bool v = _led_5_box_changed;
  xSemaphoreGive(_mutex_led_5_box);
  return v;
}



int get_led_5_box() {
  return geti(LED_5_BOX);
}

void set_led_5_box(int value) {
  if (geti(LED_5_BOX) == value) return;
  seti(LED_5_BOX, value);
  xSemaphoreTake(_mutex_led_5_box, 0);
  _led_5_box_changed = true;
  xSemaphoreGive(_mutex_led_5_box);
}


static SemaphoreHandle_t _mutex_led_0_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_dim_changed = true;

void reset_led_0_dim_changed() {
  xSemaphoreTake(_mutex_led_0_dim, 0);
  _led_0_dim_changed = false;
  xSemaphoreGive(_mutex_led_0_dim);
}

bool is_led_0_dim_changed() {
  xSemaphoreTake(_mutex_led_0_dim, 0);
  bool v = _led_0_dim_changed;
  xSemaphoreGive(_mutex_led_0_dim);
  return v;
}



int get_led_0_dim() {
  return geti(LED_0_DIM);
}

void set_led_0_dim(int value) {
  if (geti(LED_0_DIM) == value) return;
  seti(LED_0_DIM, value);
  xSemaphoreTake(_mutex_led_0_dim, 0);
  _led_0_dim_changed = true;
  xSemaphoreGive(_mutex_led_0_dim);
}


static SemaphoreHandle_t _mutex_led_1_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_dim_changed = true;

void reset_led_1_dim_changed() {
  xSemaphoreTake(_mutex_led_1_dim, 0);
  _led_1_dim_changed = false;
  xSemaphoreGive(_mutex_led_1_dim);
}

bool is_led_1_dim_changed() {
  xSemaphoreTake(_mutex_led_1_dim, 0);
  bool v = _led_1_dim_changed;
  xSemaphoreGive(_mutex_led_1_dim);
  return v;
}



int get_led_1_dim() {
  return geti(LED_1_DIM);
}

void set_led_1_dim(int value) {
  if (geti(LED_1_DIM) == value) return;
  seti(LED_1_DIM, value);
  xSemaphoreTake(_mutex_led_1_dim, 0);
  _led_1_dim_changed = true;
  xSemaphoreGive(_mutex_led_1_dim);
}


static SemaphoreHandle_t _mutex_led_2_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _led_2_dim_changed = true;

void reset_led_2_dim_changed() {
  xSemaphoreTake(_mutex_led_2_dim, 0);
  _led_2_dim_changed = false;
  xSemaphoreGive(_mutex_led_2_dim);
}

bool is_led_2_dim_changed() {
  xSemaphoreTake(_mutex_led_2_dim, 0);
  bool v = _led_2_dim_changed;
  xSemaphoreGive(_mutex_led_2_dim);
  return v;
}



int get_led_2_dim() {
  return geti(LED_2_DIM);
}

void set_led_2_dim(int value) {
  if (geti(LED_2_DIM) == value) return;
  seti(LED_2_DIM, value);
  xSemaphoreTake(_mutex_led_2_dim, 0);
  _led_2_dim_changed = true;
  xSemaphoreGive(_mutex_led_2_dim);
}


static SemaphoreHandle_t _mutex_led_3_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _led_3_dim_changed = true;

void reset_led_3_dim_changed() {
  xSemaphoreTake(_mutex_led_3_dim, 0);
  _led_3_dim_changed = false;
  xSemaphoreGive(_mutex_led_3_dim);
}

bool is_led_3_dim_changed() {
  xSemaphoreTake(_mutex_led_3_dim, 0);
  bool v = _led_3_dim_changed;
  xSemaphoreGive(_mutex_led_3_dim);
  return v;
}



int get_led_3_dim() {
  return geti(LED_3_DIM);
}

void set_led_3_dim(int value) {
  if (geti(LED_3_DIM) == value) return;
  seti(LED_3_DIM, value);
  xSemaphoreTake(_mutex_led_3_dim, 0);
  _led_3_dim_changed = true;
  xSemaphoreGive(_mutex_led_3_dim);
}


static SemaphoreHandle_t _mutex_led_4_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _led_4_dim_changed = true;

void reset_led_4_dim_changed() {
  xSemaphoreTake(_mutex_led_4_dim, 0);
  _led_4_dim_changed = false;
  xSemaphoreGive(_mutex_led_4_dim);
}

bool is_led_4_dim_changed() {
  xSemaphoreTake(_mutex_led_4_dim, 0);
  bool v = _led_4_dim_changed;
  xSemaphoreGive(_mutex_led_4_dim);
  return v;
}



int get_led_4_dim() {
  return geti(LED_4_DIM);
}

void set_led_4_dim(int value) {
  if (geti(LED_4_DIM) == value) return;
  seti(LED_4_DIM, value);
  xSemaphoreTake(_mutex_led_4_dim, 0);
  _led_4_dim_changed = true;
  xSemaphoreGive(_mutex_led_4_dim);
}


static SemaphoreHandle_t _mutex_led_5_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _led_5_dim_changed = true;

void reset_led_5_dim_changed() {
  xSemaphoreTake(_mutex_led_5_dim, 0);
  _led_5_dim_changed = false;
  xSemaphoreGive(_mutex_led_5_dim);
}

bool is_led_5_dim_changed() {
  xSemaphoreTake(_mutex_led_5_dim, 0);
  bool v = _led_5_dim_changed;
  xSemaphoreGive(_mutex_led_5_dim);
  return v;
}



int get_led_5_dim() {
  return geti(LED_5_DIM);
}

void set_led_5_dim(int value) {
  if (geti(LED_5_DIM) == value) return;
  seti(LED_5_DIM, value);
  xSemaphoreTake(_mutex_led_5_dim, 0);
  _led_5_dim_changed = true;
  xSemaphoreGive(_mutex_led_5_dim);
}


void init_helpers() {
  _mutex_wifi_status = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_wifi_ssid = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_wifi_password = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_time = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_n_restarts = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_timestamp = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_server_ip = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_server_hostname = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_server_port = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_version_filename = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_filename = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_broker_url = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_0_sda = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_0_scl = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_0_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_1_sda = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_1_scl = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_1_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_state = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_device_name = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_timer_type = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_timer_output = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_started_at = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_on_hour = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_on_min = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_off_hour = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_off_min = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_stretch = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_led_dim = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_blower = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_blower_mode = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_blower_gpio = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_blower_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_sht1x_temp_c = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_sht1x_temp_f = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_sht1x_humi = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_arduino_co2 = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_dust_gpy2y10 = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_led_info = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_timer_type = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_timer_output = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_started_at = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_on_hour = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_on_min = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_off_hour = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_off_min = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_stretch = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_led_dim = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_blower = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_blower_mode = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_blower_gpio = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_blower_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_sht1x_temp_c = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_sht1x_temp_f = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_sht1x_humi = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_arduino_co2 = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_dust_gpy2y10 = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_led_info = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_timer_type = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_timer_output = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_started_at = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_on_hour = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_on_min = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_off_hour = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_off_min = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_stretch = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_led_dim = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_blower = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_blower_mode = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_blower_gpio = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_blower_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_sht1x_temp_c = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_sht1x_temp_f = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_sht1x_humi = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_arduino_co2 = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_dust_gpy2y10 = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_2_led_info = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_duty = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_duty = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_2_duty = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_3_duty = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_4_duty = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_5_duty = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_gpio = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_gpio = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_2_gpio = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_3_gpio = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_4_gpio = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_5_gpio = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_x = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_x = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_2_x = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_3_x = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_4_x = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_5_x = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_y = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_y = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_2_y = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_3_y = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_4_y = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_5_y = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_z = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_z = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_2_z = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_3_z = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_4_z = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_5_z = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_2_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_3_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_4_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_5_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_box = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_box = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_2_box = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_3_box = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_4_box = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_5_box = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_dim = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_dim = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_2_dim = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_3_dim = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_4_dim = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_5_dim = xSemaphoreCreateMutexStatic(&mutex_buffer);
}

/*
 * [/GENERATED]
 */
