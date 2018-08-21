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
#include "driver/ledc.h"
#include "esp_err.h"

#include "led.h"
#include "../ble_db.h"
#include "../core/kv.h"
#include "../core/kv_ble.h"
#include "../misc/log.h"
#include "../time/time.h"
#include "../state/state.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/*  UUID string: 4291ec1b-65df-19c4-c5f1-e4259071fc5d */
const uint8_t LED_0_0_DUTY_UUID[ESP_UUID_LEN_128] = {0x5d,0xfc,0x71,0x90,0x25,0xe4,0xf1,0xc5,0xc4,0x19,0xdf,0x65,0x1b,0xec,0x91,0x42};
/*  UUID string: 18a17b54-716d-3eb8-af12-b447d7c81cd8 */
const uint8_t LED_0_1_DUTY_UUID[ESP_UUID_LEN_128] = {0xd8,0x1c,0xc8,0xd7,0x47,0xb4,0x12,0xaf,0xb8,0x3e,0x6d,0x71,0x54,0x7b,0xa1,0x18};
/*  UUID string: 2914d978-e7d9-6f5a-36e8-1a11011ab737 */
const uint8_t LED_0_2_DUTY_UUID[ESP_UUID_LEN_128] = {0x37,0xb7,0x1a,0x01,0x11,0x1a,0xe8,0x36,0x5a,0x6f,0xd9,0xe7,0x78,0xd9,0x14,0x29};
/*  UUID string: 4cba86fc-e385-3cd2-2de5-5c7ef8a6ed40 */
const uint8_t LED_1_0_DUTY_UUID[ESP_UUID_LEN_128] = {0x40,0xed,0xa6,0xf8,0x7e,0x5c,0xe5,0x2d,0xd2,0x3c,0x85,0xe3,0xfc,0x86,0xba,0x4c};
/*  UUID string: 5b11c5f4-67b6-c712-fc1c-4b13fa9fd3cb */
const uint8_t LED_1_1_DUTY_UUID[ESP_UUID_LEN_128] = {0xcb,0xd3,0x9f,0xfa,0x13,0x4b,0x1c,0xfc,0x12,0xc7,0xb6,0x67,0xf4,0xc5,0x11,0x5b};
/*  UUID string: bd87b60e-30b7-d99c-56e2-cd377da4494e */
const uint8_t LED_1_2_DUTY_UUID[ESP_UUID_LEN_128] = {0x4e,0x49,0xa4,0x7d,0x37,0xcd,0xe2,0x56,0x9c,0xd9,0xb7,0x30,0x0e,0xb6,0x87,0xbd};

#define LEDC_LS_CH0_GPIO       (32)
#define LEDC_LS_CH0_CHANNEL    LEDC_CHANNEL_0
#define LEDC_LS_CH1_GPIO       (33)
#define LEDC_LS_CH1_CHANNEL    LEDC_CHANNEL_1
#define LEDC_LS_CH2_GPIO       (25)
#define LEDC_LS_CH2_CHANNEL    LEDC_CHANNEL_2
#define LEDC_LS_CH3_GPIO       (17)
#define LEDC_LS_CH3_CHANNEL    LEDC_CHANNEL_3
#define LEDC_LS_CH4_GPIO       (16)
#define LEDC_LS_CH4_CHANNEL    LEDC_CHANNEL_4
#define LEDC_LS_CH5_GPIO       (4)
#define LEDC_LS_CH5_CHANNEL    LEDC_CHANNEL_5


#define LEDC_CH_NUM            (6)
#define LEDC_FADE_TIME         (1000)

typedef struct led_config {
  char           *duty_key;
  enum idx       duty_val_idx;

  ledc_channel_config_t channel_config;
} led_config_t;

#define N_CHANNELS 6

#define CHANNEL(side, n, gpio) { \
    duty_key: LED_##side##_##n##_DUTY, \
    duty_val_idx: IDX_VALUE(LED_##side##_##n##_DUTY), \
    \
    channel_config: { \
      gpio_num:    LEDC_LS_CH##gpio##_GPIO, \
      speed_mode:  LEDC_LOW_SPEED_MODE, \
      channel:     LEDC_LS_CH##gpio##_CHANNEL, \
      intr_type:   LEDC_INTR_FADE_END, \
      timer_sel:   LEDC_TIMER_1, \
      duty:        0, \
    } \
  }

led_config_t ledc_channels[N_CHANNELS] = {
  CHANNEL(0, 0, 0),
  CHANNEL(0, 1, 1),
  CHANNEL(0, 2, 2),
  CHANNEL(1, 0, 3),
  CHANNEL(1, 1, 4),
  CHANNEL(1, 2, 5)
};

QueueHandle_t cmd;

