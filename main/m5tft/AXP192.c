#include "AXP192.h"

int8_t AxpInitFromList(wire_t *wire, uint8_t *Buff)
{
    uint16_t offset = 0;
    uint16_t size = 0;

    if ((Buff[0] != 'A') || (Buff[1] != 'X') || (Buff[2] != 'P'))
    {
        return -1;
    }
    else
    {
        offset = Buff[3];
        size = (Buff[4] << 8) + Buff[5];
    }

    for (int i = 0; i < size; i++)
    {
        AxpWriteByte(wire, Buff[offset + i * 2], Buff[offset + i * 2 + 1]);
    }
    return 0;
}

void AxpWriteByte(wire_t *wire, uint8_t Addr, uint8_t Data)
{
    I2Cwirtebyte(wire, 0x34, Addr, Data);
}

uint8_t AxpRead8bit(wire_t *wire, uint8_t Addr)
{
    uint8_t redata = I2Creadbyte(wire, 0x34, Addr);
    return redata;
}

uint16_t AxpRead12Bit(wire_t *wire, uint8_t Addr)
{
    uint16_t Data = 0;
    uint8_t rd_buff[2];
    I2CreadBuff(wire, 0x34, Addr, rd_buff, 2);
    Data = ((rd_buff[0] << 4) + rd_buff[1]); //
    return Data;
}

uint16_t AxpRead13Bit(wire_t *wire, uint8_t Addr)
{
    uint16_t Data = 0;
    uint8_t rd_buff[2];
    I2CreadBuff(wire, 0x34, Addr, rd_buff, 2);
    Data = ((rd_buff[0] << 5) + rd_buff[1]); //
    return Data;
}

uint16_t AxpRead16bit(wire_t *wire, uint8_t Addr)
{
    uint16_t Data = 0;
    uint8_t rd_buff[2];
    I2CreadBuff(wire, 0x34, Addr, rd_buff, 2);
    Data = ((rd_buff[0] << 8) + rd_buff[1]); //
    return Data;
}

uint32_t AxpRead24bit(wire_t *wire, uint8_t Addr)
{
    uint32_t ReData = 0;
    for (int i = 0; i < 3; i++)
    {
        ReData <<= 8;
        ReData |= I2Creadbyte(wire, 0x34, Addr + i);
    }
    return ReData;
}

uint32_t AxpRead32bit(wire_t *wire, uint8_t Addr)
{
    uint32_t ReData = 0;
    for (int i = 0; i < 4; i++)
    {
        ReData <<= 8;
        ReData |= I2Creadbyte(wire, 0x34, Addr + i);
    }
    return ReData;
}

void AxpReadBuff(wire_t *wire, uint8_t Addr, uint8_t Size, uint8_t *Buff)
{
    I2CreadBuff(wire, 0x34, Addr, Buff, Size);
}

float AXP192GetBatVoltage(wire_t *wire)
{
    float ADCLSB = 1.1 / 1000.0;
    uint16_t ReData = AxpRead12Bit(wire, 0x78);
    return ReData * ADCLSB;
}

float AXP192GetBatCurrent(wire_t *wire)
{
    float ADCLSB = 0.5;
    uint16_t CurrentIn = AxpRead13Bit(wire, 0x7A);
    uint16_t CurrentOut = AxpRead13Bit(wire, 0x7C);
    return (CurrentOut - CurrentIn) * ADCLSB;
}

float AXP192GetVinVoltage(wire_t *wire)
{
    float ADCLSB = 1.7/1000;
    uint16_t ReData = AxpRead12Bit(wire, 0x56);
    return ReData * ADCLSB;
}

float AXP192GetVinCurrent(wire_t *wire)
{
    float ADCLSB = 0.625;
    uint16_t ReData = AxpRead12Bit(wire, 0x58);
    return ReData * ADCLSB;
}

float AXP192GetVBusVoltage(wire_t *wire)
{
    float ADCLSB = 1.7;
    uint16_t ReData = AxpRead12Bit(wire, 0x5A);
    return ReData * ADCLSB;
}

float AXP192GetVBusCurrent(wire_t *wire)
{
    float ADCLSB = 0.375;
    uint16_t ReData = AxpRead12Bit(wire, 0x5C);
    return ReData * ADCLSB;
}

float AXP192GetTempInAXP192(wire_t *wire)
{
    float ADCLSB = 0.1;
    const float OFFSET_DEG_C = -144.7;
    uint16_t ReData = AxpRead12Bit(wire, 0x5E);
    return OFFSET_DEG_C + ReData * ADCLSB;
}

float AXP192GetBatPower(wire_t *wire)
{
    float VoltageLSB = 1.1;
    float CurrentLCS = 0.5;
    uint32_t ReData = AxpRead24bit(wire, 0x70);
    return ReData * VoltageLSB * CurrentLCS / 1000.0;
}

float AXP192GetBatChargeCurrent(wire_t *wire)
{
    float ADCLSB = 0.5;
    uint16_t ReData = AxpRead12Bit(wire, 0x7A);
    return ReData * ADCLSB;
}

float AXP192GetAPSVoltage(wire_t *wire)
{
    float ADCLSB = 1.4;
    uint16_t ReData = AxpRead12Bit(wire, 0x7E);
    return ReData * ADCLSB;
}

float AXP192GetBatCoulomInput(wire_t *wire)
{
    uint32_t ReData = AxpRead32bit(wire, 0xB0);
    return ReData * 65536 * 0.5 / 3600 / 25.0;
}

float AXP192GetBatCoulomOut(wire_t *wire)
{
    uint32_t ReData = AxpRead32bit(wire, 0xB4);
    return ReData * 65536 * 0.5 / 3600 / 25.0;
}

void AXP192SetCouloClear(wire_t *wire)
{
    AxpWriteByte(wire, 0xB8, 0x20);
}

void AXP192SetLDO2(wire_t *wire, bool State)
{
    uint8_t buf = AxpRead8bit(wire, 0x12);
    if (State == true)
    {
        buf = (1 << 2) | buf;
    }
    else
    {
        buf = ~(1 << 2) & buf;
    }
    AxpWriteByte(wire, 0x12, buf);
}