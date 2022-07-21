#!/bin/sh
clear 
make clean
make
./a.out >> log-ppg.log
echo "Hello"
