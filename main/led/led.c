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

/*  UUID string: 4750daf8-0f06-ad2b-178e-ec58c7f30421 */
const uint8_t LED_0_0_PWR_UUID[ESP_UUID_LEN_128] = {0x21,0x04,0xf3,0xc7,0x58,0xec,0x8e,0x17,0x2b,0xad,0x06,0x0f,0xf8,0xda,0x50,0x47};
/*  UUID string: 3c14371f-b1b6-6d66-cc02-b01396f6f84f */
const uint8_t LED_0_1_PWR_UUID[ESP_UUID_LEN_128] = {0x4f,0xf8,0xf6,0x96,0x13,0xb0,0x02,0xcc,0x66,0x6d,0xb6,0xb1,0x1f,0x37,0x14,0x3c};
/*  UUID string: ca2a9037-7626-6751-60fb-c3922021cc42 */
const uint8_t LED_0_2_PWR_UUID[ESP_UUID_LEN_128] = {0x42,0xcc,0x21,0x20,0x92,0xc3,0xfb,0x60,0x51,0x67,0x26,0x76,0x37,0x90,0x2a,0xca};
/*  UUID string: 0365b1c9-4079-4caf-51f4-2730ca055bb5 */
const uint8_t LED_1_0_PWR_UUID[ESP_UUID_LEN_128] = {0xb5,0x5b,0x05,0xca,0x30,0x27,0xf4,0x51,0xaf,0x4c,0x79,0x40,0xc9,0xb1,0x65,0x03};
/*  UUID string: ab2abc56-1a48-84d1-1b20-6c0035d7c9eb */
const uint8_t LED_1_1_PWR_UUID[ESP_UUID_LEN_128] = {0xeb,0xc9,0xd7,0x35,0x00,0x6c,0x20,0x1b,0xd1,0x84,0x48,0x1a,0x56,0xbc,0x2a,0xab};
/*  UUID string: 05a5cc9e-a67b-bc62-2577-6ceb69cbc567 */
const uint8_t LED_1_2_PWR_UUID[ESP_UUID_LEN_128] = {0x67,0xc5,0xcb,0x69,0xeb,0x6c,0x77,0x25,0x62,0xbc,0x7b,0xa6,0x9e,0xcc,0xa5,0x05};

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

#define LEDC_LS_CH0_GPIO       (19)
#define LEDC_LS_CH0_CHANNEL    LEDC_CHANNEL_0
#define LEDC_LS_CH1_GPIO       (18)
#define LEDC_LS_CH1_CHANNEL    LEDC_CHANNEL_1
#define LEDC_LS_CH2_GPIO       (5)
#define LEDC_LS_CH2_CHANNEL    LEDC_CHANNEL_2
#define LEDC_LS_CH3_GPIO       (33)
#define LEDC_LS_CH3_CHANNEL    LEDC_CHANNEL_3
#define LEDC_LS_CH4_GPIO       (25)
#define LEDC_LS_CH4_CHANNEL    LEDC_CHANNEL_4
#define LEDC_LS_CH5_GPIO       (26)
#define LEDC_LS_CH5_CHANNEL    LEDC_CHANNEL_5

#define LEDC_CH_NUM            (6)
#define LEDC_FADE_TIME         (1000)

typedef struct led_config {
  char           *duty_key;
  char           *power_key;
  enum idx       duty_val_idx;
  enum idx       power_val_idx;

  ledc_channel_config_t channel_config;
} led_config_t;

#define N_CHANNELS 6

led_config_t ledc_channels[N_CHANNELS] = {
  {
    duty_key: LED_0_0_DUTY,
    power_key: LED_0_0_PWR,
    duty_val_idx: IDX_VALUE(LED_0_0_PWR),
    power_val_idx: IDX_VALUE(LED_0_0_DUTY),

    channel_config: {
      gpio_num:    LEDC_LS_CH0_GPIO,
      speed_mode:  LEDC_LOW_SPEED_MODE,
      channel:     LEDC_LS_CH0_CHANNEL,
      intr_type:   LEDC_INTR_FADE_END,
      timer_sel:   LEDC_TIMER_1,
      duty:        0,
    }
  },
  {
    duty_key: "LED_0_1_DUTY",
    power_key: "LED_0_1_PWR",
    duty_val_idx: IDX_VALUE(LED_0_1_PWR),
    power_val_idx: IDX_VALUE(LED_0_1_DUTY),

    channel_config: {
      gpio_num:    LEDC_LS_CH1_GPIO,
      speed_mode:  LEDC_LOW_SPEED_MODE,
      channel:     LEDC_LS_CH1_CHANNEL,
      intr_type:   LEDC_INTR_FADE_END,
      timer_sel:   LEDC_TIMER_1,
      duty:        0,
    }
  },
  {
    duty_key: "LED_0_2_DUTY",
    power_key: "LED_0_2_PWR",
    duty_val_idx: IDX_VALUE(LED_0_2_PWR),
    power_val_idx: IDX_VALUE(LED_0_2_DUTY),

    channel_config: {
      gpio_num:    LEDC_LS_CH2_GPIO,
      speed_mode:  LEDC_LOW_SPEED_MODE,
      channel:     LEDC_LS_CH2_CHANNEL,
      intr_type:   LEDC_INTR_FADE_END,
      timer_sel:   LEDC_TIMER_1,
      duty:        0,
    }
  },
  {
    duty_key: "LED_1_0_DUTY",
    power_key: "LED_1_0_PWR",
    duty_val_idx: IDX_VALUE(LED_1_0_PWR),
    power_val_idx: IDX_VALUE(LED_1_0_DUTY),

    channel_config: {
      gpio_num:    LEDC_LS_CH3_GPIO,
      speed_mode:  LEDC_LOW_SPEED_MODE,
      channel:     LEDC_LS_CH3_CHANNEL,
      intr_type:   LEDC_INTR_FADE_END,
      timer_sel:   LEDC_TIMER_1,
      duty:        0,
    }
  },
  {
    duty_key: "LED_1_1_DUTY",
    power_key: "LED_1_1_PWR",
    duty_val_idx: IDX_VALUE(LED_1_1_PWR),
    power_val_idx: IDX_VALUE(LED_1_1_DUTY),

    channel_config: {
      gpio_num:    LEDC_LS_CH4_GPIO,
      speed_mode:  LEDC_LOW_SPEED_MODE,
      channel:     LEDC_LS_CH4_CHANNEL,
      intr_type:   LEDC_INTR_FADE_END,
      timer_sel:   LEDC_TIMER_1,
      duty:        0,
    }
  },
  {
    duty_key: "LED_1_2_DUTY",
    power_key: "LED_1_2_PWR",
    duty_val_idx: IDX_VALUE(LED_1_2_PWR),
    power_val_idx: IDX_VALUE(LED_1_2_DUTY),

    channel_config: {
      gpio_num:    LEDC_LS_CH5_GPIO,
      speed_mode:  LEDC_LOW_SPEED_MODE,
      channel:     LEDC_LS_CH5_CHANNEL,
      intr_type:   LEDC_INTR_FADE_END,
      timer_sel:   LEDC_TIMER_1,
      duty:        0,
    }
  },
};

