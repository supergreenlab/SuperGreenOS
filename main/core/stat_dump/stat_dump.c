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

#include "../include_modules.h"

#define MAX_KEY_SIZE 21

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

    /*
     * [GENERATED]
     */

    int value;
    char str[MAX_KVALUE_SIZE] = {0};
    getstr(WIFI_SSID, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_SSID", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(WIFI_PASSWORD, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_PASSWORD", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(TIME);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "TIME", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(N_RESTARTS);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "N_RESTARTS", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(OTA_TIMESTAMP);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "OTA_TIMESTAMP", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(OTA_SERVER_IP, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_IP", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(OTA_SERVER_HOSTNAME, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_HOSTNAME", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(OTA_SERVER_PORT, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_PORT", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(OTA_VERSION_FILENAME, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_VERSION_FILENAME", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(OTA_FILENAME, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_FILENAME", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(OTA, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(BROKER_URL, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "BROKER_URL", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(I2C_SDA);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_SDA", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(I2C_SCL);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_SCL", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(STATE);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "STATE", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    getstr(DEVICE_NAME, str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "DEVICE_NAME", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(TIMER_TYPE);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "TIMER_TYPE", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(TIMER_OUTPUT);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "TIMER_OUTPUT", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(STARTED_AT);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "STARTED_AT", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(ON_HOUR);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "ON_HOUR", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(ON_MIN);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "ON_MIN", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(OFF_HOUR);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "OFF_HOUR", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(OFF_MIN);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "OFF_MIN", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(STRETCH);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "STRETCH", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_DIM);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_DIM", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(BLOWER);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BLOWER", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(BLOWER_GPIO);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BLOWER_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(SHT1X_TEMP_C);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "SHT1X_TEMP_C", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(SHT1X_TEMP_F);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "SHT1X_TEMP_F", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(SHT1X_HUMI);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "SHT1X_HUMI", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_0_DUTY);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_DUTY", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_1_DUTY);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_DUTY", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_2_DUTY);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_DUTY", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_3_DUTY);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_DUTY", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_4_DUTY);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_DUTY", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_5_DUTY);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_DUTY", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_0_GPIO);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_1_GPIO);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_2_GPIO);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_3_GPIO);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_4_GPIO);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_5_GPIO);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_0_X);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_X", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_1_X);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_X", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_2_X);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_X", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_3_X);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_X", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_4_X);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_X", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_5_X);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_X", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_0_Y);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_Y", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_1_Y);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_Y", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_2_Y);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_Y", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_3_Y);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_Y", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_4_Y);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_Y", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_5_Y);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_Y", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_0_Z);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_Z", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_1_Z);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_Z", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_2_Z);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_Z", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_3_Z);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_Z", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_4_Z);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_Z", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = geti(LED_5_Z);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_Z", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);

    vTaskDelay(60000 / portTICK_PERIOD_MS);

    /*
     * [/GENERATED]
     */
  }
}

void init_stat_dump_queues() {
}

void init_stat_dump() {
  xTaskCreate(stat_dump_task, "STAT_DUMP", 3072, NULL, 10, NULL);
}
