package config

_box_conf: [...]

modules box: _MODULE & {
  is_array: true
  array_len: len(_box_conf)
}

modules box fields "\(k)_enabled": _INT8 & _NVS & _HTTP_RW & {
  default: v.enabled
  nvs key: "B_\(k)_E"
  write_cb: false
} for k, v in _box_conf

modules box fields "\(k)_started_at": _INT32 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_ST_AT"
  default: 0
} for k, v in _box_conf
