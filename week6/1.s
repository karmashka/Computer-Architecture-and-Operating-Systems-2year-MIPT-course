#include <asm/unistd_32.h>
.intel_syntax noprefix

.global _start

.text

_start:    
    sub esp, SIZE
loop:
    mov eax, __NR_read
    mov ebx, 0 // stdin
    mov ecx, esp
    mov edx, SIZE
    int 0x80

    cmp eax, 0
    je end

    mov edx, eax
    mov eax, __NR_write
    mov ebx, 1 // stdout
    mov ecx, esp
    int 0x80
    jmp loop

end:
    add esp, SIZE
    mov eax, __NR_exit
    mov ebx, 1 // return value
    int 0x80


.data

    SIZE:
    .long 8192
