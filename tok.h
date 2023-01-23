#include "util/vec.h"
#include "util/hash.h"

enum TokenType {
	ERROR,
	NUM,
	CHAR, STRINGOPEN,
	OP, // 0 = addition, 1 = sub, 2 = mul, 3 = div, 4 = ++, 5 = --, 6 = >, 7 = <, 8 = ==
	SYMBOL, // val = string
	DECLARATION, // 0 = var, 1 = fun, 2 = struct
	FN, RETURN,
	IF, ELSE, ELSEIF,
	EOS, // END OF STATEMENT (0 = newline, 1 = semicolon)
};

struct Token {
	enum TokenType type;
	char* loc;
	u32 len;

	hashtable* vars;
	
	
	union {
		u64 i;
		char* str;
	} val;
};

struct Token* tokenize(char* str);

