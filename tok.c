#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"
#include "tok.h"

// FOR DEBUG
#include <stdio.h>

// To differentiate our many different types of strings we have sometimes
typedef char* vstr;

static inline void skip(char* s, u32* idx);
static inline vstr symb(char* str, u32 idx);
static inline i32 expect(char* s, u32 idx, char* e);
static inline void parse(struct Tokens* toks, char* str);
static inline u32 findeos(char* s, u32 idx);

hashtable* keywords = NULL;

void init_keywords() {
	keywords = ht(242);
	hti(keywords, "let", new_i(DECL));
	hti(keywords, "fn", new_i(DECL));
	hti(keywords, "struct", new_i(DECL));
	hti(keywords, "if", new_i(IF));
	hti(keywords, "else", new_i(ELSE));
}



struct Tokens* tokenize(char* str) {

	// Initializes the keyword dict
	if(!keywords) init_keywords();

	struct Tokens* toks = malloc(sizeof(struct Tokens));
	toks->toks = vnew();
	toks->vars = ht(200);
	toks->funcs = ht(200);
	toks->structs = ht(200);

	parse(toks, str);
	
	return toks;
}


// Uses existing tokenizer object to tokenize, saves time, space, money and funccalls
void retokenize(struct Tokens* toks, char* str) {
	vclear(toks->toks);
	
	void* item;
	while((item = htdfast(toks->vars))) free(item);
	while((item = htdfast(toks->funcs))) free(item);
	while((item = htdfast(toks->structs))) free(item);
	htreset(toks->vars); htreset(toks->funcs); htreset(toks->structs);
	
	if(*str)
		parse(toks, str);
}

// Frees tokenizer output
void tokfree(struct Tokens* t) {
	vfree(t->toks);
	void* item;
	while((item = htdfast(t->vars))) free(item);
	while((item = htdfast(t->funcs))) free(item);
	while((item = htdfast(t->structs))) free(item);
	htfree(t->vars); htfree(t->funcs); htfree(t->structs);
	free(t);
}




static inline void parse(struct Tokens* toks, char* str) {
	u32 idx = 0;
	struct Token* t = toks->toks;

	// Makes it easy to push tokens
	#define tok(x, l, ...) push(t, { .loc = idx, .type = x, .len = l, __VA_ARGS__ }), idx += l//,\
		// printf("\nPushed token '"#x"' with length %d at idx %d on line %d", l, idx - l, __LINE__)
	#define last t[vlen(t) - 1]
	#define throw(...) { error_at(str, idx, __VA_ARGS__); goto error; }
	#define SKIP skip(str, &idx);

	while (str[idx]) {
		// printf("%c", str[idx]);
		
		if(isspace(str[idx])) goto end;

		// Evaluates a number
		if(isdigit(str[idx])) {
			int num; u32 len = 1;

			// If the number is longer than just a single digit, do a lot of stuff ig
			if(isdigit(str[idx + 1])) {
				
				// Create a vector string to keep track of number chars
				vstr numstr = vnew();
				while(isdigit(str[idx]))
					push(numstr, str[idx]), idx++;
				len = vlen(numstr);
				push(numstr, 0);
			
				num = atoi(numstr);
			} else num = str[idx] - '0';

			tok(NUM, len, .val = num);
			continue;
		}

		// Operators
		switch(str[idx]) {
			case '=': tok(OP, 1, .val = { .op = SET }); continue;
			case '+':
				if(str[idx + 1] == '=') {
					tok(OP, 2, .val = { .op = ADDSET });
					continue;
				}
				tok(OP, 1, .val = { .op = ADD });
				continue;
		}

		if(isalpha(str[idx])) {
			vstr sym = symb(str, idx);
			push(sym, 0);
			enum TokenType* token = htg(keywords, sym);
			if(token) {
				switch(*token) {
					case DECL:

						// TODO: FUNCTIONS PLS FINISH THIS AND DON'T EXPECT THIS TO WORK
						if(sym[0] == 'f') {

							// Expect name after function
							tok(DECL, 2, .val = { .decl = FN });
							SKIP
							if(!isalpha(str[idx])) throw("Expected function name after 'fn'.");
							
							vstr name = symb(str, idx);
							tok(IDENT, vlen(name), .val = { .s = name });

							i32 paren = expect(str, idx, "(");
							if(paren < 0) throw("Expected '(' after function name in function declaration.");
							
						} else if(sym[0] == 'l') {
							tok(DECL, 3, .val = { .decl = LET });
							SKIP
							if(!isalpha(str[idx]) && str[idx] != '_') throw("Expected identifier after variable declaration, instead got '%c'", str[idx]);

							vstr name = symb(str, idx);
							push(name, 0);
							tok(IDENT, vlen(name) - 1, .val = { .s = name });
							
						}
						continue;
					case ELSE: {
						u32 start = idx;
						idx += 4;
						SKIP

						// Allocs a string for the `if`
						vstr maybeif = symb(str, idx);
						push(maybeif, 0);
						
						// Takes care of `else if`s
						if(vlen(maybeif) && !strcmp(maybeif, "if"))
							push(t, { .loc = start - 4, .type = ELSEIF, .len = idx - start + 4 + 2 });
						
						// Or backtracks if there's no if
						else push(t, { .loc = start - 4, .type = ELSE, .len = 4 });

						vfree(sym); vfree(maybeif);
						continue;
					}
					default:
						tok(*token, vlen(sym) - 1, .val = { .s = sym });
						continue;
				}
			} else {
				tok(IDENT, vlen(sym) - 1, .val = { .s = sym });
				continue;
			}
		}

	end:
		idx++;
		continue;
		
	error:
		// We need to erase the whole line as if it didn't exist
		while(t[vlen(t)].type != EOS) pop(t);
		while(str[idx] && str[idx] != '\n') idx++;
		continue;
	}

	toks->toks = t;
}



static inline vstr symb(char* str, u32 idx) {
	vstr s = vnew();
	while(isalnum(str[idx]) || str[idx] == '_') push(s, str[(idx)++]);
	return s;
}

static inline void skip(char* s, u32* idx) { while(s[*idx] == ' ' || s[*idx] == '\n') (*idx)++; }
static inline u32 findeos(char* s, u32 idx) {
	while(s[idx]
		&& ((s[idx] == '/' && s[idx+1] == '/')
		|| s[idx] == ';' || s[idx] == '\n')) idx ++;
	return idx;
}


static inline i32 expect(char* s, u32 idx, char* e) {
	while(s[idx] == ' ' || s[idx] == '\n') idx++;

	// Since strlen takes C string, we need to put a 0 at the end of the string we need to compare to cut it off :(
	u32 len = strlen(e);
	char tmp = s[len];
	s[len] = 0;
	if(strcmp(s, e)) return -1;
	s[len] = tmp;

	return idx;
}


