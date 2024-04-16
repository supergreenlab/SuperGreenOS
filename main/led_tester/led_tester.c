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
#include "led_tester.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"

#include "../led/led.h"

static void led_tester_task(void *param);

void init_led_tester() {
  ESP_LOGI(SGO_LOG_NOSEND, "@LED_TESTER Initializing led_tester module\n");

  xTaskCreatePinnedToCore(led_tester_task, "LED_TESTER", 4096, NULL, 10, NULL, 1);
}

static void led_tester_task(void *param) {
  double i = 0;
  while (true) {
    for (int j = 0; j < N_LED; ++j) {
      double duty = (cosf(i+j*M_PI/6)+1)/2*100;
      set_led_duty(j, (int)duty);
    }
    refresh_led(-1, -1);
    i += M_PI/6;
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

