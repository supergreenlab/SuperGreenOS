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

#ifndef BLE_UTILS_H_
#define BLE_UTILS_H_

#include "ble.h"
#include "esp_gatts_api.h"

#define PROFILE_NUM         1

struct gatts_profile_inst {
  esp_gatts_cb_t gatts_cb;
  uint16_t gatts_if;
  uint16_t app_id;
  uint16_t conn_id;
  uint16_t service_handle;
  esp_gatt_srvc_id_t service_id;
  uint16_t char_handle;
  esp_bt_uuid_t char_uuid;
  esp_gatt_perm_t perm;
  esp_gatt_char_prop_t property;
  uint16_t descr_handle;
  esp_bt_uuid_t descr_uuid;
};

#define CHAR_DECLARATION_SIZE     (0)
#define CHAR_VAL_LEN_MAX 517

// I

#define RW_I_NOTIFIABLE_CHAR(name) [IDX_CHAR_##name]   =  \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ, \
    CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read_write_notify}}, \
  \
  [IDX_CHAR_VAL_##name] = \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_128, (uint8_t *)&( name ## _UUID), ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE, \
    sizeof(i_char_value), sizeof(i_char_value), (uint8_t *)i_char_value}}, \
  \
  [IDX_CHAR_CFG_##name]  = \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE, \
    sizeof(uint16_t), sizeof(client_configuration), (uint8_t *)client_configuration}}

//

#define R_I_NOTIFIABLE_CHAR(name) [IDX_CHAR_##name]   =  \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ, \
    CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read_notify}}, \
  \
  [IDX_CHAR_VAL_##name] = \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_128, (uint8_t *)&( name ## _UUID), ESP_GATT_PERM_READ, \
    sizeof(i_char_value), sizeof(i_char_value), (uint8_t *)i_char_value}}, \
  \
  [IDX_CHAR_CFG_##name]  = \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE, \
    sizeof(uint16_t), sizeof(client_configuration), (uint8_t *)client_configuration}}

//

#define RW_I_CHAR(name) [IDX_CHAR_##name]   =  \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ, \
    CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read_write}}, \
  \
  [IDX_CHAR_VAL_##name] = \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_128, (uint8_t *)&( name ## _UUID), ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE, \
    sizeof(i_char_value), sizeof(i_char_value), (uint8_t *)i_char_value}}

//

#define R_I_CHAR(name) [IDX_CHAR_##name]   =  \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ, \
    CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}}, \
  \
  [IDX_CHAR_VAL_##name] = \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_128, (uint8_t *)&( name ## _UUID), ESP_GATT_PERM_READ, \
    sizeof(i_char_value), sizeof(i_char_value), (uint8_t *)i_char_value}}

// STR

#define RW_STR_NOTIFIABLE_CHAR(name) [IDX_CHAR_##name]   =  \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ, \
    CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read_write_notify}}, \
  \
  [IDX_CHAR_VAL_##name] = \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_128, (uint8_t *)&( name ## _UUID), ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE, \
    CHAR_VAL_LEN_MAX, sizeof(str_char_value), (uint8_t *)str_char_value}}, \
  \
  [IDX_CHAR_CFG_##name]  = \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE, \
    sizeof(uint16_t), sizeof(client_configuration), (uint8_t *)client_configuration}}

//

#define R_STR_NOTIFIABLE_CHAR(name) [IDX_CHAR_##name]   =  \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ, \
    CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read_notify}}, \
  \
  [IDX_CHAR_VAL_##name] = \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_128, (uint8_t *)&( name ## _UUID), ESP_GATT_PERM_READ, \
    CHAR_VAL_LEN_MAX, sizeof(str_char_value), (uint8_t *)str_char_value}}, \
  \
  [IDX_CHAR_CFG_##name]  = \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE, \
    sizeof(uint16_t), sizeof(client_configuration), (uint8_t *)client_configuration}}

//

#define RW_STR_CHAR(name) [IDX_CHAR_##name]   =  \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ, \
    CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read_write}}, \
  \
  [IDX_CHAR_VAL_##name] = \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_128, (uint8_t *)&( name ## _UUID), ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE, \
    CHAR_VAL_LEN_MAX, sizeof(str_char_value), (uint8_t *)str_char_value}}

//

#define R_STR_CHAR(name) [IDX_CHAR_##name]   =  \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ, \
    CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read}}, \
  \
  [IDX_CHAR_VAL_##name] = \
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_128, (uint8_t *)&( name ## _UUID), ESP_GATT_PERM_READ, \
    CHAR_VAL_LEN_MAX, sizeof(str_char_value), (uint8_t *)str_char_value}}

#define PROFILE_APP_IDX       0

extern uint16_t handle_table[HRS_IDX_NB];
extern struct gatts_profile_inst profile_tab[PROFILE_NUM];
extern const esp_gatts_attr_db_t gatt_db[HRS_IDX_NB];

extern const uint16_t primary_service_uuid;
extern const uint16_t character_declaration_uuid;
extern const uint16_t character_client_config_uuid;
extern const uint8_t char_prop_read;
extern const uint8_t char_prop_read_write;
extern const uint8_t char_prop_read_write_notify;
extern const uint8_t char_prop_read_notify;
extern const uint8_t client_configuration[2];
extern const uint8_t i_char_value[4];
extern const uint8_t str_char_value[1];

#endif
