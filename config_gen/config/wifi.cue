package config

modules wifi: _CORE_MODULE

modules wifi fields status: _INT8 & _HTTP & {
  _default_var: "DISCONNECTED"
}

modules wifi fields ssid: _STRING & _NVS & _HTTP_RW & {
  remote: false
  nosend: true
  nvs key: "WSSID"
  write_cb: true
}

modules wifi fields password: _STRING & _NVS & _HTTP_RW & {
  remote: false
  nosend: true
  nvs key: "WPASS"
  write_cb: true
}

modules wifi fields ap_ssid: _STRING & _NVS & _HTTP_RW & {
  nosend: true
  nvs key: "WAPSSID"
  _default_var: "DEFAULT_AP_SSID"
}

modules wifi fields ap_password: _STRING & _NVS & _HTTP_RW & {
  nosend: true
  nvs key: "WAPPASS"
  _default_var: "DEFAULT_AP_PASSWORD"
}

modules wifi fields mdns_domain: _STRING & _NVS & _HTTP_RW & {
  remote: false
  name: "mdns_domain"
  nvs key: "MDNSD"
  default: string | *"supergreendriver"
  write_cb: true
}

modules wifi fields ip: _STRING & _HTTP & {
}
