/*
 * Copyright (C) 2019  SuperGreenLab <towelie@supergreenlab.com>
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

#include "mqtt.h"
#include "mqtt_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

#include "../log/log.h"
#include "../kv/kv.h"
#include "../wifi/wifi.h"

static esp_mqtt_client_handle_t client;

static QueueHandle_t cmd;
static QueueHandle_t log_queue;

#define MAX_LOG_QUEUE_ITEM_SIZE 128
#define MAX_LOG_QUEUE_ITEMS 50
static uint8_t buf_out[MAX_LOG_QUEUE_ITEM_SIZE] = {0};

static int CMD_MQTT_DISCONNECTED = 0;
static int CMD_MQTT_CONNECTED = 1;
static int CMD_MQTT_FORCE_FLUSH = 2;

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
  switch (event->event_id) {
    case MQTT_EVENT_BEFORE_CONNECT:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_BEFORE_CONNECT");
      break;
    case MQTT_EVENT_CONNECTED:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_CONNECTED");
      xQueueSend(cmd, &CMD_MQTT_CONNECTED, 0);
      break;
    case MQTT_EVENT_DISCONNECTED:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_DISCONNECTED");
      xQueueSend(cmd, &CMD_MQTT_DISCONNECTED, 0);
      break;
    case MQTT_EVENT_SUBSCRIBED:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
      break;
    case MQTT_EVENT_UNSUBSCRIBED:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
      break;
    case MQTT_EVENT_PUBLISHED:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
      break;
    case MQTT_EVENT_DATA:
      ESP_LOGI(SGO_LOG_EVENT, "MQTT_EVENT_DATA");
      break;
    case MQTT_EVENT_ERROR:
      ESP_LOGI(SGO_LOG_EVENT, "MQTT_EVENT_ERROR");
      break;
  }
  return ESP_OK;
}

static void mqtt_task(void *param) {
  int c;
  bool connected = false;
  bool first_connect = true;

  uint64_t _chipmacid;
  esp_efuse_mac_get_default((uint8_t*) (&_chipmacid));

  char log_channel[MAX_KVALUE_SIZE] = {0};
  get_broker_channel(log_channel, sizeof(log_channel) - 1);
  if (strlen(log_channel) == 0) {
    sprintf(log_channel, "%llx.log", _chipmacid);
    set_broker_channel(log_channel);
  }
  ESP_LOGI(SGO_LOG_EVENT, "@MQTT Log channel: %s", log_channel);

  char client_id[MAX_KVALUE_SIZE] = {0};
  get_broker_clientid(client_id, sizeof(client_id) - 1);
  if (strlen(client_id) == 0) {
    sprintf(client_id, "%llx", _chipmacid);
    set_broker_clientid(client_id);
  } else if (strlen(client_id) == 1 && client_id[0] == '-') {
    client_id[0] = 0;
  }
  ESP_LOGI(SGO_LOG_EVENT, "@MQTT Log clientid: %s", client_id);

  char broker_url[MAX_KVALUE_SIZE] = {0};
  getstr(BROKER_URL, broker_url, sizeof(broker_url)-1);
  esp_mqtt_client_config_t mqtt_cfg = {
    .uri = broker_url,
    .event_handle = mqtt_event_handler,
    .client_id = client_id,
    // .user_context = (void *)your_context
  };

  client = esp_mqtt_client_init(&mqtt_cfg);
  esp_mqtt_client_start(client);

  while(true) {
    if (xQueueReceive(cmd, &c, 10000 / portTICK_PERIOD_MS)) {
      if (c == CMD_MQTT_CONNECTED) {
        connected = true;
        if (first_connect) {
          first_connect = false;
          ESP_LOGI(SGO_LOG_EVENT, "@MQTT First connect");
        }
      } else if (c == CMD_MQTT_DISCONNECTED) {
        connected = false;
      }
    }
    if (connected) {
      memset(buf_out, 0, MAX_LOG_QUEUE_ITEM_SIZE);
      while (xQueueReceive(log_queue, buf_out, 0)) {
        esp_mqtt_client_publish(client, log_channel, (char *)buf_out, 0, 0, 0);
        memset(buf_out, 0, MAX_LOG_QUEUE_ITEM_SIZE);
      }
    }
  }
}

static int mqtt_logging_vprintf(const char *str, va_list l) {
  int totalsize = vsnprintf(NULL, 0, str, l);
  if (totalsize >= MAX_LOG_QUEUE_ITEM_SIZE - 1) {
    return vprintf(str, l);
  }
  
  va_list nl;
  va_copy(nl, l);
  va_arg(nl, int);
  const char *tag = va_arg(nl, const char *);
  if (strcmp(tag, SGO_LOG_MSG) != 0 &&
      strcmp(tag, SGO_LOG_EVENT) != 0 &&
      strcmp(tag, SGO_LOG_METRIC) != 0) {
    return vprintf(str, l);
  }

  uint8_t buf_in[MAX_LOG_QUEUE_ITEM_SIZE] = {0};
  if (uxQueueMessagesWaiting(log_queue) >= MAX_LOG_QUEUE_ITEMS) {
    xQueueReceive(log_queue, buf_in, 0);
  }
  memset(buf_in, 0, MAX_LOG_QUEUE_ITEM_SIZE);
  int len = vsprintf((char*)buf_in, str, l);
  buf_in[len] = 0;
  xQueueSend(log_queue, buf_in, 0);
  if (cmd && uxQueueMessagesWaiting(log_queue) > 5) {
    xQueueSend(cmd, &CMD_MQTT_FORCE_FLUSH, 0);
  }
  return vprintf(str, l);
}

void mqtt_intercept_log() {
  log_queue = xQueueCreate(MAX_LOG_QUEUE_ITEMS, MAX_LOG_QUEUE_ITEM_SIZE);
  if (log_queue == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@MQTT Unable to create mqtt log queue");
  }

  esp_log_set_vprintf(mqtt_logging_vprintf);
}

void init_mqtt() {
  ESP_LOGI(SGO_LOG_EVENT, "@MQTT Intializing MQTT task");

  //esp_log_level_set("MQTT_CLIENT", ESP_LOG_NONE);

  cmd = xQueueCreate(10, sizeof(int));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@MQTT Unable to create mqtt queue");
  }

  xTaskCreate(mqtt_task, "MQTT", 4096, NULL, 10, NULL);
}
