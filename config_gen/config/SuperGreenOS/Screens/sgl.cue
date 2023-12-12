package config

modules sgl: _MODULE & {
  init_priority: 40
}

modules sgl fields token: _STRING & _NVS & _HTTP_RW & {
  default: string | *""
  nosend: true
  remote: false
  nvs key: "SGL_TK"
  http read: false
  default: ""
}

modules sgl fields enckey: _STRING & _NVS & _HTTP_RW & {
  default: string | *""
  nosend: true
  remote: false
  nvs key: "SGL_EK"
  http read: false
  default: ""
}
