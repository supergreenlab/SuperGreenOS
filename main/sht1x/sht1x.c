/*
 * =====================================================================================
 *
 *       Filename:  sht1x.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/17/2018 05:47:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "../core/log/log.h"
#include "sht1x.h"
#include "sht1x_driver.h"
#include "../core/i2c/i2c.h"
#include "../core/kv/kv.h"
#include "../box/box.h"

void init_sht1x(int portId, int sda, int sdk) {
  int boxId = portId;

  ESP_LOGI(SGO_LOG_EVENT, "@SHT1X_%d Initializing sht1x pseudo i2c device", boxId);
}

void loop_sht1x(int portId, int sda, int sck) {
  int boxId = portId;

  esp_log_level_set("gpio", ESP_LOG_NONE);
  stop_i2c(portId);
  float temp_c = read_temperature_c(sda, sck);
  float temp_f = read_temperature_f(sda, sck);
  float humi = read_humidity(sda, sck);
  set_box_sht1x_temp_c(boxId, temp_c);
  set_box_sht1x_temp_f(boxId, temp_f);
  set_box_sht1x_humi(boxId, humi);

  ESP_LOGI(SGO_LOG_METRIC, "@SHT1X_%d temp_c=%f, temp_f=%f, humi=%f", boxId, temp_c, temp_f, humi);

  release_gpios(sda, sck);
}
