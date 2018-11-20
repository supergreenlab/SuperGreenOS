/*
 * =====================================================================================
 *
 *       Filename:  sht1x_driver.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/18/2018 04:55:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
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
