package config

modules mqtt fields scrcallbackinclude: _STRING & {
  default: "../../sgl/sgl.h"
}

modules mqtt fields scrcallback: _STRING & {
  default: "mqtt_message"
}
