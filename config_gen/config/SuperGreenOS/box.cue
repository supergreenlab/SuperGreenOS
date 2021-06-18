package config

_box_conf: [...]

modules box: _MODULE & {
  init: false
  array_len: len(_box_conf)
}

modules box fields "\(k)_temp": _INT8 & _HTTP & _INDIR & {
  dump_freq: 1
  indir key: "temp_sensor"
  indir source: "\(k)_temp_source"
  default: 0
} for k, v in _box_conf

modules box fields "\(k)_temp_source": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_T_SRC"
  default: v.temp_source
} for k, v in _box_conf

modules box fields "\(k)_humi": _INT8 & _HTTP & _INDIR & {
  dump_freq: 1
  indir key: "humi_sensor"
  indir source: "\(k)_humi_source"
  default: 0
} for k, v in _box_conf

modules box fields "\(k)_humi_source": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_H_SRC"
  default: v.humi_source
} for k, v in _box_conf

modules box fields "\(k)_vpd": _UINT8 & _HTTP & _INDIR & {
  dump_freq: 1
  indir key: "vpd_sensor"
  indir source: "\(k)_vpd_source"
  default: 0
} for k, v in _box_conf

modules box fields "\(k)_vpd_source": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_VPD_SRC"
  default: v.vpd_source
} for k, v in _box_conf

modules box fields "\(k)_weight": _INT32 & _HTTP & _INDIR & {
  dump_freq: 1
  indir key: "weight_sensor"
  indir source: "\(k)_weight_source"
  default: 0
} for k, v in _box_conf

modules box fields "\(k)_weight_source": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_W_SRC"
  default: v.weight_source
} for k, v in _box_conf

modules box fields "\(k)_co2": _INT32 & _HTTP & _INDIR & {
  dump_freq: 1
  indir key: "co2_sensor"
  indir source: "\(k)_co2_source"
  default: 0
} for k, v in _box_conf

modules box fields "\(k)_co2_source": _INT8 & _NVS & _HTTP_RW & {
  nvs key: "B_\(k)_CO_SRC"
  default: v.co2_source
} for k, v in _box_conf

modules box fields "\(k)_enabled": _INT8 & _NVS & _HTTP_RW & {
  default: v.enabled
  nvs key: "B_\(k)_E"
  write_cb: true
} for k, v in _box_conf
