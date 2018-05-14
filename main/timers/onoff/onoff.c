/*
 * =====================================================================================
 *
 *       Filename:  onoff.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/13/2018 15:34:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "onoff.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "../../misc/log.h"
#include "../../core/kv.h"
#include "../../core/kv_ble.h"
#include "../../core/ble.h"
#include "../../ble_db.h"

/*  UUID string: e867f9a6-4ab7-09da-ef26-19f350ed4ba1 */
const uint8_t ON_HOUR_UUID[ESP_UUID_LEN_128] = {0xa1,0x4b,0xed,0x50,0xf3,0x19,0x26,0xef,0xda,0x09,0xb7,0x4a,0xa6,0xf9,0x67,0xe8};
/*  UUID string: 7528a50b-dd3b-f714-62f5-7167f1791347 */
const uint8_t ON_MIN_UUID[ESP_UUID_LEN_128] = {0x47,0x13,0x79,0xf1,0x67,0x71,0xf5,0x62,0x14,0xf7,0x3b,0xdd,0x0b,0xa5,0x28,0x75};
/*  UUID string: 5dafb88c-9d7e-ab6b-0253-12294c35beae */
const uint8_t OFF_HOUR_UUID[ESP_UUID_LEN_128] = {0xae,0xbe,0x35,0x4c,0x29,0x12,0x53,0x02,0x6b,0xab,0x7e,0x9d,0x8c,0xb8,0xaf,0x5d};
/*  UUID string: 086aa1e1-d9ab-2d22-4110-4f3f05efd3d4 */
const uint8_t OFF_MIN_UUID[ESP_UUID_LEN_128] = {0xd4,0xd3,0xef,0x05,0x3f,0x4f,0x10,0x41,0x22,0x2d,0xab,0xd9,0xe1,0xa1,0x6a,0x08};

#define ON_HOUR "ON_H"
#define ON_MIN "ON_M"
#define OFF_HOUR "OFF_H"
#define OFF_MIN "OFF_M"

#define NOT_SET INT_MAX

const unsigned char CMD_QUIT = 1;

QueueHandle_t cmd;

void onoff_task(void *param);

void init_onoff() {
  defaulti(ON_HOUR, NOT_SET);
  defaulti(ON_MIN, NOT_SET);
  defaulti(OFF_HOUR, NOT_SET);
  defaulti(OFF_MIN, NOT_SET);

  sync_ble_i(ON_HOUR, IDX_VALUE(ON_HOUR));
  sync_ble_i(ON_MIN, IDX_VALUE(ON_MIN));
  sync_ble_i(OFF_HOUR, IDX_VALUE(OFF_HOUR));
  sync_ble_i(OFF_MIN, IDX_VALUE(OFF_MIN));
}

void start_onoff() {
  ESP_LOGI(TAG, "start_onoff");
  BaseType_t ret = xTaskCreate(onoff_task, "onoff task", 1024, NULL, tskIDLE_PRIORITY, NULL);
  if (ret != pdPASS) {
    ESP_LOGE(TAG, "Failed to create task");
  }
  cmd = xQueueCreate(10, sizeof(unsigned char));
  if (cmd == NULL) {
    ESP_LOGE(TAG, "Failed to create queue");
  }
}

void stop_onoff() {
  ESP_LOGI(TAG, "stop_onoff");
}

void onoff_task(void *param) {
  unsigned char c;
  while (1) {
    if(xQueueReceive(cmd, &c, (TickType_t) 100)) {
      if (c == CMD_QUIT) {
        ESP_LOGI(TAG, "onoff timer CMD_QUIT");
        break;
      }
    }
  }

  vQueueDelete(cmd);
  cmd = NULL;
  vTaskDelete(NULL);
}

// BLE Callbacks

void on_set_on_hour(int value) {
  seti(ON_HOUR, value);
}

void on_set_on_min(int value) {
  seti(ON_MIN, value);
}

void on_set_off_hour(int value) {
  seti(OFF_HOUR, value);
}

void on_set_off_min(int value) {
  seti(OFF_MIN, value);
}
