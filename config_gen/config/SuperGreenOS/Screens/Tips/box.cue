package config

_box_conf: [
  {
    enabled: 0
    temp_source: 0x10
    humi_source: 0x10
    vpd_source: 0x10
    weight_source: 1
    co2_source: 1
    blower_ref_source: 0
    fan_ref_source: 0
  },
]

modules box fields "\(k)_weight": {
  disabled: true
} for k, v in _box_conf

modules box fields "\(k)_weight_source": {
  disabled: true
} for k, v in _box_conf

