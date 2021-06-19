package config

modules valve: _MODULE

modules valve fields "open": _INT8 & _HTTP & {
  default: 0
}

modules valve fields "gpio": _UINT8 & _HTTP & {
  default: int | *0
}

modules valve fields "enabled": _UINT8 & _NVS & _HTTP_RW & {
  default: false
  nvs key: "VA_E"
}

modules valve fields "cycle_div": _UINT8 & _NVS & _HTTP_RW & {
  default: 6
  nvs key: "CYC_D"
}

modules valve fields "cycle_duration": _UINT16 & _NVS & _HTTP_RW & {
  nvs key: "CYC_D_D"
  default: 1000
}

modules valve fields "ref_min": _UINT8 & _NVS & _HTTP_RW & {
  nvs key: "VA_RMI"
  default: 21
}

modules valve fields "ref_max": _UINT8 & _NVS & _HTTP_RW & {
  nvs key: "VA_RMA"
  default: 30
}

modules valve fields "ref": _UINT8 & _HTTP & _INDIR & {
  indir key: "valve_ref"
  indir source: "ref_source"
  default: 0
}

modules valve fields "ref_source": _UINT8 & _NVS & _HTTP_RW & {
  nvs key: "VA_RS"
  default: 0
}

modules valve fields "ref_on_min": _UINT8 & _NVS & _HTTP_RW & {
  nvs key: "VA_O_MI"
  default: 1
}

modules valve fields "ref_on_max": _UINT8 & _NVS & _HTTP_RW & {
  nvs key: "VA_O_MA"
  default: 100
}

modules valve fields "ref_on": _UINT8 & _HTTP & _INDIR & {
  indir key: "valve_ref_on"
  indir source: "ref_on_source"
  default: 0
}

modules valve fields "ref_on_source": _UINT8 & _NVS & _HTTP_RW & {
  nvs key: "VA_O_RS"
  default: 0
}
