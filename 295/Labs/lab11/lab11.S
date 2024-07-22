# By Randy Panopio
# ID: 301294517
# rpanopio@sfu.ca 
    .section .note.GNU-stack, ""
    .global dot_double_vec, dot_single_vec, map_poly_double_vec, map_poly_single_vec, dot_double, dot_single, map_poly_double, map_poly_single
.data

.text

dot_double_vec:
    # rdi is address to arr1, rsi is address to arr2, rdx is len of arr
    vpxor %ymm0, %ymm0, %ymm0  # Clear ymm0 to hold the result (0.0)
    xor %rcx, %rcx             # Clear rcx to use as the loop counter

dot_loop_double_vec:
    # Check if the counter (rcx) has reached the length (rdx)
    cmp %rdx, %rcx
    jge dot_combine_double_vec 

    vmovupd (%rdi,%rcx,8), %ymm1   # Load 4 values from arr1 into ymm1
    vmovupd (%rsi,%rcx,8), %ymm2   # Load 4 values from arr2 into ymm2
    # Multiply and add to the result in ymm0
    vmulpd %ymm1, %ymm2, %ymm3     # Multiply %ymm1 by %ymm2 and store in %ymm3
    vaddpd %ymm3, %ymm0, %ymm0     # Add %ymm3 to %ymm0

    add $4, %rcx                   # Increment the loop counter by 4, completing processing 4 values
    jmp dot_loop_double_vec
    ret

dot_combine_double_vec:
    # combines the ymm 256 bit register to the final 64 bit output value and set it to our output xmm0
    # Extract the upper 128 bits of ymm0 into xmm1
    vextractf128 $0x1, %ymm0, %xmm1
    vaddpd %xmm1, %xmm0, %xmm0
    vshufpd $0b01, %xmm0, %xmm0, %xmm1
    vaddsd %xmm1, %xmm0, %xmm0
    ret

dot_single_vec:
    # rdi is address to arr1, rsi is address to arr2, rdx is len of arr
    vpxor %ymm0, %ymm0, %ymm0  # Clear ymm0 to hold the result (0.0)
    xor %rcx, %rcx             # Clear rcx to use as the loop counter

dot_loop_single_vec:
    # Check if the counter (rcx) has reached the length (rdx)
    cmp %rdx, %rcx
    jge dot_combine_single_vec 

    vmovups (%rdi,%rcx,4), %ymm1   # Load 8 values from arr1 into ymm1
    vmovups (%rsi,%rcx,4), %ymm2   # Load 8 values from arr2 into ymm2
    # Multiply and add to the result in ymm0
    vmulps %ymm1, %ymm2, %ymm3     # Multiply %ymm1 by %ymm2 and store in %ymm3
    vaddps %ymm3, %ymm0, %ymm0     # Add %ymm3 to %ymm0

    add $8, %rcx                   # Increment the loop counter by 8, completing processing 8 values (assuming we can process 8 32 bit floats on the passed arrays)
    jmp dot_loop_single_vec
    ret

dot_combine_single_vec:
    # combines the ymm 256 bit register to the final 32 bit output value and set it to our output xmm0
    # Extract the upper 128 bits of ymm0 into xmm1
    vextractf128 $0x1, %ymm0, %xmm1
    vaddps %xmm1, %xmm0, %xmm0
    vshufps $0b11101110, %xmm0, %xmm0, %xmm1
    vaddps %xmm1, %xmm0, %xmm0
    vshufps $0b00010101, %xmm0, %xmm0, %xmm1
    vaddss %xmm1, %xmm0, %xmm0
    ret

map_poly_double_vec:
    xor %rcx, %rcx
    # Broadcast the coefficients to all elements of the ymm registers
    vbroadcastsd %xmm0, %ymm0    # ymm0 = a
    vbroadcastsd %xmm1, %ymm1    # ymm1 = b
    vbroadcastsd %xmm2, %ymm2    # ymm2 = c
    vbroadcastsd %xmm3, %ymm3    # ymm3 = d    

poly_double_loop_vec:
    # If index >= length, exit loop
    cmp %rdx, %rcx
    jge loop_done 

    # Load 4 input values into ymm4
    vmovupd (%rdi,%rcx,8), %ymm4

    # Calculate the polynomial x*(x*(a*x + b) + c) + d
    vmovapd %ymm4, %ymm5        # ymm5 = x
    vmulpd %ymm4, %ymm0, %ymm5  # ymm5 = a * x
    vaddpd %ymm1, %ymm5, %ymm5  # ymm5 = a * x + b
    vmulpd %ymm4, %ymm5, %ymm5  # ymm5 = (a * x + b) * x
    vaddpd %ymm2, %ymm5, %ymm5  # ymm5 = (a * x + b) * x + c
    vmulpd %ymm4, %ymm5, %ymm5  # ymm5 = ((a * x + b) * x + c) * x
    vaddpd %ymm3, %ymm5, %ymm5  # ymm5 = ((a * x + b) * x + c) * x + d

    # Store the result in the output array
    vmovupd %ymm5, (%rsi,%rcx,8)

    add $4, %rcx             # Increment the loop counter by 4
    jmp poly_double_loop_vec

map_poly_single_vec:
    xor %rcx, %rcx
    # Broadcast the coefficients to all elements of the xmm registers
    vbroadcastss %xmm0, %ymm0    # ymm0 = a
    vbroadcastss %xmm1, %ymm1    # ymm1 = b
    vbroadcastss %xmm2, %ymm2    # ymm2 = c
    vbroadcastss %xmm3, %ymm3    # ymm3 = d

poly_single_loop_vec:
    # If index >= length, exit loop
    cmp %rdx, %rcx
    jge loop_done 

    # Load 8 input values into ymm4
    vmovups (%rdi,%rcx,4), %ymm4

    # Calculate the polynomial x*(x*(a*x + b) + c) + d
    vmovaps %ymm4, %ymm5    # ymm5 = x
    vmulps %ymm4, %ymm0, %ymm5  # ymm5 = a * x
    vaddps %ymm1, %ymm5, %ymm5  # ymm5 = a * x + b
    vmulps %ymm4, %ymm5, %ymm5  # ymm5 = (a * x + b) * x
    vaddps %ymm2, %ymm5, %ymm5  # ymm5 = (a * x + b) * x + c
    vmulps %ymm4, %ymm5, %ymm5  # ymm5 = ((a * x + b) * x + c) * x
    vaddps %ymm3, %ymm5, %ymm5  # ymm5 = ((a * x + b) * x + c) * x + d

    # Store the result in the output array
    vmovups %ymm5, (%rsi,%rcx,4)

    add $8, %rcx             # Increment the loop counter by 8
    jmp poly_single_loop_vec

# ------- Copy of Lab 10 ------- 
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