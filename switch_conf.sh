#!/bin/bash

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
git clone git@github.com:vitaminwater/$NAME.git main/conf
