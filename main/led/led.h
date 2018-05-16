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

#endif
