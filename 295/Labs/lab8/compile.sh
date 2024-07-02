#!/bin/bash

echo "setting virtual memory to 4gb"
ulimit -v 4194304  # limit to 4GB virtual memory
make clean
sudo gcc -Wall -Wpedantic -std=c17 -march=haswell -O3 array-2d.c
./a.out 5120000