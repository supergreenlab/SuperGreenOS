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

#ifndef _SCD_30_H
#define _SCD_30_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define SCD30_ADDRESS 0x61

#define COMMAND_CONTINUOUS_MEASUREMENT 0x0010
#define COMMAND_SET_MEASUREMENT_INTERVAL 0x4600
#define COMMAND_GET_DATA_READY 0x0202
#define COMMAND_READ_MEASUREMENT 0x0300
#define COMMAND_AUTOMATIC_SELF_CALIBRATION 0x5306
#define COMMAND_SET_FORCED_RECALIBRATION_FACTOR 0x5204
#define COMMAND_SET_TEMPERATURE_OFFSET 0x5403
#define COMMAND_SET_ALTITUDE_COMPENSATION 0x5102
#define COMMAND_RESET 0xD304 // Soft reset
#define COMMAND_STOP_MEAS 0x0104
#define COMMAND_READ_FW_VER 0xD100

typedef union
{
  uint8_t array[4];
  float value;
} ByteToFl;

typedef struct {

  bool co2HasBeenReported;
  bool humidityHasBeenReported;
  bool temperatureHasBeenReported;

  float co2;
  float temperature;
  float humidity;

} scd30_handle;

uint16_t getCO2(scd30_handle *s);
float getHumidity(scd30_handle *s);
float getTemperature(scd30_handle *s);
float getTemperatureOffset(scd30_handle *s);
uint16_t getAltitudeCompensation(scd30_handle *s);

bool getAutoSelfCalibration(scd30_handle *s);
bool getSettingValue(scd30_handle *s, uint16_t registerAddress, uint16_t *val);
inline bool getForcedRecalibration(scd30_handle *s, uint16_t *val) { return (getSettingValue(s, COMMAND_SET_FORCED_RECALIBRATION_FACTOR, val)); }
inline bool getMeasurementInterval(scd30_handle *s, uint16_t *val) { return (getSettingValue(s, COMMAND_SET_MEASUREMENT_INTERVAL, val)); }
inline bool getTemperatureOffset(scd30_handle *s, uint16_t *val) { return (getSettingValue(s, COMMAND_SET_TEMPERATURE_OFFSET, val)); }
inline bool getAltitudeCompensation(scd30_handle *s, uint16_t *val) { return (getSettingValue(s, COMMAND_SET_ALTITUDE_COMPENSATION, val)); }
inline bool getFirmwareVersion(scd30_handle *s, uint16_t *val) { return (getSettingValue(s, COMMAND_READ_FW_VER, val)); }

bool setMeasurementInterval(scd30_handle *s, uint16_t interval);
bool setAmbientPressure(scd30_handle *s, uint16_t pressure_mbar);
bool setAltitudeCompensation(scd30_handle *s, uint16_t altitude);
bool setAutoSelfCalibration(scd30_handle *s, bool enable);
bool setForcedRecalibrationFactor(scd30_handle *s, uint16_t concentration);
bool setTemperatureOffset(scd30_handle *s, float tempOffset);

bool dataAvailable(scd30_handle *s);
bool readMeasurement(scd30_handle *s);

void reset(scd30_handle *s);

bool beginMeasuring(scd30_handle *s, uint16_t pressureOffset);
bool StopMeasurement(scd30_handle *s);

bool sendCommandArg(scd30_handle *s, uint16_t command, uint16_t arguments);
bool sendCommand(scd30_handle *s, uint16_t command);
uint16_t readRegister(scd30_handle *s, uint16_t registerAddress);
uint8_t computeCRC8(scd30_handle *s, uint8_t data[], uint8_t len);

#endif
