package config

modules broker: _CORE_MODULE

modules broker fields url: _STRING & _NVS & _HTTP_RW & {
  nvs key: "BRKR_URL"
  default: "mqtt://sink.supergreenlab.com:1883"
}

modules broker fields channel: _STRING & _NVS & _HTTP_RW & {
  nvs key: "BRKR_CHN"
  default: ""
}

modules broker fields clientid: _STRING & _NVS & _HTTP_RW & {
  nvs key: "BRKR_CLID"
  default: ""
}
