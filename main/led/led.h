/*
 * =====================================================================================
 *
 *       Filename:  led.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/16/2018 14:52:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef LED_H_
#define LED_H_

#include "esp_gatt_common_api.h"

#define LED_SIDES 2
#define LED_PER_SIDES 3
#define LED_MIN_DUTY           (550)
#define LED_MAX_DUTY           (8191)

#define LED_PWR(side, n) LED_##side##_##n##_PWR
#define LED_DUTY(side, n) LED_##side##_##n##_DUTY

#define LED_0_0_PWR "LED_0_0_PWR"
#define LED_0_1_PWR "LED_0_1_PWR"
#define LED_0_2_PWR "LED_0_2_PWR"
#define LED_1_0_PWR "LED_1_0_PWR"
#define LED_1_1_PWR "LED_1_1_PWR"
#define LED_1_2_PWR "LED_1_2_PWR"

#define LED_0_0_DUTY "LED_0_0_DUTY"
#define LED_0_1_DUTY "LED_0_1_DUTY"
#define LED_0_2_DUTY "LED_0_2_DUTY"
#define LED_1_0_DUTY "LED_1_0_DUTY"
#define LED_1_1_DUTY "LED_1_1_DUTY"
#define LED_1_2_DUTY "LED_1_2_DUTY"

extern const uint8_t LED_0_0_PWR_UUID[ESP_UUID_LEN_128];
extern const uint8_t LED_0_1_PWR_UUID[ESP_UUID_LEN_128];
extern const uint8_t LED_0_2_PWR_UUID[ESP_UUID_LEN_128];
extern const uint8_t LED_1_0_PWR_UUID[ESP_UUID_LEN_128];
extern const uint8_t LED_1_1_PWR_UUID[ESP_UUID_LEN_128];
extern const uint8_t LED_1_2_PWR_UUID[ESP_UUID_LEN_128];

extern const uint8_t LED_0_0_DUTY_UUID[ESP_UUID_LEN_128];
extern const uint8_t LED_0_1_DUTY_UUID[ESP_UUID_LEN_128];
extern const uint8_t LED_0_2_DUTY_UUID[ESP_UUID_LEN_128];
extern const uint8_t LED_1_0_DUTY_UUID[ESP_UUID_LEN_128];
extern const uint8_t LED_1_1_DUTY_UUID[ESP_UUID_LEN_128];
extern const uint8_t LED_1_2_DUTY_UUID[ESP_UUID_LEN_128];

void init_led();
void refresh_led();

#endif
