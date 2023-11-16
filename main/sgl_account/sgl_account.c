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
#include "sgl_account.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"

#include "api.h"

static void sgl_account_task(void *param);

void init_sgl_account() {
  ESP_LOGI(SGO_LOG_EVENT, "@SGL_ACCOUNT Initializing sgl_account module");

  xTaskCreatePinnedToCore(sgl_account_task, "SGL_ACCOUNT", 4096, NULL, 10, NULL, 1);
}

static void sgl_account_task(void *param) {
	vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
  while (true) {
    https();

    vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
  }
}

