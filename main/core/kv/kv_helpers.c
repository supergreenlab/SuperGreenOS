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
#include "kv_ble.h"
#include "../ble/ble.h"

/*
 * [GENERATED]
 */

void set_wifi_status(int value) {
  set_attr_value_and_notify(IDX_CHAR_VAL_WIFI_STATUS, (uint8_t *)&value, sizeof(int));
}
void set_wifi_ssid(const char *value) {
  setstr(WIFI_SSID, value);
  set_attr_value(IDX_CHAR_VAL_WIFI_SSID, (uint8_t *)value, strlen(value));
}
void set_wifi_password(const char *value) {
  setstr(WIFI_PASS, value);
}
void set_time(int value) {
  seti(TIME, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_TIME, (uint8_t *)&value, sizeof(int));
}
void set_ota_timestamp(int value) {
}
void set_ota_server_ip(const char *value) {
  setstr(OTA_SERVER_IP, value);
  set_attr_value(IDX_CHAR_VAL_OTA_SERVER_IP, (uint8_t *)value, strlen(value));
}
void set_ota_server_hostname(const char *value) {
  setstr(OTA_SERVER_HOSTNAME, value);
  set_attr_value(IDX_CHAR_VAL_OTA_SERVER_HOSTNAME, (uint8_t *)value, strlen(value));
}
void set_ota_server_port(const char *value) {
  setstr(OTA_SERVER_PORT, value);
  set_attr_value(IDX_CHAR_VAL_OTA_SERVER_PORT, (uint8_t *)value, strlen(value));
}
void set_ota_version_filename(const char *value) {
  setstr(OTA_VERSION_FILENAME, value);
  set_attr_value(IDX_CHAR_VAL_OTA_VERSION_FILENAME, (uint8_t *)value, strlen(value));
}
void set_ota_filename(const char *value) {
  setstr(OTA_FILENAME, value);
  set_attr_value(IDX_CHAR_VAL_OTA_FILENAME, (uint8_t *)value, strlen(value));
}
void set_i2c_sda(int value) {
  seti(I2C_SDA, value);
}
void set_i2c_scl(int value) {
  seti(I2C_SCL, value);
}
void set_state(int value) {
  seti(STATE, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_STATE, (uint8_t *)&value, sizeof(int));
}
void set_device_name(const char *value) {
  setstr(DEVICE_NAME, value);
  set_attr_value(IDX_CHAR_VAL_DEVICE_NAME, (uint8_t *)value, strlen(value));
}
void set_timer_type(int value) {
  seti(TIMER_TYPE, value);
}
void set_timer_output(int value) {
  seti(TIMER_OUTPUT, value);
}
void set_started_at(int value) {
  seti(STARTED_AT, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_STARTED_AT, (uint8_t *)&value, sizeof(int));
}
void set_on_hour(int value) {
  seti(ON_HOUR, value);
}
void set_on_min(int value) {
  seti(ON_MIN, value);
}
void set_off_hour(int value) {
  seti(OFF_HOUR, value);
}
void set_off_min(int value) {
  seti(OFF_MIN, value);
}
void set_stretch(int value) {
  seti(STRETCH, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_STRETCH, (uint8_t *)&value, sizeof(int));
}
void set_led_dim(int value) {
  seti(LED_DIM, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_LED_DIM, (uint8_t *)&value, sizeof(int));
}
void set_blower(int value) {
  seti(BLOWER, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_BLOWER, (uint8_t *)&value, sizeof(int));
}
void set_blower_gpio(int value) {
  seti(BLOWER_GPIO, value);
}
void set_sht1x_temp_c(int value) {
  seti(SHT1X_TEMP_C, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_SHT1X_TEMP_C, (uint8_t *)&value, sizeof(int));
}
void set_sht1x_temp_f(int value) {
  seti(SHT1X_TEMP_F, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_SHT1X_TEMP_F, (uint8_t *)&value, sizeof(int));
}
void set_sht1x_humi(int value) {
  seti(SHT1X_HUMI, value);
  set_attr_value_and_notify(IDX_CHAR_VAL_SHT1X_HUMI, (uint8_t *)&value, sizeof(int));
}
void set_led_info(const char *value) {
  set_attr_value_and_notify(IDX_CHAR_VAL_LED_INFO, (uint8_t *)value, strlen(value));
}
void set_led_0_duty(int value) {
  seti(LED_0_DUTY, value);
}
void set_led_1_duty(int value) {
  seti(LED_1_DUTY, value);
}
void set_led_2_duty(int value) {
  seti(LED_2_DUTY, value);
}
void set_led_3_duty(int value) {
  seti(LED_3_DUTY, value);
}
void set_led_4_duty(int value) {
  seti(LED_4_DUTY, value);
}
void set_led_5_duty(int value) {
  seti(LED_5_DUTY, value);
}
void set_led_0_gpio(int value) {
  seti(LED_0_GPIO, value);
}
void set_led_1_gpio(int value) {
  seti(LED_1_GPIO, value);
}
void set_led_2_gpio(int value) {
  seti(LED_2_GPIO, value);
}
void set_led_3_gpio(int value) {
  seti(LED_3_GPIO, value);
}
void set_led_4_gpio(int value) {
  seti(LED_4_GPIO, value);
}
void set_led_5_gpio(int value) {
  seti(LED_5_GPIO, value);
}
void set_led_0_x(int value) {
  seti(LED_0_X, value);
}
void set_led_1_x(int value) {
  seti(LED_1_X, value);
}
void set_led_2_x(int value) {
  seti(LED_2_X, value);
}
void set_led_3_x(int value) {
  seti(LED_3_X, value);
}
void set_led_4_x(int value) {
  seti(LED_4_X, value);
}
void set_led_5_x(int value) {
  seti(LED_5_X, value);
}
void set_led_0_y(int value) {
  seti(LED_0_Y, value);
}
void set_led_1_y(int value) {
  seti(LED_1_Y, value);
}
void set_led_2_y(int value) {
  seti(LED_2_Y, value);
}
void set_led_3_y(int value) {
  seti(LED_3_Y, value);
}
void set_led_4_y(int value) {
  seti(LED_4_Y, value);
}
void set_led_5_y(int value) {
  seti(LED_5_Y, value);
}
void set_led_0_z(int value) {
  seti(LED_0_Z, value);
}
void set_led_1_z(int value) {
  seti(LED_1_Z, value);
}
void set_led_2_z(int value) {
  seti(LED_2_Z, value);
}
void set_led_3_z(int value) {
  seti(LED_3_Z, value);
}
void set_led_4_z(int value) {
  seti(LED_4_Z, value);
}
void set_led_5_z(int value) {
  seti(LED_5_Z, value);
}

/*
 * [/GENERATED]
 */
