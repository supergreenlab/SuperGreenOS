#!/bin/bash

set -e

GREEN="\033[0;32m"
NC="\033[0m"

echo -e "Creating spiffs.bin partition:"
rm -rf spiffs_fs_gz
mkdir -p spiffs_fs_gz
for i in $(ls ./spiffs_fs); do
  gzip -c "./spiffs_fs/$i" >> "./spiffs_fs_gz/$i"
  echo -e "Created spiffs_fs_gz/$i: ${GREEN}Done${NC}"
done
mkspiffs -c spiffs_fs_gz/ -b 4096 -p 256 -s 0x8000 spiffs.bin
echo -e "Created spiffs.bin: ${GREEN}Done${NC}"

python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port /dev/ttyUSB1 --baud 115200 write_flash -z 0x3f0000 spiffs.bin
rm spiffs.bin
rm -rf spiffs_fs_gz
