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
#include "float.h"
#include "bitmaps.h"
#include "bitmaps_definitions.h"
#include "freertos/task.h"
#include "../core/log/log.h"

// Animation function

SemaphoreHandle_t render_mutex;

TickType_t sort_children_by_scale(Node *node, void *p) {
	int n = node->num_children;

	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n-i-1; j++) {
			if (node->children[j]->renderOpts.scale > node->children[j+1]->renderOpts.scale) {
				Node* temp = node->children[j];
				node->children[j] = node->children[j+1];
				node->children[j+1] = temp;
			}
		}
	}
	return LONG_TICK;
}

TickType_t  simple_animation(Node *node, void *p) {
  SimpleAnimationParams *params = (SimpleAnimationParams *)p;

  // Calculate the distance to the destination
  float dx = params->dest_x - node->x;
  float dy = params->dest_y - node->y;

  // Normalize the distance based on speed while maintaining direction
  float distance = sqrtf(dx*dx + dy*dy);

  // If we're close enough to the destination, snap to it
  if (distance <= abs(params->speed)) {
    node->x = params->dest_x;
    node->y = params->dest_y;

		free(params);

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
  //ESP_LOGI(SGO_LOG_NOSEND, "%f", params->elapsedTime);
                                        //
  return SHORT_TICK;
}

TickType_t sine_animation_between(Node *node, void *p) {
    SineAnimationBetweenParams *params = (SineAnimationBetweenParams *)p;

    float mid_x = (params->xfrom + params->xto) / 2.0;
    float mid_y = (params->yfrom + params->yto) / 2.0;

    float amplitude_x = (params->xto - params->xfrom) / 2.0;
    float amplitude_y = (params->yto - params->yfrom) / 2.0;

    float offset_x = amplitude_x * sinf(params->elapsedTime);
    float offset_y = amplitude_y * sinf(params->elapsedTime);

    node->x = mid_x + offset_x;
    node->y = mid_y + offset_y;

    params->elapsedTime += params->speed; // Adjust this value to change the speed of the oscillation

    return SHORT_TICK;
}

TickType_t simple_transparency_animation(Node *node, void *p) {
  SimpleTransparencyAnimationParams *params = (SimpleTransparencyAnimationParams*)p;

  // Update the transparency of the node
  node->renderOpts.transparency += params->speed;

  // Check if the node's transparency has reached the destination transparency
  if ((params->speed > 0 && node->renderOpts.transparency >= params->dest_transparency) ||
      (params->speed < 0 && node->renderOpts.transparency <= params->dest_transparency)) {

    node->renderOpts.transparency = params->dest_transparency;  // Ensure it doesn't overshoot

		free(params);

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

TickType_t sine_scale_animation(Node *node, void *p) {
  SineScaleAnimationParams *params = (SineScaleAnimationParams *)p;

  float scaleRange = params->max_scale - params->min_scale;
  float scale = params->min_scale + scaleRange * (sin(params->elapsed_time) + 1) / 2;

  node->renderOpts.scale = scale;

  params->elapsed_time += params->speed;
  return SHORT_TICK;
}

TickType_t simple_scale_animation(Node *node, void *p) {
  SimpleScaleAnimationParams *params = (SimpleScaleAnimationParams*)p;

  // Update the transparency of the node
  node->renderOpts.scale += params->speed;

  // Check if the node's transparency has reached the destination transparency
  if ((params->speed > 0 && node->renderOpts.scale >= params->dest_scale) ||
      (params->speed < 0 && node->renderOpts.scale <= params->dest_scale)) {

    node->renderOpts.scale = params->dest_scale;  // Ensure it doesn't overshoot

		free(params);

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

  // Return a delay. For this example, I'll use a fixed delay of 50ms. Adjust as necessary.
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
  memset(node, 0, sizeof(Node));

  node->x = x;
  node->y = y;
  node->bitmap = bitmap;
  node->funcParams[0] = funcParams;
  node->funcs[0] = func;
  node->num_children = 0;
  node->renderOpts.transparency = 1;
  node->renderOpts.antialias = true;
  node->renderOpts.scale = 1;
  return node;
}

void delete_node(Node *node) {
	if (node->parent) {
		remove_child(node->parent, node);
	}

  for (int i = 0; i < node->num_children; i++) {
		node->children[i]->parent = NULL;
    delete_node(node->children[i]);
  }

  if (node->children) {
    free(node->children);
  }

  for (int i = 0; i < N_NODE_FUNCTION; i++) {
    if (node->funcParams[i]) {
      free(node->funcParams[i]);
    }
  }

  free(node);
}

float get_effective_scale(const Node *node) {
  float resultingScale = 1.0f;

  while (node) {
    resultingScale *= node->renderOpts.scale;
    node = node->parent;
  }

  return resultingScale;
}

void add_child(Node *parent, Node *child) {
  if (parent->num_children == 0) {
    parent->children = (Node**)malloc(sizeof(Node*));
  } else {
    parent->children = (Node**)realloc(parent->children, (parent->num_children + 1) * sizeof(Node*));
  }

  parent->children[parent->num_children] = child;
  parent->num_children++;
  child->parent = parent;
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
	//ESP_LOGI(SGO_LOG_NOSEND, "=================\nROOT NODE");
  while( xSemaphoreTake( render_mutex, portMAX_DELAY ) != pdPASS );
  TickType_t d = render_node(node, 0, 0, 1, 1);
  xSemaphoreGive(render_mutex);
  return d;
}

TickType_t render_node(Node *node, float parent_x, float parent_y, float transparency, float scale) {

  TickType_t tickTime = LONG_TICK;
  for (int i = 0; i < N_NODE_FUNCTION; ++i) {
    if (node->funcs[i] != NULL) {
      TickType_t t = node->funcs[i](node, node->funcParams[i]);
      if (t < tickTime) {
        tickTime = t;
      }
    }
  }

	float actualTransparency = node->renderOpts.transparency * transparency;
	float actualScale = node->renderOpts.scale * scale;
	float new_x = parent_x + node->x * scale;
	float new_y = parent_y + node->y * scale;

  if (node->bitmap) {
    RenderOpt opts = node->renderOpts;
    opts.transparency = actualTransparency;
    opts.scale = actualScale;
    draw_bitmap(node->bitmap, new_x, new_y, &opts);
  } else if (node->drawFunc) {
    node->drawFunc(node, new_x, new_y);
	}

  for (int i = 0; i < node->num_children; i++) {
    TickType_t t = render_node(node->children[i], new_x, new_y, actualTransparency, actualScale);
    if (t < tickTime) {
      tickTime = t;
    }
  }

  return tickTime;
}

NodeSize set_text_node(Node *textNode, const char *text, uint8_t mask) {
  int len = strlen(text);
  float currentX = 0;

  if(len > textNode->num_children) {
    len = textNode->num_children;
  }

	NodeSize size = (NodeSize){0, 0};

  int i = 0;
  for (; i < len && text[i]; i++) {
    char c = text[i];

    Node *letterNode = textNode->children[i];

    if (c == ' ') {
      currentX += letterNode->renderOpts.scale * 10;
      continue;
    }

    bitmap_data *charBitmap = get_bitmap_for_name(&c, 1, mask);
    if (charBitmap == NULL) {
      ESP_LOGI(SGO_LOG_NOSEND, "Missing bitmap for letter '%c'", c);
      continue;
    }

    letterNode->x = currentX;
    //letterNode->y = 0;
    letterNode->bitmap = charBitmap;

    currentX += charBitmap->width * letterNode->renderOpts.scale;
		if (charBitmap->height * letterNode->renderOpts.scale > size.height) {
			size.height = charBitmap->height * letterNode->renderOpts.scale;
		}
  }
  size.width = currentX;
  for (; i < textNode->num_children; i++) {
    textNode->children[i]->bitmap = NULL;
  }
  for (i = 0; i < textNode->num_children; ++i) {
    if (textNode->children[i]->bitmap == NULL) {
      continue;
    }
    float offsetY = 0;
    if (textNode->renderOpts.offsetNumbers && text[i] >= '0' && text[i] <= '9') {
      offsetY = -5 * textNode->children[i]->renderOpts.scale;
    }
    textNode->children[i]->y = offsetY + size.height - textNode->children[i]->bitmap->height * textNode->children[i]->renderOpts.scale;
  }
	return size;
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
