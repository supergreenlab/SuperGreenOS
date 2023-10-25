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

#include <string.h>

#include "bitmaps.h"

#include "m5tft.h"
#include "tftspi.h"
#include "bitmaps_definitions.h"
#include "math.h"

#include "../core/log/log.h"

color_t frame[DEFAULT_TFT_DISPLAY_HEIGHT * DEFAULT_TFT_DISPLAY_WIDTH];

color_t blend_pixels(color_t dest, color_t src, float alpha) {
	uint8_t r = dest.r * (1.0f - alpha) + src.r * alpha;
	uint8_t g = dest.g * (1.0f - alpha) + src.g * alpha;
	uint8_t b = dest.b * (1.0f - alpha) + src.b * alpha;
	return (color_t){ r, g, b };
}

void draw_bitmap(const bitmap_data *img, float x, float y, RenderOpt *opts) {
  float scale = (opts) ? opts->scale : 1.0f;
  float transparency = (opts) ? opts->transparency : 1.0f;

  if (scale == 0 || transparency == 0) {
    return;
  }

  int scaledWidth = img->width * scale;
  int scaledHeight = img->height * scale;

  // Check if the image is completely out of the frame
  if (x + scaledWidth < 0 || x > DEFAULT_TFT_DISPLAY_HEIGHT || y + scaledHeight < 0 || y > DEFAULT_TFT_DISPLAY_WIDTH) {
    return; // Image is out of frame, so return immediately
  }

	int minX = 0;
	int minY = 0;
	int maxX = DEFAULT_TFT_DISPLAY_HEIGHT;
	int maxY = DEFAULT_TFT_DISPLAY_WIDTH;

  // Calculate the start and end values for loops to avoid unnecessary iteration
  int startX = (x < minX) ? -x : minX;
  int startY = (y < minY) ? -y : minY;
  int endX = (x + scaledWidth > maxX) ? maxX - x : scaledWidth;
  int endY = (y + scaledHeight > maxY) ? maxY - y : scaledHeight;
	
  float srcIncrementX = img->width / scaledWidth;
  float srcIncrementY = img->height / scaledHeight;

  float srcXAccum = (float)startX * srcIncrementX;

  // Iterate only within calculated bounds
  for (int i = startX; i < endX; i++) {
		if (opts && opts->limit) {
			if (x + i < opts->frame.x1 + (opts->frameRef ? opts->frameRef->x : 0) || x + i > opts->frame.x2 + (opts->frameRef ? opts->frameRef->x : 0)) {
				srcXAccum += srcIncrementX;
				continue;
			}
		}
		float srcYAccum = (float)startY * srcIncrementY;
    for (int j = startY; j < endY; j++) {
			if (opts && opts->limit) {
				if ((y + j) < opts->frame.y1 + (opts->frameRef ? opts->frameRef->y : 0) || (y + j) > opts->frame.y2 + (opts->frameRef ? opts->frameRef->y : 0)) {
					srcYAccum += srcIncrementY;
					continue;
				}
			}

      int srcX = (int)srcXAccum;
      int srcY = (int)srcYAccum;
      bmp_color_t color = img->palette[img->bitmap[srcX + srcY * (int)img->width]];

			if (color.a == 0) {
				srcYAccum += srcIncrementY;
				continue;
			}

      if (opts != NULL && color.r == color.g && color.g == color.b && color.b != 0xff) {
        float grayValue = 1.0f - ((float)color.r / 255.0f); // invert grayscale value
        uint8_t color_to = 0xff;
        if (opts->invert) {
          color_to = 0x00;
        }
        color.r = (1 - grayValue) * color_to + grayValue * (float)opts->targetColor.r;
        color.g = (1 - grayValue) * color_to + grayValue * (float)opts->targetColor.g;
        color.b = (1 - grayValue) * color_to + grayValue * (float)opts->targetColor.b;
      } else if (opts && opts->invert) {
        color.r = 255 - color.r;
        color.g = 255 - color.g;
        color.b = 255 - color.b;
      }

			float alpha = (opts != NULL ? opts->transparency : 1) * ((float)color.a / 255);

			float x_frac = x + i - floorf(x + i);
			float y_frac = y + j - floorf(y + j);

			bool do_position_blending = (opts && opts->blendposition) && (x_frac > 0 || y_frac > 0);

			if (do_position_blending) {
				float weight_tl = (1.0f - x_frac) * (1.0f - y_frac);
				float weight_tr = x_frac * (1.0f - y_frac);
				float weight_bl = (1.0f - x_frac) * y_frac;
				float weight_br = x_frac * y_frac;

				int tl_idx = (floorf(x) + i) + (floorf(y) + j) * DEFAULT_TFT_DISPLAY_HEIGHT;
				int tr_idx = (floorf(x) + i + 1) + (floorf(y) + j) * DEFAULT_TFT_DISPLAY_HEIGHT;
				int bl_idx = (floorf(x) + i) + (floorf(y) + j + 1) * DEFAULT_TFT_DISPLAY_HEIGHT;
				int br_idx = (floorf(x) + i + 1) + (floorf(y) + j + 1) * DEFAULT_TFT_DISPLAY_HEIGHT;

				if (tl_idx > 0 && tl_idx < DEFAULT_TFT_DISPLAY_WIDTH * DEFAULT_TFT_DISPLAY_HEIGHT) {
					frame[tl_idx] = blend_pixels(frame[tl_idx], (color_t){ color.r, color.g, color.b }, alpha * weight_tl);
				}
				if (tr_idx > 0 && tr_idx < DEFAULT_TFT_DISPLAY_WIDTH * DEFAULT_TFT_DISPLAY_HEIGHT) {
					frame[tr_idx] = blend_pixels(frame[tr_idx], (color_t){ color.r, color.g, color.b }, alpha * weight_tr);
				}
				if (bl_idx > 0 && bl_idx < DEFAULT_TFT_DISPLAY_WIDTH * DEFAULT_TFT_DISPLAY_HEIGHT) {
					frame[bl_idx] = blend_pixels(frame[bl_idx], (color_t){ color.r, color.g, color.b }, alpha * weight_bl);
				}
				if (br_idx > 0 && br_idx < DEFAULT_TFT_DISPLAY_WIDTH * DEFAULT_TFT_DISPLAY_HEIGHT) {
					frame[br_idx] = blend_pixels(frame[br_idx], (color_t){ color.r, color.g, color.b }, alpha * weight_br);
				}
			} else {
				if (alpha < 1) {
					color_t current_pixel = frame[((int)x + i) + ((int)y + j) * DEFAULT_TFT_DISPLAY_HEIGHT];
					color.r = current_pixel.r * (1.0f - alpha) + color.r * alpha;
					color.g = current_pixel.g * (1.0f - alpha) + color.g * alpha;
					color.b = current_pixel.b * (1.0f - alpha) + color.b * alpha;
				}

				frame[((int)x + i) + ((int)y + j) * DEFAULT_TFT_DISPLAY_HEIGHT] = (color_t){ color.r, color.g, color.b };
			}

      srcYAccum += srcIncrementY;
    }
    srcXAccum += srcIncrementX;
  }
}

