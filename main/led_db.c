/*
 * =====================================================================================
 *
 *       Filename:  led_db.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/28/2018 13:35:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "led_db.h"

#include "driver/ledc.h"

const unsigned int N_LEDS = 6;

#define LED_MIN_DUTY           (0)
#define LED_MAX_DUTY           (8191)

LED_DUTY_UUID(0)
LED_DUTY_UUID(1)
LED_DUTY_UUID(2)
LED_DUTY_UUID(3)
LED_DUTY_UUID(4)
LED_DUTY_UUID(5)

led_config_t ledc_channels[] = {
  CHANNEL(0, LED_MIN_DUTY, LED_MAX_DUTY, 0, 0, 0, 32, 1, 0),
  CHANNEL(1, LED_MIN_DUTY, LED_MAX_DUTY, 1, 1, 0, 33, 1, 1),
  CHANNEL(2, LED_MIN_DUTY, LED_MAX_DUTY, 0, 0, 1, 25, 1, 2),
  CHANNEL(3, LED_MIN_DUTY, LED_MAX_DUTY, 1, 1, 1, 17, 1, 3),
  CHANNEL(4, LED_MIN_DUTY, LED_MAX_DUTY, 0, 0, 2, 16, 1, 4),
  CHANNEL(5, LED_MIN_DUTY, LED_MAX_DUTY, 1, 1, 2, 4, 1, 5)
};

void init_led_timers() {
  ledc_timer_config_t ledc_timer = {
    speed_mode:       LEDC_LOW_SPEED_MODE,
    { duty_resolution:  LEDC_TIMER_13_BIT, },
    timer_num:        LEDC_TIMER_1,
    freq_hz:          120,
  };
  ledc_timer_config(&ledc_timer);
}
