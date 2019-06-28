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
static bool _wifi_status_undefined = true;

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

bool is_wifi_status_undefined() {
  xSemaphoreTake(_mutex_wifi_status, 0);
  bool v = _wifi_status_undefined;
  xSemaphoreGive(_mutex_wifi_status);
  return v;
}


static int _wifi_status = INT_MAX;

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
  _wifi_status_undefined = false;
  xSemaphoreGive(_mutex_wifi_status);
  set_attr_value_and_notify(IDX_CHAR_VAL_WIFI_STATUS, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_wifi_ssid; // TODO check RAM weight of creating so many semaphores :/
static bool _wifi_ssid_changed = true;
static bool _wifi_ssid_undefined = true;

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

bool is_wifi_ssid_undefined() {
  xSemaphoreTake(_mutex_wifi_ssid, 0);
  bool v = _wifi_ssid_undefined;
  xSemaphoreGive(_mutex_wifi_ssid);
  return v;
}




void get_wifi_ssid(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(WIFI_SSID, dest, len);
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
static bool _wifi_password_undefined = true;

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

bool is_wifi_password_undefined() {
  xSemaphoreTake(_mutex_wifi_password, 0);
  bool v = _wifi_password_undefined;
  xSemaphoreGive(_mutex_wifi_password);
  return v;
}




void get_wifi_password(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(WIFI_PASSWORD, dest, len);
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

static SemaphoreHandle_t _mutex_wifi_ap_ssid; // TODO check RAM weight of creating so many semaphores :/
static bool _wifi_ap_ssid_changed = true;
static bool _wifi_ap_ssid_undefined = true;

void reset_wifi_ap_ssid_changed() {
  xSemaphoreTake(_mutex_wifi_ap_ssid, 0);
  _wifi_ap_ssid_changed = false;
  xSemaphoreGive(_mutex_wifi_ap_ssid);
}

bool is_wifi_ap_ssid_changed() {
  xSemaphoreTake(_mutex_wifi_ap_ssid, 0);
  bool v = _wifi_ap_ssid_changed;
  xSemaphoreGive(_mutex_wifi_ap_ssid);
  return v;
}

bool is_wifi_ap_ssid_undefined() {
  xSemaphoreTake(_mutex_wifi_ap_ssid, 0);
  bool v = _wifi_ap_ssid_undefined;
  xSemaphoreGive(_mutex_wifi_ap_ssid);
  return v;
}




void get_wifi_ap_ssid(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(WIFI_AP_SSID, dest, len);
}

void set_wifi_ap_ssid(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(WIFI_AP_SSID, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(WIFI_AP_SSID, value);
  xSemaphoreTake(_mutex_wifi_ap_ssid, 0);
  _wifi_ap_ssid_changed = true;
  xSemaphoreGive(_mutex_wifi_ap_ssid);
}

static SemaphoreHandle_t _mutex_wifi_ap_password; // TODO check RAM weight of creating so many semaphores :/
static bool _wifi_ap_password_changed = true;
static bool _wifi_ap_password_undefined = true;

void reset_wifi_ap_password_changed() {
  xSemaphoreTake(_mutex_wifi_ap_password, 0);
  _wifi_ap_password_changed = false;
  xSemaphoreGive(_mutex_wifi_ap_password);
}

bool is_wifi_ap_password_changed() {
  xSemaphoreTake(_mutex_wifi_ap_password, 0);
  bool v = _wifi_ap_password_changed;
  xSemaphoreGive(_mutex_wifi_ap_password);
  return v;
}

bool is_wifi_ap_password_undefined() {
  xSemaphoreTake(_mutex_wifi_ap_password, 0);
  bool v = _wifi_ap_password_undefined;
  xSemaphoreGive(_mutex_wifi_ap_password);
  return v;
}




void get_wifi_ap_password(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(WIFI_AP_PASSWORD, dest, len);
}

void set_wifi_ap_password(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(WIFI_AP_PASSWORD, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(WIFI_AP_PASSWORD, value);
  xSemaphoreTake(_mutex_wifi_ap_password, 0);
  _wifi_ap_password_changed = true;
  xSemaphoreGive(_mutex_wifi_ap_password);
}

static SemaphoreHandle_t _mutex_mdns_domain; // TODO check RAM weight of creating so many semaphores :/
static bool _mdns_domain_changed = true;
static bool _mdns_domain_undefined = true;

void reset_mdns_domain_changed() {
  xSemaphoreTake(_mutex_mdns_domain, 0);
  _mdns_domain_changed = false;
  xSemaphoreGive(_mutex_mdns_domain);
}

bool is_mdns_domain_changed() {
  xSemaphoreTake(_mutex_mdns_domain, 0);
  bool v = _mdns_domain_changed;
  xSemaphoreGive(_mutex_mdns_domain);
  return v;
}

bool is_mdns_domain_undefined() {
  xSemaphoreTake(_mutex_mdns_domain, 0);
  bool v = _mdns_domain_undefined;
  xSemaphoreGive(_mutex_mdns_domain);
  return v;
}




void get_mdns_domain(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(MDNS_DOMAIN, dest, len);
}

void set_mdns_domain(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(MDNS_DOMAIN, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(MDNS_DOMAIN, value);
  xSemaphoreTake(_mutex_mdns_domain, 0);
  _mdns_domain_changed = true;
  xSemaphoreGive(_mutex_mdns_domain);
}

static SemaphoreHandle_t _mutex_wifi_ip; // TODO check RAM weight of creating so many semaphores :/
static bool _wifi_ip_changed = true;
static bool _wifi_ip_undefined = true;

void reset_wifi_ip_changed() {
  xSemaphoreTake(_mutex_wifi_ip, 0);
  _wifi_ip_changed = false;
  xSemaphoreGive(_mutex_wifi_ip);
}

bool is_wifi_ip_changed() {
  xSemaphoreTake(_mutex_wifi_ip, 0);
  bool v = _wifi_ip_changed;
  xSemaphoreGive(_mutex_wifi_ip);
  return v;
}

bool is_wifi_ip_undefined() {
  xSemaphoreTake(_mutex_wifi_ip, 0);
  bool v = _wifi_ip_undefined;
  xSemaphoreGive(_mutex_wifi_ip);
  return v;
}




void get_wifi_ip(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(WIFI_IP, dest, len);
}

void set_wifi_ip(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(WIFI_IP, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(WIFI_IP, value);
  xSemaphoreTake(_mutex_wifi_ip, 0);
  _wifi_ip_changed = true;
  xSemaphoreGive(_mutex_wifi_ip);
  set_attr_value_and_notify(IDX_CHAR_VAL_WIFI_IP, (uint8_t *)value, strlen(value));
}

static SemaphoreHandle_t _mutex_time; // TODO check RAM weight of creating so many semaphores :/
static bool _time_changed = true;
static bool _time_undefined = true;

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

bool is_time_undefined() {
  xSemaphoreTake(_mutex_time, 0);
  bool v = _time_undefined;
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
  _time_undefined = false;
  xSemaphoreGive(_mutex_time);
  set_attr_value_and_notify(IDX_CHAR_VAL_TIME, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_n_restarts; // TODO check RAM weight of creating so many semaphores :/
static bool _n_restarts_changed = true;
static bool _n_restarts_undefined = true;

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

bool is_n_restarts_undefined() {
  xSemaphoreTake(_mutex_n_restarts, 0);
  bool v = _n_restarts_undefined;
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
  _n_restarts_undefined = false;
  xSemaphoreGive(_mutex_n_restarts);
}


static SemaphoreHandle_t _mutex_ota_timestamp; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_timestamp_changed = true;
static bool _ota_timestamp_undefined = true;

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

bool is_ota_timestamp_undefined() {
  xSemaphoreTake(_mutex_ota_timestamp, 0);
  bool v = _ota_timestamp_undefined;
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
  _ota_timestamp_undefined = false;
  xSemaphoreGive(_mutex_ota_timestamp);
}


static SemaphoreHandle_t _mutex_ota_server_ip; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_server_ip_changed = true;
static bool _ota_server_ip_undefined = true;

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

bool is_ota_server_ip_undefined() {
  xSemaphoreTake(_mutex_ota_server_ip, 0);
  bool v = _ota_server_ip_undefined;
  xSemaphoreGive(_mutex_ota_server_ip);
  return v;
}




void get_ota_server_ip(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_IP, dest, len);
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
static bool _ota_server_hostname_undefined = true;

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

bool is_ota_server_hostname_undefined() {
  xSemaphoreTake(_mutex_ota_server_hostname, 0);
  bool v = _ota_server_hostname_undefined;
  xSemaphoreGive(_mutex_ota_server_hostname);
  return v;
}




void get_ota_server_hostname(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_HOSTNAME, dest, len);
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
static bool _ota_server_port_undefined = true;

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

bool is_ota_server_port_undefined() {
  xSemaphoreTake(_mutex_ota_server_port, 0);
  bool v = _ota_server_port_undefined;
  xSemaphoreGive(_mutex_ota_server_port);
  return v;
}




void get_ota_server_port(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_SERVER_PORT, dest, len);
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

static SemaphoreHandle_t _mutex_ota_basedir; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_basedir_changed = true;
static bool _ota_basedir_undefined = true;

void reset_ota_basedir_changed() {
  xSemaphoreTake(_mutex_ota_basedir, 0);
  _ota_basedir_changed = false;
  xSemaphoreGive(_mutex_ota_basedir);
}

bool is_ota_basedir_changed() {
  xSemaphoreTake(_mutex_ota_basedir, 0);
  bool v = _ota_basedir_changed;
  xSemaphoreGive(_mutex_ota_basedir);
  return v;
}

bool is_ota_basedir_undefined() {
  xSemaphoreTake(_mutex_ota_basedir, 0);
  bool v = _ota_basedir_undefined;
  xSemaphoreGive(_mutex_ota_basedir);
  return v;
}




void get_ota_basedir(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(OTA_BASEDIR, dest, len);
}

void set_ota_basedir(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(OTA_BASEDIR, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(OTA_BASEDIR, value);
  xSemaphoreTake(_mutex_ota_basedir, 0);
  _ota_basedir_changed = true;
  xSemaphoreGive(_mutex_ota_basedir);
}

static SemaphoreHandle_t _mutex_ota_status; // TODO check RAM weight of creating so many semaphores :/
static bool _ota_status_changed = true;
static bool _ota_status_undefined = true;

void reset_ota_status_changed() {
  xSemaphoreTake(_mutex_ota_status, 0);
  _ota_status_changed = false;
  xSemaphoreGive(_mutex_ota_status);
}

bool is_ota_status_changed() {
  xSemaphoreTake(_mutex_ota_status, 0);
  bool v = _ota_status_changed;
  xSemaphoreGive(_mutex_ota_status);
  return v;
}

bool is_ota_status_undefined() {
  xSemaphoreTake(_mutex_ota_status, 0);
  bool v = _ota_status_undefined;
  xSemaphoreGive(_mutex_ota_status);
  return v;
}


static int _ota_status = INT_MAX;

int get_ota_status() {
  xSemaphoreTake(_mutex_ota_status, 0);
  int v = _ota_status;
  xSemaphoreGive(_mutex_ota_status);
  return v;
}

void set_ota_status(int value) {
  xSemaphoreTake(_mutex_ota_status, 0);
  if (_ota_status == value) return;
  _ota_status = value;
  _ota_status_changed = true;
  _ota_status_undefined = false;
  xSemaphoreGive(_mutex_ota_status);
}


static SemaphoreHandle_t _mutex_broker_url; // TODO check RAM weight of creating so many semaphores :/
static bool _broker_url_changed = true;
static bool _broker_url_undefined = true;

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

bool is_broker_url_undefined() {
  xSemaphoreTake(_mutex_broker_url, 0);
  bool v = _broker_url_undefined;
  xSemaphoreGive(_mutex_broker_url);
  return v;
}




void get_broker_url(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(BROKER_URL, dest, len);
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

static SemaphoreHandle_t _mutex_broker_channel; // TODO check RAM weight of creating so many semaphores :/
static bool _broker_channel_changed = true;
static bool _broker_channel_undefined = true;

void reset_broker_channel_changed() {
  xSemaphoreTake(_mutex_broker_channel, 0);
  _broker_channel_changed = false;
  xSemaphoreGive(_mutex_broker_channel);
}

bool is_broker_channel_changed() {
  xSemaphoreTake(_mutex_broker_channel, 0);
  bool v = _broker_channel_changed;
  xSemaphoreGive(_mutex_broker_channel);
  return v;
}

bool is_broker_channel_undefined() {
  xSemaphoreTake(_mutex_broker_channel, 0);
  bool v = _broker_channel_undefined;
  xSemaphoreGive(_mutex_broker_channel);
  return v;
}




void get_broker_channel(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(BROKER_CHANNEL, dest, len);
}

void set_broker_channel(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(BROKER_CHANNEL, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(BROKER_CHANNEL, value);
  xSemaphoreTake(_mutex_broker_channel, 0);
  _broker_channel_changed = true;
  xSemaphoreGive(_mutex_broker_channel);
}

static SemaphoreHandle_t _mutex_broker_clientid; // TODO check RAM weight of creating so many semaphores :/
static bool _broker_clientid_changed = true;
static bool _broker_clientid_undefined = true;

void reset_broker_clientid_changed() {
  xSemaphoreTake(_mutex_broker_clientid, 0);
  _broker_clientid_changed = false;
  xSemaphoreGive(_mutex_broker_clientid);
}

bool is_broker_clientid_changed() {
  xSemaphoreTake(_mutex_broker_clientid, 0);
  bool v = _broker_clientid_changed;
  xSemaphoreGive(_mutex_broker_clientid);
  return v;
}

bool is_broker_clientid_undefined() {
  xSemaphoreTake(_mutex_broker_clientid, 0);
  bool v = _broker_clientid_undefined;
  xSemaphoreGive(_mutex_broker_clientid);
  return v;
}




void get_broker_clientid(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(BROKER_CLIENTID, dest, len);
}

void set_broker_clientid(const char *value) {
  assert(strlen(value) <= MAX_KVALUE_SIZE - 1);
  char old_value[MAX_KVALUE_SIZE] = {0};
  getstr(BROKER_CLIENTID, old_value, MAX_KVALUE_SIZE - 1);
  if (!strcmp(old_value, value)) return;
  setstr(BROKER_CLIENTID, value);
  xSemaphoreTake(_mutex_broker_clientid, 0);
  _broker_clientid_changed = true;
  xSemaphoreGive(_mutex_broker_clientid);
}

static SemaphoreHandle_t _mutex_i2c_0_sda; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_0_sda_changed = true;
static bool _i2c_0_sda_undefined = true;

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

bool is_i2c_0_sda_undefined() {
  xSemaphoreTake(_mutex_i2c_0_sda, 0);
  bool v = _i2c_0_sda_undefined;
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
  _i2c_0_sda_undefined = false;
  xSemaphoreGive(_mutex_i2c_0_sda);
}


static SemaphoreHandle_t _mutex_i2c_0_scl; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_0_scl_changed = true;
static bool _i2c_0_scl_undefined = true;

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

bool is_i2c_0_scl_undefined() {
  xSemaphoreTake(_mutex_i2c_0_scl, 0);
  bool v = _i2c_0_scl_undefined;
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
  _i2c_0_scl_undefined = false;
  xSemaphoreGive(_mutex_i2c_0_scl);
}


static SemaphoreHandle_t _mutex_i2c_0_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_0_enabled_changed = true;
static bool _i2c_0_enabled_undefined = true;

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

bool is_i2c_0_enabled_undefined() {
  xSemaphoreTake(_mutex_i2c_0_enabled, 0);
  bool v = _i2c_0_enabled_undefined;
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
  _i2c_0_enabled_undefined = false;
  xSemaphoreGive(_mutex_i2c_0_enabled);
}


static SemaphoreHandle_t _mutex_i2c_1_sda; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_1_sda_changed = true;
static bool _i2c_1_sda_undefined = true;

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

bool is_i2c_1_sda_undefined() {
  xSemaphoreTake(_mutex_i2c_1_sda, 0);
  bool v = _i2c_1_sda_undefined;
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
  _i2c_1_sda_undefined = false;
  xSemaphoreGive(_mutex_i2c_1_sda);
}


static SemaphoreHandle_t _mutex_i2c_1_scl; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_1_scl_changed = true;
static bool _i2c_1_scl_undefined = true;

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

bool is_i2c_1_scl_undefined() {
  xSemaphoreTake(_mutex_i2c_1_scl, 0);
  bool v = _i2c_1_scl_undefined;
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
  _i2c_1_scl_undefined = false;
  xSemaphoreGive(_mutex_i2c_1_scl);
}


static SemaphoreHandle_t _mutex_i2c_1_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _i2c_1_enabled_changed = true;
static bool _i2c_1_enabled_undefined = true;

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

bool is_i2c_1_enabled_undefined() {
  xSemaphoreTake(_mutex_i2c_1_enabled, 0);
  bool v = _i2c_1_enabled_undefined;
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
  _i2c_1_enabled_undefined = false;
  xSemaphoreGive(_mutex_i2c_1_enabled);
}


static SemaphoreHandle_t _mutex_reboot; // TODO check RAM weight of creating so many semaphores :/
static bool _reboot_changed = true;
static bool _reboot_undefined = true;

void reset_reboot_changed() {
  xSemaphoreTake(_mutex_reboot, 0);
  _reboot_changed = false;
  xSemaphoreGive(_mutex_reboot);
}

bool is_reboot_changed() {
  xSemaphoreTake(_mutex_reboot, 0);
  bool v = _reboot_changed;
  xSemaphoreGive(_mutex_reboot);
  return v;
}

bool is_reboot_undefined() {
  xSemaphoreTake(_mutex_reboot, 0);
  bool v = _reboot_undefined;
  xSemaphoreGive(_mutex_reboot);
  return v;
}


static int _reboot = INT_MAX;

int get_reboot() {
  xSemaphoreTake(_mutex_reboot, 0);
  int v = _reboot;
  xSemaphoreGive(_mutex_reboot);
  return v;
}

void set_reboot(int value) {
  xSemaphoreTake(_mutex_reboot, 0);
  if (_reboot == value) return;
  _reboot = value;
  _reboot_changed = true;
  _reboot_undefined = false;
  xSemaphoreGive(_mutex_reboot);
}


static SemaphoreHandle_t _mutex_state; // TODO check RAM weight of creating so many semaphores :/
static bool _state_changed = true;
static bool _state_undefined = true;

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

bool is_state_undefined() {
  xSemaphoreTake(_mutex_state, 0);
  bool v = _state_undefined;
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
  _state_undefined = false;
  xSemaphoreGive(_mutex_state);
  set_attr_value_and_notify(IDX_CHAR_VAL_STATE, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_device_name; // TODO check RAM weight of creating so many semaphores :/
static bool _device_name_changed = true;
static bool _device_name_undefined = true;

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

bool is_device_name_undefined() {
  xSemaphoreTake(_mutex_device_name, 0);
  bool v = _device_name_undefined;
  xSemaphoreGive(_mutex_device_name);
  return v;
}




void get_device_name(char *dest, size_t len) {
  assert(len <= MAX_KVALUE_SIZE - 1);
  getstr(DEVICE_NAME, dest, len);
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

static SemaphoreHandle_t _mutex_status_led_red_gpio; // TODO check RAM weight of creating so many semaphores :/
static bool _status_led_red_gpio_changed = true;
static bool _status_led_red_gpio_undefined = true;

void reset_status_led_red_gpio_changed() {
  xSemaphoreTake(_mutex_status_led_red_gpio, 0);
  _status_led_red_gpio_changed = false;
  xSemaphoreGive(_mutex_status_led_red_gpio);
}

bool is_status_led_red_gpio_changed() {
  xSemaphoreTake(_mutex_status_led_red_gpio, 0);
  bool v = _status_led_red_gpio_changed;
  xSemaphoreGive(_mutex_status_led_red_gpio);
  return v;
}

bool is_status_led_red_gpio_undefined() {
  xSemaphoreTake(_mutex_status_led_red_gpio, 0);
  bool v = _status_led_red_gpio_undefined;
  xSemaphoreGive(_mutex_status_led_red_gpio);
  return v;
}



int get_status_led_red_gpio() {
  return geti(STATUS_LED_RED_GPIO);
}

void set_status_led_red_gpio(int value) {
  if (geti(STATUS_LED_RED_GPIO) == value) return;
  seti(STATUS_LED_RED_GPIO, value);
  xSemaphoreTake(_mutex_status_led_red_gpio, 0);
  _status_led_red_gpio_changed = true;
  _status_led_red_gpio_undefined = false;
  xSemaphoreGive(_mutex_status_led_red_gpio);
}


static SemaphoreHandle_t _mutex_status_led_green_gpio; // TODO check RAM weight of creating so many semaphores :/
static bool _status_led_green_gpio_changed = true;
static bool _status_led_green_gpio_undefined = true;

void reset_status_led_green_gpio_changed() {
  xSemaphoreTake(_mutex_status_led_green_gpio, 0);
  _status_led_green_gpio_changed = false;
  xSemaphoreGive(_mutex_status_led_green_gpio);
}

bool is_status_led_green_gpio_changed() {
  xSemaphoreTake(_mutex_status_led_green_gpio, 0);
  bool v = _status_led_green_gpio_changed;
  xSemaphoreGive(_mutex_status_led_green_gpio);
  return v;
}

bool is_status_led_green_gpio_undefined() {
  xSemaphoreTake(_mutex_status_led_green_gpio, 0);
  bool v = _status_led_green_gpio_undefined;
  xSemaphoreGive(_mutex_status_led_green_gpio);
  return v;
}



int get_status_led_green_gpio() {
  return geti(STATUS_LED_GREEN_GPIO);
}

void set_status_led_green_gpio(int value) {
  if (geti(STATUS_LED_GREEN_GPIO) == value) return;
  seti(STATUS_LED_GREEN_GPIO, value);
  xSemaphoreTake(_mutex_status_led_green_gpio, 0);
  _status_led_green_gpio_changed = true;
  _status_led_green_gpio_undefined = false;
  xSemaphoreGive(_mutex_status_led_green_gpio);
}


static SemaphoreHandle_t _mutex_status_led_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _status_led_dim_changed = true;
static bool _status_led_dim_undefined = true;

void reset_status_led_dim_changed() {
  xSemaphoreTake(_mutex_status_led_dim, 0);
  _status_led_dim_changed = false;
  xSemaphoreGive(_mutex_status_led_dim);
}

bool is_status_led_dim_changed() {
  xSemaphoreTake(_mutex_status_led_dim, 0);
  bool v = _status_led_dim_changed;
  xSemaphoreGive(_mutex_status_led_dim);
  return v;
}

bool is_status_led_dim_undefined() {
  xSemaphoreTake(_mutex_status_led_dim, 0);
  bool v = _status_led_dim_undefined;
  xSemaphoreGive(_mutex_status_led_dim);
  return v;
}



int get_status_led_dim() {
  return geti(STATUS_LED_DIM);
}

void set_status_led_dim(int value) {
  if (geti(STATUS_LED_DIM) == value) return;
  seti(STATUS_LED_DIM, value);
  xSemaphoreTake(_mutex_status_led_dim, 0);
  _status_led_dim_changed = true;
  _status_led_dim_undefined = false;
  xSemaphoreGive(_mutex_status_led_dim);
}


static SemaphoreHandle_t _mutex_box_0_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_enabled_changed = true;
static bool _box_0_enabled_undefined = true;

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

bool is_box_0_enabled_undefined() {
  xSemaphoreTake(_mutex_box_0_enabled, 0);
  bool v = _box_0_enabled_undefined;
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
  _box_0_enabled_undefined = false;
  xSemaphoreGive(_mutex_box_0_enabled);
}


static SemaphoreHandle_t _mutex_box_0_timer_type; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_timer_type_changed = true;
static bool _box_0_timer_type_undefined = true;

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

bool is_box_0_timer_type_undefined() {
  xSemaphoreTake(_mutex_box_0_timer_type, 0);
  bool v = _box_0_timer_type_undefined;
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
  _box_0_timer_type_undefined = false;
  xSemaphoreGive(_mutex_box_0_timer_type);
}


static SemaphoreHandle_t _mutex_box_0_timer_output; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_timer_output_changed = true;
static bool _box_0_timer_output_undefined = true;

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

bool is_box_0_timer_output_undefined() {
  xSemaphoreTake(_mutex_box_0_timer_output, 0);
  bool v = _box_0_timer_output_undefined;
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
  _box_0_timer_output_undefined = false;
  xSemaphoreGive(_mutex_box_0_timer_output);
}


static SemaphoreHandle_t _mutex_box_0_started_at; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_started_at_changed = true;
static bool _box_0_started_at_undefined = true;

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

bool is_box_0_started_at_undefined() {
  xSemaphoreTake(_mutex_box_0_started_at, 0);
  bool v = _box_0_started_at_undefined;
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
  _box_0_started_at_undefined = false;
  xSemaphoreGive(_mutex_box_0_started_at);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_STARTED_AT, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_box_0_on_hour; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_on_hour_changed = true;
static bool _box_0_on_hour_undefined = true;

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

bool is_box_0_on_hour_undefined() {
  xSemaphoreTake(_mutex_box_0_on_hour, 0);
  bool v = _box_0_on_hour_undefined;
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
  _box_0_on_hour_undefined = false;
  xSemaphoreGive(_mutex_box_0_on_hour);
}


static SemaphoreHandle_t _mutex_box_0_on_min; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_on_min_changed = true;
static bool _box_0_on_min_undefined = true;

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

bool is_box_0_on_min_undefined() {
  xSemaphoreTake(_mutex_box_0_on_min, 0);
  bool v = _box_0_on_min_undefined;
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
  _box_0_on_min_undefined = false;
  xSemaphoreGive(_mutex_box_0_on_min);
}


static SemaphoreHandle_t _mutex_box_0_off_hour; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_off_hour_changed = true;
static bool _box_0_off_hour_undefined = true;

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

bool is_box_0_off_hour_undefined() {
  xSemaphoreTake(_mutex_box_0_off_hour, 0);
  bool v = _box_0_off_hour_undefined;
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
  _box_0_off_hour_undefined = false;
  xSemaphoreGive(_mutex_box_0_off_hour);
}


static SemaphoreHandle_t _mutex_box_0_off_min; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_off_min_changed = true;
static bool _box_0_off_min_undefined = true;

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

bool is_box_0_off_min_undefined() {
  xSemaphoreTake(_mutex_box_0_off_min, 0);
  bool v = _box_0_off_min_undefined;
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
  _box_0_off_min_undefined = false;
  xSemaphoreGive(_mutex_box_0_off_min);
}


static SemaphoreHandle_t _mutex_box_0_stretch; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_stretch_changed = true;
static bool _box_0_stretch_undefined = true;

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

bool is_box_0_stretch_undefined() {
  xSemaphoreTake(_mutex_box_0_stretch, 0);
  bool v = _box_0_stretch_undefined;
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
  _box_0_stretch_undefined = false;
  xSemaphoreGive(_mutex_box_0_stretch);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_STRETCH, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_box_0_led_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_led_dim_changed = true;
static bool _box_0_led_dim_undefined = true;

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

bool is_box_0_led_dim_undefined() {
  xSemaphoreTake(_mutex_box_0_led_dim, 0);
  bool v = _box_0_led_dim_undefined;
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
  _box_0_led_dim_undefined = false;
  xSemaphoreGive(_mutex_box_0_led_dim);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_LED_DIM, (uint8_t *)&value, sizeof(int));
}


static SemaphoreHandle_t _mutex_box_0_sht21_temp_c; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_sht21_temp_c_changed = true;
static bool _box_0_sht21_temp_c_undefined = true;

void reset_box_0_sht21_temp_c_changed() {
  xSemaphoreTake(_mutex_box_0_sht21_temp_c, 0);
  _box_0_sht21_temp_c_changed = false;
  xSemaphoreGive(_mutex_box_0_sht21_temp_c);
}

bool is_box_0_sht21_temp_c_changed() {
  xSemaphoreTake(_mutex_box_0_sht21_temp_c, 0);
  bool v = _box_0_sht21_temp_c_changed;
  xSemaphoreGive(_mutex_box_0_sht21_temp_c);
  return v;
}

bool is_box_0_sht21_temp_c_undefined() {
  xSemaphoreTake(_mutex_box_0_sht21_temp_c, 0);
  bool v = _box_0_sht21_temp_c_undefined;
  xSemaphoreGive(_mutex_box_0_sht21_temp_c);
  return v;
}



int get_box_0_sht21_temp_c() {
  return geti(BOX_0_SHT21_TEMP_C);
}

void set_box_0_sht21_temp_c(int value) {
  if (geti(BOX_0_SHT21_TEMP_C) == value) return;
  seti(BOX_0_SHT21_TEMP_C, value);
  xSemaphoreTake(_mutex_box_0_sht21_temp_c, 0);
  _box_0_sht21_temp_c_changed = true;
  _box_0_sht21_temp_c_undefined = false;
  xSemaphoreGive(_mutex_box_0_sht21_temp_c);
}


static SemaphoreHandle_t _mutex_box_0_sht21_temp_f; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_sht21_temp_f_changed = true;
static bool _box_0_sht21_temp_f_undefined = true;

void reset_box_0_sht21_temp_f_changed() {
  xSemaphoreTake(_mutex_box_0_sht21_temp_f, 0);
  _box_0_sht21_temp_f_changed = false;
  xSemaphoreGive(_mutex_box_0_sht21_temp_f);
}

bool is_box_0_sht21_temp_f_changed() {
  xSemaphoreTake(_mutex_box_0_sht21_temp_f, 0);
  bool v = _box_0_sht21_temp_f_changed;
  xSemaphoreGive(_mutex_box_0_sht21_temp_f);
  return v;
}

bool is_box_0_sht21_temp_f_undefined() {
  xSemaphoreTake(_mutex_box_0_sht21_temp_f, 0);
  bool v = _box_0_sht21_temp_f_undefined;
  xSemaphoreGive(_mutex_box_0_sht21_temp_f);
  return v;
}



int get_box_0_sht21_temp_f() {
  return geti(BOX_0_SHT21_TEMP_F);
}

void set_box_0_sht21_temp_f(int value) {
  if (geti(BOX_0_SHT21_TEMP_F) == value) return;
  seti(BOX_0_SHT21_TEMP_F, value);
  xSemaphoreTake(_mutex_box_0_sht21_temp_f, 0);
  _box_0_sht21_temp_f_changed = true;
  _box_0_sht21_temp_f_undefined = false;
  xSemaphoreGive(_mutex_box_0_sht21_temp_f);
}


static SemaphoreHandle_t _mutex_box_0_sht21_humi; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_sht21_humi_changed = true;
static bool _box_0_sht21_humi_undefined = true;

void reset_box_0_sht21_humi_changed() {
  xSemaphoreTake(_mutex_box_0_sht21_humi, 0);
  _box_0_sht21_humi_changed = false;
  xSemaphoreGive(_mutex_box_0_sht21_humi);
}

bool is_box_0_sht21_humi_changed() {
  xSemaphoreTake(_mutex_box_0_sht21_humi, 0);
  bool v = _box_0_sht21_humi_changed;
  xSemaphoreGive(_mutex_box_0_sht21_humi);
  return v;
}

bool is_box_0_sht21_humi_undefined() {
  xSemaphoreTake(_mutex_box_0_sht21_humi, 0);
  bool v = _box_0_sht21_humi_undefined;
  xSemaphoreGive(_mutex_box_0_sht21_humi);
  return v;
}



int get_box_0_sht21_humi() {
  return geti(BOX_0_SHT21_HUMI);
}

void set_box_0_sht21_humi(int value) {
  if (geti(BOX_0_SHT21_HUMI) == value) return;
  seti(BOX_0_SHT21_HUMI, value);
  xSemaphoreTake(_mutex_box_0_sht21_humi, 0);
  _box_0_sht21_humi_changed = true;
  _box_0_sht21_humi_undefined = false;
  xSemaphoreGive(_mutex_box_0_sht21_humi);
}


static SemaphoreHandle_t _mutex_box_0_led_info; // TODO check RAM weight of creating so many semaphores :/
static bool _box_0_led_info_changed = true;
static bool _box_0_led_info_undefined = true;

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

bool is_box_0_led_info_undefined() {
  xSemaphoreTake(_mutex_box_0_led_info, 0);
  bool v = _box_0_led_info_undefined;
  xSemaphoreGive(_mutex_box_0_led_info);
  return v;
}



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
  if (!strcmp(_box_0_led_info, value)) return;
  strncpy(_box_0_led_info, value, strlen(value));
  _box_0_led_info_changed = true;
  xSemaphoreGive(_mutex_box_0_led_info);
  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_LED_INFO, (uint8_t *)value, strlen(value));
}

static SemaphoreHandle_t _mutex_box_1_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_enabled_changed = true;
static bool _box_1_enabled_undefined = true;

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

bool is_box_1_enabled_undefined() {
  xSemaphoreTake(_mutex_box_1_enabled, 0);
  bool v = _box_1_enabled_undefined;
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
  _box_1_enabled_undefined = false;
  xSemaphoreGive(_mutex_box_1_enabled);
}


static SemaphoreHandle_t _mutex_box_1_timer_type; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_timer_type_changed = true;
static bool _box_1_timer_type_undefined = true;

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

bool is_box_1_timer_type_undefined() {
  xSemaphoreTake(_mutex_box_1_timer_type, 0);
  bool v = _box_1_timer_type_undefined;
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
  _box_1_timer_type_undefined = false;
  xSemaphoreGive(_mutex_box_1_timer_type);
}


static SemaphoreHandle_t _mutex_box_1_timer_output; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_timer_output_changed = true;
static bool _box_1_timer_output_undefined = true;

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

bool is_box_1_timer_output_undefined() {
  xSemaphoreTake(_mutex_box_1_timer_output, 0);
  bool v = _box_1_timer_output_undefined;
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
  _box_1_timer_output_undefined = false;
  xSemaphoreGive(_mutex_box_1_timer_output);
}


static SemaphoreHandle_t _mutex_box_1_started_at; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_started_at_changed = true;
static bool _box_1_started_at_undefined = true;

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

bool is_box_1_started_at_undefined() {
  xSemaphoreTake(_mutex_box_1_started_at, 0);
  bool v = _box_1_started_at_undefined;
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
  _box_1_started_at_undefined = false;
  xSemaphoreGive(_mutex_box_1_started_at);
}


static SemaphoreHandle_t _mutex_box_1_on_hour; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_on_hour_changed = true;
static bool _box_1_on_hour_undefined = true;

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

bool is_box_1_on_hour_undefined() {
  xSemaphoreTake(_mutex_box_1_on_hour, 0);
  bool v = _box_1_on_hour_undefined;
  xSemaphoreGive(_mutex_box_1_on_hour);
  return v;
}



int get_box_1_on_hour() {
  return geti(BOX_1_ON_HOUR);
}

void set_box_1_on_hour(int value) {
  if (geti(BOX_1_ON_HOUR) == value) return;
  seti(BOX_1_ON_HOUR, value);
  xSemaphoreTake(_mutex_box_1_on_hour, 0);
  _box_1_on_hour_changed = true;
  _box_1_on_hour_undefined = false;
  xSemaphoreGive(_mutex_box_1_on_hour);
}


static SemaphoreHandle_t _mutex_box_1_on_min; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_on_min_changed = true;
static bool _box_1_on_min_undefined = true;

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

bool is_box_1_on_min_undefined() {
  xSemaphoreTake(_mutex_box_1_on_min, 0);
  bool v = _box_1_on_min_undefined;
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
  _box_1_on_min_undefined = false;
  xSemaphoreGive(_mutex_box_1_on_min);
}


static SemaphoreHandle_t _mutex_box_1_off_hour; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_off_hour_changed = true;
static bool _box_1_off_hour_undefined = true;

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

bool is_box_1_off_hour_undefined() {
  xSemaphoreTake(_mutex_box_1_off_hour, 0);
  bool v = _box_1_off_hour_undefined;
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
  _box_1_off_hour_undefined = false;
  xSemaphoreGive(_mutex_box_1_off_hour);
}


static SemaphoreHandle_t _mutex_box_1_off_min; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_off_min_changed = true;
static bool _box_1_off_min_undefined = true;

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

bool is_box_1_off_min_undefined() {
  xSemaphoreTake(_mutex_box_1_off_min, 0);
  bool v = _box_1_off_min_undefined;
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
  _box_1_off_min_undefined = false;
  xSemaphoreGive(_mutex_box_1_off_min);
}


static SemaphoreHandle_t _mutex_box_1_stretch; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_stretch_changed = true;
static bool _box_1_stretch_undefined = true;

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

bool is_box_1_stretch_undefined() {
  xSemaphoreTake(_mutex_box_1_stretch, 0);
  bool v = _box_1_stretch_undefined;
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
  _box_1_stretch_undefined = false;
  xSemaphoreGive(_mutex_box_1_stretch);
}


static SemaphoreHandle_t _mutex_box_1_led_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_led_dim_changed = true;
static bool _box_1_led_dim_undefined = true;

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

bool is_box_1_led_dim_undefined() {
  xSemaphoreTake(_mutex_box_1_led_dim, 0);
  bool v = _box_1_led_dim_undefined;
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
  _box_1_led_dim_undefined = false;
  xSemaphoreGive(_mutex_box_1_led_dim);
}


static SemaphoreHandle_t _mutex_box_1_sht21_temp_c; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_sht21_temp_c_changed = true;
static bool _box_1_sht21_temp_c_undefined = true;

void reset_box_1_sht21_temp_c_changed() {
  xSemaphoreTake(_mutex_box_1_sht21_temp_c, 0);
  _box_1_sht21_temp_c_changed = false;
  xSemaphoreGive(_mutex_box_1_sht21_temp_c);
}

bool is_box_1_sht21_temp_c_changed() {
  xSemaphoreTake(_mutex_box_1_sht21_temp_c, 0);
  bool v = _box_1_sht21_temp_c_changed;
  xSemaphoreGive(_mutex_box_1_sht21_temp_c);
  return v;
}

bool is_box_1_sht21_temp_c_undefined() {
  xSemaphoreTake(_mutex_box_1_sht21_temp_c, 0);
  bool v = _box_1_sht21_temp_c_undefined;
  xSemaphoreGive(_mutex_box_1_sht21_temp_c);
  return v;
}



int get_box_1_sht21_temp_c() {
  return geti(BOX_1_SHT21_TEMP_C);
}

void set_box_1_sht21_temp_c(int value) {
  if (geti(BOX_1_SHT21_TEMP_C) == value) return;
  seti(BOX_1_SHT21_TEMP_C, value);
  xSemaphoreTake(_mutex_box_1_sht21_temp_c, 0);
  _box_1_sht21_temp_c_changed = true;
  _box_1_sht21_temp_c_undefined = false;
  xSemaphoreGive(_mutex_box_1_sht21_temp_c);
}


static SemaphoreHandle_t _mutex_box_1_sht21_temp_f; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_sht21_temp_f_changed = true;
static bool _box_1_sht21_temp_f_undefined = true;

void reset_box_1_sht21_temp_f_changed() {
  xSemaphoreTake(_mutex_box_1_sht21_temp_f, 0);
  _box_1_sht21_temp_f_changed = false;
  xSemaphoreGive(_mutex_box_1_sht21_temp_f);
}

bool is_box_1_sht21_temp_f_changed() {
  xSemaphoreTake(_mutex_box_1_sht21_temp_f, 0);
  bool v = _box_1_sht21_temp_f_changed;
  xSemaphoreGive(_mutex_box_1_sht21_temp_f);
  return v;
}

bool is_box_1_sht21_temp_f_undefined() {
  xSemaphoreTake(_mutex_box_1_sht21_temp_f, 0);
  bool v = _box_1_sht21_temp_f_undefined;
  xSemaphoreGive(_mutex_box_1_sht21_temp_f);
  return v;
}



int get_box_1_sht21_temp_f() {
  return geti(BOX_1_SHT21_TEMP_F);
}

void set_box_1_sht21_temp_f(int value) {
  if (geti(BOX_1_SHT21_TEMP_F) == value) return;
  seti(BOX_1_SHT21_TEMP_F, value);
  xSemaphoreTake(_mutex_box_1_sht21_temp_f, 0);
  _box_1_sht21_temp_f_changed = true;
  _box_1_sht21_temp_f_undefined = false;
  xSemaphoreGive(_mutex_box_1_sht21_temp_f);
}


static SemaphoreHandle_t _mutex_box_1_sht21_humi; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_sht21_humi_changed = true;
static bool _box_1_sht21_humi_undefined = true;

void reset_box_1_sht21_humi_changed() {
  xSemaphoreTake(_mutex_box_1_sht21_humi, 0);
  _box_1_sht21_humi_changed = false;
  xSemaphoreGive(_mutex_box_1_sht21_humi);
}

bool is_box_1_sht21_humi_changed() {
  xSemaphoreTake(_mutex_box_1_sht21_humi, 0);
  bool v = _box_1_sht21_humi_changed;
  xSemaphoreGive(_mutex_box_1_sht21_humi);
  return v;
}

bool is_box_1_sht21_humi_undefined() {
  xSemaphoreTake(_mutex_box_1_sht21_humi, 0);
  bool v = _box_1_sht21_humi_undefined;
  xSemaphoreGive(_mutex_box_1_sht21_humi);
  return v;
}



int get_box_1_sht21_humi() {
  return geti(BOX_1_SHT21_HUMI);
}

void set_box_1_sht21_humi(int value) {
  if (geti(BOX_1_SHT21_HUMI) == value) return;
  seti(BOX_1_SHT21_HUMI, value);
  xSemaphoreTake(_mutex_box_1_sht21_humi, 0);
  _box_1_sht21_humi_changed = true;
  _box_1_sht21_humi_undefined = false;
  xSemaphoreGive(_mutex_box_1_sht21_humi);
}


static SemaphoreHandle_t _mutex_box_1_led_info; // TODO check RAM weight of creating so many semaphores :/
static bool _box_1_led_info_changed = true;
static bool _box_1_led_info_undefined = true;

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

bool is_box_1_led_info_undefined() {
  xSemaphoreTake(_mutex_box_1_led_info, 0);
  bool v = _box_1_led_info_undefined;
  xSemaphoreGive(_mutex_box_1_led_info);
  return v;
}



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
  if (!strcmp(_box_1_led_info, value)) return;
  strncpy(_box_1_led_info, value, strlen(value));
  _box_1_led_info_changed = true;
  xSemaphoreGive(_mutex_box_1_led_info);
}

static SemaphoreHandle_t _mutex_led_0_duty; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_duty_changed = true;
static bool _led_0_duty_undefined = true;

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

bool is_led_0_duty_undefined() {
  xSemaphoreTake(_mutex_led_0_duty, 0);
  bool v = _led_0_duty_undefined;
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
  _led_0_duty_undefined = false;
  xSemaphoreGive(_mutex_led_0_duty);
}


static SemaphoreHandle_t _mutex_led_1_duty; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_duty_changed = true;
static bool _led_1_duty_undefined = true;

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

bool is_led_1_duty_undefined() {
  xSemaphoreTake(_mutex_led_1_duty, 0);
  bool v = _led_1_duty_undefined;
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
  _led_1_duty_undefined = false;
  xSemaphoreGive(_mutex_led_1_duty);
}


static SemaphoreHandle_t _mutex_led_0_gpio; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_gpio_changed = true;
static bool _led_0_gpio_undefined = true;

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

bool is_led_0_gpio_undefined() {
  xSemaphoreTake(_mutex_led_0_gpio, 0);
  bool v = _led_0_gpio_undefined;
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
  _led_0_gpio_undefined = false;
  xSemaphoreGive(_mutex_led_0_gpio);
}


static SemaphoreHandle_t _mutex_led_1_gpio; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_gpio_changed = true;
static bool _led_1_gpio_undefined = true;

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

bool is_led_1_gpio_undefined() {
  xSemaphoreTake(_mutex_led_1_gpio, 0);
  bool v = _led_1_gpio_undefined;
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
  _led_1_gpio_undefined = false;
  xSemaphoreGive(_mutex_led_1_gpio);
}


static SemaphoreHandle_t _mutex_led_0_x; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_x_changed = true;
static bool _led_0_x_undefined = true;

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

bool is_led_0_x_undefined() {
  xSemaphoreTake(_mutex_led_0_x, 0);
  bool v = _led_0_x_undefined;
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
  _led_0_x_undefined = false;
  xSemaphoreGive(_mutex_led_0_x);
}


static SemaphoreHandle_t _mutex_led_1_x; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_x_changed = true;
static bool _led_1_x_undefined = true;

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

bool is_led_1_x_undefined() {
  xSemaphoreTake(_mutex_led_1_x, 0);
  bool v = _led_1_x_undefined;
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
  _led_1_x_undefined = false;
  xSemaphoreGive(_mutex_led_1_x);
}


static SemaphoreHandle_t _mutex_led_0_y; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_y_changed = true;
static bool _led_0_y_undefined = true;

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

bool is_led_0_y_undefined() {
  xSemaphoreTake(_mutex_led_0_y, 0);
  bool v = _led_0_y_undefined;
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
  _led_0_y_undefined = false;
  xSemaphoreGive(_mutex_led_0_y);
}


static SemaphoreHandle_t _mutex_led_1_y; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_y_changed = true;
static bool _led_1_y_undefined = true;

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

bool is_led_1_y_undefined() {
  xSemaphoreTake(_mutex_led_1_y, 0);
  bool v = _led_1_y_undefined;
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
  _led_1_y_undefined = false;
  xSemaphoreGive(_mutex_led_1_y);
}


static SemaphoreHandle_t _mutex_led_0_z; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_z_changed = true;
static bool _led_0_z_undefined = true;

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

bool is_led_0_z_undefined() {
  xSemaphoreTake(_mutex_led_0_z, 0);
  bool v = _led_0_z_undefined;
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
  _led_0_z_undefined = false;
  xSemaphoreGive(_mutex_led_0_z);
}


static SemaphoreHandle_t _mutex_led_1_z; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_z_changed = true;
static bool _led_1_z_undefined = true;

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

bool is_led_1_z_undefined() {
  xSemaphoreTake(_mutex_led_1_z, 0);
  bool v = _led_1_z_undefined;
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
  _led_1_z_undefined = false;
  xSemaphoreGive(_mutex_led_1_z);
}


static SemaphoreHandle_t _mutex_led_0_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_enabled_changed = true;
static bool _led_0_enabled_undefined = true;

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

bool is_led_0_enabled_undefined() {
  xSemaphoreTake(_mutex_led_0_enabled, 0);
  bool v = _led_0_enabled_undefined;
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
  _led_0_enabled_undefined = false;
  xSemaphoreGive(_mutex_led_0_enabled);
}


static SemaphoreHandle_t _mutex_led_1_enabled; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_enabled_changed = true;
static bool _led_1_enabled_undefined = true;

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

bool is_led_1_enabled_undefined() {
  xSemaphoreTake(_mutex_led_1_enabled, 0);
  bool v = _led_1_enabled_undefined;
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
  _led_1_enabled_undefined = false;
  xSemaphoreGive(_mutex_led_1_enabled);
}


static SemaphoreHandle_t _mutex_led_0_box; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_box_changed = true;
static bool _led_0_box_undefined = true;

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

bool is_led_0_box_undefined() {
  xSemaphoreTake(_mutex_led_0_box, 0);
  bool v = _led_0_box_undefined;
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
  _led_0_box_undefined = false;
  xSemaphoreGive(_mutex_led_0_box);
}


static SemaphoreHandle_t _mutex_led_1_box; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_box_changed = true;
static bool _led_1_box_undefined = true;

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

bool is_led_1_box_undefined() {
  xSemaphoreTake(_mutex_led_1_box, 0);
  bool v = _led_1_box_undefined;
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
  _led_1_box_undefined = false;
  xSemaphoreGive(_mutex_led_1_box);
}


static SemaphoreHandle_t _mutex_led_0_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_dim_changed = true;
static bool _led_0_dim_undefined = true;

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

bool is_led_0_dim_undefined() {
  xSemaphoreTake(_mutex_led_0_dim, 0);
  bool v = _led_0_dim_undefined;
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
  _led_0_dim_undefined = false;
  xSemaphoreGive(_mutex_led_0_dim);
}


static SemaphoreHandle_t _mutex_led_1_dim; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_dim_changed = true;
static bool _led_1_dim_undefined = true;

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

bool is_led_1_dim_undefined() {
  xSemaphoreTake(_mutex_led_1_dim, 0);
  bool v = _led_1_dim_undefined;
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
  _led_1_dim_undefined = false;
  xSemaphoreGive(_mutex_led_1_dim);
}


static SemaphoreHandle_t _mutex_led_0_fade; // TODO check RAM weight of creating so many semaphores :/
static bool _led_0_fade_changed = true;
static bool _led_0_fade_undefined = true;

void reset_led_0_fade_changed() {
  xSemaphoreTake(_mutex_led_0_fade, 0);
  _led_0_fade_changed = false;
  xSemaphoreGive(_mutex_led_0_fade);
}

bool is_led_0_fade_changed() {
  xSemaphoreTake(_mutex_led_0_fade, 0);
  bool v = _led_0_fade_changed;
  xSemaphoreGive(_mutex_led_0_fade);
  return v;
}

bool is_led_0_fade_undefined() {
  xSemaphoreTake(_mutex_led_0_fade, 0);
  bool v = _led_0_fade_undefined;
  xSemaphoreGive(_mutex_led_0_fade);
  return v;
}



int get_led_0_fade() {
  return geti(LED_0_FADE);
}

void set_led_0_fade(int value) {
  if (geti(LED_0_FADE) == value) return;
  seti(LED_0_FADE, value);
  xSemaphoreTake(_mutex_led_0_fade, 0);
  _led_0_fade_changed = true;
  _led_0_fade_undefined = false;
  xSemaphoreGive(_mutex_led_0_fade);
}


static SemaphoreHandle_t _mutex_led_1_fade; // TODO check RAM weight of creating so many semaphores :/
static bool _led_1_fade_changed = true;
static bool _led_1_fade_undefined = true;

void reset_led_1_fade_changed() {
  xSemaphoreTake(_mutex_led_1_fade, 0);
  _led_1_fade_changed = false;
  xSemaphoreGive(_mutex_led_1_fade);
}

bool is_led_1_fade_changed() {
  xSemaphoreTake(_mutex_led_1_fade, 0);
  bool v = _led_1_fade_changed;
  xSemaphoreGive(_mutex_led_1_fade);
  return v;
}

bool is_led_1_fade_undefined() {
  xSemaphoreTake(_mutex_led_1_fade, 0);
  bool v = _led_1_fade_undefined;
  xSemaphoreGive(_mutex_led_1_fade);
  return v;
}



int get_led_1_fade() {
  return geti(LED_1_FADE);
}

void set_led_1_fade(int value) {
  if (geti(LED_1_FADE) == value) return;
  seti(LED_1_FADE, value);
  xSemaphoreTake(_mutex_led_1_fade, 0);
  _led_1_fade_changed = true;
  _led_1_fade_undefined = false;
  xSemaphoreGive(_mutex_led_1_fade);
}


void init_helpers() {
  _mutex_wifi_status = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_wifi_ssid = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_wifi_password = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_wifi_ap_ssid = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_wifi_ap_password = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_mdns_domain = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_wifi_ip = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_time = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_n_restarts = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_timestamp = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_server_ip = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_server_hostname = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_server_port = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_basedir = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_ota_status = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_broker_url = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_broker_channel = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_broker_clientid = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_0_sda = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_0_scl = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_0_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_1_sda = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_1_scl = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_i2c_1_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_reboot = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_state = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_device_name = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_status_led_red_gpio = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_status_led_green_gpio = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_status_led_dim = xSemaphoreCreateMutexStatic(&mutex_buffer);
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
  _mutex_box_0_sht21_temp_c = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_sht21_temp_f = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_0_sht21_humi = xSemaphoreCreateMutexStatic(&mutex_buffer);
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
  _mutex_box_1_sht21_temp_c = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_sht21_temp_f = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_sht21_humi = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_box_1_led_info = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_duty = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_duty = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_gpio = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_gpio = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_x = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_x = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_y = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_y = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_z = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_z = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_enabled = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_box = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_box = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_dim = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_dim = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_0_fade = xSemaphoreCreateMutexStatic(&mutex_buffer);
  _mutex_led_1_fade = xSemaphoreCreateMutexStatic(&mutex_buffer);
}

/*
 * [/GENERATED]
 */
