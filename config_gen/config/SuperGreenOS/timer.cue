package config

modules timer: _MODULE & {
  field_prefix: "box"
  array_len: len(_box_conf)
}

modules timer fields "\(k)_timer_type": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_TT"
  nvs manual: true
  _default_var: "TIMER_MANUAL"
} for k, v in _box_conf

modules timer fields "\(k)_timer_output": _INT8 & _NVS & _HTTP & {
  nvs key: "B_\(k)_TO"
  default: 0
} for k, v in _box_conf
