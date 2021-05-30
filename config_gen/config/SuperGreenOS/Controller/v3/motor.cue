package config

modules motors fields curve default: 0

modules motor fields "\(k)_frequency": _UINT16 & {
  default: 40000
} for k, v in _motor_conf
