global _start
section .rdata
	db 0

section .text
_start:
	xor eax, eax
	ret