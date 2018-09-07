#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Illegal number of parameters"
fi

NAME=$1

pushd main/conf > /dev/null
if [[ `git status --porcelain` ]]; then
  echo "ERROR: Pending modifications in main/conf/ !"
  exit
fi
popd > /dev/null

./switch_conf.sh $NAME

TS=`date +"%s"`
sed -i '' -E "s/^#define OTA_TIMESTAMP [^$]+/#define OTA_TIMESTAMP ${TS}UL/g" main/conf/ota_db.h
ssh ccsas.biz "echo $TS > /var/www/$NAME/last_timestamp"
make
scp build/chronic-o-matic.bin ccsas.biz:/var/www/$NAME/firmware.bin
sed -i '' -E "s/^#define OTA_TIMESTAMP [^$]+/#define OTA_TIMESTAMP 0UL/g" main/conf/ota_db.h
