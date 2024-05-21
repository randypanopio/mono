    .section .note.GNU-stack,""
    .global _start
    .text

# Name: Randy Panopio
# Student ID: 301294517
do_something:
    push %rbx
    mov $1, %rcx
    mov $0, %rbx
    
loop_top:
    add %rcx, %rbx
    add $2, %rcx    
    cmp %rdi, %rbx
    # modify the comparison, jump only if strictly greater
    # one option, increment + 1 to the comparison register, making it strictly greater than the original input
    jl loop_top
        
    mov %rbx, %rax
    pop %rbx
    ret

_start:
    mov $60, %rdi
    call do_something
        
    # exit
    mov $0, %rdi
    call syscall_exit
