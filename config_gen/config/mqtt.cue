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

modules mqtt fields cmdcallbackinclude: _STRING & {
  default: string | *""
  nosend: true
}

modules mqtt fields cmdcallback: _STRING & {
  default: string | *""
  nosend: true
}

modules mqtt fields scrcallbackinclude: _STRING & {
  default: string | *""
  nosend: true
}

modules mqtt fields scrcallback: _STRING & {
  default: string | *""
  nosend: true
}
