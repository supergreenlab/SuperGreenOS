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

#include "blower.h"

#include "math.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

#include "../core/log/log.h"
#include "../core/ble/ble_db.h"
#include "../core/kv/kv.h"
#include "../core/kv/kv_ble.h"

#include "../box/box.h"

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

static QueueHandle_t cmd;

static void set_duty(int i, float duty_cycle)
{
  mcpwm_set_duty(MCPWM_UNIT_0, i / MCPWM_TIMER_MAX, i % MCPWM_OPR_MAX, duty_cycle);
}

static void blower_task(void *param) {
  int c;

  while (1) {
    for (int i = 0; i < N_BOXES; ++i) {
      if (get_box_enabled(i) != 1 || get_box_blower_enabled(i) != 1) continue;
      int v = get_box_blower(i);
      int mode = get_box_blower_mode(i);
      if (mode == BLOWER_MODE_TIMER) {
        int timerOutput = get_box_timer_output(i);
        v = (float)v * (float)timerOutput / 100.0f;
      }
      set_duty(i, v);
    }
    xQueueReceive(cmd, &c, 3000 / portTICK_PERIOD_MS);
  }
}

void init_blower() {
  ESP_LOGI(SGO_LOG_EVENT, "@BLOWER Initializing blower task");

  cmd = xQueueCreate(10, sizeof(int));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@BLOWER Unable to create blower queue");
  }

  for (int i = 0; i < N_BOXES; ++i) {
    if (get_box_enabled(i) != 1 || get_box_blower_enabled(i) != 1) continue;
    int blower_gpio = get_box_blower_gpio(i);
    mcpwm_gpio_init(MCPWM_UNIT_0, i, blower_gpio);
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 200;
    pwm_config.cmpr_a = 0;
    pwm_config.cmpr_b = 0;
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, i / MCPWM_TIMER_MAX, &pwm_config);

    set_duty(i, 0.0);
  }
  xTaskCreate(blower_task, "BLOWER", 2048, NULL, 10, NULL);
}

/* BLE Callbacks */

int on_set_box_blower(int boxId, int value) {
  value = min(100, max(value, 0));
  xQueueSend(cmd, &value, 0);
  return value;
}
