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

#include <string.h>

#include "node.h"
#include "math.h"
#include "bitmaps.h"
#include "bitmaps_definitions.h"
#include "freertos/task.h"
#include "../core/log/log.h"

// Animation function

TickType_t  simple_animation(Node *node, void *p) {
  SimpleAnimationParams *params = (SimpleAnimationParams *)p;

  // Calculate the distance to the destination
  float dx = params->dest_x - node->x;
  float dy = params->dest_y - node->y;

  // Normalize the distance based on speed while maintaining direction
  float distance = sqrtf(dx*dx + dy*dy);

  // If we're close enough to the destination, snap to it
  if (distance <= params->speed) {
    node->x = params->dest_x;
    node->y = params->dest_y;

    if (params->nextFunc) {
      node->funcs[params->nextFuncIndex] = params->nextFunc;
      node->funcParams[params->nextFuncIndex] = params->nextParams;
    } else {
      // If no next function, set node function to NULL (halt further actions/animations)
      node->funcs[params->nextFuncIndex] = NULL;
      node->funcParams[params->nextFuncIndex] = NULL;
    }

    return LONG_TICK;
  }

  // Calculate the step size while keeping the direction
  float step_x = params->speed * (dx / distance);
  float step_y = params->speed * (dy / distance);

  // Update the node's position
  node->x += step_x;
  node->y += step_y;
  return SHORT_TICK;
}

TickType_t sine_animation(Node *node, void *p) {
  SineAnimationParams *params = (SineAnimationParams *)p;

  // Use elapsedTime to determine the phase of the sine wave
  float offset_x = params->magnitude_x * sinf(params->elapsedTime);
  float offset_y = params->magnitude_y * cosf(params->elapsedTime);

  node->x = params->center_x + offset_x;
  node->y = params->center_y + offset_y;

  params->elapsedTime += params->speed; // Adjust this value to change the speed of the oscillation
                                        //
  return SHORT_TICK;
}

TickType_t simple_transparency_animation(Node *node, void *p) {
  SimpleTransparencyAnimationParams *params = (SimpleTransparencyAnimationParams*)p;

  // Check if the node's transparency has reached the destination transparency
  if ((params->speed > 0 && node->renderOpts.transparency >= params->dest_transparency) ||
      (params->speed < 0 && node->renderOpts.transparency <= params->dest_transparency)) {

    node->renderOpts.transparency = params->dest_transparency;  // Ensure it doesn't overshoot

    // Check if there's a next function to execute after this animation
    if (params->nextFunc) {
      node->funcs[params->nextFuncIndex] = params->nextFunc;
      node->funcParams[params->nextFuncIndex] = params->nextParams;
    } else {
      // If no next function, set node function to NULL (halt further animations)
      node->funcs[params->nextFuncIndex] = NULL;
      node->funcParams[params->nextFuncIndex] = NULL;
    }

    // Returning 0 to stop the timer
    return LONG_TICK;
  }

  // Update the transparency of the node
  node->renderOpts.transparency += params->speed;

  // Return a delay. For this example, I'll use a fixed delay of 50ms. Adjust as necessary.
  return SHORT_TICK;  
}

TickType_t sine_transparency_animation(Node *node, void *p) {
  SineTransparencyAnimationParams *params = (SineTransparencyAnimationParams *)p;

  float transparencyRange = params->max_transparency - params->min_transparency;
  float transparency = params->min_transparency + transparencyRange * (sin(params->elapsed_time) + 1) / 2;

  node->renderOpts.transparency = transparency;

  params->elapsed_time += params->speed;
  return SHORT_TICK;
}

TickType_t wait_action(Node *node, void *p) {
  WaitActionParams *params = (WaitActionParams*)p;
  TickType_t currentTime = xTaskGetTickCount() * portTICK_PERIOD_MS;  // Assuming you're using FreeRTOS, adjust if otherwise

  if (params->since < 0) {
    params->since = currentTime;
  }

  TickType_t elapsedTime = currentTime - params->since;

  // Check if elapsed time has reached the duration
  if (elapsedTime >= params->duration) {
    // Check if there's a next function to execute after this action
    if (params->nextFunc) {
      node->funcs[params->nextFuncIndex] = params->nextFunc;
      node->funcParams[params->nextFuncIndex] = params->nextParams;
    } else {
      // If no next function, set node function to NULL (halt further actions/animations)
      node->funcs[params->nextFuncIndex] = NULL;
      node->funcParams[params->nextFuncIndex] = NULL;
    }

    // Returning 0 to stop the timer
    return LONG_TICK;
  }

  // Return a delay for the remaining duration
  return (params->duration - elapsedTime) / portTICK_PERIOD_MS;
}

// Node management functions

