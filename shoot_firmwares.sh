#!/bin/bash

set -e

./update_config.sh config_gen/config/SuperGreenOS/Solo config.solo.json
./update_templates.sh config.solo.json
./update_htmlapp.sh config.solo.json
./update_firmware.sh SoloV2.1Testing
last_timestamp=$(cat ./releases/SoloV2.1Testing/last_timestamp)
cp -r ./releases/SoloV2.1Testing/$last_timestamp/html_app ../SuperGreenApp2/super_green_app/assets/firmware/SoloV2.1/
cp ./releases/SoloV2.1Testing/$last_timestamp/firmware.bin ../SuperGreenApp2/super_green_app/assets/firmware/SoloV2.1/
cp ./releases/SoloV2.1Testing/$last_timestamp/timestamp ../SuperGreenApp2/super_green_app/assets/firmware/SoloV2.1/
cp -r ./releases/SoloV2.1Testing ../backend/SuperGreenCloud/www/update/

./update_config.sh config_gen/config/SuperGreenOS/Pickle config.pickle.json
./update_templates.sh config.pickle.json
./update_htmlapp.sh config.pickle.json
./update_firmware.sh PickleV2.1Testing
last_timestamp=$(cat ./releases/PickleV2.1Testing/last_timestamp)
cp -r ./releases/PickleV2.1Testing/$last_timestamp/html_app ../SuperGreenApp2/super_green_app/assets/firmware/PickleV2.1/
cp ./releases/PickleV2.1Testing/$last_timestamp/firmware.bin ../SuperGreenApp2/super_green_app/assets/firmware/PickleV2.1/
cp ./releases/PickleV2.1Testing/$last_timestamp/timestamp ../SuperGreenApp2/super_green_app/assets/firmware/PickleV2.1/
cp -r ./releases/PickleV2.1Testing ../backend/SuperGreenCloud/www/update/

./update_config.sh config_gen/config/SuperGreenOS/Driver config.driver.json
./update_templates.sh config.driver.json
./update_htmlapp.sh config.driver.json
./update_firmware.sh DriverV2.1Testing
last_timestamp=$(cat ./releases/DriverV2.1Testing/last_timestamp)
cp -r ./releases/DriverV2.1Testing/$last_timestamp/html_app ../SuperGreenApp2/super_green_app/assets/firmware/DriverV2.1/
cp ./releases/DriverV2.1Testing/$last_timestamp/firmware.bin ../SuperGreenApp2/super_green_app/assets/firmware/DriverV2.1/
cp ./releases/DriverV2.1Testing/$last_timestamp/timestamp ../SuperGreenApp2/super_green_app/assets/firmware/DriverV2.1/
cp -r ./releases/DriverV2.1Testing ../backend/SuperGreenCloud/www/update/

./update_config.sh config_gen/config/SuperGreenOS/Controller/v2.1 config.controller.json
./update_templates.sh config.controller.json
./update_htmlapp.sh config.controller.json
./update_firmware.sh ControllerV2.1Testing
last_timestamp=$(cat ./releases/ControllerV2.1Testing/last_timestamp)
cp -r ./releases/ControllerV2.1Testing/$last_timestamp/html_app ../SuperGreenApp2/super_green_app/assets/firmware/ControllerV2.1/
cp ./releases/ControllerV2.1Testing/$last_timestamp/firmware.bin ../SuperGreenApp2/super_green_app/assets/firmware/ControllerV2.1/
cp ./releases/ControllerV2.1Testing/$last_timestamp/timestamp ../SuperGreenApp2/super_green_app/assets/firmware/ControllerV2.1/
cp -r ./releases/ControllerV2.1Testing ../backend/SuperGreenCloud/www/update/

./update_config.sh config_gen/config/SuperGreenOS/Controller/v3 config.controller.json
./update_templates.sh config.controller.json
./update_htmlapp.sh config.controller.json
./update_firmware.sh ControllerV3Testing
last_timestamp=$(cat ./releases/ControllerV3Testing/last_timestamp)
cp -r ./releases/ControllerV3Testing/$last_timestamp/html_app ../SuperGreenApp2/super_green_app/assets/firmware/ControllerV3/
cp ./releases/ControllerV3Testing/$last_timestamp/firmware.bin ../SuperGreenApp2/super_green_app/assets/firmware/ControllerV3/
cp ./releases/ControllerV3Testing/$last_timestamp/timestamp ../SuperGreenApp2/super_green_app/assets/firmware/ControllerV3/
cp -r ./releases/ControllerV3Testing ../backend/SuperGreenCloud/www/update/
