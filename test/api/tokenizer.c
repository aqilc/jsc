#include "../../tok.h"
#include "tests.h"

#undef TESTINIT
#define TESTINIT struct Tokens* t = 
#undef TESTCLEAN
#define TESTCLEAN tokfree(t);

TEST("Tokenize Single keyword")
	tokenize("let");
	assert(t->toks[0].type == DECL);
	assert(vlen(t->toks) == 1);
TEND()

TEST("Tokenize Operator +")
	tokenize("+");
	assert(t->toks[0].type == OP);
	assert(vlen(t->toks) == 1);
TEND()

#include "tests_end.h"
