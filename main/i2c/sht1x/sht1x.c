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

#include "../../log/log.h"
#include "sht1x.h"
#include "sht1x_driver.h"
#include "../i2c.h"
#include "../../kv/kv.h"

#define SHT1X_TEMP_C "SHT1X_C"
#define SHT1X_TEMP_F "SHT1X_F"
#define SHT1X_HUMI "SHT1X_HU"

void init_sht1x() {
  defaulti(SHT1X_TEMP_C, -1);
  defaulti(SHT1X_TEMP_F, -1);
  defaulti(SHT1X_HUMI, -1);
}

void read_sht1x(int sda, int sck) {
  esp_log_level_set("gpio", ESP_LOG_NONE);
  stop_i2c();
  float temp_c = read_temperature_c(sda, sck);
  float temp_f = read_temperature_f(sda, sck);
  float humi = read_humidity(sda, sck);
  seti(SHT1X_TEMP_C, temp_c);
  seti(SHT1X_TEMP_F, temp_f);
  seti(SHT1X_HUMI, humi);
  release_gpios(sda, sck);
}
