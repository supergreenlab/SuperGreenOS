/*
 * =====================================================================================
 *
 *       Filename:  sht1x.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/17/2018 05:46:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef SHT1X_H_
#define SHT1X_H_

void init_sht1x(int portId, int sda, int sdk);
void loop_sht1x(int portId, int sda, int sdk);

#endif
