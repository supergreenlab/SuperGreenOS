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

#include "metrics_page.h"
#include "math.h"
#include "freertos/task.h"
#include "../core/kv/kv.h"
#include "../core/log/log.h"

typedef struct {

  int current_temp;
  int current_humi;
  int current_co2;

  int last_temp;
  int last_humi;
  int last_co2;
  TickType_t last_fetch;

  Node *background_node;

  Node *temperature;
  Node *humidity;
  Node *co2;

  Node *phase;

  Node *loading;

} metrics_screen_params;

Node *plant_date_root;
metrics_screen_params *pdparams;
SineAnimationParams *pdSinParam;

Node *create_phase(const char *value, float elapsedTime);

void update_plant_date(char *value) {
  ESP_LOGI(SGO_LOG_NOSEND, "update_plant_date: %s", value);
  while( xSemaphoreTake( render_mutex, portMAX_DELAY ) != pdPASS );

  float elapsedTime = 0;
  if (pdparams->phase != NULL) {
    if (pdSinParam != NULL) {
      elapsedTime = pdSinParam->elapsedTime;
    }

    delete_node(pdparams->phase);
  }
  pdparams->phase = create_phase(value, elapsedTime);
  for (int i = 0; i < pdparams->phase->num_children; ++i) {
    pdparams->phase->children[i]->renderOpts.frameRef = (node_position *)plant_date_root->parent;
	}
  add_child(pdparams->background_node, pdparams->phase);
  xSemaphoreGive(render_mutex);
}

TickType_t metrics_screen_loop(Node *node, void *p) {
  metrics_screen_params *pdparams = (metrics_screen_params *)p;

  if (pdparams->loading && pdparams->last_temp != 0 && pdparams->last_humi != 0 && pdparams->last_co2 != 0) {
    delete_node(pdparams->loading);
    pdparams->loading = NULL;
  }

  if (!pdparams->loading && pdparams->background_node->renderOpts.transparency != 1) {
    pdparams->background_node->renderOpts.transparency += (1 - pdparams->background_node->renderOpts.transparency) / 5;
    if (pdparams->background_node->renderOpts.transparency > 0.9) {
      pdparams->background_node->renderOpts.transparency = 1;
    }
  }

  TickType_t returnTick = 2000 / portTICK_PERIOD_MS;
  if (pdparams->last_temp != pdparams->current_temp) {
    pdparams->current_temp += pdparams->last_temp > pdparams->current_temp ? 1 : -1;
    char value[6] = {0};
    sprintf(value, "%d°", pdparams->current_temp);
    set_text_node(pdparams->temperature, value, NORMAL_FONT_SIZE);
    returnTick = SHORT_TICK;
  }
  if (pdparams->last_humi != pdparams->current_humi) {
    pdparams->current_humi += pdparams->last_humi > pdparams->current_humi ? 1 : -1;
    char value[6] = {0};
    sprintf(value, "%d%%", pdparams->current_humi);
    set_text_node(pdparams->humidity, value, NORMAL_FONT_SIZE);
    returnTick = SHORT_TICK;
  }
  if (pdparams->last_co2 != pdparams->current_co2) {
    bool dir = pdparams->last_co2 > pdparams->current_co2;
    pdparams->current_co2 += pdparams->last_co2 > pdparams->current_co2 ? 20 : -20;
    if (dir != (pdparams->last_co2 > pdparams->current_co2)) {
      pdparams->current_co2 = pdparams->last_co2;
    }
    char value[6] = {0};
    sprintf(value, "%d", pdparams->current_co2);
    NodeSize size = set_text_node(pdparams->co2, value, NORMAL_FONT_SIZE);
    pdparams->co2->x = 160 - size.width - 10;
    returnTick = SHORT_TICK;
  }

  TickType_t tick = xTaskGetTickCount();
  if ((tick - pdparams->last_fetch) * portTICK_PERIOD_MS > 2000) {

    pdparams->last_temp = get_box_0_temp();
    pdparams->last_humi = get_box_0_humi();
    pdparams->last_co2 = get_box_0_co2();

    pdparams->last_fetch = tick;
  }

  return returnTick;
}

Node *create_temperature() {
  char value[4] = {0};
  sprintf(value, "%d°", get_box_0_temp());
  Node *node = create_text_node(5, 5, 3, value, (color_t){ 59, 179, 11 }, NORMAL_FONT_SIZE);
  return node;
}

