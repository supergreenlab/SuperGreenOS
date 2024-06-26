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

#include "timelapses_screen.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/mqtt/mqtt.h"
#include "../core/kv/kv.h"
#include "../core/log/log.h"

#include "../sgl/sgl.h"
#include "../m5tft/app.h"

#include "./timelapses_page.h"

typedef struct {
  uint8_t type;
  uint32_t offset;
  uint16_t len;
  uint8_t colors[];
} __attribute__ ((packed)) set_timelapses_event;

void setTimelapseData(const char *msg, int len) {
  ESP_LOGI(SGO_LOG_NOSEND, "Set timelapse data");
  set_timelapses_event *evt = (set_timelapses_event *)msg;
  update_timelapse_frame(evt->offset, evt->len, evt->colors);
}

typedef struct {
  uint8_t type;
  uint16_t len;
  color_t colors[];
} __attribute__ ((packed)) set_timelapses_palette_event;

void setTimelapsePalette(const char *msg, int len) {
  set_timelapses_palette_event *evt = (set_timelapses_palette_event *)msg;
  ESP_LOGI(SGO_LOG_NOSEND, "Set timelapse palette %d", evt->len);
  update_timelapse_palette(evt->len, evt->colors);
}

int timelapseUpdatesCount = 0;

void updateTimelapseFn() {
  if (!(timelapseUpdatesCount % 60 == 0)) {
    timelapseUpdatesCount++;
    ESP_LOGI(SGO_LOG_NOSEND, "Skipping timelapse update");
    return;
  }
  timelapseUpdatesCount++;
  ESP_LOGI(SGO_LOG_NOSEND, "timelapse update");
  uint8_t cmd = GET_TIMELAPSE;
  send_screen_message((char *)&cmd, 1);
}

void init_timelapses_screen() {
  ESP_LOGI(SGO_LOG_NOSEND, "@TIMELAPSES_SCREEN Initializing timelapses_screen module");

  add_screen_init(init_timelapses_page);
  set_command_update(GET_TIMELAPSE, updateTimelapseFn);
  set_command(SET_TIMELAPSE, setTimelapseData);
  set_command(SET_TIMELAPSE_PALETTE, setTimelapsePalette);
}

uint8_t on_set_timelapses_screen_order(uint8_t value) {
  return value;
}
