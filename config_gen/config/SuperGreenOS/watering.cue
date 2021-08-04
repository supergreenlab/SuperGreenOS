package config

modules watering: _MODULE & {
  field_prefix: "box"
  array_len: len(_box_conf)
}

modules watering fields "\(k)_watering_left": _INT8 & _NVS & _HTTP & _HTTP_RW & {
  nvs key: "B_\(k)_WAT_LE"
  default: -1
} for k, v in _box_conf

modules watering fields "\(k)_watering_duty": _INT8 & _HTTP & {
  motor_input: 0x8 + k 
  helper: "Watering control for box#\(k+1)"
  default: 0
} for k, v in _box_conf

modules watering fields "\(k)_watering_period": _UINT16 & _NVS & _HTTP & _HTTP_RW & {
  nvs key: "B_\(k)_WAT_P"
  default: 2880
  write_cb: true
} for k, v in _box_conf

modules watering fields "\(k)_watering_duration": _UINT16 & _NVS & _HTTP & _HTTP_RW & {
  nvs key: "B_\(k)_WAT_D"
  default: 600
  write_cb: true
} for k, v in _box_conf

modules watering fields "\(k)_watering_last": _INT32 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_WAT_L"
  default: 0
  write_cb: true
} for k, v in _box_conf

modules watering fields "\(k)_watering_power": _INT8 & _NVS & _HTTP & _HTTP_RW & {
  nvs key: "B_\(k)_WAT_PWR"
  default: 20
  write_cb: true
} for k, v in _box_conf
