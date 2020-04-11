package config

modules mqtt: _CORE_MODULE & {
  field_prefix: "broker"
}

modules mqtt fields url: _STRING & _NVS & _HTTP_RW & {
  nvs key: "BRKR_URL"
  default: "mqtt://sink2.supergreenlab.com:1883"
}

modules mqtt fields channel: _STRING & _NVS & _HTTP_RW & {
  nvs key: "BRKR_CHN"
  default: ""
}

modules mqtt fields clientid: _STRING & _NVS & _BLE & _HTTP_RW & {
  ble uuid: "{0x17,0xfe,0xc3,0xc1,0x6b,0xe1,0x15,0x54,0xa5,0x74,0x55,0x9c,0x81,0x69,0x42,0x42}"
  nvs key: "BRKR_CLID"
  default: ""
}
