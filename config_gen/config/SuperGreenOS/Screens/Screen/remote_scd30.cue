package config

modules remote_scd30: _MODULE

modules remote_scd30 fields "present": _INT8 & _HTTP & {
  default: 0
}

modules remote_scd30 fields "co2": _UINT16 & _HTTP & {
  default: 0
  co2_sensor: 0x1+k
  helper: "Remote SCD30 co2"
}

modules remote_scd30 fields "temp": _INT8 & _HTTP & {
  default: 0
  temp_sensor: 0x10+k
  helper: "Remote SCD30 temperature"
}

modules remote_scd30 fields "humi": _INT8 & _HTTP & {
  default: 0
  humi_sensor: 0x10+k
  helper: "Remote SCD30 humidity"
}

modules remote_scd30 fields "vpd": _UINT8 & _HTTP & {
  default: 0
  vpd_sensor: 0x10+k
  helper: "Remote SCD30 vpd"
}
