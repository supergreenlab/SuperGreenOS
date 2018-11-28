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

if [ "$#" -ne 1 ]; then
  echo "Illegal number of parameters"
  exit
fi

pushd main/conf > /dev/null
if [[ `git status --porcelain` ]]; then
  echo "ERROR: Pending modifications in main/conf/ !"
  exit
fi
popd > /dev/null

NAME=$1
DEST="releases/$NAME"
mkdir -p $DEST

./switch_conf.sh $NAME

TS=`date +"%s"`
sed -i -E "s/^#define OTA_TIMESTAMP [^$]+/#define OTA_TIMESTAMP ${TS}UL/g" main/conf/ota_db.h
make
cp build/chronic-o-matic.bin $DEST/firmware.bin
echo $TS > $DEST/last_timestamp
# scp build/chronic-o-matic.bin ccsas.biz:/var/www/$NAME/firmware.bin
# ssh ccsas.biz "echo $TS > /var/www/$NAME/last_timestamp"
sed -i -E "s/^#define OTA_TIMESTAMP [^$]+/#define OTA_TIMESTAMP 0UL/g" main/conf/ota_db.h
