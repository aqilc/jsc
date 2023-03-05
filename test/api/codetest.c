#include "tests.h"
#include "../../codegen.h"

#undef TESTCLEAN
#define TESTCLEAN treset();

// Func ptr definitions
void  (*cdg_exit)(void);
void  (*cdg_init)(void);
char* (*cdg_prog)(void);


int exitc = 0, initc = 0, progc = 0;

// Func ptr definitions
void  texit(void) {
	exitc++;
}
void  tinit(void) {
	initc++;
}
char* tprog(void) {
	progc++;
	return NULL;
}
void treset() { exitc = 0, initc = 0, progc = 0; }

void load_back(char* s) {}



TEST("Nothing")
	cdg_prog = tprog;
	cdg_init = tinit;
	cdg_exit = texit;
	
	char* res = codegen(tokenize(""));
	
	asserteq(exitc, 1);
	asserteq(initc, 1);
	asserteq(progc, 1);
TEND()

#include "tests_end.h"
