package config

modules graphs_screen: _MODULE & {
  init_priority: 20
}

modules graphs_screen fields "order": _UINT8 & _NVS & _HTTP_RW & {
  default: 2
  nvs key: "GRSCR_ORDR"
  write_cb: true
}

