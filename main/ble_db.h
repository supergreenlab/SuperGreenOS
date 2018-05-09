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

enum idx
{
    IDX_TIME_SVC,

    IDX_CHAR_TIME,
    IDX_CHAR_VAL_TIME,
    IDX_CHAR_CFG_TIME,

    IDX_CHAR_SIMULATED_TIME,
    IDX_CHAR_VAL_SIMULATED_TIME,
    IDX_CHAR_CFG_SIMULATED_TIME,

    IDX_CHAR_START_DATE_MONTH,
    IDX_CHAR_VAL_START_DATE_MONTH,

    IDX_CHAR_START_DATE_DAY,
    IDX_CHAR_VAL_START_DATE_DAY,

    IDX_CHAR_DURATION_DAYS,
    IDX_CHAR_VAL_DURATION_DAYS,

    IDX_CHAR_SIMULATION_DURATION_DAYS,
    IDX_CHAR_VAL_SIMULATION_DURATION_DAYS,

    IDX_CHAR_STARTED_AT,
    IDX_CHAR_VAL_STARTED_AT,

    HRS_IDX_NB,
};

extern const esp_gatts_attr_db_t gatt_db[HRS_IDX_NB];

#endif
