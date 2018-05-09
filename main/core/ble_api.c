/*
 * =====================================================================================
 *
 *       Filename:  ble_api.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/9/2018 15:47:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "ble.h"
#include "ble_utils.h"

void notify_handle(enum idx i, const uint8_t *notify_data, uint16_t notify_data_length) {
  if (profile_tab[PROFILE_APP_IDX].gatts_if == ESP_GATT_IF_NONE || profile_tab[PROFILE_APP_IDX].conn_id == UINT16_MAX) return;

  ESP_ERROR_CHECK(esp_ble_gatts_send_indicate(profile_tab[PROFILE_APP_IDX].gatts_if, profile_tab[PROFILE_APP_IDX].conn_id, handle_table[i], notify_data_length, (uint8_t *)notify_data, false));
}

void set_attr_value(enum idx i, const uint8_t *value, uint16_t value_length) {
  ESP_ERROR_CHECK(esp_ble_gatts_set_attr_value(handle_table[i], value_length, value));
}

void notify_attr(enum idx i) {
  if (profile_tab[PROFILE_APP_IDX].gatts_if == ESP_GATT_IF_NONE || profile_tab[PROFILE_APP_IDX].conn_id == UINT16_MAX) return;

  const uint8_t *value;
  uint16_t value_length;
  
  ESP_ERROR_CHECK(esp_ble_gatts_get_attr_value(handle_table[i], &value_length, &value));
  notify_handle(i, value, value_length);
}
