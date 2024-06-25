# By Randy Panopio
# ID: 301294517
# rpanopio@sfu.ca 
    .section .note.GNU-stack, ""
    .global randint, fill_array, dot_struct, dot

.data
randint_seed:
    .quad 0

.text

randint:
    # retrieve current seed
    mov randint_seed(%rip), %rax 
    
    # seed = seed * 6364136223846793005 + 1442695040888963407
    movabs $6364136223846793005, %rbx
    mul %rbx
    movabs $1442695040888963407, %rbx

    # set seed calculation into rax
    add %rbx, %rax  

    # store the new seed back
    mov %rax, randint_seed(%rip) 
    ret

fill_array:
    # rdi is address to arr, rsi is len of arr
    mov $0, %rcx

fill_loop:
    # Check if the counter (rcx) has reached the length (rsi)
    cmp %rsi, %rcx
    jge loop_done

    # maybe TODO, preserve registers, but since I know what randint does, its fine
    # Call rand to get the value
    call randint
    
    # set value (from randint) to the current iteration of the array 
    mov %rax, (%rdi, %rcx, 8)
    
    # increment iterator and loop
    inc %rcx
    jmp fill_loop
    ret

dot:
    # rdi is address to arr1, rsi is address to arr2, rdx is len of arr
    mov $0, %rax
    mov $0, %rcx

dot_loop:
    # Check if the counter (rcx) has reached the length (rdx)
    cmp %rdx, %rcx
    jge loop_done

    # get products
    # (starting address, n offset * word size (8 for 64bit))
    mov (%rdi, %rcx, 8), %r8 # arr1[i]    
    imul (%rsi, %rcx, 8), %r8 # arr2[i]
    add %r8, %rax

    inc %rcx
    jmp dot_loop
    ret

dot_struct:
    # rdi is address to struct arr, rsi is len of arr
    mov $0, %rax
    mov $0, %rcx
    imul $2, %rsi

dot_struct_loop:
    # Check if the counter (rcx) has reached the length (rsi)
    cmp %rsi, %rcx
    jge loop_done
    # ([0-63,64-127],[128-x,y-z])
    # n=0,            n=1

    # get products
    # (starting address, n offset * word size (8 for 64bit))
    mov (%rdi, %rcx, 8), %r8 # first int64_t
    mov %rcx, %r9
    inc %r9
    imul (%rdi, %r9, 8), %r8 # second int64_t
    
    add %r8, %rax

    add $2, %rcx # increment by 2
    jmp dot_struct_loop
    ret

loop_done:
    ret

