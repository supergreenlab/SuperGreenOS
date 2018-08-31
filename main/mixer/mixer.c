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

#include "../conf/ble_db.h"
#include "../kv/kv.h"
#include "../kv/kv_ble.h"
#include "../ble/ble.h"
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

static void set_duty(int i, int duty) {
  set_led_duty(i, duty);
  set_attr_value_and_notify(ledc_channels[i].duty_val_idx, (uint8_t *)&duty, sizeof(int));
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
    double duty = timerOutput;
    duty = max(0, min(100, duty));
    set_all_duty(duty);
    vTaskDelay(30 * 1000 / portTICK_PERIOD_MS);
  }
}

static void set_all_duty(int value) {
  for (int i = 0; i < N_LEDS; ++i) {
    set_duty(i, value);
  }
}

//  BLE Callbacks

void on_set_led_dim(int value) {
  seti(LED_DIM, value); 
  set_all_duty(10);
  refresh_led(-1);
}
