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

DATA="$1"

if [ ! -f "$DATA" ]; then
  echo "USAGE: $0 /path/to/config.yml"
  exit
fi

DIR="main"

if [ "$#" -eq 2 ]; then
  DATA="$1"
  DIR="$2"
fi

GREEN="\033[0;32m"
NC="\033[0m"
for i in $(find $DIR -name '*.template')
do
  mustache $DATA $i > "${i/.template/}"
  echo -e "Processing $i: ${GREEN}Done${NC}"
done
