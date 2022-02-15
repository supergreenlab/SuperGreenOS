package config

modules fan: _MODULE & {
  required: true
  field_prefix: "box"
  array_len: len(_box_conf)
}

modules fan fields "\(k)_fan_duty": _INT8 & _HTTP & {
  motor_input: 0x1 + k 
  helper: "fan control for box#\(k+1)"
  default: 0
} for k, v in _box_conf

modules fan fields "\(k)_fan_power": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_FAN_PWR"
  default: 15
} for k, v in _box_conf

modules fan fields "\(k)_fan_vpd_ref": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_FAN_VPD"
  default: 10
} for k, v in _box_conf

modules fan fields "\(k)_fan_min": _INT8 & _HTTP & {
  func: "fan_min(\(k))"
  dump_with: "\(k)_fan_duty"
} for k, v in _box_conf

modules fan fields "\(k)_fan_max": _INT8 & _HTTP & {
  func: "fan_max(\(k))"
  dump_with: "\(k)_fan_duty"
} for k, v in _box_conf

modules fan fields "\(k)_fan_ref_min": _INT8 & _HTTP & {
  func: "fan_ref_min(\(k))"
  dump_with: "\(k)_fan_duty"
} for k, v in _box_conf

modules fan fields "\(k)_fan_ref_max": _INT8 & _HTTP & {
  func: "fan_ref_max(\(k))"
  dump_with: "\(k)_fan_duty"
} for k, v in _box_conf

modules fan fields "\(k)_fan_ref": _INT8 & _HTTP & {
  func: "fan_ref(\(k))"
  dump_with: "\(k)_fan_duty"
} for k, v in _box_conf

modules fan fields "\(k)_fan_type": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_FAN_TYP"
  default: 1
  write_cb: true
} for k, v in _box_conf

