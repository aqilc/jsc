#include "vec.h"

enum TokenType {
	ERROR,
	NUM,
	OP, // 0 = addition, 1 = sub, 2 = mul, 3 = div
	SYMBOL,
	DECLARATION,
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

