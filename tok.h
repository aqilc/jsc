#include "util/vec.h"
#include "util/hash.h"

enum TokenType {
	// ERROR,
	NUM,
	STRING,
	OP, // See enum below
	PAREN, // for functions
	IDENT, // val = string
	DECL, // See enum below
	RETURN,
	IF, ELSE, ELSEIF,
	EOS, // END OF STATEMENT (0 = newline, 1 = semicolon)
};

struct Token {
	enum TokenType type;
	u32 loc;
	u32 len;
	
	union {
		i64 i;
		u64 u;
		float f;
		double d;
		// long double ld;
		enum {
			FN, LET, STRUCT, TRAIT
		} decl;
		enum {
			ADD, SUB, MUL, DIV, SET,
			ADDSET, SUBSET,
			INCR, DECR,
			GREATER, LESS, EQ, GREATEQ, LESSEQ,
		} op;
		char* s; // For parsed strings
	} val;
};

struct Tokens {
	struct Token* toks;
	
	hashtable* vars;
	hashtable* funcs;
	hashtable* structs;
};

struct Tokens* tokenize(char* str);
