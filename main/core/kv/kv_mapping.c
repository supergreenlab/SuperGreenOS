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
    .name = "REBOOT",
    
      .setter = internal_set_reboot,
    
    .getter = get_reboot,
  },

  {
    .name = "N_RESTARTS",
    
      .setter = NULL,
    
    .getter = get_n_restarts,
  },

  {
    .name = "OTA_STATUS",
    
      .setter = NULL,
    
    .getter = get_ota_status,
  },

  {
    .name = "I2C_0_SDA",
    
      .setter = internal_set_i2c_0_sda,
    
    .getter = get_i2c_0_sda,
  },

  {
    .name = "I2C_1_SDA",
    
      .setter = internal_set_i2c_1_sda,
    
    .getter = get_i2c_1_sda,
  },

  {
    .name = "I2C_2_SDA",
    
      .setter = internal_set_i2c_2_sda,
    
    .getter = get_i2c_2_sda,
  },

  {
    .name = "I2C_0_SCL",
    
      .setter = internal_set_i2c_0_scl,
    
    .getter = get_i2c_0_scl,
  },

  {
    .name = "I2C_1_SCL",
    
      .setter = internal_set_i2c_1_scl,
    
    .getter = get_i2c_1_scl,
  },

  {
    .name = "I2C_2_SCL",
    
      .setter = internal_set_i2c_2_scl,
    
    .getter = get_i2c_2_scl,
  },

  {
    .name = "I2C_0_ENABLED",
    
      .setter = internal_set_i2c_0_enabled,
    
    .getter = get_i2c_0_enabled,
  },

  {
    .name = "I2C_1_ENABLED",
    
      .setter = internal_set_i2c_1_enabled,
    
    .getter = get_i2c_1_enabled,
  },

  {
    .name = "I2C_2_ENABLED",
    
      .setter = internal_set_i2c_2_enabled,
    
    .getter = get_i2c_2_enabled,
  },

  {
    .name = "I2C_0_PORT",
    
      .setter = internal_set_i2c_0_port,
    
    .getter = get_i2c_0_port,
  },

  {
    .name = "I2C_1_PORT",
    
      .setter = internal_set_i2c_1_port,
    
    .getter = get_i2c_1_port,
  },

  {
    .name = "I2C_2_PORT",
    
      .setter = internal_set_i2c_2_port,
    
    .getter = get_i2c_2_port,
  },

  {
    .name = "WIFI_STATUS",
    
      .setter = NULL,
    
    .getter = get_wifi_status,
  },

  {
    .name = "MOTORS_CURVE",
    
      .setter = internal_set_motors_curve,
    
    .getter = get_motors_curve,
  },

  {
    .name = "MOTOR_0_DUTY",
    
      .setter = NULL,
    
    .getter = get_motor_0_duty,
  },

  {
    .name = "MOTOR_1_DUTY",
    
      .setter = NULL,
    
    .getter = get_motor_1_duty,
  },

  {
    .name = "MOTOR_2_DUTY",
    
      .setter = NULL,
    
    .getter = get_motor_2_duty,
  },

  {
    .name = "MOTOR_0_SOURCE",
    
      .setter = internal_set_motor_0_source,
    
    .getter = get_motor_0_source,
  },

  {
    .name = "MOTOR_1_SOURCE",
    
      .setter = internal_set_motor_1_source,
    
    .getter = get_motor_1_source,
  },

  {
    .name = "MOTOR_2_SOURCE",
    
      .setter = internal_set_motor_2_source,
    
    .getter = get_motor_2_source,
  },

  {
    .name = "MOTOR_0_GPIO",
    
      .setter = internal_set_motor_0_gpio,
    
    .getter = get_motor_0_gpio,
  },

  {
    .name = "MOTOR_1_GPIO",
    
      .setter = internal_set_motor_1_gpio,
    
    .getter = get_motor_1_gpio,
  },

  {
    .name = "MOTOR_2_GPIO",
    
      .setter = internal_set_motor_2_gpio,
    
    .getter = get_motor_2_gpio,
  },

  {
    .name = "BOX_0_BLOWER_DUTY",
    
      .setter = internal_set_box_0_blower_duty,
    
    .getter = get_box_0_blower_duty,
  },

  {
    .name = "BOX_1_BLOWER_DUTY",
    
      .setter = internal_set_box_1_blower_duty,
    
    .getter = get_box_1_blower_duty,
  },

  {
    .name = "BOX_2_BLOWER_DUTY",
    
      .setter = internal_set_box_2_blower_duty,
    
    .getter = get_box_2_blower_duty,
  },

  {
    .name = "BOX_0_BLOWER_MIN",
    
      .setter = internal_set_box_0_blower_min,
    
    .getter = get_box_0_blower_min,
  },

  {
    .name = "BOX_1_BLOWER_MIN",
    
      .setter = internal_set_box_1_blower_min,
    
    .getter = get_box_1_blower_min,
  },

  {
    .name = "BOX_2_BLOWER_MIN",
    
      .setter = internal_set_box_2_blower_min,
    
    .getter = get_box_2_blower_min,
  },

  {
    .name = "BOX_0_BLOWER_MAX",
    
      .setter = internal_set_box_0_blower_max,
    
    .getter = get_box_0_blower_max,
  },

  {
    .name = "BOX_1_BLOWER_MAX",
    
      .setter = internal_set_box_1_blower_max,
    
    .getter = get_box_1_blower_max,
  },

  {
    .name = "BOX_2_BLOWER_MAX",
    
      .setter = internal_set_box_2_blower_max,
    
    .getter = get_box_2_blower_max,
  },

  {
    .name = "BOX_0_BLOWER_REF_MIN",
    
      .setter = internal_set_box_0_blower_ref_min,
    
    .getter = get_box_0_blower_ref_min,
  },

  {
    .name = "BOX_1_BLOWER_REF_MIN",
    
      .setter = internal_set_box_1_blower_ref_min,
    
    .getter = get_box_1_blower_ref_min,
  },

  {
    .name = "BOX_2_BLOWER_REF_MIN",
    
      .setter = internal_set_box_2_blower_ref_min,
    
    .getter = get_box_2_blower_ref_min,
  },

  {
    .name = "BOX_0_BLOWER_REF_MAX",
    
      .setter = internal_set_box_0_blower_ref_max,
    
    .getter = get_box_0_blower_ref_max,
  },

  {
    .name = "BOX_1_BLOWER_REF_MAX",
    
      .setter = internal_set_box_1_blower_ref_max,
    
    .getter = get_box_1_blower_ref_max,
  },

  {
    .name = "BOX_2_BLOWER_REF_MAX",
    
      .setter = internal_set_box_2_blower_ref_max,
    
    .getter = get_box_2_blower_ref_max,
  },

  {
    .name = "BOX_0_BLOWER_REF",
    
      .setter = NULL,
    
    .getter = get_box_0_blower_ref,
  },

  {
    .name = "BOX_1_BLOWER_REF",
    
      .setter = NULL,
    
    .getter = get_box_1_blower_ref,
  },

  {
    .name = "BOX_2_BLOWER_REF",
    
      .setter = NULL,
    
    .getter = get_box_2_blower_ref,
  },

  {
    .name = "BOX_0_BLOWER_REF_SOURCE",
    
      .setter = internal_set_box_0_blower_ref_source,
    
    .getter = get_box_0_blower_ref_source,
  },

  {
    .name = "BOX_1_BLOWER_REF_SOURCE",
    
      .setter = internal_set_box_1_blower_ref_source,
    
    .getter = get_box_1_blower_ref_source,
  },

  {
    .name = "BOX_2_BLOWER_REF_SOURCE",
    
      .setter = internal_set_box_2_blower_ref_source,
    
    .getter = get_box_2_blower_ref_source,
  },

  {
    .name = "BOX_0_ON_HOUR",
    
      .setter = internal_set_box_0_on_hour,
    
    .getter = get_box_0_on_hour,
  },

  {
    .name = "BOX_1_ON_HOUR",
    
      .setter = internal_set_box_1_on_hour,
    
    .getter = get_box_1_on_hour,
  },

  {
    .name = "BOX_2_ON_HOUR",
    
      .setter = internal_set_box_2_on_hour,
    
    .getter = get_box_2_on_hour,
  },

  {
    .name = "BOX_0_ON_MIN",
    
      .setter = internal_set_box_0_on_min,
    
    .getter = get_box_0_on_min,
  },

  {
    .name = "BOX_1_ON_MIN",
    
      .setter = internal_set_box_1_on_min,
    
    .getter = get_box_1_on_min,
  },

  {
    .name = "BOX_2_ON_MIN",
    
      .setter = internal_set_box_2_on_min,
    
    .getter = get_box_2_on_min,
  },

  {
    .name = "BOX_0_OFF_HOUR",
    
      .setter = internal_set_box_0_off_hour,
    
    .getter = get_box_0_off_hour,
  },

  {
    .name = "BOX_1_OFF_HOUR",
    
      .setter = internal_set_box_1_off_hour,
    
    .getter = get_box_1_off_hour,
  },

  {
    .name = "BOX_2_OFF_HOUR",
    
      .setter = internal_set_box_2_off_hour,
    
    .getter = get_box_2_off_hour,
  },

  {
    .name = "BOX_0_OFF_MIN",
    
      .setter = internal_set_box_0_off_min,
    
    .getter = get_box_0_off_min,
  },

  {
    .name = "BOX_1_OFF_MIN",
    
      .setter = internal_set_box_1_off_min,
    
    .getter = get_box_1_off_min,
  },

  {
    .name = "BOX_2_OFF_MIN",
    
      .setter = internal_set_box_2_off_min,
    
    .getter = get_box_2_off_min,
  },

  {
    .name = "BOX_0_ENABLED",
    
      .setter = internal_set_box_0_enabled,
    
    .getter = get_box_0_enabled,
  },

  {
    .name = "BOX_1_ENABLED",
    
      .setter = internal_set_box_1_enabled,
    
    .getter = get_box_1_enabled,
  },

  {
    .name = "BOX_2_ENABLED",
    
      .setter = internal_set_box_2_enabled,
    
    .getter = get_box_2_enabled,
  },

  {
    .name = "BOX_0_TEMP",
    
      .setter = NULL,
    
    .getter = get_box_0_temp,
  },

  {
    .name = "BOX_1_TEMP",
    
      .setter = NULL,
    
    .getter = get_box_1_temp,
  },

  {
    .name = "BOX_2_TEMP",
    
      .setter = NULL,
    
    .getter = get_box_2_temp,
  },

  {
    .name = "BOX_0_TEMP_SOURCE",
    
      .setter = internal_set_box_0_temp_source,
    
    .getter = get_box_0_temp_source,
  },

  {
    .name = "BOX_1_TEMP_SOURCE",
    
      .setter = internal_set_box_1_temp_source,
    
    .getter = get_box_1_temp_source,
  },

  {
    .name = "BOX_2_TEMP_SOURCE",
    
      .setter = internal_set_box_2_temp_source,
    
    .getter = get_box_2_temp_source,
  },

  {
    .name = "BOX_0_HUMI",
    
      .setter = NULL,
    
    .getter = get_box_0_humi,
  },

  {
    .name = "BOX_1_HUMI",
    
      .setter = NULL,
    
    .getter = get_box_1_humi,
  },

  {
    .name = "BOX_2_HUMI",
    
      .setter = NULL,
    
    .getter = get_box_2_humi,
  },

  {
    .name = "BOX_0_HUMI_SOURCE",
    
      .setter = internal_set_box_0_humi_source,
    
    .getter = get_box_0_humi_source,
  },

  {
    .name = "BOX_1_HUMI_SOURCE",
    
      .setter = internal_set_box_1_humi_source,
    
    .getter = get_box_1_humi_source,
  },

  {
    .name = "BOX_2_HUMI_SOURCE",
    
      .setter = internal_set_box_2_humi_source,
    
    .getter = get_box_2_humi_source,
  },

  {
    .name = "BOX_0_VPD_SOURCE",
    
      .setter = internal_set_box_0_vpd_source,
    
    .getter = get_box_0_vpd_source,
  },

  {
    .name = "BOX_1_VPD_SOURCE",
    
      .setter = internal_set_box_1_vpd_source,
    
    .getter = get_box_1_vpd_source,
  },

  {
    .name = "BOX_2_VPD_SOURCE",
    
      .setter = internal_set_box_2_vpd_source,
    
    .getter = get_box_2_vpd_source,
  },

  {
    .name = "STATUS_LED_RED_GPIO",
    
      .setter = internal_set_status_led_red_gpio,
    
    .getter = get_status_led_red_gpio,
  },

  {
    .name = "STATUS_LED_GREEN_GPIO",
    
      .setter = internal_set_status_led_green_gpio,
    
    .getter = get_status_led_green_gpio,
  },

  {
    .name = "STATUS_LED_DIM",
    
      .setter = internal_set_status_led_dim,
    
    .getter = get_status_led_dim,
  },

  {
    .name = "BOX_0_TIMER_TYPE",
    
      .setter = internal_set_box_0_timer_type,
    
    .getter = get_box_0_timer_type,
  },

  {
    .name = "BOX_1_TIMER_TYPE",
    
      .setter = internal_set_box_1_timer_type,
    
    .getter = get_box_1_timer_type,
  },

  {
    .name = "BOX_2_TIMER_TYPE",
    
      .setter = internal_set_box_2_timer_type,
    
    .getter = get_box_2_timer_type,
  },

  {
    .name = "BOX_0_TIMER_OUTPUT",
    
      .setter = NULL,
    
    .getter = get_box_0_timer_output,
  },

  {
    .name = "BOX_1_TIMER_OUTPUT",
    
      .setter = NULL,
    
    .getter = get_box_1_timer_output,
  },

  {
    .name = "BOX_2_TIMER_OUTPUT",
    
      .setter = NULL,
    
    .getter = get_box_2_timer_output,
  },

  {
    .name = "STATE",
    
      .setter = internal_set_state,
    
    .getter = get_state,
  },

  {
    .name = "BOX_0_WATERING_DUTY",
    
      .setter = internal_set_box_0_watering_duty,
    
    .getter = get_box_0_watering_duty,
  },

  {
    .name = "BOX_1_WATERING_DUTY",
    
      .setter = internal_set_box_1_watering_duty,
    
    .getter = get_box_1_watering_duty,
  },

  {
    .name = "BOX_2_WATERING_DUTY",
    
      .setter = internal_set_box_2_watering_duty,
    
    .getter = get_box_2_watering_duty,
  },

  {
    .name = "BOX_0_WATERING_POWER",
    
      .setter = internal_set_box_0_watering_power,
    
    .getter = get_box_0_watering_power,
  },

  {
    .name = "BOX_1_WATERING_POWER",
    
      .setter = internal_set_box_1_watering_power,
    
    .getter = get_box_1_watering_power,
  },

  {
    .name = "BOX_2_WATERING_POWER",
    
      .setter = internal_set_box_2_watering_power,
    
    .getter = get_box_2_watering_power,
  },

  {
    .name = "LEDS_FASTMODE",
    
      .setter = internal_set_leds_fastmode,
    
    .getter = get_leds_fastmode,
  },

  {
    .name = "LED_0_DUTY",
    
      .setter = internal_set_led_0_duty,
    
    .getter = get_led_0_duty,
  },

  {
    .name = "LED_1_DUTY",
    
      .setter = internal_set_led_1_duty,
    
    .getter = get_led_1_duty,
  },

  {
    .name = "LED_2_DUTY",
    
      .setter = internal_set_led_2_duty,
    
    .getter = get_led_2_duty,
  },

  {
    .name = "LED_0_GPIO",
    
      .setter = internal_set_led_0_gpio,
    
    .getter = get_led_0_gpio,
  },

  {
    .name = "LED_1_GPIO",
    
      .setter = internal_set_led_1_gpio,
    
    .getter = get_led_1_gpio,
  },

  {
    .name = "LED_2_GPIO",
    
      .setter = internal_set_led_2_gpio,
    
    .getter = get_led_2_gpio,
  },

  {
    .name = "LED_3_DUTY",
    
      .setter = internal_set_led_3_duty,
    
    .getter = get_led_3_duty,
  },

  {
    .name = "LED_4_DUTY",
    
      .setter = internal_set_led_4_duty,
    
    .getter = get_led_4_duty,
  },

  {
    .name = "LED_5_DUTY",
    
      .setter = internal_set_led_5_duty,
    
    .getter = get_led_5_duty,
  },

  {
    .name = "LED_3_GPIO",
    
      .setter = internal_set_led_3_gpio,
    
    .getter = get_led_3_gpio,
  },

  {
    .name = "LED_4_GPIO",
    
      .setter = internal_set_led_4_gpio,
    
    .getter = get_led_4_gpio,
  },

  {
    .name = "LED_5_GPIO",
    
      .setter = internal_set_led_5_gpio,
    
    .getter = get_led_5_gpio,
  },

  {
    .name = "LED_0_BOX",
    
      .setter = internal_set_led_0_box,
    
    .getter = get_led_0_box,
  },

  {
    .name = "LED_1_BOX",
    
      .setter = internal_set_led_1_box,
    
    .getter = get_led_1_box,
  },

  {
    .name = "LED_2_BOX",
    
      .setter = internal_set_led_2_box,
    
    .getter = get_led_2_box,
  },

  {
    .name = "LED_3_BOX",
    
      .setter = internal_set_led_3_box,
    
    .getter = get_led_3_box,
  },

  {
    .name = "LED_4_BOX",
    
      .setter = internal_set_led_4_box,
    
    .getter = get_led_4_box,
  },

  {
    .name = "LED_5_BOX",
    
      .setter = internal_set_led_5_box,
    
    .getter = get_led_5_box,
  },

  {
    .name = "LED_0_DIM",
    
      .setter = internal_set_led_0_dim,
    
    .getter = get_led_0_dim,
  },

  {
    .name = "LED_1_DIM",
    
      .setter = internal_set_led_1_dim,
    
    .getter = get_led_1_dim,
  },

  {
    .name = "LED_2_DIM",
    
      .setter = internal_set_led_2_dim,
    
    .getter = get_led_2_dim,
  },

  {
    .name = "LED_3_DIM",
    
      .setter = internal_set_led_3_dim,
    
    .getter = get_led_3_dim,
  },

  {
    .name = "LED_4_DIM",
    
      .setter = internal_set_led_4_dim,
    
    .getter = get_led_4_dim,
  },

  {
    .name = "LED_5_DIM",
    
      .setter = internal_set_led_5_dim,
    
    .getter = get_led_5_dim,
  },

  {
    .name = "LED_0_FADE",
    
      .setter = internal_set_led_0_fade,
    
    .getter = get_led_0_fade,
  },

  {
    .name = "LED_1_FADE",
    
      .setter = internal_set_led_1_fade,
    
    .getter = get_led_1_fade,
  },

  {
    .name = "LED_2_FADE",
    
      .setter = internal_set_led_2_fade,
    
    .getter = get_led_2_fade,
  },

  {
    .name = "LED_3_FADE",
    
      .setter = internal_set_led_3_fade,
    
    .getter = get_led_3_fade,
  },

  {
    .name = "LED_4_FADE",
    
      .setter = internal_set_led_4_fade,
    
    .getter = get_led_4_fade,
  },

  {
    .name = "LED_5_FADE",
    
      .setter = internal_set_led_5_fade,
    
    .getter = get_led_5_fade,
  },

  {
    .name = "SHT21_0_TEMP",
    
      .setter = NULL,
    
    .getter = get_sht21_0_temp,
  },

  {
    .name = "SHT21_1_TEMP",
    
      .setter = NULL,
    
    .getter = get_sht21_1_temp,
  },

  {
    .name = "SHT21_2_TEMP",
    
      .setter = NULL,
    
    .getter = get_sht21_2_temp,
  },

  {
    .name = "SHT21_0_HUMI",
    
      .setter = NULL,
    
    .getter = get_sht21_0_humi,
  },

  {
    .name = "SHT21_1_HUMI",
    
      .setter = NULL,
    
    .getter = get_sht21_1_humi,
  },

  {
    .name = "SHT21_2_HUMI",
    
      .setter = NULL,
    
    .getter = get_sht21_2_humi,
  },

  {
    .name = "SHT21_0_PRESENT",
    
      .setter = NULL,
    
    .getter = get_sht21_0_present,
  },

  {
    .name = "SHT21_1_PRESENT",
    
      .setter = NULL,
    
    .getter = get_sht21_1_present,
  },

  {
    .name = "SHT21_2_PRESENT",
    
      .setter = NULL,
    
    .getter = get_sht21_2_present,
  },

  {
    .name = "SHT21_0_VPD_LEAF_OFFSET",
    
      .setter = internal_set_sht21_0_vpd_leaf_offset,
    
    .getter = get_sht21_0_vpd_leaf_offset,
  },

  {
    .name = "SHT21_1_VPD_LEAF_OFFSET",
    
      .setter = internal_set_sht21_1_vpd_leaf_offset,
    
    .getter = get_sht21_1_vpd_leaf_offset,
  },

  {
    .name = "SHT21_2_VPD_LEAF_OFFSET",
    
      .setter = internal_set_sht21_2_vpd_leaf_offset,
    
    .getter = get_sht21_2_vpd_leaf_offset,
  },


