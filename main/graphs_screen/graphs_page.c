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

typedef struct {
  Node *textNode;
} graphs_params;

void init_graphs_page(Node *root) {
  graphs_params *params = (graphs_params *)malloc(sizeof(graphs_params));
  params->textNode = create_text_node(10, 10, 10, "Graphs", (color_t){255, 255, 255}, NORMAL_FONT_SIZE);
  add_child(root, params->textNode);
}
