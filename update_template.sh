#!/bin/bash

for i in $(find . -name '*.template')
do
  mustache config.yml $i > "${i/.template/}"
done
