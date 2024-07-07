all: sort arr

sort:
	g++ -Wall -Wpedantic -std=c++17 -march=haswell -O3 -g sort.cpp -o sort.out

arr:
	gcc -Wall -Wpedantic -std=c17 -march=haswell -O1 -g array-2d.c -o arr.out

clean:
	rm -f *.out *.o