## some commands

scp -p24 -r rpanopio@csil-cpu1.csil.sfu.ca: /Users/randypanopio/Documents/mono/295/Labs/lab1
 /sfuhome/295

/Users/randypanopio/Documents/mono/295/Labs/lab1


scp -P24 /Users/randypanopio/Documents/mono/295/Labs/lab1 rpanopio@csil-cpu1.csil.sfu.ca:



gcc -Wall -Wpedantic -std=c17 -march=x86_64 array_sum_speed.c array_sum.S 

gcc -Wall -Wpedantic -std=c17 -march=haswell  array_sum_speed.c array_sum.S 


# clang compielr not avail in CSIl
clang -Wall -Wpedantic -std=c17 -march=haswell  array_sum_speed.c array_sum.S 