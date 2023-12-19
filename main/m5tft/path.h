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

#ifndef PATH_H
#define PATH_H

#include "m5tft.h"
#include "node.h"

void drawLineAA(int x0, int y0, int x1, int y1, color_t color, float thickness);
void drawSingleLineAA(int x0, int y0, int x1, int y1, color_t color);
void drawPixel(int x, int y, color_t color);
void fillRectangle(int x, int y, int width, int height, color_t color);

#endif
