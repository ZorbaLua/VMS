#!/bin/bash

for file in `find . -print | grep -i '.*[.]vm$'`
do
    vms $file < INPUT | diff -y -b - EXP >/dev/null
    if [ $? -eq 0 ]; then
        perl -C -e 'print chr 0x2713'
        echo $file
    else
        perl -C -e 'print chr 0x2717'
        echo $file
    fi
done
