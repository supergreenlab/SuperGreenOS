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

typedef struct Node Node;

typedef void (*NodeFunction)(Node *node);

struct Node {
	float x; // position relative to its parent
	float y;
	bitmap_data *bitmap;
	void *funcParams;
	NodeFunction func; // optional animation or custom logic function
	Node **children; // pointer to an array of child nodes
	int num_children; // count of child nodes
};

typedef struct {
    float dest_x;
    float dest_y;
    float speed; // pixels per frame; how fast the node should move towards its destination
} AnimationParams;

Node* create_node(int x, int y, bitmap_data *bitmap, NodeFunction func, void *funcParams);
void add_child(Node *parent, Node *child);
void render_node(Node *node, int parent_x, int parent_y);

void simple_animation(Node *node);

void set_text_node(Node *textNode, const char *text);
Node* create_text_node(int x, int y, int max_length, const char *text);

#endif
