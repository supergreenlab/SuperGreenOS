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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "sht1x_driver.h"

void shift_out(int sda, int sck, unsigned char c);

// Init functions

void setup_gpios(int sda, int sck) {
	gpio_config_t io_conf;
	io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
	io_conf.mode = GPIO_MODE_OUTPUT;
	io_conf.pin_bit_mask = (1ULL << sck);
	io_conf.pull_down_en = 0;
	io_conf.pull_up_en = 0;
	gpio_config(&io_conf);

  set_sda_mode(sda, false);
}

void release_gpios(int sda, int sck) {
  gpio_reset_pin(sda);
  gpio_reset_pin(sck);
}

void set_sda_mode(int sda, bool input) {
	gpio_config_t io_conf;
	io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
	io_conf.mode = (input ? GPIO_MODE_INPUT : GPIO_MODE_OUTPUT);
	io_conf.pin_bit_mask = (1ULL << sda);
	io_conf.pull_down_en = 0;
	io_conf.pull_up_en = 0;
	gpio_config(&io_conf);
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

  const float D1 = -40.0;   // for 14 Bit @ 5V
  const float D2 =   0.018; // for 14 Bit DEGF

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
  wait_for_result_SHT(sda);
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
  wait_for_result_SHT(sda);
  val = get_data16SHT(sda, sck);
  skip_crc_SHT(sda, sck);

  return (val);
}

void sendcommand_SHT(int command, int sda, int sck)
{
  int ack;

	set_sda_mode(sda, false);
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
  set_sda_mode(sda, true);
  ack = gpio_get_level(sda);
  if (ack != 0) {
    //Serial.println("Ack Error 0");
  }
  gpio_set_level(sck, 0);
  ack = gpio_get_level(sda);
  if (ack != 1) {
    //Serial.println("Ack Error 1");
  }
}

/**
 */
void wait_for_result_SHT(int sda)
{
  int i;
  int ack;

  set_sda_mode(sda, true);

  for(i= 0; i < 100; ++i)
  {
    vTaskDelay(1/portTICK_PERIOD_MS * 10);
    ack = gpio_get_level(sda);

    if (ack == 0) {
      break;
    }
  }

  if (ack == 1) {
    //Serial.println("Ack Error 2"); // Can't do serial stuff here, need another way of reporting errors
  }
}

int get_data16SHT(int sda, int sck)
{
  int val;

  set_sda_mode(sda, true);
  val = shift_in(sda, sck, 8);
  val *= 256;

  set_sda_mode(sda, false);
  gpio_set_level(sda, 1);
  gpio_set_level(sda, 0);
  gpio_set_level(sck, 1);
  gpio_set_level(sck, 0);

  set_sda_mode(sda, true);
  val |= shift_in(sda, sck, 8);

  return val;
}

void skip_crc_SHT(int sda, int sck)
{
  set_sda_mode(sda, false);

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
     vTaskDelay(1 / portTICK_PERIOD_MS * 10);
     ret = ret * 2 + gpio_get_level(sda);
     gpio_set_level(sck, 0);
  }

  return(ret);
}

void shift_out(int sda, int sck, unsigned char c) {
  int i=0;
  int pin;
  set_sda_mode(sda, false);

  gpio_set_level(sda, 0);
  gpio_set_level(sck, 0);

  for (i=0; i<=7; i++)  {
    gpio_set_level(sck, 0);

		pin = c & (1 << i);
    gpio_set_level(sda, pin);
    gpio_set_level(sck, 1);
    gpio_set_level(sda, 0);
  }

  //stop shifting
  gpio_set_level(sck, 0);
}
