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
#include "stdint.h"
#include "stdlib.h"

#include "../m5tft/path.h"

#define N_METRICS_VALUES 24

uint8_t humidity[N_METRICS_VALUES] = {0};
uint8_t temperature[N_METRICS_VALUES] = {0};
uint8_t co2[N_METRICS_VALUES] = {0};
uint8_t vpd[N_METRICS_VALUES] = {0};

uint8_t light[N_METRICS_VALUES] = {0};

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

void init_graphs_labels(Node *node) {
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
}
