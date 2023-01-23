#include <ctype.h>
#include <stdlib.h>
#include "tok.h"

struct Token* tokenize(char* str) {
	struct Token* t = vnew();

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

		// Pushes an error token, increasing length as there are more of them
		if(t[vlen(t) - 1].type != ERROR)
			push(t, { .loc = str, .type = ERROR, .len = 1 });
		else t[vlen(t) - 1].len ++;

		end:
		str++;
	}
	
	return t;
}
