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

#include "../core/kv.h"
#include "../misc/log.h"
#include "../led/led.h"
#include "../timers/timer.h"

static void mixer_task();

void init_mixer() {
  BaseType_t ret = xTaskCreate(mixer_task, "Mixer task", 2048, NULL, tskIDLE_PRIORITY, NULL);
  if (ret != pdPASS) {
    ESP_LOGE(TAG, "Failed to create task");
  }
}

static void mixer_task() {
  while (1) {
    double timerOutput = geti(TIMER_OUTPUT);
    double duty = LED_MIN_DUTY + (LED_MAX_DUTY - LED_MIN_DUTY) * (timerOutput - 50) / 100;
    seti(LED_DUTY(0, 0), duty);
    seti(LED_DUTY(0, 1), duty);
    seti(LED_DUTY(0, 2), duty);
    seti(LED_DUTY(1, 0), duty);
    seti(LED_DUTY(1, 1), duty);
    seti(LED_DUTY(1, 2), duty);
    vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
  }
}
