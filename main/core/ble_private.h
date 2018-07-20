/*
 * =====================================================================================
 *
 *       Filename:  ble_private.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/09/2018 11:24:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BLE_PRIVATE_H_
#define BLE_PRIVATE_H_

#include "esp_gatts_api.h"

void on_write(esp_ble_gatts_cb_param_t *param);
void on_read(esp_ble_gatts_cb_param_t *param);

#endif
