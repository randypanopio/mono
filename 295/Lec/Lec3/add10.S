
; note this is private, need to declare it to be public
; .global add10 
; this code above makes the function add10 public during assembly

; NOTE rax is the register we always return to

add10:
    ; we assumed that arg goes into rdi, and the output read by the pgoram will be in rax

    ; rdi we agree that the coompiler sets the rules it goes to rdi (Linux)

    ; move reg rdi to reg raz. Copy this to that syntax
    ; these are registers (special regs)
    ; there are only a few *16?) registers to work with
    ; very fast
    mov %rdi, %rax

    ; equivalent to rax += 10
    ; % => means the name of register
    ; $-> is a literal eg. $10 -> litearlly 10
    add $10, %rax

    ; return this function call (no actual return? we assume program looks at rax)

    ret