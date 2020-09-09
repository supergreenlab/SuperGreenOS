#!/bin/bash

# Copyright (C) 2019  SuperGreenLab <towelie@supergreenlab.com>
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

if [ "$#" -ne 3 ]; then
  echo "[Usage] $0 template_name module_name config_file"
  exit
fi

GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

TEMPLATE_NAME="$1"
MODULE_NAME="$2"
CONFIG="$3"
PROJECT_NAME=`basename $(pwd)` # TODO fix this

mkdir -p main/$MODULE_NAME
echo -e "Creating main/$MODULE_NAME: ${GREEN}Done${NC}"
for i in $(find templates/$TEMPLATE_NAME/code/*)
do
  FILE="$(basename ${i/.template/})"
  FILE_PATH="main/$MODULE_NAME/${FILE/$TEMPLATE_NAME/$MODULE_NAME}"
  ejs-cli -O "{\"name\": \"$MODULE_NAME\"}" $i > "$FILE_PATH"
  echo -e "Call ejs-cli for $i to $FILE_PATH: ${GREEN}Done${NC}"
done
for i in $(find templates/$TEMPLATE_NAME/config/*)
do
  FILE="$(basename ${i/.template/})"
  FILE_PATH="config_gen/config/$PROJECT_NAME/${FILE/$TEMPLATE_NAME/$MODULE_NAME}"
  ejs-cli -O "{\"name\": \"$MODULE_NAME\"}" $i > "$FILE_PATH"
  echo -e "Call ejs-cli for $i to $FILE_PATH: ${GREEN}Done${NC}"
done

./update_config.sh config_gen/config/$PROJECT_NAME/ $CONFIG

echo "==="
echo "Running ./update_templates.sh...."
./update_templates.sh $CONFIG
