.text
.global main

main:
    push {r4-r6, lr}
    ldr r1, =memory_size
    mov r0, #0

    mov r5, r1 // memory size
    mov r6, #0 // current index
    bl realloc
 
    mov r4, r0 // pointer to memory

input:
    ldr r1, =stdin
    ldr r0, [r1]
    bl fgetc

    cmp r0, #-1 // check if EOF
    beq output

    str r0, [r4, r6]
    cmp r5, r6
    add r6, r6, #4
    bgt input
// if buffer is full, then reallocate
    mov r1, #2
    mul r5, r1, r5

    mov r1, r5
    mov r0, r4
    bl realloc

    mov r4, r0
    b input

output:
    sub r6, r6, #4
    cmp r6, #-1
    ble exit_ouput

    ldr r1, =stdout
    ldr r1, [r1]
    ldr r0, [r4, r6]
    bl fputc

    b output

exit_ouput:
    mov r0, #0
    pop {r4-r6, pc}

.data
memory_size: .word 4
