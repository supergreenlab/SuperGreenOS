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

void scaled_draw_bitmap(const bitmap_data *img, int x, int y, float scale, RenderOpt *opts) {
  // Calculate the new scaled dimensions
  int scaled_width = ceilf(img->width * scale);
  int scaled_height = ceilf(img->height * scale);

  // Calculate the starting draw positions to ensure the image is anchored at its center
  int draw_start_x = x + ((img->width - scaled_width) / 2);
  int draw_start_y = y + ((img->height - scaled_height) / 2);

  for (int i = 0; i < scaled_width; i++) {
    for (int j = 0; j < scaled_height; j++) {

      // Calculate the corresponding source pixel based on scaling
      int src_x = (int)(i / scale);
      int src_y = (int)(j / scale);

      // Fetch the palette color from the original bitmap, not the scaled one
      color_t color = img->palette[img->bitmap[src_x + src_y * img->width]];

      // Calculate the positions on the frame where the pixel should be drawn
      int frame_x = draw_start_x + i;
      int frame_y = draw_start_y + j;

      // Check boundaries to avoid overwriting the frame and ignore transparent pixels
      if (frame_x < DEFAULT_TFT_DISPLAY_HEIGHT && frame_y < DEFAULT_TFT_DISPLAY_WIDTH 
          && frame_x >= 0 && frame_y >= 0 
          && !(color.r == 0xff && color.g == 0x00 && color.b == 0xff)) {

        frame[frame_x + frame_y * DEFAULT_TFT_DISPLAY_HEIGHT] = color;
      }
    }
  }
}

void draw_bitmap(const bitmap_data *img, int x, int y, RenderOpt *opts) {
  float scale = (opts && opts->scale) ? opts->scale : 1.0f;

  int scaledWidth = (float)img->width * scale;
  int scaledHeight = (float)img->height * scale;

  // Check if the image is completely out of the frame
  if (x + scaledWidth < 0 || x > DEFAULT_TFT_DISPLAY_HEIGHT || y + scaledHeight < 0 || y > DEFAULT_TFT_DISPLAY_WIDTH) {
    return; // Image is out of frame, so return immediately
  }

  // Calculate the start and end values for loops to avoid unnecessary iteration
  int startX = (x < 0) ? -x : 0;
  int startY = (y < 0) ? -y : 0;
  int endX = (x + scaledWidth > DEFAULT_TFT_DISPLAY_HEIGHT) ? DEFAULT_TFT_DISPLAY_HEIGHT - x : scaledWidth;
  int endY = (y + scaledHeight > DEFAULT_TFT_DISPLAY_WIDTH) ? DEFAULT_TFT_DISPLAY_WIDTH - y : scaledHeight;

  float srcIncrementX = (float)img->width / scaledWidth;
  float srcIncrementY = (float)img->height / scaledHeight;

  float srcXAccum = (float)startX * srcIncrementX;

  // Iterate only within calculated bounds
  for (int i = startX; i < endX; i++) {
    float srcYAccum = (float)startY * srcIncrementY;
    for (int j = startY; j < endY; j++) {
      int srcX = (int)srcXAccum;
      int srcY = (int)srcYAccum;
      color_t color = img->palette[img->bitmap[srcX + srcY * img->width]];

      // Check for transparent color
      if (color.r == 0xff && color.g == 0x00 && color.b == 0xff) {
        if (opts && !opts->antialias) {
          srcYAccum += srcIncrementY;
          continue;
        }
        int sumR = 0, sumG = 0, sumB = 0, count = 0;

        // Define relative positions of adjacent pixels
        int adjX[] = {-1, 1, 1, -1};
        int adjY[] = {-1, 1, -1, 1};

        // Check only the top, right, bottom, and left pixels
        for (int k = 0; k < 4; k++) {
          int nx = srcX + adjX[k];
          int ny = srcY + adjY[k];
          if (nx >= 0 && nx < img->width && ny >= 0 && ny < img->height) {
            color_t adjacentColor = img->palette[img->bitmap[nx + ny * img->width]];
            if (adjacentColor.r != 0xff || adjacentColor.g != 0x00 || adjacentColor.b != 0xff) {
              if (opts && opts->invert) {
                sumR += 255 - adjacentColor.r;
                sumG += 255 - adjacentColor.g;
                sumB += 255 - adjacentColor.b;
              } else {
                sumR += adjacentColor.r;
                sumG += adjacentColor.g;
                sumB += adjacentColor.b;
              }
              count++;
            }
          }
        }

        // If there are any non-transparent adjacent pixels, calculate the average
        if (count > 0) {
          color_t current_pixel = frame[(x + i) + (y + j) * DEFAULT_TFT_DISPLAY_HEIGHT];
          color.r = (sumR + current_pixel.r) / (count + 1);
          color.g = (sumG + current_pixel.g) / (count + 1);
          color.b = (sumB + current_pixel.b) / (count + 1);
        } else {
          srcYAccum += srcIncrementY;
          continue; // Skip if the pixel is transparent and has no non-transparent neighbors
        }
      } else if (opts != NULL && color.r == color.g && color.g == color.b && color.b != 0xff) {
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

      if (opts != NULL && opts->transparency < 1) {
        color_t current_pixel = frame[(x + i) + (y + j) * DEFAULT_TFT_DISPLAY_HEIGHT];
        float alpha = opts->transparency;
        color.r = current_pixel.r * (1.0f - alpha) + color.r * alpha;
        color.g = current_pixel.g * (1.0f - alpha) + color.g * alpha;
        color.b = current_pixel.b * (1.0f - alpha) + color.b * alpha;
      }

      frame[(x + i) + (y + j) * DEFAULT_TFT_DISPLAY_HEIGHT] = color;
      srcYAccum += srcIncrementY;
    }
    srcXAccum += srcIncrementX;
  }
}

bitmap_data* get_bitmap_for_name(char* name, int len, uint8_t mask) {
	for (int i = 0; i < n_bitmaps; i++) {
    if (!(bitmap_db[i]->mask & mask)) {
      continue;
    }
		if (strncmp(bitmap_db[i]->name, name, len) == 0) {
			return bitmap_db[i];
		}
	}
  ESP_LOGI(SGO_LOG_NOSEND, "Does not exist %c", name[0]);
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
