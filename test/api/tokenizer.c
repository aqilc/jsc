#include "../../tok.h"
#include "tests.h"

TEST("Tokenize Single keyword")
	struct Tokens* toks = tokenize("let");
	struct Token* t = toks->toks;
	assert(t->type == DECL);
TEND()

#include "tests_end.h"
