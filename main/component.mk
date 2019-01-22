# Core modules
COMPONENT_SRCDIRS := . core core/wifi core/ble core/kv core/ota core/httpd core/stat_dump core/time core/mqtt core/i2c

# Custom modules
COMPONENT_SRCDIRS += blower fans led mixer state status_led timer onoff manual

# I2C devices
COMPONENT_SRCDIRS += dust_gp2y10 sht1x arduino_co2
