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

#ifndef I2C_H_
#define I2C_H_

#include "driver/i2c.h"

void init_i2c();
void start_i2c(int portId);
void stop_i2c(int portId);

typedef enum {
	I2C_ERROR_OK=0,
	I2C_ERROR_DEV,
	I2C_ERROR_ACK,
	I2C_ERROR_TIMEOUT,
	I2C_ERROR_BUS,
	I2C_ERROR_BUSY,
	I2C_ERROR_MEMORY,
	I2C_ERROR_CONTINUE,
	I2C_ERROR_NO_BEGIN
} i2c_err_t;

i2c_err_t i2cWrite(int port, uint16_t address, uint8_t* buff, uint16_t size, bool sendStop, uint16_t timeOutMillis);
i2c_err_t i2cRead(int port, uint16_t address, uint8_t* buff, uint16_t size, bool sendStop, uint16_t timeOutMillis, uint32_t *readCount);

#endif
