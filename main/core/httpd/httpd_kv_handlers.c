/*
 * Copyright (C) 2019  SuperGreenLab <towelie@supergreenlab.com>
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
#include <string.h>

#include "../kv/kv.h"
#include "../kv/kv_helpers_internal.h"
#include "httpd_kv_handlers.h"
#include "../include_modules.h"

const kvi_handler kvi_handlers[] = {
/*
* [GENERATED]
*/
  
  {
    .name = "WIFI_STATUS",
    .handler = NULL,
    .getter = get_wifi_status,
  },
  {
    .name = "TIME",
    .handler = internal_set_time,
    .getter = get_time,
  },
  {
    .name = "N_RESTARTS",
    .handler = NULL,
    .getter = get_n_restarts,
  },
  {
    .name = "OTA_TIMESTAMP",
    .handler = internal_set_ota_timestamp,
    .getter = get_ota_timestamp,
  },
  {
    .name = "I2C_SDA",
    .handler = internal_set_i2c_sda,
    .getter = get_i2c_sda,
  },
  {
    .name = "I2C_SCL",
    .handler = internal_set_i2c_scl,
    .getter = get_i2c_scl,
  },
  {
    .name = "STATE",
    .handler = internal_set_state,
    .getter = get_state,
  },
  {
    .name = "TIMER_TYPE",
    .handler = internal_set_timer_type,
    .getter = get_timer_type,
  },
  {
    .name = "TIMER_OUTPUT",
    .handler = NULL,
    .getter = get_timer_output,
  },
  {
    .name = "STARTED_AT",
    .handler = internal_set_started_at,
    .getter = get_started_at,
  },
  {
    .name = "ON_HOUR",
    .handler = internal_set_on_hour,
    .getter = get_on_hour,
  },
  {
    .name = "ON_MIN",
    .handler = internal_set_on_min,
    .getter = get_on_min,
  },
  {
    .name = "OFF_HOUR",
    .handler = internal_set_off_hour,
    .getter = get_off_hour,
  },
  {
    .name = "OFF_MIN",
    .handler = internal_set_off_min,
    .getter = get_off_min,
  },
  {
    .name = "STRETCH",
    .handler = internal_set_stretch,
    .getter = get_stretch,
  },
  {
    .name = "LED_DIM",
    .handler = internal_set_led_dim,
    .getter = get_led_dim,
  },
  {
    .name = "BLOWER",
    .handler = internal_set_blower,
    .getter = get_blower,
  },
  {
    .name = "BLOWER_MODE",
    .handler = internal_set_blower_mode,
    .getter = get_blower_mode,
  },
  {
    .name = "BLOWER_GPIO",
    .handler = internal_set_blower_gpio,
    .getter = get_blower_gpio,
  },
  {
    .name = "SHT1X_TEMP_C",
    .handler = NULL,
    .getter = get_sht1x_temp_c,
  },
  {
    .name = "SHT1X_TEMP_F",
    .handler = NULL,
    .getter = get_sht1x_temp_f,
  },
  {
    .name = "SHT1X_HUMI",
    .handler = NULL,
    .getter = get_sht1x_humi,
  },
  {
    .name = "LED_0_DUTY",
    .handler = internal_set_led_0_duty,
    .getter = get_led_0_duty,
  },
  {
    .name = "LED_1_DUTY",
    .handler = internal_set_led_1_duty,
    .getter = get_led_1_duty,
  },
  {
    .name = "LED_2_DUTY",
    .handler = internal_set_led_2_duty,
    .getter = get_led_2_duty,
  },
  {
    .name = "LED_3_DUTY",
    .handler = internal_set_led_3_duty,
    .getter = get_led_3_duty,
  },
  {
    .name = "LED_4_DUTY",
    .handler = internal_set_led_4_duty,
    .getter = get_led_4_duty,
  },
  {
    .name = "LED_5_DUTY",
    .handler = internal_set_led_5_duty,
    .getter = get_led_5_duty,
  },
  {
    .name = "LED_0_GPIO",
    .handler = internal_set_led_0_gpio,
    .getter = get_led_0_gpio,
  },
  {
    .name = "LED_1_GPIO",
    .handler = internal_set_led_1_gpio,
    .getter = get_led_1_gpio,
  },
  {
    .name = "LED_2_GPIO",
    .handler = internal_set_led_2_gpio,
    .getter = get_led_2_gpio,
  },
  {
    .name = "LED_3_GPIO",
    .handler = internal_set_led_3_gpio,
    .getter = get_led_3_gpio,
  },
  {
    .name = "LED_4_GPIO",
    .handler = internal_set_led_4_gpio,
    .getter = get_led_4_gpio,
  },
  {
    .name = "LED_5_GPIO",
    .handler = internal_set_led_5_gpio,
    .getter = get_led_5_gpio,
  },
  {
    .name = "LED_0_X",
    .handler = internal_set_led_0_x,
    .getter = get_led_0_x,
  },
  {
    .name = "LED_1_X",
    .handler = internal_set_led_1_x,
    .getter = get_led_1_x,
  },
  {
    .name = "LED_2_X",
    .handler = internal_set_led_2_x,
    .getter = get_led_2_x,
  },
  {
    .name = "LED_3_X",
    .handler = internal_set_led_3_x,
    .getter = get_led_3_x,
  },
  {
    .name = "LED_4_X",
    .handler = internal_set_led_4_x,
    .getter = get_led_4_x,
  },
  {
    .name = "LED_5_X",
    .handler = internal_set_led_5_x,
    .getter = get_led_5_x,
  },
  {
    .name = "LED_0_Y",
    .handler = internal_set_led_0_y,
    .getter = get_led_0_y,
  },
  {
    .name = "LED_1_Y",
    .handler = internal_set_led_1_y,
    .getter = get_led_1_y,
  },
  {
    .name = "LED_2_Y",
    .handler = internal_set_led_2_y,
    .getter = get_led_2_y,
  },
  {
    .name = "LED_3_Y",
    .handler = internal_set_led_3_y,
    .getter = get_led_3_y,
  },
  {
    .name = "LED_4_Y",
    .handler = internal_set_led_4_y,
    .getter = get_led_4_y,
  },
  {
    .name = "LED_5_Y",
    .handler = internal_set_led_5_y,
    .getter = get_led_5_y,
  },
  {
    .name = "LED_0_Z",
    .handler = internal_set_led_0_z,
    .getter = get_led_0_z,
  },
  {
    .name = "LED_1_Z",
    .handler = internal_set_led_1_z,
    .getter = get_led_1_z,
  },
  {
    .name = "LED_2_Z",
    .handler = internal_set_led_2_z,
    .getter = get_led_2_z,
  },
  {
    .name = "LED_3_Z",
    .handler = internal_set_led_3_z,
    .getter = get_led_3_z,
  },
  {
    .name = "LED_4_Z",
    .handler = internal_set_led_4_z,
    .getter = get_led_4_z,
  },
  {
    .name = "LED_5_Z",
    .handler = internal_set_led_5_z,
    .getter = get_led_5_z,
  },
  {
    .name = "LED_0_ENABLE",
    .handler = internal_set_led_0_enable,
    .getter = get_led_0_enable,
  },
  {
    .name = "LED_1_ENABLE",
    .handler = internal_set_led_1_enable,
    .getter = get_led_1_enable,
  },
  {
    .name = "LED_2_ENABLE",
    .handler = internal_set_led_2_enable,
    .getter = get_led_2_enable,
  },
  {
    .name = "LED_3_ENABLE",
    .handler = internal_set_led_3_enable,
    .getter = get_led_3_enable,
  },
  {
    .name = "LED_4_ENABLE",
    .handler = internal_set_led_4_enable,
    .getter = get_led_4_enable,
  },
  {
    .name = "LED_5_ENABLE",
    .handler = internal_set_led_5_enable,
    .getter = get_led_5_enable,
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
    .handler = internal_set_wifi_ssid,
    .getter = get_wifi_ssid,
  },
  {
    .name = "WIFI_PASSWORD",
    .handler = internal_set_wifi_password,
    .getter = get_wifi_password,
  },
  {
    .name = "OTA_SERVER_IP",
    .handler = internal_set_ota_server_ip,
    .getter = get_ota_server_ip,
  },
  {
    .name = "OTA_SERVER_HOSTNAME",
    .handler = internal_set_ota_server_hostname,
    .getter = get_ota_server_hostname,
  },
  {
    .name = "OTA_SERVER_PORT",
    .handler = internal_set_ota_server_port,
    .getter = get_ota_server_port,
  },
  {
    .name = "OTA_VERSION_FILENAME",
    .handler = internal_set_ota_version_filename,
    .getter = get_ota_version_filename,
  },
  {
    .name = "OTA_FILENAME",
    .handler = internal_set_ota_filename,
    .getter = get_ota_filename,
  },
  {
    .name = "BROKER_URL",
    .handler = internal_set_broker_url,
    .getter = get_broker_url,
  },
  {
    .name = "DEVICE_NAME",
    .handler = internal_set_device_name,
    .getter = get_device_name,
  },
  {
    .name = "LED_INFO",
    .handler = NULL,
    .getter = get_led_info,
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
