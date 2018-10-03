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
#include <time.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lwip/apps/sntp.h"

#include "../log/log.h"
#include "time.h"
#include "utils.h"
#include "../kv/kv.h"
#include "../kv/kv_ble.h"
#include "../ble/ble.h"
#include "../conf/ble_db.h"
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

  xTaskCreate(time_task, "Time Task", 4096, NULL, 10, NULL);
}

static void time_task(void *param) {
  if (hasi(TIME)) {
    time_t now = (time_t)geti(TIME);
    struct timeval tv = { .tv_sec = now, .tv_usec = 0 };
    settimeofday(&tv, NULL);
    xTaskCreate(ntp_task, "NTP task", 4096, NULL, 10, NULL);
  } else {
    wait_connected();
    setup();
  }
  while(true) {
    time_t now;
    time(&now);
    print_time(SGO_LOG_NOSEND, "@TIME", now);
    seti(TIME, (int)now);
    set_attr_value_and_notify(IDX_CHAR_VAL_TIME, (uint8_t *)&now, sizeof(time_t));

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
  ESP_LOGI(SGO_LOG_EVENT, "@TIME Initializing SNTP\n");
  sntp_setoperatingmode(SNTP_OPMODE_POLL);
  sntp_setservername(0, (char *)NTP_SERVER);
  sntp_init();
}

/* ble callbacks */

void on_set_time(time_t value) {
  ESP_LOGI(SGO_LOG_EVENT, "@TIMER on_set_time = %d", (int)value);
  struct timeval tv = { .tv_sec = value, .tv_usec = 0 };
  settimeofday(&tv, NULL);
  seti(TIME, (int)value);
}
