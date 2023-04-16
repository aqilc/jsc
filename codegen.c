#include "codegen.h"
#include "string.h"

/*
https://sonictk.github.io/asm_tutorial/
https://stackoverflow.com/questions/36529449/why-are-rbp-and-rsp-called-general-purpose-registers
https://stackoverflow.com/questions/892928/why-are-x86-registers-named-the-way-they-are

god dang it why is assembly like this: https://c.compiler-explorer.com/z/K9aon84rE

ASSEMBLY MAIN IDEAS:
	REGISTERS:
		* 14 General Purpose Registers on an x64 cpu: rax, rbx, rcx, rdx, rdi, rsi, r8, r9, r10, r11 r12, r13, r14 and r15
			* General purpose registers:
				* AX: Accumulator, BX: Base, CX: Counter, DX: Data
				* _l (first 8), _h (second 8)
				* _x(first word(16 bits))
				* e_x(first 32 bits)
				* r_x(first 64 bits)
				* Can be used for other registers ending in x
		* 2 Special Purpose registers: rbp, rsp
			* rbp: Stack base pointer
			* rsp: Stack pointer
		* rip = Instruction pointer.

	NOTES:
		* lea rax, [rel main]: moves the function ptr of main to %rax

REFERENCES:
	* https://github.com/rui314/chibicc/blob/f814033d04c4cefdbcf8174d65011d484d69303c/codegen.c
	* https://social.msdn.microsoft.com/Forums/vstudio/en-US/71a80e19-4e6a-41fe-b1db-26e331da474d/linking-errors-lnk2001-unresolved-external-symbol-when-compiled-by-nasm?forum=vclanguage
*/


// References to global variable IDs
ht(char*, int) cdg_gvars;

char* codegen(struct Tokens* t) {
	
	cdg_init();

	switch (t->toks[0].type) {
		default: break;
	}


	cdg_exit();
	
	return cdg_prog();
}



// Parses an expression using the shunting yard algorithm
void expr(struct Tokens* t) {


}