package config

modules sht21: _MODULE & {
  field_prefix: "box"
  is_array: true
  array_len: len(_box_conf)
}

modules sht21 fields "\(k)_sht21_temp_c": _INT8 & _HTTP & {
  nvs key: "B_\(k)_SHT21_C"
  default: -255
} for k, v in _box_conf

modules sht21 fields "\(k)_sht21_temp_f": _INT8 & _HTTP & {
  nvs key: "B_\(k)_SHT21_F"
  default: -255
} for k, v in _box_conf

modules sht21 fields "\(k)_sht21_humi": _INT8 & _HTTP & {
  nvs key: "B_\(k)_HUMI"
  default: -255
} for k, v in _box_conf
