package config

modules mqtt fields scrcallbackinclude: _STRING & {
  default: "../../sgl/sgl.h"
}

modules mqtt fields scrcallback: _STRING & {
  default: "mqtt_message"
}

modules mqtt fields scrtoken: _STRING & _NVS & _HTTP_RW & {
  default: string | *""
  nosend: true
  remote: false
  nvs key: "BRKR_SCR_TK"
  default: ""
  write_cb: true
}

modules mqtt fields screnckey: _STRING & _NVS & _HTTP_RW & {
  default: string | *""
  nosend: true
  remote: false
  nvs key: "BRKR_SCR_EK"
  default: ""
  http read: false
}
