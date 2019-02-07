#!/bin/bash

ruby -ryaml -rjson -e 'puts JSON.pretty_generate(YAML.load(ARGF))' < config.yml > spiffs_fs/config.json
