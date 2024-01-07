package config

modules remote_sensors: _MODULE

modules remote_sensors fields "weight": _INT32 & _HTTP & {
  default: 0
  weight_sensor: 0x1+k
  helper: "Remote HX711 weight"
}

modules remote_sensors fields "co2": _UINT16 & _HTTP & {
  default: 0
  co2_sensor: 0x1+k
  helper: "Remote SCD30 co2"
}

modules remote_sensors fields "temp": _INT8 & _HTTP & {
  default: 0
  temp_sensor: 0x10+k
  helper: "Remote SCD30 temperature"
}

modules remote_sensors fields "humi": _INT8 & _HTTP & {
  default: 0
  humi_sensor: 0x10+k
  helper: "Remote SCD30 humidity"
}

modules remote_sensors fields "vpd": _UINT8 & _HTTP & {
  default: 0
  vpd_sensor: 0x10+k
  helper: "Remote SCD30 vpd"
}
