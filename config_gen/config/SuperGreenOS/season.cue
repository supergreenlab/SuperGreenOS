package config

modules season: _MODULE & {
  init: false
  field_prefix: "box"
  array_len: len(_box_conf)
}

modules season fields "\(k)_start_month": _UINT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_ST_M"
  default: 4
} for k, v in _box_conf

modules season fields "\(k)_start_day": _UINT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_ST_D"
  default: 1
} for k, v in _box_conf

modules season fields "\(k)_duration_days": _UINT16 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_D_D"
  default: 215
} for k, v in _box_conf

modules season fields "\(k)_sim_duration_days": _UINT16 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_S_D_D"
  default: 75
} for k, v in _box_conf

modules season fields "\(k)_simulated_time": _UINT32 & _HTTP & {
  default: 0
} for k, v in _box_conf
