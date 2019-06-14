#!/bin/bash

CONFIG="$1"

if [ ! -f "$CONFIG" ]; then
  echo "USAGE: $0 /path/to/config.yml"
  exit
fi

ruby -ryaml -rjson -e 'puts JSON.pretty_generate(YAML.load(ARGF))' < "$CONFIG" > spiffs_fs/config.json
