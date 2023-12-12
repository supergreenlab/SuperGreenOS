package config

modules checklist_screen: _MODULE & {
  init_priority: 25
}

modules checklist_screen fields "order": _UINT8 & _NVS & _HTTP_RW & {
  default: 1
  nvs key: "CKSCR_ORDR"
  write_cb: true
}

