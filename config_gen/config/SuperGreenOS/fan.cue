package config

modules fan: _MODULE & {
  required: true
  field_prefix: "box"
  array_len: len(_box_conf)
}

modules fan fields "\(k)_fan_duty": _INT8 & _HTTP & {
  motor_input: 0xf + k 
  helper: "Fan control for box#\(k+1)"
  default: 0
  write_cb: true
} for k, v in _box_conf

modules fan fields "\(k)_fan_min": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_FAN_MI"
  default: 8
  write_cb: true
} for k, v in _box_conf

modules fan fields "\(k)_fan_max": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_FAN_MA"
  default: 30
  write_cb: true
} for k, v in _box_conf

modules fan fields "\(k)_fan_ref_min": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_FAN_RMI"
  default: 21
  write_cb: true
} for k, v in _box_conf

modules fan fields "\(k)_fan_ref_max": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_FAN_RMA"
  default: 30
  write_cb: true
} for k, v in _box_conf

modules fan fields "\(k)_fan_ref": _INT8 & _HTTP & _INDIR & {
  indir key: "fan_ref"
  indir source: "\(k)_fan_ref_source"
  default: 0
} for k, v in _box_conf

modules fan fields "\(k)_fan_ref_source": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_FAN_RSRC"
  default: v.fan_ref_source
  write_cb: true
} for k, v in _box_conf
