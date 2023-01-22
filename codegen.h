#include "util/vec.h"
#include "tok.h"
#include "util/hash.h"

struct envinfo {
	hashtable* vars;
	hashtable* functions;
	struct Token* toks;
	u32 cur;
};
