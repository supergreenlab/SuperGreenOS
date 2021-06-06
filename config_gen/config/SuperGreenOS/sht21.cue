package config

modules sht21: _I2C_MODULE & {
  array_len: len(_i2c_conf)
}

modules sht21 fields "\(k)_present": _INT8 & _HTTP & {
  default: 0
} for k, v in _i2c_conf

modules sht21 fields "\(k)_temp": _INT8 & _HTTP & {
  default: 0
  temp_sensor: 0x1+k
  blower_ref: 0x1+k
  helper: "SHT21 temperature on port #\(k+1)"
} for k, v in _i2c_conf

modules sht21 fields "\(k)_humi": _INT8 & _HTTP & {
  default: 0
  humi_sensor: 0x4+k
  blower_ref: 0xf+k
  helper: "SHT21 humidity on port #\(k+1)"
} for k, v in _i2c_conf

modules sht21 fields "\(k)_vpd": _UINT8 & _HTTP & {
  default: 0
  vpd_sensor: 0x1+k
  helper: "SHT21 humidity on port #\(k+1)"
} for k, v in _i2c_conf

modules sht21 fields "\(k)_vpd_leaf_offset": _INT8 & _NVS & _HTTP_RW & {
  default: -20
  nvs key: "B_\(k)_VPD_LO"
} for k, v in _i2c_conf
