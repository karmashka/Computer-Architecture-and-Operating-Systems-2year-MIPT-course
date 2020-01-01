.text
.global main

main:
    push {r4, lr}
    ldr r0, =input  //load 1st arg of scanf
    sub sp, sp, #8  //take stack space
    mov r1, sp      //poiner to stack
    add r2, r1, #4  
    bl scanf

    ldr r3, [sp]    //load variables from stack
    ldr r4, [sp, #4]
    add r1, r3, r4

    ldr r0, =output //load 1st arg for printf  
    bl printf
    
    add sp, sp, #8  //return stack space
    mov r0, #0     
    pop {r4, pc}

.data
input: .asciz "%d %d"
output: .asciz "%d\n"