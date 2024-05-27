# gcc -Os -c helpers.c && as -g --warn recurse.S -o recurse.o && ld helpers.o recurse.o

    .section .note.GNU-stack,""
    .global _start

.text

factorial:
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
    

_start:
    mov $5, %rdi
    call factorial
    mov %rax, %rdi
    call print_uint64
    
    # exit
    mov $0, %rdi
    call syscall_exit
