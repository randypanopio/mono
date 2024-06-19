all: p1 p2

p1:
	gcc -Wall -Wpedantic -std=c17 -march=haswell -O3 tests.c lab6.S -o p1.out

p2:
	g++ -Wall -Wpedantic -std=c++14 -march=haswell -O3 utf8.c utf8-test.c -o p2.out

clean: 
	rm -f *.out *.o p1 p2 *.html