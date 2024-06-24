all: main time
main: comp_tests asm link_main
time: comp_time asm link_timing

comp_tests:
	gcc -Wall -Wpedantic -std=c17 -march=haswell -c tests.c
comp_time: 
	gcc -Wall -Wpedantic -std=c17 -march=haswell -c lab7c.c timing.c
link_main:
	gcc lab7.o tests.o -o main.out
link_timing:
	gcc lab7.o lab7c.o timing.o -o timing.out
asm:
	as --warn -g lab7.S -o lab7.o

clean: 
	rm -f *.out *.o 