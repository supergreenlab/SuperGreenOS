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
  echo "ERROR: Illegal number of parameters"
  exit
fi

NAME=$1

pushd main/conf > /dev/null
if [[ `git status --porcelain` ]]; then
  echo "ERROR: Pending modifications in main/conf/ !"
  exit
fi
popd > /dev/null

rm -rf main/conf
git clone git@github.com:supergreenlab/$NAME.git main/conf
