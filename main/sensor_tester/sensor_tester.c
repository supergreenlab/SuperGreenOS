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
#include "sensor_tester.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"

#include "../status_led/status_led.h"

#ifdef MODULE_STATUS_LED

status_led_timeline ok_timeline = {
  .loop = true,
  .fade = true,
  .step = 0.1,
  .red = {LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY},
  .green = {LED_MAX_DUTY, LED_MAX_DUTY/2, LED_MAX_DUTY, LED_MAX_DUTY/2, LED_MAX_DUTY, LED_MAX_DUTY/2, LED_MAX_DUTY, LED_MAX_DUTY/2},
};

#endif

static void sensor_tester_task(void *param);

void init_sensor_tester() {
  ESP_LOGI(SGO_LOG_EVENT, "@SENSOR_TESTER Initializing sensor_tester module\n");

  xTaskCreatePinnedToCore(sensor_tester_task, "SENSOR_TESTER", 4096, NULL, 10, NULL, 1);
}

static void sensor_tester_task(void *param) {
  while (true) {

#ifdef MODULE_STATUS_LED

    status_led_timeline timeline = {
      .loop = true,
      .fade = false,
      .step = 1.0f/3.0f,
      .red = {LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY},
      .green = {LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY},
    };

#endif

#ifdef MODULE_SHT21
    bool ok = true;
    for (int i = 0; i < N_SHT21; ++i) {
      bool is_ok = get_sht21_present(i) == 1;
      ok &= is_ok;

#ifdef MODULE_STATUS_LED

      timeline.green[i*2] = is_ok ? LED_MAX_DUTY : LED_MIN_DUTY;
      timeline.red[i*2] = is_ok ? LED_MIN_DUTY : LED_MAX_DUTY;

#endif

    }

#ifdef MODULE_STATUS_LED

    if (ok) {
      set_status_led_timeline(ok_timeline);
    } else {
      set_status_led_timeline(timeline);
    }

#endif

#endif

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

