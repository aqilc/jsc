#include <stdbool.h>
#include "helpers.h"
#include "util/vec.h"
#include "util/hash.h"

enum TokenType {
	// ERROR,
	TTNUM,
	TTSTRING,
	TTOP, // See enum below
	TTARG, // for functions, maybe generics
	TTPAREN,
	TTIDENT, // val = string
	TTKEYWORD,
	TTDECL,
	TTEOS, // END OF STATEMENT (0 = newline, 1 = semicolon)
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
			OPADD, OPSUB, OPMUL, OPDIV, OPMOD, OPSET, // basic operations
			OPADDSET, OPSUBSET, OPMULSET, OPDIVSET, OPMODSET, // operations with assignment
			OPSHIFTRIGHT, OPSHIFTLEFT, // bitshifts
			OPXOR, OPAND, OPOR, // bitwise operations
			OPPOW, // power
			OPINCR, OPDECR, // Increment and decrement
			OPGREATER, OPLESS, OPEQ, OPGREATEQ, OPLESSEQ, OPNOTEQ, // Comparisons
		} op;
		
		char* s; // For parsed strings
	} val;
};

struct Tokens {
	struct Token* toks;
};

struct Tokens* tokenize(char* str);
void retokenize(struct Tokens* toks, char* str);
void tokfree(struct Tokens* t);
