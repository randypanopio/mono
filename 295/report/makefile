all: merge insertion tim

merge:
	gcc -Wall -Wpedantic -march=haswell -o test_merge.out mergesort_test.c -lm

insertion:
	gcc -Wall -Wpedantic -march=haswell -o test_insertion.out insertionsort_test.c -lm

tim:
	gcc -Wall -Wpedantic -march=haswell -o test_tim.out timsort_test.c timsort/timsort.c -lm

tim_mem:
	gcc -Wall -Wpedantic -march=haswell -o tim_mem.out timsort_mem.c timsort/timsort.c -lm

clean:
	rm -f *.out *.o
