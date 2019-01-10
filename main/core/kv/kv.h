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

void set_wifi_status(int value);
void set_wifi_ssid(const char *value);
void set_wifi_password(const char *value);
void set_time(int value);
void set_ota_timestamp(int value);
void set_ota_server_ip(const char *value);
void set_ota_server_hostname(const char *value);
void set_ota_server_port(const char *value);
void set_ota_version_filename(const char *value);
void set_ota_filename(const char *value);
void set_mqtt_broker_url(const char *value);
void set_broker_url(const char *value);
void set_i2c_sda(int value);
void set_i2c_scl(int value);
void set_state(int value);
void set_device_name(const char *value);
void set_timer_type(int value);
void set_timer_output(int value);
void set_started_at(int value);
void set_on_hour(int value);
void set_on_min(int value);
void set_off_hour(int value);
void set_off_min(int value);
void set_stretch(int value);
void set_led_dim(int value);
void set_blower(int value);
void set_blower_gpio(int value);
void set_sht1x_temp_c(int value);
void set_sht1x_temp_f(int value);
void set_sht1x_humi(int value);
void set_led_info(const char *value);
void set_led_0_duty(int value);
void set_led_1_duty(int value);
void set_led_2_duty(int value);
void set_led_3_duty(int value);
void set_led_4_duty(int value);
void set_led_5_duty(int value);
void set_led_0_gpio(int value);
void set_led_1_gpio(int value);
void set_led_2_gpio(int value);
void set_led_3_gpio(int value);
void set_led_4_gpio(int value);
void set_led_5_gpio(int value);
void set_led_0_x(int value);
void set_led_1_x(int value);
void set_led_2_x(int value);
void set_led_3_x(int value);
void set_led_4_x(int value);
void set_led_5_x(int value);
void set_led_0_y(int value);
void set_led_1_y(int value);
void set_led_2_y(int value);
void set_led_3_y(int value);
void set_led_4_y(int value);
void set_led_5_y(int value);
void set_led_0_z(int value);
void set_led_1_z(int value);
void set_led_2_z(int value);
void set_led_3_z(int value);
void set_led_4_z(int value);
void set_led_5_z(int value);

/*
 * [/GENERATED]
 */

#endif
