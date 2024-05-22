    .section .note.GNU-stack,""
    .global _start
    .text

# Name: Randy Panopio
# Student ID: 301294517
do_something:
    push %rbx           # push preserved register to stack
    mov $1, %rcx        # replace rcx with the value 1
    mov $0, %rbx        # replace rbx with the value 0
    
loop_top:
    add %rcx, %rbx      # add current rcx to rbx
    add $2, %rcx        # add 2 to rcx (curent state is 2+rbx)

    # TODO modify the comparison, jump only if strictly greater
    # option 1, increment + 1 to the register being compared, making it strictly greater than the original input.
    # option 2, change the cmp operator with jg and switch the comparison.  

    # original cmp and jump
    # cmp %rdi, %rbx      # compare rdi from rbx
    # jl loop_top         # jump to line 12 iff cmp rdi < rbx

    # modified strictly if rdi was strictly greater than rbx.
    cmp %rbx, %rdi        # compare rbx from rdi
    jg loop_top           # jump to line 12 iff rbx > rdi
        
    mov %rbx, %rax      # if did not jump, set return val with rbx
    pop %rbx            # pop rbx back to original state
    ret

_start:
    mov $60, %rdi       # set arg1 register to 60
    call do_something   
        
    # exit
    mov $0, %rdi        # reset arg1 register to 0
    call syscall_exit