bitmap_data* get_bitmap_for_name(char *name, int len, uint8_t mask) {
  for (int i = 0; i < n_bitmaps; i++) {
    if (!(bitmap_db[i]->mask & mask)) {
      continue;
    }
		if (strncmp(bitmap_db[i]->name, name, len) == 0) {
			return bitmap_db[i];
		}
  }
  //ESP_LOGI(SGO_LOG_NOSEND, "Does not exist \"%c\" (%x)", name[0], name[0]);
  return NULL;  // Return NULL if character bitmap not found
}

void fill_screen(color_t color) {
  for (int i = 0; i < DEFAULT_TFT_DISPLAY_HEIGHT * DEFAULT_TFT_DISPLAY_WIDTH; ++i) {
    frame[i] = color;
  }
}

void flush_frame() {
  int buffer_size = DEFAULT_TFT_DISPLAY_HEIGHT * DEFAULT_TFT_DISPLAY_WIDTH/4;
  send_data(0, 0, DEFAULT_TFT_DISPLAY_HEIGHT-1, 19, buffer_size, frame);
  send_data(0, 20, DEFAULT_TFT_DISPLAY_HEIGHT-1, 39, buffer_size, frame+buffer_size);
  send_data(0, 40, DEFAULT_TFT_DISPLAY_HEIGHT-1, 59, buffer_size, frame+buffer_size*2);
  send_data(0, 60, DEFAULT_TFT_DISPLAY_HEIGHT-1, 79, buffer_size, frame+buffer_size*3);
}