QueueHandle_t cmd;

static const unsigned char CMD_REFRESH_LED = 1;

void init_keys(led_config_t config) {
  defaulti(config.duty_key, 0);
  defaulti(config.power_key, 100);

  sync_ble_i(config.duty_key, config.duty_val_idx);
  sync_ble_i(config.power_key, config.power_val_idx);
}

void fade_no_wait_led(ledc_channel_config_t ledc_channel, int duty) {
  ledc_set_fade_with_time(ledc_channel.speed_mode,
      ledc_channel.channel, duty, LEDC_FADE_TIME);
}

void fade_and_wait_led(ledc_channel_config_t ledc_channel, int duty) {
  ledc_set_fade_with_time(ledc_channel.speed_mode,
      ledc_channel.channel, duty, LEDC_FADE_TIME);
  ledc_fade_start(ledc_channel.speed_mode,
      ledc_channel.channel, LEDC_FADE_WAIT_DONE);
}

void led_task(void *param) {

  unsigned char c;

  for (int i = 0; i < N_CHANNELS; ++i) {
    init_keys(ledc_channels[i]);
    ledc_channel_config(&ledc_channels[i].channel_config);
  }

  while(1) {
    for (int i = 0; i < N_CHANNELS; ++i) {
      int duty = geti(ledc_channels[i].duty_key);
      int power = geti(ledc_channels[i].power_key);
      ESP_LOGI(TAG, "power: %d duty: %d led: %d", power, duty, (int)((double)duty * (double)power/100));

      fade_no_wait_led(ledc_channels[i].channel_config, (int)((double)duty * (double)power/100));
    }
    if (xQueueReceive(cmd, &c, 30*1000 / portTICK_PERIOD_MS)) {
      ESP_LOGI(TAG, "Force refresh leds");
    }
  }
}

void init_led() {
  ESP_LOGI(TAG, "Initializing led task");

  cmd = xQueueCreate(10, sizeof(unsigned char));
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

void refresh_led() {
  xQueueSend(cmd, &CMD_REFRESH_LED, 0);
}

/* BLE Callbacks */

void on_set_led_0_0_pwr(int value) {
  seti(LED_0_0_PWR, value);
  refresh_led();
}

void on_set_led_0_1_pwr(int value) {
  seti(LED_0_1_PWR, value);
  refresh_led();
}

void on_set_led_0_2_pwr(int value) {
  seti(LED_0_2_PWR, value);
  refresh_led();
}

void on_set_led_1_0_pwr(int value) {
  seti(LED_1_0_PWR, value);
  refresh_led();
}

void on_set_led_1_1_pwr(int value) {
  seti(LED_1_1_PWR, value);
  refresh_led();
}

void on_set_led_1_2_pwr(int value) {
  seti(LED_1_2_PWR, value);
  refresh_led();
}



void on_set_led_0_0_duty(int value) {
  seti(LED_0_0_DUTY, value);
  refresh_led();
}

void on_set_led_0_1_duty(int value) {
  seti(LED_0_1_DUTY, value);
  refresh_led();
}

void on_set_led_0_2_duty(int value) {
  seti(LED_0_2_DUTY, value);
  refresh_led();
}

void on_set_led_1_0_duty(int value) {
  seti(LED_1_0_DUTY, value);
  refresh_led();
}

void on_set_led_1_1_duty(int value) {
  seti(LED_1_1_DUTY, value);
  refresh_led();
}

void on_set_led_1_2_duty(int value) {
  seti(LED_1_2_DUTY, value);
  refresh_led();
}
