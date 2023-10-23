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

#ifndef APP_H
#define APP_H

#include "node.h"

typedef struct {

  int current_temp;
  int current_humi;
  int current_co2;

  int last_temp;
  int last_humi;
  int last_co2;
  TickType_t last_fetch;

  Node *background_node;

  Node *temperature;
  Node *humidity;
  Node *co2;

  Node *phase;

  Node *loading;

} metrics_screen_params;

void init_screen_app(Node *root);
void init_metrics_screen(Node *root, metrics_screen_params *params);

#endif
