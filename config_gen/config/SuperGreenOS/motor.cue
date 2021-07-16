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
  required: true
  init_priority: 90
}

modules motor fields "\(k)_duty_testing": _INT8 & _HTTP_RW & {
  default: 0
} for k, v in _motor_conf

modules motor fields "\(k)_duty": _INT8 & _HTTP & _INDIR & {
  indir key: "motor_input"
  indir source: "\(k)_source"
  default: 0
} for k, v in _motor_conf

modules motor fields "\(k)_min": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "M_\(k)_MIN"
  write_cb: true
  default: 8
} for k, v in _motor_conf

modules motor fields "\(k)_max": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "M_\(k)_MAX"
  write_cb: true
  default: 100
} for k, v in _motor_conf

modules motor fields "\(k)_source": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "M_\(k)_D_SRC"
  write_cb: true
  default: v.source
} for k, v in _motor_conf

modules motor fields "\(k)_gpio": _INT8 & {
  default: v.gpio
} for k, v in _motor_conf

modules motor fields "\(k)_frequency": _UINT16 & {
  default: int | *40000
} for k, v in _motor_conf
