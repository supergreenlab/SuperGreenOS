package config

modules mixer: _MODULE & {
  field_prefix: "box"
  array_len: len(_box_conf)
}

modules mixer fields "\(k)_stretch": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_STRETCH"
  default: 0
  write_cb: true
} for k, v in _box_conf

modules mixer fields "\(k)_led_dim": _INT32 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_L_DIM"
  default: 0
  write_cb: true
} for k, v in _box_conf
