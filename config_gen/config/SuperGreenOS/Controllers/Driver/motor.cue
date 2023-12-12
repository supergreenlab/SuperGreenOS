package config

modules motors fields "curve" default: 0

_motor_conf: [
  {
    gpio: 22
    source: 1
  },
  {
    gpio: 21
    source: 2
  },
]

modules motor fields "\(k)_frequency": _UINT16 & _NVS & _HTTP_RW & {
  nvs key: "M_\(k)_HZ"
  default: 40000
  write_cb: true
} for k, v in _motor_conf
