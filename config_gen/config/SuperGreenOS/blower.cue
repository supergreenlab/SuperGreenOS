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

modules blower fields "\(k)_blower_day": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_BLWR_D"
  default: 20
  write_cb: true
} for k, v in _box_conf

modules blower fields "\(k)_blower_night": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_BLWR_N"
  default: 10
  write_cb: true
} for k, v in _box_conf
