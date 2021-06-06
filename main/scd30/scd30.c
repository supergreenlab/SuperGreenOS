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
#include "scd30.h"
#include "driver/i2c.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"

#define SCD30_ADDR 0x42

void init_scd30(int i2cId) {
  ESP_LOGI(SGO_LOG_EVENT, "@SCD30 Initializing scd30 i2c device\n");
}

void loop_scd30(int i2cId) {
  start_i2c();
  stop_i2c();
}

