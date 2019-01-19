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

#include <stdlib.h>

#include "led_db.h"
#include "../core/kv/kv.h"

#include "driver/ledc.h"

const unsigned int N_LEDS = 6;

// Warning: this values should be synced with config.yml defaults,
// will fix later TODO
led_config_t ledc_channels[] = {
  CHANNEL(0, 1, 0, 0, 0, 32, 1, 0),
  CHANNEL(1, 1, 1, 1, 0, 17, 1, 1),
  CHANNEL(2, 1, 0, 0, 1, 33, 1, 2),
  CHANNEL(3, 1, 1, 1, 1, 16, 1, 3),
  CHANNEL(4, 1, 0, 0, 2, 25, 1, 4),
  CHANNEL(5, 1, 1, 1, 2, 4, 1, 5)
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
