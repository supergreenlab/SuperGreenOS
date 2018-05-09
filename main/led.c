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

#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

#include "kv.h"
#include "time.h"

#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

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
#define LED_MIN_DUTY           (550)
#define LED_MAX_DUTY           (8191)
#define LEDC_FADE_TIME         (1000)

#define YEAR_ADV_OFFSET (time_t)(10*24*60*60) // solstice is 21st June, that's the 172nd day in year

typedef struct led_config {
  ledc_channel_t  channel;
  int             gpio;
  int             side;
  int             num;

  char           power_key[32];
} led_config_t;

int get_duty_for_time() {
  time_t now = get_box_time() - YEAR_ADV_OFFSET;

  struct tm timeinfo;
  localtime_r(&now, &timeinfo); 

  double day_adv = (double)(timeinfo.tm_hour*60*60 + timeinfo.tm_min*60 + timeinfo.tm_sec) / (double)(24*60*60);
  double year_adv = (double)(timeinfo.tm_yday) / (double) 365;

  double span = LED_MAX_DUTY - LED_MIN_DUTY;
  double duty = LED_MIN_DUTY - cos(year_adv * M_PI * 2) * span / 2 - cos(day_adv * M_PI * 2) * span / 2;
  return min(LED_MAX_DUTY, max(0, duty));
}

void init_keys(led_config_t config) {
  defaulti(config.power_key, 100);
}

void fade_and_wait_led(ledc_channel_config_t ledc_channel, int duty) {
  ledc_set_fade_with_time(ledc_channel.speed_mode,
      ledc_channel.channel, duty, LEDC_FADE_TIME);
  ledc_fade_start(ledc_channel.speed_mode,
      ledc_channel.channel, LEDC_FADE_WAIT_DONE);
}

void led_task(void *param) {
  led_config_t config = *((led_config_t *)param);
  init_keys(config);
  ledc_channel_config_t ledc_channel = {
    gpio_num:    config.gpio,
    speed_mode:  LEDC_LOW_SPEED_MODE,
    channel:     config.channel,
    intr_type:   LEDC_INTR_FADE_END,
    timer_sel:   LEDC_TIMER_1,
    duty:        0,
  };
  ledc_channel_config(&ledc_channel);

  while(1) {
    int power = geti(config.power_key);
    int duty = get_duty_for_time();
    printf("power: %d duty: %d led: %d\n", power, duty, (int)((double)duty * (double)power/100));

    fade_and_wait_led(ledc_channel, (int)((double)duty * (double)power/100));
    vTaskDelay(30*1000 / portTICK_PERIOD_MS);
  }
}

void start_led_task(ledc_channel_t channel, int gpio, int side, int num) {
  led_config_t *conf = (led_config_t *)malloc(sizeof(led_config_t));
  conf->channel = channel;
  conf->gpio = gpio;
  conf->side = side;
  conf->num = num;
  memset(conf->power_key, 0, sizeof(conf->power_key));
  sprintf(conf->power_key, "LED_%d_%d_PWR", side, num);
  xTaskCreate(led_task, "Led task", 2048, conf, 10, NULL);
}

void init_led() {
  printf("Initializing led task\n");

  ledc_timer_config_t ledc_timer = {
    speed_mode:       LEDC_LOW_SPEED_MODE,
    { duty_resolution:  LEDC_TIMER_13_BIT, },
    timer_num:        LEDC_TIMER_1,
    freq_hz:          120,
  };
  ledc_timer_config(&ledc_timer);

  ledc_fade_func_install(0);

  seti("LED_0_0_PWR", 50);
  seti("LED_1_0_PWR", 50);

  seti("LED_0_1_PWR", 75);
  seti("LED_1_1_PWR", 75);

  start_led_task(LEDC_LS_CH0_CHANNEL, LEDC_LS_CH0_GPIO, 0, 0);
  start_led_task(LEDC_LS_CH1_CHANNEL, LEDC_LS_CH1_GPIO, 0, 1);
  start_led_task(LEDC_LS_CH2_CHANNEL, LEDC_LS_CH2_GPIO, 0, 2);

  start_led_task(LEDC_LS_CH3_CHANNEL, LEDC_LS_CH3_GPIO, 1, 0);
  start_led_task(LEDC_LS_CH4_CHANNEL, LEDC_LS_CH4_GPIO, 1, 1);
  start_led_task(LEDC_LS_CH5_CHANNEL, LEDC_LS_CH5_GPIO, 1, 2);
}
