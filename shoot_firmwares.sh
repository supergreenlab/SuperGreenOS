#!/bin/bash

./update_config.sh config_gen/config/SuperGreenOS/Driver config.driver.json
./update_templates.sh config.driver.json
./update_htmlapp.sh config.driver.json
./update_firmware.sh DriverV2.1Testing
cp -r ./releases/DriverV2.1Testing ../backend/SuperGreenCloud/www/update/DriverV2.1Testing

./update_config.sh config_gen/config/SuperGreenOS/Controller config.controller.json
./update_templates.sh config.controller.json
./update_htmlapp.sh config.controller.json
./update_firmware.sh ControllerV2.1Testing
cp -r ./releases/ControllerV2.1Testing ../backend/SuperGreenCloud/www/update/ControllerV2.1Testing
