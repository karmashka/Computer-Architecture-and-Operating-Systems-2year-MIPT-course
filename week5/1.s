.intel_syntax noprefix
.text

.global my_sin

my_sin:
	push ebp
	mov ebp, esp
	xorpd xmm0, xmm0 #xmm0 = 0 old
	movsd xmm1, [ebp + 8] #xmm1 = x, res
	mov eax, 1
	cvtsi2sd xmm2, eax #xmm2 = 1, fac
	cvtsi2sd xmm3, eax #xmm3 = 1, sgn
	movsd xmm4, [ebp + 8] #xmm4 = x, xn
	mov ecx, 3 
	mov edx, -1
	movsd xmm7, [ebp + 8] #xmm7 = x
	mulsd xmm7, xmm7

loop:
	movsd xmm0, xmm1 #old = res

	cvtsi2sd xmm5, ecx #xmm5 = i
	mulsd xmm2, xmm5	#fac *= i
	cvtsi2sd xmm6, eax #xmm6 = 1
	subsd xmm5, xmm6 #xmm5= i - 1
	mulsd xmm2, xmm5 # fac*= i -1

	cvtsi2sd xmm6, edx #xmm6 = -1
	mulsd xmm3, xmm6 #sgn *= -1

	mulsd xmm4, xmm7 #xn *= x * x

	movsd xmm6, xmm4
	mulsd xmm6, xmm3
	divsd xmm6, xmm2 #xmm6 = xn * sgn / fac


	addsd xmm1, xmm6 #res += xn * sgn / fac
	
	add ecx, 2
	comisd xmm1, xmm0 #if res != old loop
	jne loop

	sub esp, 8
	movsd [esp], xmm0
	fld qword ptr [esp]
	add esp, 8
	mov esp, ebp
	pop ebp
	ret
