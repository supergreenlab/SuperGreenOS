package config

_led_conf: [...]

modules led: _MODULE & {
  array_len: len(_led_conf)
}

modules led fields "\(k)_duty": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "L_\(k)_D"
  default: 0
  write_cb: true
} for k, v in _led_conf

modules led fields "\(k)_gpio": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "L_\(k)_IO"
  default: v.gpio
} for k, v in _led_conf

modules led fields "\(k)_x": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "L_\(k)_X"
  default: 0
} for k, v in _led_conf

modules led fields "\(k)_y": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "L_\(k)_Y"
  default: 0
} for k, v in _led_conf

modules led fields "\(k)_z": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "L_\(k)_Z"
  default: 0
} for k, v in _led_conf

modules led fields "\(k)_box": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "L_\(k)_BOX"
  default: 0
} for k, v in _led_conf

modules led fields "\(k)_dim": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "L_\(k)_DI"
  default: 100
  write_cb: true
} for k, v in _led_conf

modules led fields "\(k)_fade": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "L_\(k)_FADE"
  default: 1
} for k, v in _led_conf
