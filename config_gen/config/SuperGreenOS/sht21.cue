package config

modules sht21: _I2C_MODULE & {
  init: false
  field_prefix: "box"
  array_len: len(_box_conf)
}

modules sht21 fields "\(k)_sht21_temp_c": _INT8 & _HTTP & {
  nvs key: "B_\(k)_SHT21_C"
  default: 0
} for k, v in _box_conf

modules sht21 fields "\(k)_sht21_temp_f": _INT8 & _HTTP & {
  nvs key: "B_\(k)_SHT21_F"
  default: 0
} for k, v in _box_conf

modules sht21 fields "\(k)_sht21_humi": _INT8 & _HTTP & {
  nvs key: "B_\(k)_HUMI"
  default: 0
} for k, v in _box_conf
