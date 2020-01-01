.text
.global solve

solve:
	push {r4-r8}
	mov r4, #0
loop:
	mul r5, r0, r4 // Ax
	mul r5, r4, r5 // Ax^2
	mul r5, r4, r5 // Ax^3
	mul r6, r4, r1 // Bx
	mul r6, r4, r6 // Bx^2
	mul r7, r4, r2 // Cx
	add r8, r5, r6 // Ax^3 + Bx^2
	add r8, r7, r8 // Ax^3 + Bx^2 + Cx
	add r8, r3, r8 // Ax^3 + Bx^2 + Cx + D
	cmp r8, #0
	beq exit
	add r4, #1
	b loop
exit:
	mov r0, r4
	pop {r4-r8}

	bx lr
