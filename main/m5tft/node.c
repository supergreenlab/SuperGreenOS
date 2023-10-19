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
#include "bitmaps_definitions.h"
#include "../core/log/log.h"

// Animation function

void simple_animation(Node *node) {
	if (!node->funcParams) return;

	SimpleAnimationParams *params = (SimpleAnimationParams *)node->funcParams;

	// Calculate the distance to the destination
	float dx = params->dest_x - node->x;
	float dy = params->dest_y - node->y;

	// Normalize the distance based on speed while maintaining direction
	float distance = sqrtf(dx*dx + dy*dy);

	// If we're close enough to the destination, snap to it
	if (distance <= params->speed) {
		node->x = params->dest_x;
		node->y = params->dest_y;
		return;
	}

	// Calculate the step size while keeping the direction
	float step_x = params->speed * (dx / distance);
	float step_y = params->speed * (dy / distance);

	// Update the node's position
	node->x += step_x;
	node->y += step_y;
}

void sine_animation(Node *node) {
	SineAnimationParams *params = (SineAnimationParams *)node->funcParams;

	// Use elapsedTime to determine the phase of the sine wave
	float offset_x = params->magnitude_x * sinf(params->elapsedTime);
	float offset_y = params->magnitude_y * cosf(params->elapsedTime);

	node->x = params->center_x + offset_x;
	node->y = params->center_y + offset_y;

	params->elapsedTime += 0.1; // Adjust this value to change the speed of the oscillation
}

// Node management functions

// Create a new node. For simplicity, memory allocation is straightforward and lacks error checking.
Node* create_node(int x, int y, bitmap_data *bitmap, NodeFunction func, void *funcParams) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->x = x;
	node->y = y;
	node->bitmap = bitmap;
	node->funcParams = funcParams;
	node->func = func;
	node->children = NULL;
	node->num_children = 0;
	return node;
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

// Rendering function to draw the entire UI
void render_node(Node *node, int parent_x, int parent_y) {
	if (!node) return;

	// Call the node's custom function (if it exists)
	if (node->func) {
		node->func(node);
	}

	// Draw the node's bitmap (if it exists)
	if (node->bitmap) {
		draw_bitmap(node->bitmap, parent_x + node->x, parent_y + node->y);
	}

	// Render all child nodes
	for (int i = 0; i < node->num_children; i++) {
		render_node(node->children[i], parent_x + node->x, parent_y + node->y);
	}
}

// Text node

bitmap_data* get_bitmap_for_name(char* name, int len) {
	for (int i = 0; i < n_bitmaps; i++) {
		if (strncmp(bitmap_db[i]->name, name, len) == 0) {
			return bitmap_db[i];
		}
	}
	return NULL;  // Return NULL if character bitmap not found
}

void set_text_node(Node *textNode, const char *text) {
	int len = strlen(text);
	float currentX = 0;  // Starting x position

	// Limit the text length to the number of allocated child nodes
	if(len > textNode->num_children) {
		len = textNode->num_children;
	}

	int i = 0;
	for (; i < len; i++) {
		char c = text[i];

		bitmap_data *charBitmap = get_bitmap_for_name(&c, 1);
		if (charBitmap == NULL) {
			ESP_LOGI(SGO_LOG_NOSEND, "Skipping %c", c);
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

Node* create_text_node(int x, int y, int max_length, const char *text) {
	Node *root = create_node(x, y, NULL, NULL, NULL);

	for(int i = 0; i < max_length; i++) {
		Node *letterNode = create_node(0, 0, NULL, NULL, NULL);
		add_child(root, letterNode);
	}

	set_text_node(root, text);

	return root;
}

