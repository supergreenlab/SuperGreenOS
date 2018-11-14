/*
 * =====================================================================================
 *
 *       Filename:  stat_dump.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/30/2018 11:27:15 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string.h>

#include "stat_dump.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "../log/log.h"
#include "../kv/kv.h"
#include "../wifi/wifi.h"

#define MAX_KEY_SIZE 21
static char kbuf[MAX_KEY_SIZE] = {0};
static char strbuf[MAX_KVALUE_SIZE] = {0};

static QueueHandle_t kvs_queue;
static QueueHandle_t kvi_queue;

void add_kvs_dump(const char *k) {
  xQueueSend(kvs_queue, k, 0); 
}

void add_kvi_dump(const char *k) {
  xQueueSend(kvi_queue, k, 0); 
}

static void stat_dump_task(void *param) {
  wait_connected();
  vTaskDelay(60000 / portTICK_PERIOD_MS);
  int n_tasks = uxTaskGetNumberOfTasks();
  uint32_t ulTotalRunTime, ulStatsAsPercentage;
  TaskStatus_t *statuses = malloc(n_tasks * sizeof(TaskStatus_t));
  while(1) {
    int nn_tasks = uxTaskGetNumberOfTasks();
    if (n_tasks != nn_tasks) {
      free(statuses);
      n_tasks = nn_tasks;
      statuses = malloc(n_tasks * sizeof(TaskStatus_t));
    }
    uxTaskGetSystemState(statuses, n_tasks, &ulTotalRunTime);
    ulTotalRunTime /= 100UL;
    if (ulTotalRunTime == 0) continue;

    for (int i = 0; i < n_tasks; ++i) {
      ulStatsAsPercentage = statuses[i].ulRunTimeCounter / ulTotalRunTime;
      ESP_LOGI(SGO_LOG_METRIC, "@%s stack_left=%d, task_counter=%d, task_percent=%d", statuses[i].pcTaskName, statuses[i].usStackHighWaterMark, statuses[i].ulRunTimeCounter, ulStatsAsPercentage);
    }
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    for (int i = 0; i < uxQueueMessagesWaiting(kvs_queue); ++i) {
      memset(kbuf, 0, MAX_KEY_SIZE);
      memset(strbuf, 0, MAX_KVALUE_SIZE);
      xQueueReceive(kvs_queue, kbuf, 0);
      getstr(kbuf, strbuf, MAX_KVALUE_SIZE);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", kbuf, strbuf);
      xQueueSend(kvs_queue, kbuf, 0);
      vTaskDelay(50 / portTICK_PERIOD_MS);
    }

    vTaskDelay(5000 / portTICK_PERIOD_MS);

    for (int i = 0; i < uxQueueMessagesWaiting(kvi_queue); ++i) {
      memset(kbuf, 0, MAX_KEY_SIZE);
      xQueueReceive(kvi_queue, kbuf, 0);
      int v = geti(kbuf);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", kbuf, v);
      xQueueSend(kvi_queue, kbuf, 0);
      vTaskDelay(50 / portTICK_PERIOD_MS);
    }

    vTaskDelay(60000 / portTICK_PERIOD_MS);
  }
}

void init_stat_dump_queues() {
  kvs_queue = xQueueCreate(50, MAX_KEY_SIZE);
  if (kvs_queue == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@STAT_DUMP Unable to create kvs queue");
  }

  kvi_queue = xQueueCreate(50, MAX_KEY_SIZE);
  if (kvi_queue == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@STAT_DUMP Unable to create kvi queue");
  }
}

void init_stat_dump() {
  xTaskCreate(stat_dump_task, "STAT_DUMP", 3072, NULL, 10, NULL);
}
