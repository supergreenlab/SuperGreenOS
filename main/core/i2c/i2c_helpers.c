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

#include "i2c_helpers.h"

#include "i2c.h"
#include "../kv/kv.h"

#define I2C_CB(i2cId, param) int on_set_i2c_## i2cId ##_## param(int value) { \
  return on_set_i2c_## param(i2cId, value); \
}

#define I2C_GETTER(param) int get_i2c_## param(int i2cId) { \
  switch(i2cId) { \
    case 0: \
      return get_i2c_0_## param(i2cId); \
    case 1: \
      return get_i2c_1_## param(i2cId); \
  } \
  return 0; \
}

#define I2C_SETTER(param) void set_i2c_## param(int i2cId, int value) { \
  switch(i2cId) { \
    case 0: \
      set_i2c_0_## param(value); \
    case 1: \
      set_i2c_1_## param(value); \
  } \
}


I2C_SETTER(sda)
I2C_GETTER(sda)
I2C_SETTER(scl)
I2C_GETTER(scl)
I2C_SETTER(enabled)
I2C_GETTER(enabled)
