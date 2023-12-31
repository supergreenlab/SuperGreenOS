package config

modules remote_sht21: _MODULE

modules remote_sht21 fields "present": _INT8 & _HTTP & {
  default: 0
}

modules remote_sht21 fields "temp": _INT8 & _HTTP & {
  default: 0
  temp_sensor: 0x1+k
  helper: "Remote SHT21 temperature"
}

modules remote_sht21 fields "humi": _INT8 & _HTTP & {
  default: 0
  humi_sensor: 0x1+k
  helper: "Remote SHT21 humidity"
}

modules remote_sht21 fields "vpd": _UINT8 & _HTTP & {
  default: 0
  vpd_sensor: 0x1+k
  helper: "Remote SHT21 vpd"
}
