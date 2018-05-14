/*
 * =====================================================================================
 *
 *       Filename:  wifi.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/16/2018 19:24:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
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

#include "wifi.h"
#include "../core/kv.h"
#include "../core/kv_ble.h"
#include "../ble_db.h"

/*  UUID string: 372fda1c-6d67-cbda-f083-ae31b50e06ee */
const uint8_t WIFI_STATUS_UUID[ESP_UUID_LEN_128] = {0xee,0x06,0x0e,0xb5,0x31,0xae,0x83,0xf0,0xda,0xcb,0x67,0x6d,0x1c,0xda,0x2f,0x37};
/*  UUID string: 6ca36981-9c55-74a5-5415-e16bc1c3fe17 */
const uint8_t WIFI_SSID_UUID[ESP_UUID_LEN_128] = {0x17,0xfe,0xc3,0xc1,0x6b,0xe1,0x15,0x54,0xa5,0x74,0x55,0x9c,0x81,0x69,0xa3,0x6c};
/*  UUID string: f7e40b10-6cfe-a6f1-fea0-cc6e82535db9 */
const uint8_t WIFI_PASS_UUID[ESP_UUID_LEN_128] = {0xb9,0x5d,0x53,0x82,0x6e,0xcc,0xa0,0xfe,0xf1,0xa6,0xfe,0x6c,0x10,0x0b,0xe4,0xf7};

#define SSID "WSSID"
#define PASS "WPASS"

#define DEFAULT_SSID "FastAndSeriousSoft"
#define DEFAULT_PASS "42FastAndSeriousSoft42"

/* FreeRTOS event group to signal when we are connected & ready to make a request */
static EventGroupHandle_t wifi_event_group;

/* The event group allows multiple bits for each event,
   but we only care about one event - are we connected
   to the AP with an IP? */
const int CONNECTED_BIT = BIT0;

static void setup(void);
static esp_err_t event_handler(void *ctx, system_event_t *event);

void init_wifi() {
  defaultstr(SSID, DEFAULT_SSID);
  defaultstr(PASS, "");

  sync_ble_str(SSID, IDX_VALUE(WIFI_SSID));
  setup();
}

void wait_connected() {
  xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
      false, true, portMAX_DELAY);
}

static void setup(void)
{
  tcpip_adapter_init();
  wifi_event_group = xEventGroupCreate();
  ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
  wifi_config_t wifi_config;
  strcpy((char *)wifi_config.sta.ssid, DEFAULT_SSID);
  strcpy((char *)wifi_config.sta.password, DEFAULT_PASS);
  wifi_config.sta.bssid_set = false;
  printf("Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
  ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
  ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
  ESP_ERROR_CHECK( esp_wifi_start() );
}

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
  switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
      printf("SYSTEM_EVENT_STA_START\n");
      esp_wifi_connect();
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      printf("SYSTEM_EVENT_STA_GOT_IP\n");
      xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      printf("SYSTEM_EVENT_STA_DISCONNECTED\n");
      /* This is a workaround as ESP32 WiFi libs don't currently
         auto-reassociate. */
      esp_wifi_connect();
      xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
      break;
    default:
      break;
  }
  return ESP_OK;
}

// BLE Callbacks


void on_set_wifi_ssid(const char *ssid) {

}

void on_set_wifi_password(const char *pass) {

}
