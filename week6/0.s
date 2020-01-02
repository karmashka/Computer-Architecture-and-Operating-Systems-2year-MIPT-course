#include <asm/unistd_32.h>
.intel_syntax noprefix

.global _start

.text

_start:
    mov eax, __NR_write //print hello world
    mov ebx, 1
    mov ecx, ptr_to_string
    mov edx, 14
    int 0x80

    mov eax, __NR_exit
    mov ebx, 1
    int 0x80


.data
	
string:
	.string "Hello, World!\n"
ptr_to_string:
	.long string