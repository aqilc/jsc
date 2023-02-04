#include "codegen.h"
#include "string.h"

/*
https://sonictk.github.io/asm_tutorial/
https://stackoverflow.com/questions/36529449/why-are-rbp-and-rsp-called-general-purpose-registers
https://stackoverflow.com/questions/892928/why-are-x86-registers-named-the-way-they-are

ASSEMBLY MAIN IDEAS:
	REGISTERS:
		* 14 General Purpose Registers on an x64 cpu: rax, rbx, rcx, rdx, rdi, rsi, r8, r9, r10, r11 r12, r13, r14 and r15
			* AX: Accumulator, BX: Base, CX: Counter, DX: Data
			* r_x subsets:
				* _l (first 8), _h (second 8)
				* _x(first word(16))
				* e_x(first 32 bits)
				* Can be used for other registers ending in x
		* 2 Special Purpose registers: rbp, rsp
			* rbp: Stack base pointer
			* rsp: Stack pointer
		* %rip = Instruction pointer.

	NOTES:
		* lea %rax, [rel main]: moves the function ptr of main to %rax

REFERENCES:
	* https://github.com/rui314/chibicc/blob/f814033d04c4cefdbcf8174d65011d484d69303c/codegen.c
*/



char* codegen(struct Tokens* t) {
	char* ret = vnew();

	pushsf(ret,
	"	.globl main\n"
	"main:\n"
	"	push %rbp\n"
	"	mov %rsp, %rbp\n"
	"	mov $%d, %rsp\n", 128); pushsf(ret,
	"	ret");
	
	
	return ret;
}
