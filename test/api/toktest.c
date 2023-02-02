#include "../../tok.h"
#include "tests.h"

#undef TESTINIT
#define TESTINIT 
#undef TESTCLEAN
#define TESTCLEAN tokfree(t);

TEST("Retokenization resetting buffers.")
	struct Tokens* t = tokenize("let hey bruh");
	asserteq(vlen(t->toks), 3);
	substart("Retokenize 1 time");
	retokenize(t, "");
	subend(vlen(t->toks) == 0);
TEND()

TEST("Tokenize 'let' declaration")
	struct Tokens* t = tokenize("let name");
	asserteq(vlen(t->toks), 2);
	asserteq(t->toks[0].type, DECL);
TEND()

TEST("Tokenize Operators")
	struct Tokens* t = tokenize("+");
	subtest("+", t->toks[0].type == OP && t->toks[0].val.op == ADD && vlen(t->toks) == 1);


	retokenize(t, "+=");
	substart("+=");
	asserteq(t->toks[0].type, OP); 
	asserteq(t->toks[0].val.op, ADDSET);
	asserteq(vlen(t->toks), 1);
	subend(1);
TEND()

#include "tests_end.h"
