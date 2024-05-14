# gcc -c helpers.c -o helpers.o && as --warn preserve.S -o preserve.o && ld helpers.o preserve.o

    .section .note.GNU-stack,""
    .global _start
    .text

# Return (a*b) + (a&b) + (a-b)
# %rdi = a
# %rsi = b
# %rbx = tmp
# %rax = result
mult_and_sub:
    push %rbx
    # a*b
    mov %rdi, %rax
    imul %rsi, %rax
    # ... + a&b
    mov %rdi, %rbx
    and %rsi, %rbx
    add %rbx, %rax
    # ... + a-b
    sub %rsi, %rdi
    add %rdi, %rax
    pop %rbx
    ret

_start:
    mov $1234, %rbx
    mov $5, %rdi
    mov $7, %rsi
    call mult_and_sub
    
    mov %rax, %rdi
    call print_int64

    mov %rbx, %rdi
    call print_int64  # must print 1234
    
    mov $0, %rdi
    call syscall_exit
