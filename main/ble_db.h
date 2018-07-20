/*
 * =====================================================================================
 *
 *       Filename:  ble_db.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/09/2018 11:57:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BLE_DB_H_
#define BLE_DB_H_

#include "esp_gatts_api.h"

#define CHAR_VAL(name) IDX_CHAR_##name, \
  IDX_CHAR_VAL_##name

#define CHAR_VAL_CFG(name) IDX_CHAR_##name, \
  IDX_CHAR_VAL_##name, \
  IDX_CHAR_CFG_##name

#define IDX(name) IDX_CHAR_##name
#define IDX_VALUE(name) IDX_CHAR_VAL_##name
#define IDX_CFG(name) IDX_CHAR_CFG_##name

enum idx
{
  IDX_SVC,

  CHAR_VAL_CFG(DEVICE_NAME),

  CHAR_VAL_CFG(TIME),

  CHAR_VAL_CFG(STATE),

  CHAR_VAL_CFG(LED_0_0_PWR),
  CHAR_VAL_CFG(LED_0_1_PWR),
  CHAR_VAL_CFG(LED_0_2_PWR),
  CHAR_VAL_CFG(LED_1_0_PWR),
  CHAR_VAL_CFG(LED_1_1_PWR),
  CHAR_VAL_CFG(LED_1_2_PWR),

  CHAR_VAL_CFG(LED_0_0_DUTY),
  CHAR_VAL_CFG(LED_0_1_DUTY),
  CHAR_VAL_CFG(LED_0_2_DUTY),
  CHAR_VAL_CFG(LED_1_0_DUTY),
  CHAR_VAL_CFG(LED_1_1_DUTY),
  CHAR_VAL_CFG(LED_1_2_DUTY),

  CHAR_VAL(TIMER_TYPE),
  CHAR_VAL_CFG(TIMER_OUTPUT),

  CHAR_VAL_CFG(SIMULATED_TIME),
  CHAR_VAL(START_DATE_MONTH),
  CHAR_VAL(START_DATE_DAY),
  CHAR_VAL(DURATION_DAYS),
  CHAR_VAL(SIMULATION_DURATION_DAYS),
  CHAR_VAL(STARTED_AT),

  CHAR_VAL(ON_HOUR),
  CHAR_VAL(ON_MIN),
  CHAR_VAL(OFF_HOUR),
  CHAR_VAL(OFF_MIN),

  CHAR_VAL_CFG(WIFI_STATUS),
  CHAR_VAL(WIFI_SSID),
  CHAR_VAL(WIFI_PASS),

  HRS_IDX_NB,
};

extern const esp_gatts_attr_db_t gatt_db[HRS_IDX_NB];

#endif
