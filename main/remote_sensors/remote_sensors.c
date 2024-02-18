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
#include "remote_sensors.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/mqtt/mqtt.h"
#include "../core/kv/kv.h"
#include "../core/log/log.h"

#include "../sgl/sgl.h"

typedef struct {
  uint8_t type;
  uint8_t temp;
  uint8_t humidity;
  uint8_t VPD;
  uint16_t CO2;
  uint32_t weight;
} __attribute__ ((packed)) set_remote_sensor_event;

void updateRemoteSensorsFn() {
  ESP_LOGI(SGO_LOG_NOSEND, "remote_sensor update");
  uint8_t cmd = GET_SENSORS;
  send_screen_message((char *)&cmd, 1);
}

void setRemoteSensorData(const char *msg, int len) {
  ESP_LOGI(SGO_LOG_NOSEND, "setPlantDateData");
  set_remote_sensor_event *evt = (set_remote_sensor_event *)msg;
  set_remote_sensors_temp(evt->temp);
  set_remote_sensors_humi(evt->humidity);
  set_remote_sensors_vpd(evt->VPD);
  set_remote_sensors_co2(evt->CO2);
  set_remote_sensors_weight(evt->weight);
}

void init_remote_sensors() {
  ESP_LOGI(SGO_LOG_EVENT, "@REMOTE_SENSORS Initializing remote_sensors module");

  set_command_update(GET_SENSORS, updateRemoteSensorsFn);
  set_command(SET_SENSORS, setRemoteSensorData);
}
