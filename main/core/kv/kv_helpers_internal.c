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
  setstr(WIFI_SSID, value);

  value = on_set_wifi_ssid(value);

  setstr(WIFI_SSID, value);

  set_attr_value(IDX_CHAR_VAL_WIFI_SSID, (uint8_t *)value, strlen(value));
}
void internal_set_wifi_password(const char *value) {
  setstr(WIFI_PASSWORD, value);

  value = on_set_wifi_password(value);

  setstr(WIFI_PASSWORD, value);

}
void internal_set_time(int value) {
  seti(TIME, value);

  value = on_set_time(value);

  seti(TIME, value);

  set_attr_value_and_notify(IDX_CHAR_VAL_TIME, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_n_restarts(int value) {
  seti(N_RESTARTS, value);



  // TODO: httpd notify
}
void internal_set_ota_timestamp(int value) {
  seti(OTA_TIMESTAMP, value);



  // TODO: httpd notify
}
void internal_set_ota_server_ip(const char *value) {
  setstr(OTA_SERVER_IP, value);


}
void internal_set_ota_server_hostname(const char *value) {
  setstr(OTA_SERVER_HOSTNAME, value);


}
void internal_set_ota_server_port(const char *value) {
  setstr(OTA_SERVER_PORT, value);


}
void internal_set_ota_version_filename(const char *value) {
  setstr(OTA_VERSION_FILENAME, value);


}
void internal_set_ota_filename(const char *value) {
  setstr(OTA_FILENAME, value);


}
void internal_set_broker_url(const char *value) {
  setstr(BROKER_URL, value);


}
void internal_set_i2c_0_sda(int value) {
  seti(I2C_0_SDA, value);



  // TODO: httpd notify
}
void internal_set_i2c_0_scl(int value) {
  seti(I2C_0_SCL, value);



  // TODO: httpd notify
}
void internal_set_i2c_0_enabled(int value) {
  seti(I2C_0_ENABLED, value);



  // TODO: httpd notify
}
void internal_set_i2c_1_sda(int value) {
  seti(I2C_1_SDA, value);



  // TODO: httpd notify
}
void internal_set_i2c_1_scl(int value) {
  seti(I2C_1_SCL, value);



  // TODO: httpd notify
}
void internal_set_i2c_1_enabled(int value) {
  seti(I2C_1_ENABLED, value);



  // TODO: httpd notify
}
void internal_set_state(int value) {
  seti(STATE, value);


  set_attr_value_and_notify(IDX_CHAR_VAL_STATE, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_device_name(const char *value) {
  setstr(DEVICE_NAME, value);


  set_attr_value(IDX_CHAR_VAL_DEVICE_NAME, (uint8_t *)value, strlen(value));
}
void internal_set_box_0_enabled(int value) {
  seti(BOX_0_ENABLED, value);



  // TODO: httpd notify
}
void internal_set_box_0_timer_type(int value) {

  value = on_set_box_0_timer_type(value);



  // TODO: httpd notify
}
void internal_set_box_0_timer_output(int value) {
  seti(BOX_0_TIMER_OUTPUT, value);



  // TODO: httpd notify
}
void internal_set_box_0_started_at(int value) {
  seti(BOX_0_STARTED_AT, value);


  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_STARTED_AT, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_box_0_on_hour(int value) {
  seti(BOX_0_ON_HOUR, value);



  // TODO: httpd notify
}
void internal_set_box_0_on_min(int value) {
  seti(BOX_0_ON_MIN, value);



  // TODO: httpd notify
}
void internal_set_box_0_off_hour(int value) {
  seti(BOX_0_OFF_HOUR, value);



  // TODO: httpd notify
}
void internal_set_box_0_off_min(int value) {
  seti(BOX_0_OFF_MIN, value);



  // TODO: httpd notify
}
void internal_set_box_0_stretch(int value) {
  seti(BOX_0_STRETCH, value);

  value = on_set_box_0_stretch(value);

  seti(BOX_0_STRETCH, value);

  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_STRETCH, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_box_0_led_dim(int value) {
  seti(BOX_0_LED_DIM, value);

  value = on_set_box_0_led_dim(value);

  seti(BOX_0_LED_DIM, value);

  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_LED_DIM, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_box_0_blower(int value) {
  seti(BOX_0_BLOWER, value);

  value = on_set_box_0_blower(value);

  seti(BOX_0_BLOWER, value);

  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_BLOWER, (uint8_t *)&value, sizeof(int));

  // TODO: httpd notify
}
void internal_set_box_0_blower_mode(int value) {
  seti(BOX_0_BLOWER_MODE, value);



  // TODO: httpd notify
}
void internal_set_box_0_blower_gpio(int value) {
  seti(BOX_0_BLOWER_GPIO, value);



  // TODO: httpd notify
}
void internal_set_box_0_sht1x_temp_c(int value) {
  seti(BOX_0_SHT1X_TEMP_C, value);



  // TODO: httpd notify
}
void internal_set_box_0_sht1x_temp_f(int value) {
  seti(BOX_0_SHT1X_TEMP_F, value);



  // TODO: httpd notify
}
void internal_set_box_0_sht1x_humi(int value) {
  seti(BOX_0_SHT1X_HUMI, value);



  // TODO: httpd notify
}
void internal_set_box_0_arduino_co2(int value) {
  seti(BOX_0_ARDUINO_CO2, value);



  // TODO: httpd notify
}
void internal_set_box_0_dust_gpy2y10(int value) {
  seti(BOX_0_DUST_GPY2Y10, value);



  // TODO: httpd notify
}
void internal_set_box_0_led_info(const char *value) {


  set_attr_value_and_notify(IDX_CHAR_VAL_BOX_0_LED_INFO, (uint8_t *)value, strlen(value));
}
void internal_set_box_1_enabled(int value) {
  seti(BOX_1_ENABLED, value);



  // TODO: httpd notify
}
void internal_set_box_1_timer_type(int value) {

  value = on_set_box_1_timer_type(value);



  // TODO: httpd notify
}
void internal_set_box_1_timer_output(int value) {
  seti(BOX_1_TIMER_OUTPUT, value);



  // TODO: httpd notify
}
void internal_set_box_1_started_at(int value) {
  seti(BOX_1_STARTED_AT, value);



  // TODO: httpd notify
}
void internal_set_box_1_on_hour(int value) {
  seti(B_1_ON_HOUR, value);



  // TODO: httpd notify
}
void internal_set_box_1_on_min(int value) {
  seti(BOX_1_ON_MIN, value);



  // TODO: httpd notify
}
void internal_set_box_1_off_hour(int value) {
  seti(BOX_1_OFF_HOUR, value);



  // TODO: httpd notify
}
void internal_set_box_1_off_min(int value) {
  seti(BOX_1_OFF_MIN, value);



  // TODO: httpd notify
}
void internal_set_box_1_stretch(int value) {
  seti(BOX_1_STRETCH, value);

  value = on_set_box_1_stretch(value);

  seti(BOX_1_STRETCH, value);


  // TODO: httpd notify
}
void internal_set_box_1_led_dim(int value) {
  seti(BOX_1_LED_DIM, value);

  value = on_set_box_1_led_dim(value);

  seti(BOX_1_LED_DIM, value);


  // TODO: httpd notify
}
void internal_set_box_1_blower(int value) {
  seti(BOX_1_BLOWER, value);

  value = on_set_box_1_blower(value);

  seti(BOX_1_BLOWER, value);


  // TODO: httpd notify
}
void internal_set_box_1_blower_mode(int value) {
  seti(BOX_1_BLOWER_MODE, value);



  // TODO: httpd notify
}
void internal_set_box_1_blower_gpio(int value) {
  seti(BOX_1_BLOWER_GPIO, value);



  // TODO: httpd notify
}
void internal_set_box_1_sht1x_temp_c(int value) {
  seti(BOX_1_SHT1X_TEMP_C, value);



  // TODO: httpd notify
}
void internal_set_box_1_sht1x_temp_f(int value) {
  seti(BOX_1_SHT1X_TEMP_F, value);



  // TODO: httpd notify
}
void internal_set_box_1_sht1x_humi(int value) {
  seti(BOX_1_SHT1X_HUMI, value);



  // TODO: httpd notify
}
void internal_set_box_1_arduino_co2(int value) {
  seti(BOX_1_ARDUINO_CO2, value);



  // TODO: httpd notify
}
void internal_set_box_1_dust_gpy2y10(int value) {
  seti(BOX_1_DUST_GPY2Y10, value);



  // TODO: httpd notify
}
void internal_set_box_1_led_info(const char *value) {


}
void internal_set_box_2_enabled(int value) {
  seti(BOX_2_ENABLED, value);



  // TODO: httpd notify
}
void internal_set_box_2_timer_type(int value) {

  value = on_set_box_2_timer_type(value);



  // TODO: httpd notify
}
void internal_set_box_2_timer_output(int value) {
  seti(BOX_2_TIMER_OUTPUT, value);



  // TODO: httpd notify
}
void internal_set_box_2_started_at(int value) {
  seti(BOX_2_STARTED_AT, value);



  // TODO: httpd notify
}
void internal_set_box_2_on_hour(int value) {
  seti(B_2_ON_HOUR, value);



  // TODO: httpd notify
}
void internal_set_box_2_on_min(int value) {
  seti(BOX_2_ON_MIN, value);



  // TODO: httpd notify
}
void internal_set_box_2_off_hour(int value) {
  seti(BOX_2_OFF_HOUR, value);



  // TODO: httpd notify
}
void internal_set_box_2_off_min(int value) {
  seti(BOX_2_OFF_MIN, value);



  // TODO: httpd notify
}
void internal_set_box_2_stretch(int value) {
  seti(BOX_2_STRETCH, value);

  value = on_set_box_2_stretch(value);

  seti(BOX_2_STRETCH, value);


  // TODO: httpd notify
}
void internal_set_box_2_led_dim(int value) {
  seti(BOX_2_LED_DIM, value);

  value = on_set_box_2_led_dim(value);

  seti(BOX_2_LED_DIM, value);


  // TODO: httpd notify
}
void internal_set_box_2_blower(int value) {
  seti(BOX_2_BLOWER, value);

  value = on_set_box_2_blower(value);

  seti(BOX_2_BLOWER, value);


  // TODO: httpd notify
}
void internal_set_box_2_blower_mode(int value) {
  seti(BOX_2_BLOWER_MODE, value);



  // TODO: httpd notify
}
void internal_set_box_2_blower_gpio(int value) {
  seti(BOX_2_BLOWER_GPIO, value);



  // TODO: httpd notify
}
void internal_set_box_2_sht1x_temp_c(int value) {
  seti(BOX_2_SHT1X_TEMP_C, value);



  // TODO: httpd notify
}
void internal_set_box_2_sht1x_temp_f(int value) {
  seti(BOX_2_SHT1X_TEMP_F, value);



  // TODO: httpd notify
}
void internal_set_box_2_sht1x_humi(int value) {
  seti(BOX_2_SHT1X_HUMI, value);



  // TODO: httpd notify
}
void internal_set_box_2_arduino_co2(int value) {
  seti(BOX_2_ARDUINO_CO2, value);



  // TODO: httpd notify
}
void internal_set_box_2_dust_gpy2y10(int value) {
  seti(BOX_2_DUST_GPY2Y10, value);



  // TODO: httpd notify
}
void internal_set_box_2_led_info(const char *value) {


}
void internal_set_led_0_duty(int value) {
  seti(LED_0_DUTY, value);

  value = on_set_led_0_duty(value);

  seti(LED_0_DUTY, value);


  // TODO: httpd notify
}
void internal_set_led_1_duty(int value) {
  seti(LED_1_DUTY, value);

  value = on_set_led_1_duty(value);

  seti(LED_1_DUTY, value);


  // TODO: httpd notify
}
void internal_set_led_2_duty(int value) {
  seti(LED_2_DUTY, value);

  value = on_set_led_2_duty(value);

  seti(LED_2_DUTY, value);


  // TODO: httpd notify
}
void internal_set_led_3_duty(int value) {
  seti(LED_3_DUTY, value);

  value = on_set_led_3_duty(value);

  seti(LED_3_DUTY, value);


  // TODO: httpd notify
}
void internal_set_led_4_duty(int value) {
  seti(LED_4_DUTY, value);

  value = on_set_led_4_duty(value);

  seti(LED_4_DUTY, value);


  // TODO: httpd notify
}
void internal_set_led_5_duty(int value) {
  seti(LED_5_DUTY, value);

  value = on_set_led_5_duty(value);

  seti(LED_5_DUTY, value);


  // TODO: httpd notify
}
void internal_set_led_0_gpio(int value) {
  seti(LED_0_GPIO, value);



  // TODO: httpd notify
}
void internal_set_led_1_gpio(int value) {
  seti(LED_1_GPIO, value);



  // TODO: httpd notify
}
void internal_set_led_2_gpio(int value) {
  seti(LED_2_GPIO, value);



  // TODO: httpd notify
}
void internal_set_led_3_gpio(int value) {
  seti(LED_3_GPIO, value);



  // TODO: httpd notify
}
void internal_set_led_4_gpio(int value) {
  seti(LED_4_GPIO, value);



  // TODO: httpd notify
}
void internal_set_led_5_gpio(int value) {
  seti(LED_5_GPIO, value);



  // TODO: httpd notify
}
void internal_set_led_0_x(int value) {
  seti(LED_0_X, value);



  // TODO: httpd notify
}
void internal_set_led_1_x(int value) {
  seti(LED_1_X, value);



  // TODO: httpd notify
}
void internal_set_led_2_x(int value) {
  seti(LED_2_X, value);



  // TODO: httpd notify
}
void internal_set_led_3_x(int value) {
  seti(LED_3_X, value);



  // TODO: httpd notify
}
void internal_set_led_4_x(int value) {
  seti(LED_4_X, value);



  // TODO: httpd notify
}
void internal_set_led_5_x(int value) {
  seti(LED_5_X, value);



  // TODO: httpd notify
}
void internal_set_led_0_y(int value) {
  seti(LED_0_Y, value);



  // TODO: httpd notify
}
void internal_set_led_1_y(int value) {
  seti(LED_1_Y, value);



  // TODO: httpd notify
}
void internal_set_led_2_y(int value) {
  seti(LED_2_Y, value);



  // TODO: httpd notify
}
void internal_set_led_3_y(int value) {
  seti(LED_3_Y, value);



  // TODO: httpd notify
}
void internal_set_led_4_y(int value) {
  seti(LED_4_Y, value);



  // TODO: httpd notify
}
void internal_set_led_5_y(int value) {
  seti(LED_5_Y, value);



  // TODO: httpd notify
}
void internal_set_led_0_z(int value) {
  seti(LED_0_Z, value);



  // TODO: httpd notify
}
void internal_set_led_1_z(int value) {
  seti(LED_1_Z, value);



  // TODO: httpd notify
}
void internal_set_led_2_z(int value) {
  seti(LED_2_Z, value);



  // TODO: httpd notify
}
void internal_set_led_3_z(int value) {
  seti(LED_3_Z, value);



  // TODO: httpd notify
}
void internal_set_led_4_z(int value) {
  seti(LED_4_Z, value);



  // TODO: httpd notify
}
void internal_set_led_5_z(int value) {
  seti(LED_5_Z, value);



  // TODO: httpd notify
}
void internal_set_led_0_enable(int value) {
  seti(LED_0_ENABLE, value);



  // TODO: httpd notify
}
void internal_set_led_1_enable(int value) {
  seti(LED_1_ENABLE, value);



  // TODO: httpd notify
}
void internal_set_led_2_enable(int value) {
  seti(LED_2_ENABLE, value);



  // TODO: httpd notify
}
void internal_set_led_3_enable(int value) {
  seti(LED_3_ENABLE, value);



  // TODO: httpd notify
}
void internal_set_led_4_enable(int value) {
  seti(LED_4_ENABLE, value);



  // TODO: httpd notify
}
void internal_set_led_5_enable(int value) {
  seti(LED_5_ENABLE, value);



  // TODO: httpd notify
}
void internal_set_led_0_box(int value) {
  seti(LED_0_BOX, value);



  // TODO: httpd notify
}
void internal_set_led_1_box(int value) {
  seti(LED_1_BOX, value);



  // TODO: httpd notify
}
void internal_set_led_2_box(int value) {
  seti(LED_2_BOX, value);



  // TODO: httpd notify
}
void internal_set_led_3_box(int value) {
  seti(LED_3_BOX, value);



  // TODO: httpd notify
}
void internal_set_led_4_box(int value) {
  seti(LED_4_BOX, value);



  // TODO: httpd notify
}
void internal_set_led_5_box(int value) {
  seti(LED_5_BOX, value);



  // TODO: httpd notify
}

/*
 * [/GENERATED]
 */
