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

#include "app.h"

#include "math.h"
#include "../core/kv/kv.h"
#include "../core/log/log.h"

typedef struct {

  Node *temperature;
  Node *humidity;
  Node *co2;

  Node *phase;
  Node *since;

  Node *loading;

} metrics_screen_params;

TickType_t metrics_screen_loop(Node *node, void *p) {
  metrics_screen_params *params = (metrics_screen_params *)p;

  fill_screen((color_t){43, 63, 81});

  char value[6] = {0};
  sprintf(value, "%d°", get_box_0_temp());
  set_text_node(params->temperature, value, NORMAL_FONT_SIZE);

  sprintf(value, "%d%%", get_box_0_humi());
  set_text_node(params->humidity, value, NORMAL_FONT_SIZE);

  sprintf(value, "%d", get_box_0_co2());
  NodeSize size = set_text_node(params->co2, value, NORMAL_FONT_SIZE);
  params->co2->x = 160 - size.width - 10;

  return 2000 / portTICK_PERIOD_MS;
}

Node *create_temperature() {
  char value[4] = {0};
  sprintf(value, "%d°", get_box_0_temp());
  Node *node = create_text_node(5, 5, 3, value, (color_t){ 59, 179, 11 }, NORMAL_FONT_SIZE);
  return node;
}

Node *create_humidity() {
  char value[4] = {0};
  sprintf(value, "%d%%", get_box_0_humi());
  Node *node = create_text_node(5, 45, 3, value, (color_t){ 51, 203, 212 }, NORMAL_FONT_SIZE);
  return node;
}

Node *create_co2() {
  char value[5] = {0};
  sprintf(value, "%d", get_box_0_co2());
  Node *node = create_text_node(80, 26, 7, value, (color_t){ 217, 69, 184 }, NORMAL_FONT_SIZE);
  for (int i = 0; i < node->num_children; ++i) {
    node->children[i]->renderOpts.scale = 0.9;
  }
  NodeSize size = set_text_node(node, value, NORMAL_FONT_SIZE);
  node->x = 160 - size.width - 10;
  return node;
}

Node *create_co2_label() {
  Node *node = create_text_node(100, 60, 7, "ppm", (color_t){ 217, 69, 184 }, NORMAL_FONT_SIZE);
  for (int i = 0; i < node->num_children; ++i) {
    node->children[i]->renderOpts.scale = 0.8;
  }
  NodeSize size = set_text_node(node, "ppm", NORMAL_FONT_SIZE);
  node->x = 160 - size.width - 10;
  node->y = 80 - size.height - 5;
  return node;
}

Node *create_phase() {
  const char *value = "Blooming Week 2 Day 5";
  Node *node = create_text_node(80, 5, 25, value, (color_t){ 255, 255, 255 }, NORMAL_FONT_SIZE);
  node->renderOpts.offsetNumbers = true;
  for (int i = 0; i < node->num_children; ++i) {
    node->children[i]->renderOpts.scale = 0.6;
    node->children[i]->renderOpts.limit = true;
    node->children[i]->renderOpts.frame = (frame_limits){80, 0, 150, 25};
  }
  NodeSize size = set_text_node(node, value, NORMAL_FONT_SIZE);

  SineAnimationParams *params1 = (SineAnimationParams*)malloc(sizeof(SineAnimationParams));
  params1->center_x = 120 - size.width/2;
  params1->center_y = node->y;
  params1->magnitude_x = (size.width - 80)/2 + 15;
  params1->magnitude_y = 0;
  params1->elapsedTime = M_PI * 2.5;
  params1->speed=0.01;

  node->funcParams[0] = params1;
  node->funcs[0] = sine_animation;

  return node;
}

Node *create_loading() {
  Node *node = create_text_node(80, 5, 25, "loading", (color_t){ 255, 255, 255 }, NORMAL_FONT_SIZE);
  NodeSize size = set_text_node(node, "loading", NORMAL_FONT_SIZE);
  node->x = 80 - size.width/2;
  node->y = 40 - size.height/2;
  return node;
}

void init_metrics_screen(Node *root) {
  metrics_screen_params *params = (metrics_screen_params *)malloc(sizeof(metrics_screen_params));

  params->temperature = create_temperature();
  add_child(root, params->temperature);

  params->humidity = create_humidity();
  add_child(root, params->humidity);

  params->co2 = create_co2();
  add_child(root, params->co2);

  Node *label = create_co2_label();
  add_child(root, label);

  params->phase = create_phase();
  add_child(root, params->phase);

  params->loading = create_loading();
  add_child(root, params->loading);

  root->funcParams[0] = params;
  root->funcs[0] = metrics_screen_loop;
}
