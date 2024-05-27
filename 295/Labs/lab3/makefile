all: trace asmall

asmall: comp asm link

comp:
	gcc -Wall -Wpedantic -std=c17 -march=haswell -c helpers.c tests.c 

asm:
	as --warn -g lab3.S -o lab3.o

link:
	gcc lab3.o helpers.o tests.o

trace:
	gcc -Wall -Wpedantic -std=c17 -march=haswell -g traceable.c

clean: 
	rm -f *.out *.o