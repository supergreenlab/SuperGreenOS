/*
 * =====================================================================================
 *
 *       Filename:  httpd_kv_handlers.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/14/2018 11:24:27 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string.h>

#include "../kv/kv_helpers_internal.h"
#include "httpd_kv_handlers.h"
#include "../include_modules.h"

const kvi_handler kvi_handlers[] = {
/*
* [GENERATED]
*/
  
  {
    .name = "TIME",
    .nvs_key = "TIME",
    .handler = internal_set_time,
  },
  {
    .name = "OTA_TIMESTAMP",
    .nvs_key = "OTA_TMSTP",
    .handler = internal_set_ota_timestamp,
  },
  {
    .name = "I2C_SDA",
    .nvs_key = "I2C_SDA",
    .handler = internal_set_i2c_sda,
  },
  {
    .name = "I2C_SCL",
    .nvs_key = "I2C_SCL",
    .handler = internal_set_i2c_scl,
  },
  {
    .name = "STATE",
    .nvs_key = "STATE",
    .handler = internal_set_state,
  },
  {
    .name = "TIMER_TYPE",
    .nvs_key = "TIMER_T",
    .handler = internal_set_timer_type,
  },
  {
    .name = "STARTED_AT",
    .nvs_key = "ST_AT",
    .handler = internal_set_started_at,
  },
  {
    .name = "ON_HOUR",
    .nvs_key = "ON_H",
    .handler = internal_set_on_hour,
  },
  {
    .name = "ON_MIN",
    .nvs_key = "ON_M",
    .handler = internal_set_on_min,
  },
  {
    .name = "OFF_HOUR",
    .nvs_key = "OFF_H",
    .handler = internal_set_off_hour,
  },
  {
    .name = "OFF_MIN",
    .nvs_key = "OFF_M",
    .handler = internal_set_off_min,
  },
  {
    .name = "STRETCH",
    .nvs_key = "STRETCH",
    .handler = internal_set_stretch,
  },
  {
    .name = "LED_DIM",
    .nvs_key = "LED_DIM",
    .handler = internal_set_led_dim,
  },
  {
    .name = "BLOWER",
    .nvs_key = "BLWR",
    .handler = internal_set_blower,
  },
  {
    .name = "BLOWER_GPIO",
    .nvs_key = "BLWR_IO",
    .handler = internal_set_blower_gpio,
  },
  {
    .name = "LED_0_DUTY",
    .nvs_key = "L_0_D",
    .handler = internal_set_led_0_duty,
  },
  {
    .name = "LED_1_DUTY",
    .nvs_key = "L_1_D",
    .handler = internal_set_led_1_duty,
  },
  {
    .name = "LED_2_DUTY",
    .nvs_key = "L_2_D",
    .handler = internal_set_led_2_duty,
  },
  {
    .name = "LED_3_DUTY",
    .nvs_key = "L_3_D",
    .handler = internal_set_led_3_duty,
  },
  {
    .name = "LED_4_DUTY",
    .nvs_key = "L_4_D",
    .handler = internal_set_led_4_duty,
  },
  {
    .name = "LED_5_DUTY",
    .nvs_key = "L_5_D",
    .handler = internal_set_led_5_duty,
  },
  {
    .name = "LED_0_GPIO",
    .nvs_key = "L_0_IO",
    .handler = internal_set_led_0_gpio,
  },
  {
    .name = "LED_1_GPIO",
    .nvs_key = "L_1_IO",
    .handler = internal_set_led_1_gpio,
  },
  {
    .name = "LED_2_GPIO",
    .nvs_key = "L_2_IO",
    .handler = internal_set_led_2_gpio,
  },
  {
    .name = "LED_3_GPIO",
    .nvs_key = "L_3_IO",
    .handler = internal_set_led_3_gpio,
  },
  {
    .name = "LED_4_GPIO",
    .nvs_key = "L_4_IO",
    .handler = internal_set_led_4_gpio,
  },
  {
    .name = "LED_5_GPIO",
    .nvs_key = "L_5_IO",
    .handler = internal_set_led_5_gpio,
  },
  {
    .name = "LED_0_X",
    .nvs_key = "L_0_X",
    .handler = internal_set_led_0_x,
  },
  {
    .name = "LED_1_X",
    .nvs_key = "L_1_X",
    .handler = internal_set_led_1_x,
  },
  {
    .name = "LED_2_X",
    .nvs_key = "L_2_X",
    .handler = internal_set_led_2_x,
  },
  {
    .name = "LED_3_X",
    .nvs_key = "L_3_X",
    .handler = internal_set_led_3_x,
  },
  {
    .name = "LED_4_X",
    .nvs_key = "L_4_X",
    .handler = internal_set_led_4_x,
  },
  {
    .name = "LED_5_X",
    .nvs_key = "L_5_X",
    .handler = internal_set_led_5_x,
  },
  {
    .name = "LED_0_Y",
    .nvs_key = "L_0_Y",
    .handler = internal_set_led_0_y,
  },
  {
    .name = "LED_1_Y",
    .nvs_key = "L_1_Y",
    .handler = internal_set_led_1_y,
  },
  {
    .name = "LED_2_Y",
    .nvs_key = "L_2_Y",
    .handler = internal_set_led_2_y,
  },
  {
    .name = "LED_3_Y",
    .nvs_key = "L_3_Y",
    .handler = internal_set_led_3_y,
  },
  {
    .name = "LED_4_Y",
    .nvs_key = "L_4_Y",
    .handler = internal_set_led_4_y,
  },
  {
    .name = "LED_5_Y",
    .nvs_key = "L_5_Y",
    .handler = internal_set_led_5_y,
  },
  {
    .name = "LED_0_Z",
    .nvs_key = "L_0_Z",
    .handler = internal_set_led_0_z,
  },
  {
    .name = "LED_1_Z",
    .nvs_key = "L_1_Z",
    .handler = internal_set_led_1_z,
  },
  {
    .name = "LED_2_Z",
    .nvs_key = "L_2_Z",
    .handler = internal_set_led_2_z,
  },
  {
    .name = "LED_3_Z",
    .nvs_key = "L_3_Z",
    .handler = internal_set_led_3_z,
  },
  {
    .name = "LED_4_Z",
    .nvs_key = "L_4_Z",
    .handler = internal_set_led_4_z,
  },
  {
    .name = "LED_5_Z",
    .nvs_key = "L_5_Z",
    .handler = internal_set_led_5_z,
  },

