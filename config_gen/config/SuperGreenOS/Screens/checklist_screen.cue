package config

modules checklist_screen: _MODULE & {
  init_priority: 25
}

modules checklist_screen fields "order": _UINT8 & _HTTP & {
  default: 1
  write_cb: true
}

