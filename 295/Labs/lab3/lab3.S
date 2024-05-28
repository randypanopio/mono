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
power2:
    # check rdi for recursive step
    test %rdi, %rdi
    jne recurse_double

double_base_case:
    mov $1, %rax
    ret

recurse_double:
    push %rdi
    sub $1, %rdi
    call power2
    pop %rdi
    mul %rdi
    call print_uint64
    ret

factorial:
    # check rdi for recursive step
    test %rdi, %rdi
    jne fact_recursive_case

fact_base_case:
    mov $1, %rax
    ret

fact_recursive_case:
    push %rdi
    sub $1, %rdi
    call factorial
    pop %rdi
    mul %rdi
    ret
# ---- powers of two end ---- 

# ---- haildstone sequence ---- 
hailstone_length:
    # do nothing
    ret


# ---- haildstone sequence end ---- 