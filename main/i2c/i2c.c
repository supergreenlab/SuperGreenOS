/*
 * =====================================================================================
 *
 *       Filename:  i2c.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/14/2018 12:40:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "driver/i2c.h"

#define MASTER_SCL_IO 27
#define MASTER_SDA_IO 26
#define MASTER_TX_BUF_DISABLE  0
#define MASTER_RX_BUF_DISABLE  0
#define MASTER_FREQ_HZ         100000

void i2c_task(void *param) {
  while(true) {
    int i;
    esp_err_t espRc;
    printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
    printf("00:         ");
    for (i=3; i< 0x78; i++) {
      i2c_cmd_handle_t cmd = i2c_cmd_link_create();
      i2c_master_start(cmd);
      i2c_master_write_byte(cmd, (i << 1) | I2C_MASTER_WRITE, 1 /* expect ack */);
      i2c_master_stop(cmd);

      espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
      if (i%16 == 0) {
        printf("\n%.2x:", i);
      }
      if (espRc == 0) {
        printf(" %.2x", i);
      } else {
        printf(" --");
      }
      //ESP_LOGD(tag, "i=%d, rc=%d (0x%x)", i, espRc, espRc);
      i2c_cmd_link_delete(cmd);
    }
    printf("\n");
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

  xTaskCreate(i2c_task, "i2c_test_task_1", 1024 * 2, NULL, 10, NULL);
}
