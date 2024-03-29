package config

_i2c_conf: [...]

modules i2c: _CORE_MODULE & {
  array_len: len(_i2c_conf)
}

modules i2c fields "\(k)_sda": _INT8 & {
  default: v.sda
} for k, v in _i2c_conf

modules i2c fields "\(k)_scl": _INT8 &  {
  default: v.scl
} for k, v in _i2c_conf

modules i2c fields "\(k)_enabled": _INT8 & {
  default: v.enabled
} for k, v in _i2c_conf

modules i2c fields "\(k)_port": _INT8 & {
  default: v.port
} for k, v in _i2c_conf
