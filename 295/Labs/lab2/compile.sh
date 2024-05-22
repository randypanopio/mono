#!/bin/bash

(gcc -Wall -Wpedantic -std=c17 -march=haswell -g -c f.S calculate.S main.S)
(gcc -Wall -Wpedantic -std=c17 -march=haswell -c helpers.c -o helpers.o)
(gcc -nostdlib f.o calculate.o main.o helpers.o)
(./a.out)