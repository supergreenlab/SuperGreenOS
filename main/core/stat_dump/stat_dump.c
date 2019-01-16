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
    get_wifi_ssid(str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_SSID", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    get_wifi_password(str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_PASSWORD", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_time();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "TIME", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_n_restarts();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "N_RESTARTS", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_ota_timestamp();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "OTA_TIMESTAMP", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    get_ota_server_ip(str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_IP", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    get_ota_server_hostname(str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_HOSTNAME", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    get_ota_server_port(str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_PORT", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    get_ota_version_filename(str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_VERSION_FILENAME", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    get_ota_filename(str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_FILENAME", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    get_broker_url(str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "BROKER_URL", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_i2c_sda();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_SDA", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_i2c_scl();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_SCL", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_state();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "STATE", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    get_device_name(str, MAX_KVALUE_SIZE-1);
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "DEVICE_NAME", str);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_timer_type();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "TIMER_TYPE", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_timer_output();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "TIMER_OUTPUT", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_started_at();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "STARTED_AT", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_on_hour();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "ON_HOUR", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_on_min();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "ON_MIN", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_off_hour();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "OFF_HOUR", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_off_min();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "OFF_MIN", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_stretch();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "STRETCH", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_dim();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_DIM", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_blower();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BLOWER", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_blower_gpio();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BLOWER_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_sht1x_temp_c();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "SHT1X_TEMP_C", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_sht1x_temp_f();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "SHT1X_TEMP_F", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_sht1x_humi();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "SHT1X_HUMI", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_0_duty();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_DUTY", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_1_duty();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_DUTY", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_2_duty();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_DUTY", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_3_duty();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_DUTY", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_4_duty();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_DUTY", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_5_duty();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_DUTY", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_0_gpio();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_1_gpio();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_2_gpio();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_3_gpio();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_4_gpio();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_5_gpio();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_GPIO", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_0_x();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_X", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_1_x();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_X", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_2_x();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_X", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_3_x();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_X", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_4_x();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_X", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_5_x();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_X", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_0_y();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_Y", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_1_y();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_Y", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_2_y();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_Y", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_3_y();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_Y", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_4_y();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_Y", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_5_y();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_Y", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_0_z();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_Z", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_1_z();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_Z", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_2_z();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_Z", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_3_z();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_Z", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_4_z();
    ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_Z", value);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    value = get_led_5_z();
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
