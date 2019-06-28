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
		ESP_LOGI(SGO_LOG_EVENT, "@SHT21_%d Write bus is busy", boxId);
		return false;
	} else if (ret != ESP_OK) {
		ESP_LOGI(SGO_LOG_EVENT, "@SHT21_%d Write failed", boxId);
		return false;
	}
	return true;
}

static bool crc_checksum(uint8_t data[], uint8_t no_of_bytes, uint8_t checksum);
static uint16_t read_sht21(int portId) {
  int boxId = portId;
  uint8_t v[3] = {0};

  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, SHT21_ADDR << 1 | I2C_MASTER_READ, ACK_CHECK_EN);
	i2c_master_read_byte(cmd, &v[0], ACK_VAL);
	i2c_master_read_byte(cmd, &v[1], ACK_VAL);
	i2c_master_read_byte(cmd, &v[2], NACK_VAL);
	i2c_master_stop(cmd);

	esp_err_t ret = i2c_master_cmd_begin(portId, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	if (ret == ESP_ERR_TIMEOUT) {
		ESP_LOGI(SGO_LOG_EVENT, "@SHT21_%d Read bus is busy", boxId);
		return 255;
	} else if (ret != ESP_OK) {
		ESP_LOGI(SGO_LOG_EVENT, "@SHT21_%d Read failed", boxId);
		return 255;
	}

	if(!crc_checksum(v, 2, v[2])) {
		//reset();
		ESP_LOGI(SGO_LOG_EVENT, "@SHT21_%d Wrong crc", boxId);
		return 255;
	}

	return (v[0] << 8) | v[1];
}

void loop_sht21(int portId, int sda, int sck) {
  int boxId = portId;

  start_i2c(portId);

	{
		if (!send_sht21_cmd(portId, TRIGGER_TEMP_MEASURE_NOHOLD)) {
			return;
		}
		vTaskDelay(100 / portTICK_RATE_MS);
		int16_t v = read_sht21(portId);
		if (v != 255) {
			v &= ~0x0003;
			float vd = -46.85 + 175.72 * (float)(v) / 65536.0;
			set_box_sht21_temp_c(boxId, vd);
			set_box_sht21_temp_f(boxId, vd * (9.0f/5.0f) + 32.0f);
		}
	}
	vTaskDelay(500 / portTICK_RATE_MS);
	{
		if (!send_sht21_cmd(portId, TRIGGER_HUMD_MEASURE_NOHOLD)) {
			return;
		}
		vTaskDelay(100 / portTICK_RATE_MS);
		uint16_t v = read_sht21(portId);
		if (v != 255) {
			v &= ~0x0003;
			float vd = -6.0 + 125.0 * (float)(v) / 65536.0;
			set_box_sht21_humi(boxId, vd);
		}
	}

  stop_i2c(portId);
}

const uint16_t POLYNOMIAL = 0x131;
static bool crc_checksum(uint8_t data[], uint8_t no_of_bytes, uint8_t checksum) {
	uint8_t crc = 0;
	uint8_t byteCtr;

	for (byteCtr = 0; byteCtr < no_of_bytes; ++byteCtr)
	{ crc ^= (data[byteCtr]);
		for (uint8_t bit = 8; bit > 0; --bit)
		{ if (crc & 0x80) crc = (crc << 1) ^ POLYNOMIAL;
			else crc = (crc << 1);
		}
	}
	return crc == checksum;
}
