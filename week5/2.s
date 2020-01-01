.intel_syntax noprefix
.global dot_product
.text
#(int N, const float *A, const float *B);
dot_product:
	mov ecx, 0 # loop counter
	mov eax, [esp + 8]	# load ptr to arr A 
	mov edx, [esp + 12] # load ptr to arr B
	xorpd xmm0, xmm0 #xmm0 = 0, result
	push ebx
loop:
	mov ebx, ecx
	add ebx, 4
	cmp ebx, [esp + 8]
	jg loop_end
	movups xmm1, [eax + ecx * 4] # load elem from A
	movups xmm2, [edx + ecx * 4] # load elem from B


	mulps xmm1, xmm2
	addps xmm0, xmm1

	add ecx, 4	# inc loop counter
	jmp loop

loop_end:
	cmp ecx, [esp + 8]
	jge end
	movss xmm1, [eax + ecx * 4]
	movss xmm2, [edx + ecx * 4] 

	mulss xmm1, xmm2
	addps xmm0, xmm1

	add ecx, 1
	jmp loop_end
end:
	haddps xmm0, xmm0
	haddps xmm0, xmm0
	pop ebx
	sub esp, 8
	movsd [esp], xmm0 # take result to stack top
	fld dword ptr [esp] # in x87 stack sp(0) = xmm0
	add esp, 8
	
	ret

