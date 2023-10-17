#ifndef __WIRE_H__
#define __WIRE_H__

#include <stdio.h>
#include "esp_log.h"
#include "esp_log.h"
#include "driver/i2c.h"

#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1                            /*!< I2C nack value */

typedef struct wire_s{
	uint8_t i2cnum ;
	uint8_t io_scl ;
	uint8_t io_sda ;
	uint32_t i2c_speed ;
}wire_t;

extern wire_t wire0;
extern wire_t wire1;

esp_err_t InitI2CWire( wire_t* wire );
uint8_t I2Creadbyte( wire_t* wire, uint8_t device_addr, uint8_t reg_addr );
uint8_t I2CreadBuff( wire_t* wire, uint8_t device_addr, uint8_t reg_addr, uint8_t* rd_buff, uint8_t length );
uint8_t I2Cwirtebyte( wire_t* wire, uint8_t device_addr, uint8_t reg_addr, uint8_t Data);
uint8_t I2Cwirtebuff( wire_t* wire, uint8_t device_addr, uint8_t reg_addr, uint8_t* wd_buff,uint8_t length);
uint8_t I2CbeginTransmission( wire_t* wire, uint8_t device_addr, uint8_t reg_addr );

#endif