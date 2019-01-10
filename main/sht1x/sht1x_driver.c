/*
 * =====================================================================================
 *
 *       Filename:  sht1x_driver.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/18/2018 04:55:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdbool.h>

#include "../core/log/log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "sht1x_driver.h"

void shift_out(int sda, int sck, unsigned char c);

// Init functions

void setup_gpios(int sda, int sck, bool input) {
	gpio_config_t sck_conf;
	sck_conf.intr_type = GPIO_PIN_INTR_DISABLE;
	sck_conf.mode = GPIO_MODE_OUTPUT;
	sck_conf.pin_bit_mask = (1ULL << sck);
	sck_conf.pull_down_en = 0;
	sck_conf.pull_up_en = 0;
	gpio_config(&sck_conf);

	gpio_config_t sda_conf;
	sda_conf.intr_type = GPIO_PIN_INTR_DISABLE;
	sda_conf.mode = (input ? GPIO_MODE_INPUT : GPIO_MODE_OUTPUT);
	sda_conf.pin_bit_mask = (1ULL << sda);
	sda_conf.pull_down_en = 0;
	sda_conf.pull_up_en = input;
	gpio_config(&sda_conf);
}

void release_gpios(int sda, int sck) {
  gpio_reset_pin(sda);
  gpio_reset_pin(sck);
}

// Reading functions

float read_temperature_c(int sda, int sck)
{
  int val;
  float temperature;

  const float D1 = -40.0;
  const float D2 = 0.01;

  val = read_temperature_raw(sda, sck);

  temperature = (val * D2) + D1;

  return (temperature);
}

float read_temperature_f(int sda, int sck)
{
  int val;
  float temperature;

  const float D1 = -40.0; // for 14 Bit @ 5V
  const float D2 = 0.018; // for 14 Bit DEGF

  val = read_temperature_raw(sda, sck);

  temperature = (val * D2) + D1;

  return (temperature);
}

float read_humidity(int sda, int sck)
{
  int val;
  float linear_humidity;
  float corrected_humidity;
  float temperature;

  const float C1 = -4.0;       // for 12 Bit
  const float C2 =  0.0405;    // for 12 Bit
  const float C3 = -0.0000028; // for 12 Bit
  const float T1 =  0.01;      // for 14 Bit @ 5V
  const float T2 =  0.00008;   // for 14 Bit @ 5V

  int g_humid_cmd = 0b00000101;

  sendcommand_SHT(g_humid_cmd, sda, sck);
  wait_for_result_SHT(sda, sck);
  val = get_data16SHT(sda, sck);
  skip_crc_SHT(sda, sck);

  linear_humidity = C1 + C2 * val + C3 * val * val;

  temperature = read_temperature_c(sda, sck);

  corrected_humidity = (temperature - 25.0 ) * (T1 + T2 * val) + linear_humidity;

  return (corrected_humidity);
}

// Hardware communications

float read_temperature_raw(int sda, int sck)
{
  int val;

  int g_temp_cmd  = 0b00000011;

  sendcommand_SHT(g_temp_cmd, sda, sck);
  wait_for_result_SHT(sda, sck);
  val = get_data16SHT(sda, sck);
  skip_crc_SHT(sda, sck);

  return (val);
}

void sendcommand_SHT(int command, int sda, int sck)
{
  int ack;

	setup_gpios(sda, sck, false);
  gpio_set_level(sda, 1);
  gpio_set_level(sck, 1);
  gpio_set_level(sda, 0);
  gpio_set_level(sck, 0);
  gpio_set_level(sck, 1);
  gpio_set_level(sda, 1);
  gpio_set_level(sck, 0);

  // The command (3 msb are address and must be 000, and last 5 bits are command)
  shift_out(sda, sck, command);

  // Verify we get the correct ack
  gpio_set_level(sck, 1);
  setup_gpios(sda, sck, true);
  ack = gpio_get_level(sda);
  if (ack != 0) {
    ESP_LOGI(SGO_LOG_NOSEND, "Ack Error 0");
  }
  gpio_set_level(sck, 0);
  ack = gpio_get_level(sda);
  if (ack != 1) {
    ESP_LOGI(SGO_LOG_NOSEND, "Ack Error 1");
  }
}

/**
 */
void wait_for_result_SHT(int sda, int sck)
{
  int i;
  int ack;

  setup_gpios(sda, sck, true);

  for(i= 0; i < 100; ++i)
  {
    vTaskDelay(10 / portTICK_PERIOD_MS);
    ack = gpio_get_level(sda);

    if (ack == 0) {
      break;
    }
  }

  if (ack == 1) {
    ESP_LOGI(SGO_LOG_NOSEND, "Ack Error 2");
  }
}

int get_data16SHT(int sda, int sck)
{
  int val;

  setup_gpios(sda, sck, true);
  val = shift_in(sda, sck, 8);
  val *= 256;

  setup_gpios(sda, sck, false);
  gpio_set_level(sda, 1);
  gpio_set_level(sda, 0);
  gpio_set_level(sck, 1);
  gpio_set_level(sck, 0);

  setup_gpios(sda, sck, true);
  val |= shift_in(sda, sck, 8);

  return val;
}

void skip_crc_SHT(int sda, int sck)
{
  setup_gpios(sda, sck, false);

  gpio_set_level(sda, 1);
  gpio_set_level(sck, 1);
  gpio_set_level(sck, 0);
}

// utils

int shift_in(int sda, int sck, int num_bits)
{
  int ret = 0;
  int i;

  for (i = 0; i < num_bits; ++i)
  {
     gpio_set_level(sck, 1);
     vTaskDelay(10 / portTICK_PERIOD_MS);
     ret = ret * 2 + gpio_get_level(sda);
     gpio_set_level(sck, 0);
  }

  return(ret);
}

void shift_out(int sda, int sck, uint8_t val) {
  int i;

  for(i = 0; i < 8; i++) {
    gpio_set_level(sda, !!(val & (1 << (7 - i))));
    gpio_set_level(sck, 1);
    gpio_set_level(sck, 0);
  }
}
