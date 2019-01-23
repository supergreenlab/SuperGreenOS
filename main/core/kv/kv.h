/*
 * Copyright (C) 2018  SuperGreenLab <towelie@supergreenlab.com>
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

#ifndef KV_H_
#define KV_H_

#include <stdlib.h>
#include <stdbool.h>
#include "keys.h"

#define MAX_KVALUE_SIZE 517

void preinit_kv();
void postinit_kv();

int geti(const char * key);
void seti(const char * key, int value);
bool hasi(const char * key);
void defaulti(const char * key, int value);

void getstr(const char * key, char *value, const size_t length);
void setstr(const char * key, const char * value);
bool hasstr(const char * key);
void defaultstr(const char * key, const char * value);

/*
 * [GENERATED]
 */

int get_wifi_status();
void set_wifi_status(int value);
void get_wifi_ssid(char *dest, size_t len);
void set_wifi_ssid(const char *value);
void get_wifi_password(char *dest, size_t len);
void set_wifi_password(const char *value);
int get_time();
void set_time(int value);
int get_n_restarts();
void set_n_restarts(int value);
int get_ota_timestamp();
void set_ota_timestamp(int value);
void get_ota_server_ip(char *dest, size_t len);
void set_ota_server_ip(const char *value);
void get_ota_server_hostname(char *dest, size_t len);
void set_ota_server_hostname(const char *value);
void get_ota_server_port(char *dest, size_t len);
void set_ota_server_port(const char *value);
void get_ota_version_filename(char *dest, size_t len);
void set_ota_version_filename(const char *value);
void get_ota_filename(char *dest, size_t len);
void set_ota_filename(const char *value);
void get_broker_url(char *dest, size_t len);
void set_broker_url(const char *value);
int get_i2c_0_sda();
void set_i2c_0_sda(int value);
int get_i2c_0_scl();
void set_i2c_0_scl(int value);
int get_i2c_0_enabled();
void set_i2c_0_enabled(int value);
int get_i2c_1_sda();
void set_i2c_1_sda(int value);
int get_i2c_1_scl();
void set_i2c_1_scl(int value);
int get_i2c_1_enabled();
void set_i2c_1_enabled(int value);
int get_state();
void set_state(int value);
void get_device_name(char *dest, size_t len);
void set_device_name(const char *value);
int get_box_0_enabled();
void set_box_0_enabled(int value);
int get_box_0_timer_type();
void set_box_0_timer_type(int value);
int get_box_0_timer_output();
void set_box_0_timer_output(int value);
int get_box_0_started_at();
void set_box_0_started_at(int value);
int get_box_0_on_hour();
void set_box_0_on_hour(int value);
int get_box_0_on_min();
void set_box_0_on_min(int value);
int get_box_0_off_hour();
void set_box_0_off_hour(int value);
int get_box_0_off_min();
void set_box_0_off_min(int value);
int get_box_0_stretch();
void set_box_0_stretch(int value);
int get_box_0_led_dim();
void set_box_0_led_dim(int value);
int get_box_0_blower();
void set_box_0_blower(int value);
int get_box_0_blower_mode();
void set_box_0_blower_mode(int value);
int get_box_0_blower_gpio();
void set_box_0_blower_gpio(int value);
int get_box_0_sht1x_temp_c();
void set_box_0_sht1x_temp_c(int value);
int get_box_0_sht1x_temp_f();
void set_box_0_sht1x_temp_f(int value);
int get_box_0_sht1x_humi();
void set_box_0_sht1x_humi(int value);
int get_box_0_arduino_co2();
void set_box_0_arduino_co2(int value);
int get_box_0_dust_gpy2y10();
void set_box_0_dust_gpy2y10(int value);
void get_box_0_led_info(char *dest, size_t len);
void set_box_0_led_info(const char *value);
int get_box_1_enabled();
void set_box_1_enabled(int value);
int get_box_1_timer_type();
void set_box_1_timer_type(int value);
int get_box_1_timer_output();
void set_box_1_timer_output(int value);
int get_box_1_started_at();
void set_box_1_started_at(int value);
int get_box_1_on_hour();
void set_box_1_on_hour(int value);
int get_box_1_on_min();
void set_box_1_on_min(int value);
int get_box_1_off_hour();
void set_box_1_off_hour(int value);
int get_box_1_off_min();
void set_box_1_off_min(int value);
int get_box_1_stretch();
void set_box_1_stretch(int value);
int get_box_1_led_dim();
void set_box_1_led_dim(int value);
int get_box_1_blower();
void set_box_1_blower(int value);
int get_box_1_blower_mode();
void set_box_1_blower_mode(int value);
int get_box_1_blower_gpio();
void set_box_1_blower_gpio(int value);
int get_box_1_sht1x_temp_c();
void set_box_1_sht1x_temp_c(int value);
int get_box_1_sht1x_temp_f();
void set_box_1_sht1x_temp_f(int value);
int get_box_1_sht1x_humi();
void set_box_1_sht1x_humi(int value);
int get_box_1_arduino_co2();
void set_box_1_arduino_co2(int value);
int get_box_1_dust_gpy2y10();
void set_box_1_dust_gpy2y10(int value);
void get_box_1_led_info(char *dest, size_t len);
void set_box_1_led_info(const char *value);
int get_box_2_enabled();
void set_box_2_enabled(int value);
int get_box_2_timer_type();
void set_box_2_timer_type(int value);
int get_box_2_timer_output();
void set_box_2_timer_output(int value);
int get_box_2_started_at();
void set_box_2_started_at(int value);
int get_box_2_on_hour();
void set_box_2_on_hour(int value);
int get_box_2_on_min();
void set_box_2_on_min(int value);
int get_box_2_off_hour();
void set_box_2_off_hour(int value);
int get_box_2_off_min();
void set_box_2_off_min(int value);
int get_box_2_stretch();
void set_box_2_stretch(int value);
int get_box_2_led_dim();
void set_box_2_led_dim(int value);
int get_box_2_blower();
void set_box_2_blower(int value);
int get_box_2_blower_mode();
void set_box_2_blower_mode(int value);
int get_box_2_blower_gpio();
void set_box_2_blower_gpio(int value);
int get_box_2_sht1x_temp_c();
void set_box_2_sht1x_temp_c(int value);
int get_box_2_sht1x_temp_f();
void set_box_2_sht1x_temp_f(int value);
int get_box_2_sht1x_humi();
void set_box_2_sht1x_humi(int value);
int get_box_2_arduino_co2();
void set_box_2_arduino_co2(int value);
int get_box_2_dust_gpy2y10();
void set_box_2_dust_gpy2y10(int value);
void get_box_2_led_info(char *dest, size_t len);
void set_box_2_led_info(const char *value);
int get_led_0_duty();
void set_led_0_duty(int value);
int get_led_1_duty();
void set_led_1_duty(int value);
int get_led_2_duty();
void set_led_2_duty(int value);
int get_led_3_duty();
void set_led_3_duty(int value);
int get_led_4_duty();
void set_led_4_duty(int value);
int get_led_5_duty();
void set_led_5_duty(int value);
int get_led_0_gpio();
void set_led_0_gpio(int value);
int get_led_1_gpio();
void set_led_1_gpio(int value);
int get_led_2_gpio();
void set_led_2_gpio(int value);
int get_led_3_gpio();
void set_led_3_gpio(int value);
int get_led_4_gpio();
void set_led_4_gpio(int value);
int get_led_5_gpio();
void set_led_5_gpio(int value);
int get_led_0_x();
void set_led_0_x(int value);
int get_led_1_x();
void set_led_1_x(int value);
int get_led_2_x();
void set_led_2_x(int value);
int get_led_3_x();
void set_led_3_x(int value);
int get_led_4_x();
void set_led_4_x(int value);
int get_led_5_x();
void set_led_5_x(int value);
int get_led_0_y();
void set_led_0_y(int value);
int get_led_1_y();
void set_led_1_y(int value);
int get_led_2_y();
void set_led_2_y(int value);
int get_led_3_y();
void set_led_3_y(int value);
int get_led_4_y();
void set_led_4_y(int value);
int get_led_5_y();
void set_led_5_y(int value);
int get_led_0_z();
void set_led_0_z(int value);
int get_led_1_z();
void set_led_1_z(int value);
int get_led_2_z();
void set_led_2_z(int value);
int get_led_3_z();
void set_led_3_z(int value);
int get_led_4_z();
void set_led_4_z(int value);
int get_led_5_z();
void set_led_5_z(int value);
int get_led_0_enabled();
void set_led_0_enabled(int value);
int get_led_1_enabled();
void set_led_1_enabled(int value);
int get_led_2_enabled();
void set_led_2_enabled(int value);
int get_led_3_enabled();
void set_led_3_enabled(int value);
int get_led_4_enabled();
void set_led_4_enabled(int value);
int get_led_5_enabled();
void set_led_5_enabled(int value);
int get_led_0_box();
void set_led_0_box(int value);
int get_led_1_box();
void set_led_1_box(int value);
int get_led_2_box();
void set_led_2_box(int value);
int get_led_3_box();
void set_led_3_box(int value);
int get_led_4_box();
void set_led_4_box(int value);
int get_led_5_box();
void set_led_5_box(int value);
int get_led_0_dim();
void set_led_0_dim(int value);
int get_led_1_dim();
void set_led_1_dim(int value);
int get_led_2_dim();
void set_led_2_dim(int value);
int get_led_3_dim();
void set_led_3_dim(int value);
int get_led_4_dim();
void set_led_4_dim(int value);
int get_led_5_dim();
void set_led_5_dim(int value);

/*
 * [/GENERATED]
 */

#endif
