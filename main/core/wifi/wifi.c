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

typedef const unsigned int wifi_cmd;
static wifi_cmd CMD_SSID_CHANGED = 1;
static wifi_cmd CMD_PASS_CHANGED = 2;
static wifi_cmd CMD_STA_CONNECTED = 3;
static wifi_cmd CMD_STA_DISCONNECTED = 4;
static wifi_cmd CMD_STA_CONNECTION_FAILED = 5;
static wifi_cmd CMD_AP_STACONNECTED = 6;
static wifi_cmd CMD_AP_STADISCONNECTED = 7;
static wifi_cmd CMD_AP_START = 8;

static QueueHandle_t cmd;

static EventGroupHandle_t wifi_event_group;

static const int CONNECTED_BIT = BIT0;

static void start_sta(void);
static void start_ap(void);
static esp_err_t event_handler(void *ctx, system_event_t *event);
static void wifi_task(void *param);
static bool is_valid();
static void init_mdns_service();

void init_wifi() {
  init_mdns_service();

  wifi_event_group = xEventGroupCreate();
  ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );

  tcpip_adapter_init();
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
  ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );

  cmd = xQueueCreate(5, sizeof(wifi_cmd));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@WIFI Failed to create queue");
  }

  xTaskCreate(wifi_task, "WIFI", 4096, NULL, tskIDLE_PRIORITY, NULL);

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

static void init_mdns_service()
{
	esp_err_t err = mdns_init();
	if (err) {
		ESP_LOGE(SGO_LOG_EVENT, "@WIFI MDNS Init failed: %d\n", err);
		return;
	}

  char domain[MAX_KVALUE_SIZE] = {0};
  get_mdns_domain(domain, MAX_KVALUE_SIZE-1);

	mdns_hostname_set(domain);
  mdns_service_add(NULL, "_http", "_tcp", 80, NULL, 0);

  ESP_LOGI(SGO_LOG_EVENT, "@WIFI Started MDNS advertising as %s.local", domain);
}

static void start_ap() {
  char ssid[MAX_KVALUE_SIZE] = {0};
  get_wifi_ap_ssid(ssid, MAX_KVALUE_SIZE-1);
  char password[MAX_KVALUE_SIZE] = {0};
  get_wifi_ap_password(password, MAX_KVALUE_SIZE-1);
  ESP_LOGI(SGO_LOG_EVENT, "@WIFI AP mode started SSID=%s", ssid);

  esp_wifi_stop();

  wifi_config_t wifi_config = {0};
  wifi_config.ap.authmode = WIFI_AUTH_WPA2_PSK;
  wifi_config.ap.max_connection = 1;
  memcpy(wifi_config.ap.ssid, ssid, sizeof(wifi_config.ap.ssid));
  memcpy(wifi_config.ap.password, password, sizeof(wifi_config.ap.password));

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
  
  get_wifi_ssid((char *)wifi_config.sta.ssid, sizeof(wifi_config.sta.ssid) - 1);
  get_wifi_password((char *)wifi_config.sta.password, sizeof(wifi_config.sta.password) - 1);

  wifi_config.sta.bssid_set = false;
  ESP_LOGI(SGO_LOG_EVENT, "@WIFI Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
  ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
  ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );

  ESP_ERROR_CHECK( esp_wifi_start() );
}

static void set_ip(tcpip_adapter_if_t interface) {
  tcpip_adapter_ip_info_t info;
  esp_err_t err = tcpip_adapter_get_ip_info(interface, &info);
  if (err != ESP_OK) {
    ESP_LOGE(SGO_LOG_EVENT, "@WIFI tcpip_adapter_get_ip_info failed");
    return;
  }

  char ip[20] = {0};
  sprintf(ip, "%d.%d.%d.%d", ((uint8_t*)&(info.ip.addr))[0], ((uint8_t*)&(info.ip.addr))[1], ((uint8_t*)&(info.ip.addr))[2], ((uint8_t*)&(info.ip.addr))[3]);
  set_wifi_ip(ip);
}

