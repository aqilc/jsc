#include "../util/vec.h"
#include "helpers.h"

char* rdata = NULL;
char* data  = NULL;
char* prog  = NULL;

void export(init)() {
	rdata = strtov("section .rdata\n");
	ins(rdata, "db 0");
	// data  = strtov("section .data");
	prog  = strtov(
"global _start\n"
"section .text\n"
"_start:\n"
"push rbp\n"
"mov rbp, rsp\n"
"sub rsp, 0x1000\n"); // stack size :o but need to keep it 16 byte aligned owo
}

void export(exit)() {
	ins(prog, "xor rax, rax", "ret");
}

char* export(prog)() {
	pushv(rdata, prog);
	return vtostr(rdata);
}

