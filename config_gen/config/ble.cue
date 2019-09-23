package config

modules ble: _CORE_MODULE

modules ble fields enabled: _INT8 & _HTTP_RW & {
  write_cb: true
  default: false
}
