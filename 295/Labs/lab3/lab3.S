# By Randy Panopio
# ID: 301294517
# rpanopio@sfu.ca 
    .section .note.GNU-stack, ""
    .global abs_value, power2, hailstone_length
    .text

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


power2:
    # loop up to 2^n
    # do a compare
    jle double
    ret

double:
    mov %rdi, %r8
    add %rdi, %r8
    mov %r8, %rax
    # finish this
    ret

hailstone_length:
    # do nothing
    ret
