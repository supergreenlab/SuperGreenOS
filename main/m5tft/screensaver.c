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

#include <stdlib.h>
#include <stdio.h>
#include "screensaver.h"
#include "math.h"

#include "../core/log/log.h"

typedef struct {
  float n;

  Node *textNode1;
  Node *textNode2;
  Node *textNode3;
  Node *textNode4;
} LoopParams;

TickType_t tester_loop(Node *node, void *p) {
  LoopParams *params = p;

  for (int i = 0; i < DEFAULT_TFT_DISPLAY_HEIGHT * DEFAULT_TFT_DISPLAY_WIDTH; ++i) {
    frame[i] = (color_t){43, 63, 81};
  }

  char text[10] = "";
  sprintf(text, "%04d°", (int)++params->n);
  set_text_node(params->textNode1, text, NORMAL_FONT_SIZE);

  sprintf(text, "%04d°", (int)(9999 - params->n));
  set_text_node(params->textNode2, text, NORMAL_FONT_SIZE);

  sprintf(text, "%04d", (int)(9999 - params->n));
  set_text_node(params->textNode3, text, NORMAL_FONT_SIZE);

  sprintf(text, "%04d°", (int)(9999 - params->n));
  set_text_node(params->textNode4, text, NORMAL_FONT_SIZE);

  params->n = (int)params->n % 10000;
  return SHORT_TICK;
}

void init_screensaver(Node *root) {
  ESP_LOGI(SGO_LOG_NOSEND, "init_tester");
  SineAnimationParams *params1 = (SineAnimationParams*)malloc(sizeof(SineAnimationParams));
  params1->center_x = 15;
  params1->center_y = 20;
  params1->magnitude_x = 20;
  params1->magnitude_y = 10;
  params1->elapsedTime = 0;
  params1->speed=0.1;

  SineTransparencyAnimationParams *params1trans = (SineTransparencyAnimationParams*)malloc(sizeof(SineTransparencyAnimationParams));
  params1trans->min_transparency = 0.2;
  params1trans->max_transparency = 0.8;
  params1trans->elapsed_time = 0;
  params1trans->speed = 0.0666666;

  SineScaleAnimationParams *params1scale = (SineScaleAnimationParams*)malloc(sizeof(SineScaleAnimationParams));
  params1scale->min_scale = 0.5;
  params1scale->max_scale = 1.6;
  params1scale->elapsed_time = 0;
  params1scale->speed = 0.086;

  Node* textNode1 = create_text_node(10, 10, 5, "0001°", (color_t){255, 255, 255}, NORMAL_FONT_SIZE);
  textNode1->funcParams[0] = params1;
  textNode1->funcs[0] = sine_animation;
  textNode1->funcParams[1] = params1trans;
  textNode1->funcs[1] = sine_transparency_animation;
  textNode1->funcParams[2] = params1scale;
  textNode1->funcs[2] = sine_scale_animation;
  textNode1->renderOpts.transparency = 0.5;

  for (int i = 0; i < textNode1->num_children; ++i) {
    textNode1->children[i]->renderOpts.invert = true;
  }

  add_child(root, textNode1);

  SineAnimationParams *params2 = (SineAnimationParams*)malloc(sizeof(SineAnimationParams));
  params2->center_x = 15;
  params2->center_y = 15;
  params2->magnitude_x = -20;
  params2->magnitude_y = -20;
  params2->elapsedTime = 0;
  params2->speed=-0.05;

  SineTransparencyAnimationParams *params2trans = (SineTransparencyAnimationParams*)malloc(sizeof(SineTransparencyAnimationParams));
  params2trans->min_transparency = 0.2;
  params2trans->max_transparency = 0.8;
  params2trans->elapsed_time = 0;
  params2trans->speed = -0.1333333;

  Node* textNode2 = create_text_node(10, 10, 5, "9999°", (color_t){51, 203, 212}, NORMAL_FONT_SIZE);
  textNode2->funcParams[0] = params2;
  textNode2->funcs[0] = sine_animation;

  textNode2->funcParams[1] = params2trans;
  textNode2->funcs[1] = sine_transparency_animation;

  add_child(root, textNode2);

  SineAnimationParams *params3 = (SineAnimationParams*)malloc(sizeof(SineAnimationParams));
  params3->center_x = 55;
  params3->center_y = 35;
  params3->magnitude_x = -20;
  params3->magnitude_y = -40;
  params3->elapsedTime = 0;
  params3->speed=0.075;

  SineTransparencyAnimationParams *params3trans = (SineTransparencyAnimationParams*)malloc(sizeof(SineTransparencyAnimationParams));
  params3trans->min_transparency = 0.2;
  params3trans->max_transparency = 0.8;
  params3trans->elapsed_time = M_PI/2;
  params3trans->speed = -0.1333333;

  Node* textNode3 = create_text_node(10, 10, 4, "9999", (color_t){212, 203, 51}, NORMAL_FONT_SIZE);
  textNode3->funcParams[0] = params3;
  textNode3->funcs[0] = sine_animation;

  textNode3->funcParams[1] = params3trans;
  textNode3->funcs[1] = sine_transparency_animation;

  add_child(root, textNode3);

  SineAnimationParams *params4 = (SineAnimationParams*)malloc(sizeof(SineAnimationParams));
  params4->center_x = 20;
  params4->center_y = 30;
  params4->magnitude_x = -50;
  params4->magnitude_y = -40;
  params4->elapsedTime = 0;
  params4->speed=0.1;

  SineTransparencyAnimationParams *params4trans = (SineTransparencyAnimationParams*)malloc(sizeof(SineTransparencyAnimationParams));
  params4trans->min_transparency = 0.2;
  params4trans->max_transparency = 0.8;
  params4trans->elapsed_time = M_PI/2;
  params4trans->speed = -0.2666666;

  Node* textNode4 = create_text_node(10, 10, 5, "9999°", (color_t){0, 51, 203}, NORMAL_FONT_SIZE);
  textNode4->funcParams[0] = params4;
  textNode4->funcs[0] = sine_animation;

  textNode4->funcParams[1] = params4trans;
  textNode4->funcs[1] = sine_transparency_animation;

  add_child(root, textNode4);

  LoopParams *params = (LoopParams *)malloc(sizeof(LoopParams));
  params->textNode1 = textNode1;
  params->textNode2 = textNode2;
  params->textNode3 = textNode3;
  params->textNode4 = textNode4;

  root->funcParams[0] = params;
  root->funcs[0] = tester_loop;
}
