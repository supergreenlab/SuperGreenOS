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

typedef struct {

  Node *test;

} metrics_screen_params;

TickType_t metrics_screen_loop(Node *node, void *p) {
  metrics_screen_params *params = (metrics_screen_params *)p;

  fill_screen((color_t){43, 63, 81});

  return LONG_TICK;
}

void init_metrics_screen(Node *root) {
  metrics_screen_params *params = (metrics_screen_params *)malloc(sizeof(metrics_screen_params));

  SineScaleAnimationParams *params1scale = (SineScaleAnimationParams*)malloc(sizeof(SineScaleAnimationParams));
  params1scale->min_scale = 0.5;
  params1scale->max_scale = 1.6;
  params1scale->elapsed_time = 0;
  params1scale->speed = 0.086;

  params->test = create_text_node(80, 40, 3, "26", (color_t){255, 255, 255}, NORMAL_FONT_SIZE);
  params->test->funcParams[0] = params1scale;
  params->test->funcs[0] = sine_scale_animation;

  for (int i = 0; i < params->test->num_children; ++i) {
    params->test->children[i]->renderOpts.invert = true;
  }

  add_child(root, params->test);

  root->funcParams[0] = params;
  root->funcs[0] = metrics_screen_loop;
}
