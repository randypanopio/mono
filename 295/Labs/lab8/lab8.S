# By Randy Panopio
# ID: 301294517
# rpanopio@sfu.ca 
    .section .note.GNU-stack, ""
    .global hailstone_length_cmov, hailstone_length
.data

.text

hailstone_length_cmov:
    # conditional moves 'cmov' over jumps
    cmp $1, %rdi                # Compare n (in %rdi) with 1
    je base_case                # If n == 1, jump to base_case

    push %rdi                   # Save the current value of n on the stack

    mov %rdi, %rax              # Move n into %rax
    shr $1, %rax                # Calculate n / 2 (for even case) in %rax

    mov %rdi, %rdx              # Move n into %rdx
    imul $3, %rdx               # Calculate 3 * n (for odd case) in %rdx
    add $1, %rdx                # Calculate 3 * n + 1 (for odd case) in %rdx

    test $1, %rdi               # Test if %rdi is even
    cmovz %rax, %rdi            # If even, move %rax (n / 2) into %rdi
    cmovnz %rdx, %rdi           # If odd, move %rdx (3 * n + 1) into %rdi

    call hailstone_length       # Recurse

    pop %rdi                    # Restore pushed %rdi value
    add $1, %rax                # Increment %rax
    ret

# ---- haildstone sequence Lab3 implementation ----
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
    