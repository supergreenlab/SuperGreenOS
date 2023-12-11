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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"

#include "../m5tft/app.h"
#include "./graphs_page.h"

void init_graphs_screen() {
  ESP_LOGI(SGO_LOG_EVENT, "@GRAPHS_SCREEN Initializing graphs_screen module");

  add_screen_init(init_graphs_page);
}

uint8_t on_set_graphs_screen_order(uint8_t value) {
  return value;
}
