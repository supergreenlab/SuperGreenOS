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

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "../log/log.h"
#include "nvs_flash.h"
#include "esp_bt.h"

#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"

#include "ble.h"
#include "ble_utils.h"
#include "ble_private.h"
#include "ble_db.h"
#include "../kv/kv.h"
#include "../kv/kv_ble.h"

#define ESP_APP_ID          0x55
#define BLE_DEVICE_NAME "🤖🍁"
#define SVC_INST_ID         0

#define ADV_CONFIG_FLAG       (1 << 0)
#define SCAN_RSP_CONFIG_FLAG    (1 << 1)

static uint8_t adv_config_done     = 0;

uint16_t handle_table[HRS_IDX_NB];

static uint8_t service_uuid[16] = {
	0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
};

/* The length of adv data must be less than 31 bytes */
static esp_ble_adv_data_t adv_data = {
  .set_scan_rsp    = false,
  .include_name    = true,
  .include_txpower   = true,
  .min_interval    = 0x20,
  .max_interval    = 0x40,
  .appearance      = 0x00,
  .manufacturer_len  = 0, //sizeof(manufacturer),
  .p_manufacturer_data = NULL, //manufacturer,
  .service_data_len  = 0,
  .p_service_data    = NULL,
  .service_uuid_len  = sizeof(service_uuid),
  .p_service_uuid    = service_uuid,
  .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

// scan response data
static esp_ble_adv_data_t scan_rsp_data = {
  .set_scan_rsp    = true,
  .include_name    = true,
  .include_txpower   = true,
  .min_interval    = 0x20,
  .max_interval    = 0x40,
  .appearance      = 0x00,
  .manufacturer_len  = 0, //sizeof(manufacturer),
  .p_manufacturer_data = NULL, //manufacturer,
  .service_data_len  = 0,
  .p_service_data    = NULL,
  .service_uuid_len  = sizeof(service_uuid),
  .p_service_uuid    = service_uuid,
  .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

static esp_ble_adv_params_t adv_params = {
  .adv_int_min     = 0x20,
  .adv_int_max     = 0x40,
  .adv_type      = ADV_TYPE_IND,
  .own_addr_type     = BLE_ADDR_TYPE_PUBLIC,
  .channel_map     = ADV_CHNL_ALL,
  .adv_filter_policy   = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

static void gatts_profile_event_handler(esp_gatts_cb_event_t event,
					esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);

/* One gatt-based profile one app_id and one gatts_if, this array will store the gatts_if returned by ESP_GATTS_REG_EVT */
struct gatts_profile_inst profile_tab[PROFILE_NUM] = {
  [PROFILE_APP_IDX] = {
    .gatts_cb = gatts_profile_event_handler,
    .gatts_if = ESP_GATT_IF_NONE,     /* Not get the gatt_if, so initial is ESP_GATT_IF_NONE */
    .conn_id = UINT16_MAX,
  },
};

const uint16_t primary_service_uuid     = ESP_GATT_UUID_PRI_SERVICE;
const uint16_t character_declaration_uuid   = ESP_GATT_UUID_CHAR_DECLARE;
const uint16_t character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
const uint8_t char_prop_read        =  ESP_GATT_CHAR_PROP_BIT_READ;
const uint8_t char_prop_read_write         = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE;
const uint8_t char_prop_read_write_notify   = ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
const uint8_t char_prop_read_notify   = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
const uint8_t client_configuration[2]    = {0x01, 0x00};
const uint8_t i_char_value[4]         = {0x00, 0x0, 0x0, 0x0};
const uint8_t str_char_value[1]         = {0};

/* Full Database Description - Used to add attributes into the database */
static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
  switch (event) {
    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
      adv_config_done &= (~ADV_CONFIG_FLAG);
      if (adv_config_done == 0){
        esp_ble_gap_start_advertising(&adv_params);
      }
      break;
    case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
      adv_config_done &= (~SCAN_RSP_CONFIG_FLAG);
      if (adv_config_done == 0){
        esp_ble_gap_start_advertising(&adv_params);
      }
      break;
    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
      /* advertising start complete event to indicate advertising start successfully or failed */
      if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
        ESP_LOGE(SGO_LOG_EVENT, "@BLE Advertising start failed");
      }else{
        ESP_LOGI(SGO_LOG_EVENT, "@BLE Advertising start successfully");
      }
      break;
    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
      if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
        ESP_LOGE(SGO_LOG_EVENT, "@BLE Advertising stop failed");
      }
      else {
        ESP_LOGI(SGO_LOG_EVENT, "@BLE Stop adv successfully\n");
      }
      break;
    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
      ESP_LOGI(SGO_LOG_EVENT, "@BLE Update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
          param->update_conn_params.status,
          param->update_conn_params.min_int,
          param->update_conn_params.max_int,
          param->update_conn_params.conn_int,
          param->update_conn_params.latency,
          param->update_conn_params.timeout);
      break;
    default:
      break;
  }
}

