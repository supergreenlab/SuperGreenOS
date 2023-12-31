package config

modules remote_fan: _REMOTE_MODULE & {
  field_prefix: "box"
}

modules remote_fan fields "fan_duty": _INT8 & _HTTP & {
  helper: "Remote Fan control"
  default: 0
}
