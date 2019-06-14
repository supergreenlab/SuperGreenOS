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

#ifndef LED_HELPERS_H_
#define LED_HELPERS_H_

#define LED_CB_H(ledId, param) int on_set_led_## ledId ##_## param( int value);
#define LED_GETTER_H(param) int get_led_## param(int ledId);
#define LED_SETTER_H(param) void set_led_## param(int ledId, int value);

LED_CB_H(0, duty)
LED_CB_H(1, duty)
LED_CB_H(0, gpio)
LED_CB_H(1, gpio)
LED_CB_H(0, x)
LED_CB_H(1, x)
LED_CB_H(0, y)
LED_CB_H(1, y)
LED_CB_H(0, z)
LED_CB_H(1, z)
LED_CB_H(0, enabled)
LED_CB_H(1, enabled)
LED_CB_H(0, box)
LED_CB_H(1, box)
LED_CB_H(0, dim)
LED_CB_H(1, dim)
LED_CB_H(0, fade)
LED_CB_H(1, fade)

LED_SETTER_H(duty)
LED_GETTER_H(duty)
LED_SETTER_H(gpio)
LED_GETTER_H(gpio)
LED_SETTER_H(x)
LED_GETTER_H(x)
LED_SETTER_H(y)
LED_GETTER_H(y)
LED_SETTER_H(z)
LED_GETTER_H(z)
LED_SETTER_H(enabled)
LED_GETTER_H(enabled)
LED_SETTER_H(box)
LED_GETTER_H(box)
LED_SETTER_H(dim)
LED_GETTER_H(dim)
LED_SETTER_H(fade)
LED_GETTER_H(fade)

#endif
