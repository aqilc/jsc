#include "codegen.h"
#include "string.h"

struct envinfo env = {0};



void _init() {
	if(env.vars) 
	env.vars = ht(788);
	env.functions = ht(902);
	env.cur = 0;
}

char* codegen() {
	
}
