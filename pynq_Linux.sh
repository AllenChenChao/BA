#!/bin/sh
clear 
make clean
make
./a.out >> log_add2.log
echo "Hello"
