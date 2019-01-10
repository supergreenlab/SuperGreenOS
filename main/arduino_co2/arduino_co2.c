/*
 * =====================================================================================
 *
 *       Filename:  arduino_co2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/29/2018 06:40:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "arduino_co2.h"
#include "driver/i2c.h"

#include "../core/log/log.h"
#include "../core/i2c/i2c.h"

#define ARDUINO_CO2_ADDR 0x42
#define ACK_CHECK_EN 0x1
#define ACK_VAL 0x0
#define NACK_VAL 0x1

void init_arduino_co2(int sca, int sdk) {

}

void loop_arduino_co2(int sda, int sck) {
  uint16_t v = 0;
	uint8_t nack;
  start_i2c();
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, ARDUINO_CO2_ADDR << 1 | I2C_MASTER_READ, ACK_CHECK_EN);

  i2c_master_read(cmd, (uint8_t*)&v, sizeof(v), ACK_VAL);
	i2c_master_read_byte(cmd, &nack, NACK_VAL);

	i2c_master_stop(cmd);

	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);

	if (ret == ESP_ERR_TIMEOUT) {
		ESP_LOGI(SGO_LOG_NOSEND, "@ARDUINO_CO2 Bus is busy");
	} else if (ret != ESP_OK) {
		ESP_LOGI(SGO_LOG_NOSEND, "@ARDUINO_CO2 Read failed");
	}
	ESP_LOGI(SGO_LOG_METRIC, "@ARDUINO_CO2 co2=%d", v);

  stop_i2c();
}
