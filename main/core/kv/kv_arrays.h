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

#include <stdint.h>


    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    
      int on_set_box_0_blower_day(int value);
    

    
      int on_set_box_1_blower_day(int value);
    

    
      int on_set_box_2_blower_day(int value);
    

    
      int on_set_box_0_blower_night(int value);
    

    
      int on_set_box_1_blower_night(int value);
    

    
      int on_set_box_2_blower_night(int value);
    

    

    

    

    
      int on_set_box_0_blower_frequency(int value);
    

    
      int on_set_box_1_blower_frequency(int value);
    

    
      int on_set_box_2_blower_frequency(int value);
    

    

    

    

    
      int on_set_box_0_stretch(int value);
    

    
      int on_set_box_1_stretch(int value);
    

    
      int on_set_box_2_stretch(int value);
    

    
      int on_set_box_0_led_dim(int value);
    

    
      int on_set_box_1_led_dim(int value);
    

    
      int on_set_box_2_led_dim(int value);
    

    

    

    

    
      int on_set_led_0_duty(int value);
    

    
      int on_set_led_1_duty(int value);
    

    
      int on_set_led_2_duty(int value);
    

    
      int on_set_led_3_duty(int value);
    

    
      int on_set_led_4_duty(int value);
    

    
      int on_set_led_5_duty(int value);
    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    



  int8_t get_i2c_sda(int i);
  void set_i2c_sda(int i, int8_t v);

  int8_t get_i2c_scl(int i);
  void set_i2c_scl(int i, int8_t v);

  int8_t get_i2c_enabled(int i);
  void set_i2c_enabled(int i, int8_t v);

  int8_t get_box_timer_type(int i);
  void set_box_timer_type(int i, int8_t v);

  int8_t get_box_timer_output(int i);
  void set_box_timer_output(int i, int8_t v);

  int8_t get_box_enabled(int i);
  void set_box_enabled(int i, int8_t v);

  int32_t get_box_started_at(int i);
  void set_box_started_at(int i, int32_t v);

  int8_t get_box_on_hour(int i);
  void set_box_on_hour(int i, int8_t v);

  int8_t get_box_on_min(int i);
  void set_box_on_min(int i, int8_t v);

  int8_t get_box_off_hour(int i);
  void set_box_off_hour(int i, int8_t v);

  int8_t get_box_off_min(int i);
  void set_box_off_min(int i, int8_t v);

  int8_t get_box_blower_day(int i);
  void set_box_blower_day(int i, int8_t v);

  int8_t get_box_blower_night(int i);
  void set_box_blower_night(int i, int8_t v);

  int8_t get_box_blower_gpio(int i);
  void set_box_blower_gpio(int i, int8_t v);

  int16_t get_box_blower_frequency(int i);
  void set_box_blower_frequency(int i, int16_t v);

  int8_t get_box_blower_enabled(int i);
  void set_box_blower_enabled(int i, int8_t v);

  int8_t get_box_stretch(int i);
  void set_box_stretch(int i, int8_t v);

  int8_t get_box_led_dim(int i);
  void set_box_led_dim(int i, int8_t v);

  int8_t get_box_sht21_temp_c(int i);
  void set_box_sht21_temp_c(int i, int8_t v);

  int8_t get_box_sht21_temp_f(int i);
  void set_box_sht21_temp_f(int i, int8_t v);

  int8_t get_box_sht21_humi(int i);
  void set_box_sht21_humi(int i, int8_t v);

  int8_t get_led_enabled(int i);
  void set_led_enabled(int i, int8_t v);

  int8_t get_led_duty(int i);
  void set_led_duty(int i, int8_t v);

  int8_t get_led_gpio(int i);
  void set_led_gpio(int i, int8_t v);

  int8_t get_led_x(int i);
  void set_led_x(int i, int8_t v);

  int8_t get_led_y(int i);
  void set_led_y(int i, int8_t v);

  int8_t get_led_z(int i);
  void set_led_z(int i, int8_t v);

  int8_t get_led_box(int i);
  void set_led_box(int i, int8_t v);

  int8_t get_led_dim(int i);
  void set_led_dim(int i, int8_t v);

  int8_t get_led_fade(int i);
  void set_led_fade(int i, int8_t v);


#endif

