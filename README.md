![SuperGreenLab](assets/sgl.png?raw=true "SuperGreenLab")

[![SuperGreenLab](assets/reddit-button.png?raw=true "SuperGreenLab")](https://www.reddit.com/r/SuperGreenLab)

# Table of Contents

   * [SuperGreenOS](#supergreenos)
      * [Who is this document for](#who-is-this-document-for)
      * [Features](#features)
   * [Quickstart](#quickstart)
      * [Workspace setup](#workspace-setup)
         * [Esp-idf setup](#esp-idf-setup)
         * [Clone repo, build and run](#clone-repo-build-and-run)
         * [Connect to wifi](#connect-to-wifi)
      * [Basic concept](#basic-concept)
      * [Key / value](#key--value)
      * [Available keys](#available-keys)
         * [Core keys](#core-keys)
         * [Controller keys](#controller-keys)
         * [Box keys](#box-keys)
         * [Led keys](#led-keys)

![WeedAppPic](assets/weedapppic.png?raw=true "WeedAppPic")

# SuperGreenOS

SuperGreenOS provides most features used when growing cannabis, all in one package, and controllable from your smartphone, pc, mac, linux, toaster, plumbus, whatnot...

It is the official firmware for the [SuperGreenDriver](https://github.com/supergreenlab/SuperGreenController).

## Who is this document for

This document is for developpers that want to start playing with there controller's internal stuffs, or just setup their own hardware.

## Features

Here's what it can (or will) do:

- Lights on and off schedules
- Up to 6 separate led channels (you can put multiple leds behind one channel)
- Up to 3 separate timers, for full-cycle setups (veg + flo)
- Monitoring a wide range of sensors
- Data sent to a **private** [cloud](https://github.com/supergreenlab/SuperGreenCloud)
- Produce alerts based on sensor values
- Allows remote control (TODO)
- Manual ventilation control
- Automatic ventilation control based on temperature and humidity (TODO)
- `Stretch` mode, allows to choose how much you want your plant to stretch or thicken
- `Sunglass` mode, so you don't burn your eyes when you work on your plants
- More to come..

This is the firmware that runs the [SuperGreenDriver](https://github.com/supergreenlab/SuperGreenDriver).

# Workspace setup

If you haven't already done it, you'll to setup esp-idf's toolchain and sdk.

They have a very good quickstart [here](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html).

### Clone repo, build and run

Now you should be able to clone and build the firmware:

```

git clone https://github.com/supergreenlab/SuperGreenOS.git
cd SuperGreenOS
make

```

# Basic concept

## SuperGreenOSBoilerplate

This repository is based on [SuperGreenOSBoilerplate](https://github.com/supergreenlab/SuperGreenOSBoilerplate), please read the doc here first.

##

The whole OS revolves around the key/value database embedded (KV) in the firmware.
KV is the center of trust, it sits in the middle. All modules can add more keys to work with.
All keys are defined in the file [config.yml](https://github.com/supergreenlab/SuperGreenOS/blob/master/config.yml).

Each keys have a set of avaiable configs:

- *name*: lowercase name, ex: wifi_ssid
- *caps_name*: uppcase name, ex: WIFI_SSID
- *string* or *integer*: should have the value true, determines the datatype used for the value (string is a char[512] and integer is int)
- *nvs*: if absent the key is not persistent between reboots (ie. not stored in flash)
  - *key*: name of the key in the flash, limited to 15 characters, ex: WSSID
- *ble*: if absent, the key will not be available over ble, watchout ble only supports a limited number of available keys.
  - *first*: needs to be set to true if it's the first on the list, that's a mustache template limitation:( 
  - *uuid*: BLE UUID, in the form: "{0x17,0xfe,0xc3,0xc1,0x6b,0xe1,0x15,0x54,0xa5,0x74,0x55,0x9c,0x81,0x69,0xa3,0x6c}" see [here](http://yupana-engineering.com/online-uuid-to-c-array-converter)
  - *write*: Set this to true if the key is writable
  - *notify*: Set this to true to tell the generated to produce a ble notification on value internally changed.
- *http*: if absent, the key is not be available over http
  - *write*: Set this to true if the key is writable
  - *noop*: Set this to true, just to avoid have an empty 'http' configuration (when `write` is absent)
- *write_cb*: This determines if you want a callback to be called when the key is changed, either set it to `true` and it'll call a function called `on_set_[name]`, or directly enter the name of a function you have. prototype of the function is as: `const char *on_set_name(const char *ssid)` for a string or `int on_set_name(int boxId, int value)` for integer values.
- *default*: This is the default value for the key, if the value is in a variable or macro in you code, skip this and use `default_var` instead.
- *default_var*: allows to use a variable or macro name for the default value.

## Available keys

### Core keys

- WIFI_STATUS
- WIFI_SSID
- WIFI_PASSWORD
- TIME
- N_RESTARTS
- OTA_TIMESTAMP
- OTA_SERVER_IP
- OTA_SERVER_HOSTNAME
- OTA_SERVER_PORT
- OTA_VERSION_FILENAME
- OTA_FILENAME
- BROKER_URL
- I2C_X_SDA
- I2C_X_SCL
- I2C_X_ENABLED

### Controller keys

- STATE
- DEVICE_NAME

### Box keys

- BOX_X_ENABLED
- BOX_X_TIMER_TYPE
- BOX_X_TIMER_OUTPUT
- BOX_X_STARTED_AT
- BOX_X_ON_HOUR
- BOX_X_ON_MIN
- BOX_X_OFF_HOUR
- BOX_X_OFF_MIN
- BOX_X_STRETCH
- BOX_X_LED_DIM
- BOX_X_BLOWER
- BOX_X_BLOWER_MODE
- BOX_X_BLOWER_GPIO
- BOX_X_SHT
- BOX_X_SHT
- BOX_X_SHT
- BOX_X_ARDUINO_CO
- BOX_X_DUST_GPY
- BOX_X_LED_INFO

### Led keys

- LED_X_DUTY
- LED_X_GPIO
- LED_X_X
- LED_X_Y
- LED_X_Z
- LED_X_ENABLED
- LED_X_BOX
- LED_X_DIM
