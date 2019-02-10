#!/bin/bash

pushd html_app/
mustache data.yml index.html > ../spiffs_fs/app.html
popd
