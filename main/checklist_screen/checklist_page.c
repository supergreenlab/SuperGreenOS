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

#include "checklist_page.h"

#include "../m5tft/m5tft.h"
#include "../core/log/log.h"

#include "../m5tft/path.h"

#include <stdbool.h>
#include <math.h>

typedef struct {
  Node *titleNode;
  Node *textNode[3];
} checklist_params;

Node *checklist_root;
checklist_params *chparams;
SineAnimationBetweenParams *chSinParam;

void draw_underline(Node *node, int x, int y) {
  drawLineAA(x - 30, 20, x + DEFAULT_TFT_DISPLAY_HEIGHT-1 - 30, 20, (color_t){ 59, 179, 11 }, 2);
}

void update_nchecklist(int nitems) {
  while( xSemaphoreTake( render_mutex, portMAX_DELAY ) != pdPASS );
  if (chparams->titleNode != NULL) {
    delete_node(chparams->titleNode);
  }

  char value[100] = {0};
  sprintf(value, "%d pending tasks", nitems);
  Node *node = create_text_node(30, 0, strlen(value), value, (color_t){ 255, 255, 255 }, SMALL_FONT_SIZE);

  for (int i = 0; i < strlen(value); ++i) {
    if (value[i] == ' ') {
      break;
    }
    
    node->children[i]->renderOpts.scale = 1.1;
    node->children[i]->renderOpts.targetColor = (color_t){ 59, 179, 11 };
  }
  
  Node *line = create_node(0, 0, NULL, NULL, NULL);
  line->drawFunc = draw_underline;
  add_child(node, line);

  add_child(checklist_root, node);
  chparams->titleNode = node;
  xSemaphoreGive(render_mutex);
}

void draw_entry_underline(Node *node, int x, int y) {
		drawLineAA(x, y + 20, x + DEFAULT_TFT_DISPLAY_HEIGHT-1, y + 20, (color_t){ 90, 138, 187 }, 1);
}

void update_checklist_entry(char *value, int index) {
  ESP_LOGI(SGO_LOG_NOSEND, "update_checklist_entry: %s", value);
  while( xSemaphoreTake( render_mutex, portMAX_DELAY ) != pdPASS );

  float elapsedTime = 0;
  if (chparams->textNode[index] != NULL) {
    if (chSinParam != NULL) {
      elapsedTime = chSinParam->elapsedTime;
    }
    delete_node(chparams->textNode[index]);
  }

  Node *node = create_text_node(5, index * 17 + 22, strlen(value), value, (color_t){ 255, 255, 255 }, SMALL_FONT_SIZE);
  //node->renderOpts.offsetNumbers = true;
  for (int i = 0; i < node->num_children; ++i) {
    node->children[i]->renderOpts.scale = 0.9;
    node->children[i]->renderOpts.limit = true;
    node->children[i]->renderOpts.frame = (frame_limits){SCREEN_WIDTH + 5, 5, SCREEN_WIDTH*2-10, SCREEN_HEIGHT-5};
    node->children[i]->renderOpts.frameRef = (node_position *)checklist_root->parent;
  }
  NodeSize size = set_text_node(node, value, SMALL_FONT_SIZE);

  int diff = SCREEN_WIDTH - size.width;
  if (diff < 0) {
    chSinParam = (SineAnimationBetweenParams*)malloc(sizeof(SineAnimationBetweenParams));
    chSinParam->xfrom = 10;
    chSinParam->xto = diff - 10;
		chSinParam->yfrom = node->y;
		chSinParam->yto = node->y;
    chSinParam->speed=0.01;
    chSinParam->elapsedTime = elapsedTime;

    node->funcParams[0] = chSinParam;
    node->funcs[0] = sine_animation_between;
  }

  add_child(checklist_root, node);

  chparams->textNode[index] = node;

  xSemaphoreGive(render_mutex);
}

void init_checklist_page(Node *root) {
  checklist_root = root;
  chSinParam = NULL;
  chparams = (checklist_params *)malloc(sizeof(checklist_params));
  memset(chparams, 0, sizeof(checklist_params));

  for (int i = 0; i < 3; ++i) {
    Node *line = create_node(0, i * 16 + 22, NULL, NULL, NULL);
    line->drawFunc = draw_entry_underline;
    add_child(checklist_root, line);
  }

  ESP_LOGI(SGO_LOG_NOSEND, "node[0]:  %d", (int)chparams);
}
