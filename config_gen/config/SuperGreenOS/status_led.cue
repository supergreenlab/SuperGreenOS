package config

modules status_led: _MODULE & {
  init_priority: 80
}

modules status_led fields red_gpio: _INT8 & _NVS & _HTTP_RW & {
  nvs key: "SL_R_IO"
}

modules status_led fields green_gpio: _INT8 & _NVS & _HTTP_RW & {
  nvs key: "SL_G_IO"
}

modules status_led fields dim: _INT8 & _NVS & _HTTP_RW & {
  nvs key: "SL_R_D"
  default: 10
}
