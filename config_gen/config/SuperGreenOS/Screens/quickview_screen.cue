package config

modules quickview_screen: _MODULE & {
  init_priority: 30
}

modules quickview_screen fields "order": _UINT8 & _HTTP & {
  default: 0
  write_cb: true
}

