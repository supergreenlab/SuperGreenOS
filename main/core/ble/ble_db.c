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
const uint8_t I2C_SDA_UUID[ESP_UUID_LEN_128] = {0x9b,0x6a,0x3b,0xe2,0xaa,0xb4,0x33,0xaa,0x8a,0x4a,0x9e,0xe1,0x4f,0xee,0xf9,0x40};
const uint8_t I2C_SCL_UUID[ESP_UUID_LEN_128] = {0x9b,0x6a,0x3b,0xe2,0xaa,0xb4,0x33,0xaa,0x8a,0x4a,0x9e,0xe1,0x4f,0xee,0xf9,0x40};
const uint8_t STATE_UUID[ESP_UUID_LEN_128] = {0x94,0x28,0x12,0x63,0x56,0xde,0xec,0x43,0xb4,0xfe,0xd6,0x3b,0xd2,0xdf,0xf6,0x8f};
const uint8_t DEVICE_NAME_UUID[ESP_UUID_LEN_128] = {0x25,0x8b,0x4f,0x3d,0xf1,0x61,0xee,0x68,0x6e,0xee,0x0e,0x8c,0x32,0x77,0x31,0xa6};
const uint8_t TIMER_TYPE_UUID[ESP_UUID_LEN_128] = {0xf3,0xa9,0xfa,0xb2,0x5a,0x41,0x3d,0x34,0x7b,0x0a,0xa9,0x3a,0x40,0xa8,0x5e,0x5f};
const uint8_t TIMER_OUTPUT_UUID[ESP_UUID_LEN_128] = {0x89,0x57,0x36,0x6e,0x85,0xee,0x89,0xdb,0x67,0xa9,0x99,0x82,0x94,0x60,0x28,0xb2};
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
const uint8_t LED_0_DUTY_UUID[ESP_UUID_LEN_128] = {0x00,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x42};
const uint8_t LED_1_DUTY_UUID[ESP_UUID_LEN_128] = {0x01,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x42};
const uint8_t LED_2_DUTY_UUID[ESP_UUID_LEN_128] = {0x02,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x42};
const uint8_t LED_3_DUTY_UUID[ESP_UUID_LEN_128] = {0x03,0x61,0xeb,0x40,0x8c,0x1e,0x59,0x61,0x3a,0xa5,0x78,0x55,0xcd,0x31,0xb9,0x50};
const uint8_t LED_4_DUTY_UUID[ESP_UUID_LEN_128] = {0x04,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x42};
const uint8_t LED_5_DUTY_UUID[ESP_UUID_LEN_128] = {0x05,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x42};
const uint8_t LED_0_GPIO_UUID[ESP_UUID_LEN_128] = {0x00,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x43};
const uint8_t LED_1_GPIO_UUID[ESP_UUID_LEN_128] = {0x01,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x43};
const uint8_t LED_2_GPIO_UUID[ESP_UUID_LEN_128] = {0x02,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x43};
const uint8_t LED_3_GPIO_UUID[ESP_UUID_LEN_128] = {0x03,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x43};
const uint8_t LED_4_GPIO_UUID[ESP_UUID_LEN_128] = {0x04,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x43};
const uint8_t LED_5_GPIO_UUID[ESP_UUID_LEN_128] = {0x05,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x43};
const uint8_t LED_0_X_UUID[ESP_UUID_LEN_128] = {0x00,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x44};
const uint8_t LED_1_X_UUID[ESP_UUID_LEN_128] = {0x01,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x44};
const uint8_t LED_2_X_UUID[ESP_UUID_LEN_128] = {0x02,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x44};
const uint8_t LED_3_X_UUID[ESP_UUID_LEN_128] = {0x03,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x44};
const uint8_t LED_4_X_UUID[ESP_UUID_LEN_128] = {0x04,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x44};
const uint8_t LED_5_X_UUID[ESP_UUID_LEN_128] = {0x05,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x44};
const uint8_t LED_0_Y_UUID[ESP_UUID_LEN_128] = {0x00,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x45};
const uint8_t LED_1_Y_UUID[ESP_UUID_LEN_128] = {0x01,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x45};
const uint8_t LED_2_Y_UUID[ESP_UUID_LEN_128] = {0x02,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x45};
const uint8_t LED_3_Y_UUID[ESP_UUID_LEN_128] = {0x03,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x45};
const uint8_t LED_4_Y_UUID[ESP_UUID_LEN_128] = {0x04,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x45};
const uint8_t LED_5_Y_UUID[ESP_UUID_LEN_128] = {0x05,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x45};
const uint8_t LED_0_Z_UUID[ESP_UUID_LEN_128] = {0x00,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x45};
const uint8_t LED_1_Z_UUID[ESP_UUID_LEN_128] = {0x01,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x45};
const uint8_t LED_2_Z_UUID[ESP_UUID_LEN_128] = {0x02,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x45};
const uint8_t LED_3_Z_UUID[ESP_UUID_LEN_128] = {0x03,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x45};
const uint8_t LED_4_Z_UUID[ESP_UUID_LEN_128] = {0x04,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x45};
const uint8_t LED_5_Z_UUID[ESP_UUID_LEN_128] = {0x05,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x45};

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
    RW_I_NOTIFIABLE_CHAR(I2C_SDA),
    RW_I_NOTIFIABLE_CHAR(I2C_SCL),
    RW_I_NOTIFIABLE_CHAR(STATE),
    RW_STR_CHAR(DEVICE_NAME),
    RW_I_CHAR(TIMER_TYPE),
    R_I_NOTIFIABLE_CHAR(TIMER_OUTPUT),
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
    RW_I_NOTIFIABLE_CHAR(LED_0_DUTY),
    RW_I_NOTIFIABLE_CHAR(LED_1_DUTY),
    RW_I_NOTIFIABLE_CHAR(LED_2_DUTY),
    RW_I_NOTIFIABLE_CHAR(LED_3_DUTY),
    RW_I_NOTIFIABLE_CHAR(LED_4_DUTY),
    RW_I_NOTIFIABLE_CHAR(LED_5_DUTY),
    RW_I_CHAR(LED_0_GPIO),
    RW_I_CHAR(LED_1_GPIO),
    RW_I_CHAR(LED_2_GPIO),
    RW_I_CHAR(LED_3_GPIO),
    RW_I_CHAR(LED_4_GPIO),
    RW_I_CHAR(LED_5_GPIO),
    RW_I_CHAR(LED_0_X),
    RW_I_CHAR(LED_1_X),
    RW_I_CHAR(LED_2_X),
    RW_I_CHAR(LED_3_X),
    RW_I_CHAR(LED_4_X),
    RW_I_CHAR(LED_5_X),
    RW_I_CHAR(LED_0_Y),
    RW_I_CHAR(LED_1_Y),
    RW_I_CHAR(LED_2_Y),
    RW_I_CHAR(LED_3_Y),
    RW_I_CHAR(LED_4_Y),
    RW_I_CHAR(LED_5_Y),
    RW_I_CHAR(LED_0_Z),
    RW_I_CHAR(LED_1_Z),
    RW_I_CHAR(LED_2_Z),
    RW_I_CHAR(LED_3_Z),
    RW_I_CHAR(LED_4_Z),
    RW_I_CHAR(LED_5_Z),

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
       else if (param->write.handle == handle_table[IDX_VALUE(I2C_SDA)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_i2c_sda(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(I2C_SCL)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_i2c_scl(value);
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
       else if (param->write.handle == handle_table[IDX_VALUE(LED_0_DUTY)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_0_duty(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_1_DUTY)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_1_duty(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_2_DUTY)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_2_duty(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_3_DUTY)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_3_duty(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_4_DUTY)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_4_duty(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_5_DUTY)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_5_duty(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_0_GPIO)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_0_gpio(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_1_GPIO)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_1_gpio(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_2_GPIO)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_2_gpio(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_3_GPIO)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_3_gpio(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_4_GPIO)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_4_gpio(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_5_GPIO)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_5_gpio(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_0_X)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_0_x(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_1_X)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_1_x(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_2_X)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_2_x(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_3_X)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_3_x(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_4_X)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_4_x(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_5_X)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_5_x(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_0_Y)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_0_y(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_1_Y)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_1_y(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_2_Y)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_2_y(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_3_Y)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_3_y(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_4_Y)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_4_y(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_5_Y)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_5_y(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_0_Z)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_0_z(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_1_Z)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_1_z(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_2_Z)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_2_z(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_3_Z)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_3_z(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_4_Z)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_4_z(value);
      }
       else if (param->write.handle == handle_table[IDX_VALUE(LED_5_Z)]) {
          uint32_t value = *(uint32_t *)(&param->write.value[0]);
          internal_set_led_5_z(value);
      }

  /*
   * [/GENERATED]
   */
}

void on_read(esp_ble_gatts_cb_param_t *param) {
}
