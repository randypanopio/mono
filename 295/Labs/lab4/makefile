all: comp asm link

comp:
	gcc -Wall -Wpedantic -std=c17 -march=haswell -c tests.c 

asm:
	as --warn -g lab4.S -o lab4.o

link:
	gcc lab4.o tests.o

clean: 
	rm -f *.out *.o