# By Randy Panopio
# ID: 301294517
# rpanopio@sfu.ca 
    .section .note.GNU-stack, ""
    .global abs_value, power2, hailstone_length
    .text

abs_value:
    # compare to zero
    test %rdi, %rdi
    jl negate
    mov %rdi, %rax
    ret

negate:
    # negates the current rdi register
    # since only abs_value calls me, its fine to return and keep needed value in rdi
    neg %rdi
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
