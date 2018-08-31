/*
 * =====================================================================================
 *
 *       Filename:  touch.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/13/2018 12:05:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../kv/kv.h"
#include "../ble/ble.h"
#include "../kv/kv_ble.h"
#include "../misc/log.h"
#include "../led/led.h"
#include "timer.h"
#include "../conf/ble_db.h"

#include "manual/manual.h"
#include "onoff/onoff.h"
#include "season/season.h"
#include "../state/state.h"

/*  UUID string: 5f5ea840-3aa9-0a7b-343d-415ab2faa9f3 */
const uint8_t TIMER_TYPE_UUID[ESP_UUID_LEN_128] = {0xf3,0xa9,0xfa,0xb2,0x5a,0x41,0x3d,0x34,0x7b,0x0a,0xa9,0x3a,0x40,0xa8,0x5e,0x5f};
/*  UUID string: b2286094-8299-a967-db89-ee856e365789 */
const uint8_t TIMER_OUTPUT_UUID[ESP_UUID_LEN_128] = {0x89,0x57,0x36,0x6e,0x85,0xee,0x89,0xdb,0x67,0xa9,0x99,0x82,0x94,0x60,0x28,0xb2};

static void timer_task(void *param);
static void stop(enum timer t);
static void start(enum timer t);

void init_timer() {
  defaulti(TIMER_TYPE, TIMER_MANUAL);
  defaulti(TIMER_OUTPUT, 0);

  sync_ble_i(TIMER_TYPE, IDX_VALUE(TIMER_TYPE));
  sync_ble_i(TIMER_OUTPUT, IDX_VALUE(TIMER_OUTPUT));

  start(geti(TIMER_TYPE));

  BaseType_t ret = xTaskCreate(timer_task, "Timer task", 2048, NULL, tskIDLE_PRIORITY, NULL);
  if (ret != pdPASS) {
    ESP_LOGE(TAG, "Failed to create task");
  }
}

static void stop(enum timer t) {
  switch(t) {
    case TIMER_MANUAL:
      stop_manual();
      break;
    case TIMER_ONOFF:
      stop_onoff();
      break;
    case TIMER_SEASON:
      stop_season();
      break;
  }
}

static void start(enum timer t) {
  switch(t) {
    case TIMER_MANUAL:
      start_manual();
      break;
    case TIMER_ONOFF:
      start_onoff();
      break;
    case TIMER_SEASON:
      start_season();
      break;
  }
}

void update_output(int output) {
  ESP_LOGI(TAG, "update_output %d", output);
  seti(TIMER_OUTPUT, output);
  set_attr_value_and_notify(IDX_VALUE(TIMER_OUTPUT), (uint8_t *)&output, sizeof(int));
}

static void timer_task(void *param) {
  while (1) {
    enum state s = geti(STATE);
    if (s != RUNNING) {
      vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
      continue;
    }

    enum timer t = geti(TIMER_TYPE);

    switch(t) {
      case TIMER_MANUAL:
        manual_task();
        break;
      case TIMER_ONOFF:
        onoff_task();
        break;
      case TIMER_SEASON:
        season_task();
        break;
    }
    vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
  }
}

// BLE Callbacks

void on_set_timer_type(enum timer t) {
  enum timer old = geti(TIMER_TYPE);

  if (old == t) return;
  seti(TIMER_TYPE, t);
  stop(old);
  start(t);
  refresh_led(-1);
}

void on_set_timer_output(int value) {
  if (geti(TIMER_TYPE) != TIMER_MANUAL) return;

  seti(TIMER_OUTPUT, value);
}
