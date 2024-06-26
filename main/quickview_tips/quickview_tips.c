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
#include "quickview_tips.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/mqtt/mqtt.h"
#include "../core/kv/kv.h"
#include "../core/log/log.h"

#include "../sgl/sgl.h"
#include "../m5tft/app.h"

#include "./metrics_page.h"

typedef struct {
  uint8_t type;
  char text[];
} __attribute__ ((packed)) set_plant_date_event;

void updatePlantDateFn() {
  ESP_LOGI(SGO_LOG_NOSEND, "quickview update");
  uint8_t cmd = GET_PLANT_DATE;
  send_screen_message((char *)&cmd, 1);
}

void setPlantDateData(const char *msg, int len) {
  ESP_LOGI(SGO_LOG_NOSEND, "setPlantDateData");
  set_plant_date_event *evt = (set_plant_date_event *)msg;
  update_plant_date(evt->text);
  ESP_LOGI(SGO_LOG_NOSEND, "Set plant date event: text: %s", evt->text);
}

void init_quickview_tips() {
  ESP_LOGI(SGO_LOG_NOSEND, "@QUICKVIEW_SCREEN Initializing quickview_tips module");

  add_screen_init(init_metrics_page);
  set_command_update(GET_PLANT_DATE, updatePlantDateFn);
  set_command(SET_PLANT_DATE, setPlantDateData);
}

uint8_t on_set_quickview_tips_order(uint8_t value) {
  return value;
}
