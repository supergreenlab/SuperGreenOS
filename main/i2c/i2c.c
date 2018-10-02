/*
 * Copyright (C) 2018  SuperGreenLab <towelie@supergreenlab.com>
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
#include "driver/i2c.h"

#define MASTER_SCL_IO 27
#define MASTER_SDA_IO 26
#define MASTER_TX_BUF_DISABLE  0
#define MASTER_RX_BUF_DISABLE  0
#define MASTER_FREQ_HZ         100000

static void print_scan() {
  int i;
  esp_err_t espRc;
  ESP_LOGI(LOG_NOSEND, "     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
  ESP_LOGI(LOG_NOSEND, "00:         ");
  for (i=3; i< 0x78; i++) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (i << 1) | I2C_MASTER_WRITE, 1 /* expect ack */);
    i2c_master_stop(cmd);

    espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
    if (i%16 == 0) {
      ESP_LOGI(LOG_NOSEND, "\n%.2x:", i);
    }
    if (espRc == 0) {
      ESP_LOGI(LOG_NOSEND, " %.2x", i);
    } else {
      ESP_LOGI(LOG_NOSEND, " --");
    }
    i2c_cmd_link_delete(cmd);
  }
  ESP_LOGI(LOG_NOSEND, "\n");
}

void i2c_task(void *param) {
  while(true) {
    print_scan();
    vTaskDelay(2000 / portTICK_RATE_MS);
  }
}

void init_i2c() {
  i2c_config_t conf;
  conf.mode = I2C_MODE_MASTER;
  conf.sda_io_num = MASTER_SDA_IO;
  conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
  conf.scl_io_num = MASTER_SCL_IO;
  conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
  conf.master.clk_speed = MASTER_FREQ_HZ;
  i2c_param_config(I2C_NUM_0, &conf);
  i2c_driver_install(I2C_NUM_0, conf.mode,
      MASTER_RX_BUF_DISABLE,
      MASTER_TX_BUF_DISABLE, 0);

  xTaskCreate(i2c_task, "i2c", 1024 * 2, NULL, 10, NULL);
}
