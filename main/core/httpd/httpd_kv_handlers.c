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
    .name = "BOX_0_ENABLED",
    .handler = NULL,
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
    .name = "BOX_0_BLOWER",
    .handler = internal_set_box_0_blower,
    .getter = get_box_0_blower,
  },
  {
    .name = "BOX_0_BLOWER_MODE",
    .handler = internal_set_box_0_blower_mode,
    .getter = get_box_0_blower_mode,
  },
  {
    .name = "BOX_0_BLOWER_GPIO",
    .handler = internal_set_box_0_blower_gpio,
    .getter = get_box_0_blower_gpio,
  },
  {
    .name = "BOX_0_BLOWER_ENABLED",
    .handler = internal_set_box_0_blower_enabled,
    .getter = get_box_0_blower_enabled,
  },
  {
    .name = "BOX_0_SHT1X_TEMP_C",
    .handler = NULL,
    .getter = get_box_0_sht1x_temp_c,
  },
  {
    .name = "BOX_0_SHT1X_TEMP_F",
    .handler = NULL,
    .getter = get_box_0_sht1x_temp_f,
  },
  {
    .name = "BOX_0_SHT1X_HUMI",
    .handler = NULL,
    .getter = get_box_0_sht1x_humi,
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
    .name = "BOX_0_ARDUINO_CO2",
    .handler = NULL,
    .getter = get_box_0_arduino_co2,
  },
  {
    .name = "BOX_0_DUST_GPY2Y10",
    .handler = NULL,
    .getter = get_box_0_dust_gpy2y10,
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
    .name = "BOX_1_BLOWER",
    .handler = internal_set_box_1_blower,
    .getter = get_box_1_blower,
  },
  {
    .name = "BOX_1_BLOWER_MODE",
    .handler = internal_set_box_1_blower_mode,
    .getter = get_box_1_blower_mode,
  },
  {
    .name = "BOX_1_BLOWER_GPIO",
    .handler = internal_set_box_1_blower_gpio,
    .getter = get_box_1_blower_gpio,
  },
  {
    .name = "BOX_1_BLOWER_ENABLED",
    .handler = internal_set_box_1_blower_enabled,
    .getter = get_box_1_blower_enabled,
  },
  {
    .name = "BOX_1_SHT1X_TEMP_C",
    .handler = NULL,
    .getter = get_box_1_sht1x_temp_c,
  },
  {
    .name = "BOX_1_SHT1X_TEMP_F",
    .handler = NULL,
    .getter = get_box_1_sht1x_temp_f,
  },
  {
    .name = "BOX_1_SHT1X_HUMI",
    .handler = NULL,
    .getter = get_box_1_sht1x_humi,
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
    .name = "BOX_1_ARDUINO_CO2",
    .handler = NULL,
    .getter = get_box_1_arduino_co2,
  },
  {
    .name = "BOX_1_DUST_GPY2Y10",
    .handler = NULL,
    .getter = get_box_1_dust_gpy2y10,
  },
  {
    .name = "BOX_2_ENABLED",
    .handler = internal_set_box_2_enabled,
    .getter = get_box_2_enabled,
  },
  {
    .name = "BOX_2_TIMER_TYPE",
    .handler = internal_set_box_2_timer_type,
    .getter = get_box_2_timer_type,
  },
  {
    .name = "BOX_2_TIMER_OUTPUT",
    .handler = NULL,
    .getter = get_box_2_timer_output,
  },
  {
    .name = "BOX_2_STARTED_AT",
    .handler = internal_set_box_2_started_at,
    .getter = get_box_2_started_at,
  },
  {
    .name = "BOX_2_ON_HOUR",
    .handler = internal_set_box_2_on_hour,
    .getter = get_box_2_on_hour,
  },
  {
    .name = "BOX_2_ON_MIN",
    .handler = internal_set_box_2_on_min,
    .getter = get_box_2_on_min,
  },
  {
    .name = "BOX_2_OFF_HOUR",
    .handler = internal_set_box_2_off_hour,
    .getter = get_box_2_off_hour,
  },
  {
    .name = "BOX_2_OFF_MIN",
    .handler = internal_set_box_2_off_min,
    .getter = get_box_2_off_min,
  },
  {
    .name = "BOX_2_STRETCH",
    .handler = internal_set_box_2_stretch,
    .getter = get_box_2_stretch,
  },
  {
    .name = "BOX_2_LED_DIM",
    .handler = internal_set_box_2_led_dim,
    .getter = get_box_2_led_dim,
  },
  {
    .name = "BOX_2_BLOWER",
    .handler = internal_set_box_2_blower,
    .getter = get_box_2_blower,
  },
  {
    .name = "BOX_2_BLOWER_MODE",
    .handler = internal_set_box_2_blower_mode,
    .getter = get_box_2_blower_mode,
  },
  {
    .name = "BOX_2_BLOWER_GPIO",
    .handler = internal_set_box_2_blower_gpio,
    .getter = get_box_2_blower_gpio,
  },
  {
    .name = "BOX_2_BLOWER_ENABLED",
    .handler = internal_set_box_2_blower_enabled,
    .getter = get_box_2_blower_enabled,
  },
  {
    .name = "BOX_2_SHT1X_TEMP_C",
    .handler = NULL,
    .getter = get_box_2_sht1x_temp_c,
  },
  {
    .name = "BOX_2_SHT1X_TEMP_F",
    .handler = NULL,
    .getter = get_box_2_sht1x_temp_f,
  },
  {
    .name = "BOX_2_SHT1X_HUMI",
    .handler = NULL,
    .getter = get_box_2_sht1x_humi,
  },
  {
    .name = "BOX_2_SHT21_TEMP_C",
    .handler = NULL,
    .getter = get_box_2_sht21_temp_c,
  },
  {
    .name = "BOX_2_SHT21_TEMP_F",
    .handler = NULL,
    .getter = get_box_2_sht21_temp_f,
  },
  {
    .name = "BOX_2_SHT21_HUMI",
    .handler = NULL,
    .getter = get_box_2_sht21_humi,
  },
  {
    .name = "BOX_2_ARDUINO_CO2",
    .handler = NULL,
    .getter = get_box_2_arduino_co2,
  },
  {
    .name = "BOX_2_DUST_GPY2Y10",
    .handler = NULL,
    .getter = get_box_2_dust_gpy2y10,
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
    .name = "LED_2_ENABLED",
    .handler = internal_set_led_2_enabled,
    .getter = get_led_2_enabled,
  },
  {
    .name = "LED_3_ENABLED",
    .handler = internal_set_led_3_enabled,
    .getter = get_led_3_enabled,
  },
  {
    .name = "LED_4_ENABLED",
    .handler = internal_set_led_4_enabled,
    .getter = get_led_4_enabled,
  },
  {
    .name = "LED_5_ENABLED",
    .handler = internal_set_led_5_enabled,
    .getter = get_led_5_enabled,
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
    .name = "LED_2_BOX",
    .handler = internal_set_led_2_box,
    .getter = get_led_2_box,
  },
  {
    .name = "LED_3_BOX",
    .handler = internal_set_led_3_box,
    .getter = get_led_3_box,
  },
  {
    .name = "LED_4_BOX",
    .handler = internal_set_led_4_box,
    .getter = get_led_4_box,
  },
  {
    .name = "LED_5_BOX",
    .handler = internal_set_led_5_box,
    .getter = get_led_5_box,
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
    .name = "LED_2_DIM",
    .handler = internal_set_led_2_dim,
    .getter = get_led_2_dim,
  },
  {
    .name = "LED_3_DIM",
    .handler = internal_set_led_3_dim,
    .getter = get_led_3_dim,
  },
  {
    .name = "LED_4_DIM",
    .handler = internal_set_led_4_dim,
    .getter = get_led_4_dim,
  },
  {
    .name = "LED_5_DIM",
    .handler = internal_set_led_5_dim,
    .getter = get_led_5_dim,
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
  {
    .name = "LED_2_FADE",
    .handler = internal_set_led_2_fade,
    .getter = get_led_2_fade,
  },
  {
    .name = "LED_3_FADE",
    .handler = internal_set_led_3_fade,
    .getter = get_led_3_fade,
  },
  {
    .name = "LED_4_FADE",
    .handler = internal_set_led_4_fade,
    .getter = get_led_4_fade,
  },
  {
    .name = "LED_5_FADE",
    .handler = internal_set_led_5_fade,
    .getter = get_led_5_fade,
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
  {
    .name = "BOX_2_LED_INFO",
    .handler = NULL,
    .getter = get_box_2_led_info,
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
