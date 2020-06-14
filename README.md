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

It is the official firmware for the [SuperGreenController](https://github.com/supergreenlab/SuperGreenController).

## Who is this document for

This document is for developpers that want to start playing with there controller's internal stuffs, or just setup their own hardware.
This repository is based on [SuperGreenOSBoilerplate](https://github.com/supergreenlab/SuperGreenOSBoilerplate), please read the doc here first.

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

This is the firmware that runs the [SuperGreenController](https://github.com/supergreenlab/SuperGreenController).

# Workspace setup

If you haven't already done it, you'll to setup esp-idf's toolchain and sdk.

They have a very good quickstart [here](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html).

## Clone repo, build and run

Now you should be able to clone and build the firmware:

```

git clone https://github.com/supergreenlab/SuperGreenOS.git
cd SuperGreenOS
./update_templates.sh config.controller.json
./update_htmlapp.sh config.controller.json
make -j4

```

The plug your controller or any esp32 based board and run the commands:

```

make -j4 flash monitor
./write_spiffs.sh

```

The first command flashes the firmware, the second writes the embedded admin interface on the tiny file system (~20KB available).

# How to use

Once the firmware is flashed you can access the controller's wifi network, once connected go to http://192.168.4.1/fs/app.html,
this will display the html embedded admin interface, which allows you to easily modify any of the controller's parameter.

![Admin](assets/admin.png?raw=true "Admin")


# Updated dev environment setup

## ESP-IDF

Docs reference:
https://docs.espressif.com/projects/esp-idf/en/v3.3.2/get-started/index.html

```bash
mkdir -p $HOME/esp && cd $HOME/esp
git clone --recursive https://github.com/espressif/esp-idf.git esp-idf_release_3.3.1
cd esp-idf_release_3.3.1
git checkout 143d26aa49df524e10fb8e41a71d12e731b9b71d
```

```bash
export IDF_PATH=$HOME/esp/esp-idf_release_3.3.1
source $IDF_PATH/export.sh
```

```bash
python2.7 -m pip install --user -r $IDF_PATH/requirements.txt
```
