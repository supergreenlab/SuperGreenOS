/*
 * =====================================================================================
 *
 *       Filename:  fans.c
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

#include "fans.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define FANS_GPIO (21)
#define GPIO_OUTPUT_PIN_SEL  (1ULL<<FANS_GPIO)

void init_fans() {
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
  io_conf.pull_down_en = 0;
  io_conf.pull_up_en = 0;
  gpio_config(&io_conf);

  gpio_set_level(FANS_GPIO, 1);
}
