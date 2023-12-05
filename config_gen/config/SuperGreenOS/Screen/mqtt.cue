package config

modules mqtt fields fallback: _STRING & {
  default: "mqtt_message"
}

modules mqtt fields fallbackinclude: _STRING & {
  default: "../../sgl/sgl.h"
}
