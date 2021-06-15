package config

modules hx711: _I2C_MODULE & {
  init: false
  array_len: len(_i2c_conf)
}

modules hx711 fields "\(k)_present": _INT8 & _HTTP & {
  default: 0
} for k, v in _i2c_conf

modules hx711 fields "\(k)_weight": _INT32 & _HTTP & {
  default: 0
  weight_sensor: 0x1+k
  helper: "HX711 weight on port #\(k+1)"
} for k, v in _i2c_conf

modules hx711 fields "\(k)_weight_calibration": _UINT8 & _NVS & _HTTP_RW & {
  default: 83
  nvs key: "HX_\(k)_W_CAL"
  helper: "HX711 weight divider calibration on port #\(k+1)"
} for k, v in _i2c_conf

modules hx711 fields "\(k)_weight_offset": _INT16 & _NVS & _HTTP_RW & {
  default: 0
  nvs key: "HX_\(k)_W_OFF"
  helper: "HX711 weight weight offset on port #\(k+1)"
} for k, v in _i2c_conf

