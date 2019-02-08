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

#ifndef KV_HELPERS_INTERNAL_H_
#define KV_HELPERS_INTERNAL_H_

/*
 * [GENERATED]
 */

void internal_set_wifi_status(int value);
void internal_set_wifi_ssid(const char *value);
void internal_set_wifi_password(const char *value);
void internal_set_wifi_ip(const char *value);
void internal_set_time(int value);
void internal_set_n_restarts(int value);
void internal_set_ota_timestamp(int value);
void internal_set_ota_server_ip(const char *value);
void internal_set_ota_server_hostname(const char *value);
void internal_set_ota_server_port(const char *value);
void internal_set_ota_version_filename(const char *value);
void internal_set_ota_filename(const char *value);
void internal_set_broker_url(const char *value);
void internal_set_broker_channel(const char *value);
void internal_set_broker_clientid(const char *value);
void internal_set_i2c_0_sda(int value);
void internal_set_i2c_0_scl(int value);
void internal_set_i2c_0_enabled(int value);
void internal_set_i2c_1_sda(int value);
void internal_set_i2c_1_scl(int value);
void internal_set_i2c_1_enabled(int value);
void internal_set_state(int value);
void internal_set_device_name(const char *value);
void internal_set_box_0_enabled(int value);
void internal_set_box_0_timer_type(int value);
void internal_set_box_0_timer_output(int value);
void internal_set_box_0_started_at(int value);
void internal_set_box_0_on_hour(int value);
void internal_set_box_0_on_min(int value);
void internal_set_box_0_off_hour(int value);
void internal_set_box_0_off_min(int value);
void internal_set_box_0_stretch(int value);
void internal_set_box_0_led_dim(int value);
void internal_set_box_0_blower(int value);
void internal_set_box_0_blower_mode(int value);
void internal_set_box_0_blower_gpio(int value);
void internal_set_box_0_blower_enabled(int value);
void internal_set_box_0_sht1x_temp_c(int value);
void internal_set_box_0_sht1x_temp_f(int value);
void internal_set_box_0_sht1x_humi(int value);
void internal_set_box_0_sht21_temp_c(int value);
void internal_set_box_0_sht21_temp_f(int value);
void internal_set_box_0_sht21_humi(int value);
void internal_set_box_0_arduino_co2(int value);
void internal_set_box_0_dust_gpy2y10(int value);
void internal_set_box_0_led_info(const char *value);
void internal_set_box_1_enabled(int value);
void internal_set_box_1_timer_type(int value);
void internal_set_box_1_timer_output(int value);
void internal_set_box_1_started_at(int value);
void internal_set_box_1_on_hour(int value);
void internal_set_box_1_on_min(int value);
void internal_set_box_1_off_hour(int value);
void internal_set_box_1_off_min(int value);
void internal_set_box_1_stretch(int value);
void internal_set_box_1_led_dim(int value);
void internal_set_box_1_blower(int value);
void internal_set_box_1_blower_mode(int value);
void internal_set_box_1_blower_gpio(int value);
void internal_set_box_1_blower_enabled(int value);
void internal_set_box_1_sht1x_temp_c(int value);
void internal_set_box_1_sht1x_temp_f(int value);
void internal_set_box_1_sht1x_humi(int value);
void internal_set_box_1_sht21_temp_c(int value);
void internal_set_box_1_sht21_temp_f(int value);
void internal_set_box_1_sht21_humi(int value);
void internal_set_box_1_arduino_co2(int value);
void internal_set_box_1_dust_gpy2y10(int value);
void internal_set_box_1_led_info(const char *value);
void internal_set_box_2_enabled(int value);
void internal_set_box_2_timer_type(int value);
void internal_set_box_2_timer_output(int value);
void internal_set_box_2_started_at(int value);
void internal_set_box_2_on_hour(int value);
void internal_set_box_2_on_min(int value);
void internal_set_box_2_off_hour(int value);
void internal_set_box_2_off_min(int value);
void internal_set_box_2_stretch(int value);
void internal_set_box_2_led_dim(int value);
void internal_set_box_2_blower(int value);
void internal_set_box_2_blower_mode(int value);
void internal_set_box_2_blower_gpio(int value);
void internal_set_box_2_blower_enabled(int value);
void internal_set_box_2_sht1x_temp_c(int value);
void internal_set_box_2_sht1x_temp_f(int value);
void internal_set_box_2_sht1x_humi(int value);
void internal_set_box_2_sht21_temp_c(int value);
void internal_set_box_2_sht21_temp_f(int value);
void internal_set_box_2_sht21_humi(int value);
void internal_set_box_2_arduino_co2(int value);
void internal_set_box_2_dust_gpy2y10(int value);
void internal_set_box_2_led_info(const char *value);
void internal_set_led_0_duty(int value);
void internal_set_led_1_duty(int value);
void internal_set_led_2_duty(int value);
void internal_set_led_3_duty(int value);
void internal_set_led_4_duty(int value);
void internal_set_led_5_duty(int value);
void internal_set_led_0_gpio(int value);
void internal_set_led_1_gpio(int value);
void internal_set_led_2_gpio(int value);
void internal_set_led_3_gpio(int value);
void internal_set_led_4_gpio(int value);
void internal_set_led_5_gpio(int value);
void internal_set_led_0_x(int value);
void internal_set_led_1_x(int value);
void internal_set_led_2_x(int value);
void internal_set_led_3_x(int value);
void internal_set_led_4_x(int value);
void internal_set_led_5_x(int value);
void internal_set_led_0_y(int value);
void internal_set_led_1_y(int value);
void internal_set_led_2_y(int value);
void internal_set_led_3_y(int value);
void internal_set_led_4_y(int value);
void internal_set_led_5_y(int value);
void internal_set_led_0_z(int value);
void internal_set_led_1_z(int value);
void internal_set_led_2_z(int value);
void internal_set_led_3_z(int value);
void internal_set_led_4_z(int value);
void internal_set_led_5_z(int value);
void internal_set_led_0_enabled(int value);
void internal_set_led_1_enabled(int value);
void internal_set_led_2_enabled(int value);
void internal_set_led_3_enabled(int value);
void internal_set_led_4_enabled(int value);
void internal_set_led_5_enabled(int value);
void internal_set_led_0_box(int value);
void internal_set_led_1_box(int value);
void internal_set_led_2_box(int value);
void internal_set_led_3_box(int value);
void internal_set_led_4_box(int value);
void internal_set_led_5_box(int value);
void internal_set_led_0_dim(int value);
void internal_set_led_1_dim(int value);
void internal_set_led_2_dim(int value);
void internal_set_led_3_dim(int value);
void internal_set_led_4_dim(int value);
void internal_set_led_5_dim(int value);

/*
 * [/GENERATED]
 */

#endif
