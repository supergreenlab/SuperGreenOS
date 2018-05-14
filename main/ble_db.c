/*
 * =====================================================================================
 *
 *       Filename:  ble_db.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/09/2018 11:58:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "ble_db.h"

#include "string.h"

#include "misc/log.h"
#include "core/ble_private.h"
#include "core/ble_utils.h"
#include "time/time.h"
#include "timers/timer.h"
#include "wifi/wifi.h"
#include "timers/onoff/onoff.h"
#include "timers/season/season.h"

static const uint16_t GATTS_SERVICE_UUID      = 0x00FF;

const esp_gatts_attr_db_t gatt_db[HRS_IDX_NB] = {
  // Time Service Declaration
  [IDX_SVC]    =
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&primary_service_uuid, ESP_GATT_PERM_READ,
    sizeof(uint16_t), sizeof(GATTS_SERVICE_UUID), (uint8_t *)&GATTS_SERVICE_UUID}},

  RW_I_NOTIFIABLE_CHAR(TIME),

  RW_I_NOTIFIABLE_CHAR(TIMER_TYPE),
  RW_I_NOTIFIABLE_CHAR(TIMER_OUTPUT),

  R_I_NOTIFIABLE_CHAR(SIMULATED_TIME),
  RW_I_CHAR(START_DATE_MONTH),
  RW_I_CHAR(START_DATE_DAY),
  RW_I_CHAR(DURATION_DAYS),
  RW_I_CHAR(SIMULATION_DURATION_DAYS),
  RW_I_CHAR(STARTED_AT),
  
  RW_I_CHAR(ON_HOUR),
  RW_I_CHAR(ON_MIN),
  RW_I_CHAR(OFF_HOUR),
  RW_I_CHAR(OFF_MIN),

  R_I_NOTIFIABLE_CHAR(WIFI_STATUS),
  RW_STR_CHAR(WIFI_SSID),
  RW_STR_CHAR(WIFI_PASS),
};

void on_write(esp_ble_gatts_cb_param_t *param) {
  ESP_LOGI(TAG, "on_write");

  // TIME SERVICE
  if (param->write.handle == handle_table[IDX_VALUE(TIME)]) {
    on_set_time(*(uint32_t *)(&param->write.value[0]));
  }
  
  else if (param->write.handle == handle_table[IDX_VALUE(TIMER_TYPE)]) {
    on_set_timer_type((enum timer)*(uint32_t *)(&param->write.value[0]));
  } else if (param->write.handle == handle_table[IDX_VALUE(TIMER_OUTPUT)]) {
    on_set_timer_output(*(uint32_t *)(&param->write.value[0]));
  }
  
  else if (param->write.handle == handle_table[IDX_VALUE(START_DATE_MONTH)]) {
    on_set_start_date_month(*(uint32_t *)(&param->write.value[0]));
  } else if (param->write.handle == handle_table[IDX_VALUE(START_DATE_DAY)]) {
    on_set_start_date_day(*(uint32_t *)(&param->write.value[0]));
  } else if (param->write.handle == handle_table[IDX_VALUE(DURATION_DAYS)]) {
    on_set_duration_days(*(uint32_t *)(&param->write.value[0]));
  } else if (param->write.handle == handle_table[IDX_VALUE(SIMULATION_DURATION_DAYS)]) {
    on_set_duration_days(*(uint32_t *)(&param->write.value[0]));
  } else if (param->write.handle == handle_table[IDX_VALUE(STARTED_AT)]) {
    on_set_started_at(*(uint32_t *)(&param->write.value[0]));
  }
  
  else if (param->write.handle == handle_table[IDX_VALUE(WIFI_SSID)]) {
    char ssid[32] = {0};
    strncpy(ssid, (const char *)param->write.value, param->write.len);
    on_set_wifi_ssid(ssid);
  } else if (param->write.handle == handle_table[IDX_VALUE(WIFI_PASS)]) {
    char pass[64] = {0};
    strncpy(pass, (const char *)param->write.value, param->write.len);
    on_set_wifi_password((const char *)param->write.value);
  }
}

void on_read(esp_ble_gatts_cb_param_t *param) {
  ESP_LOGI(TAG, "on_read");
}
