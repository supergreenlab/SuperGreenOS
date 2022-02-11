package config

modules timer: _MODULE & {
  field_prefix: "box"
  array_len: len(_box_conf)
}

modules timer fields "\(k)_timer_type": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_TT"
  nvs manual: true
  _default_var: "TIMER_MANUAL"
  write_cb: true
} for k, v in _box_conf

modules timer fields "\(k)_timer_output": _INT8 & _HTTP & {
  blower_ref: 0xf+k
  fan_ref: 0xf+k
  valve_ref_on: 0x2e+k
  valve_ref: 0x2e+k
  helper: "Box #\(k+1) timer output"
  default: 0
} for k, v in _box_conf

modules timer fields "\(k)_uva_timer_output": _INT8 & _HTTP & {
  helper: "Box #\(k+1) UVa timer output"
  default: 0
} for k, v in _box_conf

modules timer fields "\(k)_db_timer_output": _INT8 & _HTTP & {
  helper: "Box #\(k+1) deep blue timer output"
  default: 0
} for k, v in _box_conf

modules timer fields "\(k)_dr_timer_output": _INT8 & _HTTP & {
  helper: "Box #\(k+1) deep red timer output"
  default: 0
} for k, v in _box_conf

modules timer fields "\(k)_fr_timer_output": _INT8 & _HTTP & {
  helper: "Box #\(k+1) far red timer output"
  default: 0
} for k, v in _box_conf

modules timer fields "\(k)_timer_emerson_ratio": _INT16 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_OO_EM_R"
  default: 130
} for k, v in _box_conf

modules timer fields "\(k)_timer_emerson_power": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_OO_EM_P"
  default: 0
} for k, v in _box_conf
