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

#ifndef BLOWER_H_
#define BLOWER_H_

typedef enum {
  BLOWER_MODE_MANUAL,
  BLOWER_MODE_TIMER,
} blower_mode;

#define DEFAULT_BOX_0_BLOWER_GPIO (22)
#define DEFAULT_BOX_1_BLOWER_GPIO (21)
#define DEFAULT_BOX_2_BLOWER_GPIO (20)

void init_blower();

/* BLE Callbacks */

int on_set_box_blower(int boxId, int value);

#endif
