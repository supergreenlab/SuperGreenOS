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

#include "timelapses_page.h"

#include <sys/unistd.h>
#include "freertos/task.h"
#include "../m5tft/m5tft.h"
#include "../core/log/log.h"

#include <stdio.h>

typedef struct {
  Node *textNode;
} timelapses_params;

#define BATCH_READ_SIZE 100
#define PALETTE_SIZE 40
color_t palette[PALETTE_SIZE] = { 0 };

void draw_timelapse_frame(Node *node, int x, int y) {
  if (x >= SCREEN_WIDTH || x <= -SCREEN_WIDTH) {
    return;
  }

	FILE *file = fopen("/spiffs/frame.dat", "rb");
	if (file == NULL) {
		// perror("Failed to open file");
		return;
	}

	uint8_t buffer[BATCH_READ_SIZE];
	int bytesRead;
	// Adjust totalPixels to match the source image size, not the frame buffer size
	int totalPixels = 80 * 40; // Source image size
	int pixelIndex = 0;

	while ((bytesRead = fread(buffer, 1, BATCH_READ_SIZE, file)) > 0) {
		if (bytesRead == 0) {
			break;
		}
		for (int i = 0; i < bytesRead; i++) {
			// Calculate original source image coordinates
			int x2 = (pixelIndex % 80); // Source image width
			int y2 = (pixelIndex / 80); // Source image height

			if (pixelIndex >= totalPixels) {
				break;
			}

			// Scale coordinates for the frame buffer and offset by x, y
			int newX = (x2 * 2) + x;
			int newY = (y2 * 2) + y;

			// Write the pixel to a 2x2 area in the frame buffer
			for (int dy = 0; dy < 2; dy++) {
				for (int dx = 0; dx < 2; dx++) {
					if (newX + dx >= 0 && newX + dx < SCREEN_WIDTH && newY + dy >= 0 && newY + dy < SCREEN_HEIGHT) {
            if (palette[buffer[i]].r == 0 && palette[buffer[i]].g == 0 && palette[buffer[i]].b == 0) {
              continue;
            }
						frame[(newX + dx) + ((newY + dy) * SCREEN_WIDTH)] = palette[buffer[i]];
					}
				}
			}

			pixelIndex++;
		}
	}

	fclose(file);
}

void update_timelapse_palette(uint16_t len, color_t *colors) {
  while( xSemaphoreTake( render_mutex, portMAX_DELAY ) != pdPASS );
  memset(palette, 0, sizeof(palette));
  memcpy(palette, colors, sizeof(color_t) * len);
	printf("Palette: [ ");
	for (int i = 0; i < len; ++i) {
		printf("%d, %d, %d, ", palette[i].r, palette[i].g, palette[i].b);
	}
	printf(" ]\n");
  xSemaphoreGive(render_mutex);
}

void update_timelapse_frame(uint32_t offset, uint16_t len, uint8_t *colors) {
  while( xSemaphoreTake( render_mutex, portMAX_DELAY ) != pdPASS );

  FILE* f = NULL;
  if (offset == 0) {
    unlink("/spiffs/frame.dat");
  }
  f = fopen("/spiffs/frame.dat", "ab");
  if (f == NULL) {
    ESP_LOGE(SGO_LOG_NOSEND, "Failed to open file for writing");
    xSemaphoreGive(render_mutex);
    return;
  }
  ESP_LOGI(SGO_LOG_NOSEND, "Writing frame at %d", offset);
  size_t written = fwrite(colors, 1, len, f);
  if (written != len) {
    ESP_LOGE(SGO_LOG_NOSEND, "Failed to write complete data %d != %d", len, written);
  } else {
    ESP_LOGI(SGO_LOG_NOSEND, "Data written successfully %d", written);
  }
	fclose(f);
  xSemaphoreGive(render_mutex);
}

void init_timelapses_page(Node *root) {
	Node *graphsNode = create_node(0, 0, NULL, NULL, NULL);
	graphsNode->drawFunc = draw_timelapse_frame;
	add_child(root, graphsNode);
}
