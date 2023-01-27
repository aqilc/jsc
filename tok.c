#include <ctype.h>
#include <stdlib.h>
#include "errors.h"
#include "tok.h"


char* expect() {
	
}

struct Tokens* tokenize(char* str) {
	char* start = str;
	u32 idx = 0;
	
	struct Token* t = vnew();
	hashtable* vars;
	hashtable* funcs;
	hashtable* structs;

	// Makes it easy to push tokens
	#define pusht(...) push(t, { .loc = idx, .type = __VA_ARGS__ })

	while (str[idx]) {
		if(isspace(str[idx])) goto end;

		// Evaluates a number
		if(isdigit(str[idx])) {
			int num; u32 len;

			// If the number is longer than just a single digit, do a lot of stuff ig
			if(isdigit(str[1])) {
				
				// Create a vector string to keep track of number chars
				char* numstr = vnew();
				while(isdigit(str[idx]))
					push(numstr, str[idx]), idx++;
				len = vlen(numstr);
				push(numstr, 0);
			
				num = atoi(numstr);
			} else num = str[idx] - '0';

			pusht(NUM, .val = num, .len = len);
			goto end;
		}

		// Operators
		switch(str[idx]) {
			case '=': pusht(OP, .val = { .op = SET }, .len = 1); goto end;
			case '+':
				if(str[idx + 1] == '=') {
					pusht(OP, .val = { .op = ADDSET }, .len = 2);
					goto end;
				}
				pusht(OP, .val = { .op = ADD }, .len = 1);
				goto end;
		}

	end:
		idx++;
		continue;
		
	error:
		error_at(start, idx, "Unknown character");
		
		continue;
	}

	struct Tokens* toks = malloc(sizeof(struct Tokens));
	toks->toks = t;
	toks->vars = vars;
	toks->funcs = funcs;
	toks->structs = structs;
	return toks;
}

// Produces an identifier token
struct Token ident(char* str, u32 idx) {
	
	// Skips to where there should be an identifier
	idx = skip(str + idx) - str;
	u32 start = idx;

	// Things we would put in the token
	char* s = vnew();
	enum TokenType t = IDENT;

	// If we start with a letter or _, we have probably found an identifier
	if(isalpha(str[idx]) || str[idx] == '_') push(s, str[idx]);
	else { error_at(str, idx, "Expected identifier, found '%c'", str[idx]); t = ERROR; }

	// Go as long as there's numbers, letters, and _ and collect the full string
	while(isalnum(str[idx]) || str[idx] == '_') push(s, str[idx++]);

	// Return the token we made
	return (struct Token) { .loc = idx, .type = t, .val = { .str = s }, .len = idx - start };
}

char* skip(char* s) { while(*s == ' ' || *s == '\n') s++; return s; }
