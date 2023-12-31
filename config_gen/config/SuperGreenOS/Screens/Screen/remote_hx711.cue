package config

modules remote_hx711: _MODULE

modules remote_hx711 fields "present": _INT8 & _HTTP & {
  default: 0
}

modules remote_hx711 fields "weight": _INT32 & _HTTP & {
  default: 0
  weight_sensor: 0x1+k
  helper: "Remote HX711 weight"
}
