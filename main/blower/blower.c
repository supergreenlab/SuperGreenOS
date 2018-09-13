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

#include "../misc/log.h"
#include "../conf/ble_db.h"
#include "../kv/kv.h"
#include "../kv/kv_ble.h"

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

#define BLOWER_GPIO (22)

/*  UUID string: 03b7cea7-bedc-e37f-1bfd-7f2ab70a5e7b * */
const uint8_t BLOWER_UUID[ESP_UUID_LEN_128] = {0x7b,0x5e,0x0a,0xb7,0x2a,0x7f,0xfd,0x1b,0x7f,0xe3,0xdc,0xbe,0xa7,0xce,0xb7,0x03};

#define BLOWER "BLWR"

static QueueHandle_t cmd;

static void set_duty(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num , float duty_cycle)
{
    mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_A, duty_cycle);
    mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}

static void blower_task(void *param) {
  int c;

  while (1) {
    int v = geti(BLOWER);
    set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, v);
    xQueueReceive(cmd, &c, 3000 / portTICK_PERIOD_MS);
  }
}

void init_blower() {
  ESP_LOGI(TAG, "Initializing blower task");
  defaulti(BLOWER, 50);

  sync_ble_i(BLOWER, IDX_VALUE(BLOWER));

  cmd = xQueueCreate(10, sizeof(int));
  if (cmd == NULL) {
    ESP_LOGE(TAG, "Unable to create led queue");
  }

  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, BLOWER_GPIO);
  mcpwm_config_t pwm_config;
  pwm_config.frequency = 200;
  pwm_config.cmpr_a = 0;
  pwm_config.cmpr_b = 0;
  pwm_config.counter_mode = MCPWM_UP_COUNTER;
  pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);

  set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, 0.0);
  xTaskCreate(blower_task, "Blower task", 2048, NULL, 10, NULL);
}

/* BLE Callbacks */

void on_set_blower(int value) {
  value = min(100, max(value, 0));

  seti(BLOWER, value);

  xQueueSend(cmd, &value, 0);
}
