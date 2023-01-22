#include "codegen.h"
#include "string.h"

struct envinfo env = {0};



void _init() {
	void* tmp;
	if(env.vars) while(tmp = htdfast(env.vars)) free(tmp);
	if(env.vars) while(tmp = htdfast(env.vars)) free(tmp);
	env.vars = ht(788);
	env.functions = ht(902);
	env.cur = 0;
}

char* codegen() {
	
}
