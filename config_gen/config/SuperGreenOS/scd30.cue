package config

modules scd30: _I2C_MODULE & {
  init: false
  array_len: len(_i2c_conf)
}

modules scd30 fields "\(k)_present": _INT8 & _HTTP & {
  default: 0
} for k, v in _i2c_conf

modules scd30 fields "\(k)_co2": _UINT16 & _HTTP & {
  default: 0
  co2_sensor: 0x10+k
  blower_ref: 0x1e+k
  fan_ref: 0x1e+k
  helper: "SCD30 temperature on port #\(k+1)"
} for k, v in _i2c_conf

modules scd30 fields "\(k)_temp": _INT8 & _HTTP & {
  default: 0
  temp_sensor: 0x10+k
  blower_ref: 0x25+k
  fan_ref: 0x25+k
  helper: "SCD30 temperature on port #\(k+1)"
} for k, v in _i2c_conf

modules scd30 fields "\(k)_humi": _INT8 & _HTTP & {
  default: 0
  humi_sensor: 0x10+k
  blower_ref: 0x2c+k
  fan_ref: 0x2c+k
  helper: "SCD30 humidity on port #\(k+1)"
} for k, v in _i2c_conf

modules scd30 fields "\(k)_vpd": _UINT8 & _HTTP & {
  default: 0
  vpd_sensor: 0x10+k
  helper: "SCD30 vpd on port #\(k+1)"
} for k, v in _i2c_conf

modules scd30 fields "\(k)_vpd_leaf_offset": _INT8 & _NVS & _HTTP_RW & {
  default: -20
  nvs key: "S_\(k)_VPD_LO"
} for k, v in _i2c_conf
