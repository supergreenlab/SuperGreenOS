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
  int counter = 0;
  wait_connected();
  vTaskDelay(30 * 1000 / portTICK_PERIOD_MS);
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
    if ((counter % 20) == 0 || is_wifi_status_changed()) {
      reset_wifi_status_changed();
    }
    if ((counter % 20) == 0 || is_wifi_ssid_changed()) {
      get_wifi_ssid(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_SSID", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_wifi_ssid_changed();
    }
    if ((counter % 20) == 0 || is_wifi_password_changed()) {
      get_wifi_password(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_PASSWORD", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_wifi_password_changed();
    }
    if ((counter % 20) == 0 || is_wifi_ap_ssid_changed()) {
      get_wifi_ap_ssid(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_AP_SSID", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_wifi_ap_ssid_changed();
    }
    if ((counter % 20) == 0 || is_wifi_ap_password_changed()) {
      get_wifi_ap_password(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_AP_PASSWORD", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_wifi_ap_password_changed();
    }
    if ((counter % 20) == 0 || is_mdns_domain_changed()) {
      get_mdns_domain(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "MDNS_DOMAIN", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_mdns_domain_changed();
    }
    if ((counter % 20) == 0 || is_wifi_ip_changed()) {
      get_wifi_ip(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "WIFI_IP", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_wifi_ip_changed();
    }
    if ((counter % 20) == 0 || is_time_changed()) {
      value = get_time();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "TIME", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_time_changed();
    }
    if ((counter % 20) == 0 || is_n_restarts_changed()) {
      value = get_n_restarts();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "N_RESTARTS", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_n_restarts_changed();
    }
    if ((counter % 20) == 0 || is_ota_timestamp_changed()) {
      value = get_ota_timestamp();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "OTA_TIMESTAMP", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_ota_timestamp_changed();
    }
    if ((counter % 20) == 0 || is_ota_server_ip_changed()) {
      get_ota_server_ip(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_IP", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_ota_server_ip_changed();
    }
    if ((counter % 20) == 0 || is_ota_server_hostname_changed()) {
      get_ota_server_hostname(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_HOSTNAME", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_ota_server_hostname_changed();
    }
    if ((counter % 20) == 0 || is_ota_server_port_changed()) {
      get_ota_server_port(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_SERVER_PORT", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_ota_server_port_changed();
    }
    if ((counter % 20) == 0 || is_ota_basedir_changed()) {
      get_ota_basedir(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "OTA_BASEDIR", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_ota_basedir_changed();
    }
    if ((counter % 20) == 0 || is_broker_url_changed()) {
      get_broker_url(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "BROKER_URL", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_broker_url_changed();
    }
    if ((counter % 20) == 0 || is_broker_channel_changed()) {
      get_broker_channel(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "BROKER_CHANNEL", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_broker_channel_changed();
    }
    if ((counter % 20) == 0 || is_broker_clientid_changed()) {
      get_broker_clientid(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "BROKER_CLIENTID", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_broker_clientid_changed();
    }
    if ((counter % 20) == 0 || is_i2c_0_sda_changed()) {
      value = get_i2c_0_sda();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_0_SDA", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_i2c_0_sda_changed();
    }
    if ((counter % 20) == 0 || is_i2c_0_scl_changed()) {
      value = get_i2c_0_scl();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_0_SCL", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_i2c_0_scl_changed();
    }
    if ((counter % 20) == 0 || is_i2c_0_enabled_changed()) {
      value = get_i2c_0_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_0_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_i2c_0_enabled_changed();
    }
    if ((counter % 20) == 0 || is_i2c_1_sda_changed()) {
      value = get_i2c_1_sda();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_1_SDA", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_i2c_1_sda_changed();
    }
    if ((counter % 20) == 0 || is_i2c_1_scl_changed()) {
      value = get_i2c_1_scl();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_1_SCL", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_i2c_1_scl_changed();
    }
    if ((counter % 20) == 0 || is_i2c_1_enabled_changed()) {
      value = get_i2c_1_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "I2C_1_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_i2c_1_enabled_changed();
    }
    if ((counter % 20) == 0 || is_reboot_changed()) {
      reset_reboot_changed();
    }
    if ((counter % 20) == 0 || is_state_changed()) {
      value = get_state();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "STATE", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_state_changed();
    }
    if ((counter % 20) == 0 || is_device_name_changed()) {
      get_device_name(str, MAX_KVALUE_SIZE-1);
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%s", "DEVICE_NAME", str);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_device_name_changed();
    }
    if ((counter % 20) == 0 || is_box_0_enabled_changed()) {
      value = get_box_0_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_enabled_changed();
    }
    if ((counter % 20) == 0 || is_box_0_timer_type_changed()) {
      value = get_box_0_timer_type();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_TIMER_TYPE", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_timer_type_changed();
    }
    if ((counter % 20) == 0 || is_box_0_timer_output_changed()) {
      value = get_box_0_timer_output();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_TIMER_OUTPUT", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_timer_output_changed();
    }
    if ((counter % 20) == 0 || is_box_0_started_at_changed()) {
      value = get_box_0_started_at();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_STARTED_AT", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_started_at_changed();
    }
    if ((counter % 20) == 0 || is_box_0_on_hour_changed()) {
      value = get_box_0_on_hour();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_ON_HOUR", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_on_hour_changed();
    }
    if ((counter % 20) == 0 || is_box_0_on_min_changed()) {
      value = get_box_0_on_min();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_ON_MIN", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_on_min_changed();
    }
    if ((counter % 20) == 0 || is_box_0_off_hour_changed()) {
      value = get_box_0_off_hour();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_OFF_HOUR", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_off_hour_changed();
    }
    if ((counter % 20) == 0 || is_box_0_off_min_changed()) {
      value = get_box_0_off_min();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_OFF_MIN", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_off_min_changed();
    }
    if ((counter % 20) == 0 || is_box_0_stretch_changed()) {
      value = get_box_0_stretch();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_STRETCH", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_stretch_changed();
    }
    if ((counter % 20) == 0 || is_box_0_led_dim_changed()) {
      value = get_box_0_led_dim();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_LED_DIM", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_led_dim_changed();
    }
    if ((counter % 20) == 0 || is_box_0_blower_changed()) {
      value = get_box_0_blower();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_BLOWER", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_blower_changed();
    }
    if ((counter % 20) == 0 || is_box_0_blower_mode_changed()) {
      value = get_box_0_blower_mode();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_BLOWER_MODE", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_blower_mode_changed();
    }
    if ((counter % 20) == 0 || is_box_0_blower_gpio_changed()) {
      value = get_box_0_blower_gpio();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_BLOWER_GPIO", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_blower_gpio_changed();
    }
    if ((counter % 20) == 0 || is_box_0_blower_enabled_changed()) {
      value = get_box_0_blower_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_BLOWER_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_blower_enabled_changed();
    }
    if ((counter % 20) == 0 || is_box_0_sht1x_temp_c_changed()) {
      value = get_box_0_sht1x_temp_c();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_SHT1X_TEMP_C", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_sht1x_temp_c_changed();
    }
    if ((counter % 20) == 0 || is_box_0_sht1x_temp_f_changed()) {
      value = get_box_0_sht1x_temp_f();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_SHT1X_TEMP_F", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_sht1x_temp_f_changed();
    }
    if ((counter % 20) == 0 || is_box_0_sht1x_humi_changed()) {
      value = get_box_0_sht1x_humi();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_SHT1X_HUMI", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_sht1x_humi_changed();
    }
    if ((counter % 20) == 0 || is_box_0_sht21_temp_c_changed()) {
      value = get_box_0_sht21_temp_c();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_SHT21_TEMP_C", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_sht21_temp_c_changed();
    }
    if ((counter % 20) == 0 || is_box_0_sht21_temp_f_changed()) {
      value = get_box_0_sht21_temp_f();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_SHT21_TEMP_F", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_sht21_temp_f_changed();
    }
    if ((counter % 20) == 0 || is_box_0_sht21_humi_changed()) {
      value = get_box_0_sht21_humi();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_SHT21_HUMI", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_sht21_humi_changed();
    }
    if ((counter % 20) == 0 || is_box_0_arduino_co2_changed()) {
      value = get_box_0_arduino_co2();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_ARDUINO_CO2", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_arduino_co2_changed();
    }
    if ((counter % 20) == 0 || is_box_0_dust_gpy2y10_changed()) {
      value = get_box_0_dust_gpy2y10();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_0_DUST_GPY2Y10", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_0_dust_gpy2y10_changed();
    }
    if ((counter % 20) == 0 || is_box_0_led_info_changed()) {
      reset_box_0_led_info_changed();
    }
    if ((counter % 20) == 0 || is_box_1_enabled_changed()) {
      value = get_box_1_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_enabled_changed();
    }
    if ((counter % 20) == 0 || is_box_1_timer_type_changed()) {
      value = get_box_1_timer_type();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_TIMER_TYPE", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_timer_type_changed();
    }
    if ((counter % 20) == 0 || is_box_1_timer_output_changed()) {
      value = get_box_1_timer_output();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_TIMER_OUTPUT", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_timer_output_changed();
    }
    if ((counter % 20) == 0 || is_box_1_started_at_changed()) {
      value = get_box_1_started_at();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_STARTED_AT", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_started_at_changed();
    }
    if ((counter % 20) == 0 || is_box_1_on_hour_changed()) {
      value = get_box_1_on_hour();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_ON_HOUR", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_on_hour_changed();
    }
    if ((counter % 20) == 0 || is_box_1_on_min_changed()) {
      value = get_box_1_on_min();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_ON_MIN", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_on_min_changed();
    }
    if ((counter % 20) == 0 || is_box_1_off_hour_changed()) {
      value = get_box_1_off_hour();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_OFF_HOUR", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_off_hour_changed();
    }
    if ((counter % 20) == 0 || is_box_1_off_min_changed()) {
      value = get_box_1_off_min();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_OFF_MIN", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_off_min_changed();
    }
    if ((counter % 20) == 0 || is_box_1_stretch_changed()) {
      value = get_box_1_stretch();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_STRETCH", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_stretch_changed();
    }
    if ((counter % 20) == 0 || is_box_1_led_dim_changed()) {
      value = get_box_1_led_dim();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_LED_DIM", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_led_dim_changed();
    }
    if ((counter % 20) == 0 || is_box_1_blower_changed()) {
      value = get_box_1_blower();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_BLOWER", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_blower_changed();
    }
    if ((counter % 20) == 0 || is_box_1_blower_mode_changed()) {
      value = get_box_1_blower_mode();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_BLOWER_MODE", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_blower_mode_changed();
    }
    if ((counter % 20) == 0 || is_box_1_blower_gpio_changed()) {
      value = get_box_1_blower_gpio();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_BLOWER_GPIO", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_blower_gpio_changed();
    }
    if ((counter % 20) == 0 || is_box_1_blower_enabled_changed()) {
      value = get_box_1_blower_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_BLOWER_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_blower_enabled_changed();
    }
    if ((counter % 20) == 0 || is_box_1_sht1x_temp_c_changed()) {
      value = get_box_1_sht1x_temp_c();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_SHT1X_TEMP_C", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_sht1x_temp_c_changed();
    }
    if ((counter % 20) == 0 || is_box_1_sht1x_temp_f_changed()) {
      value = get_box_1_sht1x_temp_f();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_SHT1X_TEMP_F", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_sht1x_temp_f_changed();
    }
    if ((counter % 20) == 0 || is_box_1_sht1x_humi_changed()) {
      value = get_box_1_sht1x_humi();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_SHT1X_HUMI", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_sht1x_humi_changed();
    }
    if ((counter % 20) == 0 || is_box_1_sht21_temp_c_changed()) {
      value = get_box_1_sht21_temp_c();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_SHT21_TEMP_C", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_sht21_temp_c_changed();
    }
    if ((counter % 20) == 0 || is_box_1_sht21_temp_f_changed()) {
      value = get_box_1_sht21_temp_f();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_SHT21_TEMP_F", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_sht21_temp_f_changed();
    }
    if ((counter % 20) == 0 || is_box_1_sht21_humi_changed()) {
      value = get_box_1_sht21_humi();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_SHT21_HUMI", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_sht21_humi_changed();
    }
    if ((counter % 20) == 0 || is_box_1_arduino_co2_changed()) {
      value = get_box_1_arduino_co2();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_ARDUINO_CO2", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_arduino_co2_changed();
    }
    if ((counter % 20) == 0 || is_box_1_dust_gpy2y10_changed()) {
      value = get_box_1_dust_gpy2y10();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_1_DUST_GPY2Y10", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_1_dust_gpy2y10_changed();
    }
    if ((counter % 20) == 0 || is_box_1_led_info_changed()) {
      reset_box_1_led_info_changed();
    }
    if ((counter % 20) == 0 || is_box_2_enabled_changed()) {
      value = get_box_2_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_enabled_changed();
    }
    if ((counter % 20) == 0 || is_box_2_timer_type_changed()) {
      value = get_box_2_timer_type();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_TIMER_TYPE", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_timer_type_changed();
    }
    if ((counter % 20) == 0 || is_box_2_timer_output_changed()) {
      value = get_box_2_timer_output();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_TIMER_OUTPUT", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_timer_output_changed();
    }
    if ((counter % 20) == 0 || is_box_2_started_at_changed()) {
      value = get_box_2_started_at();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_STARTED_AT", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_started_at_changed();
    }
    if ((counter % 20) == 0 || is_box_2_on_hour_changed()) {
      value = get_box_2_on_hour();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_ON_HOUR", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_on_hour_changed();
    }
    if ((counter % 20) == 0 || is_box_2_on_min_changed()) {
      value = get_box_2_on_min();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_ON_MIN", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_on_min_changed();
    }
    if ((counter % 20) == 0 || is_box_2_off_hour_changed()) {
      value = get_box_2_off_hour();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_OFF_HOUR", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_off_hour_changed();
    }
    if ((counter % 20) == 0 || is_box_2_off_min_changed()) {
      value = get_box_2_off_min();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_OFF_MIN", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_off_min_changed();
    }
    if ((counter % 20) == 0 || is_box_2_stretch_changed()) {
      value = get_box_2_stretch();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_STRETCH", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_stretch_changed();
    }
    if ((counter % 20) == 0 || is_box_2_led_dim_changed()) {
      value = get_box_2_led_dim();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_LED_DIM", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_led_dim_changed();
    }
    if ((counter % 20) == 0 || is_box_2_blower_changed()) {
      value = get_box_2_blower();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_BLOWER", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_blower_changed();
    }
    if ((counter % 20) == 0 || is_box_2_blower_mode_changed()) {
      value = get_box_2_blower_mode();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_BLOWER_MODE", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_blower_mode_changed();
    }
    if ((counter % 20) == 0 || is_box_2_blower_gpio_changed()) {
      value = get_box_2_blower_gpio();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_BLOWER_GPIO", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_blower_gpio_changed();
    }
    if ((counter % 20) == 0 || is_box_2_blower_enabled_changed()) {
      value = get_box_2_blower_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_BLOWER_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_blower_enabled_changed();
    }
    if ((counter % 20) == 0 || is_box_2_sht1x_temp_c_changed()) {
      value = get_box_2_sht1x_temp_c();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_SHT1X_TEMP_C", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_sht1x_temp_c_changed();
    }
    if ((counter % 20) == 0 || is_box_2_sht1x_temp_f_changed()) {
      value = get_box_2_sht1x_temp_f();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_SHT1X_TEMP_F", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_sht1x_temp_f_changed();
    }
    if ((counter % 20) == 0 || is_box_2_sht1x_humi_changed()) {
      value = get_box_2_sht1x_humi();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_SHT1X_HUMI", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_sht1x_humi_changed();
    }
    if ((counter % 20) == 0 || is_box_2_sht21_temp_c_changed()) {
      value = get_box_2_sht21_temp_c();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_SHT21_TEMP_C", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_sht21_temp_c_changed();
    }
    if ((counter % 20) == 0 || is_box_2_sht21_temp_f_changed()) {
      value = get_box_2_sht21_temp_f();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_SHT21_TEMP_F", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_sht21_temp_f_changed();
    }
    if ((counter % 20) == 0 || is_box_2_sht21_humi_changed()) {
      value = get_box_2_sht21_humi();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_SHT21_HUMI", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_sht21_humi_changed();
    }
    if ((counter % 20) == 0 || is_box_2_arduino_co2_changed()) {
      value = get_box_2_arduino_co2();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_ARDUINO_CO2", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_arduino_co2_changed();
    }
    if ((counter % 20) == 0 || is_box_2_dust_gpy2y10_changed()) {
      value = get_box_2_dust_gpy2y10();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "BOX_2_DUST_GPY2Y10", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_box_2_dust_gpy2y10_changed();
    }
    if ((counter % 20) == 0 || is_box_2_led_info_changed()) {
      reset_box_2_led_info_changed();
    }
    if ((counter % 20) == 0 || is_led_0_duty_changed()) {
      value = get_led_0_duty();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_DUTY", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_0_duty_changed();
    }
    if ((counter % 20) == 0 || is_led_1_duty_changed()) {
      value = get_led_1_duty();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_DUTY", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_1_duty_changed();
    }
    if ((counter % 20) == 0 || is_led_2_duty_changed()) {
      value = get_led_2_duty();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_DUTY", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_2_duty_changed();
    }
    if ((counter % 20) == 0 || is_led_3_duty_changed()) {
      value = get_led_3_duty();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_DUTY", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_3_duty_changed();
    }
    if ((counter % 20) == 0 || is_led_4_duty_changed()) {
      value = get_led_4_duty();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_DUTY", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_4_duty_changed();
    }
    if ((counter % 20) == 0 || is_led_5_duty_changed()) {
      value = get_led_5_duty();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_DUTY", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_5_duty_changed();
    }
    if ((counter % 20) == 0 || is_led_0_gpio_changed()) {
      value = get_led_0_gpio();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_GPIO", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_0_gpio_changed();
    }
    if ((counter % 20) == 0 || is_led_1_gpio_changed()) {
      value = get_led_1_gpio();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_GPIO", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_1_gpio_changed();
    }
    if ((counter % 20) == 0 || is_led_2_gpio_changed()) {
      value = get_led_2_gpio();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_GPIO", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_2_gpio_changed();
    }
    if ((counter % 20) == 0 || is_led_3_gpio_changed()) {
      value = get_led_3_gpio();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_GPIO", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_3_gpio_changed();
    }
    if ((counter % 20) == 0 || is_led_4_gpio_changed()) {
      value = get_led_4_gpio();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_GPIO", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_4_gpio_changed();
    }
    if ((counter % 20) == 0 || is_led_5_gpio_changed()) {
      value = get_led_5_gpio();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_GPIO", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_5_gpio_changed();
    }
    if ((counter % 20) == 0 || is_led_0_x_changed()) {
      value = get_led_0_x();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_X", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_0_x_changed();
    }
    if ((counter % 20) == 0 || is_led_1_x_changed()) {
      value = get_led_1_x();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_X", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_1_x_changed();
    }
    if ((counter % 20) == 0 || is_led_2_x_changed()) {
      value = get_led_2_x();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_X", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_2_x_changed();
    }
    if ((counter % 20) == 0 || is_led_3_x_changed()) {
      value = get_led_3_x();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_X", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_3_x_changed();
    }
    if ((counter % 20) == 0 || is_led_4_x_changed()) {
      value = get_led_4_x();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_X", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_4_x_changed();
    }
    if ((counter % 20) == 0 || is_led_5_x_changed()) {
      value = get_led_5_x();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_X", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_5_x_changed();
    }
    if ((counter % 20) == 0 || is_led_0_y_changed()) {
      value = get_led_0_y();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_Y", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_0_y_changed();
    }
    if ((counter % 20) == 0 || is_led_1_y_changed()) {
      value = get_led_1_y();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_Y", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_1_y_changed();
    }
    if ((counter % 20) == 0 || is_led_2_y_changed()) {
      value = get_led_2_y();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_Y", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_2_y_changed();
    }
    if ((counter % 20) == 0 || is_led_3_y_changed()) {
      value = get_led_3_y();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_Y", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_3_y_changed();
    }
    if ((counter % 20) == 0 || is_led_4_y_changed()) {
      value = get_led_4_y();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_Y", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_4_y_changed();
    }
    if ((counter % 20) == 0 || is_led_5_y_changed()) {
      value = get_led_5_y();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_Y", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_5_y_changed();
    }
    if ((counter % 20) == 0 || is_led_0_z_changed()) {
      value = get_led_0_z();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_Z", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_0_z_changed();
    }
    if ((counter % 20) == 0 || is_led_1_z_changed()) {
      value = get_led_1_z();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_Z", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_1_z_changed();
    }
    if ((counter % 20) == 0 || is_led_2_z_changed()) {
      value = get_led_2_z();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_Z", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_2_z_changed();
    }
    if ((counter % 20) == 0 || is_led_3_z_changed()) {
      value = get_led_3_z();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_Z", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_3_z_changed();
    }
    if ((counter % 20) == 0 || is_led_4_z_changed()) {
      value = get_led_4_z();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_Z", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_4_z_changed();
    }
    if ((counter % 20) == 0 || is_led_5_z_changed()) {
      value = get_led_5_z();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_Z", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_5_z_changed();
    }
    if ((counter % 20) == 0 || is_led_0_enabled_changed()) {
      value = get_led_0_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_0_enabled_changed();
    }
    if ((counter % 20) == 0 || is_led_1_enabled_changed()) {
      value = get_led_1_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_1_enabled_changed();
    }
    if ((counter % 20) == 0 || is_led_2_enabled_changed()) {
      value = get_led_2_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_2_enabled_changed();
    }
    if ((counter % 20) == 0 || is_led_3_enabled_changed()) {
      value = get_led_3_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_3_enabled_changed();
    }
    if ((counter % 20) == 0 || is_led_4_enabled_changed()) {
      value = get_led_4_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_4_enabled_changed();
    }
    if ((counter % 20) == 0 || is_led_5_enabled_changed()) {
      value = get_led_5_enabled();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_ENABLED", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_5_enabled_changed();
    }
    if ((counter % 20) == 0 || is_led_0_box_changed()) {
      value = get_led_0_box();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_BOX", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_0_box_changed();
    }
    if ((counter % 20) == 0 || is_led_1_box_changed()) {
      value = get_led_1_box();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_BOX", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_1_box_changed();
    }
    if ((counter % 20) == 0 || is_led_2_box_changed()) {
      value = get_led_2_box();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_BOX", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_2_box_changed();
    }
    if ((counter % 20) == 0 || is_led_3_box_changed()) {
      value = get_led_3_box();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_BOX", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_3_box_changed();
    }
    if ((counter % 20) == 0 || is_led_4_box_changed()) {
      value = get_led_4_box();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_BOX", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_4_box_changed();
    }
    if ((counter % 20) == 0 || is_led_5_box_changed()) {
      value = get_led_5_box();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_BOX", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_5_box_changed();
    }
    if ((counter % 20) == 0 || is_led_0_dim_changed()) {
      value = get_led_0_dim();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_0_DIM", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_0_dim_changed();
    }
    if ((counter % 20) == 0 || is_led_1_dim_changed()) {
      value = get_led_1_dim();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_1_DIM", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_1_dim_changed();
    }
    if ((counter % 20) == 0 || is_led_2_dim_changed()) {
      value = get_led_2_dim();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_2_DIM", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_2_dim_changed();
    }
    if ((counter % 20) == 0 || is_led_3_dim_changed()) {
      value = get_led_3_dim();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_3_DIM", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_3_dim_changed();
    }
    if ((counter % 20) == 0 || is_led_4_dim_changed()) {
      value = get_led_4_dim();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_4_DIM", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_4_dim_changed();
    }
    if ((counter % 20) == 0 || is_led_5_dim_changed()) {
      value = get_led_5_dim();
      ESP_LOGI(SGO_LOG_METRIC, "@KV %s=%d", "LED_5_DIM", value);
      vTaskDelay(50 / portTICK_PERIOD_MS);
      reset_led_5_dim_changed();
    }

    vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
    ++counter;

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
