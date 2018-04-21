#!/bin/bash

cd "../Test Files"
for file in `ls *.vm`
do
    echo $file
    vms $file 2>/dev/null
    if [ $? -eq 0 ]; then
        perl -C -e 'print chr 0x2713'
    else
        perl -C -e 'print chr 0x2717'
    fi
    echo ""
done
