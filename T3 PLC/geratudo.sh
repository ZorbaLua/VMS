#!/bin/bash

for i in $(ls | egrep '.*.lin')
do
    echo $i
    mycc $i -o $(basename -s .lin $i).vm 
done

