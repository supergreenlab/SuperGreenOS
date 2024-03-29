/*
 * Copyright (C) 2023  SuperGreenLab <towelie@supergreenlab.com>
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

#ifndef TIMELAPSES_PAGE_H
#define TIMELAPSES_PAGE_H

#include "../m5tft/node.h"
#include "stdint.h"

void update_timelapse_palette(uint16_t len, color_t *colors);
void update_timelapse_frame(uint32_t offset, uint16_t len, uint8_t *colors);
void init_timelapses_page(Node *root);

#endif
