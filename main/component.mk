# Core modules
COMPONENT_SRCDIRS := . core core/ble core/kv core/log core/time core/wifi core/ota core/mqtt core/stat_dump core/httpd core/i2c

# Custom modules
COMPONENT_SRCDIRS += led timers mixer state fans timers/manual timers/onoff blower status_led core/i2c/sht1x core/i2c/arduino_co2
