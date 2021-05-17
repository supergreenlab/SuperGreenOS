package config

modules state: _MODULE & {
  init_priority: 100
  required: true
}

modules state fields state: _INT8 & _NVS & _HTTP_RW & {
  name: "state"
  _default_var: "FIRST_RUN"
  write_cb: true
}

modules state fields device_name: _STRING & _NVS & _HTTP_RW & {
  name: "device_name"
  nvs key: "DEV_NAME"
  default: string | *"SuperGreenOS"
}
