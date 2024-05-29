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

# ---- absolute value end---- 

# ---- powers of two ---- 
asdd:
  # check rdi for recursive step
  test %rdi, %rdi
  jne foo

bar:
  mov $1, %rax
  ret

foo:
  # should call power2 at some point for my recursive case
  call print_uint64
  ret

power2:
    # Base case: if rdi (n) is 0, print 1 and return
    test %rdi, %rdi
    jne recurse_double

double_base_case:
    mov $1, %rsi        # Value to print (1)
    call print_uint64   # Call print_uint64
    ret                 # Return from the function

recurse_double:
    push %rdi           # Save the current n on the stack
    dec %rdi            # Decrement n (n-1)
    call power2         # Recursive call to power2(n-1)
    pop %rdi            # Restore the original n from the stack

    # Calculate 2^n by doubling 2^(n-1)
    mov $1, %rsi        # Initialize the value to 1
    # shl %rdi, %rsi      # Calculate 2^n by left shifting 1 by n bits
    mov %rdi, %rsi
    add %rdi, %rsi

    call print_uint64   # Call print_uint64 to print 2^n
    ret                 # Return from the function
# ---- powers of two end ---- 

# ---- haildstone sequence ---- 
hailstone_length:
    # Base case: if n == 1, return 0
    cmp $1, %rdi        # Compare n (in %rdi) with 1
    je base_case        # If n == 1, jump to base_case

    # Recursive case: if n is even or odd
    push %rdi           # Save the current value of n on the stack

    # do bitewise and to check if rdi is even
    test $1, %rdi
    jz even_case

    # did not jump to even, proceeed to odd
odd_case: 
    # do 3*n + 1 to rdi
    imul $3, %rdi
    add $1, %rdi
    # recurse
    call hailstone_length
    jmp common_case

even_case:
    # do n//2 to rdi
    shr $1, %rdi
    call hailstone_length

common_case:
    # 
    pop %rdi            # Restore the original value of n
    add $1, %rax        # Add 1 to the result of the recursive call
    ret                 # Return the result

base_case:
    # set rax to zero on base case
    mov $0, %rax
    ret

# ---- haildstone sequence end ---- 