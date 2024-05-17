# Submission by Randy Panopio
# rpanopio@sfu.ca 
# ID: 301294517

    .section .note.GNU-stack, ""
    .global multiply_add
    .text

# calculate (a + (b * c))
# where a is arg1, b is arg2, c is arg3, and is typed int64_t 
# arg1 = %rdi, arg2 = %rsi, arg3 = %rdx
# thhis doesn't handle any overflow during it's operations.
multiply_add:
    # calculate b * c first
    imul %rsi, %rdx
    mov %rdx, %rax
    # add a to the return register
    add %rdi, %rax
    ret

