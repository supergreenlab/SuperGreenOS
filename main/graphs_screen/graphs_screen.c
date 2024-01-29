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
#include "graphs_screen.h"
#include "graphs_page.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/mqtt/mqtt.h"
#include "../core/kv/kv.h"
#include "../core/log/log.h"

#include "../sgl/sgl.h"
#include "../m5tft/app.h"

#include "./graphs_page.h"

typedef struct {
  uint8_t type;
  uint8_t metricType;
  uint8_t values[N_METRICS_VALUES];
} __attribute__ ((packed)) set_graphs_event;

void updateGraphsFn() {
  ESP_LOGI(SGO_LOG_NOSEND, "graphs update");
  uint8_t cmd = GET_METRICS;
  send_screen_message((char *)&cmd, 1);
}

void setGraphsData(const char *msg, int len) {
  ESP_LOGI(SGO_LOG_NOSEND, "setGraphsData");
  set_graphs_event *evt = (set_graphs_event *)msg;
  update_graphs(evt->metricType, evt->values);
}

void init_graphs_screen() {
  ESP_LOGI(SGO_LOG_EVENT, "@GRAPHS_SCREEN Initializing graphs_screen module");

  add_screen_init(init_graphs_page);
  set_command_update(GET_METRICS, updateGraphsFn);
  set_command(SET_METRICS, setGraphsData);
}

uint8_t on_set_graphs_screen_order(uint8_t value) {
  return value;
}
