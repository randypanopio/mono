    .section .note.GNU-stack,""
    .global calculate
    .text

calculate:  
    # do nothing for now, check assemble step
    push %rbx       # push val of preserved register to stack
    mov %rdi, %rbx  # use rbx to maintain rdi (x)

    # a = x + 3
    push %r12       # push r12 register to stack, use it to stack val of this calc
    mov $3, %r12    # reset r12 value to 3, start of calc
    add %rbx, %r12  # x + 3
    
    # b = f(x, a)
    mov %rbx, %rdi  # put x input to arg1 register
    mov %r12, %rsi  # put a to arg2 register
    call f
    push %r13       # push r13 register to stack, use it to track val of this calc
    mov %rax, %r13  # set r13's value from the return register of call f

    # c = f(b, x)
    mov %r13, %rdi  # put r13 input to arg1 register
    mov %rbx, %rsi  # put x to arg2 register    
    call f
    push %r14       # push r14 register to stack, use it to track val of this calc
    mov %rax, %r14  # set r14's value from the return register of call f

    # d = f(x, c)
    mov %rbx, %rdi  # put x input to arg1 register
    mov %r14, %rsi  # put c to arg2 register
    call f
    push %r15       # push r15 register to stack, use it to track val of this calc
    mov %rax, %r15  # set r15's value from the return register of call f

    # a + b + c + d
    # user non-preserved registers to do the final calculation
    mov %r12, %rax  # begin tallying final result to rax
    add %r13, %rax  # a + b
    add %r14, %rax  # a + b + c
    add %r15, %rax  # a + b + c + d 

    # reset preseve registers in order
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %rbx
    ret
