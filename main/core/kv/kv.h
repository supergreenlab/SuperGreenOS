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

void open_kv();
void preinit_kv();
void postinit_kv();
void reset_defaults();

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

void reset_wifi_status_changed();
bool is_wifi_status_changed();
bool is_wifi_status_undefined();
int get_wifi_status();
void set_wifi_status(int value);
void reset_wifi_ssid_changed();
bool is_wifi_ssid_changed();
bool is_wifi_ssid_undefined();
void get_wifi_ssid(char *dest, size_t len);
void set_wifi_ssid(const char *value);
void reset_wifi_password_changed();
bool is_wifi_password_changed();
bool is_wifi_password_undefined();
void get_wifi_password(char *dest, size_t len);
void set_wifi_password(const char *value);
void reset_wifi_ap_ssid_changed();
bool is_wifi_ap_ssid_changed();
bool is_wifi_ap_ssid_undefined();
void get_wifi_ap_ssid(char *dest, size_t len);
void set_wifi_ap_ssid(const char *value);
void reset_wifi_ap_password_changed();
bool is_wifi_ap_password_changed();
bool is_wifi_ap_password_undefined();
void get_wifi_ap_password(char *dest, size_t len);
void set_wifi_ap_password(const char *value);
void reset_mdns_domain_changed();
bool is_mdns_domain_changed();
bool is_mdns_domain_undefined();
void get_mdns_domain(char *dest, size_t len);
void set_mdns_domain(const char *value);
void reset_wifi_ip_changed();
bool is_wifi_ip_changed();
bool is_wifi_ip_undefined();
void get_wifi_ip(char *dest, size_t len);
void set_wifi_ip(const char *value);
void reset_time_changed();
bool is_time_changed();
bool is_time_undefined();
int get_time();
void set_time(int value);
void reset_n_restarts_changed();
bool is_n_restarts_changed();
bool is_n_restarts_undefined();
int get_n_restarts();
void set_n_restarts(int value);
void reset_ota_timestamp_changed();
bool is_ota_timestamp_changed();
bool is_ota_timestamp_undefined();
int get_ota_timestamp();
void set_ota_timestamp(int value);
void reset_ota_server_ip_changed();
bool is_ota_server_ip_changed();
bool is_ota_server_ip_undefined();
void get_ota_server_ip(char *dest, size_t len);
void set_ota_server_ip(const char *value);
void reset_ota_server_hostname_changed();
bool is_ota_server_hostname_changed();
bool is_ota_server_hostname_undefined();
void get_ota_server_hostname(char *dest, size_t len);
void set_ota_server_hostname(const char *value);
void reset_ota_server_port_changed();
bool is_ota_server_port_changed();
bool is_ota_server_port_undefined();
void get_ota_server_port(char *dest, size_t len);
void set_ota_server_port(const char *value);
void reset_ota_basedir_changed();
bool is_ota_basedir_changed();
bool is_ota_basedir_undefined();
void get_ota_basedir(char *dest, size_t len);
void set_ota_basedir(const char *value);
void reset_ota_status_changed();
bool is_ota_status_changed();
bool is_ota_status_undefined();
int get_ota_status();
void set_ota_status(int value);
void reset_broker_url_changed();
bool is_broker_url_changed();
bool is_broker_url_undefined();
void get_broker_url(char *dest, size_t len);
void set_broker_url(const char *value);
void reset_broker_channel_changed();
bool is_broker_channel_changed();
bool is_broker_channel_undefined();
void get_broker_channel(char *dest, size_t len);
void set_broker_channel(const char *value);
void reset_broker_clientid_changed();
bool is_broker_clientid_changed();
bool is_broker_clientid_undefined();
void get_broker_clientid(char *dest, size_t len);
void set_broker_clientid(const char *value);
void reset_i2c_0_sda_changed();
bool is_i2c_0_sda_changed();
bool is_i2c_0_sda_undefined();
int get_i2c_0_sda();
void set_i2c_0_sda(int value);
void reset_i2c_0_scl_changed();
bool is_i2c_0_scl_changed();
bool is_i2c_0_scl_undefined();
int get_i2c_0_scl();
void set_i2c_0_scl(int value);
void reset_i2c_0_enabled_changed();
bool is_i2c_0_enabled_changed();
bool is_i2c_0_enabled_undefined();
int get_i2c_0_enabled();
void set_i2c_0_enabled(int value);
void reset_reboot_changed();
bool is_reboot_changed();
bool is_reboot_undefined();
int get_reboot();
void set_reboot(int value);
void reset_state_changed();
bool is_state_changed();
bool is_state_undefined();
int get_state();
void set_state(int value);
void reset_device_name_changed();
bool is_device_name_changed();
bool is_device_name_undefined();
void get_device_name(char *dest, size_t len);
void set_device_name(const char *value);
void reset_status_led_red_gpio_changed();
bool is_status_led_red_gpio_changed();
bool is_status_led_red_gpio_undefined();
int get_status_led_red_gpio();
void set_status_led_red_gpio(int value);
void reset_status_led_green_gpio_changed();
bool is_status_led_green_gpio_changed();
bool is_status_led_green_gpio_undefined();
int get_status_led_green_gpio();
void set_status_led_green_gpio(int value);
void reset_status_led_dim_changed();
bool is_status_led_dim_changed();
bool is_status_led_dim_undefined();
int get_status_led_dim();
void set_status_led_dim(int value);
void reset_box_0_enabled_changed();
bool is_box_0_enabled_changed();
bool is_box_0_enabled_undefined();
int get_box_0_enabled();
void set_box_0_enabled(int value);
void reset_box_0_timer_type_changed();
bool is_box_0_timer_type_changed();
bool is_box_0_timer_type_undefined();
int get_box_0_timer_type();
void set_box_0_timer_type(int value);
void reset_box_0_timer_output_changed();
bool is_box_0_timer_output_changed();
bool is_box_0_timer_output_undefined();
int get_box_0_timer_output();
void set_box_0_timer_output(int value);
void reset_box_0_started_at_changed();
bool is_box_0_started_at_changed();
bool is_box_0_started_at_undefined();
int get_box_0_started_at();
void set_box_0_started_at(int value);
void reset_box_0_on_hour_changed();
bool is_box_0_on_hour_changed();
bool is_box_0_on_hour_undefined();
int get_box_0_on_hour();
void set_box_0_on_hour(int value);
void reset_box_0_on_min_changed();
bool is_box_0_on_min_changed();
bool is_box_0_on_min_undefined();
int get_box_0_on_min();
void set_box_0_on_min(int value);
void reset_box_0_off_hour_changed();
bool is_box_0_off_hour_changed();
bool is_box_0_off_hour_undefined();
int get_box_0_off_hour();
void set_box_0_off_hour(int value);
void reset_box_0_off_min_changed();
bool is_box_0_off_min_changed();
bool is_box_0_off_min_undefined();
int get_box_0_off_min();
void set_box_0_off_min(int value);
void reset_box_0_stretch_changed();
bool is_box_0_stretch_changed();
bool is_box_0_stretch_undefined();
int get_box_0_stretch();
void set_box_0_stretch(int value);
void reset_box_0_led_dim_changed();
bool is_box_0_led_dim_changed();
bool is_box_0_led_dim_undefined();
int get_box_0_led_dim();
void set_box_0_led_dim(int value);
void reset_box_0_blower_day_changed();
bool is_box_0_blower_day_changed();
bool is_box_0_blower_day_undefined();
int get_box_0_blower_day();
void set_box_0_blower_day(int value);
void reset_box_0_blower_night_changed();
bool is_box_0_blower_night_changed();
bool is_box_0_blower_night_undefined();
int get_box_0_blower_night();
void set_box_0_blower_night(int value);
void reset_box_0_blower_gpio_changed();
bool is_box_0_blower_gpio_changed();
bool is_box_0_blower_gpio_undefined();
int get_box_0_blower_gpio();
void set_box_0_blower_gpio(int value);
void reset_box_0_blower_frequency_changed();
bool is_box_0_blower_frequency_changed();
bool is_box_0_blower_frequency_undefined();
int get_box_0_blower_frequency();
void set_box_0_blower_frequency(int value);
void reset_box_0_blower_enabled_changed();
bool is_box_0_blower_enabled_changed();
bool is_box_0_blower_enabled_undefined();
int get_box_0_blower_enabled();
void set_box_0_blower_enabled(int value);
void reset_box_0_sht21_temp_c_changed();
bool is_box_0_sht21_temp_c_changed();
bool is_box_0_sht21_temp_c_undefined();
int get_box_0_sht21_temp_c();
void set_box_0_sht21_temp_c(int value);
void reset_box_0_sht21_temp_f_changed();
bool is_box_0_sht21_temp_f_changed();
bool is_box_0_sht21_temp_f_undefined();
int get_box_0_sht21_temp_f();
void set_box_0_sht21_temp_f(int value);
void reset_box_0_sht21_humi_changed();
bool is_box_0_sht21_humi_changed();
bool is_box_0_sht21_humi_undefined();
int get_box_0_sht21_humi();
void set_box_0_sht21_humi(int value);
void reset_box_0_led_info_changed();
bool is_box_0_led_info_changed();
bool is_box_0_led_info_undefined();
void get_box_0_led_info(char *dest, size_t len);
void set_box_0_led_info(const char *value);
void reset_led_0_duty_changed();
bool is_led_0_duty_changed();
bool is_led_0_duty_undefined();
int get_led_0_duty();
void set_led_0_duty(int value);
void reset_led_0_gpio_changed();
bool is_led_0_gpio_changed();
bool is_led_0_gpio_undefined();
int get_led_0_gpio();
void set_led_0_gpio(int value);
void reset_led_0_x_changed();
bool is_led_0_x_changed();
bool is_led_0_x_undefined();
int get_led_0_x();
void set_led_0_x(int value);
void reset_led_0_y_changed();
bool is_led_0_y_changed();
bool is_led_0_y_undefined();
int get_led_0_y();
void set_led_0_y(int value);
void reset_led_0_z_changed();
bool is_led_0_z_changed();
bool is_led_0_z_undefined();
int get_led_0_z();
void set_led_0_z(int value);
void reset_led_0_enabled_changed();
bool is_led_0_enabled_changed();
bool is_led_0_enabled_undefined();
int get_led_0_enabled();
void set_led_0_enabled(int value);
void reset_led_0_box_changed();
bool is_led_0_box_changed();
bool is_led_0_box_undefined();
int get_led_0_box();
void set_led_0_box(int value);
void reset_led_0_dim_changed();
bool is_led_0_dim_changed();
bool is_led_0_dim_undefined();
int get_led_0_dim();
void set_led_0_dim(int value);
void reset_led_0_fade_changed();
bool is_led_0_fade_changed();
bool is_led_0_fade_undefined();
int get_led_0_fade();
void set_led_0_fade(int value);

/*
 * [/GENERATED]
 */

#endif
