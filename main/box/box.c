/*
 * Copyright (C) 2020  SuperGreenLab <towelie@supergreenlab.com>
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

#include "../core/log/log.h"
#include "../core/kv/kv.h"

#include "../core/modules.h"

#include "../led/led.h"
#include "../timer/timer.h"
#include "../mixer/mixer.h"

#ifdef MODULE_BLOWER
#include "../blower/blower.h"
#endif

//  KV Callbacks

int on_set_box_led_dim(int boxId, int value) {
  refresh_led(boxId, -1);
  return value;
}

int on_set_box_enabled(int boxId, int value) {
  if (value == get_box_enabled(boxId)) {
    return value;
  }
  set_box_enabled(boxId, value);
  if (value == 0) {
    set_all_duty(boxId, 0, -1);
#ifdef MODULE_BLOWER
    set_box_blower_duty(boxId, 0);
#endif
  }
  refresh_timer();
#ifdef MODULE_BLOWER
  refresh_blower();
#endif
  return value;
}
