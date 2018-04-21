#!/bin/bash

cd "../Test Files"
for file in `ls *.vm`
do
    vms $file 
    if [ $? -eq 0 ]; then
        perl -C -e 'print chr 0x2713'
        echo " " $file
    else
        perl -C -e 'print chr 0x2717'
        echo " " $file
    fi
done

