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
   * [Table of Contents](#table-of-contents)

![WeedAppPic](assets/weedapppic.png?raw=true "WeedAppPic")

# SuperGreenOS

SuperGreenOS provides most features used when growing cannabis, all in one package, and controllable from your smartphone, pc, mac, linux, toaster, plumbus, whatnot...

## Who is this document for

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

# Quickstart

This quickstart will get you through the first step required

## Workspace setup

### Esp-idf setup

### Clone repo, build and run

### Connect to wifi

## Basic concept

## Key / value

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
- I2C_0_SDA
- I2C_0_SCL
- I2C_0_ENABLED
- I2C_1_SDA
- I2C_1_SCL
- I2C_1_ENABLED

### Controller keys

- STATE
- DEVICE_NAME

### Box keys

- BOX_0_ENABLED
- BOX_0_TIMER_TYPE
- BOX_0_TIMER_OUTPUT
- BOX_0_STARTED_AT
- BOX_0_ON_HOUR
- BOX_0_ON_MIN
- BOX_0_OFF_HOUR
- BOX_0_OFF_MIN
- BOX_0_STRETCH
- BOX_0_LED_DIM
- BOX_0_BLOWER
- BOX_0_BLOWER_MODE
- BOX_0_BLOWER_GPIO
- BOX_0_SHT
- BOX_0_SHT
- BOX_0_SHT
- BOX_0_ARDUINO_CO
- BOX_0_DUST_GPY
- BOX_0_LED_INFO

### Led keys

- LED_0_DUTY
- LED_0_GPIO
- LED_0_X
- LED_0_Y
- LED_0_Z
- LED_0_ENABLED
- LED_0_BOX
- LED_0_DIM
