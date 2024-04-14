#!/bin/bash

set -e

SKIP_APP="0"

if [ $# -eq "1" ]; then
  SKIP_APP="$1"
fi

./update_config.sh config_gen/config/SuperGreenOS/Controllers/Solo config.solo.json
./update_templates.sh config.solo.json
./update_htmlapp.sh config.solo.json
./update_firmware.sh SoloV2.1Testing
if [ $SKIP_APP -eq "0" ]; then
  last_timestamp=$(cat ./releases/SoloV2.1Testing/last_timestamp)
  cp -r ./releases/SoloV2.1Testing/$last_timestamp/html_app ../SuperGreenApp2/assets/firmware/SoloV2.1/
  cp ./releases/SoloV2.1Testing/$last_timestamp/firmware.bin ../SuperGreenApp2/assets/firmware/SoloV2.1/
  cp ./releases/SoloV2.1Testing/$last_timestamp/timestamp ../SuperGreenApp2/assets/firmware/SoloV2.1/
  cp -r ./releases/SoloV2.1Testing ../backend/SuperGreenCloud/www/update/
fi

./update_config.sh config_gen/config/SuperGreenOS/Controllers/Pickle config.pickle.json
./update_templates.sh config.pickle.json
./update_htmlapp.sh config.pickle.json
./update_firmware.sh PickleV2.1Testing
if [ $SKIP_APP -eq "0" ]; then
  last_timestamp=$(cat ./releases/PickleV2.1Testing/last_timestamp)
  cp -r ./releases/PickleV2.1Testing/$last_timestamp/html_app ../SuperGreenApp2/assets/firmware/PickleV2.1/
  cp ./releases/PickleV2.1Testing/$last_timestamp/firmware.bin ../SuperGreenApp2/assets/firmware/PickleV2.1/
  cp ./releases/PickleV2.1Testing/$last_timestamp/timestamp ../SuperGreenApp2/assets/firmware/PickleV2.1/
  cp -r ./releases/PickleV2.1Testing ../backend/SuperGreenCloud/www/update/
fi

./update_config.sh config_gen/config/SuperGreenOS/Controllers/Driver config.driver.json
./update_templates.sh config.driver.json
./update_htmlapp.sh config.driver.json
./update_firmware.sh DriverV2.1Testing
if [ $SKIP_APP -eq "0" ]; then
  last_timestamp=$(cat ./releases/DriverV2.1Testing/last_timestamp)
  cp -r ./releases/DriverV2.1Testing/$last_timestamp/html_app ../SuperGreenApp2/assets/firmware/DriverV2.1/
  cp ./releases/DriverV2.1Testing/$last_timestamp/firmware.bin ../SuperGreenApp2/assets/firmware/DriverV2.1/
  cp ./releases/DriverV2.1Testing/$last_timestamp/timestamp ../SuperGreenApp2/assets/firmware/DriverV2.1/
  cp -r ./releases/DriverV2.1Testing ../backend/SuperGreenCloud/www/update/
fi

./update_config.sh config_gen/config/SuperGreenOS/Controllers/Controller/v2.1 config.controller.json
./update_templates.sh config.controller.json
./update_htmlapp.sh config.controller.json
./update_firmware.sh ControllerV2.1Testing
if [ $SKIP_APP -eq "0" ]; then
  last_timestamp=$(cat ./releases/ControllerV2.1Testing/last_timestamp)
  cp -r ./releases/ControllerV2.1Testing/$last_timestamp/html_app ../SuperGreenApp2/assets/firmware/ControllerV2.1/
  cp ./releases/ControllerV2.1Testing/$last_timestamp/firmware.bin ../SuperGreenApp2/assets/firmware/ControllerV2.1/
  cp ./releases/ControllerV2.1Testing/$last_timestamp/timestamp ../SuperGreenApp2/assets/firmware/ControllerV2.1/
  cp -r ./releases/ControllerV2.1Testing ../backend/SuperGreenCloud/www/update/
fi

./update_config.sh config_gen/config/SuperGreenOS/Controllers/Controller/v3 config.controller.json
./update_templates.sh config.controller.json
./update_htmlapp.sh config.controller.json
./update_firmware.sh ControllerV3Testing
if [ $SKIP_APP -eq "0" ]; then
  last_timestamp=$(cat ./releases/ControllerV3Testing/last_timestamp)
  cp -r ./releases/ControllerV3Testing/$last_timestamp/html_app ../SuperGreenApp2/assets/firmware/ControllerV3/
  cp ./releases/ControllerV3Testing/$last_timestamp/firmware.bin ../SuperGreenApp2/assets/firmware/ControllerV3/
  cp ./releases/ControllerV3Testing/$last_timestamp/timestamp ../SuperGreenApp2/assets/firmware/ControllerV3/
  cp -r ./releases/ControllerV3Testing ../backend/SuperGreenCloud/www/update/
fi

./update_config.sh config_gen/config/SuperGreenOS/Screens/Tips config.tips.json
./update_templates.sh config.tips.json
./update_htmlapp.sh config.tips.json
./update_firmware.sh TipsTesting
if [ $SKIP_APP -eq "0" ]; then
  last_timestamp=$(cat ./releases/TipsTesting/last_timestamp)
  cp -r ./releases/TipsTesting/$last_timestamp/html_app ../SuperGreenApp2/assets/firmware/Tips/
  cp ./releases/TipsTesting/$last_timestamp/firmware.bin ../SuperGreenApp2/assets/firmware/Tips/
  cp ./releases/TipsTesting/$last_timestamp/timestamp ../SuperGreenApp2/assets/firmware/Tips/
  cp -r ./releases/TipsTesting ../backend/SuperGreenCloud/www/update/
fi

./update_config.sh config_gen/config/SuperGreenOS/Screens/Screen config.screen.json
./update_templates.sh config.screen.json
./update_htmlapp.sh config.screen.json
./update_firmware.sh ScreenTesting
if [ $SKIP_APP -eq "0" ]; then
  last_timestamp=$(cat ./releases/ScreenTesting/last_timestamp)
  cp -r ./releases/ScreenTesting/$last_timestamp/html_app ../SuperGreenApp2/assets/firmware/Screen/
  cp ./releases/ScreenTesting/$last_timestamp/firmware.bin ../SuperGreenApp2/assets/firmware/Screen/
  cp ./releases/ScreenTesting/$last_timestamp/timestamp ../SuperGreenApp2/assets/firmware/Screen/
  cp -r ./releases/ScreenTesting ../backend/SuperGreenCloud/www/update/
fi
