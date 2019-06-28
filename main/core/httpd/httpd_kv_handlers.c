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
    .name = "OTA_STATUS",
    .handler = NULL,
    .getter = get_ota_status,
  },
  {
    .name = "I2C_0_SDA",
    .handler = internal_set_i2c_0_sda,
    .getter = get_i2c_0_sda,
  },
  {
    .name = "I2C_0_SCL",
    .handler = internal_set_i2c_0_scl,
    .getter = get_i2c_0_scl,
  },
  {
    .name = "I2C_0_ENABLED",
    .handler = internal_set_i2c_0_enabled,
    .getter = get_i2c_0_enabled,
  },
  {
    .name = "I2C_1_SDA",
    .handler = internal_set_i2c_1_sda,
    .getter = get_i2c_1_sda,
  },
  {
    .name = "I2C_1_SCL",
    .handler = internal_set_i2c_1_scl,
    .getter = get_i2c_1_scl,
  },
  {
    .name = "I2C_1_ENABLED",
    .handler = internal_set_i2c_1_enabled,
    .getter = get_i2c_1_enabled,
  },
  {
    .name = "REBOOT",
    .handler = internal_set_reboot,
    .getter = get_reboot,
  },
  {
    .name = "STATE",
    .handler = internal_set_state,
    .getter = get_state,
  },
  {
    .name = "STATUS_LED_RED_GPIO",
    .handler = internal_set_status_led_red_gpio,
    .getter = get_status_led_red_gpio,
  },
  {
    .name = "STATUS_LED_GREEN_GPIO",
    .handler = internal_set_status_led_green_gpio,
    .getter = get_status_led_green_gpio,
  },
  {
    .name = "STATUS_LED_DIM",
    .handler = internal_set_status_led_dim,
    .getter = get_status_led_dim,
  },
  {
    .name = "BOX_0_ENABLED",
    .handler = internal_set_box_0_enabled,
    .getter = get_box_0_enabled,
  },
  {
    .name = "BOX_0_TIMER_TYPE",
    .handler = internal_set_box_0_timer_type,
    .getter = get_box_0_timer_type,
  },
  {
    .name = "BOX_0_TIMER_OUTPUT",
    .handler = NULL,
    .getter = get_box_0_timer_output,
  },
  {
    .name = "BOX_0_STARTED_AT",
    .handler = internal_set_box_0_started_at,
    .getter = get_box_0_started_at,
  },
  {
    .name = "BOX_0_ON_HOUR",
    .handler = internal_set_box_0_on_hour,
    .getter = get_box_0_on_hour,
  },
  {
    .name = "BOX_0_ON_MIN",
    .handler = internal_set_box_0_on_min,
    .getter = get_box_0_on_min,
  },
  {
    .name = "BOX_0_OFF_HOUR",
    .handler = internal_set_box_0_off_hour,
    .getter = get_box_0_off_hour,
  },
  {
    .name = "BOX_0_OFF_MIN",
    .handler = internal_set_box_0_off_min,
    .getter = get_box_0_off_min,
  },
  {
    .name = "BOX_0_STRETCH",
    .handler = internal_set_box_0_stretch,
    .getter = get_box_0_stretch,
  },
  {
    .name = "BOX_0_LED_DIM",
    .handler = internal_set_box_0_led_dim,
    .getter = get_box_0_led_dim,
  },
  {
    .name = "BOX_0_SHT21_TEMP_C",
    .handler = NULL,
    .getter = get_box_0_sht21_temp_c,
  },
  {
    .name = "BOX_0_SHT21_TEMP_F",
    .handler = NULL,
    .getter = get_box_0_sht21_temp_f,
  },
  {
    .name = "BOX_0_SHT21_HUMI",
    .handler = NULL,
    .getter = get_box_0_sht21_humi,
  },
  {
    .name = "BOX_1_ENABLED",
    .handler = internal_set_box_1_enabled,
    .getter = get_box_1_enabled,
  },
  {
    .name = "BOX_1_TIMER_TYPE",
    .handler = internal_set_box_1_timer_type,
    .getter = get_box_1_timer_type,
  },
  {
    .name = "BOX_1_TIMER_OUTPUT",
    .handler = NULL,
    .getter = get_box_1_timer_output,
  },
  {
    .name = "BOX_1_STARTED_AT",
    .handler = internal_set_box_1_started_at,
    .getter = get_box_1_started_at,
  },
  {
    .name = "BOX_1_ON_HOUR",
    .handler = internal_set_box_1_on_hour,
    .getter = get_box_1_on_hour,
  },
  {
    .name = "BOX_1_ON_MIN",
    .handler = internal_set_box_1_on_min,
    .getter = get_box_1_on_min,
  },
  {
    .name = "BOX_1_OFF_HOUR",
    .handler = internal_set_box_1_off_hour,
    .getter = get_box_1_off_hour,
  },
  {
    .name = "BOX_1_OFF_MIN",
    .handler = internal_set_box_1_off_min,
    .getter = get_box_1_off_min,
  },
  {
    .name = "BOX_1_STRETCH",
    .handler = internal_set_box_1_stretch,
    .getter = get_box_1_stretch,
  },
  {
    .name = "BOX_1_LED_DIM",
    .handler = internal_set_box_1_led_dim,
    .getter = get_box_1_led_dim,
  },
  {
    .name = "BOX_1_SHT21_TEMP_C",
    .handler = NULL,
    .getter = get_box_1_sht21_temp_c,
  },
  {
    .name = "BOX_1_SHT21_TEMP_F",
    .handler = NULL,
    .getter = get_box_1_sht21_temp_f,
  },
  {
    .name = "BOX_1_SHT21_HUMI",
    .handler = NULL,
    .getter = get_box_1_sht21_humi,
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
    .name = "LED_0_ENABLED",
    .handler = internal_set_led_0_enabled,
    .getter = get_led_0_enabled,
  },
  {
    .name = "LED_1_ENABLED",
    .handler = internal_set_led_1_enabled,
    .getter = get_led_1_enabled,
  },
  {
    .name = "LED_0_BOX",
    .handler = internal_set_led_0_box,
    .getter = get_led_0_box,
  },
  {
    .name = "LED_1_BOX",
    .handler = internal_set_led_1_box,
    .getter = get_led_1_box,
  },
  {
    .name = "LED_0_DIM",
    .handler = internal_set_led_0_dim,
    .getter = get_led_0_dim,
  },
  {
    .name = "LED_1_DIM",
    .handler = internal_set_led_1_dim,
    .getter = get_led_1_dim,
  },
  {
    .name = "LED_0_FADE",
    .handler = internal_set_led_0_fade,
    .getter = get_led_0_fade,
  },
  {
    .name = "LED_1_FADE",
    .handler = internal_set_led_1_fade,
    .getter = get_led_1_fade,
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
    .name = "WIFI_AP_SSID",
    .handler = internal_set_wifi_ap_ssid,
    .getter = get_wifi_ap_ssid,
  },
  {
    .name = "WIFI_AP_PASSWORD",
    .handler = internal_set_wifi_ap_password,
    .getter = get_wifi_ap_password,
  },
  {
    .name = "MDNS_DOMAIN",
    .handler = internal_set_mdns_domain,
    .getter = get_mdns_domain,
  },
  {
    .name = "WIFI_IP",
    .handler = NULL,
    .getter = get_wifi_ip,
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
    .name = "OTA_BASEDIR",
    .handler = internal_set_ota_basedir,
    .getter = get_ota_basedir,
  },
  {
    .name = "BROKER_URL",
    .handler = internal_set_broker_url,
    .getter = get_broker_url,
  },
  {
    .name = "BROKER_CHANNEL",
    .handler = internal_set_broker_channel,
    .getter = get_broker_channel,
  },
  {
    .name = "BROKER_CLIENTID",
    .handler = internal_set_broker_clientid,
    .getter = get_broker_clientid,
  },
  {
    .name = "DEVICE_NAME",
    .handler = internal_set_device_name,
    .getter = get_device_name,
  },
  {
    .name = "BOX_0_LED_INFO",
    .handler = NULL,
    .getter = get_box_0_led_info,
  },
  {
    .name = "BOX_1_LED_INFO",
    .handler = NULL,
    .getter = get_box_1_led_info,
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