static void gatts_profile_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{
  switch (event) {
    case ESP_GATTS_REG_EVT:{
      esp_err_t set_dev_name_ret = esp_ble_gap_set_device_name(BLE_DEVICE_NAME);
      if (set_dev_name_ret){
        ESP_LOGE(SGO_LOG_EVENT, "@BLE Set device name failed, error code = %x", set_dev_name_ret);
      }
      //config adv data
      esp_err_t ret = esp_ble_gap_config_adv_data(&adv_data);
      if (ret){
        ESP_LOGE(SGO_LOG_EVENT, "@BLE Config adv data failed, error code = %x", ret);
      }
      adv_config_done |= ADV_CONFIG_FLAG;
      //config scan response data
      ret = esp_ble_gap_config_adv_data(&scan_rsp_data);
      if (ret){
        ESP_LOGE(SGO_LOG_EVENT, "Config scan response data failed, error code = %x", ret);
      }
      adv_config_done |= SCAN_RSP_CONFIG_FLAG;
      esp_err_t create_attr_ret = esp_ble_gatts_create_attr_tab(gatt_db, gatts_if, HRS_IDX_NB, SVC_INST_ID);
      if (create_attr_ret){
        ESP_LOGE(SGO_LOG_EVENT, "@BLE Create attr table failed, error code = %x", create_attr_ret);
      }
    }
     	  break;
    case ESP_GATTS_READ_EVT:
      ESP_LOGI(SGO_LOG_EVENT, "@BLE ESP_GATTS_READ_EVT");
      on_read(param);
     	break;
    case ESP_GATTS_WRITE_EVT:
      if (!param->write.is_prep){
        // the data length of gattc write  must be less than GATTS_DEMO_CHAR_VAL_LEN_MAX.
        ESP_LOGI(SGO_LOG_EVENT, "@BLE GATT_WRITE_EVT, handle = %d, value len = %d, value :", param->write.handle, param->write.len);
        esp_log_buffer_hex(SGO_LOG_EVENT, param->write.value, param->write.len);
        on_write(param);
        /* send response when param->write.need_rsp is true*/
        if (param->write.need_rsp){
          esp_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, ESP_GATT_OK, NULL);
        }
      }else{
        /* handle prepare write */
        ESP_LOGI(SGO_LOG_EVENT, "@BLE GATT_WRITE_EVT IS_PREP, handle = %d, value len = %d, value :", param->write.handle, param->write.len);
      }
    	  break;
    case ESP_GATTS_EXEC_WRITE_EVT: 
      // the length of gattc prapare write data must be less than GATTS_DEMO_CHAR_VAL_LEN_MAX. 
      ESP_LOGI(SGO_LOG_EVENT, "@BLE ESP_GATTS_EXEC_WRITE_EVT");
      break;
    case ESP_GATTS_MTU_EVT:
      ESP_LOGI(SGO_LOG_EVENT, "@BLE ESP_GATTS_MTU_EVT, MTU = %d", param->mtu.mtu);
      break;
    case ESP_GATTS_CONF_EVT:
      ESP_LOGI(SGO_LOG_EVENT, "@BLE ESP_GATTS_CONF_EVT, status = %d", param->conf.status);
      break;
    case ESP_GATTS_START_EVT:
      ESP_LOGI(SGO_LOG_EVENT, "@BLE SERVICE_START_EVT, status = %d, service_handle = %d", param->start.status, param->start.service_handle);
      break;
    case ESP_GATTS_CONNECT_EVT:
      ESP_LOGI(SGO_LOG_EVENT, "@BLE ESP_GATTS_CONNECT_EVT, conn_id = %d", param->write.conn_id);
      esp_log_buffer_hex(SGO_LOG_EVENT, param->connect.remote_bda, 6);

      profile_tab[PROFILE_APP_IDX].conn_id = param->write.conn_id;

      esp_ble_conn_update_params_t conn_params = {0};
      memcpy(conn_params.bda, param->connect.remote_bda, sizeof(esp_bd_addr_t));
      /* For the IOS system, please reference the apple official documents about the ble connection parameters restrictions. */
      conn_params.latency = 0;
      conn_params.max_int = 0x20;  // max_int = 0x20*1.25ms = 40ms
      conn_params.min_int = 0x10;  // min_int = 0x10*1.25ms = 20ms
      conn_params.timeout = 400;  // timeout = 400*10ms = 4000ms
      //start sent the update connection parameters to the peer device.
      esp_ble_gap_update_conn_params(&conn_params);
      break;
    case ESP_GATTS_DISCONNECT_EVT:
      ESP_LOGI(SGO_LOG_EVENT, "@BLE ESP_GATTS_DISCONNECT_EVT, reason = %d", param->disconnect.reason);
      esp_ble_gap_start_advertising(&adv_params);
      profile_tab[PROFILE_APP_IDX].conn_id = UINT16_MAX;
      break;
    case ESP_GATTS_CREAT_ATTR_TAB_EVT:{
      if (param->add_attr_tab.status != ESP_GATT_OK){
        ESP_LOGE(SGO_LOG_EVENT, "@BLE Create attribute table failed, error code = 0x%x", param->add_attr_tab.status);
      }
      else if (param->add_attr_tab.num_handle != HRS_IDX_NB){
        ESP_LOGE(SGO_LOG_EVENT, "@BLE Create attribute table abnormally, num_handle = (%d), \
            doesn't equal to HRS_IDX_NB(%d)", param->add_attr_tab.num_handle, HRS_IDX_NB);
      }
      else {
        ESP_LOGI(SGO_LOG_EVENT, "@BLE Create attribute table successfully, the number handle = %d\n",param->add_attr_tab.num_handle);
        memcpy(handle_table, param->add_attr_tab.handles, sizeof(handle_table));
        esp_ble_gatts_start_service(handle_table[IDX_SVC]);
      }
      break;
    }
    case ESP_GATTS_STOP_EVT:
    case ESP_GATTS_OPEN_EVT:
    case ESP_GATTS_CANCEL_OPEN_EVT:
    case ESP_GATTS_CLOSE_EVT:
    case ESP_GATTS_LISTEN_EVT:
    case ESP_GATTS_CONGEST_EVT:
    case ESP_GATTS_UNREG_EVT:
    case ESP_GATTS_DELETE_EVT:
    default:
      break;
  }
}

