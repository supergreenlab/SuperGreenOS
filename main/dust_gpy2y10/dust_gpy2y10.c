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

#include "dust_gpy2y10.h"
#include "driver/i2c.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"
#include "../core/i2c/i2c.h"
#include "../box/box.h"

#define DUST_GP2Y10_ADDR 0x43
#define ACK_CHECK_EN 0x1
#define ACK_VAL 0x0
#define NACK_VAL 0x1

void init_dust_gpy2y10(int portId, int sda, int sck) {
  int boxId = portId;

  ESP_LOGI(SGO_LOG_EVENT, "@DUST_GP2Y10_%d Initializing dust_gpy2y10 i2c device\n", boxId);
}

void loop_dust_gpy2y10(int portId, int sda, int sck) {
  int boxId = portId;

  uint16_t v = 0;
	uint8_t nack;
  start_i2c();
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, DUST_GP2Y10_ADDR << 1 | I2C_MASTER_READ, ACK_CHECK_EN);

  i2c_master_read(cmd, (uint8_t*)&v, sizeof(v), ACK_VAL);
	i2c_master_read_byte(cmd, &nack, NACK_VAL);

	i2c_master_stop(cmd);

	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);

	if (ret == ESP_ERR_TIMEOUT) {
		ESP_LOGI(SGO_LOG_NOSEND, "@DUST_GPY2Y10_%d Bus is busy", boxId);
	} else if (ret != ESP_OK) {
		ESP_LOGI(SGO_LOG_NOSEND, "@DUST_GPY2Y10_%d Read failed", boxId);
	}
	ESP_LOGI(SGO_LOG_METRIC, "@DUST_GPY2Y10_%d dust=%d", boxId, v);
  set_box_dust_gpy2y10(portId, v);

  stop_i2c();
}