// Create a new node. For simplicity, memory allocation is straightforward and lacks error checking.
Node* create_node(int x, int y, bitmap_data *bitmap, NodeFunction func, void *funcParams) {
  Node *node = (Node*)malloc(sizeof(Node));

  memset(&node->renderOpts, 0, sizeof(RenderOpt));
  memset(node->funcParams, 0, sizeof(void *) * 4);
  memset(node->funcs, 0, sizeof(NodeFunction) * 4);

  node->x = x;
  node->y = y;
  node->bitmap = bitmap;
  node->funcParams[0] = funcParams;
  node->funcs[0] = func;
  node->children = NULL;
  node->num_children = 0;
  node->renderOpts.transparency = 1;
  return node;
}

void delete_node(Node *node) {
  // Recursively delete all child nodes
  for (int i = 0; i < node->num_children; i++) {
    delete_node(node->children[i]);
  }

  // Free children array if it exists
  if (node->children) {
    free(node->children);
  }

  // Free function parameters if they exist
  for (int i = 0; i < 4; i++) { // Assuming a maximum of 4 based on the given memset size in create_node
    if (node->funcParams[i]) {
      free(node->funcParams[i]);
    }
  }

  // Finally, free the node itself
  free(node);
}

void add_child(Node *parent, Node *child) {
  if (parent->num_children == 0) {
    parent->children = (Node**)malloc(sizeof(Node*));
  } else {
    parent->children = (Node**)realloc(parent->children, (parent->num_children + 1) * sizeof(Node*));
  }

  parent->children[parent->num_children] = child;
  parent->num_children++;
}

void remove_child(Node *parent, Node *child) {
  int foundIndex = -1;

  // Find the child in the parent's children array
  for (int i = 0; i < parent->num_children; i++) {
    if (parent->children[i] == child) {
      foundIndex = i;
      break;
    }
  }

  // If child not found, simply return
  if (foundIndex == -1) {
    return;
  }

  // Remove the child from the array
  for (int i = foundIndex; i < parent->num_children - 1; i++) {
    parent->children[i] = parent->children[i + 1];
  }
  parent->num_children--;

  // Resize the memory allocated for the children array
  if (parent->num_children == 0) {
    free(parent->children);
    parent->children = NULL;
  } else {
    parent->children = (Node**)realloc(parent->children, parent->num_children * sizeof(Node*));
  }
}

TickType_t root_render(Node *node) {
  return render_node(node, 0, 0, 1);
}

TickType_t render_node(Node *node, int parent_x, int parent_y, float transparency) {
  // Call the node's custom function (if it exists)
  TickType_t tickTime = LONG_TICK;
  for (int i = 0; i < N_NODE_FUNCTION; ++i) {
    if (node->funcs[i] != NULL) {
      TickType_t t = node->funcs[i](node, node->funcParams[i]);
      if (t < tickTime) {
        tickTime = t;
      }
    }
  }

  // Draw the node's bitmap (if it exists)
  if (node->bitmap) {
    RenderOpt opts = node->renderOpts;
    opts.transparency *= transparency;
    draw_bitmap(node->bitmap, parent_x + node->x, parent_y + node->y, &opts);
  }

  for (int i = 0; i < node->num_children; i++) {
    TickType_t t = render_node(node->children[i], parent_x + node->x, parent_y + node->y, node->renderOpts.transparency * transparency);
    if (t < tickTime) {
      tickTime = t;
    }
  }
  return tickTime;
}

// Text node

void set_text_node(Node *textNode, const char *text, uint8_t mask) {
  int len = strlen(text);
  float currentX = 0;  // Starting x position

  // Limit the text length to the number of allocated child nodes
  if(len > textNode->num_children) {
    len = textNode->num_children;
  }

  int i = 0;
  for (; i < len; i++) {
    char c = text[i];

    bitmap_data *charBitmap = get_bitmap_for_name(&c, 1, mask);
    if (charBitmap == NULL) {
      continue;  // Skip this character if we don't have a bitmap for it
    }

    Node *letterNode = textNode->children[i];

    letterNode->x = currentX;
    letterNode->y = 0;  // No change in y-axis for this use-case
    letterNode->bitmap = charBitmap;

    currentX += charBitmap->width;  // Move the x position for the next character
  }
  for (; i < textNode->num_children; i++) {
    textNode->children[i]->bitmap = NULL;
  }
}

Node* create_text_node(int x, int y, int max_length, const char *text, color_t color, uint8_t mask) {
  Node *root = create_node(x, y, NULL, NULL, NULL);

  for(int i = 0; i < max_length; i++) {
    Node *letterNode = create_node(0, 0, NULL, NULL, NULL);
    letterNode->renderOpts.targetColor = color;
    add_child(root, letterNode);
  }

  set_text_node(root, text, mask);

  return root;
}
