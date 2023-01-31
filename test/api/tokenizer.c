#include "../../tok.h"
#include "tests.h"

#undef TESTINIT
#define TESTINIT struct Tokens* t = 
#undef TESTCLEAN
#define TESTCLEAN tokfree(t);

TEST("Tokenize Single keyword")
	tokenize("let name");
	assert(t->toks[0].type == DECL);
	assert(vlen(t->toks) == 1);
TEND()

TEST("Tokenize Operators")
	tokenize("+");
	subtest("+", t->toks[0].type == OP && t->toks[0].val.op == ADD && vlen(t->toks) == 1);
	
	retokenize(t, "+=");
	subtest("+=", t->toks[0].type == OP && t->toks[0].val.op == ADDSET && vlen(t->toks) == 1);
TEND()

#include "tests_end.h"
