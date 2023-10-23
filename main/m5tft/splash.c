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
#include "app.h"
#include "screensaver.h"
#include "../core/log/log.h"

typedef struct {
  
  Node *root;

  Node *super;
  Node *green;
  Node *lab;

} splash_params;

TickType_t splash_loop(Node *node, void *p) {
	splash_params *params = (splash_params *)p;
  //fill_screen((color_t){ 0, 0, 0 });
  fill_screen((color_t){43, 63, 81});

	if (params->green->funcs[0] == NULL) {
		ESP_LOGI(SGO_LOG_NOSEND, "Delete splash node");

		delete_node(params->root);

		node->funcs[0] = NULL;
		free(params);

		init_metrics_screen(node);
		//init_splash(node);
		//init_screensaver(node);
		return SHORT_TICK;
	}

  return SHORT_TICK;
}

Node *create_super() {
  SimpleAnimationParams *translation = (SimpleAnimationParams *)malloc(sizeof(SimpleAnimationParams));
  memset(translation, 0, sizeof(SimpleAnimationParams));
  translation->dest_x = 80;
  translation->dest_y = 15;
  translation->speed = 5;

  WaitActionParams *wait = (WaitActionParams *)malloc(sizeof(WaitActionParams));
  memset(wait, 0, sizeof(WaitActionParams));
  wait->since = -1;
  wait->duration = 2000;
  translation->nextParams = wait;
  translation->nextFunc = wait_action;

  SimpleTransparencyAnimationParams *fade = (SimpleTransparencyAnimationParams *)malloc(sizeof(SimpleTransparencyAnimationParams));
  memset(fade, 0, sizeof(SimpleTransparencyAnimationParams));
  fade->dest_transparency = 0;
  fade->speed = -0.05;
  wait->nextParams = fade;
  wait->nextFunc = simple_transparency_animation;

  Node *node = create_text_node(0, 0, 5, "SUPER", (color_t){ 255, 255, 255 }, NORMAL_FONT_SIZE);
  for (int i = 0; i < node->num_children; ++i) {
		//node->children[i]->renderOpts.invert = true;
	}

	for (int i = 1; i < node->num_children-1; ++i) {
		node->children[i]->renderOpts.scale=0.9;
		node->children[i]->y = 2;
	}
	NodeSize size = set_text_node(node, "SUPER", NORMAL_FONT_SIZE);

	node->x = -size.width/2;
	node->y = -size.height/2;

	Node *centerNode = create_node(-100, 15, NULL, simple_animation, translation);
	centerNode->renderOpts.scale = 0.8;
	add_child(centerNode, node);

  return centerNode;
}

Node *create_green() {
  WaitActionParams *wait_pre = (WaitActionParams *)malloc(sizeof(WaitActionParams));
  memset(wait_pre, 0, sizeof(WaitActionParams));
  wait_pre->since = -1;
  wait_pre->duration = 1000;

  SimpleScaleAnimationParams *scale = (SimpleScaleAnimationParams *)malloc(sizeof(SimpleScaleAnimationParams));
  memset(scale, 0, sizeof(SimpleScaleAnimationParams));
  scale->dest_scale = 1.2;
  scale->speed = 0.025;
  wait_pre->nextParams = scale;
  wait_pre->nextFunc = simple_scale_animation;

  WaitActionParams *wait = (WaitActionParams *)malloc(sizeof(WaitActionParams));
  memset(wait, 0, sizeof(WaitActionParams));
  wait->since = -1;
  wait->duration = 1000;
  scale->nextParams = wait;
  scale->nextFunc = wait_action;

  SimpleTransparencyAnimationParams *fade = (SimpleTransparencyAnimationParams *)malloc(sizeof(SimpleTransparencyAnimationParams));
  memset(fade, 0, sizeof(SimpleTransparencyAnimationParams));
  fade->dest_transparency = 0;
  fade->speed = -0.05;
  wait->nextParams = fade;
  wait->nextFunc = simple_transparency_animation;

  Node *node = create_text_node(0, 0, 5, "GREEN", (color_t){ 59, 179, 11 }, NORMAL_FONT_SIZE);
  for (int i = 0; i < node->num_children; ++i) {
		//node->children[i]->renderOpts.invert = true;
	}
	for (int i = 1; i < node->num_children-1; ++i) {
		node->children[i]->renderOpts.scale=0.9;
		node->children[i]->y = 3;
	}
	NodeSize size = set_text_node(node, "GREEN", NORMAL_FONT_SIZE);
	node->x = -size.width/2;
	node->y = -size.height/2;

	Node *centerNode = create_node(80, 40, NULL, wait_action, wait_pre);
	centerNode->renderOpts.scale = 0;
	add_child(centerNode, node);
  return centerNode;
}

Node *create_lab() {
  SimpleAnimationParams *translation = (SimpleAnimationParams *)malloc(sizeof(SimpleAnimationParams));
  memset(translation, 0, sizeof(SimpleAnimationParams));
  translation->dest_x = 80;
  translation->dest_y = 65;
  translation->speed = 5;

  WaitActionParams *wait = (WaitActionParams *)malloc(sizeof(WaitActionParams));
  memset(wait, 0, sizeof(WaitActionParams));
  wait->since = -1;
  wait->duration = 2000;
  translation->nextParams = wait;
  translation->nextFunc = wait_action;

  SimpleTransparencyAnimationParams *fade = (SimpleTransparencyAnimationParams *)malloc(sizeof(SimpleTransparencyAnimationParams));
  memset(fade, 0, sizeof(SimpleTransparencyAnimationParams));
  fade->dest_transparency = 0;
  fade->speed = -0.05;
  wait->nextParams = fade;
  wait->nextFunc = simple_transparency_animation;

  Node *node = create_text_node(0, 0, 3, "LAB", (color_t){ 255, 255, 255 }, NORMAL_FONT_SIZE);
  for (int i = 0; i < node->num_children; ++i) {
		//node->children[i]->renderOpts.invert = true;
	}
  node->children[1]->renderOpts.scale=0.9;
  node->children[1]->y = 2;
	NodeSize size = set_text_node(node, "LAB", NORMAL_FONT_SIZE);

	node->x = -size.width/2;
	node->y = -size.height/2;

	Node *centerNode = create_node(260, 65, NULL, simple_animation, translation);
	centerNode->renderOpts.scale = 0.8;
	add_child(centerNode, node);

  return centerNode;
}

void init_splash(Node *root) {
  splash_params *params = (splash_params *)malloc(sizeof(splash_params));
  params->root = create_node(0, 0, NULL, sort_children_by_scale, NULL);
  add_child(root, params->root);

	root->funcParams[0] = params;
	root->funcs[0] = splash_loop;

  params->super = create_super();
  add_child(params->root, params->super);

  params->green = create_green();
  add_child(params->root, params->green);

  params->lab = create_lab();
  add_child(params->root, params->lab);
}
