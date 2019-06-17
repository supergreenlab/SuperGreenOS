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
void internal_set_wifi_ap_ssid(const char *value);
void internal_set_wifi_ap_password(const char *value);
void internal_set_mdns_domain(const char *value);
void internal_set_wifi_ip(const char *value);
void internal_set_time(int value);
void internal_set_n_restarts(int value);
void internal_set_ota_timestamp(int value);
void internal_set_ota_server_ip(const char *value);
void internal_set_ota_server_hostname(const char *value);
void internal_set_ota_server_port(const char *value);
void internal_set_ota_basedir(const char *value);
void internal_set_ota_status(int value);
void internal_set_broker_url(const char *value);
void internal_set_broker_channel(const char *value);
void internal_set_broker_clientid(const char *value);
void internal_set_i2c_0_sda(int value);
void internal_set_i2c_0_scl(int value);
void internal_set_i2c_0_enabled(int value);
void internal_set_reboot(int value);
void internal_set_state(int value);
void internal_set_device_name(const char *value);
void internal_set_status_led_red_gpio(int value);
void internal_set_status_led_green_gpio(int value);
void internal_set_status_led_dim(int value);
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
void internal_set_box_0_sht21_temp_c(int value);
void internal_set_box_0_sht21_temp_f(int value);
void internal_set_box_0_sht21_humi(int value);
void internal_set_box_0_led_info(const char *value);
void internal_set_led_0_duty(int value);
void internal_set_led_0_gpio(int value);
void internal_set_led_0_x(int value);
void internal_set_led_0_y(int value);
void internal_set_led_0_z(int value);
void internal_set_led_0_enabled(int value);
void internal_set_led_0_box(int value);
void internal_set_led_0_dim(int value);
void internal_set_led_0_fade(int value);

/*
 * [/GENERATED]
 */

#endif
