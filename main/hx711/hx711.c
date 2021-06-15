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
#include "hx711.h"
#include "driver/i2c.h"

#include "../core/i2c/i2c.h"
#include "../core/kv/kv.h"
#include "../core/log/log.h"

#include "driver.h"

void init_hx711(int i2cId) {
  ESP_LOGI(SGO_LOG_EVENT, "@HX711 Initializing hx711 i2c device");
}

void loop_hx711(int i2cId) {
  int sda = get_i2c_sda(i2cId);
  int scl = get_i2c_scl(i2cId);
  hx711_t dev = {
    .dout = sda,
    .pd_sck = scl,
		.gain = HX711_GAIN_A_64
	};

	esp_err_t r = hx711_init(&dev);
	if (r == ESP_OK) {
		ESP_LOGW(SGO_LOG_NOSEND, "Could not initialize HX711: %d (%s)", r, esp_err_to_name(r));
		set_hx711_present(i2cId, 0);
		return;
	}
	vTaskDelay(500 / portTICK_PERIOD_MS);

	r = hx711_wait(&dev, 500);
	if (r != ESP_OK) {
		ESP_LOGW(SGO_LOG_NOSEND, "Device not found: %d (%s)", r, esp_err_to_name(r));
		set_hx711_present(i2cId, 0);
		return;
	}

	int32_t weight;
	r = hx711_read_data(&dev, &weight);
	if (r != ESP_OK) {
		ESP_LOGW(SGO_LOG_NOSEND, "Could not read data: %d (%s)", r, esp_err_to_name(r));
		set_hx711_present(i2cId, 0);
		return;
	}

	float divider = get_hx711_weight_calibration(i2cId);
	int offset = get_hx711_weight_offset(i2cId);
	weight += offset;
	weight /= divider;

	set_hx711_weight(i2cId, weight);
	set_hx711_present(i2cId, 1);
	ESP_LOGI(SGO_LOG_NOSEND, "Weight recorded: %d", weight);
}
