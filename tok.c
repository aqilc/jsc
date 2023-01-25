#include <ctype.h>
#include <stdlib.h>
#include "errors.h"
#include "tok.h"


char* expect() {
	
}

struct Tokens* tokenize(char* str) {
	char* start = str;
	struct Token* t = vnew();
	hashtable* vars;
	hashtable* funcs;
	hashtable* structs;

	while (*str) {
		if(isspace(*str)) goto end;

		// Evaluates a number
		if(isdigit(*str)) {
			int num; u32 len;

			// If the number is longer than just a single digit, do a lot of stuff ig
			if(isdigit(str[1])) {
				
				// Create a vector string to keep track of number chars
				char* numstr = vnew();
				while(isdigit(*str))
					push(numstr, *str), str++;
				len = vlen(numstr);
				push(numstr, 0);
			
				num = atoi(numstr);
			} else num = *str - '0';

			push(t, { .loc = str, .type = NUM, .val = num, .len = len });
			goto end;
		}

		if(ispunct(*str)) {
			
		}

		error_at(start, (u32) (str - start), "Unknown character");
		abort();

		end:
		str++;
	}

	struct Tokens* toks = malloc(sizeof(struct Tokens));
	toks->toks = t;
	toks->vars = vars;
	toks->funcs = funcs;
	toks->structs = structs;
	return toks;
}
