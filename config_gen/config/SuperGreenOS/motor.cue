package config

_motor_conf: [...]

modules motors: _MODULE & {
  init: false
  code: false
}

modules motors fields "curve": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "M_C"
  default: int | *1
}

modules motor: _MODULE & {
  array_len: len(_motor_conf)
}

modules motor fields "\(k)_duty": _INT8 & _HTTP & _INDIR & {
  indir key: "motor_input"
  indir source: "\(k)_source"
  default: 0
} for k, v in _motor_conf

modules motor fields "\(k)_source": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "M_\(k)_D_SRC"
  default: v.source
} for k, v in _motor_conf

modules motor fields "\(k)_gpio": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "M_\(k)_IO"
  default: v.gpio
} for k, v in _motor_conf

modules motor fields "\(k)_frequency": _UINT16 & _NVS & _HTTP_RW & {
  nvs key: "M_\(k)_HZ"
  default: 40000
  write_cb: true
} for k, v in _motor_conf
