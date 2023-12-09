package config

modules mqtt fields cmdcallbackinclude: _STRING & {
  default: "../cmd/cmd.h"
}

modules mqtt fields cmdcallback: _STRING & {
  default: "execute_cmd"
}

modules mqtt fields scrcallbackinclude: _STRING & {
  default: "../../sgl/sgl.h"
}

modules mqtt fields scrcallback: _STRING & {
  default: "mqtt_message"
}
