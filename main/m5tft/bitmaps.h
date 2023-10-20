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

#define NORMAL_FONT_SIZE 0x01 << 0
#define SMALL_FONT_SIZE 0x01 << 1
#define CAPS_FONT 0x01 << 2
#define SPRITE 0xff

extern color_t frame[DEFAULT_TFT_DISPLAY_HEIGHT * DEFAULT_TFT_DISPLAY_WIDTH];

typedef struct {
  color_t palette[11];
  int width;
  int height;
  uint8_t mask;
  const char name[10];
  uint8_t bitmap[];
} bitmap_data;     

typedef struct {
  bool invert;
  bool antialias;
  float scale;
  float transparency;   // Ranges from 0.0 (fully transparent) to 1.0 (fully opaque)
  color_t targetColor;  // The color to be used as the new color for gray pixels
} RenderOpt;

void scaled_draw_bitmap(const bitmap_data *img, int x, int y, float scale, RenderOpt *opts);
void draw_bitmap(const bitmap_data *img, int x, int y, RenderOpt *opts);
bitmap_data* get_bitmap_for_name(char* name, int len, uint8_t mask);
void fill_screen(color_t color);
void flush_frame();

#endif
