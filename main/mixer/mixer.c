/*
 * Copyright (C) 2018  SuperGreenLab <towelie@supergreenlab.com>
 * Author: Constantin Clauzel <constantin.clauzel@gmail.com>
 *
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

#include <float.h>
#include <math.h>

#include "mixer.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "time.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"
#include "../state/state.h"
#include "../led/led.h"
#include "../timer/timer.h"

#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

static void mixer_task();
static void set_duty(int i, int duty);

// Private methods

void init_mixer() {
  ESP_LOGI(SGO_LOG_EVENT, "@MIXER Initializing mixer module");

  BaseType_t ret = xTaskCreatePinnedToCore(mixer_task, "MIXER", 4096, NULL, tskIDLE_PRIORITY, NULL, 1);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@MIXER Failed to create task");
  }
}

void set_all_duty(int boxId, int value, led_type type) {
  for (int i = 0; i < N_LED; ++i) {
    if (type != -1 && get_led_type(i) != type) {
      continue;
    }
    if (boxId != -1 && get_led_box(i) != boxId) {
      continue;
    }

    set_duty(i, value);
  }
}

// Private functions

static void set_duty(int i, int duty) {
  duty = min(100, max(duty, 0));
  set_led_duty(i, duty);
}

static void mixer_duty(int boxId) {
  {
    double timer_output = get_box_timer_output(boxId);
    double duty = max(0, min(100, timer_output));
    set_all_duty(boxId, duty, LED_FULLSPECTRUM);
  }

  {
    double timer_output = get_box_emerson_timer_output(boxId);
    double duty = max(0, min(100, timer_output));
    set_all_duty(boxId, duty, LED_EMERSON);
  }

  {
    double timer_output = get_box_stretch_timer_output(boxId);
    double duty = max(0, min(100, timer_output));
    set_all_duty(boxId, duty, LED_STRETCH);
  }

  {
    double timer_output = get_box_uva_timer_output(boxId);
    double duty = max(0, min(100, timer_output));
    set_all_duty(boxId, duty, LED_UVA);
  }

  refresh_led(boxId, -1);
}

static void mixer_task() {
  while (1) {
    enum state s = get_state();
    if (s != RUNNING) {
      vTaskDelay(5000 / portTICK_PERIOD_MS);
      continue;
    }

    for (int i = 0; i < N_BOX; ++i) {
      if (get_box_enabled(i) != 1 || get_box_timer_type(i) == TIMER_MANUAL) continue;
      mixer_duty(i);
    }

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

//  KV Callbacks
