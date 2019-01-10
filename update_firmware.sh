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

GREEN="\033[0;32m"
NC="\033[0m"
NAME="SuperGreenOSBoilerplate"
if [ "$#" -eq 1 ]; then
  NAME=$1
else
  echo "Using default name $NAME, change it as first parameter."
fi

DEST="releases/$NAME"
mkdir -p $DEST

TS=`date +"%s"`
sed -i -E "s/^#define OTA_BUILD_TIMESTAMP [^$]+/#define OTA_BUILD_TIMESTAMP ${TS}/g" main/core/ota/ota.h
make

for i in build/ota_data_initial.bin build/bootloader/bootloader.bin build/partitions.bin build/firmware.bin $IDF_PATH/components/esptool_py/esptool/esptool.py
do
cp $i $DEST/
echo -e "Copying $i to $DEST/$i: ${GREEN}Done${NC}"
done

echo $TS > $DEST/last_timestamp

echo "#!/bin/bash" > $DEST/flash.sh
echo 'DIR=`dirname "$0"`' >> $DEST/flash.sh
echo 'DIR=`( cd "$DIR" && pwd )`' >> $DEST/flash.sh
echo 'python2 $DIR/esptool.py --chip esp32 --port /dev/ttyUSB1 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0xd000 $DIR/ota_data_initial.bin 0x1000 $DIR/bootloader.bin 0x10000 $DIR/firmware.bin 0x8000 $DIR/partitions.bin' >> $DEST/flash.sh
chmod +x $DEST/flash.sh

sed -i -E "s/^#define OTA_BUILD_TIMESTAMP [^$]+/#define OTA_BUILD_TIMESTAMP 0/g" main/core/ota/ota.h
