#include "../../tok.h"
#include "tests.h"

#undef TESTINIT
#define TESTINIT struct Tokens* t = 
#undef TESTCLEAN
#define TESTCLEAN tokfree(t);

TEST("Retokenization resetting buffers.")
	tokenize("let hey bruh");
	asserteq(vlen(t->toks), 3);
	retokenize(t, "");
	asserteq(vlen(t->toks), 0);
TEND()

TEST("Numbers")
	tokenize("1");
	asserteq(vlen(t->toks), 1);
	
TEND()

TEST("Tokenize 'let' declaration")
	tokenize("let name = 2");
	asserteq(vlen(t->toks), 4);
	asserteq(t->toks[0].type,   DECL);
	asserteq(t->toks[1].type,   IDENT);
	asserteq(t->toks[2].type,   OP);
	asserteq(t->toks[2].val.op, SET);
	asserteq(t->toks[3].type,   NUM);
TEND()

TEST("Tokenize Operators")
	tokenize("+");
	subtest("+", t->toks[0].type == OP && t->toks[0].val.op == ADD && vlen(t->toks) == 1);


	retokenize(t, "+=");
	// asserteq(t->toks[0].type, OP);
	// asserteq(t->toks[0].val.op, ADDSET);
	// asserteq(vlen(t->toks), 1);
	// substart("+=");
	subtest("+=", t->toks[0].type == OP && t->toks[0].val.op == ADDSET && vlen(t->toks) == 1);
TEND()

#include "tests_end.h"
