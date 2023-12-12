package config

modules motor fields "\(k)_frequency": _UINT16 & _NVS & _HTTP_RW & {
  nvs key: "M_\(k)_HZ"
  default: 40000
  write_cb: true
} for k, v in _motor_conf
