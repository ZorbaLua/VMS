#!/bin/bash

STR=$'export PATH=${PATH}:${HOME}/bin'
FILE=~/.bash_profile

[ -d ~/bin ] || mkdir ~/bin

grep -qF "${STR}" "$FILE" || echo $'\n\n#path dos executaveis pessoais\n '${STR}$'\n\n' >> "$FILE"

cp $1 ~/bin/$2
source ~/.bash_profile
