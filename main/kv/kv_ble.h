/*
 * =====================================================================================
 *
 *       Filename:  kv_ble.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/09/2018 16:33:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef KV_BLE_H_
#define KV_BLE_H_

#include "../conf/ble_db.h"

void sync_ble_i(const char *key, enum idx i);
void sync_ble_str(const char *key, enum idx i);

#endif
