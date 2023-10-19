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

#ifndef BITMAPS
#define BITMAPS

#include "tftspi.h"

typedef struct {
  color_t palette[11];
  int width;
  int height;
  const char name[10];
  uint8_t bitmap[];
} bitmap_data;     

typedef struct {
  float transparency;   // Ranges from 0.0 (fully transparent) to 1.0 (fully opaque)
  color_t targetColor;  // The color to be used as the new color for gray pixels
} RenderOpt;

void scaled_draw_bitmap(const bitmap_data *img, int x, int y, float scale, RenderOpt *opts);
void draw_bitmap(const bitmap_data *img, int x, int y, RenderOpt *opts);

#endif
