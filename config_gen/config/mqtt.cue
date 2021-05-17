package config

modules mqtt: _CORE_MODULE & {
  field_prefix: "broker"
}

modules mqtt fields url: _STRING & _NVS & _HTTP_RW & {
  nvs key: "BRKR_URL"
  default: "mqtt://sink2.supergreenlab.com:1883"
}

modules mqtt fields channel: _STRING & _NVS & _HTTP_RW & {
  nvs key: "BRKR_CHN"
  default: ""
}

modules mqtt fields clientid: _STRING & _NVS & _HTTP_RW & {
  nvs key: "BRKR_CLID"
  default: ""
}
