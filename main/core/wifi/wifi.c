/*
 * Copyright (C) 2018  SuperGreenLab <towelie@supergreenlab.com>
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

#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_attr.h"
#include "esp_sleep.h"
#include "nvs_flash.h"
#include "mdns.h"

#include "wifi.h"
#include "../log/log.h"
#include "../ble/ble.h"
#include "../ble/ble_db.h"
#include "../kv/kv.h"
#include "../kv/kv_ble.h"

#define AP_SSID "🤖🍁"
#define AP_PASS "multipass"

static const unsigned int CMD_SSID_CHANGED = 1;
static const unsigned int CMD_PASS_CHANGED = 2;

static QueueHandle_t cmd;

static EventGroupHandle_t wifi_event_group;

static const int CONNECTED_BIT = BIT0;

static void start_sta(void);
static void start_ap(void);
static esp_err_t event_handler(void *ctx, system_event_t *event);
static void wifi_task(void *param);
static bool is_valid();

void start_mdns_service()
{
  mdns_free();
	esp_err_t err = mdns_init();
	if (err) {
		ESP_LOGE(SGO_LOG_EVENT, "@WIFI MDNS Init failed: %d\n", err);
		return;
	}

	mdns_hostname_set("supergreendriver");
  mdns_service_add(NULL, "_http", "_tcp", 80, NULL, 0);
}

void init_wifi() {
  wifi_event_group = xEventGroupCreate();
  ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );

  tcpip_adapter_init();
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
  ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );

  cmd = xQueueCreate(5, sizeof(unsigned int));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@WIFI Failed to create queue");
  }

  xTaskCreate(wifi_task, "WIFI", 2048, NULL, tskIDLE_PRIORITY, NULL);

  if (is_valid()) {
    start_sta();
  } else {
    start_ap();
  }
}

void wait_connected() {
  xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
      false, true, portMAX_DELAY);
}

static void start_ap() {
  ESP_LOGI(SGO_LOG_EVENT, "@WIFI AP mode started SSID=%s", AP_SSID);
  esp_wifi_stop();

  set_wifi_status(AP);

  wifi_config_t wifi_config = {0};
  wifi_config.ap.authmode = WIFI_AUTH_WPA2_PSK;
  wifi_config.ap.max_connection = 1;
  memcpy(wifi_config.ap.ssid, AP_SSID, sizeof(wifi_config.ap.ssid));
  memcpy(wifi_config.ap.password, AP_PASS, sizeof(wifi_config.ap.password));

  ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_AP) );
  ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config) );

  xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
  ESP_ERROR_CHECK( esp_wifi_start() );
}

static void start_sta() {
  esp_wifi_stop();
  xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);

  set_wifi_status(CONNECTING);

  wifi_config_t wifi_config = {0};
  
  getstr(WIFI_SSID, (char *)wifi_config.sta.ssid, sizeof(wifi_config.sta.ssid) - 1);
  getstr(WIFI_PASSWORD, (char *)wifi_config.sta.password, sizeof(wifi_config.sta.password) - 1);

  wifi_config.sta.bssid_set = false;
  ESP_LOGI(SGO_LOG_EVENT, "@WIFI Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
  ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
  ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );

  ESP_ERROR_CHECK( esp_wifi_start() );
}

static esp_err_t event_handler(void *ctx, system_event_t *event) {
  static int n_connection_failed = 0;
  switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI SYSTEM_EVENT_STA_START");
      esp_wifi_connect();
      set_wifi_status(CONNECTING);
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI SYSTEM_EVENT_STA_GOT_IP");
      xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
      start_mdns_service();
      set_wifi_status(CONNECTED);
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI SYSTEM_EVENT_STA_DISCONNECTED = %d", event->event_info.disconnected.reason);
      bool failed = event->event_info.disconnected.reason == WIFI_REASON_NO_AP_FOUND || event->event_info.disconnected.reason == WIFI_REASON_AUTH_FAIL;
      if (failed) {
        set_wifi_status(FAILED);
      } else {
        set_wifi_status(DISCONNECTED);
      }

      if (n_connection_failed < 5 && is_valid()) {
        ++n_connection_failed;
        esp_wifi_connect();
      } else if (!is_valid() || (n_connection_failed >= 5 && is_valid())) {
        n_connection_failed = 0;
        start_ap();
      }
      xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
      break;
    case SYSTEM_EVENT_AP_STACONNECTED:
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI SYSTEM_EVENT_AP_STACONNECTED");
      start_mdns_service();
      break;
    default:
      break;
  }
  mdns_handle_system_event(ctx, event);
  return ESP_OK;
}

static void wifi_task(void *param) {
  unsigned int c;
  for (;;) {
    if(xQueueReceive(cmd, &c, 10000 / portTICK_PERIOD_MS)) {
      if ((c == CMD_SSID_CHANGED || CMD_PASS_CHANGED)) {
        ESP_LOGI(SGO_LOG_EVENT, "@WIFI CMD_SSID_CHANGED | CMD_PASS_CHANGED");
        if (is_valid()) {
          start_sta();
        } else {
          start_ap();
        }
      }
    }
    start_mdns_service();
  }
}

// BLE Callbacks

const char *on_set_wifi_ssid(const char *ssid) {
  set_wifi_password("");
  xQueueSend(cmd, &CMD_SSID_CHANGED, 0);
  return ssid;
}

const char *on_set_wifi_password(const char *pass) {
  xQueueSend(cmd, &CMD_PASS_CHANGED, 0);
  return pass;
}

// utils

static bool is_valid() {
  uint8_t ssid[32] = {0}; 
  uint8_t pass[64] = {0};

  getstr(WIFI_SSID, (char *)ssid, sizeof(ssid) - 1);
  getstr(WIFI_PASSWORD, (char *)pass, sizeof(pass) - 1);

  return strlen((char *)ssid) != 0 && strlen((char *)pass) != 0;
}
