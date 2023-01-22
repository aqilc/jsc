#include "util/vec.h"

enum TokenType {
	ERROR,
	NUM,
	CHAR, STRINGOPEN,
	OP, // 0 = addition, 1 = sub, 2 = mul, 3 = div, 4 = ++, 5 = --, 6 = >, 7 = <, 8 = ==
	SYMBOL,
	DECLARATION,
	FN, RETURN,
	IF, ELSE, ELSEIF
};

// DATA ORIENTED PROGRAMMING POG
struct Token {
	enum TokenType type;
	char* loc;
	u32 len;
	
	union {
		u64 i;
		char* str;
	} val;
};

struct Token* tokenize(char* str);

