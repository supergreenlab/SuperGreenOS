#!/bin/bash

# Copyright (C) 2018  SuperGreenLab <towelie@supergreenlab.com>
# Author: Constantin Clauzel <constantin.clauzel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

set -e 

GREEN="\033[0;32m"
NC="\033[0m"
NAME="SuperGreenOSBoilerplate"
if [ "$#" -eq 1 ]; then
  NAME=$1
else
  echo "Using default name $NAME, change it as first parameter."
fi

TS=`date +"%s"`
DEST="releases/$NAME/$TS"
mkdir -p $DEST

sed -i -E "s/^#define OTA_BUILD_TIMESTAMP [^$]+/#define OTA_BUILD_TIMESTAMP ${TS}/g" main/core/ota/ota.h
echo -e "Set timestamp in main/core/ota/ota.h to $TS: ${GREEN}Done${NC}"
make -j4
echo -e "Building project: ${GREEN}Done${NC}"

for i in build/ota_data_initial.bin build/bootloader/bootloader.bin build/partitions.bin build/firmware.bin $IDF_PATH/components/esptool_py/esptool/esptool.py
do
cp $i $DEST/
echo -e "Copying $i to $DEST/$i: ${GREEN}Done${NC}"
done

echo $TS > "releases/$NAME/last_timestamp"
echo $TS > "$DEST/timestamp"

echo "#!/bin/bash" > $DEST/flash.sh
echo 'DIR=`dirname "$0"`' >> $DEST/flash.sh
echo 'DIR=`( cd "$DIR" && pwd )`' >> $DEST/flash.sh
echo 'python2 $DIR/esptool.py --chip esp32 --port /dev/ttyUSB1 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0xd000 $DIR/ota_data_initial.bin 0x1000 $DIR/bootloader.bin 0x10000 $DIR/firmware.bin 0x8000 $DIR/partitions.bin' >> $DEST/flash.sh
chmod +x $DEST/flash.sh
echo -e "Created $DEST/flash.sh: ${GREEN}Done${NC}"

# TODO DRY with ./write_spiffs.sh
echo -e "Creating spiffs.bin partition:"
mkdir spiffs_fs_gz
for i in $(ls ./spiffs_fs); do
  gzip -c "./spiffs_fs/$i" >> "./spiffs_fs_gz/$i"
  echo -e "Created spiffs_fs_gq/$i: ${GREEN}Done${NC}"
done
mkspiffs -c spiffs_fs_gz/ -b 4096 -p 256 -s 0x8000 $DEST/spiffs.bin
rm -rf spiffs_fs_gz

echo -e "Created $DEST/spiffs.bin: ${GREEN}Done${NC}"
echo "#!/bin/bash" > $DEST/write_spiffs.sh
echo 'DIR=`dirname "$0"`' >> $DEST/write_spiffs.sh
echo 'DIR=`( cd "$DIR" && pwd )`' >> $DEST/write_spiffs.sh
echo 'python $DIR/esptool.py --chip esp32 --port /dev/ttyUSB1 --baud 115200 write_flash -z 0x3f0000 spiffs.bin' >> $DEST/write_spiffs.sh
chmod +x $DEST/write_spiffs.sh
echo -e "Created $DEST/write_spiffs.sh: ${GREEN}Done${NC}"

sed -i -E "s/^#define OTA_BUILD_TIMESTAMP [^$]+/#define OTA_BUILD_TIMESTAMP 0/g" main/core/ota/ota.h
