all: merge insertion tim branching_test

merge:
	gcc -Wall -Wpedantic -march=haswell -o test_merge.out mergesort_test.c -lm

insertion:
	gcc -Wall -Wpedantic -march=haswell -o test_insertion.out insertionsort_test.c -lm

tim:
	gcc -Wall -Wpedantic -march=haswell -o test_tim.out timsort_test.c timsort/timsort.c -lm

branching_test:
	gcc -Wall -Wpedantic -march=haswell -o branching_test.out branching_timsort.c timsort/timsort.c -lm

clean:
	rm -f *.out *.o
