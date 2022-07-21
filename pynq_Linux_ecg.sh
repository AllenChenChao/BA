#!/bin/sh
clear 
make clean
make
./a.out >> log-ecg.log
echo "Hello"
