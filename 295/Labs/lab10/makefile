all: tests timing sin

sin:
	gcc -Wall -Wpedantic -std=c17 -march=haswell -O3 lab10c.c lab10.S sin.c -lm -o sin.out

tests:
	gcc -Wall -Wpedantic -std=c17 -march=haswell -O3 lab10.S lab10.h lab10c.c tests.c -o tests.out
timing: 
	gcc -Wall -Wpedantic -std=c17 -march=haswell -O0 lab10.S lab10.h lab10c.c timing.c -o timing.out
comp_tests:
	gcc -Wall -Wpedantic -std=c17 -march=haswell -c lab10.h tests.c
link_tests:
	gcc lab10.o tests.o -o tests.out
asm:
	as --warn -g lab10.S -o lab10.o

arr:
	gcc -Wall -Wpedantic -std=c17 -march=haswell -O0 -g array-2d.c -o arr.out

clean:
	rm -f *.out *.o