#!/bin/bash

set -e

mkspiffs -c spiffs_fs/ -b 4096 -p 256 -s 0x4000 spiffs.bin
python releases/SuperGreenOS/esptool.py --chip esp32 --port /dev/ttyUSB1 --baud 115200 write_flash -z 0x300000 spiffs.bin
rm spiffs.bin
