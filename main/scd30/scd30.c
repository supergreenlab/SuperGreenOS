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
#include <math.h>
#include "scd30.h"
#include "driver/i2c.h"

#include "driver.h"
#include "../core/i2c/i2c.h"
#include "../core/kv/kv.h"
#include "../core/log/log.h"

#define SCD30_ADDR 0x42

static scd30_handle scd30_handlers[N_SCD30] = {0};

void init_scd30(int i2cId) {
  ESP_LOGI(SGO_LOG_EVENT, "@SCD30 Initializing scd30 i2c device");

  start_i2c(i2cId);
	scd30_handle *s = &(scd30_handlers[i2cId]);
  s->port = get_i2c_port(i2cId);
  setTemperatureOffset(s, 3);
  stop_i2c(i2cId);
}

void loop_scd30(int i2cId) {
  start_i2c(i2cId);

	scd30_handle *s = &(scd30_handlers[i2cId]);
	if (!s->init) {
		if (begin(s)) {
			s->init = true;
			set_scd30_present(i2cId, 1);
		} else {
			set_scd30_present(i2cId, 0);
		}
	}
	if (s->init) {
		if (!readMeasurement(s)) {
			set_scd30_present(i2cId, 0);
		} else {
      // TODO DRY this with sht21 code
      float asvp = 610.78 * powf(2.71828, (float)s->temperature / (float)(s->temperature + 238.3) * 17.2694);

      float leaf_temp_offset = (float)get_scd30_vpd_leaf_offset(i2cId) / 10.0f;
      float ltemp = (float)s->temperature + leaf_temp_offset;
      float lsvp = 610.78 * powf(2.71828, ltemp / (ltemp + 238.3) * 17.2694);

      float vpd = lsvp - (asvp * (float)s->humidity / 100.0);
      set_scd30_temp(i2cId, roundf(s->temperature));
      set_scd30_humi(i2cId, roundf(s->humidity));
      set_scd30_vpd(i2cId, vpd / 100);

      set_scd30_co2(i2cId, s->co2);

      set_scd30_present(i2cId, 1);
    }
	}

  stop_i2c(i2cId);
}

