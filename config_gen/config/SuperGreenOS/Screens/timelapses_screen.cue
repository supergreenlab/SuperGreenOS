package config

modules timelapses_screen: _MODULE & {
  init_priority: 15
}

modules timelapses_screen fields "order": _UINT8 & _NVS & _HTTP_RW & {
  default: 3
  nvs key: "TLSCR_ORDR"
  write_cb: true
}

