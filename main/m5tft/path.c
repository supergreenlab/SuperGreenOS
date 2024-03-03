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

static void plot(RenderOpt renderOpts, int x, int y, float c, color_t color, float thickness) {
	int radius = (int)(thickness / 2);
	int startX = fmax(x - radius, 0);
	int endX = fmin(x + radius, DEFAULT_TFT_DISPLAY_HEIGHT - 1);
	int startY = fmax(y - radius, 0);
	int endY = fmin(y + radius, DEFAULT_TFT_DISPLAY_WIDTH - 1);

	for (int i = startX; i <= endX; i++) {
    if (renderOpts.limit) {
      if (i < renderOpts.frame.x1 + (renderOpts.frameRef ? renderOpts.frameRef->x : 0) || i > renderOpts.frame.x2 + (renderOpts.frameRef ? renderOpts.frameRef->x : 0)) {
        continue;
      }
    }

		for (int j = startY; j <= endY; j++) {
    if (renderOpts.limit) {
      if (j < renderOpts.frame.y1 + (renderOpts.frameRef ? renderOpts.frameRef->y : 0) || j > renderOpts.frame.y2 + (renderOpts.frameRef ? renderOpts.frameRef->y : 0)) {
        continue;
      }
    }

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

void drawLineAA(RenderOpt renderOpts, int x0, int y0, int x1, int y1, color_t color, float thickness) {
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
		plot(renderOpts, ypxl1,   xpxl1, 1 - (yend - floor(yend)) * xgap, color, thickness);
		plot(renderOpts, ypxl1+1, xpxl1, (yend - floor(yend)) * xgap, color, thickness);
	} else {
		plot(renderOpts, xpxl1, ypxl1  , 1 - (yend - floor(yend)) * xgap, color, thickness);
		plot(renderOpts, xpxl1, ypxl1+1, (yend - floor(yend)) * xgap, color, thickness);
	}
	float intery = yend + gradient;

	// Handle second endpoint
	xend = round(x1);
	yend = y1 + gradient * (xend - x1);
	xgap = (x1 + 0.5 - floor(x1 + 0.5));
	int xpxl2 = xend;
	int ypxl2 = floor(yend);
	if (steep) {
		plot(renderOpts, ypxl2  , xpxl2, 1 - (yend - floor(yend)) * xgap, color, thickness);
		plot(renderOpts, ypxl2+1, xpxl2, (yend - floor(yend)) * xgap, color, thickness);
	} else {
		plot(renderOpts, xpxl2, ypxl2, 1 - (yend - floor(yend)) * xgap, color, thickness);
		plot(renderOpts, xpxl2, ypxl2 + 1, (yend - floor(yend)) * xgap, color, thickness);
	}

	// Main loop
	if (steep) {
		for (int x = xpxl1 + 1; x <= xpxl2 - 1; x++) {
			plot(renderOpts, floor(intery), x, 1 - (intery - floor(intery)), color, thickness);
			plot(renderOpts, floor(intery) + 1, x, intery - floor(intery), color, thickness);
			intery = intery + gradient;
		}
	} else {
		for (int x = xpxl1 + 1; x <= xpxl2 - 1; x++) {
			plot(renderOpts, x, floor(intery), 1 - (intery - floor(intery)), color, thickness);
			plot(renderOpts, x, floor(intery) + 1, intery - floor(intery), color, thickness);
			intery = intery + gradient;
		}
	}
}

void fillRectangle(int x, int y, int width, int height, color_t color) {
	for (int i = x; i < x + width; i++) {
		for (int j = y; j < y + height; j++) {
			if (i >= 0 && i < DEFAULT_TFT_DISPLAY_WIDTH && j >= 0 && j < DEFAULT_TFT_DISPLAY_HEIGHT) {
				frame[j * DEFAULT_TFT_DISPLAY_WIDTH + i] = color;
			}
		}
	}
}
