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
#include "kv_mapping.h"
#include "../include_modules.h"

const kvi8_mapping kvi8_mappings[] = {
/*
* [GENERATED]
*/
  

  {
    .remote = true,
    .name = "REBOOT",
    
      .setter = internal_set_reboot,
    
    .getter = get_reboot,
  },

  {
    .remote = true,
    .name = "N_RESTARTS",
    
      .setter = NULL,
    
    .getter = get_n_restarts,
  },

  {
    .remote = true,
    .name = "OTA_STATUS",
    
      .setter = NULL,
    
    .getter = get_ota_status,
  },

  {
    .remote = true,
    .name = "I2C_0_SDA",
    
      .setter = internal_set_i2c_0_sda,
    
    .getter = get_i2c_0_sda,
  },

  {
    .remote = true,
    .name = "I2C_0_SCL",
    
      .setter = internal_set_i2c_0_scl,
    
    .getter = get_i2c_0_scl,
  },

  {
    .remote = true,
    .name = "I2C_0_ENABLED",
    
      .setter = internal_set_i2c_0_enabled,
    
    .getter = get_i2c_0_enabled,
  },

  {
    .remote = true,
    .name = "I2C_0_PORT",
    
      .setter = internal_set_i2c_0_port,
    
    .getter = get_i2c_0_port,
  },

  {
    .remote = true,
    .name = "WIFI_STATUS",
    
      .setter = NULL,
    
    .getter = get_wifi_status,
  },

  {
    .remote = true,
    .name = "BOX_0_ENABLED",
    
      .setter = internal_set_box_0_enabled,
    
    .getter = get_box_0_enabled,
  },

  {
    .remote = true,
    .name = "BOX_0_TEMP",
    
      .setter = NULL,
    
    .getter = get_box_0_temp,
  },

  {
    .remote = true,
    .name = "BOX_0_TEMP_SOURCE",
    
      .setter = internal_set_box_0_temp_source,
    
    .getter = get_box_0_temp_source,
  },

  {
    .remote = true,
    .name = "BOX_0_HUMI",
    
      .setter = NULL,
    
    .getter = get_box_0_humi,
  },

  {
    .remote = true,
    .name = "BOX_0_HUMI_SOURCE",
    
      .setter = internal_set_box_0_humi_source,
    
    .getter = get_box_0_humi_source,
  },

  {
    .remote = true,
    .name = "BOX_0_VPD_SOURCE",
    
      .setter = internal_set_box_0_vpd_source,
    
    .getter = get_box_0_vpd_source,
  },

  {
    .remote = true,
    .name = "MOTORS_CURVE",
    
      .setter = internal_set_motors_curve,
    
    .getter = get_motors_curve,
  },

  {
    .remote = true,
    .name = "MOTOR_0_DUTY",
    
      .setter = NULL,
    
    .getter = get_motor_0_duty,
  },

  {
    .remote = true,
    .name = "MOTOR_0_MIN",
    
      .setter = internal_set_motor_0_min,
    
    .getter = get_motor_0_min,
  },

  {
    .remote = true,
    .name = "MOTOR_0_MAX",
    
      .setter = internal_set_motor_0_max,
    
    .getter = get_motor_0_max,
  },

  {
    .remote = true,
    .name = "MOTOR_0_SOURCE",
    
      .setter = internal_set_motor_0_source,
    
    .getter = get_motor_0_source,
  },

  {
    .remote = true,
    .name = "MOTOR_0_GPIO",
    
      .setter = NULL,
    
    .getter = get_motor_0_gpio,
  },

  {
    .remote = true,
    .name = "BOX_0_BLOWER_DUTY",
    
      .setter = internal_set_box_0_blower_duty,
    
    .getter = get_box_0_blower_duty,
  },

  {
    .remote = true,
    .name = "BOX_0_BLOWER_MIN",
    
      .setter = internal_set_box_0_blower_min,
    
    .getter = get_box_0_blower_min,
  },

  {
    .remote = true,
    .name = "BOX_0_BLOWER_MAX",
    
      .setter = internal_set_box_0_blower_max,
    
    .getter = get_box_0_blower_max,
  },

  {
    .remote = true,
    .name = "BOX_0_BLOWER_REF_MIN",
    
      .setter = internal_set_box_0_blower_ref_min,
    
    .getter = get_box_0_blower_ref_min,
  },

  {
    .remote = true,
    .name = "BOX_0_BLOWER_REF_MAX",
    
      .setter = internal_set_box_0_blower_ref_max,
    
    .getter = get_box_0_blower_ref_max,
  },

  {
    .remote = true,
    .name = "BOX_0_BLOWER_REF",
    
      .setter = NULL,
    
    .getter = get_box_0_blower_ref,
  },

  {
    .remote = true,
    .name = "BOX_0_BLOWER_REF_SOURCE",
    
      .setter = internal_set_box_0_blower_ref_source,
    
    .getter = get_box_0_blower_ref_source,
  },

  {
    .remote = true,
    .name = "SHT21_0_TEMP",
    
      .setter = NULL,
    
    .getter = get_sht21_0_temp,
  },

  {
    .remote = true,
    .name = "SHT21_0_HUMI",
    
      .setter = NULL,
    
    .getter = get_sht21_0_humi,
  },

  {
    .remote = true,
    .name = "SHT21_0_PRESENT",
    
      .setter = NULL,
    
    .getter = get_sht21_0_present,
  },

  {
    .remote = true,
    .name = "SHT21_0_VPD_LEAF_OFFSET",
    
      .setter = internal_set_sht21_0_vpd_leaf_offset,
    
    .getter = get_sht21_0_vpd_leaf_offset,
  },

  {
    .remote = true,
    .name = "BOX_0_TIMER_TYPE",
    
      .setter = internal_set_box_0_timer_type,
    
    .getter = get_box_0_timer_type,
  },

  {
    .remote = true,
    .name = "BOX_0_TIMER_OUTPUT",
    
      .setter = NULL,
    
    .getter = get_box_0_timer_output,
  },

  {
    .remote = true,
    .name = "STATUS_LED_RED_GPIO",
    
      .setter = internal_set_status_led_red_gpio,
    
    .getter = get_status_led_red_gpio,
  },

  {
    .remote = true,
    .name = "STATUS_LED_GREEN_GPIO",
    
      .setter = internal_set_status_led_green_gpio,
    
    .getter = get_status_led_green_gpio,
  },

  {
    .remote = true,
    .name = "STATUS_LED_DIM",
    
      .setter = internal_set_status_led_dim,
    
    .getter = get_status_led_dim,
  },

  {
    .remote = true,
    .name = "STATE",
    
      .setter = internal_set_state,
    
    .getter = get_state,
  },

  {
    .remote = true,
    .name = "BOX_0_ON_HOUR",
    
      .setter = internal_set_box_0_on_hour,
    
    .getter = get_box_0_on_hour,
  },

  {
    .remote = true,
    .name = "BOX_0_ON_MIN",
    
      .setter = internal_set_box_0_on_min,
    
    .getter = get_box_0_on_min,
  },

  {
    .remote = true,
    .name = "BOX_0_OFF_HOUR",
    
      .setter = internal_set_box_0_off_hour,
    
    .getter = get_box_0_off_hour,
  },

  {
    .remote = true,
    .name = "BOX_0_OFF_MIN",
    
      .setter = internal_set_box_0_off_min,
    
    .getter = get_box_0_off_min,
  },

  {
    .remote = true,
    .name = "LEDS_FASTMODE",
    
      .setter = internal_set_leds_fastmode,
    
    .getter = get_leds_fastmode,
  },

  {
    .remote = true,
    .name = "LED_0_DUTY",
    
      .setter = internal_set_led_0_duty,
    
    .getter = get_led_0_duty,
  },

  {
    .remote = true,
    .name = "LED_0_GPIO",
    
      .setter = internal_set_led_0_gpio,
    
    .getter = get_led_0_gpio,
  },

  {
    .remote = true,
    .name = "LED_0_BOX",
    
      .setter = internal_set_led_0_box,
    
    .getter = get_led_0_box,
  },

  {
    .remote = true,
    .name = "LED_0_DIM",
    
      .setter = internal_set_led_0_dim,
    
    .getter = get_led_0_dim,
  },

  {
    .remote = true,
    .name = "LED_0_FADE",
    
      .setter = internal_set_led_0_fade,
    
    .getter = get_led_0_fade,
  },

  {
    .remote = true,
    .name = "BOX_0_WATERING_DUTY",
    
      .setter = internal_set_box_0_watering_duty,
    
    .getter = get_box_0_watering_duty,
  },

  {
    .remote = true,
    .name = "BOX_0_WATERING_POWER",
    
      .setter = internal_set_box_0_watering_power,
    
    .getter = get_box_0_watering_power,
  },


/*
* [/GENERATED]
*/
  {
    .name = NULL,
    .setter = NULL,
  },
};

