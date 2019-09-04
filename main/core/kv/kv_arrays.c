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

#include "kv.h"
#include "../include_modules.h"
#include <stdint.h>


    int on_set_led_0_duty(int value) {
      return on_set_led_duty(0, value);
    }

    int on_set_led_1_duty(int value) {
      return on_set_led_duty(1, value);
    }

    int on_set_led_2_duty(int value) {
      return on_set_led_duty(2, value);
    }

    int on_set_led_3_duty(int value) {
      return on_set_led_duty(3, value);
    }

    int on_set_led_4_duty(int value) {
      return on_set_led_duty(4, value);
    }

    int on_set_led_5_duty(int value) {
      return on_set_led_duty(5, value);
    }

    int on_set_led_0_dim(int value) {
      return on_set_led_dim(0, value);
    }

    int on_set_led_1_dim(int value) {
      return on_set_led_dim(1, value);
    }

    int on_set_led_2_dim(int value) {
      return on_set_led_dim(2, value);
    }

    int on_set_led_3_dim(int value) {
      return on_set_led_dim(3, value);
    }

    int on_set_led_4_dim(int value) {
      return on_set_led_dim(4, value);
    }

    int on_set_led_5_dim(int value) {
      return on_set_led_dim(5, value);
    }

    int on_set_motor_0_frequency(int value) {
      return on_set_motor_frequency(0, value);
    }

    int on_set_motor_1_frequency(int value) {
      return on_set_motor_frequency(1, value);
    }

    int on_set_motor_2_frequency(int value) {
      return on_set_motor_frequency(2, value);
    }

    int on_set_box_0_timer_type(int value) {
      return on_set_box_timer_type(0, value);
    }

    int on_set_box_1_timer_type(int value) {
      return on_set_box_timer_type(1, value);
    }

    int on_set_box_2_timer_type(int value) {
      return on_set_box_timer_type(2, value);
    }

    int on_set_box_0_blower_day(int value) {
      return on_set_box_blower_day(0, value);
    }

    int on_set_box_1_blower_day(int value) {
      return on_set_box_blower_day(1, value);
    }

    int on_set_box_2_blower_day(int value) {
      return on_set_box_blower_day(2, value);
    }

    int on_set_box_0_blower_night(int value) {
      return on_set_box_blower_night(0, value);
    }

    int on_set_box_1_blower_night(int value) {
      return on_set_box_blower_night(1, value);
    }

    int on_set_box_2_blower_night(int value) {
      return on_set_box_blower_night(2, value);
    }

    int on_set_box_0_stretch(int value) {
      return on_set_box_stretch(0, value);
    }

    int on_set_box_1_stretch(int value) {
      return on_set_box_stretch(1, value);
    }

    int on_set_box_2_stretch(int value) {
      return on_set_box_stretch(2, value);
    }

    int on_set_box_0_led_dim(int value) {
      return on_set_box_led_dim(0, value);
    }

    int on_set_box_1_led_dim(int value) {
      return on_set_box_led_dim(1, value);
    }

    int on_set_box_2_led_dim(int value) {
      return on_set_box_led_dim(2, value);
    }




    int8_t get_i2c_sda(int i) {
      switch(i) {
      
        case 0:
          return get_i2c_0_sda();
      
        case 1:
          return get_i2c_1_sda();
      
        case 2:
          return get_i2c_2_sda();
      
      }
      return 0;
    }

    int8_t get_i2c_scl(int i) {
      switch(i) {
      
        case 0:
          return get_i2c_0_scl();
      
        case 1:
          return get_i2c_1_scl();
      
        case 2:
          return get_i2c_2_scl();
      
      }
      return 0;
    }

    int8_t get_i2c_enabled(int i) {
      switch(i) {
      
        case 0:
          return get_i2c_0_enabled();
      
        case 1:
          return get_i2c_1_enabled();
      
        case 2:
          return get_i2c_2_enabled();
      
      }
      return 0;
    }

    int8_t get_i2c_port(int i) {
      switch(i) {
      
        case 0:
          return get_i2c_0_port();
      
        case 1:
          return get_i2c_1_port();
      
        case 2:
          return get_i2c_2_port();
      
      }
      return 0;
    }

    int8_t get_led_enabled(int i) {
      switch(i) {
      
        case 0:
          return get_led_0_enabled();
      
        case 1:
          return get_led_1_enabled();
      
        case 2:
          return get_led_2_enabled();
      
        case 3:
          return get_led_3_enabled();
      
        case 4:
          return get_led_4_enabled();
      
        case 5:
          return get_led_5_enabled();
      
      }
      return 0;
    }

    int8_t get_led_duty(int i) {
      switch(i) {
      
        case 0:
          return get_led_0_duty();
      
        case 1:
          return get_led_1_duty();
      
        case 2:
          return get_led_2_duty();
      
        case 3:
          return get_led_3_duty();
      
        case 4:
          return get_led_4_duty();
      
        case 5:
          return get_led_5_duty();
      
      }
      return 0;
    }

    int8_t get_led_gpio(int i) {
      switch(i) {
      
        case 0:
          return get_led_0_gpio();
      
        case 1:
          return get_led_1_gpio();
      
        case 2:
          return get_led_2_gpio();
      
        case 3:
          return get_led_3_gpio();
      
        case 4:
          return get_led_4_gpio();
      
        case 5:
          return get_led_5_gpio();
      
      }
      return 0;
    }

    int8_t get_led_x(int i) {
      switch(i) {
      
        case 0:
          return get_led_0_x();
      
        case 1:
          return get_led_1_x();
      
        case 2:
          return get_led_2_x();
      
        case 3:
          return get_led_3_x();
      
        case 4:
          return get_led_4_x();
      
        case 5:
          return get_led_5_x();
      
      }
      return 0;
    }

    int8_t get_led_y(int i) {
      switch(i) {
      
        case 0:
          return get_led_0_y();
      
        case 1:
          return get_led_1_y();
      
        case 2:
          return get_led_2_y();
      
        case 3:
          return get_led_3_y();
      
        case 4:
          return get_led_4_y();
      
        case 5:
          return get_led_5_y();
      
      }
      return 0;
    }

    int8_t get_led_z(int i) {
      switch(i) {
      
        case 0:
          return get_led_0_z();
      
        case 1:
          return get_led_1_z();
      
        case 2:
          return get_led_2_z();
      
        case 3:
          return get_led_3_z();
      
        case 4:
          return get_led_4_z();
      
        case 5:
          return get_led_5_z();
      
      }
      return 0;
    }

    int8_t get_led_box(int i) {
      switch(i) {
      
        case 0:
          return get_led_0_box();
      
        case 1:
          return get_led_1_box();
      
        case 2:
          return get_led_2_box();
      
        case 3:
          return get_led_3_box();
      
        case 4:
          return get_led_4_box();
      
        case 5:
          return get_led_5_box();
      
      }
      return 0;
    }

    int8_t get_led_dim(int i) {
      switch(i) {
      
        case 0:
          return get_led_0_dim();
      
        case 1:
          return get_led_1_dim();
      
        case 2:
          return get_led_2_dim();
      
        case 3:
          return get_led_3_dim();
      
        case 4:
          return get_led_4_dim();
      
        case 5:
          return get_led_5_dim();
      
      }
      return 0;
    }

    int8_t get_led_fade(int i) {
      switch(i) {
      
        case 0:
          return get_led_0_fade();
      
        case 1:
          return get_led_1_fade();
      
        case 2:
          return get_led_2_fade();
      
        case 3:
          return get_led_3_fade();
      
        case 4:
          return get_led_4_fade();
      
        case 5:
          return get_led_5_fade();
      
      }
      return 0;
    }

    int8_t get_box_on_hour(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_on_hour();
      
        case 1:
          return get_box_1_on_hour();
      
        case 2:
          return get_box_2_on_hour();
      
      }
      return 0;
    }

    int8_t get_box_on_min(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_on_min();
      
        case 1:
          return get_box_1_on_min();
      
        case 2:
          return get_box_2_on_min();
      
      }
      return 0;
    }

    int8_t get_box_off_hour(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_off_hour();
      
        case 1:
          return get_box_1_off_hour();
      
        case 2:
          return get_box_2_off_hour();
      
      }
      return 0;
    }

    int8_t get_box_off_min(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_off_min();
      
        case 1:
          return get_box_1_off_min();
      
        case 2:
          return get_box_2_off_min();
      
      }
      return 0;
    }

    int8_t get_box_timer_type(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_timer_type();
      
        case 1:
          return get_box_1_timer_type();
      
        case 2:
          return get_box_2_timer_type();
      
      }
      return 0;
    }

    int8_t get_box_timer_output(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_timer_output();
      
        case 1:
          return get_box_1_timer_output();
      
        case 2:
          return get_box_2_timer_output();
      
      }
      return 0;
    }

    int8_t get_box_blower_duty(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_blower_duty();
      
        case 1:
          return get_box_1_blower_duty();
      
        case 2:
          return get_box_2_blower_duty();
      
      }
      return 0;
    }

    int8_t get_box_blower_day(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_blower_day();
      
        case 1:
          return get_box_1_blower_day();
      
        case 2:
          return get_box_2_blower_day();
      
      }
      return 0;
    }

    int8_t get_box_blower_night(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_blower_night();
      
        case 1:
          return get_box_1_blower_night();
      
        case 2:
          return get_box_2_blower_night();
      
      }
      return 0;
    }

    int8_t get_box_blower_enabled(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_blower_enabled();
      
        case 1:
          return get_box_1_blower_enabled();
      
        case 2:
          return get_box_2_blower_enabled();
      
      }
      return 0;
    }

    int8_t get_box_stretch(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_stretch();
      
        case 1:
          return get_box_1_stretch();
      
        case 2:
          return get_box_2_stretch();
      
      }
      return 0;
    }

    int8_t get_box_led_dim(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_led_dim();
      
        case 1:
          return get_box_1_led_dim();
      
        case 2:
          return get_box_2_led_dim();
      
      }
      return 0;
    }

    int8_t get_box_enabled(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_enabled();
      
        case 1:
          return get_box_1_enabled();
      
        case 2:
          return get_box_2_enabled();
      
      }
      return 0;
    }

    int8_t get_box_temp(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_temp();
      
        case 1:
          return get_box_1_temp();
      
        case 2:
          return get_box_2_temp();
      
      }
      return 0;
    }

    int8_t get_box_humi(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_humi();
      
        case 1:
          return get_box_1_humi();
      
        case 2:
          return get_box_2_humi();
      
      }
      return 0;
    }

    int8_t get_box_temp_source(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_temp_source();
      
        case 1:
          return get_box_1_temp_source();
      
        case 2:
          return get_box_2_temp_source();
      
      }
      return 0;
    }

    int8_t get_box_humi_source(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_humi_source();
      
        case 1:
          return get_box_1_humi_source();
      
        case 2:
          return get_box_2_humi_source();
      
      }
      return 0;
    }

    int32_t get_box_started_at(int i) {
      switch(i) {
      
        case 0:
          return get_box_0_started_at();
      
        case 1:
          return get_box_1_started_at();
      
        case 2:
          return get_box_2_started_at();
      
      }
      return 0;
    }

    int8_t get_motor_duty(int i) {
      switch(i) {
      
        case 0:
          return get_motor_0_duty();
      
        case 1:
          return get_motor_1_duty();
      
        case 2:
          return get_motor_2_duty();
      
      }
      return 0;
    }

    int8_t get_motor_gpio(int i) {
      switch(i) {
      
        case 0:
          return get_motor_0_gpio();
      
        case 1:
          return get_motor_1_gpio();
      
        case 2:
          return get_motor_2_gpio();
      
      }
      return 0;
    }

    int8_t get_motor_source(int i) {
      switch(i) {
      
        case 0:
          return get_motor_0_source();
      
        case 1:
          return get_motor_1_source();
      
        case 2:
          return get_motor_2_source();
      
      }
      return 0;
    }

    int16_t get_motor_frequency(int i) {
      switch(i) {
      
        case 0:
          return get_motor_0_frequency();
      
        case 1:
          return get_motor_1_frequency();
      
        case 2:
          return get_motor_2_frequency();
      
      }
      return 0;
    }

    int8_t get_sht21_present(int i) {
      switch(i) {
      
        case 0:
          return get_sht21_0_present();
      
        case 1:
          return get_sht21_1_present();
      
        case 2:
          return get_sht21_2_present();
      
      }
      return 0;
    }

    int8_t get_sht21_temp(int i) {
      switch(i) {
      
        case 0:
          return get_sht21_0_temp();
      
        case 1:
          return get_sht21_1_temp();
      
        case 2:
          return get_sht21_2_temp();
      
      }
      return 0;
    }

    int8_t get_sht21_humi(int i) {
      switch(i) {
      
        case 0:
          return get_sht21_0_humi();
      
        case 1:
          return get_sht21_1_humi();
      
        case 2:
          return get_sht21_2_humi();
      
      }
      return 0;
    }



    void set_i2c_sda(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_i2c_0_sda(v);
          break;
      
        case 1:
          set_i2c_1_sda(v);
          break;
      
        case 2:
          set_i2c_2_sda(v);
          break;
      
      }
    }

    void set_i2c_scl(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_i2c_0_scl(v);
          break;
      
        case 1:
          set_i2c_1_scl(v);
          break;
      
        case 2:
          set_i2c_2_scl(v);
          break;
      
      }
    }

    void set_i2c_enabled(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_i2c_0_enabled(v);
          break;
      
        case 1:
          set_i2c_1_enabled(v);
          break;
      
        case 2:
          set_i2c_2_enabled(v);
          break;
      
      }
    }

    void set_i2c_port(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_i2c_0_port(v);
          break;
      
        case 1:
          set_i2c_1_port(v);
          break;
      
        case 2:
          set_i2c_2_port(v);
          break;
      
      }
    }

    void set_led_enabled(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_led_0_enabled(v);
          break;
      
        case 1:
          set_led_1_enabled(v);
          break;
      
        case 2:
          set_led_2_enabled(v);
          break;
      
        case 3:
          set_led_3_enabled(v);
          break;
      
        case 4:
          set_led_4_enabled(v);
          break;
      
        case 5:
          set_led_5_enabled(v);
          break;
      
      }
    }

    void set_led_duty(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_led_0_duty(v);
          break;
      
        case 1:
          set_led_1_duty(v);
          break;
      
        case 2:
          set_led_2_duty(v);
          break;
      
        case 3:
          set_led_3_duty(v);
          break;
      
        case 4:
          set_led_4_duty(v);
          break;
      
        case 5:
          set_led_5_duty(v);
          break;
      
      }
    }

    void set_led_gpio(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_led_0_gpio(v);
          break;
      
        case 1:
          set_led_1_gpio(v);
          break;
      
        case 2:
          set_led_2_gpio(v);
          break;
      
        case 3:
          set_led_3_gpio(v);
          break;
      
        case 4:
          set_led_4_gpio(v);
          break;
      
        case 5:
          set_led_5_gpio(v);
          break;
      
      }
    }

    void set_led_x(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_led_0_x(v);
          break;
      
        case 1:
          set_led_1_x(v);
          break;
      
        case 2:
          set_led_2_x(v);
          break;
      
        case 3:
          set_led_3_x(v);
          break;
      
        case 4:
          set_led_4_x(v);
          break;
      
        case 5:
          set_led_5_x(v);
          break;
      
      }
    }

    void set_led_y(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_led_0_y(v);
          break;
      
        case 1:
          set_led_1_y(v);
          break;
      
        case 2:
          set_led_2_y(v);
          break;
      
        case 3:
          set_led_3_y(v);
          break;
      
        case 4:
          set_led_4_y(v);
          break;
      
        case 5:
          set_led_5_y(v);
          break;
      
      }
    }

    void set_led_z(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_led_0_z(v);
          break;
      
        case 1:
          set_led_1_z(v);
          break;
      
        case 2:
          set_led_2_z(v);
          break;
      
        case 3:
          set_led_3_z(v);
          break;
      
        case 4:
          set_led_4_z(v);
          break;
      
        case 5:
          set_led_5_z(v);
          break;
      
      }
    }

    void set_led_box(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_led_0_box(v);
          break;
      
        case 1:
          set_led_1_box(v);
          break;
      
        case 2:
          set_led_2_box(v);
          break;
      
        case 3:
          set_led_3_box(v);
          break;
      
        case 4:
          set_led_4_box(v);
          break;
      
        case 5:
          set_led_5_box(v);
          break;
      
      }
    }

    void set_led_dim(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_led_0_dim(v);
          break;
      
        case 1:
          set_led_1_dim(v);
          break;
      
        case 2:
          set_led_2_dim(v);
          break;
      
        case 3:
          set_led_3_dim(v);
          break;
      
        case 4:
          set_led_4_dim(v);
          break;
      
        case 5:
          set_led_5_dim(v);
          break;
      
      }
    }

    void set_led_fade(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_led_0_fade(v);
          break;
      
        case 1:
          set_led_1_fade(v);
          break;
      
        case 2:
          set_led_2_fade(v);
          break;
      
        case 3:
          set_led_3_fade(v);
          break;
      
        case 4:
          set_led_4_fade(v);
          break;
      
        case 5:
          set_led_5_fade(v);
          break;
      
      }
    }

    void set_box_on_hour(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_on_hour(v);
          break;
      
        case 1:
          set_box_1_on_hour(v);
          break;
      
        case 2:
          set_box_2_on_hour(v);
          break;
      
      }
    }

    void set_box_on_min(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_on_min(v);
          break;
      
        case 1:
          set_box_1_on_min(v);
          break;
      
        case 2:
          set_box_2_on_min(v);
          break;
      
      }
    }

    void set_box_off_hour(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_off_hour(v);
          break;
      
        case 1:
          set_box_1_off_hour(v);
          break;
      
        case 2:
          set_box_2_off_hour(v);
          break;
      
      }
    }

    void set_box_off_min(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_off_min(v);
          break;
      
        case 1:
          set_box_1_off_min(v);
          break;
      
        case 2:
          set_box_2_off_min(v);
          break;
      
      }
    }

    void set_box_timer_type(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_timer_type(v);
          break;
      
        case 1:
          set_box_1_timer_type(v);
          break;
      
        case 2:
          set_box_2_timer_type(v);
          break;
      
      }
    }

    void set_box_timer_output(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_timer_output(v);
          break;
      
        case 1:
          set_box_1_timer_output(v);
          break;
      
        case 2:
          set_box_2_timer_output(v);
          break;
      
      }
    }

    void set_box_blower_duty(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_blower_duty(v);
          break;
      
        case 1:
          set_box_1_blower_duty(v);
          break;
      
        case 2:
          set_box_2_blower_duty(v);
          break;
      
      }
    }

    void set_box_blower_day(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_blower_day(v);
          break;
      
        case 1:
          set_box_1_blower_day(v);
          break;
      
        case 2:
          set_box_2_blower_day(v);
          break;
      
      }
    }

    void set_box_blower_night(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_blower_night(v);
          break;
      
        case 1:
          set_box_1_blower_night(v);
          break;
      
        case 2:
          set_box_2_blower_night(v);
          break;
      
      }
    }

    void set_box_blower_enabled(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_blower_enabled(v);
          break;
      
        case 1:
          set_box_1_blower_enabled(v);
          break;
      
        case 2:
          set_box_2_blower_enabled(v);
          break;
      
      }
    }

    void set_box_stretch(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_stretch(v);
          break;
      
        case 1:
          set_box_1_stretch(v);
          break;
      
        case 2:
          set_box_2_stretch(v);
          break;
      
      }
    }

    void set_box_led_dim(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_led_dim(v);
          break;
      
        case 1:
          set_box_1_led_dim(v);
          break;
      
        case 2:
          set_box_2_led_dim(v);
          break;
      
      }
    }

    void set_box_enabled(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_enabled(v);
          break;
      
        case 1:
          set_box_1_enabled(v);
          break;
      
        case 2:
          set_box_2_enabled(v);
          break;
      
      }
    }

    void set_box_temp_source(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_temp_source(v);
          break;
      
        case 1:
          set_box_1_temp_source(v);
          break;
      
        case 2:
          set_box_2_temp_source(v);
          break;
      
      }
    }

    void set_box_humi_source(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_box_0_humi_source(v);
          break;
      
        case 1:
          set_box_1_humi_source(v);
          break;
      
        case 2:
          set_box_2_humi_source(v);
          break;
      
      }
    }

    void set_box_started_at(int i, int32_t v) {
      switch(i) {
      
        case 0:
          set_box_0_started_at(v);
          break;
      
        case 1:
          set_box_1_started_at(v);
          break;
      
        case 2:
          set_box_2_started_at(v);
          break;
      
      }
    }

    void set_motor_gpio(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_motor_0_gpio(v);
          break;
      
        case 1:
          set_motor_1_gpio(v);
          break;
      
        case 2:
          set_motor_2_gpio(v);
          break;
      
      }
    }

    void set_motor_source(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_motor_0_source(v);
          break;
      
        case 1:
          set_motor_1_source(v);
          break;
      
        case 2:
          set_motor_2_source(v);
          break;
      
      }
    }

    void set_motor_frequency(int i, int16_t v) {
      switch(i) {
      
        case 0:
          set_motor_0_frequency(v);
          break;
      
        case 1:
          set_motor_1_frequency(v);
          break;
      
        case 2:
          set_motor_2_frequency(v);
          break;
      
      }
    }

    void set_sht21_present(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_sht21_0_present(v);
          break;
      
        case 1:
          set_sht21_1_present(v);
          break;
      
        case 2:
          set_sht21_2_present(v);
          break;
      
      }
    }

    void set_sht21_temp(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_sht21_0_temp(v);
          break;
      
        case 1:
          set_sht21_1_temp(v);
          break;
      
        case 2:
          set_sht21_2_temp(v);
          break;
      
      }
    }

    void set_sht21_humi(int i, int8_t v) {
      switch(i) {
      
        case 0:
          set_sht21_0_humi(v);
          break;
      
        case 1:
          set_sht21_1_humi(v);
          break;
      
        case 2:
          set_sht21_2_humi(v);
          break;
      
      }
    }


