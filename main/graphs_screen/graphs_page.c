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

#include "graphs_page.h"

#include "math.h"
#include "stdlib.h"
#include "freertos/task.h"
#include "../core/log/log.h"

#include "../m5tft/path.h"

uint8_t humidity[N_METRICS_VALUES] = {0};
uint8_t temperature[N_METRICS_VALUES] = {0};
uint8_t co2[N_METRICS_VALUES] = {0};
uint8_t weight[N_METRICS_VALUES] = {0};
uint8_t vpd[N_METRICS_VALUES] = {0};
uint8_t light[N_METRICS_VALUES] = {0};

void update_graphs(metric_types type, uint8_t values[N_METRICS_VALUES]) {
  while( xSemaphoreTake( render_mutex, portMAX_DELAY ) != pdPASS );

  switch(type) {
    case TEMP_METRIC:
      memcpy(temperature, values, sizeof(uint8_t) * N_METRICS_VALUES);
      break;
    case HUMI_METRIC:
      memcpy(humidity, values, sizeof(uint8_t) * N_METRICS_VALUES);
      break;
    case VPD_METRIC:
      memcpy(vpd, values, sizeof(uint8_t) * N_METRICS_VALUES);
      break;
    case CO2_METRIC:
      memcpy(co2, values, sizeof(uint8_t) * N_METRICS_VALUES);
      break;
    case WEIGHT_METRIC:
      memcpy(weight, values, sizeof(uint8_t) * N_METRICS_VALUES);
      break;
    case LIGHT_METRIC:
      memcpy(light, values, sizeof(uint8_t) * N_METRICS_VALUES);
      break;
  }
  xSemaphoreGive(render_mutex);
}

typedef struct {
	Node *graphsNode;
} graphs_params;

void draw_graph(uint8_t* values, int len, int x, int y, color_t color) {
	for (int i = 0; i < len-1; ++i) {
		drawLineAA(x+5 + i * DEFAULT_TFT_DISPLAY_HEIGHT / N_METRICS_VALUES, y + DEFAULT_TFT_DISPLAY_WIDTH * 3 / 4 - values[i], x+5 + (i+1) * DEFAULT_TFT_DISPLAY_HEIGHT / N_METRICS_VALUES, y + DEFAULT_TFT_DISPLAY_WIDTH * 3 / 4 - values[i+1], color, 2);
	}
}

void draw_graphs(Node *node, int x, int y) {
	draw_graph(humidity, N_METRICS_VALUES, x, y, (color_t){153, 163, 245});
	draw_graph(temperature, N_METRICS_VALUES, x, y, (color_t){59, 179, 11});
	draw_graph(co2, N_METRICS_VALUES, x, y, (color_t){204, 204, 204});
	draw_graph(vpd, N_METRICS_VALUES, x, y, (color_t){199, 85, 21});
	draw_graph(light, N_METRICS_VALUES, x, y, (color_t){234, 198, 71});

	drawLineAA(x+5, y+5, x + 5, y + DEFAULT_TFT_DISPLAY_WIDTH * 3 / 4, (color_t){255, 255, 255}, 1);

	for (int i = 0; i < 6; ++i) {
		drawLineAA(x+5, y+5 + i * (DEFAULT_TFT_DISPLAY_WIDTH * 3 / 4) / 6, x, y+5 + i * (DEFAULT_TFT_DISPLAY_WIDTH * 3 / 4) / 6, (color_t){255, 255, 255}, 1);
	}

	drawLineAA(x+5, y + DEFAULT_TFT_DISPLAY_WIDTH * 3 / 4, x + DEFAULT_TFT_DISPLAY_HEIGHT - 10, y + DEFAULT_TFT_DISPLAY_WIDTH * 3 / 4, (color_t){255, 255, 255}, 1);

	for (int i = 0; i < 12; ++i) {
		drawLineAA(x+5 + i * DEFAULT_TFT_DISPLAY_HEIGHT / 12, y + DEFAULT_TFT_DISPLAY_WIDTH * 3 / 4, x+5 + i * DEFAULT_TFT_DISPLAY_HEIGHT / 12, y + DEFAULT_TFT_DISPLAY_WIDTH * 3 / 4 + 5, (color_t){255, 255, 255}, 1);
	}
}

typedef struct {
  color_t color;
} draw_entry_underline_params;

void draw_label_line(Node *node, int x, int y) {
  drawLineAA(x-3, y+10, x + 4, y+10, ((draw_entry_underline_params *)node->funcParams[0])->color, 4);
}

void init_graphs_label(Node *root, int x, int y, color_t color, const char *label) {
  Node *node = create_node(x, y, NULL, NULL, NULL);
  add_child(root, node);

  Node *l = create_text_node(8, 0, strlen(label), label, (color_t){ 255, 255, 255 }, SMALL_FONT_SIZE);
  for (int i = 0; i < l->num_children; ++i) {
    l->children[i]->renderOpts.scale = 0.95;
  }
  add_child(node, l);

  Node *d = create_node(0, 0, NULL, NULL, NULL);
  d->drawFunc = draw_label_line;
  d->funcParams[0] = malloc(sizeof(draw_entry_underline_params));
  ((draw_entry_underline_params *)d->funcParams[0])->color = color;
  add_child(node, d);
}

void init_graphs_labels(Node *node) {
  init_graphs_label(node, 5, 63, (color_t){ 113, 124, 223 }, "Humidity");
  init_graphs_label(node, 5, 80, (color_t){ 59, 179, 11 }, "Temperature");
  init_graphs_label(node, 75, 63, (color_t){ 204, 204, 204 }, "CO2");
  init_graphs_label(node, 75, 80, (color_t){ 199, 85, 21 }, "VPD");
  init_graphs_label(node, 120, 63, (color_t){ 234, 198, 71 }, "Light");
}

void init_graphs_page(Node *root) {
  graphs_params *params = (graphs_params *)malloc(sizeof(graphs_params));

	params->graphsNode = create_node(0, 0, NULL, NULL, NULL);
	params->graphsNode->drawFunc = draw_graphs;
	add_child(root, params->graphsNode);

	for (int i = 0; i < N_METRICS_VALUES; ++i) {
		humidity[i] = (rand() % 20 + 20);
	}

	for (int i = 0; i < N_METRICS_VALUES; ++i) {
		temperature[i] = (rand() % 20 + 15);
	}

	for (int i = 0; i < N_METRICS_VALUES; ++i) {
		vpd[i] = (rand() % 20 + 25);
	}

	for (int i = 0; i < N_METRICS_VALUES; ++i) {
		vpd[i] = (rand() % 10 + 5);
	}

	for (int i = 0; i < N_METRICS_VALUES; ++i) {
		light[i] = cosf((float)i/2) * 30 + 30;
		if (light[i] > 35) {
			light[i] = 35;
		}
	}

  init_graphs_labels(root);
}