const kvi8_mapping *get_kvi8_mapping(const char *name, bool remote) {
  for (int i = 0; kvi8_mappings[i].name != NULL; ++i) {
    if (strcmp(kvi8_mappings[i].name, name) == 0) {
      if (remote && kvi8_mappings[i].remote == false) {
        return NULL;
      }
      return &kvi8_mappings[i];
    }
  }
  return NULL;
}

const kvui8_mapping kvui8_mappings[] = {
/*
* [GENERATED]
*/
  

  {
    .remote = true,
    .name = "BOX_0_VPD",
    
      .setter = NULL,
    
    .getter = get_box_0_vpd,
  },

  {
    .remote = true,
    .name = "SHT21_0_VPD",
    
      .setter = NULL,
    
    .getter = get_sht21_0_vpd,
  },


/*
* [/GENERATED]
*/
  {
    .name = NULL,
    .setter = NULL,
  },
};

const kvui8_mapping *get_kvui8_mapping(const char *name, bool remote) {
  for (int i = 0; kvui8_mappings[i].name != NULL; ++i) {
    if (strcmp(kvui8_mappings[i].name, name) == 0) {
      if (remote && kvui8_mappings[i].remote == false) {
        return NULL;
      }
      return &kvui8_mappings[i];
    }
  }
  return NULL;
}



