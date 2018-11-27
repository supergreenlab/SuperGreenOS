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
#include "../kv/kv.h"
#include "../kv/kv_ble.h"
#include "../conf/ble_db.h"

/*  UUID string: 372fda1c-6d67-cbda-f083-ae31b50e06ee */
const uint8_t WIFI_STATUS_UUID[ESP_UUID_LEN_128] = {0xee,0x06,0x0e,0xb5,0x31,0xae,0x83,0xf0,0xda,0xcb,0x67,0x6d,0x1c,0xda,0x2f,0x37};
/*  UUID string: 6ca36981-9c55-74a5-5415-e16bc1c3fe17 */
const uint8_t WIFI_SSID_UUID[ESP_UUID_LEN_128] = {0x17,0xfe,0xc3,0xc1,0x6b,0xe1,0x15,0x54,0xa5,0x74,0x55,0x9c,0x81,0x69,0xa3,0x6c};
/*  UUID string: f7e40b10-6cfe-a6f1-fea0-cc6e82535db9 */
const uint8_t WIFI_PASS_UUID[ESP_UUID_LEN_128] = {0xb9,0x5d,0x53,0x82,0x6e,0xcc,0xa0,0xfe,0xf1,0xa6,0xfe,0x6c,0x10,0x0b,0xe4,0xf7};

#define SSID "WSSID"
#define PASS "WPASS"

#define DEFAULT_SSID ""
#define DEFAULT_PASS ""

static const unsigned int DISCONNECTED = 1;
static const unsigned int CONNECTING = 2;
static const unsigned int CONNECTED = 3;
static const unsigned int FAILED = 4;

static const unsigned int CMD_SSID_CHANGED = 1;
static const unsigned int CMD_PASS_CHANGED = 2;

static QueueHandle_t cmd;

static EventGroupHandle_t wifi_event_group;

static const int CONNECTED_BIT = BIT0;

static void start_sta(void);
static esp_err_t event_handler(void *ctx, system_event_t *event);
static void wifi_task(void *param);
static bool is_valid();

void start_mdns_service()
{
	esp_err_t err = mdns_init();
	if (err) {
		ESP_LOGE(SGO_LOG_EVENT, "@WIFI MDNS Init failed: %d\n", err);
		return;
	}


  mdns_service_add(NULL, "_http", "_tcp", 80, NULL, 0);

	mdns_instance_name_set("Super Green Driver");
	mdns_hostname_set("supergreendriver");
}

void init_wifi() {
  defaultstr(SSID, DEFAULT_SSID);
  defaultstr(PASS, DEFAULT_PASS);

	start_mdns_service();

  set_attr_value(IDX_VALUE(WIFI_STATUS), (const uint8_t *)&DISCONNECTED, sizeof(const unsigned int));

  sync_ble_str(SSID, IDX_VALUE(WIFI_SSID));

  wifi_event_group = xEventGroupCreate();
  ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );

  tcpip_adapter_init();
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK( esp_wifi_init(&cfg) );

  cmd = xQueueCreate(5, sizeof(unsigned int));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@WIFI Failed to create queue");
  }

  xTaskCreate(wifi_task, "WIFI", 2048, NULL, tskIDLE_PRIORITY, NULL);

  if (is_valid()) {
    start_sta();
  }
}

void wait_connected() {
  xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
      false, true, portMAX_DELAY);
}

static void start_sta() {
  set_attr_value_and_notify(IDX_VALUE(WIFI_STATUS), (const uint8_t *)&CONNECTING, sizeof(const unsigned int));

  wifi_config_t wifi_config = {0};
  
  getstr(SSID, (char *)wifi_config.sta.ssid, sizeof(wifi_config.sta.ssid) - 1);
  getstr(PASS, (char *)wifi_config.sta.password, sizeof(wifi_config.sta.password) - 1);

  wifi_config.sta.bssid_set = false;
  ESP_LOGI(SGO_LOG_EVENT, "@WIFI Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
  ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
  ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );

  EventBits_t wbits = xEventGroupGetBits(wifi_event_group);
  if (wbits & CONNECTED_BIT) { 
    xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
    ESP_ERROR_CHECK(esp_wifi_disconnect());
  } else {
    if (esp_wifi_connect() == ESP_ERR_WIFI_NOT_STARTED) {
      ESP_ERROR_CHECK( esp_wifi_start() );
    }
  }
}

static esp_err_t event_handler(void *ctx, system_event_t *event) {
  switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI SYSTEM_EVENT_STA_START");
      esp_wifi_connect();
      set_attr_value_and_notify(IDX_VALUE(WIFI_STATUS), (const uint8_t *)&CONNECTING, sizeof(const unsigned int));
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI SYSTEM_EVENT_STA_GOT_IP");
      xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
      set_attr_value_and_notify(IDX_VALUE(WIFI_STATUS), (const uint8_t *)&CONNECTED, sizeof(const unsigned int));
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      ESP_LOGI(SGO_LOG_EVENT, "@WIFI SYSTEM_EVENT_STA_DISCONNECTED = %d", event->event_info.disconnected.reason);
      bool failed = event->event_info.disconnected.reason == WIFI_REASON_NO_AP_FOUND || event->event_info.disconnected.reason == WIFI_REASON_AUTH_FAIL;
      if (failed) {
        set_attr_value_and_notify(IDX_VALUE(WIFI_STATUS), (const uint8_t *)&FAILED, sizeof(const unsigned int));
      } else {
        set_attr_value_and_notify(IDX_VALUE(WIFI_STATUS), (const uint8_t *)&DISCONNECTED, sizeof(const unsigned int));
      }

      if (is_valid()) {
        esp_wifi_connect();
      }
      xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
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
    if(xQueueReceive(cmd, &c, (TickType_t) portMAX_DELAY)) {
      if ((c == CMD_SSID_CHANGED || CMD_PASS_CHANGED) && is_valid()) {
        ESP_LOGI(SGO_LOG_EVENT, "@WIFI CMD_SSID_CHANGED | CMD_PASS_CHANGED");
        start_sta();
      }
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// BLE Callbacks

void on_set_wifi_ssid(const char *ssid) {
  setstr(SSID, ssid);
  setstr(PASS, "");
  xQueueSend(cmd, &CMD_SSID_CHANGED, 0);
}

void on_set_wifi_password(const char *pass) {
  setstr(PASS, pass);
  set_attr_value(IDX_VALUE(WIFI_PASS), (const uint8_t *)"", 0);
  xQueueSend(cmd, &CMD_PASS_CHANGED, 0);
}

// utils

static bool is_valid() {
  uint8_t ssid[32] = {0}; 
  uint8_t pass[64] = {0};

  getstr(SSID, (char *)ssid, sizeof(ssid) - 1);
  getstr(PASS, (char *)pass, sizeof(pass) - 1);

  return strlen((char *)ssid) != 0 && strlen((char *)pass) != 0;
}
