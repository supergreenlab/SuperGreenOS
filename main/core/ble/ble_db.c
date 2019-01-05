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

#include "ble_db.h"

#include "string.h"

#include "../include_modules.h"
#include "../log/log.h"
#include "../ble/ble_utils.h"
#include "../kv/kv.h"
#include "../kv/kv_helpers_internal.h"


static const uint16_t GATTS_SERVICE_UUID      = 0x00FF;

const uint8_t WIFI_STATUS_UUID[ESP_UUID_LEN_128] = {0xee,0x06,0x0e,0xb5,0x31,0xae,0x83,0xf0,0xda,0xcb,0x67,0x6d,0x1c,0xda,0x2f,0x37};
const uint8_t WIFI_SSID_UUID[ESP_UUID_LEN_128] = {0x17,0xfe,0xc3,0xc1,0x6b,0xe1,0x15,0x54,0xa5,0x74,0x55,0x9c,0x81,0x69,0xa3,0x6c};
const uint8_t WIFI_PASS_UUID[ESP_UUID_LEN_128] = {0xb9,0x5d,0x53,0x82,0x6e,0xcc,0xa0,0xfe,0xf1,0xa6,0xfe,0x6c,0x10,0x0b,0xe4,0xf7};
const uint8_t TIME_UUID[ESP_UUID_LEN_128] = {0x9b,0x6a,0x3b,0xe2,0xaa,0xb4,0x33,0xaa,0x8a,0x4a,0x9e,0xe1,0x4f,0xee,0xf9,0x40};
const uint8_t OTA_TIMESTAMP_UUID[ESP_UUID_LEN_128] = {0x89,0x6e,0x49,0xd6,0x82,0x21,0x7e,0xce,0x96,0x23,0xc9,0xe3,0x2b,0x16,0x6f,0x61};
const uint8_t OTA_SERVER_IP_UUID[ESP_UUID_LEN_128] = {0xda,0x84,0xdb,0xbc,0x5f,0x7d,0x86,0xf5,0x10,0xf0,0xae,0xaa,0x05,0xdb,0xb8,0xf7};
const uint8_t OTA_SERVER_HOSTNAME_UUID[ESP_UUID_LEN_128] = {0x3c,0x3d,0xce,0xb9,0x11,0x81,0xce,0x11,0xe6,0x13,0xab,0x05,0x47,0x6a,0xa2,0xfa};
const uint8_t OTA_SERVER_PORT_UUID[ESP_UUID_LEN_128] = {0x6a,0xe5,0xac,0x03,0xe2,0xe0,0x6f,0x79,0x75,0x69,0xe0,0xeb,0x38,0xbd,0x35,0x6c};
const uint8_t OTA_VERSION_FILENAME_UUID[ESP_UUID_LEN_128] = {0x52,0x7b,0x93,0xa6,0x52,0x22,0x4c,0xb2,0x3f,0xc9,0x16,0x3e,0x7d,0xf5,0xe5,0x1e};
const uint8_t OTA_FILENAME_UUID[ESP_UUID_LEN_128] = {0x32,0x94,0x27,0x51,0x16,0x02,0x33,0x8b,0xa5,0xff,0x83,0xfd,0x9f,0xfd,0x10,0x3f};

const esp_gatts_attr_db_t gatt_db[HRS_IDX_NB] = {

  [IDX_SVC]    =
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&primary_service_uuid, ESP_GATT_PERM_READ,
    sizeof(uint16_t), sizeof(GATTS_SERVICE_UUID), (uint8_t *)&GATTS_SERVICE_UUID}},

  /*
   * [GENERATED]
   */

    R_I_NOTIFIABLE_CHAR(WIFI_STATUS),
    RW_STR_CHAR(WIFI_SSID),
    RW_STR_NOTIFIABLE_CHAR(WIFI_PASS),
    RW_I_NOTIFIABLE_CHAR(TIME),
    R_I_CHAR(OTA_TIMESTAMP),
    RW_STR_CHAR(OTA_SERVER_IP),
    RW_STR_CHAR(OTA_SERVER_HOSTNAME),
    RW_STR_CHAR(OTA_SERVER_PORT),
    RW_STR_CHAR(OTA_VERSION_FILENAME),
    RW_STR_CHAR(OTA_FILENAME),

  /*
   * [/GENERATED]
   */
};

void on_write(esp_ble_gatts_cb_param_t *param) {
  /*
   * [GENERATED]
   */
  
      if (param->write.handle == handle_table[IDX_VALUE(WIFI_SSID)]) {
          char value[MAX_KVALUE_SIZE] = {0};
          strncpy(value, (const char *)param->write.value, param->write.len);
          internal_set_wifi_ssid(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(WIFI_PASS)]) {
          char value[MAX_KVALUE_SIZE] = {0};
          strncpy(value, (const char *)param->write.value, param->write.len);
          internal_set_wifi_password(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(TIME)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_time(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(OTA_SERVER_IP)]) {
          char value[MAX_KVALUE_SIZE] = {0};
          strncpy(value, (const char *)param->write.value, param->write.len);
          internal_set_ota_server_ip(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(OTA_SERVER_HOSTNAME)]) {
          char value[MAX_KVALUE_SIZE] = {0};
          strncpy(value, (const char *)param->write.value, param->write.len);
          internal_set_ota_server_hostname(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(OTA_SERVER_PORT)]) {
          char value[MAX_KVALUE_SIZE] = {0};
          strncpy(value, (const char *)param->write.value, param->write.len);
          internal_set_ota_server_port(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(OTA_VERSION_FILENAME)]) {
          char value[MAX_KVALUE_SIZE] = {0};
          strncpy(value, (const char *)param->write.value, param->write.len);
          internal_set_ota_version_filename(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(OTA_FILENAME)]) {
          char value[MAX_KVALUE_SIZE] = {0};
          strncpy(value, (const char *)param->write.value, param->write.len);
          internal_set_ota_filename(value);
      }

  /*
   * [/GENERATED]
   */
}

void on_read(esp_ble_gatts_cb_param_t *param) {
}
