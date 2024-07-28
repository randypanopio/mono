all: tests timing

tests:
	gcc -Wall -Wpedantic -march=haswell -O3 lab11.h lab11_vc.cpp lab11c.cpp lab11.S tests.cpp -o tests.out -funsafe-math-optimizations

timing:
	gcc -Wall -Wpedantic -march=haswell -O3 lab11.h lab11_vc.cpp lab11c.cpp lab11.S  timing.cpp -o timing.out -funsafe-math-optimizations

clean:
	rm -f *.out *.o