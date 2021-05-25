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

#include "state.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"

#include "../status_led/status_led.h"

status_led_timeline new_timeline = {
  .loop = true,
  .fade = true,
  .step = 0.4,
  .new_default = true,
  .red = {LED_MIN_DUTY, LED_MIN_DUTY, LED_MAX_DUTY, LED_MAX_DUTY, LED_MAX_DUTY, LED_MAX_DUTY, LED_MIN_DUTY, LED_MIN_DUTY},
  .green = {LED_MAX_DUTY, LED_MAX_DUTY, LED_MAX_DUTY, LED_MAX_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY},
};

status_led_timeline running_timeline = {
  .loop = true,
  .fade = true,
  .step = 0.07,
  .new_default = true,
  .red = {LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY, LED_MIN_DUTY},
  .green = {LED_MAX_DUTY, LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY/10, LED_MAX_DUTY, LED_MAX_DUTY, LED_MAX_DUTY/10, LED_MAX_DUTY/10},
};

void init_state() {
  int state = get_state();
  if (state == FIRST_RUN) {
    set_status_led_timeline(new_timeline);
  }
}

int on_set_state(int state) {
  if (state == FIRST_RUN) {
    set_status_led_timeline(new_timeline);
  } else {
    set_status_led_timeline(running_timeline);
  }
  return state;
}
