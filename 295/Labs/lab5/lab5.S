# By Randy Panopio
# ID: 301294517
# rpanopio@sfu.ca 
    .section .note.GNU-stack, ""
    .global fibonacci, polynomial1, polynomial2, is_odd1, is_odd2, is_odd3, mul1, mul2
    .text

fibonacci:
    
    # keep calculations in rdi
    cmp $1, %rdi
    jg recursive_case
    # Base case: if n <= 1, return n
    mov %rdi, %rax
    ret

recursive_case:
    # Save n on the stack
    push %rdi

    # Calculate fibonacci(n-1)
    dec %rdi
    call fibonacci
    # Save the result of fibonacci(n-1) on the stack
    mov %rax, %rbx

    # Restore n and calculate fibonacci(n-2)
    pop %rdi
    sub $2, %rdi
    call fibonacci

    # Add the results of fibonacci(n-1) and fibonacci(n-2)
    add %rbx, %rax

    ret

polynomial1:
    # a = a*x*x*x 
    imul %rdi, %rsi
    imul %rdi, %rsi
    imul %rdi, %rsi

    # b = b*x*X
    imul %rdi, %rdx
    imul %rdi, %rdx

    # c = c*x
    imul %rdi, %rcx

    # add regs
    mov %rsi, %rax
    add %rdx, %rax
    add %rcx, %rax
    add %r8, %rax

    ret

polynomial2:
    # x*(x*(a*x + b) + c) + d
    mov %rsi, %rax
    imul %rdi, %rax
    add %rdx, %rax
    imul %rdi, %rax
    add %rcx, %rax
    imul %rdi, %rax
    add %r8, %rax
    ret

is_odd1:
    # rdi/r8 -> remainder in rdx, quotion in rax
    mov $0, %rdx
    mov %rdi, %rax
    mov $2, %r8 # divide by for checking if even or odd
    idiv %r8
    # check remainder if zero, if so iseven
    test %rdx, %rdx
    je is_even
    # otherwise odd
    mov $1, %rax
    ret
is_even:
    mov $0, %rax
    ret

is_odd2:
    # do bitewise and with one
    mov %rdi, %rax
    and $1, %rax
    ret

mul1:
    mov %rdi, %rax
    mov $65537, %r8
    mul %r8 # signed mul instruction mults into rax implicitly
    ret

mul2:
    # rax = n
    mov %rdi, %rax       # Copy the value of rdi to rax
    # n = n * 2^16 using shl
    shl $16, %rax
    # n = n * 2^16 + 1 (equating: n * 65537)
    add %rdi, %rax
    ret

