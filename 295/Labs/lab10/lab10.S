# By Randy Panopio
# ID: 301294517
# rpanopio@sfu.ca 
    .section .note.GNU-stack, ""
    .global dot_double, dot_single, sin_x87, map_poly_double, map_poly_single
.data

.text

dot_double:
    # rdi is address to arr1, rsi is address to arr2, rdx is len of arr
    pxor %xmm0, %xmm0  # Clear xmm0 to hold the result (0.0)
    xor %rcx, %rcx     # Clear rcx to use as the loop counter

dot_loop_double:
    # Check if the counter (rcx) has reached the length (rdx)
    cmp %rdx, %rcx
    jge loop_done

    # get products
    # (starting address, n offset * word size (8 for 64bit))
    # Load double precision float values into xmm registers
    movq (%rdi, %rcx, 8), %xmm1  # Load arr1[i] into xmm1
    movq (%rsi, %rcx, 8), %xmm2  # Load arr2[i] into xmm2
    # Multiply and add to the result in xmm0
    mulsd %xmm2, %xmm1  # Multiply xmm1 by xmm2 and store in xmm1
    addsd %xmm1, %xmm0  # Add xmm1 to xmm0

    inc %rcx
    jmp dot_loop_double
    ret


dot_single:
    # rdi is address to arr1, rsi is address to arr2, rdx is len of arr
    pxor %xmm0, %xmm0  # Clear xmm0 to hold the result (0.0)
    xor %rcx, %rcx     # Clear rcx to use as the loop counter

dot_loop_single:
    # Check if the counter (rcx) has reached the length (rdx)
    cmp %rdx, %rcx
    jge loop_done

    # get products
    # (starting address, n offset * word size (8 for 64bit))
    # Load double precision float values into xmm registers
    movd (%rdi, %rcx, 4), %xmm1  # Load arr1[i] into xmm1
    movd (%rsi, %rcx, 4), %xmm2  # Load arr2[i] into xmm2
    # Multiply and add to the result in xmm0
    mulss %xmm2, %xmm1  # Multiply xmm1 by xmm2 and store in xmm1
    addss %xmm1, %xmm0  # Add xmm1 to xmm0
    
    inc %rcx
    jmp dot_loop_single
    ret



map_poly_double:
    # rdi - ptr input array -> x, treated as int even if its a double ptr
    # rsi - ptr output array
    # rdx - length of the array
    # xmm0 - a -> first double arg so xmm0
    # xmm1 - b
    # xmm2 - c
    # xmm3 - d
    xor %rcx, %rcx  # Clear rcx to use as the loop index

poly_double_loop:
    # If index >= length, exit loop
    cmp %rdx, %rcx
    jge loop_done 

    # Load the input value, xmm4 = x
    movq (%rdi, %rcx, 8), %xmm4

    # Calculate the polynomial x*(x*(a*x + b) + c) + d
    movq  %xmm4, %xmm5    # xmm5 = x
    mulsd %xmm0, %xmm5    # xmm5 = a * x
    addsd %xmm1, %xmm5    # xmm5 = a * x + b
    mulsd %xmm4, %xmm5    # xmm5 = (a * x + b) * x
    addsd %xmm2, %xmm5    # xmm5 = (a * x + b) * x + c
    mulsd %xmm4, %xmm5    # xmm5 = ((a * x + b) * x + c) * x
    addsd %xmm3, %xmm5    # xmm5 = ((a * x + b) * x + c) * x + d

    # Store the result in the output array
    movq %xmm5, (%rsi, %rcx, 8)

    inc %rcx
    jmp poly_double_loop
    ret

map_poly_single:
    # do the same, but single precision
    xor %rcx, %rcx  # Clear rcx to use as the loop index

poly_single_loop:
    # If index >= length, exit loop
    cmp %rdx, %rcx
    jge loop_done 

    # Load the input value, xmm4 = x
    movd (%rdi, %rcx, 4), %xmm4

    # Calculate the polynomial x*(x*(a*x + b) + c) + d
    movq  %xmm4, %xmm5    # xmm5 = x, must be movq for some reason
    mulss %xmm0, %xmm5    # xmm5 = a * x
    addss %xmm1, %xmm5    # xmm5 = a * x + b
    mulss %xmm4, %xmm5    # xmm5 = (a * x + b) * x
    addss %xmm2, %xmm5    # xmm5 = (a * x + b) * x + c
    mulss %xmm4, %xmm5    # xmm5 = ((a * x + b) * x + c) * x
    addss %xmm3, %xmm5    # xmm5 = ((a * x + b) * x + c) * x + d

    # Store the result in the output array
    movd %xmm5, (%rsi, %rcx, 4)

    inc %rcx
    jmp poly_single_loop
    ret

loop_done:
    ret

sin_x87:
    mov $0, %rcx
s87_loop:
    cmp %rdx, %rcx
    jae s87_ret
    fldl (%rdi, %rcx, 8)
    fsin
    fstpl (%rsi, %rcx, 8)
    inc %rcx
    jmp s87_loop
s87_ret:
    ret


foo:
    ret
    # a = a*x*x*x 
    # mulsd %xmm9, %xmm0
    # mulsd %xmm9, %xmm0
    # mulsd %xmm9, %xmm0

    # b = b*x*x
    # mulsd %xmm9, %xmm1
    # mulsd %xmm9, %xmm1

    # c = c*x
    # mulsd %xmm9, %xmm2

    # add regs, use xmm7
    # movq %xmm3, %xmm7
    # addsd %xmm1, %xmm7
    # addsd %xmm2, %xmm7
    # addsd %xmm3, %xmm7
