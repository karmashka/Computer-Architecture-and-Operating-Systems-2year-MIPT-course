.intel_syntax noprefix

.global _start
.text

_start:
    mov eax, 45 # brk
    mov ebx, 0
    int 0x80
    mov [buffer], eax # find start pos

    mov eax, 45
    mov ebx, capacity # allocate memory in heap
    add ebx, [buffer]
    int 0x80
    mov edi, 0 # cur_pos
    
read: #read in chunks, look for newlines after
    mov eax, 3
    mov ecx, [buffer]
    add ecx, edi # start + cur_pos
    mov ebx, 0
    mov edx, 8192 # read 4096 bytes
    int 0x80
    cmp eax, 0
    je start_write # end of read
    add edi, eax
    cmp edi, capacity
    jne read
    mov eax, 45
    mov ebx, capacity
    add ebx, capacity
    mov capacity, ebx # double the capacity
    add ebx, [buffer]
    int 0x80
    jmp read

start_write:
    cmp edi, 0
    jz end
    sub edi, 1
    mov eax, edi
    add eax, [buffer]
    mov eax, [eax]
    cmpb al, endline_character # \n
    je write
    add edi, 1

write:
    cmp edi, 0
    jle end
    mov esi, edi

inner_loop:
    dec esi
    cmp esi, 0
    je print_str
    mov eax, [buffer]
    add eax, esi # check start[esi]
    mov eax, [eax]
    cmpb al, endline_character
    jne inner_loop
    add esi, 1
    jmp print_str # go until \n found

print_str:
    mov al, endline_character
    mov ebx, 1
    mov ecx, [buffer]
    add ecx, esi
    mov edx, edi
    sub edx, esi
    movb [ecx + edx], al # add \n at the end
    mov eax, 4
    inc edx
    mov edi, esi
    dec edi # edi points to \n every time in write_loop
    int 0x80
    jmp write

end:
    mov eax, 1
    mov ebx, 0 
    int 0x80


.data

    buffer:
        .long 0

    capacity:
        .long 8192

    endline_character:
        .byte 10