/*
* [/GENERATED]
*/
  {
    .name = NULL,
    .handler = NULL,
  },
};

const kvi_handler *get_kvi_handler(const char *name) {
  for (int i = 0; kvi_handlers[i].name != NULL; ++i) {
    if (strcmp(kvi_handlers[i].name, name) == 0) {
      return &kvi_handlers[i];
    }
  }
  return NULL;
}

const kvs_handler kvs_handlers[] = {
/*
* [GENERATED]
*/

  {
    .name = "WIFI_SSID",
    .nvs_key = "WSSID",
    .handler = internal_set_wifi_ssid,
  },
  {
    .name = "WIFI_PASSWORD",
    .nvs_key = "WPASS",
    .handler = internal_set_wifi_password,
  },
  {
    .name = "OTA_SERVER_IP",
    .nvs_key = "OTA_SRV_IP",
    .handler = internal_set_ota_server_ip,
  },
  {
    .name = "OTA_SERVER_HOSTNAME",
    .nvs_key = "OTA_SRV_HN",
    .handler = internal_set_ota_server_hostname,
  },
  {
    .name = "OTA_SERVER_PORT",
    .nvs_key = "OTA_SRV_PRT",
    .handler = internal_set_ota_server_port,
  },
  {
    .name = "OTA_VERSION_FILENAME",
    .nvs_key = "OTA_VR_FILE",
    .handler = internal_set_ota_version_filename,
  },
  {
    .name = "OTA_FILENAME",
    .nvs_key = "OTA_FILE",
    .handler = internal_set_ota_filename,
  },
  {
    .name = "OTA",
    .nvs_key = "OTA_SRV_IP",
    .handler = internal_set_mqtt_broker_url,
  },
  {
    .name = "BROKER_URL",
    .nvs_key = "BRKR_URL",
    .handler = internal_set_broker_url,
  },
  {
    .name = "DEVICE_NAME",
    .nvs_key = "DEV_NAME",
    .handler = internal_set_device_name,
  },
  {
    .name = "LED_INFO",
    .nvs_key = NULL,
  },

/*
* [/GENERATED]
*/
  {
    .name = NULL,
    .handler = NULL,
  }
};

const kvs_handler *get_kvs_handler(const char *name) {
  for (int i = 0; kvs_handlers[i].name != NULL; ++i) {
    if (strcmp(kvs_handlers[i].name, name) == 0) {
      return &kvs_handlers[i];
    }
  }
  return NULL;
}
