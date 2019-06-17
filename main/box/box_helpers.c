/*
 * Copyright (C) 2019  SuperGreenLab <towelie@supergreenlab.com>
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

#include "box_helpers.h"

#include "../core/kv/kv.h"
#include "../core/include_modules.h"

#include "box.h"

#define BOX_CB(boxId, param) int on_set_box_## boxId ##_## param(int value) { \
  return on_set_box_## param(boxId, value); \
}

#define BOX_GETTER(param) int get_box_## param(int boxId) { \
  switch(boxId) { \
    case 0: \
      return get_box_0_## param(boxId); \
  } \
  return 0; \
}

#define BOX_SETTER(param) void set_box_## param(int boxId, int value) { \
  switch(boxId) { \
    case 0: \
      set_box_0_## param(value); \
      break; \
  } \
}

BOX_CB(0, timer_type)
BOX_CB(0, stretch)
BOX_CB(0, led_dim)

BOX_SETTER(enabled)
BOX_GETTER(enabled)
BOX_SETTER(timer_type)
BOX_GETTER(timer_type)
BOX_SETTER(timer_output)
BOX_GETTER(timer_output)
BOX_SETTER(started_at)
BOX_GETTER(started_at)
BOX_SETTER(on_hour)
BOX_GETTER(on_hour)
BOX_SETTER(on_min)
BOX_GETTER(on_min)
BOX_SETTER(off_hour)
BOX_GETTER(off_hour)
BOX_SETTER(off_min)
BOX_GETTER(off_min)
BOX_SETTER(stretch)
BOX_GETTER(stretch)
BOX_SETTER(led_dim)
BOX_GETTER(led_dim)
BOX_SETTER(sht21_temp_c)
BOX_GETTER(sht21_temp_c)
BOX_SETTER(sht21_temp_f)
BOX_GETTER(sht21_temp_f)
BOX_SETTER(sht21_humi)
BOX_GETTER(sht21_humi)
