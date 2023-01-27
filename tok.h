#include "util/vec.h"
#include "util/hash.h"

enum TokenType {
	ERROR,
	NUM,
	CHAR, STRINGOPEN,
	OP, // 0: +, 1: -, 2: *, 3: /, 4: =, 5: ++, 6: --, 7: >, 8: <, 9: ==, 10: >=, 11: <=, 12: +=, 13 = -=
	IDENT, // val = string
	DECLARATION, // 0 = var, 1 = fun, 2 = struct
	FN, RETURN,
	IF, ELSE, ELSEIF,
	EOS, // END OF STATEMENT (0 = newline, 1 = semicolon)
};

struct Token {
	enum TokenType type;
	u32 loc;
	u32 len;
	
	union {
		u64 i;
		enum {
			ADD, SUB, MUL, DIV, SET,
			ADDSET, SUBSET,
			INCR, DECR,
			GREATER, LESS, EQ, GREATEQ, LESSEQ,
		} op;
		char* str;
	} val;
};

struct Tokens {
	struct Token* toks;
	
	hashtable* vars;
	hashtable* funcs;
	hashtable* structs;
};

struct Tokens* tokenize(char* str);
char* skip(char* s);
