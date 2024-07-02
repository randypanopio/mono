# By Randy Panopio
# ID: 301294517
# rpanopio@sfu.ca 
    .section .note.GNU-stack, ""
    .global hailstone_length_cmov, hailstone_length
.data

.text

hailstone_length_cmov:
    # conditional moves 'cmov' over jumps
    # check if base cased reached
    cmp $1, %rdi
    je base_case

    # save rdi
    push %rdi

    # calcualte even case on rax (n//2)
    mov %rdi, %rax
    shr $1, %rax

    # calculate odd case on rdx (3*n+1)
    mov %rdi, %rdx
    imul $3, %rdx
    add $1, %rdx

    # do hailstone case, change rdi with odd/even case on what rdi/n currently is
    test $1, %rdi
    cmovz %rax, %rdi
    cmovnz %rdx, %rdi

    # Recurse
    call hailstone_length_cmov       

    # restore rdi
    pop %rdi
    # increment rax 
    add $1, %rax
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
    