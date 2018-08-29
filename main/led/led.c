/*
 * =====================================================================================
 *
 *       Filename:  light.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/16/2018 14:51:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_err.h"

#include "led.h"
#include "../ble_db.h"
#include "../kv/kv.h"
#include "../kv/kv_ble.h"
#include "../ble/ble.h"
#include "../ble/ble_utils.h"
#include "../misc/log.h"
#include "../time/time.h"
#include "../state/state.h"

/*  UUID string: 6df781fe-6dce-5234-1870-6a972114c596 */
const uint8_t LED_INFO_UUID[ESP_UUID_LEN_128] = {0x96,0xc5,0x14,0x21,0x97,0x6a,0x70,0x18,0x34,0x52,0xce,0x6d,0xfe,0x81,0xf7,0x6d};

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define LEDC_FADE_TIME         (500)

void init_led_timers();

QueueHandle_t cmd;

void init_keys(int i) {
  char duty_key[13] = {0};
  sprintf(duty_key, "LED_%d_DUTY", i);

  defaulti(duty_key, 0);

  sync_ble_i(duty_key, ledc_channels[i].duty_val_idx);
}

static void fade_no_wait_led(ledc_channel_config_t ledc_channel, int duty) {
  ledc_set_fade_with_time(ledc_channel.speed_mode,
      ledc_channel.channel, duty, LEDC_FADE_TIME);
  ledc_fade_start(ledc_channel.speed_mode,
      ledc_channel.channel, LEDC_FADE_NO_WAIT);
}

/* static void fade_and_wait_led(ledc_channel_config_t ledc_channel, int duty) {
  ledc_set_fade_with_time(ledc_channel.speed_mode,
      ledc_channel.channel, duty, LEDC_FADE_TIME);
  ledc_fade_start(ledc_channel.speed_mode,
      ledc_channel.channel, LEDC_FADE_WAIT_DONE);
} */

static void update_led(int i) {
  char duty_key[13] = {0};
  sprintf(duty_key, "LED_%d_DUTY", i);

  double duty = geti(duty_key);
  double real_duty = ledc_channels[i].min_duty + (double)(ledc_channels[i].max_duty - ledc_channels[i].min_duty) * duty / 100;
  ESP_LOGI(TAG, "duty: %d %d", (int)duty, (int)real_duty);

  fade_no_wait_led(ledc_channels[i].channel_config, real_duty);
}

static void led_task(void *param) {

  int c;

  for (int i = 0; i < N_LEDS; ++i) {
    init_keys(i);
    ledc_channel_config(&ledc_channels[i].channel_config);
    update_led(i);
  }

  while(1) {
    if (xQueueReceive(cmd, &c, 30 * 1000 / portTICK_PERIOD_MS)) {
      ESP_LOGI(TAG, "Force refresh leds");
      if (c == -1) {
        for (int i = 0; i < N_LEDS; ++i) {
          update_led(i);
        }
      } else {
        update_led(c);
      }
    } else {
      ESP_LOGI(TAG, "Led refresh");
      for (int i = 0; i < N_LEDS; ++i) {
        update_led(i);
      }
    }
  }
}

void init_led_info() {
  char led_info[CHAR_VAL_LEN_MAX] = {0};

  sprintf(led_info, "%d", N_LEDS);
  for (int i = 0; i < N_LEDS; ++i) {
    char led[32] = {0};
    sprintf(led, "x:%d;y:%d;z:%d;gpio_num:%d", ledc_channels[i].x, ledc_channels[i].y, ledc_channels[i].z, ledc_channels[i].channel_config.gpio_num);
    if (strlen(led_info) + strlen(led) + 1 >= CHAR_VAL_LEN_MAX) {
      ESP_LOGE(TAG, "Not enough space to build LED_INFO !!!");
      break;
    }
    sprintf(led_info, "%s|%s", led_info, led);
  }
  set_attr_value(IDX_VALUE(LED_INFO), (const uint8_t *)led_info, strlen(led_info));
}

void init_led() {
  ESP_LOGI(TAG, "Initializing led task");

  init_led_info();

  cmd = xQueueCreate(10, sizeof(int));
  if (cmd == NULL) {
    ESP_LOGE(TAG, "Unable to create led queue");
  }

  init_led_timers();

  ledc_fade_func_install(0);

  xTaskCreate(led_task, "Led task", 2048, NULL, 10, NULL);
}

void refresh_led(int i) {
  xQueueSend(cmd, &i, 0);
}

int get_led_duty(int i) {
  char duty_key[13] = {0};
  sprintf(duty_key, "LED_%d_DUTY", i);

  return geti(duty_key);
}

void set_led_duty(int i, int value) {
  char duty_key[13] = {0};
  sprintf(duty_key, "LED_%d_DUTY", i);

  seti(duty_key, MIN(100, MAX(value, 0)));
  refresh_led(i);
}

/* BLE Callbacks */

void on_set_led_duty(enum idx iv, int i, int value) {
  char reset = value != MIN(100, MAX(value, 0));
  value = MIN(100, MAX(value, 0));
  set_led_duty(i, value);
  if (reset) {
    set_attr_value_and_notify(iv, (const uint8_t *)&value, sizeof(value));
  }
}
