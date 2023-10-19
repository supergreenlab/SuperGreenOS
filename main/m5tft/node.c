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

#include "node.h"
#include "math.h"

void simple_animation(Node *node) {
	if (!node->funcParams) return;

	AnimationParams *params = (AnimationParams *)node->funcParams;

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

// Add a child node to a parent node
void add_child(Node *parent, Node *child) {
	parent->num_children++;
	parent->children = (Node**)realloc(parent->children, parent->num_children * sizeof(Node *));
	parent->children[parent->num_children - 1] = child;
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
