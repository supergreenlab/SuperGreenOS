#!/bin/bash

NAME=''
HTML_APP_DIR=''

if [ "$#" -eq 2 ]; then
  NAME=$1
  HTML_APP_DIR=$2
else
  echo "Usage: $(basename $BASH_SOURCE) controller.local path/to/html_app"
  exit
fi

curl -XPOST --upload-file $HTML_APP_DIR/config.json -vvv http://$NAME/fs/config.json
curl -XPOST --upload-file $HTML_APP_DIR/app.html -vvv http://$NAME/fs/app.html
