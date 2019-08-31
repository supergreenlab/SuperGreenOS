package config

modules sht21: _I2C_MODULE & {
  init: false
  array_len: len(_i2c_conf)
}

modules sht21 fields "\(k)_present": _INT8 & _HTTP & {
  default: 0
} for k, v in _i2c_conf

modules sht21 fields "\(k)_temp": _INT8 & _HTTP & {
  default: 0
  temp_sensor: 0x1+k
} for k, v in _i2c_conf

modules sht21 fields "\(k)_humi": _INT8 & _HTTP & {
  default: 0
  humi_sensor: 0x1+k
} for k, v in _i2c_conf
