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


#include "app.h"
#include "screensaver.h"
#include "button.h"
#include "m5tft.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "../core/log/log.h"

typedef struct {

  uint8_t current_screen;
  uint8_t n_screens;

} screen_app_params;

screen_app_params *params; 
SemaphoreHandle_t params_mutex;

TickType_t screen_app_loop(Node *node, void *p) {
  fill_screen((color_t){ 43, 63, 81 });

  if (node->renderOpts.transparency < 1) {
    node->renderOpts.transparency += 0.1;
  }

  float screenX = params->current_screen * -160;
  if ((int)node->x != (int)screenX) {
    node->x += (screenX - node->x) / 5;
    if (abs(screenX - node->x) < 3) {
      node->x = screenX;
    }
    return SHORT_TICK;
  }
  return LONG_TICK;
}

void buttonEvent(void *handler_arg, esp_event_base_t base, int32_t id, void *event_data) {
  while( xSemaphoreTake( render_mutex, portMAX_DELAY ) != pdPASS );
  if ((base == button_a.esp_event_base) && (id == BUTTON_PRESSED_EVENT)) {
    ESP_LOGI(SGO_LOG_NOSEND, "Button a");
    params->current_screen++;
    params->current_screen %= params->n_screens;
    force_frame();
  }

  if ((base == button_b.esp_event_base) && (id == BUTTON_PRESSED_EVENT)) {
    ESP_LOGI(SGO_LOG_NOSEND, "Button b");
    force_frame();
  }
  xSemaphoreGive(render_mutex);
}


static init_function app_init_functions[MAX_NSCREENS] = { 0 };

void add_screen_init(init_function fn) {
  for (int i = 0; i < MAX_NSCREENS; ++i) {
    if (!app_init_functions[i]) {
      app_init_functions[i] = fn;
      return;
    }
  }
}

void init_screen_app(Node *root) {
  esp_event_handler_register_with(event_loop, BUTTON_A_EVENT_BASE, BUTTON_PRESSED_EVENT, buttonEvent, NULL);
  esp_event_handler_register_with(event_loop, BUTTON_B_EVENT_BASE, BUTTON_PRESSED_EVENT, buttonEvent, NULL);

  params_mutex = xSemaphoreCreateMutex();
  params = (screen_app_params *)malloc(sizeof(screen_app_params));
  memset(params, 0, sizeof(screen_app_params));

  for (int i = 0; i < MAX_NSCREENS; ++i) {
    if (!app_init_functions[i]) {
      break;
    }
    Node *screen = create_node(i * DEFAULT_TFT_DISPLAY_HEIGHT, 0, NULL, NULL, NULL);
    add_child(root, screen);
    app_init_functions[i](screen);
    params->n_screens++;
  }

  root->renderOpts.transparency = 0;

  root->funcParams[0] = params;
  root->funcs[0] = screen_app_loop;
}
