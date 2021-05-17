package config

modules time: _CORE_MODULE

modules time fields time: _INT32 & _NVS & _HTTP_RW & {
  name: "time"
  nvs key: "TIME"
  default: 0
  write_cb: true
}
