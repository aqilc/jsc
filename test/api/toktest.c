#include "tests.h"
#include "../../tok.h"

#undef TESTINIT
#define TESTINIT struct Tokens* t = 
#undef TESTCLEAN
#define TESTCLEAN tokfree(t);


u32 lasteidx = 0;
void error_at(char* str, u32 idx, char* msg) {
	lasteidx = idx;
}


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


TEST("Tokenize Operators")
	tokenize("+");
	subtest("Base test: +", t->toks[0].type == OP && t->toks[0].val.op == ADD && vlen(t->toks) == 1);
	
	substart("Basic ops: -, *, /, %%");
		retokenize(t, "-");
		assert(t->toks[0].type == OP && t->toks[0].val.op == SUB && vlen(t->toks) == 1);
		retokenize(t, "*");
		assert(t->toks[0].type == OP && t->toks[0].val.op == MUL && vlen(t->toks) == 1);
		retokenize(t, "/");
		assert(t->toks[0].type == OP && t->toks[0].val.op == DIV && vlen(t->toks) == 1);
		retokenize(t, "%");
		assert(t->toks[0].type == OP && t->toks[0].val.op == MOD && vlen(t->toks) == 1);
	subend(1);

	substart("Setting operations: =, +=, -=, *=, /=, %=");
		retokenize(t, "=");
		assert(t->toks[0].type == OP && t->toks[0].val.op == SET && vlen(t->toks) == 1);
		retokenize(t, "+=");
		assert(t->toks[0].type == OP && t->toks[0].val.op == ADDSET && vlen(t->toks) == 1);
		retokenize(t, "-=");
		assert(t->toks[0].type == OP && t->toks[0].val.op == SUBSET && vlen(t->toks) == 1);
		retokenize(t, "*=");
		assert(t->toks[0].type == OP && t->toks[0].val.op == MULSET && vlen(t->toks) == 1);
		retokenize(t, "/=");
		assert(t->toks[0].type == OP && t->toks[0].val.op == DIVSET && vlen(t->toks) == 1);
		retokenize(t, "%=");
		assert(t->toks[0].type == OP && t->toks[0].val.op == MODSET && vlen(t->toks) == 1);
	subend(1);
TEND()

TEST("Tokenize 'let' declaration")
	tokenize("let name = 2");
	asserteq(vlen(t->toks), 4);
	asserteq(t->toks[0].type,   DECL);
	asserteq(t->toks[1].type,   IDENT);
	asserteq(t->toks[2].type,   OP);
	asserteq(t->toks[2].val.op, SET);
	asserteq(t->toks[3].type,   NUM);
	asserteq(t->toks[3].val.i,  2);
TEND()

TEST("Tokenize function declaration")
	tokenize("fn name(arg1, arg2)");
	asserteq(t->toks[0].type,   DECL);
	asserteq(t->toks[1].type,   IDENT);
	asserteq(t->toks[2].type,   ARGB);
	asserteq(t->toks[3].type,   IDENT);
	asserteq(t->toks[4].type,   ARGSEP);
	asserteq(t->toks[5].type,   IDENT);
	asserteq(t->toks[6].type,   ARGE);
TEND()

#include "tests_end.h"
