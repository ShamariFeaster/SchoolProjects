#!/bin/bash

clear
make clean
make
echo -e "\n>>>>>>>>>>Output from $1"
example0 < $1
echo -e "\n>>>>>>>>>>Translated cpp file (mya.cpp)\n"
cat mya.cpp
echo -e "\n>>>>>>>>>>Output from cat $1\n"
cat $1
echo -e "\n>>>>>>>>>>END OF SCRIPT\n"
