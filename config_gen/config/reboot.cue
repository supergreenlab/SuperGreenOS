package config

modules reboot: _CORE_MODULE

modules reboot fields n_restarts: _INT8 & _HTTP & _NVS & {
  name: "n_restarts"
  nvs key: "N_RESTARTS"
  default: 0
}

modules reboot fields reboot: _INT8 & _HTTP_RW & {
  name: "reboot"
  write_cb: true
  default: 0
}
