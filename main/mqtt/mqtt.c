/*
 * =====================================================================================
 *
 *       Filename:  mqtt.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/25/2018 09:21:59 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "mqtt.h"
#include "mqtt_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

#include "../log/log.h"
#include "../wifi/wifi.h"

static esp_mqtt_client_handle_t client;

static QueueHandle_t cmd;
static QueueHandle_t log_queue;

#define MAX_LOG_QUEUE_SIZE 256
#define MAX_LOG_QUEUE_ITEMS 50
static uint8_t buf[MAX_LOG_QUEUE_SIZE * 2] = {0};

static int CMD_MQTT_DISCONNECTED = 0;
static int CMD_MQTT_CONNECTED = 1;
static int CMD_MQTT_FORCE_FLUSH = 2;

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
  // your_context_t *context = event->context;
  switch (event->event_id) {
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

  uint64_t _chipmacid;
  char log_channel[64] = {0};
  esp_efuse_mac_get_default((uint8_t*) (&_chipmacid));
  sprintf(log_channel, "%llx.log", _chipmacid);
  ESP_LOGI(SGO_LOG_EVENT, "@MQTT Log channel: %s", log_channel);

  wait_connected();

  esp_mqtt_client_config_t mqtt_cfg = {
    .uri = CONFIG_BROKER_URL,
    .event_handle = mqtt_event_handler,
    // .user_context = (void *)your_context
  };

  client = esp_mqtt_client_init(&mqtt_cfg);
  esp_mqtt_client_start(client);

  while(true) {
    if (xQueueReceive(cmd, &c, 10000 / portTICK_PERIOD_MS)) {
      if (c == CMD_MQTT_CONNECTED) {
        connected = true;
      } else if (c == CMD_MQTT_DISCONNECTED) {
        connected = false;
      }
    }
    if (connected) {
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT loop");
      memset(buf, 0, MAX_LOG_QUEUE_SIZE * 2);
      while (xQueueReceive(log_queue, buf, MAX_LOG_QUEUE_SIZE - 1)) {
        esp_mqtt_client_publish(client, log_channel, (char *)buf, 0, 0, 0);
        memset(buf, 0, MAX_LOG_QUEUE_SIZE * 2);
      }
    }
  }
}

static int mqtt_logging_vprintf(const char *str, va_list l) {
  int totalsize = vsnprintf(NULL, 0, str, l);
  if (totalsize >= MAX_LOG_QUEUE_SIZE * 2 - 1) {
    return vprintf(str, l);
  }
  memset(buf, 0, MAX_LOG_QUEUE_SIZE * 2);
  int len = vsprintf((char*)buf, str, l) - 1;
  buf[len] = 0;
  xQueueSend(log_queue, buf, len < MAX_LOG_QUEUE_SIZE - 1 ? len : MAX_LOG_QUEUE_SIZE - 1);
  if (cmd && uxQueueMessagesWaiting(log_queue) > 5) {
    xQueueSend(cmd, &CMD_MQTT_FORCE_FLUSH, 0);
  }
  return vprintf(str, l);
}

void mqtt_intercept_log() {
  log_queue = xQueueCreate(MAX_LOG_QUEUE_ITEMS, MAX_LOG_QUEUE_SIZE);
  if (log_queue == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@MQTT Unable to create mqtt log queue");
  }

  esp_log_set_vprintf(mqtt_logging_vprintf);
}

void init_mqtt() {
  ESP_LOGI(SGO_LOG_EVENT, "@MQTT Intializing MQTT task");

  cmd = xQueueCreate(10, sizeof(int));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@MQTT Unable to create mqtt queue");
  }

  xTaskCreate(mqtt_task, "MQTT task", 2048, NULL, 10, NULL);
}