void init_keys(led_config_t config) {
  defaulti(config.duty_key, 0);

  sync_ble_i(config.duty_key, config.duty_val_idx);
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
  int duty = geti(ledc_channels[i].duty_key);
  ESP_LOGI(TAG, "duty: %d", duty);

  fade_no_wait_led(ledc_channels[i].channel_config, duty);
}

static void led_task(void *param) {

  int c;

  for (int i = 0; i < N_CHANNELS; ++i) {
    init_keys(ledc_channels[i]);
    ledc_channel_config(&ledc_channels[i].channel_config);
    update_led(i);
  }

  while(1) {
    if (xQueueReceive(cmd, &c, 30 * 1000 / portTICK_PERIOD_MS)) {
      ESP_LOGI(TAG, "Force refresh leds");
      if (c == -1) {
        for (int i = 0; i < N_CHANNELS; ++i) {
          update_led(i);
        }
      } else {
        update_led(c);
      }
    } else {
      ESP_LOGI(TAG, "Led refresh");
      for (int i = 0; i < N_CHANNELS; ++i) {
        update_led(i);
      }
    }
  }
}

void init_led() {
  ESP_LOGI(TAG, "Initializing led task");

  cmd = xQueueCreate(10, sizeof(int));
  if (cmd == NULL) {
    ESP_LOGE(TAG, "Unable to create led queue");
  }

  ledc_timer_config_t ledc_timer = {
    speed_mode:       LEDC_LOW_SPEED_MODE,
    { duty_resolution:  LEDC_TIMER_13_BIT, },
    timer_num:        LEDC_TIMER_1,
    freq_hz:          120,
  };
  ledc_timer_config(&ledc_timer);

  ledc_fade_func_install(0);

  xTaskCreate(led_task, "Led task", 2048, NULL, 10, NULL);
}

void refresh_led(int i) {
  xQueueSend(cmd, &i, 0);
}

/* BLE Callbacks */

void on_set_led_0_0_pwr(int value) {
  value = MIN(100, MAX(value, 0));
  seti(LED_0_0_PWR, value);
  refresh_led(0);
}

void on_set_led_0_1_pwr(int value) {
  value = MIN(100, MAX(value, 0));
  seti(LED_0_1_PWR, value);
  refresh_led(1);
}

void on_set_led_0_2_pwr(int value) {
  value = MIN(100, MAX(value, 0));
  seti(LED_0_2_PWR, value);
  refresh_led(2);
}

void on_set_led_1_0_pwr(int value) {
  value = MIN(100, MAX(value, 0));
  seti(LED_1_0_PWR, value);
  refresh_led(3);
}

void on_set_led_1_1_pwr(int value) {
  value = MIN(100, MAX(value, 0));
  seti(LED_1_1_PWR, value);
  refresh_led(4);
}

void on_set_led_1_2_pwr(int value) {
  value = MIN(100, MAX(value, 0));
  seti(LED_1_2_PWR, value);
  refresh_led(5);
}



void on_set_led_0_0_duty(int value) {
  value = MIN(LED_MAX_DUTY, MAX(value, LED_MIN_DUTY));
  seti(LED_0_0_DUTY, value);

  const int pwr = geti(LED_0_0_PWR);
  if (pwr != 0) {
    refresh_led(0);
  }
}

void on_set_led_0_1_duty(int value) {
  value = MIN(LED_MAX_DUTY, MAX(value, LED_MIN_DUTY));
  seti(LED_0_1_DUTY, value);

  const int pwr = geti(LED_0_1_PWR);
  if (pwr != 0) {
    refresh_led(1);
  }
}

void on_set_led_0_2_duty(int value) {
  value = MIN(LED_MAX_DUTY, MAX(value, LED_MIN_DUTY));
  seti(LED_0_2_DUTY, value);

  const int pwr = geti(LED_0_2_PWR);
  if (pwr != 0) {
    refresh_led(2);
  }
}

void on_set_led_1_0_duty(int value) {
  value = MIN(LED_MAX_DUTY, MAX(value, LED_MIN_DUTY));
  seti(LED_1_0_DUTY, value);

  const int pwr = geti(LED_1_0_PWR);
  if (pwr != 0) {
    refresh_led(3);
  }
}

void on_set_led_1_1_duty(int value) {
  value = MIN(LED_MAX_DUTY, MAX(value, LED_MIN_DUTY));
  seti(LED_1_1_DUTY, value);

  const int pwr = geti(LED_1_1_PWR);
  if (pwr != 0) {
    refresh_led(4);
  }
}

void on_set_led_1_2_duty(int value) {
  value = MIN(LED_MAX_DUTY, MAX(value, LED_MIN_DUTY));
  seti(LED_1_2_DUTY, value);

  const int pwr = geti(LED_1_2_PWR);
  if (pwr != 0) {
    refresh_led(5);
  }
}
