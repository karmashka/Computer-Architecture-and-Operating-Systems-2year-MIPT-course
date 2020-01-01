.text
.global summ

summ:

loop:
	cmp r1, #0
	beq exit
	ldr r3, [r2]
	add r2, #4
	add r0, r3, r0
	sub r1, #1  
	b loop
	
exit:

	bx lr