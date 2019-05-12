/*
 * Copyright (C) 2019  SuperGreenLab <towelie@supergreenlab.com>
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

#include "arduino_co2.h"
#include "driver/i2c.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"
#include "../core/i2c/i2c.h"
#include "../box/box.h"

#define ARDUINO_CO2_ADDR 0x42
#define ACK_CHECK_EN 0x1
#define ACK_VAL 0x0
#define NACK_VAL 0x1

void init_arduino_co2(int portId, int sca, int sdk) {
  int boxId = portId;

  ESP_LOGI(SGO_LOG_EVENT, "@ARDUINO_CO2_%d Initializing arduino_co2 i2c device\n", boxId);
}

void loop_arduino_co2(int portId, int sda, int sck) {
  int boxId = portId; // TODO this will not do it for 3 boxes, we only have 2 i2c ports. That's good enough for now (we only do max 2 boxes in our kits, and the 2 vegs can be processed with one blower).

  uint16_t v = 0;
	uint8_t nack;
  start_i2c(portId);
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, ARDUINO_CO2_ADDR << 1 | I2C_MASTER_READ, ACK_CHECK_EN);

  i2c_master_read(cmd, (uint8_t*)&v, sizeof(v), ACK_VAL);
	i2c_master_read_byte(cmd, &nack, NACK_VAL);

	i2c_master_stop(cmd);

	esp_err_t ret = i2c_master_cmd_begin(portId, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);

	if (ret == ESP_ERR_TIMEOUT) {
		ESP_LOGI(SGO_LOG_NOSEND, "@ARDUINO_CO2_%d Bus is busy", boxId);
	} else if (ret != ESP_OK) {
		ESP_LOGI(SGO_LOG_NOSEND, "@ARDUINO_CO2_%d Read failed", boxId);
	}
	ESP_LOGI(SGO_LOG_METRIC, "@ARDUINO_CO2_%d co2=%d", boxId, v);
  set_box_arduino_co2(boxId, v);

  stop_i2c(portId);
}
