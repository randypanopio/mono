#!/bin/bash

output_file="perf_output.txt"
echo "" > $output_file  # Clear the output file

echo "---- sorted -----"
for i in {1..10}; do 
    ./branching_test.out sort 16384
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out sort 16384 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)

    ./branching_test.out sort 65536
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out sort 65536 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)

    ./branching_test.out sort 1048576
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out sort 1048576 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)

    ./branching_test.out sort 4194304
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out sort 4194304 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)

    ./branching_test.out sort 16777216
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out sort 16777216 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)
done

echo "---- revsort -----"
for i in {1..10}; do 
    ./branching_test.out rev 16384
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out rev 16384 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)

    ./branching_test.out rev 65536
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out rev 65536 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)

    ./branching_test.out rev 1048576
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out rev 1048576 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)

    ./branching_test.out rev 4194304
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out rev 4194304 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)

    ./branching_test.out rev 16777216
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out rev 16777216 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)
done

echo "---- random -----"
for i in {1..10}; do 
    ./branching_test.out rand 16384
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out rand 16384 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)

    ./branching_test.out rand 65536
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out rand 65536 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)

    ./branching_test.out rand 1048576
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out rand 1048576 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)

    ./branching_test.out rand 4194304
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out rand 4194304 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)

    ./branching_test.out rand 16777216
    perf stat -e branch-misses,branch-instructions,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./branching_test.out rand 16777216 2>&1 | tee >(grep "branch-misses\|LLC-load-misses" >> $output_file)
done
