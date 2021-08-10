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

#include "motor.h"

#include "math.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

#include "../core/log/log.h"
#include "../core/kv/kv.h"

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

static QueueHandle_t cmd;

typedef enum {
  CMD_NO_ACTION,
  CMD_CHANGED_FREQUENCY,
  CMD_REFRESH,
} motor_action;

typedef struct {
  motor_action cmd;
  int motorId;
  int value;
} motor_cmd;

static void set_duty(int i, float duty_cycle)
{
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0 + i, MCPWM_OPR_A, duty_cycle);
}

static void motor_task(void *param) {
  motor_cmd c = {.cmd = -1};

  while (1) {
    for (int i = 0; i < N_MOTOR; ++i) {
      if (get_motor_source(i) == 0) {
        set_duty(i, get_motor_duty_testing(i));
        continue;
      }
      //ESP_LOGI(SGO_LOG_NOSEND, "@MOTOR Motor: %d, duty: %d", c.motorId, get_motor_duty(i));
      double duty = get_motor_duty(i);
      if (get_motors_curve() == 1 && duty != 0 && duty != 100) {
        duty = 8*pow(1.025, duty)+5;
        duty = max(0, min(100, duty));
      }
      double min = get_motor_min(i);
      double max = get_motor_max(i);
      if (duty == 0) {
        set_duty(i, 0);
      } else {
        set_duty(i, min + (max - min) * duty / 100.0f);
      }
    }
    if (xQueueReceive(cmd, &c, 10000 / portTICK_PERIOD_MS) == pdTRUE) {
      if (c.cmd == CMD_CHANGED_FREQUENCY) {
        int motor_frequency = c.value;
        //ESP_LOGI(SGO_LOG_NOSEND, "@MOTOR CMD_CHANGED_FREQUENCY %d %d", c.motorId, motor_frequency);
        mcpwm_set_frequency(MCPWM_UNIT_0, MCPWM_TIMER_0 + c.motorId, motor_frequency);
      }
    }
  }
}

void init_motor() {
  ESP_LOGI(SGO_LOG_EVENT, "@MOTOR Initializing motor task");

  cmd = xQueueCreate(10, sizeof(motor_cmd));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@MOTOR Unable to create motor queue");
  }

  for (int i = 0; i < N_MOTOR; ++i) {
    int motor_gpio = get_motor_gpio(i);
    int motor_frequency = get_motor_frequency(i);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A + i * 2, motor_gpio);
    mcpwm_config_t pwm_config;
    pwm_config.frequency = motor_frequency;
    pwm_config.cmpr_a = 0;
    pwm_config.cmpr_b = 0;
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0 + i, &pwm_config);

    set_duty(i, 0.0);
  }
  BaseType_t ret = xTaskCreatePinnedToCore(motor_task, "MOTOR", 4096, NULL, 10, NULL, 1);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@MOTOR Failed to create task");
  }
}

void refresh_motors() {
  motor_cmd c = {.cmd = CMD_REFRESH};
  xQueueSend(cmd, &c, 0);
}

/* BLE Callbacks */

int on_set_motor_frequency(int motorId, int value) {
  value = min(40000, max(value, 2));
  motor_cmd c = {.cmd = CMD_CHANGED_FREQUENCY, .motorId = motorId, .value = value};
  xQueueSend(cmd, &c, 0);
  return value;
}

int on_set_motor_duty_testing(int motorId, int value) {
  value = min(100, max(value, 0));
  set_motor_duty_testing(motorId, value);
  refresh_motors();
  return value;
}

int on_set_motor_source(int motorId, int value) {
  set_motor_source(motorId, value);
  refresh_motors();
  return value;
}

int on_set_motor_min(int motorId, int value) {
  value = min(100, max(value, 0));
  set_motor_min(motorId, value);
  refresh_motors();
  return value;
}

int on_set_motor_max(int motorId, int value) {
  value = min(100, max(value, 0));
  set_motor_max(motorId, value);
  refresh_motors();
  return value;
}
