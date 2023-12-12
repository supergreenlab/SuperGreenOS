package config

modules mqtt fields cmdcallbackinclude: _STRING & {
  default: "../cmd/cmd.h"
}

modules mqtt fields cmdcallback: _STRING & {
  default: "execute_cmd"
}
