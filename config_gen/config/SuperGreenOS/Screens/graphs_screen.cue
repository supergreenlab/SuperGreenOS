package config

modules graphs_screen: _MODULE & {
  init_priority: 20
}

modules graphs_screen fields "order": _UINT8 & _HTTP & {
  default: 2
  write_cb: true
}

