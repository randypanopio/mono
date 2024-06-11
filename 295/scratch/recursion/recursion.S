# gcc -Os -c helpers.c && as -g --warn recurse.S -o recurse.o && ld helpers.o recurse.o

    .section .note.GNU-stack,""
    .global recurse

.text

recurse:
    test %rdi, %rdi
    jne recursive_case

base_case:
    mov $1, %rax
    ret

recursive_case:
    push %rdi
    sub $1, %rdi
    call recurse
    pop %rdi
    mul %rdi # signed mul instruction mults into rax implicitly
    ret

