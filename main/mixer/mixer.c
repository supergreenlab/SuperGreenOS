/*
 * =====================================================================================
 *
 *       Filename:  mixer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/16/2018 15:49:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "mixer.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "time.h"

#include "../core/ble.h"
#include "../ble_db.h"
#include "../core/kv.h"
#include "../core/kv_ble.h"
#include "../misc/log.h"
#include "../led/led.h"
#include "../state/state.h"
#include "../timers/timer.h"

/*  UUID string: a66375f6-7677-ba29-46b7-0fde55b0db61 */
const uint8_t LED_DIM_UUID[ESP_UUID_LEN_128] = {0x61,0xdb,0xb0,0x55,0xde,0x0f,0xb7,0x46,0x29,0xba,0x77,0x76,0xf6,0x75,0x63,0xa6};

#define LED_DIM "LED_DIM"

#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

static void mixer_task();
static void set_all_duty(int value);

void init_mixer() {
  defaulti(LED_DIM, 0);

  sync_ble_i(LED_DIM, IDX_VALUE(LED_DIM));

  BaseType_t ret = xTaskCreate(mixer_task, "Mixer task", 2048, NULL, tskIDLE_PRIORITY, NULL);
  if (ret != pdPASS) {
    ESP_LOGE(TAG, "Failed to create task");
  }
}

static void set_duty(const char *key, enum idx i, int duty) {
  seti(key, duty);
  set_attr_value_and_notify(i, (uint8_t *)&duty, sizeof(int));
}

static void mixer_task() {
  time_t now;

  while (1) {
    enum state s = geti(STATE);
    if (s != RUNNING) {
      vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
      continue;
    }

    time(&now);
    int led_dim = geti(LED_DIM);
    if (now - led_dim < 60) {
      vTaskDelay((now - led_dim + 1) * 1000 / portTICK_PERIOD_MS);
      continue;
    }

    double timerOutput = geti(TIMER_OUTPUT);
    double duty = LED_MIN_DUTY + (LED_MAX_DUTY - LED_MIN_DUTY) * timerOutput / 100;
    duty = max(0, min(LED_MAX_DUTY, duty));
    set_all_duty(duty);
    vTaskDelay(30 * 1000 / portTICK_PERIOD_MS);
  }
}

static void set_all_duty(int value) {
  set_duty(LED_DUTY(0, 0), IDX_VALUE(LED_0_0_DUTY), value);
  set_duty(LED_DUTY(0, 1), IDX_VALUE(LED_0_1_DUTY), value);
  set_duty(LED_DUTY(0, 2), IDX_VALUE(LED_0_2_DUTY), value);
  set_duty(LED_DUTY(1, 0), IDX_VALUE(LED_1_0_DUTY), value);
  set_duty(LED_DUTY(1, 1), IDX_VALUE(LED_1_1_DUTY), value);
  set_duty(LED_DUTY(1, 2), IDX_VALUE(LED_1_2_DUTY), value);
}

//  BLE Callbacks

void on_set_led_dim(int value) {
  seti(LED_DIM, value); 
  set_all_duty(LED_MIN_DUTY + (LED_MAX_DUTY - LED_MIN_DUTY) * 0.2);
  refresh_led(-1);
}