/*
* [/GENERATED]
*/
  {
    .name = NULL,
    .setter = NULL,
  },
};

const kvi8_mapping *get_kvi8_mapping(const char *name) {
  for (int i = 0; kvi8_mappings[i].name != NULL; ++i) {
    if (strcmp(kvi8_mappings[i].name, name) == 0) {
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
    .name = "BOX_0_VPD",
    
      .setter = NULL,
    
    .getter = get_box_0_vpd,
  },

  {
    .name = "BOX_1_VPD",
    
      .setter = NULL,
    
    .getter = get_box_1_vpd,
  },

  {
    .name = "BOX_2_VPD",
    
      .setter = NULL,
    
    .getter = get_box_2_vpd,
  },

  {
    .name = "SHT21_0_VPD",
    
      .setter = NULL,
    
    .getter = get_sht21_0_vpd,
  },

  {
    .name = "SHT21_1_VPD",
    
      .setter = NULL,
    
    .getter = get_sht21_1_vpd,
  },

  {
    .name = "SHT21_2_VPD",
    
      .setter = NULL,
    
    .getter = get_sht21_2_vpd,
  },


/*
* [/GENERATED]
*/
  {
    .name = NULL,
    .setter = NULL,
  },
};

const kvui8_mapping *get_kvui8_mapping(const char *name) {
  for (int i = 0; kvui8_mappings[i].name != NULL; ++i) {
    if (strcmp(kvui8_mappings[i].name, name) == 0) {
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

const kvi16_mapping *get_kvi16_mapping(const char *name) {
  for (int i = 0; kvi16_mappings[i].name != NULL; ++i) {
    if (strcmp(kvi16_mappings[i].name, name) == 0) {
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
    .name = "OTA_SERVER_PORT",
    
      .setter = internal_set_ota_server_port,
    
    .getter = get_ota_server_port,
  },

  {
    .name = "MOTOR_0_FREQUENCY",
    
      .setter = internal_set_motor_0_frequency,
    
    .getter = get_motor_0_frequency,
  },

  {
    .name = "MOTOR_1_FREQUENCY",
    
      .setter = internal_set_motor_1_frequency,
    
    .getter = get_motor_1_frequency,
  },

  {
    .name = "MOTOR_2_FREQUENCY",
    
      .setter = internal_set_motor_2_frequency,
    
    .getter = get_motor_2_frequency,
  },

  {
    .name = "BOX_0_WATERING_PERIOD",
    
      .setter = internal_set_box_0_watering_period,
    
    .getter = get_box_0_watering_period,
  },

  {
    .name = "BOX_1_WATERING_PERIOD",
    
      .setter = internal_set_box_1_watering_period,
    
    .getter = get_box_1_watering_period,
  },

  {
    .name = "BOX_2_WATERING_PERIOD",
    
      .setter = internal_set_box_2_watering_period,
    
    .getter = get_box_2_watering_period,
  },

  {
    .name = "BOX_0_WATERING_DURATION",
    
      .setter = internal_set_box_0_watering_duration,
    
    .getter = get_box_0_watering_duration,
  },

  {
    .name = "BOX_1_WATERING_DURATION",
    
      .setter = internal_set_box_1_watering_duration,
    
    .getter = get_box_1_watering_duration,
  },

  {
    .name = "BOX_2_WATERING_DURATION",
    
      .setter = internal_set_box_2_watering_duration,
    
    .getter = get_box_2_watering_duration,
  },


/*
* [/GENERATED]
*/
  {
    .name = NULL,
    .setter = NULL,
  },
};

const kvui16_mapping *get_kvui16_mapping(const char *name) {
  for (int i = 0; kvui16_mappings[i].name != NULL; ++i) {
    if (strcmp(kvui16_mappings[i].name, name) == 0) {
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
    .name = "TIME",
    
      .setter = internal_set_time,
    
    .getter = get_time,
  },

  {
    .name = "OTA_TIMESTAMP",
    
      .setter = internal_set_ota_timestamp,
    
    .getter = get_ota_timestamp,
  },

  {
    .name = "BOX_0_LED_DIM",
    
      .setter = internal_set_box_0_led_dim,
    
    .getter = get_box_0_led_dim,
  },

  {
    .name = "BOX_1_LED_DIM",
    
      .setter = internal_set_box_1_led_dim,
    
    .getter = get_box_1_led_dim,
  },

  {
    .name = "BOX_2_LED_DIM",
    
      .setter = internal_set_box_2_led_dim,
    
    .getter = get_box_2_led_dim,
  },

  {
    .name = "BOX_0_STARTED_AT",
    
      .setter = internal_set_box_0_started_at,
    
    .getter = get_box_0_started_at,
  },

  {
    .name = "BOX_1_STARTED_AT",
    
      .setter = internal_set_box_1_started_at,
    
    .getter = get_box_1_started_at,
  },

  {
    .name = "BOX_2_STARTED_AT",
    
      .setter = internal_set_box_2_started_at,
    
    .getter = get_box_2_started_at,
  },

  {
    .name = "BOX_0_WATERING_LAST",
    
      .setter = internal_set_box_0_watering_last,
    
    .getter = get_box_0_watering_last,
  },

  {
    .name = "BOX_1_WATERING_LAST",
    
      .setter = internal_set_box_1_watering_last,
    
    .getter = get_box_1_watering_last,
  },

  {
    .name = "BOX_2_WATERING_LAST",
    
      .setter = internal_set_box_2_watering_last,
    
    .getter = get_box_2_watering_last,
  },


/*
* [/GENERATED]
*/
  {
    .name = NULL,
    .setter = NULL,
  },
};

const kvi32_mapping *get_kvi32_mapping(const char *name) {
  for (int i = 0; kvi32_mappings[i].name != NULL; ++i) {
    if (strcmp(kvi32_mappings[i].name, name) == 0) {
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
    .name = NULL,
    .setter = NULL,
  },
};

const kvui32_mapping *get_kvui32_mapping(const char *name) {
  for (int i = 0; kvui32_mappings[i].name != NULL; ++i) {
    if (strcmp(kvui32_mappings[i].name, name) == 0) {
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
    .name = "BROKER_URL",
    
    .setter = internal_set_broker_url,
    
    .getter = get_broker_url,
  },

  {
    .name = "BROKER_CHANNEL",
    
    .setter = internal_set_broker_channel,
    
    .getter = get_broker_channel,
  },

  {
    .name = "BROKER_CLIENTID",
    
    .setter = internal_set_broker_clientid,
    
    .getter = get_broker_clientid,
  },

  {
    .name = "OTA_SERVER_IP",
    
    .setter = internal_set_ota_server_ip,
    
    .getter = get_ota_server_ip,
  },

  {
    .name = "OTA_SERVER_HOSTNAME",
    
    .setter = internal_set_ota_server_hostname,
    
    .getter = get_ota_server_hostname,
  },

  {
    .name = "OTA_BASEDIR",
    
    .setter = internal_set_ota_basedir,
    
    .getter = get_ota_basedir,
  },

  {
    .name = "HTTPD_AUTH",
    
    .setter = internal_set_httpd_auth,
    
    .getter = get_httpd_auth,
  },

  {
    .name = "WIFI_SSID",
    
    .setter = internal_set_wifi_ssid,
    
    .getter = get_wifi_ssid,
  },

  {
    .name = "WIFI_PASSWORD",
    
    .setter = internal_set_wifi_password,
    
    .getter = get_wifi_password,
  },

  {
    .name = "WIFI_AP_SSID",
    
    .setter = internal_set_wifi_ap_ssid,
    
    .getter = get_wifi_ap_ssid,
  },

  {
    .name = "WIFI_AP_PASSWORD",
    
    .setter = internal_set_wifi_ap_password,
    
    .getter = get_wifi_ap_password,
  },

  {
    .name = "MDNS_DOMAIN",
    
    .setter = internal_set_mdns_domain,
    
    .getter = get_mdns_domain,
  },

  {
    .name = "WIFI_IP",
    
    .setter = NULL,
    
    .getter = get_wifi_ip,
  },

  {
    .name = "DEVICE_NAME",
    
    .setter = internal_set_device_name,
    
    .getter = get_device_name,
  },


/*
* [/GENERATED]
*/
  {
    .name = NULL,
    .setter = NULL,
  }
};

const kvs_mapping *get_kvs_mapping(const char *name) {
  for (int i = 0; kvs_mappings[i].name != NULL; ++i) {
    if (strcmp(kvs_mappings[i].name, name) == 0) {
      return &kvs_mappings[i];
    }
  }
  return NULL;
}

