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

#include "led_helpers.h"

#include "led.h"
#include "../core/kv/kv.h"

#define LED_CB(ledId, param) int on_set_led_## ledId ##_## param(int value) { \
  return on_set_led_## param(ledId, value); \
}

#define LED_GETTER(param) int get_led_## param(int ledId) { \
  switch(ledId) { \
    case 0: \
      return get_led_0_## param(ledId); \
    case 1: \
      return get_led_1_## param(ledId); \
    case 2: \
      return get_led_2_## param(ledId); \
    case 3: \
      return get_led_3_## param(ledId); \
    case 4: \
      return get_led_4_## param(ledId); \
    case 5: \
      return get_led_5_## param(ledId); \
  } \
  return 0; \
}

#define LED_SETTER(param) void set_led_## param(int ledId, int value) { \
  switch(ledId) { \
    case 0: \
      set_led_0_## param(value); \
    case 1: \
      set_led_1_## param(value); \
    case 2: \
      set_led_2_## param(value); \
    case 3: \
      set_led_3_## param(value); \
    case 4: \
      set_led_4_## param(value); \
    case 5: \
      set_led_5_## param(value); \
  } \
}

LED_CB(0, duty)
LED_CB(1, duty)
LED_CB(2, duty)
LED_CB(3, duty)
LED_CB(4, duty)
LED_CB(5, duty)
LED_CB(0, dim)
LED_CB(1, dim)
LED_CB(2, dim)
LED_CB(3, dim)
LED_CB(4, dim)
LED_CB(5, dim)

LED_SETTER(duty)
LED_GETTER(duty)
LED_SETTER(gpio)
LED_GETTER(gpio)
LED_SETTER(x)
LED_GETTER(x)
LED_SETTER(y)
LED_GETTER(y)
LED_SETTER(z)
LED_GETTER(z)
LED_SETTER(enabled)
LED_GETTER(enabled)
LED_SETTER(box)
LED_GETTER(box)
LED_SETTER(dim)
LED_GETTER(dim)
