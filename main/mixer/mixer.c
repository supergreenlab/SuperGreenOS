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

#include "../core/ble.h"
#include "../ble_db.h"
#include "../core/kv.h"
#include "../misc/log.h"
#include "../led/led.h"
#include "../timers/timer.h"

#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

static void mixer_task();

void init_mixer() {
  BaseType_t ret = xTaskCreate(mixer_task, "Mixer task", 2048, NULL, tskIDLE_PRIORITY, NULL);
  if (ret != pdPASS) {
    ESP_LOGE(TAG, "Failed to create task");
  }
}

void set_duty(const char *key, enum idx i, int duty) {
  seti(key, duty);
  set_attr_value_and_notify(i, (uint8_t *)&duty, sizeof(int));
}

static void mixer_task() {
  while (1) {
    double timerOutput = geti(TIMER_OUTPUT);
    double duty = LED_MIN_DUTY + (LED_MAX_DUTY - LED_MIN_DUTY) * (timerOutput - 50) / 100;
    duty = max(0, min(LED_MAX_DUTY, duty));
    set_duty(LED_DUTY(0, 0), IDX_VALUE(LED_0_0_DUTY), duty);
    set_duty(LED_DUTY(0, 1), IDX_VALUE(LED_0_1_DUTY), duty);
    set_duty(LED_DUTY(0, 2), IDX_VALUE(LED_0_2_DUTY), duty);
    set_duty(LED_DUTY(1, 0), IDX_VALUE(LED_1_0_DUTY), duty);
    set_duty(LED_DUTY(1, 1), IDX_VALUE(LED_1_1_DUTY), duty);
    set_duty(LED_DUTY(1, 2), IDX_VALUE(LED_1_1_DUTY), duty);
    vTaskDelay(30 * 1000 / portTICK_PERIOD_MS);
  }
}
