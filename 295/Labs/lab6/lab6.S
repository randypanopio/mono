# By Randy Panopio
# ID: 301294517
# rpanopio@sfu.ca 
    .section .note.GNU-stack, ""
    .global strlen_mine, strlen_utf8 
    .text

strlen_mine:
    # reset counter
    mov $0, %rax

loop_strlen_mine:
    movzbq (%rdi), %rdx # Load byte at address rdi into rdx, zero-extend to 64-bit
    test %rdx, %rdx
    je null_char # reached 0 byte/null char

    # increment counters and move to next byte and loop again
    add $1, %rdi
    add $1, %rax
    jmp loop_strlen_mine
    ret


strlen_utf8 :
    # reset counter
    mov $0, %rax

loop_strlen_utf8:
    movzbq (%rdi), %rdx # Load byte at address rdi into rdx, zero-extend to 64-bit
    test %rdx, %rdx
    je null_char # reached 0 byte/null char

    # Check if the byte is a UTF-8 continuation byte
    mov $0xC0, %r8 # 0xC0 = 0b11000000, load into r8
    and %r8, %rdx # Perform bitwise AND 

    # check if it's a contiuation byte 
    cmp $0x80, %rdx # 0x80 = 0b10000000
    je skip_increment

    # not continuation byte, is a valid char, increment
    add $1, %rax 
    # continue to skip inc to also increment next byte and loop

skip_increment:
    # move to next byte and loop again
    add $1, %rdi
    jmp loop_strlen_utf8

null_char:
    ret
