package config

modules scd30: _I2C_MODULE & {
  init: false
  array_len: len(_i2c_conf)
}

modules scd30 fields "\(k)_present": _INT8 & _HTTP & {
  default: 0
} for k, v in _i2c_conf

