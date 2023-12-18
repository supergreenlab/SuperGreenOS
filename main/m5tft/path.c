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

#include "./path.h"

#include <math.h>

void drawPixel(int x, int y, color_t color) {
	if (x >= 0 && x < DEFAULT_TFT_DISPLAY_HEIGHT && y >= 0 && y < DEFAULT_TFT_DISPLAY_WIDTH) {
		frame[y * DEFAULT_TFT_DISPLAY_HEIGHT + x] = color;
	}
}

static void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

color_t blendPixelColor(color_t existingColor, color_t newColor, float alpha) {
	color_t result;
	result.r = (uint8_t)(existingColor.r * (1 - alpha) + newColor.r * alpha);
	result.g = (uint8_t)(existingColor.g * (1 - alpha) + newColor.g * alpha);
	result.b = (uint8_t)(existingColor.b * (1 - alpha) + newColor.b * alpha);
	return result;
}

static void plot(int x, int y, float c, color_t color, float thickness) {
	int radius = (int)(thickness / 2);
	int startX = fmax(x - radius, 0);
	int endX = fmin(x + radius, DEFAULT_TFT_DISPLAY_HEIGHT - 1);
	int startY = fmax(y - radius, 0);
	int endY = fmin(y + radius, DEFAULT_TFT_DISPLAY_WIDTH - 1);

	for (int i = startX; i <= endX; i++) {
		for (int j = startY; j <= endY; j++) {
			if ((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius) {
				int index = j * DEFAULT_TFT_DISPLAY_HEIGHT + i;
				if (index > 0 && index < DEFAULT_TFT_DISPLAY_HEIGHT * DEFAULT_TFT_DISPLAY_WIDTH) {
					color_t blendedColor = blendPixelColor(frame[index], color, c);
					frame[index] = blendedColor;
				}
			}
		}
	}
}

void drawLineAA(int x0, int y0, int x1, int y1, color_t color, float thickness) {
	int steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap(&x0, &y0);
		swap(&x1, &y1);
	}
	if (x0 > x1) {
		swap(&x0, &x1);
		swap(&y0, &y1);
	}

	float dx = x1 - x0;
	float dy = y1 - y0;
	float gradient = dy / dx;
	if (dx == 0.0) {
		gradient = 1.0;
	}

	// Handle first endpoint
	float xend = round(x0);
	float yend = y0 + gradient * (xend - x0);
	float xgap = 1 - (x0 + 0.5 - floor(x0 + 0.5));
	int xpxl1 = xend;
	int ypxl1 = floor(yend);
	if (steep) {
		plot(ypxl1,   xpxl1, 1 - (yend - floor(yend)) * xgap, color, thickness);
		plot(ypxl1+1, xpxl1, (yend - floor(yend)) * xgap, color, thickness);
	} else {
		plot(xpxl1, ypxl1  , 1 - (yend - floor(yend)) * xgap, color, thickness);
		plot(xpxl1, ypxl1+1, (yend - floor(yend)) * xgap, color, thickness);
	}
	float intery = yend + gradient;

	// Handle second endpoint
	xend = round(x1);
	yend = y1 + gradient * (xend - x1);
	xgap = (x1 + 0.5 - floor(x1 + 0.5));
	int xpxl2 = xend;
	int ypxl2 = floor(yend);
	if (steep) {
		plot(ypxl2  , xpxl2, 1 - (yend - floor(yend)) * xgap, color, thickness);
		plot(ypxl2+1, xpxl2, (yend - floor(yend)) * xgap, color, thickness);
	} else {
		plot(xpxl2, ypxl2, 1 - (yend - floor(yend)) * xgap, color, thickness);
		plot(xpxl2, ypxl2 + 1, (yend - floor(yend)) * xgap, color, thickness);
	}

	// Main loop
	if (steep) {
		for (int x = xpxl1 + 1; x <= xpxl2 - 1; x++) {
			plot(floor(intery), x, 1 - (intery - floor(intery)), color, thickness);
			plot(floor(intery) + 1, x, intery - floor(intery), color, thickness);
			intery = intery + gradient;
		}
	} else {
		for (int x = xpxl1 + 1; x <= xpxl2 - 1; x++) {
			plot(x, floor(intery), 1 - (intery - floor(intery)), color, thickness);
			plot(x, floor(intery) + 1, intery - floor(intery), color, thickness);
			intery = intery + gradient;
		}
	}
}
