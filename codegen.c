#include "codegen.h"
#include "string.h"

/*
https://sonictk.github.io/asm_tutorial/
https://stackoverflow.com/questions/36529449/why-are-rbp-and-rsp-called-general-purpose-registers
* 16 Registers on an x64 cpu: rax, rbx, rcx, rdx, rbp, rsi, rdi, rsp, r8, r9, r10, r11 r12, r13, r14 and r15
* rbp = base of stack frame, rsp = current place in stack
* rax subsets:
	* (a in rax) al (first 8), (a in rax) ah (second 8)
	* (a in rax) ax(first word(16))
	* eax(first 32 bits)
	* Can be used for other registers ending in x

*/



char* codegen(struct Token* t) {
	char* ret = vnew();

	pushsf(ret,
	"	.globl main\n"
	"main:\n"
	"	push %rbp\n"
	"	mov %rsp, %rbp\n"
	"	mov $%d, %rsp\n", 128); pushsf(ret,
	"");
	
	
	return ret;
}
