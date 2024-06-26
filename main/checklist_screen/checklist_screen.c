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
#include "checklist_screen.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/mqtt/mqtt.h"
#include "../core/kv/kv.h"
#include "../core/log/log.h"

#include "../sgl/sgl.h"
#include "../m5tft/app.h"

#include "./checklist_page.h"

typedef struct {
  uint8_t type;
  uint8_t order;
  uint8_t nitems;
  char text[];
} __attribute__ ((packed)) set_checklists_event;


int checklistUpdatesCount = 0;

void updateChecklistFn() {
  if (!(checklistUpdatesCount % 3 == 0)) {
    checklistUpdatesCount++;
    ESP_LOGI(SGO_LOG_NOSEND, "Skipping checklist update");
    return;
  }
  checklistUpdatesCount++;
  ESP_LOGI(SGO_LOG_NOSEND, "checklists update");
  uint8_t cmd = GET_CHECKLISTS;
  send_screen_message((char *)&cmd, 1);
}

void setChecklistData(const char *msg, int len) {
  ESP_LOGI(SGO_LOG_NOSEND, "setChecklistData");
  set_checklists_event *evt = (set_checklists_event *)msg;
  update_checklist_entry(evt->text, evt->order);
  update_nchecklist(evt->nitems);
  ESP_LOGI(SGO_LOG_NOSEND, "Set checklist event: len: %d order: %d text: %s", len, evt->order, evt->text);
}

void init_checklist_screen() {
  ESP_LOGI(SGO_LOG_NOSEND, "@CHECKLIST_SCREEN Initializing checklist_screen module");

  add_screen_init(init_checklist_page);
  set_command_update(GET_CHECKLISTS, updateChecklistFn);
  set_command(SET_CHECKLISTS, setChecklistData);
}

uint8_t on_set_checklist_screen_order(uint8_t value) {
  return value;
}