Node *create_humidity() {
  char value[4] = {0};
  sprintf(value, "%d%%", get_box_0_humi());
  Node *node = create_text_node(5, 45, 3, value, (color_t){ 51, 203, 212 }, NORMAL_FONT_SIZE);
  return node;
}

Node *create_co2() {
  char value[5] = {0};
  sprintf(value, "%d", get_box_0_co2());
  Node *node = create_text_node(80, 24, 7, value, (color_t){ 217, 69, 184 }, NORMAL_FONT_SIZE);
  NodeSize size = set_text_node(node, value, NORMAL_FONT_SIZE);
  node->x = 160 - size.width - 10;
  return node;
}

Node *create_co2_label() {
  Node *node = create_text_node(100, 60, 7, "ppm", (color_t){ 217, 69, 184 }, NORMAL_FONT_SIZE);
  for (int i = 0; i < node->num_children; ++i) {
    node->children[i]->renderOpts.scale = 0.8;
  }
  NodeSize size = set_text_node(node, "ppm", NORMAL_FONT_SIZE);
  node->x = 160 - size.width - 10;
  node->y = 80 - size.height - 5;
  return node;
}

Node *create_phase(const char *value, float elapsedTime) {
  Node *node = create_text_node(80, 5, 25, value, (color_t){ 255, 255, 255 }, SMALL_FONT_SIZE);
  //node->renderOpts.offsetNumbers = true;
  for (int i = 0; i < node->num_children; ++i) {
    //node->children[i]->renderOpts.scale = 0.6;
    node->children[i]->renderOpts.limit = true;
    node->children[i]->renderOpts.frame = (frame_limits){72, 0, 150, 25};
  }
  NodeSize size = set_text_node(node, value, SMALL_FONT_SIZE);

  pdSinParam = (SineAnimationParams*)malloc(sizeof(SineAnimationParams));
  pdSinParam->center_x = 120 - size.width/2 - 8;
  pdSinParam->center_y = node->y;
  pdSinParam->magnitude_x = (size.width - 80)/2 + 5;
  pdSinParam->magnitude_y = 0;
  pdSinParam->elapsedTime = M_PI * 2.5;
  pdSinParam->speed=0.01;
  pdSinParam->elapsedTime = elapsedTime;

  node->funcParams[0] = pdSinParam;
  node->funcs[0] = sine_animation;

  return node;
}

Node *create_loading() {
  SineTransparencyAnimationParams *params1trans = (SineTransparencyAnimationParams*)malloc(sizeof(SineTransparencyAnimationParams));
  params1trans->min_transparency = 0.4;
  params1trans->max_transparency = 0.9;
  params1trans->elapsed_time = 0;
  params1trans->speed = 0.25;

  Node *node = create_text_node(80, 5, 25, "Loading", (color_t){ 255, 255, 255 }, NORMAL_FONT_SIZE);

  for (int i = 0; i < node->num_children; ++i) {
    node->children[i]->renderOpts.scale = 0.8;
  }

  NodeSize size = set_text_node(node, "Loading", NORMAL_FONT_SIZE);
  node->x = 80 - size.width/2;
  node->y = 40 - size.height/2;
  node->funcParams[0] = params1trans;
  node->funcs[0] = sine_transparency_animation;

  Node *sub_node = create_node(0, 0, NULL, NULL, NULL);
  add_child(sub_node, node);

  return sub_node;
}

void init_metrics_page(Node *root) {
  plant_date_root = root;
  pdparams = (metrics_screen_params *)malloc(sizeof(metrics_screen_params));
  memset(pdparams, 0, sizeof(metrics_screen_params));

  pdparams->background_node = create_node(0, 0, NULL, NULL, NULL);
  add_child(root, pdparams->background_node);
  pdparams->background_node->renderOpts.transparency = 0.2;

  pdparams->temperature = create_temperature();
  add_child(pdparams->background_node, pdparams->temperature);

  pdparams->humidity = create_humidity();
  add_child(pdparams->background_node, pdparams->humidity);

  pdparams->co2 = create_co2();
  add_child(pdparams->background_node, pdparams->co2);

  Node *label = create_co2_label();
  add_child(pdparams->background_node, label);

  pdparams->loading = create_loading();
  add_child(root, pdparams->loading);

  pdparams->phase = create_phase("Not linked yet", 0);
  for (int i = 0; i < pdparams->phase->num_children; ++i) {
    pdparams->phase->children[i]->renderOpts.frameRef = (node_position *)plant_date_root->parent;
	}
  add_child(pdparams->background_node, pdparams->phase);

  root->funcParams[0] = pdparams;
  root->funcs[0] = metrics_screen_loop;
}
