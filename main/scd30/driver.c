/*
 * Copyright (C) 2021  SuperGreenLab <towelie@supergreenlab.com>
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

#include "driver.h"
#include "../core/i2c/i2c.h"
#include "../core/log/log.h"

// NOTE: this is taken from the arduino sparkfun library that was in cpp with the arduino framework.
// https://github.com/sparkfun/SparkFun_SCD30_Arduino_Library/

bool begin(scd30_handle *s) {
	uint16_t fwVer;
  if (getFirmwareVersion(s, &fwVer) == false) {
    return false;
	}
	ESP_LOGI(SGO_LOG_NOSEND, "@SCD30 firmware version %02x", fwVer);

	if (beginMeasuring(s, 0) == true) {
    if (setMeasurementInterval(s, 2) == false) {
			return false;
		}
    if (setAutoSelfCalibration(s, false) == false) {
			return false;
		}
    return true;
  }

  return false;
}

//Returns the latest available CO2 level
//If the current level has already been reported, trigger a new read
uint16_t getCO2(scd30_handle *s)
{
  if (s->co2HasBeenReported == true) //Trigger a new read
    readMeasurement(s);            //Pull in new co2, humidity, and temp into global vars

  s->co2HasBeenReported = true;

  return (uint16_t)s->co2; //Cut off decimal as co2 is 0 to 10,000
}

//Returns the latest available humidity
//If the current level has already been reported, trigger a new read
float getHumidity(scd30_handle *s)
{
  if (s->humidityHasBeenReported == true) //Trigger a new read
    readMeasurement(s);                 //Pull in new co2, humidity, and temp into global vars

  s->humidityHasBeenReported = true;

  return s->humidity;
}

//Returns the latest available temperature
//If the current level has already been reported, trigger a new read
float getTemperature(scd30_handle *s)
{
  if (s->temperatureHasBeenReported == true) //Trigger a new read
    readMeasurement(s);                    //Pull in new co2, humidity, and temp into global vars

  s->temperatureHasBeenReported = true;

  return s->temperature;
}

//Enables or disables the ASC
bool setAutoSelfCalibration(scd30_handle *s, bool enable)
{
  if (enable)
    return sendCommandArg(s, COMMAND_AUTOMATIC_SELF_CALIBRATION, 1); //Activate continuous ASC
  else
    return sendCommandArg(s, COMMAND_AUTOMATIC_SELF_CALIBRATION, 0); //Deactivate continuous ASC
}

//Set the forced recalibration factor. See 1.3.7.
//The reference CO2 concentration has to be within the range 400 ppm ≤ cref(CO2) ≤ 2000 ppm.
bool setForcedRecalibrationFactor(scd30_handle *s, uint16_t concentration)
{
  if (concentration < 400 || concentration > 2000)
  {
    return false; //Error check.
  }
  return sendCommandArg(s, COMMAND_SET_FORCED_RECALIBRATION_FACTOR, concentration);
}

//Get the temperature offset. See 1.3.8.
float getTemperatureOffset(scd30_handle *s)
{
  uint16_t response = readRegister(s, COMMAND_SET_TEMPERATURE_OFFSET);
  return (((float)response) / 100.0);
}

//Set the temperature offset. See 1.3.8.
bool setTemperatureOffset(scd30_handle *s, float tempOffset)
{
  union
  {
    int16_t signed16;
    uint16_t unsigned16;
  } signedUnsigned; // Avoid any ambiguity casting int16_t to uint16_t
  signedUnsigned.signed16 = tempOffset * 100;
  return sendCommandArg(s, COMMAND_SET_TEMPERATURE_OFFSET, signedUnsigned.unsigned16);
}

//Get the altitude compenstation. See 1.3.9.
uint16_t getAltitudeCompensation(scd30_handle *s)
{
  return readRegister(s, COMMAND_SET_ALTITUDE_COMPENSATION);
}

//Set the altitude compenstation. See 1.3.9.
bool setAltitudeCompensation(scd30_handle *s, uint16_t altitude)
{
  return sendCommandArg(s, COMMAND_SET_ALTITUDE_COMPENSATION, altitude);
}

//Set the pressure compenstation. This is passed during measurement startup.
//mbar can be 700 to 1200
bool setAmbientPressure(scd30_handle *s, uint16_t pressure_mbar)
{
  if (pressure_mbar < 700 || pressure_mbar > 1200)
  {
    return false;
  }
  return sendCommandArg(s, COMMAND_CONTINUOUS_MEASUREMENT, pressure_mbar);
}

// SCD30 soft reset
void reset(scd30_handle *s)
{
	sendCommand(s, COMMAND_RESET);
}

// Get the current ASC setting
bool getAutoSelfCalibration(scd30_handle *s)
{
  uint16_t response = readRegister(s, COMMAND_AUTOMATIC_SELF_CALIBRATION);
  if (response == 1) {
    return true;
  }
  else {
	return false;
  }
}

//Begins continuous measurements
//Continuous measurement status is saved in non-volatile memory. When the sensor
//is powered down while continuous measurement mode is active SCD30 will measure
//continuously after repowering without sending the measurement command.
//Returns true if successful
bool beginMeasuring(scd30_handle *s, uint16_t pressureOffset)
{
  return (sendCommandArg(s, COMMAND_CONTINUOUS_MEASUREMENT, pressureOffset));
}

// Stop continuous measurement
bool StopMeasurement(scd30_handle *s)
{
  return(sendCommand(s, COMMAND_STOP_MEAS));
}

//Sets interval between measurements
//2 seconds to 1800 seconds (30 minutes)
bool setMeasurementInterval(scd30_handle *s, uint16_t interval)
{
  return sendCommandArg(s, COMMAND_SET_MEASUREMENT_INTERVAL, interval);
}

//Returns true when data is available
bool dataAvailable(scd30_handle *s)
{
  uint16_t response = readRegister(s, COMMAND_GET_DATA_READY);

  if (response == 1)
    return (true);
  return (false);
}

//Get 18 bytes from SCD30
//Updates global variables with floats
//Returns true if success
bool readMeasurement(scd30_handle *s)
{
  //Verify we have data from the sensor
  if (dataAvailable(s) == false) {
    return (false);
	}

  ByteToFl tempCO2; tempCO2.value = 0;
  ByteToFl tempHumidity; tempHumidity.value = 0;
  ByteToFl tempTemperature; tempTemperature.value = 0;

	uint8_t outBuff[2] = {COMMAND_READ_MEASUREMENT >> 8, COMMAND_READ_MEASUREMENT & 0xFF};
	i2c_err_t err = i2cWrite(s->port, SCD30_ADDRESS, outBuff, sizeof(outBuff), true, 150);
  if (!(err == I2C_ERROR_CONTINUE || err == I2C_ERROR_OK)) {
		ESP_LOGW(SGO_LOG_NOSEND, "@SCD30 i2cWrite failed %02x", err);
    return (0);
	}

  vTaskDelay(3000 / portTICK_RATE_MS);
	
	uint32_t size;
	uint8_t buff[18];
	i2cRead(s->port, SCD30_ADDRESS, buff, 18, true, 150, &size);
  uint8_t foundCrc;
  bool error = false;
  if (size == 18)
  {
    uint8_t bytesToCrc[2];
    for (uint8_t x = 0; x < 18; x++)
    {
      uint8_t incoming = buff[x];

      switch (x)
      {
      case 0:
      case 1:
      case 3:
      case 4:
        tempCO2.array[x < 3 ? 3-x : 4-x] = incoming;
        bytesToCrc[x % 3] = incoming;
        break;
      case 6:
      case 7:
      case 9:
      case 10:
        tempTemperature.array[x < 9 ? 9-x : 10-x] = incoming;
        bytesToCrc[x % 3] = incoming;
        break;
      case 12:
      case 13:
      case 15:
      case 16:
        tempHumidity.array[x < 15 ? 15-x : 16-x] = incoming;
        bytesToCrc[x % 3] = incoming;
        break;
      default:
        //Validate CRC
        foundCrc = computeCRC8(s, bytesToCrc, 2);
        if (foundCrc != incoming)
        {
					ESP_LOGW(SGO_LOG_NOSEND, "@SCD30 readMeasurement: found CRC in byte %d, expected %02x, got %02x", x, foundCrc, incoming);
          error = true;
        }
        break;
      }
    }
  }
  else
  {	
		ESP_LOGW(SGO_LOG_NOSEND, "@SCD30 readMeasurement: no SCD30 data found from I2C, i2c claims we should receive %d bytes", size);
    return false;
  }

  if (error)
  {
		ESP_LOGW(SGO_LOG_NOSEND, "@SCD30 readMeasurement: encountered error reading SCD30 data.");
    return false;
  }
  //Now copy the uint32s into their associated floats
  s->co2 = tempCO2.value;
  s->temperature = tempTemperature.value;
  s->humidity = tempHumidity.value;

  //Mark our global variables as fresh
  s->co2HasBeenReported = false;
  s->humidityHasBeenReported = false;
  s->temperatureHasBeenReported = false;

  return (true); //Success! New data available in globals.
}

//Gets a setting by reading the appropriate register.
//Returns true if the CRC is valid.
bool getSettingValue(scd30_handle *s, uint16_t registerAddress, uint16_t *val)
{
	uint8_t outBuff[2] = {registerAddress >> 8, registerAddress & 0xFF};
	i2c_err_t err = i2cWrite(s->port, SCD30_ADDRESS, outBuff, sizeof(outBuff), true, 150);
  if (!(err == I2C_ERROR_CONTINUE || err == I2C_ERROR_OK)) {
		ESP_LOGW(SGO_LOG_NOSEND, "@SCD30 i2cWrite failed %02x", err);
    return (0);
	}

  vTaskDelay(3000 / portTICK_RATE_MS);

	uint32_t size;
	uint8_t buff[3];
	err = i2cRead(s->port, SCD30_ADDRESS, buff, sizeof(buff), true, 150, &size);
	if (!(err == I2C_ERROR_CONTINUE || err == I2C_ERROR_OK)) {
		ESP_LOGW(SGO_LOG_NOSEND, "@SCD30 i2cRead failed %02x", err);
    return (0);
	}

  if (size == 3)
  {
    uint8_t data[2];
    data[0] = buff[0];
    data[1] = buff[1];
    uint8_t crc = buff[2];
    *val = (uint16_t)data[0] << 8 | data[1];
    uint8_t expectedCRC = computeCRC8(s, data, 2);
    if (crc == expectedCRC) // Return true if CRC check is OK
      return (true);
		ESP_LOGW(SGO_LOG_NOSEND, "@SCD30 getSettingValue: CRC fail: expected %02x, got %02x", expectedCRC, crc);
  } else {
		ESP_LOGW(SGO_LOG_NOSEND, "@SCD30 i2cRead failed %d", size);
	}
  return (false);
}

//Gets two bytes from SCD30
uint16_t readRegister(scd30_handle *s, uint16_t registerAddress)
{
	uint8_t outBuff[2] = {registerAddress >> 8, registerAddress & 0xFF};
	i2c_err_t err = i2cWrite(s->port, SCD30_ADDRESS, outBuff, sizeof(outBuff), true, 150);
  if (!(err == I2C_ERROR_CONTINUE || err == I2C_ERROR_OK)) {
		ESP_LOGW(SGO_LOG_NOSEND, "@SCD30 i2cWrite in readRegister failed %02x", err);
    return (0);
	}

  vTaskDelay(3000 / portTICK_RATE_MS);

 	uint32_t size;
	uint8_t buff[2];
	err = i2cRead(s->port, SCD30_ADDRESS, buff, 2, true, 150, &size);
  if (size == 2)
  {
    uint8_t msb = buff[0];
    uint8_t lsb = buff[1];
    return ((uint16_t)msb << 8 | lsb);
  }
	ESP_LOGW(SGO_LOG_NOSEND, "@SCD30 i2cRead in readRegister failed %02x", err);
  return (0); //Sensor did not respond
}

//Sends a command along with arguments and CRC
bool sendCommandArg(scd30_handle *s, uint16_t command, uint16_t arguments)
{
  uint8_t data[2];
  data[0] = arguments >> 8;
  data[1] = arguments & 0xFF;
  uint8_t crc = computeCRC8(s, data, 2); //Calc CRC on the arguments only, not the command

	uint8_t outBuff[5] = {command >> 8, command & 0xFF, arguments >> 8, arguments & 0xFF, crc};
	i2c_err_t err = i2cWrite(s->port, SCD30_ADDRESS, outBuff, sizeof(outBuff), true, 150);
  if (!(err == I2C_ERROR_CONTINUE || err == I2C_ERROR_OK)) {
		ESP_LOGW(SGO_LOG_NOSEND, "@SCD30 i2cWrite in sendCommandArg failed %02x", err);
    return false;
	}

  return true;
}

//Sends just a command, no arguments, no CRC
bool sendCommand(scd30_handle *s, uint16_t command)
{
	uint8_t outBuff[2] = {command >> 8, command & 0xFF};
	i2c_err_t err = i2cWrite(s->port, SCD30_ADDRESS, outBuff, sizeof(outBuff), true, 150);
  if (!(err == I2C_ERROR_CONTINUE || err == I2C_ERROR_OK)) {
		ESP_LOGW(SGO_LOG_NOSEND, "@SCD30 i2cWrite in sendCommand failed %02x", err);
    return false;
	}

  return true;
}

//Given an array and a number of bytes, this calculate CRC8 for those bytes
//CRC is only calc'd on the data portion (two bytes) of the four bytes being sent
//From: http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html
//Tested with: http://www.sunshine2k.de/coding/javascript/crc/crc_js.html
//x^8+x^5+x^4+1 = 0x31
uint8_t computeCRC8(scd30_handle *s, uint8_t data[], uint8_t len)
{
  uint8_t crc = 0xFF; //Init with 0xFF

  for (uint8_t x = 0; x < len; x++)
  {
    crc ^= data[x]; // XOR-in the next input byte

    for (uint8_t i = 0; i < 8; i++)
    {
      if ((crc & 0x80) != 0)
        crc = (uint8_t)((crc << 1) ^ 0x31);
      else
        crc <<= 1;
    }
  }

  return crc; //No output reflection
}
