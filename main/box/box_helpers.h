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

#ifndef BOX_HELPERS_H_
#define BOX_HELPERS_H_

#define BOX_CB_H(boxId, param) int on_set_box_## boxId ##_## param( int value);
#define BOX_GETTER_H(param) int get_box_## param(int boxId);
#define BOX_SETTER_H(param) void set_box_## param(int boxId, int value);

BOX_CB_H(0, enabled)
BOX_CB_H(0, timer_type)
BOX_CB_H(0, timer_output)
BOX_CB_H(0, started_at)
BOX_CB_H(0, on_hour)
BOX_CB_H(0, on_min)
BOX_CB_H(0, off_hour)
BOX_CB_H(0, off_min)
BOX_CB_H(0, stretch)
BOX_CB_H(0, led_dim)
BOX_CB_H(0, blower_day)
BOX_CB_H(0, blower_night)
BOX_CB_H(0, blower_gpio)
BOX_CB_H(0, blower_frequency)
BOX_CB_H(0, blower_enabled)
BOX_CB_H(0, sht1x_temp_c)
BOX_CB_H(0, sht1x_temp_f)
BOX_CB_H(0, sht1x_humi)
BOX_CB_H(0, sht21_temp_c)
BOX_CB_H(0, sht21_temp_f)
BOX_CB_H(0, sht21_humi)
BOX_CB_H(0, arduino_co2)
BOX_CB_H(0, dust_gpy2y10)
BOX_CB_H(0, led_info)
BOX_CB_H(1, enabled)
BOX_CB_H(1, timer_type)
BOX_CB_H(1, timer_output)
BOX_CB_H(1, started_at)
BOX_CB_H(1, on_hour)
BOX_CB_H(1, on_min)
BOX_CB_H(1, off_hour)
BOX_CB_H(1, off_min)
BOX_CB_H(1, stretch)
BOX_CB_H(1, led_dim)
BOX_CB_H(1, blower_day)
BOX_CB_H(1, blower_night)
BOX_CB_H(1, blower_gpio)
BOX_CB_H(1, blower_frequency)
BOX_CB_H(1, blower_enabled)
BOX_CB_H(1, sht1x_temp_c)
BOX_CB_H(1, sht1x_temp_f)
BOX_CB_H(1, sht1x_humi)
BOX_CB_H(1, sht21_temp_c)
BOX_CB_H(1, sht21_temp_f)
BOX_CB_H(1, sht21_humi)
BOX_CB_H(1, arduino_co2)
BOX_CB_H(1, dust_gpy2y10)
BOX_CB_H(1, led_info)
BOX_CB_H(2, enabled)
BOX_CB_H(2, timer_type)
BOX_CB_H(2, timer_output)
BOX_CB_H(2, started_at)
BOX_CB_H(2, on_hour)
BOX_CB_H(2, on_min)
BOX_CB_H(2, off_hour)
BOX_CB_H(2, off_min)
BOX_CB_H(2, stretch)
BOX_CB_H(2, led_dim)
BOX_CB_H(2, blower_day)
BOX_CB_H(2, blower_night)
BOX_CB_H(2, blower_gpio)
BOX_CB_H(2, blower_frequency)
BOX_CB_H(2, blower_enabled)
BOX_CB_H(2, sht1x_temp_c)
BOX_CB_H(2, sht1x_temp_f)
BOX_CB_H(2, sht1x_humi)
BOX_CB_H(2, sht21_temp_c)
BOX_CB_H(2, sht21_temp_f)
BOX_CB_H(2, sht21_humi)
BOX_CB_H(2, arduino_co2)
BOX_CB_H(2, dust_gpy2y10)
BOX_CB_H(2, led_info)

BOX_SETTER_H(enabled)
BOX_GETTER_H(enabled)
BOX_SETTER_H(timer_type)
BOX_GETTER_H(timer_type)
BOX_SETTER_H(timer_output)
BOX_GETTER_H(timer_output)
BOX_SETTER_H(started_at)
BOX_GETTER_H(started_at)
BOX_SETTER_H(on_hour)
BOX_GETTER_H(on_hour)
BOX_SETTER_H(on_min)
BOX_GETTER_H(on_min)
BOX_SETTER_H(off_hour)
BOX_GETTER_H(off_hour)
BOX_SETTER_H(off_min)
BOX_GETTER_H(off_min)
BOX_SETTER_H(stretch)
BOX_GETTER_H(stretch)
BOX_SETTER_H(led_dim)
BOX_GETTER_H(led_dim)
BOX_SETTER_H(blower_day)
BOX_GETTER_H(blower_day)
BOX_SETTER_H(blower_night)
BOX_GETTER_H(blower_night)
BOX_SETTER_H(blower_gpio)
BOX_GETTER_H(blower_gpio)
BOX_SETTER_H(blower_frequency)
BOX_GETTER_H(blower_frequency)
BOX_SETTER_H(blower_enabled)
BOX_GETTER_H(blower_enabled)
BOX_SETTER_H(sht21_temp_c)
BOX_GETTER_H(sht21_temp_c)
BOX_SETTER_H(sht21_temp_f)
BOX_GETTER_H(sht21_temp_f)
BOX_SETTER_H(sht21_humi)
BOX_GETTER_H(sht21_humi)

#endif
