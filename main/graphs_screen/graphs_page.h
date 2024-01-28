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

#ifndef GRAPHS_PAGE_H
#define GRAPHS_PAGE_H

#include "stdint.h"
#include "../m5tft/node.h"

#define N_METRICS_VALUES 24

typedef enum {
  TEMP_METRIC,
  HUMI_METRIC,
  VPD_METRIC,
  CO2_METRIC,
  WEIGHT_METRIC,
  LIGHT_METRIC,
} metric_types;

void update_graphs(metric_types type, uint8_t values[N_METRICS_VALUES]);
void init_graphs_page(Node *root);

#endif