const kvi16_mapping kvi16_mappings[] = {
/*
* [GENERATED]
*/

 

/*
* [/GENERATED]
*/
  {
    .name = NULL,
    .setter = NULL,
  },
};

const kvi16_mapping *get_kvi16_mapping(const char *name, bool remote) {
  for (int i = 0; kvi16_mappings[i].name != NULL; ++i) {
    if (strcmp(kvi16_mappings[i].name, name) == 0) {
      if (remote && kvi16_mappings[i].remote == false) {
        return NULL;
      }

      return &kvi16_mappings[i];
    }
  }
  return NULL;
}

const kvui16_mapping kvui16_mappings[] = {
/*
* [GENERATED]
*/

 
  {
    .remote = false,
    .name = "OTA_SERVER_PORT",
    
      .setter = internal_set_ota_server_port,
    
    .getter = get_ota_server_port,
  },

  {
    .remote = true,
    .name = "MOTOR_0_FREQUENCY",
    
      .setter = internal_set_motor_0_frequency,
    
    .getter = get_motor_0_frequency,
  },

  {
    .remote = true,
    .name = "BOX_0_WATERING_PERIOD",
    
      .setter = internal_set_box_0_watering_period,
    
    .getter = get_box_0_watering_period,
  },

  {
    .remote = true,
    .name = "BOX_0_WATERING_DURATION",
    
      .setter = internal_set_box_0_watering_duration,
    
    .getter = get_box_0_watering_duration,
  },


/*
* [/GENERATED]
*/
  {
    .name = NULL,
    .setter = NULL,
  },
};

const kvui16_mapping *get_kvui16_mapping(const char *name, bool remote) {
  for (int i = 0; kvui16_mappings[i].name != NULL; ++i) {
    if (strcmp(kvui16_mappings[i].name, name) == 0) {
      if (remote && kvui16_mappings[i].remote == false) {
        return NULL;
      }
      return &kvui16_mappings[i];
    }
  }
  return NULL;
}


const kvi32_mapping kvi32_mappings[] = {
/*
* [GENERATED]
*/

 
  {
    .remote = true,
    .name = "TIME",
    
      .setter = internal_set_time,
    
    .getter = get_time,
  },

  {
    .remote = false,
    .name = "OTA_TIMESTAMP",
    
      .setter = internal_set_ota_timestamp,
    
    .getter = get_ota_timestamp,
  },

  {
    .remote = true,
    .name = "BOX_0_STARTED_AT",
    
      .setter = internal_set_box_0_started_at,
    
    .getter = get_box_0_started_at,
  },

  {
    .remote = true,
    .name = "BOX_0_LED_DIM",
    
      .setter = internal_set_box_0_led_dim,
    
    .getter = get_box_0_led_dim,
  },

  {
    .remote = true,
    .name = "BOX_0_WATERING_LAST",
    
      .setter = internal_set_box_0_watering_last,
    
    .getter = get_box_0_watering_last,
  },


/*
* [/GENERATED]
*/
  {
    .remote = false,
    .name = NULL,
    .setter = NULL,
  },
};

