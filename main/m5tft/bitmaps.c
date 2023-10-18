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

#include "bitmaps.h"

#include "m5tft.h"
#include "tftspi.h"
#include "bitmaps_definitions.h"

void draw_bitmap(const bitmap_data *img, int x, int y) {
	// Iterate through the image's pixels
	for (int i = 0; i < img->width; i++) {
		for (int j = 0; j < img->height; j++) {
			// Fetch the palette color
			color_t color = img->palette[img->bitmap[i + j * img->width]];

			// Check boundaries to avoid overwriting the frame
			if (x + i < 160 && y + j < 80 && x + i >= 0 && y + j >= 0) {
				frame[(x + i) + (y + j) * 160] = color;
			}
		}
	}
}
