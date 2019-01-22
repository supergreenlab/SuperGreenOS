/*
 * =====================================================================================
 *
 *       Filename:  arduino_co2.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/29/2018 06:40:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef ARDUINO_CO2_H_
#define ARDUINO_CO2_H_

void init_arduino_co2(int portId, int sca, int sdk);
void loop_arduino_co2(int portId, int sda, int sck);

#endif