static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{

  /* If event is register event, store the gatts_if for each profile */
  if (event == ESP_GATTS_REG_EVT) {
    if (param->reg.status == ESP_GATT_OK) {
      profile_tab[PROFILE_APP_IDX].gatts_if = gatts_if;
    } else {
      ESP_LOGE(SGO_LOG_EVENT, "@BLE Reg app failed, app_id = %04x, status = %d",
          param->reg.app_id,
          param->reg.status);
      return;
    }
  }
  do {
    int idx;
    for (idx = 0; idx < PROFILE_NUM; idx++) {
      /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
      if (gatts_if == ESP_GATT_IF_NONE || gatts_if == profile_tab[idx].gatts_if) {
        if (profile_tab[idx].gatts_cb) {
          profile_tab[idx].gatts_cb(event, gatts_if, param);
        }
      }
    }
  } while (0);
}

void init_ble()
{
  esp_err_t ret;

  ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));

  esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
  ret = esp_bt_controller_init(&bt_cfg);
  if (ret) {
    ESP_LOGE(SGO_LOG_EVENT, "@BLE enable controller failed: %s", esp_err_to_name(ret));
    return;
  }

  ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
  if (ret) {
    ESP_LOGE(SGO_LOG_EVENT, "@BLE enable controller failed: %s", esp_err_to_name(ret));
    return;
  }

  ret = esp_bluedroid_init();
  if (ret) {
    ESP_LOGE(SGO_LOG_EVENT, "@BLE init bluetooth failed: %s", esp_err_to_name(ret));
    return;
  }

  ret = esp_bluedroid_enable();
  if (ret) {
    ESP_LOGE(SGO_LOG_EVENT, "@BLE Enable bluetooth failed: %s", esp_err_to_name(ret));
    return;
  }

  ret = esp_ble_gatts_register_callback(gatts_event_handler);
  if (ret){
    ESP_LOGE(SGO_LOG_EVENT, "@BLE Gatts register error, error code = %x", ret);
    return;
  }

  ret = esp_ble_gap_register_callback(gap_event_handler);
  if (ret){
    ESP_LOGE(SGO_LOG_EVENT, "@BLE Gap register error, error code = %x", ret);
    return;
  }

  ret = esp_ble_gatts_app_register(ESP_APP_ID);
  if (ret){
    ESP_LOGE(SGO_LOG_EVENT, "@BLE Gatts app register error, error code = %x", ret);
    return;
  }
}
