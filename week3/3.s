.text
.global sort_by_age

//typedef struct Person {
//    uint32_t  id;
//    uint8_t   age;
//    char      first_name[20];
//    char      last_name[20];
//} person_t;


sort_by_age:
	push {r4-r9, lr} // i = r4, j = r5, arr r7, N = r6, r2 = left_elem, r3 = right
	mov r4, r0 // i = N - 1
	sub r4, r4, #1
	mov r6, r0

	mov r7, r1
external_loop:
	cmp r4, #0
	ble exit
	mov r5, #0 // j = 0

interior_loop:
	
	cmp r5, r4 // j < i
	subeq r4, r4, #1
	beq external_loop

	mov r0, r7 // pointer to arr[j] 
	mov r3, #48
	mul r3, r5, r3
	add r0, r0, r3
	add r1, r0, #48 // pointer to arr[j + 1]
	ldrb r2, [r0, #4]
	ldrb r3, [r1, #4]
	cmp r2, r3
	blgt swap
	add r5, r5, #1 //j+1
	b interior_loop

exit:
	pop {r4-r9, pc}

swap:
	push {r4-r7, lr}
	strb r3, [r0, #4]
	strb r2, [r1, #4]
	ldr r2, [r0]
	ldr r3, [r1]
	str r3, [r0]
	str r2, [r1]
	mov r5, #5
loop:
	cmp r5, #45
	beq loop_end
	ldr r2, [r0, r5]
	ldr r3, [r1, r5]
	str r2, [r1, r5]
	str r3, [r0, r5]
	add r5, r5, #4
	b loop

loop_end:
	pop {r4-r7, pc}

	