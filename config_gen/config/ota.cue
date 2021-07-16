package config

modules ota: _CORE_MODULE

modules ota fields timestamp: _INT32 & _NVS & _HTTP_RW & {
  remote: false
  nvs key: "OTA_TMSTP"
  _default_var: "OTA_BUILD_TIMESTAMP"
}

modules ota fields server_ip: _STRING & _NVS & _HTTP_RW & {
  remote: false
  nvs key: "OTA_SRV_IP"
  default: "192.168.4.2"
}

modules ota fields server_hostname: _STRING & _NVS & _HTTP_RW & {
  remote: false
  nvs key: "OTA_SRV_HN"
  default: "update2.supergreenlab.com"
}

modules ota fields server_port: _UINT16 & _NVS & _HTTP_RW & {
  remote: false
  nvs key: "OTA_SRV_UPRT"
  default: 80
}

modules ota fields basedir: _STRING & _NVS & _HTTP_RW & {
  remote: false
  default: string | *"/SuperGreenOSBoilerplate"
}

modules ota fields status: _INT8 & _HTTP & {
  _default_var: "OTA_STATUS_IDLE"
}
