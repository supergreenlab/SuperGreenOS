#ifndef __AXP192_H__
#define __AXP192_H__

#include <stdio.h>
#include "esp_log.h"
#include "wire.h" 

int8_t AxpInitFromList( wire_t* wire, uint8_t* Buff );
void AxpWriteByte( wire_t* wire, uint8_t Addr ,  uint8_t Data );
uint8_t  AxpRead8bit( wire_t* wire, uint8_t Addr );
uint16_t AxpRead12Bit( wire_t* wire, uint8_t Addr);
uint16_t AxpRead13Bit( wire_t* wire, uint8_t Addr);
uint16_t AxpRead16bit( wire_t* wire, uint8_t Addr );
uint32_t AxpRead24bit( wire_t* wire, uint8_t Addr );
uint32_t AxpRead32bit( wire_t* wire, uint8_t Addr );
void AxpReadBuff( wire_t* wire, uint8_t Addr , uint8_t Size , uint8_t *Buff );

float AXP192GetBatVoltage( wire_t* wire );
float AXP192GetBatCurrent( wire_t* wire );
float AXP192GetVinVoltage( wire_t* wire );
float AXP192GetVinCurrent( wire_t* wire );
float AXP192GetVBusVoltage( wire_t* wire );
float AXP192GetVBusCurrent( wire_t* wire );
float AXP192GetTempInAXP192( wire_t* wire );
float AXP192GetBatPower( wire_t* wire );
float AXP192GetBatChargeCurrent( wire_t* wire );
float AXP192GetAPSVoltage( wire_t* wire );
float AXP192GetBatCoulomInput( wire_t* wire );
float AXP192GetBatCoulomOut( wire_t* wire );
void AXP192SetCouloClear( wire_t* wire );
void AXP192SetLDO2( wire_t* wire, bool State );

#endif
