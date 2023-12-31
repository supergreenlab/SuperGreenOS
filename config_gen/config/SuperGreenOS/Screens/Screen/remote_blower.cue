package config

modules remote_blower: _REMOTE_MODULE & {
  required: true
  field_prefix: "box"
}

modules remote_blower fields "blower_duty": _INT8 & _HTTP & {
  helper: "Remote blower control"
  default: 0
}
