.intel_syntax noprefix

.global A
.global B
.global R
.global N

.global summ
.global everyday795
.text

summ:
    push ebp
    mov ebp, esp
    mov ecx, N
    push ebx
.loop:
    mov eax, ecx # shift indexation
    dec eax 
    
    mov ebx, A
    mov edx, [ebx + 4 * eax] # load from memory number A[i]
    mov ebx, B
    add edx, [ebx + 4 * eax]
    mov ebx, R
    mov [ebx + 4 * eax], edx
    loop .loop

    pop ebx
    pop ebp
    ret

everyday795:
    push ebp
    mov ebp, esp

    sub esp, 4      # allocate space for arg
    mov eax, esp
    mov [esp], eax
    lea eax, input  # load arg for scanf
    push eax
    call scanf
    mov eax, [esp + 4] # load integer, which was read (A)
    add esp, 8

    mov edx, [ebp + 8]  # take X
    imul edx, eax       # A * X
    add edx, [ebp + 12] # take Y, A * X + Y 
    push edx            #save result
    lea eax, output     #load arg for printf
    push eax
    call printf
    add esp, 8
    
    pop ebp
    ret

.data
    input: .asciz "%d"
    output: .asciz "%d\n"   