static esp_err_t event_handler(void *ctx, system_event_t *event) {
  switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI SYSTEM_EVENT_STA_START");
      esp_wifi_connect();
      set_wifi_status(CONNECTING);
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI SYSTEM_EVENT_STA_GOT_IP");
      xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
      xQueueSend(cmd, &CMD_STA_CONNECTED, 0);
      set_wifi_status(CONNECTED);
      set_ip(TCPIP_ADAPTER_IF_STA);
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI SYSTEM_EVENT_STA_DISCONNECTED = %d", event->event_info.disconnected.reason);
      bool failed = event->event_info.disconnected.reason == WIFI_REASON_NO_AP_FOUND || event->event_info.disconnected.reason == WIFI_REASON_AUTH_FAIL;
      if (failed) {
        xQueueSend(cmd, &CMD_STA_CONNECTION_FAILED, 0);
        set_wifi_status(FAILED);
      } else {
        xQueueSend(cmd, &CMD_STA_DISCONNECTED, 0);
        set_wifi_status(DISCONNECTED);
      }
      xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
      break;
    case SYSTEM_EVENT_AP_START:
      xQueueSend(cmd, &CMD_AP_START, 0);
      set_wifi_status(AP);
      set_ip(TCPIP_ADAPTER_IF_AP);
      break;
    case SYSTEM_EVENT_AP_STACONNECTED:
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI SYSTEM_EVENT_AP_STACONNECTED");
      xQueueSend(cmd, &CMD_AP_STACONNECTED, 0);
      break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI SYSTEM_EVENT_AP_STADISCONNECTED");
      xQueueSend(cmd, &CMD_AP_STADISCONNECTED, 0);
      break;
    default:
      break;
  }
  mdns_handle_system_event(ctx, event);
  return ESP_OK;
}

static bool try_sta_connection() {
  wifi_mode_t wm = {0};
  //wifi_sta_list_t sl = {0}; // commented all esp_wifi_ap_get_sta_list stuffs as it seems it doesn't refresh properly
  if (esp_wifi_get_mode(&wm) == ESP_OK && wm != WIFI_MODE_STA) {
    //if (esp_wifi_ap_get_sta_list(&sl) == ESP_OK) {
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI Trying STA while no-one's watching");
      start_sta();
      return true;
    /*} else {
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI unable to esp_wifi_ap_get_sta_list");
    }*/
  } else {
    ESP_LOGI(SGO_LOG_EVENT, "@WIFI unable to get_mode");
  }
  return false;
}

static void wifi_task(void *param) {
  unsigned int c;
  unsigned int n_connection_failed = 0;
  unsigned int n_connected_sta = 0;
  unsigned int counter = 1;
  bool was_valid = is_valid();

  for (;;) {
    if (xQueueReceive(cmd, &c, 20000 / portTICK_PERIOD_MS)) {
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI xQueueReceive %d", c);

      // Wifi STA conf change
      if ((c == CMD_SSID_CHANGED || c == CMD_PASS_CHANGED)) {
        ESP_LOGI(SGO_LOG_EVENT, "@WIFI CMD_SSID_CHANGED | CMD_PASS_CHANGED");
        bool _is_valid = is_valid();
        if (_is_valid != was_valid) {
          was_valid = _is_valid;
          if (_is_valid) {
            start_sta();
          }/* else {
            start_ap();
          }*/
        }
      } else if (c == CMD_AP_START) {
        ESP_LOGI(SGO_LOG_EVENT, "@WIFI CMD_AP_START");
        n_connected_sta = 0;
      } else if (c == CMD_STA_CONNECTED) {
        ESP_LOGI(SGO_LOG_EVENT, "@WIFI CMD_STA_CONNECTED");
      } else if (c == CMD_AP_STACONNECTED) {
        ESP_LOGI(SGO_LOG_EVENT, "@WIFI CMD_AP_STACONNECTED");
        ++n_connected_sta;
      } else if (c == CMD_AP_STADISCONNECTED) {
        ESP_LOGI(SGO_LOG_EVENT, "@WIFI CMD_AP_STADISCONNECTED");
        --n_connected_sta;

      // STA connection stopped
      } else if (c == CMD_STA_CONNECTION_FAILED || c == CMD_STA_DISCONNECTED) {
        ESP_LOGI(SGO_LOG_EVENT, "@WIFI CMD_STA_CONNECTION_FAILED || CMD_STA_DISCONNECTED");
        if (n_connection_failed < 5 && is_valid()) {
          ++n_connection_failed;
          ESP_LOGI(SGO_LOG_EVENT, "@WIFI Retry: %d/5", n_connection_failed);
          esp_wifi_connect();
        } else if (!is_valid() || (n_connection_failed >= 5 && is_valid())) {
          ESP_LOGI(SGO_LOG_EVENT, "@WIFI Too many retries, start AP mode");
          n_connection_failed = 0;
          start_ap();
        }
      }
    } else {
      // if AP mode and noone's watching, try STA mode.
      ++counter;
      if (!(counter % 6) && !n_connected_sta && is_valid() && try_sta_connection()) {
        continue;
      }
      //ESP_LOGI(SGO_LOG_EVENT, "@WIFI Refresh MDNS service");
    }
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
  char ssid[MAX_KVALUE_SIZE] = {0};
  get_wifi_ssid(ssid, MAX_KVALUE_SIZE-1);
  char password[MAX_KVALUE_SIZE] = {0};
  get_wifi_password(password, MAX_KVALUE_SIZE-1);

  return strlen(ssid) != 0 && strlen(password) != 0;
}
