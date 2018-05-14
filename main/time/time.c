/*
 * =====================================================================================
 *
 *       Filename:  time.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/16/2018 19:26:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "apps/sntp/sntp.h"

#include "../misc/log.h"
#include "time.h"
#include "utils.h"
#include "../core/kv.h"
#include "../core/kv_ble.h"
#include "../core/ble.h"
#include "../ble_db.h"
#include "../wifi/wifi.h"

// "40f9ee4f-e19e-4a8a-aa33-b4aae23b6a9b"
const uint8_t TIME_UUID[ESP_UUID_LEN_128] = {0x9b,0x6a,0x3b,0xe2,0xaa,0xb4,0x33,0xaa,0x8a,0x4a,0x9e,0xe1,0x4f,0xee,0xf9,0x40};

#define TIME "TIME"

static void time_task(void *param);
static void ntp_task(void *param);
static void setup(void);

void init_time() {
  defaulti(TIME, 4);
  sync_ble_i(TIME, IDX_CHAR_VAL_TIME);

  xTaskCreate(time_task, "Time Task", 2048, NULL, 10, NULL);
}

static void time_task(void *param) {
  if (hasi(TIME)) {
    time_t now = (time_t)geti(TIME);
    struct timeval tv = { .tv_sec = now, .tv_usec = 0 };
    settimeofday(&tv, NULL);
    print_time(now);
    xTaskCreate(ntp_task, "NTP task", 2048, NULL, 10, NULL);
  } else {
    wait_connected();
    setup();
  }
  while(true) {
    time_t now;
    time(&now);
    print_time(now);
    seti(TIME, (int)now);
    set_attr_value(IDX_CHAR_VAL_TIME, (uint8_t *)&now, sizeof(time_t));
    notify_attr(IDX_CHAR_VAL_TIME);

    vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
  }
}

static void ntp_task(void *param) {
  wait_connected();
  setup();
  vTaskDelete(NULL);
}

static void setup(void) {
  const char *NTP_SERVER = "pool.ntp.org";
  printf("Initializing SNTP\n");
  sntp_setoperatingmode(SNTP_OPMODE_POLL);
  sntp_setservername(0, (char *)NTP_SERVER);
  sntp_init();
}

/* ble callbacks */

void on_set_time(time_t value) {
  ESP_LOGI(TAG, "on_set_time %d", (int)value);
  struct timeval tv = { .tv_sec = value, .tv_usec = 0 };
  settimeofday(&tv, NULL);
  seti(TIME, (int)value);
}
