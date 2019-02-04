/*
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

#include <stdlib.h>
#include "sht21.h"
#include "driver/i2c.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"
#include "../core/i2c/i2c.h"
#include "../box/box.h"

#define TRIGGER_TEMP_MEASURE_NOHOLD  0xF3
#define TRIGGER_HUMD_MEASURE_NOHOLD  0xF5
#define SHT21_ADDR 0x40
#define ACK_CHECK_EN 0x1
#define ACK_VAL 0x0
#define NACK_VAL 0x1

static uint16_t read_sht21(int portId);

void init_sht21(int portId, int sda, int sck) {
  ESP_LOGI(SGO_LOG_EVENT, "@SHT21 Initializing sht21 i2c device\n");
  // TODO: write you setup code here
}

static float get_humidity(int portId)
{
	uint16_t v = read_sht21(portId);
	return ;
}

static float get_temperature(int portId)
{
	uint16_t v = read_sht21(portId);
	return ;
}

static bool send_sht21_cmd(int portId, uint8_t cmd_b) {
  int boxId = portId;

  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, SHT21_ADDR << 1 | I2C_MASTER_WRITE, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, cmd_b, ACK_CHECK_EN);
	i2c_master_stop(cmd);

	esp_err_t ret = i2c_master_cmd_begin(portId, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	if (ret == ESP_ERR_TIMEOUT) {
		ESP_LOGI(SGO_LOG_NOSEND, "@SHT21_%d Bus is busy", boxId);
		return false;
	} else if (ret != ESP_OK) {
		ESP_LOGI(SGO_LOG_NOSEND, "@SHT21_%d Write failed", boxId);
		return false;
	}
	ESP_LOGI(SGO_LOG_NOSEND, "@SHT21_%d Write OK", boxId);
	return true;
}

static uint16_t read_sht21(int portId) {
  int boxId = portId;
	uint8_t cs = 0;
  uint16_t v = 0;

  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, SHT21_ADDR << 1 | I2C_MASTER_READ, ACK_CHECK_EN);
	i2c_master_read(cmd, (uint8_t*)&v, sizeof(v), ACK_VAL);
	i2c_master_read_byte(cmd, &cs, NACK_VAL);
	i2c_master_stop(cmd);

	esp_err_t ret = i2c_master_cmd_begin(portId, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	if (ret == ESP_ERR_TIMEOUT) {
		ESP_LOGI(SGO_LOG_NOSEND, "@SHT21_%d Bus is busy", boxId);
		return 255;
	} else if (ret != ESP_OK) {
		ESP_LOGI(SGO_LOG_NOSEND, "@SHT21_%d Read failed", boxId);
		return 255;
	}

	return v;
}

void loop_sht21(int portId, int sda, int sck) {
	static int state = 0;
  int boxId = portId;

  start_i2c(portId);

	if (state == 0) {
		if (send_sht21_cmd(portId, TRIGGER_TEMP_MEASURE_NOHOLD)) {
			state = 1;
		}
	} else if (state == 1) {
		uint16_t v = read_sht21(portId);
		if (v != 255) {
			v = (-46.85 + 175.72 / 65536.0 * (float)(v));
			ESP_LOGI(SGO_LOG_METRIC, "@SHT21_%d temp=%d", boxId, v);
			state = 2;
		}
	} else if (state == 2) {
		if (send_sht21_cmd(portId, TRIGGER_HUMD_MEASURE_NOHOLD)) {
			state = 3;
		}
	} else if (state == 3) {
		uint16_t v = read_sht21(portId);
		if (v != 255) {
			v = (-6.0 + 125.0 / 65536.0 * (float)(v));
			ESP_LOGI(SGO_LOG_METRIC, "@SHT21_%d humi=%d", boxId, v);
			state = 4;
		}
	}

  stop_i2c(portId);
}
