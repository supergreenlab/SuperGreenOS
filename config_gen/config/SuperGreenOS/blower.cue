package config

modules blower: _MODULE & {
  field_prefix: "box"
  array_len: len(_box_conf)
}

modules blower fields "\(k)_blower_duty": _INT8 & _NVS & _HTTP & _HTTP_RW & {
  nvs key: "B_\(k)_BLWR_DD"
  motor_input: 0x1 + k 
  indir_help: "Blower control for box#\(k)"
  default: 0
  write_cb: true
} for k, v in _box_conf

modules blower fields "\(k)_blower_min": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_BLWR_MI"
  default: 5
  write_cb: true
} for k, v in _box_conf

modules blower fields "\(k)_blower_max": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_BLWR_MA"
  default: 60
  write_cb: true
} for k, v in _box_conf

modules blower fields "\(k)_blower_ref_min": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_BLWR_RMI"
  default: 21
  write_cb: true
} for k, v in _box_conf

modules blower fields "\(k)_blower_ref_max": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_BLWR_RMA"
  default: 30
  write_cb: true
} for k, v in _box_conf

modules blower fields "\(k)_blower_ref": _INT8 & _HTTP & _INDIR & {
  indir key: "blower_ref"
  indir source: "\(k)_blower_ref_source"
  default: 0
} for k, v in _box_conf

modules blower fields "\(k)_blower_ref_source": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_BLWR_RSRC"
  default: v.blower_ref_source
} for k, v in _box_conf