const kvi32_mapping *get_kvi32_mapping(const char *name, bool remote) {
  for (int i = 0; kvi32_mappings[i].name != NULL; ++i) {
    if (strcmp(kvi32_mappings[i].name, name) == 0) {
      if (remote && kvi32_mappings[i].remote == false) {
        return NULL;
      }
      return &kvi32_mappings[i];
    }
  }
  return NULL;
}

const kvui32_mapping kvui32_mappings[] = {
/*
* [GENERATED]
*/

 

/*
* [/GENERATED]
*/
  {
    .remote = true,
    .name = NULL,
    .setter = NULL,
  },
};

const kvui32_mapping *get_kvui32_mapping(const char *name, bool remote) {
  for (int i = 0; kvui32_mappings[i].name != NULL; ++i) {
    if (strcmp(kvui32_mappings[i].name, name) == 0) {
      if (remote && kvui32_mappings[i].remote == false) {
        return NULL;
      }
      return &kvui32_mappings[i];
    }
  }
  return NULL;
}

const kvs_mapping kvs_mappings[] = {
/*
* [GENERATED]
*/


  {
    .remote = true,
    .name = "BROKER_URL",
    
    .setter = internal_set_broker_url,
    
    .getter = get_broker_url,
  },

  {
    .remote = true,
    .name = "BROKER_CHANNEL",
    
    .setter = internal_set_broker_channel,
    
    .getter = get_broker_channel,
  },

  {
    .remote = true,
    .name = "BROKER_CLIENTID",
    
    .setter = internal_set_broker_clientid,
    
    .getter = get_broker_clientid,
  },

  {
    .remote = false,
    .name = "OTA_SERVER_IP",
    
    .setter = internal_set_ota_server_ip,
    
    .getter = get_ota_server_ip,
  },

  {
    .remote = false,
    .name = "OTA_SERVER_HOSTNAME",
    
    .setter = internal_set_ota_server_hostname,
    
    .getter = get_ota_server_hostname,
  },

  {
    .remote = false,
    .name = "OTA_BASEDIR",
    
    .setter = internal_set_ota_basedir,
    
    .getter = get_ota_basedir,
  },

  {
    .remote = false,
    .name = "HTTPD_AUTH",
    
    .setter = internal_set_httpd_auth,
    
    .getter = get_httpd_auth,
  },

  {
    .remote = false,
    .name = "WIFI_SSID",
    
    .setter = internal_set_wifi_ssid,
    
    .getter = get_wifi_ssid,
  },

  {
    .remote = false,
    .name = "WIFI_PASSWORD",
    
    .setter = internal_set_wifi_password,
    
    .getter = get_wifi_password,
  },

  {
    .remote = true,
    .name = "WIFI_AP_SSID",
    
    .setter = internal_set_wifi_ap_ssid,
    
    .getter = get_wifi_ap_ssid,
  },

  {
    .remote = true,
    .name = "WIFI_AP_PASSWORD",
    
    .setter = internal_set_wifi_ap_password,
    
    .getter = get_wifi_ap_password,
  },

  {
    .remote = false,
    .name = "MDNS_DOMAIN",
    
    .setter = internal_set_mdns_domain,
    
    .getter = get_mdns_domain,
  },

  {
    .remote = true,
    .name = "WIFI_IP",
    
    .setter = NULL,
    
    .getter = get_wifi_ip,
  },

  {
    .remote = true,
    .name = "DEVICE_NAME",
    
    .setter = internal_set_device_name,
    
    .getter = get_device_name,
  },


/*
* [/GENERATED]
*/
  {
    .remote = true,
    .name = NULL,
    .setter = NULL,
  }
};

const kvs_mapping *get_kvs_mapping(const char *name, bool remote) {
  for (int i = 0; kvs_mappings[i].name != NULL; ++i) {
    if (strcmp(kvs_mappings[i].name, name) == 0) {
      if (remote && kvs_mappings[i].remote == false) {
        return NULL;
      }
      return &kvs_mappings[i];
    }
  }
  return NULL;
}

