package config

modules httpd: _CORE_MODULE

modules httpd fields auth: _STRING & _NVS & _HTTP_RW & {
  nosend: true
  remote: false
  nvs key: "AUTH_HDR"
  http read: false
  default: ""
}
