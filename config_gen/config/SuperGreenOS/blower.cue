package config

modules blower: _MODULE & {
  required: true
  field_prefix: "box"
  array_len: len(_box_conf)
}

modules blower fields "\(k)_blower_duty": _INT8 & _HTTP & {
  motor_input: 0x1 + k 
  helper: "Blower control for box#\(k+1)"
  default: 0
} for k, v in _box_conf

modules blower fields "\(k)_blower_power": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_BLWR_PWR"
  default: 15
} for k, v in _box_conf

modules blower fields "\(k)_blower_vpd_ref": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_BLWR_VPD"
  default: 10
} for k, v in _box_conf

modules blower fields "\(k)_blower_min": _INT8 & _HTTP & {
  func: "blower_min(\(k))"
  dump_with: "\(k)_blower_duty"
} for k, v in _box_conf

modules blower fields "\(k)_blower_max": _INT8 & _HTTP & {
  func: "blower_max(\(k))"
  dump_with: "\(k)_blower_duty"
} for k, v in _box_conf

modules blower fields "\(k)_blower_ref_min": _INT8 & _HTTP & {
  func: "blower_ref_min(\(k))"
  dump_with: "\(k)_blower_duty"
} for k, v in _box_conf

modules blower fields "\(k)_blower_ref_max": _INT8 & _HTTP & {
  func: "blower_ref_max(\(k))"
  dump_with: "\(k)_blower_duty"
} for k, v in _box_conf

modules blower fields "\(k)_blower_ref": _INT8 & _HTTP & {
  func: "blower_ref(\(k))"
  dump_with: "\(k)_blower_duty"
} for k, v in _box_conf

modules blower fields "\(k)_blower_type": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_BLWR_TYP"
  default: 2
  write_cb: true
} for k, v in _box_conf
