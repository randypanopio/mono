all: tests timing

tests:
	gcc -Wall -Wpedantic -std=c17 -march=haswell lab8.S lab8c.c tests.c -o tests.out

timing:
	gcc -Wall -Wpedantic -std=c17 -march=haswell lab8.S lab8c.c timing.c -o timing.out


clean: 
	rm -f *.out *.o