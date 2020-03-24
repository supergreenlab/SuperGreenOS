/*
 * Copyright (C) 2020  SuperGreenLab <towelie@supergreenlab.com>
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


#ifndef SHT1X_DRIVER_H_
#define SHT1X_DRIVER_H_

void setup_gpios(int sda, int sck, bool input);
void release_gpios(int sda, int sck);
void set_sda_mode(int sda, bool input);
float read_temperature_c(int sda, int sck);
float read_temperature_f(int sda, int sck);
float read_humidity(int sda, int sck);
float read_temperature_raw(int sda, int sck);
int shift_in(int data_pin, int clock_pin, int _num_bits);
void sendcommand_SHT(int command, int data_pin, int clock_pin);
void wait_for_result_SHT(int data_pin, int clock_pin);
int get_data16SHT(int data_pin, int clock_pin);
void skip_crc_SHT(int data_pin, int clock_pin);

#endif
