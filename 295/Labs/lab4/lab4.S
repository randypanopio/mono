# By Randy Panopio
# ID: 301294517
# rpanopio@sfu.ca 
    .section .note.GNU-stack, ""
    .global is_prime, largest_power_unsigned, overflowing_subtract, dumb
    .text

# ---- is_prime ---- 
is_prime:
    # handle cases 2, and <1
    cmp $2, %rdi
    je prime
    cmp $1, %rdi
    jle not_prime

    # iterating using r8, starting from 2
    mov $2, %r8

prime_loop:
    # If r8 >= rdi (reached final divisor), then is prime
    cmp %rdi, %r8
    jge prime 

    # rdi/r8 -> remainder in rdx, quotion in rax
    mov $0, %rdx
    mov %rdi, %rax
    div %r8

    # check remainder if zero, if so it was divisible so not prime
    test %rdx, %rdx
    je not_prime

    # Increment r8 iterator and loop
    inc %r8
    jmp prime_loop

prime:
    mov $1, %rax
    ret

not_prime:
    mov $0, %rax
    ret

# ---- largest_power_unsigned ---- 
largest_power_unsigned:
    # begin comparison calc using rax
    mov %rdi, %rax
    # store n on r9 for future multiplication
    mov %rdi, %r9
    mov $0, %r10

power_loop:
    # store calculated value to rax
    # temporarily store current rax to r10 (previous iter before mul)
    mov %rax, %r10
    # multiply n to itself again, mul mults it into rax implicitly
    mul %r9
    jo power_overflow

    # didnt overflow, proceed with iteration
    jmp power_loop 
    ret

power_overflow:
    mov %r10, %rax
    ret

# ---- overflowing_subtract ---- 
overflowing_subtract:
    # Subtract b from a and store the result in rax
    mov %rdi, %rax   # Move a to rax
    sub %rsi, %rax   # Subtract b from a
    # Check for signed overflow
    jo overflow_detected

    # If no overflow, return rax
    ret

overflow_detected:
    # If overflow, return 0
    mov $0, %rax
    ret

# ---- dumb ---- 
dumb:
    # cases: 
    # c1(a!=0, b=0)->ret(a)  
    # c2(a=0)->ret(b+1) 
    # c_common->ret(dumb)
    # a = rdi, b = rsi
    
case_1:
    # case 1: if a == 0 
    test %rdi, %rdi
    jne case_2
    # returne b+!
    mov %rsi, %rax
    add $1, %rax
    ret

case_2:
    # case 2: if b == 0, return a, but need to check if its also c1
    test %rsi, %rsi
    jne recursive_case # case 1 and case 2 failed, proceed to recursive case
    mov %rdi, %rax
    ret


recursive_case:
    # save a,b to stack
    push %rdi
    push %rsi

    # a-1, b-1
    dec %rdi
    dec %rsi

    # recurse with (a-1, b-1)
    call dumb

    # instruct pop from stack, restoring a, b values
    pop %rsi
    pop %rdi

    # Perform the final calculation: a + a + b + rec
    mov %rdi, %r8   # use r8 for calc
    add %rdi, %r8   # r8 = a + a
    add %rsi, %r8   # r8 = a + a + b
    add %r8, %rax   # rax = a + a + b + rec
    ret