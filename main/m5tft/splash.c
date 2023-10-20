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

#include "splash.h"
#include "../core/log/log.h"

typedef struct {
  
  Node *root;

  Node *super;
  Node *green;
  Node *lab;

} splash_params;

TickType_t slash_loop(Node *node, void *p) {
  //fill_screen((color_t){255, 255, 255});
  ESP_LOGI(SGO_LOG_NOSEND, "pouet");
  return SHORT_TICK;
}

Node *create_super() {
  /*SimpleAnimationParams *translation = (SimpleAnimationParams *)malloc(sizeof(SimpleAnimationParams));
  memset(translation, 0, sizeof(SimpleAnimationParams));
  translation->dest_x = 40;
  translation->dest_y = 5;
  translation->speed = 5;

  WaitActionParams *wait = (WaitActionParams *)malloc(sizeof(WaitActionParams));
  memset(wait, 0, sizeof(WaitActionParams));
  wait->since = -1;
  wait->duration = 1000;
  translation->nextParams = wait;
  translation->nextFunc = wait_action;*/

  /*SimpleTransparencyAnimationParams *fade = (SimpleTransparencyAnimationParams *)malloc(sizeof(SimpleTransparencyAnimationParams));
  memset(fade, 0, sizeof(SimpleTransparencyAnimationParams));
  fade->dest_transparency = 0;
  fade->speed = 1;

  wait->nextParams = fade;
  wait->nextFunc = simple_transparency_animation;*/

  Node *node = create_text_node(5, 5, 5, "super", (color_t){ 255, 255, 255 }, NORMAL_FONT_SIZE);
  for (int i = 0; i < node->num_children; ++i) {
		node->children[i]->renderOpts.invert = true;
	}

  //node->funcParams[0] = translation;
  //node->funcs[0] = simple_animation;
  return node;
}

Node *create_green() {
  Node *node = create_node(0, 0, NULL, NULL, NULL);
  return node;
}

Node *create_lab() {
  Node *node = create_node(0, 0, NULL, NULL, NULL);
  return node;
}

void init_splash(Node *root) {
  splash_params *params = (splash_params *)malloc(sizeof(splash_params));
  params->root = create_node(0, 0, NULL, slash_loop, params);
  add_child(root, params->root);

  params->super = create_super();
  add_child(params->root, params->super);

  /*params->green = create_green();
  add_child(params->root, params->green);

  params->lab = create_lab();
  add_child(params->root, params->lab);

  Node *test = create_text_node(10, 10, 5, "super", (color_t){23, 150, 200}, NORMAL_FONT_SIZE);
  add_child(root, test);*/
}
