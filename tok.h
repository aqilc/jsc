#include <stdbool.h>
#include "helpers.h"
#include "util/vec.h"
#include "util/hash.h"

enum TokenType {
	// ERROR,
	NUM,
	STRING,
	OP, // See enum below
	ARG, // for functions, maybe generics
	ARGB, ARGE, ARGSEP, // Start + end + separator of args
	SCOPEB, SCOPEE, // Start + end of scopes
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
		
		enum {
			FN, LET, STRUCT, TRAIT
		} decl;
		
		enum {
			// SPECIALLY SET, DO NOT CHANGE ORDER OF BASIC -> ASSIGNMENT VERSIONS OF NORMAL OPS
			ADD, SUB, MUL, DIV, MOD, SET, // basic operations
			ADDSET, SUBSET, MULSET, DIVSET, MODSET, // operations with assignment
			SHIFTRIGHT, SHIFTLEFT, // bitshifts
			XOR, AND, OR, // bitwise operations
			POW, // power
			INCR, DECR, // Increment and decrement
			GREATER, LESS, EQ, GREATEQ, LESSEQ, NOTEQ, // Comparisons
		} op;
		
		char* s; // For parsed strings
	} val;
};

struct Tokens {
	struct Token* toks;
	
	ht(char*, bool) vars;
	ht(char*, bool) funcs;
	ht(char*, bool) structs;
};

struct Tokens* tokenize(char* str);
void retokenize(struct Tokens* toks, char* str);
void tokfree(struct Tokens* t);
