package config

modules onoff: _MODULE & {
  init: false
  field_prefix: "box"
  array_len: len(_box_conf)
}

modules onoff fields "\(k)_on_hour": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_ON_H"
  default: 3
} for k, v in _box_conf

modules onoff fields "\(k)_on_min": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_ON_M"
  default: 0
} for k, v in _box_conf

modules onoff fields "\(k)_off_hour": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_OFF_H"
  default: 21
} for k, v in _box_conf

modules onoff fields "\(k)_off_min": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_OFF_M"
  default: 0
} for k, v in _box_conf

modules timer fields "\(k)_emerson_ratio": _INT8 & _HTTP & {
  helper: "Box #\(k+1) emerson effect dr/fr ratio"
  default: 0
} for k, v in _box_conf
