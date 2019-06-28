find main/ -name '*.template' -exec sh -c 'echo ${1%.*}' sh {} \;
