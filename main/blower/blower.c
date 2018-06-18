/*
 * =====================================================================================
 *
 *       Filename:  blower.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/13/2018 15:18:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "blower.h"

#include "math.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

#define BLOWER_GPIO (22)

static void set_duty(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num , float duty_cycle)
{
    mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_A, duty_cycle);
    mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
}

static void blower_task(void *param) {
  double i = 0;
  while (1) {
    set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, 100.0f);
    vTaskDelay(100 / portTICK_RATE_MS);
    ++i;
  }
}

void init_blower() {
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
