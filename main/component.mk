# Core modules
COMPONENT_SRCDIRS := . core core/wifi core/ble core/kv core/ota core/httpd core/stat_dump core/time core/mqtt core/i2c core/reboot

# Custom modules
COMPONENT_SRCDIRS += led mixer state status_led timer onoff manual box

# I2C devices
COMPONENT_SRCDIRS += sht21
