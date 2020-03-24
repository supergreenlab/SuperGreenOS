/*
 * Copyright (C) 2020  SuperGreenLab <towelie@supergreenlab.com>
 * Author: Constantin Clauzel <constantin.clauzel@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdlib.h>
#include <stdbool.h>

#include "../core/log/log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "sht1x_driver.h"

void shift_out(int sda, int scl, unsigned char c);

// Init functions

void setup_gpios(int sda, int scl, bool input) {
	gpio_config_t scl_conf;
	scl_conf.intr_type = GPIO_PIN_INTR_DISABLE;
	scl_conf.mode = GPIO_MODE_OUTPUT;
	scl_conf.pin_bit_mask = (1ULL << scl);
	scl_conf.pull_down_en = 0;
	scl_conf.pull_up_en = 0;
	gpio_config(&scl_conf);

	gpio_config_t sda_conf;
	sda_conf.intr_type = GPIO_PIN_INTR_DISABLE;
	sda_conf.mode = (input ? GPIO_MODE_INPUT : GPIO_MODE_OUTPUT);
	sda_conf.pin_bit_mask = (1ULL << sda);
	sda_conf.pull_down_en = 0;
	sda_conf.pull_up_en = input;
	gpio_config(&sda_conf);
}

void release_gpios(int sda, int scl) {
  gpio_reset_pin(sda);
  gpio_reset_pin(scl);
}

// Reading functions

float read_temperature_c(int sda, int scl)
{
  int val;
  float temperature;

  const float D1 = -40.0;
  const float D2 = 0.01;

  val = read_temperature_raw(sda, scl);

  temperature = (val * D2) + D1;

  return (temperature);
}

float read_temperature_f(int sda, int scl)
{
  int val;
  float temperature;

  const float D1 = -40.0; // for 14 Bit @ 5V
  const float D2 = 0.018; // for 14 Bit DEGF

  val = read_temperature_raw(sda, scl);

  temperature = (val * D2) + D1;

  return (temperature);
}

float read_humidity(int sda, int scl)
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

  sendcommand_SHT(g_humid_cmd, sda, scl);
  wait_for_result_SHT(sda, scl);
  val = get_data16SHT(sda, scl);
  skip_crc_SHT(sda, scl);

  linear_humidity = C1 + C2 * val + C3 * val * val;

  temperature = read_temperature_c(sda, scl);

  corrected_humidity = (temperature - 25.0 ) * (T1 + T2 * val) + linear_humidity;

  return (corrected_humidity);
}

// Hardware communications

float read_temperature_raw(int sda, int scl)
{
  int val;

  int g_temp_cmd  = 0b00000011;

  sendcommand_SHT(g_temp_cmd, sda, scl);
  wait_for_result_SHT(sda, scl);
  val = get_data16SHT(sda, scl);
  skip_crc_SHT(sda, scl);

  return (val);
}

void sendcommand_SHT(int command, int sda, int scl)
{
  int ack;

	setup_gpios(sda, scl, false);
  gpio_set_level(sda, 1);
  gpio_set_level(scl, 1);
  gpio_set_level(sda, 0);
  gpio_set_level(scl, 0);
  gpio_set_level(scl, 1);
  gpio_set_level(sda, 1);
  gpio_set_level(scl, 0);

  // The command (3 msb are address and must be 000, and last 5 bits are command)
  shift_out(sda, scl, command);

  // Verify we get the correct ack
  gpio_set_level(scl, 1);
  setup_gpios(sda, scl, true);
  ack = gpio_get_level(sda);
  if (ack != 0) {
    //ESP_LOGI(SGO_LOG_NOSEND, "SHT1X Ack Error 0 (sda: %d scl: %d)", sda, scl);
    return;
  }
  gpio_set_level(scl, 0);
  ack = gpio_get_level(sda);
  if (ack != 1) {
    //ESP_LOGI(SGO_LOG_NOSEND, "Ack Error 1 (sda: %d scl: %d)", sda, scl);
    return;
  }
}

/**
 */
void wait_for_result_SHT(int sda, int scl)
{
  int i;
  int ack;

  setup_gpios(sda, scl, true);

  for(i= 0; i < 100; ++i)
  {
    vTaskDelay(10 / portTICK_PERIOD_MS);
    ack = gpio_get_level(sda);

    if (ack == 0) {
      break;
    }
  }

  if (ack == 1) {
    //ESP_LOGI(SGO_LOG_NOSEND, "Ack Error 2 (sda: %d scl: %d)", sda, scl);
  }
}

int get_data16SHT(int sda, int scl)
{
  int val;

  setup_gpios(sda, scl, true);
  val = shift_in(sda, scl, 8);
  val *= 256;

  setup_gpios(sda, scl, false);
  gpio_set_level(sda, 1);
  gpio_set_level(sda, 0);
  gpio_set_level(scl, 1);
  gpio_set_level(scl, 0);

  setup_gpios(sda, scl, true);
  val |= shift_in(sda, scl, 8);

  return val;
}

void skip_crc_SHT(int sda, int scl)
{
  setup_gpios(sda, scl, false);

  gpio_set_level(sda, 1);
  gpio_set_level(scl, 1);
  gpio_set_level(scl, 0);
}

// utils

int shift_in(int sda, int scl, int num_bits)
{
  int ret = 0;
  int i;

  for (i = 0; i < num_bits; ++i)
  {
     gpio_set_level(scl, 1);
     vTaskDelay(10 / portTICK_PERIOD_MS);
     ret = ret * 2 + gpio_get_level(sda);
     gpio_set_level(scl, 0);
  }

  return(ret);
}

void shift_out(int sda, int scl, uint8_t val) {
  int i;

  for(i = 0; i < 8; i++) {
    gpio_set_level(sda, !!(val & (1 << (7 - i))));
    gpio_set_level(scl, 1);
    gpio_set_level(scl, 0);
  }
}
