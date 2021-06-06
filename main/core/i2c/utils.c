/*
 * Copyright (C) 2021  SuperGreenLab <towelie@supergreenlab.com>
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

#include "i2c.h"

#include <stdint.h>
#include <stdbool.h>

#define ACK_CHECK_EN                1                   /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS               0                   /*!< I2C master will not check ack from slave */
#define ACK_VAL                     0x0                 /*!< I2C ack value */
#define NACK_VAL                    0x1                 /*!< I2C nack value */

i2c_err_t i2cWrite(int port, uint16_t address, uint8_t* buff, uint16_t size, bool sendStop, uint16_t timeOutMillis){
	esp_err_t ret = ESP_OK;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
	i2c_master_write(cmd, buff, size, ACK_CHECK_EN);
	//if send stop?
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(port, cmd, timeOutMillis / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	return ret;
}

i2c_err_t i2cRead(int port, uint16_t address, uint8_t* buff, uint16_t size, bool sendStop, uint16_t timeOutMillis, uint32_t *readCount){
	esp_err_t ret = ESP_OK;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_READ, ACK_CHECK_EN);
	if (size > 1) {
		i2c_master_read(cmd, buff, size - 1, ACK_VAL);
	}
	i2c_master_read_byte(cmd, buff + size - 1, NACK_VAL);
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(port, cmd, timeOutMillis / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
	if(ret == ESP_OK){
		*readCount = size;
	}
	return ret;
}
