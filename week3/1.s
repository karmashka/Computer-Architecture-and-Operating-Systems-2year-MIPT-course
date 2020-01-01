.text
.global main

main:
    push {r4, lr}

begin:
    ldr r0, =stdin
    ldr r0, [r0]
    bl fgetc
    cmp r0, #-1   // check if EOF
    beq exit

    mov r4, r0
    bl isdigit
    cmp r0, #0
    mov r0, r4    // prepare arg for fputc
    ldr r1, =stdout
    ldr r1, [r1]
    blne fputc
    b begin

exit:
    mov r0, #0
    pop {r4, pc}