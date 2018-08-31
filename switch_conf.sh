#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Illegal number of parameters"
fi

NAME=$1

rm -rf main/conf
git clone git@github.com:vitaminwater/$NAME.git main/conf
