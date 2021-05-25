package config

modules tester: _CORE_MODULE & {
  init: false
}

modules tester fields enabled: _INT8 & _NVS & _HTTP_RW & {
  nvs key: "TEST_E"
  write_cb: true
  default: int | *0
}
