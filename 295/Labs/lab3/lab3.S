# By Randy Panopio
# ID: 301294517
# rpanopio@sfu.ca 
    .section .note.GNU-stack, ""
    .global abs_value, power2, hailstone_length
    .text

# ---- absolute value ---- 
abs_value:
    # do the comparison in rax, can use it for calc in place
    mov %rdi, %rax
    # compare to zero
    test %rax, %rax
    # run an abs val to rax if number is negative
    jl negate
    ret

negate:
    # negates the current rax register
    # since only abs_value calls me, its fine to return and keep needed value in rax
    neg %rax
    ret

# ---- powers of two ---- 
power2:
    # Base case: if rdi (n) is 0, print 1 and return
    # calculate power2 directly then iterate towards it

    # jump to case zero if input is zero
    test %rdi, %rdi
    je case_zero

    # store on r8 calc value, starting from 1 to 2^n
    mov $1, %r8
    # print case 1 before calculating
    call print

calculate_power2:
    # calculate up to 2^n, decrementing rdi and storing iterations on r8
    test %rdi, %rdi
    jne shift_to_n
    ret

shift_to_n:
    # do increment of iteration using rdi and shift left for doubling our value (on r8)
    push %rdi
    dec %rdi
    shl %r8
    call print
    call calculate_power2
    pop %rdi
    ret

print:
    # store to temp register r10 val of rdi to call print function
    mov %rdi, %r10
    mov %r8, %rdi
    call print_uint64
    mov %r10, %rdi
    ret

case_zero:
    mov $1, %rdi
    call print_uint64
    ret

# ---- haildstone sequence ---- 
hailstone_length:
    # Compare n (in %rdi) with 1, if not eq 1, continue calculation
    cmp $1, %rdi
    # If n == 1, jump to base_case
    je base_case

    # Save the current value of n on the stack
    push %rdi           

    # proceed ro branching
    # do bitwise and to check if rdi is even
    test $1, %rdi
    jz even_case

    # did not jump to even, proceeed to odd
odd_case: 
    # do 3*n + 1 to rdi
    imul $3, %rdi
    add $1, %rdi
    # recurse
    call hailstone_length
    # jump and add last case of calculation
    jmp common_case

even_case:
    # do n//2 to rdi
    shr $1, %rdi
    call hailstone_length
    # jump and add last case of calculation
    jmp common_case

common_case:
    # restore pushed rdi value. "pop from the call stack", and return 
    pop %rdi
    add $1, %rax
    ret

base_case:
    # set rax to zero on base case
    mov $0, %rax
    ret

