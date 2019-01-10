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
const uint8_t WIFI_PASSWORD_UUID[ESP_UUID_LEN_128] = {0xb9,0x5d,0x53,0x82,0x6e,0xcc,0xa0,0xfe,0xf1,0xa6,0xfe,0x6c,0x10,0x0b,0xe4,0xf7};
const uint8_t TIME_UUID[ESP_UUID_LEN_128] = {0x9b,0x6a,0x3b,0xe2,0xaa,0xb4,0x33,0xaa,0x8a,0x4a,0x9e,0xe1,0x4f,0xee,0xf9,0x40};
const uint8_t STATE_UUID[ESP_UUID_LEN_128] = {0x94,0x28,0x12,0x63,0x56,0xde,0xec,0x43,0xb4,0xfe,0xd6,0x3b,0xd2,0xdf,0xf6,0x8f};
const uint8_t DEVICE_NAME_UUID[ESP_UUID_LEN_128] = {0x25,0x8b,0x4f,0x3d,0xf1,0x61,0xee,0x68,0x6e,0xee,0x0e,0x8c,0x32,0x77,0x31,0xa6};
const uint8_t TIMER_TYPE_UUID[ESP_UUID_LEN_128] = {0xf3,0xa9,0xfa,0xb2,0x5a,0x41,0x3d,0x34,0x7b,0x0a,0xa9,0x3a,0x40,0xa8,0x5e,0x5f};
const uint8_t STARTED_AT_UUID[ESP_UUID_LEN_128] = {0xa2,0x95,0x3b,0x05,0x4b,0x30,0x39,0xba,0x57,0x4f,0x01,0xf1,0x34,0x02,0x45,0x1f};
const uint8_t ON_HOUR_UUID[ESP_UUID_LEN_128] = {0xa1,0x4b,0xed,0x50,0xf3,0x19,0x26,0xef,0xda,0x09,0xb7,0x4a,0xa6,0xf9,0x67,0xe8};
const uint8_t ON_MIN_UUID[ESP_UUID_LEN_128] = {0x47,0x13,0x79,0xf1,0x67,0x71,0xf5,0x62,0x14,0xf7,0x3b,0xdd,0x0b,0xa5,0x28,0x75};
const uint8_t OFF_HOUR_UUID[ESP_UUID_LEN_128] = {0xae,0xbe,0x35,0x4c,0x29,0x12,0x53,0x02,0x6b,0xab,0x7e,0x9d,0x8c,0xb8,0xaf,0x5d};
const uint8_t OFF_MIN_UUID[ESP_UUID_LEN_128] = {0xd4,0xd3,0xef,0x05,0x3f,0x4f,0x10,0x41,0x22,0x2d,0xab,0xd9,0xe1,0xa1,0x6a,0x08};
const uint8_t STRETCH_UUID[ESP_UUID_LEN_128] = {0xe5,0x5a,0x87,0x47,0xcc,0xb2,0xe1,0xa5,0x22,0x48,0xb0,0x95,0x6b,0x32,0x72,0x70};
const uint8_t LED_DIM_UUID[ESP_UUID_LEN_128] = {0x61,0xdb,0xb0,0x55,0xde,0x0f,0xb7,0x46,0x29,0xba,0x77,0x76,0xf6,0x75,0x63,0xa6};
const uint8_t BLOWER_UUID[ESP_UUID_LEN_128] = {0x7b,0x5e,0x0a,0xb7,0x2a,0x7f,0xfd,0x1b,0x7f,0xe3,0xdc,0xbe,0xa7,0xce,0xb7,0x03};
const uint8_t SHT1X_TEMP_C_UUID[ESP_UUID_LEN_128] = {0x25,0x8e,0x2d,0xf9,0x77,0x3d,0x9f,0xee,0x37,0x61,0x00,0x3b,0x36,0x28,0xab,0xb5};
const uint8_t SHT1X_TEMP_F_UUID[ESP_UUID_LEN_128] = {0x7b,0xac,0x28,0xbb,0xf8,0xaa,0x7c,0xde,0x31,0xee,0xab,0xa2,0x9d,0xc4,0xdd,0xbe};
const uint8_t SHT1X_HUMI_UUID[ESP_UUID_LEN_128] = {0x29,0xdb,0x5c,0x3f,0xdb,0x0c,0x91,0x88,0x5c,0x1e,0x93,0xf9,0x4c,0x16,0xa7,0xba};
const uint8_t LED_INFO_UUID[ESP_UUID_LEN_128] = {0x96,0xc5,0x14,0x21,0x97,0x6a,0x70,0x18,0x34,0x52,0xce,0x6d,0xfe,0x81,0xf7,0x6d};

const esp_gatts_attr_db_t gatt_db[HRS_IDX_NB] = {

  [IDX_SVC]    =
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&primary_service_uuid, ESP_GATT_PERM_READ,
    sizeof(uint16_t), sizeof(GATTS_SERVICE_UUID), (uint8_t *)&GATTS_SERVICE_UUID}},

  /*
   * [GENERATED]
   */

    R_I_NOTIFIABLE_CHAR(WIFI_STATUS),
    RW_STR_CHAR(WIFI_SSID),
    RW_STR_NOTIFIABLE_CHAR(WIFI_PASSWORD),
    RW_I_NOTIFIABLE_CHAR(TIME),
    RW_I_NOTIFIABLE_CHAR(STATE),
    RW_STR_CHAR(DEVICE_NAME),
    RW_I_CHAR(TIMER_TYPE),
    RW_I_NOTIFIABLE_CHAR(STARTED_AT),
    RW_I_CHAR(ON_HOUR),
    RW_I_CHAR(ON_MIN),
    RW_I_CHAR(OFF_HOUR),
    RW_I_CHAR(OFF_MIN),
    R_I_NOTIFIABLE_CHAR(STRETCH),
    R_I_NOTIFIABLE_CHAR(LED_DIM),
    R_I_NOTIFIABLE_CHAR(BLOWER),
    R_I_NOTIFIABLE_CHAR(SHT1X_TEMP_C),
    R_I_NOTIFIABLE_CHAR(SHT1X_TEMP_F),
    R_I_NOTIFIABLE_CHAR(SHT1X_HUMI),
    R_STR_NOTIFIABLE_CHAR(LED_INFO),

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
       else if (param->write.handle == handle_table[IDX_VALUE(WIFI_PASSWORD)]) {
          char value[MAX_KVALUE_SIZE] = {0};
          strncpy(value, (const char *)param->write.value, param->write.len);
          internal_set_wifi_password(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(TIME)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_time(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(STATE)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_state(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(DEVICE_NAME)]) {
          char value[MAX_KVALUE_SIZE] = {0};
          strncpy(value, (const char *)param->write.value, param->write.len);
          internal_set_device_name(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(TIMER_TYPE)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_timer_type(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(STARTED_AT)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_started_at(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(ON_HOUR)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_on_hour(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(ON_MIN)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_on_min(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(OFF_HOUR)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_off_hour(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(OFF_MIN)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_off_min(value);
      }

  /*
   * [/GENERATED]
   */
}

void on_read(esp_ble_gatts_cb_param_t *param) {
}
