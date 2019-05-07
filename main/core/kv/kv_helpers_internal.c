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

#include <string.h>

#include "kv.h"
#include "keys.h"
#include "kv_ble.h"
#include "../ble/ble.h"

#include "../include_modules.h"

/*
 * [GENERATED]
 */

void internal_set_wifi_status(int value) {


  set_attr_value_and_notify(IDX_CHAR_VAL_WIFI_STATUS, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_wifi_ssid(const char *value) {
  set_wifi_ssid(value);

  value = on_set_wifi_ssid(value);

  set_wifi_ssid(value);

  set_attr_value(IDX_CHAR_VAL_WIFI_SSID, (uint8_t *)value, strlen(value));
}
void internal_set_wifi_password(const char *value) {
  set_wifi_password(value);

  value = on_set_wifi_password(value);

  set_wifi_password(value);

}
void internal_set_wifi_ap_ssid(const char *value) {
  set_wifi_ap_ssid(value);


}
void internal_set_wifi_ap_password(const char *value) {
  set_wifi_ap_password(value);


}
void internal_set_mdns_domain(const char *value) {
  set_mdns_domain(value);


}
void internal_set_wifi_ip(const char *value) {
  set_wifi_ip(value);


  set_attr_value_and_notify(IDX_CHAR_VAL_WIFI_IP, (uint8_t *)value, strlen(value));
}
void internal_set_time(int value) {
  set_time(value);

  value = on_set_time(value);

  set_time(value);

  set_attr_value_and_notify(IDX_CHAR_VAL_TIME, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_n_restarts(int value) {
  set_n_restarts(value);



  // TODO: httpd notify
}
void internal_set_ota_timestamp(int value) {
  set_ota_timestamp(value);



  // TODO: httpd notify
}
void internal_set_ota_server_ip(const char *value) {
  set_ota_server_ip(value);


}
void internal_set_ota_server_hostname(const char *value) {
  set_ota_server_hostname(value);


}
void internal_set_ota_server_port(const char *value) {
  set_ota_server_port(value);


}
void internal_set_ota_basedir(const char *value) {
  set_ota_basedir(value);


}
void internal_set_ota_status(int value) {



  // TODO: httpd notify
}
void internal_set_broker_url(const char *value) {
  set_broker_url(value);


}
void internal_set_broker_channel(const char *value) {
  set_broker_channel(value);


}
void internal_set_broker_clientid(const char *value) {
  set_broker_clientid(value);


}
void internal_set_i2c_0_sda(int value) {
  set_i2c_0_sda(value);



  // TODO: httpd notify
}
void internal_set_i2c_0_scl(int value) {
  set_i2c_0_scl(value);



  // TODO: httpd notify
}
void internal_set_i2c_0_enabled(int value) {
  set_i2c_0_enabled(value);



  // TODO: httpd notify
}
void internal_set_i2c_1_sda(int value) {
  set_i2c_1_sda(value);



  // TODO: httpd notify
}
void internal_set_i2c_1_scl(int value) {
  set_i2c_1_scl(value);



  // TODO: httpd notify
}
void internal_set_i2c_1_enabled(int value) {
  set_i2c_1_enabled(value);



  // TODO: httpd notify
}
void internal_set_reboot(int value) {

  value = on_set_reboot(value);



  // TODO: httpd notify
}
void internal_set_state(int value) {
  set_state(value);


  set_attr_value_and_notify(IDX_CHAR_VAL_STATE, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_device_name(const char *value) {
  set_device_name(value);


  set_attr_value(IDX_CHAR_VAL_DEVICE_NAME, (uint8_t *)value, strlen(value));
}
void internal_set_box_0_enabled(int value) {
  set_box_0_enabled(value);



  // TODO: httpd notify
}
void internal_set_box_0_timer_type(int value) {

  value = on_set_box_0_timer_type(value);



  // TODO: httpd notify
}
void internal_set_box_0_timer_output(int value) {
  set_box_0_timer_output(value);



  // TODO: httpd notify
}
void internal_set_box_0_started_at(int value) {
  set_box_0_started_at(value);


  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_STARTED_AT, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_box_0_on_hour(int value) {
  set_box_0_on_hour(value);



  // TODO: httpd notify
}
void internal_set_box_0_on_min(int value) {
  set_box_0_on_min(value);



  // TODO: httpd notify
}
void internal_set_box_0_off_hour(int value) {
  set_box_0_off_hour(value);



  // TODO: httpd notify
}
void internal_set_box_0_off_min(int value) {
  set_box_0_off_min(value);



  // TODO: httpd notify
}
void internal_set_box_0_stretch(int value) {
  set_box_0_stretch(value);

  value = on_set_box_0_stretch(value);

  set_box_0_stretch(value);

  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_STRETCH, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_box_0_led_dim(int value) {
  set_box_0_led_dim(value);

  value = on_set_box_0_led_dim(value);

  set_box_0_led_dim(value);

  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_LED_DIM, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_box_0_blower_day(int value) {
  set_box_0_blower_day(value);

  value = on_set_box_0_blower_day(value);

  set_box_0_blower_day(value);


  // TODO: httpd notify
}
void internal_set_box_0_blower_night(int value) {
  set_box_0_blower_night(value);

  value = on_set_box_0_blower_night(value);

  set_box_0_blower_night(value);


  // TODO: httpd notify
}
void internal_set_box_0_blower_gpio(int value) {
  set_box_0_blower_gpio(value);



  // TODO: httpd notify
}
void internal_set_box_0_blower_enabled(int value) {
  set_box_0_blower_enabled(value);



  // TODO: httpd notify
}
void internal_set_box_0_sht1x_temp_c(int value) {
  set_box_0_sht1x_temp_c(value);



  // TODO: httpd notify
}
void internal_set_box_0_sht1x_temp_f(int value) {
  set_box_0_sht1x_temp_f(value);



  // TODO: httpd notify
}
void internal_set_box_0_sht1x_humi(int value) {
  set_box_0_sht1x_humi(value);



  // TODO: httpd notify
}
void internal_set_box_0_sht21_temp_c(int value) {
  set_box_0_sht21_temp_c(value);



  // TODO: httpd notify
}
void internal_set_box_0_sht21_temp_f(int value) {
  set_box_0_sht21_temp_f(value);



  // TODO: httpd notify
}
void internal_set_box_0_sht21_humi(int value) {
  set_box_0_sht21_humi(value);



  // TODO: httpd notify
}
void internal_set_box_0_arduino_co2(int value) {
  set_box_0_arduino_co2(value);



  // TODO: httpd notify
}
void internal_set_box_0_dust_gpy2y10(int value) {
  set_box_0_dust_gpy2y10(value);



  // TODO: httpd notify
}
void internal_set_box_0_led_info(const char *value) {


  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_LED_INFO, (uint8_t *)value, strlen(value));
}
void internal_set_box_1_enabled(int value) {
  set_box_1_enabled(value);



  // TODO: httpd notify
}
void internal_set_box_1_timer_type(int value) {

  value = on_set_box_1_timer_type(value);



  // TODO: httpd notify
}
void internal_set_box_1_timer_output(int value) {
  set_box_1_timer_output(value);



  // TODO: httpd notify
}
void internal_set_box_1_started_at(int value) {
  set_box_1_started_at(value);



  // TODO: httpd notify
}
void internal_set_box_1_on_hour(int value) {
  set_box_1_on_hour(value);



  // TODO: httpd notify
}
void internal_set_box_1_on_min(int value) {
  set_box_1_on_min(value);



  // TODO: httpd notify
}
void internal_set_box_1_off_hour(int value) {
  set_box_1_off_hour(value);



  // TODO: httpd notify
}
void internal_set_box_1_off_min(int value) {
  set_box_1_off_min(value);



  // TODO: httpd notify
}
void internal_set_box_1_stretch(int value) {
  set_box_1_stretch(value);

  value = on_set_box_1_stretch(value);

  set_box_1_stretch(value);


  // TODO: httpd notify
}
void internal_set_box_1_led_dim(int value) {
  set_box_1_led_dim(value);

  value = on_set_box_1_led_dim(value);

  set_box_1_led_dim(value);


  // TODO: httpd notify
}
void internal_set_box_1_blower_day(int value) {
  set_box_1_blower_day(value);

  value = on_set_box_1_blower_day(value);

  set_box_1_blower_day(value);


  // TODO: httpd notify
}
void internal_set_box_1_blower_night(int value) {
  set_box_1_blower_night(value);

  value = on_set_box_1_blower_night(value);

  set_box_1_blower_night(value);


  // TODO: httpd notify
}
void internal_set_box_1_blower_gpio(int value) {
  set_box_1_blower_gpio(value);



  // TODO: httpd notify
}
void internal_set_box_1_blower_enabled(int value) {
  set_box_1_blower_enabled(value);



  // TODO: httpd notify
}
void internal_set_box_1_sht1x_temp_c(int value) {
  set_box_1_sht1x_temp_c(value);



  // TODO: httpd notify
}
void internal_set_box_1_sht1x_temp_f(int value) {
  set_box_1_sht1x_temp_f(value);



  // TODO: httpd notify
}
void internal_set_box_1_sht1x_humi(int value) {
  set_box_1_sht1x_humi(value);



  // TODO: httpd notify
}
void internal_set_box_1_sht21_temp_c(int value) {
  set_box_1_sht21_temp_c(value);



  // TODO: httpd notify
}
void internal_set_box_1_sht21_temp_f(int value) {
  set_box_1_sht21_temp_f(value);



  // TODO: httpd notify
}
void internal_set_box_1_sht21_humi(int value) {
  set_box_1_sht21_humi(value);



  // TODO: httpd notify
}
void internal_set_box_1_arduino_co2(int value) {
  set_box_1_arduino_co2(value);



  // TODO: httpd notify
}
void internal_set_box_1_dust_gpy2y10(int value) {
  set_box_1_dust_gpy2y10(value);



  // TODO: httpd notify
}
void internal_set_box_1_led_info(const char *value) {


}
void internal_set_box_2_enabled(int value) {
  set_box_2_enabled(value);



  // TODO: httpd notify
}
void internal_set_box_2_timer_type(int value) {

  value = on_set_box_2_timer_type(value);



  // TODO: httpd notify
}
void internal_set_box_2_timer_output(int value) {
  set_box_2_timer_output(value);



  // TODO: httpd notify
}
void internal_set_box_2_started_at(int value) {
  set_box_2_started_at(value);



  // TODO: httpd notify
}
void internal_set_box_2_on_hour(int value) {
  set_box_2_on_hour(value);



  // TODO: httpd notify
}
void internal_set_box_2_on_min(int value) {
  set_box_2_on_min(value);



  // TODO: httpd notify
}
void internal_set_box_2_off_hour(int value) {
  set_box_2_off_hour(value);



  // TODO: httpd notify
}
void internal_set_box_2_off_min(int value) {
  set_box_2_off_min(value);



  // TODO: httpd notify
}
void internal_set_box_2_stretch(int value) {
  set_box_2_stretch(value);

  value = on_set_box_2_stretch(value);

  set_box_2_stretch(value);


  // TODO: httpd notify
}
void internal_set_box_2_led_dim(int value) {
  set_box_2_led_dim(value);

  value = on_set_box_2_led_dim(value);

  set_box_2_led_dim(value);


  // TODO: httpd notify
}
void internal_set_box_2_blower_day(int value) {
  set_box_2_blower_day(value);

  value = on_set_box_2_blower_day(value);

  set_box_2_blower_day(value);


  // TODO: httpd notify
}
void internal_set_box_2_blower_night(int value) {
  set_box_2_blower_night(value);

  value = on_set_box_2_blower_night(value);

  set_box_2_blower_night(value);


  // TODO: httpd notify
}
void internal_set_box_2_blower_gpio(int value) {
  set_box_2_blower_gpio(value);



  // TODO: httpd notify
}
void internal_set_box_2_blower_enabled(int value) {
  set_box_2_blower_enabled(value);



  // TODO: httpd notify
}
void internal_set_box_2_sht1x_temp_c(int value) {
  set_box_2_sht1x_temp_c(value);



  // TODO: httpd notify
}
void internal_set_box_2_sht1x_temp_f(int value) {
  set_box_2_sht1x_temp_f(value);



  // TODO: httpd notify
}
void internal_set_box_2_sht1x_humi(int value) {
  set_box_2_sht1x_humi(value);



  // TODO: httpd notify
}
void internal_set_box_2_sht21_temp_c(int value) {
  set_box_2_sht21_temp_c(value);



  // TODO: httpd notify
}
void internal_set_box_2_sht21_temp_f(int value) {
  set_box_2_sht21_temp_f(value);



  // TODO: httpd notify
}
void internal_set_box_2_sht21_humi(int value) {
  set_box_2_sht21_humi(value);



  // TODO: httpd notify
}
void internal_set_box_2_arduino_co2(int value) {
  set_box_2_arduino_co2(value);



  // TODO: httpd notify
}
void internal_set_box_2_dust_gpy2y10(int value) {
  set_box_2_dust_gpy2y10(value);



  // TODO: httpd notify
}
void internal_set_box_2_led_info(const char *value) {


}
void internal_set_led_0_duty(int value) {
  set_led_0_duty(value);

  value = on_set_led_0_duty(value);

  set_led_0_duty(value);


  // TODO: httpd notify
}
void internal_set_led_1_duty(int value) {
  set_led_1_duty(value);

  value = on_set_led_1_duty(value);

  set_led_1_duty(value);


  // TODO: httpd notify
}
void internal_set_led_2_duty(int value) {
  set_led_2_duty(value);

  value = on_set_led_2_duty(value);

  set_led_2_duty(value);


  // TODO: httpd notify
}
void internal_set_led_3_duty(int value) {
  set_led_3_duty(value);

  value = on_set_led_3_duty(value);

  set_led_3_duty(value);


  // TODO: httpd notify
}
void internal_set_led_4_duty(int value) {
  set_led_4_duty(value);

  value = on_set_led_4_duty(value);

  set_led_4_duty(value);


  // TODO: httpd notify
}
void internal_set_led_5_duty(int value) {
  set_led_5_duty(value);

  value = on_set_led_5_duty(value);

  set_led_5_duty(value);


  // TODO: httpd notify
}
void internal_set_led_6_duty(int value) {
  set_led_6_duty(value);

  value = on_set_led_6_duty(value);

  set_led_6_duty(value);


  // TODO: httpd notify
}
void internal_set_led_0_gpio(int value) {
  set_led_0_gpio(value);



  // TODO: httpd notify
}
void internal_set_led_1_gpio(int value) {
  set_led_1_gpio(value);



  // TODO: httpd notify
}
void internal_set_led_2_gpio(int value) {
  set_led_2_gpio(value);



  // TODO: httpd notify
}
void internal_set_led_3_gpio(int value) {
  set_led_3_gpio(value);



  // TODO: httpd notify
}
void internal_set_led_4_gpio(int value) {
  set_led_4_gpio(value);



  // TODO: httpd notify
}
void internal_set_led_5_gpio(int value) {
  set_led_5_gpio(value);



  // TODO: httpd notify
}
void internal_set_led_6_gpio(int value) {
  set_led_6_gpio(value);



  // TODO: httpd notify
}
void internal_set_led_0_x(int value) {
  set_led_0_x(value);



  // TODO: httpd notify
}
void internal_set_led_1_x(int value) {
  set_led_1_x(value);



  // TODO: httpd notify
}
void internal_set_led_2_x(int value) {
  set_led_2_x(value);



  // TODO: httpd notify
}
void internal_set_led_3_x(int value) {
  set_led_3_x(value);



  // TODO: httpd notify
}
void internal_set_led_4_x(int value) {
  set_led_4_x(value);



  // TODO: httpd notify
}
void internal_set_led_5_x(int value) {
  set_led_5_x(value);



  // TODO: httpd notify
}
void internal_set_led_6_x(int value) {
  set_led_6_x(value);



  // TODO: httpd notify
}
void internal_set_led_0_y(int value) {
  set_led_0_y(value);



  // TODO: httpd notify
}
void internal_set_led_1_y(int value) {
  set_led_1_y(value);



  // TODO: httpd notify
}
void internal_set_led_2_y(int value) {
  set_led_2_y(value);



  // TODO: httpd notify
}
void internal_set_led_3_y(int value) {
  set_led_3_y(value);



  // TODO: httpd notify
}
void internal_set_led_4_y(int value) {
  set_led_4_y(value);



  // TODO: httpd notify
}
void internal_set_led_5_y(int value) {
  set_led_5_y(value);



  // TODO: httpd notify
}
void internal_set_led_6_y(int value) {
  set_led_6_y(value);



  // TODO: httpd notify
}
void internal_set_led_0_z(int value) {
  set_led_0_z(value);



  // TODO: httpd notify
}
void internal_set_led_1_z(int value) {
  set_led_1_z(value);



  // TODO: httpd notify
}
void internal_set_led_2_z(int value) {
  set_led_2_z(value);



  // TODO: httpd notify
}
void internal_set_led_3_z(int value) {
  set_led_3_z(value);



  // TODO: httpd notify
}
void internal_set_led_4_z(int value) {
  set_led_4_z(value);



  // TODO: httpd notify
}
void internal_set_led_5_z(int value) {
  set_led_5_z(value);



  // TODO: httpd notify
}
void internal_set_led_6_z(int value) {
  set_led_6_z(value);



  // TODO: httpd notify
}
void internal_set_led_0_enabled(int value) {
  set_led_0_enabled(value);



  // TODO: httpd notify
}
void internal_set_led_1_enabled(int value) {
  set_led_1_enabled(value);



  // TODO: httpd notify
}
void internal_set_led_2_enabled(int value) {
  set_led_2_enabled(value);



  // TODO: httpd notify
}
void internal_set_led_3_enabled(int value) {
  set_led_3_enabled(value);



  // TODO: httpd notify
}
void internal_set_led_4_enabled(int value) {
  set_led_4_enabled(value);



  // TODO: httpd notify
}
void internal_set_led_5_enabled(int value) {
  set_led_5_enabled(value);



  // TODO: httpd notify
}
void internal_set_led_6_enabled(int value) {
  set_led_6_enabled(value);



  // TODO: httpd notify
}
void internal_set_led_0_box(int value) {
  set_led_0_box(value);



  // TODO: httpd notify
}
void internal_set_led_1_box(int value) {
  set_led_1_box(value);



  // TODO: httpd notify
}
void internal_set_led_2_box(int value) {
  set_led_2_box(value);



  // TODO: httpd notify
}
void internal_set_led_3_box(int value) {
  set_led_3_box(value);



  // TODO: httpd notify
}
void internal_set_led_4_box(int value) {
  set_led_4_box(value);



  // TODO: httpd notify
}
void internal_set_led_5_box(int value) {
  set_led_5_box(value);



  // TODO: httpd notify
}
void internal_set_led_6_box(int value) {
  set_led_6_box(value);



  // TODO: httpd notify
}
void internal_set_led_0_dim(int value) {
  set_led_0_dim(value);

  value = on_set_led_0_dim(value);

  set_led_0_dim(value);


  // TODO: httpd notify
}
void internal_set_led_1_dim(int value) {
  set_led_1_dim(value);

  value = on_set_led_1_dim(value);

  set_led_1_dim(value);


  // TODO: httpd notify
}
void internal_set_led_2_dim(int value) {
  set_led_2_dim(value);

  value = on_set_led_2_dim(value);

  set_led_2_dim(value);


  // TODO: httpd notify
}
void internal_set_led_3_dim(int value) {
  set_led_3_dim(value);

  value = on_set_led_3_dim(value);

  set_led_3_dim(value);


  // TODO: httpd notify
}
void internal_set_led_4_dim(int value) {
  set_led_4_dim(value);

  value = on_set_led_4_dim(value);

  set_led_4_dim(value);


  // TODO: httpd notify
}
void internal_set_led_5_dim(int value) {
  set_led_5_dim(value);

  value = on_set_led_5_dim(value);

  set_led_5_dim(value);


  // TODO: httpd notify
}
void internal_set_led_6_dim(int value) {
  set_led_6_dim(value);

  value = on_set_led_6_dim(value);

  set_led_6_dim(value);


  // TODO: httpd notify
}
void internal_set_led_0_fade(int value) {
  set_led_0_fade(value);



  // TODO: httpd notify
}
void internal_set_led_1_fade(int value) {
  set_led_1_fade(value);



  // TODO: httpd notify
}
void internal_set_led_2_fade(int value) {
  set_led_2_fade(value);



  // TODO: httpd notify
}
void internal_set_led_3_fade(int value) {
  set_led_3_fade(value);



  // TODO: httpd notify
}
void internal_set_led_4_fade(int value) {
  set_led_4_fade(value);



  // TODO: httpd notify
}
void internal_set_led_5_fade(int value) {
  set_led_5_fade(value);



  // TODO: httpd notify
}
void internal_set_led_6_fade(int value) {
  set_led_6_fade(value);



  // TODO: httpd notify
}

/*
 * [/GENERATED]
 */
