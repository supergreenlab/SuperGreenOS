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

#ifndef NODE_H
#define NODE_H

#include "bitmaps.h"
#include "freertos/queue.h"
#include <string.h>
#include "freertos/semphr.h"

extern SemaphoreHandle_t render_mutex;

typedef struct Node Node;

typedef TickType_t (*NodeFunction)(Node *node, void *p);
typedef void (*DrawFunction)(Node *node, int x, int y);

#define N_NODE_FUNCTION 4

struct Node {
  float x;
  float y;
  bitmap_data *bitmap;
  DrawFunction drawFunc;
  void *funcParams[N_NODE_FUNCTION];
  NodeFunction funcs[N_NODE_FUNCTION];
  Node **children;
  int num_children;
  Node *parent;

  RenderOpt renderOpts;
};

typedef struct {
  float width;
  float height;
} NodeSize;

TickType_t root_render(Node *node);
TickType_t render_node(Node *node, float parent_x, float parent_y, float transparency, float scale);

float get_effective_scale(const Node *node);
Node* create_node(int x, int y, bitmap_data *bitmap, NodeFunction func, void *funcParams);
void add_child(Node *parent, Node *child);
NodeSize set_text_node(Node *textNode, const char *text, uint8_t mask);
Node* create_text_node(int x, int y, int max_length, const char *text, color_t color, uint8_t mask);
void delete_node(Node *node);
void remove_child(Node *parent, Node *child);
TickType_t sort_children_by_scale(Node *node, void *p);

#define SHORT_TICK 10 / portTICK_PERIOD_MS
#define LONG_TICK 1000 / portTICK_PERIOD_MS

typedef struct {

  float dest_x;
  float dest_y;
  float speed; // pixels per frame; how fast the node should move towards its destination

  int nextFuncIndex;
  void *nextParams;
  NodeFunction nextFunc;

} SimpleAnimationParams;

TickType_t simple_animation(Node *node, void *p);

typedef struct {

  float center_x;
  float center_y;
  float magnitude_x;
  float magnitude_y;
  float elapsedTime; // To keep track of time for sin oscillation
  float speed;

} SineAnimationParams;

TickType_t sine_animation(Node *node, void *p);

typedef struct {

  float xfrom;
  float yfrom;
  float xto;
  float yto;
  float elapsedTime; // To keep track of time for sin oscillation
  float speed;

} SineAnimationBetweenParams;

TickType_t sine_animation_between(Node *node, void *p);

typedef struct {

  float dest_transparency;
  float speed;

  int nextFuncIndex;
  void *nextParams;
  NodeFunction nextFunc;

} SimpleTransparencyAnimationParams;

TickType_t simple_transparency_animation(Node *node, void *p);

typedef struct {

  float min_transparency;
  float max_transparency;
  float elapsed_time;
  float speed;

} SineTransparencyAnimationParams;

TickType_t sine_transparency_animation(Node *node, void *p);

typedef struct {

  float min_scale;
  float max_scale;
  float elapsed_time;
  float speed;

} SineScaleAnimationParams;

TickType_t sine_scale_animation(Node *node, void *p);

typedef struct {

  float dest_scale;
  float speed;

  int nextFuncIndex;
  void *nextParams;
  NodeFunction nextFunc;

} SimpleScaleAnimationParams;

TickType_t simple_scale_animation(Node *node, void *p);

typedef struct {

  int since;
  int duration;

  int nextFuncIndex;
  void *nextParams;
  NodeFunction nextFunc;

} WaitActionParams;

TickType_t wait_action(Node *node, void *p);

#endif
