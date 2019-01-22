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

#include "status_led/status_led.h"
#include "state/state.h"
#include "led/led.h"
#include "fans/fans.h"
#include "blower/blower.h"

#include "timer/timer.h"
#include "manual/manual.h"
#include "onoff/onoff.h"

#include "mixer/mixer.h"

void init_app() {
  init_status_led();
  init_state();
  init_led();
  init_fans();
  init_blower();

  init_timer();

  init_mixer();
}
