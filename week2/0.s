.text
.global f

f:
mul r1, r3, r1 // Bx
mul r0, r3, r0 // Ax
mul r0, r3, r0 // Ax^2
add r0, r2, r0 // Ax^2 + C
add r0, r1, r0 // Ax^2 + C + Bx
bx lr