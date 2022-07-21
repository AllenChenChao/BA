#!/bin/sh
clear 
make clean
make
./a.out >> log-eeg.log
echo "Hello"
