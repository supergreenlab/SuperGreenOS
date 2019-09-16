package config

import (
  "strings"
)

modules wifi fields mdns_domain default: strings.ToLower(modules.state.fields.device_name.default)
