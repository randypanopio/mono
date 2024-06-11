all: comp asm link

comp:
	gcc -Wall -Wpedantic -std=c17 -march=haswell -c tests.c 

asm:
	as --warn -g recursion.S -o recursion.o

link:
	gcc recursion.o tests.o

clean: 
	rm -f *.out *.o