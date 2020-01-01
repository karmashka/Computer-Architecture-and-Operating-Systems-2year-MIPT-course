.intel_syntax noprefix
.global calc
.global vector_sum

.text

calc:
	movsd xmm0, [esp+4] # load A 
	movsd xmm1, [esp+12] # load B
	movsd xmm2, [esp+20] # load C
	cvtsi2sd xmm3, [esp + 28] #load D

	addsd xmm0, xmm1 # A + B
	addsd xmm2, xmm3 # C + D

	divsd xmm0, xmm2 # A + B / C + D

	sub esp, 8
	movsd [esp], xmm0 # take result to stack top
	fld qword ptr [esp] # in x87 stack sp(0) = xmm0
	add esp, 8
	ret

vector_sum:
	mov ecx, 0			# loop counter
	mov eax, [esp + 8]	# load ptr to arr A 
	mov edx, [esp + 12] # load ptr to arr B
	push ebx 			# caller safe
	mov ebx, [esp + 16]	# load ptr to arr R

loop:
	movaps xmm0, [eax + ecx * 4] # load elem from A
	movaps xmm1, [edx + ecx * 4] # load elem from B

	addps xmm0, xmm1			# add elem from A and from B
	movaps [ebx + ecx * 4], xmm0 # load result at arr R

	add ecx, 4	# dec loop counter
	cmp ecx, [esp + 4]	
	jne loop

	pop ebx
	ret
