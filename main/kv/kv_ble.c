/*
 * =====================================================================================
 *
 *       Filename:  kv_ble.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/09/2018 16:36:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string.h>

#include "../misc/log.h"
#include "./kv.h"
#include "./kv_ble.h"

#include "../ble/ble.h"

void sync_ble_i(const char *key, enum idx i) {
  int value = geti(key);
  set_attr_value(i, (const uint8_t *)&value, sizeof(int));
}

void sync_ble_str(const char *key, enum idx i) {
  char value[517] = {0};
  getstr(key, value, sizeof(value) - 1);
  ESP_LOGI(TAG, "%s = %s strlen(value) = %d", key, value, strlen(value));
  set_attr_value(i, (const uint8_t *)value, strlen(value));
}
