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

color_t palette[100];
uint8_t *timelapse_frame;

void draw_timelapse_frame(Node *node, int x, int y) {
  for (int y2 = 0; y2 < SCREEN_HEIGHT; ++y2) {
    for (int x2 = 0; x2 < SCREEN_WIDTH; ++x2) {
      if (x2 + x < 0 || x2 + x > SCREEN_WIDTH) {
        continue;
      }
      if (y2 + y < 0 || y2 + y > SCREEN_HEIGHT) {
        continue;
      }
      frame[(x2 + x) + (y2 + y) * SCREEN_WIDTH] = palette[timelapse_frame[x2 + y2 * SCREEN_WIDTH]];
    }
  }
}

void update_timelapse_palette(uint16_t len, color_t *colors) {
  while( xSemaphoreTake( render_mutex, portMAX_DELAY ) != pdPASS );
  memset(palette, 0, sizeof(palette));
  memcpy(palette, colors, sizeof(color_t) * len);
  xSemaphoreGive(render_mutex);
}

void update_timelapse_frame(uint32_t offset, uint16_t len, uint8_t *colors) {
  while( xSemaphoreTake( render_mutex, portMAX_DELAY ) != pdPASS );
  memcpy(timelapse_frame + offset, colors, len);
  xSemaphoreGive(render_mutex);
}

void init_timelapses_page(Node *root) {
  timelapse_frame = malloc(sizeof(uint8_t) * (SCREEN_WIDTH * SCREEN_HEIGHT));
  memset(timelapse_frame, 0, sizeof(uint8_t) * (SCREEN_WIDTH * SCREEN_HEIGHT));
	Node *graphsNode = create_node(0, 0, NULL, NULL, NULL);
	graphsNode->drawFunc = draw_timelapse_frame;
	add_child(root, graphsNode);
}
