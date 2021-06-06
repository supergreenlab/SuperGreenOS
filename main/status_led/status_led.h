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

#ifndef STATUS_LED_H
#define STATUS_LED_H

#include <stdint.h>
#include <stdbool.h>

#define STATUS_LED_TIMELINE_LENGTH 8

#define LED_MIN_DUTY           (0.0f)
#define LED_MAX_DUTY           (511.0f)

typedef struct {
  bool reset;
  bool loop;
  bool fade;
  bool new_default;
  double step;
  double red[STATUS_LED_TIMELINE_LENGTH];
  double green[STATUS_LED_TIMELINE_LENGTH];
} status_led_timeline;

status_led_timeline DEFAULT_TIMELINE;

void set_status_led_timeline(status_led_timeline timeline);

void init_status_led();

#endif
