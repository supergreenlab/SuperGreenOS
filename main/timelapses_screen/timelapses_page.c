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

#include "freertos/task.h"
#include "../m5tft/m5tft.h"
#include "../core/log/log.h"

typedef struct {
  Node *textNode;
} timelapses_params;

#define BATCH_READ_SIZE 100
#define PALETTE_SIZE 100
color_t palette[PALETTE_SIZE] = { 0 };

void draw_timelapse_frame(Node *node, int x, int y) {
	FILE *file = fopen("frame.dat", "rb");
	if (file == NULL) {
		//perror("Failed to open file");
		return;
	}

	uint8_t buffer[BATCH_READ_SIZE];
	int bytesRead;
	int totalPixels = SCREEN_WIDTH * SCREEN_HEIGHT;
	int pixelIndex = 0;

	while ((bytesRead = fread(buffer, 1, BATCH_READ_SIZE, file)) > 0) {
		if (bytesRead == 0) {
			break;
		}
		for (int i = 0; i < bytesRead; i++) {
			int x2 = (pixelIndex % SCREEN_WIDTH);
			int y2 = (pixelIndex / SCREEN_WIDTH);

			if (pixelIndex >= totalPixels) {
				break;
			}

			if (x2 + x >= 0 && x2 + x < SCREEN_WIDTH && y2 + y >= 0 && y2 + y < SCREEN_HEIGHT) {
				frame[(x2 + x) + (y2 + y) * SCREEN_WIDTH] = palette[buffer[i]];
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
  xSemaphoreGive(render_mutex);
}

void update_timelapse_frame(uint32_t offset, uint16_t len, uint8_t *colors) {
  while( xSemaphoreTake( render_mutex, portMAX_DELAY ) != pdPASS );
  FILE* f = fopen("frame.dat", "wb");
  if (f == NULL) {
    ESP_LOGE(SGO_LOG_NOSEND, "Failed to open file for writing");
    return;
  }
  fseek(f, offset, SEEK_SET);
  size_t written = fwrite(colors, 1, len, f);
  if (written != len) {
    ESP_LOGE(SGO_LOG_NOSEND, "Failed to write complete data");
  } else {
    ESP_LOGI(SGO_LOG_NOSEND, "Data written successfully");
  }
	fclose(f);
  xSemaphoreGive(render_mutex);
}

void init_timelapses_page(Node *root) {
	Node *graphsNode = create_node(0, 0, NULL, NULL, NULL);
	graphsNode->drawFunc = draw_timelapse_frame;
	add_child(root, graphsNode);
}
