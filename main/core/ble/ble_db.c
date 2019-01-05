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

static const uint16_t GATTS_SERVICE_UUID      = 0x00FF;

const esp_gatts_attr_db_t gatt_db[HRS_IDX_NB] = {
  [IDX_SVC]    =
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&primary_service_uuid, ESP_GATT_PERM_READ,
    sizeof(uint16_t), sizeof(GATTS_SERVICE_UUID), (uint8_t *)&GATTS_SERVICE_UUID}},

  /*
   * [GENERATED]
   */

  /*
   * [/GENERATED]
   */
};

void on_write(esp_ble_gatts_cb_param_t *param) {
  /*
   * [GENERATED]
   */

  /*
   * [/GENERATED]
   */
}

void on_read(esp_ble_gatts_cb_param_t *param) {
}
