package config

modules timelapses_screen: _MODULE & {
  init_priority: 15
}

modules timelapses_screen fields "order": _UINT8 & _HTTP & {
  default: 3
  write_cb: true
}

